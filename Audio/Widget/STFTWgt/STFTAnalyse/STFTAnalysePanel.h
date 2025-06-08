#pragma once

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include "./ui_STFTAnalysePanel.h"

#include "./STFTCht/FFT_Chart_STFTHotGram.h"
#include "../../TimeSecCht/TimeSecCht_Wgt.h"
//#include "./STFTCht/FFT_Chart_STFTTimeSection.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../Perception/AudioEngine/AudioEngine.h"

class STFTAnalysePanel : public QWidget
{
	Q_OBJECT

public:
	STFTAnalysePanel(QWidget *parent = nullptr);
	~STFTAnalysePanel();

	void setSTFTData(const ST_STFTOutputData& data);

protected:
	void init();
	void initUI();
	void initUpdateTimer();
	void updateSTFTLabel(const ST_STFTOutputData& data);
	void updateSTFTPanel(const ST_STFTOutputData& data);

	void updateTimeFrameLabel(QTime FrameStartTime,QTime FrameMidTime,QTime FrameEndTime);

	

protected slots:
	void slot_TimeFrameSliderMoved(int newVal);
	void slot_updateTimeSecChtBtnClicked();
	void slot_showTimePhaseSecBtnClicked();
	void slot_showTimePhaseSecWndHide();
	void slot_updateHotChtBtnClicked();
	void slot_play();
	void slot_jump();
	void slot_stop();
	void slot_updateTimerTimeUp();
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr);

	void slot_btnNextFrameClicked();
	void slot_btnLastFrameClicked();
	

private:
	Ui::STFTAnalysePanelClass ui;

	QString m_STFTDataKey;
	ST_STFTInputpara m_dataPara;

	FFT_Chart_STFTHotGram*		m_pSTFTHotChart				= nullptr;
	TimeSecCht_Wgt*				m_pTimeSecCht				= nullptr;
	//FFT_Chart_STFTTimeSection*	m_pSTFTTimeSectionAmpCht	= nullptr;
	//FFT_Chart_STFTTimeSection* m_pSTFTTimeSectionPhaseCht	= nullptr;

	QTimer* m_pUpdateSectionTimer = nullptr;
	int m_nUpdateMsec = 50;
	int m_nCurrentTimeUpCount = 0;

};
