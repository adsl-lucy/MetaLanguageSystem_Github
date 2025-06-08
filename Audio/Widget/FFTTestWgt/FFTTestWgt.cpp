#include "FFTTestWgt.h"
#pragma execution_character_set("utf-8")

FFTTestWgt::FFTTestWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUI();
	initBaseSigChartWgt();
	initModSigChartWgt();
	initFFTChtWgt();
}

FFTTestWgt::~FFTTestWgt()
{

}

void FFTTestWgt::initUI()
{
	setObjectName("oneDimensionSTFTTestWgt");
	setWindowTitle("1DSTFT_TestWgt");

	m_pBtnGroup_ModSigType = new QButtonGroup(this);
	m_pBtnGroup_ModSigType->addButton(ui.radioButton_modSig_Type_sin, 0);
	m_pBtnGroup_ModSigType->addButton(ui.radioButton_modSig_Type_square, 1);
	m_pBtnGroup_ModSigType->setExclusive(true);

	m_pBtnGroup_FFTType = new QButtonGroup(this);
	m_pBtnGroup_FFTType->addButton(ui.radioButton_FFTFrom_zhihu		, (int)EN_FFTType::Zhihu);
	m_pBtnGroup_FFTType->addButton(ui.radioButton_FFTFrom_FFTW		, (int)EN_FFTType::FFTW);
	m_pBtnGroup_FFTType->addButton(ui.radioButton_FFTFrom_cudaFFt	, (int)EN_FFTType::CudaFFT);
	m_pBtnGroup_FFTType->setExclusive(true);
	ui.radioButton_FFTFrom_zhihu->setChecked(true);

	connect(ui.btn_drawBaseSignal, &QPushButton::clicked, this, &FFTTestWgt::slot_onDrawBaseSigBtnClicked);
	connect(ui.btn_drawmodSig	 , &QPushButton::clicked, this, &FFTTestWgt::slot_onDrawModuleSigBtnClicked);
	connect(ui.btn_drawFFTResult , &QPushButton::clicked, this, &FFTTestWgt::slot_onDrawFFTBtnClicked);
	connect(ui.btn_saveModResultToDCenter, &QPushButton::clicked, this, &FFTTestWgt::slot_onSaveSigToDataCenterBtnClicked);

	connect(this, &FFTTestWgt::sgn_drawBaseSig		, FFTManager::instance(), &FFTManager::slot_drawBaseSig);
	connect(this, &FFTTestWgt::sgn_drawModuleSig	, FFTManager::instance(), &FFTManager::slot_drawModuleAndModResultSig);
	connect(this, &FFTTestWgt::sgn_drawFFTResult	, FFTManager::instance(), &FFTManager::slot_getFFTResult);
	connect(this, &FFTTestWgt::sgn_saveModSigToDataCenter, DataCenterManager::instance(), &DataCenterManager::slot_saveGenerateSignal);

}

void FFTTestWgt::initBaseSigChartWgt()
{
	m_axis_BaseSigTime = new QValueAxis();
	m_axis_BaseSigTime->setRange(0, 1000);
	m_axis_BaseSigTime->setLabelFormat("%.1f");
	m_axis_BaseSigTime->setTitleText("base signal time(ms)");

	m_axis_BaseSigVal = new QValueAxis();
	m_axis_BaseSigVal->setRange(0, 100);
	m_axis_BaseSigVal->setLabelFormat("%.1f");
	m_axis_BaseSigVal->setTitleText("sig val(μPa)");

	m_series_BaseSignal = nullptr;

	m_cht_baseSig = new QChart();

	m_cht_baseSig->setTitle("base signal");
	m_cht_baseSig->legend()->hide();
	m_cht_baseSig->addAxis(m_axis_BaseSigTime, Qt::AlignBottom);
	m_cht_baseSig->addAxis(m_axis_BaseSigVal, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_baseSig = new QChartView(m_cht_baseSig);
	m_chtView_baseSig->setRenderHint(QPainter::Antialiasing);
	m_chtView_baseSig->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_baseSig->setMinimumSize(980, 230);

	ui.HLayout_baseSig_chart->insertWidget(0, m_chtView_baseSig);

}

void FFTTestWgt::initModSigChartWgt()
{
	m_axis_ModuleSigTime = new QValueAxis();
	m_axis_ModuleSigTime->setRange(0, 1000);
	m_axis_ModuleSigTime->setLabelFormat("%.1f");
	m_axis_ModuleSigTime->setTitleText("module signal time(ms)");

	m_axis_ModuleSigDepthVal = new QValueAxis();
	m_axis_ModuleSigDepthVal->setRange(-1, 1);
	m_axis_ModuleSigDepthVal->setLabelFormat("%.1f");
	m_axis_ModuleSigDepthVal->setTitleText("depth");

	m_axis_ModuleSigResultVal = new QValueAxis();
	m_axis_ModuleSigResultVal->setRange(-100, 100);
	m_axis_ModuleSigResultVal->setLabelFormat("%.1f");
	m_axis_ModuleSigResultVal->setTitleText("mod Sig Val(μPa)");

	m_series_ModuleSignal = nullptr;

	m_cht_ModuleSig = new QChart();

	m_cht_ModuleSig->setTitle("module signal");
	m_cht_ModuleSig->legend()->show();
	m_cht_ModuleSig->legend()->setAlignment(Qt::AlignBottom);
	m_cht_ModuleSig->addAxis(m_axis_ModuleSigTime, Qt::AlignBottom);
	m_cht_ModuleSig->addAxis(m_axis_ModuleSigDepthVal, Qt::AlignLeft);
	m_cht_ModuleSig->addAxis(m_axis_ModuleSigResultVal, Qt::AlignRight);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_ModuleSig = new QChartView(m_cht_ModuleSig);
	m_chtView_ModuleSig->setRenderHint(QPainter::Antialiasing);
	m_chtView_ModuleSig->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_ModuleSig->setMinimumSize(980, 230);

	ui.HLayout_modSig_chart->insertWidget(0, m_chtView_ModuleSig);
}

void FFTTestWgt::initFFTChtWgt()
{
	m_axis_FFTFreq = new QValueAxis();
	m_axis_FFTFreq->setRange(0, 20000);
	m_axis_FFTFreq->setLabelFormat("%.0f");
	m_axis_FFTFreq->setTitleText("Frequency(HZ)");

	m_axis_FFTFreqAmp = new QValueAxis();
	m_axis_FFTFreqAmp->setRange(0, 100);
	m_axis_FFTFreqAmp->setLabelFormat("%.1f");
	m_axis_FFTFreqAmp->setTitleText("Freq Amp ");

	m_series_FFTResult = nullptr;

	m_cht_FFT = new QChart();

	m_cht_FFT->setTitle("FFT result");
	m_cht_FFT->legend()->hide();
	m_cht_FFT->addAxis(m_axis_FFTFreq, Qt::AlignBottom);
	m_cht_FFT->addAxis(m_axis_FFTFreqAmp, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_FFT = new QChartView(m_cht_FFT);
	m_chtView_FFT->setRenderHint(QPainter::Antialiasing);
	m_chtView_FFT->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	ui.HLayout_FFT_Chart->insertWidget(0, m_chtView_FFT);

}

ST_AudioBaseSignalPara FFTTestWgt::getBaseSigPara()
{
	ST_AudioBaseSignalPara BaseSigPara;

	BaseSigPara.baseFrequency		= ui.dSBox_baseSig_Freq->value();
	BaseSigPara.startTime			= ui.dSBox_baseSig_StartT->value() / 1000;
	BaseSigPara.signalTimeLength	= ui.dSBox_baseSig_TimeLength->value() / 1000;
	BaseSigPara.amplitude			= ui.dSBox_baseSig_Amp->value();
	BaseSigPara.sampleRate			= ui.dSBos_baseSig_SampleRate->value();

	return BaseSigPara;
}

void FFTTestWgt::copyModuleSigResult(ST_AudioModuleSignal& result)
{
	m_moduleSigResult.basePara = result.basePara;
	m_moduleSigResult.modulePara = result.modulePara;

	auto copyVec = [](QVector<ST_AudioPoint>& fromVec, QVector<ST_AudioPoint>& toVec)
		{
			toVec.clear();
			ST_AudioPoint nullpt;
			toVec = QVector<ST_AudioPoint>(fromVec.size(), nullpt);
			for (int i = 0; i < fromVec.size(); i++)
			{
				toVec[i] = fromVec[i];
			}
		};

	m_moduleSigResult.vecModuleSignal.clear();

	copyVec(result.vecModuleSignal			, m_moduleSigResult.vecModuleSignal);
	copyVec(result.vecModuleResultSignal	, m_moduleSigResult.vecModuleResultSignal);

}

void FFTTestWgt::slot_onDrawBaseSigBtnClicked()
{
	ST_AudioBaseSignalPara BaseSigPara = getBaseSigPara();

	ST_AudioBaseSignal resultSignal;
	resultSignal.signalPara = BaseSigPara;
	emit sgn_drawBaseSig(resultSignal);
	slot_getBaseSigValue(resultSignal);

}

void FFTTestWgt::slot_onDrawModuleSigBtnClicked()
{
	bool drawModSig = ui.checkBox_modSig_drawModSig->isChecked();
	bool drawModResultSig = ui.checkBox_modSig_drawSigAfterMod->isChecked();

	if (!drawModSig && !drawModResultSig)
	{
		return;
	}

	ST_AudioBaseSignalPara BaseSigPara = getBaseSigPara();

	ST_AudioModuleSignalPara ModuleSigPara;
	ModuleSigPara.signalType	= (EN_ModuleSignalType)m_pBtnGroup_ModSigType->checkedId();

	ModuleSigPara.moduleFrequency	= ui.dSBox_modSig_Freq->value();
	ModuleSigPara.startTime			= ui.dSBox_modSig_StartT->value() / 1000;
	ModuleSigPara.signalTimeLength	= ui.dSBox_modSig_TimeLength->value() / 1000;
	ModuleSigPara.depth				= ui.dSBox_modSig_Depth->value();
	ModuleSigPara.sampleRate		= ui.dSBos_modSig_SampleRate->value();

	ST_AudioModuleSignal modSig;
	modSig.basePara		= BaseSigPara;
	modSig.modulePara	= ModuleSigPara;

	emit sgn_drawModuleSig(modSig);
	slot_getModuleSigValue(modSig, drawModSig, drawModResultSig);
	copyModuleSigResult(modSig);

}

void FFTTestWgt::slot_onDrawFFTBtnClicked()
{
	ST_FFTInputData FFTInputData;
	ST_FFTInputPara& FFTPara = FFTInputData.para;

	FFTPara.FFTType			= (EN_FFTType)m_pBtnGroup_FFTType->checkedId();

	FFTPara.startTime		= ui.dSBox_FFTstartTime->value() / 1000;
	FFTPara.inputPointCountInPowerOf2 = ui.dSBox_FFTInputPointInPowerOf2->value();
	FFTPara.sampleRate		= ui.dSBox_FFTSampleRate->value();

	

	int inputPointCount = pow(2, FFTPara.inputPointCountInPowerOf2);
	FFTPara.timeLength = FFTManager::instance()->getFrameTimeLength(inputPointCount, FFTPara.sampleRate);

	FFTInputData.AudioPtVec.clear();
	ST_AudioPoint nullpt;
	FFTInputData.AudioPtVec = QVector<ST_AudioPoint>(inputPointCount, nullpt);


	const QVector<ST_AudioPoint>& modSigVec = m_moduleSigResult.vecModuleResultSignal;

	int currentInputPtCount = 0;
	for (int currentPtIndex = 0; currentPtIndex < modSigVec.size(); currentPtIndex++)
	{
		const ST_AudioPoint& currentPt = modSigVec[currentPtIndex];
		if (currentPt.pTime < FFTPara.startTime)
		{
			continue;
		}
		else if (currentInputPtCount >= inputPointCount)
		{
			break;
		}
		else if (currentPt.pTime > FFTPara.startTime + FFTPara.timeLength)
		{
			break;
		}

		FFTInputData.AudioPtVec[currentInputPtCount] = modSigVec[currentPtIndex];
		currentInputPtCount++;

	}

	ST_FFTOutputData result;
	emit sgn_drawFFTResult(FFTInputData, result);
	slot_getFFTResult(result);
}

void FFTTestWgt::slot_getBaseSigValue(ST_AudioBaseSignal& baseSignalVal)
{
	const ST_AudioBaseSignalPara& sigPara = baseSignalVal.signalPara;


	//因为计算过程里面的值都是s，而呈现的位置是微妙，所以横坐标时间要乘1000
	m_axis_BaseSigTime->setRange(sigPara.startTime * 1000,
								(sigPara.startTime + sigPara.signalTimeLength) * 1000);

	double maxAmp = sigPara.amplitude;

	m_axis_BaseSigVal->setRange(-1 * maxAmp, maxAmp);

	m_cht_baseSig->removeAllSeries();

	m_series_BaseSignal = new QLineSeries();

	const QVector<ST_AudioPoint>& resultVec = baseSignalVal.vecPoint;

	for (auto pos = resultVec.cbegin(); pos != resultVec.cend(); pos++)
	{
		m_series_BaseSignal->append(pos->pTime * 1000, pos->pVal);
	}

	m_cht_baseSig->addSeries(m_series_BaseSignal);

	bool attachAxisStateA = m_series_BaseSignal->attachAxis(m_axis_BaseSigTime);
	bool attachAxisStateB = m_series_BaseSignal->attachAxis(m_axis_BaseSigVal);

}

void FFTTestWgt::slot_getModuleSigValue(ST_AudioModuleSignal& modSig, bool drawModSig, bool drawModBaseSig)
{
	const ST_AudioModuleSignalPara&		modSigPara		= modSig.modulePara;
	const ST_AudioBaseSignalPara&		baseSigPara		= modSig.basePara;


	if (!drawModBaseSig)
	{
		m_axis_ModuleSigTime->setRange(modSigPara.startTime * 1000, (modSigPara.startTime + modSigPara.signalTimeLength) * 1000);
	}
	else
	{
		m_axis_ModuleSigTime->setRange(modSigPara.startTime * 1000, (modSigPara.startTime + modSigPara.signalTimeLength) * 1000);
		double maxAmp = baseSigPara.amplitude;
		m_axis_ModuleSigResultVal->setRange(-1 * maxAmp, maxAmp);
	}

	m_axis_ModuleSigDepthVal->setRange(-1, 1);

	m_cht_ModuleSig->removeAllSeries();

	if (drawModSig)
	{
		m_series_ModuleSignal = new QLineSeries();
		m_series_ModuleSignalInverse = new QLineSeries();
		const QVector<ST_AudioPoint>& resultModVec = modSig.vecModuleSignal;

		m_series_ModuleSignal->setName("mod sig");
		m_series_ModuleSignalInverse->setName("mod sig");

		for (auto pos = resultModVec.cbegin(); pos != resultModVec.cend(); pos++)
		{
			m_series_ModuleSignal->append(pos->pTime * 1000, pos->pVal);
			m_series_ModuleSignalInverse->append(pos->pTime * 1000, pos->pVal * -1);
		}
		m_cht_ModuleSig->addSeries(m_series_ModuleSignal);
		m_cht_ModuleSig->addSeries(m_series_ModuleSignalInverse);

		bool attachAxisStateA = m_series_ModuleSignal->attachAxis(m_axis_ModuleSigTime);
		bool attachAxisStateB = m_series_ModuleSignal->attachAxis(m_axis_ModuleSigDepthVal);

		bool attachAxisStateC = m_series_ModuleSignalInverse->attachAxis(m_axis_ModuleSigTime);
		bool attachAxisStateD = m_series_ModuleSignalInverse->attachAxis(m_axis_ModuleSigDepthVal);
	}

	if (drawModBaseSig)
	{
		m_series_ModBaseSignal = new QLineSeries();
		m_series_ModBaseSignal->setName("base sig after mod");
		const QVector<ST_AudioPoint>& resultModBaseVec = modSig.vecModuleResultSignal;

		for (auto pos = resultModBaseVec.cbegin(); pos != resultModBaseVec.cend(); pos++)
		{
			m_series_ModBaseSignal->append(pos->pTime * 1000, pos->pVal);
		}
		m_cht_ModuleSig->addSeries(m_series_ModBaseSignal);

		bool attachAxisStateA = m_series_ModBaseSignal->attachAxis(m_axis_ModuleSigTime);
		bool attachAxisStateB = m_series_ModBaseSignal->attachAxis(m_axis_ModuleSigResultVal);
	}

}

void FFTTestWgt::slot_getFFTResult(ST_FFTOutputData& resultData)
{
	ST_FFTOutputPara& para = resultData.para;

	double startFreq = para.startFreq;
	double endFreq = para.endFreq;

	m_axis_FFTFreq->setRange(startFreq, endFreq / 2);
	m_axis_FFTFreqAmp->setRange(0, para.maxAmp);

	m_cht_FFT->removeAllSeries();

	m_series_FFTResult = new QLineSeries();

	int maxAmp = 0;

	for (auto pos = resultData.resultVec.cbegin(); pos != resultData.resultVec.cend(); pos++)
	{
		m_series_FFTResult->append(pos->frequency, pos->amplitude);

	}

	m_cht_FFT->addSeries(m_series_FFTResult);

	bool attachAxisStateA = m_series_FFTResult->attachAxis(m_axis_FFTFreq);
	bool attachAxisStateB = m_series_FFTResult->attachAxis(m_axis_FFTFreqAmp);


	ui.label_FFTFreqDelta->setText(QString("频率间隔:%1(hz)").arg(para.DeltaFreq));
	ui.label_FFTWindowLength->setText(QString("窗口时长:%1(ms)").arg(para.timeLength * 1000));
	ui.label_FFTInputPointCount->setText(QString("采样点数:%1").arg(resultData.resultVec.size()));

}

void FFTTestWgt::slot_onSaveSigToDataCenterBtnClicked()
{
	bool saveState = false;
	emit sgn_saveModSigToDataCenter(m_moduleSigResult, saveState);
	qDebug() << "FFTTestWgt::slot_onSaveSigToDataCenterBtnClicked : save state : " << saveState;
}