#include "Cht_LABColorDistribute.h"
#pragma execution_character_set("utf-8")

Cht_LABColorDistribute::Cht_LABColorDistribute(QWidget* parent):QWidget(parent)
{
	setMouseTracking(true);


	m_ftAxisValStr.setPixelSize(m_nAxiesValStrFontSize);
	m_ftAxisValStr.setFamily("黑体");
	m_ftAxisValStr.setPixelSize(m_nAxiesValStrFontSize);

	m_pConcurrentWatcher = new QFutureWatcher<void>(this);
	connect(m_pConcurrentWatcher, &QFutureWatcher<void>::progressValueChanged, this, &Cht_LABColorDistribute::slot_GenProgressValueChanged);

}

Cht_LABColorDistribute::~Cht_LABColorDistribute()
{
}

void Cht_LABColorDistribute::setDrawingSet(bool drawAxis, bool drawGrid)
{
	m_bDrawAxis = drawAxis;
	m_bDrawGrid = drawGrid;
	update();
}

void Cht_LABColorDistribute::setAxiSetting(EN_LabCht_AxiType AxiType, ST_LabCht_AxiPos startPos, ST_LabCht_AxiPos endPos, ST_LabCht_Density gridDensity)
{
	m_AxiType		= AxiType;
	m_AxiStartPos	= startPos;
	m_AxiEndPos		= endPos;
	m_GridDensity	= gridDensity;
	update();
}

void Cht_LABColorDistribute::resetCrRect(EN_LabCht_CrRectType CrRectType, bool GammaExist, int CrRectWidth, ST_LabCht_Density CrDensity)
{
	m_CrRectType = CrRectType;
	m_CrDensity = CrDensity;
	m_bGammaExist = GammaExist;
	m_nCrRectWidth = CrRectWidth;
	if (m_CrRectType == EN_LabCht_CrRectType::Density)
	{
		switch (m_AxiType)
		{
			case EN_LabCht_AxiType::Fix_L_Axi_Euclid	: resetCrRectVec_Fix_L_Euclid(); break;
			case EN_LabCht_AxiType::Fix_AB_Axi_Euclid	: resetCrRectVec_Fix_AB_Euclid(); break;
		}
		update();
	}
	else
	{
		m_bOnGenrate = true;
		resetCrRectVec_Pixel();
	}

}

void Cht_LABColorDistribute::getCaculateResult(int& CaculateRectCount, int& ValidRectCount)
{
	CaculateRectCount	= m_nCaculateRectCount;
	ValidRectCount		= m_nValidRectCount;
}

void Cht_LABColorDistribute::mousePressEvent(QMouseEvent* event)
{
	m_bMousePressed = true;
	m_ptMousePressedPt = event->pos();
	m_ptMouseCurrentPt = event->pos();
	sendMousePosMsg(m_ptMousePressedPt, true);
	sendMousePosMsg(m_ptMouseCurrentPt, false);
	sendPosMetric(true, m_ptMousePressedPt, m_ptMouseCurrentPt);
	update();
}

void Cht_LABColorDistribute::mouseReleaseEvent(QMouseEvent* event)
{
	m_bMousePressed = false;
	m_ptMousePressedPt = QPoint(-1, -1);
	sendMousePosMsg(m_ptMousePressedPt, true);
	sendPosMetric(false, m_ptMousePressedPt, m_ptMouseCurrentPt);
	update();
}

void Cht_LABColorDistribute::leaveEvent(QEvent* event)
{
	m_bMousePressed = false;
	m_ptMousePressedPt = QPoint(-1, -1);
	sendMousePosMsg(m_ptMousePressedPt, true);
	sendPosMetric(false, m_ptMousePressedPt, m_ptMouseCurrentPt);
	update();
}

void Cht_LABColorDistribute::mouseMoveEvent(QMouseEvent* event)
{
	m_ptMouseCurrentPt = event->pos();
	sendMousePosMsg(m_ptMouseCurrentPt, false);

	if (m_bMousePressed)
	{
		sendPosMetric(true, m_ptMousePressedPt, m_ptMouseCurrentPt);
	}

	update();
}

void Cht_LABColorDistribute::sendMousePosMsg(const QPoint& mousePos, bool isPressed)
{
	ST_ChtLab_MousePosLabInfo posInfo;
	getMousePosInfo(mousePos, posInfo);

	if (isPressed)
	{
		emit sgn_updateMousePressedPosInfo(posInfo);
	}
	else
	{		
		emit sgn_updateCurrentMousePosInfo(posInfo);
	}

}

void Cht_LABColorDistribute::sendPosMetric(bool MetricValid, const QPoint& mousePos1, const QPoint mousePos2)
{
	if (!MetricValid)
	{
		emit sgn_updateMousePosMetricInfo(false, -1, -1, -1, -1,-1);
	}
	else
	{
		ST_ChtLab_MousePosLabInfo pos1Info,pos2Info;
		getMousePosInfo(mousePos1, pos1Info);
		getMousePosInfo(mousePos2, pos2Info);

		MetricValid = pos1Info.SRgbValid && pos2Info.SRgbValid;
		if (!MetricValid)
		{
			emit sgn_updateMousePosMetricInfo(false, -1, -1, -1, -1, -1);
		}
		else
		{
			double dis_RGB255   = ColorMetrics::instance()->getMetric_RGB255(pos1Info.MouseCr, pos2Info.MouseCr);
			double dis_LAB_1976 = ColorMetrics::instance()->getMetric_LAB(EN_LAB_Metric_Type::CIE_1976, pos1Info.MouseLab, pos2Info.MouseLab);
			double dis_LAB_1984 = ColorMetrics::instance()->getMetric_LAB(EN_LAB_Metric_Type::CIE_1984, pos1Info.MouseLab, pos2Info.MouseLab);
			double dis_LAB_1994 = ColorMetrics::instance()->getMetric_LAB(EN_LAB_Metric_Type::CIE_1994, pos1Info.MouseLab, pos2Info.MouseLab);
			double dis_LAB_2000 = ColorMetrics::instance()->getMetric_LAB(EN_LAB_Metric_Type::CIE_2000, pos1Info.MouseLab, pos2Info.MouseLab);
			emit sgn_updateMousePosMetricInfo(true, dis_RGB255, dis_LAB_1976, dis_LAB_1984, dis_LAB_1994, dis_LAB_2000);
		}
	}
}

void Cht_LABColorDistribute::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.setPen(Qt::NoPen);

	QRect thisRect = this->rect();

	painter.drawRect(thisRect);

	if (m_bOnGenrate)
	{
		return;
	}

	QRect	drawAreaRect		= getDrawAreaRect();
	QRect	LeftAxisRect		= QRect(QPoint(0, m_nTopTitleHeight), drawAreaRect.bottomLeft());
	QRect	TopAxisRect			= QRect(QPoint(m_nLeftAxisWidth, 0), drawAreaRect.topRight());
	QRect	BottomAxisRect		= getBottomAxisRect();
	QRect	RightColorMapRect	= QRect(QPoint(drawAreaRect.topRight().x(), m_nTopTitleHeight), QPoint(thisRect.right(), thisRect.height() - m_nBottomAxisHeight));

	//drawAxisRect(painter, drawAreaRect, LeftAxisRect, TopAxisRect, BottomAxisRect, RightColorMapRect);

	switch (m_AxiType)
	{
		case EN_LabCht_AxiType::Fix_L_Axi_Euclid	:paintAxies_Fix_L_Euclid(painter); break;
		case EN_LabCht_AxiType::Fix_AB_Axi_Euclid	:paintAxies_Fix_AB(painter); break;
	}


	painter.setPen(Qt::NoPen);

	if (m_CrRectType == EN_LabCht_CrRectType::Density)
	{
		for (int rowIndex = 0; rowIndex < m_vecCrRect.size(); rowIndex++)
		{
			const QVector<ST_LabCht_CrRect>& RowRef = m_vecCrRect[rowIndex];
			for (int colIndex = 0; colIndex < RowRef.size(); colIndex++)
			{
				const ST_LabCht_CrRect& RectRef = RowRef[colIndex];
				if (RectRef.CrValid)
				{
					painter.setBrush(RectRef.QCr);
					painter.drawRect(RectRef.drawRect);
				}
			}
		}
	}
	else
	{
		QRect drawRect = getDrawAreaRect();
		QRect ImgRect;
		ImgRect.setLeft(drawRect.left() + 1);
		ImgRect.setRight(drawRect.right() - 1);
		ImgRect.setTop(drawRect.top() + 1);
		ImgRect.setBottom(drawRect.bottom() - 1);

		painter.drawImage(drawRect.topLeft() + QPoint(1,1), m_CrPixelImg);
	}

	if (m_bMousePressed)
	{
		QPen MetricLinePine;
		MetricLinePine.setColor(Qt::white);
		MetricLinePine.setWidth(2);

		painter.setPen(MetricLinePine);
		painter.drawLine(m_ptMousePressedPt, m_ptMouseCurrentPt);
	}

}

void Cht_LABColorDistribute::drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect)
{
	QRect thisRect = this->rect();
	painter.setBrush(Qt::NoBrush);

	QPen AreaPen;
	AreaPen.setWidth(2);

	auto drawAreaRectWithText = [&painter, &AreaPen](const QColor RectCr, const QRect& rect,QString drawText)
		{
			AreaPen.setColor(RectCr);
			painter.setPen(AreaPen);
			painter.drawRect(rect);
			painter.drawText(rect, Qt::AlignCenter, drawText);
		};

	drawAreaRectWithText(Qt::red		, thisRect					, QString(""));
	drawAreaRectWithText(Qt::red		, LeftAxisRect				, QString("L"));
	drawAreaRectWithText(Qt::green		, TopAxisRect				, QString("T"));
	drawAreaRectWithText(Qt::blue		, BottomAxisRect			, QString("B"));
	drawAreaRectWithText(Qt::magenta	, RightColorMapRect			, QString("R"));
	drawAreaRectWithText(Qt::magenta	, getMaxDrawAreaSquare()	, QString("center Area"));

}

void Cht_LABColorDistribute::paintAxies_Fix_L_Euclid(QPainter& painter)
{
	QRect	drawAreaRect	= getDrawAreaRect();
	QRect	DrawAreaSquare	= getMaxDrawAreaSquare();
	QRect	BottomAxisRect	= getBottomAxisRect();
	QRect	LeftAxisArea	= QRect(QPoint(0, m_nTopTitleHeight), drawAreaRect.bottomLeft());

	QPen AxisPen;
	AxisPen.setWidth(1);
	AxisPen.setColor(m_CrAxis);
	painter.setPen(AxisPen);

	painter.setFont(m_ftAxisValStr);

	{
		QPoint intervalStartPt_AxiA		= BottomAxisRect.topLeft() + QPoint(0, 1);
		int    startA	= m_AxiStartPos.A;
		int    endA		= m_AxiEndPos.A;
		int    totalScaleCount_AxiA		= (double)(endA - startA) / (double)m_GridDensity.AB + 1;
		double scaleInterval_AxiA		= (double)DrawAreaSquare.width() / (double)(totalScaleCount_AxiA - 1);
		double ValInterval_AxiA			= (double)(endA - startA) / (double)(totalScaleCount_AxiA - 1);

		if (m_bDrawAxis)
		{		
			AxisPen.setWidth(2);
			painter.setPen(AxisPen);
			for (int scaleIndex = 0; scaleIndex < totalScaleCount_AxiA; scaleIndex++)
			{
				QString ValStr = QString::number((double)startA + ValInterval_AxiA * scaleIndex, 'f', 0) + QString(" ");
				QPoint scaleStartPt = QPoint(intervalStartPt_AxiA.x() + scaleInterval_AxiA * scaleIndex, intervalStartPt_AxiA.y());
				QPoint scaleEndPt = scaleStartPt + QPoint(0, m_nAxiesScaleLength);

				//painter.setPen(AxisPen);
				painter.drawLine(scaleStartPt, scaleEndPt);

				QRectF boundingRect = painter.boundingRect(BottomAxisRect, ValStr);
				boundingRect.moveCenter(QPointF(scaleStartPt.x(), 0));
				boundingRect.moveTop(scaleEndPt.y() + m_nAxiesValStrMargin);

				painter.drawText(boundingRect, Qt::AlignCenter, ValStr);
			}
			BottomAxisRect.setWidth(DrawAreaSquare.width());
			BottomAxisRect.moveCenter(BottomAxisRect.center() + QPoint(0, 10));
			painter.drawText(BottomAxisRect, Qt::AlignCenter, QString("A"));
		}

		if (m_bDrawGrid)
		{		
			AxisPen.setWidth(1);
			painter.setPen(AxisPen);
			for (int gridAIndex = 0; gridAIndex < totalScaleCount_AxiA; gridAIndex++)
			{
				QPoint scaleStartPt = QPoint(intervalStartPt_AxiA.x() + scaleInterval_AxiA * gridAIndex, intervalStartPt_AxiA.y());
				QPoint scaleEndPt = scaleStartPt - QPoint(0, DrawAreaSquare.height());
				painter.drawLine(scaleStartPt, scaleEndPt);
			}
		}
	}

	{
		QPoint	intervalStartPt_AxiB = LeftAxisArea.bottomRight() - QPoint(1, -1);
		double	startB	= m_AxiStartPos.B;
		double	endB	= m_AxiEndPos.B;

		int    totalScaleCount_AxiB = (double)(endB - startB) / (double)m_GridDensity.AB + 1;
		double scaleInterval_AxiB	= (double)DrawAreaSquare.height() / (double)(totalScaleCount_AxiB - 1);
		double ValInterval_AxiB		= (endB - startB) / (totalScaleCount_AxiB - 1);

		if (m_bDrawAxis)
		{
			AxisPen.setWidth(2);
			painter.setPen(AxisPen);
			for (int scaleIndex = 0; scaleIndex < totalScaleCount_AxiB; scaleIndex++)
			{
				QString valStr = QString::number((double)startB + ValInterval_AxiB * scaleIndex, 'f', 0) + QString(" ");

				QPoint scaleStartPt = QPoint(intervalStartPt_AxiB.x(), intervalStartPt_AxiB.y() - scaleInterval_AxiB * scaleIndex);
				QPoint scaleEndPt = scaleStartPt - QPoint(m_nAxiesScaleLength, 0);
				painter.drawLine(scaleStartPt, scaleEndPt);

				QRectF boundingRect = painter.boundingRect(LeftAxisArea, valStr);
				boundingRect.moveCenter(QPointF(0, scaleStartPt.y()));
				boundingRect.moveRight(scaleEndPt.x() - m_nAxiesValStrMargin);

				painter.drawText(boundingRect, Qt::AlignCenter, valStr);
			}
		}

		LeftAxisArea.moveCenter(LeftAxisArea.center() - QPoint(20, 0));
		painter.drawText(LeftAxisArea, Qt::AlignCenter, QString("B"));

		if (m_bDrawGrid)
		{
			AxisPen.setWidth(1);
			painter.setPen(AxisPen);
			for (int gridBIndex = 0; gridBIndex < totalScaleCount_AxiB; gridBIndex++)
			{
				QPoint GridStartPoint(intervalStartPt_AxiB.x(), intervalStartPt_AxiB.y() - scaleInterval_AxiB * gridBIndex);
				QPoint GridEndPoint = GridStartPoint + QPoint(DrawAreaSquare.width(), 0);
				painter.drawLine(GridStartPoint, GridEndPoint);
			}
		}
	}

}

void Cht_LABColorDistribute::paintAxies_Fix_AB(QPainter& painter)
{
	QRect	drawAreaRect = getDrawAreaRect();
	QRect	DrawAreaSquare = getMaxDrawAreaSquare();
	QRect	BottomAxisRect = getBottomAxisRect();
	QRect	LeftAxisArea = QRect(QPoint(0, m_nTopTitleHeight), drawAreaRect.bottomLeft());

	QPen AxisPen;
	AxisPen.setWidth(1);
	AxisPen.setColor(m_CrAxis);
	painter.setPen(AxisPen);

	painter.setFont(m_ftAxisValStr);

	{
		QPoint	intervalStartPt_AxiL = LeftAxisArea.bottomRight() - QPoint(1, -1);
		double	startL	= m_AxiStartPos.L;
		double	endL	= m_AxiEndPos.L;
		int    totalScaleCount_AxiL		= (double)(endL - startL) / (double)m_GridDensity.L + 1;
		double scaleInterval_AxiL		= (double)LeftAxisArea.height() / (double)(totalScaleCount_AxiL - 1);
		double ValInterval_AxiL			= (endL - startL) / (totalScaleCount_AxiL - 1);

		if (m_bDrawAxis)
		{
			AxisPen.setWidth(2);
			painter.setPen(AxisPen);
			for (int scaleIndex = 0; scaleIndex < totalScaleCount_AxiL; scaleIndex++)
			{
				QString valStr = QString::number((double)startL + ValInterval_AxiL * scaleIndex, 'f', 0) + QString(" ");

				QPoint scaleStartPt = QPoint(intervalStartPt_AxiL.x(), intervalStartPt_AxiL.y() - scaleInterval_AxiL * scaleIndex);
				QPoint scaleEndPt = scaleStartPt - QPoint(m_nAxiesScaleLength, 0);

				painter.drawLine(scaleStartPt, scaleEndPt);

				QRectF boundingRect = painter.boundingRect(LeftAxisArea, valStr);
				boundingRect.moveCenter(QPointF(0, scaleStartPt.y()));
				boundingRect.moveRight(scaleEndPt.x() - m_nAxiesValStrMargin);

				painter.drawText(boundingRect, Qt::AlignCenter, valStr);

			}
		}

		LeftAxisArea.moveCenter(LeftAxisArea.center() - QPoint(20, 0));
		painter.drawText(LeftAxisArea, Qt::AlignCenter, QString("L"));

		if (m_bDrawGrid)
		{
			AxisPen.setWidth(1);
			painter.setPen(AxisPen);
			for (int gridAIndex = 0; gridAIndex < totalScaleCount_AxiL; gridAIndex++)
			{
				QPoint GridStartPoint(intervalStartPt_AxiL.x(), intervalStartPt_AxiL.y() - scaleInterval_AxiL * gridAIndex);
				QPoint GridEndPoint = GridStartPoint + QPoint(DrawAreaSquare.width(), 0);
				painter.drawLine(GridStartPoint, GridEndPoint);
			}
		}

	}
	
	{
		QPoint intervalStartPt_AxiR = BottomAxisRect.topLeft() + QPoint(0, 1);
		int    startR = m_AxiStartPos.R;
		int    endR = m_AxiEndPos.R;
		int    totalScaleCount_AxiR = (double)(endR - startR) / (double)m_GridDensity.Radius + 1;
		double scaleInterval_AxiR = (double)DrawAreaSquare.width() / (double)(totalScaleCount_AxiR - 1);
		double ValInterval_AxiR = (double)(endR - startR) / (double)(totalScaleCount_AxiR - 1);

		if (m_bDrawAxis)
		{
			for (int scaleIndex = 0; scaleIndex < totalScaleCount_AxiR; scaleIndex++)
			{
				QString ValStr = QString::number((double)startR + ValInterval_AxiR * scaleIndex, 'f', 1) + QString(" ");
				QPoint scaleStartPt = QPoint(intervalStartPt_AxiR.x() + scaleInterval_AxiR * scaleIndex, intervalStartPt_AxiR.y());
				QPoint scaleEndPt = scaleStartPt + QPoint(0, m_nAxiesScaleLength);

				//painter.setPen(AxisPen);
				painter.drawLine(scaleStartPt, scaleEndPt);

				QRectF boundingRect = painter.boundingRect(BottomAxisRect, ValStr);
				boundingRect.moveCenter(QPointF(scaleStartPt.x(), 0));
				boundingRect.moveTop(scaleEndPt.y() + m_nAxiesValStrMargin);

				painter.drawText(boundingRect, Qt::AlignCenter, ValStr);
			}
		}
		BottomAxisRect.setWidth(DrawAreaSquare.width());
		BottomAxisRect.moveCenter(BottomAxisRect.center() + QPoint(0, 10));
		painter.drawText(BottomAxisRect, Qt::AlignCenter, QString("R"));

		if (m_bDrawGrid)
		{
			for (int gridBIndex = 0; gridBIndex < totalScaleCount_AxiR; gridBIndex++)
			{
				QPoint scaleStartPt = QPoint(intervalStartPt_AxiR.x() + scaleInterval_AxiR * gridBIndex, intervalStartPt_AxiR.y());
				QPoint scaleEndPt = scaleStartPt - QPoint(0, DrawAreaSquare.height());
				painter.drawLine(scaleStartPt, scaleEndPt);
			}
		}

	}	
}

void Cht_LABColorDistribute::getMousePosInfo(const QPoint mousePos, ST_ChtLab_MousePosLabInfo& posInfo)
{
	QRect  DrawArea = getMaxDrawAreaSquare();

	posInfo.PosValid = DrawArea.contains(mousePos);
	posInfo.SRgbValid = false;

	if (posInfo.PosValid)
	{
		posInfo.MouseLab = getPointLAB(mousePos);
		ColorMetrics::instance()->LabD65ToXYZ(posInfo.MouseLab, posInfo.MouseXYZ);

		if (m_bGammaExist)
		{
			ColorMetrics::instance()->XYZTosRgb(posInfo.MouseXYZ, posInfo.MouseGammaSRgb);
			ColorMetrics::instance()->GammaSRGBToSRgb(posInfo.MouseGammaSRgb, posInfo.MouseSRgb);
			posInfo.SRgbValid = ColorMetrics::instance()->checkSRgbValid(posInfo.MouseSRgb);
			if (posInfo.SRgbValid)
			{
				ColorMetrics::instance()->sRgbToQColor(posInfo.MouseSRgb, posInfo.MouseCr);
			}
		}
		else
		{
			ColorMetrics::instance()->XYZTosRgb(posInfo.MouseXYZ, posInfo.MouseSRgb);
			posInfo.SRgbValid = ColorMetrics::instance()->checkSRgbValid(posInfo.MouseSRgb);
			if (posInfo.SRgbValid)
			{
				ColorMetrics::instance()->sRgbToQColor(posInfo.MouseSRgb, posInfo.MouseCr);
			}
		}

	}
}

QRect Cht_LABColorDistribute::getDrawAreaRect()
{
	QRect		thisRect = this->rect();
	QPoint		drawAreaStartPt = QPoint(m_nLeftAxisWidth, m_nTopTitleHeight);
	QPoint		drawAreaEndPt = QPoint(thisRect.width() - m_nRightColorMapRegionWidth, thisRect.height() - m_nBottomAxisHeight);
	QRect		drawAreaRect = QRect(drawAreaStartPt, drawAreaEndPt);
	return		drawAreaRect;
}

QRect Cht_LABColorDistribute::getBottomAxisRect()
{
	QRect  drawAreaRect = getDrawAreaRect();
	QRect  BottomAxisRect = QRect(drawAreaRect.bottomLeft(), QPoint(drawAreaRect.bottomRight().x(), this->rect().height()));
	return BottomAxisRect;
}

QRect Cht_LABColorDistribute::getMaxDrawAreaSquare()
{
	QRect drawAreaRect		= getDrawAreaRect();
	int   MaxSquareWidth	= qMin(drawAreaRect.width(), drawAreaRect.height());
	QRect MaxDrawAreaRect	= QRect(drawAreaRect.topLeft(), QSize(MaxSquareWidth, MaxSquareWidth));
	return MaxDrawAreaRect;
}

ST_LABPoint Cht_LABColorDistribute::getPointLAB(QPoint pos)
{
	QRect	DrawAreaSquare = getMaxDrawAreaSquare();

	ST_LABPoint resultPt;
	resultPt.L = -1;

	if (!DrawAreaSquare.contains(pos))
	{
		return resultPt;
	}

	switch (m_AxiType)
	{
		case EN_LabCht_AxiType::Fix_L_Axi_Euclid:
		{
			QPoint ArrowFromOriginPt = pos - DrawAreaSquare.bottomLeft();
			double APerPixel = (double)(m_AxiEndPos.A - m_AxiStartPos.A) / (double)DrawAreaSquare.width();
			double BPerPixel = (double)(m_AxiEndPos.B - m_AxiStartPos.B) / (double)DrawAreaSquare.height();
			resultPt.L = m_AxiStartPos.L;
			resultPt.A = m_AxiStartPos.A + APerPixel * abs(ArrowFromOriginPt.x());
			resultPt.B = m_AxiStartPos.B + BPerPixel * abs(ArrowFromOriginPt.y());
		}break;
		case EN_LabCht_AxiType::Fix_AB_Axi_Euclid:
		{
			QPoint ArrowFromOriginPt = pos - DrawAreaSquare.bottomLeft();
			double RPerPixel = (double)(m_AxiEndPos.R - m_AxiStartPos.R) / (double)DrawAreaSquare.width();
			double LPerPixel = (double)(m_AxiEndPos.L - m_AxiStartPos.L) / (double)DrawAreaSquare.height();
			resultPt.L = m_AxiStartPos.L + LPerPixel * abs(ArrowFromOriginPt.y());

			double RFormStartAB = ArrowFromOriginPt.x() * RPerPixel;
			double ABArrowLength = sqrt(pow(m_AxiStartPos.A, 2) + pow(m_AxiStartPos.B, 2));
			QPointF unitABArrow(abs((double)m_AxiStartPos.A) / ABArrowLength, abs((double)m_AxiStartPos.B / ABArrowLength));
			double startA = unitABArrow.x() * m_AxiStartPos.R;
			double startB = unitABArrow.y() * m_AxiStartPos.R;
			resultPt.A = startA + unitABArrow.x() * RFormStartAB;
			resultPt.B = startB + unitABArrow.y() * RFormStartAB;
		}break;
	}
	return resultPt;
}

void Cht_LABColorDistribute::getLabPos(const ST_LABPoint& LABVal, QPoint& resultPt)
{
	resultPt = QPoint(-1,-1);
	QRect	DrawAreaSquare = getMaxDrawAreaSquare();
	switch (m_AxiType)
	{
		case EN_LabCht_AxiType::Fix_L_Axi_Euclid:
		{
			if (LABVal.L != m_AxiStartPos.L)
			{
				return;
			}

			if (LABVal.A < m_AxiStartPos.A || LABVal.A > m_AxiEndPos.A)
			{
				return;
			}

			if (LABVal.B < m_AxiStartPos.B || LABVal.B > m_AxiEndPos.B)
			{
				return;
			}

			if (LABVal.A == 10 && LABVal.B == 10)
			{
				int a = 0;
			}

			double AFromOrigin = LABVal.A - m_AxiStartPos.A;
			double BFromOrigin = LABVal.B - m_AxiStartPos.B;

			double APerPixel = (double)(m_AxiEndPos.A - m_AxiStartPos.A) / (double)DrawAreaSquare.width();
			double BPerPixel = (double)(m_AxiEndPos.B - m_AxiStartPos.B) / (double)DrawAreaSquare.height();

			QPoint originPt = DrawAreaSquare.bottomLeft();
		
			resultPt.rx() = originPt.x() + AFromOrigin / APerPixel;
			resultPt.ry() = originPt.y() - BFromOrigin / BPerPixel;


		}break;
		case EN_LabCht_AxiType::Fix_AB_Axi_Euclid: //这个只能显示投影 不能没法检错
		{
			double LFromOrigin = LABVal.L - m_AxiStartPos.L;
			QPoint originPt = DrawAreaSquare.bottomLeft();
			double LPerPixel = (m_AxiEndPos.L - m_AxiStartPos.L) / (double)DrawAreaSquare.height();
			resultPt.ry() = originPt.y() - LFromOrigin / LPerPixel;

			double ABArrowLength = sqrt(pow(m_AxiStartPos.A, 2) + pow(m_AxiStartPos.B, 2));
			QPointF unitABArrow(abs((double)m_AxiStartPos.A) / ABArrowLength, abs((double)m_AxiStartPos.B / ABArrowLength));
			QPointF StartRArrow(unitABArrow.x() * m_AxiStartPos.R, unitABArrow.y() * m_AxiStartPos.R);
		
			double relvanceA = LABVal.A - StartRArrow.x();
			double relvanceB = LABVal.B - StartRArrow.y();

			double projection_R = relvanceA * unitABArrow.x() + relvanceB * unitABArrow.y();
		
			double RPerPixel = (double)(m_AxiEndPos.R - m_AxiStartPos.R) / (double)DrawAreaSquare.width();
			resultPt.rx() = originPt.x() + projection_R / RPerPixel;

		}break;
	}

}

void Cht_LABColorDistribute::resetCrRectVec_Fix_L_Euclid()
{
	int startA = m_AxiStartPos.A;
	int endA = m_AxiEndPos.A;
	int startB = m_AxiStartPos.B;
	int endB = m_AxiEndPos.B;

	int Col_A_Count = (endA - startA) / m_CrDensity.AB;
	int Row_B_Count = (endB - startB) / m_CrDensity.AB;

	ST_LabCht_CrRect nullCrRect;
	QVector<ST_LabCht_CrRect> nullRow(Col_A_Count, nullCrRect);
	m_vecCrRect.clear();
	m_vecCrRect = QVector<QVector<ST_LabCht_CrRect>>(Row_B_Count, nullRow);

	int hundredsOfRow = qMax(Col_A_Count / 100, 1);

	m_nCaculateRectCount = Col_A_Count * Row_B_Count;
	m_nValidRectCount = 0;

	for (int rowIndex = 0; rowIndex < Row_B_Count; rowIndex++)
	{
		double currentB = rowIndex * m_CrDensity.AB + startB + m_CrDensity.AB / 2;
		for (int colIndex = 0; colIndex < Col_A_Count; colIndex++)
		{
			double currentA = colIndex * m_CrDensity.AB + startA + m_CrDensity.AB / 2;

			ST_LabCht_CrRect& ChtRectRef = m_vecCrRect[rowIndex][colIndex];

			ST_LABPoint& LabPtRef = ChtRectRef.LaBPt;

			LabPtRef.L = m_AxiStartPos.L;
			LabPtRef.A = currentA;
			LabPtRef.B = currentB;

			QRect& drawRectRef = ChtRectRef.drawRect;
			drawRectRef.setSize(QSize(m_nCrRectWidth, m_nCrRectWidth));

			QPoint RectCenter;
			getLabPos(LabPtRef, RectCenter);
			drawRectRef.moveCenter(RectCenter);

			QColor& ptCr = m_vecCrRect[rowIndex][colIndex].QCr;
			bool& CrValid = ChtRectRef.CrValid;

			CrValid = ColorMetrics::instance()->LabD65ToQRgb(LabPtRef, ptCr, m_bGammaExist);

			if (CrValid)
			{
				m_nValidRectCount += 1;
			}

		}

		if (rowIndex % hundredsOfRow == 0)
		{
			emit sgn_CrRectGenState(rowIndex / Col_A_Count, 1, QString("%1 / %2").arg(rowIndex).arg(Col_A_Count));
		}

	}

	emit sgn_CrRectGenState(100, 0, QString(""));
	
}

void Cht_LABColorDistribute::resetCrRectVec_Fix_AB_Euclid()
{
	int startR = m_AxiStartPos.R;
	int endR = m_AxiEndPos.R;
	int startL = m_AxiStartPos.L;
	int endL = m_AxiEndPos.L;

	int Col_R_Count = (endR - startR) / m_CrDensity.Radius;
	int Row_L_Count = (endL - startL) / m_CrDensity.L;

	ST_LabCht_CrRect nullCrRect;
	QVector<ST_LabCht_CrRect> nullRow(Col_R_Count, nullCrRect);
	m_vecCrRect.clear();
	m_vecCrRect = QVector<QVector<ST_LabCht_CrRect>>(Row_L_Count, nullRow);

	double ABArrowLength = sqrt(pow(m_AxiStartPos.A, 2) + pow(m_AxiStartPos.B, 2));
	QPointF unitABArrow(abs((double)m_AxiStartPos.A) / ABArrowLength, abs((double)m_AxiStartPos.B / ABArrowLength));

	double StartA = startR * unitABArrow.x();
	double StartB = startR * unitABArrow.y();

	int hundredsOfRow = qMax(Col_R_Count / 100, 1);

	m_nCaculateRectCount = Col_R_Count * Row_L_Count;
	m_nValidRectCount = 0;

	for (int rowIndex = 0; rowIndex < Row_L_Count; rowIndex++)
	{
		double currentL = rowIndex * m_CrDensity.L + startL + m_CrDensity.L / 2;
		for (int colIndex = 0; colIndex < Col_R_Count; colIndex++)
		{
			double currentR = colIndex * m_CrDensity.Radius + startR + m_CrDensity.Radius / 2;

			ST_LabCht_CrRect& ChtRectRef = m_vecCrRect[rowIndex][colIndex];

			ST_LABPoint& LabPtRef = ChtRectRef.LaBPt;

			LabPtRef.L = currentL;
			LabPtRef.A = currentR * unitABArrow.x();
			LabPtRef.B = currentR * unitABArrow.y();

			QRect& drawRectRef = ChtRectRef.drawRect;
			drawRectRef.setSize(QSize(m_nCrRectWidth, m_nCrRectWidth));

			QColor& ptCr = m_vecCrRect[rowIndex][colIndex].QCr;
			bool& CrValid = ChtRectRef.CrValid;

			CrValid = ColorMetrics::instance()->LabD65ToQRgb(LabPtRef, ptCr, m_bGammaExist);

			QPoint RectCenter;
			getLabPos(LabPtRef, RectCenter);
			drawRectRef.moveCenter(RectCenter);

			if (CrValid)
			{
				m_nValidRectCount += 1;
			}

		}

		if (rowIndex % hundredsOfRow == 0)
		{
			emit sgn_CrRectGenState(rowIndex / Col_R_Count, 1, QString("%1 / %2").arg(rowIndex).arg(Col_R_Count));
		}

	}

	emit sgn_CrRectGenState(100, 0, QString(""));

}

void Cht_LABColorDistribute::resetCrRectVec_Pixel()
{
	QRect	DrawAreaSquare = getMaxDrawAreaSquare();

	int startX = DrawAreaSquare.left() + 1;
	int endX = DrawAreaSquare.right() - 1;
	int startY = DrawAreaSquare.bottom() - 1;
	int endY = DrawAreaSquare.top() + 1;

	int Col_X_Count = endX - startX + 1;
	int Row_Y_Count = startY - endY + 1;

	m_nCaculateRectCount = Col_X_Count * Row_Y_Count;
	m_nValidRectCount = 0;

	ST_LabCht_CrRect nullCrRect;
	nullCrRect.drawRect.setSize(QSize(1, 1));
	QVector<ST_LabCht_CrRect> nullRow(Col_X_Count, nullCrRect);
	m_vecCrRect.clear();
	m_vecCrRect = QVector<QVector<ST_LabCht_CrRect>>(Row_Y_Count, nullRow);

	m_CrPixelImg = QImage(QSize(Col_X_Count + 1, Row_Y_Count + 1), QImage::Format_ARGB32);
	m_CrPixelImg.fill(QColor(0, 0, 0, 0));

	ST_LabCht_CrRectGenCmd DefaultCmd;
	DefaultCmd.pCht = this;
	m_vecCrRectGenCmd.clear();
	m_vecCrRectGenCmd = QVector<ST_LabCht_CrRectGenCmd>(Row_Y_Count, DefaultCmd);

	for (int CmdIndex = 0; CmdIndex < Row_Y_Count; CmdIndex++)
	{
		m_vecCrRectGenCmd[CmdIndex].RowIndex = CmdIndex;
	}

	QFuture<void> future = QtConcurrent::map(m_vecCrRectGenCmd, Cht_LABColorDistribute::OperateGenCmd);
	m_pConcurrentWatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);
}

void Cht_LABColorDistribute::AddValidCrCount(const int addNum)
{
	m_mutex.lock();
	m_nValidRectCount += addNum;
	m_mutex.unlock();
}

void Cht_LABColorDistribute::OperateGenCmd(const ST_LabCht_CrRectGenCmd& GenCmd)
{
	GenCmd.pCht->slot_fillTargetRow(GenCmd.RowIndex);
}


void Cht_LABColorDistribute::slot_fillTargetRow(int rowIndex)
{
	QRect		DrawAreaSquare = getMaxDrawAreaSquare();

			int	startX		= DrawAreaSquare.left() + 1;
			int startY		= DrawAreaSquare.bottom() - 1;
	const	int	currentY	= startY - rowIndex;
	const   int totalY		= m_vecCrRect.size();

	QVector<ST_LabCht_CrRect>& rowVecRef = m_vecCrRect[rowIndex];
	int		colCount = rowVecRef.size();

	int ValidCrCount = 0;

	for (int currentCol = 0; currentCol < colCount; currentCol++)
	{
		int currentX = startX + currentCol;

		QPoint currentPixel(currentX, currentY);
		ST_LabCht_CrRect& ChtRectRef = rowVecRef[currentCol];
		ChtRectRef.drawRect.moveCenter(currentPixel);
		ST_LABPoint& LabPtRef = ChtRectRef.LaBPt;
		LabPtRef = getPointLAB(currentPixel);

		QColor& ptCr = ChtRectRef.QCr;
		bool& CrValid = ChtRectRef.CrValid;

		CrValid = ColorMetrics::instance()->LabD65ToQRgb(LabPtRef, ptCr, m_bGammaExist);
		if (CrValid)
		{
			ptCr.setAlpha(255);
		}
		else
		{
			ptCr.setAlpha(0);
		}

		int y1 = currentY - (DrawAreaSquare.top() - 1);
		int y2 = DrawAreaSquare.bottom() - 1 - currentY;

		m_CrPixelImg.setPixelColor(QPoint(currentCol, y1), ptCr.rgba());

		if (CrValid)
		{
			ValidCrCount += 1;
		}

	}

	AddValidCrCount(ValidCrCount);
	//qDebug() << "Cht_LABColorDistribute::slot_fillTargetRow row Index : " << rowIndex;

}

void Cht_LABColorDistribute::slot_GenFinished()
{
	m_bOnGenrate = false;
	update();
}

void Cht_LABColorDistribute::slot_GenProgressValueChanged(int val)
{
	if (m_vecCrRect.isEmpty())
	{
		qDebug() << "Cht_LABColorDistribute::slot_GenProgressValueChanged RectVec empty!";
		return;
	}

	int RowCount = m_vecCrRect.size();
	int hunderdsOfRow = qMax(1, RowCount / 100);
	int processedCount = val;
	int percentage = (double)processedCount / (double)RowCount * 100; ;
	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_CrRectGenState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(RowCount));;
		m_nLastReportPercantage = percentage;
	}
	qDebug() << QString("Cht_LABColorDistribute::slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(RowCount);
	if (processedCount == RowCount)
	{
		slot_GenFinished();
	}
}
