#include "FFTWPlanManager.h"

#pragma execution_character_set("utf-8")



FFTWPlanManager* FFTWPlanManager::m_instance = nullptr;

FFTWPlanManager* FFTWPlanManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new FFTWPlanManager();
	}
	return m_instance;
}

FFTWPlanManager::FFTWPlanManager()
{
	m_vecPlan.clear();
}

void FFTWPlanManager::generateNewPlan(int pointCount, ST_FFTWPlan& newPlan)
{
	newPlan.FFTPointCount = pointCount;
	newPlan.p_fftwInput = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * pointCount);
	newPlan.p_fftwOutput = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * pointCount);
	newPlan.plan = fftw_plan_dft_1d(pointCount, newPlan.p_fftwInput, newPlan.p_fftwOutput, FFTW_FORWARD, FFTW_ESTIMATE);
}
void FFTWPlanManager::freePlan(ST_FFTWPlan& planData)
{
	fftw_destroy_plan(planData.plan);
	fftw_free(planData.p_fftwInput);
	fftw_free(planData.p_fftwOutput);
}

void FFTWPlanManager::resetPlanVec(int planCount, int fftwPointCount)
{
	freeAllPlan();
	ST_FFTWPlan nullPlan;
	nullPlan.beThreadUsed	= false;
	nullPlan.FFTPointCount	= -1;
	nullPlan.p_fftwInput	= nullptr;
	nullPlan.p_fftwOutput	= nullptr;
	m_vecPlan.clear();
	m_vecPlan = QVector<ST_FFTWPlan>(planCount, nullPlan);

	for (int planIndex = 0; planIndex < planCount; planIndex++)
	{
		ST_FFTWPlan& PlanInVec = m_vecPlan[planIndex];
		generateNewPlan(fftwPointCount, PlanInVec);
		PlanInVec.planIndex = planIndex;
	}

}

void FFTWPlanManager::freeAllPlan()
{
	for (int planIndex = 0; planIndex < m_vecPlan.size(); planIndex++)
	{
		ST_FFTWPlan& PlanInVec = m_vecPlan[planIndex];
		freePlan(PlanInVec);
	}
	m_vecPlan.clear();
}

const ST_FFTWPlan& FFTWPlanManager::getNearestUnusedPlan(bool& UnusedPlanExisted)
{
	m_mutex.lock();
	UnusedPlanExisted = false;
	for (int planIndex = 0; planIndex < m_vecPlan.size(); planIndex++)
	{
		ST_FFTWPlan& PlanInVec = m_vecPlan[planIndex];
		if (PlanInVec.beThreadUsed)
		{
			continue;
		}
		else
		{
			PlanInVec.beThreadUsed = true;
			UnusedPlanExisted = true;
			m_mutex.unlock();
			return PlanInVec;
		}
	}

	m_mutex.unlock();
	return m_vecPlan[0];

}

void FFTWPlanManager::freePlanInVec(const ST_FFTWPlan& planRef)
{
	if (planRef.planIndex < 0 || planRef.planIndex >= m_vecPlan.size())
	{
		return;
	}
	m_mutex.lock();
	m_vecPlan[planRef.planIndex].beThreadUsed = false;
	m_mutex.unlock();
}

int  FFTWPlanManager::getCurrentUsedPlan()
{
	int count = 0;
	for (int planIndex = 0; planIndex < m_vecPlan.size(); planIndex++)
	{
		ST_FFTWPlan& PlanInVec = m_vecPlan[planIndex];
		if (PlanInVec.beThreadUsed)
		{
			count++;
		}
	}
	return count;
}
int  FFTWPlanManager::getMaxPlanCount()
{
	return m_vecPlan.size();
}