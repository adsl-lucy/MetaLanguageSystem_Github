#include "FreqDoubleNetwork.h"

#pragma execution_character_set("utf-8")

FreqDoubleNetwork* FreqDoubleNetwork::m_instance = nullptr;

FreqDoubleNetwork* FreqDoubleNetwork::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new FreqDoubleNetwork();
	}
	return m_instance;
}

FreqDoubleNetwork::FreqDoubleNetwork() :QObject(nullptr)
{
	m_pConcurrentWatcher = new QFutureWatcher<void>(this);
	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished()));
	connect(m_pConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &FreqDoubleNetwork::slot_FreqDoubGenProgressValueChanged);
}

int	FreqDoubleNetwork::getMatrixIndex(const ST_FreqMultipleTensor& Tensor, double freq)
{
	if (freq <Tensor.resultPara.tensorStartFreqVal || freq > Tensor.resultPara.tensorEndFreqVal)
	{
		return -1;
	}

	int Index = round((freq - Tensor.resultPara.tensorStartFreqVal) / Tensor.resultPara.TensorFreqInterval);
	return Index;
}

void FreqDoubleNetwork::duplicateFreqDoubleTensor(const ST_FreqMultipleTensor& source, ST_FreqMultipleTensor& target)
{
	target.GenPara = source.GenPara;
	target.resultPara = source.resultPara;
	target.VecMultipleMatrix.clear();
	ST_FreqMultipleMaxtrix nullMatrix;
	target.VecMultipleMatrix = QVector<ST_FreqMultipleMaxtrix>(source.VecMultipleMatrix.size(), nullMatrix);
	for (int MatrixIndex = 0; MatrixIndex < target.VecMultipleMatrix.size(); MatrixIndex++)
	{
		const ST_FreqMultipleMaxtrix&	sourceMatrix = source.VecMultipleMatrix[MatrixIndex];
		ST_FreqMultipleMaxtrix&			targetMatrix = target.VecMultipleMatrix[MatrixIndex];

		ST_FreqMultiplePos nullMultiplePos;
		targetMatrix.vecMultiplePos.clear();
		targetMatrix.vecMultiplePos = QVector<ST_FreqMultiplePos>(sourceMatrix.vecMultiplePos.size(), nullMultiplePos);

		for (int MutiPlePosIndex = 0; MutiPlePosIndex < sourceMatrix.vecMultiplePos.size(); MutiPlePosIndex++)
		{
			const	ST_FreqMultiplePos& sourceMultiplePos = sourceMatrix.vecMultiplePos[MutiPlePosIndex];
					ST_FreqMultiplePos& targetMultiplePos = targetMatrix.vecMultiplePos[MutiPlePosIndex];

			targetMultiplePos = sourceMultiplePos;
		}
	}

}

void FreqDoubleNetwork::startGenFreqDoubleTensor(const ST_FreqMultipleTensorGenPara& GenPara, ST_FreqMultipleTensor& resultTensor)
{
	resultTensor.GenPara = GenPara;
	resultTensor.VecMultipleMatrix.clear();
	
	const double FFTFreqInterval = (double)GenPara.sampleRate / (double)GenPara.WndPtCount;

	resultTensor.resultPara.FFTFreqInterval				= FFTFreqInterval;
	resultTensor.resultPara.TensorFreqInterval			= FFTFreqInterval / 2;
	resultTensor.resultPara.tensorStartFFTFreqIndex		= floor(GenPara.startFreq								/ FFTFreqInterval);
	resultTensor.resultPara.tensorEndFFTFreqIndex		= floor(GenPara.endFreq									/ FFTFreqInterval);
	resultTensor.resultPara.tensorStartFreqVal			= resultTensor.resultPara.tensorStartFFTFreqIndex		* FFTFreqInterval;
	resultTensor.resultPara.tensorEndFreqVal			= resultTensor.resultPara.tensorEndFFTFreqIndex			* FFTFreqInterval;
	resultTensor.resultPara.tensorEffectFFTPtCount		= floor(GenPara.MaxEffectFreq							/ FFTFreqInterval) + 1;
	resultTensor.resultPara.tensorMaxEffectFFTPtFreq	= (resultTensor.resultPara.tensorEffectFFTPtCount - 1)	* FFTFreqInterval;

	int MatrixCount = (resultTensor.resultPara.tensorEndFFTFreqIndex - resultTensor.resultPara.tensorStartFFTFreqIndex) * 2 + 1;

	resultTensor.resultPara.tensorTotalEffectPtCount = 0;
	resultTensor.resultPara.tensorTotalPtCount = pow(resultTensor.resultPara.tensorEffectFFTPtCount, 2) * MatrixCount;

	ST_FreqMultipleMaxtrix nullMatrix;
	nullMatrix.BaseFreqIndex_int	= -1;
	nullMatrix.BaseFreqIndex_double = -1.0;
	resultTensor.VecMultipleMatrix = QVector<ST_FreqMultipleMaxtrix>(MatrixCount, nullMatrix);

	const ST_FreqMultipleTensorResultPara& resultPara = resultTensor.resultPara;

	int hundredsOfMatrix = qMax(1,MatrixCount / 100);

	const double	TensorStartFreq			= resultTensor.resultPara.tensorStartFreqVal;
	const double	TensorFreqInterval		= resultTensor.resultPara.TensorFreqInterval;
	const int		TensorFFTStartIndex		= resultTensor.resultPara.tensorStartFFTFreqIndex;
	const int		TensorFFTEndIndex		= resultTensor.resultPara.tensorEndFFTFreqIndex;

	for (int MatrixIndex = 0; MatrixIndex < MatrixCount; MatrixIndex++)
	{
		ST_FreqMultipleMaxtrix& newMatrix = resultTensor.VecMultipleMatrix[MatrixIndex];

		newMatrix.isInsertFreq = (MatrixIndex % 2 == 1);
		newMatrix.BaseFreq = resultPara.tensorStartFreqVal +  MatrixIndex * resultPara.TensorFreqInterval;

		if (newMatrix.isInsertFreq)
		{
			newMatrix.BaseFreqIndex_double	= newMatrix.BaseFreq / resultPara.FFTFreqInterval;
			newMatrix.IntervalHalfWidth		= (1 - 2 * GenPara.FFTWndPeakDriftRatio) * FFTFreqInterval / 2.0;
		}
		else
		{
			newMatrix.BaseFreqIndex_int		= newMatrix.BaseFreq / resultPara.FFTFreqInterval;
			newMatrix.IntervalHalfWidth		= GenPara.FFTWndPeakDriftRatio * FFTFreqInterval;			
		}
				
		newMatrix.selfOverlappingStartMultipleTime = floor((newMatrix.BaseFreq / newMatrix.IntervalHalfWidth + 1) / 2.0);
		newMatrix.vecMultiplePos.clear();

		int MaxEffectMultiplePosCount = qMin(GenPara.maxMultipleTime, (int)floor(GenPara.MaxEffectFreq / newMatrix.BaseFreq));
		int EffectMultiplePosCount = 0;
		if (GenPara.isCutOffOnSelOverlappingStartPos)
		{
			EffectMultiplePosCount = qMin(newMatrix.selfOverlappingStartMultipleTime, MaxEffectMultiplePosCount);
		}
		else
		{
			EffectMultiplePosCount = MaxEffectMultiplePosCount;
		}

		ST_FreqMultiplePos nullMultplePos;
		newMatrix.vecMultiplePos = QVector<ST_FreqMultiplePos>(EffectMultiplePosCount, nullMultplePos);

		for (int MutiPlePosIndex = 0; MutiPlePosIndex < EffectMultiplePosCount; MutiPlePosIndex++)
		{
			ST_FreqMultiplePos& newMutiplePos = newMatrix.vecMultiplePos[MutiPlePosIndex];
			newMutiplePos.multipleTime		= MutiPlePosIndex + 1;
			newMutiplePos.ExactStartFreq	= (newMatrix.BaseFreq - newMatrix.IntervalHalfWidth) * newMutiplePos.multipleTime;
			newMutiplePos.ExactEndFreq		= qMin(GenPara.MaxEffectFreq,(newMatrix.BaseFreq + newMatrix.IntervalHalfWidth) * newMutiplePos.multipleTime);

			int startMatrixIndex	= getOpenAreaIndex((newMutiplePos.ExactStartFreq	- TensorStartFreq) / TensorFreqInterval	,true);
			int endMatrixIndex		= getOpenAreaIndex((newMutiplePos.ExactEndFreq		- TensorStartFreq) / TensorFreqInterval	,false);

			if (startMatrixIndex >= MatrixCount)
			{
				newMutiplePos.startMatrixIndex = -1;
			}
			else
			{
				newMutiplePos.startMatrixIndex = startMatrixIndex;
			}

			if (endMatrixIndex < MatrixCount)
			{
				newMutiplePos.endMatrixIndex = endMatrixIndex;
			}
			else
			{
				if (newMutiplePos.startMatrixIndex == -1)
				{
					newMutiplePos.endMatrixIndex = -1;
				}
				else
				{
					newMutiplePos.endMatrixIndex = MatrixCount - 1;
				}
			}


			newMutiplePos.startFreqIndex	= getOpenAreaIndex(newMutiplePos.ExactStartFreq	/ FFTFreqInterval,true);
			newMutiplePos.endFreqIndex		= getOpenAreaIndex(newMutiplePos.ExactEndFreq	/ FFTFreqInterval,false);

			newMutiplePos.TruncateStartFreq = newMutiplePos.startFreqIndex	* FFTFreqInterval;
			newMutiplePos.TruncateEndFreq	= newMutiplePos.endFreqIndex	* FFTFreqInterval;
			newMatrix.totalPtCount_FFT		+= newMutiplePos.endFreqIndex - newMutiplePos.startFreqIndex + 1;
		}

		resultTensor.resultPara.tensorTotalEffectPtCount += newMatrix.totalPtCount_FFT;

		if (MatrixIndex % hundredsOfMatrix == 0)
		{
			emit sgn_FDN_GenState(MatrixIndex / hundredsOfMatrix, 1, QString(" %1 / %2").arg(MatrixIndex).arg(MatrixCount));
		}

	}

	resultTensor.resultPara.tensorFillRate = (double)resultTensor.resultPara.tensorTotalEffectPtCount / (double)resultTensor.resultPara.tensorTotalPtCount;

	emit sgn_FDN_GenState(100, 1, QString(" %1 / %2").arg(MatrixCount).arg(MatrixCount));

}


void FreqDoubleNetwork::slot_StartGenFreqDoubleNetworkOutput(QString dataKey, const ST_FreqMultipleTensorGenPara& GenPara, const ST_FMTActiveCond& ActiveCond)
{
	bool STFTExist		= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	bool EffOscExist	= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, dataKey);
	bool BDSNRExist		= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, dataKey);
	bool DiffExist		= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::Diff, dataKey);
	if (!STFTExist || !EffOscExist || !BDSNRExist || !DiffExist)
	{
		qDebug() << QString("FreqDoubleNetwork::slot_StartGenFreqDoubleNetworkOutput Invalid DataState : STFT : %1 EffOsc : %2 BDSNR : %3 Diff : %4")
			.arg(AudioProtocol::boolToStr(STFTExist))
			.arg(AudioProtocol::boolToStr(EffOscExist))
			.arg(AudioProtocol::boolToStr(BDSNRExist))
			.arg(AudioProtocol::boolToStr(DiffExist));
		return;
	}

	const ST_STFTOutputData&				STFTDataRef		= DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();
	const ST_WndSpecConstrainResult&		EFFOscDataRef	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(dataKey).value();
	const ST_BandWidthSNRConstrainData&		BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value();
	const ST_DiffNetOutput&					DiffDataRef		= DataCenterManager::instance()->getDiffOutputMap().find(dataKey).value();

	int STFTPtCount		= STFTDataRef.vecOutput[0].resultVec.size();
	int EffOscPtCount	= EFFOscDataRef.FrameVec[0].VecSTFTPtState.size();
	int BDSNRPtCount	= BDSNRDataRef.FrameVec[0].vecBDSNRptTag.size();
	int DiffPtCount		= DiffDataRef.FrameVec[0].vecFFTPoint.size();

	m_tempData.dataKey = dataKey;
	startGenFreqDoubleTensor(GenPara, m_tempData.Tensor);
	m_tempData.ActiveCond = ActiveCond;	

	ST_FreqDoubleNetworkFrame nullFrame;
	nullFrame.VecParentPt.clear();
	nullFrame.VecChildPt.clear();
	int ParentPtCount = m_tempData.Tensor.VecMultipleMatrix.size();
	int FFTPtCount = BDSNRPtCount;
	ST_FreqMultipleNetworkParentPt nullParentPt;
	ST_FreqMultipleNetworkChildPt  nullChildPt;
	nullFrame.VecParentPt	= QVector<ST_FreqMultipleNetworkParentPt>(ParentPtCount, nullParentPt);
	nullFrame.VecChildPt = QVector<ST_FreqMultipleNetworkChildPt>(FFTPtCount, nullChildPt);

	for (int ParentPtIndex = 0; ParentPtIndex < ParentPtCount; ParentPtIndex++)
	{
		const	ST_FreqMultipleMaxtrix&			MatrixRef	= m_tempData.Tensor.VecMultipleMatrix[ParentPtIndex];
				ST_FreqMultipleNetworkParentPt& parentPtRef = nullFrame.VecParentPt[ParentPtIndex];

		parentPtRef.MatrixIndex		= ParentPtIndex;
		parentPtRef.isInsertFreq	= MatrixRef.isInsertFreq;
	}

	for (int ChildPtIndex = 0; ChildPtIndex < FFTPtCount; ChildPtIndex++)
	{
		const	ST_FFTPoint&					FFTPtRef	= STFTDataRef.vecOutput[0].resultVec[ChildPtIndex];
				ST_FreqMultipleNetworkChildPt&	childPtRef	= nullFrame.VecChildPt[ChildPtIndex];

				childPtRef.FFTPtIndex = ChildPtIndex;
				childPtRef.centerFreq = FFTPtRef.frequency;
				childPtRef.isActiveBaseFreq = false;
				childPtRef.HasParentFreq = false;
	}

	int FrameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::STFTOutputData, dataKey);

	m_tempData.FrameVec.clear();
	m_tempData.FrameVec = QVector<ST_FreqDoubleNetworkFrame>(FrameCount, nullFrame);

	for (int FrameIndex = 0; FrameIndex < FrameCount; FrameIndex++)
	{
		ST_FreqDoubleNetworkFrame& FrameRef = m_tempData.FrameVec[FrameIndex];
		FrameRef.FrameIndex = FrameIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_tempData.FrameVec, FreqDoubleNetwork::GenFreqDoubFrame);
	m_pConcurrentWatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_FreqDoubGenProgressValueChanged(0);

}

void FreqDoubleNetwork::GenFreqDoubFrame(ST_FreqDoubleNetworkFrame& FreqDoubFrameRef)
{
	int FrameIndex = FreqDoubFrameRef.FrameIndex;
	const ST_FreqDoubleNetworkOutput& tempData = FreqDoubleNetwork::instance()->m_tempData;
	QString dataKey = tempData.dataKey;

	FreqDoubleNetwork::instance()->resetMatrixActiveState(FrameIndex, tempData, FreqDoubFrameRef.VecParentPt);
	FreqDoubleNetwork::instance()->mergeResonantMatrix(tempData, FreqDoubFrameRef.VecParentPt);
	//FreqDoubleNetwork::instance()->mergeResonantFFTPT(FrameIndex, tempData, FreqDoubFrameRef.VecParentPt, FreqDoubFrameRef.VecChildPt);

}

int FreqDoubleNetwork::getOpenAreaIndex(double index_double, bool LeftSide)
{
	int		floorNum	= floor(index_double);
	double	DecimalNum = index_double - floorNum;
	if (LeftSide)
	{
		if (DecimalNum < 0.5)
		{
			return floorNum;
		}
		else
		{
			return floorNum + 1;
		}
	}
	else
	{
		if (DecimalNum <= 0.5)
		{
			return floorNum;
		}
		else
		{
			return floorNum + 1;
		}
	}
}

void FreqDoubleNetwork::resetMatrixActiveState(const int FrameIndex, const ST_FreqDoubleNetworkOutput& tempData, QVector<ST_FreqMultipleNetworkParentPt>& parentVecRef)
{
	QString dataKey = tempData.dataKey;

	//const ST_STFTOutputData&			STFTDataRef		= DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();
	const ST_WndSpecConstrainResult&	EFFOscDataRef	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(dataKey).value();
	const ST_BandWidthSNRConstrainData& BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value();
	const ST_DiffNetOutput&				DiffDataRef		= DataCenterManager::instance()->getDiffOutputMap().find(dataKey).value();

	//const ST_FFTOutputData&					STFTDataFrame		= STFTDataRef.vecOutput[FrameIndex];
	const ST_WndSpecConstrainFrame&			EffOscDataFrame		= EFFOscDataRef.FrameVec[FrameIndex];
	const ST_BandWidthSNRConstrainFrame&	BDSNRDataFrame		= BDSNRDataRef.FrameVec[FrameIndex];
	const ST_DiffFrame&						DiffDataFrame		= DiffDataRef.FrameVec[FrameIndex];

	const ST_FreqMultipleTensor&	Tensor		= tempData.Tensor;
	const ST_FMTActiveCond&			ActiveCond	= tempData.ActiveCond;

	for (int MatrixIndex = 0; MatrixIndex < Tensor.VecMultipleMatrix.size(); MatrixIndex++)
	{
		const	ST_FreqMultipleMaxtrix&			MatrixRef	= Tensor.VecMultipleMatrix[MatrixIndex];
				ST_FreqMultipleNetworkParentPt& parentPtRef = parentVecRef[MatrixIndex];

		if (MatrixRef.isInsertFreq == false)
		{
			const ST_WndSpecConstrainPtTag&		EffOscPtTag		= EffOscDataFrame.VecSTFTPtState[MatrixRef.BaseFreqIndex_int];
			const ST_BandWidthSNRPtTag&			BDSNRPtTag		= BDSNRDataFrame.vecBDSNRptTag[MatrixRef.BaseFreqIndex_int];
			const ST_DiffNetPoint&				DiffPtTag		= DiffDataFrame.vecFFTPoint[MatrixRef.BaseFreqIndex_int];

			bool Active = false;
			switch (ActiveCond.MatrixActiveSource)
			{
				case EN_FMTSourceType::EffOsc:	Active = EffOscPtTag.ptConstrainState == EN_WndSepcConstrainState::EffectiveOscillation; break;
				case EN_FMTSourceType::BDSNR:	Active = BDSNRPtTag.ptSNRConstrainType == EN_BDSNRPtType::BDSNR_EffectivePt; break;
			}
			parentPtRef.isActive = Active;
			if (parentPtRef.isActive)
			{
				parentPtRef.BaseDiffGroup			= DiffPtTag.BidirectGroupIndex;
				parentPtRef.isDiffSuddenAppear	= DiffPtTag.isDisappear;
				parentPtRef.DiffRatio				= DiffPtTag.DiffRatio;
				parentPtRef.DiffVal					= DiffPtTag.Diffval;
			}
		}
		else
		{
			continue;
		}
	}

	for (int MatrixIndex = 0; MatrixIndex < Tensor.VecMultipleMatrix.size(); MatrixIndex++)
	{
		const ST_FreqMultipleMaxtrix&	MatrixRef	= Tensor.VecMultipleMatrix[MatrixIndex];
		ST_FreqMultipleNetworkParentPt& parentPtRef = parentVecRef[MatrixIndex];

		if (MatrixRef.isInsertFreq)
		{
			parentPtRef.isActive = false;

			int		LeftMatrixIndex		= MatrixIndex - 1;
			int		rightMatrixIndex	= MatrixIndex + 1;

			const ST_FreqMultipleNetworkParentPt& LeftPtRef		= parentVecRef[LeftMatrixIndex];
			const ST_FreqMultipleNetworkParentPt& RightPtRef	= parentVecRef[rightMatrixIndex];

			if (LeftPtRef.isActive == false || RightPtRef.isActive == false)
			{
				continue;
			}

			const ST_DiffNetPoint& DiffPtTag_Left	= DiffDataFrame.vecFFTPoint[floor(MatrixRef.BaseFreqIndex_double)];
			const ST_DiffNetPoint& DiffPtTag_Right	= DiffDataFrame.vecFFTPoint[ceil(MatrixRef.BaseFreqIndex_double)];

			if (DiffPtTag_Left.isDisappear || DiffPtTag_Right.isDisappear)
			{
				continue;
			}

			int  LeftDiffIndex	= DiffPtTag_Left.BidirectGroupIndex;
			int  RightDiffIndex = DiffPtTag_Right.BidirectGroupIndex;

			bool sameDiffGroup = FreqDoubleNetwork::instance()->checkSameDiffGroup(DiffPtTag_Left.DiffRatio, DiffPtTag_Right.DiffRatio, ActiveCond);

			if (!sameDiffGroup)
			{
				continue;
			}		

			const ST_WndSpecConstrainPtTag&		EffOscPtTag_Left	= EffOscDataFrame.VecSTFTPtState[floor(MatrixRef.BaseFreqIndex_double)];
			const ST_WndSpecConstrainPtTag&		EffOscPtTag_Right	= EffOscDataFrame.VecSTFTPtState[ceil(MatrixRef.BaseFreqIndex_double)];
			const ST_BandWidthSNRPtTag&			BDSNRPtTag_Left		= BDSNRDataFrame.vecBDSNRptTag[floor(MatrixRef.BaseFreqIndex_double)];
			const ST_BandWidthSNRPtTag&			BDSNRPtTag_Right	= BDSNRDataFrame.vecBDSNRptTag[ceil(MatrixRef.BaseFreqIndex_double)];

			bool Active = false;

			switch (ActiveCond.MatrixActiveSource)
			{
				case EN_FMTSourceType::EffOsc:
				{
					bool Left_Effect	= EffOscPtTag_Left.ptConstrainState		== EN_WndSepcConstrainState::EffectiveOscillation;
					bool Right_Effect	= EffOscPtTag_Right.ptConstrainState	== EN_WndSepcConstrainState::EffectiveOscillation;
					Active = Left_Effect && Right_Effect;
				}break;
				case EN_FMTSourceType::BDSNR:
				{
					bool Left_Effect	= BDSNRPtTag_Left.ptSNRConstrainType	== EN_BDSNRPtType::BDSNR_EffectivePt;
					bool Right_Effect	= BDSNRPtTag_Right.ptSNRConstrainType	== EN_BDSNRPtType::BDSNR_EffectivePt;
					Active = Left_Effect && Right_Effect;
				}break;
			}

			if (!Active)
			{
				continue;
			}

			parentPtRef.isActive				= true;
			parentPtRef.BaseDiffGroup			= DiffPtTag_Left.BidirectGroupIndex;
			parentPtRef.isDiffSuddenAppear	= DiffPtTag_Left.isDisappear;
			parentPtRef.DiffRatio				= (DiffPtTag_Left.DiffRatio + DiffPtTag_Right.DiffRatio) / 2;

			int LeftLeftindex  = LeftMatrixIndex - 1;
			if (LeftLeftindex >= 0 && LeftLeftindex < parentVecRef.size())
			{
				const ST_FreqMultipleNetworkParentPt& LeftLeftPtRef = parentVecRef[LeftLeftindex];
				if (LeftLeftPtRef.isActive == false)
				{
					parentVecRef[LeftMatrixIndex].isActive = false;
				}
			}
			else
			{
				parentVecRef[LeftMatrixIndex].isActive = false;
			}

			int RightRightIndex = rightMatrixIndex + 1;
			if (RightRightIndex >= 0 && RightRightIndex < parentVecRef.size())
			{
				const ST_FreqMultipleNetworkParentPt& RightRightPtRef = parentVecRef[RightRightIndex];
				if (RightRightPtRef.isActive == false)
				{
					parentVecRef[rightMatrixIndex].isActive = false;
				}
			}
			else
			{
				parentVecRef[rightMatrixIndex].isActive = false;
			}
		}
	}
}

void FreqDoubleNetwork::mergeResonantMatrix(const ST_FreqDoubleNetworkOutput& tempData, QVector<ST_FreqMultipleNetworkParentPt>& parentVecRef)
{
	const ST_FreqMultipleTensor&	Tensor		= tempData.Tensor;
	const ST_FMTActiveCond&			ActiveCond	= tempData.ActiveCond;

	for (int MatrixIndex = 0; MatrixIndex < Tensor.VecMultipleMatrix.size(); MatrixIndex++)
	{
		const	ST_FreqMultipleMaxtrix&				MatrixRef	= Tensor.VecMultipleMatrix[MatrixIndex];
				ST_FreqMultipleNetworkParentPt&		parentPtRef = parentVecRef[MatrixIndex];

		if (parentPtRef.isActive == false)
		{
			continue;
		}

		if (MatrixRef.vecMultiplePos.size() <= 1)
		{
			continue;
		}

		parentPtRef.ActiveMultipleFreqCount = 0;

		for (int multipleIndex = 1; multipleIndex < MatrixRef.vecMultiplePos.size(); multipleIndex++)
		{
			const ST_FreqMultiplePos& multiplePos = MatrixRef.vecMultiplePos[multipleIndex];

			if (multiplePos.startMatrixIndex == -1)
			{
				break;
			}

			for (int checkMatrixIndex = multiplePos.startMatrixIndex; checkMatrixIndex <= multiplePos.endMatrixIndex; checkMatrixIndex++)
			{
				ST_FreqMultipleNetworkParentPt& checkMatrixRef = parentVecRef[checkMatrixIndex];

				if (!checkMatrixRef.isActive)
				{
					continue;
				}

				bool stateA = (checkMatrixRef.BaseDiffGroup			== parentPtRef.BaseDiffGroup);
				bool stateB = (checkMatrixRef.isDiffSuddenAppear	&& parentPtRef.isDiffSuddenAppear);
				bool StateC = checkSameDiffGroup(parentPtRef.DiffRatio, checkMatrixRef.DiffRatio, ActiveCond);

				if (stateB || StateC)
				{
					checkMatrixRef.isActive = false;
					checkMatrixRef.HasParent = true;
					checkMatrixRef.ParentMatrixIndex = MatrixIndex;
					parentPtRef.ActiveMultipleFreqCount += 1;
				}
			}
		}
	}

}

void FreqDoubleNetwork::mergeResonantFFTPT(const int FrameIndex, const ST_FreqDoubleNetworkOutput& tempData, 
	const QVector<ST_FreqMultipleNetworkParentPt>& parentVecRef, QVector<ST_FreqMultipleNetworkChildPt>& childVecRef)
{
	QString dataKey = tempData.dataKey;

	const ST_WndSpecConstrainResult&		EFFOscDataRef	= DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(dataKey).value();
	const ST_BandWidthSNRConstrainData&		BDSNRDataRef	= DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value();
	const ST_DiffNetOutput&					DiffDataRef		= DataCenterManager::instance()->getDiffOutputMap().find(dataKey).value();

	const ST_WndSpecConstrainFrame&			EffOscDataFrame		= EFFOscDataRef.FrameVec[FrameIndex];
	const ST_BandWidthSNRConstrainFrame&	BDSNRDataFrame		= BDSNRDataRef.FrameVec[FrameIndex];
	const ST_DiffFrame&						DiffDataFrame		= DiffDataRef.FrameVec[FrameIndex];

	const ST_FreqMultipleTensor&	Tensor		= tempData.Tensor;
	const ST_FMTActiveCond&			ActiveCond	= tempData.ActiveCond;

	for (int FFTPtIndex = 0; FFTPtIndex < Tensor.resultPara.tensorStartFFTFreqIndex; FFTPtIndex++)
	{
		const ST_WndSpecConstrainPtTag&		EffOscPtTag		= EffOscDataFrame.VecSTFTPtState[FFTPtIndex];
		const ST_BandWidthSNRPtTag&			BDSNRPtTag		= BDSNRDataFrame.vecBDSNRptTag[FFTPtIndex];

		ST_FreqMultipleNetworkChildPt& childPtRef = childVecRef[FFTPtIndex];

		if (BDSNRPtTag.ptSNRConstrainType == EN_BDSNRPtType::BDSNR_EffectivePt)
		{
			childPtRef.isActiveBaseFreq = true;
		}
	}

	for (int FFTPtIndex = Tensor.resultPara.tensorStartFFTFreqIndex; FFTPtIndex <= Tensor.resultPara.tensorEndFFTFreqIndex; FFTPtIndex++)
	{
		ST_FreqMultipleNetworkChildPt	childPt = childVecRef[FFTPtIndex];
		//
	}

	for (int MatrixIndex = 0; MatrixIndex < Tensor.VecMultipleMatrix.size(); MatrixIndex++)
	{
		const	ST_FreqMultipleMaxtrix&			MatrixRef = Tensor.VecMultipleMatrix[MatrixIndex];
		const	ST_FreqMultipleNetworkParentPt& parentPtRef = parentVecRef[MatrixIndex];

		if (!parentPtRef.isActive)
		{
			continue;
		}

		if (MatrixRef.vecMultiplePos.size() <= 1)
		{
			continue;
		}

		for (int multipleIndex = 1; multipleIndex < MatrixRef.vecMultiplePos.size(); multipleIndex++)
		{
			const ST_FreqMultiplePos& multiplePos = MatrixRef.vecMultiplePos[multipleIndex];

			if (multiplePos.endFreqIndex <= Tensor.resultPara.tensorEndFFTFreqIndex)
			{
				continue;
			}

			for (int FFTPtIndex = multiplePos.startFreqIndex; FFTPtIndex <= multiplePos.endFreqIndex; FFTPtIndex++)
			{
				if (FFTPtIndex <= Tensor.resultPara.tensorEndFFTFreqIndex)
				{
					continue;
				}

				ST_FreqMultipleNetworkChildPt& childPtRef = childVecRef[FFTPtIndex];
				if (childPtRef.HasParentFreq)
				{
					continue;
				}


				const ST_WndSpecConstrainPtTag&		EffOscPtTag		= EffOscDataFrame.VecSTFTPtState[FFTPtIndex];
				const ST_BandWidthSNRPtTag&			BDSNRPtTag		= BDSNRDataFrame.vecBDSNRptTag[FFTPtIndex];
				const ST_DiffNetPoint&				DiffPtTag		= DiffDataFrame.vecFFTPoint[FFTPtIndex];

				bool PtEffect = false;

				switch (ActiveCond.MatrixSearchSource)
				{
					case EN_FMTSourceType::EffOsc	:PtEffect = EffOscPtTag.ptConstrainState	== EN_WndSepcConstrainState::EffectiveOscillation; break;
					case EN_FMTSourceType::BDSNR	:PtEffect = BDSNRPtTag.ptSNRConstrainType	== EN_BDSNRPtType::BDSNR_EffectivePt; break;
				}

				if (!PtEffect)
				{
					continue;
				}

				if (DiffPtTag.isDisappear)
				{
					continue;
				}

				bool stateA = (parentPtRef.BaseDiffGroup == DiffPtTag.BidirectGroupIndex);
				bool stateB = (parentPtRef.isDiffSuddenAppear == DiffPtTag.isSuddenAppear);

				if (stateA && stateB)
				{
					childPtRef.HasParentFreq = true;
					childPtRef.ParentMatrixIndex = MatrixIndex;
					break;
				}
			}
		}
	}

}

bool FreqDoubleNetwork::checkSameDiffGroup(const double DiffRatio_1, const double DiffRatio_2, const ST_FMTActiveCond& ActiveCond)
{
	return abs(DiffRatio_1 - DiffRatio_2) < ActiveCond.ChildDiffRatioMaxDistance;
}

void FreqDoubleNetwork::slot_FreqDoubGenProgressValueChanged(int val)
{
	if (m_tempData.FrameVec.isEmpty())
	{
		qDebug() << "AudioDiffNet::slot_FreqDoubGenProgressValueChanged m_tempMFCCData.FrameVec empty!";
		return;
	}

	int			FrameCount = m_tempData.FrameVec.size();
	double		hunderdsOfFrame = qMax(1, FrameCount / 100);
	int			processedCount = val;
	int			percentage = (double)processedCount / hunderdsOfFrame;

	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_FDN_GenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(FrameCount));;
		m_nLastReportPercantage = percentage;
	}

	qDebug() << QString("AudioDiffNet::slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(FrameCount);

	if (processedCount == FrameCount)
	{
		slot_FreqDoubGenFinished();
	}
}

void FreqDoubleNetwork::slot_FreqDoubGenFinished()
{
	DataCenterManager::instance()->slot_saveFreqDoubData(m_tempData.dataKey, m_tempData);

	m_tempData.Tensor.VecMultipleMatrix.clear();
	m_tempData.FrameVec.clear();

}