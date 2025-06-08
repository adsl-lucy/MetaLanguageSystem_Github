#include "TimeSecCht_Painter.h"
#pragma execution_character_set("utf-8")

TimeSecCht_Painter::TimeSecCht_Painter(QObject* parent) 
	:QObject(parent)
{
	QFont titleFont;
	titleFont.setFamily("ºÚÌå");
	titleFont.setPixelSize(20);
	m_ft_titleFont = titleFont;

	QFont legendFont;
	legendFont.setFamily("ºÚÌå");
	legendFont.setPixelSize(TimeSecCht_Audio::const_n_LegendFontSize);
	m_ft_LegendFont = legendFont;

	QFont valStrFt;
	valStrFt.setPixelSize(TimeSecCht_Audio::const_n_AxiesValStrFontSize);
	valStrFt.setFamily("ºÚÌå");
	m_ft_valStrFt = valStrFt;

}

TimeSecCht_Painter::~TimeSecCht_Painter()
{

}

void TimeSecCht_Painter::FillTargetFrame(const ST_SecChtThreadProcessData data)
{
	const QMap<QString, ST_STFTOutputData>& STFTMapRef = DataCenterManager::instance()->getSTFTOutputMap();
	auto mapPos = STFTMapRef.find(data.dataKey);
	if (mapPos == STFTMapRef.end())
	{
		qDebug() << "TimeSecCht_Painter::FillTargetFrame STFTMapPos end!";
		return;
	}

	const ST_STFTOutputData& dataRef = mapPos.value();

	if (data.frameIndex < 0 || data.frameIndex >= dataRef.vecOutput.size())
	{
		qDebug() << QString("TimeSecCht_Painter::FillTargetFrame FrameIndex outSize : %1!").arg(data.frameIndex);
		return;
	}

	const ST_FFTOutputData& frameData = dataRef.vecOutput[data.frameIndex];
	data.pPainter->generateFreqBarVec(data.frameIndex, frameData);
}

void TimeSecCht_Painter::setDataRange(const ST_TimeSecChtDataRange dataRange)
{
	m_DataRange = dataRange;
}


QRect TimeSecCht_Painter::getFreqBarRect(int startFreq, int bandWidth, double RectDB)
{
	QRect nullRect = QRect(0, 0, 0, 0);
	QRect drawArea = getDrawAreaRect();
	if (startFreq < m_DataRange.minFreq || startFreq + bandWidth > m_DataRange.maxFreq)
	{
		return nullRect;
	}

	int startX = FreqToPosX(startFreq);
	int endX = FreqToPosX(startFreq + bandWidth);
	int startY = drawArea.bottom();
	int height = 0;
	height = getDbHeight(RectDB);

	int endY = startY - height;

	QRect resultRect = QRect(QPoint(startX, startY), QPoint(endX, endY));

	return resultRect;
}

void TimeSecCht_Painter::resetChtRect(const QRect ChtRect)
{
	m_ChtRect = ChtRect;
}

void TimeSecCht_Painter::setCurrentFrameIndex(int index)
{
	m_nCurrentFrameIndex = index;
}

void TimeSecCht_Painter::setTimeSecChtPaintSetting(const ST_TimeSecChtPaintSetting paintSetting)
{
	m_paintSetting = paintSetting;
}

void TimeSecCht_Painter::repaint(QPainter& painter)
{
	const int& TopTitleHeight	= TimeSecCht_Audio::const_n_TopTitleHeight;
	const int& LeftAxisWidth	= TimeSecCht_Audio::const_n_LeftAxisWidth;
	const int& BottomAxisHeight = TimeSecCht_Audio::const_n_BottomAxisHeight;

	QRect	drawAreaRect = getDrawAreaRect();

	QRect LeftAxisRect		= QRect(QPoint(0, TopTitleHeight), drawAreaRect.bottomLeft());
	QRect TopAxisRect		= QRect(QPoint(LeftAxisWidth, 0), drawAreaRect.topRight());
	QRect BottomAxisRect	= getBottomAxisRect();
	QRect RightColorMapRect = QRect(QPoint(drawAreaRect.topRight().x(), TopTitleHeight),QPoint(m_ChtRect.right(), m_ChtRect.height() - BottomAxisHeight));

	if (false)
	{
		drawAxisRect(painter, drawAreaRect, LeftAxisRect, TopAxisRect, BottomAxisRect, RightColorMapRect);
	}

	drawTitle(painter, TopAxisRect);
	drawFreqAxis(painter, BottomAxisRect);
	drawValueAxis(painter, LeftAxisRect, false);
	drawValueArea(painter, drawAreaRect);
	drawValueAreaRect(painter, drawAreaRect);

	if (hasBandWidthFilterRect())
	{
		drawFilterActvateState(painter, BottomAxisRect);
	}

	if (m_paintSetting.EffOsc_TIQLine)
	{
		drawThreshHoldInQuiet(painter, drawAreaRect);
		drawTIQLineLegend(painter, RightColorMapRect);
	}

	if (m_bMouseInDrawArea)
	{
		drawMousePosCrossLine(painter, drawAreaRect);
		drawMousePosValue(painter, drawAreaRect);
	}

	if (m_bMouseInFilterArea && hasBandWidthFilterRect())
	{
		drawActiveRectValue(painter);
	}


	drawLengend(painter, RightColorMapRect);

}

void TimeSecCht_Painter::updateTitleText(EN_TimeSecCht_PaintType paintType)
{
	QString DataTypeStr;
	switch (paintType)
	{
		case EN_TimeSecCht_PaintType::STFT			:DataTypeStr = QString("STFT"); break;
		case EN_TimeSecCht_PaintType::EffOsc		:DataTypeStr = QString("EffOsc"); break;
		case EN_TimeSecCht_PaintType::BDSNR			:DataTypeStr = QString("BDSNR"); break;
		case EN_TimeSecCht_PaintType::VibState		:DataTypeStr = QString("VibState"); break;
	}

	m_strTitle = QString("TimeSecCht[%1]:%2 ").arg(DataTypeStr).arg(m_strDataKey);

}

void TimeSecCht_Painter::drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect)
{
	painter.setBrush(Qt::NoBrush);

	QPen AreaPen;
	AreaPen.setWidth(2);

	AreaPen.setColor(Qt::red);
	painter.setPen(AreaPen);
	painter.drawRect(m_ChtRect);

	AreaPen.setColor(Qt::black);
	painter.setPen(AreaPen);
	painter.drawRect(LeftAxisRect);
	painter.drawText(LeftAxisRect, Qt::AlignCenter, QString("L"));

	AreaPen.setColor(Qt::green);
	painter.setPen(AreaPen);
	painter.drawRect(TopAxisRect);
	painter.drawText(TopAxisRect, Qt::AlignCenter, QString("T"));

	AreaPen.setColor(Qt::blue);
	painter.setPen(AreaPen);
	painter.drawRect(BottomAxisRect);
	painter.drawText(BottomAxisRect, Qt::AlignCenter, QString("B"));


	AreaPen.setColor(Qt::magenta);
	painter.setPen(AreaPen);
	painter.drawRect(RightColorMapRect);
	painter.drawText(RightColorMapRect, Qt::AlignCenter, QString("R"));
}

void TimeSecCht_Painter::drawTitle(QPainter& painter, QRect& TopAxisRect)
{
	painter.setBrush(Qt::NoBrush);
	painter.setFont(m_ft_titleFont);

	QPen TitlePen;
	TitlePen.setWidth(2);
	TitlePen.setColor(TimeSecCht_Audio::const_Cr_Title);
	painter.setPen(TitlePen);

	painter.drawText(TopAxisRect, Qt::AlignCenter, m_strTitle);
}

void TimeSecCht_Painter::drawValueAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis)
{
	painter.setFont(m_ft_valStrFt);

	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(TimeSecCht_Audio::const_Cr_Axis);

	QPoint intervalStartPt	= LeftAxisArea.bottomRight() - QPoint(1, -1);
	double    startVal		= m_DataRange.minDB;
	double    maxFVal		= m_DataRange.maxDB;

	int    totalScaleCount = TimeSecCht_Audio::const_n_DBScaleIntervalCount + 1;
	double scaleInterval = (double)LeftAxisArea.height() / (double)(totalScaleCount - 1);
	double ValInterval = (maxFVal - startVal) / (totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString valStr;

		valStr = QString::number(startVal + ValInterval * scaleIndex) + QString("db");


		QPoint scaleStartPt = QPoint(intervalStartPt.x(), intervalStartPt.y() - scaleInterval * scaleIndex);
		QPoint scaleEndPt = scaleStartPt - QPoint(TimeSecCht_Audio::const_n_AxiesScaleLength, 0);

		painter.setPen(AxisPen);
		painter.drawLine(scaleStartPt, scaleEndPt);

		QRectF boundingRect = painter.boundingRect(LeftAxisArea, valStr);
		boundingRect.moveCenter(QPointF(0, scaleStartPt.y()));
		boundingRect.moveRight(scaleEndPt.x() - TimeSecCht_Audio::const_n_AxiesValStrMargin);

		painter.drawText(boundingRect, Qt::AlignCenter, valStr);

	}
}

void TimeSecCht_Painter::drawFreqAxis(QPainter& painter, QRect& BottomAxisArea)
{
	painter.setFont(m_ft_valStrFt);

	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(TimeSecCht_Audio::const_Cr_Axis);

	QPoint intervalStartPt	= BottomAxisArea.topLeft() + QPoint(0, 1);
	int    startFreq		= m_DataRange.minFreq;
	int    EndFreq			= m_DataRange.maxFreq;
	int    totalScaleCount	= TimeSecCht_Audio::const_n_FreqScaleIntervalCount + 1;
	double scaleInterval	= (double)BottomAxisArea.width() / (double)(totalScaleCount - 1);
	double FreqInterval		= (double)(EndFreq - startFreq) / (double)(totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString FreqStr = QString::number(startFreq + FreqInterval * scaleIndex) + QString("hz");
		QPoint scaleStartPt = QPoint(intervalStartPt.x() + scaleInterval * scaleIndex, intervalStartPt.y());
		QPoint scaleEndPt = scaleStartPt + QPoint(0, TimeSecCht_Audio::const_n_AxiesScaleLength);

		painter.setPen(AxisPen);
		painter.drawLine(scaleStartPt, scaleEndPt);

		QRectF boundingRect = painter.boundingRect(BottomAxisArea, FreqStr);
		boundingRect.moveCenter(QPointF(scaleStartPt.x(), 0));
		boundingRect.moveTop(scaleEndPt.y() + TimeSecCht_Audio::const_n_AxiesValStrMargin);

		painter.drawText(boundingRect, Qt::AlignCenter, FreqStr);
	}
}

void TimeSecCht_Painter::drawThreshHoldInQuiet(QPainter& painter, QRect& drawArea)
{
	int startY = drawArea.bottom();

	int    X1 = FreqToPosX(0);
	double DBY1 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(0));

	int    X2 = FreqToPosX(200);
	double DBY2 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(200));

	int    X3 = FreqToPosX(500);
	double DBY3 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(500));

	int    X4 = FreqToPosX(10000);
	double DBY4 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(10000));

	int    X5 = FreqToPosX(18000);
	double DBY5 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(18000));

	int    X6 = FreqToPosX(20000);
	double DBY6 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(20000));

	QPen ThreshHoldPen;
	ThreshHoldPen.setWidth(2);
	ThreshHoldPen.setStyle(Qt::DashLine);
	ThreshHoldPen.setColor(TimeSecCht_Audio::const_Cr_ThreshHoldLine);
	painter.setPen(ThreshHoldPen);

	QRect clipRect = drawArea;
	clipRect.setWidth(drawArea.width() - 4);
	clipRect.setHeight(drawArea.height() - 4);
	clipRect.moveCenter(drawArea.center());
	painter.setClipRect(clipRect);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawLine(X1, DBY1, X2, DBY2);
	painter.drawLine(X2, DBY2, X3, DBY3);
	painter.drawLine(X3, DBY3, X4, DBY4);
	painter.drawLine(X4, DBY4, X5, DBY5);
	painter.drawLine(X5, DBY5, X6, DBY6);

	painter.setClipRect(clipRect, Qt::NoClip);
	painter.setRenderHint(QPainter::Antialiasing, false);
}

void TimeSecCht_Painter::drawLengend(QPainter& painter, QRect& RightColorMapRect)
{
	
}

void TimeSecCht_Painter::drawTIQLineLegend(QPainter& painter, QRect& RightColorMapRect)
{
	const int& LegendTextMargin = TimeSecCht_Audio::const_n_LegendTextMargin;
	const int& LegendLeftMargin = TimeSecCht_Audio::const_n_LegendLeftMargin;
	const int& LegendTopMargin = TimeSecCht_Audio::const_n_LegendLeftMargin;
	const int& LegendFontSize = TimeSecCht_Audio::const_n_LegendFontSize;

	const QSize& legendSize = TimeSecCht_Audio::const_sz_Legend;

	int		LengendStrRectWidth = RightColorMapRect.width() - LegendTextMargin - legendSize.width() - LegendLeftMargin * 2;

	QPoint  LegendThreshHoldInQuietStartPt = RightColorMapRect.topLeft() + QPoint(LegendLeftMargin, LegendTopMargin);
	QPoint	LegendStrThreshHoldTopLeft = LegendThreshHoldInQuietStartPt + QPoint(20 + LegendTextMargin, (legendSize.height() - LegendFontSize) / 2);
	QRect	LegendStrThreshHoldInQuiet = QRect(LegendStrThreshHoldTopLeft, QSize(LengendStrRectWidth, LegendFontSize));

	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	QPen ThreshHoldPen;
	ThreshHoldPen.setWidth(2);
	ThreshHoldPen.setStyle(Qt::DashLine);
	ThreshHoldPen.setColor(TimeSecCht_Audio::const_Cr_ThreshHoldLine);
	painter.setPen(ThreshHoldPen);
	painter.drawLine(LegendThreshHoldInQuietStartPt
		+ QPoint(0, legendSize.height() / 2), LegendThreshHoldInQuietStartPt + QPoint(20, legendSize.height() / 2));

	painter.setPen(NormalTextPen);
	QString ThreshholdInQuietLegendStr = QString("TIQ");
	painter.drawText(LegendStrThreshHoldInQuiet, Qt::AlignLeft | Qt::AlignVCenter, ThreshholdInQuietLegendStr);
}

void TimeSecCht_Painter::drawCrRectLegend(QPainter& painter, QRect& RightColorMapRect, int index, QString text, QColor Cr)
{
	const int& LegendTextMargin = TimeSecCht_Audio::const_n_LegendTextMargin;
	const int& LegendLeftMargin = TimeSecCht_Audio::const_n_LegendLeftMargin;
	const int& LegendTopMargin	= TimeSecCht_Audio::const_n_LegendLeftMargin;
	const int& LegendFontSize	= TimeSecCht_Audio::const_n_LegendFontSize;
	const int& LegendSpacing	= TimeSecCht_Audio::const_n_LegendSpacing;

	const QSize& legendSize = TimeSecCht_Audio::const_sz_Legend;

	int		LengendStrRectWidth = RightColorMapRect.width() - LegendTextMargin - legendSize.width() - LegendLeftMargin * 2;

	QPoint  LegendThreshHoldInQuietStartPt = RightColorMapRect.topLeft() + QPoint(LegendLeftMargin, LegendTopMargin);
	QPoint	LegendRectStartTopLeft = LegendThreshHoldInQuietStartPt + QPoint(0, legendSize.height() + LegendSpacing);
	QRect   LegendRect(LegendRectStartTopLeft + QPoint(0, (legendSize.height() + LegendSpacing) * index), legendSize);
	QPoint	LegendStrTopLeft = LegendRect.topLeft() + QPoint(legendSize.width() + LegendTextMargin, (legendSize.height() - LegendFontSize) / 2);
	QRect	LegendStrRect = QRect(LegendStrTopLeft, QSize(LengendStrRectWidth, LegendFontSize));

	painter.setBrush(Cr);
	painter.drawRect(LegendRect);
	painter.drawText(LegendStrRect, Qt::AlignLeft | Qt::AlignVCenter, text);

}

void TimeSecCht_Painter::drawValueAreaRect(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(TimeSecCht_Audio::const_Cr_Axis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::NoBrush);
	painter.drawRect(drawArea);
}

void TimeSecCht_Painter::drawMousePosCrossLine(QPainter& painter, QRect& drawArea)
{
	QPen linePen;
	linePen.setWidth(2);
	linePen.setColor(Qt::blue);

	int FreqX = m_ptMousePos.x();
	int FreqStartY = drawArea.bottom();
	int FreqEndY = drawArea.top();

	int ValY = m_ptMousePos.y();
	int ValStartX = drawArea.left();
	int ValEndY = drawArea.right();

	painter.setPen(linePen);
	painter.drawLine(QPoint(FreqX, FreqStartY), QPoint(FreqX, FreqEndY));
	painter.drawLine(QPoint(ValStartX, ValY), QPoint(ValEndY, ValY));

	QSize valRectSize(80, 20);

	QRect ValRect;
	ValRect.setSize(valRectSize);
	ValRect.moveCenter(QPoint(drawArea.left() - valRectSize.width() / 2, m_ptMousePos.y()));

	QRect FreqRect;
	FreqRect.setSize(valRectSize);
	FreqRect.moveCenter(QPoint(FreqX, drawArea.bottom() + valRectSize.height() / 2));

	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);
	painter.setBrush(Qt::white);

	painter.drawRect(ValRect);
	painter.drawRect(FreqRect);

	int FreqVal = PosXToFreq(m_ptMousePos.x());
	painter.drawText(FreqRect, Qt::AlignCenter, QString::number(FreqVal) + "hz");
	double DbVal = PosYToDb(m_ptMousePos.y());
	painter.drawText(ValRect, Qt::AlignCenter, QString::number(DbVal, 'f', 1) + "db");
}

void TimeSecCht_Painter::drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea)
{
}

void TimeSecCht_Painter::drawActiveRectValue(QPainter& painter)
{

}

void TimeSecCht_Painter::setMousePosState(bool mouseInDrawArea, bool mouseInFilterArea, QPoint mousePos)
{
	m_bMouseInDrawArea		= mouseInDrawArea;
	m_bMouseInFilterArea	= mouseInFilterArea;
	m_ptMousePos			= mousePos;
}

QRect TimeSecCht_Painter::getDrawAreaRect()
{
	QPoint		drawAreaStartPt = QPoint(TimeSecCht_Audio::const_n_LeftAxisWidth, TimeSecCht_Audio::const_n_TopTitleHeight);
	QPoint		drawAreaEndPt	= QPoint(	m_ChtRect.width()	- TimeSecCht_Audio::const_n_RightColorMapRegionWidth
											,m_ChtRect.height() - TimeSecCht_Audio::const_n_BottomAxisHeight);
	QRect		drawAreaRect	= QRect(drawAreaStartPt, drawAreaEndPt);
	return		drawAreaRect;
}

QRect TimeSecCht_Painter::getBottomAxisRect()
{
	QRect  drawAreaRect = getDrawAreaRect();
	QRect  BottomAxisRect = QRect(drawAreaRect.bottomLeft(), QPoint(drawAreaRect.bottomRight().x(), m_ChtRect.height()));
	return BottomAxisRect;
}

bool TimeSecCht_Painter::hasBandWidthFilterRect()
{
	return false;
}

int   TimeSecCht_Painter::FreqToPosX(double freq)
{
	QRect drawArea = getDrawAreaRect();
	double FreqRatio = (freq - (double)m_DataRange.minFreq) / ((double)m_DataRange.maxFreq - (double)m_DataRange.minFreq);
	int FreqX = FreqRatio * drawArea.width() + drawArea.x();
	return FreqX;
}

int   TimeSecCht_Painter::PosXToFreq(int posX)
{
	QRect drawArea = getDrawAreaRect();

	if (posX < drawArea.left() || posX > drawArea.right())
	{
		return -1;
	}

	double XRatio = ((double)posX - (double)drawArea.left()) / (double)drawArea.width();
	double TotalFreqWidth = m_DataRange.maxFreq - m_DataRange.minFreq;
	double resultFreq = XRatio * TotalFreqWidth + m_DataRange.minFreq;
	return resultFreq;

}

int   TimeSecCht_Painter::getDbHeight(const double valDb)
{
	QRect drawArea = getDrawAreaRect();
	double valRatio = (valDb - m_DataRange.minDB) / (m_DataRange.maxDB - m_DataRange.minDB);

	if (valRatio < 0)
	{
		return 0;
	}
	else if (valRatio > 1)
	{
		return drawArea.height();
	}

	if (valDb > 40)
	{
		int a = 0;
	}

	double ratioHeight = drawArea.height() * valRatio;
	return (int)ratioHeight;

}

double TimeSecCht_Painter::PosYToDb(int posY)
{
	QRect drawArea = getDrawAreaRect();
	if (posY < drawArea.top() && posY > drawArea.bottom())
	{
		return 0;
	}

	int realtiveY = drawArea.bottom() - posY;
	double realtiveDb = ((double)realtiveY / (double)drawArea.height()) * (m_DataRange.maxDB - m_DataRange.minDB) + m_DataRange.minDB;
	return realtiveDb;

}