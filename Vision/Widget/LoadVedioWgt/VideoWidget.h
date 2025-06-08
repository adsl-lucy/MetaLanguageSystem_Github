#pragma once

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include "./ui_VideoWidget.h"
#include "../VideoFrameWgt/VideoFrameWidget.h"

#include "../../../ThirdParty/FFMpegManager/FFMpegManager.h"

class VideoWidget : public QWidget
{
	Q_OBJECT

public:
	VideoWidget(QWidget *parent = nullptr);
	~VideoWidget();

	void printVideoTagInfo(const ST_VideoFileTag& fileTag, const ST_VideoLoadSetting& loadSetting);
	void loadVideoFrame(const ST_VideoFileTag& fileTag,const ST_VideoLoadSetting& loadSetting);

public:signals:
	void sgn_playVideo();
	void sgn_stopVideo();

protected:
	void initUI();
	void initUpdateTimer();
	void initFrameWidget();
	void printCurrentFrameInfo(int index);

	void slot_play();
	void slot_pause();
	void slot_stop();
	void slot_nextFrame();
	void slot_nextIFrame();
	void slot_UpdateTimerTimeout();
	void slot_btnExtraWindowClicked();
	void slot_FrameWindowHide();

protected slots:
	void slot_FrameIndexSliderMoved(int index);

private:
	Ui::VideoWidgetClass ui;

	VideoFrameWidget* m_pVideoFrameWidget = nullptr;

	ST_VideoFileTag m_currentFileTag;
	ST_VideoLoadSetting m_VideoLoadSetting;
	QTimer* m_pUpdateFrameTimer = nullptr;
	int m_nCurrentFrame = -1;
	int m_nUpdateMsec = -1;

	VideoFrameWidget* m_pExtraFrameWindow = nullptr;

	bool			m_bLoadFrameOnWindow = false;
};
