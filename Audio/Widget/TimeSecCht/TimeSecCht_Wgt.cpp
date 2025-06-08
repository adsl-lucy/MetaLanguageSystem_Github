#include "TimeSecCht_Wgt.h"

TimeSecCht_Wgt::TimeSecCht_Wgt(QWidget* parent):QWidget(parent)
{
	setMouseTracking(true);

	m_pPainter_STFT = new TimeSecCht_Painter_STFT(this);
	m_PainterVec.push_back(m_pPainter_STFT);
	connect(m_pPainter_STFT, &TimeSecCht_Painter_STFT::sgn_SecRectGenerateState, this, &TimeSecCht_Wgt::sgn_SecRectGenerateState);
	connect(m_pPainter_STFT, &TimeSecCht_Painter_STFT::sgn_GenFinished, this, [=] 
		{
			slot_RectGenFinished(EN_TimeSecCht_PaintType::STFT);
		});

	m_pPainter_EffOsc = new TimeSecCht_Painter_EffOsc(this);
	m_PainterVec.push_back(m_pPainter_EffOsc);
	connect(m_pPainter_EffOsc, &TimeSecCht_Painter_EffOsc::sgn_SecRectGenerateState, this, &TimeSecCht_Wgt::sgn_SecRectGenerateState);
	connect(m_pPainter_EffOsc, &TimeSecCht_Painter_EffOsc::sgn_GenFinished, this, [=]
		{
			slot_RectGenFinished(EN_TimeSecCht_PaintType::EffOsc);
		});

	m_pPainter_BDSNR = new TimeSecCht_Painter_BDSNR(this);
	m_PainterVec.push_back(m_pPainter_BDSNR);
	connect(m_pPainter_BDSNR, &TimeSecCht_Painter_BDSNR::sgn_SecRectGenerateState, this, &TimeSecCht_Wgt::sgn_SecRectGenerateState);
	connect(m_pPainter_BDSNR, &TimeSecCht_Painter_BDSNR::sgn_GenFinished, this, [=]
		{
			slot_RectGenFinished(EN_TimeSecCht_PaintType::BDSNR);
		});

	m_pPainter_VibState = new TimeSecCht_Painter_VibState(this);
	m_PainterVec.push_back(m_pPainter_VibState);
	connect(m_pPainter_VibState, &TimeSecCht_Painter_VibState::sgn_SecRectGenerateState, this, &TimeSecCht_Wgt::sgn_SecRectGenerateState);
	connect(m_pPainter_VibState, &TimeSecCht_Painter_VibState::sgn_GenFinished, this, [=]
		{
			slot_RectGenFinished(EN_TimeSecCht_PaintType::VibState);
		});

	

}

TimeSecCht_Wgt::~TimeSecCht_Wgt()
{

}

void TimeSecCht_Wgt::setGenType(const ST_TimeSecChtGenSetting GenSet)
{
	m_GenSetting = GenSet;
}

void TimeSecCht_Wgt::setPaintType(const EN_TimeSecCht_PaintType paintType)
{
	m_PaintType = paintType;
	update();
}

void TimeSecCht_Wgt::setDataRange(const ST_TimeSecChtDataRange dataRange)
{
	for (TimeSecCht_Painter* painter : m_PainterVec)
	{
		painter->setDataRange(dataRange);
	}
}

void TimeSecCht_Wgt::resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para)
{
	m_GenState.Gen_STFT			= !m_GenSetting.Gen_STFT;
	m_GenState.Gen_EffOsc		= !m_GenSetting.Gen_EffOsc;
	m_GenState.Gen_BDSNR		= !m_GenSetting.Gen_BDSNR;
	m_GenState.Gen_VibState		= !m_GenSetting.Gen_VibState;

	if (m_GenSetting.Gen_STFT)			m_pPainter_STFT->resetTimeSecChtRect(dataKey, para);
	if (m_GenSetting.Gen_EffOsc)		m_pPainter_EffOsc->resetTimeSecChtRect(dataKey, para);
	if (m_GenSetting.Gen_BDSNR)			m_pPainter_BDSNR->resetTimeSecChtRect(dataKey, para);
	if (m_GenSetting.Gen_VibState)		m_pPainter_VibState->resetTimeSecChtRect(dataKey, para);

}

void TimeSecCht_Wgt::setCurrentFrameIndex(int index)
{
	for (TimeSecCht_Painter* painter : m_PainterVec)
	{
		painter->setCurrentFrameIndex(index);
	}
	update();
}

void TimeSecCht_Wgt::setPaintSetting(const ST_TimeSecChtPaintSetting paintSetting)
{
	for (TimeSecCht_Painter* painter : m_PainterVec)
	{
		painter->setTimeSecChtPaintSetting(paintSetting);
	}
	update();
}

void TimeSecCht_Wgt::slot_RectGenFinished(EN_TimeSecCht_PaintType type)
{
	m_mutex.lock();
	switch (type)
	{
		case EN_TimeSecCht_PaintType::STFT		:m_GenState.Gen_STFT		= true; break;
		case EN_TimeSecCht_PaintType::EffOsc	:m_GenState.Gen_EffOsc		= true; break;
		case EN_TimeSecCht_PaintType::BDSNR		:m_GenState.Gen_BDSNR		= true; break;
		case EN_TimeSecCht_PaintType::VibState	:m_GenState.Gen_VibState	= true; break;
	}

	if (	m_GenState.Gen_STFT 
		&&	m_GenState.Gen_EffOsc
		&&	m_GenState.Gen_BDSNR
		&&	m_GenState.Gen_VibState)
	{
		emit sgn_SecRectGenFinished();
	}
	m_mutex.unlock();
	
}

void TimeSecCht_Wgt::mouseMoveEvent(QMouseEvent* event)
{
	QPoint	mousePos = event->pos();

	TimeSecCht_Painter* currentPainter = getCurrentPainter();
	if (currentPainter == nullptr)
	{
		return;
	}

	QRect	DrawArea = currentPainter->getDrawAreaRect();
	QRect	BottomAxisRect = currentPainter->getBottomAxisRect();

	bool mouseInDrawArea = DrawArea.contains(mousePos);
	bool mouseInMFCCRect = false;

	if (m_PaintType == EN_TimeSecCht_PaintType::BDSNR)
	{
		mouseInMFCCRect = BottomAxisRect.contains(mousePos);
	}

	if (!mouseInDrawArea && !mouseInMFCCRect)
	{
		mousePos = QPoint(-1, -1);
	}

	currentPainter->setMousePosState(mouseInDrawArea, mouseInMFCCRect, mousePos);

	update();
}

void TimeSecCht_Wgt::leaveEvent(QEvent* event)
{
	TimeSecCht_Painter* currentPainter = getCurrentPainter();
	if (currentPainter)
	{
		currentPainter->setMousePosState(false, false, QPoint(-1,-1));
	}
}

void TimeSecCht_Wgt::showEvent(QShowEvent* event)
{
	resetPainterRect();
}

void TimeSecCht_Wgt::hideEvent(QHideEvent* event)
{
}

void TimeSecCht_Wgt::resizeEvent(QResizeEvent* event)
{
	resetPainterRect();
}

void TimeSecCht_Wgt::paintEvent(QPaintEvent* event)
{
	TimeSecCht_Painter* currentPainter = getCurrentPainter();
	if (currentPainter)
	{
		QPainter painter(this);
		currentPainter->repaint(painter);
	}
}

TimeSecCht_Painter* TimeSecCht_Wgt::getCurrentPainter()
{
	switch (m_PaintType)
	{
		case EN_TimeSecCht_PaintType::STFT			:return m_pPainter_STFT;
		case EN_TimeSecCht_PaintType::EffOsc		:return m_pPainter_EffOsc;
		case EN_TimeSecCht_PaintType::BDSNR			:return m_pPainter_BDSNR;
		case EN_TimeSecCht_PaintType::VibState		:return m_pPainter_VibState;
	}
	return nullptr;
}

void TimeSecCht_Wgt::resetPainterRect()
{
	QRect thisRect = this->rect();
	for (TimeSecCht_Painter* painter : m_PainterVec)
	{
		painter->resetChtRect(thisRect);
	}
}
