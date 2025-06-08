#include "FreqDoubWgt.h"
#pragma execution_character_set("utf-8")

FreqDoubWgt::FreqDoubWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUi();
	initChtPanelWgt();
	initFreqDoubANSCht();
}

FreqDoubWgt::~FreqDoubWgt()
{}

void FreqDoubWgt::initUi()
{
	ui.progressBar_TensorGenState->setValue(0);
	connect(ui.btn_GenTensor,&QPushButton::clicked,this,&FreqDoubWgt::slot_GenFreqDoubTensorBtnClicked);
	connect(ui.btn_updateTensorCht, &QPushButton::clicked, this, &FreqDoubWgt::slot_updateChtBtnClicked);
	connect(DataCenterManager::instance(), &DataCenterManager::sgn_STFTDataSaved, this, &FreqDoubWgt::slot_getNewSTFTData);
	connect(FreqDoubleNetwork::instance(), &FreqDoubleNetwork::sgn_FDN_GenState, this, &FreqDoubWgt::slot_updateFreqDoubleTensorGenState);
	
}

void FreqDoubWgt::initChtPanelWgt()
{
	m_pChtPanelWgt = new FreqDoubChtPanelWgt(this);
	ui.VLayout_ChtPanel->insertWidget(0, m_pChtPanelWgt);
	connect(m_pChtPanelWgt, &FreqDoubChtPanelWgt::sgn_AskFreqDoubleTensorPara, this, [=](ST_FreqMultipleTensorGenPara& GenPara)
		{
			getFreqMultipleTensorGenPara(GenPara);
		});
}

void FreqDoubWgt::initFreqDoubANSCht()
{
	m_FreqDoubDistribute_axisX = new QBarCategoryAxis(this);
	m_FreqDoubDistribute_axisY = new QValueAxis(this);
	m_FreqDoubDistribute_axisY->setRange(0, 20000);

	m_FreqDoubDistribute_chart = new QChart();
	m_FreqDoubDistribute_chart->setTitle("Frequency doubling ditribution");
	m_FreqDoubDistribute_chart->setAnimationOptions(QChart::SeriesAnimations);

	m_FreqDoubDistribute_chart->addAxis(m_FreqDoubDistribute_axisX, Qt::AlignBottom);
	m_FreqDoubDistribute_chart->addAxis(m_FreqDoubDistribute_axisY, Qt::AlignLeft);
	m_FreqDoubDistribute_chart->legend()->setVisible(false);

	m_FreqDoubDistribute_chartView = new QChartView(m_FreqDoubDistribute_chart);
	m_FreqDoubDistribute_chartView->setRenderHint(QPainter::Antialiasing);
	m_FreqDoubDistribute_chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	ui.HLayout_Cht_FreqDoubDistribute->insertWidget(0, m_FreqDoubDistribute_chartView);

	m_vecFreqDoubleCount_Set.clear();

	m_FreqDoubleCount_Series = nullptr;

	m_FreqDoubleCount_AxisY = new QValueAxis();
	m_FreqDoubleCount_AxisY->setRange(0, 40);

	m_FreqDoubleCount_AxisX = new QBarCategoryAxis();

	m_FreqDoubleCount_Cht = new QChart();
	//m_WndFFTPartchart->addSeries(series);
	m_FreqDoubleCount_Cht->setTitle("Freq doubling Count");
	m_FreqDoubleCount_Cht->setAnimationOptions(QChart::NoAnimation);
	m_FreqDoubleCount_Cht->addAxis(m_FreqDoubleCount_AxisX, Qt::AlignBottom);
	m_FreqDoubleCount_Cht->addAxis(m_FreqDoubleCount_AxisY, Qt::AlignLeft);
	m_FreqDoubleCount_Cht->legend()->setVisible(true);
	m_FreqDoubleCount_Cht->legend()->setAlignment(Qt::AlignBottom);

	m_FreqDoubleCount_ChtView = new QChartView(m_FreqDoubleCount_Cht);
	m_FreqDoubleCount_ChtView->setRenderHint(QPainter::Antialiasing);
	m_FreqDoubleCount_ChtView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	ui.HLayout_Cht_FreqDoubCount->insertWidget(0, m_FreqDoubleCount_ChtView);
	

}

void FreqDoubWgt::slot_getNewSTFTData(QString dataKey)
{
	const ST_STFTOutputData& data = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	if (data.vecOutput.isEmpty())
	{
		qDebug() << "OscillationSeparatorWgt::slot_getSTFTData : dataVec Empty!";
		return;
	}

	ui.SBox_SampleRate->setValue(data.InputPara.sampleRate);
	ui.SBox_WndPtCount->setValue(data.InputPara.WndPara.pointCount);
	m_pChtPanelWgt->slot_getNewSTFTData(dataKey);

}

void FreqDoubWgt::slot_autoGenFreqDoubData(QString dataKey)
{
	ui.mainTabWidget->setCurrentIndex(0);
	slot_GenFreqDoubTensorBtnClicked();
	ui.mainTabWidget->setCurrentIndex(1);
	m_pChtPanelWgt->slot_AutoGenFreqDoubData(dataKey);
}

void FreqDoubWgt::getFreqMultipleTensorGenPara(ST_FreqMultipleTensorGenPara& para)
{
	para.sampleRate = ui.SBox_SampleRate->value();
	para.WndPtCount = ui.SBox_WndPtCount->value();
	para.MaxEffectFreq = ui.SBox_MaxEffectFreq->value();
	para.FFTWndPeakDriftRatio = ui.DSBox_WndSpecConstrainFreqDriftRatio->value() / 100.0;
	para.startFreq = ui.DSBox_TensorStartFreq->value();
	para.endFreq = ui.DSBox_TensorEndFreq->value();
	para.maxMultipleTime = ui.SBox_MaxMultiTime->value();
	para.ParentRealtionIncludeStartFreqCount = ui.SBox_ParentMatrixIncludeMainFreqCount->value();
	para.isCutOffOnSelOverlappingStartPos = ui.checkBox_cutOffOnOverLappingStartPos->isChecked();
}

void FreqDoubWgt::slot_GenFreqDoubTensorBtnClicked()
{
	ST_FreqMultipleTensorGenPara para;
	getFreqMultipleTensorGenPara(para);

	FreqDoubleNetwork::instance()->startGenFreqDoubleTensor(para, m_tempTensor);

	ui.label_TensorResult_StartFreq->setText(QString("张量起始频率： %1 hz").arg(m_tempTensor.resultPara.tensorStartFreqVal, 0, 'f', 2));
	ui.label_TensorResult_EndFreq->setText(QString("张量终止频率： %1 hz").arg(m_tempTensor.resultPara.tensorEndFreqVal, 0, 'f', 2));
	ui.label_TensorResult_MatrixCount->setText(QString("倍频矩阵个数： %1").arg(m_tempTensor.VecMultipleMatrix.size()));
	ui.label_TensorResult_MatrixFreqInterval->setText(QString("矩阵频率间隔： %1 hz").arg(m_tempTensor.resultPara.TensorFreqInterval, 0, 'f', 2));

	ui.SBox_Cht_ShowMatricFreq->setMinimum(0);
	ui.SBox_Cht_ShowMatricFreq->setMaximum(m_tempTensor.resultPara.tensorEndFreqVal);

	if (ui.checkBox_UpdateChtAfterGetTensor->isChecked())
	{
		slot_updateChtBtnClicked();
	}
	
}

void FreqDoubWgt::slot_updateFreqDoubleTensorGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_TensorGenState->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_tensorGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_tensorGenState->setText(QString("生成结束"));
	}
}

void FreqDoubWgt::slot_updateChtBtnClicked()
{
	int centerFreq = ui.SBox_Cht_ShowMatricFreq->value();
	int maxMutipleTime = ui.SBox_Cht_ShowMultipleTime->value();
	updateFreqDoubleTensorCht(m_tempTensor, centerFreq, maxMutipleTime);
}

void FreqDoubWgt::updateFreqDoubleTensorCht(const ST_FreqMultipleTensor& result, int CenterFreq, int maxMultipleTime)
{
	int centerFreqMatrixIndex = ((double)CenterFreq - result.resultPara.tensorStartFreqVal) / result.resultPara.TensorFreqInterval;
	if (centerFreqMatrixIndex < 0 || centerFreqMatrixIndex >= result.VecMultipleMatrix.size())
	{
		qDebug() << "FreqDoubWgt::updateFreqDoubleTensorCht invalid FreqIndexInVec : " << centerFreqMatrixIndex;
		return;
	}

	const ST_FreqMultipleMaxtrix& matrix = result.VecMultipleMatrix[centerFreqMatrixIndex];

	ui.label_cht_IsMatrixInsertFreq->setText(QString("这是不是一个插入频率点：%1").arg(matrix.isInsertFreq?QString("是"):QString("不是")));

	if (matrix.isInsertFreq)
	{
		ui.label_Cht_ShowFreqPtIndex->setText(QString("分析频率FFT点索引：%1").arg(matrix.BaseFreqIndex_double, 0, 'f', 1));
	}
	else
	{
		ui.label_Cht_ShowFreqPtIndex->setText(QString("分析频率FFT点索引：%1").arg(matrix.BaseFreqIndex_int));
	}
	
	ui.label_Cht_ShowFreq->setText(QString("分析频率FFT点频率：%1").arg(matrix.BaseFreq, 0, 'f', 2));
	ui.label_Cht_ShowMatricMaxMultTime->setText(QString("有效倍频次数：%1").arg(matrix.vecMultiplePos.size()));
	ui.label_Cht_selfOverlappintStartMultiTime->setText(QString("首个自交叠区域倍频次数：%1").arg(matrix.selfOverlappingStartMultipleTime));

	m_FreqDoubDistribute_chart->removeAllSeries();
	m_FreqDoubDistribute_Series = new QCandlestickSeries();
	m_FreqDoubDistribute_Series->setName(QString("baseFreq : %1 mutipleMatrix").arg(matrix.BaseFreq, 0, 'f', 2));
	m_FreqDoubDistribute_Series->setIncreasingColor(QColor(Qt::green));

	QStringList MultiPosDistributeCategories;

	double maxFreq = 0;

	for (int multiplePosIndex = 0; multiplePosIndex < matrix.vecMultiplePos.size(); multiplePosIndex++)
	{
		if (multiplePosIndex + 1 > maxMultipleTime)
		{
			break;
		}

		const ST_FreqMultiplePos& MultiplePos = matrix.vecMultiplePos[multiplePosIndex];

		QCandlestickSet* CandleSet = new QCandlestickSet();
		CandleSet->setLow(MultiplePos.ExactStartFreq);
		CandleSet->setHigh(MultiplePos.ExactEndFreq);
		CandleSet->setOpen(MultiplePos.TruncateStartFreq);
		CandleSet->setClose(MultiplePos.TruncateEndFreq);
		m_FreqDoubDistribute_Series->append(CandleSet);
		MultiPosDistributeCategories << QString::number(MultiplePos.multipleTime);

		maxFreq = qMax(maxFreq, MultiplePos.ExactEndFreq);

	}

	m_FreqDoubDistribute_chart->addSeries(m_FreqDoubDistribute_Series);

	maxFreq = qMin(20000.0, maxFreq *1.05);
	m_FreqDoubDistribute_axisY->setRange(0, maxFreq);

	m_FreqDoubDistribute_axisX->clear();
	m_FreqDoubDistribute_axisX->setCategories(MultiPosDistributeCategories);	

	bool state1 = m_FreqDoubDistribute_Series->attachAxis(m_FreqDoubDistribute_axisX);
	bool state2 = m_FreqDoubDistribute_Series->attachAxis(m_FreqDoubDistribute_axisY);

	m_FreqDoubleCount_Cht->removeAllSeries();
	m_FreqDoubleCount_Series = new QBarSeries();

	double maxCount = 0;
	QStringList MultiPosPtCountCategories;
	QBarSet* MultiplePosSet = new QBarSet(QString("baseFreq %1").arg(matrix.BaseFreq));

	for (int multiplePosIndex = 0; multiplePosIndex < matrix.vecMultiplePos.size(); multiplePosIndex++)
	{
		if (multiplePosIndex + 1 > maxMultipleTime)
		{
			break;
		}

		const ST_FreqMultiplePos& MultiplePos = matrix.vecMultiplePos[multiplePosIndex];	
		double MultiplePosPtCount = MultiplePos.endFreqIndex - MultiplePos.startFreqIndex + 1;

		*MultiplePosSet << MultiplePosPtCount;
		MultiPosPtCountCategories << QString::number(MultiplePos.multipleTime);
		
		maxCount = qMax(maxCount, MultiplePosPtCount);

	}
	m_FreqDoubleCount_Series->append(MultiplePosSet);
	m_FreqDoubleCount_Cht->addSeries(m_FreqDoubleCount_Series);

	m_FreqDoubleCount_AxisY->setRange(0, maxCount);

	
	
	m_FreqDoubleCount_AxisX->clear();
	m_FreqDoubleCount_AxisX->append(MultiPosPtCountCategories);

	bool state3 = m_FreqDoubleCount_Series->attachAxis(m_FreqDoubleCount_AxisX);
	bool state4 = m_FreqDoubleCount_Series->attachAxis(m_FreqDoubleCount_AxisY);

}