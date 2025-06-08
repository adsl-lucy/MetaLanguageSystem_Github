#pragma once

#include <QWidget>
#include <QButtonGroup>

#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "./Cht_LABColorDistribute.h"
#include "../ImagePainter/ImagePainterWgt.h"
#include "../../Perception/ImageProcessor/ImageProcessor.h"

#include "./ui_ColorMetricWidget.h"

class ColorMetricWidget : public QWidget
{
	Q_OBJECT

public:
	ColorMetricWidget(QWidget *parent = nullptr);
	~ColorMetricWidget();

public slots:
	void slot_AutoLoadImg(QString Key);

protected:
	void initUI();

	void getCurrentAxiSetting(EN_LabCht_AxiType& AxiType, ST_LabCht_AxiPos& AxiStartPos, ST_LabCht_AxiPos& AxiEndPos, ST_LabCht_Density& gridDensity);
	void getCrRectSetting(EN_LabCht_CrRectType& CrRectType, int& CrRectWidth, ST_LabCht_Density& CrDensity);
	void updateGenResult();
	void LoadImg(QString Key);

	ImagePaintType getCurrentImgPaintType();

protected slots:
	void slot_AxiSetBtnClicked();
	void slot_updateChtBtnClicked();
	void slot_updateCrRectBtnClicked();
	void slot_DrawingSettingBtnClicked();
	void slot_getCrGenState(int percentage, int activateThreadCount, QString errstr);
	void slot_updateCurrentMousePosInfo(const ST_ChtLab_MousePosLabInfo& PosInfo);
	void slot_updatePressedMousePosInfo(const ST_ChtLab_MousePosLabInfo& PosInfo);
	void slot_updateCrMetricInfo(const bool PosValid, const double RGBDis, const double LAB_1976, const double LAB_1984, const double LAB_1994, const double LAB_2000);

	void slot_getNewImgData(QString Key);
	void slot_LoadImgBtnClicked();
	void slot_transferImgBtnClicked();
	void slot_VisualImgTransferPercentage(int val, QString msg);
	void slot_ImgPaintTypeBtnClicked();

private:
	Ui::ColorMetricWidgetClass ui;

	Cht_LABColorDistribute* m_pLabCht = nullptr;

	QButtonGroup* m_pBtnGroup_AxiFix			= nullptr;
	QButtonGroup* m_pBtnGroup_CrRectType		= nullptr;
	QButtonGroup* m_pBtnGroup_ChtDrawingType	= nullptr;

	QButtonGroup*	m_pBtnGroup_ImgPaintType = nullptr;
	QImage			 m_tempImg;
	ST_VisualImage	 m_visualImg;
	ImagePainterWgt* m_pImgPainterWgt = nullptr;

};
