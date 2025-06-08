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
#include <QImage>
#include <QApplication>

#include "../../protocol/protocol_audio.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

class FFT_Chart_STFTHotGram : public QWidget
{
	Q_OBJECT
public:
	FFT_Chart_STFTHotGram(QWidget* parent);
	~FFT_Chart_STFTHotGram();

	void setTitleText(QString titleStr) { m_strTitle = titleStr; }
	void setSTFTResultPara(const ST_STFTInputpara& para);

	void setFreqRange(int startFreq, int endFreq);	
	void setCurrentTime(QTime currentTime);
	void setTimeRange(QTime startTime, int chtTimeLength);
	void getCurrentTimeRange(QTime& startTime, QTime& endTime);

	void setDbRange(int startDB, int endDb);

	void  setFreqBandWidth(int hz);
	void  setTimeInterval(int msec);

	void setCurrentFrameIndex(int frameIndex);
	void resetColorRect(QString datKey);

protected:
	void init();

	void mouseMoveEvent(QMouseEvent* event);
	void leaveEvent(QEvent* event);
	void paintEvent(QPaintEvent* event);
	void drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect);
	void drawTitle(QPainter& painter, QRect& TopAxisRect);
	void drawColorMap(QPainter& painter, QRect& RightColorMapRect);
	void drawFreqAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis);
	void drawTimeAxis(QPainter& painter, QRect& BottomAxisArea);
	

	void drawValueArea(QPainter& painter, QRect& drawArea);
	void drawCurrentTime(QPainter& painter, QRect& drawArea);
	void drawMousePosValue(QPainter& painter, QRect& drawArea);

	QRect getDrawAreaRect();
	double getValueInPixel(QPoint pt);
	QColor getColorFromDB(double val);

	int PosXToTimeMsec(int posX);
	int MsecToPosX(int Msec);
	int PosYoFreq(int posY);
	int FreqToPosY(int Freq);
	QTime getChtEndTime();

	struct ST_FFTFreqColorRect
	{
		int startFreq			= 0;
		//int FreqBandWidth		= 0;	//这个色块的带宽在下面有计算
		double startMsec		= 0;
		//double MsecInterval		= 0;//这个色块的时长在下面有计算
		double maxDB			= 0;
		double minDB			= 0;
		QColor BarColor;
		int InCountFFTPt = 0;
		QRect  rectFromTime0 = QRect(0,0,0,0);
	};

	void FillSTFTDataIntoFrame(const int TimeFrameIndex, const ST_STFTInputpara& para, const QVector<ST_FFTOutputData>& dataVec);
	
	bool getCrRectInDataVecIndex(double frameStartFreq, double frameStartMsec, const QVector<ST_FFTOutputData>& dataVec,
		int& startTimeFrameIndex, int& endTimeFrameIndex, int& startFreqRectIndex, int& endFreqRectIndex);

	int getTimeIndexInCrVec(int timeMsec);
	int getFreqIndexInCrVec(int Freq);

	struct ST_HotChtThreadProcessData
	{
		FFT_Chart_STFTHotGram* pCht = nullptr;
		QString dataKey;
		int frameIndex = -1;
	};

	static void FillTargetFrame(const ST_HotChtThreadProcessData data);
public:signals:
	void sgn_HotRectGenerateState(int percentage, int activateThreadCount, QString errstr);
protected:
	void slot_GenFinished();
	void slot_GenProgressValueChanged(int val);
	void GenPixmap();
private:
	QString			  m_currentSTFTDataKey;
	int				m_nLastReportPercantage = -1;
	QVector<ST_HotChtThreadProcessData>	  m_currentProcessVec;
	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;



private:
	int m_nLeftAxisWidth = 80;
	int m_nBottomAxisWidth = 30;
	int m_nTopTitleHeight = 30;
	int m_nRightColorMapRegionWidth = 140;

	QString m_strTitle = "STFT Hot Gram";
	QFont	m_ft_titleFont;
	QColor  m_crTitle = Qt::black;
	QColor  m_crAxis = Qt::black;

	int		m_nAxiesScaleLength = 5;
	int     m_nAxiesValStrMargin = 5;
	int     m_nAxiesValStrFontSize = 15;

	int		m_nColorMapWidth = 25;

	QColor  m_nColorMap00Percent = Qt::black;
	QColor  m_nColorMap33Percent = QColor(81, 18, 124);
	QColor  m_nColorMap66Percent = QColor(233, 84, 98);
	QColor  m_nColorMap100Percent = QColor(252, 249, 187);

	int		m_nMinFreq		= 0;
	int		m_nMaxFreq		= 4500;
	QTime	m_StartTime		= QTime(0, 0, 0);
	int		m_ChtTimeLengthMsec = 1000;
	double  m_dMinDB		= 0;
	double  m_dMaxDB		= 80;
	int		m_nFreqScaleIntervalCount = 10;
	int     m_nTimeScaleIntervalCount = 10;
	int     m_nTotalValueCount = 10;

	int		m_nColorRectBandWidth			= 20;
	int		m_nColorRectTimeIntervalMsec	= 20;

	int					m_nCurrentFrameIndex = -1;
	ST_STFTInputpara	m_para;
	int		m_nCrRectFreqIntervalY		= -1;	//一个颜色快在Y方向上的尺寸
	int		m_nCrRectTimeIntervalX		= -1;	//一个颜色快在X方向上的尺寸
	double	m_dCrRectFreqBandWidth		= -1;	//一个颜色快在Y方向的实际带宽（hz）
	double	m_dCrRectTimeLengthMsec		= -1;	//一个颜色块在X方向的实际时长(毫秒)
	QVector<QVector<ST_FFTFreqColorRect>> m_vecCrFrame;
	QImage m_HotChtImage;

	bool	m_bMouseInDrawArea = false;
	QPoint	m_ptMousePos;
	QTime   m_currentTime = QTime(0, 0, 0);
	

	//防止生成的时候画图
	bool    m_bOnGenerate = false;
	
};

