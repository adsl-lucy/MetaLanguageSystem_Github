//添加冲激调制函数后的改良屏蔽策略面板
//同时消除一些前期开发的历史遗留问题
#pragma once

#include <QWidget>
#include <QtCharts>

#include "../../protocol/protocol_audio.h"
#include "../../Perception/EffOscMaskManager/EffOscMaskManager.h"
#include "./ui_EffOscWgt.h"

class EffOscWgt : public QWidget
{
	Q_OBJECT

public:
	EffOscWgt(QWidget *parent = nullptr);
	~EffOscWgt();

protected:
	void initUI();
	void initWndTimeCht();
	void initWndFFTCht();


	ST_STFTWndPara getWndPara();
	//仅包含STFT窗的图表
	void loadNormalWndToCht(const ST_STFTWnd& WndResult);
	void updateSTFTWndLabel(const ST_STFTWnd& WndResult);

	ST_STFTActiveWndPara getActWndPara();
	void loadActiveWndToCht(ST_ActvieWnd& WndResult);
	void loadActiveWndFFTToCht(const ST_ActiveWndAnsResult& result);

protected slots:
	void slot_WndLengthTypeChanged();
	void slot_GenSTFTWndBtnClicked();

	void slot_ActiveWndShowTypeBtnChanged();
	void slot_GenActiveWndBtnClicked();
	void slot_GenActiveWndFFTSpecBtnClicked();
	void slot_updateWndFFTChtBtnClicked();	
	void slot_getActiveWndMsg(int percentage, int threadCount, QString msg);
	void slot_getActiveWndANSResult(ST_ActiveWndAnsResult& result);
	void slot_ActiveWndFFTMouseHovered(const QPointF& point, bool state);

private:
	Ui::EffOscWgtClass ui;

	QButtonGroup* m_pBtnGroupFFTWndLengthType = nullptr;
	QButtonGroup* m_pBtnGroupFFTWndFFTValShowType = nullptr;
	QButtonGroup* m_pBtnGroupActiveWndValShowType = nullptr;

	QLineSeries*	m_series_ActiveWnd_STFTWnd		= nullptr;
	QLineSeries*	m_series_ActiveWnd_Active		= nullptr;
	QLineSeries*	m_series_ActiveWnd_ActiveWnd	= nullptr;
	QValueAxis*		m_axis_WndTimeCht_Time			= nullptr;
	QValueAxis*		m_axis_WndTimeCht_ptIndex		= nullptr;
	QValueAxis*		m_axis_WndTimeCht_ptVal			= nullptr;
	QChart*			m_cht_WndTime					= nullptr;
	QChartView*		m_chtView_WndTimeCht			= nullptr;

	QVector<ST_FFTPoint> m_vecActiveWndFFTPt;

	QLineSeries*	m_series_WndFFTResult	= nullptr;
	QValueAxis*		m_axis_WndFFTFreq		= nullptr;
	QValueAxis*		m_axis_WndFFTFreqAmp	= nullptr;
	QChart*			m_cht_WndFFT			= nullptr;
	QChartView*		m_chtView_WndFFT		= nullptr;

};
