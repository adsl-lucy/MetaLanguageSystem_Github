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

class BandWidthFilterManager : public QObject
{
	Q_OBJECT
public:
	static BandWidthFilterManager* instance();
protected:
	BandWidthFilterManager();
	static BandWidthFilterManager* m_instance;

public:signals:
	void sgn_BDSNR_GenState(int percentage, int activateThreadCount, QString errstr);

public:
	QString ConstrainPtTypeToStr(EN_BDSNRPtType state);

	double	NromalFreqToMelFreq(double normalFreq);
	double	MelFreqToNormalFreq(double melFreq);

	void	slot_StartGenBandWidthFilterData(const ST_BandWidthFilterPara& GenPara, ST_BandWidthFilterData& result);

	void	slot_StartBandWidthFilterConstrainData(QString dataKey, const ST_BandWidthFilterPara& FilterPara,const ST_BandWidthFilter_workPara& FilterActivePara);

protected:
	void GenFileterShape(ST_BandWidthFilterData& result);
	void GenFilterWeightPt(ST_BandWidthFilterData& filterData);

protected slots:
	void slot_BDSNRGenProgressValueChanged(int val);
	void slot_BDSNRGenFinished();

	static void GenBDSNRFrame(ST_BandWidthSNRConstrainFrame& FrameData);
	static void updateFilterVal(ST_BandWidthSNRConstrainFrame& FrameData);
	static void updatePtTag(ST_BandWidthSNRConstrainFrame& FrameData);

private:
	ST_BandWidthSNRConstrainData m_tempBDSNRData;
	int m_nLastReportPercantage = -1;
	QFutureWatcher<void>* m_pConcurrentWatcher = nullptr;
	QMutex m_mutex;
};

