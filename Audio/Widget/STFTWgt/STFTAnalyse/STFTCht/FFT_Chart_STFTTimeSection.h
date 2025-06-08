#pragma once

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QFont>
#include <QTime>
#include <QFontDatabase>
#include <QLinearGradient>
#include <qDebug>
#include <QMouseEvent>
#include <QtConcurrent>
#include <QThreadPool>
#include <QFutureWatcher>

#include "../../protocol/protocol_audio.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

//图显示的内容类型
enum class EN_TimeSecType : int
{
	Amp,	//强度
	Phase	//相位
};

//FFT时域截面的图
class FFT_Chart_STFTTimeSection :  public QWidget
{
	Q_OBJECT
public:

	FFT_Chart_STFTTimeSection(QWidget* parent);
	~FFT_Chart_STFTTimeSection();

	void setTitleText(QString titleStr) { m_strTitle = titleStr; }
	void setChtType(EN_TimeSecType Type);


	//输入值频谱的最大值固定为1（归一化后的PCM），其对应DB默认为80
	void setSTFTResultPara(const ST_STFTInputpara& para);

	void setDrawFreqRanged(int startFreq, int endFreq);
	void setDrawDBRange(double min, double max);
	void setFreqBarBandWidth(int hzPerBar);

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
	void drawValueArea(QPainter& painter, QRect& drawArea);
	void drawMousePosValue(QPainter& painter, QRect& drawArea);

	QRect getDrawAreaRect();
	

	struct ST_FreqBar
	{
		int startFreq = 0;
		int bandWidth = 0;
		int InCountFFTPt = 0;
		double maxVal = 0;
		double minVal = 0;
		QRect BarRect;
	};

	int   FreqToPosX(double freq);
	int   PosXToFreq(int posX);
	int   getDbHeight(const double val);
	double PosYToDb(int posY);

	int    getPhaseHeight(const double val);
	double posYToPhase(int posY);
	
	bool  generateFreqBarVec(const int BarVecIndex,const ST_FFTOutputData& FrameData);
	QRect getFreqBarRect(int startFreq,int bandWidth,double RectMaxVal);

	struct ST_SecChtThreadProcessData
	{
		FFT_Chart_STFTTimeSection* pCht = nullptr;
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
	EN_TimeSecType m_showDataType = EN_TimeSecType::Amp;

	QString			  m_currentSTFTDataKey;
	int				  m_nLastReportPercantage = -1;
	QVector<ST_SecChtThreadProcessData>	  m_currentProcessVec;
	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;

	int m_nLeftAxisWidth = 80;
	int m_nBottomAxisWidth = 30;
	int m_nTopTitleHeight = 30;
	int m_nRightColorMapRegionWidth = 140;

	QString m_strTitle = "STFT Time Section Amplitude";
	QFont	m_ft_titleFont;
	QColor  m_crTitle = Qt::black;
	QColor  m_crAxis = Qt::black;

	int		m_nAxiesScaleLength = 5;
	int     m_nAxiesValStrMargin = 5;
	int     m_nAxiesValStrFontSize = 15;

	int		m_nColorMapWidth = 25;

	int		m_nMinFreq = 0;
	int		m_nMaxFreq = 20000;

	double  m_dMinDB = -20;
	double  m_dMaxDB = 80;

	double  m_dMaxPhase = const_audio_pi * 2;
	double  m_dMinPhase = 0;

	int		m_nFreqScaleIntervalCount	= 10;	//频率刻度尺画几个间隔
	int     m_nDBScaleIntervalCount		= 10;  //值刻度尺话几个间隔

	int		m_ndrawFrameIndex = -1;
	int		m_nFreqBarBandWidth = 100;//一个频率条的带宽
	int     m_nBarInterval = 0;

	ST_STFTInputpara	m_STFTPara;
	QVector<QVector<ST_FreqBar>> m_vecFrameBar;
	//ST_STFTOutputData m_drawData;	//数据太大了，存不下，放在外面

	bool m_bMouseInDrawArea = false;
	QPoint m_ptMousePos;

	

};

