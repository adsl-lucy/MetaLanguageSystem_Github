#include "VideoFrameWidget.h"
#include "../../../ThirdParty/FFMpegManager/FFMpegManager.h"

VideoFrameWidget::VideoFrameWidget(QWidget* parent)
{

}

VideoFrameWidget::~VideoFrameWidget()
{

}

void VideoFrameWidget::setVideoFrameTag(ST_VideoFileTag tag, ST_VideoLoadSetting LoadSetting)
{
	m_videoFileTag = tag;
	m_videoLoadSetting = LoadSetting;
}

void VideoFrameWidget::loadFrame(int index)
{
	m_nCurrentFrame = index;
	update();
}

QRect VideoFrameWidget::getImageArea(QSize imageSize, QRect drawArea)
{

	int imageWidth		= imageSize.width();
	int imageHeight		= imageSize.height();
	int drawWidth		= drawArea.width();
	int drawHeight		= drawArea.height();

	double WidthShrinkRatio  =  (double)drawWidth / (double)imageWidth;
	double HeightShrinkRatio =  (double)drawHeight / (double)imageHeight;

	QRect resultRect;
	int resultWidth = 0;
	int resultHeight = 0;

	if (imageWidth <= drawWidth && imageHeight <= drawHeight)
	{
		resultWidth = imageWidth;
		resultHeight = imageHeight;
	}
	else if (WidthShrinkRatio < HeightShrinkRatio)
	{
		resultWidth = drawWidth;
		resultHeight = imageHeight * WidthShrinkRatio;
	}
	else
	{
		resultWidth = imageWidth * HeightShrinkRatio;
		resultHeight = drawHeight;
	}

	resultRect.setWidth(resultWidth);
	resultRect.setHeight(resultHeight);
	resultRect.moveCenter(drawArea.center());

	return resultRect;
}

void VideoFrameWidget::hideEvent(QHideEvent* event)
{
	qDebug() << QString("VideoFrameWidget::hideEvent");
	emit sgn_windowHide();
}

void VideoFrameWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.setPen(Qt::NoPen);

	QRect thisRect = this->rect();

	painter.drawRect(thisRect);

	if (m_nCurrentFrame < 0 || m_nCurrentFrame >= m_videoLoadSetting.LoadFrameCount)
	{
		return;
	}

	ST_VideoH264Frame& FrameRef = FFMpegManager::instance()->getTempVideoDataVecRef()[m_nCurrentFrame];

	QImage& frameImage = FrameRef.Frame;

	QRect imageRect = QRect(QPoint(0, 0), QSize(FrameRef.FrameTag.width, FrameRef.FrameTag.height));

	QRect shrinkRect = getImageArea(m_videoLoadSetting.loadFrameSize, thisRect);
	painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
	painter.drawImage(shrinkRect, frameImage);

}