#include "LoadVideoFrameTagThread.h"
#include "../FFMpegManager.h"

LoadVideoFrameTagThread::LoadVideoFrameTagThread(QObject* parent)
	:QThread(parent)
{
	m_pFFProbeProcess = new QProcess(this);
	
	connect(m_pFFProbeProcess, &QProcess::readyReadStandardOutput, this, &LoadVideoFrameTagThread::slot_readyReadProcessStandardOutput);
	connect(m_pFFProbeProcess, &QProcess::readyReadStandardError, this, &LoadVideoFrameTagThread::slot_readyReadProcessStandardError);

	connect(m_pFFProbeProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		[=](int exitCode, QProcess::ExitStatus exitStatus) {
			slot_ProcessFinished(exitCode, exitStatus);
		});
}

void LoadVideoFrameTagThread::runWithArgument(QString ffProbeDir, const ST_VideoLoadSetting& LoadSetting, QStringList arguments)
{
	m_arguments.clear();
	m_arguments = arguments;
	m_tempDataArray.clear();
	m_FFProbePath = ffProbeDir;
	m_tempFrameTagVec.clear();
	m_LoadSetting = LoadSetting;
	run();
}

void LoadVideoFrameTagThread::run()
{
	ST_VideoFileTag fileTag =  FFMpegManager::instance()->getTmepVideoFileTag();
	ST_VideoH264FrameTag nullTag;
	m_tempFrameTagVec = QVector<ST_VideoH264FrameTag>(fileTag.FrameCount, nullTag);
	m_pFFProbeProcess->start(m_FFProbePath, m_arguments);
	if (!m_pFFProbeProcess->waitForStarted())
	{
		qDebug() << "LoadVideoFrameTagThread::run :process cant start!";
		emit sgn_loadTagFinished(false);
	}
}

void LoadVideoFrameTagThread::slot_readyReadProcessStandardOutput()
{
	QByteArray standardData = m_pFFProbeProcess->readAllStandardOutput();
	int getSize = standardData.size();
	m_tempDataArray.append(standardData);
	QString printStr = QString(" %1 -> %2").arg(getSize).arg(m_tempDataArray.size());

	emit sgn_loadTagState(0, printStr);

	qDebug() << QString("LoadVideoFrameTagThread::slot_readyReadProcessStandardOutput : readyReadStandardOutput getDataSize : %1 totalDataSize %2")
		.arg(standardData.size()).arg(m_tempDataArray.size());
}

void LoadVideoFrameTagThread::slot_readyReadProcessStandardError()
{
	QByteArray standardErrorData = m_pFFProbeProcess->readAllStandardOutput();

	qDebug() << "LoadVideoFrameTagThread::slot_readyReadProcessStandardError " << standardErrorData;

}

void LoadVideoFrameTagThread::slot_ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	QJsonDocument	resultJsonDoc = QJsonDocument::fromJson(m_tempDataArray);
	QJsonObject		decodeDataObj(resultJsonDoc.object());
	QJsonArray	    frameArray = decodeDataObj["frames"].toArray();
	int frameCount = frameArray.size();

	//QVector<ST_VideoH264Frame>& frameVecRef = FFMpegManager::instance()->getTempVideoDataVecRef();

	int hundredsOfFrame = frameCount / 100;

	int IFrameCount = 0;
	int PFrameCount = 0;
	int BFrameCount = 0;

	for (int frameIndex = 0; frameIndex < frameArray.size(); frameIndex++)
	{
		QJsonObject streamObject = frameArray[frameIndex].toObject();
		QString streamTypeStr = streamObject["media_type"].toString();

		if (streamTypeStr != QString("video"))
		{
			qDebug() << "LoadVideoFrameTagThread::slot_ProcessFinished : stream0 frame not video!";
			emit sgn_loadTagFinished(false);
			break;
		}

		ST_VideoH264FrameTag frameTag;
		frameTag.FrameIndex = frameIndex;

		FFProbedStreamJsonObjToFrameTag(streamObject, frameTag);

		switch (frameTag.frameType)
		{
			case EN_VideoH264FrameType::I :IFrameCount += 1; break;
			case EN_VideoH264FrameType::P :PFrameCount += 1; break;
			case EN_VideoH264FrameType::B :BFrameCount += 1; break;
		}

		//ST_VideoH264FrameTag& FrameTag = FFMpegManager::instance()->getVideoFrameTagRef(frameIndex);

		m_tempFrameTagVec[frameIndex] = frameTag;

		if (frameIndex % hundredsOfFrame == 0)
		{
			emit sgn_loadTagState(frameIndex / hundredsOfFrame,QString("%1 / %2").arg(frameIndex).arg(frameCount));
		}

	}

	QVector<ST_VideoH264Frame>& FrameVecRef = FFMpegManager::instance()->getTempVideoDataVecRef();
	ST_VideoFileTag& VideoFileTagRef = FFMpegManager::instance()->getTmepVideoFileTag();
	ST_VideoLoadSetting & VideoLoadTagRef = FFMpegManager::instance()->getTmepVideoLoadSetting();
	double FrameStrechRatio = (double)VideoFileTagRef.frameRate / (double)m_LoadSetting.loadFrameRate;

	int totalTransferFrameCount = FrameVecRef.size();
	int hundredsOfTransferFrame = totalTransferFrameCount / 100;

	int LoadFrameCount_I = 0;
	int LoadFrameCount_P = 0;
	int LoadFrameCount_B = 0;

	for (int frameIndex = 0; frameIndex < totalTransferFrameCount; frameIndex++)
	{
		int loadFrameIndex = frameIndex * FrameStrechRatio;
		if (loadFrameIndex < 0 || loadFrameIndex >= m_tempFrameTagVec.size())
		{
			continue;
		}
		ST_VideoH264FrameTag& FrameTag = FFMpegManager::instance()->getVideoFrameTagRef(frameIndex);
		FrameTag = m_tempFrameTagVec[loadFrameIndex];

		switch (FrameTag.frameType)
		{
			case EN_VideoH264FrameType::I:LoadFrameCount_I += 1; break;
			case EN_VideoH264FrameType::P:LoadFrameCount_P += 1; break;
			case EN_VideoH264FrameType::B:LoadFrameCount_B += 1; break;
		}

		if (frameIndex % hundredsOfTransferFrame == 0)
		{
			emit sgn_loadTagState(frameIndex / hundredsOfTransferFrame, QString("%1 / %2").arg(frameIndex).arg(hundredsOfTransferFrame));
		}
	}
	m_tempFrameTagVec.clear();
	
	VideoFileTagRef.IFrameCount = IFrameCount;
	VideoFileTagRef.PFrameCount = PFrameCount;
	VideoFileTagRef.BFrameCount = BFrameCount;

	VideoLoadTagRef.LoadFrameCount_I = LoadFrameCount_I;
	VideoLoadTagRef.LoadFrameCount_P = LoadFrameCount_P;
	VideoLoadTagRef.LoadFrameCount_B = LoadFrameCount_B;

	emit sgn_loadTagFinished(true);

}

void LoadVideoFrameTagThread::FFProbedStreamJsonObjToFrameTag(QJsonObject& decodeDataObj, ST_VideoH264FrameTag& frameTag)
{
	QString frameTypeStr = decodeDataObj["pict_type"].toString();
	if (frameTypeStr == "I")
	{
		frameTag.frameType = EN_VideoH264FrameType::I;
	}
	else if (frameTypeStr == "P")
	{
		frameTag.frameType = EN_VideoH264FrameType::P;
	}
	else if (frameTypeStr == "B")
	{
		frameTag.frameType = EN_VideoH264FrameType::B;
	}
	else
	{
		qDebug() << "FFMpegManager::FFProbedStreamJsonObjToFrameTag undefined FrameType : " << frameTypeStr;
		return;
	}


	frameTag.width = decodeDataObj["width"].toInt();
	frameTag.height = decodeDataObj["height"].toInt();

	frameTag.FrameTime_Base = decodeDataObj["pts"].toInt();
	frameTag.FrameTime_sec = decodeDataObj["pts_time"].toString().toDouble();
	frameTag.duration_base = decodeDataObj["duration"].toInt();
	frameTag.duration_sec = decodeDataObj["duration_time"].toString().toDouble();
}