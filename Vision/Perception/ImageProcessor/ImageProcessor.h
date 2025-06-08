#pragma once
#include <QObject>

#include "../../protocol/protocol_vision.h"
#include "../ColorMetrics/ColorMetrics.h"

class ImageProcessor : public QObject
{
	Q_OBJECT
public:
	static ImageProcessor* instance();
protected:
	ImageProcessor();
	static ImageProcessor* m_instance;

public:
	QString getImageFormatStr(QImage::Format format);
	void transferImageData(const QImage& data, ST_VisualImage& VisualImg);
	static void duplicateVisualImage(const ST_VisualImage& source, ST_VisualImage& target);

public:signals:
	void sgn_VisualImgTransferPercentage(int val, QString msg);

};

