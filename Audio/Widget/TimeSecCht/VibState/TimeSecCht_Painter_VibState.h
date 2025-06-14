#pragma once
#include "../TimeSecCht_Painter.h"
#include "../../Cognition/VibrateStateRelvanceNetwork/VibrateStateRelvanceNetwork.h"

class TimeSecCht_Painter_VibState: public TimeSecCht_Painter
{
	Q_OBJECT
public:
	TimeSecCht_Painter_VibState(QObject* parent);

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
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_Atk;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_Increase;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_Sustain;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_Decrease;

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_transfer_NotTransfer;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_transfer_Atk;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_transfer_Increase;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_transfer_Sustain;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_transfer_Decrease;



	int				  m_nLastReportPercantage = -1;
	QVector<ST_SecChtThreadProcessData>	  m_currentProcessVec;
	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;

};