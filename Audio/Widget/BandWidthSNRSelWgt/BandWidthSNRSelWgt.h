#pragma once

#include <QWidget>
#include <QtCharts>
#include <QButtonGroup>

#include "../../protocol/protocol_audio.h"
#include "../../Perception/BandWidthFilter/BandWidthFilterManager.h"
#include "../../Perception/AudioEngine/AudioEngine.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

#include "../STFTWgt/STFTAnalyse/STFTCht/FFT_Chart_STFTHotGram.h"
#include "../../TimeSecCht/TimeSecCht_Wgt.h"
//#include "./BDSNR_TimeSecCht.h"
//#include "./TimeSecCht_BDSNR_OpenGL.h"

#include "./ui_BandWidthSNRSelWgt.h"

class BandWidthSNRSelWgt : public QWidget
{
	Q_OBJECT

public:
	BandWidthSNRSelWgt(QWidget *parent = nullptr);
	~BandWidthSNRSelWgt();

public:signals:
	void sgn_goEffSigBuffWgt(QString dataKey);

public slots:
	void slot_autoGenBDSNRResult(QString DataKey);

protected:
	void initUi();
	void initFilterCht();
	void initHotCht();
	void initTimeSecCht();
	void initUpdateTimer();
	void showFilterResult(const ST_BandWidthFilterData& result);

	ST_BandWidthFilterPara getCurrentFilterPara();
	void updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime);

	void resetFrameRateState();
	void updateFrameRateState();

protected slots:
	void slot_updateBandWidthFilterCht();
	void slot_GenfBandWidthFilterPtAndUpdateCht();
	void slot_startGenBDSNRResultBtnClicked();

	void slot_getNewSTFTData(QString dataKey);
	void slot_BDSNR_DataGet(QString dataKey);
	void updateSTFTLabel(const ST_STFTOutputData& data);
	void updateSTFTPanel(const ST_STFTOutputData& data);

	void slot_TimeSecChtShowTypeChanged();
	void slot_NoiseBtnGroupClicked();
	void slot_updateHotChtBtnClicked();
	void slot_updateTimeSecChtBtnClicked();	
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_BDSNR_GenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateTimeSecChtGenState(int percentage, int activateThreadCount, QString errstr);

	void slot_play();
	void slot_jump();
	void slot_stop();
	void slot_updateTimerTimeUp();
	void slot_TimeFrameSliderMoved(int newVal);
	void slot_btnNextFrameClicked();
	void slot_btnLastFrameClicked();


private:
	Ui::BandWidthSNRSelWgtClass ui;

	QButtonGroup* m_pBtnGroup_FilterMaxValType		= nullptr;
	QButtonGroup* m_pBtnGroup_FilterCond_MainArea	= nullptr;
	QButtonGroup* m_pBtnGroup_FilterCond_SubArea	= nullptr;
	QButtonGroup* m_pBtnGroup_GetBDSNRData			= nullptr;
	QButtonGroup* m_pbtnGroupTimeSecChtShowType		= nullptr;
	QButtonGroup* m_pBtnGroup_NoiseDrawSet			= nullptr;

	QValueAxis* m_axis_MFCCWeight = nullptr;
	QValueAxis* m_axis_MFCCFreq = nullptr;
	QChart* m_cht_MFCC = nullptr;
	QChartView* m_chtView_MFCC = nullptr;

	FFT_Chart_STFTHotGram*		m_pHotCht = nullptr;
	TimeSecCht_Wgt*				m_pTimeSecCht = nullptr;
	//BDSNR_TimeSecCht*			m_pTimeSecCht = nullptr;

	//TimeSecCht_BDSNR_OpenGL* m_pTestCht = nullptr;

	QString				m_STFTDataKey;
	ST_STFTInputpara	m_dataPara;

	QTimer* m_pUpdateSectionTimer = nullptr;
	int m_nUpdateMsec = 50;
	int m_nCurrentTimeUpCount = 0;

	int m_nStatFrameRateStartFrameIndex = -1;
	QTime m_TimeFrameRateStatStartSysTime = QTime(0, 0, 0);

};
