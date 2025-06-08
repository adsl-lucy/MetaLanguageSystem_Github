#include "WndSpecConstrainNetwork.h"
#pragma execution_character_set("utf-8")

WndSpecConstrainNetwork* WndSpecConstrainNetwork::m_instance = nullptr;

WndSpecConstrainNetwork* WndSpecConstrainNetwork::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new WndSpecConstrainNetwork();
	}
	return m_instance;
}

WndSpecConstrainNetwork::WndSpecConstrainNetwork() :QObject(nullptr)
{
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_WndConstrainResultAnsEnd, this, &WndSpecConstrainNetwork::slot_getWndSpecConstrainResult);
	m_pWndConstrainValWatcher = new QFutureWatcher<void>(this);
	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished()));
	connect(m_pWndConstrainValWatcher, &QFutureWatcher<void>::progressValueChanged, this, &WndSpecConstrainNetwork::slot_WndConstrainValValueChanged);
}

QString WndSpecConstrainNetwork::getWndConstrainStateStr(EN_WndSepcConstrainState state)
{
	QString result;
	switch (state)
	{
		case EN_WndSepcConstrainState::EffectiveOscillation	:result = QString("有效震荡"); break;
		case EN_WndSepcConstrainState::WndSpecNoise			:result = QString("无效噪声"); break;
		case EN_WndSepcConstrainState::UnderTIQ				:result = QString("低于听觉阈值"); break;
	}
	return result;
}

void WndSpecConstrainNetwork::slot_StartGenWndSpecConstrainResult(QString Key, const ST_WndSpecConstrainPara& WndSpecConstrainPara)
{
	bool STFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, Key);

	if (!STFTDataExist)
	{
		qDebug() << "OscillationSeparator::slot_StartGenWndSpecConstrainResult STFT data Unexist :" << Key;
		return;
	}

	m_tempResult.dataKey = Key;
	m_bOnAskWndSpecConstrainResult = true;
	FFTWindowManager::instance()->slot_StartGenWndConstrainResult(WndSpecConstrainPara);

}

void WndSpecConstrainNetwork::slot_getWndSpecConstrainResult(ST_WndSpecConstrainDistribute& WndSpecConstrainResult)
{
	if (!m_bOnAskWndSpecConstrainResult)
	{
		return;
	}
	m_bOnAskWndSpecConstrainResult = false;

	if (WndSpecConstrainResult.ConstrainSidePtCount <= 0)
	{
		qDebug() << "OscillationSeparator::slot_getWndSpecConstrainResult inValid ConstrainSidePtCount :" << WndSpecConstrainResult.ConstrainSidePtCount;
		return;
	}

	m_tempResult.WndConstrainPara = WndSpecConstrainResult;

	const ST_STFTOutputData& STFTDataRef = DataCenterManager::instance()->getSTFTOutputMap().find(m_tempResult.dataKey).value();

	int frameCount = STFTDataRef.vecOutput.size();
	int STFTPtCount = FFTManager::instance()->getEffectFFTPointCount(STFTDataRef.InputPara);

	ST_WndSpecConstrainFrame nullFrame;
	ST_WndSpecConstrainPtTag nullWndSpecConstrainPt;

	nullFrame.VecSTFTPtState.clear();
	nullFrame.VecSTFTPtState = QVector<ST_WndSpecConstrainPtTag>(STFTPtCount, nullWndSpecConstrainPt);

	for (int ptIndex = 0; ptIndex < nullFrame.VecSTFTPtState.size(); ptIndex++)
	{
		ST_WndSpecConstrainPtTag& ptTag = nullFrame.VecSTFTPtState[ptIndex];;
		ptTag.ConstrainSourceFreq = STFTDataRef.vecOutput[0].resultVec[ptIndex].frequency;
		ptTag.ptConstrainState = EN_WndSepcConstrainState::UnderTIQ;
	}

	m_tempResult.FrameVec.clear();
	m_tempResult.FrameVec = QVector<ST_WndSpecConstrainFrame>(frameCount, nullFrame);

	for (int frameIndex = 0; frameIndex < m_tempResult.FrameVec.size(); frameIndex++)
	{
		m_tempResult.FrameVec[frameIndex].FrameIndex = frameIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_tempResult.FrameVec, WndSpecConstrainNetwork::updateFrameConstrainPtState);
	m_pWndConstrainValWatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_WndConstrainValValueChanged(0);
}

void WndSpecConstrainNetwork::updateFrameConstrainPtState(ST_WndSpecConstrainFrame& FrameRef)
{
	QString dataKey = WndSpecConstrainNetwork::instance()->m_tempResult.dataKey;
	int FrameIndex = FrameRef.FrameIndex;

	const ST_FFTOutputData& STFTFrame = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value().vecOutput[FrameIndex];
	const ST_WndSpecConstrainDistribute& constrainSidePara = WndSpecConstrainNetwork::instance()->m_tempResult.WndConstrainPara;
	int constrainSidePtCount = constrainSidePara.ConstrainSidePtCount;

	auto updateConstrainPtVal_Compare = [](ST_WndSpecConstrainPtTag& ptTagRef, int constrainPtIndex, double constrainPtFreq, double constrainAmp, double constrainDB)
		{		
			if (ptTagRef.MaxConstrainVal_Compare > constrainAmp)
			{
				return;
			}
			ptTagRef.ConstrainSourceIndex = constrainPtIndex;
			ptTagRef.ConstrainSourceFreq = constrainPtFreq;
			ptTagRef.MaxConstrainVal_Compare = constrainAmp;
			ptTagRef.MaxConstrainDB_Compare = constrainDB;
			
		};

	for (int STFTPtIndex = 0; STFTPtIndex < FrameRef.VecSTFTPtState.size(); STFTPtIndex++)
	{
		double STFTPtAmp	= STFTFrame.resultVec[STFTPtIndex].amplitude;
		double STFTPtFreq	= STFTFrame.resultVec[STFTPtIndex].frequency;

		for (int sidePtIndex = 1; sidePtIndex <= constrainSidePtCount; sidePtIndex++)
		{
			int leftIndex = STFTPtIndex - 1;
			int rightIndex = STFTPtIndex + 1;

			double constrainAmp = STFTPtAmp * constrainSidePara.VecConstrain_DriftPeak_Ratio_afterEnhance[sidePtIndex - 1];
			double constrainDB = AudioProtocol::fftRealToDB(constrainAmp, const_audio_normalAudioFileMaxDB);

			if (leftIndex >= 0)
			{
				updateConstrainPtVal_Compare(FrameRef.VecSTFTPtState[leftIndex], STFTPtIndex, STFTPtFreq, constrainAmp, constrainDB);
			}

			if (rightIndex < FrameRef.VecSTFTPtState.size())
			{
				updateConstrainPtVal_Compare(FrameRef.VecSTFTPtState[rightIndex], STFTPtIndex, STFTPtFreq, constrainAmp, constrainDB);
			}
		}

	}

	for (int STFTPtIndex = 0; STFTPtIndex < FrameRef.VecSTFTPtState.size(); STFTPtIndex++)
	{
		double STFTPtAmp			= STFTFrame.resultVec[STFTPtIndex].amplitude;
		double STFTPtFreq			= STFTFrame.resultVec[STFTPtIndex].frequency;
		double ThreshHoldInQuietDB	= AudioProtocol::getHearingThreshHoldInQuietDB(STFTPtFreq);
		double ZreoDBAmp			= AudioProtocol::getFFTRealFromDB(0, const_audio_normalAudioFileMaxDB);

		//double ThreshHoldInQuietFFTReal = 0;
		//if (STFTPtFreq < 500)
		//{
		//	ThreshHoldInQuietFFTReal = AudioProtocol::getFFTRealFromDB(ThreshHoldInQuietDB, const_audio_normalAudioFileMaxDB);
		//}
		//else
		//{
		//	ThreshHoldInQuietFFTReal = ZreoDBAmp;
		//}

		double ThreshHoldInQuietFFTReal = AudioProtocol::getFFTRealFromDB(ThreshHoldInQuietDB, const_audio_normalAudioFileMaxDB);

		ST_WndSpecConstrainPtTag& ptTagRef = FrameRef.VecSTFTPtState[STFTPtIndex];

		if (STFTPtAmp < ThreshHoldInQuietFFTReal)
		{
			ptTagRef.ptConstrainState = EN_WndSepcConstrainState::UnderTIQ;
		}
		else if (STFTPtAmp <= ptTagRef.MaxConstrainVal_Compare)
		{
			ptTagRef.ptConstrainState = EN_WndSepcConstrainState::WndSpecNoise;
		}
		else
		{
			ptTagRef.ptConstrainState = EN_WndSepcConstrainState::EffectiveOscillation;
		}
	}

}

void WndSpecConstrainNetwork::slot_WndConstrainValValueChanged(int val)
{
	if (m_tempResult.FrameVec.isEmpty())
	{
		qDebug() << "OscillationSeparator::slot_WndConstrainValValueChanged m_tempResult.FrameVec empty!";
		return;
	}

	int FrameCount = m_tempResult.FrameVec.size();
	int hunderdsOfFrame = qMax(1, FrameCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_WndSpecConstrainGenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(FrameCount));;
		m_nLastReportPercantage = percentage;
	}
	qDebug() << QString("OscillationSeparator::slot_WndConstrainValValueChanged :%1 / %2 ").arg(processedCount).arg(FrameCount);
	if (processedCount == FrameCount)
	{
		slot_WndConstrainGenFinished();
	}
}

void WndSpecConstrainNetwork::slot_WndConstrainGenFinished()
{
	DataCenterManager::instance()->slot_saveWndSpecConstrainData(m_tempResult.dataKey, m_tempResult);
	m_tempResult.FrameVec.clear();
}
