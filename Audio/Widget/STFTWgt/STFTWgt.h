#pragma once

#include <QWidget>
#include <QDebug>
#include <QtCharts>
#include <QButtonGroup>
#include <QThread>
#include <QThreadPool>

#include "./ui_STFTWgt.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../Perception/FFTWindowManager/FFTWindowManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "./STFTAnalyse/STFTAnalysePanel.h"
#include "./STFTAnalyse/STFTCht/FFT_Chart_STFTHotGram.h"

class STFTWgt : public QWidget
{
	Q_OBJECT

public:
	STFTWgt(QWidget *parent = nullptr);
	~STFTWgt();

public:signals:
	void sgn_generateSTFTWnd(ST_STFTWnd& WndResult);
	void sgn_generateSTFTResult(ST_STFTInputData& inputData);
	void sgn_startGenWndSpecConstrainResult(QString dataKey);

public slots:
	void slot_getSTFTGenerateState(int percentage, int activateThreadCount,QString errstr);
	void slot_getSTFTResult(ST_STFTOutputData& outputData);
	void slot_AudoGenSTFTData(QString DataKey);

protected:

	void initUI();
	void initLoadSigCht();
	void initSigWndCht();
	void initSTFTHotCht();
	void initSTFTPanel();

	void showEvent(QShowEvent* event);

	void updateLoadDataCombox();
	void updateLoadSigLabel(int ChnCount, int durationMs,int pointCount,int sampleRate);

	void loadSigFromCurrentSelGenSig();
	void loadSigFromCurrentSelWavSig();

	void loadSigToCht(QString chtName,int startMsec, int endMsec, double maxAmp, const QVector<ST_AudioPoint>& dataVec);
	void loadWndToCht(QString ChtName, ST_STFTWnd& WndResult);
	void updateSTFTWndLabel(double WndMsec,int WndPtCount);

	ST_STFTWndPara getWndPara();

	QTime updateProcessTime();
	//Qt concurrent sig finish 不一定发射 搞得打个时间要靠这个
	void  printSTFTProcessTime(QString prefix, QString suffix);


protected slots:
	void slot_loadGenSigBtnClicked();
	void slot_generateSTFTWndBtnClicked();
	void slot_generateSTFTResultBtnClicked();
	void slot_WndLengthTypeChanged();
	void slot_WndGapTypeChanged();
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);

private:
	Ui::STFTWgtClass ui;

	QString			m_STFTDataKey;

	QButtonGroup*	m_pBtnGroupLoadSigType	= nullptr;

	QLineSeries*	m_series_LoadSignal		= nullptr;
	QValueAxis*		m_axis_LoadSigTime		= nullptr;
	QValueAxis*		m_axis_LoadSigVal		= nullptr;
	QChart*			m_cht_LoadSig			= nullptr;
	QChartView*		m_chtView_LoadSig		= nullptr;

	QButtonGroup*	m_pBtnGroupSTFTWndType = nullptr;
	QButtonGroup*	m_pBtnGroupSTFTWndLengthType = nullptr;

	QLineSeries*	m_series_STFTWnd		= nullptr;
	QValueAxis*		m_axis_STFTWndTime		= nullptr;
	QValueAxis*		m_axis_STFTWndPoint		= nullptr;
	QValueAxis*		m_axis_STFTWndVal		= nullptr;
	QChart*			m_cht_STFTWnd			= nullptr;
	QChartView*		m_chtView_STFTWndSig	= nullptr;

	QButtonGroup* m_pBtnGroupSTFTGapType = nullptr;

	STFTAnalysePanel* m_pSTFTPanel = nullptr;
	FFT_Chart_STFTHotGram* m_pHotGram = nullptr;

	QTime m_STFTProcessTime;

};
