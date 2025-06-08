#include "LoadVedioWgt.h"
#pragma execution_character_set("utf-8")

LoadVedioWgt::LoadVedioWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUi();
	initFFMpegManager();
	initLoadAudioWgt();
	initLoadVideoWgt();
}

LoadVedioWgt::~LoadVedioWgt()
{}

void LoadVedioWgt::initFFMpegManager()
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
	connect(FFMpegManager::instance(), &FFMpegManager::sgn_loadVideoTagState, this, &LoadVedioWgt::slot_loadVideoTagState);
	connect(FFMpegManager::instance(), &FFMpegManager::sgn_loadVideoTagFinished, this, &LoadVedioWgt::slot_loadVideoTagFinished);
	connect(FFMpegManager::instance(), &FFMpegManager::sgn_ExtractAudioState, this, &LoadVedioWgt::slot_ExtractAudioState);
	connect(FFMpegManager::instance(), &FFMpegManager::sgn_ExtractAudioFinished, this, &LoadVedioWgt::slot_ExtractAudioFinished);
	connect(FFMpegManager::instance(), &FFMpegManager::sgn_VideoFrameLoadState, this, &LoadVedioWgt::slot_VideoFrameLoadState);
	connect(FFMpegManager::instance(), &FFMpegManager::sgn_VideoLoadFinished, this, &LoadVedioWgt::slot_VideoLoadFinished);

}

void LoadVedioWgt::initLoadAudioWgt()
{
	m_pWavWgt = new WaveWgt(this);
	ui.VLayout_LoadAudio->insertWidget(0, m_pWavWgt);
	connect(m_pWavWgt, &WaveWgt::sgn_dataLoadState, this, &LoadVedioWgt::slot_AudioLoadState);

	connect(m_pWavWgt, &WaveWgt::sgn_playBtnClicked, AudioEngine::instance(), &AudioEngine::slot_startPlay);
	//connect(m_pWavWgt, &WaveWgt::sgn_pauseBtnClicked, AudioEngine::instance(), &AudioEngine::slot_jump);
	connect(m_pWavWgt, &WaveWgt::sgn_stopBtnClicked, AudioEngine::instance(), &AudioEngine::slot_stopPlay);

	//connect(AudioEngine::instance(), &AudioEngine::sgn_playPositionChanged, m_pWavWgt, &WaveWgt::slot_updateVolumn);
}

void LoadVedioWgt::initLoadVideoWgt()
{
	m_pVideoWgt = new VideoWidget(this);
	ui.VLayout_LoadVideo->insertWidget(0, m_pVideoWgt);
	connect(m_pVideoWgt, &VideoWidget::sgn_playVideo, m_pWavWgt, &WaveWgt::slot_playBtnClicked);
	connect(m_pVideoWgt, &VideoWidget::sgn_stopVideo, m_pWavWgt, &WaveWgt::slot_stopBtnClicked);
}

void LoadVedioWgt::initUi()
{
	connect(AudioEngine::instance(), &AudioEngine::sgn_loadRawDataState, this, &LoadVedioWgt::slot_loadAudioRawDataState);
	connect(AudioEngine::instance(), &AudioEngine::sgn_transFerRawDataState, this, &LoadVedioWgt::slot_transferAudioDataState);
	connect(ui.btn_selLoadFile,		&QPushButton::clicked, this, &LoadVedioWgt::slot_selFileBtnClicked);
	connect(ui.btn_DecodeAndLoad,	&QPushButton::clicked, this, &LoadVedioWgt::slot_DecodeAndLoadBtnClicked);
	connect(ui.btn_decodeOnly,		&QPushButton::clicked, this, &LoadVedioWgt::slot_DecodeOnlyBtnClicked);
	connect(ui.btn_loadOnly,		&QPushButton::clicked, this, &LoadVedioWgt::slot_LoadOnlyBtnClicked);
	ui.btn_DecodeAndLoad->setEnabled(false);
	ui.btn_decodeOnly->setEnabled(false);
	ui.btn_loadOnly->setEnabled(false);
}

void LoadVedioWgt::slot_selFileBtnClicked()
{
	QString loadDir = QApplication::applicationDirPath() + QString("/TestVedio");
	QString OpenFileDir = QFileDialog::getOpenFileName(this, tr("Open file"), loadDir, tr("Vedio Files (*.mp4 *.mkv *.mov *.wmv *.avi)"));
	if (OpenFileDir.isEmpty())
	{
		return;
	}
	selAndReadFileHead(OpenFileDir);
}

void LoadVedioWgt::selAndReadFileHead(QString OpenFileDir)
{
	QFileInfo			fileInfo(OpenFileDir);
	QString				fileNameStr = fileInfo.baseName();
	QString				fileDirStr = fileInfo.path();
	EN_VideoFileType	fileType = FFMpegManager::instance()->getVedioFileType(OpenFileDir);

	if (fileType == EN_VideoFileType::undefine)
	{
		ui.label_fileTagLoadState->setText("不支持的视频格式");
		return;
	}

	//ui.btn_loadWavFile->setEnabled(false);
	//ui.btn_transferIntoWavAndLoad->setEnabled(false);
	ui.label_fileTagLoadState->setText("文件头读取状态：开始读取文件头状态");
	ui.label_fileTagLoadState->repaint();

	ST_VideoFileTag vedioFileTag;
	ST_AudioFileTag audioFileTag;

	bool processState = FFMpegManager::instance()->getVedioFileTag(OpenFileDir, vedioFileTag, audioFileTag);
	if (processState)
	{
		ui.label_fileTagLoadState->setText("文件头读取状态：读取文件头成功");
		printVideoFileTag(vedioFileTag, audioFileTag);
		m_selVedioFileTag = vedioFileTag;
		m_selAudioFileTag = audioFileTag;
		ui.SBox_LoadPicWidth->setValue(vedioFileTag.width);
		ui.SBox_LoadPicHeight->setValue(vedioFileTag.height);
	}
	else
	{
		ui.label_fileTagLoadState->setText("文件头读取状态：读取文件头失败");
	}
	ui.btn_DecodeAndLoad->setEnabled(processState);
	ui.btn_decodeOnly->setEnabled(processState);
	
	bool decodeFileExist = FFMpegManager::instance()->checkDecodeFileExist(m_selVedioFileTag);
	ui.btn_loadOnly->setEnabled(decodeFileExist);

}

void LoadVedioWgt::printVideoFileTag(const ST_VideoFileTag& vedioFileTag, const ST_AudioFileTag& audioFileTag)
{
	ui.label_file_FileName->setText(QString("文件名：%1").arg(vedioFileTag.fileName));
	ui.label_file_Path->setText(QString("文件路径：%1").arg(vedioFileTag.filePath));
	ui.label_file_FileType->setText(QString("文件类型：%1").arg(VisionProtocol::VedioFileTypeToSuffix(vedioFileTag.fileType)));
	ui.label_file_Duration->setText(QString("持续时间：%1").arg(vedioFileTag.Duration.toString("hh:mm:ss")));

	ui.label_video_codec->setText(QString("视频编码器：%1").arg(vedioFileTag.codec));

	QString resolutionStr = QString("%1 %2").arg(vedioFileTag.width).arg(vedioFileTag.height);

	ui.label_video_resolution->setText(QString("分辨率：%1").arg(resolutionStr));
	ui.label_video_frameRate->setText(QString("帧率：%1").arg(vedioFileTag.frameRate,0,'f',1));
	ui.label_video_BitRate->setText(QString("视频比特率：%1").arg(vedioFileTag.BitRate));
	ui.label_video_pixFmt->setText(QString("像素格式：%1").arg(vedioFileTag.pixelFormat));
	ui.label_video_colorType->setText(QString("颜色格式：%1").arg(vedioFileTag.colorDecodeType));

	ui.label_audio_codec->setText(QString("音频编码器：%1").arg(AudioProtocol::AudioFileTypeToStr(audioFileTag.fileType)));
	ui.label_audio_ChanelNum->setText(QString("通道数：%1").arg(audioFileTag.ChannelNum));
	ui.label_audio_sampleRate->setText(QString("采样率：%1").arg(audioFileTag.sampleRate));
	ui.label_audio_Bitrate->setText(QString("音频比特率：%1").arg(audioFileTag.BitRate));
}

void LoadVedioWgt::slot_AudioLoadState(int percentage, QString msg)
{
	ui.label_audioLoadState->setText(msg);
	ui.progressBar_audioLoadState->setValue(percentage);
}

void LoadVedioWgt::slot_loadAudioRawDataState(int currentByte, int totalByte, bool error, QString errStr)
{
	if (error)
	{
		ui.label_audioLoadState->setText(QString("音频读取状态：%1").arg(errStr));
		ui.progressBar_audioLoadState->setValue(0);
	}
	else
	{
		ui.label_audioLoadState->setText(QString("音频读取状态：%1 / %2").arg(currentByte).arg(totalByte));
		ui.progressBar_audioLoadState->setValue((double)currentByte / (double)totalByte * 100);
	}
}

void LoadVedioWgt::slot_transferAudioDataState(bool isLeftCh, int percentage, bool error, QString errStr)
{
	QString headStr("音频读取状态：");

	isLeftCh ? headStr += QString(" 左 ") : headStr += QString(" 右 ");

	if (error)
	{
		ui.label_audioLoadState->setText(headStr + errStr);
		ui.progressBar_audioLoadState->setValue(0);
	}
	else
	{
		ui.label_audioLoadState->setText(headStr + QString("：%1%").arg(percentage));
		ui.progressBar_audioLoadState->setValue(percentage);
	}
}

void LoadVedioWgt::slot_loadVideoTagState(int precentage, QString errstr)
{
	ui.label_fileTagLoadState->setText(QString("帧标签读取状态：%1").arg(errstr));
	ui.progressBar_fileTagLoadState->setValue(precentage);
}

void LoadVedioWgt::slot_loadVideoTagFinished(bool loadState)
{
	if (!loadState)
	{
		ui.label_fileTagLoadState->setText(QString("帧标签读取状态：%1").arg(QString("失败")));
		ui.progressBar_fileTagLoadState->setValue(0);
		return;
	}
 
	ui.label_fileTagLoadState->setText(QString("帧标签读取状态：%1").arg(QString("成功")));
	ui.progressBar_fileTagLoadState->setValue(100);

	bool decodeFileExist = FFMpegManager::instance()->checkDecodeFileExist(m_selVedioFileTag);
	ui.btn_loadOnly->setEnabled(decodeFileExist);

	const ST_VideoFileTag& TempVideoFileTag = FFMpegManager::instance()->getTmepVideoFileTag();
	ST_VideoLoadSetting& loadSetting = FFMpegManager::instance()->getTmepVideoLoadSetting();

	m_pVideoWgt->printVideoTagInfo(TempVideoFileTag, loadSetting);


}

void LoadVedioWgt::slot_ExtractAudioState(bool state, QString errStr)
{
	ui.label_audioLoadState->setText(QString("音频读取状态：%1").arg(errStr));
}

void LoadVedioWgt::slot_ExtractAudioFinished(ST_WavDoubleData& ExtractData)
{
	m_pWavWgt->loadWavData(ExtractData,false);
}

void LoadVedioWgt::slot_VideoFrameLoadState(int extractFrameCount, int loadFrameCount, int precentage)
{
	ui.label_videoLoadState->setText(QString("视频读取状态 解码：%1 加载：%2").arg(extractFrameCount).arg(loadFrameCount));
	ui.progressBar_VideoLoadState->setValue(precentage);
}

void LoadVedioWgt::slot_VideoLoadFinished(bool loadState)
{
	if (!loadState)
	{
		ui.label_videoLoadState->setText(QString("视频读取状态 : 错误"));
		ui.progressBar_VideoLoadState->setValue(0);
		return;
	}
	ui.label_videoLoadState->setText(QString("视频读取状态 : 成功"));
	ui.progressBar_VideoLoadState->setValue(100);

	ST_VideoFileTag& FileTag = FFMpegManager::instance()->getTmepVideoFileTag();
	ST_VideoLoadSetting& loadSetting = FFMpegManager::instance()->getTmepVideoLoadSetting();

	m_pVideoWgt->loadVideoFrame(FileTag, loadSetting);

}

void LoadVedioWgt::slot_DecodeAndLoadBtnClicked()
{
	bool decodeFileExist = FFMpegManager::instance()->checkDecodeFileExist(m_selVedioFileTag);
	if (decodeFileExist)
	{
		QString msgFileName = m_selVedioFileTag.fileName + '.' + VisionProtocol::VedioFileTypeToSuffix(m_selVedioFileTag.fileType);
		QMessageBox::StandardButton btnType = QMessageBox::information(this, QString("转换结果已存在"), msgFileName + QString("解码结果已存在，是否仅导入解码结果?"),
			QMessageBox::Yes | QMessageBox::No);

		if (btnType == QMessageBox::Yes)
		{
			slot_LoadOnlyBtnClicked();
			return;
		}
	}

	ST_VideoLoadSetting LoadSetting = getCurrentLoadSetting();
	LoadSetting.loadType = EN_VideoLoadType::DecodeAndLoad;
	FFMpegManager::instance()->startDecodeVideoFile(m_selVedioFileTag, LoadSetting);
	FFMpegManager::instance()->startExtractAndLoadWavFileFromVideo(m_selVedioFileTag, m_selAudioFileTag);

}

void LoadVedioWgt::slot_DecodeOnlyBtnClicked()
{
	ST_VideoLoadSetting LoadSetting = getCurrentLoadSetting();
	LoadSetting.loadType = EN_VideoLoadType::DecodeOnly;
	FFMpegManager::instance()->startDecodeVideoFile(m_selVedioFileTag, LoadSetting);

}

void LoadVedioWgt::slot_LoadOnlyBtnClicked()
{
	bool decodeFileExist = FFMpegManager::instance()->checkDecodeFileExist(m_selVedioFileTag);
	if (!decodeFileExist)
	{
		QString msgFileName = m_selVedioFileTag.fileName + '.' + VisionProtocol::VedioFileTypeToSuffix(m_selVedioFileTag.fileType);
		QMessageBox::information(this, QString("解码结果不存在"), msgFileName + QString("解码结果不存在！"), QMessageBox::Yes);
		return;
	}
	ST_VideoLoadSetting LoadSetting = getCurrentLoadSetting();
	LoadSetting.loadType = EN_VideoLoadType::LoadOnly;
	FFMpegManager::instance()->startDecodeVideoFile(m_selVedioFileTag, LoadSetting);
	FFMpegManager::instance()->startExtractAndLoadWavFileFromVideo(m_selVedioFileTag, m_selAudioFileTag);
}


ST_VideoLoadSetting LoadVedioWgt::getCurrentLoadSetting()
{
	ST_VideoLoadSetting LoadSetting;
	LoadSetting.loadFrameRate = ui.SBox_LoadFrameRate->value();

	int LoadWidth = ui.SBox_LoadPicWidth->value();
	int LoadHeight = ui.SBox_LoadPicHeight->value();
	LoadSetting.loadFrameSize = QSize(LoadWidth, LoadHeight);

	LoadSetting.LoadFrameCount = VisionProtocol::getVideoLoadFrameCount(m_selVedioFileTag, LoadSetting);

	return LoadSetting;
}
