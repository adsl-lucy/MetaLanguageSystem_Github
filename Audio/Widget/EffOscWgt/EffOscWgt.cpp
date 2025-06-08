#include "EffOscWgt.h"
#pragma execution_character_set("utf-8")

EffOscWgt::EffOscWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUI();
	initWndTimeCht();
	initWndFFTCht();

}

EffOscWgt::~EffOscWgt()
{}

void EffOscWgt::initUI()
{
	ui.comboBox_WndType->setItemData(0, QVariant((int)EN_STFTWndType::Rect));
	ui.comboBox_WndType->setItemData(1, QVariant((int)EN_STFTWndType::Hann));
	m_pBtnGroupFFTWndLengthType = new QButtonGroup(this);
	m_pBtnGroupFFTWndLengthType->addButton(ui.radioBtn_WndLengthType_Time, 0);
	m_pBtnGroupFFTWndLengthType->addButton(ui.radioBtn_WndLengthType_Point, 1);
	m_pBtnGroupFFTWndLengthType->setExclusive(true);
	connect(m_pBtnGroupFFTWndLengthType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_WndLengthTypeChanged(); });
	ui.radioBtn_WndLengthType_Point->setChecked(true);
	slot_WndLengthTypeChanged();
	connect(ui.btn_GenWndTimeGraph, &QPushButton::clicked, this, &EffOscWgt::slot_GenSTFTWndBtnClicked);
	

	m_pBtnGroupActiveWndValShowType = new QButtonGroup(this);
	m_pBtnGroupActiveWndValShowType->setExclusive(false);
	m_pBtnGroupActiveWndValShowType->addButton(ui.checkBox_ActiveWnd_ShowType_STFTWnd, 0);
	m_pBtnGroupActiveWndValShowType->addButton(ui.checkBox_ActiveWnd_ShowType_ActiveVal, 1);
	m_pBtnGroupActiveWndValShowType->addButton(ui.checkBox_ActiveWnd_ShowType_ActiveWnd, 2);

	connect(m_pBtnGroupActiveWndValShowType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_ActiveWndShowTypeBtnChanged(); });
	connect(ui.btn_GenActiveWndTimeGraph, &QPushButton::clicked, this, &EffOscWgt::slot_GenActiveWndBtnClicked);
	connect(ui.btn_GenActiveWndFFTGraph, &QPushButton::clicked, this, &EffOscWgt::slot_GenActiveWndFFTSpecBtnClicked);
	connect(ui.btn_updateActiveWndFFTCht, &QPushButton::clicked, this, &EffOscWgt::slot_updateWndFFTChtBtnClicked);
	
	connect(EffOscMaskManager::instance(), &EffOscMaskManager::sgn_ActiveWndGenState, this, &EffOscWgt::slot_getActiveWndMsg);
	connect(EffOscMaskManager::instance(), &EffOscMaskManager::sgn_ActiveWndAnsEnd, this, &EffOscWgt::slot_getActiveWndANSResult);
	
}

void EffOscWgt::initWndTimeCht()
{
	m_axis_WndTimeCht_Time = new QValueAxis();
	m_axis_WndTimeCht_Time->setRange(0, 1000);
	m_axis_WndTimeCht_Time->setLabelFormat("%.1f");
	m_axis_WndTimeCht_Time->setTitleText(" time In Window(ms)");

	m_axis_WndTimeCht_ptIndex = new QValueAxis();
	m_axis_WndTimeCht_ptIndex->setRange(0, 4096);
	m_axis_WndTimeCht_ptIndex->setLabelFormat("%.0f");
	m_axis_WndTimeCht_ptIndex->setTitleText("point In Window(index)");

	m_axis_WndTimeCht_ptVal = new QValueAxis();
	m_axis_WndTimeCht_ptVal->setRange(0, 100);
	m_axis_WndTimeCht_ptVal->setLabelFormat("%.1f");
	m_axis_WndTimeCht_ptVal->setTitleText("val(Percentage)");

	m_series_ActiveWnd_STFTWnd		= nullptr;
	m_series_ActiveWnd_Active		= nullptr;
	m_series_ActiveWnd_ActiveWnd	= nullptr;

	m_cht_WndTime = new QChart();

	m_cht_WndTime->setTitle("WndVal :");
	m_cht_WndTime->legend()->show();
	m_cht_WndTime->addAxis(m_axis_WndTimeCht_Time		, Qt::AlignBottom);
	m_cht_WndTime->addAxis(m_axis_WndTimeCht_ptIndex	, Qt::AlignTop);
	m_cht_WndTime->addAxis(m_axis_WndTimeCht_ptVal		, Qt::AlignLeft);

	m_chtView_WndTimeCht = new QChartView(m_cht_WndTime);
	m_chtView_WndTimeCht->setRenderHint(QPainter::Antialiasing);
	m_chtView_WndTimeCht->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_WndTimeCht->setMinimumSize(980, 230);

	ui.HLayout_TimeCht_Wnd->insertWidget(0, m_chtView_WndTimeCht);
}

void EffOscWgt::initWndFFTCht()
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

	ui.VLayout_ActiveFFTWndSpectrum_Cht->insertWidget(0, m_chtView_WndFFT);
}

ST_STFTWndPara EffOscWgt::getWndPara()
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

void EffOscWgt::loadNormalWndToCht(const ST_STFTWnd& WndResult)
{
	m_axis_WndTimeCht_ptIndex->setRange(0, WndResult.WndPara.pointCount - 1);
	m_axis_WndTimeCht_ptVal->setRange(0, 1);
	m_axis_WndTimeCht_Time->setRange(0, WndResult.WndPara.WndMsec);

	m_cht_WndTime->removeAllSeries();

	int hundredsOfPt = qMax(1, WndResult.VecWndPt.size() / 100);
	m_series_ActiveWnd_STFTWnd = new QLineSeries();
	m_cht_WndTime->setTitle(QString("STFT Wnd Time Distribute"));

	double msecInterval = 1000.0 / WndResult.WndPara.sampleRate;

	for (int ptIndex = 0; ptIndex < WndResult.VecWndPt.size(); ptIndex++)
	{
		double val = WndResult.VecWndPt[ptIndex];
		double msec = ptIndex * msecInterval;
		m_series_ActiveWnd_STFTWnd->append(ptIndex, val);

		if (ptIndex % hundredsOfPt == 0)
		{
			//ui.progressBar_dataLoadState->setValue(ptIndex / hundredsOfPt);
		}
	}

	//ui.progressBar_dataLoadState->setValue(100);

	m_cht_WndTime->addSeries(m_series_ActiveWnd_STFTWnd);
	m_cht_WndTime->legend()->hide();

	bool attachAxisStateA = m_series_ActiveWnd_STFTWnd->attachAxis(m_axis_WndTimeCht_ptIndex);
	bool attachAxisStateB = m_series_ActiveWnd_STFTWnd->attachAxis(m_axis_WndTimeCht_ptVal);
}

void EffOscWgt::updateSTFTWndLabel(const ST_STFTWnd& WndResult)
{
	ui.label_resultWndLength_Point->setText(QString("窗型等价点数：%1").arg(WndResult.WndPara.pointCount));
	ui.label_resultWndLength_Time->setText(QString("窗型等价时长：%1 ms").arg(WndResult.WndPara.WndMsec, 0, 'f', 2));
	double FFTDeltaFreq = EffOscMaskManager::instance()->getDeltaFreq(WndResult.WndPara.sampleRate, WndResult.WndPara.pointCount);
	ui.label_WndSTFTFreqDelta->setText(QString("FFT输出频率间隔：%1 hz").arg(FFTDeltaFreq, 0, 'f', 2));
}

ST_STFTActiveWndPara EffOscWgt::getActWndPara()
{
	ST_STFTWndPara STFTWndPara = getWndPara();

	ST_STFTActiveWndPara STFTActiveWndPara;
	STFTActiveWndPara.STFTWndPara = STFTWndPara;
	double startRatioPos = ui.DSBox_ActiveStartRatio->value() / 100.0;
	STFTActiveWndPara.IncreaseTime = ui.DSBox_IncreaseTime->value() / 1000.0;

	double wndMSec = STFTWndPara.WndMsec;
	STFTActiveWndPara.startRatioPos = startRatioPos;
	STFTActiveWndPara.startTimePos = (startRatioPos * wndMSec) / 1000;

	STFTActiveWndPara.startPointPos = STFTActiveWndPara.startRatioPos * STFTWndPara.pointCount;
	STFTActiveWndPara.IncreaseTime = ui.DSBox_IncreaseTime->value() / 1000;
	STFTActiveWndPara.IncreasePtCount = ui.DSBox_IncreaseTime->value() / STFTWndPara.WndMsec * STFTWndPara.pointCount;

	return STFTActiveWndPara;
}

void EffOscWgt::loadActiveWndToCht(ST_ActvieWnd& WndResult)
{
	const ST_STFTActiveWndPara ActWndPara = WndResult.WndPara;
	m_axis_WndTimeCht_ptIndex->setRange(0, ActWndPara.STFTWndPara.pointCount - 1);
	m_axis_WndTimeCht_ptVal->setRange(0, 1);
	m_axis_WndTimeCht_Time->setRange(0, ActWndPara.STFTWndPara.WndMsec);

	m_cht_WndTime->removeAllSeries();
	m_cht_WndTime->setTitle(QString("STFT Active Wnd Time Distribute"));

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
			//ui.progressBar_ActiveFuncLoadState->setValue(ptIndex / hundredsOfPt);
		}
	}

	//ui.progressBar_ActiveFuncLoadState->setValue(100);

	m_cht_WndTime->addSeries(m_series_ActiveWnd_STFTWnd);
	m_cht_WndTime->addSeries(m_series_ActiveWnd_Active);
	m_cht_WndTime->addSeries(m_series_ActiveWnd_ActiveWnd);

	m_cht_WndTime->legend()->show();

	bool attachAxisStateA_1 = m_series_ActiveWnd_STFTWnd->attachAxis(m_axis_WndTimeCht_ptIndex);
	bool attachAxisStateB_1 = m_series_ActiveWnd_Active->attachAxis(m_axis_WndTimeCht_ptIndex);
	bool attachAxisStateC_1 = m_series_ActiveWnd_ActiveWnd->attachAxis(m_axis_WndTimeCht_ptIndex);

	bool attachAxisStateA_2 = m_series_ActiveWnd_STFTWnd->attachAxis(m_axis_WndTimeCht_ptVal);
	bool attachAxisStateB_2 = m_series_ActiveWnd_Active->attachAxis(m_axis_WndTimeCht_ptVal);
	bool attachAxisStateC_2 = m_series_ActiveWnd_ActiveWnd->attachAxis(m_axis_WndTimeCht_ptVal);
}

void EffOscWgt::loadActiveWndFFTToCht(const ST_ActiveWndAnsResult& result)
{
	m_axis_WndFFTFreq->setRange(0, result.AnsPara.showMaxFreq);
	if (m_series_WndFFTResult != nullptr)
	{
		disconnect(m_series_WndFFTResult, &QLineSeries::hovered, this, &EffOscWgt::slot_ActiveWndFFTMouseHovered);
	}
	m_cht_WndFFT->removeAllSeries();

	m_series_WndFFTResult = new QLineSeries();

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
			m_series_WndFFTResult->append(resultPt.frequency, resultPt.amplitude);
			m_vecActiveWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecActiveWndFFTPt[ptIndex].amplitude = resultPt.amplitude;
			maxAmp = qMax(maxAmp, resultPt.amplitude);
		}
	}
	else if (ui.radioButton_ActiveWndFFTValType_db->isChecked())
	{
		for (int ptIndex = 0; ptIndex < result.VecWndFFTPt.size(); ptIndex++)
		{
			const ST_FFTPoint& resultPt = result.VecWndFFTPt[ptIndex];
			double resultDb = AudioProtocol::getRelativeDB(resultPt.amplitude, result.maxAmp);
			m_series_WndFFTResult->append(resultPt.frequency, resultDb);
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
			m_series_WndFFTResult->append(resultPt.frequency, resultDb);
			m_vecActiveWndFFTPt[ptIndex].frequency = resultPt.frequency;
			m_vecActiveWndFFTPt[ptIndex].amplitude = resultDb;
			minVal = qMin(minVal, resultDb);
		}
	}

	if (ui.radioButton_ActiveWndFFTValType_AbsDb->isChecked())
	{
		m_axis_WndFFTFreqAmp->setRange(0, 80);
	}
	else
	{
		m_axis_WndFFTFreqAmp->setRange(ui.SBox_ActiveWndFFTShowMinVal->value(), maxAmp);
	}


	m_cht_WndFFT->addSeries(m_series_WndFFTResult);

	connect(m_series_WndFFTResult, &QLineSeries::hovered, this, &EffOscWgt::slot_ActiveWndFFTMouseHovered);

	bool attachAxisStateA = m_series_WndFFTResult->attachAxis(m_axis_WndFFTFreq);
	bool attachAxisStateB = m_series_WndFFTResult->attachAxis(m_axis_WndFFTFreqAmp);
}

void EffOscWgt::slot_WndLengthTypeChanged()
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

void EffOscWgt::slot_GenSTFTWndBtnClicked()
{
	ST_STFTWnd result;
	ST_STFTWndPara& para = result.WndPara;
	para = getWndPara();

	EffOscMaskManager::instance()->slot_generateSTFTWindow(result);

	QString ChtName;
	switch (result.WndPara.WndType)
	{
		case EN_STFTWndType::Rect:ChtName = QString("Wnd Rect"); break;
		case EN_STFTWndType::Hann:ChtName = QString("Wnd Hann"); break;
	}
	loadNormalWndToCht(result);
	updateSTFTWndLabel(result);
}

void EffOscWgt::slot_ActiveWndShowTypeBtnChanged()
{
	QList<QAbstractSeries*> SeriesList = m_cht_WndTime->series();

	if (SeriesList.size() != 3)
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

void EffOscWgt::slot_GenActiveWndBtnClicked()
{
	ST_STFTActiveWndPara activeWndPara = getActWndPara();
	const ST_STFTWndPara& STFTWndPara = activeWndPara.STFTWndPara;

	ui.label_ActiveWnd_sampleRate->setText(QString("采样率: %1").arg(STFTWndPara.sampleRate));
	ui.label_ActiveWnd_WndType->setText(QString("窗函数类型: %1").arg(EffOscMaskManager::instance()->getWndTypeStr(STFTWndPara.WndType)));
	ui.label_ActiveWnd_FFTWndPtCount->setText(QString("窗函数点数: %1").arg(STFTWndPara.pointCount));

	ST_ActvieWnd ActiveWnd;
	ActiveWnd.WndPara = activeWndPara;

	EffOscMaskManager::instance()->slot_StartGenActiveWndPt(ActiveWnd);
	loadActiveWndToCht(ActiveWnd);
	slot_ActiveWndShowTypeBtnChanged();
}

void EffOscWgt::slot_GenActiveWndFFTSpecBtnClicked()
{
	ST_ActiveWndAnsPara ActiveWndAnsPara;
	ActiveWndAnsPara.WndPara			= getActWndPara();
	ActiveWndAnsPara.showMaxFreq		= ui.SBox_ActiveWndFFTShowMaxFreq->value();
	ActiveWndAnsPara.showFreqPtCount	= ui.SBox_ActiveWndFFTShowPointCount->value();

	EffOscMaskManager::instance()->slot_startGenActiveWndFFTResult(ActiveWndAnsPara);
}

void EffOscWgt::slot_updateWndFFTChtBtnClicked()
{
	m_axis_WndFFTFreqAmp->setRange(ui.SBox_ActiveWndFFTShowMinVal->value(), 0);
	m_axis_WndFFTFreq->setRange(0, ui.SBox_ActiveWndFFTShowMaxFreq->value());
	m_cht_WndFFT->update();
}

void EffOscWgt::slot_getActiveWndMsg(int percentage, int threadCount, QString msg)
{
	ui.progressBar_ActvieWndFFTGenState->setValue(percentage);
	ui.label_ActvieWndFFTGenState->setText(QString("生成状态：活跃线程 %1 %2").arg(threadCount).arg(msg));
}

void EffOscWgt::slot_getActiveWndANSResult(ST_ActiveWndAnsResult& result)
{
	loadActiveWndFFTToCht(result);
}

void EffOscWgt::slot_ActiveWndFFTMouseHovered(const QPointF& point, bool state)
{
	QToolTip::showText(QCursor::pos(), QString("point : freq :%1  val :%2").arg(point.x(), 0, 'f', 2).arg(point.y(), 0, 'f', 2));
}
