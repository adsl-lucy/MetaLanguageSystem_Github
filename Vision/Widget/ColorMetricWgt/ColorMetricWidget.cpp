#include "ColorMetricWidget.h"
#pragma execution_character_set("utf-8")

ColorMetricWidget::ColorMetricWidget(QWidget *parent)
	: QWidget(parent)
{	
	ui.setupUi(this);
	initUI();
}

ColorMetricWidget::~ColorMetricWidget()
{}

void ColorMetricWidget::initUI()
{
	m_pLabCht = new Cht_LABColorDistribute(this);
	ui.HLayout_Cht_Lab->insertWidget(0, m_pLabCht);

	connect(m_pLabCht, &Cht_LABColorDistribute::sgn_CrRectGenState, this, &ColorMetricWidget::slot_getCrGenState);	
	connect(m_pLabCht, &Cht_LABColorDistribute::sgn_updateCurrentMousePosInfo, this, &ColorMetricWidget::slot_updateCurrentMousePosInfo);
	connect(m_pLabCht, &Cht_LABColorDistribute::sgn_updateMousePressedPosInfo, this, &ColorMetricWidget::slot_updatePressedMousePosInfo);
	connect(m_pLabCht, &Cht_LABColorDistribute::sgn_updateMousePosMetricInfo, this, &ColorMetricWidget::slot_updateCrMetricInfo);

	m_pBtnGroup_AxiFix = new QButtonGroup(this);
	m_pBtnGroup_AxiFix->addButton(ui.radioButton_Axi_Fix_L);
	m_pBtnGroup_AxiFix->addButton(ui.radioButton_Axi_Fix_R);
	m_pBtnGroup_AxiFix->setExclusive(true);
	connect(m_pBtnGroup_AxiFix, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int id) { slot_AxiSetBtnClicked(); });
	ui.radioButton_Axi_Fix_L->setChecked(true);

	m_pBtnGroup_CrRectType = new QButtonGroup(this);
	m_pBtnGroup_CrRectType->addButton(ui.radioButton_Axi_Interval_pixel);
	m_pBtnGroup_CrRectType->addButton(ui.radioButton_Axi_Interval_Density);
	m_pBtnGroup_CrRectType->setExclusive(true);
	connect(m_pBtnGroup_CrRectType, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int id) { slot_AxiSetBtnClicked(); });
	ui.radioButton_Axi_Interval_pixel->setChecked(true);

	m_pBtnGroup_ChtDrawingType = new QButtonGroup(this);
	m_pBtnGroup_ChtDrawingType->setExclusive(false);
	m_pBtnGroup_ChtDrawingType->addButton(ui.checkBox_drawAxis);
	m_pBtnGroup_ChtDrawingType->addButton(ui.checkBox_drawGrid);
	connect(m_pBtnGroup_ChtDrawingType, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int id) { slot_DrawingSettingBtnClicked(); });

	connect(ui.btn_updateChtOnly	, &QPushButton::clicked, this, &ColorMetricWidget::slot_updateChtBtnClicked);
	connect(ui.btn_GenLABDistribute	, &QPushButton::clicked, this, &ColorMetricWidget::slot_updateCrRectBtnClicked);

	slot_AxiSetBtnClicked();
	slot_updateChtBtnClicked();
	slot_DrawingSettingBtnClicked();

	m_pImgPainterWgt = new ImagePainterWgt(this);
	m_pImgPainterWgt->setImagePaintType(ImagePaintType::QImage);
	ui.HLayout_ImagePainter->insertWidget(0, m_pImgPainterWgt);
	ui.btn_transferImg->setEnabled(false);

	m_pBtnGroup_ImgPaintType = new QButtonGroup(this);
	m_pBtnGroup_ImgPaintType->addButton(ui.radioButton_CrMode_RGB);
	m_pBtnGroup_ImgPaintType->addButton(ui.radioButton_CrMode_LAB_L);
	m_pBtnGroup_ImgPaintType->setExclusive(true);
	connect(m_pBtnGroup_ImgPaintType, QOverload<int>::of(&QButtonGroup::buttonClicked),
		[=](int id) { slot_ImgPaintTypeBtnClicked(); });

	connect(DataCenterManager::instance(), &DataCenterManager::sgn_QImgDataSaved, this, &ColorMetricWidget::slot_getNewImgData);
	connect(ui.btn_LoadImg, &QPushButton::clicked, this, &ColorMetricWidget::slot_LoadImgBtnClicked);
	connect(ui.btn_transferImg, &QPushButton::clicked, this, &ColorMetricWidget::slot_transferImgBtnClicked);
	connect(ImageProcessor::instance(), &ImageProcessor::sgn_VisualImgTransferPercentage, this, &ColorMetricWidget::slot_VisualImgTransferPercentage);

}

void ColorMetricWidget::getCurrentAxiSetting(EN_LabCht_AxiType& AxiType, ST_LabCht_AxiPos& AxiStartPos, ST_LabCht_AxiPos& AxiEndPos,ST_LabCht_Density& gridDensity)
{
	if (ui.radioButton_Axi_Fix_L->isChecked())
	{
		AxiType = EN_LabCht_AxiType::Fix_L_Axi_Euclid;
	}
	else
	{
		AxiType = EN_LabCht_AxiType::Fix_AB_Axi_Euclid;
	}

	AxiStartPos.L		= ui.DSBox_PlaneStart_L->value();
	AxiStartPos.A		= ui.DSBox_PlaneStart_A->value();
	AxiStartPos.B		= ui.DSBox_PlaneStart_B->value();
	AxiStartPos.R		= ui.DSBox_PlaneStart_R->value();

	AxiEndPos.L			= ui.DSBox_PlaneEnd_L->value();
	AxiEndPos.A			= ui.DSBox_PlaneEnd_A->value();
	AxiEndPos.B			= ui.DSBox_PlaneEnd_B->value();
	AxiEndPos.R			= ui.DSBox_PlaneEnd_R->value();

	gridDensity.Radius	= ui.DSBox_Interval_Grid_Radius->value();
	gridDensity.L		= ui.DSBox_Interval_Grid_L->value();
	gridDensity.AB		= ui.DSBox_Interval_Grid_AB->value();

}

void ColorMetricWidget::getCrRectSetting(EN_LabCht_CrRectType& CrRectType, int& CrRectWidth, ST_LabCht_Density& CrDensity)
{
	if (ui.radioButton_Axi_Interval_pixel->isChecked())
	{
		CrRectType = EN_LabCht_CrRectType::Pixel;
	}
	else
	{
		CrRectType = EN_LabCht_CrRectType::Density;
	}

	CrRectWidth = ui.SBox_CrRectWidth->value();

	CrDensity.Radius	= ui.DSBox_Interval_Cr_Radius->value();
	CrDensity.L			= ui.DSBox_Interval_Cr_L->value();
	CrDensity.AB		= ui.DSBox_Interval_Cr_AB->value();
}

void ColorMetricWidget::updateGenResult()
{
	int CaculateRectCount = 0;
	int ValidRectCount = 0;
	m_pLabCht->getCaculateResult(CaculateRectCount, ValidRectCount);
	ui.label_CaculateRectCount->setText(QString("计算色块数量：%1").arg(CaculateRectCount));
	ui.label_ValidRectCount->setText(QString("有效色块数量：%1").arg(ValidRectCount));
}


void ColorMetricWidget::slot_updateChtBtnClicked()
{
	EN_LabCht_AxiType AxiType;
	ST_LabCht_AxiPos AxiStartPos, AxiEndPos;
	ST_LabCht_Density gridDensity;
	getCurrentAxiSetting(AxiType, AxiStartPos, AxiEndPos, gridDensity);
	m_pLabCht->setAxiSetting(AxiType, AxiStartPos, AxiEndPos, gridDensity);
}

void ColorMetricWidget::slot_updateCrRectBtnClicked()
{
	slot_updateChtBtnClicked();
	EN_LabCht_CrRectType CrRectType;
	int CrRectWidth;
	ST_LabCht_Density CrDensity;
	getCrRectSetting(CrRectType, CrRectWidth, CrDensity);
	bool GammaExist = ui.checkBox_GammaExist->isChecked();
	m_pLabCht->resetCrRect(CrRectType, GammaExist, CrRectWidth, CrDensity);
}

void ColorMetricWidget::slot_DrawingSettingBtnClicked()
{
	bool drawAxies	= ui.checkBox_drawAxis->isChecked();
	bool drawGrid	= ui.checkBox_drawGrid->isChecked();
	m_pLabCht->setDrawingSet(drawAxies, drawGrid);
}

void ColorMetricWidget::slot_getCrGenState(int percentage, int activateThreadCount, QString errstr)
{
	ui.progressBar_RectGenState->setValue(percentage);
	if (percentage != 100)
	{
		ui.label_CrGenState->setText(QString("活跃线程：%1 %2").arg(activateThreadCount).arg(errstr));
	}
	else
	{
		ui.label_CrGenState->setText(QString("生成结束"));
		updateGenResult();
	}
}

void ColorMetricWidget::slot_updateCurrentMousePosInfo(const ST_ChtLab_MousePosLabInfo& PosInfo)
{
	ui.label_MousePos_Current_Lab->setText(QString("LAB:"));
	ui.label_MousePos_Current_XYZ->setText(QString("XYZ:"));
	ui.label_MousePos_Current_sRgbGamma->setText(QString("sRgbGamma:"));
	ui.label_MousePos_Current_sRgb->setText(QString("sRgb:"));
	ui.label_MousePos_Current_Cr255->setText(QString("QColor:"));
	ui.label_MousePos_Current_CrPaint->setStyleSheet(QString("QLabel{background-color:rgba(0,0,0,0);}"));

	if (PosInfo.PosValid)
	{
		const ST_LABPoint& MouseLab = PosInfo.MouseLab;
		const ST_xyzPoint& MouseXYZ = PosInfo.MouseXYZ;
		const ST_sRgbPoint& MouseGammaSRgb = PosInfo.MouseGammaSRgb;
		const ST_sRgbPoint& MouseSRgb = PosInfo.MouseSRgb;
		const QColor& MouseCr = PosInfo.MouseCr;


		ui.label_MousePos_Current_Lab->setText(QString("LAB: L:%1 A:%2 B:%3").arg(MouseLab.L, 0, 'f', 1).arg(MouseLab.A, 0, 'f', 1).arg(MouseLab.B, 0, 'f', 1));
		ui.label_MousePos_Current_XYZ->setText(QString("XYZ: X:%1 Y:%2 Z:%3").arg(MouseXYZ.x, 0, 'f', 3).arg(MouseXYZ.y, 0, 'f', 3).arg(MouseXYZ.z, 0, 'f', 3));
		ui.label_MousePos_Current_sRgbGamma->setText(QString("sRgbGamma: r:%1 g:%2 b:%3").arg(MouseGammaSRgb.r, 0, 'f', 3).arg(MouseGammaSRgb.g, 0, 'f', 3).arg(MouseGammaSRgb.b, 0, 'f', 3));
		ui.label_MousePos_Current_sRgb->setText(QString("sRgb: L:%1 A:%2 B:%3").arg(MouseSRgb.r, 0, 'f', 3).arg(MouseSRgb.g, 0, 'f', 3).arg(MouseSRgb.b, 0, 'f', 3));
		if (PosInfo.SRgbValid)
		{
			ui.label_MousePos_Current_Cr255->setText(QString("QColor: R:%1 G:%2 B:%3").arg(MouseCr.red()).arg(MouseCr.green()).arg(MouseCr.blue()));
			ui.label_MousePos_Current_CrPaint->setStyleSheet(QString("QLabel{background-color:rgb(%1,%2,%3);}").arg(MouseCr.red()).arg(MouseCr.green()).arg(MouseCr.blue()));
		}
	}
}

void ColorMetricWidget::slot_updatePressedMousePosInfo(const ST_ChtLab_MousePosLabInfo& PosInfo)
{
	ui.label_MousePos_Press_Lab->setText(QString("LAB:"));
	ui.label_MousePos_Press_XYZ->setText(QString("XYZ:"));
	ui.label_MousePos_Press_sRgbGamma->setText(QString("sRgbGamma:"));
	ui.label_MousePos_Press_sRgb->setText(QString("sRgb:"));
	ui.label_MousePos_Press_Cr255->setText(QString("QColor:"));
	ui.label_MousePos_Press_CrPaint->setStyleSheet(QString("QLabel{background-color:rgba(0,0,0,0);}"));

	if (PosInfo.PosValid)
	{
		const ST_LABPoint& MouseLab = PosInfo.MouseLab;
		const ST_xyzPoint& MouseXYZ = PosInfo.MouseXYZ;
		const ST_sRgbPoint& MouseGammaSRgb = PosInfo.MouseGammaSRgb;
		const ST_sRgbPoint& MouseSRgb = PosInfo.MouseSRgb;
		const QColor& MouseCr = PosInfo.MouseCr;


		ui.label_MousePos_Press_Lab->setText(QString("LAB: L:%1 A:%2 B:%3").arg(MouseLab.L, 0, 'f', 1).arg(MouseLab.A, 0, 'f', 1).arg(MouseLab.B, 0, 'f', 1));
		ui.label_MousePos_Press_XYZ->setText(QString("XYZ: X:%1 Y:%2 Z:%3").arg(MouseXYZ.x, 0, 'f', 3).arg(MouseXYZ.y, 0, 'f', 3).arg(MouseXYZ.z, 0, 'f', 3));
		ui.label_MousePos_Press_sRgbGamma->setText(QString("sRgbGamma: r:%1 g:%2 b:%3").arg(MouseGammaSRgb.r, 0, 'f', 3).arg(MouseGammaSRgb.g, 0, 'f', 3).arg(MouseGammaSRgb.b, 0, 'f', 3));
		ui.label_MousePos_Press_sRgb->setText(QString("sRgb: L:%1 A:%2 B:%3").arg(MouseSRgb.r, 0, 'f', 3).arg(MouseSRgb.g, 0, 'f', 3).arg(MouseSRgb.b, 0, 'f', 3));
		if (PosInfo.SRgbValid)
		{
			ui.label_MousePos_Press_Cr255->setText(QString("QColor: R:%1 G:%2 B:%3").arg(MouseCr.red()).arg(MouseCr.green()).arg(MouseCr.blue()));
			ui.label_MousePos_Press_CrPaint->setStyleSheet(QString("QLabel{background-color:rgb(%1,%2,%3);}").arg(MouseCr.red()).arg(MouseCr.green()).arg(MouseCr.blue()));
		}
	}
}

void ColorMetricWidget::slot_updateCrMetricInfo(const bool PosValid, const double RGBDis, const double LAB_1976, const double LAB_1984, const double LAB_1994, const double LAB_2000)
{
	ui.label_CrMetric_RGB_255->setText( QString("RGB_255  :"));
	ui.label_CrMetric_LAB_1976->setText(QString("LAB_1976 :"));
	ui.label_CrMetric_LAB_1984->setText(QString("LAB_1984 :"));
	ui.label_CrMetric_LAB_1994->setText(QString("LAB_1994 :"));
	ui.label_CrMetric_LAB_2000->setText(QString("LAB_2000 :"));
	if (PosValid)
	{
		ui.label_CrMetric_RGB_255->setText( QString("RGB_255  :%1").arg(RGBDis));
		ui.label_CrMetric_LAB_1976->setText(QString("LAB_1976 :%1").arg(LAB_1976));
		ui.label_CrMetric_LAB_1984->setText(QString("LAB_1984 :%1").arg(LAB_1984));
		ui.label_CrMetric_LAB_1994->setText(QString("LAB_1994 :%1").arg(LAB_1994));
		ui.label_CrMetric_LAB_2000->setText(QString("LAB_2000 :%1").arg(LAB_2000));
	}
}

void ColorMetricWidget::slot_AutoLoadImg(QString Key)
{
	ui.tabWidget_main->setCurrentIndex(1);
	LoadImg(Key);
}

void ColorMetricWidget::slot_getNewImgData(QString Key)
{
	ui.comboBox_selImg->addItem(Key);
}

void ColorMetricWidget::slot_LoadImgBtnClicked()
{
	QString Key = ui.comboBox_selImg->currentText();
	LoadImg(Key);
}


void ColorMetricWidget::LoadImg(QString Key)
{
	ui.btn_transferImg->setEnabled(false);
	bool DataExist = DataCenterManager::instance()->checkImageExist(EN_DataCenterVisualDataType::QImage, Key);
	if (!DataExist)
	{
		return;
	}

	m_tempImg = DataCenterManager::instance()->getQImageMap().find(Key).value();

	QSize imageSize = m_tempImg.size();
	QString ImageSzStr = QString("%1 X %2").arg(imageSize.width()).arg(imageSize.height());
	QString formatStr = ImageProcessor::instance()->getImageFormatStr(m_tempImg.format());

	ui.label_Img_FileName->setText(QString("文件名：%1").arg(Key));
	ui.label_img_Size->setText(QString("图像尺寸：%1").arg(ImageSzStr));
	ui.label_Img_CrDepth->setText(QString("颜色深度：%1").arg(m_tempImg.depth()));
	ui.label_Img_CrFormat->setText(QString("颜色格式：%1").arg(formatStr));

	m_pImgPainterWgt->setQImg(m_tempImg);
	m_pImgPainterWgt->setImagePaintType(ImagePaintType::QImage);

	if (ui.checkBox_autoLabTransfer->isChecked())
	{
		slot_transferImgBtnClicked();
	}
	else
	{
		ui.btn_transferImg->setEnabled(true);
	}
	
}

void ColorMetricWidget::slot_transferImgBtnClicked()
{
	ImageProcessor::instance()->transferImageData(m_tempImg, m_visualImg);
	m_pImgPainterWgt->setVisualImg(m_visualImg);
	ImagePaintType paintType = getCurrentImgPaintType();
	m_pImgPainterWgt->setImagePaintType(paintType);
}

void ColorMetricWidget::slot_VisualImgTransferPercentage(int val, QString msg)
{
	ui.progressBar_transferState->setValue(val);
	ui.label_transferState->setText(QString("转换状态:%1").arg(msg));
}


ImagePaintType ColorMetricWidget::getCurrentImgPaintType()
{
	if (ui.radioButton_CrMode_RGB->isChecked())
	{
		return ImagePaintType::VisualImage_Origin;
	}
	else
	{
		return ImagePaintType::VisualImage_LAB_L;
	}
}

void ColorMetricWidget::slot_ImgPaintTypeBtnClicked()
{
	ImagePaintType paintType = getCurrentImgPaintType();
	m_pImgPainterWgt->setImagePaintType(paintType);
}

void ColorMetricWidget::slot_AxiSetBtnClicked()
{
	EN_LabCht_AxiType ChtAxiType;
	if (ui.radioButton_Axi_Fix_L->isChecked())
	{
		ChtAxiType = EN_LabCht_AxiType::Fix_L_Axi_Euclid;
	}
	else
	{
		ChtAxiType = EN_LabCht_AxiType::Fix_AB_Axi_Euclid;
	}

	EN_LabCht_CrRectType RectType;
	if (ui.radioButton_Axi_Interval_pixel->isChecked())
	{
		RectType = EN_LabCht_CrRectType::Pixel;
	}
	else
	{
		RectType = EN_LabCht_CrRectType::Density;
	}

	ui.DSBox_PlaneStart_L->setEnabled(false);
	ui.DSBox_PlaneStart_A->setEnabled(false);
	ui.DSBox_PlaneStart_B->setEnabled(false);
	ui.DSBox_PlaneStart_R->setEnabled(false);
	ui.DSBox_PlaneEnd_L->setEnabled(false);
	ui.DSBox_PlaneEnd_A->setEnabled(false);
	ui.DSBox_PlaneEnd_B->setEnabled(false);
	ui.DSBox_PlaneEnd_R->setEnabled(false);
	ui.DSBox_Interval_Cr_Radius->setEnabled(false);
	ui.DSBox_Interval_Cr_L->setEnabled(false);
	ui.DSBox_Interval_Cr_AB->setEnabled(false);
	ui.DSBox_Interval_Grid_Radius->setEnabled(false);
	ui.DSBox_Interval_Grid_L->setEnabled(false);
	ui.DSBox_Interval_Grid_AB->setEnabled(false);

	switch (ChtAxiType)
	{
		case EN_LabCht_AxiType::Fix_L_Axi_Euclid:
		{
			ui.DSBox_PlaneStart_L->setEnabled(true);
			ui.DSBox_PlaneStart_A->setEnabled(true);
			ui.DSBox_PlaneStart_B->setEnabled(true);
			ui.DSBox_PlaneEnd_A->setEnabled(true);
			ui.DSBox_PlaneEnd_B->setEnabled(true);

			if (RectType == EN_LabCht_CrRectType::Density)
			{
				ui.DSBox_Interval_Cr_AB->setEnabled(true);
			}
		
			ui.DSBox_Interval_Grid_AB->setEnabled(true);
		}break;
		case EN_LabCht_AxiType::Fix_AB_Axi_Euclid:
		{
			ui.DSBox_PlaneStart_L->setEnabled(true);
			ui.DSBox_PlaneStart_A->setEnabled(true);
			ui.DSBox_PlaneStart_B->setEnabled(true);
			ui.DSBox_PlaneStart_R->setEnabled(true);
			ui.DSBox_PlaneEnd_L->setEnabled(true);
			ui.DSBox_PlaneEnd_R->setEnabled(true);

			if (RectType == EN_LabCht_CrRectType::Density)
			{
				ui.DSBox_Interval_Cr_L->setEnabled(true);
				ui.DSBox_Interval_Cr_Radius->setEnabled(true);
			}

			ui.DSBox_Interval_Grid_L->setEnabled(true);
			ui.DSBox_Interval_Grid_Radius->setEnabled(true);
		}break;
	}


}
