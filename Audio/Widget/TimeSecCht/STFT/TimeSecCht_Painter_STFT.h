#pragma once
#include "../TimeSecCht_Painter.h"

class TimeSecCht_Painter_STFT : public TimeSecCht_Painter
{
	Q_OBJECT
public:
	TimeSecCht_Painter_STFT(QObject* parent);

	void resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para) override;

public:signals:
	void sgn_GenFinished();

protected:
	bool  generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& FrameData) override;

	void drawValueArea(QPainter& painter, QRect& drawArea) override;
	void drawMousePosValue(QPainter& painter, QRect& drawArea) override;
	void drawLengend(QPainter& painter, QRect& RightColorMapRect) override;

protected slots:
	void slot_GenFinished();
	void slot_GenProgressValueChanged(int val);
private:

	struct ST_FFTFreqBar
	{
		double	centerFreq = 0;
		//int	bandWidth	= 0; //这个用图表内的公共数值

		int		FFTPtIndex = 0;
		double  doubleVal = 0;
		double  DBVal = 0;
		QRect	BarRect;

		int		FilterIndex = -1;
		int		FilterBandWidth = 0;

	};

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_STFT;	
	int				  m_nLastReportPercantage = -1;
	QVector<ST_SecChtThreadProcessData>	  m_currentProcessVec;
	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;

};

