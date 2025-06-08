#pragma once

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QButtonGroup>
#include "./ui_EffOscWidget.h"

#include "../../protocol/protocol_audio.h"
#include "../STFTWgt/STFTAnalyse/STFTCht/FFT_Chart_STFTHotGram.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../Perception/AudioEngine/AudioEngine.h"
#include "../../Perception/FFTWindowManager/FFTWindowManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "../../Perception/WndSpecConstrainNetwork/WndSpecConstrainNetwork.h"
#include "../../TimeSecCht/TimeSecCht_Wgt.h"
//#include "./EffOscTimeSecCht.h"

class EffOscWidget : public QWidget
{
	Q_OBJECT

public:
	EffOscWidget(QWidget *parent = nullptr);
	~EffOscWidget();

public:signals:
	void sgn_GoBDSNRResult(QString DataKey);

public slots:
	void slot_getNewSTFTData(QString dataKey);
	void slot_GenWndSpecConstrainBtnClicked();

protected:
	void init();
	void initUI();
	void initUpdateTimer();
	void updateSTFTLabel(const ST_STFTOutputData& data);
	void updateSTFTPanel(const ST_STFTOutputData& data);

	void updateTimeFrameLabel(QTime FrameStartTime, QTime FrameMidTime, QTime FrameEndTime);

	void resetFrameRateState();
	void updateFrameRateState();

protected slots:
	void slot_TimeFrameSliderMoved(int newVal);
	void slot_updateHotChtBtnClicked();
	void slot_updateTimeSecChtBtnClicked();	
	void slot_NoiseBtnGroupClicked();
	void slot_play();
	void slot_jump();
	void slot_stop();
	void slot_updateTimerTimeUp();
	void slot_getFFTWindowManagerMsg(int percentage, int threadCount, QString msg);
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateWndSepcConstrainGenState(int percentage, int activateThreadCount, QString errstr);
	void slotWndConstrainResultGet();
	void slot_btnNextFrameClicked();
	void slot_btnLastFrameClicked();
	void slot_TimeSecChtTypeChanged();

private:
	Ui::EffOscWidgetClass ui;

	QString m_STFTDataKey;
	ST_STFTInputpara	m_dataPara;

	FFT_Chart_STFTHotGram*	m_pSTFTHotCht		= nullptr;
	//EffOscTimeSecCht*		m_pEffOscTimeSecCht = nullptr;
	TimeSecCht_Wgt*			m_pTimeSecCht		= nullptr;

	bool m_bOnGenWndSpecConstrainResult = false;

	QButtonGroup* m_pBtnGroup_getWndSpecConstraindata = nullptr;
	QButtonGroup* m_pBtnGroup_TimeSecChtShowType = nullptr;
	QButtonGroup* m_pBtnGroup_NoiseDrawSet = nullptr;

	QTimer*		m_pUpdateSectionTimer	= nullptr;
	int			m_nUpdateMsec			= 50;
	int			m_nCurrentTimeUpCount	= 0;

	int			m_nStatFrameRateStartFrameIndex = -1;
	QTime		m_TimeFrameRateStatStartSysTime = QTime(0, 0, 0);

};
