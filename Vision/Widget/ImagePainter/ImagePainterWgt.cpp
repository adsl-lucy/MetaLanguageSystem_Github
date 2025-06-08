#include "ImagePainterWgt.h"

ImagePainterWgt::ImagePainterWgt(QWidget* parent) :QWidget(parent)
{
};

ImagePainterWgt::~ImagePainterWgt()
{

}

void ImagePainterWgt::setImagePaintType(ImagePaintType type)
{
	m_paintType = type;
	update();
}

void ImagePainterWgt::setQImg(const QImage& source)
{
	m_paintImg = source;
	update();
}

void ImagePainterWgt::setVisualImg(const ST_VisualImage& source)
{
	ImageProcessor::duplicateVisualImage(source, m_visualImg);
	update();
}

QRect ImagePainterWgt::getImageArea(QSize imageSize, QRect drawArea)
{

	int imageWidth = imageSize.width();
	int imageHeight = imageSize.height();
	int drawWidth = drawArea.width();
	int drawHeight = drawArea.height();

	double WidthShrinkRatio = (double)drawWidth / (double)imageWidth;
	double HeightShrinkRatio = (double)drawHeight / (double)imageHeight;

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

void ImagePainterWgt::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.setPen(Qt::NoPen);

	QRect thisRect = this->rect();

	painter.drawRect(thisRect);

	QImage paintImage;

	switch (m_paintType)
	{
		case ImagePaintType::QImage				:paintImage = m_paintImg; break;
		case ImagePaintType::VisualImage_Origin	:paintImage = m_visualImg.Img_Origin; break;
		case ImagePaintType::VisualImage_LAB_L	:paintImage = m_visualImg.Img_Lab_L; break;
	}
	
	QSize ImgSize = paintImage.size();
	QRect imageRect = QRect(QPoint(0, 0), ImgSize);
	QRect shrinkRect = getImageArea(ImgSize, thisRect);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.drawImage(shrinkRect, paintImage);

}