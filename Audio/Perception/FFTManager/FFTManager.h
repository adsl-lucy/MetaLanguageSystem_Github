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

#pragma region 信号生成

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
	//仅限一次性傅里叶变换调用 STFT不走这里
	void slot_getFFTResult(ST_FFTInputData& FFTInputData, ST_FFTOutputData& resultFrame);
protected:
	//单线程，多线程，均可复用（没有相位输出）
	void FFT_Zhihu(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame);

	//仅限一次性FFT使用，多次使用性能不佳
	void FFT_FFTW_useOnce(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame);
	//多次使用的FFTW
	void FFT_FFTW_multiUse(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame, const ST_FFTWPlan& planData);

	//将FFTW的输出转化为实际使用的帧
	void fromFFTWoutputToResultFrame(const ST_FFTInputData& FFTPara, const ST_FFTWPlan& fftwOutputPlanData, ST_FFTOutputData& resultFrame);

	//未实现
	void FFT_Cuda(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame);

	void FFT_ZhihuOrigin(QVector<double>& dataR, QVector<double>& dataI, QVector<double>& dataA, int N, int M);
#pragma endregion

#pragma region STFT
public:signals:
	void sgn_STFTGenerateState(int percentage, int activateThreadCount, QString errstr);
	void sgn_getSTFTResult(ST_STFTOutputData& resultData);
public slots:
	//STFT对外统一入口
	void slot_generateSTFTResult(ST_STFTInputData& inputData);

protected:
	//知乎算法 + 单线程实现 普通玩家 普通性能
	void generateSTFTResultByOneThreadWithZhihu(ST_STFTInputData& inputData);
	//知乎算法 + 多线程实现 普通玩家性能的巅峰
	void generateSTFTResultByConcurentWithZhihu(ST_STFTInputData& inputData);
	//FFTW     + 单线程实现 世界级 CPU 单线程性能
	void generateSTFTResultByOneThreadWithFFTW(ST_STFTInputData& inputData);
	//FFTW     + 多线程实现
	void generateSTFTResultByMultiThreadWithFFTW(ST_STFTInputData& inputData);

protected:
	int getSTFTFrameCount(const ST_STFTInputData& para);
	//通过STFT输入参数计算FFT某一帧的信息，计算成功返回true,计算失败返回false
	bool getSTFTFramePara(const ST_STFTInputData& fromPara, int frameIndex,ST_FFTInputPara& setFFTPara, int& FrameStartIndex, int& FrameEndIndex);

	bool putOnSTFTWndOnAudioPt(const ST_STFTWnd& WndData,QVector<ST_AudioPoint>& AudioPtBuffer);

	bool resetMultiThreadBuffer(ST_STFTInputData& inputData);
	//线程拿到帧数后要初始化输入和输出数据内容
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

	//多线程用缓存
	ST_STFTWnd		  m_currentSTFTWnd;
	QVector<int>	  m_currentProcessFrameIndexVec;
	ST_STFTInputData  m_currentInputData;
	ST_STFTOutputData m_currentOutputData;

	EN_FFTType		  m_MultiThreadFFTType = EN_FFTType::Zhihu;

	fftw_plan		  m_globalFFTWPlan;

#pragma endregion



};

