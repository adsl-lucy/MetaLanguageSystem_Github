#pragma once
#include "../TimeSecCht_Painter.h"
#include "../../Perception/BandWidthFilter/BandWidthFilterManager.h"

class TimeSecCht_Painter_BDSNR : public TimeSecCht_Painter
{
	Q_OBJECT
public:
	TimeSecCht_Painter_BDSNR(QObject* parent);

	void resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para) override;

public:signals:
	void sgn_GenFinished();

protected:

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

	struct ST_BandWidthFilterActiveRect
	{
		QRect FilterPosRect;
		int   FilterIndex = -1;
		bool  isFilterActive = false;
	};

	bool  hasBandWidthFilterRect() override { return true; };
	void  GenBasicFilterRect(const QVector<ST_BandWidthFilter>& FilterVec, QVector<ST_BandWidthFilterActiveRect>& MFCCActiveVec, QVector<ST_FFTFreqBar>& MFCCFreqBarVec);
	bool  generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& FrameData) override;

	void drawValueArea(QPainter& painter, QRect& drawArea) override;
	void drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea) override;
	void drawMousePosValue(QPainter& painter, QRect& drawArea) override;
	void drawLengend(QPainter& painter, QRect& RightColorMapRect) override;
	void drawActiveRectValue(QPainter& painter) override;

	int   MousePosToMFCCFilterRectIndex(QPoint mousePos);

protected slots:
	void slot_GenFinished();
	void slot_GenProgressValueChanged(int val);
private:

	int m_nFilterRectHeight = 12;
	ST_BandWidthFilterData m_drawFilterData;
	QVector<QVector<ST_BandWidthFilterActiveRect>> m_vecDrawBandWidthFilterRect;

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_STFT;

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_Noise;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_Constrain;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_EffectPt_Main;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_EffectPt_Sub;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_ActiveFilter_Main;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_ActiveFilter_Sub;

	int				  m_nLastReportPercantage = -1;
	QVector<ST_SecChtThreadProcessData>	  m_currentProcessVec;
	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;

};