#pragma once
#include <QObject>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qDebug>
#include <QDir>

#include "../../Audio/protocol/protocol_audio.h"
#include "../../Vision/protocol/protocol_vision.h"
#include "./LoadThread/LoadVideoFrameTagThread.h"
#include "./LoadThread/ExtractAudioThread.h"
#include "./LoadThread/LoadVideoFrameImageThread.h"

class FFMpegManager : public QObject
{
	Q_OBJECT
public:
	static FFMpegManager* instance();

protected:
	FFMpegManager();
	static FFMpegManager* m_instance;

private:
	QString  m_strFFMpegPath;
	QString  m_strFFProbePath;

public:
	bool checkFFMpegState();
	bool checkFFProbeState();

	//使用ffprobe读取文件格式+标签
	const ST_AudioFileTag getNormalAudioFileTag(QString filePath,bool& processState);

	bool  transferIntoWavFormat(const ST_AudioFileTag& targetFileTag, QString targetDir, QString& resultFile);

	EN_AudioFileType getAudioFileType(QString fileDir);
	void saveHelpFile();

protected:
	void FFProbedStreamJsonObjToAudioTag(QJsonObject& decodeDataObj,QJsonObject& streamObject, ST_AudioFileTag& resultTag);
	

public:signals:
	void sgn_loadVideoTagState(int precentage, QString errstr);
	void sgn_loadVideoTagFinished(bool loadState);
	void sgn_ExtractAudioState(bool state, QString errStr);
	void sgn_ExtractAudioFinished(ST_WavDoubleData& ExtractData);
	void sgn_VideoFrameLoadState(int extractFrameCount, int loadFrameCount, int precentage);
	void sgn_VideoLoadFinished(bool loadState);

public:
	EN_VideoFileType getVedioFileType(QString fileDir);

	bool getVedioFileTag(QString VedioFilePath, ST_VideoFileTag& VedioFileTag, ST_AudioFileTag& audioFileTag);
	bool extractVedioAudioToWavFile(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag, QString& resultWavFile);
	bool checkDecodeFileExist(const ST_VideoFileTag& VedioFileTag);

	void startDecodeVideoFile(const ST_VideoFileTag& VideoFileTag, const ST_VideoLoadSetting& LoadSetting);
	void startExtractAndLoadWavFileFromVideo(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag);

	ST_VideoFileTag&				getTmepVideoFileTag()		{ return m_currentLoadTempData.VisionData.FileTag; };
	ST_VideoLoadSetting&			getTmepVideoLoadSetting()	{ return m_currentLoadTempData.VisionData.LoadSetting; };
	
	ST_VideoH264FrameTag&			getVideoFrameTagRef(int index);
	QImage&							getVideoFrameImageRef(int index);;
	QVector<ST_VideoH264Frame>&		getTempVideoDataVecRef() { return m_currentLoadTempData.VisionData.FrameVec; };

protected:
	void FFProbedStreamJsonObjToVedioTag(QJsonObject& streamObject, ST_VideoFileTag& resultTag);
	

	QString VedioFileTagToFileName(const ST_VideoFileTag& VedioFileTag);
	QString VedioFileTagToDecodeDir(const ST_VideoFileTag& VedioFileTag);
	QString VedioFileTagToImageDir(const ST_VideoFileTag& VedioFileTag);
	QString VedioFileTagToExtractAudioFileDir(const ST_VideoFileTag& VedioFileTag,const ST_AudioFileTag& audioFileTag);
	QString VedioFileTagToTransCodeWavFileDir(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag);

	void   generateDecodeImgNameList(const ST_VideoFileTag& VedioFileTag, const ST_VideoLoadSetting& LoadSetting,QVector<QString>& nameList);

protected slots:
	void slot_loadVideoFrameTagFinished(bool loadSuccess);
	void slot_updateExtractAudioLoadState(bool state, QString errStr);

private:
	ST_VideoH264Data m_currentLoadTempData;

	LoadVideoFrameTagThread*	m_pLoadVideoFrameTagThread = nullptr;
	ExtractAudioThread*			m_pExtractAudioThread = nullptr;
	LoadVideoFrameImageThread*	m_pLoadVideoFrameImageThread = nullptr;
};

