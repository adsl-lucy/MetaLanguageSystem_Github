#pragma once

#include <QObject>
#include <QRect>
#include <QPainter>
#include <QFontDatabase>
#include <qDebug>
#include <QMouseEvent>
#include <QtConcurrent>
#include <QThreadPool>
#include <QFutureWatcher>

#include "./TimeSecCht_define.h"
#include "../../protocol/protocol_audio.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"


class TimeSecCht_Painter : public QObject
{
	Q_OBJECT
public:
	TimeSecCht_Painter(QObject* parent);
	~TimeSecCht_Painter();

	virtual void resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para) = 0;

	struct ST_SecChtThreadProcessData
	{
		TimeSecCht_Painter* pPainter = nullptr;
		QString dataKey;
		int frameIndex = -1;
	};

	static void FillTargetFrame(const ST_SecChtThreadProcessData data);

	virtual bool  generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& FrameData) = 0;
	QRect getFreqBarRect(int startFreq, int bandWidth, double RectDB);

	void resetChtRect(const QRect ChtRect);
	void setCurrentFrameIndex(int index);
	void setDataRange(const ST_TimeSecChtDataRange dataRange);
	void setTimeSecChtPaintSetting(const ST_TimeSecChtPaintSetting paintSetting);
	void repaint(QPainter& painter);

	void setMousePosState(bool mouseInDrawArea, bool mouseInFilterArea, QPoint mousePos);
	QRect getDrawAreaRect();
	QRect getBottomAxisRect();
	virtual bool hasBandWidthFilterRect();

public:signals:
	void sgn_SecRectGenerateState(int percentage, int activateThreadCount, QString errstr);

protected:
	void	updateTitleText(EN_TimeSecCht_PaintType paintType);
	int		FreqToPosX(double freq);
	int		PosXToFreq(int posX);
	int		getDbHeight(const double val);
	double	PosYToDb(int posY);

	void drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect);
	void drawTitle(QPainter& painter, QRect& TopAxisRect);
	void drawValueAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis);
	void drawFreqAxis(QPainter& painter, QRect& BottomAxisArea);
	void drawThreshHoldInQuiet(QPainter& painter, QRect& drawArea);
	
	void drawCrRectLegend(QPainter& painter, QRect& RightColorMapRect, int index, QString text, QColor Cr);

	void drawValueAreaRect(QPainter& painter, QRect& drawArea);
	void drawMousePosCrossLine(QPainter& painter, QRect& drawArea);
	virtual void drawValueArea(QPainter& painter, QRect& drawArea)		= 0;	
	virtual void drawMousePosValue(QPainter& painter, QRect& drawArea)	= 0;
	virtual void drawLengend(QPainter& painter, QRect& RightColorMapRect) = 0;
	void	drawTIQLineLegend(QPainter& painter, QRect& RightColorMapRect);

	virtual void drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea);
	virtual void drawActiveRectValue(QPainter& painter);
	
	QString m_strDataKey;	
	QString m_strTitle;
	ST_TimeSecChtDataRange m_DataRange;
	double m_dFreqBarBandWidth = 0;

	ST_STFTInputpara m_STFTPara;
	int     m_nCurrentFrameIndex = -1;
	QRect   m_ChtRect;
	ST_TimeSecChtPaintSetting	m_paintSetting;
	
	QFont	m_ft_titleFont;
	QFont	m_ft_LegendFont;
	QFont   m_ft_valStrFt;

	bool	m_bMouseInDrawArea = false;
	bool	m_bMouseInFilterArea = false;
	QPoint	m_ptMousePos = QPoint(-1,-1);
	
};

