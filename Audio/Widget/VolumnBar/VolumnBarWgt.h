#pragma once
#include <QWidget>
#include <QPainter>

class VolumnBarWgt :    public QWidget
{
	Q_OBJECT
public:
	VolumnBarWgt(QWidget* parent);
	~VolumnBarWgt();

	void setMaxMin(double max, double  min);
	void setVal(double  val);

protected:
	void	paintEvent(QPaintEvent* event);
	int		getExistBlock(double  val);
	int     getValueHeight(double val);

private:
	QColor m_crGradientStart	= Qt::green;
	QColor m_crGradientMid		= Qt::yellow;
	QColor m_crGradientEnd		= Qt::red;

	int m_nBlockCount = 16;
	double  m_nCurrentVal	= -40;
	double  m_nMaxVal		= 0;
	double  m_nMinVal		= -80;

};

