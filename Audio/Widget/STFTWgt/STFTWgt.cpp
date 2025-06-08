#include "STFTWgt.h"
#pragma execution_character_set("utf-8")

STFTWgt::STFTWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUI();
	initSigWndCht();
	initLoadSigCht();
	initSTFTHotCht();
	initSTFTPanel();

	connect(this, &STFTWgt::sgn_generateSTFTResult, FFTManager::instance(), &FFTManager::slot_generateSTFTResult);

	connect(FFTManager::instance(), &FFTManager::sgn_STFTGenerateState	, this, &STFTWgt::slot_getSTFTGenerateState);
	connect(FFTManager::instance(), &FFTManager::sgn_getSTFTResult		, this, &STFTWgt::slot_getSTFTResult);

}

STFTWgt::~STFTWgt()
{}

void STFTWgt::initUI()
{
	m_pBtnGroupLoadSigType = new QButtonGroup(this);
	m_pBtnGroupLoadSigType->addButton(ui.radioBtn_SigFrom_Gen, 0);
	m_pBtnGroupLoadSigType->addButton(ui.radioBtn_SigFrom_Wav, 1);
	m_pBtnGroupLoadSigType->setExclusive(true);
	ui.radioBtn_SigFrom_Wav->setChecked(true);

	ui.progressBar_dataLoadState->setValue(0);

	connect(ui.btn_loadSig, &QPushButton::clicked, this, &STFTWgt::slot_loadGenSigBtnClicked);

	m_pBtnGroupSTFTWndType = new QButtonGroup(this);
	m_pBtnGroupSTFTWndType->addButton(ui.radioBtn_Wnd_Null, (int)EN_STFTWndType::Rect);
	m_pBtnGroupSTFTWndType->addButton(ui.radioBtn_Wnd_Hann, (int)EN_STFTWndType::Hann);
	m_pBtnGroupSTFTWndType->setExclusive(true);
	ui.radioBtn_Wnd_Hann->setChecked(true);

	m_pBtnGroupSTFTWndLengthType = new QButtonGroup(this);
	m_pBtnGroupSTFTWndLengthType->addButton(ui.radioBtn_WndLengthType_Time, 0);
	m_pBtnGroupSTFTWndLengthType->addButton(ui.radioBtn_WndLengthType_Point, 1);
	m_pBtnGroupSTFTWndLengthType->setExclusive(true);
	connect(m_pBtnGroupSTFTWndLengthType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_WndLengthTypeChanged(); });
	ui.radioBtn_WndLengthType_Point->setChecked(true);
	slot_WndLengthTypeChanged();

	connect(ui.btn_GenWnd,  &QPushButton::clicked, this, &STFTWgt::slot_generateSTFTWndBtnClicked);
	connect(this, &STFTWgt::sgn_generateSTFTWnd, FFTWindowManager::instance(), &FFTWindowManager::slot_generateSTFTWindow);

	ui.combox_FFTSource->addItem(QString("知乎网友"), (int)EN_FFTType::Zhihu);
	ui.combox_FFTSource->addItem(QString("FFTW")	, (int)EN_FFTType::FFTW);
	ui.combox_FFTSource->addItem(QString("CudaFFT")	, (int)EN_FFTType::CudaFFT);
	ui.combox_FFTSource->setCurrentIndex(1);

	ui.progressBar_STFTGenerateState->setValue(0);
	connect(ui.btn_genSTFTResult, &QPushButton::clicked, this, &STFTWgt::slot_generateSTFTResultBtnClicked);

	m_pBtnGroupSTFTGapType = new QButtonGroup(this);
	m_pBtnGroupSTFTGapType->addButton(ui.radioBtn_STFTGapType_Time		,(int)EN_STFTWndGapType::timelength);
	m_pBtnGroupSTFTGapType->addButton(ui.radioBtn_STFTGapType_WndRatio	, (int)EN_STFTWndGapType::WndRatio);
	m_pBtnGroupSTFTGapType->setExclusive(true);
	ui.radioBtn_STFTGapType_WndRatio->setChecked(true);
	connect(m_pBtnGroupSTFTGapType, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
		[=](int id, bool checked) { slot_WndGapTypeChanged(); });
	slot_WndGapTypeChanged();

	ui.label_processState->setText(QString("理想线程数量：%1").arg(QThread::idealThreadCount()));


}

void STFTWgt::initLoadSigCht()
{
	m_axis_LoadSigTime = new QValueAxis();
	m_axis_LoadSigTime->setRange(0, 1000);
	m_axis_LoadSigTime->setLabelFormat("%.1f");
	m_axis_LoadSigTime->setTitleText("base signal time(ms)");

	m_axis_LoadSigVal = new QValueAxis();
	m_axis_LoadSigVal->setRange(0, 100);
	m_axis_LoadSigVal->setLabelFormat("%.1f");
	m_axis_LoadSigVal->setTitleText("sig val(μPa)");

	m_series_LoadSignal = nullptr;

	m_cht_LoadSig = new QChart();

	m_cht_LoadSig->setTitle("load signal :");
	m_cht_LoadSig->legend()->hide();
	m_cht_LoadSig->addAxis(m_axis_LoadSigTime, Qt::AlignBottom);
	m_cht_LoadSig->addAxis(m_axis_LoadSigVal, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_LoadSig = new QChartView(m_cht_LoadSig);
	m_chtView_LoadSig->setRenderHint(QPainter::Antialiasing);
	m_chtView_LoadSig->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_LoadSig->setMinimumSize(980, 230);

	ui.VLayout_Cht_Sig->insertWidget(0, m_chtView_LoadSig);
}

void STFTWgt::initSigWndCht()
{
	m_axis_STFTWndTime = new QValueAxis();
	m_axis_STFTWndTime->setRange(0, 1000);
	m_axis_STFTWndTime->setLabelFormat("%.1f");
	m_axis_STFTWndTime->setTitleText(" time In STFT Window(ms)");

	m_axis_STFTWndPoint = new QValueAxis();
	m_axis_STFTWndPoint->setRange(0, 4096);
	m_axis_STFTWndPoint->setLabelFormat("%.1f");
	m_axis_STFTWndPoint->setTitleText("point In STFT Window(index)");

	m_axis_STFTWndVal = new QValueAxis();
	m_axis_STFTWndVal->setRange(0, 100);
	m_axis_STFTWndVal->setLabelFormat("%.1f");
	m_axis_STFTWndVal->setTitleText("val(Percentage)");

	m_series_STFTWnd = nullptr;

	m_cht_STFTWnd = new QChart();

	m_cht_STFTWnd->setTitle("signal Window :");
	m_cht_STFTWnd->legend()->hide();
	m_cht_STFTWnd->addAxis(m_axis_STFTWndTime, Qt::AlignBottom);
	m_cht_STFTWnd->addAxis(m_axis_STFTWndPoint, Qt::AlignTop);
	m_cht_STFTWnd->addAxis(m_axis_STFTWndVal, Qt::AlignLeft);
	//m_cht_baseSig->setTheme(QChart::ChartThemeBlueCerulean);

	m_chtView_STFTWndSig = new QChartView(m_cht_STFTWnd);
	m_chtView_STFTWndSig->setRenderHint(QPainter::Antialiasing);
	m_chtView_STFTWndSig->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_chtView_STFTWndSig->setMinimumSize(980, 230);

	ui.VLayout_Cht_STFTWnd->insertWidget(0, m_chtView_STFTWndSig);
}

void STFTWgt::initSTFTHotCht()
{
	m_pHotGram = new FFT_Chart_STFTHotGram(this);
	ui.VLayout_STFTResult_Hot->insertWidget(0,m_pHotGram);
	connect(m_pHotGram, &FFT_Chart_STFTHotGram::sgn_HotRectGenerateState, this, &STFTWgt::slot_updateHotChtGenState);
}

void STFTWgt::initSTFTPanel()
{
	m_pSTFTPanel = new STFTAnalysePanel(this);
	ui.VLayout_STFT_detail->insertWidget(0, m_pSTFTPanel);
}

void STFTWgt::updateLoadDataCombox()
{
	ui.comboBox_GenSig->clear();
	const QMap<QString, ST_AudioModuleSignal>& GenMapRef = DataCenterManager::instance()->getGenSigMap();
	for (auto pos = GenMapRef.begin(); pos != GenMapRef.end(); pos++)
	{
		ui.comboBox_GenSig->addItem(pos.key());
	}

	ui.comboBox_WavSig->clear();
	const QMap<QString, ST_WavDoubleData>& wavMapRef = DataCenterManager::instance()->getWavSigMap();
	for (auto pos = wavMapRef.begin(); pos != wavMapRef.end(); pos++)
	{
		ui.comboBox_WavSig->addItem(pos.key());
	}

}

void STFTWgt::updateLoadSigLabel(int ChnCount,int durationMs, int pointCount, int sampleRate)
{
	ui.label_SigChnNum->setText(QString("通道数：%1").arg(ChnCount));
	ui.label_SigDuration->setText(QString("持续时间：%1").arg(durationMs));
	ui.label_SigPotintCount->setText(QString("载入点数：%1").arg(pointCount));
	ui.label_SigSampleRate->setText(QString("采样数：%1").arg(sampleRate));
}

void STFTWgt::showEvent(QShowEvent* event)
{
	//qDebug() << "STFTWgt::showEvent : ";
	updateLoadDataCombox();
}

void STFTWgt::loadSigFromCurrentSelGenSig()
{
	QString selGenSigName = ui.comboBox_GenSig->currentText();
	qDebug() << "STFTWgt::loadSigFromCurrentSelGenSig :: currentSig name : " << selGenSigName;

	const QMap<QString, ST_AudioModuleSignal>& mapRef = DataCenterManager::instance()->getGenSigMap();

	auto mapPos = mapRef.find(selGenSigName);
	if (mapPos == mapRef.end())
	{
		qDebug() << "STFTWgt::loadSigFromCurrentSelGenSig :: map pos end! : ";
		return;
	}

	const ST_AudioModuleSignal& dataRef = mapPos.value();

	int startMsec	= dataRef.vecModuleResultSignal[0].pTime		* 1000;
	int endMsec		= dataRef.vecModuleResultSignal.rbegin()->pTime * 1000;
	double maxAmp	= dataRef.basePara.amplitude;

	loadSigToCht(selGenSigName,startMsec, endMsec, maxAmp, dataRef.vecModuleResultSignal);
	updateLoadSigLabel(1, dataRef.basePara.signalTimeLength * 1000, dataRef.vecModuleResultSignal.size(), dataRef.basePara.sampleRate);
	ui.SBox_WndSampleRate->setValue(dataRef.basePara.sampleRate);
}

void STFTWgt::loadSigFromCurrentSelWavSig()
{
	QString selWavSigName = ui.comboBox_WavSig->currentText();
	qDebug() << "STFTWgt::loadSigFromCurrentSelWavSig :: currentSig name : " << selWavSigName;

	const QMap<QString, ST_WavDoubleData>& mapRef = DataCenterManager::instance()->getWavSigMap();
	auto mapPos = mapRef.find(selWavSigName);
	if (mapPos == mapRef.end())
	{
		qDebug() << "STFTWgt::loadSigFromCurrentSelWavSig :: map pos end! : ";
		return;
	}

	const ST_WavDoubleData& dataRef = mapPos.value();

	int startMsec	= dataRef.LeftChannel[0].pTime * 1000;
	int endMsec		= dataRef.LeftChannel.rbegin()->pTime * 1000;
	double maxAmp	= 1.0;

	loadSigToCht(selWavSigName,startMsec, endMsec, maxAmp, dataRef.LeftChannel);

	int timeLength = endMsec - startMsec;

	updateLoadSigLabel(1, timeLength, dataRef.LeftChannel.size(), dataRef.fileTag.sampleRate);
	ui.SBox_WndSampleRate->setValue(dataRef.fileTag.sampleRate);
}

void STFTWgt::loadSigToCht(QString chtName, int startMsec,int endMsec,double maxAmp,const QVector<ST_AudioPoint>& dataVec)
{
	//const ST_AudioBaseSignalPara& sigPara = baseSignalVal.signalPara;

	//因为计算过程里面的值都是s，而呈现的位置是微妙，所以横坐标时间要乘1000
	m_axis_LoadSigTime->setRange(startMsec,endMsec);
	m_axis_LoadSigVal->setRange(-1 * maxAmp, maxAmp);
	m_cht_LoadSig->removeAllSeries();

	m_series_LoadSignal = new QLineSeries();
	m_cht_LoadSig->setTitle(QString("load signal : %1").arg(chtName));
	int hundredsOfPt = qMax(1, dataVec.size() / 100);

	int WndPixelOnx = m_cht_LoadSig->plotArea().width();
	int ptPerPixel = 10;
	int loadPtInterval = qMax(1,dataVec.size() / (WndPixelOnx * ptPerPixel));


	for (int ptIndex = 0; ptIndex < dataVec.size(); ptIndex++)
	{
		if (ptIndex % loadPtInterval == 0)
		{
			const ST_AudioPoint& point = dataVec[ptIndex];
			m_series_LoadSignal->append(point.pTime * 1000, point.pVal);
		}
		
		if (ptIndex % hundredsOfPt == 0)
		{
			ui.progressBar_dataLoadState->setValue(ptIndex / hundredsOfPt);
		}
	}

	ui.progressBar_dataLoadState->setValue(100);

	m_cht_LoadSig->addSeries(m_series_LoadSignal);

	bool attachAxisStateA = m_series_LoadSignal->attachAxis(m_axis_LoadSigTime);
	bool attachAxisStateB = m_series_LoadSignal->attachAxis(m_axis_LoadSigVal);
}

void STFTWgt::slot_loadGenSigBtnClicked()
{
	if (ui.radioBtn_SigFrom_Gen->isChecked())
	{
		loadSigFromCurrentSelGenSig();
	}
	else if (ui.radioBtn_SigFrom_Wav->isChecked())
	{
		loadSigFromCurrentSelWavSig();
	}
}

void STFTWgt::slot_WndLengthTypeChanged()
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

void STFTWgt::slot_WndGapTypeChanged()
{
	ui.DSBox_STFTGapLength_timeMSec->setEnabled(false);
	ui.DSBox_STFTGapWndLenghtRatio->setEnabled(false);
	if (ui.radioBtn_STFTGapType_WndRatio->isChecked())
	{
		ui.DSBox_STFTGapWndLenghtRatio->setEnabled(true);
	}
	else if (ui.radioBtn_STFTGapType_Time->isChecked())
	{
		ui.DSBox_STFTGapLength_timeMSec->setEnabled(true);
	}
}

ST_STFTWndPara STFTWgt::getWndPara()
{
	ST_STFTWndPara para;
	para.WndType = (EN_STFTWndType)m_pBtnGroupSTFTWndType->checkedId();
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

void STFTWgt::slot_generateSTFTWndBtnClicked()
{
	ST_STFTWnd result;
	ST_STFTWndPara& para = result.WndPara;
	para = getWndPara();

	emit sgn_generateSTFTWnd(result);

	QString ChtName;
	switch (result.WndPara.WndType)
	{
		case EN_STFTWndType::Rect:ChtName = QString("Wnd Rect"); break;
		case EN_STFTWndType::Hann:ChtName = QString("Wnd Hann"); break;
	}
	loadWndToCht(ChtName, result);
	updateSTFTWndLabel(para.WndMsec, para.pointCount);

}

void STFTWgt::slot_generateSTFTResultBtnClicked()
{
	ST_STFTInputData inputData;
	ST_STFTInputpara& para = inputData.para;

	ui.label_processState->setText(QString("开始加载数据"));
	ui.label_processState->repaint();

	para.FFTType = (EN_FFTType)ui.combox_FFTSource->currentData().toInt();
	para.multiThreadMode = ui.checkBox_STFT_MultiThreadMode->isChecked();

	if (ui.radioBtn_SigFrom_Gen->isChecked())
	{
		para.fileName = ui.comboBox_GenSig->currentText();
		qDebug() << "STFTWgt::loadSigFromCurrentSelGenSig :: currentSig name : " << para.fileName;

		const QMap<QString, ST_AudioModuleSignal>& mapRef = DataCenterManager::instance()->getGenSigMap();

		auto mapPos = mapRef.find(para.fileName);
		if (mapPos == mapRef.end())
		{
			qDebug() << "STFTWgt::loadSigFromCurrentSelGenSig :: map pos end! : ";
			return;
		}

		const ST_AudioModuleSignal& dataRef = mapPos.value();

		para.startTime = dataRef.vecModuleResultSignal[0].pTime;
		para.timeLength = dataRef.basePara.signalTimeLength;
		para.sampleRate = dataRef.basePara.sampleRate;
		AudioProtocol::duplicateAudioVec(dataRef.vecModuleResultSignal, inputData.vecPoint);
	}
	else if (ui.radioBtn_SigFrom_Wav->isChecked())
	{
		para.fileName = ui.comboBox_WavSig->currentText();
		qDebug() << "STFTWgt::loadSigFromCurrentSelWavSig :: currentSig name : " << para.fileName;

		const QMap<QString, ST_WavDoubleData>& mapRef = DataCenterManager::instance()->getWavSigMap();
		auto mapPos = mapRef.find(para.fileName);
		if (mapPos == mapRef.end())
		{
			qDebug() << "STFTWgt::loadSigFromCurrentSelWavSig :: map pos end! : ";
			return;
		}

		const ST_WavDoubleData& dataRef = mapPos.value();

		para.startTime	= dataRef.LeftChannel[0].pTime;
		para.timeLength = QTime(0,0,0).msecsTo(dataRef.fileTag.Duration);
		para.sampleRate = dataRef.fileTag.sampleRate;

		double secPerPt = 1.0 / para.sampleRate;
		double ptCount = dataRef.LeftChannel.size();
		para.timeLength = secPerPt * ptCount;
		AudioProtocol::duplicateAudioVec(dataRef.LeftChannel, inputData.vecPoint);
	}

	
	para.WndPara	= getWndPara();
	para.FFTPOW2	= log2(para.WndPara.pointCount);
	para.WndGapType = (EN_STFTWndGapType)m_pBtnGroupSTFTGapType->checkedId();

	if (para.WndGapType == EN_STFTWndGapType::WndRatio)
	{
		para.GapInWndRatio = ui.DSBox_STFTGapWndLenghtRatio->value();
		para.GapInTimeLength = para.WndPara.WndMsec * para.GapInWndRatio / 1000.0;
	}
	else if (para.WndGapType == EN_STFTWndGapType::timelength)
	{
		para.GapInTimeLength = ui.DSBox_STFTGapLength_timeMSec->value() / 1000.0;
		para.GapInWndRatio = para.GapInTimeLength * 1000.0 / para.WndPara.WndMsec;
	}
	ui.label_STFTGapInTime->setText(QString("步长等价时间：%1 ms").arg(para.GapInTimeLength * 1000));
	ui.label_STFTGapInWndRatio->setText(QString("步长等价窗口比例：%1%").arg(para.GapInWndRatio * 100, 0, 'f', 2));

	m_STFTProcessTime = QTime::currentTime();

	ui.label_processState->setText(QString("初始化任务"));
	ui.label_processState->repaint();
	emit sgn_generateSTFTResult(inputData);

}

QTime STFTWgt::updateProcessTime()
{
	QTime currentTime = QTime::currentTime();
	int msecCost = m_STFTProcessTime.msecsTo(currentTime);
	QTime processTime = QTime(0, 0, 0).addMSecs(msecCost);
	m_STFTProcessTime = currentTime;
	qDebug() << "STFTWgt::updateProcessTime : " << msecCost;
	return processTime;
}

void  STFTWgt::printSTFTProcessTime(QString prefix, QString suffix)
{
	ui.label_processState->setText(QString(" %1: %2 %3").arg(prefix).arg(updateProcessTime().toString("mm:ss.zzz")).arg(suffix));
	ui.label_processState->repaint();
}

void STFTWgt::slot_getSTFTGenerateState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_STFTGenerateState->setValue(percentage);
	ui.label_processState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	
}

void STFTWgt::slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_STFTGenerateState->setValue(percentage);
	ui.label_processState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	if (percentage == 100)
	{
		printSTFTProcessTime(QString("预览图开销"), QString(" "));
		if (ui.checkBox_genWndSpecConstrainAfterSTFTResult->isChecked())
		{
			emit sgn_startGenWndSpecConstrainResult(m_STFTDataKey);
		}
	}
}

void STFTWgt::slot_getSTFTResult(ST_STFTOutputData& outputData)
{
	printSTFTProcessTime(QString("STFT 时间开销"), QString("开始缓存"));

	bool saveState = false;
	QString DatacenterName = DataCenterManager::instance()->slot_saveSTFTData(outputData, saveState);
	if (!saveState)
	{
		qDebug() << "STFTWgt::slot_getSTFTResult saveState fault!";
		ui.label_processState->setText(QString("STFT 缓存失败"));
		return;
	}

	m_STFTDataKey = DatacenterName;
	
	const ST_STFTOutputData& outputDataInDataCenter = DataCenterManager::instance()->getSTFTOutputMap().find(DatacenterName).value();

	m_pSTFTPanel->setSTFTData(outputDataInDataCenter);
	m_pHotGram->setSTFTResultPara(outputData.InputPara);
	m_pHotGram->setCurrentFrameIndex(0);
	
	QTime outputDataStartTime = QTime(0, 0, 0).addMSecs(outputData.InputPara.startTime * 1000);
	QTime outputDataEndTime = outputDataStartTime.addMSecs(outputData.InputPara.timeLength * 1000);

	m_pHotGram->setTimeRange(outputDataStartTime, outputDataStartTime.msecsTo(outputDataEndTime));
	m_pHotGram->setDbRange(0, 80);
	m_pHotGram->setFreqRange(0, 20000);
	m_pHotGram->setFreqBandWidth(50);
	m_pHotGram->setTimeInterval(20);

	printSTFTProcessTime(QString("缓存开销"), QString("开始生成预览图"));
	m_pHotGram->resetColorRect(DatacenterName);

}

void STFTWgt::slot_AudoGenSTFTData(QString DataKey)
{
	updateLoadDataCombox();
	ui.radioBtn_SigFrom_Wav->setChecked(true);
	int index = ui.comboBox_WavSig->findText(DataKey);
	if (index<0 || index > ui.comboBox_WavSig->count())
	{
		ui.label_dataLoadState->setText("error");
		return;
	}
	ui.comboBox_WavSig->setCurrentIndex(index);
	slot_loadGenSigBtnClicked();
	slot_generateSTFTWndBtnClicked();
	slot_generateSTFTResultBtnClicked();

}

void STFTWgt::loadWndToCht(QString ChtName, ST_STFTWnd& WndResult)
{
	m_axis_STFTWndPoint->setRange(0, WndResult.WndPara.pointCount - 1);
	m_axis_STFTWndVal->setRange(0 , 1);
	m_axis_STFTWndTime->setRange(0, WndResult.WndPara.WndMsec);

	m_cht_STFTWnd->removeAllSeries();

	int hundredsOfPt = WndResult.VecWndPt.size() / 100;
	m_series_STFTWnd = new QLineSeries();
	m_cht_STFTWnd->setTitle(ChtName);

	double msecInterval = 1000.0 / WndResult.WndPara.sampleRate;

	for (int ptIndex = 0; ptIndex < WndResult.VecWndPt.size(); ptIndex++)
	{
		double val		= WndResult.VecWndPt[ptIndex];
		double msec		= ptIndex * msecInterval;
		m_series_STFTWnd->append(msec, val);

		if (ptIndex % hundredsOfPt == 0)
		{
			ui.progressBar_dataLoadState->setValue(ptIndex / hundredsOfPt);
		}
	}

	ui.progressBar_dataLoadState->setValue(100);

	m_cht_STFTWnd->addSeries(m_series_STFTWnd);

	bool attachAxisStateA = m_series_STFTWnd->attachAxis(m_axis_STFTWndTime);
	bool attachAxisStateB = m_series_STFTWnd->attachAxis(m_axis_STFTWndVal);
}

void STFTWgt::updateSTFTWndLabel(double WndMsec, int WndPtCount)
{
	ui.label_resultWndLength_Point->setText(QString("窗型等价点数：%1").arg(WndPtCount));
	ui.label_resultWndLength_Time->setText(QString("窗型等价时长：%1 ms").arg(WndMsec, 0, 'f', 2));
}