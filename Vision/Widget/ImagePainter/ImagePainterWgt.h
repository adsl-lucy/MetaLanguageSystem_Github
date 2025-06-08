#pragma once
#include <QWidget>
#include <QImage>
#include <QPainter>

#include "../../Perception/ImageProcessor/ImageProcessor.h"
#include "../../protocol/protocol_vision.h"

enum class ImagePaintType :int
{
	QImage,
	VisualImage_Origin,
	VisualImage_LAB_L
};

class ImagePainterWgt : public QWidget
{
	Q_OBJECT

public:
	ImagePainterWgt(QWidget* parent = nullptr);
	~ImagePainterWgt();

	void setImagePaintType(ImagePaintType type);
	void setQImg(const QImage& source);
	void setVisualImg(const ST_VisualImage& source);

protected:
	QRect getImageArea(QSize imageSize, QRect drawArea);
	void paintEvent(QPaintEvent* event);

private:
	ImagePaintType m_paintType = ImagePaintType::QImage;
	QImage		   m_paintImg;
	ST_VisualImage m_visualImg;
};

