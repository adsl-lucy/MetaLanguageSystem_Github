#include "FFTWindowWgt.h"
#pragma execution_character_set("utf-8")

FFTWindowWgt::FFTWindowWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUI();
	initWndTimeCht();
	initWndFFTSpectrumCht();
	initWndPartBarCht();
	initWndConstrainResultCht();
	initEffOscWgt();

	initActiveFuncCht();
	initActiveWndFFTSpectrumCht();
}

FFTWindowWgt::~FFTWindowWgt()
{}

void FFTWindowWgt::initUI()
{
	m_pBtnGroupFFTWndLengthType = new QButtonGroup(this);
	m_pBtnGroupFFTWndLengthType->addButton(ui.radioBtn_WndLengthType_Time, 0);
	m_pBtnGroupFFTWndLengthType->addButton(ui.radioBtn_WndLengthType_Point, 1);
	m_pBtnGroupFFTWndLengthType->setExclusive(true);
	connect(m_pBtnGroupFFTWndLengthType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_WndLengthTypeChanged(); });
	ui.radioBtn_WndLengthType_Point->setChecked(true);
	slot_WndLengthTypeChanged();
	connect(ui.btn_GenWndTimeGraph, &QPushButton::clicked, this, &FFTWindowWgt::slot_GenFFTWndTimeGraphBtnClicked);

	m_pBtnGroupActiveWndStartTimeType = new QButtonGroup(this);
	m_pBtnGroupActiveWndStartTimeType->addButton(ui.radioButton_ActiveStartType_Time, 0);
	m_pBtnGroupActiveWndStartTimeType->addButton(ui.radioButton_ActiveStartType_Ratio, 1);
	m_pBtnGroupActiveWndStartTimeType->setExclusive(true);
	connect(m_pBtnGroupActiveWndStartTimeType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_ActiveWndStartTimeTypeChanged(); });
	ui.radioButton_ActiveStartType_Ratio->setChecked(true);
	slot_ActiveWndStartTimeTypeChanged();

	m_pBtnGroupActiveWndValShowType = new QButtonGroup(this);
	m_pBtnGroupActiveWndValShowType->setExclusive(false);
	m_pBtnGroupActiveWndValShowType->addButton(ui.checkBox_ActiveWnd_ShowType_STFTWnd, 0);
	m_pBtnGroupActiveWndValShowType->addButton(ui.checkBox_ActiveWnd_ShowType_ActiveVal, 1);
	m_pBtnGroupActiveWndValShowType->addButton(ui.checkBox_ActiveWnd_ShowType_ActiveWnd, 2);
	
	connect(m_pBtnGroupActiveWndValShowType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_ActiveWndShowTypeBtnChanged(); });


	ui.comboBox_WndType->setItemData(0, QVariant((int)EN_STFTWndType::Rect));
	ui.comboBox_WndType->setItemData(1, QVariant((int)EN_STFTWndType::Hann));
	ui.progressBar_dataLoadState->setValue(0);

	connect(this, &FFTWindowWgt::sgn_generateFFTWndTimeGraph, FFTWindowManager::instance(), &FFTWindowManager::slot_generateSTFTWindow);
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_WndFFTGenState, this, &FFTWindowWgt::slot_getFFTWindowManagerMsg);
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_WndFFTAnsEnd, this, &FFTWindowWgt::slot_getWndFFTResult);
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_WndConstrainResultAnsEnd, this, &FFTWindowWgt::slot_getWndConstrainResult);

	m_pBtnGroupFFTWndFFTValShowType = new QButtonGroup(this);
	m_pBtnGroupFFTWndFFTValShowType->addButton(ui.radioButton_WndFFTValType_AbsoluteVal, 0);
	m_pBtnGroupFFTWndFFTValShowType->addButton(ui.radioButton_WndFFTValType_db, 1);
	m_pBtnGroupFFTWndFFTValShowType->setExclusive(true);
	connect(ui.btn_GenWndFFTGraph, &QPushButton::clicked, this, &FFTWindowWgt::slot_GenFFTWndFFTGraphBtnClicked);
	connect(ui.btn_updateWndFFTCht, &QPushButton::clicked, this, &FFTWindowWgt::slot_UpdateFFTWndFFTGraphBtnClicked);

	connect(ui.btn_updateWndFFTPartCht, &QPushButton::clicked, this, &FFTWindowWgt::slot_updateFFTPartCht);
	connect(ui.btn_GenWndSpecConstrainResult, &QPushButton::clicked, this, &FFTWindowWgt::slot_GenWndConstrainResultBtnClicked);
	connect(ui.checkBox_forcePt2DBVal, &QCheckBox::clicked, this, [=]()
		{
			ui.DSBox_forcePt2DBVal->setEnabled(ui.checkBox_forcePt2DBVal->isChecked());
		});

	connect(ui.btn_GenActiveFunc, &QPushButton::clicked, this, &FFTWindowWgt::slot_GenActiveWndBtnClicked);
	connect(ui.btn_updateActiveWndFFTCht, &QPushButton::clicked, this, &FFTWindowWgt::slot_UpdateActiveWndFFTGraphBtnClicked);
	connect(ui.btn_GenActiveWndFFTGraph, &QPushButton::clicked, this, &FFTWindowWgt::slot_GenActiveWndFFTGraphBtnClicked);
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_ActiveWndGenState, this, &FFTWindowWgt::slot_getActiveWndMsg);
	connect(FFTWindowManager::instance(), &FFTWindowManager::sgn_ActiveWndAnsEnd, this, &FFTWindowWgt::slot_getActiveWndANSResult);

}

void FFTWindowWgt::initWndTimeCht()
{
	m_axis_WndTimeGraph_Time = new QValueAxis();
	m_axis_WndTimeGraph_Time->setRange(0, 1000);
	m_axis_WndTimeGraph_Time->setLabelFormat("%.1f");
	m_axis_WndTimeGraph_Time->setTitleText(" time In Window(ms)");

	m_axis_WndTimeGraph_ptIndex = new QValueAxis();
	m_axis_WndTimeGraph_ptIndex->setRange(0, 4096);
	m_axis_WndTimeGraph_ptIndex->setLabelFormat("%.0f");
	m_axis_WndTimeGraph_ptIndex->setTitleText("point In Window(index)");

	m_axis_WndTimeGraph_ptval = new QValueAxis();
	m_axis_WndTimeGraph_ptval->setRange(0, 100);
	m_axis_WndTimeGraph_ptval->setLabelFormat("%.1f");
	m_axis_WndTimeGraph_ptval->setTitleText("val(Percentage)");

	m_series_WndTimeGraph = nullptr;

	m_cht_WndTimeGraph = new QChart();

	m_cht_WndTimeGraph->setTitle("FFT Window :");
	m_cht_WndTimeGraph->legend()->hide();
	m_cht_WndTimeGraph->addAxis(m_axis_WndTimeGraph_Time, Qt::AlignBottom);
	m_cht_WndTimeGraph->addAxis(m_axis_WndTimeGraph_ptIndex, Qt::AlignTop);
	m_cht_WndTimeGraph->addAxis(m_axis_WndTimeGraph_ptval, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_WndTimeGraph = new QChartView(m_cht_WndTimeGraph);
	m_chtView_WndTimeGraph->setRenderHint(QPainter::Antialiasing);
	m_chtView_WndTimeGraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_WndTimeGraph->setMinimumSize(980, 230);

	ui.HLayout_FFTWnd_TimeCht->insertWidget(0, m_chtView_WndTimeGraph);
}

void FFTWindowWgt::initActiveFuncCht()
{
	m_axis_ActiveFunc_Time = new QValueAxis();
	m_axis_ActiveFunc_Time->setRange(0, 1000);
	m_axis_ActiveFunc_Time->setLabelFormat("%.1f");
	m_axis_ActiveFunc_Time->setTitleText(" time In Window(ms)");

	m_axis_ActiveFunc_ptIndex = new QValueAxis();
	m_axis_ActiveFunc_ptIndex->setRange(0, 4096);
	m_axis_ActiveFunc_ptIndex->setLabelFormat("%.0f");
	m_axis_ActiveFunc_ptIndex->setTitleText("point In Window(index)");

	m_axis_ActiveFunc_ptval = new QValueAxis();
	m_axis_ActiveFunc_ptval->setRange(0, 100);
	m_axis_ActiveFunc_ptval->setLabelFormat("%.1f");
	m_axis_ActiveFunc_ptval->setTitleText("val(Percentage)");

	m_series_ActiveWnd_STFTWnd = nullptr;
	m_series_ActiveWnd_Active = nullptr;
	m_series_ActiveWnd_ActiveWnd = nullptr;

	m_cht_ActiveWndPt = new QChart();

	m_cht_ActiveWndPt->setTitle("ActiveWndVal :");
	m_cht_ActiveWndPt->legend()->show();
	m_cht_ActiveWndPt->addAxis(m_axis_ActiveFunc_Time, Qt::AlignBottom);
	m_cht_ActiveWndPt->addAxis(m_axis_ActiveFunc_ptIndex, Qt::AlignTop);
	m_cht_ActiveWndPt->addAxis(m_axis_ActiveFunc_ptval, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_ActiveWndPt = new QChartView(m_cht_ActiveWndPt);
	m_chtView_ActiveWndPt->setRenderHint(QPainter::Antialiasing);
	m_chtView_ActiveWndPt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_ActiveWndPt->setMinimumSize(980, 230);

	ui.HLayout_FFTWnd_ActiveFunc_Cht->insertWidget(0, m_chtView_ActiveWndPt);
}

void FFTWindowWgt::initWndFFTSpectrumCht()
{
	m_axis_WndFFTFreq = new QValueAxis();
	m_axis_WndFFTFreq->setRange(0, 20000);
	m_axis_WndFFTFreq->setLabelFormat("%.0f");
	m_axis_WndFFTFreq->setTitleText("Frequency(HZ)");

	m_axis_WndFFTFreqAmp = new QValueAxis();
	m_axis_WndFFTFreqAmp->setRange(0, 100);
	m_axis_WndFFTFreqAmp->setLabelFormat("%.1f");
	m_axis_WndFFTFreqAmp->setTitleText("Freq Amp ");

	m_series_WndFFTResult = nullptr;

	m_cht_WndFFT = new QChart();

	m_cht_WndFFT->setTitle("FFT result");
	m_cht_WndFFT->legend()->hide();
	m_cht_WndFFT->addAxis(m_axis_WndFFTFreq, Qt::AlignBottom);
	m_cht_WndFFT->addAxis(m_axis_WndFFTFreqAmp, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_WndFFT = new QChartView(m_cht_WndFFT);
	m_chtView_WndFFT->setRenderHint(QPainter::Antialiasing);
	m_chtView_WndFFT->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	ui.VLayout_FFTWndSpectrum_Cht->insertWidget(0, m_chtView_WndFFT);
}

void FFTWindowWgt::initActiveWndFFTSpectrumCht()
{
	m_axis_ActiveWndFFTFreq = new QValueAxis();
	m_axis_ActiveWndFFTFreq->setRange(0, 20000);
	m_axis_ActiveWndFFTFreq->setLabelFormat("%.0f");
	m_axis_ActiveWndFFTFreq->setTitleText("Frequency(HZ)");

	m_axis_ActiveWndFFTFreqAmp = new QValueAxis();
	m_axis_ActiveWndFFTFreqAmp->setRange(0, 100);
	m_axis_ActiveWndFFTFreqAmp->setLabelFormat("%.1f");
	m_axis_ActiveWndFFTFreqAmp->setTitleText("Freq Amp ");

	m_series_ActiveWndFFTResult = nullptr;

	m_cht_ActiveWndFFT = new QChart();
	m_cht_ActiveWndFFT->setTitle("FFT result");
	m_cht_ActiveWndFFT->legend()->hide();
	m_cht_ActiveWndFFT->addAxis(m_axis_ActiveWndFFTFreq, Qt::AlignBottom);
	m_cht_ActiveWndFFT->addAxis(m_axis_ActiveWndFFTFreqAmp, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_ActiveWndFFT = new QChartView(m_cht_ActiveWndFFT);
	m_chtView_ActiveWndFFT->setRenderHint(QPainter::Antialiasing);
	m_chtView_ActiveWndFFT->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	ui.VLayout_ActiveFFTWndSpectrum_Cht->insertWidget(0, m_chtView_ActiveWndFFT);
}

void FFTWindowWgt::initWndPartBarCht()
{
	m_WndFFTPartSeries = nullptr;

	m_WndFFTPartAxisY = new QValueAxis();
	m_WndFFTPartAxisY->setRange(0, 40);

	m_WndFFTPartAxisX = new QBarCategoryAxis();	

	m_WndFFTPartCht = new QChart();
	//m_WndFFTPartchart->addSeries(series);
	m_WndFFTPartCht->setTitle("FFT 窗函数误差统计");
	m_WndFFTPartCht->setAnimationOptions(QChart::NoAnimation);
	m_WndFFTPartCht->addAxis(m_WndFFTPartAxisX, Qt::AlignBottom);
	m_WndFFTPartCht->addAxis(m_WndFFTPartAxisY, Qt::AlignLeft);
	m_WndFFTPartCht->legend()->setVisible(true);
	m_WndFFTPartCht->legend()->setAlignment(Qt::AlignBottom);
	

	m_WndFFTPartChtView = new QChartView(m_WndFFTPartCht);
	m_WndFFTPartChtView->setRenderHint(QPainter::Antialiasing);
	ui.HLayout_WndFFTPart_Cht->insertWidget(0, m_WndFFTPartChtView);

}

void FFTWindowWgt::initWndConstrainResultCht()
{
	m_WndConstrainResultSeries = nullptr;

	m_WndConstrainResultAxisY = new QValueAxis();
	m_WndConstrainResultAxisY->setRange(0, 80);

	m_WndConstrainResultAxisX = new QBarCategoryAxis();

	m_WndConstrainResultCht = new QChart();
	//m_WndFFTPartchart->addSeries(series);
	m_WndConstrainResultCht->setTitle("窗函数抑制结果");
	m_WndConstrainResultCht->setAnimationOptions(QChart::NoAnimation);
	m_WndConstrainResultCht->addAxis(m_WndConstrainResultAxisX, Qt::AlignBottom);
	m_WndConstrainResultCht->addAxis(m_WndConstrainResultAxisY, Qt::AlignLeft);
	m_WndConstrainResultCht->legend()->setVisible(true);
	m_WndConstrainResultCht->legend()->setAlignment(Qt::AlignBottom);


	m_WndConstrainResultChtView = new QChartView(m_WndConstrainResultCht);
	m_WndConstrainResultChtView->setRenderHint(QPainter::Antialiasing);
	ui.HLayout_WndSepcConstrainOutput->insertWidget(0, m_WndConstrainResultChtView);
}

void FFTWindowWgt::initEffOscWgt()
{
	m_pEffOscWgt = new EffOscWidget(this);
	ui.VLayout_EffOscWidget->insertWidget(0, m_pEffOscWgt);
	connect(m_pEffOscWgt, &EffOscWidget::sgn_GoBDSNRResult, this, &FFTWindowWgt::sgn_GoBDSNRResult);
}

ST_STFTWndPara FFTWindowWgt::getWndPara()
{
	ST_STFTWndPara para;
	para.WndType = (EN_STFTWndType)ui.comboBox_WndType->currentData().toInt();
	para.sampleRate = ui.SBox_WndSampleRate->value();

	if (ui.radioBtn_WndLengthType_Point->isChecked())
	{
		para.pointCount = ui.SBox_WndLengthPointCount->value();
		para.WndMsec = (double)para.pointCount / (double)para.sampleRate * 1000;

	}
	else if (ui.radioBtn_WndLengthType_Time->isChecked())
	{
		para.WndMsec = ui.DSBox_WndLength_TimeMSec->value();
		para.pointCount = para.WndMsec / 1000.0 * para.sampleRate;
	}
	return para;
}

void FFTWindowWgt::slot_AudoGenWndSpecConstrainResult(QString dataKey)
{
	ui.tabWidget_Main->setCurrentIndex(1);
	m_pEffOscWgt->slot_GenWndSpecConstrainBtnClicked();
}

void FFTWindowWgt::slot_WndLengthTypeChanged()
{
	ui.DSBox_WndLength_TimeMSec->setEnabled(false);
	ui.SBox_WndLengthPointCount->setEnabled(false);
	if (ui.radioBtn_WndLengthType_Point->isChecked())
	{
		ui.SBox_WndLengthPointCount->setEnabled(true);
	}
	else if (ui.radioBtn_WndLengthType_Time->isChecked())
	{
		ui.DSBox_WndLength_TimeMSec->setEnabled(true);
	}
}

void FFTWindowWgt::slot_ActiveWndStartTimeTypeChanged()
{
	ui.DSBox_ActiveStartTime->setEnabled(false);
	ui.DSBox_ActiveStartRatio->setEnabled(false);
	if (ui.radioButton_ActiveStartType_Time->isChecked())
	{
		ui.DSBox_ActiveStartTime->setEnabled(true);
	}
	else if (ui.radioButton_ActiveStartType_Ratio->isChecked())
	{
		ui.DSBox_ActiveStartRatio->setEnabled(true);
	}
}

void FFTWindowWgt::slot_ActiveWndShowTypeBtnChanged()
{
	QList<QAbstractSeries*> SeriesList = m_cht_ActiveWndPt->series();

	if (SeriesList.isEmpty())
	{
		return;
	}

	for (QAbstractSeries* pSeries : SeriesList)
	{
		if (pSeries->name() == QString("STFT Wnd Val"))
		{
			pSeries->setVisible(ui.checkBox_ActiveWnd_ShowType_STFTWnd->isChecked());
		}

		if (pSeries->name() == QString("Active Val"))
		{
			pSeries->setVisible(ui.checkBox_ActiveWnd_ShowType_ActiveVal->isChecked());
		}

		if (pSeries->name() == QString("ActiveWnd Val"))
		{
			pSeries->setVisible(ui.checkBox_ActiveWnd_ShowType_ActiveWnd->isChecked());
		}
	}

}

void FFTWindowWgt::slot_GenActiveWndFFTGraphBtnClicked()
{
	ST_ActiveWndAnsPara ActiveWndAnsPara;
	ActiveWndAnsPara.WndPara = getActWndPara();
	ActiveWndAnsPara.showMaxFreq		= ui.SBox_ActiveWndFFTShowMaxFreq->value();
	ActiveWndAnsPara.showFreqPtCount	= ui.SBox_ActiveWndFFTShowPointCount->value();

	FFTWindowManager::instance()->slot_startGenActiveWndFFTResult(ActiveWndAnsPara);
}

void FFTWindowWgt::slot_getActiveWndMsg(int percentage, int threadCount, QString msg)
{
	ui.progressBar_ActiveFuncLoadState->setValue(percentage);
	//ui.label_GenState->setText(QString("生成状态：活跃线程 %1 %2").arg(threadCount).arg(msg));
}

void FFTWindowWgt::slot_getActiveWndANSResult(ST_ActiveWndAnsResult& result)
{
	loadActiveWndFFTResult(result);
}

void FFTWindowWgt::slot_ActiveWndFFTMouseHovered(const QPointF& point, bool state)
{
	QToolTip::showText(QCursor::pos(), QString("point : freq :%1  val :%2").arg(point.x(), 0, 'f', 2).arg(point.y(), 0, 'f', 2));
}

void FFTWindowWgt::slot_UpdateActiveWndFFTGraphBtnClicked()
{
	m_axis_ActiveWndFFTFreqAmp->setRange(ui.SBox_ActiveWndFFTShowMinVal->value(), 0);
	m_axis_ActiveWndFFTFreq->setRange(0, ui.SBox_ActiveWndFFTShowMaxFreq->value());
	m_cht_ActiveWndFFT->update();
}

void FFTWindowWgt::slot_GenFFTWndTimeGraphBtnClicked()
{
	ST_STFTWnd result;
	ST_STFTWndPara& para = result.WndPara;
	para = getWndPara();

	emit sgn_generateFFTWndTimeGraph(result);

	QString ChtName;
	switch (result.WndPara.WndType)
	{
		case EN_STFTWndType::Rect:ChtName = QString("Wnd Rect"); break;
		case EN_STFTWndType::Hann:ChtName = QString("Wnd Hann"); break;
	}
	loadWndToCht(ChtName, result);
	updateSTFTWndLabel(para.WndMsec, para.pointCount);	
}

void FFTWindowWgt::updateSTFTWndLabel(double WndMsec, int WndPtCount)
{
	ui.label_resultWndLength_Point->setText(QString("窗型等价点数：%1").arg(WndPtCount));
	ui.label_resultWndLength_Time->setText(QString("窗型等价时长：%1 ms").arg(WndMsec, 0, 'f', 2));
	double FFTDeltaFreq = 1.0 / (WndMsec / 1000);
	ui.label_WndSTFTFreqDelta->setText(QString("FFT输出频率间隔：%1 hz").arg(FFTDeltaFreq, 0, 'f', 2));
}

void FFTWindowWgt::loadWndToCht(QString ChtName, ST_STFTWnd& WndResult)
{
	m_axis_WndTimeGraph_ptIndex->setRange(0, WndResult.WndPara.pointCount - 1);
	m_axis_WndTimeGraph_ptval->setRange(0, 1);
	m_axis_WndTimeGraph_Time->setRange(0, WndResult.WndPara.WndMsec);

	m_cht_WndTimeGraph->removeAllSeries();

	int hundredsOfPt = qMax(1,WndResult.VecWndPt.size() / 100);
	m_series_WndTimeGraph = new QLineSeries();
	m_cht_WndTimeGraph->setTitle(ChtName);

	double msecInterval = 1000.0 / WndResult.WndPara.sampleRate;

	for (int ptIndex = 0; ptIndex < WndResult.VecWndPt.size(); ptIndex++)
	{
		double val = WndResult.VecWndPt[ptIndex];
		double msec = ptIndex * msecInterval;
		m_series_WndTimeGraph->append(msec, val);

		if (ptIndex % hundredsOfPt == 0)
		{
			ui.progressBar_dataLoadState->setValue(ptIndex / hundredsOfPt);
		}
	}

	ui.progressBar_dataLoadState->setValue(100);

	m_cht_WndTimeGraph->addSeries(m_series_WndTimeGraph);

	bool attachAxisStateA = m_series_WndTimeGraph->attachAxis(m_axis_WndTimeGraph_Time);
	bool attachAxisStateB = m_series_WndTimeGraph->attachAxis(m_axis_WndTimeGraph_ptval);


	//自己看看窗型内不同时刻的权重情况	
	if (true)
	{
		int testWndPointCount = 8;

		int moveMsec = 20;
		int testWndTimeGap = (double)moveMsec / (double)1000 * (double)WndResult.WndPara.sampleRate;

		//int testWndTimeGap    = WndResult.WndPara.pointCount / 4;
		int OneTimeHaveShowTime = (WndResult.WndPara.pointCount - 1) / testWndTimeGap + 1;

		QVector<double> nullWeightVec = QVector<double>(OneTimeHaveShowTime + 1, 0); //不同时刻的权重，最后加一个总权重

		QVector<QVector<double>> resultVec = QVector<QVector<double>>(testWndPointCount, nullWeightVec);

		for (int EstPtIndex = 0; EstPtIndex < resultVec.size(); EstPtIndex++)
		{
			QVector<double>& WeightVecRef = resultVec[EstPtIndex];
			for (int PtInWndIndex = 0; PtInWndIndex < OneTimeHaveShowTime + 1; PtInWndIndex++)
			{
				double weight = 0;

				if (PtInWndIndex == OneTimeHaveShowTime)
				{
					for (int PtInWndIndex = 0; PtInWndIndex < OneTimeHaveShowTime; PtInWndIndex++)
					{
						weight += WeightVecRef[PtInWndIndex];
					}
				}
				else
				{
					int ptInWndIndex = testWndTimeGap / testWndPointCount * EstPtIndex + PtInWndIndex * testWndTimeGap;
					if (ptInWndIndex < WndResult.VecWndPt.size() && ptInWndIndex >= 0)
					{
						weight = WndResult.VecWndPt[ptInWndIndex];
					}
				}		
				WeightVecRef[PtInWndIndex] = weight;
			}
		
		}

		int a = 0;
	}



}

void FFTWindowWgt::slot_GenFFTWndFFTGraphBtnClicked()
{
	ST_STFTWndAnsPara WndFFTPara;
	WndFFTPara.WndPara = getWndPara();
	WndFFTPara.showMaxFreq = ui.SBox_WndFFTShowMaxFreq->value();
	WndFFTPara.showFreqPtCount = ui.SBox_WndFFTShowPointCount->value();

	FFTWindowManager::instance()->slot_startGenerateSTFTWindowFFTResult(WndFFTPara);
}

void FFTWindowWgt::slot_getWndFFTResult(ST_STFTWndAnsResult& result)
{
	saveWndFFTResult(result);
	loadWndFFTResult(result);
	loadWndFFTPartEstimate(result);
}

void FFTWindowWgt::slot_UpdateFFTWndFFTGraphBtnClicked()
{
	m_axis_WndFFTFreqAmp->setRange(ui.SBox_WndFFTShowMinVal->value(), 0);
	m_axis_WndFFTFreq->setRange(0, ui.SBox_WndFFTShowMaxFreq->value());
	m_cht_WndFFT->update();
}

void FFTWindowWgt::slot_getFFTWindowManagerMsg(int percentage, int threadCount, QString msg)
{
	ui.progressBar_dataLoadState->setValue(percentage);
	ui.label_GenState->setText(QString("生成状态：活跃线程 %1 %2").arg(threadCount).arg(msg));
}

void FFTWindowWgt::saveWndFFTResult(ST_STFTWndAnsResult& result)
{
	m_tempWndFFTResult.maxAmp = result.maxAmp;
	m_tempWndFFTResult.VecWndFFTPart.clear();
	for (int partIndex = 0; partIndex < result.VecWndFFTPart.size(); partIndex++)
	{
		m_tempWndFFTResult.VecWndFFTPart.append(result.VecWndFFTPart[partIndex]);
	}
}

void FFTWindowWgt::loadWndFFTResult(ST_STFTWndAnsResult& result)
{
	m_axis_WndFFTFreq->setRange(0, result.AnsPara.showMaxFreq);	
	if (m_series_WndFFTResult != nullptr)
	{
		disconnect(m_series_WndFFTResult, &QLineSeries::hovered, this, &FFTWindowWgt::slot_WndFFTMouseHovered);
	}
	m_cht_WndFFT->removeAllSeries();

	m_series_WndFFTResult = new QLineSeries();

	double maxAmp = 0;
	double minVal = 0;
	//QVector<double> resultDbVec;

	m_vecWndFFTPt.clear();
	ST_FFTPoint nullpt;
	m_vecWndFFTPt = QVector<ST_FFTPoint>(result.VecWndFFTPt.size(), nullpt);

	if (ui.radioButton_WndFFTValType_AbsoluteVal->isChecked())
	{
		minVal = 0;
		for (int ptIndex = 0; ptIndex < result.VecWndFFTPt.size(); ptIndex++)
		{
			const ST_FFTPoint& resultPt = result.VecWndFFTPt[ptIndex];
			m_series_WndFFTResult->append(resultPt.frequency, resultPt.amplitude);
			m_vecWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecWndFFTPt[ptIndex].amplitude = resultPt.amplitude;
			maxAmp = qMax(maxAmp, resultPt.amplitude);
		}	
	}
	else
	{

		
		for (int ptIndex = 0; ptIndex < result.VecWndFFTPt.size(); ptIndex++)
		{
			const ST_FFTPoint& resultPt = result.VecWndFFTPt[ptIndex];
			double resultDb = AudioProtocol::getRelativeDB(resultPt.amplitude, result.maxAmp);
			m_series_WndFFTResult->append(resultPt.frequency, resultDb);
			m_vecWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecWndFFTPt[ptIndex].amplitude = resultDb;
			minVal = qMin(minVal, resultDb);
		}
		int a = 0;
	}

	m_axis_WndFFTFreqAmp->setRange(ui.SBox_WndFFTShowMinVal->value(), maxAmp);

	m_cht_WndFFT->addSeries(m_series_WndFFTResult);

	connect(m_series_WndFFTResult, &QLineSeries::hovered, this, &FFTWindowWgt::slot_WndFFTMouseHovered);

	bool attachAxisStateA = m_series_WndFFTResult->attachAxis(m_axis_WndFFTFreq);
	bool attachAxisStateB = m_series_WndFFTResult->attachAxis(m_axis_WndFFTFreqAmp);

	ui.label_WndFFTSubPartCount->setText(QString("统计旁瓣个数：%1").arg(result.VecWndFFTPart.size()));
	ui.label_WndFFTDeltaFreq->setText(QString("图像频率间隔：%1 hz").arg(result.DeltaFreq, 0, 'f', 2));

	if (result.VecWndFFTPart.size() > 0)
	{
		ui.label_mainPartMaxFFTError->setText(QString("主峰最大误差：%1 %").arg(result.VecWndFFTPart[0].PartMaxErrorPercent * 100, 0, 'f', 2));
		ui.label_mainPart10dbHalfWidth->setText(QString("主峰10db半宽：%1 hz").arg(result.VecWndFFTPart[0].db10RightWidth, 0, 'f', 2));
	}

	if (result.VecWndFFTPart.size() > 1)
	{
		ui.label_firstPartHeight->setText(QString("第一旁瓣高度：%1 db").arg(AudioProtocol::getRelativeDB(result.VecWndFFTPart[1].PartMaxVal, result.maxAmp), 0, 'f', 2));
		ui.label_firstPartFreq->setText(QString("第一旁瓣位置：%1 hz").arg(result.VecWndFFTPart[1].PartMaxValFreq, 0, 'f', 2));
	}

	if (result.VecWndFFTPart.size() > 2)
	{
		ui.label_SecondPartHeight->setText(QString("第二旁瓣高度：%1 db").arg(AudioProtocol::getRelativeDB(result.VecWndFFTPart[2].PartMaxVal, result.maxAmp), 0, 'f', 2));
		ui.label_SecondPartFreq->setText(QString("第二旁瓣位置：%1 hz").arg(result.VecWndFFTPart[2].PartMaxValFreq, 0, 'f', 2));
	}

}

void FFTWindowWgt::loadWndFFTPartEstimate(ST_STFTWndAnsResult& result)
{
	if (m_WndFFTPartSeries != nullptr)
	{
		disconnect(m_WndFFTPartSeries, &QAbstractBarSeries::hovered, this, &FFTWindowWgt::slot_wndFFTPartChtHovered);
	}
	m_WndFFTPartCht->removeAllSeries();
	m_WndFFTPartSeries = new QBarSeries();

	ui.SBox_WndPartCht_PartCount->setMinimum(0);
	ui.SBox_WndPartCht_PartCount->setMaximum(result.VecWndFFTPart.size());


	int EstiBarCount = ui.SBox_WndPartCht_PartCount->value();
	m_vecWndFFTPartSet.clear();

	double maxVal = 0;

	for (int BartSetIndex = 0; BartSetIndex < EstiBarCount; BartSetIndex++)
	{
		QBarSet* FFTPartSet = new QBarSet(QString("WndFFTPart %1").arg(BartSetIndex));

		const ST_STFTWndPart& currentPart = result.VecWndFFTPart[BartSetIndex];

		double maxValDb = AudioProtocol::getRelativeDB(currentPart.PartMaxVal, result.maxAmp);

		*FFTPartSet		<< maxValDb * -1
						<< currentPart.PartMaxErrorDb * -1
						//<< currentPart.PartMaxErrorPercent * 100
						<< currentPart.PartMaxValFreq
						<< currentPart.db10RightWidth
						<< currentPart.db20RightWidth
						<< currentPart.db30RightWidth;
		m_WndFFTPartSeries->append(FFTPartSet);
		m_vecWndFFTPartSet.append(FFTPartSet);

		maxVal = qMax(maxVal, maxValDb * -1);
		maxVal = qMax(maxVal, currentPart.PartMaxErrorDb * -1);
		//maxVal = qMax(maxVal, currentPart.PartMaxErrorPercent * 100);
		maxVal = qMax(maxVal, currentPart.PartMaxValFreq);
		maxVal = qMax(maxVal, currentPart.db10RightWidth);
		maxVal = qMax(maxVal, currentPart.db20RightWidth);
		maxVal = qMax(maxVal, currentPart.db30RightWidth);

	}

	m_WndFFTPartAxisX->clear();
	QStringList categories;
	categories << "旁瓣峰值" << "旁瓣峰值最大误差" /* << "PartMaxErrorPercent"*/ << "旁瓣峰值位置" << "旁瓣db10半宽" << "旁瓣db20半宽" << "旁瓣db30半宽";
	m_WndFFTPartAxisX->append(categories);
	m_WndFFTPartAxisY->setRange(0, maxVal + 10);
	m_WndFFTPartCht->addSeries(m_WndFFTPartSeries);

	connect(m_WndFFTPartSeries,&QAbstractBarSeries::hovered,this,&FFTWindowWgt::slot_wndFFTPartChtHovered);

	m_WndFFTPartSeries->attachAxis(m_WndFFTPartAxisX);
	m_WndFFTPartSeries->attachAxis(m_WndFFTPartAxisY);


}

void FFTWindowWgt::saveActiveWndFFTResult(ST_ActiveWndAnsResult& result)
{
	//m_vecActiveWndFFTPt.maxAmp = result.maxAmp;
	//m_vecActiveWndFFTPt.VecWndFFTPart.clear();
	//for (int partIndex = 0; partIndex < result.VecWndFFTPart.size(); partIndex++)
	{
		//m_tempWndFFTResult.VecWndFFTPart.append(result.VecWndFFTPart[partIndex]);
	}
}

void FFTWindowWgt::loadActiveWndFFTResult(ST_ActiveWndAnsResult& result)
{
	m_axis_ActiveWndFFTFreq->setRange(0, result.AnsPara.showMaxFreq);
	if (m_series_ActiveWndFFTResult != nullptr)
	{
		disconnect(m_series_ActiveWndFFTResult, &QLineSeries::hovered, this, &FFTWindowWgt::slot_ActiveWndFFTMouseHovered);
	}
	m_cht_ActiveWndFFT->removeAllSeries();

	m_series_ActiveWndFFTResult = new QLineSeries();

	double maxAmp = 0;
	double minVal = 0;
	//QVector<double> resultDbVec;

	m_vecActiveWndFFTPt.clear();
	ST_FFTPoint nullpt;
	m_vecActiveWndFFTPt = QVector<ST_FFTPoint>(result.VecWndFFTPt.size(), nullpt);

	if (ui.radioButton_ActiveWndFFTValType_AbsoluteVal->isChecked())
	{
		minVal = 0;
		for (int ptIndex = 0; ptIndex < result.VecWndFFTPt.size(); ptIndex++)
		{
			const ST_FFTPoint& resultPt = result.VecWndFFTPt[ptIndex];
			m_series_ActiveWndFFTResult->append(resultPt.frequency, resultPt.amplitude);
			m_vecActiveWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecActiveWndFFTPt[ptIndex].amplitude = resultPt.amplitude;
			maxAmp = qMax(maxAmp, resultPt.amplitude);
		}
	}
	else if(ui.radioButton_ActiveWndFFTValType_db->isChecked())
	{
		for (int ptIndex = 0; ptIndex < result.VecWndFFTPt.size(); ptIndex++)
		{
			const ST_FFTPoint& resultPt = result.VecWndFFTPt[ptIndex];
			double resultDb = AudioProtocol::getRelativeDB(resultPt.amplitude, result.maxAmp);
			m_series_ActiveWndFFTResult->append(resultPt.frequency, resultDb);
			m_vecActiveWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecActiveWndFFTPt[ptIndex].amplitude = resultDb;
			minVal = qMin(minVal, resultDb);
		}
	}
	else
	{
		for (int ptIndex = 0; ptIndex < result.VecWndFFTPt.size(); ptIndex++)
		{
			const ST_FFTPoint& resultPt = result.VecWndFFTPt[ptIndex];
			double maxReal = result.AnsPara.WndPara.STFTWndPara.pointCount;
			double fftReal = resultPt.amplitude / maxReal;
			double resultDb = AudioProtocol::fftRealToDB(fftReal, const_audio_normalAudioFileMaxDB);
			m_series_ActiveWndFFTResult->append(resultPt.frequency, resultDb);
			m_vecActiveWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecActiveWndFFTPt[ptIndex].amplitude = resultDb;
			minVal = qMin(minVal, resultDb);
		}
	}

	if (ui.radioButton_ActiveWndFFTValType_AbsDb->isChecked())
	{
		m_axis_ActiveWndFFTFreqAmp->setRange(0, 80);
	}
	else
	{
		m_axis_ActiveWndFFTFreqAmp->setRange(ui.SBox_ActiveWndFFTShowMinVal->value(), maxAmp);
	}
	

	m_cht_ActiveWndFFT->addSeries(m_series_ActiveWndFFTResult);

	connect(m_series_ActiveWndFFTResult, &QLineSeries::hovered, this, &FFTWindowWgt::slot_ActiveWndFFTMouseHovered);

	bool attachAxisStateA = m_series_ActiveWndFFTResult->attachAxis(m_axis_ActiveWndFFTFreq);
	bool attachAxisStateB = m_series_ActiveWndFFTResult->attachAxis(m_axis_ActiveWndFFTFreqAmp);
}

void FFTWindowWgt::slot_WndFFTMouseHovered(const QPointF& point, bool state)
{
	QToolTip::showText(QCursor::pos(), QString("point : freq :%1  val :%2").arg(point.x(), 0, 'f', 2).arg(point.y(), 0, 'f', 2));
}

void FFTWindowWgt::slot_updateFFTPartCht()
{
	loadWndFFTPartEstimate(m_tempWndFFTResult);
}

void FFTWindowWgt::slot_GenWndConstrainResultBtnClicked()
{
	ST_WndSpecConstrainPara para;
	para.ConstrainDBRange		= ui.SBox_MaxConstrainDbPos->value();
	para.startEnhanceSidePos	= ui.SBox__EnheaceConstrainPos->value();
	para.EnhanceRatio			= ui.DSbox_EnhanceConstrainRatio->value() / 100;
	para.PeakValDriftRatio		= ui.DSBox_PeakFreqDriftRatio->value() / 100;
	para.isForcePt2DBVal		= ui.checkBox_forcePt2DBVal->isChecked();
	if (para.isForcePt2DBVal)
	{
		para.forcePt2DBVal = ui.DSBox_forcePt2DBVal->value();
	}

	para.WndPara = getWndPara();
	m_WndConstrainResultAxisY->setRange(0, para.ConstrainDBRange + 10);

	m_bOnGenWndConstrainResult = true;

	FFTWindowManager::instance()->slot_StartGenWndConstrainResult(para);
}

void FFTWindowWgt::slot_getWndConstrainResult(ST_WndSpecConstrainDistribute& result)
{
	if (!m_bOnGenWndConstrainResult)
	{
		return;
	}
	m_bOnGenWndConstrainResult = false;

	m_tampResult.VecConstrain_DriftPeak_DB_AfterEnhance		= result.VecConstrain_DriftPeak_DB_AfterEnhance;
	m_tampResult.VecConstrain_DriftPeak_Ratio_afterEnhance = result.VecConstrain_DriftPeak_Ratio_afterEnhance;
	m_tampResult.VecConstrain_DriftPeak_DB_beforeEnhance		= result.VecConstrain_DriftPeak_DB_beforeEnhance;
	m_tampResult.VecConstrain_DriftPeak_Ratio_beforeEnhance	= result.VecConstrain_DriftPeak_Ratio_beforeEnhance;

	int ConstrainPartCount = result.VecConstrain_DriftPeak_DB_AfterEnhance.size();

	ui.label_constrainSidePtCount->setText(QString("抑制边缘点个数：%1").arg(ConstrainPartCount));
	ui.label_NoiseUnConstrainFreqInterval->setText(QString("窗谱噪声无法抑制距离：%1 hz").arg(result.NoiseUnConstrainFreqInterval, 0, 'f', 2));
	ui.label_NoiseToBeSignalFreqInterval->setText(QString("窗谱噪声压制主信号距离：%1 hz").arg(result.NoiseToBeSignalFreqInterval, 0, 'f', 2));

	if (m_WndConstrainResultSeries != nullptr)
	{
		disconnect(m_WndConstrainResultSeries, &QAbstractBarSeries::hovered, this, &FFTWindowWgt::slot_wndConstrainPartChtHovered);
	}
	m_WndConstrainResultCht->removeAllSeries();
	m_WndConstrainResultSeries = new QBarSeries();
	
	m_vecWndConstrainResultSet.clear();

	for (int SetIndex = 0; SetIndex < ConstrainPartCount; SetIndex++)
	{
		QBarSet* FFTPartSet = new QBarSet(QString("Part %1").arg(SetIndex));

		*FFTPartSet << result.VecConstrain_DriftPeak_DB_beforeEnhance[SetIndex] * -1
			<< result.VecConstrain_DriftPeak_DB_AfterEnhance[SetIndex] * -1; 

		m_WndConstrainResultSeries->append(FFTPartSet);
		m_vecWndConstrainResultSet.append(FFTPartSet);
	}

	m_WndConstrainResultAxisX->clear();
	QStringList categories;
	categories << "增强前DB" << "增强后DB" ;
	m_WndConstrainResultAxisX->append(categories);

	m_WndConstrainResultCht->addSeries(m_WndConstrainResultSeries);

	connect(m_WndConstrainResultSeries, &QAbstractBarSeries::hovered, this, &FFTWindowWgt::slot_wndConstrainPartChtHovered);

	m_WndConstrainResultSeries->attachAxis(m_WndConstrainResultAxisX);
	m_WndConstrainResultSeries->attachAxis(m_WndConstrainResultAxisY);
}

void FFTWindowWgt::slot_wndConstrainPartChtHovered(bool status, int index, QBarSet* barset)
{
	if (!status)
	{
		return;
	}

	int HoverBarIndex = -1;
	for (int currentBarIndex = 0; currentBarIndex < m_vecWndConstrainResultSet.size(); currentBarIndex++)
	{
		if (m_vecWndConstrainResultSet[currentBarIndex] == barset)
		{
			HoverBarIndex = currentBarIndex;
			break;
		}
	}

	if (HoverBarIndex == -1)
	{
		qDebug() << "FFTWindowWgt::slot_wndConstrainPartChtHovered : unexist HoverBar pointer!";
		return;
	}

	QString showResult = QString("PartIndex %1 \n").arg(HoverBarIndex);


	if (index == 0)
	{
		double beforeEnhanceDB		= m_tampResult.VecConstrain_DriftPeak_DB_beforeEnhance[HoverBarIndex];
		double beforeEnhanceRatio	= m_tampResult.VecConstrain_DriftPeak_Ratio_beforeEnhance[HoverBarIndex];		
		showResult.append(QString("beforeEnhanceDb    %1 db\n").arg(beforeEnhanceDB, 0, 'f', 2));
		showResult.append(QString("beforeEnhanceRatio %1 ").arg(beforeEnhanceRatio, 0, 'f', 7));
	}
	else
	{
		double afterEnhanceDB		= m_tampResult.VecConstrain_DriftPeak_DB_AfterEnhance[HoverBarIndex];
		double afterEnhanceRatio	= m_tampResult.VecConstrain_DriftPeak_Ratio_afterEnhance[HoverBarIndex];
		showResult.append(QString("afterEnhanceDb     %1 db\n").arg(afterEnhanceDB, 0, 'f', 2));
		showResult.append(QString("afterEnhanceRatio  %1 ").arg(afterEnhanceRatio, 0, 'f', 7));
	}

	QToolTip::showText(QCursor::pos(), showResult);

}

void FFTWindowWgt::slot_GenActiveWndBtnClicked()
{
	ST_STFTActiveWndPara activeWndPara = getActWndPara();
	const ST_STFTWndPara& STFTWndPara = activeWndPara.STFTWndPara;

	ui.label_ActiveWnd_sampleRate->setText(QString("采样率: %1").arg(STFTWndPara.sampleRate));
	ui.label_ActiveWnd_WndType->setText(QString("窗函数类型: %1").arg(FFTWindowManager::instance()->getWndTypeStr(STFTWndPara.WndType)));
	ui.label_ActiveWnd_FFTWndPtCount->setText(QString("窗函数点数: %1").arg(STFTWndPara.pointCount));

	ST_ActvieWnd ActiveWnd;
	ActiveWnd.WndPara = activeWndPara;

	FFTWindowManager::instance()->slot_StartGenActiveWndPt(ActiveWnd);
	loadActiveWndToCht(ActiveWnd);
	slot_ActiveWndShowTypeBtnChanged();
}


void FFTWindowWgt::slot_wndFFTPartChtHovered(bool status, int index, QBarSet* barset)
{

	if (!status)
	{
		return;
	}

	int HoverBarIndex = -1;
	for (int currentBarIndex = 0; currentBarIndex < m_vecWndFFTPartSet.size(); currentBarIndex++)
	{
		if (m_vecWndFFTPartSet[currentBarIndex] == barset)
		{
			HoverBarIndex = currentBarIndex;
			break;
		}
	}

	if (HoverBarIndex == -1)
	{
		qDebug() << "FFTWindowWgt::slot_wndFFTPartChtHovered : unexist HoverBar pointer!";
		return;
	}

	QString showResult = QString("PartIndex %1 \n").arg(HoverBarIndex);
	double  showVal = barset->at(index);

	switch (index)
	{
		case 0:showResult.append(QString("maxValDb %1 db").arg(showVal * -1, 0, 'f', 2)); break;
		case 1:showResult.append(QString("PartMaxErrorDb %1 db").arg(showVal * -1, 0, 'f', 2)); break;
		case 2:showResult.append(QString("PartMaxValFreq %1 hz").arg(showVal, 0, 'f', 2)); break;
		case 3:showResult.append(QString("db10RightWidth %1 hz").arg(showVal, 0, 'f', 2)); break;
		case 4:showResult.append(QString("db20RightWidth %1 hz").arg(showVal, 0, 'f', 2)); break;
		case 5:showResult.append(QString("db30RightWidth %1 hz").arg(showVal, 0, 'f', 2)); break;
	}

	QToolTip::showText(QCursor::pos(), showResult);
}

int FFTWindowWgt::getPointIndex(const QPointF& ChartPos)
{
	if (m_series_WndFFTResult == nullptr)
	{
		return 0;
	}

	qreal indexInQreal = (ChartPos.x() - m_startValue) / m_interval + qreal(0.5);
	int   indexInInt = int(indexInQreal);
	return indexInInt;
}

ST_STFTActiveWndPara FFTWindowWgt::getActWndPara()
{
	ST_STFTWndPara STFTWndPara = getWndPara();

	ST_STFTActiveWndPara STFTActiveWndPara;
	STFTActiveWndPara.STFTWndPara = getWndPara();
	double startTimePos = ui.DSBox_ActiveStartTime->value() / 1000.0;
	double startRatioPos = ui.DSBox_ActiveStartRatio->value() / 100.0;
	STFTActiveWndPara.IncreaseTime = ui.DSBox_IncreaseTime->value() / 1000.0;

	double wndMSec = STFTWndPara.WndMsec;
	if (ui.radioButton_ActiveStartType_Time->isChecked())
	{
		STFTActiveWndPara.startTimePos = startTimePos;
		double startMSec = STFTActiveWndPara.startTimePos * 1000;		
		STFTActiveWndPara.startRatioPos = startMSec / wndMSec;
	}
	else
	{
		STFTActiveWndPara.startRatioPos = startRatioPos;
		STFTActiveWndPara.startTimePos = (startRatioPos * wndMSec) / 1000;
	}

	STFTActiveWndPara.startPointPos = STFTActiveWndPara.startRatioPos * STFTWndPara.pointCount;
	STFTActiveWndPara.IncreaseTime = ui.DSBox_IncreaseTime->value() / 1000;
	STFTActiveWndPara.IncreasePtCount = ui.DSBox_IncreaseTime->value() / STFTWndPara.WndMsec * STFTWndPara.pointCount;

	return STFTActiveWndPara;
}

void FFTWindowWgt::loadActiveWndToCht(ST_ActvieWnd& WndResult)
{
	const ST_STFTActiveWndPara ActWndPara = WndResult.WndPara;
	m_axis_ActiveFunc_ptIndex->setRange(0, ActWndPara.STFTWndPara.pointCount - 1);
	m_axis_ActiveFunc_ptval->setRange(0, 1);
	m_axis_ActiveFunc_Time->setRange(0, ActWndPara.STFTWndPara.WndMsec);

	m_cht_ActiveWndPt->removeAllSeries();

	int hundredsOfPt = qMax(1, WndResult.VecSTFTWndPt.size() / 100);
	m_series_ActiveWnd_STFTWnd = new QLineSeries();
	m_series_ActiveWnd_STFTWnd->setName(QString("STFT Wnd Val"));
	m_series_ActiveWnd_Active = new QLineSeries();
	m_series_ActiveWnd_Active->setName(QString("Active Val"));
	m_series_ActiveWnd_ActiveWnd = new QLineSeries();
	m_series_ActiveWnd_ActiveWnd->setName(QString("ActiveWnd Val"));

	double msecInterval = 1000.0 / ActWndPara.STFTWndPara.sampleRate;

	for (int ptIndex = 0; ptIndex < WndResult.VecSTFTWndPt.size(); ptIndex++)
	{
		double STFTWndVal = WndResult.VecSTFTWndPt[ptIndex];
		double ActiveVal = WndResult.VecActivePt[ptIndex];
		double ActiveWndVal = WndResult.VecActiveWndPt[ptIndex];
		m_series_ActiveWnd_STFTWnd->append(ptIndex, STFTWndVal);
		m_series_ActiveWnd_Active->append(ptIndex, ActiveVal);
		m_series_ActiveWnd_ActiveWnd->append(ptIndex, ActiveWndVal);

		if (ptIndex % hundredsOfPt == 0)
		{
			ui.progressBar_ActiveFuncLoadState->setValue(ptIndex / hundredsOfPt);
		}
	}

	ui.progressBar_ActiveFuncLoadState->setValue(100);

	m_cht_ActiveWndPt->addSeries(m_series_ActiveWnd_STFTWnd);
	m_cht_ActiveWndPt->addSeries(m_series_ActiveWnd_Active);
	m_cht_ActiveWndPt->addSeries(m_series_ActiveWnd_ActiveWnd);

	bool attachAxisStateA_1 = m_series_ActiveWnd_STFTWnd->attachAxis(m_axis_ActiveFunc_ptIndex);
	bool attachAxisStateB_1 = m_series_ActiveWnd_Active->attachAxis(m_axis_ActiveFunc_ptIndex);
	bool attachAxisStateC_1 = m_series_ActiveWnd_ActiveWnd->attachAxis(m_axis_ActiveFunc_ptIndex);

	bool attachAxisStateA_2 = m_series_ActiveWnd_STFTWnd->attachAxis(m_axis_ActiveFunc_ptval);
	bool attachAxisStateB_2 = m_series_ActiveWnd_Active->attachAxis(m_axis_ActiveFunc_ptval);
	bool attachAxisStateC_2 = m_series_ActiveWnd_ActiveWnd->attachAxis(m_axis_ActiveFunc_ptval);


}
