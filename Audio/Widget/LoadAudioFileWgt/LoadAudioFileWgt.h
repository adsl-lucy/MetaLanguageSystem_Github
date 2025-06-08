#pragma once

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "./ui_LoadAudioFileWgt.h"
#include "../../../ThirdParty/FFMpegManager/FFMpegManager.h"
#include "../../protocol/protocol_audio.h"
#include "../../Perception/AudioEngine/AudioEngine.h"
#include "./WaveWgt.h"

class LoadAudioFileWgt : public QWidget
{
	Q_OBJECT

public:
	LoadAudioFileWgt(QWidget *parent = nullptr);
	~LoadAudioFileWgt();

public:signals:
	void sgn_saveWavData(ST_WavDoubleData& data, bool& saveState);
	void sgn_autoGenSTFTData(QString dataKey);

protected:
	void initUi();
	void initWavWgt();
	void initFFMpegManager();

	void selAndReadFileHead(QString fileDir);
	void printWavFileTag(const ST_AudioFileTag& data);
	

protected slots:
	void slot_selFileBtnClicked();
	void slot_transferSelFileIntoWavAndLoad();
	void slot_loadWavFileBtnClicked();
	void slot_showAudioDeviceDialog();
	void slot_updateDeviceInfo();
	void slot_wavDoubleDataSaved(QString dataKey);

	void slot_loadRawDataState(int currentByte, int totalByte, bool error, QString errStr);
	void slot_transferDataState(bool isLeftCh, int percentage, bool error, QString errStr);
	void slot_chtLoadDataState(int percentage, QString msg);
	
private:
	Ui::LoadAudioFileWgtClass ui;

	WaveWgt* m_pWavWgt = nullptr;

	ST_AudioFileTag m_currentSelFileTag;
};
