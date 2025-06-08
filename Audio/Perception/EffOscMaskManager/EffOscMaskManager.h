#pragma once
#include <QObject>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureWatcher>

#include "../../protocol/protocol_audio.h"

class EffOscMaskManager : public QObject
{
	Q_OBJECT
public:
	static EffOscMaskManager* instance();
protected:
	EffOscMaskManager();
	static EffOscMaskManager* m_instance;

public:signals:
	void sgn_ActiveWndGenState(int percentage, int threadCount, QString msg);
	void sgn_ActiveWndAnsEnd(ST_ActiveWndAnsResult& result);

public:
	QString getWndTypeStr(EN_STFTWndType type);
	double getDeltaFreq(int sampleRate,int WndPtCount);

public slots:
	void slot_generateSTFTWindow(ST_STFTWnd& WndData);
	void slot_StartGenActiveWndPt(ST_ActvieWnd& ActWndResult);
	void slot_startGenActiveWndFFTResult(ST_ActiveWndAnsPara& para);

protected:
	void geneRectSTFTWnd(ST_STFTWnd& WndPara);
	void geneHannSTFTWnd(ST_STFTWnd& WndPara);



protected:
	static void slot_ansActiveFFTWndOnFreq(const int& FreqIndex);	
	void slot_onFinishedWndActive();
	void slot_WndFFTProgressValueChanged(int val);

	//void staticActiveWndFFtPtPartData(ST_ActiveWndAnsResult& result);
private:

	QFutureWatcher<void>* m_pActiveWndConcurrentWatcher = nullptr;
	QVector<int>		  m_VecWndFFTAnsFreqIndex;
	int					  m_nLastActiveWndReportPercantage = 0;
	//ST_ActiveWndAnsPara   m_tempActiveWndAnsPara;
	ST_ActvieWnd		  m_tempActiveWndData;
	ST_ActiveWndAnsResult m_tempActiveWndAnsResult;
		 

};

