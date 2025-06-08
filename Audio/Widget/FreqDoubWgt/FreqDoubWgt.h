#pragma once

#include <QWidget>
#include <QtCharts>
#include <QButtonGroup>

#include "../../protocol/protocol_audio.h"
#include "../../Perception/AudioEngine/AudioEngine.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "../STFTWgt/STFTAnalyse/STFTCht/FFT_Chart_STFTHotGram.h"
#include "../../Cognition/FreqDoubleRelevanceNetWork/FreqDoubleNetwork.h"
#include "./FreqDoubChtPanelWgt.h"

#include "./ui_FreqDoubWgt.h"

class FreqDoubWgt : public QWidget
{
	Q_OBJECT

public:
	FreqDoubWgt(QWidget *parent = nullptr);
	~FreqDoubWgt();

public slots:
	void slot_getNewSTFTData(QString dataKey);
	void slot_autoGenFreqDoubData(QString dataKey);

protected:
	void initUi();
	void initChtPanelWgt();
	void initFreqDoubANSCht();
	void updateFreqDoubleTensorCht(const ST_FreqMultipleTensor& result,int CenterFreq,int maxMultipleTime);

	void getFreqMultipleTensorGenPara(ST_FreqMultipleTensorGenPara& GenPara);

protected slots:
	void slot_GenFreqDoubTensorBtnClicked();
	void slot_updateChtBtnClicked();
	void slot_updateFreqDoubleTensorGenState(int percentage, int activateThreadCount, QString errstr);

private:
	Ui::FreqDoubWgtClass ui;

	FreqDoubChtPanelWgt* m_pChtPanelWgt = nullptr;

	ST_FreqMultipleTensor	m_tempTensor;

	QCandlestickSeries*		m_FreqDoubDistribute_Series		= nullptr;
	QBarCategoryAxis*		m_FreqDoubDistribute_axisX		= nullptr;
	QValueAxis*				m_FreqDoubDistribute_axisY		= nullptr;
	QChart*					m_FreqDoubDistribute_chart		= nullptr;
	QChartView*				m_FreqDoubDistribute_chartView	= nullptr;

	QVector<QBarSet*>		m_vecFreqDoubleCount_Set;
	QBarSeries*				m_FreqDoubleCount_Series		= nullptr;
	QBarCategoryAxis*		m_FreqDoubleCount_AxisX			= nullptr;
	QValueAxis*				m_FreqDoubleCount_AxisY			= nullptr;
	QChart*					m_FreqDoubleCount_Cht			= nullptr;
	QChartView*				m_FreqDoubleCount_ChtView		= nullptr;

};
