#include "BandWidthFilterManager.h"
#pragma execution_character_set("utf-8")

BandWidthFilterManager* BandWidthFilterManager::m_instance = nullptr;

BandWidthFilterManager* BandWidthFilterManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new BandWidthFilterManager();
	}
	return m_instance;
}

BandWidthFilterManager::BandWidthFilterManager() :QObject(nullptr)
{
	m_pConcurrentWatcher = new QFutureWatcher<void>(this);
	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished()));
	connect(m_pConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &BandWidthFilterManager::slot_BDSNRGenProgressValueChanged);

}

QString BandWidthFilterManager::ConstrainPtTypeToStr(EN_BDSNRPtType state)
{
	QString result;
	switch (state)
	{
		case EN_BDSNRPtType::WndSpecNoise		:result = QString("WndSpecNoise"); break;
		case EN_BDSNRPtType::BDSNR_ConstrainPt	:result = QString("BDSNR_ConstrainPt"); break;
		case EN_BDSNRPtType::BDSNR_EffectivePt	:result = QString("BDSNR_EffectivePt"); break;
	}
	return result;
}

double BandWidthFilterManager::NromalFreqToMelFreq(double normalFreq)
{
	return 2595 * log10(1.0 + normalFreq / 700.0);
}

double BandWidthFilterManager::MelFreqToNormalFreq(double melFreq)
{
	return (pow(10.0, melFreq / 2595.0) - 1.0) * 700.0;
}

void BandWidthFilterManager::slot_StartGenBandWidthFilterData(const ST_BandWidthFilterPara& GenPara, ST_BandWidthFilterData& result)
{
	result.para = GenPara;

	GenFileterShape(result);
	GenFilterWeightPt(result);

}

void BandWidthFilterManager::slot_StartBandWidthFilterConstrainData(QString dataKey, const ST_BandWidthFilterPara& FilterPara, const ST_BandWidthFilter_workPara& FilterActivePara)
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

	const ST_STFTOutputData& STFTDataRef = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	m_tempBDSNRData.DataKey = dataKey;
	m_tempBDSNRData.WorkPara = FilterActivePara;
	slot_StartGenBandWidthFilterData(FilterPara, m_tempBDSNRData.FilterData);

	const ST_BandWidthFilterPara& FilterGenPara = m_tempBDSNRData.FilterData.para;

	m_tempBDSNRData.FrameVec.clear();

	int FFTPtTagCount   = m_tempBDSNRData.FilterData.FilterFFTPtIndexVec.size();
	int FilterCount		= FilterGenPara.EqualWidthFilterCount + FilterGenPara.LogWidthFilterCount;
	int FrameCount		= STFTDataRef.vecOutput.size();

	ST_BandWidthFilterPt nullFilterPt;
	ST_BandWidthSNRPtTag nullSNRPtTag;
	ST_BandWidthSNRConstrainFrame nullFilterCFrame;
	nullFilterCFrame.vecBDFilterValue.clear();
	nullFilterCFrame.vecBDSNRptTag.clear();
	nullFilterCFrame.vecBDFilterValue = QVector<ST_BandWidthFilterPt>(FilterCount, nullFilterPt);
	nullFilterCFrame.vecBDSNRptTag	  = QVector<ST_BandWidthSNRPtTag>(FFTPtTagCount, nullSNRPtTag);
	
	for(int SNRPtIndex = 0; SNRPtIndex < FFTPtTagCount; SNRPtIndex++)
	{
		ST_BandWidthSNRPtTag& SNRPtPtRef = nullFilterCFrame.vecBDSNRptTag[SNRPtIndex];
		SNRPtPtRef.ptIndex = SNRPtIndex;
		SNRPtPtRef.ptFreq = STFTDataRef.vecOutput[0].resultVec[SNRPtIndex].frequency;
	}

	m_tempBDSNRData.FrameVec.clear();
	m_tempBDSNRData.FrameVec = QVector<ST_BandWidthSNRConstrainFrame>(FrameCount, nullFilterCFrame);

	for (int FrameIndex = 0; FrameIndex < FrameCount; FrameIndex++)
	{
		ST_BandWidthSNRConstrainFrame& FrameRef = m_tempBDSNRData.FrameVec[FrameIndex];
		FrameRef.FrameInSTFTIndex = FrameIndex;
		FrameRef.FrameStartTime = FrameIndex * STFTDataRef.InputPara.GapInTimeLength;
	}



	QFuture<void> future = QtConcurrent::map(m_tempBDSNRData.FrameVec, BandWidthFilterManager::GenBDSNRFrame);
	m_pConcurrentWatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_BDSNRGenProgressValueChanged(0);
}

void BandWidthFilterManager::GenBDSNRFrame(ST_BandWidthSNRConstrainFrame& BDSNRFrameData)
{
	BandWidthFilterManager::updateFilterVal(BDSNRFrameData);
	BandWidthFilterManager::updatePtTag(BDSNRFrameData);
}

void BandWidthFilterManager::updateFilterVal(ST_BandWidthSNRConstrainFrame& BDSNRFrameData)
{
	int			FrameIndex		= BDSNRFrameData.FrameInSTFTIndex;
	QString		DataKey			= BandWidthFilterManager::instance()->m_tempBDSNRData.DataKey;

	const ST_STFTOutputData&			STFTDataRef			= DataCenterManager::instance()->getSTFTOutputMap().find(DataKey).value();
	const ST_FFTOutputData&				STFTFrameData		= STFTDataRef.vecOutput[FrameIndex];
	const ST_WndSpecConstrainFrame&		WndConstrainFrame	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(DataKey).value().FrameVec[FrameIndex];
	const ST_BandWidthFilterData&		FilterDataRef		= BandWidthFilterManager::instance()->m_tempBDSNRData.FilterData;
	const ST_BandWidthFilter_workPara& FilterWorkPara		= BandWidthFilterManager::instance()->m_tempBDSNRData.WorkPara;


	for (int FilterPtIndex = 0; FilterPtIndex < BDSNRFrameData.vecBDFilterValue.size(); FilterPtIndex++)
	{
		ST_BandWidthFilterPt& FilterPtRef = BDSNRFrameData.vecBDFilterValue[FilterPtIndex];
		FilterPtRef.isActive = false;
		FilterPtRef.BandWidthMaxAmp = 0;
		FilterPtRef.BandWidthMaxAmp_DB = 0;
		FilterPtRef.BandWidthMaxAmpIndex = -1;

		FilterPtRef.BandWidthMaxWeightAmpIndex = -1;
		FilterPtRef.BandWidthMaxWeightAmp = 0;
		FilterPtRef.BandWidthMaxWeightAmp_DB = 0;

		FilterPtRef.BandWidthFilterVal_MainArea = 0;
		FilterPtRef.BandWidthFilterVal_MainArea_DB = 0;

		FilterPtRef.BandWidthFilterVal_SubArea = 0;
		FilterPtRef.BandWidthFilterVal_SubArea_DB = 0;
	}

	auto updateFilterVal = [&FilterWorkPara, &FilterDataRef, &BDSNRFrameData](const int FFTPtIndex, const ST_FFTPoint& FFTPtRef, int FilterIndex, int FilterPtIndex)
		{
			const ST_BandWidthFilter& FilterData = FilterDataRef.FilterVec[FilterIndex];

			const double FFTPtWeight = FilterData.FilterPointVec[FilterPtIndex].Weight / FilterData.centerPtArea;
			const double FFTPtWeightVal = FFTPtRef.amplitude * FFTPtWeight;

			ST_BandWidthFilterPt& FilterPt = BDSNRFrameData.vecBDFilterValue[FilterIndex];

			if (FFTPtRef.amplitude > FilterPt.BandWidthMaxAmp)
			{
				FilterPt.BandWidthMaxAmp = FFTPtRef.amplitude;
				FilterPt.BandWidthMaxAmp_DB = AudioProtocol::fftRealToDB(FFTPtRef.amplitude, const_audio_normalAudioFileMaxDB);
				FilterPt.BandWidthMaxAmpIndex = FFTPtIndex;

				if (FilterWorkPara.FilterMaxValType == EN_BDSNR_FilterMaxValType::maxVal)
				{
					FilterPt.BandWidthFilterVal_MainArea = FFTPtRef.amplitude * FilterWorkPara.FilterValDecrease_MainArea_Ratio;
					FilterPt.BandWidthFilterVal_MainArea_DB = AudioProtocol::fftRealToDB(FilterPt.BandWidthFilterVal_MainArea, const_audio_normalAudioFileMaxDB);

					FilterPt.BandWidthFilterVal_SubArea = FFTPtRef.amplitude * FilterWorkPara.FilterValDecrease_SubArea_Ratio;
					FilterPt.BandWidthFilterVal_SubArea_DB = AudioProtocol::fftRealToDB(FilterPt.BandWidthFilterVal_SubArea, const_audio_normalAudioFileMaxDB);

					if (FilterPt.BandWidthFilterVal_MainArea_DB > 0)
					{
						FilterPt.isActive = true;
					}
				}
			}

			if (FFTPtWeightVal > FilterPt.BandWidthMaxWeightAmp)
			{
				FilterPt.BandWidthMaxWeightAmp = FFTPtWeightVal;
				FilterPt.BandWidthMaxWeightAmp_DB = AudioProtocol::fftRealToDB(FFTPtWeightVal, const_audio_normalAudioFileMaxDB);
				FilterPt.BandWidthMaxWeightAmpIndex = FFTPtIndex;
				FilterPt.BandWidthMaxWeightAmpWeight = FFTPtWeight;

				if (FilterWorkPara.FilterMaxValType == EN_BDSNR_FilterMaxValType::maxVal_Weight)
				{
					FilterPt.BandWidthFilterVal_MainArea = FFTPtWeightVal * FilterWorkPara.FilterValDecrease_MainArea_Ratio;
					FilterPt.BandWidthFilterVal_MainArea_DB = AudioProtocol::fftRealToDB(FilterPt.BandWidthFilterVal_MainArea, const_audio_normalAudioFileMaxDB);

					FilterPt.BandWidthFilterVal_SubArea = FFTPtWeightVal * FilterWorkPara.FilterValDecrease_SubArea_Ratio;
					FilterPt.BandWidthFilterVal_SubArea_DB = AudioProtocol::fftRealToDB(FilterPt.BandWidthFilterVal_SubArea, const_audio_normalAudioFileMaxDB);

					if (FilterPt.BandWidthFilterVal_MainArea_DB > 0)
					{
						FilterPt.isActive = true;
					}
				}
			}
		};


	for (int FFTPtIndex = 0; FFTPtIndex < FilterDataRef.FilterFFTPtIndexVec.size(); FFTPtIndex++)
	{
		const ST_FFTPtInBDFilterLocation& LocData = FilterDataRef.FilterFFTPtIndexVec[FFTPtIndex];
		const ST_FFTPoint& FFTPt = STFTFrameData.resultVec[FFTPtIndex];
		const ST_WndSpecConstrainPtTag& WndSpecConstrainPtTag = WndConstrainFrame.VecSTFTPtState[FFTPtIndex];

		if (LocData.FFTPtFreq - FFTPt.frequency > 0.01)
		{
			qDebug() << QString("BandWidthFilterManager::GenBDSNRFrame MFCCLocData Freq Err : %1 : %2").arg(LocData.FFTPtFreq).arg(FFTPt.frequency);
		}

		if (WndSpecConstrainPtTag.ptConstrainState != EN_WndSepcConstrainState::EffectiveOscillation)
		{
			continue;
		}

		if (LocData.FirstFilterIndex != -1)
		{
			updateFilterVal(FFTPtIndex, FFTPt, LocData.FirstFilterIndex, LocData.FirstFilterPtIndex);
		}

		if (LocData.SecondFileterIndex != -1)
		{
			updateFilterVal(FFTPtIndex, FFTPt, LocData.SecondFileterIndex, LocData.SecondFilterPtIndex);
		}

		if (LocData.ThirdFilterIndex != -1)
		{
			updateFilterVal(FFTPtIndex, FFTPt, LocData.ThirdFilterIndex, LocData.ThirdFilterPtIndex);
		}

	}
}

void BandWidthFilterManager::updatePtTag(ST_BandWidthSNRConstrainFrame& BDSNRFrameData)
{
	int FrameIndex = BDSNRFrameData.FrameInSTFTIndex;
	QString DataKey = BandWidthFilterManager::instance()->m_tempBDSNRData.DataKey;

	const ST_STFTOutputData&			STFTDataRef			= DataCenterManager::instance()->getSTFTOutputMap().find(DataKey).value();
	const ST_FFTOutputData&				STFTFrameData		= STFTDataRef.vecOutput[FrameIndex];
	const ST_WndSpecConstrainFrame&		WndConstrainFrame	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(DataKey).value().FrameVec[FrameIndex];
	const ST_BandWidthFilterData&		FilterDataRef		= BandWidthFilterManager::instance()->m_tempBDSNRData.FilterData;
	const ST_BandWidthFilter_workPara&	FilterWorkPara		= BandWidthFilterManager::instance()->m_tempBDSNRData.WorkPara;

	auto getFilterVal = [&BDSNRFrameData, &FilterDataRef, &FilterWorkPara](int FilterIndex		, int FilterPtIndex		,double& PtInFilterWeight
																		 , bool& FilterActive	, double& FilterVal_Main,double& FilterVal_Sub)
		{
			if (FilterIndex == -1)
			{
				return;
			}

			const ST_BandWidthFilter&		FilterData			= FilterDataRef.FilterVec[FilterIndex];
											PtInFilterWeight	= FilterData.FilterPointVec[FilterPtIndex].Weight / FilterData.centerPtArea;
			const ST_BandWidthFilterPt&		FilterPt			= BDSNRFrameData.vecBDFilterValue[FilterIndex];
											FilterActive		= FilterPt.isActive;
											FilterVal_Main		= FilterPt.BandWidthFilterVal_MainArea;
											FilterVal_Sub		= FilterPt.BandWidthFilterVal_SubArea;
		};

	auto checkFFTPtBeFiltered = [](const EN_BDSNR_FilterCondition filterCond,const double ptVal,
									bool FirstFilterIsActive	, double FirstFilterWeight	,double FirstFilterVal,
									bool SecondFilterIsActive	, double SecondFilterWeight	,double SecondFilterVal,
									bool ThirdFilterIsActive	, double ThirdFilterWeight	,double ThirdFilterVal,
									bool& beFiltered			, double& FilterVal
		)
		{
			beFiltered = true;
			switch (filterCond)
			{
				case EN_BDSNR_FilterCondition::filter_strong:
			{
					beFiltered = false;
					if (FirstFilterIsActive)	beFiltered |= ptVal < FirstFilterVal;
					if (SecondFilterIsActive)	beFiltered |= ptVal < SecondFilterVal;
					if (ThirdFilterIsActive)	beFiltered |= ptVal < ThirdFilterVal;
				FilterVal = qMax(qMax(FirstFilterVal, SecondFilterVal), ThirdFilterVal);
			}break;
			case EN_BDSNR_FilterCondition::filter_weak:
			{
				beFiltered = true;
				if (!FirstFilterIsActive && !SecondFilterIsActive && !ThirdFilterIsActive)
				{
					beFiltered = false;
					FilterVal = 0;
				}
				else
				{
					if (FirstFilterIsActive)	beFiltered &= ptVal < FirstFilterVal;
					if (SecondFilterIsActive)	beFiltered &= ptVal < SecondFilterVal;
					if (ThirdFilterIsActive)	beFiltered &= ptVal < ThirdFilterVal;

					double tempMaxVal = qMax(qMax(FirstFilterVal, SecondFilterVal), ThirdFilterVal);
					if (FirstFilterIsActive && FirstFilterVal > 0)
					{
						FilterVal = qMin(tempMaxVal, FirstFilterVal);
					}
					if (SecondFilterIsActive && SecondFilterVal > 0)
					{
						FilterVal = qMin(tempMaxVal, SecondFilterVal);
					}
					if (ThirdFilterIsActive && ThirdFilterVal > 0)
					{
						FilterVal = qMin(tempMaxVal, ThirdFilterVal);
					}
				}

				
			}break;
			case EN_BDSNR_FilterCondition::filter_weight:
			{
				double totalWeight = 0;

				if (FirstFilterIsActive)	totalWeight += FirstFilterWeight;
				if (SecondFilterIsActive)	totalWeight += SecondFilterWeight;
				if (ThirdFilterIsActive)	totalWeight += ThirdFilterWeight;

				FilterVal = 0;

				if (FirstFilterIsActive)	FilterVal += FirstFilterWeight / totalWeight * FirstFilterVal;
				if (SecondFilterIsActive)	FilterVal += SecondFilterWeight / totalWeight * SecondFilterVal;
				if (ThirdFilterIsActive)	FilterVal += ThirdFilterWeight / totalWeight * ThirdFilterVal;

				beFiltered = ptVal < FilterVal;

			}break;
			}
		};


	for (int FFTPtIndex = 0; FFTPtIndex < FilterDataRef.FilterFFTPtIndexVec.size(); FFTPtIndex++)
	{
		const ST_FFTPtInBDFilterLocation& LocData = FilterDataRef.FilterFFTPtIndexVec[FFTPtIndex];
		const ST_FFTPoint& FFTPt = STFTFrameData.resultVec[FFTPtIndex];
		const ST_WndSpecConstrainPtTag& WndSpecConstrainPtTag = WndConstrainFrame.VecSTFTPtState[FFTPtIndex];

		ST_BandWidthSNRPtTag& BDSNRPtTag = BDSNRFrameData.vecBDSNRptTag[FFTPtIndex];

		if (WndSpecConstrainPtTag.ptConstrainState != EN_WndSepcConstrainState::EffectiveOscillation)
		{
			BDSNRPtTag.ptSNRConstrainType = EN_BDSNRPtType::WndSpecNoise;
			continue;
		}

		double FirstFilterWeight		= 0;
		bool   FirstFilterIsActive		= false;
		double FirstFilterVal_Main		= 0;
		double FirstFilterVal_Sub		= 0;		
		
		double SecondFilterWeight		= 0;
		bool   SecondFilterIsActive		= false;
		double SecondFilterVal_Main		= 0;
		double SecondFilterVal_Sub		= 0;

		double ThirdFilterWeight		= 0;
		bool   ThirdFilterIsActive		= false;
		double ThirdFilterVal_Main		= 0;
		double ThirdFilterVal_Sub		= 0;

		if (LocData.FirstFilterIndex != -1)
		{
			getFilterVal(LocData.FirstFilterIndex, LocData.FirstFilterPtIndex, FirstFilterWeight
						,FirstFilterIsActive, FirstFilterVal_Main, FirstFilterVal_Sub);
		}

		if (LocData.SecondFileterIndex != -1)
		{
			getFilterVal(LocData.SecondFileterIndex, LocData.SecondFilterPtIndex, SecondFilterWeight
						,SecondFilterIsActive, SecondFilterVal_Main, SecondFilterVal_Sub);
		}

		if (LocData.ThirdFilterIndex != -1)
		{
			getFilterVal(LocData.ThirdFilterIndex, LocData.ThirdFilterPtIndex, ThirdFilterWeight
						, ThirdFilterIsActive, ThirdFilterVal_Main, ThirdFilterVal_Sub);
		}

		if (LocData.FirstFilterIndex != -1 && LocData.SecondFileterIndex != -1 && LocData.ThirdFilterIndex != -1)
		{
			BDSNRPtTag.ptSNRConstrainType = EN_BDSNRPtType::WndSpecNoise;
		}
		else
		{
			bool	BeFilteredBySub	= true;
			double	SubFilterVal	= 0;

				
			checkFFTPtBeFiltered(FilterWorkPara.FilterCondition_SubArea		, FFTPt.amplitude,
								FirstFilterIsActive	, FirstFilterWeight		, FirstFilterVal_Sub,
								SecondFilterIsActive, SecondFilterWeight	, SecondFilterVal_Sub,
								ThirdFilterIsActive	, ThirdFilterWeight		, ThirdFilterVal_Sub,
								BeFilteredBySub		, SubFilterVal);


			if (BeFilteredBySub)
			{
				BDSNRPtTag.ptSNRConstrainType = EN_BDSNRPtType::BDSNR_ConstrainPt;
				BDSNRPtTag.MaskAmp_Sub = SubFilterVal;
				continue;
			}
			else
			{
				BDSNRPtTag.ptSNRConstrainType = EN_BDSNRPtType::BDSNR_EffectivePt;
				BDSNRPtTag.MaskAmp_Sub = 0;
			}

			bool	BeFilteredByMain = true;
			double	MainFilterVal = 0;


			checkFFTPtBeFiltered(	FilterWorkPara.FilterCondition_MainArea, FFTPt.amplitude,
									FirstFilterIsActive		, FirstFilterWeight, FirstFilterVal_Main,
									SecondFilterIsActive	, SecondFilterWeight, SecondFilterVal_Main,
									ThirdFilterIsActive		, ThirdFilterWeight, ThirdFilterVal_Main,
									BeFilteredByMain, MainFilterVal);

			BDSNRPtTag.isMainAreaSignal = !BeFilteredByMain;
			if (!BDSNRPtTag.isMainAreaSignal)
			{
				BDSNRPtTag.MaskAmp_Main = MainFilterVal;
			}
			
		}

	}
}


void BandWidthFilterManager::GenFileterShape(ST_BandWidthFilterData& result)
{
	const ST_BandWidthFilterPara& para = result.para;
	int FilterCount = result.para.EqualWidthFilterCount + result.para.LogWidthFilterCount;

	ST_BandWidthFilter nullFilter;
	result.FilterVec.clear();
	result.FilterVec = QVector<ST_BandWidthFilter>(FilterCount, nullFilter);

	double EqualWidthFilterGap = (double)para.EqualWidthFilterMaxFreq / (double)para.EqualWidthFilterCount;

	for (int Freqindex = 0; Freqindex < para.EqualWidthFilterCount; Freqindex++)
	{
		ST_BandWidthFilter& FilterRef = result.FilterVec[Freqindex];

		FilterRef.startFreq		= Freqindex * EqualWidthFilterGap;
		FilterRef.CenterFreq	= FilterRef.startFreq + EqualWidthFilterGap;
		FilterRef.endFreq		= FilterRef.CenterFreq + EqualWidthFilterGap;
		FilterRef.Width			= EqualWidthFilterGap * 2;
		FilterRef.maxWeight		= 2.0 / FilterRef.Width;
		result.maxWeight		= std::max(result.maxWeight, FilterRef.maxWeight);
	}

	double startMelFreq		= NromalFreqToMelFreq(para.EqualWidthFilterMaxFreq);
	double endMelFreq		= NromalFreqToMelFreq(para.EndFreq);
	double MelFreqInterval	= (endMelFreq - startMelFreq) / (para.LogWidthFilterCount + 1);

	int logFilterStartIndex = para.EqualWidthFilterCount;

	for (int Freqindex = 0; Freqindex < para.LogWidthFilterCount; Freqindex++)
	{
		ST_BandWidthFilter& FilterRef = result.FilterVec[logFilterStartIndex + Freqindex];

		double FilterStartMelFreq	= startMelFreq + Freqindex * MelFreqInterval;
		double FilterEndMelFreq		= startMelFreq + (Freqindex + 2) * MelFreqInterval;

		FilterRef.startFreq		= MelFreqToNormalFreq(FilterStartMelFreq);
		FilterRef.endFreq		= MelFreqToNormalFreq(FilterEndMelFreq);
		FilterRef.Width			= FilterRef.endFreq - FilterRef.startFreq;
		FilterRef.CenterFreq	= FilterRef.startFreq + FilterRef.Width / 2;
		FilterRef.maxWeight		= 2.0 / FilterRef.Width;
		result.maxWeight		= std::max(result.maxWeight, FilterRef.maxWeight);

	}
}

void BandWidthFilterManager::GenFilterWeightPt(ST_BandWidthFilterData& result)
{
	double SecPerPt = 1.0 / (double)result.para.sampleRate;
	double WndTimeLength = SecPerPt * result.para.WndPtCount;
	double FreqDelta = 1.0 / WndTimeLength;
	int	   FreqPtCount = ceil(result.para.EndFreq / FreqDelta);

	int FilterCount = result.FilterVec.size();

	result.FilterFFTPtIndexVec.clear();
	ST_FFTPtInBDFilterLocation nullLocPt;
	nullLocPt.FFTPtFreq = -1;
	nullLocPt.FirstFilterIndex = -1;
	nullLocPt.SecondFileterIndex = -1;
	nullLocPt.ThirdFilterIndex = -1;
	result.FilterFFTPtIndexVec = QVector<ST_FFTPtInBDFilterLocation>(FreqPtCount, nullLocPt);

	for (int FilterIndex = 0; FilterIndex < FilterCount; FilterIndex++)
	{
		ST_BandWidthFilter& filterRef = result.FilterVec[FilterIndex];

		int startFreqIndex = 0;

		if (filterRef.startFreq - floor(filterRef.startFreq / FreqDelta) * FreqDelta < 0.001)
		{
			startFreqIndex = floor(filterRef.startFreq / FreqDelta);
		}
		else
		{
			startFreqIndex = floor(filterRef.startFreq / FreqDelta) + 1;
		}

		int endFreqIndex = floor(filterRef.endFreq / FreqDelta);
		int middlePtFreq = round(filterRef.CenterFreq / FreqDelta);

		int FreqCount = endFreqIndex - startFreqIndex + 1;

		if (FreqCount <= 0)
		{
			qDebug() << "MFCCManager::GenFilterWeightPt invalid FreqCount : " << FreqCount;
			continue;
		}

		ST_BandWidthFilterWeightPt nullMFCCPt;
		filterRef.FilterPointVec.clear();
		filterRef.FilterPointVec = QVector<ST_BandWidthFilterWeightPt>(FreqCount, nullMFCCPt);

		double FilterHalfWidth = filterRef.Width / 2;

		for (int MFCCPtIndex = 0; MFCCPtIndex < FreqCount; MFCCPtIndex++)
		{
			ST_BandWidthFilterWeightPt& MFCCPt = filterRef.FilterPointVec[MFCCPtIndex];
			int FreqIndex = MFCCPtIndex + startFreqIndex;
			MFCCPt.Freq = FreqIndex * FreqDelta;
			MFCCPt.ptIndexInFFT = FreqIndex;

			double leftFreq = std::max(MFCCPt.Freq - FreqDelta / 2, filterRef.startFreq);
			double rightFreq = std::min(MFCCPt.Freq + FreqDelta / 2, filterRef.endFreq);

			if (FreqIndex < middlePtFreq)
			{
				double leftWeight = (leftFreq - filterRef.startFreq) / FilterHalfWidth * filterRef.maxWeight;
				double rightWeight = (rightFreq - filterRef.startFreq) / FilterHalfWidth * filterRef.maxWeight;
				MFCCPt.Weight = (leftWeight + rightWeight) * FreqDelta / 2;
			}
			else if (FreqIndex > middlePtFreq)
			{
				double leftWeight = (filterRef.endFreq - leftFreq) / FilterHalfWidth * filterRef.maxWeight;
				double rightWeight = (filterRef.endFreq - rightFreq) / FilterHalfWidth * filterRef.maxWeight;
				MFCCPt.Weight = (leftWeight + rightWeight) * FreqDelta / 2;
			}
			else
			{
				double leftWeight = (leftFreq - filterRef.startFreq) / FilterHalfWidth * filterRef.maxWeight;
				double rightWeight = (filterRef.endFreq - rightFreq) / FilterHalfWidth * filterRef.maxWeight;

				MFCCPt.Weight += (leftWeight + filterRef.maxWeight) * (filterRef.CenterFreq - leftFreq) / 2;
				MFCCPt.Weight += (rightWeight + filterRef.maxWeight) * (rightFreq - filterRef.CenterFreq) / 2;
			}

			ST_FFTPtInBDFilterLocation& LocRef = result.FilterFFTPtIndexVec[FreqIndex];
			if (LocRef.FFTPtFreq == -1)
			{
				LocRef.FFTPtFreq = MFCCPt.Freq;
				LocRef.FirstFilterIndex = FilterIndex;
				LocRef.FirstFilterPtIndex = MFCCPtIndex;
			}
			else if (LocRef.SecondFileterIndex == -1)
			{
				LocRef.SecondFileterIndex = FilterIndex;
				LocRef.SecondFilterPtIndex = MFCCPtIndex;
			}
			else if (LocRef.ThirdFilterIndex == -1)
			{
				LocRef.ThirdFilterIndex = FilterIndex;
				LocRef.ThirdFilterPtIndex = MFCCPtIndex;
			}

		}
	}

	for (int FilterIndex = 0; FilterIndex < FilterCount; FilterIndex++)
	{
		ST_BandWidthFilter& filterRef = result.FilterVec[FilterIndex];
		int FFTPtCount = filterRef.FilterPointVec.size();
		for (int MFCCPtIndex = 0; MFCCPtIndex < FFTPtCount; MFCCPtIndex++)
		{
			const ST_BandWidthFilterWeightPt& WeightPt = filterRef.FilterPointVec[MFCCPtIndex];
			filterRef.centerPtArea = qMax(filterRef.centerPtArea, WeightPt.Weight);
		}
	}

}

void BandWidthFilterManager::slot_BDSNRGenProgressValueChanged(int val)
{
	if (m_tempBDSNRData.FrameVec.isEmpty())
	{
		qDebug() << "BandWidthFilterManager::slot_BDSNRGenProgressValueChanged m_tempMFCCData.FrameVec empty!";
		return;
	}

	int			FrameCount = m_tempBDSNRData.FrameVec.size();
	double		hunderdsOfFrame = qMax(1, FrameCount / 100);
	int			processedCount = val;
	int			percentage = (double)processedCount / hunderdsOfFrame;

	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_BDSNR_GenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(FrameCount));;
		m_nLastReportPercantage = percentage;
	}

	qDebug() << QString("BandWidthFilterManager::slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(FrameCount);

	if (processedCount == FrameCount)
	{
		slot_BDSNRGenFinished();
	}
}

void BandWidthFilterManager::slot_BDSNRGenFinished()
{
	DataCenterManager::instance()->slot_saveBDSNRData(m_tempBDSNRData.DataKey, m_tempBDSNRData);

	m_tempBDSNRData.FilterData.FilterFFTPtIndexVec.clear();
	m_tempBDSNRData.FilterData.FilterVec.clear();
	m_tempBDSNRData.FrameVec.clear();

}
