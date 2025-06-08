#include "FFTManager.h"
#include "../FFTWindowManager/FFTWindowManager.h"

#pragma execution_character_set("utf-8")

FFTManager* FFTManager::m_instance = nullptr;

FFTManager* FFTManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new FFTManager();
	}
	return m_instance;
}

FFTManager::FFTManager() :QObject(nullptr)
{
	m_pSTFTwatcher = new QFutureWatcher<void>(this);
	connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_STFTFinished()));
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &FFTManager::slot_STFTprogressValueChanged);
}

double FFTManager::getSinValue(double frequency, double time, double amplitude)
{
	double totalPhase = 2 * const_audio_pi * frequency * time;
	double value = amplitude * sin(totalPhase);
	return value;
}

double FFTManager::getSquareValue(double frequency, double time, double amplitude)
{
	double totalPhase	= 2 * const_audio_pi * frequency * time;
	double value		= amplitude * sin(totalPhase);
	if (value > 0)
	{
		return amplitude;
	}
	else
	{
		return 0;
	}
}

double FFTManager::getModuleValue(const ST_AudioModuleSignalPara& moduleSigParaRef, double currentPt)
{
	if (currentPt < moduleSigParaRef.startTime || currentPt > moduleSigParaRef.startTime + moduleSigParaRef.signalTimeLength)
	{
		return 0;
	}

	double  resultPx = 0;
	double  depthInRatio = moduleSigParaRef.depth / 100;
	double  depthInRatioRes = abs(1 - depthInRatio);

	if (moduleSigParaRef.signalType == EN_ModuleSignalType::tri_sin)
	{
		double	sinPx = getSinValue(moduleSigParaRef.moduleFrequency, currentPt, 1);
		resultPx = (1 + depthInRatioRes) / 2 + (1 - depthInRatioRes) / 2 * sinPx;
	}
	else if (moduleSigParaRef.signalType == EN_ModuleSignalType::square)
	{
		double squarePx = getSquareValue(moduleSigParaRef.moduleFrequency, currentPt, 1);
		resultPx = depthInRatioRes + depthInRatio * squarePx;
	}

	return resultPx;

}

void FFTManager::slot_drawBaseSig(ST_AudioBaseSignal& resultSignal)
{

	ST_AudioBaseSignalPara& baseSigParaRef = resultSignal.signalPara;

	if (baseSigParaRef.sampleRate <= 0)
	{
		baseSigParaRef.sampleRate = 100;
	}

	if (baseSigParaRef.signalTimeLength <= 0)
	{
		baseSigParaRef.signalTimeLength = 1;
	}

	if (baseSigParaRef.baseFrequency <= 0)
	{
		baseSigParaRef.baseFrequency = 10;
	}

	if (baseSigParaRef.amplitude <= 0)
	{
		baseSigParaRef.amplitude = 1;
	}

	int		totalDotCount		= baseSigParaRef.signalTimeLength * baseSigParaRef.sampleRate;
	double	timeLengthPerDot	= 1.0 / baseSigParaRef.sampleRate;

	resultSignal.vecPoint.clear();
	ST_AudioPoint nullSigPt;
	resultSignal.vecPoint = QVector<ST_AudioPoint>(totalDotCount, nullSigPt);

	for (int currentPointIndex = 0; currentPointIndex < totalDotCount; currentPointIndex++)
	{
		double	currentPt = baseSigParaRef.startTime + currentPointIndex * timeLengthPerDot;
		double	currentPx = getSinValue(baseSigParaRef.baseFrequency, currentPt, baseSigParaRef.amplitude);

		ST_AudioPoint& resultPtRef = resultSignal.vecPoint[currentPointIndex];
		resultPtRef.pTime = currentPt;
		resultPtRef.pVal = currentPx;
	}
}

void FFTManager::slot_drawModuleAndModResultSig(ST_AudioModuleSignal& modSignal)
{
	getModuleSig(modSignal);
	getModuleResultSig(modSignal);
}

void FFTManager::getModuleSig(ST_AudioModuleSignal& modSignal)
{
	ST_AudioModuleSignalPara& moduleSigParaRef = modSignal.modulePara;

	if (moduleSigParaRef.sampleRate <= 0)
	{
		moduleSigParaRef.sampleRate = 100;
	}

	if (moduleSigParaRef.signalTimeLength <= 0)
	{
		moduleSigParaRef.signalTimeLength = 1;
	}

	if (moduleSigParaRef.moduleFrequency <= 0)
	{
		moduleSigParaRef.moduleFrequency = 10;
	}

	if (moduleSigParaRef.depth <= 0)
	{
		moduleSigParaRef.depth = 1;
	}

	int		totalDotCount = moduleSigParaRef.signalTimeLength * moduleSigParaRef.sampleRate;
	double	timeLengthPerDot = 1.0 / moduleSigParaRef.sampleRate;



	modSignal.vecModuleSignal.clear();
	ST_AudioPoint nullSigPt;
	modSignal.vecModuleSignal = QVector<ST_AudioPoint>(totalDotCount, nullSigPt);

	for (int currentPointIndex = 0; currentPointIndex < totalDotCount; currentPointIndex++)
	{
		double	currentPt = moduleSigParaRef.startTime + currentPointIndex * timeLengthPerDot;
		double  resultPx = 0;

		resultPx = getModuleValue(moduleSigParaRef, currentPt);

		ST_AudioPoint& resultPtRef = modSignal.vecModuleSignal[currentPointIndex];
		resultPtRef.pTime = currentPt;
		resultPtRef.pVal = resultPx;
	}


}
void FFTManager::getModuleResultSig(ST_AudioModuleSignal& modSignal)
{
	ST_AudioBaseSignalPara&	baseSigPara				= modSignal.basePara;
	const ST_AudioModuleSignalPara& moduleSigPara	= modSignal.modulePara;

	ST_AudioBaseSignalPara modBaseSigPara;

	modBaseSigPara.startTime = 0;

	double baseSigEndTime	= baseSigPara.startTime + baseSigPara.signalTimeLength;
	double modSigEndTime	= moduleSigPara.startTime + moduleSigPara.signalTimeLength;

	double endTimeT			= std::max(baseSigEndTime, modSigEndTime);

	modBaseSigPara.signalTimeLength		= endTimeT - modBaseSigPara.startTime;
	modBaseSigPara.sampleRate			= baseSigPara.sampleRate;
	modBaseSigPara.amplitude			= baseSigPara.amplitude;
	modBaseSigPara.baseFrequency		= baseSigPara.baseFrequency;

	int totalDotCount = modBaseSigPara.signalTimeLength * modBaseSigPara.sampleRate;
	double timeLengthPerDot = 1.0 / modBaseSigPara.sampleRate;

	modSignal.vecModuleResultSignal.clear();
	ST_AudioPoint nullSigPt;
	modSignal.vecModuleResultSignal = QVector<ST_AudioPoint>(totalDotCount, nullSigPt);

	for (int currentPointIndex = 0; currentPointIndex < totalDotCount; currentPointIndex++)
	{
		double	currentPt = modBaseSigPara.startTime + currentPointIndex * timeLengthPerDot;
		double  resultPx = 0;

		if (currentPt < baseSigPara.startTime || currentPt > baseSigEndTime)
		{
			resultPx = 0;
		}
		else
		{
			double	currentPx = getSinValue(modBaseSigPara.baseFrequency, currentPt, modBaseSigPara.amplitude);
			double  moduleRatio = getModuleValue(moduleSigPara, currentPt);
			resultPx = currentPx * moduleRatio;

		}

		ST_AudioPoint& resultPtRef = modSignal.vecModuleResultSignal[currentPointIndex];
		resultPtRef.pTime = currentPt;
		resultPtRef.pVal = resultPx;

	}
}

double FFTManager::getFrameTimeLength(int ptCount, int sampleRate)
{
	double secPerPoint = 1.0 / (double)sampleRate;
	double result = ptCount * secPerPoint;
	return result;
}

double FFTManager::getFreqencyInterval(int WndSampleRate, int WndPointCount)
{
	double secPerPoint = 1.0 / (double)WndSampleRate;
	double WndTimeLength = secPerPoint * (double)WndPointCount;
	double FreqencyInterval = 1.0 / WndTimeLength;
	return FreqencyInterval;
}

int FFTManager::getEffectFFTPointCount(const ST_STFTInputpara& inputPara)
{
	return inputPara.WndPara.pointCount / 2;
}

void FFTManager::slot_getFFTResult(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame)
{
	switch (FFTPara.para.FFTType)
	{
		case EN_FFTType::Zhihu		:FFT_Zhihu(FFTPara, resultFrame); break;
		case EN_FFTType::FFTW		:FFT_FFTW_useOnce(FFTPara, resultFrame); break;
		case EN_FFTType::CudaFFT	:FFT_Cuda(FFTPara, resultFrame); break;
	}
}

void FFTManager::FFT_Zhihu(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame)
{
	QVector<double> FFTInputRVec(FFTPara.AudioPtVec.size(), 0);
	QVector<double> FFTInputIVec(FFTPara.AudioPtVec.size(), 0);
	QVector<double> FFToutputAVec(FFTPara.AudioPtVec.size(), 0);
	for (int i = 0; i < FFTPara.AudioPtVec.size(); i++)
	{
		ST_AudioPoint& audioPoint = FFTPara.AudioPtVec[i];
		FFTInputRVec[i] = audioPoint.pVal;
	}

	FFT_ZhihuOrigin(FFTInputRVec, FFTInputIVec, FFToutputAVec, FFTPara.AudioPtVec.size(), FFTPara.para.inputPointCountInPowerOf2);

	resultFrame.para.startTime	= FFTPara.para.startTime;
	resultFrame.para.timeLength	= FFTPara.para.timeLength;
	resultFrame.para.DeltaFreq	= 1.0 / FFTPara.para.timeLength;

	int freqCount = FFToutputAVec.size();

	resultFrame.para.startFreq = 0;
	resultFrame.para.endFreq = resultFrame.para.startFreq + (freqCount - 1) * resultFrame.para.DeltaFreq;

	resultFrame.resultVec.clear();

	ST_FFTPoint nullFFTPoint;
	resultFrame.resultVec = QVector<ST_FFTPoint>(freqCount, nullFFTPoint);
	resultFrame.para.maxAmp = 0;

	for (int i = 0; i < FFToutputAVec.size(); i++)
	{
		ST_FFTPoint FFTPt;
		double resultFreqAmp = FFToutputAVec[i];

		FFTPt.frequency = i * resultFrame.para.DeltaFreq;
		FFTPt.amplitude = resultFreqAmp * (2.0 / FFTPara.AudioPtVec.size());

		FFTPt.phase = 0;
		resultFrame.resultVec[i] = FFTPt;

		if (FFTPt.amplitude > resultFrame.para.maxAmp)
		{
			resultFrame.para.maxAmp = FFTPt.amplitude;
		}

	}
}

void FFTManager::FFT_FFTW_useOnce(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame)
{

	int pointCount = FFTPara.AudioPtVec.size();
	if (pointCount <= 0)
	{
		qDebug() << "FFTManager::FFT_FFTW inputVec empty!";
		return;
	}

	ST_FFTWPlan newPlan;
	FFTWPlanManager::generateNewPlan(pointCount, newPlan);

	/*
	fftw_complex* fftwInput		= (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * pointCount);
	fftw_complex* fftwOutput	= (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * pointCount);
	fftw_plan	  plan			= fftw_plan_dft_1d(pointCount, fftwInput, fftwOutput, FFTW_FORWARD, FFTW_ESTIMATE);
	*/

	for (int AudioPtIndex = 0; AudioPtIndex < pointCount; AudioPtIndex++)
	{
		ST_AudioPoint& audioPoint = FFTPara.AudioPtVec[AudioPtIndex];

		newPlan.p_fftwInput[AudioPtIndex][0] = audioPoint.pVal;
		newPlan.p_fftwInput[AudioPtIndex][1] = 0.0;
	}

	fftw_execute(newPlan.plan);

	fromFFTWoutputToResultFrame(FFTPara, newPlan, resultFrame);

	FFTWPlanManager::freePlan(newPlan);

}

void FFTManager::FFT_FFTW_multiUse(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame, const ST_FFTWPlan& planData)
{
	int pointCount = planData.FFTPointCount;
	if (FFTPara.AudioPtVec.size() != pointCount)
	{
		qDebug() << QString("FFTManager::FFT_FFTW_multiUse pointCount Unsafe! AudioPtVecSize : %1 planPointCount : %2")
			.arg(FFTPara.AudioPtVec.size()).arg(pointCount);
		return;
	}

	fftw_complex* fftwInput = planData.p_fftwInput;

	for (int AudioPtIndex = 0; AudioPtIndex < pointCount; AudioPtIndex++)
	{
		ST_AudioPoint& audioPoint = FFTPara.AudioPtVec[AudioPtIndex];

		fftwInput[AudioPtIndex][0] = audioPoint.pVal;
		fftwInput[AudioPtIndex][1] = 0.0;
	}

	fftw_execute(planData.plan);

	fromFFTWoutputToResultFrame(FFTPara, planData, resultFrame);

}

void FFTManager::fromFFTWoutputToResultFrame(const ST_FFTInputData& FFTPara,const ST_FFTWPlan& fftwOutputPlanData, ST_FFTOutputData& resultFrame)
{
	int pointCount = fftwOutputPlanData.FFTPointCount;
	fftw_complex* fftwOutput = fftwOutputPlanData.p_fftwOutput;

	if (pointCount != FFTPara.AudioPtVec.size())
	{
		qDebug() << " FFTManager::fromFFTWoutputToResultFrame intputVec size diff!";
		return;
	}

	QVector<double> FFToutputAVec(FFTPara.AudioPtVec.size(), 0);
	QVector<double> FFToutputPVec(FFTPara.AudioPtVec.size(), 0);

	for (int freqIndex = 0; freqIndex < pointCount; freqIndex++)
	{
		FFToutputAVec[freqIndex] = sqrt(pow(fftwOutput[freqIndex][0], 2) + pow(fftwOutput[freqIndex][1], 2));
		FFToutputPVec[freqIndex] = acos(fftwOutput[freqIndex][0] / FFToutputAVec[freqIndex]);
		//FFToutputPVec[freqIndex] = atan(fftwOutput[freqIndex][0] / fftwOutput[freqIndex][1]) + const_audio_pi * 0.5;
	}

	resultFrame.para.startTime = FFTPara.para.startTime;
	resultFrame.para.timeLength = FFTPara.para.timeLength;
	resultFrame.para.DeltaFreq = 1.0 / FFTPara.para.timeLength;

	int freqCount = FFToutputAVec.size();

	resultFrame.para.startFreq = 0;
	resultFrame.para.endFreq = resultFrame.para.startFreq + (freqCount - 1) * resultFrame.para.DeltaFreq;

	resultFrame.resultVec.clear();

	ST_FFTPoint nullFFTPoint;
	resultFrame.resultVec = QVector<ST_FFTPoint>(freqCount, nullFFTPoint);
	resultFrame.para.maxAmp = 0;

	for (int i = 0; i < FFToutputAVec.size(); i++)
	{
		ST_FFTPoint FFTPt;
		double resultFreqAmp = FFToutputAVec[i];

		FFTPt.frequency = i * resultFrame.para.DeltaFreq;
		FFTPt.amplitude = resultFreqAmp * (2.0 / FFTPara.AudioPtVec.size());

		FFTPt.phase = FFToutputPVec[i];
		resultFrame.resultVec[i] = FFTPt;

		if (FFTPt.amplitude > resultFrame.para.maxAmp)
		{
			resultFrame.para.maxAmp = FFTPt.amplitude;
		}

	}

	//qDebug() << QString("FFTManager::fromFFTWoutputToResultFrame frameIndex : %1 maxVal %2").arg(1).arg(resultFrame.para.maxAmp);

}

void FFTManager::FFT_Cuda(ST_FFTInputData& FFTPara, ST_FFTOutputData& resultFrame)
{

}

void FFTManager::FFT_ZhihuOrigin(QVector<double>& dataR, QVector<double>& dataI, QVector<double>& dataA, int N, int M)
{
	int i, j, k, r;
	int p, L, B;
	unsigned int I, J, F0, F1, m, n;
	float Tr, Ti, temp;
	//输入序列倒序
/*
J=N/2;
for(I = 1; I < N - 2; I++)
{
	//数组元素互换
	if(I<J)
	{
		temp = dataR[I];
		dataR[I] = dataR[J];
		dataR[J] = temp;
	}
	//求取下一个反序数
	K=N/2;//K是N的权值变量，从最高位权值开始判断。
	while(1)
	{
		//从左到右循环判断该位是否为1
		if(J< K)
		{
			J=J+K;//判断结果为该位为0，加上该位权值，0变成1。
			break;//循环结束
		}
		else
		{
			J=J-K;//判断结果为该位为1，减去该位权值，1变成0。
			K=K/2;//得到下一位的权值，继续下一位0或1的判断。
		 }
	}
}*/

//倒序
	for (I = 0; (int)I < N; I++)   //根据规律四，需要对数组元素执行码间倒序
	{
		/*获取下标I的反序J的数值*/
		J = 0;
		for (k = 0; k < (M / 2 + 0.5); k++)     //k表示操作
		{
			//*反序操作*/
			m = 1;//m是最低位为1的二进制数
			n = (unsigned int)pow(2, M - 1);//n是第M位为1的二进制数
			m <<= k; //对m左移k位
			n >>= k; //对n右移k位
			F0 = I & n;//I与n按位与提取出前半部分第k位
			F1 = I & m;//I与m按位与提取出F0对应的后半部分的低位
			if (F0) J = J | m; //J与m按位或使F0对应低位为1
			if (F1) J = J | n; //J与n按位或使F1对应高位为1 
		}
		//printf("I为：");printBin(I,M);printf(" %d\n",I);
		//printf("J为：");printBin(J,M);printf(" %d\n\n",J);

		if (I < J)
		{
			temp = dataR[I];
			dataR[I] = dataR[J];
			dataR[J] = temp;
			//补充虚数部分交换： 
			temp = dataI[I];
			dataI[I] = dataI[J];
			dataI[J] = temp;
		}
	}

	//进行FFT
		/*	Tr = Xr(J+B)cos(2.0*PI*p/N) + Xi(J+B)sin(2.0*PI*p/N)
			Ti = Xi(J+B)cos(2.0*PI*p/N) - Xr(J+B)sin(2.0*PI*p/N)
			Ar[J] = Xr(J) + Tr
			Ai[J] = Xi(J) + Ti
			Ar[J+B] = Xr(J) - Tr
			Ai[J+B] = Xi(J) - Ti
		   (其中 Xr为上一级的Ar, Xi为上一级的Ai)*/
	for (L = 1; L <= M; L++)	//FFT蝶形级数L从1--M
	{
		/*第L级的运算:
		然后对于第L级，我们在问题五种提到，蝶形运算的种类数目等于间隔B:有多少种蝶形运算就要需要循环多少次;
		随着循环的不同，旋转指数P也不同，P的增量为k=2^(M-L)*/
		//先计算一下间隔 B = 2^(L-1);
		B = 1;
		B = (int)pow(2, L - 1);
		for (j = 0; j <= B - 1; j++)
			//j = 0,1,2,...,2^(L-1) - 1
		{	/*同种蝶形运算*/
			//先计算增量k=2^(M-L)
			k = 1;
			k = (int)pow(2, M - L);
			//计算旋转指数p，增量为k时，则P=j*k
			p = 1;
			p = j * k;
			/*接下来，由问题六我们可以知道同种蝶形运算的次数刚好为增量k=2^(M-L)；
			同种蝶形的运算次数即为蝶形运算的次数*/
			for (i = 0; i <= k - 1; i++)
			{
				//数组下标定为r
				r = 1;
				r = j + 2 * B * i;
				Tr = dataR[r + B] * cos(2.0 * const_audio_pi * p / N) + dataI[r + B] * sin(2.0 * const_audio_pi * p / N);
				Ti = dataI[r + B] * cos(2.0 * const_audio_pi * p / N) - dataR[r + B] * sin(2.0 * const_audio_pi * p / N);
				dataR[r + B] = dataR[r] - Tr;
				dataI[r + B] = dataI[r] - Ti;
				dataR[r] = dataR[r] + Tr;
				dataI[r] = dataI[r] + Ti;
			}
		}
	}
	//计算幅值 
	for (i = 0; i < N; i++)
	{
		dataA[i] = sqrt(dataR[i] * dataR[i] + dataI[i] * dataI[i]);
	}
}

bool FFTManager::resetMultiThreadBuffer(ST_STFTInputData& inputData)
{
	m_currentInputData.para = inputData.para;
	AudioProtocol::duplicateAudioVec(inputData.vecPoint, m_currentInputData.vecPoint);

	const ST_STFTInputpara& inputPara = inputData.para;

	int pointCount = inputData.vecPoint.size();
	int frameSize = pow(2, inputPara.FFTPOW2);
	int frameCount = getSTFTFrameCount(inputData);

	bool initState = AudioProtocol::initSTFTData(frameCount, frameSize, m_currentOutputData);
	m_currentOutputData.InputPara = inputPara;

	if (!initState)
	{
		qDebug() << "FFTManager::slot_generateSTFTResultByConcurent initVec error";
		return false;
	}

	m_currentSTFTWnd.WndPara = inputData.para.WndPara;
	FFTWindowManager::instance()->slot_generateSTFTWindow(m_currentSTFTWnd);

	m_currentProcessFrameIndexVec.clear();
	m_currentProcessFrameIndexVec = QVector<int>(frameCount, 0);
	for (int i = 0; i < m_currentProcessFrameIndexVec.size(); i++)
	{
		m_currentProcessFrameIndexVec[i] = i;
	}
	return true;
}

void FFTManager::generateSTFTResultByConcurentWithZhihu(ST_STFTInputData& inputData)
{
	bool resetState = resetMultiThreadBuffer(inputData);

	if (!resetState)
	{
		return;
	}
	m_MultiThreadFFTType = EN_FFTType::Zhihu;
	QFuture<void> future = QtConcurrent::map(m_currentProcessFrameIndexVec, FFTManager::generateFFTFrameFromFrameIndexWithZhihu);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_STFTprogressValueChanged(0);

}

//FFTW     + 单线程实现 世界级 CPU 单线程性能
void FFTManager::generateSTFTResultByOneThreadWithFFTW(ST_STFTInputData& inputData)
{
	const ST_STFTInputpara& inputPara = inputData.para;

	int pointCount = inputData.vecPoint.size();
	int frameSize = pow(2, inputPara.FFTPOW2);
	int frameCount = getSTFTFrameCount(inputData);

	ST_STFTOutputData resultData;
	bool initState = AudioProtocol::initSTFTData(frameCount, frameSize, resultData);
	resultData.InputPara = inputPara;

	if (!initState)
	{
		qDebug() << "FFTManager::generateSTFTResultByOneThreadWithFFTW initVec error";
		return;
	}

	ST_AudioPoint nullAudioPt;
	QVector<ST_AudioPoint> AudioPtBuffer = QVector<ST_AudioPoint>(inputPara.WndPara.pointCount, nullAudioPt);

	ST_STFTWnd STFTWnd;
	STFTWnd.WndPara = inputData.para.WndPara;
	FFTWindowManager::instance()->slot_generateSTFTWindow(STFTWnd);

	int hunderdsOfFrame = qMax(1, frameCount / 100);

	ST_FFTWPlan multUsedPlan;
	FFTWPlanManager::generateNewPlan(frameSize, multUsedPlan);

	for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
	{
		ST_FFTInputData inputFFTData;
		int frameStartIndex = -1;
		int frameEndIndex = -1;
		bool frameState = getSTFTFramePara(inputData, frameIndex, inputFFTData.para, frameStartIndex, frameEndIndex);
		if (!frameState)
		{
			qDebug() << QString("FFTManager::generateSTFTResultByOneThreadWithFFTW: frame : %1 paraInvalid!").arg(frameIndex);
			break;
		}

		for (int AudioPtIndex = frameStartIndex; AudioPtIndex <= frameEndIndex; AudioPtIndex++)
		{
			AudioPtBuffer[AudioPtIndex - frameStartIndex] = inputData.vecPoint[AudioPtIndex];
		}

		bool WndState = putOnSTFTWndOnAudioPt(STFTWnd, AudioPtBuffer);
		if (!WndState)
		{
			qDebug() << QString("FFTManager::generateSTFTResultByOneThreadWithFFTW: Wnd error! frameIndex :%1").arg(frameIndex);
			break;
		}

		inputFFTData.AudioPtVec.clear();
		inputFFTData.AudioPtVec = AudioPtBuffer;

		FFT_FFTW_multiUse(inputFFTData, resultData.vecOutput[frameIndex], multUsedPlan);

		if (hunderdsOfFrame == 1)
		{
			emit sgn_STFTGenerateState(frameIndex / frameCount, 1, QString("%1 / %2 ").arg(frameIndex).arg(frameCount));
		}
		else if (frameIndex % hunderdsOfFrame == 0)
		{
			emit sgn_STFTGenerateState(frameIndex / hunderdsOfFrame, 1, QString("%1 / %2 ").arg(frameIndex).arg(frameCount));
		}

	}

	FFTWPlanManager::freePlan(multUsedPlan);

	emit sgn_STFTGenerateState(100, 1, QString());
	emit sgn_getSTFTResult(resultData);
}

//FFTW     + 多线程实现 有BUG
void FFTManager::generateSTFTResultByMultiThreadWithFFTW(ST_STFTInputData& inputData)
{
	bool resetState = resetMultiThreadBuffer(inputData);

	if (!resetState)
	{
		return;
	}

	FFTWPlanManager::instance()->resetPlanVec(QThread::idealThreadCount(), inputData.para.WndPara.pointCount);

	m_MultiThreadFFTType = EN_FFTType::FFTW;
	QFuture<void> future = QtConcurrent::map(m_currentProcessFrameIndexVec, FFTManager::generateFFTFrameFromFrameIndexWithFFTW);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_STFTprogressValueChanged(0);
}

void FFTManager::slot_STFTFinished()
{
	emit sgn_STFTGenerateState(100, 1, QString());
	emit sgn_getSTFTResult(m_currentOutputData);

	m_currentInputData.vecPoint.clear();
	m_currentSTFTWnd.VecWndPt.clear();
	m_currentOutputData.vecOutput.clear();
	m_currentProcessFrameIndexVec.clear();

	if (m_MultiThreadFFTType == EN_FFTType::FFTW)
	{
		FFTWPlanManager::instance()->freeAllPlan();
	}

}

void FFTManager::slot_STFTprogressValueChanged(int val)
{
	if (m_currentOutputData.vecOutput.isEmpty())
	{
		qDebug() << "FFTManager::slot_STFTprogressRangeChanged VecOutput empty!";
		return;
	}	

	int frameCount = m_currentOutputData.vecOutput.size();
	int hunderdsOfFrame = qMax(1, frameCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_STFTGenerateState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(frameCount));;
		m_nLastReportPercantage = percentage;
	}
	qDebug() << QString("slot_STFTprogressRangeChanged :%1 / %2 ").arg(processedCount).arg(frameCount);
}

bool FFTManager::initInputAndOutPutFrameWithFrameIndex(int FrameIndex, ST_FFTInputData& inputFFTData, ST_FFTOutputData& outputFrame)
{
	const ST_STFTInputData& inputSTFTData = FFTManager::instance()->getCurrentInputSTFTData();
	const ST_STFTInputpara& inputPara = inputSTFTData.para;
	//ST_STFTOutputData& outputData = FFTManager::instance()->getCurrentOutputSTFTData();
	//ST_FFTOutputData& outputFrame = outputData.vecOutput[FrameIndex];

	//ST_FFTInputData inputFFTData;
	int frameStartIndex = -1;
	int frameEndIndex = -1;
	bool frameState = FFTManager::instance()->getSTFTFramePara(inputSTFTData, FrameIndex, inputFFTData.para, frameStartIndex, frameEndIndex);
	if (!frameState)
	{
		qDebug() << QString("FFTManager::generateFFTFrameFromFrameIndex: frame : %1 paraInvalid!").arg(FrameIndex);
		outputFrame.concurentValid = false;
		return false;
	}

	ST_AudioPoint nullAudioPt;
	QVector<ST_AudioPoint> AudioPtBuffer = QVector<ST_AudioPoint>(inputPara.WndPara.pointCount, nullAudioPt);

	for (int AudioPtIndex = frameStartIndex; AudioPtIndex <= frameEndIndex; AudioPtIndex++)
	{
		AudioPtBuffer[AudioPtIndex - frameStartIndex] = inputSTFTData.vecPoint[AudioPtIndex];
	}

	const ST_STFTWnd& STFTWnd = FFTManager::instance()->getCurrentSTFTWnd();

	bool WndState = FFTManager::instance()->putOnSTFTWndOnAudioPt(STFTWnd, AudioPtBuffer);
	if (!WndState)
	{
		qDebug() << QString("FFTManager::generateFFTFrameFromFrameIndex: frame : %1 WndState inValid!").arg(FrameIndex);
		outputFrame.concurentValid = false;
		return false;
	}

	inputFFTData.AudioPtVec.clear();
	inputFFTData.AudioPtVec = AudioPtBuffer;
	return true;
}

void FFTManager::generateFFTFrameFromFrameIndexWithZhihu(int FrameIndex)
{
	ST_FFTInputData inputFFTData;
	ST_STFTOutputData& outputData = FFTManager::instance()->getCurrentOutputSTFTData();
	ST_FFTOutputData& outputFrame = outputData.vecOutput[FrameIndex];
	bool initState = FFTManager::instance()->initInputAndOutPutFrameWithFrameIndex(FrameIndex, inputFFTData, outputFrame);

	if(!initState)
	{
		qDebug() << QString("FFTManager::generateFFTFrameFromFrameIndexWithZhihu : frameIndex %1 initFailed!").arg(FrameIndex);
		return;
	}

	FFTManager::instance()->FFT_Zhihu(inputFFTData, outputFrame);
	outputFrame.concurentValid = true;

}

void FFTManager::generateFFTFrameFromFrameIndexWithFFTW(int FrameIndex)
{
	ST_FFTInputData inputFFTData;
	ST_STFTOutputData& outputData = FFTManager::instance()->getCurrentOutputSTFTData();
	ST_FFTOutputData& outputFrame = outputData.vecOutput[FrameIndex];
	bool initState = FFTManager::instance()->initInputAndOutPutFrameWithFrameIndex(FrameIndex, inputFFTData, outputFrame);

	if (!initState)
	{
		qDebug() << QString("FFTManager::generateFFTFrameFromFrameIndexWithFFTW : frameIndex %1 initFailed!").arg(FrameIndex);
		return;
	}

	if (FFTWPlanManager::instance()->getMaxPlanCount() == 0)
	{
		qDebug() << QString("FFTManager::generateFFTFrameFromFrameIndexWithFFTW : frameIndex %1 no existPlan!").arg(FrameIndex);
		return;
	}

	bool planSafe = false;
	const ST_FFTWPlan UnusedPpan = FFTWPlanManager::instance()->getNearestUnusedPlan(planSafe);

	if(!planSafe)
	{
		qDebug() << QString("FFTManager::generateFFTFrameFromFrameIndexWithFFTW plan not Enough! planCount : %1").arg(FFTWPlanManager::instance()->getMaxPlanCount());
		return;
	}

	FFTManager::instance()->FFT_FFTW_multiUse(inputFFTData, outputFrame, UnusedPpan);
	outputFrame.concurentValid = true;
	FFTWPlanManager::instance()->freePlanInVec(UnusedPpan);
}

void FFTManager::slot_generateSTFTResult(ST_STFTInputData& inputData)
{
	switch (inputData.para.FFTType)
	{
		case EN_FFTType::Zhihu:
		{
			if (inputData.para.multiThreadMode)
			{
				generateSTFTResultByConcurentWithZhihu(inputData);	//知乎+多线程
			}
			else
			{
				generateSTFTResultByOneThreadWithZhihu(inputData);	//知乎+单线程
			}
		}break;
		case EN_FFTType::FFTW:
		{
			if (inputData.para.multiThreadMode)
			{
				generateSTFTResultByMultiThreadWithFFTW(inputData);	//FFTW+多线程
			}
			else
			{
				generateSTFTResultByOneThreadWithFFTW(inputData);	//FFTW+单线程
			}
		}break;
		case EN_FFTType::CudaFFT:
		{
			if (inputData.para.multiThreadMode)
			{

			}
			else
			{

			}
		}break;
	}	
	
}

void FFTManager::generateSTFTResultByOneThreadWithZhihu(ST_STFTInputData& inputData)
{
	const ST_STFTInputpara& inputPara = inputData.para;

	int pointCount = inputData.vecPoint.size();
	int frameSize = pow(2, inputPara.FFTPOW2);
	int frameCount = getSTFTFrameCount(inputData);

	ST_STFTOutputData resultData;
	bool initState = AudioProtocol::initSTFTData(frameCount, frameSize, resultData);
	resultData.InputPara = inputPara;

	if (!initState)
	{
		qDebug() << "FFTManager::generateSTFTResultByOneThreadWithZhihu initVec error";
		return;
	}

	ST_AudioPoint nullAudioPt;
	QVector<ST_AudioPoint> AudioPtBuffer = QVector<ST_AudioPoint>(inputPara.WndPara.pointCount, nullAudioPt);

	ST_STFTWnd STFTWnd;
	STFTWnd.WndPara = inputData.para.WndPara;
	FFTWindowManager::instance()->slot_generateSTFTWindow(STFTWnd);

	int hunderdsOfFrame = qMax(1, frameCount / 100);

	for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
	{
		ST_FFTInputData inputFFTData;
		int frameStartIndex = -1;
		int frameEndIndex = -1;
		bool frameState = getSTFTFramePara(inputData, frameIndex, inputFFTData.para, frameStartIndex, frameEndIndex);
		if (!frameState)
		{
			qDebug() << QString("FFTManager::generateSTFTResultByOneThreadWithZhihu: frame : %1 paraInvalid!").arg(frameIndex);
			break;
		}

		for (int AudioPtIndex = frameStartIndex; AudioPtIndex <= frameEndIndex; AudioPtIndex++)
		{
			AudioPtBuffer[AudioPtIndex - frameStartIndex] = inputData.vecPoint[AudioPtIndex];
		}

		bool WndState = putOnSTFTWndOnAudioPt(STFTWnd, AudioPtBuffer);
		if (!WndState)
		{
			qDebug() << QString("FFTManager::generateSTFTResultByOneThreadWithZhihu: Wnd error! frameIndex :%1").arg(frameIndex);
			break;
		}

		inputFFTData.AudioPtVec.clear();
		inputFFTData.AudioPtVec = AudioPtBuffer;

		FFT_Zhihu(inputFFTData, resultData.vecOutput[frameIndex]);

		if (hunderdsOfFrame == 1)
		{
			emit sgn_STFTGenerateState(frameIndex / frameCount, 1, QString("%1 / %2 ").arg(frameIndex).arg(frameCount));
		}
		else if (frameIndex % hunderdsOfFrame == 0)
		{
			emit sgn_STFTGenerateState(frameIndex / hunderdsOfFrame, 1, QString("%1 / %2 ").arg(frameIndex).arg(frameCount));			
		}

	}

	emit sgn_STFTGenerateState(100, 1, QString());
	emit sgn_getSTFTResult(resultData);
}

int FFTManager::getSTFTFrameCount(const ST_STFTInputData& data)
{
	const ST_STFTInputpara& para = data.para;

	int frameCount = -1;

	if (para.WndGapType == EN_STFTWndGapType::WndRatio)
	{
		int WndPtCount = para.WndPara.pointCount;
		int GapPtCount = para.GapInWndRatio * WndPtCount;
		int totalPtCount = data.vecPoint.size();

		if (totalPtCount < WndPtCount)
		{
			return 0;
		}
		else 
		{
			frameCount = (totalPtCount - WndPtCount) / GapPtCount + 1;
		}
	}
	else if (para.WndGapType == EN_STFTWndGapType::timelength)
	{
		double WndTimeLength = para.WndPara.WndMsec / 1000;
		double GapTimeLength = para.GapInTimeLength;
		double dataTimeLength = para.timeLength;
		if (para.timeLength < GapTimeLength)
		{
			frameCount = 0;
		}
		else
		{
			frameCount = ((para.timeLength - WndTimeLength) / GapTimeLength) + 1;
		}
	}
	return frameCount;
}

bool FFTManager::getSTFTFramePara(const ST_STFTInputData& fromData, int frameIndex, ST_FFTInputPara& setFFTPara, int& FrameStartIndex, int& FrameEndIndex)
{
	auto checkIndexValid = [](const QVector<ST_AudioPoint>& vec,int checkIndex)->bool 
		{
			if (vec.isEmpty())
			{
				return false;
			}
			else if (checkIndex < 0)
			{
				return false;
			}
			else if (checkIndex >= vec.size())
			{
				return false;
			}
			return true;
		};


	setFFTPara.inputPointCountInPowerOf2 = fromData.para.FFTPOW2;

	setFFTPara.FFTType		= fromData.para.FFTType;
	setFFTPara.sampleRate	= fromData.para.sampleRate;	
	setFFTPara.timeLength	= fromData.para.WndPara.WndMsec / 1000;

	int WndPointCount = fromData.para.WndPara.pointCount;

	if ((int)setFFTPara.sampleRate == 0)
	{
		return false;
	}

	double secPerPoint = 1.0 / setFFTPara.sampleRate;
	bool startIndexState = false;
	bool endIndexState = false;

	if (fromData.para.WndGapType == EN_STFTWndGapType::timelength)
	{
		double GapTimeLength = fromData.para.GapInTimeLength;
		setFFTPara.startTime = GapTimeLength * frameIndex;
		if (setFFTPara.startTime < 0 || setFFTPara.startTime > fromData.para.timeLength)
		{
			return false;
		}

		FrameStartIndex = setFFTPara.startTime / secPerPoint;
		FrameEndIndex	= FrameStartIndex + WndPointCount - 1;

	}
	else if(fromData.para.WndGapType == EN_STFTWndGapType::WndRatio)
	{
		
		double GapInWndRatio = fromData.para.GapInWndRatio;
		int GapInWndPoint = WndPointCount * GapInWndRatio;
		FrameStartIndex = frameIndex * GapInWndPoint;
		bool startIndexState = checkIndexValid(fromData.vecPoint, FrameStartIndex);
		if(!startIndexState)
		{
			return false;		
		};
		setFFTPara.startTime = fromData.vecPoint[FrameStartIndex].pTime;
		FrameEndIndex = FrameStartIndex + WndPointCount - 1;
	}

	startIndexState		= checkIndexValid(fromData.vecPoint, FrameStartIndex);
	endIndexState		= checkIndexValid(fromData.vecPoint, FrameEndIndex);

	return startIndexState && endIndexState;

}

bool FFTManager::putOnSTFTWndOnAudioPt(const ST_STFTWnd& WndData, QVector<ST_AudioPoint>& AudioPtBuffer)
{
	if (WndData.VecWndPt.isEmpty() || AudioPtBuffer.isEmpty())
	{
		qDebug() << QString("FFTManager::putOnSTFTWndOnAudioPt Wnd or buffer isEmpty");
		return false;
	}

	if (WndData.VecWndPt.size() != AudioPtBuffer.size())
	{
		qDebug() << QString("FFTManager::putOnSTFTWndOnAudioPt Wnd and buffer size diff! Wnd : %1 buf %2")
			.arg(WndData.VecWndPt.size()).arg(AudioPtBuffer.size());
		return false;
	}

	for (int ptIndex = 0; ptIndex < AudioPtBuffer.size(); ptIndex++)
	{
		AudioPtBuffer[ptIndex].pVal *= WndData.VecWndPt[ptIndex];
	}

	return true;

}