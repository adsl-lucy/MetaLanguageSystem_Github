#include "AudioDiffNet.h"
#pragma execution_character_set("utf-8")

AudioDiffNet* AudioDiffNet::m_instance = nullptr;

AudioDiffNet* AudioDiffNet::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new AudioDiffNet();
	}
	return m_instance;
}

AudioDiffNet::AudioDiffNet() :QObject(nullptr)
{
	m_pConcurrentWatcher = new QFutureWatcher<void>(this);
	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished()));
	connect(m_pConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &AudioDiffNet::slot_DiffGenProgressValueChanged);

}

void AudioDiffNet::GenDiffGroup(const ST_DiffNetPara& GenPara, ST_DiffNetState& NetStateRef)
{
	NetStateRef.totalGroupCount = GenPara.bidirectionalGroupCount + 2;
	NetStateRef.mapDiffGroup.clear();
	int		intervalCount = floor((GenPara.bidirectionalGroupCount - 2) / 2) + 1;
	double	currentInterval = GenPara.BidirectionGroupStartInterval;
	double  currentEndAbsRatio = 0;
	for (int intervalIndex = 0; intervalIndex <= intervalCount; intervalIndex++)
	{
		if (intervalIndex == 0)
		{
			ST_DiffNetBiDirectGroup newGroup;
			newGroup.isASideGroup = false;
			newGroup.groupIndex = 0;
			currentEndAbsRatio = currentInterval / 2;
			newGroup.startRatio = currentEndAbsRatio * -1;
			newGroup.endRatio = currentEndAbsRatio;
			NetStateRef.mapDiffGroup.insert(0, newGroup);
		}
		else if (intervalIndex < intervalCount)
		{
			ST_DiffNetBiDirectGroup newPositiveGroup;
			newPositiveGroup.groupIndex = intervalIndex;
			newPositiveGroup.isASideGroup = false;
			newPositiveGroup.startRatio = currentEndAbsRatio;
			newPositiveGroup.endRatio = currentEndAbsRatio + currentInterval;
			NetStateRef.mapDiffGroup.insert(newPositiveGroup.groupIndex, newPositiveGroup);
			
			ST_DiffNetBiDirectGroup newNegativeGroup;
			newNegativeGroup.groupIndex = intervalIndex * -1;
			newNegativeGroup.isASideGroup = false;
			newNegativeGroup.startRatio = (currentEndAbsRatio + currentInterval) * -1;
			newNegativeGroup.endRatio = currentEndAbsRatio * -1;
			NetStateRef.mapDiffGroup.insert(newNegativeGroup.groupIndex, newNegativeGroup);

			currentEndAbsRatio = newPositiveGroup.endRatio;

		}
		else if (intervalIndex == intervalCount)
		{
			ST_DiffNetBiDirectGroup newPositiveSideGroup;
			newPositiveSideGroup.groupIndex = intervalIndex;
			newPositiveSideGroup.isASideGroup = true;
			newPositiveSideGroup.startRatio = currentEndAbsRatio;
			newPositiveSideGroup.endRatio = 0;
			NetStateRef.mapDiffGroup.insert(intervalIndex, newPositiveSideGroup);

			ST_DiffNetBiDirectGroup newNegativeSideGroup;
			newNegativeSideGroup.groupIndex = intervalIndex * -1;
			newNegativeSideGroup.isASideGroup = true;
			newNegativeSideGroup.startRatio = 0;
			newNegativeSideGroup.endRatio = currentEndAbsRatio * -1;
			NetStateRef.mapDiffGroup.insert(intervalIndex * -1, newNegativeSideGroup);
		}
		if (GenPara.IntervalType == EN_DiffNetGroupIntervalType::Double)
		{
			currentInterval *= 2;
		}
	}

	NetStateRef.SideStartRatio = currentEndAbsRatio;
}

void AudioDiffNet::slot_StartGenDiffResult(const ST_DiffNetPara& GenPara, QString dataKey)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	if (!checkSTFTDataExist)
	{
		qDebug() << "BandWidthFilterManager::slot_StartBandWidthFilterConstrainData Unexsit STFTOutputData ! " << dataKey;
		return;
	}

	bool WndSpecConstrainDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, dataKey);
	if (!WndSpecConstrainDataExist)
	{
		qDebug() << "BandWidthFilterManager::slot_StartGenEffectiveMFCCData Unexsit WndSpecConstrainData! " << dataKey;
		return;
	}

	bool BDSNRDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, dataKey);
	if (!BDSNRDataExist)
	{
		qDebug() << "BandWidthFilterManager::slot_StartGenEffectiveMFCCData Unexsit BDSNRDataExist! " << dataKey;
		return;
	}

	const ST_STFTOutputData&			STFTDataRef		= DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();
	const ST_WndSpecConstrainResult&	EFFOscDataRef	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(dataKey).value();
	const ST_BandWidthSNRConstrainData& BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value();

	m_tempData.DataKey = dataKey;
	m_tempData.inputPara = GenPara;
	
	GenDiffGroup(GenPara, m_tempData.DiffNetState);

	m_tempData.FrameVec.clear();

	int FFTPtCount		= BDSNRDataRef.FrameVec[0].vecBDSNRptTag.size();
	int FilterCount		= BDSNRDataRef.FrameVec[0].vecBDFilterValue.size();
	int FrameCount		= BDSNRDataRef.FrameVec.size();

	ST_DiffNetPoint nullFFTPt;
	nullFFTPt.ptType	= EN_DiffPtType::FFTpoint;
	ST_DiffNetPoint nullFilterPt;
	nullFilterPt.ptType = EN_DiffPtType::MFCCFilter;
	ST_DiffFrame nullDiffFrame;
	nullDiffFrame.vecFFTPoint.clear();
	nullDiffFrame.vecBandWidthFilterPoint.clear();
	nullDiffFrame.vecFFTPoint				= QVector<ST_DiffNetPoint>(FFTPtCount, nullFFTPt);
	nullDiffFrame.vecBandWidthFilterPoint	= QVector<ST_DiffNetPoint>(FilterCount, nullFilterPt);

	for (int FFTptIndex = 0; FFTptIndex < FFTPtCount; FFTptIndex++)
	{
		const	ST_BandWidthSNRPtTag&	BDSNRPtRef	= BDSNRDataRef.FrameVec[0].vecBDSNRptTag[FFTptIndex];
				ST_DiffNetPoint&		DiffPtRef	= nullDiffFrame.vecFFTPoint[FFTptIndex];
				DiffPtRef.ptCenterFreq = BDSNRPtRef.ptFreq;
	}

	for (int FilterptIndex = 0; FilterptIndex < FilterCount; FilterptIndex++)
	{
		const	ST_BandWidthFilter& BDSNRFilterRef	= BDSNRDataRef.FilterData.FilterVec[FilterptIndex];
				ST_DiffNetPoint&	DiffPtRef		= nullDiffFrame.vecBandWidthFilterPoint[FilterptIndex];
		DiffPtRef.ptCenterFreq = BDSNRFilterRef.CenterFreq;
	}

	m_tempData.FrameVec.clear();
	m_tempData.FrameVec = QVector<ST_DiffFrame>(FrameCount, nullDiffFrame);

	for (int FrameIndex = 0; FrameIndex < FrameCount; FrameIndex++)
	{
		ST_DiffFrame& FrameRef = m_tempData.FrameVec[FrameIndex];
		FrameRef.FrameInSTFTIndex = FrameIndex;
		FrameRef.FrameStartTime = FrameIndex * STFTDataRef.InputPara.GapInTimeLength;
	}

	QFuture<void> future = QtConcurrent::map(m_tempData.FrameVec, AudioDiffNet::GenDiffFrame);
	m_pConcurrentWatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_DiffGenProgressValueChanged(0);
}

void AudioDiffNet::GenDiffFrame(ST_DiffFrame& FrameData)
{
	const QString			DataKey		= AudioDiffNet::instance()->m_tempData.DataKey;
	const ST_DiffNetPara&	NetPara		= AudioDiffNet::instance()->m_tempData.inputPara;
	const ST_DiffNetState&	NetState	= AudioDiffNet::instance()->m_tempData.DiffNetState;

	const ST_STFTOutputData&			STFTDataRef		= DataCenterManager::instance()->getSTFTOutputMap().find(DataKey).value();
	const ST_WndSpecConstrainResult&	EFFOscDataRef	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(DataKey).value();
	const ST_BandWidthSNRConstrainData& BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(DataKey).value();

	const double ZeroDbVal = AudioProtocol::getFFTRealFromDB(0, const_audio_normalAudioFileMaxDB);

	int currentFrameIndex	= FrameData.FrameInSTFTIndex;
	int LastFrameIndex		= currentFrameIndex - 1;

	auto CheckCurrentLastPtValid = [&EFFOscDataRef, &BDSNRDataRef](int CurrentFrameIndex, int LastFrameIndex, int FFTPtIndex, 
		const EN_DiffNetPtEffectType EffType,bool& currentValid, bool& LastValid)
		{
			LastValid = false;
			currentValid = false;

			switch (EffType)
			{
				case EN_DiffNetPtEffectType::STFT:
				{
					LastValid = true;
					currentValid = true;
				}break;
				case EN_DiffNetPtEffectType::EffOsc:
				{
					const ST_WndSpecConstrainPtTag& CurrentEffOscPtTag = EFFOscDataRef.FrameVec[CurrentFrameIndex].VecSTFTPtState[FFTPtIndex];
					currentValid = (CurrentEffOscPtTag.ptConstrainState == EN_WndSepcConstrainState::EffectiveOscillation);

					if (LastFrameIndex >= 0)
					{
						const ST_WndSpecConstrainPtTag& LastEffOscPtTag = EFFOscDataRef.FrameVec[LastFrameIndex].VecSTFTPtState[FFTPtIndex];
						LastValid = (LastEffOscPtTag.ptConstrainState == EN_WndSepcConstrainState::EffectiveOscillation);
					}
					else
					{
						LastValid = false;
					}

				}break;
				case EN_DiffNetPtEffectType::BDSNR:
				{
					const ST_BandWidthSNRPtTag& CurrentBDSNRPtTag = BDSNRDataRef.FrameVec[CurrentFrameIndex].vecBDSNRptTag[FFTPtIndex];
					currentValid = (CurrentBDSNRPtTag.ptSNRConstrainType == EN_BDSNRPtType::BDSNR_EffectivePt);

					if (LastFrameIndex >= 0)
					{
						const ST_BandWidthSNRPtTag& LastBDSNRPtTag = BDSNRDataRef.FrameVec[LastFrameIndex].vecBDSNRptTag[FFTPtIndex];
						LastValid = (LastBDSNRPtTag.ptSNRConstrainType == EN_BDSNRPtType::BDSNR_EffectivePt);
					}
					else
					{
						LastValid = false;
					}
				}break;
				}
		};

	auto setPtGroupIndex = [&NetState](ST_DiffNetPoint& DiffPtTagRef,double LastPtVal,double currentPtVal)
		{
			DiffPtTagRef.Diffval = currentPtVal - LastPtVal;
			DiffPtTagRef.DiffRatio = DiffPtTagRef.Diffval / LastPtVal;

			int sideGroupIndex = (NetState.mapDiffGroup.size() - 1) / 2;

			DiffPtTagRef.getAGroup = false;

			for (int GroupIndex = sideGroupIndex * -1; GroupIndex <= sideGroupIndex; GroupIndex++)
			{
				const ST_DiffNetBiDirectGroup& groupRef = NetState.mapDiffGroup.find(GroupIndex).value();
				if (groupRef.isASideGroup)
				{
					if (GroupIndex < 0 && DiffPtTagRef.DiffRatio < groupRef.endRatio)
					{
						DiffPtTagRef.BidirectGroupIndex = GroupIndex;
						DiffPtTagRef.getAGroup = true;
						break;
					}
					else if (GroupIndex > 0 && DiffPtTagRef.DiffRatio > groupRef.startRatio)
					{
						DiffPtTagRef.BidirectGroupIndex = GroupIndex;
						DiffPtTagRef.getAGroup = true;
						break;
					}
				}
				else
				{
					if (DiffPtTagRef.DiffRatio > groupRef.startRatio && DiffPtTagRef.DiffRatio < groupRef.endRatio)
					{
						DiffPtTagRef.BidirectGroupIndex = GroupIndex;
						DiffPtTagRef.getAGroup = true;
						break;
					}
				}
			}
		};

	for (int FFTPtIndex = 0; FFTPtIndex < FrameData.vecFFTPoint.size(); FFTPtIndex++)
	{
		ST_DiffNetPoint& DiffPtTagRef	= FrameData.vecFFTPoint[FFTPtIndex];
	

		if (currentFrameIndex == 43 && FFTPtIndex == 73)
		{
			int a = 0;
		}

		double currentPtVal = STFTDataRef.vecOutput[currentFrameIndex].resultVec[FFTPtIndex].amplitude;
		double LastPtVal	= 0;

		if (LastFrameIndex >= 0)
		{
			LastPtVal = STFTDataRef.vecOutput[LastFrameIndex].resultVec[FFTPtIndex].amplitude;
		}

		bool currentPtValid	= false;
		bool LastPtValid	= false;

		CheckCurrentLastPtValid(currentFrameIndex, LastFrameIndex, FFTPtIndex, NetPara.EffPtType, currentPtValid, LastPtValid);

		if (!currentPtValid)
		{
			currentPtVal = 0;
		}

		if (!LastPtValid)
		{
			LastPtVal = 0;
		}

		DiffPtTagRef.isDisappear = false;
		DiffPtTagRef.isSuddenAppear = false;

		if (currentPtVal < ZeroDbVal)
		{
			DiffPtTagRef.isDisappear = true;
			DiffPtTagRef.getAGroup = true;
		}
		else if (LastPtVal < ZeroDbVal)
		{
			DiffPtTagRef.isSuddenAppear = true;
			DiffPtTagRef.getAGroup = true;
		}
		else
		{
			setPtGroupIndex(DiffPtTagRef, LastPtVal, currentPtVal);	
		}
	}

	for (int FilterPtIndex = 0; FilterPtIndex < FrameData.vecBandWidthFilterPoint.size(); FilterPtIndex++)
	{
		ST_DiffNetPoint& DiffPtTagRef = FrameData.vecBandWidthFilterPoint[FilterPtIndex];

		double currentPtVal = BDSNRDataRef.FrameVec[currentFrameIndex].vecBDFilterValue[FilterPtIndex].BandWidthFilterVal_SubArea;
		double LastPtVal = 0;

		if (LastFrameIndex >= 0)
		{
			LastPtVal = BDSNRDataRef.FrameVec[LastFrameIndex].vecBDFilterValue[FilterPtIndex].BandWidthFilterVal_SubArea;
		}
	

		const ST_BandWidthFilterPt& CurrentBDSNRFilterTag = BDSNRDataRef.FrameVec[currentFrameIndex].vecBDFilterValue[FilterPtIndex];
		bool currentPtValid = (CurrentBDSNRFilterTag.isActive);

		bool LastPtValid = false;
		if (LastFrameIndex >= 0)
		{
			const ST_BandWidthFilterPt& LastBDSNRFilterTag = BDSNRDataRef.FrameVec[LastFrameIndex].vecBDFilterValue[FilterPtIndex];
			LastPtValid = (LastBDSNRFilterTag.isActive);
		}

		if (!currentPtValid)
		{
			currentPtVal = 0;
		}

		if (!LastPtValid)
		{
			LastPtVal = 0;
		}

		DiffPtTagRef.isDisappear = false;
		DiffPtTagRef.isSuddenAppear = false;

		if (currentPtVal < ZeroDbVal)
		{
			DiffPtTagRef.isDisappear = true;
		}
		else if (LastPtVal < ZeroDbVal)
		{
			DiffPtTagRef.isSuddenAppear = true;
		}
		else
		{
			setPtGroupIndex(DiffPtTagRef, LastPtVal, currentPtVal);
		}
	}

}

void AudioDiffNet::slot_DiffGenProgressValueChanged(int val)
{
	if (m_tempData.FrameVec.isEmpty())
	{
		qDebug() << "AudioDiffNet::slot_DiffGenProgressValueChanged m_tempMFCCData.FrameVec empty!";
		return;
	}

	int			FrameCount = m_tempData.FrameVec.size();
	double		hunderdsOfFrame = qMax(1, FrameCount / 100);
	int			processedCount = val;
	int			percentage = (double)processedCount / hunderdsOfFrame;

	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_Diff_GenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(FrameCount));;
		m_nLastReportPercantage = percentage;
	}

	qDebug() << QString("AudioDiffNet::slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(FrameCount);

	if (processedCount == FrameCount)
	{
		slot_DiffGenFinished();
	}
}

void AudioDiffNet::slot_DiffGenFinished()
{
	DataCenterManager::instance()->slot_saveDiffData(m_tempData.DataKey, m_tempData);

	m_tempData.DiffNetState.mapDiffGroup.clear();
	m_tempData.FrameVec.clear();

}
