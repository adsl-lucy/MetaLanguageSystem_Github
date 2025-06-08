#pragma once
#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QtConcurrent>
#include <QThreadPool>
#include <QMutex>
#include <QFutureWatcher>
#include <QMouseEvent>

#include "../../protocol/protocol_vision.h"
#include "../../Perception/ColorMetrics/ColorMetrics.h"

//怎么画这个二维图
enum class EN_LabCht_AxiType : int
{
	Fix_L_Axi_Euclid,		//L固定			AB欧式坐标系 A 横坐标 B 纵坐标
	Fix_AB_Axi_Euclid,		//AB向量固定	AB欧式坐标系 R 横坐标 L 纵坐标
};

//色块区分
enum class EN_LabCht_CrRectType : int
{
	Density,	//按照指定密度
	Pixel,		//每个像素不同
};

//设置坐标轴位置
struct ST_LabCht_AxiPos
{
	double L		= 0;
	double A		= 0;
	double B		= 0;
	double R		= 0;
};

//控制内容密度
struct ST_LabCht_Density
{
	double Radius	= 0;
	double L		= 0;
	double AB		= 0;
};

struct ST_ChtLab_MousePosLabInfo
{
	bool PosValid = false;
	bool SRgbValid = false;
	ST_LABPoint MouseLab;
	ST_xyzPoint MouseXYZ;
	ST_sRgbPoint MouseGammaSRgb;
	ST_sRgbPoint MouseSRgb;
	QColor MouseCr;
};

class Cht_LABColorDistribute :public QWidget  
{
	Q_OBJECT
public:
	Cht_LABColorDistribute(QWidget* parent);
	~Cht_LABColorDistribute();

	void setDrawingSet(bool drawAxis,bool drawGrid);
	void setAxiSetting(EN_LabCht_AxiType AxiType, ST_LabCht_AxiPos startPos, ST_LabCht_AxiPos endPos, ST_LabCht_Density gridDensity);
	void resetCrRect(EN_LabCht_CrRectType CrRectType,bool GammaExist,int CrRectWidth,ST_LabCht_Density CrDensity);
	void getCaculateResult(int& CaculateRectCount,int& ValidRectCount);

public:signals:
	void sgn_CrRectGenState(int percentage, int threadCount, QString msg);
	void sgn_updateCurrentMousePosInfo(const ST_ChtLab_MousePosLabInfo& MousePosInfo);
	void sgn_updateMousePressedPosInfo(const ST_ChtLab_MousePosLabInfo& MousePosInfo);
	void sgn_updateMousePosMetricInfo(const bool PosValid,const double RGBDis, const double LAB_1976, const double LAB_1984, const double LAB_1994, const double LAB_2000);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void leaveEvent(QEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

	void sendMousePosMsg(const QPoint& mousePos, bool isPressed);
	void sendPosMetric(bool MetricValid,const QPoint& mousePos1, const QPoint mousePos2);

	void paintEvent(QPaintEvent* event);
	void drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect);
	void paintAxies_Fix_L_Euclid(QPainter& painter);
	void paintAxies_Fix_AB(QPainter& painter);
	void getMousePosInfo(const QPoint mousePos, ST_ChtLab_MousePosLabInfo& posInfo);

	QRect getDrawAreaRect();
	QRect getBottomAxisRect();
	QRect getMaxDrawAreaSquare();

	ST_LABPoint getPointLAB(QPoint pos);
	void getLabPos(const ST_LABPoint& LABVal,QPoint& resultPt);

	struct ST_LabCht_CrRectGenCmd
	{
		int RowIndex = 0;
		Cht_LABColorDistribute* pCht = nullptr;
	};

	struct ST_LabCht_CrRect
	{
		bool		CrValid = false;
		QColor		QCr;
		ST_LABPoint LaBPt;
		QRect		drawRect;
	};

	void resetCrRectVec_Fix_L_Euclid();
	void resetCrRectVec_Fix_AB_Euclid();
	void resetCrRectVec_Pixel();
	void AddValidCrCount(const int addNum);

	static void OperateGenCmd(const ST_LabCht_CrRectGenCmd& GenCmd);
public:signals:
	void sgn_SecRectGenerateState(int percentage, int activateThreadCount, QString errstr);
protected:
	void slot_fillTargetRow(int rowIndex);
	void slot_GenFinished();
	void slot_GenProgressValueChanged(int val);

private:
	int m_nLastReportPercantage = -1;

	QMutex m_mutex;
	QFutureWatcher<void>* m_pConcurrentWatcher = nullptr;
	QVector<ST_LabCht_CrRectGenCmd> m_vecCrRectGenCmd;
	bool m_bOnGenrate = false;


	EN_LabCht_AxiType		m_AxiType		= EN_LabCht_AxiType::Fix_L_Axi_Euclid;
	EN_LabCht_CrRectType	m_CrRectType	= EN_LabCht_CrRectType::Density;

	bool				m_bDrawAxis = true;
	bool				m_bDrawGrid = true;

	bool				m_bGammaExist = true;
	ST_LabCht_AxiPos	m_AxiStartPos;
	ST_LabCht_AxiPos	m_AxiEndPos;
	ST_LabCht_Density	m_GridDensity;
	ST_LabCht_Density	m_CrDensity;
	
	QString				m_strTitle = "Effective Oscillation Time Section Cht";
	QFont				m_ft_titleFont;
	QColor				m_crTitle = Qt::black;

	QColor				m_CrAxis				= QColor(255,255,255,120);
	int					m_nAxiesScaleLength		= 5;
	int					m_nAxiesValStrMargin	= 5;
	QFont				m_ftAxisValStr;
	int					m_nAxiesValStrFontSize	= 15;
	int					m_nCrRectWidth = 2;

	int m_nLeftAxisWidth			= 80;
	int m_nBottomAxisHeight			= 60;
	int m_nTopTitleHeight			= 30;
	int m_nRightColorMapRegionWidth = 140;

	QVector<QVector<ST_LabCht_CrRect>> m_vecCrRect;
	QImage	m_CrPixelImg;
	int		m_nCaculateRectCount = 0;
	int		m_nValidRectCount = 0;
	bool	m_bMousePressed = false;
	QPoint  m_ptMousePressedPt = QPoint(-1, -1);
	QPoint  m_ptMouseCurrentPt = QPoint(-1, -1);

};

