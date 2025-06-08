#pragma once
#include <QObject>
#include <qDebug>
#include <QtConcurrent>
#include <QThreadPool>
#include <QFutureWatcher>
#include <QMutex>
#include "../../protocol/protocol_audio.h"

#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"

class VibrateStateRelvanceNetwork : public QObject
{
	Q_OBJECT
public:
	static VibrateStateRelvanceNetwork* instance();
protected:
	VibrateStateRelvanceNetwork();
	static VibrateStateRelvanceNetwork* m_instance;

public:signals:
	void sgn_VibStateRel_GenState(int percentage, int activateThreadCount, QString errstr);

public:
	QString getVibStateStr(const EN_VibrateState state);
	void slot_StartBandWidthFilterConstrainData(QString dataKey, const ST_VibrateStateThreshHold& VibStateThreshHold);

protected:
	void setStatePtVal(const int ptIndex, const QVector<ST_VibrateStatePt>& ptVec);

protected slots:
	static void slot_GenVibPtState(const int ptIndex);
	void slot_GenProgressValueChanged(int val);
	void slot_GenFinished();

private:
	QVector<int> m_vecVibPtIndex;
	ST_VibrateStateNetworkNetworkData m_tempData;
	int m_nLastReportPercantage = -1;
	QFutureWatcher<void>* m_pConcurrentWatcher = nullptr;
	QMutex m_mutex;
};

