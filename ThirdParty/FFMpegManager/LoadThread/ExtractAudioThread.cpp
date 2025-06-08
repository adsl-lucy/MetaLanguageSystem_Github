#include "ExtractAudioThread.h"
#include "../FFMpegManager.h"
#pragma execution_character_set("utf-8")

ExtractAudioThread::ExtractAudioThread(QObject* parent):QThread(parent)
{

}

void ExtractAudioThread::runWithArgument(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& AudioFileTag)
{
	m_VedioFileTag = VedioFileTag;
	m_AudioFileTag = AudioFileTag;
	run();
}


void ExtractAudioThread::run()
{
	QString resultFileDir;
	bool processState = FFMpegManager::instance()->extractVedioAudioToWavFile(m_VedioFileTag, m_AudioFileTag, resultFileDir);
	if (processState)
	{
		bool loadAudioTagState = false;
		m_AudioFileTag = FFMpegManager::instance()->getNormalAudioFileTag(resultFileDir, loadAudioTagState);

		ST_WavRawData rawData;
		rawData.fileTag = m_AudioFileTag;

		bool loadWavRawDataState = AudioEngine::instance()->loadWavFile(resultFileDir, rawData);

		if (!loadWavRawDataState)
		{
			emit sgn_loadState(false,QString("文件读取失败"));
			return;
		}


		bool transferState = AudioEngine::instance()->PcmDataToDoubleData(rawData, m_WavDoubleData);

		if (transferState)
		{
			emit sgn_loadState(true, QString("文件载入成功"));
		}
		else
		{
			emit sgn_loadState(false, QString("文件读取失败"));
			return;
		}

		emit sgn_loadState(true, QString("文件读取成功"));
	}
}