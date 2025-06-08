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

class FreqDoubleNetwork : public QObject
{
	Q_OBJECT
public:
	static FreqDoubleNetwork* instance();
protected:
	FreqDoubleNetwork();
	static FreqDoubleNetwork* m_instance;
public:signals:
	void sgn_FDN_GenState(int percentage, int activateThreadCount, QString errstr);

public:
	int	getMatrixIndex(const ST_FreqMultipleTensor& Tensor,double freq);


	void duplicateFreqDoubleTensor(const ST_FreqMultipleTensor& source, ST_FreqMultipleTensor& target);
	void startGenFreqDoubleTensor(const ST_FreqMultipleTensorGenPara& GenPara, ST_FreqMultipleTensor& result);

public slots:
	void slot_StartGenFreqDoubleNetworkOutput(QString dataKey,const ST_FreqMultipleTensorGenPara& GenPara,const ST_FMTActiveCond& ActiveCond);

protected slots:
	void slot_FreqDoubGenProgressValueChanged(int val);
	void slot_FreqDoubGenFinished();

	static void GenFreqDoubFrame(ST_FreqDoubleNetworkFrame& FrameData);

protected:
	//求一个浮点索引对应于开区间的索引
	//LeftSide : true
	// 2.00 - 2.49 = 2    2.50 - 3 ->3
	//LeftSide : false
	// 2.00 - 2.50 = 2    2.51 - 3 ->3
	int getOpenAreaIndex(double index_double,bool LeftSide);

	void resetMatrixActiveState(const int FrameIndex, const ST_FreqDoubleNetworkOutput& tempData, QVector<ST_FreqMultipleNetworkParentPt>& parentVecRef);
	void mergeResonantMatrix(const ST_FreqDoubleNetworkOutput& tempData, QVector<ST_FreqMultipleNetworkParentPt>& parentVecRef);
	void mergeResonantFFTPT(const int FrameIndex, const ST_FreqDoubleNetworkOutput& tempData, const QVector<ST_FreqMultipleNetworkParentPt>& parentVecRef, QVector<ST_FreqMultipleNetworkChildPt>& childVecRef);

	bool checkSameDiffGroup(const double DiffRatio_1, const double DiffRatio_2, const ST_FMTActiveCond& ActiveCond);

private:
	ST_FreqDoubleNetworkOutput m_tempData;
	int m_nLastReportPercantage = -1;
	QFutureWatcher<void>* m_pConcurrentWatcher = nullptr;

};

