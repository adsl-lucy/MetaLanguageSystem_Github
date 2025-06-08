#pragma once

#include <QWidget>
#include <QFileDialog>
#include <QImageReader>
#include "../../Perception/ImageProcessor/ImageProcessor.h"
#include "../../protocol/protocol_vision.h"
#include "../ImagePainter/ImagePainterWgt.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

#include "./ui_LoadImageWgt.h"

class LoadImageWgt : public QWidget
{
	Q_OBJECT

public:
	LoadImageWgt(QWidget *parent = nullptr);
	~LoadImageWgt();

public:signals:
	void sgn_CrMetricWgtAutoLoadPicture(QString Key);

protected:
	void initUi();
	void resetFileTagLabel();
	void selAndLoadImg(QString fileDir);

protected slots:
	void slot_selFileBtnClicked();
	void slot_shrinkImgBtnClicked();
	void slot_saveImgToDataCenterBtnClicked();

private:
	Ui::LoadImageWgtClass ui;
	QString     m_LoadImgName;
	QImage		m_LoadImg;	
	ImagePainterWgt*	m_pImgPainterWgt = nullptr;
};
