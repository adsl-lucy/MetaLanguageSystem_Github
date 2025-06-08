#pragma once

#pragma once

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QButtonGroup>

#include "../../protocol/protocol_audio.h"
#include "../STFTWgt/STFTAnalyse/STFTCht/FFT_Chart_STFTHotGram.h"
#include "../../Perception/AudioEngine/AudioEngine.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "../TimeSecCht/TimeSecCht_Wgt.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../Cognition/VibrateStateRelvanceNetwork/VibrateStateRelvanceNetwork.h"
#include "./ui_EffSigBuffWgt.h"

class EffSigBuffWgt : public QWidget
{
	Q_OBJECT

public:
	EffSigBuffWgt(QWidget *parent = nullptr);
	~EffSigBuffWgt();

private:
	Ui::EffSigBuffWgtClass ui;

public slots:
	void slot_getNewSTFTData(QString dataKey);
	void slot_AutoGenEffSigBuffData(QString dataKey);

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
	void slot_GenVibStateRelBtnClicked();
	void slot_updateTimeSecChtBtnClicked();
	void slot_play();
	void slot_jump();
	void slot_stop();
	void slot_updateTimerTimeUp();
	void slot_getVibStateGenMsg(int percentage, int threadCount, QString msg);
	void slot_updateHotChtGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateTimeSecGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_TimeSecGenFinished();
	void slot_EffSigBuffResultGet(QString DataKey);
	void slot_btnNextFrameClicked();
	void slot_btnLastFrameClicked();
	void slot_TimeSecChtTypeChanged();

	void slot_PaintSettingBtnClicked();

private:

	QString m_STFTDataKey;
	ST_STFTInputpara	m_dataPara;

	FFT_Chart_STFTHotGram* m_pSTFTHotCht = nullptr;
	TimeSecCht_Wgt* m_pTimeSecCht = nullptr;

	QButtonGroup* m_pBtnGroup_getEffSigBuffData = nullptr;
	QButtonGroup* m_pBtnGroup_TimeSecCht_PaintSetting = nullptr;
	QButtonGroup* m_pBtnGroup_TimeSecCht_VibStatePaintSetting = nullptr;

	QTimer*		m_pUpdateSectionTimer = nullptr;
	int			m_nUpdateMsec = 50;
	int			m_nCurrentTimeUpCount = 0;

	int			m_nStatFrameRateStartFrameIndex = -1;
	QTime		m_TimeFrameRateStatStartSysTime = QTime(0, 0, 0);


};
