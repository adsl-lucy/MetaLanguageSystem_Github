#include "EffSigBuffWgt.h"
#pragma execution_character_set("utf-8")

EffSigBuffWgt::EffSigBuffWgt(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	initUI();
	initUpdateTimer();
}

EffSigBuffWgt::~EffSigBuffWgt()
{}


void EffSigBuffWgt::initUI()
{
	connect(ui.btn_updateTimeSecCht, &QPushButton::clicked, this, &EffSigBuffWgt::slot_updateTimeSecChtBtnClicked);
	connect(ui.btn_updateHotCht, &QPushButton::clicked, this, &EffSigBuffWgt::slot_updateHotChtBtnClicked);
	connect(ui.btn_VibStateRel_GenResult, &QPushButton::clicked, this, &EffSigBuffWgt::slot_GenVibStateRelBtnClicked);

	connect(ui.HSlider_TimeFrameIndex, &QAbstractSlider::valueChanged, this, &EffSigBuffWgt::slot_TimeFrameSliderMoved);

	connect(ui.btn_play, &QPushButton::clicked, this, &EffSigBuffWgt::slot_play);
	connect(ui.btn_jump, &QPushButton::clicked, this, &EffSigBuffWgt::slot_jump);
	connect(ui.btn_stop, &QPushButton::clicked, this, &EffSigBuffWgt::slot_stop);

	connect(ui.btn_lastFrame, &QPushButton::clicked, this, &EffSigBuffWgt::slot_btnLastFrameClicked);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &EffSigBuffWgt::slot_btnNextFrameClicked);

	connect(DataCenterManager::instance(), &DataCenterManager::sgn_STFTDataSaved, this, &EffSigBuffWgt::slot_getNewSTFTData);
	connect(VibrateStateRelvanceNetwork::instance(), &VibrateStateRelvanceNetwork::sgn_VibStateRel_GenState, this, &EffSigBuffWgt::slot_getVibStateGenMsg);
	connect(DataCenterManager::instance(), &DataCenterManager::sgn_VibStateRelDataSaved, this, &EffSigBuffWgt::slot_EffSigBuffResultGet);

	m_pBtnGroup_getEffSigBuffData = new QButtonGroup(this);
	m_pBtnGroup_getEffSigBuffData->setExclusive(true);
	m_pBtnGroup_getEffSigBuffData->addButton(ui.radioButton_getData_GoTimeSecCht);
	//m_pBtnGroup_getDiffData->addButton(ui.radioButton_getDiffNetData_GoTimeSecCht);
	ui.radioButton_getData_GoTimeSecCht->setChecked(true);

	ui.comboBox_TimeSecChtBarType->setItemData(0, QVariant((int)EN_TimeSecCht_PaintType::STFT));
	ui.comboBox_TimeSecChtBarType->setItemData(1, QVariant((int)EN_TimeSecCht_PaintType::EffOsc));
	ui.comboBox_TimeSecChtBarType->setItemData(2, QVariant((int)EN_TimeSecCht_PaintType::BDSNR));
	ui.comboBox_TimeSecChtBarType->setItemData(3, QVariant((int)EN_TimeSecCht_PaintType::VibState));

	connect(ui.comboBox_TimeSecChtBarType, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) { slot_TimeSecChtTypeChanged(); });
	slot_TimeSecChtTypeChanged();

	m_pBtnGroup_TimeSecCht_PaintSetting = new QButtonGroup(this);
	m_pBtnGroup_TimeSecCht_PaintSetting->setExclusive(false);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_EffOsc_drawUnderTIQBar);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_EffOsc_drawTIQLine);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_EffOsc_drawWndSpecNoise);

	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_BDSNR_drawFilter);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_BDSNR_drawFilterMain);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_BDSNR_drawConstrainPt);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_BDSNR_drawSubPt);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_TimeSecCht_BDSNR_drawNoisePt);

	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_VibState_Paint_NotTransfer);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_VibState_Paint_Atk);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_VibState_Paint_Increase);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_VibState_Paint_Sustain);
	m_pBtnGroup_TimeSecCht_PaintSetting->addButton(ui.checkBox_VibState_Paint_Decrease);

	m_pBtnGroup_TimeSecCht_VibStatePaintSetting = new QButtonGroup(this);
	m_pBtnGroup_TimeSecCht_VibStatePaintSetting->setExclusive(true);
	m_pBtnGroup_TimeSecCht_VibStatePaintSetting->addButton(ui.radioButton_VibState_AllState);
	m_pBtnGroup_TimeSecCht_VibStatePaintSetting->addButton(ui.radioButton_VibState_transferState);

	connect(m_pBtnGroup_TimeSecCht_PaintSetting, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int id) { slot_PaintSettingBtnClicked(); });
	connect(m_pBtnGroup_TimeSecCht_VibStatePaintSetting, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int id) { slot_PaintSettingBtnClicked(); });
	slot_PaintSettingBtnClicked();
}

void EffSigBuffWgt::initUpdateTimer()
{
	m_pUpdateSectionTimer = new QTimer(this);
	m_pUpdateSectionTimer->setSingleShot(false);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	connect(m_pUpdateSectionTimer, &QTimer::timeout, this, &EffSigBuffWgt::slot_updateTimerTimeUp);

}

void EffSigBuffWgt::init()
{
	m_pSTFTHotCht = new FFT_Chart_STFTHotGram(this);
	m_pSTFTHotCht->setTitleText(QString("STFT Hot Cht"));
	ui.VLayout_STFT_Cht_HotCht->insertWidget(0, m_pSTFTHotCht);
	connect(m_pSTFTHotCht, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &EffSigBuffWgt::slot_updateHotChtGenState);


	m_pTimeSecCht = new TimeSecCht_Wgt(this);
	ui.HLayout_TimeSecCht->insertWidget(0, m_pTimeSecCht);
	connect(m_pTimeSecCht, &TimeSecCht_Wgt::sgn_SecRectGenerateState, this, &EffSigBuffWgt::slot_updateTimeSecGenState);
	connect(m_pTimeSecCht, &TimeSecCht_Wgt::sgn_SecRectGenFinished, this, &EffSigBuffWgt::slot_TimeSecGenFinished);

	ST_TimeSecChtGenSetting TimeSecChtGenSetting;
	TimeSecChtGenSetting.Gen_STFT		= true;
	TimeSecChtGenSetting.Gen_EffOsc		= true;
	TimeSecChtGenSetting.Gen_BDSNR		= true;
	TimeSecChtGenSetting.Gen_VibState	= true;
	m_pTimeSecCht->setGenType(TimeSecChtGenSetting);
}

void EffSigBuffWgt::updateSTFTLabel(const ST_STFTOutputData& data)
{
	ui.label_STFTFileName->setText(QString("文件名称 : %1").arg(data.InputPara.fileName));

	QTime startTime = QTime(0, 0, 0).addMSecs(data.InputPara.startTime * 1000);
	QTime endTime = startTime.addMSecs(data.InputPara.timeLength * 1000);

	int dataDurationMsec = data.InputPara.timeLength * 1000;
	QTime dataDurationTime = QTime(0, 0, 0).addMSecs(dataDurationMsec);

	ui.label_dataDuration->setText(QString("数据持续时间 : %1").arg(dataDurationTime.toString("mm:ss.zzz")));

	double FreqInterval = FFTManager::instance()->getFreqencyInterval(data.InputPara.sampleRate, data.InputPara.WndPara.pointCount);
	ui.label_STFTState->setText(QString("FFT频率间隔 : %1 hz STFT步长 :%2 ms ").arg(FreqInterval, 0, 'f', 2).arg(data.InputPara.GapInTimeLength * 1000, 0, 'f', 2));
}

void EffSigBuffWgt::updateSTFTPanel(const ST_STFTOutputData& data)
{
	int maxFrameIndex = data.vecOutput.size() - 1;
	ui.HSlider_TimeFrameIndex->setMinimum(0);
	ui.HSlider_TimeFrameIndex->setMaximum(maxFrameIndex);
}

void EffSigBuffWgt::updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime)
{
	ui.label_TimeFrameTime->setText(QString("截面时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));
	ui.label_TimeSecCht_FrameCenterTime->setText(QString("截面中心时间：%1").arg(FrameMidTime.toString("mm:ss.zzz")));
}

void EffSigBuffWgt::resetFrameRateState()
{
	m_TimeFrameRateStatStartSysTime = QTime::currentTime();
	m_nStatFrameRateStartFrameIndex = ui.HSlider_TimeFrameIndex->value();
}

void EffSigBuffWgt::updateFrameRateState()
{
	int MsecCost = m_TimeFrameRateStatStartSysTime.msecsTo(QTime::currentTime());
	int FrameCost = ui.HSlider_TimeFrameIndex->value() - m_nStatFrameRateStartFrameIndex;
	double AvrMsecPerFrame = (double)MsecCost / (double)FrameCost;
	double FrameRate = 1000.0 / AvrMsecPerFrame;
	ui.label_TimeSecCht_AvrSecFrameRate->setText(QString("平均帧率：%1").arg(FrameRate, 0, 'f', 2));
}

void EffSigBuffWgt::slot_TimeFrameSliderMoved(int newVal)
{
	//qDebug() << "STFTAnalysePanel::slot_TimeFrameSliderMoved : " << newVal;
	int		frameIndex = newVal;
	double	frameInterval = m_dataPara.GapInTimeLength;
	int		frameStartMsec = frameIndex * frameInterval * 1000;
	int		frameEndMsec = frameStartMsec + m_dataPara.WndPara.WndMsec;
	int		frameMidMsec = (frameStartMsec + frameEndMsec) / 2;

	QTime frameStartTime = QTime(0, 0, 0).addMSecs(frameStartMsec);
	QTime frameMidTime = QTime(0, 0, 0).addMSecs(frameMidMsec);
	QTime frameEndTime = QTime(0, 0, 0).addMSecs(frameEndMsec);
	updateTimeFrameLabel(frameStartTime, frameMidTime, frameEndTime);

	m_pTimeSecCht->setCurrentFrameIndex(newVal);

	m_pSTFTHotCht->setCurrentTime(frameStartTime);

	QTime HotChtStartTime;
	QTime HotChtEndTime;
	m_pSTFTHotCht->getCurrentTimeRange(HotChtStartTime, HotChtEndTime);
	if (frameStartTime < HotChtStartTime || frameStartTime > HotChtEndTime)
	{
		int HotChtTimeWndLengthMsec = ui.SBox_hotChtTimeLength->value();
		QTime HotChtStartTime = ui.timeEdit_hotChtStartTime->time();
		int MsecToHotChtStartTime = QTime(0, 0, 0).msecsTo(HotChtStartTime);

		int currentPage = HotChtStartTime.msecsTo(frameStartTime) / HotChtTimeWndLengthMsec;
		QTime hotChtNewStartTime = HotChtStartTime.addMSecs(currentPage * HotChtTimeWndLengthMsec);
		if (currentPage < 0)
		{
			hotChtNewStartTime = QTime(0, 0, 0);
		}
		m_pSTFTHotCht->setTimeRange(hotChtNewStartTime, HotChtTimeWndLengthMsec);
	}

}

void EffSigBuffWgt::slot_updateTimerTimeUp()
{
	updateFrameRateState();
	double frameMsec = m_nCurrentTimeUpCount * m_nUpdateMsec;
	double frameInterval = m_dataPara.GapInTimeLength * 1000;
	int frameIndex = frameMsec / frameInterval;
	int maxFrame = ui.HSlider_TimeFrameIndex->maximum();
	if (frameIndex > maxFrame)
	{
		qDebug() << QString("OscillationSeparatorWgt::slot_updateTimerTimeUp : stop");
		m_pUpdateSectionTimer->stop();
		ui.HSlider_TimeFrameIndex->setValue(maxFrame);
		slot_TimeFrameSliderMoved(maxFrame);
	}
	else
	{
		QString currentTime = QTime::currentTime().toString("mm:ss.zzz");
		qDebug() << QString("OscillationSeparatorWgt::slot_updateTimerTimeUp : show msec %1 : frameindex : %2 realTime %3").arg(frameMsec).arg(frameIndex).arg(currentTime);
		ui.HSlider_TimeFrameIndex->setValue(frameIndex);
		slot_TimeFrameSliderMoved(frameIndex);
		m_nCurrentTimeUpCount += 1;
	}

}

void EffSigBuffWgt::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_HotCht_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_HotChtGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_HotChtGenState->setText(QString("生成结束"));
	}
}

void EffSigBuffWgt::slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_TimeSec_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_TimeSecGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}

}

void EffSigBuffWgt::slot_TimeSecGenFinished()
{
	ui.progressBar_TimeSec_Genstate->setValue(100);
	ui.label_TimeSecGenState->setText(QString("生成结束"));
}

void EffSigBuffWgt::slot_EffSigBuffResultGet(QString DataKey)
{
	if (ui.radioButton_getData_GoTimeSecCht->isChecked())
	{
		slot_updateHotChtBtnClicked();
		ui.tabWidget_EffSigBuffPannel->setCurrentIndex(1);
		slot_updateTimeSecChtBtnClicked();
	}
}

void EffSigBuffWgt::slot_getVibStateGenMsg(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_VibState_GenResult->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_VibState_GenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_VibState_GenState->setText(QString("生成结束"));
	}
}
//
//void EffSigBuffWgt::slot_AudioObjecResultGet(QString DataKey)
//{
//	//bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterDataType::Diff, m_STFTDataKey);
//
//	//if (!dataExist)
//	//{
//	//	return;
//	//}
//
//	//const ST_DiffNetOutput& DiffData = DataCenterManager::instance()->getDiffOutputMap().find(m_STFTDataKey).value();
//	//ui.label_EndGroupStartRatio->setText(QString("最后一组起始比例（%）：%1").arg(DiffData.DiffNetState.SideStartRatio * 100, 0, 'f', 2));
//
//	//if (ui.radioButton_getDiffNetData_GoTimeSecCht->isChecked())
//	//{
//	//	slot_updateHotChtBtnClicked();
//	//	ui.tabWidget_DiffNetPannel->setCurrentIndex(1);
//	//	slot_updateTimeSecChtBtnClicked();
//	//}
//	//else
//	//{
//	//	emit sgn_GoFreqDoubleResult(m_STFTDataKey);
//	//}
//}


void EffSigBuffWgt::slot_btnNextFrameClicked()
{
	if (ui.HSlider_TimeFrameIndex->value() < ui.HSlider_TimeFrameIndex->maximum())
	{
		int newVal = ui.HSlider_TimeFrameIndex->value() + 1;
		ui.HSlider_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}
void EffSigBuffWgt::slot_btnLastFrameClicked()
{
	if (ui.HSlider_TimeFrameIndex->value() > 0)
	{
		int newVal = ui.HSlider_TimeFrameIndex->value() - 1;
		ui.HSlider_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}

void EffSigBuffWgt::slot_TimeSecChtTypeChanged()
{
	EN_TimeSecCht_PaintType currentType = (EN_TimeSecCht_PaintType)ui.comboBox_TimeSecChtBarType->currentData().toInt();
	m_pTimeSecCht->setPaintType(currentType);
}

void EffSigBuffWgt::slot_PaintSettingBtnClicked()
{
	ST_TimeSecChtPaintSetting paintSetting;
	paintSetting.EffOsc_UnderTIQBar		= ui.checkBox_TimeSecCht_EffOsc_drawUnderTIQBar->isChecked();
	paintSetting.EffOsc_TIQLine			= ui.checkBox_TimeSecCht_EffOsc_drawTIQLine->isChecked();
	paintSetting.EffOsc_WndSepcNoise	= ui.checkBox_TimeSecCht_EffOsc_drawWndSpecNoise->isChecked();
	

	paintSetting.BDSNR_Noise				= ui.checkBox_TimeSecCht_BDSNR_drawNoisePt->isChecked();
	paintSetting.BDSNR_ConstrainPt			= ui.checkBox_TimeSecCht_BDSNR_drawConstrainPt->isChecked();
	paintSetting.BDSNR_EffectSubPt			= ui.checkBox_TimeSecCht_BDSNR_drawSubPt->isChecked();
	paintSetting.BDSNR_ActiveFilter			= ui.checkBox_TimeSecCht_BDSNR_drawFilter->isChecked();
	paintSetting.BDSNR_ActiveFilter_Main	= ui.checkBox_TimeSecCht_BDSNR_drawFilterMain->isChecked();

	paintSetting.VibState_transferOnly = ui.radioButton_VibState_transferState->isChecked();

	paintSetting.VibState_NotTransfer	= ui.checkBox_VibState_Paint_NotTransfer->isChecked();
	paintSetting.VibState_Atk			= ui.checkBox_VibState_Paint_Atk->isChecked();
	paintSetting.VibState_Increase		= ui.checkBox_VibState_Paint_Increase->isChecked();
	paintSetting.VibState_Sustain		= ui.checkBox_VibState_Paint_Sustain->isChecked();
	paintSetting.VibState_Decrease		= ui.checkBox_VibState_Paint_Decrease->isChecked();

	

	m_pTimeSecCht->setPaintSetting(paintSetting);
}

void EffSigBuffWgt::slot_getNewSTFTData(QString dataKey)
{
	const ST_STFTOutputData& data = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	if (data.vecOutput.isEmpty())
	{
		qDebug() << "EffSigBuffWgt::slot_getSTFTData : dataVec Empty!";
		return;
	}
	m_STFTDataKey = data.DatacenterName;
	m_dataPara = data.InputPara;

	updateSTFTLabel(data);
	updateSTFTPanel(data);

	m_pSTFTHotCht->setSTFTResultPara(data.InputPara);
	m_pSTFTHotCht->setCurrentFrameIndex(0);

}

void EffSigBuffWgt::slot_AutoGenEffSigBuffData(QString dataKey)
{
	ui.tabWidget_EffSigBuffPannel->setCurrentIndex(0);
	slot_GenVibStateRelBtnClicked();
}

void EffSigBuffWgt::slot_updateHotChtBtnClicked()
{
	QTime startTime = ui.timeEdit_hotChtStartTime->time();
	int   WndMsecLength = ui.SBox_hotChtTimeLength->value();
	int   startFreq = ui.SBox_HotChtStartFreq->value();
	int   endFreq = ui.SBox_HotchtEndFreq->value();
	int   startDb = ui.SBox_HotCht_StartDB->value();
	int   endDb = ui.SBox_HotCht_EndDB->value();
	int   BarBandWidth = ui.SBox_HotChtFreqBandWidth->value();
	int   BarTimeLength = ui.SBox_HotChtTimeIntervalMsec->value();

	m_pSTFTHotCht->setFreqRange(startFreq, endFreq);
	m_pSTFTHotCht->setTimeRange(startTime, WndMsecLength);
	m_pSTFTHotCht->setDbRange(startDb, endDb);
	m_pSTFTHotCht->setFreqBandWidth(BarBandWidth);
	m_pSTFTHotCht->setTimeInterval(BarTimeLength);
	m_pSTFTHotCht->resetColorRect(m_STFTDataKey);
}

void EffSigBuffWgt::slot_GenVibStateRelBtnClicked()
{

	ST_VibrateStateThreshHold threshHold;
	threshHold.AttackMinRatio	= ui.DSBox_AtkMinRatio->value() / 100.0;
	threshHold.SustainMaxRatio	= ui.DSBox_SusMaxRatio->value() / 100.0;
	threshHold.SustainMinRatio	= ui.DSBox_SusMinRatio->value() / 100.0;

	double AttackMinRatio_DB = AudioProtocol::getRelativeDB(threshHold.AttackMinRatio + 1.0, 1);
	ui.label_AtkMinRatio_DBVal->setText(QString("剧烈上升最小DB增幅：%1").arg(AttackMinRatio_DB, 0, 'f', 1));

	double SustainMaxRatio_DB = AudioProtocol::getRelativeDB(threshHold.SustainMaxRatio + 1.0, 1);
	ui.label_SusMaxRatio_DBVal->setText(QString("小波动最大DB增幅：%1").arg(SustainMaxRatio_DB, 0, 'f', 1));

	double SustainMinRatio_DB = AudioProtocol::getRelativeDB(threshHold.SustainMinRatio + 1.0, 1);
	ui.label_SusMinRatio_DBVal->setText(QString("小波动最大DB降幅：%1").arg(SustainMinRatio_DB, 0, 'f', 1));

	bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, m_STFTDataKey);

	if (dataExist)
	{
		VibrateStateRelvanceNetwork::instance()->slot_StartBandWidthFilterConstrainData(m_STFTDataKey, threshHold);
	}

}

void EffSigBuffWgt::slot_updateTimeSecChtBtnClicked()
{

	m_nUpdateMsec = ui.SBox_UpdateTimer->value();

	ST_TimeSecChtDataRange dataRange;
	dataRange.minFreq	= ui.SBox_TimeSecCht_minFreq->value();
	dataRange.maxFreq	= ui.SBox_TimeSecCht_maxFreq->value();
	dataRange.minDB		= ui.SBox_TimeSecCht_minDB->value();
	dataRange.maxDB		= ui.SBox_TimeSecCht_maxDB->value();

	m_pTimeSecCht->setDataRange(dataRange);
	m_pTimeSecCht->resetTimeSecChtRect(m_STFTDataKey, m_dataPara);

}

void EffSigBuffWgt::slot_play()
{
	AudioEngine::instance()->slot_startPlay();
	m_nCurrentTimeUpCount = 0;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
	resetFrameRateState();

}

void EffSigBuffWgt::slot_jump()
{
	int		frameIndex = ui.HSlider_TimeFrameIndex->value();
	double	frameInterval = m_dataPara.GapInTimeLength;
	int		frameStartMsec = frameIndex * frameInterval * 1000;

	QTime frameStartTime = QTime(0, 0, 0).addMSecs(frameStartMsec);
	AudioEngine::instance()->slot_jump(frameStartTime);

	m_nCurrentTimeUpCount = frameStartMsec / m_nUpdateMsec;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
	resetFrameRateState();
}

void EffSigBuffWgt::slot_stop()
{
	AudioEngine::instance()->slot_stopPlay();
	m_pUpdateSectionTimer->stop();
}


