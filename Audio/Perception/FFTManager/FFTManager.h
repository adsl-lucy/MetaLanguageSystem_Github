#pragma once
#include <QObject>
#include <QDebug>

#include <QtConcurrent>
#include <QThreadPool>



#include "../../protocol/protocol_audio.h"
#include "../../../ThirdParty/FFTw/fftw3.h"
#include "../../../ThirdParty/FFTw/FFTWPlanManager.h"

class FFTWindowManager;


class FFTManager :public QObject
{
	Q_OBJECT
public:
	static FFTManager* instance();
protected:
	FFTManager();
	static FFTManager* m_instance;

#pragma region �ź�����

public slots:
	void slot_drawBaseSig(ST_AudioBaseSignal& resultSignal);
	void slot_drawModuleAndModResultSig(ST_AudioModuleSignal& modSignal);
	

protected:
	double getSinValue(double frequency, double time, double amplitude);
	double getSquareValue(double frequency, double time, double amplitude);

	double getModuleValue(const ST_AudioModuleSignalPara& moduleSigParaRef, double currentPt);
	void getModuleSig(ST_AudioModuleSignal& modSignal);
	void getModuleResultSig(ST_AudioModuleSignal& modSignal);
#pragma endregion

#pragma region FFT

public:
	double getFrameTimeLength(int ptCount, int sampleRate);
	double getFreqencyInterval(int WndSampleRate, int WndPointCount);
	int    getEffectFFTPointCount(const ST_STFTInputpara& inputPara);
public slots:
	//����һ���Ը���Ҷ�任���� STFT��������
	void slot_getFFTResult(ST_FFTInputData& FFTInputData, ST_FFTOutputData& resultFrame);
protected:
	//���̣߳����̣߳����ɸ��ã�û����λ�����
	void FFT_Zhihu(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame);

	//����һ����FFTʹ�ã����ʹ�����ܲ���
	void FFT_FFTW_useOnce(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame);
	//���ʹ�õ�FFTW
	void FFT_FFTW_multiUse(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame, const ST_FFTWPlan& planData);

	//��FFTW�����ת��Ϊʵ��ʹ�õ�֡
	void fromFFTWoutputToResultFrame(const ST_FFTInputData& FFTPara, const ST_FFTWPlan& fftwOutputPlanData, ST_FFTOutputData& resultFrame);

	//δʵ��
	void FFT_Cuda(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame);

	void FFT_ZhihuOrigin(QVector<double>& dataR, QVector<double>& dataI, QVector<double>& dataA, int N, int M);
#pragma endregion

#pragma region STFT
public:signals:
	void sgn_STFTGenerateState(int percentage, int activateThreadCount, QString errstr);
	void sgn_getSTFTResult(ST_STFTOutputData& resultData);
public slots:
	//STFT����ͳһ���
	void slot_generateSTFTResult(ST_STFTInputData& inputData);

protected:
	//֪���㷨 + ���߳�ʵ�� ��ͨ��� ��ͨ����
	void generateSTFTResultByOneThreadWithZhihu(ST_STFTInputData& inputData);
	//֪���㷨 + ���߳�ʵ�� ��ͨ������ܵ��۷�
	void generateSTFTResultByConcurentWithZhihu(ST_STFTInputData& inputData);
	//FFTW     + ���߳�ʵ�� ���缶 CPU ���߳�����
	void generateSTFTResultByOneThreadWithFFTW(ST_STFTInputData& inputData);
	//FFTW     + ���߳�ʵ��
	void generateSTFTResultByMultiThreadWithFFTW(ST_STFTInputData& inputData);

protected:
	int getSTFTFrameCount(const ST_STFTInputData& para);
	//ͨ��STFT�����������FFTĳһ֡����Ϣ������ɹ�����true,����ʧ�ܷ���false
	bool getSTFTFramePara(const ST_STFTInputData& fromPara, int frameIndex,ST_FFTInputPara& setFFTPara, int& FrameStartIndex, int& FrameEndIndex);

	bool putOnSTFTWndOnAudioPt(const ST_STFTWnd& WndData,QVector<ST_AudioPoint>& AudioPtBuffer);

	bool resetMultiThreadBuffer(ST_STFTInputData& inputData);
	//�߳��õ�֡����Ҫ��ʼ������������������
	bool initInputAndOutPutFrameWithFrameIndex(int frameIndex, ST_FFTInputData& inputFFTData, ST_FFTOutputData& outputFrame);

	static void generateFFTFrameFromFrameIndexWithZhihu(int FrameIndex);

	static void generateFFTFrameFromFrameIndexWithFFTW(int FrameIndex);

	const ST_STFTWnd&		getCurrentSTFTWnd()				{ return m_currentSTFTWnd; };
	const ST_STFTInputData& getCurrentInputSTFTData()		{ return m_currentInputData;};
	ST_STFTOutputData&		getCurrentOutputSTFTData()		{ return m_currentOutputData; };

protected slots:
	void slot_STFTFinished();
	void slot_STFTprogressValueChanged(int val);

private:

	QFutureWatcher<void>* m_pSTFTwatcher = nullptr;
	int				  m_nLastReportPercantage = 0;

	//���߳��û���
	ST_STFTWnd		  m_currentSTFTWnd;
	QVector<int>	  m_currentProcessFrameIndexVec;
	ST_STFTInputData  m_currentInputData;
	ST_STFTOutputData m_currentOutputData;

	EN_FFTType		  m_MultiThreadFFTType = EN_FFTType::Zhihu;

	fftw_plan		  m_globalFFTWPlan;

#pragma endregion



};

