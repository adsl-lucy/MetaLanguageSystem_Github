#include "EffOscMaskManager.h"
#pragma execution_character_set("utf-8")

EffOscMaskManager* EffOscMaskManager::m_instance = nullptr;

EffOscMaskManager* EffOscMaskManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new EffOscMaskManager();
	}
	return m_instance;
}

EffOscMaskManager::EffOscMaskManager() :QObject(nullptr)
{
	m_pActiveWndConcurrentWatcher = new QFutureWatcher<void>(this);
	//connect(m_pActiveWndConcurrentWatcher, SIGNAL(finished()), this, SLOT(slot_onFinishedWndActive()));
	connect(m_pActiveWndConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &EffOscMaskManager::slot_WndFFTProgressValueChanged);

}

QString EffOscMaskManager::getWndTypeStr(EN_STFTWndType type)
{
	QString result;
	switch (type)
	{
		case EN_STFTWndType::Rect:result = QString("Rect"); break;
		case EN_STFTWndType::Hann:result = QString("Hann"); break;
	}
	return result;
}

double EffOscMaskManager::getDeltaFreq(int sampleRate, int WndPtCount)
{
	double SecPerPt = 1.0 / (double)sampleRate;
	double WndSec = WndPtCount * SecPerPt;
	double FreqDelta = 1.0 / WndSec;
	return FreqDelta;
}

void EffOscMaskManager::slot_generateSTFTWindow(ST_STFTWnd& WndData)
{
	switch (WndData.WndPara.WndType)
	{
		case EN_STFTWndType::Rect:geneRectSTFTWnd(WndData); break;
		case EN_STFTWndType::Hann:geneHannSTFTWnd(WndData); break;
	}
}

void EffOscMaskManager::slot_StartGenActiveWndPt(ST_ActvieWnd& ActWndResult)
{
	const ST_STFTActiveWndPara& ActWndPara = ActWndResult.WndPara;
	ST_STFTWnd TempSTFTWnd;
	TempSTFTWnd.WndPara = ActWndPara.STFTWndPara;
	slot_generateSTFTWindow(TempSTFTWnd);

	ActWndResult.VecSTFTWndPt.clear();
	ActWndResult.VecActivePt.clear();
	ActWndResult.VecActiveWndPt.clear();

	int pointCount = ActWndPara.STFTWndPara.pointCount;
	if (pointCount < 1)
	{
		return;
	}

	ActWndResult.VecSTFTWndPt = QVector<double>(pointCount, 0);
	ActWndResult.VecActivePt = QVector<double>(pointCount, 0);
	ActWndResult.VecActiveWndPt = QVector<double>(pointCount, 0);

	for (int ptIndex = 0; ptIndex < pointCount; ptIndex++)
	{
		ActWndResult.VecSTFTWndPt[ptIndex] = TempSTFTWnd.VecWndPt[ptIndex];
		if (ptIndex < ActWndPara.startPointPos)
		{
			ActWndResult.VecActivePt[ptIndex] = 0;
		}
		else if (ptIndex >= ActWndPara.startPointPos + ActWndPara.IncreasePtCount)
		{
			ActWndResult.VecActivePt[ptIndex] = 1;
		}
		else
		{
			double increasePt = ptIndex - ActWndPara.startPointPos;
			double totalIncreasePt = ActWndPara.IncreasePtCount;
			ActWndResult.VecActivePt[ptIndex] = increasePt / totalIncreasePt;
		}
		ActWndResult.VecActiveWndPt[ptIndex] = ActWndResult.VecActivePt[ptIndex] * ActWndResult.VecSTFTWndPt[ptIndex];
	}
}

void EffOscMaskManager::slot_startGenActiveWndFFTResult(ST_ActiveWndAnsPara& AnsPara)
{

	m_tempActiveWndData.WndPara = AnsPara.WndPara;

	slot_StartGenActiveWndPt(m_tempActiveWndData);

	m_tempActiveWndAnsResult.DeltaFreq = double(AnsPara.showMaxFreq) / double(AnsPara.showFreqPtCount);
	m_tempActiveWndAnsResult.VecWndFFTPt.clear();
	ST_FFTPoint nullFFTPoint;
	m_tempActiveWndAnsResult.VecWndFFTPt = QVector<ST_FFTPoint>(AnsPara.showFreqPtCount, nullFFTPoint);
	m_tempActiveWndAnsResult.maxAmp = 0;
	m_tempActiveWndAnsResult.AnsPara = AnsPara;

	m_VecWndFFTAnsFreqIndex.clear();
	m_VecWndFFTAnsFreqIndex = QVector<int>(AnsPara.showFreqPtCount, 0);
	for (int FreqIndex = 0; FreqIndex < AnsPara.showFreqPtCount; FreqIndex++)
	{
		m_VecWndFFTAnsFreqIndex[FreqIndex] = FreqIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_VecWndFFTAnsFreqIndex, EffOscMaskManager::slot_ansActiveFFTWndOnFreq);
	m_pActiveWndConcurrentWatcher->setFuture(future);
	m_nLastActiveWndReportPercantage = -1;
	slot_WndFFTProgressValueChanged(0);
}

void EffOscMaskManager::geneRectSTFTWnd(ST_STFTWnd& WndPara)
{
	WndPara.VecWndPt.clear();
	WndPara.VecWndPt = QVector<double>(WndPara.WndPara.pointCount, 1.0);
}

void EffOscMaskManager::geneHannSTFTWnd(ST_STFTWnd& WndPara)
{
	WndPara.VecWndPt.clear();

	int pointCount = WndPara.WndPara.pointCount;
	if (pointCount < 1)
	{
		return;
	}

	WndPara.VecWndPt = QVector<double>(pointCount, 0);

	for (int index = 0; index < pointCount; index++)
	{
		double phase = (double)2 * (double)const_audio_pi * (double)index / (double)pointCount;
		double WndVal = 0.5 * (1.0 - cos(phase));
		WndPara.VecWndPt[index] = WndVal;
	}
}

void EffOscMaskManager::slot_ansActiveFFTWndOnFreq(const int& FreqIndex)
{
	if (FreqIndex < 0)
	{
		return;
	}

	double secPerPt			= 1.0 / EffOscMaskManager::instance()->m_tempActiveWndAnsResult.AnsPara.WndPara.STFTWndPara.sampleRate;
	double currentFFTFreq	= FreqIndex * EffOscMaskManager::instance()->m_tempActiveWndAnsResult.DeltaFreq;
	double totalRealPart	= 0;
	double totalImgPart		= 0;

	const QVector<double>& VecWndPtRef = EffOscMaskManager::instance()->m_tempActiveWndData.VecActiveWndPt;

	for (int AddWndPointIndex = 0; AddWndPointIndex < VecWndPtRef.size(); AddWndPointIndex++)
	{
		double currentPhase = AddWndPointIndex * currentFFTFreq * secPerPt * 2 * const_audio_pi;
		double currentRealPart = cos(currentPhase) * VecWndPtRef[AddWndPointIndex];
		double currentImgPart = sin(currentPhase) * VecWndPtRef[AddWndPointIndex];
		totalRealPart += currentRealPart;
		totalImgPart += currentImgPart;
	}

	double resultAmp = sqrt(pow(totalRealPart, 2) + pow(totalImgPart, 2));

	EffOscMaskManager::instance()->m_tempActiveWndAnsResult.VecWndFFTPt[FreqIndex].frequency = currentFFTFreq;
	EffOscMaskManager::instance()->m_tempActiveWndAnsResult.VecWndFFTPt[FreqIndex].amplitude = resultAmp;
}

void EffOscMaskManager::slot_onFinishedWndActive()
{
	//staticActiveWndFFtPtPartData(m_tempActiveWndAnsResult);
	emit sgn_ActiveWndAnsEnd(m_tempActiveWndAnsResult);
	m_tempActiveWndData.VecActivePt.clear();
	m_tempActiveWndData.VecSTFTWndPt.clear();
	m_tempActiveWndData.VecActiveWndPt.clear();
	m_tempActiveWndAnsResult.VecWndFFTPt.clear();
}

void EffOscMaskManager::slot_WndFFTProgressValueChanged(int val)
{
	if (m_tempActiveWndAnsResult.VecWndFFTPt.isEmpty())
	{
		qDebug() << "EffOscMaskManager::slot_WndFFTProgressValueChanged VecOutput empty!";
		return;
	}

	int ptCount = m_tempActiveWndAnsResult.VecWndFFTPt.size();
	int hunderdsOfFrame = qMax(1, ptCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastActiveWndReportPercantage)
	{
		emit sgn_ActiveWndGenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(ptCount));;
		m_nLastActiveWndReportPercantage = percentage;
	}
	qDebug() << QString("sgn_ActiveWndGenState :%1 / %2 ").arg(processedCount).arg(percentage);

	if (processedCount == ptCount)
	{
		slot_onFinishedWndActive();
	}

}
