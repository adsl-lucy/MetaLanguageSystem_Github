#pragma once
#include <QWidget>
#include <QPainter>
#include <QString>
#include <QFont>
#include <QTime>
#include <QFontDatabase>
#include <qDebug>
#include <QMouseEvent>
#include <QtConcurrent>
#include <QThreadPool>
#include <QFutureWatcher>

#include "../../protocol/protocol_audio.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "../../Perception/WndSpecConstrainNetwork/WndSpecConstrainNetwork.h"
#include "../../Perception/BandWidthFilter/BandWidthFilterManager.h"
#include "../../Cognition/FreqDoubleRelevanceNetWork/FreqDoubleNetwork.h"

enum class EN_FreqDoub_TimeSecChtBarType :int
{
	STFT,
	EffectiveOscillation,
	BDSNR,
	DiffGroup,
	FreqDoub
};

class TimeSecCht_FreqDoub :  public QWidget
{
	Q_OBJECT
public:
	TimeSecCht_FreqDoub(QWidget* parent);
	~TimeSecCht_FreqDoub();

	void setTitleText(QString titleStr) { m_strTitle = titleStr; }
	void setChtType(EN_FreqDoub_TimeSecChtBarType Type);
	void setNoisePaintSetting(bool TIQLine, bool UnderTIQBar, bool WndSepcNoise, bool BDSNR_Noise, bool BDSNR_Constrain, bool BDSNR_ActiveFilter,bool FreqDoubChild);


	//输入值频谱的最大值固定为1（归一化后的PCM），其对应DB默认为80
	void setSTFTResultPara(const ST_STFTInputpara& para);

	void setDrawFreqRanged(int startFreq, int endFreq);
	void setDrawDBRange(double min, double max);
	//void setFreqBarBandWidth(int hzPerBar);

	void setCurrentFrameIndex(int index);
	void resetFrameRect(QString dataKey);

public:signals:
	void sgn_windowHide();

protected:
	void init();

	void mouseMoveEvent(QMouseEvent* event);
	void leaveEvent(QEvent* event);
	void hideEvent(QHideEvent* event);
	void paintEvent(QPaintEvent* event);
	void drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect);
	void drawTitle(QPainter& painter, QRect& TopAxisRect);
	void drawValueAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis);
	void drawFreqAxis(QPainter& painter, QRect& BottomAxisArea);
	void drawThreshHoldInQuiet(QPainter& painter, QRect& drawArea);

	void drawValueArea_STFT(QPainter& painter, QRect& drawArea);
	void drawValueArea_EffectiveOsc(QPainter& painter, QRect& drawArea);
	void drawValueArea_BDSNR(QPainter& painter, QRect& drawArea);
	void drawValueArea_Diff(QPainter& painter, QRect& drawArea);
	void drawValueArea_FreqDoub(QPainter& painter, QRect& drawArea);
	void drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea);

	void drawMousePosValue(QPainter& painter, QRect& drawArea);
	void drawActiveRectValue(QPainter& painter);
	void drawLengend(QPainter& painter, QRect& RightColorMapRect);
	void drawPtCount(QPainter& painter, QRect& RightColorMapRect);
	QRect getDrawAreaRect();
	QRect getBottomAxisRect();


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

		int     matrixIndex = 0;


	};

	struct ST_BandWidthFilterActiveRect
	{
		QRect FilterPosRect;
		int   FilterIndex = -1;
		bool  isFilterActive = false;
	};


	int   FreqToPosX(double freq);
	int   PosXToFreq(int posX);
	int   getDbHeight(const double val);
	double PosYToDb(int posY);
	int   MousePosToMFCCFilterRectIndex(QPoint mousePos);

	void  ResetDiffGroupColorMap(int DiffGroupCount);
	void  GenBasicFilterRect(const QVector<ST_BandWidthFilter>& FilterVec, QVector<ST_BandWidthFilterActiveRect>& MFCCActiveVec, QVector<ST_FFTFreqBar>& MFCCFreqBarVec);
	bool  generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& FrameData);
	QRect getFreqBarRect(int startFreq, int bandWidth, double RectMaxVal);

	struct ST_SecChtThreadProcessData
	{
		TimeSecCht_FreqDoub* pCht = nullptr;
		QString dataKey;
		int frameIndex = -1;
	};

	static void FillTargetFrame(const ST_SecChtThreadProcessData data);
public:signals:
	void sgn_SecRectGenerateState(int percentage, int activateThreadCount, QString errstr);
protected:
	void slot_GenFinished();
	void slot_GenProgressValueChanged(int val);

private:
	EN_FreqDoub_TimeSecChtBarType m_showDataType = EN_FreqDoub_TimeSecChtBarType::STFT;

	QString			  m_currentSTFTDataKey;
	int				  m_nLastReportPercantage = -1;
	QVector<ST_SecChtThreadProcessData>	  m_currentProcessVec;
	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;

	int m_nLeftAxisWidth = 80;
	int m_nBottomAxisHeight = 60;
	int m_nTopTitleHeight = 30;
	int m_nRightColorMapRegionWidth = 140;

	QString m_strTitle = "Effective Oscillation Time Section Cht";
	QFont	m_ft_titleFont;
	QColor  m_crTitle = Qt::black;
	QColor  m_crAxis = Qt::black;

	int		m_nAxiesScaleLength = 5;
	int     m_nAxiesValStrMargin = 5;
	int     m_nAxiesValStrFontSize = 15;

	int		m_nColorMapWidth = 25;

	int		m_nMinFreq = 0;
	int		m_nMaxFreq = 20000;

	double  m_dMinDB = 0;
	double  m_dMaxDB = 80;

	int		m_nFreqScaleIntervalCount = 10;	//频率刻度尺画几个间隔
	int     m_nDBScaleIntervalCount = 10;  //值刻度尺话几个间隔

	int		m_ndrawFrameIndex = -1;
	double	m_dFreqBarBandWidth = 10.77;//一个频率条的带宽  这里都是一个STFT点算一根，因为状态没法相容了
	int     m_nBarInterval = 0;
	ST_STFTInputpara	m_STFTPara;

	bool m_bDrawTIQLine = false;
	bool m_bDrawWndSpecNoise = false;
	bool m_bDrawUnderTIQBar = false;
	bool m_bDraw_BDSNR_Noise = false;
	bool m_bDraw_BDSNR_ConstrainPt = false;
	bool m_bDraw_BDSNR_ActiveFilter = false;
	bool m_bDraw_Diff_Disappear = false;
	bool m_bDraw_Diff_Filter = false;
	bool m_bDraw_FreqDoub_Child= false;

	int m_nFilterRectHeight = 12;
	ST_BandWidthFilterData m_drawFilterData;
	QVector<QVector<ST_BandWidthFilterActiveRect>> m_vecDrawBandWidthFilterRect;

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_STFT;

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_UnderTIQ;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_WndSpecNoise;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_EffectiveOscillation;

	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_Noise;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_Constrain;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_EffectPt;
	QVector<QVector<ST_FFTFreqBar>> m_vecFrameBar_BDSNR_ActiveFilter;

	QVector<QVector<ST_FFTFreqBar>>				m_vecFrameBar_Diff_DisAppearGroup;
	QVector<QVector<ST_FFTFreqBar>>				m_vecFrameBar_Diff_SuddenAppearGroup;
	QVector<QMap<int, QVector<ST_FFTFreqBar>>>  m_vecFrameBar_Diff_SideGroupMap;

	QVector<QVector<ST_FFTFreqBar>>				m_vecFrameBar_FreqDoub_ActiveParentMatrix;
	QVector<QVector<ST_FFTFreqBar>>				m_vecFrameBar_FreqDoub_ActiveChildMatrix;

	bool m_bMouseInDrawArea = false;
	bool m_bMouseInFilterActiveArea = false;
	QPoint m_ptMousePos;
	QPoint m_ptMousePos_ActiveMFCCRect;

	QFont	m_ft_LegendFont;
	int    m_nLegendFontSize = 12;
	QSize  m_szLegend = QSize(8, 8);
	int    m_nLegendLeftMargin = 16;
	int    m_nLegendTopMargin = 16;
	int    m_nLegendTextMargin = 8;
	int    m_nLegendSpacing = 16;

	QColor m_crSTFTOnlyBar = Qt::blue;

	QColor m_cr_EffOsc_UnderTIQBar = Qt::darkGray;
	QColor m_cr_EffOsc_WndSpecNoiseBar = Qt::gray;
	QColor m_cr_EffOsc_EffectiveOscillationBar = Qt::green;

	QColor m_cr_BDSNR_Noise = Qt::darkGray;
	QColor m_cr_BDSNR_Signal_Constrain = Qt::magenta;
	QColor m_cr_BDSNR_Signal_Effective = Qt::cyan;
	QColor m_cr_BDSNR_ConstrainFilter_InActive = Qt::gray;
	QColor m_cr_BDSNR_ConstrainFilter_Active = Qt::green;

	QColor m_cr_Diff_DisappearGroup = Qt::gray;
	QColor m_cr_Diff_SuddenAppearGroup = Qt::yellow;
	QColor m_cr_Diff_DecreaseSideGroup = Qt::green;
	QColor m_cr_Diff_StableGroup = Qt::blue;
	QColor m_cr_Diff_IncreaseSideGroup = Qt::red;

	QColor m_cr_FreqDoub_ParentMatrix	= Qt::blue;
	QColor m_cr_FreqDoub_ChildMatrix	= Qt::magenta;


	QMap<int, QColor> m_mapSideGroupColor;

	QColor m_crThreshHoldLine = Qt::black;
};

