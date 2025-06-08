#include "WaveWgt.h"
#pragma execution_character_set("utf-8")

WaveWgt::WaveWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUi();
	initVolumnBar();
	initLeftChart();
	initRightChart();
}

WaveWgt::~WaveWgt()
{}


void WaveWgt::initUi()
{
	ui.hSlider_windowScale->setTickInterval(1);
	connect(ui.hSlider_windowScale,		&QAbstractSlider::sliderMoved	, this, &WaveWgt::slot_windowLengthSliderMove);
	connect(ui.HScrollBar_windowPos,	&QAbstractSlider::sliderMoved	, this, &WaveWgt::slot_WndPosScrollBarMove);
	connect(ui.btn_reloadCht,			&QPushButton::clicked			, this, &WaveWgt::slot_reloadBtnClicked);
	connect(ui.btn_loadAll,				&QPushButton::clicked			, this, &WaveWgt::slot_reloadAllBtnClicked);

	connect(ui.btn_play		, &QPushButton::clicked, this, &WaveWgt::slot_playBtnClicked);
	connect(ui.btn_pause	, &QPushButton::clicked, this, &WaveWgt::slot_jumpBtnClicked);
	connect(ui.btn_stop		, &QPushButton::clicked, this, &WaveWgt::slot_stopBtnClicked);
	connect(ui.btn_loadToDataCenter, &QPushButton::clicked, this, &WaveWgt::slot_loadDataToDCenterBtnClicked);

	connect(this, &WaveWgt::sgn_saveWavData, DataCenterManager::instance(), &DataCenterManager::slot_saveWavData);

	ui.btn_pause->hide();

}

void WaveWgt::initVolumnBar()
{
	m_pVolumnBar = new VolumnBarWgt(this);
	m_pVolumnBar->setMaxMin(80, 0);
	m_pVolumnBar->setVal(0);
	ui.VLayout_volumnBar->insertWidget(0, m_pVolumnBar);

	m_pVolumnUpdateTimer = new QTimer(this);
	m_pVolumnUpdateTimer->setSingleShot(false);
	m_pVolumnUpdateTimer->setInterval(m_nVolumnUpdateIntervalMs);
	m_pVolumnUpdateTimer->setTimerType(Qt::PreciseTimer);
	m_pVolumnUpdateTimer->stop();
	connect(m_pVolumnUpdateTimer,&QTimer::timeout,this,&WaveWgt::slot_updateVolumn);
}

void WaveWgt::initLeftChart()
{
	m_leftCht_axis_x_1DWave = new QValueAxis();
	m_leftCht_axis_x_1DWave->setRange(0, 1000);
	m_leftCht_axis_x_1DWave->setLabelFormat("%.1f");
	m_leftCht_axis_x_1DWave->setTitleText("wav time(s)");

	m_leftCht_axis_y_1DWave = new QValueAxis();
	m_leftCht_axis_y_1DWave->setRange(-1, 1);
	m_leftCht_axis_y_1DWave->setLabelFormat("%.1f");
	m_leftCht_axis_y_1DWave->setTitleText("wav val(pcm)");

	m_leftCht_series_1DWave = nullptr;

	m_leftCht = new QChart();

	m_leftCht->setTitle("Wav Left Channel chart");
	m_leftCht->legend()->hide();
	m_leftCht->addAxis(m_leftCht_axis_x_1DWave, Qt::AlignBottom);
	m_leftCht->addAxis(m_leftCht_axis_y_1DWave, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_leftCht_chtView_1DWave = new QChartView(m_leftCht);
	m_leftCht_chtView_1DWave->setRenderHint(QPainter::Antialiasing);
	m_leftCht_chtView_1DWave->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_leftCht_chtView_1DWave->setMinimumSize(820, 250);

	ui.VLayout_LeftCh->insertWidget(0, m_leftCht_chtView_1DWave);
}

void WaveWgt::initRightChart()
{
	m_rightCht_axis_x_1DWave = new QValueAxis();
	m_rightCht_axis_x_1DWave->setRange(0, 1000);
	m_rightCht_axis_x_1DWave->setLabelFormat("%.1f");
	m_rightCht_axis_x_1DWave->setTitleText("wav time(s)");

	m_rightCht_axis_y_1DWave = new QValueAxis();
	m_rightCht_axis_y_1DWave->setRange(-1, 1);
	m_rightCht_axis_y_1DWave->setLabelFormat("%.1f");
	m_rightCht_axis_y_1DWave->setTitleText("wav val(pcm)");

	m_rightCht_series_1DWave = nullptr;

	m_rightCht = new QChart();

	m_rightCht->setTitle("Wav Right Channel chart");
	m_rightCht->legend()->hide();
	m_rightCht->addAxis(m_rightCht_axis_x_1DWave, Qt::AlignBottom);
	m_rightCht->addAxis(m_rightCht_axis_y_1DWave, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_rightCht_chtView_1DWave = new QChartView(m_rightCht);
	m_rightCht_chtView_1DWave->setRenderHint(QPainter::Antialiasing);
	m_rightCht_chtView_1DWave->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_rightCht_chtView_1DWave->setMinimumSize(820, 250);

	ui.VLayout_rightCh->insertWidget(0, m_rightCht_chtView_1DWave);
}

void WaveWgt::loadWavData(const ST_WavDoubleData& data, bool AutoSenToDataCenter)
{
	setPannelEnable(false);
	loadData(data);
	resetPannel();
	generateVolumnMap();
	loadDataIntoCht(m_nCurrentZoomRate,QTime(0,0,0),m_data.fileTag.Duration);
	
	setPannelEnable(true);
	if (AutoSenToDataCenter)
	{
		slot_loadDataToDCenterBtnClicked();
	}
	
}


//控制面板可操作性
void WaveWgt::setPannelEnable(bool state)
{
	ui.HScrollBar_windowPos->setEnabled(state);
	ui.hSlider_windowScale->setEnabled(state);
	ui.hSlider_currentTime->setEnabled(state);
	ui.btn_stop->setEnabled(state);
	ui.btn_play->setEnabled(state);
	ui.btn_pause->setEnabled(state);
}
//存储数据
void WaveWgt::loadData(const ST_WavDoubleData& data)
{
	m_data.fileTag = data.fileTag;

	auto loadDataIntoVec = [=](bool isLeft, const QVector<ST_AudioPoint>& data, QVector<ST_AudioPoint>& myVec)
		{
			myVec.clear();

			if (data.empty())
			{
				return;
			}

			ST_AudioPoint nullpoint;
			myVec = QVector<ST_AudioPoint>(data.size(), nullpoint);
			int OneOfHundredLine = data.size() / 100;//很难不超过100个点，所以不用和1比

			QString channelStr = isLeft ? QString("左") : QString("右");
			QString emitMshHead = QString("导入状态%1 :").arg(channelStr);

			for (int ptIndex = 0; ptIndex < data.size(); ptIndex++)
			{
				myVec[ptIndex] = data[ptIndex];
				if (ptIndex % OneOfHundredLine == 0)
				{
					int percentage = ptIndex / OneOfHundredLine;

					QString msgStr = emitMshHead + QString("存储图表数据 %1% ").arg(percentage);
					emit sgn_dataLoadState(percentage, msgStr);
				}
			}
			emit sgn_dataLoadState(100, emitMshHead + QString("存储结束"));
		
		};

	loadDataIntoVec(true, data.LeftChannel, m_data.LeftChannel);
	loadDataIntoVec(false, data.RightChannel, m_data.RightChannel);
	

}
//把数据写入图表
void WaveWgt::loadDataIntoCht(const EN_ZoomRate newZoomRate, QTime startTime, QTime endTime)
{
	m_leftCht->removeAllSeries();
	m_rightCht->removeAllSeries();

	if (m_data.fileTag.ChannelNum == 1)
	{
		ui.groupBox_rightCh->hide();
	}
	else if (m_data.fileTag.ChannelNum == 2)
	{
		ui.groupBox_rightCh->show();
	}

	auto loadDataToCht = [=](bool isLeft, const EN_ZoomRate newZoomRate,const ST_AudioFileTag& fileTag, const QVector<ST_AudioPoint>& dataVecRef,
		QTime loadStartTime,QTime loadEndTime,
		QLineSeries* Cht_series,
		QValueAxis* axis_x,
		QValueAxis* axis_y,
		QChart* Cht)
		{
			QString channelStr = isLeft ? QString("左") : QString("右");
			QString emitMshHead = QString("导入状态%1 :").arg(channelStr);


			int startMS = 0;
			int endMS = QTime(0, 0, 0).msecsTo(fileTag.Duration);

			axis_x->setRange(startMS, endMS);
			axis_y->setRange(-1, 1);

			//Cht->removeAllSeries();		

			int channelPtCount = dataVecRef.size();

			if (dataVecRef.empty())
			{
				emit sgn_dataLoadState(0, emitMshHead + QString("声道数据为空"));
				return;
			}

			Cht_series = new QLineSeries();

			int OneOfHundredLine = channelPtCount / 100;

			int oneWndPixelOnx = Cht->plotArea().width();

			int wndMsec = getZoomRateMsec(newZoomRate);

			double windowCount = (double)QTime(0, 0, 0).msecsTo(m_data.fileTag.Duration) / (double)wndMsec;

			int totalPixelOnX = windowCount * oneWndPixelOnx;
			int ptPerPixelOnX = 10;
			double ptDrawIntervalDouble = (double)channelPtCount / ((double)totalPixelOnX * (double)ptPerPixelOnX);

			int ptDrawInterval = std::max(ptDrawIntervalDouble, 1.0);

			int loadStartTimeMsec	= QTime(0, 0, 0).msecsTo(loadStartTime);
			int loadEndTimeMsec		= QTime(0, 0, 0).msecsTo(loadEndTime);

			for (int ptIndex = 0; ptIndex < dataVecRef.size(); ptIndex++)
			{
				const ST_AudioPoint& currentAudioPoint = dataVecRef[ptIndex];

				double pointSec = currentAudioPoint.pTime;
				double currentLevel = currentAudioPoint.pVal;

				double pointMsec = pointSec * 1000;

				if (pointMsec < loadStartTimeMsec)
				{
					continue;
				}
				else if (pointMsec > loadEndTimeMsec)
				{
					break;
				}

				if (ptIndex % ptDrawInterval == 0)
				{
					double currentPtMsec = pointSec * 1000;
					Cht_series->append(currentPtMsec, currentLevel);
				}

				if (ptIndex % OneOfHundredLine == 0)
				{
					int percentage = ptIndex / OneOfHundredLine;

					QString msgStr = emitMshHead + QString("写入图表数据 %1% ").arg(percentage);
					emit sgn_dataLoadState(percentage, msgStr);
				}
			}

			emit sgn_dataLoadState(100, emitMshHead + QString("导入结束"));

			Cht->addSeries(Cht_series);

			bool attachAxisStateA = Cht_series->attachAxis(axis_x);
			bool attachAxisStateB = Cht_series->attachAxis(axis_y);
		};




	loadDataToCht(true, newZoomRate, m_data.fileTag, m_data.LeftChannel, 
					startTime,endTime,
					m_leftCht_series_1DWave, 
					m_leftCht_axis_x_1DWave, 
					m_leftCht_axis_y_1DWave, 
					m_leftCht);
	if (m_data.fileTag.ChannelNum == 2)
	{
		loadDataToCht(false, newZoomRate, m_data.fileTag, m_data.RightChannel,
						startTime, endTime,
						m_rightCht_series_1DWave, 
						m_rightCht_axis_x_1DWave,
						m_rightCht_axis_y_1DWave, 
						m_rightCht);
	}
}



int WaveWgt::getZoomRateMsec(const EN_ZoomRate rate)
{
	int msec = -1;
	switch (rate)
	{
		case EN_ZoomRate::null	: msec = 0			; break;
		case EN_ZoomRate::Ms100	: msec = 100		; break;
		case EN_ZoomRate::Ms200	: msec = 200		; break;
		case EN_ZoomRate::Ms500	: msec = 500		; break;
		case EN_ZoomRate::Sec1	: msec = 1  * 1000		; break;
		case EN_ZoomRate::Sec2	: msec = 2  * 1000		; break;
		case EN_ZoomRate::Sec5	: msec = 5  * 1000		; break;
		case EN_ZoomRate::Sec10	: msec = 10 * 1000		; break;
		case EN_ZoomRate::Sec30	: msec = 30 * 1000		; break;
		case EN_ZoomRate::Min1	: msec = 60 * 1000		; break;
		case EN_ZoomRate::Min5	: msec = 5 * 60 * 1000	; break;
		case EN_ZoomRate::All	: msec = QTime(0, 0, 0).msecsTo(m_data.fileTag.Duration); break;
	}
	return msec;
}

QString WaveWgt::getZoomRateStr(const EN_ZoomRate rate)
{
	switch (rate)
	{
		case EN_ZoomRate::null		: return QString("null");
		case EN_ZoomRate::Ms100		: return QString("100ms");
		case EN_ZoomRate::Ms200		: return QString("200ms");
		case EN_ZoomRate::Ms500		: return QString("500ms");
		case EN_ZoomRate::Sec1		: return QString("1s");
		case EN_ZoomRate::Sec2		: return QString("2s");
		case EN_ZoomRate::Sec5		: return QString("5s");
		case EN_ZoomRate::Sec10		: return QString("10s");
		case EN_ZoomRate::Sec30		: return QString("30s");
		case EN_ZoomRate::Min1		: return QString("1min");
		case EN_ZoomRate::Min5		: return QString("5min");
		case EN_ZoomRate::All		: return QString("all");
	}
	return QString("error");
}

void WaveWgt::resetMaxZoomRate()
{
	int totalMsec = QTime(0, 0, 0).msecsTo(m_data.fileTag.Duration);
	if (totalMsec <= getZoomRateMsec(EN_ZoomRate::null))
	{
		m_nMaxZoomRate = EN_ZoomRate::null;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::null) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Ms100))
	{
		m_nMaxZoomRate = EN_ZoomRate::null;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Ms100) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Ms200))
	{
		m_nMaxZoomRate = EN_ZoomRate::Ms100;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Ms200) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Ms500))
	{
		//如果时长在500Ms以内，那么只有刻度100Ms 200Ms 下一个刻度就是all 没有500Ms 此时all就是最大尺寸 以此类推
		m_nMaxZoomRate = EN_ZoomRate::Ms200;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Ms500) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Sec1))
	{
		m_nMaxZoomRate = EN_ZoomRate::Ms500;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Sec1) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Sec2))
	{
		m_nMaxZoomRate = EN_ZoomRate::Sec1;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Sec2) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Sec5))
	{
		m_nMaxZoomRate = EN_ZoomRate::Sec2;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Sec5) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Sec10))
	{
		m_nMaxZoomRate = EN_ZoomRate::Sec5;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Sec10) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Sec30))
	{
		m_nMaxZoomRate = EN_ZoomRate::Sec10;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Sec30) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Min1))
	{
		m_nMaxZoomRate = EN_ZoomRate::Sec30;
	}
	else if (totalMsec > getZoomRateMsec(EN_ZoomRate::Min1) && totalMsec <= getZoomRateMsec(EN_ZoomRate::Min5))
	{
		m_nMaxZoomRate = EN_ZoomRate::Min1;
	}
	else
	{
		m_nMaxZoomRate = EN_ZoomRate::Min5;
	}
}

void WaveWgt::resetZoomSlider()
{
	int maxZoomValue = (int)m_nMaxZoomRate + 1;
	ui.hSlider_windowScale->setMaximum(maxZoomValue);
	ui.hSlider_windowScale->setValue(maxZoomValue);
	ui.hSlider_windowScale->setMinimum(1);
	m_nCurrentZoomRate = EN_ZoomRate::All;
	updateZoomSliderLabel();
}

EN_ZoomRate WaveWgt::getSliderZoomRate(int value)
{
	if (value == (int)m_nMaxZoomRate + 1)
	{
		return EN_ZoomRate::All;
	}
	return (EN_ZoomRate)value;
}

void WaveWgt::updateZoomSliderLabel()
{
	QString rateStrHead = QString("窗口长度：");
	QString rateStrVal;
	if (m_nCurrentZoomRate == EN_ZoomRate::All)
	{
		rateStrVal = m_data.fileTag.Duration.toString("hh:mm:ss");
	}
	else
	{
		rateStrVal = getZoomRateStr(m_nCurrentZoomRate);
	}

	ui.label_windowLength->setText(rateStrHead + rateStrVal);

	qDebug() << QString("sliderNewVal : %1 ZoomRateStr : %2").arg((int)m_nCurrentZoomRate).arg(rateStrVal);

}

void WaveWgt::resetWndPosScrollBar(const EN_ZoomRate newZoomRate)
{
	int pageStepMs = getZoomRateMsec(newZoomRate);
	ui.HScrollBar_windowPos->setMinimum(0);	
	ui.HScrollBar_windowPos->setPageStep(pageStepMs);	
	int FileLengthMs = QTime(0, 0, 0).msecsTo(m_data.fileTag.Duration);	
	ui.HScrollBar_windowPos->setMaximum(FileLengthMs - pageStepMs);

	if (newZoomRate == EN_ZoomRate::All)
	{
		m_WndPosStartTime = QTime(0, 0, 0);
	}
	else if (QTime(0, 0, 0).msecsTo(m_WndPosStartTime) > ui.HScrollBar_windowPos->maximum())
	{
		m_WndPosStartTime = QTime(0, 0, 0).addMSecs(ui.HScrollBar_windowPos->maximum());
	}
	m_WndPosEndTime = m_WndPosStartTime.addMSecs(pageStepMs);

	updateWndPosScrollBarLabel();
}

void WaveWgt::updateWndPosScrollBarLabel()
{
	QString wndStartStr = QString("窗口开始时间:%1").arg(m_WndPosStartTime.toString("mm:ss.zzz"));
	QString wndEndStr	= QString("窗口结束时间:%1").arg(m_WndPosEndTime.toString("mm:ss.zzz"));
	ui.label_windowStartTime->setText(wndStartStr);
	ui.label_windowEndTime->setText(wndEndStr);
}

void WaveWgt::chartWndPosChanged(QTime startTime, QTime endTime)
{
	int startMsec	= QTime(0, 0, 0).msecsTo(startTime);
	int endMsec		= QTime(0, 0, 0).msecsTo(endTime);
	m_leftCht_axis_x_1DWave->setRange(startMsec, endMsec);
	if (m_data.fileTag.ChannelNum == 2)
	{
		m_rightCht_axis_x_1DWave->setRange(startMsec, endMsec);
	}
}


void WaveWgt::resetPannel()
{
	resetMaxZoomRate();
	resetZoomSlider();
	resetWndPosScrollBar(m_nCurrentZoomRate);
	resetLoadTimeEdit();
}

void WaveWgt::resetLoadTimeEdit()
{
	m_chtLoadStartTime	= QTime(0, 0, 0);
	m_chtLoadEndTime	= m_data.fileTag.Duration;

	ui.timeEdit_chtLoadStartTime->setMinimumTime(m_chtLoadStartTime);
	ui.timeEdit_chtLoadStartTime->setMaximumTime(m_chtLoadEndTime);
	ui.timeEdit_chtLoadStartTime->setTime(m_chtLoadStartTime);
	ui.timeEdit_chtLoadEndTime->setMinimumTime(m_chtLoadStartTime);
	ui.timeEdit_chtLoadEndTime->setMaximumTime(m_chtLoadEndTime);
	ui.timeEdit_chtLoadEndTime->setTime(m_chtLoadEndTime);
}

void WaveWgt::generateVolumnMap()
{
	m_mapMsecVolumn.clear();

	double		volumnIntervalMs		= m_nVolumnUpdateIntervalMs;
	double		sampleRate				= m_data.fileTag.sampleRate;
	double		intervalPtCount			= sampleRate * volumnIntervalMs / 1000;
	int			volumnCount				= QTime(0, 0, 0).msecsTo(m_data.fileTag.Duration) / volumnIntervalMs + 1;
	int			maxIndex				= m_data.LeftChannel.size() - 1;

	for (int VolumnIndex = 0; VolumnIndex < volumnCount; VolumnIndex++)
	{
		int startPtIndex = intervalPtCount * VolumnIndex;
		int endPtIndex = qMin((int)(intervalPtCount * (VolumnIndex + 1)), maxIndex);

		double maxDB = 0;
		double totalDB = 0;
		int	   countPt = 0;
		for (int ptIndex = startPtIndex; ptIndex <= endPtIndex; ptIndex++)
		{
			double absLeftVal = abs(m_data.LeftChannel[ptIndex].pVal);
			double absLeftDB = AudioProtocol::fftRealToDB(absLeftVal,const_audio_normalAudioFileMaxDB);
			
			maxDB = qMax(absLeftDB, maxDB);
			countPt += 1;
			totalDB += absLeftDB;

			if (m_data.fileTag.ChannelNum == 2)
			{
				double absRightVal = abs(m_data.RightChannel[ptIndex].pVal);
				double absRightDB = AudioProtocol::fftRealToDB(absRightVal, const_audio_normalAudioFileMaxDB);
				maxDB = qMax(absRightDB, maxDB);
				countPt += 1;
				totalDB += absRightDB;
			}
		}

		double AvrDB = totalDB / (double)countPt;

		int CurrentMsec = VolumnIndex * volumnIntervalMs;
		m_mapMsecVolumn.insert(CurrentMsec, maxDB);

	}
	int a = 0;

}

void WaveWgt::slot_windowLengthSliderMove(int newValue)
{
	m_nCurrentZoomRate = getSliderZoomRate(newValue);
	updateZoomSliderLabel();
	resetWndPosScrollBar(m_nCurrentZoomRate);
	loadDataIntoCht(m_nCurrentZoomRate, m_chtLoadStartTime, m_chtLoadEndTime);
	chartWndPosChanged(m_WndPosStartTime, m_WndPosEndTime);
}

void WaveWgt::slot_WndPosScrollBarMove(int value)
{
	m_WndPosStartTime = QTime(0, 0, 0).addMSecs(value);
	m_WndPosEndTime = m_WndPosStartTime.addMSecs(ui.HScrollBar_windowPos->pageStep());
	chartWndPosChanged(m_WndPosStartTime, m_WndPosEndTime);
	updateWndPosScrollBarLabel();
}

void WaveWgt::slot_reloadBtnClicked()
{
	QTime startTime = ui.timeEdit_chtLoadStartTime->time();
	QTime endTime = ui.timeEdit_chtLoadEndTime->time();
	if (startTime >= endTime)
	{
		ui.label_reloadState->setText("重新载入状态：输入无效");
		return;
	}
	m_chtLoadStartTime = startTime;
	m_chtLoadEndTime = endTime;
	loadDataIntoCht(m_nCurrentZoomRate, m_chtLoadStartTime, m_chtLoadEndTime);
	ui.label_reloadState->setText("重新载入状态：重载结束");
}

void WaveWgt::slot_reloadAllBtnClicked()
{
	ui.timeEdit_chtLoadStartTime->setTime(QTime(0,0,0));
	ui.timeEdit_chtLoadEndTime->setTime(m_data.fileTag.Duration);
	slot_reloadBtnClicked();
}

void WaveWgt::slot_loadDataToDCenterBtnClicked()
{
	ST_WavDoubleData loadData;
	loadData.fileTag = m_data.fileTag;

	QTime startTime = ui.timeEdit_chtLoadStartTime->time();
	QTime endTime = ui.timeEdit_chtLoadEndTime->time();
	if (startTime >= endTime)
	{
		ui.label_reloadState->setText("存储状态：时间范围无效");
		return;
	}

	auto loadDataToVec = [](QTime startTime,QTime endTime, const QVector<ST_AudioPoint>& fromVec, QVector<ST_AudioPoint>& toVec)
		{
			toVec.clear();

			double startMsec	= QTime(0,0,0).msecsTo(startTime);
			double endMsec		= QTime(0, 0, 0).msecsTo(endTime);

			for (int ptIndex = 0; ptIndex < fromVec.size(); ptIndex++)
			{
				const ST_AudioPoint& point = fromVec[ptIndex];
				double PtMsec = point.pTime * 1000;
				if (PtMsec < startMsec)
				{
					continue;
				}
				else if (PtMsec > endMsec)
				{
					break;
				}

				toVec.push_back(point);

			}
		};

	loadDataToVec(startTime, endTime, m_data.LeftChannel, loadData.LeftChannel);
	loadDataToVec(startTime, endTime, m_data.RightChannel, loadData.RightChannel);
	
	bool saveState = false;
	emit sgn_saveWavData(loadData, saveState);

	ui.label_reloadState->setText(QString("存储状态：%1").arg(saveState ?QString("成功") : QString("失败")));

}

void WaveWgt::slot_playBtnClicked()
{
	emit sgn_playBtnClicked();
	m_nCurrentVolumnUpdateCount = -1;
	slot_updateVolumn();
	m_pVolumnUpdateTimer->start();
}

void WaveWgt::slot_jumpBtnClicked()
{
	//emit sgn_jumpBtnClicked();
	//m_pVolumnUpdateTimer->stop();
}

void WaveWgt::slot_stopBtnClicked()
{
	emit sgn_stopBtnClicked();
	m_pVolumnUpdateTimer->stop();
}

void WaveWgt::slot_updateVolumn()
{
	m_nCurrentVolumnUpdateCount += 1;
	int msec = m_nCurrentVolumnUpdateCount * m_nVolumnUpdateIntervalMs;

	if (QTime(0, 0, 0).addMSecs(msec) >= m_data.fileTag.Duration)
	{
		m_pVolumnUpdateTimer->stop();
		m_nCurrentVolumnUpdateCount = -1;
	}

	auto pos = m_mapMsecVolumn.upperBound(msec);
	if (pos == m_mapMsecVolumn.end())
	{
		return;
	}

	double dbVal= pos.value();
	m_pVolumnBar->setVal(dbVal);
	qDebug() << "updateVolumn : dbVal : " << dbVal;
}