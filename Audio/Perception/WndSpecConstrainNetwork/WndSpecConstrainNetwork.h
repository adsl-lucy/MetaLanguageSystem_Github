#pragma once
#include <QObject>
#include <qDebug>
#include <QtConcurrent>
#include <QThreadPool>
#include <QFutureWatcher>
#include <QMutex>

#include "../../protocol/protocol_audio.h"
#include "../../Perception/FFTManager/FFTManager.h"
#include "../../Perception/FFTWindowManager/FFTWindowManager.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"


class WndSpecConstrainNetwork : public QObject
{
	Q_OBJECT
public:
	static WndSpecConstrainNetwork* instance();
protected:
	WndSpecConstrainNetwork();
	static WndSpecConstrainNetwork* m_instance;

public:
	QString getWndConstrainStateStr(EN_WndSepcConstrainState state);
public:signals:
	void sgn_WndSpecConstrainGenState(int percentage, int activateThreadCount, QString errstr);
public slots:
	void slot_StartGenWndSpecConstrainResult(QString Key, const ST_WndSpecConstrainPara& WndSpecConstrainPara);

protected slots:
	void slot_getWndSpecConstrainResult(ST_WndSpecConstrainDistribute& result);

	static void updateFrameConstrainPtState(ST_WndSpecConstrainFrame& FrameRef);

	void slot_WndConstrainValValueChanged(int val);
	void slot_WndConstrainGenFinished();

private:
	bool m_bOnAskWndSpecConstrainResult = false;
	ST_WndSpecConstrainResult m_tempResult;
	int m_nLastReportPercantage = -1;
	QFutureWatcher<void>* m_pWndConstrainValWatcher = nullptr;

};

