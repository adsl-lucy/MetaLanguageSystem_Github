#pragma once

#include <QWidget>
#include <QtCharts>
#include <QButtonGroup>
#include "./ui_FFTTestWgt.h"

#include "../../protocol/protocol_audio.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

class FFTTestWgt : public QWidget
{
	Q_OBJECT

public:
	FFTTestWgt(QWidget *parent = nullptr);
	~FFTTestWgt();

public:signals:
	void sgn_drawBaseSig(ST_AudioBaseSignal& resultSignal);
	void sgn_drawModuleSig(ST_AudioModuleSignal& modSignal);
	void sgn_drawFFTResult(ST_FFTInputData& FFTPara,ST_FFTOutputData& resultFrame);
	void sgn_saveModSigToDataCenter(ST_AudioModuleSignal& m_moduleSigResult,bool& saveState);

public slots:
	void slot_getBaseSigValue(ST_AudioBaseSignal& baseSignalVal);
	void slot_getModuleSigValue(ST_AudioModuleSignal& modSig, bool drawModSig, bool drawModBaseSig);
	void slot_getFFTResult(ST_FFTOutputData& resultFrame);


protected:
	void initUI();
	void initBaseSigChartWgt();
	void initModSigChartWgt();
	void initFFTChtWgt();

	ST_AudioBaseSignalPara getBaseSigPara();

	void copyModuleSigResult(ST_AudioModuleSignal& result);
	

protected slots:
	void slot_onDrawBaseSigBtnClicked();
	void slot_onDrawModuleSigBtnClicked();
	void slot_onDrawFFTBtnClicked();
	void slot_onSaveSigToDataCenterBtnClicked();

private:
	Ui::FFTTestWgtClass ui;

	QButtonGroup*	m_pBtnGroup_ModSigType			= nullptr;
	QButtonGroup*	m_pBtnGroup_FFTType				= nullptr;

	QLineSeries*	m_series_BaseSignal				= nullptr;
	QValueAxis*		m_axis_BaseSigTime				= nullptr;
	QValueAxis*		m_axis_BaseSigVal				= nullptr;
	QChart*			m_cht_baseSig					= nullptr;
	QChartView*		m_chtView_baseSig				= nullptr;

	QLineSeries*	m_series_ModuleSignal			= nullptr;
	QLineSeries*	m_series_ModuleSignalInverse	= nullptr;

	QLineSeries*	m_series_ModBaseSignal			= nullptr;

	QValueAxis*		m_axis_ModuleSigTime			= nullptr;
	QValueAxis*		m_axis_ModuleSigDepthVal		= nullptr;
	QValueAxis*		m_axis_ModuleSigResultVal		= nullptr;
	QChart*			m_cht_ModuleSig					= nullptr;
	QChartView*		m_chtView_ModuleSig				= nullptr;

	QLineSeries*	m_series_FFTResult				= nullptr;
	QValueAxis*		m_axis_FFTFreq					= nullptr;
	QValueAxis*		m_axis_FFTFreqAmp				= nullptr;
	QChart*			m_cht_FFT						= nullptr;
	QChartView*		m_chtView_FFT					= nullptr;

	ST_AudioModuleSignal m_moduleSigResult;

};
