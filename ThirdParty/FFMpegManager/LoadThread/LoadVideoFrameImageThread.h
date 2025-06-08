#pragma once
#include <QThread>
#include <QProcess>
#include <QtConcurrent>
#include <QThreadPool>
#include "../../../Vision/protocol/protocol_vision.h"


class LoadVideoFrameImageThread : public QThread
{
	Q_OBJECT
protected:
	LoadVideoFrameImageThread(QObject* parent);
	~LoadVideoFrameImageThread();

	static LoadVideoFrameImageThread* m_instance;

	struct ST_LoadImageTask
	{
		int FrameIndex = -1;
		QString frameDir;
		bool loadState = false;
		QSize loadSize = QSize(0, 0);
	};

public:
	static LoadVideoFrameImageThread* instance();

	void runWithArgument(QString ffmpegDir,const ST_VideoFileTag& loadVideoTag, const QStringList arguments,QString outputFileDir,QVector<QString>& loadFileList, const ST_VideoLoadSetting& LoadSetting);

	static void LoadImageFile(ST_LoadImageTask& loadTask);

	QVector<QImage>& getTemVecRef() {return m_tempImageVec;};

public:signals:
	void sgn_VideoFrameLoadState(int extractFrameCount, int loadFrameCount, int precentage);
	void sgn_VideoLoadFinished(bool loadState);

protected:
	bool initOutputDir();
	void run() override;

	void resetScanTaskVec();
	void getProcessState(int& finishCount,int& remainCount, int& loadDataSizeInByte);
	int  getCurrentDecodeFrameCount();
	

protected slots:
	void slot_rescanImageTask();
	void slot_readyReadProcessStandardOutput();
	void slot_readyReadProcessStandardError();

	void slot_ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void slot_LoadImageProgressValueChanged(int val);
	void slot_scanFinished();


private:
	QString			m_ffmpegDir;
	ST_VideoFileTag m_VideoFileTag;
	ST_VideoLoadSetting m_VideoLoadSetting;

	QStringList		m_arguments;
	QString         m_outputFileDir;

	QProcess*		m_pFFMpegProcess = nullptr;

	QVector<ST_LoadImageTask> m_AllTaskVec;
	QVector<ST_LoadImageTask> m_currentScanTaskVec;


	QFutureWatcher<void>* m_pFilterWatcher = nullptr;

	QVector<QImage> m_tempImageVec;
	int m_nLastReportPercantage = -1;
	int m_nLastReportLoadFrameCount = -1;
	int m_nLastReportDecodeFrameCount = -1;

	int m_nRescanMsec		= 50;
	int m_nMaxScanImageCount	= 100;
	int m_nMaxLoadDataInGigaByte = 50;

};

