#include "DataCenterManager.h"
#pragma execution_character_set("utf-8")
#include "../../Perception/ImageProcessor/ImageProcessor.h"

DataCenterManager* DataCenterManager::m_instance = nullptr;

DataCenterManager* DataCenterManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new DataCenterManager();
	}
	return m_instance;
}

DataCenterManager::DataCenterManager() :QObject(nullptr)
{

}

bool DataCenterManager::checkDataExist(EN_DataCenterAudioDataType dataType, QString Key)
{
	switch (dataType)
	{
	case EN_DataCenterAudioDataType::AudioModuleSignal:
	{
		auto MapPos = m_map_GenSig.find(Key);
		if (MapPos != m_map_GenSig.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::WavDoubleData:
	{
		auto MapPos = m_map_WavSig.find(Key);
		if (MapPos != m_map_WavSig.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::STFTOutputData:
	{
		auto MapPos = m_map_STFTOutput.find(Key);
		if (MapPos != m_map_STFTOutput.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::WndSpecConstrain:
	{
		auto MapPos = m_mapWndSpecConstrain.find(Key);
		if (MapPos != m_mapWndSpecConstrain.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::BDSNR:
	{
		auto MapPos = m_mapBDSNR.find(Key);
		if (MapPos != m_mapBDSNR.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::VibState:
	{
		auto MapPos = m_mapVibState.find(Key);
		if (MapPos != m_mapVibState.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::Diff:
	{
		auto MapPos = m_mapDiff.find(Key);
		if (MapPos != m_mapDiff.end())
		{
			return true;
		}
	}break;
	case EN_DataCenterAudioDataType::FreqDoub:
	{
		auto MapPos = m_mapFreqDoub.find(Key);
		if (MapPos != m_mapFreqDoub.end())
		{
			return true;
		}
	}break;

	}
	return false;
}

int DataCenterManager::getDaraFrameCount(EN_DataCenterAudioDataType dataType, QString Key)
{
	bool dataExist = checkDataExist(dataType, Key);
	if (!dataExist)
	{
		return -1;
	}

	switch (dataType)
	{
		case EN_DataCenterAudioDataType::AudioModuleSignal:
		{
			const ST_AudioModuleSignal& data = m_map_GenSig.find(Key).value();
			return data.vecModuleResultSignal.size();
		}break;
		case EN_DataCenterAudioDataType::WavDoubleData:
		{
			const ST_WavDoubleData& data = m_map_WavSig.find(Key).value();
			return data.LeftChannel.size();
		}break;
		case EN_DataCenterAudioDataType::STFTOutputData:
		{
			const ST_STFTOutputData& data = m_map_STFTOutput.find(Key).value();
			return data.vecOutput.size();
		}break;
		case EN_DataCenterAudioDataType::WndSpecConstrain:
		{
			const ST_WndSpecConstrainResult& data = m_mapWndSpecConstrain.find(Key).value();
			return data.FrameVec.size();
		}break;
		case EN_DataCenterAudioDataType::BDSNR:
		{
			const ST_BandWidthSNRConstrainData& data = m_mapBDSNR.find(Key).value();
			return data.FrameVec.size();
		}break;
		case EN_DataCenterAudioDataType::VibState:
		{
			const ST_VibrateStateNetworkNetworkData& data = m_mapVibState.find(Key).value();
			return data.FrameVec.size();
		}break;
		case EN_DataCenterAudioDataType::Diff:
		{
			const ST_DiffNetOutput& data = m_mapDiff.find(Key).value();
			return data.FrameVec.size();
		}break;
		case EN_DataCenterAudioDataType::FreqDoub:
		{
			const ST_FreqDoubleNetworkOutput& data = m_mapFreqDoub.find(Key).value();
			return data.FrameVec.size();
		}break;

	}

	return -1;

}

void DataCenterManager::slot_saveGenerateSignal(ST_AudioModuleSignal& data, bool& saveState)
{
	if (data.vecModuleResultSignal.isEmpty())
	{
		saveState = false;
		return;
	}

	QString SigName = QString("%1ms Base:%2hz mod:%3hz")
		.arg(data.basePara.signalTimeLength * 1000)
		.arg(data.basePara.baseFrequency)
		.arg(data.modulePara.moduleFrequency);

	auto pos = m_map_GenSig.find(SigName);
	if (pos != m_map_GenSig.end())
	{
		saveState = false;
		return;
	}

	m_map_GenSig.insert(SigName, data);
	saveState = true;

}
void DataCenterManager::slot_saveWavData(ST_WavDoubleData& data, bool& saveState)
{
	if (data.LeftChannel.isEmpty())
	{
		saveState = false;
		return;
	}

	double startMsec	= data.LeftChannel[0].pTime * 1000;
	double endMsec		= data.LeftChannel.rbegin()->pTime * 1000;

	QTime startTime = QTime(0, 0, 0).addMSecs(startMsec);
	QTime endTime	= QTime(0, 0, 0).addMSecs(endMsec);

	/*
	QString SigName = QString("file : %1, %2 - %3")
		.arg(data.fileTag.fileName)
		.arg(startTime.toString("mm:ss"))
		.arg(endTime.toString("mm:ss"));
	*/

	QString SigName = QString("file[%1]").arg(data.fileTag.fileName);

	m_map_WavSig.insert(SigName, data);
	saveState = true;
	emit sgn_WavDoubleDataSaved(SigName);
}

QString  DataCenterManager::slot_saveSTFTData(ST_STFTOutputData& STFTOutputData, bool& saveState)
{
	QString DataCenterName;
	if (STFTOutputData.vecOutput.isEmpty())
	{
		saveState = false;
		return DataCenterName;
	}

	double startMsec	= STFTOutputData.vecOutput[0].para.startTime * 1000;
	double endMsec		= STFTOutputData.vecOutput.rbegin()->para.startTime * 1000;

	QTime startTime		= QTime(0, 0, 0).addMSecs(startMsec);
	QTime endTime		= QTime(0, 0, 0).addMSecs(endMsec);


	//DataCenterName = QString("STFT file : %1, %2 - %3")
	//	.arg(STFTOutputData.InputPara.fileName)
	//	.arg(startTime.toString("mm:ss"))
	//	.arg(endTime.toString("mm:ss"));

	DataCenterName = QString(" %1, %2 - %3")
	.arg(STFTOutputData.InputPara.fileName)
	.arg(startTime.toString("mm:ss"))
	.arg(endTime.toString("mm:ss"));

	ST_STFTOutputData nullData;
	m_map_STFTOutput.insert(DataCenterName, nullData);

	ST_STFTOutputData& dataInMap = m_map_STFTOutput.find(DataCenterName).value();
	AudioProtocol::duplicateSTFTData(STFTOutputData, dataInMap);
	dataInMap.DatacenterName = DataCenterName;
	saveState = true;

	emit sgn_STFTDataSaved(DataCenterName);

	return DataCenterName;
}

void DataCenterManager::slot_saveWndSpecConstrainData(QString key, ST_WndSpecConstrainResult& tempData)
{
	if (tempData.FrameVec.empty())
	{
		qDebug() << "DataCenterManager::slot_saveWndSpecConstrainData nullData : " << key;
		return;
	}

	auto pos = m_mapWndSpecConstrain.find(key);
	if (pos != m_mapWndSpecConstrain.end())
	{
		qDebug() << "DataCenterManager::slot_saveWndSpecConstrainData Cover exist Data : " << key;
		m_mapWndSpecConstrain.erase(pos);
	}
	ST_WndSpecConstrainResult nullData;
	m_mapWndSpecConstrain.insert(key, nullData);
	auto dupPos = m_mapWndSpecConstrain.find(key);
	ST_WndSpecConstrainResult& MapDataRef = dupPos.value();

	MapDataRef.dataKey = tempData.dataKey;
	MapDataRef.WndConstrainPara = tempData.WndConstrainPara;

	int frameCount = tempData.FrameVec.size();
	int STFTPtCount = tempData.FrameVec[0].VecSTFTPtState.size();

	ST_WndSpecConstrainFrame nullFrame;
	ST_WndSpecConstrainPtTag nullWndSpecConstrainPt;

	nullFrame.VecSTFTPtState.clear();
	nullFrame.VecSTFTPtState = QVector<ST_WndSpecConstrainPtTag>(STFTPtCount, nullWndSpecConstrainPt);
	MapDataRef.FrameVec = QVector<ST_WndSpecConstrainFrame>(frameCount, nullFrame);

	for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
	{
		const ST_WndSpecConstrainFrame& dataFrame = tempData.FrameVec[frameIndex];
		ST_WndSpecConstrainFrame& dupFrame	= MapDataRef.FrameVec[frameIndex];

		for (int STFTPtIndex = 0; STFTPtIndex < STFTPtCount; STFTPtIndex++)
		{
			dupFrame.VecSTFTPtState[STFTPtIndex] = dataFrame.VecSTFTPtState[STFTPtIndex];
		}
	}

	emit sgn_WndConstrainDataSaved(key);

}

void DataCenterManager::slot_saveBDSNRData(QString key, ST_BandWidthSNRConstrainData& tempData)
{
	if (tempData.FrameVec.empty())
	{
		qDebug() << "DataCenterManager::ST_BandWidthSNRConstrainData nullData : " << key;
		return;
	}

	auto pos = m_mapBDSNR.find(key);
	if (pos != m_mapBDSNR.end())
	{
		qDebug() << "DataCenterManager::ST_BandWidthSNRConstrainData Cover exist Data : " << key;
		m_mapBDSNR.erase(pos);
	}

	ST_BandWidthSNRConstrainData nullData;
	m_mapBDSNR.insert(key, nullData);
	auto dupPos = m_mapBDSNR.find(key);
	ST_BandWidthSNRConstrainData& MapDataRef = dupPos.value();

	MapDataRef.DataKey		= tempData.DataKey;
	MapDataRef.WorkPara	= tempData.WorkPara;
	MapDataRef.FilterData	= tempData.FilterData;

	int frameCount		= tempData.FrameVec.size();
	int FilterCount		= tempData.FrameVec[0].vecBDFilterValue.size();
	int STFTPtCount		= tempData.FrameVec[0].vecBDSNRptTag.size();

	ST_BandWidthFilterPt nullFilterPt;
	ST_BandWidthSNRPtTag nullSNRPtTag;
	ST_BandWidthSNRConstrainFrame nullFilterCFrame;
	nullFilterCFrame.vecBDFilterValue.clear();
	nullFilterCFrame.vecBDSNRptTag.clear();
	nullFilterCFrame.vecBDFilterValue = QVector<ST_BandWidthFilterPt>(FilterCount, nullFilterPt);
	nullFilterCFrame.vecBDSNRptTag = QVector<ST_BandWidthSNRPtTag>(STFTPtCount, nullSNRPtTag);

	MapDataRef.FrameVec.clear();
	MapDataRef.FrameVec = QVector<ST_BandWidthSNRConstrainFrame>(frameCount, nullFilterCFrame);

	for (int FrameIndex = 0; FrameIndex < frameCount; FrameIndex++)
	{
		const	ST_BandWidthSNRConstrainFrame& sourceFrame = tempData.FrameVec[FrameIndex];
				ST_BandWidthSNRConstrainFrame& targetFrame = MapDataRef.FrameVec[FrameIndex];
	
		targetFrame.FrameInSTFTIndex	= sourceFrame.FrameInSTFTIndex;
		targetFrame.FrameStartTime		= sourceFrame.FrameStartTime;

		for (int FilterPtIndex = 0; FilterPtIndex < FilterCount; FilterPtIndex++)
		{
			targetFrame.vecBDFilterValue[FilterPtIndex] = sourceFrame.vecBDFilterValue[FilterPtIndex];
		}

		for (int BDSNRPtIndex = 0; BDSNRPtIndex < STFTPtCount; BDSNRPtIndex++)
		{
			targetFrame.vecBDSNRptTag[BDSNRPtIndex] = sourceFrame.vecBDSNRptTag[BDSNRPtIndex];
		}

	}

	emit sgn_BDSNRDataSaved(key);
}

void DataCenterManager::slot_saveVibStateData(QString key, ST_VibrateStateNetworkNetworkData& tempData)
{
	if (tempData.FrameVec.empty())
	{
		qDebug() << "DataCenterManager::slot_saveVibStateRelData nullData : " << key;
		return;
	}

	auto pos = m_mapVibState.find(key);
	if (pos != m_mapVibState.end())
	{
		qDebug() << "DataCenterManager::slot_saveVibStateRelData Cover exist Data : " << key;
		m_mapVibState.erase(pos);
	}

	ST_VibrateStateNetworkNetworkData nullData;
	m_mapVibState.insert(key, nullData);
	auto dupPos = m_mapVibState.find(key);
	ST_VibrateStateNetworkNetworkData& MapDataRef = dupPos.value();

	MapDataRef.dataKey = tempData.dataKey;
	MapDataRef.ThreshHold = tempData.ThreshHold;

	int frameCount = tempData.FrameVec.size();
	int VibPtCount = tempData.FrameVec[0].VecVibratePt.size();

	ST_VibrateStatePt nullVibPtTag;
	ST_VibrateStateNetworkFrame nullVibStateFrame;
	nullVibStateFrame.VecVibratePt.clear();
	nullVibStateFrame.VecVibratePt = QVector<ST_VibrateStatePt>(VibPtCount, nullVibPtTag);

	MapDataRef.FrameVec.clear();
	MapDataRef.FrameVec = QVector<ST_VibrateStateNetworkFrame>(frameCount, nullVibStateFrame);

	for (int FrameIndex = 0; FrameIndex < frameCount; FrameIndex++)
	{
		const	ST_VibrateStateNetworkFrame& sourceFrame = tempData.FrameVec[FrameIndex];
		ST_VibrateStateNetworkFrame& targetFrame = MapDataRef.FrameVec[FrameIndex];

		targetFrame.FrameIndex = sourceFrame.FrameIndex;

		for (int VibPtIndex = 0; VibPtIndex < VibPtCount; VibPtIndex++)
		{
			targetFrame.VecVibratePt[VibPtIndex] = sourceFrame.VecVibratePt[VibPtIndex];
		}
	}

	emit sgn_VibStateRelDataSaved(key);
}

void DataCenterManager::slot_saveDiffData(QString key, ST_DiffNetOutput& tempData)
{
	if (tempData.FrameVec.empty())
	{
		qDebug() << "DataCenterManager::slot_saveDiffData nullData : " << key;
		return;
	}

	auto pos = m_mapDiff.find(key);
	if (pos != m_mapDiff.end())
	{
		qDebug() << "DataCenterManager::slot_saveDiffData Cover exist Data : " << key;
		m_mapDiff.erase(pos);
	}

	ST_DiffNetOutput nullData;
	m_mapDiff.insert(key, nullData);
	auto dupPos = m_mapDiff.find(key);
	ST_DiffNetOutput& MapDataRef = dupPos.value();

	MapDataRef.DataKey			= tempData.DataKey;
	MapDataRef.inputPara		= tempData.inputPara;
	MapDataRef.DiffNetState		= tempData.DiffNetState;

	int frameCount = tempData.FrameVec.size();
	int STFTPtCount = tempData.FrameVec[0].vecFFTPoint.size();
	int FilterCount = tempData.FrameVec[0].vecBandWidthFilterPoint.size();

	ST_DiffNetPoint nullDiffPt;
	ST_DiffFrame nullDiffFrame;
	nullDiffFrame.vecFFTPoint.clear();
	nullDiffFrame.vecBandWidthFilterPoint.clear();
	nullDiffFrame.vecFFTPoint				= QVector<ST_DiffNetPoint>(STFTPtCount, nullDiffPt);
	nullDiffFrame.vecBandWidthFilterPoint	= QVector<ST_DiffNetPoint>(FilterCount, nullDiffPt);

	MapDataRef.FrameVec.clear();
	MapDataRef.FrameVec = QVector<ST_DiffFrame>(frameCount, nullDiffFrame);

	for (int FrameIndex = 0; FrameIndex < frameCount; FrameIndex++)
	{
		const	ST_DiffFrame&	sourceFrame = tempData.FrameVec[FrameIndex];
		ST_DiffFrame&			targetFrame = MapDataRef.FrameVec[FrameIndex];

		targetFrame.FrameInSTFTIndex = sourceFrame.FrameInSTFTIndex;
		targetFrame.FrameStartTime = sourceFrame.FrameStartTime;

		for (int FilterPtIndex = 0; FilterPtIndex < FilterCount; FilterPtIndex++)
		{
			targetFrame.vecBandWidthFilterPoint[FilterPtIndex] = sourceFrame.vecBandWidthFilterPoint[FilterPtIndex];
		}

		for (int BDSNRPtIndex = 0; BDSNRPtIndex < STFTPtCount; BDSNRPtIndex++)
		{
			targetFrame.vecFFTPoint[BDSNRPtIndex] = sourceFrame.vecFFTPoint[BDSNRPtIndex];
		}

	}

	emit sgn_DiffDataSaved(key);
}

void DataCenterManager::slot_saveFreqDoubData(QString key, ST_FreqDoubleNetworkOutput& tempData)
{
	if (tempData.FrameVec.empty())
	{
		qDebug() << "DataCenterManager::slot_saveFreqDoubData nullData : " << key;
		return;
	}

	auto pos = m_mapFreqDoub.find(key);
	if (pos != m_mapFreqDoub.end())
	{
		qDebug() << "DataCenterManager::slot_saveFreqDoubData Cover exist Data : " << key;
		m_mapFreqDoub.erase(pos);
	}

	ST_FreqDoubleNetworkOutput nullData;
	m_mapFreqDoub.insert(key, nullData);
	auto dupPos = m_mapFreqDoub.find(key);
	ST_FreqDoubleNetworkOutput& MapDataRef = dupPos.value();

	MapDataRef.dataKey		= tempData.dataKey;
	MapDataRef.Tensor		= tempData.Tensor;
	MapDataRef.ActiveCond	= tempData.ActiveCond;

	int frameCount = tempData.FrameVec.size();
	int ParentPtCount = tempData.FrameVec[0].VecParentPt.size();
	int ChildPtCount = tempData.FrameVec[0].VecChildPt.size();

	ST_FreqDoubleNetworkFrame		nullFrame;
	ST_FreqMultipleNetworkParentPt	nullParentPt;
	ST_FreqMultipleNetworkChildPt	nullChildPt;
	
	nullFrame.VecParentPt.clear();
	nullFrame.VecChildPt.clear();
	
	nullFrame.VecParentPt	= QVector<ST_FreqMultipleNetworkParentPt>(ParentPtCount, nullParentPt);
	nullFrame.VecChildPt	= QVector<ST_FreqMultipleNetworkChildPt>(ChildPtCount, nullChildPt);

	MapDataRef.FrameVec.clear();
	MapDataRef.FrameVec = QVector<ST_FreqDoubleNetworkFrame>(frameCount, nullFrame);

	for (int FrameIndex = 0; FrameIndex < frameCount; FrameIndex++)
	{
		const	ST_FreqDoubleNetworkFrame& sourceFrame = tempData.FrameVec[FrameIndex];
		ST_FreqDoubleNetworkFrame& targetFrame = MapDataRef.FrameVec[FrameIndex];

		targetFrame.FrameIndex						= sourceFrame.FrameIndex;
		targetFrame.ActiveMatrixCount				= sourceFrame.ActiveMatrixCount;
		targetFrame.MaxActiveMatrixIndex			= sourceFrame.MaxActiveMatrixIndex;
		targetFrame.MaxActiveMatrixMultipleTime		= sourceFrame.MaxActiveMatrixMultipleTime;

		for (int ParentPtIndex = 0; ParentPtIndex < ParentPtCount; ParentPtIndex++)
		{
			targetFrame.VecParentPt[ParentPtIndex] = sourceFrame.VecParentPt[ParentPtIndex];
		}

		for (int ChildPtIndex = 0; ChildPtIndex < ChildPtCount; ChildPtIndex++)
		{
			targetFrame.VecChildPt[ChildPtIndex] = sourceFrame.VecChildPt[ChildPtIndex];
		}
	}

	emit sgn_FreqDoubDataSaved(key);
}

bool DataCenterManager::checkImageExist(EN_DataCenterVisualDataType dataType, QString Key)
{
	switch (dataType)
	{
		case EN_DataCenterVisualDataType::QImage:
		{
			auto MapPos = m_map_QImage.find(Key);
			if (MapPos != m_map_QImage.end())
			{
				return true;
			}			
		}break;
		case EN_DataCenterVisualDataType::VisualImg:
		{
			auto MapPos = m_map_VisualImage.find(Key);
			if (MapPos != m_map_VisualImage.end())
			{
				return true;
			}
		}break;
	}
	return false;
}

void DataCenterManager::slot_saveQImg(QString Key, QImage& data, bool& saveState)
{
	saveState = false;
	if (data.isNull())
	{
		qDebug() << "DataCenterManager::slot_saveQImg nullData : " << Key;
		return;
	}

	auto pos = m_map_QImage.find(Key);
	if (pos != m_map_QImage.end())
	{
		qDebug() << "DataCenterManager::slot_saveQImg Cover exist Data : " << Key;
		m_map_QImage.erase(pos);
	}

	QImage nullData;
	m_map_QImage.insert(Key, nullData);
	auto dupPos = m_map_QImage.find(Key);
	QImage& MapDataRef = dupPos.value();
	MapDataRef = data;
	saveState = true;
	emit sgn_QImgDataSaved(Key);
}

void DataCenterManager::slot_saveVisualImg(ST_VisualImage& data, bool& saveState)
{
	saveState = false;
	if (data.pixelVec.empty())
	{
		qDebug() << "DataCenterManager::slot_saveVisualImg nullData : " << data.fileName;
		return;
	}

	QString Key = data.fileName;

	auto pos = m_map_VisualImage.find(Key);
	if (pos != m_map_VisualImage.end())
	{
		qDebug() << "DataCenterManager::slot_saveVisualImg Cover exist Data : " << Key;
		m_map_VisualImage.erase(pos);
	}

	ST_VisualImage nullData;
	m_map_VisualImage.insert(Key, nullData);
	auto dupPos = m_map_VisualImage.find(Key);
	ST_VisualImage& MapDataRef = dupPos.value();

	ImageProcessor::duplicateVisualImage(data, MapDataRef);
	saveState = true;
	emit sgn_VisualImgDataSaved(Key);

}