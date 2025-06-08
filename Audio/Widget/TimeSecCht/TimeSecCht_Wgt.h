#pragma once

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QMutex>


#include "./TimeSecCht_define.h"
#include "../../protocol/protocol_audio.h"
#include "./TimeSecCht_Painter.h"
#include "./STFT/TimeSecCht_Painter_STFT.h"
#include "./EffOsc/TimeSecCht_Painter_EffOsc.h"
#include "./BDSNR/TimeSecCht_Painter_BDSNR.h"
#include "./VibState/TimeSecCht_Painter_VibState.h"

class TimeSecCht_Wgt : public QWidget
{
	Q_OBJECT
public:
	TimeSecCht_Wgt(QWidget* parent);
	~TimeSecCht_Wgt();

	void setGenType(const ST_TimeSecChtGenSetting GenSet);
	void setPaintType(const EN_TimeSecCht_PaintType paintType);
	void setDataRange(const ST_TimeSecChtDataRange dataRange);
	void resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para);

	void setCurrentFrameIndex(int index);
	void setPaintSetting(const ST_TimeSecChtPaintSetting paintSetting);

public:signals:
	void sgn_SecRectGenerateState(int percentage, int activateThreadCount, QString errstr);
	void sgn_SecRectGenFinished();

protected slots:
	void slot_RectGenFinished(EN_TimeSecCht_PaintType type);

protected:
	void mouseMoveEvent(QMouseEvent* event);
	void leaveEvent(QEvent* event);
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);
	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* event);

	TimeSecCht_Painter* getCurrentPainter();
	void	resetPainterRect();

private:
	EN_TimeSecCht_PaintType	 m_PaintType	= EN_TimeSecCht_PaintType::STFT;
	QMutex					 m_mutex;
	ST_TimeSecChtGenSetting  m_GenState;
	ST_TimeSecChtGenSetting  m_GenSetting;
	TimeSecCht_Painter_STFT*		m_pPainter_STFT			= nullptr;
	TimeSecCht_Painter_EffOsc*		m_pPainter_EffOsc		= nullptr;
	TimeSecCht_Painter_BDSNR*		m_pPainter_BDSNR		= nullptr;
	TimeSecCht_Painter_VibState*	m_pPainter_VibState		= nullptr;

	QVector<TimeSecCht_Painter*> m_PainterVec;

};