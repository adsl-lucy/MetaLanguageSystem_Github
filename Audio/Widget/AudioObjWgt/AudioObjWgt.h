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
//#include "./TimeSecCht_AudioObj.h"
#include "./ui_AudioObjWgt.h"

class AudioObjWgt : public QWidget
{
	Q_OBJECT

public:
	AudioObjWgt(QWidget *parent = nullptr);
	~AudioObjWgt();

private:
	Ui::AudioObjWgtClass ui;

public:signals:
	//void sgn_GoFreqDoubleResult(QString DataKey);

public slots:
	void slot_getNewSTFTData(QString dataKey);
	void slot_AutoGenAudioObjInputData(QString dataKey);

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
	void slot_GenAudioObjDataBtnClicked();
	void slot_updateTimeSecChtBtnClicked();
	void slot_play();
	void slot_jump();
	void slot_stop();
	void slot_updateTimerTimeUp();
	void slot_getAudioObjectMsg(int percentage, int threadCount, QString msg);
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_AudioObjecResultGet(QString DataKey);
	void slot_btnNextFrameClicked();
	void slot_btnLastFrameClicked();
	void slot_TimeSecChtTypeChanged();

private:

	QString m_STFTDataKey;
	ST_STFTInputpara	m_dataPara;

	FFT_Chart_STFTHotGram*	m_pSTFTHotCht = nullptr;
	//TimeSecCht_AudioObj*	m_pAuObjTimeSecCht = nullptr;

	QButtonGroup* m_pBtnGroup_getDiffData = nullptr;
	QButtonGroup* m_pBtnGroup_TimeSecChtShowType = nullptr;

	QTimer* m_pUpdateSectionTimer = nullptr;
	int			m_nUpdateMsec = 50;
	int			m_nCurrentTimeUpCount = 0;

	int			m_nStatFrameRateStartFrameIndex = -1;
	QTime		m_TimeFrameRateStatStartSysTime = QTime(0, 0, 0);

};
