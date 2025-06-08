#pragma once
#include <QObject>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureWatcher>

#include "../../protocol/protocol_audio.h"

class FFTManager;

class FFTWindowManager :public QObject
{
	Q_OBJECT
public:
	static FFTWindowManager* instance();
protected:
	FFTWindowManager();
	static FFTWindowManager* m_instance;

public:
	QString getWndTypeStr(EN_STFTWndType type);

#pragma region STFTWndAns
public:signals:
	void sgn_WndFFTGenState(int percentage, int threadCount, QString msg);
	void sgn_WndFFTAnsEnd(ST_STFTWndAnsResult& result);
	void sgn_WndConstrainResultAnsEnd(ST_WndSpecConstrainDistribute& result);

public slots:
	void slot_generateSTFTWindow(ST_STFTWnd& WndPara);
	void slot_startGenerateSTFTWindowFFTResult(ST_STFTWndAnsPara& para);
	void slot_onFinishedWndFFT();
	void slot_WndFFTProgressValueChanged(int val);
	void slot_StartGenWndConstrainResult(const ST_WndSpecConstrainPara para);

protected:
	static void slot_ansFFTWndOnFreq(const int& FreqIndex);
private:
	QFutureWatcher<void>* m_pSTFTWndConcurrentWatcher = nullptr;

	int					m_nLastSTFTWndReportPercantage = 0;
	QVector<int>		m_VecWndFFTAnsFreqIndex;
	ST_STFTWndAnsPara   m_tempFFTAnsPara;
	ST_STFTWnd			m_tempFFTWndData;
	ST_STFTWndAnsResult m_tempFFTWndResult;

	bool m_nOnAnsWndConstrain = false;
	ST_WndSpecConstrainDistribute m_tempWndConstrainResult;

protected:
	void geneRectSTFTWnd(ST_STFTWnd& WndPara);
	void geneHannSTFTWnd(ST_STFTWnd& WndPara);

	void geneRectSTFTWndCustom(ST_STFTWnd& WndPara, int customPtCount);
	void geneHannSTFTWndCustom(ST_STFTWnd& WndPara, int customPtCount);

	void staticWndFFtPtPartData(ST_STFTWndAnsResult& result);
	void startStatWndConstrainResult(ST_STFTWndAnsResult& result);
#pragma endregion

#pragma region ActiveWndAns

public:signals:
	void sgn_ActiveWndGenState(int percentage, int threadCount, QString msg);
	void sgn_ActiveWndAnsEnd(ST_ActiveWndAnsResult& result);
public slots:
	void slot_StartGenActiveWndPt(ST_ActvieWnd& ActWndResult);
	void slot_startGenActiveWndFFTResult(ST_ActiveWndAnsPara& para);	
	void slot_onFinishedWndActive();
	void slot_WndActiveProgressValueChanged(int val);

protected:
	static void slot_ansActiveFFTWndOnFreq(const int& FreqIndex);

	void staticActiveWndFFtPtPartData(ST_ActiveWndAnsResult& result);
private:

	QFutureWatcher<void>* m_pActiveWndConcurrentWatcher = nullptr;
	int					  m_nLastActiveWndReportPercantage = 0;
	ST_ActiveWndAnsPara   m_tempActiveWndAnsPara;
	ST_ActvieWnd		  m_tempActiveWndData;
	ST_ActiveWndAnsResult m_tempActiveWndAnsResult;

protected:

#pragma endregion


};