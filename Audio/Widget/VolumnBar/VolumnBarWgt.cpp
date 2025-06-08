#include "VolumnBarWgt.h"

VolumnBarWgt::VolumnBarWgt(QWidget* parent) :QWidget(parent)
{

}
VolumnBarWgt::~VolumnBarWgt()
{

}

void VolumnBarWgt::setMaxMin(double  max, double  min)
{
	m_nMaxVal = max;
	m_nMinVal = min;
	update();
}

void VolumnBarWgt::setVal(double  val)
{
	m_nCurrentVal = val;
	update();
}

int VolumnBarWgt::getExistBlock(double  val)
{
	if (val >= m_nMaxVal)
	{
		return m_nBlockCount;
	}
	else if (val <= m_nMinVal)
	{
		return 0;
	}

	double interval = abs(m_nMaxVal - m_nMinVal) / (double)m_nBlockCount;
	int count = (val - m_nMinVal) / interval;
	return count;

}

int    VolumnBarWgt::getValueHeight(double val)
{
	int totalHeight = this->rect().height();
	int valueHeight = (abs(val - m_nMinVal) / abs(m_nMaxVal - m_nMinVal)) * (double)totalHeight;
	return valueHeight;
}

void VolumnBarWgt::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QRect thisRect = this->rect();

	QPen pen;
	pen.setColor(Qt::darkGray);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(Qt::black);

	painter.drawRect(thisRect);

	QLinearGradient gradient;
	gradient.setColorAt(0, m_crGradientStart);
	gradient.setColorAt(0.8, m_crGradientMid);
	gradient.setColorAt(1, m_crGradientEnd);

	gradient.setStart(thisRect.bottomLeft());
	gradient.setFinalStop(thisRect.topLeft());

	pen.setColor(Qt::black);
	pen.setWidth(6);

	painter.setPen(pen);
	painter.setBrush(gradient);

	painter.drawRect(thisRect);

	if (true)
	{
		int valueHeight = getValueHeight(m_nCurrentVal);
		int UpBlackHeight = this->rect().height() - valueHeight;
		painter.setPen(pen);
		painter.setBrush(Qt::black);
		QRect topBlackRect = QRect(0, 0, 0, 0);
		topBlackRect.setSize(QSize(thisRect.width(), UpBlackHeight));
		painter.drawRect(topBlackRect);
	}

	if(false)
	{
		pen.setWidth(2);
		painter.setPen(pen);
		painter.setBrush(Qt::NoBrush);

		int intervalY = thisRect.height() / m_nBlockCount;

		for (int i = 1; i <= m_nBlockCount; i++)
		{
			int y = intervalY * i;
			QPoint startPt(0, y);
			QPoint endPt(thisRect.width(), y);
			painter.drawLine(startPt, endPt);

		}

		int existBlockCount = getExistBlock(m_nCurrentVal);

		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::black);

		for (int i = 0; i < m_nBlockCount - existBlockCount; i++)
		{
			int startY = intervalY * i;
			int endY = intervalY * (i + 1);
			QRect blackBlock(QPoint(0, startY), QPoint(thisRect.width(), endY));
			painter.drawRect(blackBlock);
		}
	}
	
}