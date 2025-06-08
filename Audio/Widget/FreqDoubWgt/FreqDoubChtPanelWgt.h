#pragma once

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QButtonGroup>

#include "../../protocol/protocol_audio.h"
#include "../STFTWgt/STFTAnalyse/STFTCht/FFT_Chart_STFTHotGram.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../Perception/AudioEngine/AudioEngine.h"
#include "../../Perception/FFTWindowManager/FFTWindowManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "../../Cognition/AudioDiffNet/AudioDiffNet.h"
//#include "./TimeSecCht_FreqDoub.h"
#include "../../Cognition/FreqDoubleRelevanceNetWork/FreqDoubleNetwork.h"

#include "ui_FreqDoubChtPanelWgt.h"

class FreqDoubChtPanelWgt : public QWidget
{
	Q_OBJECT

public:
	FreqDoubChtPanelWgt(QWidget *parent = nullptr);
	~FreqDoubChtPanelWgt();

public:signals:
	void sgn_GoFreqDoubleResult(QString DataKey);
	void sgn_AskFreqDoubleTensorPara(ST_FreqMultipleTensorGenPara& GenPara);

public slots:
	void slot_getNewSTFTData(QString dataKey);
	void slot_AutoGenFreqDoubData(QString dataKey);

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
	void slot_GenFreqDoubDataBtnClicked();
	void slot_updateTimeSecChtBtnClicked();
	void slot_NoiseBtnGroupClicked();
	void slot_play();
	void slot_jump();
	void slot_stop();
	void slot_updateTimerTimeUp();
	void slot_getFreqDoubNetMsg(int percentage, int threadCount, QString msg);
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr);
	void slotFreqDoubResultGet(QString DataKey);
	void slot_btnNextFrameClicked();
	void slot_btnLastFrameClicked();
	void slot_TimeSecChtTypeChanged();

private:
	Ui::FreqDoubChtPanelWgtClass ui;

	QString					m_STFTDataKey;
	ST_STFTInputpara		m_dataPara;

	FFT_Chart_STFTHotGram*	m_pSTFTHotCht = nullptr;
	//TimeSecCht_FreqDoub*	m_pFreqDoubTimeSecCht = nullptr;

	QButtonGroup*			m_pBtnGroup_getFreqDoubData		= nullptr;
	QButtonGroup*			m_pBtnGroup_NoiseDrawSet = nullptr;

	QTimer*					m_pUpdateSectionTimer = nullptr;
	int						m_nUpdateMsec = 50;
	int						m_nCurrentTimeUpCount = 0;

	int						m_nStatFrameRateStartFrameIndex = -1;
	QTime					m_TimeFrameRateStatStartSysTime = QTime(0, 0, 0);

};
