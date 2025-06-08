#include "./FFTWindowManager.h"
#include "../FFTManager/FFTManager.h"

#pragma execution_character_set("utf-8")

FFTWindowManager* FFTWindowManager::m_instance = nullptr;

FFTWindowManager* FFTWindowManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new FFTWindowManager();
	}
	return m_instance;
}

FFTWindowManager::FFTWindowManager() :QObject(nullptr)
{
	m_pSTFTWndConcurrentWatcher = new QFutureWatcher<void>(this);
	connect(m_pSTFTWndConcurrentWatcher, SIGNAL(finished()), this, SLOT(slot_onFinishedWndFFT()));
	connect(m_pSTFTWndConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &FFTWindowManager::slot_WndFFTProgressValueChanged);

	m_pActiveWndConcurrentWatcher = new QFutureWatcher<void>(this);
	connect(m_pActiveWndConcurrentWatcher, SIGNAL(finished()), this, SLOT(slot_onFinishedWndActive()));
	connect(m_pActiveWndConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &FFTWindowManager::slot_WndActiveProgressValueChanged);
}

QString FFTWindowManager::getWndTypeStr(EN_STFTWndType type)
{
	QString result;
	switch (type)
	{
		case EN_STFTWndType::Rect:result = QString("Rect"); break;
		case EN_STFTWndType::Hann:result = QString("Hann"); break;
	}
	return result;
}

void FFTWindowManager::slot_generateSTFTWindow(ST_STFTWnd& WndPara)
{
	switch (WndPara.WndPara.WndType)
	{
		case EN_STFTWndType::Rect:geneRectSTFTWnd(WndPara); break;
		case EN_STFTWndType::Hann:geneHannSTFTWnd(WndPara); break;
	}
}

void FFTWindowManager::geneRectSTFTWnd(ST_STFTWnd& WndPara)
{
	WndPara.VecWndPt.clear();
	WndPara.VecWndPt = QVector<double>(WndPara.WndPara.pointCount, 1.0);
}

void FFTWindowManager::geneHannSTFTWnd(ST_STFTWnd& WndPara)
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

void FFTWindowManager::geneRectSTFTWndCustom(ST_STFTWnd& WndPara, int customPtCount)
{
	WndPara.VecWndPt.clear();
	WndPara.VecWndPt = QVector<double>(customPtCount, 1.0);
}

void FFTWindowManager::geneHannSTFTWndCustom(ST_STFTWnd& WndPara, int customPtCount)
{
	WndPara.VecWndPt.clear();

	int pointCount = customPtCount;
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

void FFTWindowManager::slot_startGenerateSTFTWindowFFTResult(ST_STFTWndAnsPara& para)
{
	m_tempFFTAnsPara.WndPara			= para.WndPara;
	m_tempFFTAnsPara.showMaxFreq		= para.showMaxFreq;
	m_tempFFTAnsPara.showFreqPtCount	= para.showFreqPtCount;

	m_tempFFTWndData.WndPara = para.WndPara;

	slot_generateSTFTWindow(m_tempFFTWndData);

	m_tempFFTWndResult.DeltaFreq = double(para.showMaxFreq) / double(para.showFreqPtCount);
	m_tempFFTWndResult.VecWndFFTPt.clear();
	ST_FFTPoint nullFFTPoint;
	m_tempFFTWndResult.VecWndFFTPt = QVector<ST_FFTPoint>(para.showFreqPtCount, nullFFTPoint);
	m_tempFFTWndResult.maxAmp = 0;
	m_tempFFTWndResult.AnsPara = m_tempFFTAnsPara;

	m_VecWndFFTAnsFreqIndex.clear();
	m_VecWndFFTAnsFreqIndex = QVector<int>(para.showFreqPtCount, 0);
	for (int FreqIndex = 0; FreqIndex < para.showFreqPtCount; FreqIndex++)
	{
		m_VecWndFFTAnsFreqIndex[FreqIndex] = FreqIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_VecWndFFTAnsFreqIndex, FFTWindowManager::slot_ansFFTWndOnFreq);
	m_pSTFTWndConcurrentWatcher->setFuture(future);
	m_nLastSTFTWndReportPercantage = -1;
	slot_WndFFTProgressValueChanged(0);

}

void FFTWindowManager::slot_ansFFTWndOnFreq(const int& FreqIndex)
{
	if (FreqIndex < 0)
	{
		return;
	}

	double secPerPt			= 1.0 / FFTWindowManager::instance()->m_tempFFTAnsPara.WndPara.sampleRate;
	double currentFFTFreq	= FreqIndex * FFTWindowManager::instance()->m_tempFFTWndResult.DeltaFreq;
	double totalRealPart	= 0;
	double totalImgPart		= 0;

	const QVector<double>& VecWndPtRef = FFTWindowManager::instance()->m_tempFFTWndData.VecWndPt;

	for (int AddWndPointIndex = 0; AddWndPointIndex < VecWndPtRef.size(); AddWndPointIndex++)
	{
		double currentPhase = AddWndPointIndex * currentFFTFreq * secPerPt * 2 * const_audio_pi;
		double currentRealPart = cos(currentPhase) * VecWndPtRef[AddWndPointIndex];
		double currentImgPart = sin(currentPhase) * VecWndPtRef[AddWndPointIndex];
		totalRealPart += currentRealPart;
		totalImgPart += currentImgPart;
	}

	double resultAmp = sqrt(pow(totalRealPart, 2) + pow(totalImgPart, 2));

	FFTWindowManager::instance()->m_tempFFTWndResult.VecWndFFTPt[FreqIndex].frequency = currentFFTFreq;
	FFTWindowManager::instance()->m_tempFFTWndResult.VecWndFFTPt[FreqIndex].amplitude = resultAmp;
}

void FFTWindowManager::slot_ansActiveFFTWndOnFreq(const int& FreqIndex)
{
	if (FreqIndex < 0)
	{
		return;
	}

	double secPerPt = 1.0 / FFTWindowManager::instance()->m_tempActiveWndAnsPara.WndPara.STFTWndPara.sampleRate;
	double currentFFTFreq = FreqIndex * FFTWindowManager::instance()->m_tempActiveWndAnsResult.DeltaFreq;
	double totalRealPart = 0;
	double totalImgPart = 0;

	const QVector<double>& VecWndPtRef = FFTWindowManager::instance()->m_tempActiveWndData.VecActiveWndPt;

	for (int AddWndPointIndex = 0; AddWndPointIndex < VecWndPtRef.size(); AddWndPointIndex++)
	{
		double currentPhase = AddWndPointIndex * currentFFTFreq * secPerPt * 2 * const_audio_pi;
		double currentRealPart = cos(currentPhase) * VecWndPtRef[AddWndPointIndex];
		double currentImgPart = sin(currentPhase) * VecWndPtRef[AddWndPointIndex];
		totalRealPart += currentRealPart;
		totalImgPart += currentImgPart;
	}

	double resultAmp = sqrt(pow(totalRealPart, 2) + pow(totalImgPart, 2));

	FFTWindowManager::instance()->m_tempActiveWndAnsResult.VecWndFFTPt[FreqIndex].frequency = currentFFTFreq;
	FFTWindowManager::instance()->m_tempActiveWndAnsResult.VecWndFFTPt[FreqIndex].amplitude = resultAmp;
}

void FFTWindowManager::staticActiveWndFFtPtPartData(ST_ActiveWndAnsResult& result)
{
	int FreqPtCount = result.VecWndFFTPt.size();
	if (FreqPtCount <= 0)
	{
		return;
	}

	result.maxAmp = 0;

	for (int ptIndex = 0; ptIndex < FreqPtCount; ptIndex++)
	{
		result.maxAmp = qMax(result.maxAmp, result.VecWndFFTPt[ptIndex].amplitude);
	}

}

void FFTWindowManager::slot_WndFFTProgressValueChanged(int val)
{
	if (m_tempFFTWndResult.VecWndFFTPt.isEmpty())
	{
		qDebug() << "FFTWindowManager::slot_WndFFTProgressValueChanged VecOutput empty!";
		return;
	}

	int ptCount = m_tempFFTWndResult.VecWndFFTPt.size();
	int hunderdsOfFrame = qMax(1, ptCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastSTFTWndReportPercantage)
	{
		emit sgn_WndFFTGenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(ptCount));;
		m_nLastSTFTWndReportPercantage = percentage;
	}
	qDebug() << QString("sgn_WndFFTGenState :%1 / %2 ").arg(processedCount).arg(percentage);
}

void FFTWindowManager::slot_StartGenWndConstrainResult(const ST_WndSpecConstrainPara para)
{
	m_tempWndConstrainResult.VecConstrain_PeakRatio.clear();
	m_tempWndConstrainResult.VecConstrain_PeakDB.clear();
	m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_beforeEnhance.clear();
	m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_beforeEnhance.clear();
	m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_afterEnhance.clear();
	m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_AfterEnhance.clear();
	m_tempWndConstrainResult.ConstrainSidePtCount = 0;
	m_tempWndConstrainResult.GenPara = para;
	
	ST_STFTWndAnsPara WndSTFTAnSPara;

	WndSTFTAnSPara.WndPara = para.WndPara;
	WndSTFTAnSPara.showFreqPtCount = 20000;
	WndSTFTAnSPara.showMaxFreq = 200;

	m_nOnAnsWndConstrain = true;

	slot_startGenerateSTFTWindowFFTResult(WndSTFTAnSPara);
}

void FFTWindowManager::slot_StartGenActiveWndPt(ST_ActvieWnd& ActWndResult)
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

void FFTWindowManager::slot_startGenActiveWndFFTResult(ST_ActiveWndAnsPara& para)
{
	m_tempActiveWndAnsPara.WndPara = para.WndPara;
	m_tempActiveWndAnsPara.showMaxFreq = para.showMaxFreq;
	m_tempActiveWndAnsPara.showFreqPtCount = para.showFreqPtCount;

	m_tempActiveWndData.WndPara = para.WndPara;

	slot_StartGenActiveWndPt(m_tempActiveWndData);

	m_tempActiveWndAnsResult.DeltaFreq = double(para.showMaxFreq) / double(para.showFreqPtCount);
	m_tempActiveWndAnsResult.VecWndFFTPt.clear();
	ST_FFTPoint nullFFTPoint;
	m_tempActiveWndAnsResult.VecWndFFTPt = QVector<ST_FFTPoint>(para.showFreqPtCount, nullFFTPoint);
	m_tempActiveWndAnsResult.maxAmp = 0;
	m_tempActiveWndAnsResult.AnsPara = m_tempActiveWndAnsPara;

	m_VecWndFFTAnsFreqIndex.clear();
	m_VecWndFFTAnsFreqIndex = QVector<int>(para.showFreqPtCount, 0);
	for (int FreqIndex = 0; FreqIndex < para.showFreqPtCount; FreqIndex++)
	{
		m_VecWndFFTAnsFreqIndex[FreqIndex] = FreqIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_VecWndFFTAnsFreqIndex, FFTWindowManager::slot_ansActiveFFTWndOnFreq);
	m_pActiveWndConcurrentWatcher->setFuture(future);
	m_nLastActiveWndReportPercantage = -1;
	slot_WndActiveProgressValueChanged(0);
}

void FFTWindowManager::slot_onFinishedWndActive()
{
	staticActiveWndFFtPtPartData(m_tempActiveWndAnsResult);
	emit sgn_ActiveWndAnsEnd(m_tempActiveWndAnsResult);
	m_tempActiveWndData.VecActivePt.clear();
	m_tempActiveWndData.VecSTFTWndPt.clear();
	m_tempActiveWndData.VecActiveWndPt.clear();
	m_tempActiveWndAnsResult.VecWndFFTPt.clear();
}

void FFTWindowManager::slot_WndActiveProgressValueChanged(int val)
{
	if (m_tempActiveWndAnsResult.VecWndFFTPt.isEmpty())
	{
		qDebug() << "FFTWindowManager::slot_WndActiveProgressValueChanged VecOutput empty!";
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
	qDebug() << QString("sgn_ActiveWndFFTGenState :%1 / %2 ").arg(processedCount).arg(percentage);
}

void FFTWindowManager::slot_onFinishedWndFFT()
{
	staticWndFFtPtPartData(m_tempFFTWndResult);
	if (m_nOnAnsWndConstrain)
	{
		startStatWndConstrainResult(m_tempFFTWndResult);
		emit sgn_WndConstrainResultAnsEnd(m_tempWndConstrainResult);
		m_nOnAnsWndConstrain = false;
	}
	else
	{
		emit sgn_WndFFTAnsEnd(m_tempFFTWndResult);
	}
	m_tempFFTWndData.VecWndPt.clear();
	m_tempFFTWndResult.VecWndFFTPart.clear();
	m_tempFFTWndResult.VecWndFFTPt.clear();
}

void FFTWindowManager::staticWndFFtPtPartData(ST_STFTWndAnsResult& result)
{
	int FreqPtCount = result.VecWndFFTPt.size();
	if (FreqPtCount <=0)
	{
		return;
	}

	result.VecWndFFTPart.clear();

	int hundredOfFreq = 0;
	if (FreqPtCount < 100)
	{
		hundredOfFreq = 0;
	}
	else
	{
		hundredOfFreq = FreqPtCount / 100;
	}

	auto resetTempPart = [](ST_STFTWndPart& resetPart)
		{
			resetPart.PartMaxVal = 0;
			resetPart.PartMaxValFreq = 0;
			resetPart.PartMaxValPtIndex = 0;
			resetPart.totalRightWidth = 0;
			resetPart.db10RightWidth = 0;
			resetPart.db20RightWidth = 0;
			resetPart.db30RightWidth = 0;
			resetPart.PartMaxErrorPercent = 0;
			resetPart.PartMaxErrorDb = 0;
		};

	ST_STFTWndPart temPart;
	resetTempPart(temPart);

	double LastDiff = 0;

	result.maxAmp = 0;
	double FreqPtInterval = result.DeltaFreq;

	for (int FreqIndex = 0; FreqIndex < FreqPtCount - 1; FreqIndex++)
	{
		if (FreqIndex == 0)
		{
			temPart.PartMaxVal = result.VecWndFFTPt[FreqIndex].amplitude;
			temPart.PartMaxValFreq = result.VecWndFFTPt[FreqIndex].frequency;
			temPart.PartMaxValPtIndex = FreqIndex;
		}

		double nextDiff = result.VecWndFFTPt[FreqIndex + 1].amplitude - result.VecWndFFTPt[FreqIndex].amplitude;

		result.maxAmp = qMax(result.maxAmp, result.VecWndFFTPt[FreqIndex].amplitude);

		if (nextDiff < 0 && LastDiff > 0)
		{
			temPart.PartMaxVal			= result.VecWndFFTPt[FreqIndex].amplitude;
			temPart.PartMaxValFreq		= result.VecWndFFTPt[FreqIndex].frequency;
			temPart.PartMaxValPtIndex	= FreqIndex;
		}
		else if (nextDiff > 0 && LastDiff < 0)
		{
			result.VecWndFFTPart.append(temPart);
			resetTempPart(temPart);
		}
		else if (nextDiff < 0 && LastDiff < 0)
		{
			temPart.totalRightWidth += FreqPtInterval;
		}

		LastDiff = nextDiff;


		if (hundredOfFreq == 0)
		{
			emit sgn_WndFFTGenState((double)FreqIndex / (double)FreqPtCount * 100,1,QString());
		}
		else
		{
			if (FreqIndex % hundredOfFreq == 0)
			{
				emit sgn_WndFFTGenState(FreqIndex / hundredOfFreq, 1, QString());
			}
		}
	}

	double FFTDeltaFreq = 1.0 / (result.AnsPara.WndPara.WndMsec / 1000);

	for (int FreqPartIndex = 0; FreqPartIndex < result.VecWndFFTPart.size(); FreqPartIndex++)
	{
		ST_STFTWndPart& FreqPart = result.VecWndFFTPart[FreqPartIndex];

		double partMaxDb = AudioProtocol::getRelativeDB(FreqPart.PartMaxVal, result.maxAmp);
		FreqPart.PartMaxErrorPercent = -1;

		for (int fftPtIndex = FreqPart.PartMaxValPtIndex; fftPtIndex < result.VecWndFFTPt.size(); fftPtIndex++)
		{
			const ST_FFTPoint& currentFFTPt = result.VecWndFFTPt[fftPtIndex];
			double freqDisFromTop = currentFFTPt.frequency - FreqPart.PartMaxValFreq;

			if (freqDisFromTop > FreqPart.totalRightWidth)
			{
				break;
			}

			if (FreqPart.PartMaxErrorPercent < 0)
			{
				if (freqDisFromTop >= FFTDeltaFreq / 2)
				{
					double errorPercent = currentFFTPt.amplitude / FreqPart.PartMaxVal;
					FreqPart.PartMaxErrorPercent = 1 - errorPercent;
					FreqPart.PartMaxErrorDb = AudioProtocol::getRelativeDB(currentFFTPt.amplitude, FreqPart.PartMaxVal);
				}
			}


			double fftPtAbsDB = AudioProtocol::getRelativeDB(currentFFTPt.amplitude, result.maxAmp);
			if (partMaxDb - fftPtAbsDB < 10)
			{
				FreqPart.db10RightWidth += FreqPtInterval;
				FreqPart.db20RightWidth += FreqPtInterval;
				FreqPart.db30RightWidth += FreqPtInterval;
			}
			else if (partMaxDb - fftPtAbsDB > 10 && partMaxDb - fftPtAbsDB < 20)
			{
				FreqPart.db20RightWidth += FreqPtInterval;
				FreqPart.db30RightWidth += FreqPtInterval;
			}
			else if (partMaxDb - fftPtAbsDB > 20 && partMaxDb - fftPtAbsDB < 30)
			{
				FreqPart.db30RightWidth += FreqPtInterval;
			}
			else
			{
				break;
			}

		}
		emit sgn_WndFFTGenState((double)FreqPartIndex / (double)result.VecWndFFTPart.size() * 100, 1, QString());
	}

	emit sgn_WndFFTGenState(100, 1, QString());
}

void FFTWindowManager::startStatWndConstrainResult(ST_STFTWndAnsResult& result)
{
	double FFTDeltaFreq = (double)m_tempWndConstrainResult.GenPara.WndPara.sampleRate / (double)m_tempWndConstrainResult.GenPara.WndPara.pointCount;

	double specMaxVal				= result.VecWndFFTPt[0].amplitude;
	double DriftPeakFreq			= FFTDeltaFreq * m_tempWndConstrainResult.GenPara.PeakValDriftRatio;
	double DriftValleyFreq			= FFTDeltaFreq * (1 - m_tempWndConstrainResult.GenPara.PeakValDriftRatio);
	double middleIntervalPtFreq		= FFTDeltaFreq * 0.5;
	
	double currentFreq = 0;
	int    currentPtIndex = 0;
	while (currentFreq < DriftPeakFreq)
	{
		currentPtIndex += 1;
		currentFreq = result.VecWndFFTPt[currentPtIndex].frequency;
	}

	double DriftPeakVal				= result.VecWndFFTPt[currentPtIndex].amplitude;
	double DriftPeakRatio_SpecPeak	= DriftPeakVal / specMaxVal;
	double DriftDB_SpecPeak			= AudioProtocol::getRelativeDB(DriftPeakVal, specMaxVal);

	m_tempWndConstrainResult.VecConstrain_PeakRatio.push_back(DriftPeakRatio_SpecPeak);
	m_tempWndConstrainResult.VecConstrain_PeakDB.push_back(DriftDB_SpecPeak);

	while (currentFreq < middleIntervalPtFreq)
	{
		currentPtIndex += 1;
		currentFreq = result.VecWndFFTPt[currentPtIndex].frequency;
	}

	double middlePtVal		= result.VecWndFFTPt[currentPtIndex].amplitude;
	double middlePtRatio	= middlePtVal / specMaxVal;
	double middlePtDB		= AudioProtocol::getRelativeDB(middlePtVal, specMaxVal);

	m_tempWndConstrainResult.VecConstrain_PeakRatio.push_back(middlePtRatio);
	m_tempWndConstrainResult.VecConstrain_PeakDB.push_back(middlePtDB);

	while (currentFreq < DriftValleyFreq)
	{
		currentPtIndex += 1;
		currentFreq = result.VecWndFFTPt[currentPtIndex].frequency;
	}

	double DriftValleyPtVal						= result.VecWndFFTPt[currentPtIndex].amplitude;
	double DriftValleyValRatio_Peak				= DriftValleyPtVal / specMaxVal;
	double DriftValleyValDB_Peak				= AudioProtocol::getRelativeDB(DriftValleyValRatio_Peak, 1);

	double DriftValley_RaletiveRatio_DriftPeak	= DriftValleyPtVal / DriftPeakVal;
	double DriftValley_RaletiveDB_DirftPeak		= AudioProtocol::getRelativeDB(DriftValley_RaletiveRatio_DriftPeak,1);

	m_tempWndConstrainResult.VecConstrain_PeakRatio.push_back(DriftValleyValRatio_Peak);
	m_tempWndConstrainResult.VecConstrain_PeakDB.push_back(DriftValleyValDB_Peak);

	if (true)
	{
		qDebug() << QString("sampleRate :%1 WndPtCount :%2").arg(result.AnsPara.WndPara.sampleRate).arg(result.AnsPara.WndPara.pointCount);
		qDebug() << QString("%1% driftpos Val: %2 ratio : %3% db : %4 ")
			.arg(m_tempWndConstrainResult.GenPara.PeakValDriftRatio * 100, 0, 'f', 2)
			.arg(DriftPeakVal, 0, 'f', 2)
			.arg(DriftPeakRatio_SpecPeak * 100, 0, 'f', 2)
			.arg(DriftDB_SpecPeak, 0, 'f', 2);
		qDebug() << QString("%1% driftpos Val: %2 ratio : %3% db : %4 ")
			.arg(50.0, 0, 'f', 2)
			.arg(middlePtVal, 0, 'f', 2)
			.arg(middlePtRatio * 100, 0, 'f', 2)
			.arg(middlePtDB, 0, 'f', 2);
		qDebug() << QString("%1% driftpos Val: %2 ratio : %3% db : %4 ")
			.arg((1 - m_tempWndConstrainResult.GenPara.PeakValDriftRatio) * 100, 0, 'f', 2)
			.arg(DriftValleyPtVal, 0, 'f', 2)
			.arg(DriftValleyValRatio_Peak * 100, 0, 'f', 2)
			.arg(DriftValleyValDB_Peak, 0, 'f', 2);
		qDebug() << QString("driftpos %1% / %2% = %3% reletaiveDB : %4 ")
			.arg((1 - m_tempWndConstrainResult.GenPara.PeakValDriftRatio) * 100, 0, 'f', 1)
			.arg(m_tempWndConstrainResult.GenPara.PeakValDriftRatio * 100, 0, 'f', 1)
			.arg(DriftValley_RaletiveRatio_DriftPeak, 0, 'f', 2)
			.arg(DriftValley_RaletiveDB_DirftPeak, 0, 'f', 2);
		int a = 0;
	}

	m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_beforeEnhance.push_back(DriftValley_RaletiveRatio_DriftPeak);
	m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_beforeEnhance.push_back(DriftValley_RaletiveDB_DirftPeak);
	m_tempWndConstrainResult.ConstrainSidePtCount += 1;

	
	int tempPtIndex = currentPtIndex;
	double WndSpecNoiseUnConstrainRatio = DriftValley_RaletiveRatio_DriftPeak / 2;
	

	while (tempPtIndex < result.VecWndFFTPt.size())
	{
		double tempPtFreq	= result.VecWndFFTPt[tempPtIndex].frequency;
		double tempPtVal	= result.VecWndFFTPt[tempPtIndex].amplitude;
		double tempPtRatio_Peak = tempPtVal / specMaxVal;
		double tempPtDB_Peak = AudioProtocol::getRelativeDB(tempPtRatio_Peak, 1);

		if (tempPtRatio_Peak <= WndSpecNoiseUnConstrainRatio)
		{
			qDebug() << QString("sampleRate :%1 WndPtCount :%2 WndSpecNoiseUnConstrainRatio : %3%")
				.arg(result.AnsPara.WndPara.sampleRate).arg(result.AnsPara.WndPara.pointCount)
			.arg(WndSpecNoiseUnConstrainRatio * 100, 0, 'f', 2);
			qDebug() << QString("interval WndSpecNoise Ratio : %1% FreqDistance : %2 hz")
				.arg(tempPtRatio_Peak * 100, 0, 'f', 2)
				.arg(tempPtFreq, 0, 'f', 2);
			qDebug() << QString("max UnWndSpecNoise FreqInterval :%1hz").arg(tempPtFreq * 2, 0, 'f', 2);
			m_tempWndConstrainResult.NoiseUnConstrainFreqInterval = tempPtFreq * 2;
			break;
		}
		tempPtIndex += 1;
	}

	tempPtIndex = currentPtIndex;
	double WndSpecNoiseToBeSignalRatio = 0.5;
	while (tempPtIndex < result.VecWndFFTPt.size())
	{
		double tempPtFreq = result.VecWndFFTPt[tempPtIndex].frequency;
		double tempPtVal = result.VecWndFFTPt[tempPtIndex].amplitude;
		double tempPtRatio_Peak = tempPtVal / specMaxVal;
		double tempPtDB_Peak = AudioProtocol::getRelativeDB(tempPtRatio_Peak, 1);

		if (tempPtRatio_Peak <= WndSpecNoiseToBeSignalRatio)
		{
			qDebug() << QString("sampleRate :%1 WndPtCount :%2 WndSpecNoiseToBeSignalRatio : %3%")
				.arg(result.AnsPara.WndPara.sampleRate).arg(result.AnsPara.WndPara.pointCount)
				.arg(WndSpecNoiseToBeSignalRatio * 100, 0, 'f', 2);
			qDebug() << QString("interval WndSpecNoise Ratio : %1% FreqDistance : %2 hz")
				.arg(tempPtRatio_Peak * 100, 0, 'f', 2)
				.arg(tempPtFreq, 0, 'f', 2);
			qDebug() << QString("max UnWndSpecNoise FreqInterval :%1hz").arg(tempPtFreq * 2, 0, 'f', 2);
			m_tempWndConstrainResult.NoiseToBeSignalFreqInterval = tempPtFreq * 2;
			break;
		}
		tempPtIndex += 1;
	}
	

	int currentFFTIndex = currentPtIndex;
	double targetFreq = (m_tempWndConstrainResult.ConstrainSidePtCount + 1) * FFTDeltaFreq;

	auto getFreqPtInWhichPart = [](const QVector<ST_STFTWndPart>& partVecRef,double ptFreq)->int 
		{

			for (int currentStartPartIndex = 0; currentStartPartIndex < partVecRef.size() - 1; currentStartPartIndex++)
			{
				const ST_STFTWndPart& startPart = partVecRef[currentStartPartIndex];
				const ST_STFTWndPart& nextPart	= partVecRef[currentStartPartIndex + 1];

				if (ptFreq > nextPart.PartMaxValFreq)
				{
					continue;
				}

				double middleFreq = (startPart.PartMaxValFreq + nextPart.PartMaxValFreq) / 2;
				if (ptFreq >= startPart.PartMaxValFreq && ptFreq <= middleFreq)
				{
					return currentStartPartIndex;
				}
				else
				{
					return currentStartPartIndex + 1;
				}
			}

			return -1;

		};

	double currentRelativeVal	= DriftValleyValRatio_Peak;
	double currentReletiveDB	= DriftValley_RaletiveDB_DirftPeak;

	while (currentReletiveDB * -1 < m_tempWndConstrainResult.GenPara.ConstrainDBRange && currentFFTIndex < result.VecWndFFTPt.size())
	{
		currentFreq = result.VecWndFFTPt[currentFFTIndex].frequency;
		if (currentFreq >= targetFreq)
		{
			int ptPartIndex = getFreqPtInWhichPart(result.VecWndFFTPart, currentFreq);
			if (ptPartIndex == 0)
			{
				m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_beforeEnhance.push_back(currentRelativeVal);
				m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_beforeEnhance.push_back(currentReletiveDB);
			}
			else if(ptPartIndex <0)
			{
				break;
			}
			else
			{
				double targetRelativeVal_specPeak	= result.VecWndFFTPart[ptPartIndex].PartMaxVal / specMaxVal;
				double targetRelativeVal_middlePt	= result.VecWndFFTPart[ptPartIndex].PartMaxVal / middlePtVal;
				currentReletiveDB			= AudioProtocol::getRelativeDB(targetRelativeVal_middlePt, 1);
				double PeakRelativeDB		= AudioProtocol::getRelativeDB(targetRelativeVal_specPeak, 1);

				m_tempWndConstrainResult.VecConstrain_PeakRatio.push_back(targetRelativeVal_specPeak);
				m_tempWndConstrainResult.VecConstrain_PeakDB.push_back(PeakRelativeDB);
				m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_beforeEnhance.push_back(targetRelativeVal_middlePt);
				m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_beforeEnhance.push_back(currentReletiveDB);
			}
			m_tempWndConstrainResult.ConstrainSidePtCount += 1;
			targetFreq = (m_tempWndConstrainResult.ConstrainSidePtCount + 1) * FFTDeltaFreq;
		}
		currentFFTIndex += 1;
	}

	m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_afterEnhance.clear();
	m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_AfterEnhance.clear();

	
	for (int ptIndex = 0; ptIndex < m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_beforeEnhance.size(); ptIndex++)
	{
		double currentVal	= m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_beforeEnhance[ptIndex];
		double currentDB	= m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_beforeEnhance[ptIndex];
		double EnhanceVal	= currentVal * m_tempWndConstrainResult.GenPara.EnhanceRatio;
		double EnhanceDB	= AudioProtocol::getRelativeDB(EnhanceVal, 1);

		if (ptIndex == 1 && m_tempWndConstrainResult.GenPara.isForcePt2DBVal)
		{
			double forceDB = m_tempWndConstrainResult.GenPara.forcePt2DBVal * -1;
			m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_AfterEnhance.push_back(forceDB);
			double fftReal = AudioProtocol::getFFTRealFromDB(forceDB, 0);
			m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_afterEnhance.push_back(fftReal);
		}
		else if (ptIndex < m_tempWndConstrainResult.GenPara.startEnhanceSidePos)
		{
			m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_afterEnhance.push_back(currentVal);
			m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_AfterEnhance.push_back(currentDB);
		}
		else
		{
			m_tempWndConstrainResult.VecConstrain_DriftPeak_Ratio_afterEnhance.push_back(EnhanceVal);
			m_tempWndConstrainResult.VecConstrain_DriftPeak_DB_AfterEnhance.push_back(EnhanceDB);
		}
	}

	int b = 0;

}