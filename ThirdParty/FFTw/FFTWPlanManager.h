#pragma once

#include "./fftw3.h"
#include <QVector>
#include <QMutex>

//一个FFTW执行用的命令，用完要释放
struct ST_FFTWPlan
{
	int				planIndex = -1;//位于容器中的位置，用于任务结束后释放这个对象
	bool            beThreadUsed = false;	//是否已被线程使用，属于一个线程锁
	int				FFTPointCount = 0;
	fftw_complex*	p_fftwInput;
	fftw_complex*	p_fftwOutput;
	fftw_plan		plan;
};

//
class FFTWPlanManager
{
public:
	static FFTWPlanManager* instance();

	static void generateNewPlan(int pointCount, ST_FFTWPlan& newPlan);
	static void freePlan(ST_FFTWPlan& plan);
protected:
	FFTWPlanManager();
	static FFTWPlanManager* m_instance;

public:
	void resetPlanVec(int planCount, int fftwPointCount);
	void freeAllPlan();	
	const ST_FFTWPlan& getNearestUnusedPlan(bool& UnusedPlanExisted);
	void freePlanInVec(const ST_FFTWPlan& planRef);
	int  getCurrentUsedPlan();
	int  getMaxPlanCount();



private:
	QVector<ST_FFTWPlan> m_vecPlan;


	QMutex m_mutex;
};

