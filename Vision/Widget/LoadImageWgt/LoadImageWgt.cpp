#include "LoadImageWgt.h"
#pragma execution_character_set("utf-8")

LoadImageWgt::LoadImageWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUi();
}

LoadImageWgt::~LoadImageWgt()
{}

void LoadImageWgt::initUi()
{
	connect(ui.btn_selLoadImg	,&QPushButton::clicked, this, &LoadImageWgt::slot_selFileBtnClicked);
	connect(ui.btn_shrinkImg	,&QPushButton::clicked, this, &LoadImageWgt::slot_shrinkImgBtnClicked);
	connect(ui.btn_saveImgToDataCenter, &QPushButton::clicked, this, &LoadImageWgt::slot_saveImgToDataCenterBtnClicked);

	m_pImgPainterWgt = new ImagePainterWgt(this);
	m_pImgPainterWgt->setImagePaintType(ImagePaintType::QImage);
	ui.HLayout_ImagePainter->insertWidget(0, m_pImgPainterWgt);
}

void LoadImageWgt::resetFileTagLabel()
{
	ui.label_Img_FileName->setText(QString("文件名："));
	ui.label_file_Path->setText(QString("文件路径："));
	ui.label_Img_FileType->setText(QString("文件类型："));
	ui.label_img_LoadState->setText(QString("加载状态："));
	ui.label_img_Size->setText(QString("图像尺寸："));
}

void LoadImageWgt::selAndLoadImg(QString OpenFileDir)
{
	QFileInfo			fileInfo(OpenFileDir);
	QString				fileNameStr		= fileInfo.baseName();
	QString				fileDirStr		= fileInfo.path();
	QString				Suffix			= fileInfo.suffix();

	ui.label_Img_FileName->setText(QString("文件名：%1").arg(fileNameStr));
	ui.label_file_Path->setText(QString("文件路径：%1").arg(fileDirStr));
	ui.label_Img_FileType->setText(QString("文件类型：%1").arg(Suffix));
	
	QImageReader ImgReader(OpenFileDir);
	bool canRead = ImgReader.canRead();
	if (!canRead)
	{
		ui.label_img_LoadState->setText(QString("加载状态：%1").arg(VisionProtocol::boolToStr(canRead)));
		return;
	}

	m_LoadImg = ImgReader.read();
	QImage::Format imgFormat = m_LoadImg.format();
	bool LoadState = imgFormat != QImage::Format_Invalid;
	
	if (!LoadState)
	{
		ui.label_img_LoadState->setText(QString("加载状态：%1").arg(VisionProtocol::boolToStr(canRead)));
		return;
	}

	ui.label_img_LoadState->setText(QString("加载状态：%1").arg(VisionProtocol::boolToStr(canRead)));	
	ui.btn_shrinkImg->setEnabled(true);
	ui.btn_saveImgToDataCenter->setEnabled(true);
	QSize imageSize = m_LoadImg.size();
	QString ImageSzStr = QString("%1 X %2").arg(imageSize.width()).arg(imageSize.height());

	ui.label_img_Size->setText(QString("图像尺寸：%1").arg(ImageSzStr));
	ui.label_Img_CrDepth->setText(QString("颜色深度：%1").arg(m_LoadImg.depth()));

	QString formatStr = ImageProcessor::instance()->getImageFormatStr(m_LoadImg.format());

	ui.label_Img_CrFormat->setText(QString("颜色格式：%1").arg(formatStr));

	m_LoadImgName = fileNameStr;
	ui.SBox_LoadPicWidth->setMaximum(imageSize.width());
	ui.SBox_LoadPicHeight->setMaximum(imageSize.height());

	m_pImgPainterWgt->setQImg(m_LoadImg);

}

void LoadImageWgt::slot_selFileBtnClicked()
{
	resetFileTagLabel();
	ui.btn_shrinkImg->setEnabled(false);
	ui.btn_saveImgToDataCenter->setEnabled(false);

	QString loadDir = QApplication::applicationDirPath() + QString("/TestImage");
	QString OpenFileDir = QFileDialog::getOpenFileName(this, tr("Open file"), loadDir, tr("Vedio Files (*.jpg)"));
	if (OpenFileDir.isEmpty())
	{
		return;
	}
	selAndLoadImg(OpenFileDir);
	if (ui.checkBox_autoShrink->isChecked())
	{
		ui.btn_shrinkImg->setEnabled(false);
		slot_shrinkImgBtnClicked();
	}
}

void LoadImageWgt::slot_shrinkImgBtnClicked()
{
	int LoadWidth = ui.SBox_LoadPicWidth->value();
	int LoadHeight = ui.SBox_LoadPicHeight->value();
	QImage shrinKImage = m_LoadImg.scaled(QSize(LoadWidth, LoadHeight), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	m_LoadImg = shrinKImage;
	m_pImgPainterWgt->setQImg(m_LoadImg);
	if (ui.checkBox_autoSaveDataCenter->isChecked())
	{
		slot_saveImgToDataCenterBtnClicked();
		ui.btn_saveImgToDataCenter->setEnabled(false);
	}
}

void LoadImageWgt::slot_saveImgToDataCenterBtnClicked()
{
	bool saveState = false;
	DataCenterManager::instance()->slot_saveQImg(m_LoadImgName, m_LoadImg, saveState);

	if (ui.checkBox_CrMetric->isChecked())
	{
		emit sgn_CrMetricWgtAutoLoadPicture(m_LoadImgName);
	}

}
