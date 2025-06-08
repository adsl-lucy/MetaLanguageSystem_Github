#include "VisionMainWgt.h"

VisionMainWgt::VisionMainWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();

}

VisionMainWgt::~VisionMainWgt()
{}

void VisionMainWgt::init()
{
	m_pLoadVedioWgt = new LoadVedioWgt(this);
	ui.VLayout_LoadVedioFile->insertWidget(0, m_pLoadVedioWgt);

	m_pLoadImageWgt = new LoadImageWgt(this);
	ui.VLayout_LoadImg->insertWidget(0, m_pLoadImageWgt);

	m_pCrMetricWgt = new ColorMetricWidget(this);
	ui.VLayout_ColorMetricWgt->insertWidget(0, m_pCrMetricWgt);

	connect(m_pLoadImageWgt, &LoadImageWgt::sgn_CrMetricWgtAutoLoadPicture, this, [=](QString Key) 
		{
			ui.tabWidget->setCurrentIndex(2);
			m_pCrMetricWgt->slot_AutoLoadImg(Key);
		});

}
