#include "VibrateStateRelvanceNetwork.h"
#pragma execution_character_set("utf-8")

VibrateStateRelvanceNetwork* VibrateStateRelvanceNetwork::m_instance = nullptr;

VibrateStateRelvanceNetwork* VibrateStateRelvanceNetwork::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new VibrateStateRelvanceNetwork();
	}
	return m_instance;
}

VibrateStateRelvanceNetwork::VibrateStateRelvanceNetwork() :QObject(nullptr)
{
	m_pConcurrentWatcher = new QFutureWatcher<void>(this);
	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished()));
	connect(m_pConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &VibrateStateRelvanceNetwork::slot_GenProgressValueChanged);

}

void VibrateStateRelvanceNetwork::slot_GenProgressValueChanged(int val)
{
	if (m_tempData.FrameVec.isEmpty())
	{
		qDebug() << "VibrateStateRelvanceNetwork::slot_GenProgressValueChanged m_tempMFCCData.FrameVec empty!";
		return;
	}

	int			ptCount = m_tempData.FrameVec[0].VecVibratePt.size();
	int			processedCount = val;
	int			percentage = (double)processedCount / ptCount * 100;

	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_VibStateRel_GenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(ptCount));;
		m_nLastReportPercantage = percentage;
	}

	qDebug() << QString("VibrateStateRelvanceNetwork::slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(ptCount);

	if (processedCount == ptCount)
	{
		slot_GenFinished();
	}
}

QString VibrateStateRelvanceNetwork::getVibStateStr(const EN_VibrateState state)
{
	switch (state)
	{
		case EN_VibrateState::null		:return QString("null");
		case EN_VibrateState::Attack	:return QString("Attack");
		case EN_VibrateState::Increase	:return QString("Increase");
		case EN_VibrateState::Sustain	:return QString("Sustain");
		case EN_VibrateState::Decrease	:return QString("Decrease");
	}
	return QString();
}

void VibrateStateRelvanceNetwork::slot_StartBandWidthFilterConstrainData(QString dataKey, const ST_VibrateStateThreshHold& VibStateThreshHold)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	bool checkBDSNRDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, dataKey);
	if (!checkSTFTDataExist)
	{
		qDebug() << "VibrateStateRelvanceNetwork::slot_StartBandWidthFilterConstrainData Unexsit STFTOutputData ! " << dataKey;
		return;
	}

	if (!checkSTFTDataExist)
	{
		qDebug() << "VibrateStateRelvanceNetwork::slot_StartBandWidthFilterConstrainData Unexsit BDSNR Data ! " << dataKey;
		return;
	}

	const ST_STFTOutputData&				STFTDataRef		= DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();
	const ST_BandWidthSNRConstrainData&		BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value();

	m_tempData.dataKey = dataKey;
	m_tempData.ThreshHold = VibStateThreshHold;

	int FFTPtCount = BDSNRDataRef.FrameVec[0].vecBDSNRptTag.size();
	int FrameCount = STFTDataRef.vecOutput.size();

	ST_VibrateStatePt vibStatePt;
	ST_VibrateStateNetworkFrame nullFrame;
	m_vecVibPtIndex.clear();
	nullFrame.VecVibratePt.clear();
	nullFrame.VecVibratePt = QVector<ST_VibrateStatePt>(FFTPtCount, vibStatePt);

	for (int VibStatePtIndex = 0; VibStatePtIndex < FFTPtCount; VibStatePtIndex++)
	{
		ST_VibrateStatePt& VibStatePtRef = nullFrame.VecVibratePt[VibStatePtIndex];
		VibStatePtRef.ptFreq = STFTDataRef.vecOutput[0].resultVec[VibStatePtIndex].frequency;
		m_vecVibPtIndex.push_back(VibStatePtIndex);
	}

	m_tempData.FrameVec.clear();
	m_tempData.FrameVec = QVector<ST_VibrateStateNetworkFrame>(FrameCount, nullFrame);

	for (int FrameIndex = 0; FrameIndex < FrameCount; FrameIndex++)
	{
		ST_VibrateStateNetworkFrame& FrameRef = m_tempData.FrameVec[FrameIndex];
		FrameRef.FrameIndex = FrameIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_vecVibPtIndex, VibrateStateRelvanceNetwork::slot_GenVibPtState);
	m_pConcurrentWatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);

}

void VibrateStateRelvanceNetwork::setStatePtVal(const int ptIndex, const QVector<ST_VibrateStatePt>& ptVec)
{
	m_mutex.lock();
	for (int frameIndex = 0; frameIndex < ptVec.size(); frameIndex++)
	{
		m_tempData.FrameVec[frameIndex].VecVibratePt[ptIndex] = ptVec[frameIndex];
	}
	m_mutex.unlock();
}

void VibrateStateRelvanceNetwork::slot_GenVibPtState(const int ptIndex)
{
	QString		DataKey = VibrateStateRelvanceNetwork::instance()->m_tempData.dataKey;

	const ST_STFTOutputData&			STFTDataRef		= DataCenterManager::instance()->getSTFTOutputMap().find(DataKey).value();
	const ST_BandWidthSNRConstrainData& BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(DataKey).value();
	const ST_VibrateStateThreshHold&	ThreshHold		= VibrateStateRelvanceNetwork::instance()->m_tempData.ThreshHold;

	int FrameCount = STFTDataRef.vecOutput.size();
	ST_VibrateStatePt nullVibStatePt;
	nullVibStatePt.ptFreq = STFTDataRef.vecOutput[0].resultVec[ptIndex].frequency;
	QVector<ST_VibrateStatePt> tempPtVec = QVector<ST_VibrateStatePt>(FrameCount, nullVibStatePt);

	double lastEffAmp	= 0;

	for (int frameIndex = 0; frameIndex < FrameCount; frameIndex++)
	{
		const ST_FFTPoint&			currentFFTPt		= STFTDataRef.vecOutput[frameIndex].resultVec[ptIndex];
		const ST_BandWidthSNRPtTag& currentBDSNRPtTag	= BDSNRDataRef.FrameVec[frameIndex].vecBDSNRptTag[ptIndex];

		ST_VibrateStatePt& currentVibPt = tempPtVec[frameIndex];

		bool UnderTIQ = AudioProtocol::checkFreqPtUnderTIQ(currentFFTPt.frequency, currentFFTPt.amplitude, const_audio_normalAudioFileMaxDB);
		
		//if (currentBDSNRPtTag.ptSNRConstrainType != EN_BDSNRPtType::BDSNR_EffectivePt)
		//{
		//	currentVibPt.EffSigVal	= 0;
		//}
		if (UnderTIQ)
		{
			currentVibPt.EffSigVal = 0;
		}
		else
		{
			currentVibPt.EffSigVal	= currentFFTPt.amplitude;
		}	

		if (currentVibPt.EffSigVal == 0)
		{
			currentVibPt.ptState = EN_VibrateState::null;
		}
		else
		{
			if (lastEffAmp == 0)
			{
				currentVibPt.ptState = EN_VibrateState::Attack;
			}
			else
			{
				currentVibPt.FirstOrderDiffVal = currentVibPt.EffSigVal - lastEffAmp;
				currentVibPt.FirstOrderDiffRatio = currentVibPt.FirstOrderDiffVal / lastEffAmp;

				if (currentVibPt.FirstOrderDiffRatio < ThreshHold.SustainMinRatio)
				{
					currentVibPt.ptState = EN_VibrateState::Decrease;
				}
				else if (currentVibPt.FirstOrderDiffRatio < ThreshHold.SustainMaxRatio)
				{
					currentVibPt.ptState = EN_VibrateState::Sustain;
				}
				else if (currentVibPt.FirstOrderDiffRatio < ThreshHold.AttackMinRatio)
				{
					currentVibPt.ptState = EN_VibrateState::Increase;
				}
				else
				{
					currentVibPt.ptState = EN_VibrateState::Attack;
				}

			}
		}

		lastEffAmp = currentVibPt.EffSigVal;

	}

	EN_VibrateState lastVibState	= EN_VibrateState::null;
	int StatePersisFrame			= 0;
	int PersistentExistFrameCount	= 0;

	for (int frameIndex = 0; frameIndex < FrameCount; frameIndex++)
	{
		ST_VibrateStatePt& currentVibPt = tempPtVec[frameIndex];

		currentVibPt.isTransferPt = false;

		if (currentVibPt.ptState == EN_VibrateState::null)
		{
			StatePersisFrame = 0;
			PersistentExistFrameCount = 0;
		}
		else if (currentVibPt.ptState == lastVibState)
		{
			StatePersisFrame += 1;
			PersistentExistFrameCount += 1;
		}
		else
		{
			currentVibPt.isTransferPt = true;
			StatePersisFrame = 1;
			if (lastVibState == EN_VibrateState::null)
			{
				PersistentExistFrameCount = 1;
			}
			else
			{
				PersistentExistFrameCount += 1;
			}		
		}
		currentVibPt.PersistentExistFrameCount = PersistentExistFrameCount;
		currentVibPt.StatePersisFrame = StatePersisFrame;
		lastVibState = currentVibPt.ptState;
		
	}

	VibrateStateRelvanceNetwork::instance()->setStatePtVal(ptIndex, tempPtVec);

}


void VibrateStateRelvanceNetwork::slot_GenFinished()
{
	DataCenterManager::instance()->slot_saveVibStateData(m_tempData.dataKey, m_tempData);
	m_tempData.FrameVec.clear();
}