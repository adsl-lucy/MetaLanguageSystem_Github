#include "BandWidthSNRSelWgt.h"
#pragma execution_character_set("utf-8")

BandWidthSNRSelWgt::BandWidthSNRSelWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);	
	initFilterCht();
	initHotCht();
	initTimeSecCht();
	initUi();
	initUpdateTimer();
	slot_TimeSecChtShowTypeChanged();
}

BandWidthSNRSelWgt::~BandWidthSNRSelWgt()
{}

void BandWidthSNRSelWgt::initUi()
{

	connect(ui.btn_updateBandWidthFilterCht		, &QPushButton::clicked					, this, &BandWidthSNRSelWgt::slot_updateBandWidthFilterCht);
	connect(ui.btn_GenFilterAndUpdateCht		, &QPushButton::clicked					, this, &BandWidthSNRSelWgt::slot_GenfBandWidthFilterPtAndUpdateCht);
	connect(ui.btn_GenBDSNRResult				, &QPushButton::clicked					, this, &BandWidthSNRSelWgt::slot_startGenBDSNRResultBtnClicked);
	connect(DataCenterManager::instance()		, &DataCenterManager::sgn_STFTDataSaved	, this, &BandWidthSNRSelWgt::slot_getNewSTFTData);
	connect(DataCenterManager::instance()		, &DataCenterManager::sgn_BDSNRDataSaved, this, &BandWidthSNRSelWgt::slot_BDSNR_DataGet);

	connect(BandWidthFilterManager::instance(), &BandWidthFilterManager::sgn_BDSNR_GenState, this, &BandWidthSNRSelWgt::slot_BDSNR_GenState);

	connect(ui.btn_updateHotCht					, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_updateHotChtBtnClicked);
	connect(ui.btn_updateTimeSecCht				, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_updateTimeSecChtBtnClicked);

	connect(ui.btn_play, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_play);
	connect(ui.btn_jump, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_jump);
	connect(ui.btn_stop, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_stop);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_btnNextFrameClicked);
	connect(ui.btn_lastFrame, &QPushButton::clicked, this, &BandWidthSNRSelWgt::slot_btnLastFrameClicked);
	connect(ui.HSlider_TimeFrameIndex, &QAbstractSlider::valueChanged, this, &BandWidthSNRSelWgt::slot_TimeFrameSliderMoved);

	m_pBtnGroup_FilterMaxValType = new QButtonGroup(this);
	m_pBtnGroup_FilterMaxValType->setExclusive(true);
	m_pBtnGroup_FilterMaxValType->addButton(ui.radioButton_BDMaxVal_Max);
	m_pBtnGroup_FilterMaxValType->addButton(ui.radioButton_BDMaxVal_WeightMax);
	ui.radioButton_BDMaxVal_WeightMax->setChecked(true);

	m_pBtnGroup_FilterCond_MainArea = new QButtonGroup(this);
	m_pBtnGroup_FilterCond_MainArea->setExclusive(true);
	m_pBtnGroup_FilterCond_MainArea->addButton(ui.radioButton_FilterCond_MainArea_Strong	,(int)EN_BDSNR_FilterCondition::filter_strong);
	m_pBtnGroup_FilterCond_MainArea->addButton(ui.radioButton_FilterCond_MainArea_Weak		,(int)EN_BDSNR_FilterCondition::filter_weak);
	m_pBtnGroup_FilterCond_MainArea->addButton(ui.radioButton_FilterCond_MainArea_Weight	,(int)EN_BDSNR_FilterCondition::filter_weight);
	ui.radioButton_FilterCond_MainArea_Strong->setChecked(true);

	m_pBtnGroup_FilterCond_SubArea = new QButtonGroup(this);
	m_pBtnGroup_FilterCond_SubArea->setExclusive(true);
	m_pBtnGroup_FilterCond_SubArea->addButton(ui.radioButton_FilterCond_SubArea_Strong	,(int)EN_BDSNR_FilterCondition::filter_strong);
	m_pBtnGroup_FilterCond_SubArea->addButton(ui.radioButton_FilterCond_SubArea_Weak	,(int)EN_BDSNR_FilterCondition::filter_weak);
	m_pBtnGroup_FilterCond_SubArea->addButton(ui.radioButton_FilterCond_SubArea_Weight	,(int)EN_BDSNR_FilterCondition::filter_weight);
	ui.radioButton_FilterCond_SubArea_Weight->setChecked(true);

	m_pBtnGroup_GetBDSNRData = new QButtonGroup(this);
	m_pBtnGroup_GetBDSNRData->setExclusive(true);
	m_pBtnGroup_GetBDSNRData->addButton(ui.radioButton_getBDSNRData_GoTimeSecCht);
	m_pBtnGroup_GetBDSNRData->addButton(ui.radioButton_getBDSNRData_GoEffSigBuff);
	ui.radioButton_getBDSNRData_GoEffSigBuff->setChecked(true);

	m_pbtnGroupTimeSecChtShowType = new QButtonGroup(this);
	m_pbtnGroupTimeSecChtShowType->addButton(ui.radioButton_TimeSecCht_STFT, 0);
	m_pbtnGroupTimeSecChtShowType->addButton(ui.radioButton_TimeSecCht_WndSepcConstrain, 1);
	m_pbtnGroupTimeSecChtShowType->addButton(ui.radioButton_TimeSecHct_BDSNR, 2);
	m_pbtnGroupTimeSecChtShowType->setExclusive(true);
	connect(m_pbtnGroupTimeSecChtShowType, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) { slot_TimeSecChtShowTypeChanged(); });
	ui.radioButton_TimeSecHct_BDSNR->setChecked(true);
	slot_TimeSecChtShowTypeChanged();

	m_pBtnGroup_NoiseDrawSet = new QButtonGroup(this);
	m_pBtnGroup_NoiseDrawSet->setExclusive(false);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawTIQLine);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawUnderTIQBar);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawWndSpecNoise);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNRNoisePt);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNR_ConstrainPt);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNR_SubPt);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNR_Filter);
	m_pBtnGroup_NoiseDrawSet->addButton(ui.checkBox_TimeSecCht_drawBDSNR_FilterMain);
	connect(m_pBtnGroup_NoiseDrawSet, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) { slot_NoiseBtnGroupClicked(); });
	slot_NoiseBtnGroupClicked();

}

void BandWidthSNRSelWgt::initFilterCht()
{
	m_axis_MFCCFreq = new QValueAxis();
	m_axis_MFCCFreq->setRange(0, 20000);
	m_axis_MFCCFreq->setLabelFormat("%.0f");
	m_axis_MFCCFreq->setTitleText("Filter Freq Range(hz)");

	m_axis_MFCCWeight = new QValueAxis();
	m_axis_MFCCWeight->setRange(0, 100);
	m_axis_MFCCWeight->setLabelFormat("%.1f");
	m_axis_MFCCWeight->setTitleText("Freq Weight (%)");

	m_cht_MFCC = new QChart();
	m_cht_MFCC->setTitle("BandWidth Filter Weight");
	m_cht_MFCC->legend()->hide();
	m_cht_MFCC->addAxis(m_axis_MFCCFreq, Qt::AlignBottom);
	m_cht_MFCC->addAxis(m_axis_MFCCWeight, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_MFCC = new QChartView(m_cht_MFCC);
	m_chtView_MFCC->setRenderHint(QPainter::Antialiasing);
	m_chtView_MFCC->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_MFCC->setMinimumSize(980, 230);

	ui.HLayout_BandWidthFilterCht->insertWidget(0, m_chtView_MFCC);
}

void BandWidthSNRSelWgt::initHotCht()
{
	m_pHotCht = new FFT_Chart_STFTHotGram(this);
	m_pHotCht->setTitleText(QString("MFCC Hot Cht"));
	m_pHotCht->setFreqRange(0, 20000);
	ui.VLayout_Cht_HotCht->insertWidget(0, m_pHotCht);
	connect(m_pHotCht, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &BandWidthSNRSelWgt::slot_updateHotChtGenState);
}

void BandWidthSNRSelWgt::initTimeSecCht()
{
	//m_pTimeSecCht = new BDSNR_TimeSecCht(this);
	//m_pTimeSecCht->setTitleText(QString("BandWidth SNR Constrain TimeSec Cht"));
	//ui.HLayout_BDSNR_TimeSecCht->insertWidget(0, m_pTimeSecCht);
	//connect(m_pTimeSecCht, &BDSNR_TimeSecCht::sgn_SecRectGenerateState, this, &BandWidthSNRSelWgt::slot_updateTimeSecChtGenState);

	//m_pTestCht = new TimeSecCht_BDSNR_OpenGL();
	//m_pTestCht->show();
	//connect(m_pTestCht, &TimeSecCht_BDSNR_OpenGL::sgn_SecRectGenerateState, this, &BandWidthSNRSelWgt::slot_updateTimeSecChtGenState);

	m_pTimeSecCht = new TimeSecCht_Wgt(this);
	ui.HLayout_BDSNR_TimeSecCht->insertWidget(0, m_pTimeSecCht);
	connect(m_pTimeSecCht, &TimeSecCht_Wgt::sgn_SecRectGenerateState, this, &BandWidthSNRSelWgt::slot_updateTimeSecChtGenState);

	ST_TimeSecChtGenSetting TimeSecChtGenSetting;
	TimeSecChtGenSetting.Gen_STFT = true;
	TimeSecChtGenSetting.Gen_EffOsc = true;
	TimeSecChtGenSetting.Gen_BDSNR = true;
	TimeSecChtGenSetting.Gen_VibState = false;
	m_pTimeSecCht->setGenType(TimeSecChtGenSetting);

}

void BandWidthSNRSelWgt::initUpdateTimer()
{
	m_pUpdateSectionTimer = new QTimer(this);
	m_pUpdateSectionTimer->setSingleShot(false);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	connect(m_pUpdateSectionTimer, &QTimer::timeout, this, &BandWidthSNRSelWgt::slot_updateTimerTimeUp);
}

void BandWidthSNRSelWgt::slot_updateBandWidthFilterCht()
{
	m_axis_MFCCFreq->setRange(ui.SBox_chtStartFreq->value(), ui.SBox_chtEndFreq->value());
}

ST_BandWidthFilterPara BandWidthSNRSelWgt::getCurrentFilterPara()
{
	ST_BandWidthFilterPara para;
	para.startFreq		= 0;
	para.EndFreq		= 20000;
	para.EqualWidthFilterMaxFreq	= ui.SBox_EqualWidthAreaMaxFreq->value();
	para.EqualWidthFilterCount		= ui.SBox_EqualWidthAreaFilterCount->value();
	para.LogWidthFilterCount		= ui.SBox_LogAreaFilterCount->value();
	para.sampleRate					= ui.SBox_STFTSampleRate->value();
	para.WndPtCount					= ui.SBox_STFTWndPtCount->value();
	return para;
}

void BandWidthSNRSelWgt::slot_GenfBandWidthFilterPtAndUpdateCht()
{
	ST_BandWidthFilterPara para = getCurrentFilterPara();
	ST_BandWidthFilterData result;

	BandWidthFilterManager::instance()->slot_StartGenBandWidthFilterData(para, result);

	showFilterResult(result);
	QString str1 = QString("等间距区域滤波器带宽 : %1 hz").arg((double)para.EqualWidthFilterMaxFreq / (double)para.EqualWidthFilterCount * 2, 0, 'f', 2);
	ui.label_EqualWidthAreaFilterWidth->setText(str1);
	ui.label_totalFilterCount->setText(QString("全局滤波器数量 : %1").arg(para.EqualWidthFilterCount + para.LogWidthFilterCount));
	
}

void BandWidthSNRSelWgt::slot_startGenBDSNRResultBtnClicked()
{
	ST_BandWidthFilterPara FilterPara = getCurrentFilterPara();
	ST_BandWidthFilter_workPara cond;
	
	if (ui.radioButton_BDMaxVal_Max->isChecked())
	{
		cond.FilterMaxValType = EN_BDSNR_FilterMaxValType::maxVal;
	}
	else if (ui.radioButton_BDMaxVal_WeightMax->isChecked())
	{
		cond.FilterMaxValType = EN_BDSNR_FilterMaxValType::maxVal_Weight;
	}

	cond.FilterValDecrease_MainArea_Ratio = (1.0 - ui.DSBox_FilterValDecreaseRatio_MainArea->value() / 100);
	cond.FilterValDecrease_MainArea_DB = AudioProtocol::fftRealToDB(cond.FilterValDecrease_MainArea_Ratio, 0);
	ui.label_FilterValDecrease_DB_MainArea->setText(QString("主对象区等价响度衰减：%1 db").arg(cond.FilterValDecrease_MainArea_DB, 0, 'f', 2));

	cond.FilterValDecrease_SubArea_Ratio = (1.0 - ui.DSBox_FilterValDecreaseRatio_SubArea->value() / 100);
	cond.FilterValDecrease_SubArea_DB = AudioProtocol::fftRealToDB(cond.FilterValDecrease_SubArea_Ratio, 0);
	ui.label_FilterValDecrease_DB_SubArea->setText(QString("主对象区等价响度衰减：%1 db").arg(cond.FilterValDecrease_SubArea_DB, 0, 'f', 2));


	cond.FilterCondition_MainArea = (EN_BDSNR_FilterCondition)m_pBtnGroup_FilterCond_MainArea->checkedId();
	cond.FilterCondition_SubArea = (EN_BDSNR_FilterCondition)m_pBtnGroup_FilterCond_SubArea->checkedId();


	BandWidthFilterManager::instance()->slot_StartBandWidthFilterConstrainData(m_STFTDataKey, FilterPara, cond);
}

void BandWidthSNRSelWgt::slot_TimeSecChtShowTypeChanged()
{
	if (ui.radioButton_TimeSecCht_STFT->isChecked())
	{
		m_pTimeSecCht->setPaintType(EN_TimeSecCht_PaintType::STFT);
		//m_pTestCht->setChtType(EN_BDSNR_TimeSecChtBarType_GL::STFT);
	}
	else if (ui.radioButton_TimeSecCht_WndSepcConstrain->isChecked())
	{
		m_pTimeSecCht->setPaintType(EN_TimeSecCht_PaintType::EffOsc);
		//m_pTestCht->setChtType(EN_BDSNR_TimeSecChtBarType_GL::EffectiveOscillation);
	}
	else if (ui.radioButton_TimeSecHct_BDSNR->isChecked())
	{
		m_pTimeSecCht->setPaintType(EN_TimeSecCht_PaintType::BDSNR);
		//m_pTestCht->setChtType(EN_BDSNR_TimeSecChtBarType_GL::BDSNR);
	}
}

void BandWidthSNRSelWgt::slot_NoiseBtnGroupClicked()
{
	//bool EffOsc_drawTIQLine			= ui.checkBox_TimeSecCht_drawTIQLine->isChecked();
	//bool EffOsc_drawUnderTIQBar		= ui.checkBox_TimeSecCht_drawUnderTIQBar->isChecked();
	//bool EffOsc_drawWndSpecNoise	= ui.checkBox_TimeSecCht_drawWndSpecNoise->isChecked();

	//bool BDSNR_drawNoise		= ui.checkBox_TimeSecCht_drawBDSNRNoisePt->isChecked();
	//bool BDSNR_drawConstrainPt	= ui.checkBox_TimeSecCht_drawBDSNR_ConstrainPt->isChecked();
	//bool BDSNR_drawSubPt		= ui.checkBox_TimeSecCht_drawBDSNR_SubPt->isChecked();
	//bool BDSNR_drawFilter		= ui.checkBox_TimeSecCht_drawBDSNR_Filter->isChecked();
	//bool BDSNR_drawFilterMain	= ui.checkBox_TimeSecCht_drawBDSNR_FilterMain->isChecked();

	//m_pTimeSecCht->setNoisePaintSetting_EffOsc(EffOsc_drawTIQLine, EffOsc_drawUnderTIQBar, EffOsc_drawWndSpecNoise);
	//m_pTimeSecCht->setNoisePaintSetting_BDSNR(BDSNR_drawNoise, BDSNR_drawConstrainPt, BDSNR_drawSubPt, BDSNR_drawFilter, BDSNR_drawFilterMain);

	//m_pTestCht->setNoisePaintSetting_EffOsc(EffOsc_drawTIQLine, EffOsc_drawUnderTIQBar, EffOsc_drawWndSpecNoise);
	//m_pTestCht->setNoisePaintSetting_BDSNR(BDSNR_drawNoise, BDSNR_drawConstrainPt, BDSNR_drawSubPt, BDSNR_drawFilter, BDSNR_drawFilterMain);

	ST_TimeSecChtPaintSetting paintSetting;
	paintSetting.EffOsc_UnderTIQBar		= ui.checkBox_TimeSecCht_drawUnderTIQBar->isChecked();
	paintSetting.EffOsc_TIQLine			= ui.checkBox_TimeSecCht_drawTIQLine->isChecked();
	paintSetting.EffOsc_WndSepcNoise	= ui.checkBox_TimeSecCht_drawWndSpecNoise->isChecked();


	paintSetting.BDSNR_Noise				= ui.checkBox_TimeSecCht_drawBDSNRNoisePt->isChecked();
	paintSetting.BDSNR_ConstrainPt			= ui.checkBox_TimeSecCht_drawBDSNR_ConstrainPt->isChecked();
	paintSetting.BDSNR_EffectSubPt			= ui.checkBox_TimeSecCht_drawBDSNR_SubPt->isChecked();
	paintSetting.BDSNR_ActiveFilter			= ui.checkBox_TimeSecCht_drawBDSNR_Filter->isChecked();
	paintSetting.BDSNR_ActiveFilter_Main	= ui.checkBox_TimeSecCht_drawBDSNR_FilterMain->isChecked();

	m_pTimeSecCht->setPaintSetting(paintSetting);
	
}

void BandWidthSNRSelWgt::slot_autoGenBDSNRResult(QString DataKey)
{
	ui.tabWidget_Filter->setCurrentIndex(0);
	slot_GenfBandWidthFilterPtAndUpdateCht();
	ui.tabWidget_BDSNR_Panel->setCurrentIndex(0);
	slot_startGenBDSNRResultBtnClicked();
}

void BandWidthSNRSelWgt::slot_getNewSTFTData(QString dataKey)
{
	const ST_STFTOutputData& data = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	if (data.vecOutput.isEmpty())
	{
		qDebug() << "OscillationSeparatorWgt::slot_getSTFTData : dataVec Empty!";
		return;
	}
	m_STFTDataKey = data.DatacenterName;
	m_dataPara = data.InputPara;

	ui.SBox_STFTSampleRate->setValue(data.InputPara.sampleRate);
	ui.SBox_STFTWndPtCount->setValue(data.InputPara.WndPara.pointCount);

	updateSTFTLabel(data);
	updateSTFTPanel(data);

	//m_pTimeSecCht->setSTFTResultPara(data.InputPara);
	//m_pTimeSecCht->setCurrentFrameIndex(0);

	//m_pTestCht->setSTFTResultPara(data.InputPara);
	//m_pTestCht->setCurrentFrameIndex(0);

	m_pHotCht->setSTFTResultPara(data.InputPara);
	m_pHotCht->setCurrentFrameIndex(0);

}

void BandWidthSNRSelWgt::showFilterResult(const ST_BandWidthFilterData& result)
{
	m_axis_MFCCWeight->setRange(0, result.maxWeight);
	m_axis_MFCCFreq->setRange(result.para.startFreq, result.para.EndFreq);

	m_axis_MFCCWeight->setLabelFormat("%.5f");

	m_cht_MFCC->removeAllSeries();

	for (int FilterIndex = 0; FilterIndex < result.FilterVec.size(); FilterIndex++)
	{
		QLineSeries* filterSeries = new QLineSeries(m_cht_MFCC);
		filterSeries->setName(QString("filter %1").arg(FilterIndex));

		const ST_BandWidthFilter& filterRef = result.FilterVec[FilterIndex];
		filterSeries->append(QPointF(filterRef.startFreq, 0));
		filterSeries->append(QPointF(filterRef.CenterFreq, filterRef.maxWeight));
		filterSeries->append(QPointF(filterRef.endFreq, 0));
		m_cht_MFCC->addSeries(filterSeries);
		filterSeries->attachAxis(m_axis_MFCCFreq);
		filterSeries->attachAxis(m_axis_MFCCWeight);

	}
	slot_updateBandWidthFilterCht();

}

void BandWidthSNRSelWgt::slot_updateHotChtBtnClicked()
{
	QTime startTime			= ui.timeEdit_hotChtStartTime->time();
	int   WndMsecLength		= ui.SBox_hotChtTimeLength->value();
	int   startFreq			= ui.SBox_HotChtStartFreq->value();
	int   endFreq			= ui.SBox_HotchtEndFreq->value();
	int   startDb			= ui.SBox_HotCht_StartDB->value();
	int   endDb				= ui.SBox_HotCht_EndDB->value();
	int   BarBandWidth		= ui.SBox_HotCht_FreqBandWidth->value();
	int   BarTimeLength		= ui.SBox_HotCht_TimeIntervalMsec->value();

	m_nUpdateMsec = BarTimeLength;

	m_pHotCht->setFreqRange(startFreq, endFreq);
	m_pHotCht->setTimeRange(startTime, WndMsecLength);
	m_pHotCht->setDbRange(startDb, endDb);
	m_pHotCht->setFreqBandWidth(BarBandWidth);
	m_pHotCht->setTimeInterval(BarTimeLength);
	m_pHotCht->resetColorRect(m_STFTDataKey);
}

void BandWidthSNRSelWgt::slot_updateTimeSecChtBtnClicked()
{
	//int showMinFreq			= ui.SBox_TimeSecCht_startFreq->value();
	//int showMaxFreq			= ui.SBox_TimeSecCht_endFreq->value();
	//int dbMinVal			= ui.SBox_TimeSecCht_StartDB->value();
	//int dbMaxVal			= ui.SBox_TimeSecCht_EndDB->value();
	m_nUpdateMsec			= ui.SBox_TimeSecCht_UpdateTimer->value();

	//m_pTimeSecCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pTimeSecCht->setDrawDBRange(dbMinVal, dbMaxVal);
	//m_pTimeSecCht->resetFrameRect(m_STFTDataKey);

	//m_pTestCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pTestCht->setDrawDBRange(dbMinVal, dbMaxVal);
	//m_pTestCht->resetFrameRect(m_STFTDataKey);

	ST_TimeSecChtDataRange dataRange;
	dataRange.minFreq	= ui.SBox_TimeSecCht_startFreq->value();
	dataRange.maxFreq	= ui.SBox_TimeSecCht_endFreq->value();
	dataRange.minDB		= ui.SBox_TimeSecCht_StartDB->value();
	dataRange.maxDB		= ui.SBox_TimeSecCht_EndDB->value();

	m_pTimeSecCht->setDataRange(dataRange);
	m_pTimeSecCht->resetTimeSecChtRect(m_STFTDataKey, m_dataPara);

}

void BandWidthSNRSelWgt::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
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

void BandWidthSNRSelWgt::slot_BDSNR_GenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_BDSNR_GenState->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_BDSNR_GenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_BDSNR_GenState->setText(QString("生成结束"));

	}
}

void BandWidthSNRSelWgt::slot_updateTimeSecChtGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_TimeSecCht_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_TimeSecGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_TimeSecGenState->setText(QString("生成结束"));
	}


}

void BandWidthSNRSelWgt::slot_play()
{
	AudioEngine::instance()->slot_startPlay();
	m_nCurrentTimeUpCount = 0;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
	resetFrameRateState();
}

void BandWidthSNRSelWgt::slot_jump()
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

void BandWidthSNRSelWgt::slot_stop()
{
	AudioEngine::instance()->slot_stopPlay();
	m_pUpdateSectionTimer->stop();
}

void BandWidthSNRSelWgt::slot_updateTimerTimeUp()
{
	updateFrameRateState();
	double frameMsec = m_nCurrentTimeUpCount * m_nUpdateMsec;
	double frameInterval = m_dataPara.GapInTimeLength * 1000;
	int frameIndex = frameMsec / frameInterval;
	int maxFrame = ui.HSlider_TimeFrameIndex->maximum();
	if (frameIndex > maxFrame)
	{
		qDebug() << QString("BandWidthSNRSelWgt::slot_updateTimerTimeUp : stop");
		m_pUpdateSectionTimer->stop();
		ui.HSlider_TimeFrameIndex->setValue(maxFrame);
		slot_TimeFrameSliderMoved(maxFrame);
	}
	else
	{
		QString currentTime = QTime::currentTime().toString("mm:ss.zzz");
		qDebug() << QString("BandWidthSNRSelWgt::slot_updateTimerTimeUp : show msec %1 : frameindex : %2 realTime %3").arg(frameMsec).arg(frameIndex).arg(currentTime);
		ui.HSlider_TimeFrameIndex->setValue(frameIndex);
		slot_TimeFrameSliderMoved(frameIndex);
		m_nCurrentTimeUpCount += 1;
	}
}

void BandWidthSNRSelWgt::slot_TimeFrameSliderMoved(int newVal)
{
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
	//m_pTestCht->setCurrentFrameIndex(newVal);

	m_pHotCht->setCurrentTime(frameStartTime);
	QTime HotChtStartTime;
	QTime HotChtEndTime;
	m_pHotCht->getCurrentTimeRange(HotChtStartTime, HotChtEndTime);
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
		m_pHotCht->setTimeRange(hotChtNewStartTime, HotChtTimeWndLengthMsec);
	}
}

void BandWidthSNRSelWgt::slot_btnNextFrameClicked()
{
	if (ui.HSlider_TimeFrameIndex->value() < ui.HSlider_TimeFrameIndex->maximum())
	{
		int newVal = ui.HSlider_TimeFrameIndex->value() + 1;
		ui.HSlider_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}
void BandWidthSNRSelWgt::slot_btnLastFrameClicked()
{
	if (ui.HSlider_TimeFrameIndex->value() > 0)
	{
		int newVal = ui.HSlider_TimeFrameIndex->value() - 1;
		ui.HSlider_TimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}

void BandWidthSNRSelWgt::updateSTFTLabel(const ST_STFTOutputData& data)
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

void BandWidthSNRSelWgt::updateSTFTPanel(const ST_STFTOutputData& data)
{
	int maxFrameIndex = data.vecOutput.size() - 1;
	ui.HSlider_TimeFrameIndex->setMinimum(0);
	ui.HSlider_TimeFrameIndex->setMaximum(maxFrameIndex);
}

void BandWidthSNRSelWgt::updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime)
{
	ui.labe_HSliderTime->setText(QString("截面时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));
	ui.label_TimeSecCht_Frame_CenterTime->setText(QString("截面中心时间：%1").arg(FrameMidTime.toString("mm:ss.zzz")));
}

void BandWidthSNRSelWgt::resetFrameRateState()
{
	m_TimeFrameRateStatStartSysTime = QTime::currentTime();
	m_nStatFrameRateStartFrameIndex = ui.HSlider_TimeFrameIndex->value();
}

void BandWidthSNRSelWgt::updateFrameRateState()
{
	int MsecCost = m_TimeFrameRateStatStartSysTime.msecsTo(QTime::currentTime());
	int FrameCost = ui.HSlider_TimeFrameIndex->value() - m_nStatFrameRateStartFrameIndex;
	double AvrMsecPerFrame = (double)MsecCost / (double)FrameCost;
	double FrameRate = 1000.0 / AvrMsecPerFrame;
	ui.label_TimeSecCht_Avr_SecFrameRate->setText(QString("平均帧率：%1").arg(FrameRate, 0, 'f', 2));
}

void BandWidthSNRSelWgt::slot_BDSNR_DataGet(QString dataKey)
{
	if (ui.radioButton_getBDSNRData_GoTimeSecCht->isChecked())
	{
		ui.tabWidget_Filter->setCurrentIndex(1);
		slot_updateHotChtBtnClicked();
		ui.tabWidget_BDSNR_Panel->setCurrentIndex(1);
		slot_updateTimeSecChtBtnClicked();
	}
	else if (ui.radioButton_getBDSNRData_GoEffSigBuff->isChecked())
	{
		emit sgn_goEffSigBuffWgt(m_STFTDataKey);
	}
}