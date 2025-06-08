#pragma once

#include <QWidget>
#include <QFileDialog>

#include "./ui_LoadVedioWgt.h"

#include "../../../ThirdParty/FFMpegManager/FFMpegManager.h"
#include "../../../Audio/Widget/LoadAudioFileWgt/WaveWgt.h"
#include "../../../Audio/Perception/AudioEngine/AudioEngine.h"
#include "./VideoWidget.h"


class LoadVedioWgt : public QWidget
{
	Q_OBJECT

public:
	LoadVedioWgt(QWidget *parent = nullptr);
	~LoadVedioWgt();

protected:
	void initUi();
	void initFFMpegManager();
	void initLoadAudioWgt();
	void initLoadVideoWgt();

	void selAndReadFileHead(QString fileDir);
	void printVideoFileTag(const ST_VideoFileTag& vedioFileTag, const ST_AudioFileTag& audioFileTag);

	ST_VideoLoadSetting getCurrentLoadSetting();

protected slots:
	void slot_selFileBtnClicked();
	//void slot_LoadVedioBtnClicked();
	void slot_DecodeAndLoadBtnClicked();
	void slot_DecodeOnlyBtnClicked();
	void slot_LoadOnlyBtnClicked();

	void slot_AudioLoadState(int percentage, QString msg);
	void slot_loadAudioRawDataState(int currentByte, int totalByte, bool error, QString errStr);
	void slot_transferAudioDataState(bool isLeftCh, int percentage, bool error, QString errStr);

	void slot_loadVideoTagState(int precentage, QString errstr);
	void slot_loadVideoTagFinished(bool loadState);
	void slot_ExtractAudioState(bool state, QString errStr);
	void slot_ExtractAudioFinished(ST_WavDoubleData& ExtractData);
	void slot_VideoFrameLoadState(int extractFrameCount, int loadFrameCount, int precentage);
	void slot_VideoLoadFinished(bool loadState);

private:
	Ui::LoadVedioWgtClass ui;

	WaveWgt*		m_pWavWgt	= nullptr;
	VideoWidget*	m_pVideoWgt = nullptr;

	ST_VideoFileTag m_selVedioFileTag;
	ST_AudioFileTag m_selAudioFileTag;

};
