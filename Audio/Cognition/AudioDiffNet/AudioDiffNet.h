#pragma once
#include <QObject>
#include <qDebug>
#include <QtConcurrent>
#include <QThreadPool>
#include <QFutureWatcher>
#include <QMutex>
#include "../../protocol/protocol_audio.h"
#include "../../../CenterProcessing/DataCenter/DataCenterManager.h"
#include "../../Perception/FFTManager/FFTManager.h"

class AudioDiffNet : public QObject
{
	Q_OBJECT
public:
	static AudioDiffNet* instance();
protected:
	AudioDiffNet();
	static AudioDiffNet* m_instance;

public:signals:
	void sgn_Diff_GenState(int percentage, int activateThreadCount, QString errstr);

public slots:
	void slot_StartGenDiffResult(const ST_DiffNetPara& GenPara,QString DataKey);
	
protected slots:
	void slot_DiffGenProgressValueChanged(int val);
	void slot_DiffGenFinished();

	static void GenDiffFrame(ST_DiffFrame& FrameData);

protected:
	void GenDiffGroup(const ST_DiffNetPara& GenPara, ST_DiffNetState& NetStateRef);

private:
	ST_DiffNetOutput m_tempData;
	int m_nLastReportPercantage = -1;
	QFutureWatcher<void>* m_pConcurrentWatcher = nullptr;
	QMutex m_mutex;
};

