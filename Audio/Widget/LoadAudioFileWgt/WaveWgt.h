#pragma once

#include <QWidget>
#include <QtCharts>

#include "./ui_WaveWgt.h"
#include "../../protocol/protocol_audio.h"
#include "../VolumnBar/VolumnBarWgt.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

//���Ŷȣ�����ͼ�����ɵ�ʱ�䳤��
//�����ų��ȴ���������Ƶ����ʱ�����ö�ٲ�����Ч
enum class EN_ZoomRate : int
{
	null	= 0,		
	Ms100	= 1,
	Ms200	= 2,
	Ms500	= 3,
	Sec1	= 4,
	Sec2	= 5,
	Sec5	= 6,
	Sec10	= 7,
	Sec30	= 8,
	Min1	= 9,
	Min5	= 10,
	All		= 11,
};


//����ͼ �Դ����ݴ洢����
class WaveWgt : public QWidget
{
	Q_OBJECT

public:
	WaveWgt(QWidget *parent = nullptr);
	~WaveWgt();

public:
	void loadWavData(const ST_WavDoubleData& data,bool AutoSenToDataCenter);

public:signals:
	void sgn_dataLoadState(int percentage,QString msg);

	void sgn_playBtnClicked();
	void sgn_jumpBtnClicked(QTime jumpTime);
	void sgn_stopBtnClicked();

	void sgn_saveWavData(ST_WavDoubleData& data, bool& saveState);

public slots:
	void slot_playBtnClicked();
	void slot_jumpBtnClicked();
	void slot_stopBtnClicked();

protected:
	void initUi();
	void initVolumnBar();
	void initLeftChart();
	void initRightChart();

	//�������ɲ�����
	void setPannelEnable(bool state);
	//�洢����
	void loadData(const ST_WavDoubleData& data);
	//������д��ͼ��
	void loadDataIntoCht(const EN_ZoomRate newZoomRate,QTime startTime,QTime endTime);

	void resetPannel();
	void resetLoadTimeEdit();

	void generateVolumnMap();


	int getZoomRateMsec(const EN_ZoomRate rate);
	QString getZoomRateStr(const EN_ZoomRate rate);
	void resetMaxZoomRate();
	void resetZoomSlider();
	EN_ZoomRate getSliderZoomRate(int value);
	void updateZoomSliderLabel();

	void resetWndPosScrollBar(const EN_ZoomRate newZoomRate);
	void updateWndPosScrollBarLabel();
	void chartWndPosChanged(QTime startTime, QTime endTime);

protected slots:
	void slot_windowLengthSliderMove(int value);
	void slot_WndPosScrollBarMove(int value);
	void slot_reloadBtnClicked();
	void slot_reloadAllBtnClicked();
	void slot_loadDataToDCenterBtnClicked();
	void slot_updateVolumn();




private:
	Ui::WaveWgtClass ui;

	QLineSeries*	m_leftCht_series_1DWave		= nullptr;
	QValueAxis*		m_leftCht_axis_x_1DWave		= nullptr;
	QValueAxis*		m_leftCht_axis_y_1DWave		= nullptr;
	QChart*			m_leftCht					= nullptr;
	QChartView*		m_leftCht_chtView_1DWave	= nullptr;

	QLineSeries*	m_rightCht_series_1DWave	= nullptr;
	QValueAxis*		m_rightCht_axis_x_1DWave	= nullptr;
	QValueAxis*		m_rightCht_axis_y_1DWave	= nullptr;
	QChart*			m_rightCht					= nullptr;
	QChartView*		m_rightCht_chtView_1DWave	= nullptr;

	ST_WavDoubleData m_data;

	EN_ZoomRate m_nMaxZoomRate = EN_ZoomRate::null;//������������������������������Ƶ��С��500Ms ����200Ms����ô���ڵ����ߴ����500Ms
	EN_ZoomRate m_nCurrentZoomRate = EN_ZoomRate::null;

	QTime m_WndPosStartTime = QTime(0, 0, 0);
	QTime m_WndPosEndTime	= QTime(0, 0, 0);

	QTime m_chtLoadStartTime = QTime(0, 0, 0);
	QTime m_chtLoadEndTime	= QTime(0, 0, 0);

	int			m_nVolumnUpdateIntervalMs = 20;
	VolumnBarWgt* m_pVolumnBar = nullptr;

	QMap<int, double> m_mapMsecVolumn;
	QTimer* m_pVolumnUpdateTimer = nullptr;
	int m_nCurrentVolumnUpdateCount = -1;
};
