#include "BandWidthInputWgt.h"
#pragma execution_character_set("utf-8")


BandWidthInputWgt::BandWidthInputWgt(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	initUI();
	initUpdateTimer();
}

BandWidthInputWgt::~BandWidthInputWgt()
{}

void BandWidthInputWgt::initUI()
{
	connect(ui.btn_updateTimeSecCht, &QPushButton::clicked, this, &BandWidthInputWgt::slot_updateTimeSecChtBtnClicked);
	connect(ui.btn_updateHotCht, &QPushButton::clicked, this, &BandWidthInputWgt::slot_updateHotChtBtnClicked);
	connect(ui.btn_BandWidthInputNet_GenResult, &QPushButton::clicked, this, &BandWidthInputWgt::slot_GenBandWidthInputDataBtnClicked);

	connect(ui.HSlider_TimeFrameIndex, &QAbstractSlider::valueChanged, this, &BandWidthInputWgt::slot_TimeFrameSliderMoved);

	connect(ui.btn_play, &QPushButton::clicked, this, &BandWidthInputWgt::slot_play);
	connect(ui.btn_jump, &QPushButton::clicked, this, &BandWidthInputWgt::slot_jump);
	connect(ui.btn_stop, &QPushButton::clicked, this, &BandWidthInputWgt::slot_stop);

	connect(ui.btn_lastFrame, &QPushButton::clicked, this, &BandWidthInputWgt::slot_btnLastFrameClicked);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &BandWidthInputWgt::slot_btnNextFrameClicked);

	connect(DataCenterManager::instance(), &DataCenterManager::sgn_STFTDataSaved, this, &BandWidthInputWgt::slot_getNewSTFTData);
	//connect(DataCenterManager::instance(), &DataCenterManager::sgn_DiffDataSaved, this, &BandWidthInputWgt::slotDiffResultGet);

	m_pBtnGroup_getDiffData = new QButtonGroup(this);
	m_pBtnGroup_getDiffData->setExclusive(true);
	m_pBtnGroup_getDiffData->addButton(ui.radioButton_getData_GoTimeSecCht);
	//m_pBtnGroup_getDiffData->addButton(ui.radioButton_getDiffNetData_GoTimeSecCht);
	ui.radioButton_getData_GoTimeSecCht->setChecked(true);

	//ui.comboBox_TimeSecChtBarType->setItemData(0, QVariant((int)EN_BDI_TimeSecChtBarType::STFT));
	//ui.comboBox_TimeSecChtBarType->setItemData(1, QVariant((int)EN_BDI_TimeSecChtBarType::EffectiveOscillation));
	//ui.comboBox_TimeSecChtBarType->setItemData(2, QVariant((int)EN_BDI_TimeSecChtBarType::BDSNR));
	//ui.comboBox_TimeSecChtBarType->setItemData(3, QVariant((int)EN_BDI_TimeSecChtBarType::DiffGroup));

	connect(ui.comboBox_TimeSecChtBarType, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) { slot_TimeSecChtTypeChanged(); });
	slot_TimeSecChtTypeChanged();

}

void BandWidthInputWgt::initUpdateTimer()
{
	m_pUpdateSectionTimer = new QTimer(this);
	m_pUpdateSectionTimer->setSingleShot(false);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	connect(m_pUpdateSectionTimer, &QTimer::timeout, this, &BandWidthInputWgt::slot_updateTimerTimeUp);

}

void BandWidthInputWgt::init()
{
	m_pSTFTHotCht = new FFT_Chart_STFTHotGram(this);
	m_pSTFTHotCht->setTitleText(QString("STFT Hot Cht"));
	ui.VLayout_STFT_Cht_HotCht->insertWidget(0, m_pSTFTHotCht);
	connect(m_pSTFTHotCht, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &BandWidthInputWgt::slot_updateHotChtGenState);


	//m_pBDITimeSecCht = new TimeSecCht_BandWidthInput(this);
	//m_pBDITimeSecCht->setTitleText(QString("Diff Relevance TimeSec Cht"));
	//ui.HLayout_TimeSecCht->insertWidget(0, m_pBDITimeSecCht);
	//connect(m_pBDITimeSecCht, &TimeSecCht_BandWidthInput::sgn_SecRectGenerateState, this, &BandWidthInputWgt::slot_updateTimeSecGenState);
}

void BandWidthInputWgt::updateSTFTLabel(const ST_STFTOutputData& data)
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

void BandWidthInputWgt::updateSTFTPanel(const ST_STFTOutputData& data)
{
	int maxFrameIndex = data.vecOutput.size() - 1;
	ui.HSlider_TimeFrameIndex->setMinimum(0);
	ui.HSlider_TimeFrameIndex->setMaximum(maxFrameIndex);
}

void BandWidthInputWgt::updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime)
{
	ui.label_TimeFrameTime->setText(QString("截面时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));
	ui.label_TimeSecCht_FrameCenterTime->setText(QString("截面中心时间：%1").arg(FrameMidTime.toString("mm:ss.zzz")));
}

void BandWidthInputWgt::resetFrameRateState()
{
	m_TimeFrameRateStatStartSysTime = QTime::currentTime();
	m_nStatFrameRateStartFrameIndex = ui.HSlider_TimeFrameIndex->value();
}

void BandWidthInputWgt::updateFrameRateState()
{
	int MsecCost = m_TimeFrameRateStatStartSysTime.msecsTo(QTime::currentTime());
	int FrameCost = ui.HSlider_TimeFrameIndex->value() - m_nStatFrameRateStartFrameIndex;
	double AvrMsecPerFrame = (double)MsecCost / (double)FrameCost;
	double FrameRate = 1000.0 / AvrMsecPerFrame;
	ui.label_TimeSecCht_AvrSecFrameRate->setText(QString("平均帧率：%1").arg(FrameRate, 0, 'f', 2));
}

void BandWidthInputWgt::slot_TimeFrameSliderMoved(int newVal)
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

	//m_pBDITimeSecCht->setCurrentFrameIndex(newVal);

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

void BandWidthInputWgt::slot_updateTimerTimeUp()
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

void BandWidthInputWgt::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
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

void BandWidthInputWgt::slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_TimeSec_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_TimeSecGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_TimeSecGenState->setText(QString("生成结束"));
	}

}

void BandWidthInputWgt::slot_getBandWidthInputNetMsg(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_BandWidthInputNet_GenResult->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_BandWidthInputNet_GenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_BandWidthInputNet_GenState->setText(QString("生成结束"));
	}
}

void BandWidthInputWgt::slotBandWidthInputResultGet(QString DataKey)
{
	//bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterDataType::Diff, m_STFTDataKey);

	//if (!dataExist)
	//{
	//	return;
	//}

	//const ST_DiffNetOutput& DiffData = DataCenterManager::instance()->getDiffOutputMap().find(m_STFTDataKey).value();
	//ui.label_EndGroupStartRatio->setText(QString("最后一组起始比例（%）：%1").arg(DiffData.DiffNetState.SideStartRatio * 100, 0, 'f', 2));

	//if (ui.radioButton_getDiffNetData_GoTimeSecCht->isChecked())
	//{
	//	slot_updateHotChtBtnClicked();
	//	ui.tabWidget_DiffNetPannel->setCurrentIndex(1);
	//	slot_updateTimeSecChtBtnClicked();
	//}
	//else
	//{
	//	emit sgn_GoFreqDoubleResult(m_STFTDataKey);
	//}
}


void BandWidthInputWgt::slot_btnNextFrameClicked()
{
	if (ui.HSlider_TimeFrameIndex->value() < ui.HSlider_TimeFrameIndex->maximum())
	{
		int newVal = ui.HSlider_TimeFrameIndex->value() + 1;
		ui.HSlider_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}
void BandWidthInputWgt::slot_btnLastFrameClicked()
{
	if (ui.HSlider_TimeFrameIndex->value() > 0)
	{
		int newVal = ui.HSlider_TimeFrameIndex->value() - 1;
		ui.HSlider_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}

void BandWidthInputWgt::slot_TimeSecChtTypeChanged()
{
	//EN_BDI_TimeSecChtBarType currentType = (EN_BDI_TimeSecChtBarType)ui.comboBox_TimeSecChtBarType->currentData().toInt();
	//m_pBDITimeSecCht->setChtType(currentType);
}

void BandWidthInputWgt::slot_getNewSTFTData(QString dataKey)
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

	//m_pBDITimeSecCht->setSTFTResultPara(data.InputPara);
	//m_pBDITimeSecCht->setCurrentFrameIndex(0);

	m_pSTFTHotCht->setSTFTResultPara(data.InputPara);
	m_pSTFTHotCht->setCurrentFrameIndex(0);

}

void BandWidthInputWgt::slot_AutoGenBandWidthInputData(QString dataKey)
{
	ui.tabWidget_DiffNetPannel->setCurrentIndex(0);
	slot_GenBandWidthInputDataBtnClicked();
}

void BandWidthInputWgt::slot_updateHotChtBtnClicked()
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

void BandWidthInputWgt::slot_GenBandWidthInputDataBtnClicked()
{
	/*ST_DiffNetPara para;
	para.bidirectionalGroupCount = ui.SBox_BidirectGroupCount->value();
	para.BidirectionGroupStartInterval = ui.DSBox_BidirectGroupStartInterval->value() / 100.0;

	if (ui.radioButton_BidirectGroupIntervalType_Same->isChecked())
	{
		para.IntervalType = EN_DiffNetGroupIntervalType::Same;
	}
	else if (ui.radioButton_BidirectGroupIntervalType_double->isChecked())
	{
		para.IntervalType = EN_DiffNetGroupIntervalType::Double;
	}

	if (ui.radioButton_DiffNetEffectPtType_STFT->isChecked())
	{
		para.EffPtType = EN_DiffNetPtEffectType::STFT;
	}
	else if (ui.radioButton_DiffNetEffectPtType_EFFOsc->isChecked())
	{
		para.EffPtType = EN_DiffNetPtEffectType::EffOsc;
	}
	else if (ui.radioButton_DiffNetEffectPtType_BDSNR->isChecked())
	{
		para.EffPtType = EN_DiffNetPtEffectType::BDSNR;
	}

	bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterDataType::STFTOutputData, m_STFTDataKey);

	if (!dataExist)
	{
		return;
	}

	AudioDiffNet::instance()->slot_StartGenDiffResult(para, m_STFTDataKey);*/

}

void BandWidthInputWgt::slot_updateTimeSecChtBtnClicked()
{
	//int showMinFreq = ui.SBox_OscSep_TimeSec_startFreq->value();
	//int showMaxFreq = ui.SBox_OscSep_TimeSec_endFreq->value();
	//int dbMinVal = ui.SBox_Diff_TimeSec_StartDB->value();
	//int dbMaxVal = ui.SBox_Diff_TimeSec_EndDB->value();
	//int FreqBarBandWidth = ui.SBox_OscSep_TimeSec_BarBandWidth->value();
	m_nUpdateMsec = ui.SBox_Diff_UpdateTimer->value();

	//m_pBDITimeSecCht->setFreqBarBandWidth(FreqBarBandWidth);
	//m_pBDITimeSecCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pBDITimeSecCht->setDrawDBRange(dbMinVal, dbMaxVal);
	//m_pBDITimeSecCht->resetFrameRect(m_STFTDataKey);

}

void BandWidthInputWgt::slot_play()
{
	AudioEngine::instance()->slot_startPlay();
	m_nCurrentTimeUpCount = 0;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
	resetFrameRateState();

}

void BandWidthInputWgt::slot_jump()
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

void BandWidthInputWgt::slot_stop()
{
	AudioEngine::instance()->slot_stopPlay();
	m_pUpdateSectionTimer->stop();
}

