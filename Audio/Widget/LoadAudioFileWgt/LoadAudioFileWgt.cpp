#include "LoadAudioFileWgt.h"
#pragma execution_character_set("utf-8")

LoadAudioFileWgt::LoadAudioFileWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initUi();
	initWavWgt();
	initFFMpegManager();
	slot_updateDeviceInfo();
	connect(AudioEngine::instance(), &AudioEngine::sgn_loadRawDataState, this, &LoadAudioFileWgt::slot_loadRawDataState);
	connect(AudioEngine::instance(), &AudioEngine::sgn_transFerRawDataState, this, &LoadAudioFileWgt::slot_transferDataState);
	connect(AudioEngine::instance(), &AudioEngine::sgn_InputDeviceChanged, this, &LoadAudioFileWgt::slot_updateDeviceInfo);
	connect(AudioEngine::instance(), &AudioEngine::sgn_OutputDeviceChanged, this, &LoadAudioFileWgt::slot_updateDeviceInfo);
	connect(DataCenterManager::instance(), &DataCenterManager::sgn_WavDoubleDataSaved, this, &LoadAudioFileWgt::slot_wavDoubleDataSaved);
}

LoadAudioFileWgt::~LoadAudioFileWgt()
{}

void LoadAudioFileWgt::initUi()
{
	connect(ui.btn_selLoadFile,					&QPushButton::clicked, this, &LoadAudioFileWgt::slot_selFileBtnClicked);
	connect(ui.btn_transferIntoWavAndLoad,		&QPushButton::clicked, this, &LoadAudioFileWgt::slot_transferSelFileIntoWavAndLoad);
	connect(ui.btn_loadWavFile,					&QPushButton::clicked, this, &LoadAudioFileWgt::slot_loadWavFileBtnClicked);
	connect(ui.btn_showAudioDeviceDialog,		&QPushButton::clicked, this, &LoadAudioFileWgt::slot_showAudioDeviceDialog);
}

void LoadAudioFileWgt::initWavWgt()
{
	m_pWavWgt = new WaveWgt(this);
	ui.VLayout_loadWavCht->insertWidget(0, m_pWavWgt);
	connect(m_pWavWgt, &WaveWgt::sgn_dataLoadState, this, &LoadAudioFileWgt::slot_chtLoadDataState);

	connect(m_pWavWgt, &WaveWgt::sgn_playBtnClicked		, AudioEngine::instance(), &AudioEngine::slot_startPlay);
	connect(m_pWavWgt, &WaveWgt::sgn_jumpBtnClicked,      AudioEngine::instance(), &AudioEngine::slot_jump);
	connect(m_pWavWgt, &WaveWgt::sgn_stopBtnClicked		, AudioEngine::instance(), &AudioEngine::slot_stopPlay);

	//connect(AudioEngine::instance(), &AudioEngine::sgn_playPositionChanged, m_pWavWgt, &WaveWgt::slot_updateVolumn);
}

void LoadAudioFileWgt::initFFMpegManager()
{
	bool ffMpegExist = FFMpegManager::instance()->checkFFMpegState();
	bool ffProbeState = FFMpegManager::instance()->checkFFProbeState();

	if (ffMpegExist)
	{
		ui.label_ffmpegState->setText("ffMpeg:exist");
	}
	else
	{
		ui.label_ffmpegState->setText("ffMpeg:unexist");
	}

	if (ffMpegExist)
	{
		ui.label_ffprobeState->setText("ffProbe:exist");
	}
	else
	{
		ui.label_ffprobeState->setText("ffProbe:unexist");
	}
}

void LoadAudioFileWgt::slot_selFileBtnClicked()
{
	QString loadDir = QApplication::applicationDirPath() + QString("/TestAudio");
	QString OpenFileDir = QFileDialog::getOpenFileName(this, tr("Open file"), loadDir, tr("Audio Files (*.mp3 *.flac *.wav)"));
	selAndReadFileHead(OpenFileDir);
}

void LoadAudioFileWgt::selAndReadFileHead(QString OpenFileDir)
{
	QFileInfo			fileInfo(OpenFileDir);
	QString				fileNameStr = fileInfo.baseName();
	QString				fileDirStr = fileInfo.path();
	EN_AudioFileType	fileType = FFMpegManager::instance()->getAudioFileType(OpenFileDir);

	ui.btn_loadWavFile->setEnabled(false);
	ui.btn_transferIntoWavAndLoad->setEnabled(false);
	ui.label_loadState->setText("����״̬����ʼ��ȡ�ļ�ͷ״̬");
	ui.label_loadState->repaint();

	bool loadState = false;
	const ST_AudioFileTag audioTag = FFMpegManager::instance()->getNormalAudioFileTag(OpenFileDir, loadState);

	ui.label_selFileName->setText(QString("�ļ�����%1").arg(fileNameStr));
	ui.label_selFilePath->setText(QString("�ļ�·����%1").arg(fileDirStr));
	ui.label_selFileType->setText(QString("�ļ����ͣ�%1").arg(AudioProtocol::AudioFileTypeToStr(fileType)));

	if (loadState)
	{
		ui.label_loadState->setText("����״̬����ȡ�ļ�ͷ�ɹ�");
		printWavFileTag(audioTag);
		m_currentSelFileTag = audioTag;
		ui.btn_loadWavFile->setEnabled(fileType == EN_AudioFileType::wav);
		ui.btn_transferIntoWavAndLoad->setEnabled(fileType == EN_AudioFileType::mp3 || fileType == EN_AudioFileType::flac);		
	}
	else
	{
		ui.label_loadState->setText("����״̬����ȡ�ļ�ͷʧ��");
	}
}

void LoadAudioFileWgt::slot_transferSelFileIntoWavAndLoad()
{
	QString targetPath = m_currentSelFileTag.filePath;
	QString ArgResultSuffix = AudioProtocol::AudioFileTypeToStr(EN_AudioFileType::wav);
	QString resultFile = targetPath + '/' + m_currentSelFileTag.fileName + '.' + ArgResultSuffix;
	

	if (QFile::exists(resultFile))
	{
		QString msgFileName = m_currentSelFileTag.fileName + '.' + ArgResultSuffix;
		QMessageBox::StandardButton btnType = QMessageBox::information(this, QString("ת������Ѵ���"),msgFileName + QString("�Ѵ��ڣ��Ƿ�ɾ�������ļ�?"),
																		QMessageBox::Yes | QMessageBox::No);

		if (btnType == QMessageBox::Yes)
		{
			bool removeState = QFile::remove(resultFile);
			if (!removeState)
			{
				ui.label_loadState->setText("�Ƴ������ļ�ʧ��");
			}
		}
		else
		{
			return;
		}	
	}

	ui.btn_loadWavFile->setEnabled(false);
	ui.btn_transferIntoWavAndLoad->setEnabled(false);

	ui.label_loadState->setText("����״̬����ʼת����ʽ");
	ui.label_loadState->repaint();
	bool transferState	= FFMpegManager::instance()->transferIntoWavFormat(m_currentSelFileTag, targetPath, resultFile);

	if (!transferState)
	{
		ui.label_loadState->setText("����״̬����ʽת��ʧ��");
		return;
	}

	selAndReadFileHead(resultFile);
	slot_loadWavFileBtnClicked();
}

void LoadAudioFileWgt::slot_loadWavFileBtnClicked()
{
	ui.btn_loadWavFile->setEnabled(false);
	QString fullFilePath = AudioEngine::instance()->getFullWavFilePath(m_currentSelFileTag);

	ST_WavRawData rawData;
	rawData.fileTag = m_currentSelFileTag;

	bool loadState = AudioEngine::instance()->loadWavFile(fullFilePath, rawData);

	if (!loadState)
	{
		ui.label_loadState->setText("����״̬���ļ���ȡʧ��");
		ui.btn_loadWavFile->setEnabled(true);
		return;
	}


	ST_WavDoubleData doubleData;
	bool transferState = AudioEngine::instance()->PcmDataToDoubleData(rawData, doubleData);

	if (transferState)
	{
		ui.label_loadState->setText("����״̬���ļ�����ɹ�");
	}
	else
	{
		ui.label_loadState->setText("����״̬���ļ�����ʧ��");
		ui.btn_loadWavFile->setEnabled(true);
		return;
	}
	
	m_pWavWgt->loadWavData(doubleData,ui.checkBox_autoGenSTFTResult->isChecked());

}

void LoadAudioFileWgt::printWavFileTag(const ST_AudioFileTag& data)
{
	ui.label_selFileChannelNum->setText(QString("ͨ������%1").arg(data.ChannelNum));
	ui.label_selFileDuration->setText(QString("����ʱ�䣺%1").arg(data.Duration.toString("hh:mm:ss")));
	ui.label_selFileBitRate->setText(QString("�����ʣ�%1").arg(data.BitRate));
	ui.label_selFileBitrate->setText(QString("�����ʣ�%1").arg(data.sampleRate));
	ui.label_selFileBitPerSample->setText(QString("������ȣ�%1").arg(data.BitBerSample));
}

void LoadAudioFileWgt::slot_showAudioDeviceDialog()
{
	AudioEngine::instance()->showAudioDeviceDialog();
}

void LoadAudioFileWgt::slot_updateDeviceInfo()
{
	const QAudioDeviceInfo& inputDev = AudioEngine::instance()->getCurrentInputDevice();
	const QAudioDeviceInfo& outputDev = AudioEngine::instance()->getCurrentOutputDevice();

	ui.label_currentInputDevice->setText(QString("�����豸��%1").arg(inputDev.deviceName()));
	ui.label_currentOutputDevice->setText(QString("����豸��%1").arg(outputDev.deviceName()));
}

void LoadAudioFileWgt::slot_wavDoubleDataSaved(QString dataKey)
{
	if (ui.checkBox_autoGenSTFTResult->isChecked() && this->isVisible())
	{
		emit sgn_autoGenSTFTData(dataKey);
	}
}

void LoadAudioFileWgt::slot_loadRawDataState(int currentByte, int totalByte, bool error, QString errStr)
{
	if (error)
	{
		ui.label_loadState->setText(QString("����״̬��%1").arg(errStr));
		ui.progressBar_loadData->setValue(0);
	}
	else
	{
		ui.label_loadState->setText(QString("����״̬��%1 / %2").arg(currentByte).arg(totalByte));
		ui.progressBar_loadData->setValue((double)currentByte / (double)totalByte * 100);
	}
}
void LoadAudioFileWgt::slot_transferDataState(bool isLeftCh, int percentage, bool error, QString errStr)
{
	QString headStr("ת��״̬��");

	isLeftCh ? headStr += QString(" �� ") : headStr += QString(" �� ");

	if (error)
	{
		ui.label_loadState->setText(headStr + errStr);
		ui.progressBar_loadData->setValue(0);
	}
	else
	{
		ui.label_loadState->setText(headStr + QString("��%1%").arg(percentage));
		ui.progressBar_loadData->setValue(percentage);
	}
}

void LoadAudioFileWgt::slot_chtLoadDataState(int percentage, QString msg)
{
	ui.label_loadState->setText(msg);
	ui.progressBar_loadData->setValue(percentage);
}
