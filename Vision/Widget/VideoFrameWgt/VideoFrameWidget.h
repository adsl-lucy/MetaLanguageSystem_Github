#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QHideEvent>

#include "../../protocol/protocol_vision.h"

class VideoFrameWidget : public QWidget
{
	Q_OBJECT
public:
	VideoFrameWidget(QWidget* parent);
	~VideoFrameWidget();

	void setVideoFrameTag(ST_VideoFileTag tag, ST_VideoLoadSetting m_videoLoadSetting);
	void loadFrame(int index);

public:signals:
	void sgn_windowHide();

protected:
	QRect getImageArea(QSize imageSize, QRect drawArea);
	void paintEvent(QPaintEvent* event);
	void hideEvent(QHideEvent* event);

private:
	ST_VideoFileTag m_videoFileTag;
	ST_VideoLoadSetting m_videoLoadSetting;
	int m_nCurrentFrame = -1;

};

