#include "STFTAnalysePanel.h"
#pragma execution_character_set("utf-8")

STFTAnalysePanel::STFTAnalysePanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	initUI();
	initUpdateTimer();
}

STFTAnalysePanel::~STFTAnalysePanel()
{}

void STFTAnalysePanel::initUI()
{
	connect(ui.btn_updateTimeSecCht	, &QPushButton::clicked, this, &STFTAnalysePanel::slot_updateTimeSecChtBtnClicked);
	connect(ui.btn_updateHotCht		, &QPushButton::clicked, this, &STFTAnalysePanel::slot_updateHotChtBtnClicked);
	connect(ui.HSlider_STFTTimeFrameIndex, &QAbstractSlider::sliderMoved, this, &STFTAnalysePanel::slot_TimeFrameSliderMoved);

	connect(ui.btn_play, &QPushButton::clicked, this, &STFTAnalysePanel::slot_play);
	connect(ui.btn_jump, &QPushButton::clicked, this, &STFTAnalysePanel::slot_jump);
	connect(ui.btn_stop, &QPushButton::clicked, this, &STFTAnalysePanel::slot_stop);

	connect(ui.btn_lastFrame, &QPushButton::clicked, this, &STFTAnalysePanel::slot_btnLastFrameClicked);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &STFTAnalysePanel::slot_btnNextFrameClicked);

	connect(ui.btn_showPhaseTimeSec, &QPushButton::clicked, this, &STFTAnalysePanel::slot_showTimePhaseSecBtnClicked);
}

void STFTAnalysePanel::initUpdateTimer()
{
	m_pUpdateSectionTimer = new QTimer(this);
	m_pUpdateSectionTimer->setSingleShot(false);
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
	connect(m_pUpdateSectionTimer, &QTimer::timeout, this, &STFTAnalysePanel::slot_updateTimerTimeUp);

}

void STFTAnalysePanel::init()
{
	m_pSTFTHotChart			= new FFT_Chart_STFTHotGram(this);
	m_pSTFTHotChart->setTitleText(QString("STFT Hot Cht"));
	ui.VLayout_STFT_Cht_HotCht->insertWidget(0, m_pSTFTHotChart);
	connect(m_pSTFTHotChart, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &STFTAnalysePanel::slot_updateHotChtGenState);

	//m_pSTFTTimeSectionAmpCht = new FFT_Chart_STFTTimeSection(this);
	//m_pSTFTTimeSectionAmpCht->setChtType(EN_TimeSecType::Amp);
	//m_pSTFTTimeSectionAmpCht->setTitleText(QString("STFT TimeSection Cht"));
	//ui.VLayout_STFT_Cht_TimeSection->insertWidget(0, m_pSTFTTimeSectionAmpCht);
	//connect(m_pSTFTTimeSectionAmpCht, &FFT_Chart_STFTTimeSection::sgn_SecRectGenerateState, this, &STFTAnalysePanel::slot_updateTimeSecGenState);

	//m_pSTFTTimeSectionPhaseCht = new FFT_Chart_STFTTimeSection(nullptr);
	//m_pSTFTTimeSectionPhaseCht->setChtType(EN_TimeSecType::Phase);
	//m_pSTFTTimeSectionPhaseCht->resize(1088, 331);
	//m_pSTFTTimeSectionPhaseCht->hide();
	//connect(m_pSTFTTimeSectionAmpCht, &FFT_Chart_STFTTimeSection::sgn_SecRectGenerateState, this, &STFTAnalysePanel::slot_updateTimeSecGenState);
	//connect(m_pSTFTTimeSectionPhaseCht, &FFT_Chart_STFTTimeSection::sgn_windowHide, this, &STFTAnalysePanel::slot_showTimePhaseSecWndHide);

	m_pTimeSecCht = new TimeSecCht_Wgt(this);
	ui.VLayout_STFT_Cht_TimeSection->insertWidget(0, m_pTimeSecCht);
	connect(m_pTimeSecCht, &TimeSecCht_Wgt::sgn_SecRectGenerateState, this, &STFTAnalysePanel::slot_updateTimeSecGenState);

	ST_TimeSecChtGenSetting TimeSecChtGenSetting;
	TimeSecChtGenSetting.Gen_STFT = true;
	TimeSecChtGenSetting.Gen_EffOsc = false;
	TimeSecChtGenSetting.Gen_BDSNR = false;
	TimeSecChtGenSetting.Gen_VibState = false;
	m_pTimeSecCht->setGenType(TimeSecChtGenSetting);

}

void STFTAnalysePanel::updateSTFTLabel(const ST_STFTOutputData& data)
{
	ui.label_STFTFileName->setText(QString("文件名称 : %1").arg(data.InputPara.fileName));

	QTime startTime = QTime(0, 0, 0).addMSecs(data.InputPara.startTime * 1000);
	QTime endTime	= startTime.addMSecs(data.InputPara.timeLength * 1000);
	
	ui.label_DataStartTime->setText(QString("数据开始时间 : %1").arg(startTime.toString("mm:ss.zzz")));
	ui.label_dataEndTime->setText(QString("数据结束时间 : %1").arg(endTime.toString("mm:ss.zzz")));

	double FreqInterval = FFTManager::instance()->getFreqencyInterval(data.InputPara.sampleRate, data.InputPara.WndPara.pointCount);

	ui.label_FFTFreqInterval->setText(QString("FFT频率间隔 : %1 hz").arg(FreqInterval,0,'f',2));
	ui.label_STFTGapIntervalMsec->setText(QString("STFT步长 :%1 ms ").arg(data.InputPara.GapInTimeLength * 1000,0,'f',2));
	ui.label_FFTFreqCount->setText(QString("频率点数 :%1 ").arg(data.vecOutput[0].resultVec.size()));
	ui.label_TimeFrameCount->setText(QString("时间点数 : %1 ").arg(data.vecOutput.size()));
}

void STFTAnalysePanel::updateSTFTPanel(const ST_STFTOutputData& data)
{
	int maxFrameIndex = data.vecOutput.size() - 1;
	ui.HSlider_STFTTimeFrameIndex->setMinimum(0);
	ui.HSlider_STFTTimeFrameIndex->setMaximum(maxFrameIndex);
}

void STFTAnalysePanel::setSTFTData(const ST_STFTOutputData& data)
{
	if (data.vecOutput.isEmpty())
	{
		qDebug() << "STFTAnalysePanel::setSTFTData : dataVec Empty!";
		return;
	}
	m_STFTDataKey = data.DatacenterName;
	m_dataPara = data.InputPara;

	updateSTFTLabel(data);
	updateSTFTPanel(data);
	//m_pSTFTTimeSectionAmpCht->setSTFTResultPara(data.InputPara);
	//m_pSTFTTimeSectionAmpCht->setCurrentFrameIndex(0);
	//if (ui.checkBox_genPhaseSec->isChecked())
	//{
	//	m_pSTFTTimeSectionPhaseCht->setSTFTResultPara(data.InputPara);
	//	m_pSTFTTimeSectionPhaseCht->setCurrentFrameIndex(0);
	//}


	m_pSTFTHotChart->setSTFTResultPara(data.InputPara);
	m_pSTFTHotChart->setCurrentFrameIndex(0);

}

void STFTAnalysePanel::slot_TimeFrameSliderMoved(int newVal)
{
	//qDebug() << "STFTAnalysePanel::slot_TimeFrameSliderMoved : " << newVal;
	int		frameIndex		= newVal;
	double	frameInterval	= m_dataPara.GapInTimeLength;
	int		frameStartMsec	= frameIndex * frameInterval * 1000;
	int		frameEndMsec	= frameStartMsec + m_dataPara.WndPara.WndMsec;
	int		frameMidMsec	= (frameStartMsec + frameEndMsec) / 2;

	QTime frameStartTime	= QTime(0, 0, 0).addMSecs(frameStartMsec);
	QTime frameMidTime		= QTime(0, 0, 0).addMSecs(frameMidMsec);
	QTime frameEndTime		= QTime(0, 0, 0).addMSecs(frameEndMsec);
	updateTimeFrameLabel(frameStartTime, frameMidTime, frameEndTime);

	m_pTimeSecCht->setCurrentFrameIndex(newVal);

	//m_pSTFTTimeSectionAmpCht->setCurrentFrameIndex(newVal);

	//if (m_pSTFTTimeSectionPhaseCht->isVisible())
	//{
	//	m_pSTFTTimeSectionPhaseCht->setCurrentFrameIndex(newVal);
	//}
	

	m_pSTFTHotChart->setCurrentTime(frameStartTime);
	QTime HotChtStartTime;
	QTime HotChtEndTime;
	m_pSTFTHotChart->getCurrentTimeRange(HotChtStartTime, HotChtEndTime);
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
		m_pSTFTHotChart->setTimeRange(hotChtNewStartTime, HotChtTimeWndLengthMsec);
	}


}

void STFTAnalysePanel::slot_updateTimerTimeUp()
{
	double frameMsec = m_nCurrentTimeUpCount * m_nUpdateMsec;
	double frameInterval = m_dataPara.GapInTimeLength * 1000;
	int frameIndex = frameMsec / frameInterval;
	int maxFrame = ui.HSlider_STFTTimeFrameIndex->maximum();
	if (frameIndex > maxFrame)
	{
		qDebug() << QString("STFTAnalysePanel::slot_updateTimerTimeUp : stop");
		m_pUpdateSectionTimer->stop();
		ui.HSlider_STFTTimeFrameIndex->setValue(maxFrame);
		slot_TimeFrameSliderMoved(maxFrame);
	}
	else
	{
		QString currentTime = QTime::currentTime().toString("mm:ss.zzz");
		qDebug() << QString("STFTAnalysePanel::slot_updateTimerTimeUp : show msec %1 : frameindex : %2 realTime %3").arg(frameMsec).arg(frameIndex).arg(currentTime);
		ui.HSlider_STFTTimeFrameIndex->setValue(frameIndex);
		slot_TimeFrameSliderMoved(frameIndex);
		m_nCurrentTimeUpCount +=1;
	}

}

void STFTAnalysePanel::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_STFT_HotCht_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_HotChtGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{

		ui.label_HotChtGenState->setText(QString("生成结束"));
	}
}

void STFTAnalysePanel::slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_STFT_TimeSec_Genstate->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_TimeSecGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{

		ui.label_TimeSecGenState->setText(QString("生成结束"));
	}
}

void STFTAnalysePanel::slot_btnNextFrameClicked()
{
	if (ui.HSlider_STFTTimeFrameIndex->value() < ui.HSlider_STFTTimeFrameIndex->maximum())
	{
		int newVal = ui.HSlider_STFTTimeFrameIndex->value() + 1;
		ui.HSlider_STFTTimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}
void STFTAnalysePanel::slot_btnLastFrameClicked()
{
	if (ui.HSlider_STFTTimeFrameIndex->value() > 0 )
	{
		int newVal = ui.HSlider_STFTTimeFrameIndex->value() - 1;
		ui.HSlider_STFTTimeFrameIndex->setValue(newVal);
		slot_TimeFrameSliderMoved(newVal);
	}
}

void STFTAnalysePanel::updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime)
{
	ui.label_STFTTimeFrameTime->setText(QString("截面时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));

	ui.label_STFT_Frame_startTime->setText(QString("截面开始时间：%1").arg(FrameStartTime.toString("mm:ss.zzz")));
	ui.label_STFT_Frame_midTime->setText(QString("截面中心时间：%1").arg(FrameMidTime.toString("mm:ss.zzz")));
	ui.label_STFT_Frame_endTime->setText(QString("截面结束时间：%1").arg(FrameEndTime.toString("mm:ss.zzz")));
}

void STFTAnalysePanel::slot_updateTimeSecChtBtnClicked()
{
	//int showMinFreq			= ui.SBox_STFT_TimeSec_startFreq->value();
	//int showMaxFreq			= ui.SBox_STFT_TimeSec_endFreq->value();
	//int dbMinVal			= ui.SBox_STFT_TimeSec_StartDB->value();
	//int dbMaxVal			= ui.SBox_STFT_TimeSec_EndDB->value();
	//int FreqBarBandWidth	= ui.SBox_STFT_TimeSec_BarBandWidth->value();
	m_nUpdateMsec			= ui.SBox_STFTUpdateTimer->value();

	//m_pSTFTTimeSectionAmpCht->setFreqBarBandWidth(FreqBarBandWidth);
	//m_pSTFTTimeSectionAmpCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pSTFTTimeSectionAmpCht->setDrawDBRange(dbMinVal, dbMaxVal);
	//m_pSTFTTimeSectionAmpCht->resetFrameRect(m_STFTDataKey);

	//m_pSTFTTimeSectionPhaseCht->setFreqBarBandWidth(FreqBarBandWidth);
	//m_pSTFTTimeSectionPhaseCht->setDrawFreqRanged(showMinFreq, showMaxFreq);
	//m_pSTFTTimeSectionPhaseCht->resetFrameRect(m_STFTDataKey);

	ST_TimeSecChtDataRange dataRange;
	dataRange.minFreq = ui.SBox_STFT_TimeSec_startFreq->value();
	dataRange.maxFreq = ui.SBox_STFT_TimeSec_endFreq->value();
	dataRange.minDB = ui.SBox_STFT_TimeSec_StartDB->value();
	dataRange.maxDB = ui.SBox_STFT_TimeSec_EndDB->value();

	m_pTimeSecCht->setDataRange(dataRange);
	m_pTimeSecCht->resetTimeSecChtRect(m_STFTDataKey, m_dataPara);

}

void STFTAnalysePanel::slot_showTimePhaseSecBtnClicked()
{
	//m_pSTFTTimeSectionPhaseCht->show();
	//ui.btn_showPhaseTimeSec->setEnabled(false);
}

void STFTAnalysePanel::slot_showTimePhaseSecWndHide()
{
	ui.btn_showPhaseTimeSec->setEnabled(true);
}

void STFTAnalysePanel::slot_updateHotChtBtnClicked()
{
	QTime startTime = ui.timeEdit_hotChtStartTime->time();
	int   WndMsecLength = ui.SBox_hotChtTimeLength->value();
	int   startFreq = ui.SBox_HotChtStartFreq->value();
	int   endFreq = ui.SBox_HotchtEndFreq->value();
	int   startDb = ui.SBox_STFT_HotCht_StartDB->value();
	int   endDb = ui.SBox_STFT_HotCht_EndDB->value();
	int   BarBandWidth = ui.SBox_HotChtFreqBandWidth->value();
	int   BarTimeLength = ui.SBox_HotChtTimeIntervalMsec->value();

	m_pSTFTHotChart->setFreqRange(startFreq, endFreq);
	m_pSTFTHotChart->setTimeRange(startTime, WndMsecLength);
	m_pSTFTHotChart->setDbRange(startDb, endDb);
	m_pSTFTHotChart->setFreqBandWidth(BarBandWidth);
	m_pSTFTHotChart->setTimeInterval(BarTimeLength);
	m_pSTFTHotChart->resetColorRect(m_STFTDataKey);
}

void STFTAnalysePanel::slot_play()
{
	AudioEngine::instance()->slot_startPlay();
	m_nCurrentTimeUpCount = 0;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();

}

void STFTAnalysePanel::slot_jump()
{
	int		frameIndex = ui.HSlider_STFTTimeFrameIndex->value();
	double	frameInterval = m_dataPara.GapInTimeLength;
	int		frameStartMsec = frameIndex * frameInterval * 1000;
	//int		frameEndMsec = frameStartMsec + m_dataPara.WndPara.WndMsec;
	//int		frameMidMsec = (frameStartMsec + frameEndMsec) / 2;

	QTime frameStartTime = QTime(0, 0, 0).addMSecs(frameStartMsec);
	//QTime frameMidTime = QTime(0, 0, 0).addMSecs(frameMidMsec);
	//QTime frameEndTime = QTime(0, 0, 0).addMSecs(frameEndMsec);
	AudioEngine::instance()->slot_jump(frameStartTime);



	m_nCurrentTimeUpCount = frameStartMsec / m_nUpdateMsec;
	slot_updateTimerTimeUp();
	m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
	m_pUpdateSectionTimer->start();
}

void STFTAnalysePanel::slot_stop()
{
	AudioEngine::instance()->slot_stopPlay();
	m_pUpdateSectionTimer->stop();
}