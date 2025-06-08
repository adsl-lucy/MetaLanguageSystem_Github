#include "FreqDoubChtPanelWgt.h"
#pragma execution_character_set("utf-8")

FreqDoubChtPanelWgt::FreqDoubChtPanelWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	initUI();
	initUpdateTimer();
}

FreqDoubChtPanelWgt::~FreqDoubChtPanelWgt()
{
}


void FreqDoubChtPanelWgt::initUI()
{
	connect(ui.btn_updateTimeSecCht, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_updateTimeSecChtBtnClicked);
	connect(ui.btn_updateHotCht, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_updateHotChtBtnClicked);
	connect(ui.btn_FreqDoubNet_GenResult, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_GenFreqDoubDataBtnClicked);

	connect(FreqDoubleNetwork::instance(), &FreqDoubleNetwork::sgn_FDN_GenState, this, &FreqDoubChtPanelWgt::slot_getFreqDoubNetMsg);
	connect(DataCenterManager::instance(), &DataCenterManager::sgn_FreqDoubDataSaved, this, &FreqDoubChtPanelWgt::slotFreqDoubResultGet);

	connect(ui.HSlider_OscSep_TimeFrameIndex, &QAbstractSlider::valueChanged, this, &FreqDoubChtPanelWgt::slot_TimeFrameSliderMoved);

	connect(ui.btn_play, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_play);
	connect(ui.btn_jump, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_jump);
	connect(ui.btn_stop, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_stop);

	connect(ui.btn_lastFrame, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_btnLastFrameClicked);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &FreqDoubChtPanelWgt::slot_btnNextFrameClicked);

	m_pBtnGroup_getFreqDoubData = new QButtonGroup(this);
	m_pBtnGroup_getFreqDoubData->setExclusive(false);
	m_pBtnGroup_getFreqDoubData->addButton(ui.radioButton_getFreqDoubtData_GoTimeSecCht);
	m_pBtnGroup_getFreqDoubData->setExclusive(true);

	//ui.comboBox_TimeSecChtBarType->setItemData(0, QVariant((int)EN_FreqDoub_TimeSecChtBarType::STFT));
	//ui.comboBox_TimeSecChtBarType->setItemData(1, QVariant((int)EN_FreqDoub_TimeSecChtBarType::EffectiveOscillation));
	//ui.comboBox_TimeSecChtBarType->setItemData(2, QVariant((int)EN_FreqDoub_TimeSecChtBarType::BDSNR));
	//ui.comboBox_TimeSecChtBarType->setItemData(3, QVariant((int)EN_FreqDoub_TimeSecChtBarType::DiffGroup));
	//ui.comboBox_TimeSecChtBarType->setItemData(4, QVariant((int)EN_FreqDoub_TimeSecChtBarType::FreqDoub));

	connect(ui.comboBox_TimeSecChtBarType, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) { slot_TimeSecChtTypeChanged(); });
	slot_TimeSecChtTypeChanged();

	ui.comboBox_MatrixSource_Active->setItemData(0, QVariant((int)EN_FMTSourceType::EffOsc));
	ui.comboBox_MatrixSource_Active->setItemData(1, QVariant((int)EN_FMTSourceType::BDSNR));

	ui.comboBox_MatrixSource_Search->setItemData(0, QVariant((int)EN_FMTSourceType::EffOsc));
	ui.comboBox_MatrixSource_Search->setItemData(1, QVariant((int)EN_FMTSourceType::BDSNR));

	m_pBtnGroup_NoiseDrawSet = new QButtonGroup(this);
	m_pBtnGroup_NoiseDrawSet->setExclusive(false);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawTIQLine);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawUnderTIQBar);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawWndSpecNoise);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNRNoisePt);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNRConstrainPt);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNRActiveFilter);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawFreqDoubChild);
	connect(m_pBtnGroup_NoiseDrawSet, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) { slot_NoiseBtnGroupClicked(); });
	slot_NoiseBtnGroupClicked();

}

void FreqDoubChtPanelWgt::initUpdateTimer()
{
	m_pUpdateSectionTimer = new QTimer(this);
	m_pUpdateSectionTimer->setSingleShot(false);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	connect(m_pUpdateSectionTimer, &QTimer::timeout, this, &FreqDoubChtPanelWgt::slot_updateTimerTimeUp);

}

void FreqDoubChtPanelWgt::init()
{
	m_pSTFTHotCht = new FFT_Chart_STFTHotGram(this);
	m_pSTFTHotCht->setTitleText(QString("STFT Hot Cht"));
	ui.VLayout_STFT_Cht_HotCht->insertWidget(0, m_pSTFTHotCht);
	connect(m_pSTFTHotCht, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &FreqDoubChtPanelWgt::slot_updateHotChtGenState);


	//m_pFreqDoubTimeSecCht = new TimeSecCht_FreqDoub(this);
	//m_pFreqDoubTimeSecCht->setTitleText(QString("Freq Double Relvance TimeSec Cht"));
	//ui.HLayout_FreqDoub_TimeSecCht->insertWidget(0, m_pFreqDoubTimeSecCht);
	//connect(m_pFreqDoubTimeSecCht, &TimeSecCht_FreqDoub::sgn_SecRectGenerateState, this, &FreqDoubChtPanelWgt::slot_updateTimeSecGenState);
}

void FreqDoubChtPanelWgt::slot_getNewSTFTData(QString dataKey)
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

	//m_pFreqDoubTimeSecCht->setSTFTResultPara(data.InputPara);
	//m_pFreqDoubTimeSecCht->setCurrentFrameIndex(0);

	m_pSTFTHotCht->setSTFTResultPara(data.InputPara);
	m_pSTFTHotCht->setCurrentFrameIndex(0);

}

void FreqDoubChtPanelWgt::updateSTFTLabel(const ST_STFTOutputData& data)
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

void FreqDoubChtPanelWgt::updateSTFTPanel(const ST_STFTOutputData& data)
{
	int maxFrameIndex = data.vecOutput.size() - 1;
	ui.HSlider_OscSep_TimeFrameIndex->setMinimum(0);
	ui.HSlider_OscSep_TimeFrameIndex->setMaximum(maxFrameIndex);
}

void FreqDoubChtPanelWgt::updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime)
{
	ui.label_OscSep_TimeFrameTime->setText(QString("截面时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));
	ui.label_OscSep_Frame_CenterTime->setText(QString("截面中心时间：%1").arg(FrameMidTime.toString("mm:ss.zzz")));
}

void FreqDoubChtPanelWgt::resetFrameRateState()
{
	m_TimeFrameRateStatStartSysTime = QTime::currentTime();
	m_nStatFrameRateStartFrameIndex = ui.HSlider_OscSep_TimeFrameIndex->value();
}

void FreqDoubChtPanelWgt::updateFrameRateState()
{
	int MsecCost = m_TimeFrameRateStatStartSysTime.msecsTo(QTime::currentTime());
	int FrameCost = ui.HSlider_OscSep_TimeFrameIndex->value() - m_nStatFrameRateStartFrameIndex;
	double AvrMsecPerFrame = (double)MsecCost / (double)FrameCost;
	double FrameRate = 1000.0 / AvrMsecPerFrame;
	ui.label_OscSep_Avr_SecFrameRate->setText(QString("平均帧率：%1").arg(FrameRate, 0, 'f', 2));
}

void FreqDoubChtPanelWgt::slot_TimeFrameSliderMoved(int newVal)
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

	//m_pFreqDoubTimeSecCht->setCurrentFrameIndex(newVal);

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

void FreqDoubChtPanelWgt::slot_updateTimerTimeUp()
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

void FreqDoubChtPanelWgt::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
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

void FreqDoubChtPanelWgt::slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr)
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

void FreqDoubChtPanelWgt::slot_getFreqDoubNetMsg(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_FreqDoubNet_GenResult->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_FreqDoubNet_GenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_FreqDoubNet_GenState->setText(QString("生成结束"));
	}
}

void FreqDoubChtPanelWgt::slotFreqDoubResultGet(QString DataKey)
{
	bool dataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::Diff, m_STFTDataKey);

	if (!dataExist)
	{
		return;
	}

	const ST_DiffNetOutput& DiffData = DataCenterManager::instance()->getDiffOutputMap().find(m_STFTDataKey).value();

	if (ui.radioButton_getFreqDoubtData_GoTimeSecCht->isChecked())
	{
		slot_updateHotChtBtnClicked();
		ui.tabWidget_DiffNetPannel->setCurrentIndex(1);
		slot_updateTimeSecChtBtnClicked();
	}
	else
	{

	}
}


void FreqDoubChtPanelWgt::slot_btnNextFrameClicked()
{
	if (ui.HSlider_OscSep_TimeFrameIndex->value() < ui.HSlider_OscSep_TimeFrameIndex->maximum())
	{
		int newVal = ui.HSlider_OscSep_TimeFrameIndex->value() + 1;
		ui.HSlider_OscSep_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}
void FreqDoubChtPanelWgt::slot_btnLastFrameClicked()
{
	if (ui.HSlider_OscSep_TimeFrameIndex->value() > 0)
	{
		int newVal = ui.HSlider_OscSep_TimeFrameIndex->value() - 1;
		ui.HSlider_OscSep_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}

void FreqDoubChtPanelWgt::slot_TimeSecChtTypeChanged()
{

	//EN_FreqDoub_TimeSecChtBarType currentType = (EN_FreqDoub_TimeSecChtBarType)ui.comboBox_TimeSecChtBarType->currentData().toInt();
	//m_pFreqDoubTimeSecCht->setChtType(currentType);

}

void FreqDoubChtPanelWgt::slot_AutoGenFreqDoubData(QString dataKey)
{
	ui.tabWidget_DiffNetPannel->setCurrentIndex(0);
	slot_GenFreqDoubDataBtnClicked();
}

void FreqDoubChtPanelWgt::slot_updateHotChtBtnClicked()
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

void FreqDoubChtPanelWgt::slot_GenFreqDoubDataBtnClicked()
{

	bool STFTExist		= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, m_STFTDataKey);
	bool EffOscExist	= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, m_STFTDataKey);
	bool BDSNRExist		= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, m_STFTDataKey);
	bool DiffExist		= DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::Diff, m_STFTDataKey);
	if (!STFTExist || !EffOscExist || !BDSNRExist || !DiffExist)
	{
		return;
	}

	ST_FMTActiveCond ActiveCond;
	ActiveCond.MatrixActiveSource = (EN_FMTSourceType)ui.comboBox_MatrixSource_Active->currentData().toInt();
	ActiveCond.MatrixSearchSource = (EN_FMTSourceType)ui.comboBox_MatrixSource_Search->currentData().toInt();

	ActiveCond.ChildDiffRatioMaxDistance				= ui.DSBox_DiffSame_MaxAbsRatio->value() / 100;
	ActiveCond.ChildFreqDiffSameGroupTimeCount			= ui.SBox_MergeDiffDirectSameCount->value();
	ActiveCond.ChildFreqSplitOnceOnDiffInConsistant		= ui.checkBox_SplitOnceOnDiffInConsistant->isChecked();
	ActiveCond.ChildFreqSplitDiffDirectInconsistCount	= ui.SBox_SplitDiffDirectInconsistCount->value();

	ST_FreqMultipleTensorGenPara TensorGenPara;

	emit sgn_AskFreqDoubleTensorPara(TensorGenPara);

	FreqDoubleNetwork::instance()->slot_StartGenFreqDoubleNetworkOutput(m_STFTDataKey, TensorGenPara, ActiveCond);

}

void FreqDoubChtPanelWgt::slot_updateTimeSecChtBtnClicked()
{
	//int showMinFreq = ui.SBox_OscSep_TimeSec_startFreq->value();
	//int showMaxFreq = ui.SBox_OscSep_TimeSec_endFreq->value();
	//int dbMinVal = ui.SBox_Diff_TimeSec_StartDB->value();
	//int dbMaxVal = ui.SBox_Diff_TimeSec_EndDB->value();
	////int FreqBarBandWidth = ui.SBox_OscSep_TimeSec_BarBandWidth->value();
	m_nUpdateMsec = ui.SBox_Diff_UpdateTimer->value();

	////m_pDiffTimeSecCht->setFreqBarBandWidth(FreqBarBandWidth);
	//m_pFreqDoubTimeSecCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pFreqDoubTimeSecCht->setDrawDBRange(dbMinVal, dbMaxVal);
	//m_pFreqDoubTimeSecCht->resetFrameRect(m_STFTDataKey);

}

void FreqDoubChtPanelWgt::slot_NoiseBtnGroupClicked()
{
	bool drawTIQLine = ui.checkBox_TimeSecCht_drawTIQLine->isChecked();
	bool drawUnderTIQBar = ui.checkBox_TimeSecCht_drawUnderTIQBar->isChecked();
	bool drawWndSpecNoise = ui.checkBox_TimeSecCht_drawWndSpecNoise->isChecked();
	bool drawBDSNR_Noise = ui.checkBox_TimeSecCht_drawBDSNRNoisePt->isChecked();
	bool drawBDSNR_ConstrainPt = ui.checkBox_TimeSecCht_drawBDSNRConstrainPt->isChecked();
	bool drawBDNSR_ActiveFilter = ui.checkBox_TimeSecCht_drawBDSNRActiveFilter->isChecked();
	bool drawFreqDoub_Child = ui.checkBox_TimeSecCht_drawFreqDoubChild->isChecked();

	//m_pFreqDoubTimeSecCht->setNoisePaintSetting(drawTIQLine, drawUnderTIQBar, drawWndSpecNoise, drawBDSNR_Noise, drawBDSNR_ConstrainPt, drawBDNSR_ActiveFilter, drawFreqDoub_Child);
}

void FreqDoubChtPanelWgt::slot_play()
{
	AudioEngine::instance()->slot_startPlay();
	m_nCurrentTimeUpCount = 0;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
	resetFrameRateState();

}

void FreqDoubChtPanelWgt::slot_jump()
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

void FreqDoubChtPanelWgt::slot_stop()
{
	AudioEngine::instance()->slot_stopPlay();
	m_pUpdateSectionTimer->stop();
}
