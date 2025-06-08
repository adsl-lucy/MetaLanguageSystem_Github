#pragma once

#include <QWidget>
#include <QtCharts>
#include "./ui_FFTWindowWgt.h"

#include "../../protocol/protocol_audio.h"
#include "../../Perception/FFTWindowManager/FFTWindowManager.h"
#include "./EffOscWidget.h"

class FFTWindowWgt : public QWidget
{
	Q_OBJECT

public:
	FFTWindowWgt(QWidget *parent = nullptr);
	~FFTWindowWgt();

public:signals:
	void sgn_GoBDSNRResult(QString DataKey);

public slots:
	  void slot_AudoGenWndSpecConstrainResult(QString dataKey);

protected:signals:
	void sgn_generateFFTWndTimeGraph(ST_STFTWnd& WndResult);

protected:
	void initUI();
	void initWndTimeCht();
	void initActiveFuncCht();
	void initWndFFTSpectrumCht();
	void initActiveWndFFTSpectrumCht();
	void initWndPartBarCht();
	void initWndConstrainResultCht();
	void initEffOscWgt();

	ST_STFTWndPara getWndPara();
	
	void loadWndToCht(QString ChtName, ST_STFTWnd& WndResult);//里面可以看看窗内一个位置不同点的权重情况
	void updateSTFTWndLabel(double WndMsec, int WndPtCount);
	
	void saveWndFFTResult(ST_STFTWndAnsResult& result);
	void loadWndFFTResult(ST_STFTWndAnsResult& result);
	void loadWndFFTPartEstimate(ST_STFTWndAnsResult& result);

	void saveActiveWndFFTResult(ST_ActiveWndAnsResult& result);
	void loadActiveWndFFTResult(ST_ActiveWndAnsResult& result);

	int getPointIndex(const QPointF& ChartPos);

	ST_STFTActiveWndPara getActWndPara();
	void loadActiveWndToCht(ST_ActvieWnd& WndResult);


protected slots:
	void slot_WndLengthTypeChanged();
	
	void slot_GenFFTWndTimeGraphBtnClicked();
	void slot_GenFFTWndFFTGraphBtnClicked();
	void slot_UpdateFFTWndFFTGraphBtnClicked();
	void slot_getFFTWindowManagerMsg(int percentage, int threadCount, QString msg);
	void slot_getWndFFTResult(ST_STFTWndAnsResult& result);
	void slot_WndFFTMouseHovered(const QPointF& point, bool state);
	void slot_wndFFTPartChtHovered(bool status, int index, QBarSet* barset);
	void slot_updateFFTPartCht();
	void slot_GenWndConstrainResultBtnClicked();
	void slot_getWndConstrainResult(ST_WndSpecConstrainDistribute& result);
	void slot_wndConstrainPartChtHovered(bool status, int index, QBarSet* barset);

	void slot_GenActiveWndBtnClicked();
	void slot_ActiveWndStartTimeTypeChanged();
	void slot_ActiveWndShowTypeBtnChanged();
	void slot_GenActiveWndFFTGraphBtnClicked();
	void slot_getActiveWndMsg(int percentage, int threadCount, QString msg);
	void slot_getActiveWndANSResult(ST_ActiveWndAnsResult& result);
	void slot_ActiveWndFFTMouseHovered(const QPointF& point, bool state);
	void slot_UpdateActiveWndFFTGraphBtnClicked();
private:
	Ui::FFTWindowWgtClass ui;

	EffOscWidget*  m_pEffOscWgt = nullptr;

	QButtonGroup*  m_pBtnGroupFFTWndLengthType = nullptr;
	QButtonGroup*  m_pBtnGroupFFTWndFFTValShowType = nullptr;
	QButtonGroup*  m_pBtnGroupActiveWndStartTimeType = nullptr;
	QButtonGroup*  m_pBtnGroupActiveWndValShowType = nullptr;

	QLineSeries*	m_series_WndTimeGraph		= nullptr;
	QValueAxis*		m_axis_WndTimeGraph_Time	= nullptr;
	QValueAxis*		m_axis_WndTimeGraph_ptIndex	= nullptr;
	QValueAxis*		m_axis_WndTimeGraph_ptval	= nullptr;
	QChart*			m_cht_WndTimeGraph			= nullptr;
	QChartView*		m_chtView_WndTimeGraph		= nullptr;

	ST_STFTWndAnsResult m_tempWndFFTResult;

	QLineSeries*	m_series_WndFFTResult	= nullptr;
	QValueAxis*		m_axis_WndFFTFreq		= nullptr;
	QValueAxis*		m_axis_WndFFTFreqAmp	= nullptr;
	QChart*			m_cht_WndFFT			= nullptr;
	QChartView*		m_chtView_WndFFT		= nullptr;

	QVector<ST_FFTPoint> m_vecWndFFTPt;

	//因为QChart自带图表的数据有丢失，所以额外添加一个算位置的中间量
	qreal			m_startValue	= 0;		//图表开始的x值
	qreal			m_endValue		= 0;		//图表结束的x值
	qreal			m_totalLength	= 0;		//图表x值跨度
	qreal			m_interval		= 0;		//图表一个点占据的长度

	QVector<QBarSet*>   m_vecWndFFTPartSet;
	QBarSeries*			m_WndFFTPartSeries		= nullptr;
	QBarCategoryAxis*	m_WndFFTPartAxisX		= nullptr;
	QValueAxis*			m_WndFFTPartAxisY		= nullptr;
	QChart*				m_WndFFTPartCht			= nullptr;
	QChartView*			m_WndFFTPartChtView		= nullptr;


	bool				m_bOnGenWndConstrainResult		= false;
	ST_WndSpecConstrainDistribute m_tampResult;
	QVector<QBarSet*>   m_vecWndConstrainResultSet;
	QBarSeries*			m_WndConstrainResultSeries		= nullptr;
	QBarCategoryAxis*	m_WndConstrainResultAxisX		= new QBarCategoryAxis();
	QValueAxis*			m_WndConstrainResultAxisY		= nullptr;
	QChart*				m_WndConstrainResultCht			= nullptr;
	QChartView*			m_WndConstrainResultChtView		= nullptr;

	QLineSeries*		m_series_ActiveWnd_STFTWnd		= nullptr;
	QLineSeries*		m_series_ActiveWnd_Active		= nullptr;
	QLineSeries*		m_series_ActiveWnd_ActiveWnd	= nullptr;
	QValueAxis*			m_axis_ActiveFunc_Time			= nullptr;
	QValueAxis*			m_axis_ActiveFunc_ptIndex		= nullptr;
	QValueAxis*			m_axis_ActiveFunc_ptval			= nullptr;
	QChart*				m_cht_ActiveWndPt				= nullptr;
	QChartView*			m_chtView_ActiveWndPt			= nullptr;

	QLineSeries*		m_series_ActiveWndFFTResult		= nullptr;
	QValueAxis*			m_axis_ActiveWndFFTFreq			= nullptr;
	QValueAxis*			m_axis_ActiveWndFFTFreqAmp		= nullptr;
	QChart*				m_cht_ActiveWndFFT				= nullptr;
	QChartView*			m_chtView_ActiveWndFFT			= nullptr;


	QVector<ST_FFTPoint> m_vecActiveWndFFTPt;


};
