#include "LoadVideoFrameImageThread.h"
#include "../FFMpegManager.h"
#pragma execution_character_set("utf-8")


LoadVideoFrameImageThread* LoadVideoFrameImageThread::m_instance = nullptr;

LoadVideoFrameImageThread* LoadVideoFrameImageThread::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new LoadVideoFrameImageThread(nullptr);
	}
	return m_instance;
}

LoadVideoFrameImageThread::LoadVideoFrameImageThread(QObject* parent) 
	:QThread(parent)
{

	m_pFFMpegProcess = new QProcess(this);

	connect(m_pFFMpegProcess, &QProcess::readyReadStandardOutput, this, &LoadVideoFrameImageThread::slot_readyReadProcessStandardOutput);
	connect(m_pFFMpegProcess, &QProcess::readyReadStandardError, this,  &LoadVideoFrameImageThread::slot_readyReadProcessStandardError);

	connect(m_pFFMpegProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		[=](int exitCode, QProcess::ExitStatus exitStatus) {
			slot_ProcessFinished(exitCode, exitStatus);
		});

	m_pFilterWatcher = new QFutureWatcher<void>(this);
	connect(m_pFilterWatcher, SIGNAL(finished()), this, SLOT(slot_scanFinished()));
	connect(m_pFilterWatcher, &QFutureWatcher<void>::progressValueChanged, this, &LoadVideoFrameImageThread::slot_LoadImageProgressValueChanged);

}

LoadVideoFrameImageThread::~LoadVideoFrameImageThread()
{

}

void LoadVideoFrameImageThread::runWithArgument(QString ffmpegDir, const ST_VideoFileTag& loadVideoTag, const QStringList arguments, 
	QString outputFileDir, QVector<QString>& loadFileVec, const ST_VideoLoadSetting& LoadSetting)
{
	m_ffmpegDir			= ffmpegDir;	
	m_VideoFileTag		= loadVideoTag;
	m_outputFileDir		= outputFileDir;
	m_VideoLoadSetting	= LoadSetting;

	m_AllTaskVec.clear();	

	for (int currentIndex = 0; currentIndex < loadFileVec.size(); currentIndex++)
	{
		ST_LoadImageTask newTask;
		newTask.FrameIndex = currentIndex;
		newTask.frameDir = loadFileVec[currentIndex];
		newTask.loadState = false;
		newTask.loadSize = m_VideoLoadSetting.loadFrameSize;
		m_AllTaskVec.push_back(newTask);
	}

	m_arguments.clear();
	m_arguments = arguments;

	if (m_VideoLoadSetting.loadType != EN_VideoLoadType::LoadOnly)
	{
		bool initDirState = initOutputDir();
		if (!initDirState)
		{
			emit sgn_VideoLoadFinished(false);
			return;
		}
	}


	QImage nullImage;
	m_tempImageVec.clear();
	m_tempImageVec = QVector<QImage>(m_VideoLoadSetting.LoadFrameCount, nullImage);

	m_nLastReportDecodeFrameCount = -1;

	switch (m_VideoLoadSetting.loadType)
	{
		case EN_VideoLoadType::DecodeOnly:
		{
			m_pFFMpegProcess->start(m_ffmpegDir, m_arguments);
			if (!m_pFFMpegProcess->waitForStarted())
			{
				qDebug() << "LoadVideoFrameImageThread::run :process cant start!";
				emit sgn_VideoLoadFinished(false);
			}
		}break;
		case EN_VideoLoadType::LoadOnly:
		{
			m_nLastReportDecodeFrameCount = getCurrentDecodeFrameCount();
			slot_rescanImageTask();
		}break;
		case EN_VideoLoadType::DecodeAndLoad:
		{
			m_pFFMpegProcess->start(m_ffmpegDir, m_arguments);
			if (!m_pFFMpegProcess->waitForStarted())
			{
				qDebug() << "LoadVideoFrameImageThread::run :process cant start!";
				emit sgn_VideoLoadFinished(false);
			}
			slot_rescanImageTask();
		}break;
	}



	
}

void LoadVideoFrameImageThread::LoadImageFile(ST_LoadImageTask& loadTask)
{
	if (!QFile::exists(loadTask.frameDir))
	{
		qDebug() << "LoadVideoFrameImageThread::LoadImageFile unexist image : " << loadTask.frameDir;
		loadTask.loadState = false;
		return;
	}

	QImage loadImage;
	bool loadState = loadImage.load(loadTask.frameDir);

	if (!loadState)
	{
		qDebug() << "LoadVideoFrameImageThread::LoadImageFile cannot load image : " << loadTask.frameDir;
		loadTask.loadState = false;
		return;
	}

	QImage shrinKImage = loadImage.scaled(loadTask.loadSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);

	LoadVideoFrameImageThread::instance()->getTemVecRef()[loadTask.FrameIndex] = shrinKImage;

	loadTask.loadState = true;
}

bool LoadVideoFrameImageThread::initOutputDir()
{
	QDir outputFileDir(m_outputFileDir);
	if (!outputFileDir.exists())
	{
		bool mkState = outputFileDir.mkpath(m_outputFileDir);
		if (!mkState)
		{
			qDebug() << "LoadVideoFrameImageThread::initOutputDir: can 't create outputPath : " << m_outputFileDir;
			return false;
		}
	}
	else
	{
		int fileCount = outputFileDir.count();
		if (fileCount != 0)
		{
			QDir delFileDir(m_outputFileDir);
			delFileDir.setFilter(QDir::Files);
			int fileCount = delFileDir.count();
			for (int i = 0; i < fileCount; i++)
			{
				qDebug() << "LoadVideoFrameImageThread::initOutputDir removeFile : " << delFileDir[i];
				delFileDir.remove(delFileDir[i]);
			}

		}
	}
	return true;
}

void LoadVideoFrameImageThread::slot_rescanImageTask()
{
	resetScanTaskVec();
	run();
}

void LoadVideoFrameImageThread::resetScanTaskVec()
{
	m_currentScanTaskVec.clear();
	
	double FrameStrechRatio = (double)m_VideoFileTag.frameRate / (double)m_VideoLoadSetting.loadFrameRate;

	for (int taskIndex = 0; taskIndex < m_AllTaskVec.size(); taskIndex++)
	{
		int loadFrameIndex = taskIndex * FrameStrechRatio;

		if (taskIndex >= m_nLastReportDecodeFrameCount)
		{
			break;
		}

		ST_LoadImageTask& task = m_AllTaskVec[taskIndex];
		if (!task.loadState)
		{
			m_currentScanTaskVec.push_back(task);
			if (m_currentScanTaskVec.size() >= m_nMaxScanImageCount)
			{
				break;
			}
		}
	}
	
}

void LoadVideoFrameImageThread::run()
{	
	if (m_currentScanTaskVec.isEmpty())
	{
		slot_scanFinished();
		return;
	}

	QFuture<void> future = QtConcurrent::map(m_currentScanTaskVec, LoadVideoFrameImageThread::LoadImageFile);
	m_pFilterWatcher->setFuture(future);
}

void  LoadVideoFrameImageThread::getProcessState(int& finishCount, int& remainCount,int& loadDataSizeInByte)
{
	finishCount = 0;
	remainCount = 0;
	loadDataSizeInByte = 0;
	for (int taskIndex = 0; taskIndex < m_AllTaskVec.size(); taskIndex++)
	{
		ST_LoadImageTask& taskRef = m_AllTaskVec[taskIndex];
		if (taskRef.loadState)
		{
			finishCount += 1;
			int dataInByte = m_tempImageVec[taskIndex].sizeInBytes();
			loadDataSizeInByte += dataInByte;
		}
		else
		{
			remainCount += 1;
		}
	}
}

void LoadVideoFrameImageThread::slot_readyReadProcessStandardOutput()
{
	QByteArray standardData = m_pFFMpegProcess->readAllStandardOutput();
	qDebug() << "LoadVideoFrameImageThread::Standard_Output";
	
}

int  LoadVideoFrameImageThread::getCurrentDecodeFrameCount()
{
	QDir outputFileDir(m_outputFileDir);
	outputFileDir.setFilter(QDir::Files);
	int decodeFrameCount = outputFileDir.count();
	return decodeFrameCount;
}

void LoadVideoFrameImageThread::slot_readyReadProcessStandardError()
{
	QByteArray standardErrorData = m_pFFMpegProcess->readAllStandardError();
	qDebug() << "LoadVideoFrameImageThread::Standard_Error" << standardErrorData;
	m_nLastReportDecodeFrameCount = getCurrentDecodeFrameCount();
	int totalFrameCount = m_AllTaskVec.size();

	switch (m_VideoLoadSetting.loadType)
	{
		case EN_VideoLoadType::DecodeOnly:
		{
			emit sgn_VideoFrameLoadState(m_nLastReportDecodeFrameCount, 0, m_nLastReportDecodeFrameCount * 100 / totalFrameCount);
		}break;
		case EN_VideoLoadType::LoadOnly:
		{
			/**/
		}break;
		case EN_VideoLoadType::DecodeAndLoad:
		{
			if (totalFrameCount != 0)
			{
				int LoadPercentage = m_nLastReportLoadFrameCount * 100 / totalFrameCount;
				emit sgn_VideoFrameLoadState(m_nLastReportDecodeFrameCount, m_nLastReportLoadFrameCount, LoadPercentage);
			}

		}break;
	}

}

void LoadVideoFrameImageThread::slot_ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << "LoadVideoFrameImageThread::FFMpeg progress Finished";

	QDir outputFileDir(m_outputFileDir);
	outputFileDir.setFilter(QDir::Files);
	m_nLastReportDecodeFrameCount = outputFileDir.count();
	int totalFrameCount = m_VideoFileTag.FrameCount;

	switch (m_VideoLoadSetting.loadType)
	{
		case EN_VideoLoadType::DecodeOnly:
		{
			emit sgn_VideoLoadFinished(true);
		}break;
		case EN_VideoLoadType::LoadOnly:
		{
			/**/
		}break;
		case EN_VideoLoadType::DecodeAndLoad:
		{
			int LoadPercentage = m_nLastReportLoadFrameCount * 100 / totalFrameCount;
			emit sgn_VideoFrameLoadState(m_nLastReportDecodeFrameCount, m_nLastReportLoadFrameCount, LoadPercentage);
		}break;
	}
	
}

void LoadVideoFrameImageThread::slot_LoadImageProgressValueChanged(int val)
{

}

void LoadVideoFrameImageThread::slot_scanFinished()
{
	int LoadImageCount = 0;
	int remainTaskCount = 0;
	for (int TaskIndex = 0; TaskIndex < m_currentScanTaskVec.size(); TaskIndex++)
	{
		ST_LoadImageTask& processTask = m_currentScanTaskVec[TaskIndex];
		m_AllTaskVec[processTask.FrameIndex].loadState = processTask.loadState;
		if (processTask.loadState)
		{
			LoadImageCount += 1;
		}
		else
		{
			remainTaskCount += 1;
		}
	}

	int totalRemainTaskCount = 0;
	int totalTaskCount  = m_AllTaskVec.size();
	int loadDataInByte = 0;
	getProcessState(m_nLastReportLoadFrameCount, totalRemainTaskCount, loadDataInByte);


	if (totalRemainTaskCount == 0)
	{
		for (int transferImageIndex = 0; transferImageIndex < m_tempImageVec.size(); transferImageIndex++)
		{
			FFMpegManager::instance()->getVideoFrameImageRef(transferImageIndex) = m_tempImageVec[transferImageIndex];
		}
		m_AllTaskVec.clear();
		m_currentScanTaskVec.clear();
		m_tempImageVec.clear();
		emit sgn_VideoLoadFinished(true);
		return;
	}

	emit sgn_VideoFrameLoadState(m_nLastReportDecodeFrameCount, m_nLastReportLoadFrameCount, m_nLastReportLoadFrameCount * 100 / totalTaskCount);

	if (m_VideoLoadSetting.loadType == EN_VideoLoadType::DecodeAndLoad)
	{
		QTimer::singleShot(m_nRescanMsec, this, &LoadVideoFrameImageThread::slot_rescanImageTask);
	}
	else if (m_VideoLoadSetting.loadType == EN_VideoLoadType::LoadOnly)
	{
		slot_rescanImageTask();
	}
	

}