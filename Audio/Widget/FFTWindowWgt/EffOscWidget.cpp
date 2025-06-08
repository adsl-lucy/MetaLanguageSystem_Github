#include "EffOscWidget.h"

#pragma execution_character_set("utf-8")

EffOscWidget::EffOscWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);	
	init();
	initUI();
	initUpdateTimer();
}

EffOscWidget::~EffOscWidget()
{}


void EffOscWidget::initUI()
{
	connect(ui.btn_updateTimeSecCht, &QPushButton::clicked, this, &EffOscWidget::slot_updateTimeSecChtBtnClicked);
	connect(ui.btn_updateHotCht, &QPushButton::clicked, this, &EffOscWidget::slot_updateHotChtBtnClicked);
	connect(ui.btn_WndSpecConstrain_GenResult, &QPushButton::clicked, this, &EffOscWidget::slot_GenWndSpecConstrainBtnClicked);

	connect(ui.HSlider_OscSep_TimeFrameIndex, &QAbstractSlider::valueChanged, this, &EffOscWidget::slot_TimeFrameSliderMoved);

	connect(ui.btn_play, &QPushButton::clicked, this, &EffOscWidget::slot_play);
	connect(ui.btn_jump, &QPushButton::clicked, this, &EffOscWidget::slot_jump);
	connect(ui.btn_stop, &QPushButton::clicked, this, &EffOscWidget::slot_stop);

	connect(ui.btn_lastFrame, &QPushButton::clicked, this, &EffOscWidget::slot_btnLastFrameClicked);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &EffOscWidget::slot_btnNextFrameClicked);

	connect(DataCenterManager::instance(), &DataCenterManager::sgn_STFTDataSaved, this, &EffOscWidget::slot_getNewSTFTData);
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_WndFFTGenState, this, &EffOscWidget::slot_getFFTWindowManagerMsg);
	connect(WndSpecConstrainNetwork::instance(), &WndSpecConstrainNetwork::sgn_WndSpecConstrainGenState, this, &EffOscWidget::slot_updateWndSepcConstrainGenState);
	connect(DataCenterManager::instance(), &DataCenterManager::sgn_WndConstrainDataSaved, this, &EffOscWidget::slotWndConstrainResultGet);

	m_pBtnGroup_getWndSpecConstraindata = new QButtonGroup(this);	
	m_pBtnGroup_getWndSpecConstraindata->addButton(ui.radioButton_getWndConstrainData_UpdateCht);
	m_pBtnGroup_getWndSpecConstraindata->addButton(ui.radioButton_getWndConstrainData_GoBDSNR);
	m_pBtnGroup_getWndSpecConstraindata->setExclusive(true);
	ui.radioButton_getWndConstrainData_GoBDSNR->setChecked(true);

	m_pBtnGroup_TimeSecChtShowType = new QButtonGroup(this);
	m_pBtnGroup_TimeSecChtShowType->addButton(ui.radioButton_TimeSecCht_STFT, 0);
	m_pBtnGroup_TimeSecChtShowType->addButton(ui.radioButton_TimeSecCht_WndSepcConstrain, 1);
	m_pBtnGroup_TimeSecChtShowType->setExclusive(true);
	connect(m_pBtnGroup_TimeSecChtShowType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_TimeSecChtTypeChanged(); });
	ui.radioButton_TimeSecCht_WndSepcConstrain->setChecked(true);
	slot_TimeSecChtTypeChanged();

	m_pBtnGroup_NoiseDrawSet = new QButtonGroup(this);
	m_pBtnGroup_NoiseDrawSet->setExclusive(false);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_drawTIQLine);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_drawUnderTIQBar);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_drawWndSpecNoise);
	connect(m_pBtnGroup_NoiseDrawSet, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) { slot_NoiseBtnGroupClicked(); });
	slot_NoiseBtnGroupClicked();

}

void EffOscWidget::initUpdateTimer()
{
	m_pUpdateSectionTimer = new QTimer(this);
	m_pUpdateSectionTimer->setSingleShot(false);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	connect(m_pUpdateSectionTimer, &QTimer::timeout, this, &EffOscWidget::slot_updateTimerTimeUp);

}

void EffOscWidget::init()
{
	m_pSTFTHotCht = new FFT_Chart_STFTHotGram(this);
	m_pSTFTHotCht->setTitleText(QString("STFT Hot Cht"));
	ui.VLayout_STFT_Cht_HotCht->insertWidget(0, m_pSTFTHotCht);
	connect(m_pSTFTHotCht, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &EffOscWidget::slot_updateHotChtGenState);


	//m_pEffOscTimeSecCht = new EffOscTimeSecCht(this);
	//m_pEffOscTimeSecCht->setTitleText(QString("Effective Oscillation TimeSec Cht"));
	//ui.HLayout_EffOsc_TimeSecCht->insertWidget(0, m_pEffOscTimeSecCht);
	//connect(m_pEffOscTimeSecCht, &EffOscTimeSecCht::sgn_SecRectGenerateState, this, &EffOscWidget::slot_updateTimeSecGenState);

	m_pTimeSecCht = new TimeSecCht_Wgt(this);
	ui.HLayout_EffOsc_TimeSecCht->insertWidget(0, m_pTimeSecCht);
	connect(m_pTimeSecCht, &TimeSecCht_Wgt::sgn_SecRectGenerateState, this, &EffOscWidget::slot_updateTimeSecGenState);

	ST_TimeSecChtGenSetting TimeSecChtGenSetting;
	TimeSecChtGenSetting.Gen_STFT = true;
	TimeSecChtGenSetting.Gen_EffOsc = true;
	TimeSecChtGenSetting.Gen_BDSNR = false;
	TimeSecChtGenSetting.Gen_VibState = false;
	m_pTimeSecCht->setGenType(TimeSecChtGenSetting);

}

void EffOscWidget::updateSTFTLabel(const ST_STFTOutputData& data)
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

void EffOscWidget::updateSTFTPanel(const ST_STFTOutputData& data)
{
	int maxFrameIndex = data.vecOutput.size() - 1;
	ui.HSlider_OscSep_TimeFrameIndex->setMinimum(0);
	ui.HSlider_OscSep_TimeFrameIndex->setMaximum(maxFrameIndex);
}

void EffOscWidget::updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime)
{
	ui.label_OscSep_TimeFrameTime->setText(QString("截面时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));
	ui.label_OscSep_Frame_CenterTime->setText(QString("截面中心时间：%1").arg(FrameMidTime.toString("mm:ss.zzz")));
}

void EffOscWidget::resetFrameRateState()
{
	m_TimeFrameRateStatStartSysTime = QTime::currentTime();
	m_nStatFrameRateStartFrameIndex = ui.HSlider_OscSep_TimeFrameIndex->value();
}

void EffOscWidget::updateFrameRateState()
{
	int MsecCost = m_TimeFrameRateStatStartSysTime.msecsTo(QTime::currentTime());
	int FrameCost = ui.HSlider_OscSep_TimeFrameIndex->value() - m_nStatFrameRateStartFrameIndex;
	double AvrMsecPerFrame = (double)MsecCost / (double)FrameCost;
	double FrameRate = 1000.0 / AvrMsecPerFrame;
	ui.label_OscSep_Avr_SecFrameRate->setText(QString("平均帧率：%1").arg(FrameRate, 0, 'f', 2));
}

void EffOscWidget::slot_TimeFrameSliderMoved(int newVal)
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

	//m_pEffOscTimeSecCht->setCurrentFrameIndex(newVal);
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

void EffOscWidget::slot_updateTimerTimeUp()
{
	updateFrameRateState();
	double frameMsec = m_nCurrentTimeUpCount * m_nUpdateMsec;
	double frameInterval = m_dataPara.GapInTimeLength * 1000;
	int frameIndex = frameMsec / frameInterval;
	int maxFrame = ui.HSlider_OscSep_TimeFrameIndex->maximum();
	if (frameIndex > maxFrame)
	{
		qDebug() << QString("OscillationSeparatorWgt::slot_updateTimerTimeUp : stop");
		m_pUpdateSectionTimer->stop();
		ui.HSlider_OscSep_TimeFrameIndex->setValue(maxFrame);
		slot_TimeFrameSliderMoved(maxFrame);
	}
	else
	{
		QString currentTime = QTime::currentTime().toString("mm:ss.zzz");
		qDebug() << QString("OscillationSeparatorWgt::slot_updateTimerTimeUp : show msec %1 : frameindex : %2 realTime %3").arg(frameMsec).arg(frameIndex).arg(currentTime);
		ui.HSlider_OscSep_TimeFrameIndex->setValue(frameIndex);
		slot_TimeFrameSliderMoved(frameIndex);
		m_nCurrentTimeUpCount += 1;
	}

}

void EffOscWidget::slot_getFFTWindowManagerMsg(int percentage, int threadCount, QString msg)
{
	ui.progressBar_WndSpecConstrain_GenResult->setValue(percentage);
	ui.label_WndSpecConstrainGenState->setText(QString("生成状态：活跃线程 %1 %2").arg(threadCount).arg(msg));
}

void EffOscWidget::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
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

void EffOscWidget::slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_OscSep_TimeSec_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_TimeSecGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_TimeSecGenState->setText(QString("生成结束"));
	}

}

void EffOscWidget::slot_updateWndSepcConstrainGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_WndSpecConstrain_GenResult->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_WndSpecConstrainGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_WndSpecConstrainGenState->setText(QString("生成结束"));
	}
}

void EffOscWidget::slotWndConstrainResultGet()
{
	bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, m_STFTDataKey);

	if (!dataExist)
	{
		return;
	}

	const ST_WndSpecConstrainResult& WndSpecConstrainResult = DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(m_STFTDataKey).value();
	ui.label_constrainSidePtCount->setText(QString("窗函数频谱抑制边缘点个数：%1").arg(WndSpecConstrainResult.WndConstrainPara.ConstrainSidePtCount));

	if (ui.radioButton_getWndConstrainData_UpdateCht->isChecked())
	{
		slot_updateHotChtBtnClicked();
		ui.tabWidget_OscSepPannel->setCurrentIndex(1);
		slot_updateTimeSecChtBtnClicked();
	}
	else
	{
		emit sgn_GoBDSNRResult(m_STFTDataKey);
	}
}

void EffOscWidget::slot_NoiseBtnGroupClicked()
{
	//bool drawTIQLine = ui.checkBox_drawTIQLine->isChecked();
	//bool drawUnderTIQBar = ui.checkBox_drawUnderTIQBar->isChecked();
	//bool drawWndSpecNoise = ui.checkBox_drawWndSpecNoise->isChecked();

	//m_pEffOscTimeSecCht->setNoisePaintSetting(drawTIQLine, drawWndSpecNoise, drawUnderTIQBar);

	ST_TimeSecChtPaintSetting paintSetting;
	paintSetting.EffOsc_UnderTIQBar = ui.checkBox_drawUnderTIQBar->isChecked();
	paintSetting.EffOsc_TIQLine = ui.checkBox_drawTIQLine->isChecked();
	paintSetting.EffOsc_WndSepcNoise = ui.checkBox_drawWndSpecNoise->isChecked();

	m_pTimeSecCht->setPaintSetting(paintSetting);
}

void EffOscWidget::slot_btnNextFrameClicked()
{
	if (ui.HSlider_OscSep_TimeFrameIndex->value() < ui.HSlider_OscSep_TimeFrameIndex->maximum())
	{
		int newVal = ui.HSlider_OscSep_TimeFrameIndex->value() + 1;
		ui.HSlider_OscSep_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}
void EffOscWidget::slot_btnLastFrameClicked()
{
	if (ui.HSlider_OscSep_TimeFrameIndex->value() > 0)
	{
		int newVal = ui.HSlider_OscSep_TimeFrameIndex->value() - 1;
		ui.HSlider_OscSep_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}

void EffOscWidget::slot_TimeSecChtTypeChanged()
{
	if (ui.radioButton_TimeSecCht_STFT->isChecked())
	{
		m_pTimeSecCht->setPaintType(EN_TimeSecCht_PaintType::STFT);
	}
	else if (ui.radioButton_TimeSecCht_WndSepcConstrain->isChecked())
	{
		m_pTimeSecCht->setPaintType(EN_TimeSecCht_PaintType::EffOsc);
	}
}

void EffOscWidget::slot_getNewSTFTData(QString dataKey)
{
	const ST_STFTOutputData& data = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	if (data.vecOutput.isEmpty())
	{
		qDebug() << "OscillationSeparatorWgt::slot_getSTFTData : dataVec Empty!";
		return;
	}
	m_STFTDataKey = data.DatacenterName;
	m_dataPara = data.InputPara;

	updateSTFTLabel(data);
	updateSTFTPanel(data);

	//m_pEffOscTimeSecCht->setSTFTResultPara(data.InputPara);
	//m_pEffOscTimeSecCht->setCurrentFrameIndex(0);

	m_pSTFTHotCht->setSTFTResultPara(data.InputPara);
	m_pSTFTHotCht->setCurrentFrameIndex(0);

}

void EffOscWidget::slot_updateHotChtBtnClicked()
{
	QTime startTime = ui.timeEdit_hotChtStartTime->time();
	int   WndMsecLength = ui.SBox_hotChtTimeLength->value();
	int   startFreq = ui.SBox_HotChtStartFreq->value();
	int   endFreq = ui.SBox_HotchtEndFreq->value();
	int   startDb = ui.SBox_ADSR_HotCht_StartDB->value();
	int   endDb = ui.SBox_ADSR_HotCht_EndDB->value();
	int   BarBandWidth = ui.SBox_HotChtFreqBandWidth->value();
	int   BarTimeLength = ui.SBox_HotChtTimeIntervalMsec->value();

	m_pSTFTHotCht->setFreqRange(startFreq, endFreq);
	m_pSTFTHotCht->setTimeRange(startTime, WndMsecLength);
	m_pSTFTHotCht->setDbRange(startDb, endDb);
	m_pSTFTHotCht->setFreqBandWidth(BarBandWidth);
	m_pSTFTHotCht->setTimeInterval(BarTimeLength);
	m_pSTFTHotCht->resetColorRect(m_STFTDataKey);
}

void EffOscWidget::slot_GenWndSpecConstrainBtnClicked()
{
	ST_WndSpecConstrainPara WndSpecConsstrainPara;
	WndSpecConsstrainPara.ConstrainDBRange = ui.SBox_MaxConstrainDbPos->value();
	WndSpecConsstrainPara.startEnhanceSidePos = ui.SBox__EnheaceConstrainPos->value();
	WndSpecConsstrainPara.EnhanceRatio = ui.DSbox_EnhanceConstrainRatio->value() / 100;
	WndSpecConsstrainPara.PeakValDriftRatio = ui.DSBox_PeakFreqDriftRatio->value() / 100;
	WndSpecConsstrainPara.isForcePt2DBVal = ui.checkBox_forcePt2DBVal->isChecked();
	if (WndSpecConsstrainPara.isForcePt2DBVal)
	{
		WndSpecConsstrainPara.forcePt2DBVal = ui.DSBox_forcePt2DBVal->value();
	}

	WndSpecConsstrainPara.WndPara = m_dataPara.WndPara;

	if (WndSpecConsstrainPara.WndPara.pointCount <= 0)
	{
		return;
	}

	bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, m_STFTDataKey);

	if (!dataExist)
	{
		return;
	}

	WndSpecConstrainNetwork::instance()->slot_StartGenWndSpecConstrainResult(m_STFTDataKey, WndSpecConsstrainPara);

}

void EffOscWidget::slot_updateTimeSecChtBtnClicked()
{
	//int showMinFreq = ui.SBox_OscSep_TimeSec_startFreq->value();
	//int showMaxFreq = ui.SBox_OscSep_TimeSec_endFreq->value();
	//int dbMinVal = ui.SBox_OscSep_TimeSec_StartDB->value();
	//int dbMaxVal = ui.SBox_OscSep_TimeSec_EndDB->value();
	//int FreqBarBandWidth = ui.SBox_OscSep_TimeSec_BarBandWidth->value();
	m_nUpdateMsec = ui.SBox_OscSep_UpdateTimer->value();

	////m_pOscSepTimeSecCht->setFreqBarBandWidth(FreqBarBandWidth);
	//m_pEffOscTimeSecCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pEffOscTimeSecCht->setDrawDBRange(dbMinVal, dbMaxVal);
	//m_pEffOscTimeSecCht->resetFrameRect(m_STFTDataKey);

	ST_TimeSecChtDataRange dataRange;
	dataRange.minFreq = ui.SBox_OscSep_TimeSec_startFreq->value();
	dataRange.maxFreq = ui.SBox_OscSep_TimeSec_endFreq->value();
	dataRange.minDB = ui.SBox_OscSep_TimeSec_StartDB->value();
	dataRange.maxDB = ui.SBox_OscSep_TimeSec_EndDB->value();

	m_pTimeSecCht->setDataRange(dataRange);
	m_pTimeSecCht->resetTimeSecChtRect(m_STFTDataKey, m_dataPara);

}

void EffOscWidget::slot_play()
{
	AudioEngine::instance()->slot_startPlay();
	m_nCurrentTimeUpCount = 0;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
	resetFrameRateState();

}

void EffOscWidget::slot_jump()
{
	int		frameIndex = ui.HSlider_OscSep_TimeFrameIndex->value();
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

void EffOscWidget::slot_stop()
{
	AudioEngine::instance()->slot_stopPlay();
	m_pUpdateSectionTimer->stop();
}