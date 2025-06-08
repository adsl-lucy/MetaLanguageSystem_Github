#pragma once

#include <QWidget>

#include "./ui_VisionMainWgt.h"

#include "../LoadVedioWgt/LoadVedioWgt.h"
#include "../LoadImageWgt/LoadImageWgt.h"
#include "../ColorMetricWgt/ColorMetricWidget.h"

class VisionMainWgt : public QWidget
{
	Q_OBJECT

public:
	VisionMainWgt(QWidget *parent = nullptr);
	~VisionMainWgt();

protected:
	void init();


private:
	Ui::VisionMainWgtClass ui;

	LoadVedioWgt*		m_pLoadVedioWgt = nullptr;
	LoadImageWgt*		m_pLoadImageWgt = nullptr;
	ColorMetricWidget*	m_pCrMetricWgt	= nullptr;

};
