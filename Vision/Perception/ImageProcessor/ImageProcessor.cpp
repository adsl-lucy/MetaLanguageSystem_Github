#include "ImageProcessor.h"
#pragma execution_character_set("utf-8")

ImageProcessor* ImageProcessor::m_instance = nullptr;

ImageProcessor::ImageProcessor()
{

}

ImageProcessor* ImageProcessor::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ImageProcessor();
	}
	return m_instance;
}

QString ImageProcessor::getImageFormatStr(QImage::Format format)
{
	switch (format)
	{
		case QImage::Format_Invalid					:return QString("Invalid");
		case QImage::Format_Mono					:return QString("Mono");
		case QImage::Format_MonoLSB					:return QString("MonoLSB");
		case QImage::Format_Indexed8				:return QString("Indexed8");
		case QImage::Format_RGB32					:return QString("RGB32");
		case QImage::Format_ARGB32					:return QString("ARGB32");
		case QImage::Format_ARGB32_Premultiplied	:return QString("ARGB32_Premultiplied");
		case QImage::Format_RGB16					:return QString("RGB16");
		case QImage::Format_ARGB8565_Premultiplied	:return QString("ARGB8565_Premultiplied");
		case QImage::Format_RGB666					:return QString("RGB666");
		case QImage::Format_ARGB6666_Premultiplied	:return QString("ARGB6666_Premultiplied");
		case QImage::Format_RGB555					:return QString("RGB555");
		case QImage::Format_ARGB8555_Premultiplied	:return QString("ARGB8555_Premultiplied");
		case QImage::Format_RGB888					:return QString("RGB888");
		case QImage::Format_RGB444					:return QString("RGB444");
		case QImage::Format_ARGB4444_Premultiplied	:return QString("ARGB4444_Premultiplied");
		case QImage::Format_RGBX8888				:return QString("RGBX8888");
		case QImage::Format_RGBA8888				:return QString("RGBA8888");
		case QImage::Format_RGBA8888_Premultiplied	:return QString("RGBA8888_Premultiplied");
		case QImage::Format_BGR30					:return QString("BGR30");
		case QImage::Format_A2BGR30_Premultiplied	:return QString("A2BGR30_Premultiplied");
		case QImage::Format_RGB30					:return QString("RGB30");
		case QImage::Format_A2RGB30_Premultiplied	:return QString("A2RGB30_Premultiplied");
		case QImage::Format_Alpha8					:return QString("Alpha8");
		case QImage::Format_Grayscale8				:return QString("Grayscale8");
		case QImage::Format_RGBX64					:return QString("RGBX64");
		case QImage::Format_RGBA64					:return QString("RGBA64");
		case QImage::Format_RGBA64_Premultiplied	:return QString("RGBA64_Premultiplied");
	}
	return QString("");
}

void ImageProcessor::transferImageData(const QImage& data, ST_VisualImage& VisualImg)
{
	VisualImg.pixelVec.clear();
		
	int LineCount	= data.size().height();
	int RowCount	= data.size().width();

	ST_VisualPixel nullPixel;

	QVector<ST_VisualPixel> NullLine(RowCount, nullPixel);

	VisualImg.ImageSize		= QSize(RowCount, LineCount);
	VisualImg.pixelVec		= QVector<QVector<ST_VisualPixel>>(LineCount, NullLine);
	VisualImg.Img_Origin	= data;
	VisualImg.Img_Lab_L		= QImage(QSize(RowCount, LineCount), QImage::Format_ARGB32);
	VisualImg.Img_Lab_L.fill(QColor(0, 0, 0,0));

	int hunderdOfLine = qMax(1,LineCount / 100);

	for (int LineIndex = 0; LineIndex < LineCount; LineIndex++)
	{
		for (int RowIndex = 0; RowIndex < RowCount; RowIndex++)
		{
			ST_VisualPixel& NewPixel = VisualImg.pixelVec[LineIndex][RowIndex];
			NewPixel.OriginCr = data.pixelColor(QPoint(RowIndex, LineIndex));
			ColorMetrics::instance()->QRgbToLabD65(NewPixel.OriginCr, NewPixel.LabVal,true);

			int Lab_L_To_255 = (double)NewPixel.LabVal.L / 100.0 * 255.0;
			QColor Lab_LCr(Lab_L_To_255, Lab_L_To_255, Lab_L_To_255);

			VisualImg.Img_Lab_L.setPixelColor(QPoint(RowIndex, LineIndex), Lab_LCr);
		}
		if (LineIndex % hunderdOfLine == 0)
		{
			emit sgn_VisualImgTransferPercentage(LineIndex / hunderdOfLine, QString("%1 / %2").arg(LineIndex).arg(LineCount));
		}
	}
	emit sgn_VisualImgTransferPercentage(100,QString(""));
}

void ImageProcessor::duplicateVisualImage(const ST_VisualImage& source, ST_VisualImage& target)
{
	target.fileName		= source.fileName;
	target.ImageSize	= source.ImageSize;
	target.Img_Origin	= source.Img_Origin;
	target.Img_Lab_L	= source.Img_Lab_L;

	int LineCount	= source.ImageSize.height();
	int RowCount	= source.ImageSize.width();

	ST_VisualPixel nullPixel;

	QVector<ST_VisualPixel> NullLine(RowCount, nullPixel);
	target.pixelVec.clear();
	target.pixelVec = QVector<QVector<ST_VisualPixel>>(LineCount, NullLine);

	for (int LineIndex = 0; LineIndex < LineCount; LineIndex++)
	{
		for (int RowIndex = 0; RowIndex < RowCount; RowIndex++)
		{
			target.pixelVec[LineIndex][RowIndex] = source.pixelVec[LineIndex][RowIndex];
		}
	}
}
