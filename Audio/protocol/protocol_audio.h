#pragma once
#include <QString>
#include <QTime>
#include <QVector>
#include <QAudioFormat>
#include <qDebug>

#pragma region AudioBase

const double const_audio_pi = 3.1415926;

//一般音频文件默认的最大音量对应DB
const double const_audio_normalAudioFileMaxDB = 80.0;

//可以处理的音频文件类型
enum class EN_AudioFileType :int
{
	undefine,
	wav,
	mp3,
	flac,
	aac,
};

//一个音频文件格式的标签
struct ST_AudioFileTag
{
	QString				fileName;
	QString				filePath;
	EN_AudioFileType	fileType;
	int					ChannelNum		= -1;
	QTime				Duration		= QTime();
	int					BitRate			= -1;
	int					sampleRate		= -1;
	int					BitBerSample	= -1;	//一个采样点有几个位，一般pcm16编码一个点有16位（2个字节）
};

const int const_PCMS16MaxAmplitude = 32768; // because minimum is -32768
const int const_PCMS16MinAmplitude = -32768; // because minimum is -32768

//读取的wav文件数值，文件里面记得就是这些，这里没有从pcm变成浮点数
struct ST_WavRawData
{
	ST_AudioFileTag		fileTag;
	QVector<int>		LeftChannel;
	QVector<int>		RightChannel;
};

//一个音频采样点
struct ST_AudioPoint
{
	//时间，单位是秒
	double pTime = 0;	

	//幅值，单位是最大振幅（位移量） 
	//对于pcm16而言
	//记录数值为32767	时，这里的幅值为1
	//记录数值为-32768	时，这里的幅值为-1
	double pVal = 0;	
};

//实际分析的对象
//包含原始文件标签
//不同声道的采样点具体信息
//每个采样点包含音频对应的时间和浮点振幅
struct ST_WavDoubleData
{
	ST_AudioFileTag		fileTag;

	QVector<ST_AudioPoint>		LeftChannel;
	QVector<ST_AudioPoint>		RightChannel;
};

//音频信号数据
struct ST_AudioBaseSignalPara
{
	double	baseFrequency		= 100;			//基频频率
	double	startTime			= 0;			//开始时间（s）
	double	signalTimeLength	= 1;			//信号时间长度(s)
	double	amplitude			= 1;			//振幅（强度 μpa）
	int		sampleRate			= 44100;		//采样率
};

//音频信号结果
struct ST_AudioBaseSignal
{
	ST_AudioBaseSignalPara signalPara;
	QVector<ST_AudioPoint> vecPoint;
};

//调制信号波形
enum EN_ModuleSignalType : int
{
	tri_sin,		//正弦
	square			//方波
};

//调制信号数据
struct ST_AudioModuleSignalPara
{
	EN_ModuleSignalType signalType = EN_ModuleSignalType::tri_sin;

	double		moduleFrequency		= 100;			//调制频率
	double		startTime			= 0;			//开始时间（s）
	double		signalTimeLength	= 1;			//信号时间长度(s)
	double		depth				= 100;			//调制度,这是一个百分数
	int			sampleRate			= 441000;		//采样率
};

//音频信号结果
struct ST_AudioModuleSignal
{
	ST_AudioBaseSignalPara		basePara;
	ST_AudioModuleSignalPara	modulePara;
	QVector<ST_AudioPoint>		vecModuleSignal;		//调试信号
	QVector<ST_AudioPoint>		vecModuleResultSignal;	//基频被调制后的结果
};
#pragma endregion

#pragma region FFT + STFT

//用谁的FFT函数
enum EN_FFTType
{
	Zhihu,		//知乎网友
	FFTW,		//FFTW
	CudaFFT		//Cuda
};

//一次FFT分析的参数
struct ST_FFTInputPara
{
	EN_FFTType FFTType	= EN_FFTType::Zhihu;
	double startTime	= 0;		//开始时间（单位：S）
	double inputPointCountInPowerOf2 = 100;		//输入时间对应2的幂  就是输入的点是2的几次方
	double timeLength	= 0;
	double sampleRate	= 44100;	//采样率
};

//一次FFT分析的输入
struct ST_FFTInputData
{
	ST_FFTInputPara para;
	QVector<ST_AudioPoint>	AudioPtVec;					//输入的音频点
};

//FFT结果中一个频率的强度信息
struct ST_FFTPoint
{
	double frequency = 0;	//频率
	double amplitude = 0;	//强度
	double phase	 = 0;	//相位
};

//一次FFT计算结果的描述参数
struct ST_FFTOutputPara
{
	double startFreq	= 0;	//开始频率
	double endFreq		= 0;	//结束频率
	double DeltaFreq	= 0;	//频率间隔

	double maxAmp		= 0;	//最大强度

	double startTime	= 0;	//帧开始时间（单位s）
	double timeLength	= 0;	//描述的时间长度

};

//一次FFT分析的结果
struct ST_FFTOutputData
{
	bool concurentValid = false;	//多线程STFT专用标签
	ST_FFTOutputPara para;
	QVector<ST_FFTPoint> resultVec;
};

//时域窗型
enum class EN_STFTWndType :int
{
	Rect = 0,	//矩形窗，都是1
	Hann = 1,	//Hann窗
};

//时域窗参数
struct ST_STFTWndPara
{
	EN_STFTWndType WndType			= EN_STFTWndType::Rect;
	int				sampleRate		= -1;	//这个窗对应的采样率
	int				pointCount		= -1;	//这个窗口有多少个点
	double			WndMsec			= -1;	//这个窗等价于有多少毫秒
};

//时域窗结果
struct ST_STFTWnd
{
	ST_STFTWndPara WndPara;
	QVector<double> VecWndPt;
};

//时域窗间隔类型
enum EN_STFTWndGapType
{
	timelength,	//依照时间间隔
	WndRatio	//依照窗口尺寸比例
};

//一次STFT分析的输入参数
struct ST_STFTInputpara
{
	
	QString     fileName;					//输入对象名称
	bool		multiThreadMode = false;	//是否多线程，性能测试/实现限制等多方面要素考虑

	//波形参数
	double		startTime = 0;		//开始时间（单位：S）
	double		timeLength = 0;
	double		sampleRate = 44100;	//采样率
	

	//FFT参数
	EN_FFTType	FFTType		= EN_FFTType::Zhihu;//FFT类型
	double		FFTPOW2		= 100;		//FFT 输入时间对应2的幂  就是输入的点是2的几次方


	//窗参数
	ST_STFTWndPara		WndPara;
	EN_STFTWndGapType	WndGapType			= EN_STFTWndGapType::WndRatio;
	double				GapInWndRatio		= 0;	//分析间隔等价于窗的比例尺寸
	double				GapInTimeLength		= 0;	//分析间隔等价于时间的长度（单位：S）

};

//一次STFT分析的输入
struct ST_STFTInputData
{
	ST_STFTInputpara para;
	QVector<ST_AudioPoint> vecPoint;	//具体的音频点
};

//一次STFT分析的输出
struct ST_STFTOutputData
{
	QString DatacenterName;
	ST_STFTInputpara InputPara;	
	QVector<ST_FFTOutputData> vecOutput;
};

#pragma endregion

#pragma region WndSpecConstrain + BDSNR

//时域窗频域分析的参数
struct ST_STFTWndAnsPara
{
	ST_STFTWndPara WndPara;
	int showMaxFreq = 0;
	int showFreqPtCount = 0;
};

//时域窗激发调制函数的参数
struct ST_STFTActiveWndPara
{
	ST_STFTWndPara STFTWndPara;		//STFT窗参数
	double startTimePos = 0;		//激发开始时间（单位：S）
	double startRatioPos = -1;		//激发开始比例
	int    startPointPos = -1;		//激发开始的点位置
	double IncreaseTime = 0;		//上升持续时间（单位：S）
	int    IncreasePtCount = 0;		//上升历经多少个点
};

//时域窗频域分析的参数
struct ST_ActiveWndAnsPara
{
	ST_STFTActiveWndPara WndPara;
	int showMaxFreq			= 0;
	int showFreqPtCount		= 0;
};

//时域窗结果
struct ST_ActvieWnd
{
	ST_STFTActiveWndPara WndPara;
	QVector<double> VecSTFTWndPt;		//STFT窗函数点
	QVector<double> VecActivePt;		//激发调制函数点（上升曲线，没带STFT窗）
	QVector<double> VecActiveWndPt;		//激发窗函数点（上升曲线 X STFT窗函数）
};

//时域窗FFT结果的一个旁瓣（主瓣的宽度是其全宽的一半）
struct ST_STFTWndPart
{
	double PartMaxVal = 0; //旁瓣最大高度
	double PartMaxValFreq = 0; //旁瓣最大高度所在频率
	double PartMaxValPtIndex = 0; //旁瓣最大高度所在容器内的索引
	double PartMaxErrorPercent = 0; //采样频率导致的最大峰值误差比例（损失的比例）
	double PartMaxErrorDb = 0; //采样频率导致的最大峰值误差db（损失的比例）

	double totalRightWidth = 0; //可以统计到的右侧最大宽度（计算辅助用）
	double db10RightWidth = 0; //右侧10db衰减相对峰值位置
	double db20RightWidth = 0; //右侧20db衰减相对峰值位置
	double db30RightWidth = 0; //右侧30db衰减相对峰值位置
};

//时域窗分析结果
struct ST_STFTWndAnsResult
{
	ST_STFTWndAnsPara AnsPara;

	double DeltaFreq = 0;
	double maxAmp = 0;

	QVector<ST_FFTPoint> VecWndFFTPt;
	QVector<ST_STFTWndPart> VecWndFFTPart;

};

//时域窗分析结果
struct ST_ActiveWndAnsResult
{
	ST_ActiveWndAnsPara AnsPara;

	double DeltaFreq	= 0;
	double maxAmp		= 0;

	QVector<ST_FFTPoint> VecWndFFTPt;
};

//窗函数频谱抑制生成控制
struct ST_WndSpecConstrainPara
{
	ST_STFTWndPara WndPara;

	double	ConstrainDBRange = 60;			//基于多大噪声构成抑制范围
	double  PeakValDriftRatio = 0.0;		//峰值频率偏移的比例（相邻第一点随着偏移而增强，此外的峰值不变）
	bool    isForcePt2DBVal = false;		//是否强制指定第二点抑制比例（经验数值）
	double  forcePt2DBVal = 0;
	double  forcePt2Ratio = 0;
	int		startEnhanceSidePos = -1;		//开始增强抑制的点
	double	EnhanceRatio = 1;				//增强抑制比例
};

//窗函数频谱抑制相对参数
struct ST_WndSpecConstrainDistribute
{
	ST_WndSpecConstrainPara GenPara;
	int ConstrainSidePtCount = -1;
	double NoiseUnConstrainFreqInterval = 0;	//两个普函数叠加出现无法抑制的噪声的频率间隔（谱噪声分辨率）
	double NoiseToBeSignalFreqInterval = 0;		//两个普函数叠加使得中间的点已经和两个信号一样大的频率间隔（合并分辨率）

	QVector<double> VecConstrain_PeakRatio;		//旁瓣值相对窗谱峰值的比例
	QVector<double> VecConstrain_PeakDB;		//旁瓣值相对窗谱峰值比例的响度（DB）

	QVector<double> VecConstrain_DriftPeak_Ratio_beforeEnhance;   //增强抑制之前旁瓣值相对便宜峰值的相对值（绝对值比例）
	QVector<double> VecConstrain_DriftPeak_DB_beforeEnhance;	  //增强抑制之前旁瓣值相对便宜峰值的响度（DB）
	QVector<double> VecConstrain_DriftPeak_Ratio_afterEnhance;    //增强抑制之后的相对值（绝对值比例）
	QVector<double> VecConstrain_DriftPeak_DB_AfterEnhance;		  //增强抑制之后的相对值（DB）
};

//窗函数抑制网络对抗结果（过滤窗函数频谱噪声）
enum class EN_WndSepcConstrainState :int
{
	UnderTIQ,				//低于听觉阈值
	WndSpecNoise,			//无效噪声
	EffectiveOscillation,	//有效震荡	
};

//一个点的抑制结果
struct ST_WndSpecConstrainPtTag
{
	double						ptFreq				= -1;
	
	EN_WndSepcConstrainState	ptConstrainState	= EN_WndSepcConstrainState::UnderTIQ;

	double MaxConstrainVal_Compare	= 0;
	double MaxConstrainDB_Compare	= 0;
	int    ConstrainSourceIndex		= -1;
	double ConstrainSourceFreq		= 0;

	int	   affliationMfccFilterIndex = -1;	//随机震荡中被被判定属于哪个MFCC滤波器

};

//一个抑制之后的帧
struct ST_WndSpecConstrainFrame
{
	int FrameIndex = 0;
	QVector<ST_WndSpecConstrainPtTag> VecSTFTPtState;
};

//一个抑制结果
struct ST_WndSpecConstrainResult
{
	QString dataKey;
	ST_WndSpecConstrainDistribute WndConstrainPara;
	QVector<ST_WndSpecConstrainFrame> FrameVec;
};


//滤波器生成参数
struct ST_BandWidthFilterPara
{
	int startFreq = 0;
	int EndFreq = 0;

	int EqualWidthFilterMaxFreq = 0;
	int EqualWidthFilterCount = 0;
	int LogWidthFilterCount = 0;

	//计算频率间隔用的参数
	int sampleRate = 0;
	int WndPtCount = 0;

};

//一个带宽滤波器上某个频率点的权重
struct ST_BandWidthFilterWeightPt
{
	int     ptIndexInFFT = -1;
	double	Freq = 0;
	double	Weight = 0;
};

//一个具体带宽滤波器参数
struct ST_BandWidthFilter
{
	double startFreq	= 0;
	double endFreq		= 0;
	double CenterFreq	= 0;
	double Width		= 0;
	double maxWeight	= 0;
	double centerPtArea = 0; //最大权重点的面积

	int    startFFTPtIndex	= -1;
	int    endFFTPtIndex	= -1;
	QVector<ST_BandWidthFilterWeightPt> FilterPointVec;
};

//帮助STFT点定位带宽滤波器的辅助参数
struct ST_FFTPtInBDFilterLocation
{
	double	FFTPtFreq = 0;
	int		FirstFilterIndex = -1;		//位于哪个滤波器
	int		FirstFilterPtIndex = -1;	//位于滤波器内第几个权重点

	int		SecondFileterIndex = -1;
	int		SecondFilterPtIndex = -1;

	int		ThirdFilterIndex = -1;
	int		ThirdFilterPtIndex = -1;
};

//一组具体的带宽滤波器结构
struct ST_BandWidthFilterData
{
	ST_BandWidthFilterPara para;
	double maxWeight = 0;
	QVector<ST_BandWidthFilter>			FilterVec;				//每个滤波器长啥样
	QVector<ST_FFTPtInBDFilterLocation> FilterFFTPtIndexVec;	//STFT点在滤波器内怎么找滤波器
};

//带宽滤波器带宽内滤波最值来源
enum class EN_BDSNR_FilterMaxValType : int
{
	maxVal,				//最值无权重
	maxVal_Weight		//最值有权中：离得越近权重越高
};

//带宽滤波器滤波方式
enum class EN_BDSNR_FilterCondition : int
{
	filter_strong,	//强滤波：小于任意一个所在滤波器过滤值即过滤
	filter_weak,	//弱滤波：小于所有所在滤波器过滤值才过滤
	filter_weight,	//加权滤波：小于所在滤波器权重滤波值才滤波
};

//带宽SNR滤波工作参数条件
struct ST_BandWidthFilter_workPara
{
	EN_BDSNR_FilterMaxValType FilterMaxValType			= EN_BDSNR_FilterMaxValType::maxVal;
	EN_BDSNR_FilterCondition  FilterCondition_MainArea	= EN_BDSNR_FilterCondition::filter_strong;	//主区域滤波方案
	EN_BDSNR_FilterCondition  FilterCondition_SubArea	= EN_BDSNR_FilterCondition::filter_strong;	//次区域滤波方案

	double					  FilterValDecrease_MainArea_Ratio = 0.1;	//滤波器最值衰减的比例（主对象区）
	double					  FilterValDecrease_MainArea_DB = 0;		//滤波器最值衰减等价的响度值（主对象区）

	double					  FilterValDecrease_SubArea_Ratio	= 0.1;	//滤波器最值衰减的比例（次对象区/环境区）
	double					  FilterValDecrease_SubArea_DB		= 0;	//滤波器最值衰减等价的响度值（次对象区/环境区）
};

//一个带宽滤波器的输出数值
struct ST_BandWidthFilterPt
{
	bool		isActive					= false;	//是否被激活(值输出值大于0DB)

	double		BandWidthMaxAmpIndex		= -1;		//带宽内最值的索引	
	double		BandWidthMaxAmp				= -1;		//带宽内最值（振幅）
	double		BandWidthMaxAmp_DB			= -1;		//带宽内最值（响度）
	
	double		BandWidthMaxWeightAmpIndex	= -1;		//带宽内加权最值的索引
	double		BandWidthMaxWeightAmpWeight = -1;		//带宽内加权最值在滤波器内的权重
	double		BandWidthMaxWeightAmp		= -1;		//带宽内加权最值（振幅）
	double		BandWidthMaxWeightAmp_DB	= -1;		//带宽内加权最值（响度）

	double		BandWidthFilterVal_MainArea		= -1;		//带宽滤波器输出的滤波值（主对象区）
	double		BandWidthFilterVal_MainArea_DB	= -1;		//带宽滤波器输出的滤波值(响度)（主对象区）

	double		BandWidthFilterVal_SubArea		= -1;		//带宽滤波器输出的次区域滤波值（次对象区/环境区）
	double		BandWidthFilterVal_SubArea_DB	= -1;		//带宽滤波器输出的次区域滤波值(响度)（次对象区/环境区）

};

//震荡分类器对点的分类结果（是用STFT还是MFCC）
enum class EN_BDSNRPtType :int
{
	WndSpecNoise,		//有效震荡噪声点（上一级被过滤）
	BDSNR_ConstrainPt,	//信噪比抑制点
	BDSNR_EffectivePt,	//信噪比有效点（非抑制点）
};

//一个点带宽噪声抑制的标记
struct ST_BandWidthSNRPtTag
{
	int			ptIndex = -1;
	double		ptFreq = 0;

	EN_BDSNRPtType ptSNRConstrainType = EN_BDSNRPtType::WndSpecNoise;

	bool		isMainAreaSignal = false;	//是不是主对象区信号，False表示在环境区，这个仅在非抑制信号内有效
	int			MaskedByFilterIndex = -1;
	double		MaskAmp_Main	= 0;
	double		MaskAmp_Sub		= 0;
};

//带宽滤波器输出的一帧
struct ST_BandWidthSNRConstrainFrame
{
	int								FrameInSTFTIndex = -1;	//这一帧对应STFT中的哪一帧
	double							FrameStartTime = -1;	//这一帧起始时间
	QVector<ST_BandWidthFilterPt>	vecBDFilterValue;		//每一个带宽滤波器的值
	QVector<ST_BandWidthSNRPtTag>	vecBDSNRptTag;			//带宽滤波器抑制后的结果
};

//带宽滤波器输出的最终结果
struct ST_BandWidthSNRConstrainData
{
	QString									DataKey;
	ST_BandWidthFilterData					FilterData;
	ST_BandWidthFilter_workPara				WorkPara;
	QVector<ST_BandWidthSNRConstrainFrame>	FrameVec;
};

#pragma endregion


#pragma region Correlation Separation

//差分网络
enum class EN_DiffNetGroupIntervalType
{
	Same,	//等间距
	Double	//双倍
};

//差分网络视为有效点（非零点）从哪开始
enum class EN_DiffNetPtEffectType
{
	STFT,
	EffOsc,
	BDSNR,
};

//差分网络参数，将每一个频率点的变化率分到一个双向的组内
struct ST_DiffNetPara
{
	////双向分组分几组，(-a,a)是第0组,(a,2a)是第1组(-2a,-a)是第-1组
	//第一帧和消失各为额外一组
	int		bidirectionalGroupCount				= 0;		 
	double	BidirectionGroupStartInterval		= 0.00;		//第一组的长度是多少（a/2）

	EN_DiffNetGroupIntervalType IntervalType	= EN_DiffNetGroupIntervalType::Same;
	EN_DiffNetPtEffectType		EffPtType		= EN_DiffNetPtEffectType::STFT;
};

//差分比例的双向分组，除了突然出现的线条以及消失的线条（第一个有效帧），其他的都在这个组内
//这是一个开区间，所以不包含边缘的值
struct ST_DiffNetBiDirectGroup
{
	bool	isASideGroup	= 0;//这是不是一个边缘组，边缘组意味着包含了无穷大或者无穷小的比例
	int		groupIndex		= 0;//组索引，比例区间小于0，就是复数，一正一负（中间）就是0，两个正就是正数，如果是最左/最右的组，那么有一个值会无效，变成0
	double	startRatio		= 0;//区间左边的值/最小值
	double  endRatio		= 0;//区间右边的值/最大值
};

//一个差分网络的最终状态
struct ST_DiffNetState
{
	double		SideStartRatio		= 0;//边缘组从哪一个比例开始
	int			totalGroupCount		= 0;//总共有多少组（包含突然出现的组和消失组）
	QMap<int,ST_DiffNetBiDirectGroup>  mapDiffGroup;//最终每一个线条都会被分到这个组内
};

//这是一个FFT的点还是带宽滤波器
enum class EN_DiffPtType : int
{
	FFTpoint,	//FFT分析输出
	MFCCFilter	//MFCC滤波器
};

//一个差分点
struct ST_DiffNetPoint
{
	double			ptCenterFreq		= 0;
	EN_DiffPtType	ptType				= EN_DiffPtType::FFTpoint;
	
	//对一个线条分类的两类依据
	
	//是不是消失组（额外分组）
	bool			isDisappear = false;
	//是不是突然出现的第一帧（额外分组）
	bool			isSuddenAppear		= false;
	
	//如果既不是消失组，也不是突然出现的组，那么进入下面的分类
	//这一帧和上一帧差值与上一帧的比率，如果是出现的第一帧，那么这个比例是-1;
	
	double			DiffRatio			= 0;	
	double			Diffval				= 0;//这一帧减上一帧的值
	int				BidirectGroupIndex	= 0;//属于双向分组的第几组
	bool			getAGroup			= false;//是否被分组（Debug 参量）
};

//一个差分帧
struct ST_DiffFrame
{
	int FrameInSTFTIndex = 0;
	double FrameStartTime = 0;
	QVector<ST_DiffNetPoint> vecFFTPoint;				//FFT点变化
	QVector<ST_DiffNetPoint> vecBandWidthFilterPoint;	//带宽滤波器变化
};

//一个差分输出
struct ST_DiffNetOutput
{
	QString DataKey;
	ST_DiffNetPara	inputPara;
	ST_DiffNetState DiffNetState;
	QVector<ST_DiffFrame> FrameVec;
};


//倍频张量生成参数
struct ST_FreqMultipleTensorGenPara
{
	int		sampleRate				= 0;//音频采样率
	int		WndPtCount				= 0;//窗函数点数量
	double	MaxEffectFreq			= 0;//最大有效频率（听觉有效范围）
	double	FFTWndPeakDriftRatio	= 0;//窗口屏蔽峰值偏移比率
	double	startFreq				= 0;//张量起始频率
	double	endFreq					= 0;//张量截至频率（有音高的极限频率）
	int		maxMultipleTime			= 0;//允许谐波数量

	bool	isCutOffOnSelOverlappingStartPos = false;//是否去除自交叠区域出现之后的倍频区域

	int		ParentRealtionIncludeStartFreqCount = 0;//父子倍频矩阵关系要求包含前N个谐波的数量
};

//一个倍频点，基于某个基频的N次倍频
struct ST_FreqMultiplePos
{
	int	   multipleTime			= 0;		//这是第几次倍频
	int	   startFreqIndex		= 0;		//实际计算时的起始频率索引(FFT)
	int	   endFreqIndex			= 0;		//实际计算时的结束频率索引(FFT)
	int	   startMatrixIndex		= 0;		//起始对应的倍频矩阵索引（超出矩阵范围就是-1，此时使用FFT索引）
	int	   endMatrixIndex		= 0;		//结束对应的倍频矩阵索引（如果范围超出矩阵，那么就是-1，对于张量频率范围内，使用最大张量范围，在此范围之外，使用FFT索引）

	double ExactStartFreq		= 0;		//范围最小频率（计算精确值）
	double ExactEndFreq			= 0;		//范围最大频率（计算精确值）
	double TruncateStartFreq	= 0;		//范围最小频率（截断值）
	double TruncateEndFreq		= 0;		//范围最大频率（截断值）
};

//因为是一个稀疏矩阵，所以只记录有有效点，不然生成的张量太大了
struct ST_FreqMultipleMaxtrix
{	
	bool	isInsertFreq				= false;	//是不是一个插入频率，这个频率位于两个FFT点的中间，其计算带宽为前后两个点偏移概率去除后的部分

	int		BaseFreqIndex_int		= 0;			//整形基频索引（如果这是一个FFT频率，那么就是索引，对于插入频率，这是-1）
	double  BaseFreqIndex_double	= 0;			//浮点基频索引（如果这是一个插入频率，那么就是对应的索引，如果是FFT存在的频率，那就是-1）
	double	BaseFreq				= 0;			//基频频率
	double	IntervalHalfWidth		= 0;			//区间半宽
	int		totalPtCount_FFT		= 0;			//整个矩阵非零点的数量

	//自交叠出现的第一个倍频次数,这个索引的区域和下一个区域相交
	//这个值是倍频次数，所以-1才是对饮矩阵内的索引
	int		selfOverlappingStartMultipleTime = 0;	

	QVector<ST_FreqMultiplePos> vecMultiplePos;
};

//生成张量的结果参数
struct ST_FreqMultipleTensorResultPara
{	
	double	FFTFreqInterval				= 0;	//FFT的频率间隔
	double	TensorFreqInterval			= 0;	//矩阵之间实际频率间隔

	//张量尺寸
	int		tensorStartFFTFreqIndex		= 0;	//矩阵起始频率索引
	int		tensorEndFFTFreqIndex		= 0;	//矩阵结束频率索引
	double  tensorStartFreqVal			= 0;	//矩阵起始频率值
	double	tensorEndFreqVal			= 0;	//矩阵结束频率值

	int		tensorEffectFFTPtCount		= 0;	//矩阵内一共有多少个频率点(方阵，长宽一样)
	double  tensorMaxEffectFFTPtFreq	= 0;	//矩阵内最大的有效频率
	int		tensorTotalPtCount			= 0;	//张量里面一共有多少点

	double  tensorFillRate				= 0;	//张量填充率
	int     tensorTotalEffectPtCount	= 0;	//张量一共有多少非零点
};

//倍频矩阵中输入来源
enum EN_FMTSourceType :int
{
	EffOsc,
	BDSNR
};

//矩阵激活设定
struct ST_FMTActiveCond
{
	EN_FMTSourceType MatrixActiveSource	= EN_FMTSourceType::EffOsc;	//矩阵激活来源
	EN_FMTSourceType MatrixSearchSource	= EN_FMTSourceType::EffOsc;	//激活矩阵搜索来源

	double	ChildDiffRatioMaxDistance				= 0;
	int		ChildFreqDiffSameGroupTimeCount			= 0;			//构成矩阵要素，要求差分方向累计一致次数
	bool	ChildFreqSplitOnceOnDiffInConsistant	= true;			//矩阵要素差分方向不一致时立刻分离
	int		ChildFreqSplitDiffDirectInconsistCount	= 1;			//矩阵要素，差分方向不一致几次才分离
};

//一个具体的倍频张量
//张量间不同矩阵的间隔是FFT频率的一半，插入中间频率的矩阵，可以有效解决前后频率倍频区域重叠的问题
struct ST_FreqMultipleTensor
{
	ST_FreqMultipleTensorGenPara	GenPara;
	ST_FreqMultipleTensorResultPara resultPara;
	QVector<ST_FreqMultipleMaxtrix> VecMultipleMatrix;
};

//倍频张量输出中的一个父点，和张量中的矩阵一一对应
//可以从属于某一个父矩阵
struct ST_FreqMultipleNetworkParentPt
{
	int		MatrixIndex					= -1;
	bool	isInsertFreq				= false;
	bool	isActive					= false;	//这根线是否被探测到
	bool	HasParent					= false;	//这个线是否被父对象包含
	int		ParentMatrixIndex			= -1;
	int		ActiveMultipleFreqCount		= -1;		//累计获得多少次基频
	int		BaseDiffGroup				= -1;
	double	DiffVal						= 0;
	double  DiffRatio					= 0;
	bool	isDiffSuddenAppear			= false;
};

//倍频张量输出中的一子点，和FFT点一一对应
//可以从属于某个基频矩阵，那个基频矩阵未必是一个FFT点
struct ST_FreqMultipleNetworkChildPt
{
	int		FFTPtIndex			= -1;
	double	centerFreq			= 0;
	
	bool	isActiveBaseFreq	= false;
	bool	HasParentFreq		= false;
	int		ParentMatrixIndex	= -1;
	int		ParentFreqSameDiffGroupTimeCount		= -1;
	int		ParentFreqInconsistDiffGroupTimeCount	= -1;
};

struct ST_FreqDoubleNetworkFrame
{
	int FrameIndex					= -1;
	int ActiveMatrixCount			= -1;
	int MaxActiveMatrixMultipleTime = -1;
	int MaxActiveMatrixIndex		= -1;
	QVector<ST_FreqMultipleNetworkParentPt>	VecParentPt;	//基频矩阵激活情况(和张量中的矩阵一一对应）
	QVector<ST_FreqMultipleNetworkChildPt>	VecChildPt;		//FFT点从属情况,这里点的数量虽然和EFFOSC一样，但是从张量频率范围之外开始才有效
};

struct ST_FreqDoubleNetworkOutput
{
	QString	dataKey;
	ST_FreqMultipleTensor Tensor;
	ST_FMTActiveCond	  ActiveCond;
	QVector<ST_FreqDoubleNetworkFrame>	FrameVec;
};

#pragma endregion

#pragma region Vibrate State Relvance

//震动状态分类阈值
//剧烈上升：[AtkMin , + ∞]
//普通上升：[SusMax , AtkMin]
//普通波动：[SusMin , SusMax]
//普通下降：[- ∞ , SusMin]
struct ST_VibrateStateThreshHold
{
	double AttackMinRatio	= 0; //剧烈上升最小比例，在这个比例之上都是剧烈上升
	double SustainMaxRatio = 0;  //普通波动最大比例，在这个之上进入普通上升
	double SustainMinRatio = 0;  //普通波动最低比例，在这个之上是波动，之下是下降
	//double DecreaseMaxRatio = 0;
};

//一个点的震动状态
enum class EN_VibrateState : int
{
	null,		//无信号，空状态
	Attack,		//剧烈上升，震荡建立
	Increase,	//普通上升
	Sustain,	//维持状态，在一个小范围内波动
	Decrease,	//普通下降
};

//一个信号点的振动状态
//这一定是一个FFT点
struct ST_VibrateStatePt
{
	double  ptFreq = 0;

	//数值差分统计量
	double	EffSigVal = 0;					//有效信号强度 经过去噪后的等效强度（如果被滤掉那么就是0，否则就是原始数值）
	double  FirstOrderDiffVal = 0;			//和上一帧有效信号强度的差分数值	
	double  FirstOrderDiffRatio = 0;		//和上一帧相比的增长比率 如果是第一帧那么这个数值无效

	//基于数值差分的状态推算
	EN_VibrateState ptState = EN_VibrateState::null;//当前帧的状态
	int		PersistentExistFrameCount = 0;	//累计有效存在了多少帧
	int     StatePersisFrame = 0;//当前状态持续了多少帧
	bool	isTransferPt = false;//这一帧和上一帧的状态是否不同 （关键点）

};

struct ST_VibrateStateNetworkFrame
{
	int FrameIndex = -1;
	QVector<ST_VibrateStatePt>	VecVibratePt;	
};

struct ST_VibrateStateNetworkNetworkData
{
	QString	dataKey;
	ST_VibrateStateThreshHold ThreshHold;
	QVector<ST_VibrateStateNetworkFrame>	FrameVec;
};

#pragma endregion

namespace AudioProtocol
{
	QString			boolToStr(bool state);
	QString			AudioFileTypeToStr(EN_AudioFileType fileType);
	EN_AudioFileType AudioFileSuffixToType(QString suffix);

	// Scale PCM value to [-1.0, 1.0]
	qreal pcmToReal(qint16 pcm);

	// Scale real value in [-1.0, 1.0] to PCM
	qint16 realToPcm(qreal real);

	qint64 audioLength(const QAudioFormat& format, qint64 microSeconds);
	qint64 audioDuration(const QAudioFormat& format, qint64 bytes);

	void duplicateAudioVec(const QVector<ST_AudioPoint>& fromVec, QVector<ST_AudioPoint>& toVec);

	bool initSTFTData(int frameCount, int FFTPointInFrame, ST_STFTOutputData& InitData);
	void duplicateSTFTData(const ST_STFTOutputData& fromData, ST_STFTOutputData& toData);

	double fftRealToDB(double fftReal, double maxDb);
	double getFFTRealFromDB(double fftDB, double maxDb);
	double getRelativeDB(double realVal, double maxVal);

	//听觉感知阈值（dB）
	//0     HZ  : 70 db
	//200   HZ  : 15 db
	//500   HZ  : 0  db
	//5000  HZ  : 0  db
	//10000 HZ  : 0  db
	//18000 HZ  : 16 db
	//20000 HZ  : 80 db
	double getHearingThreshHoldInQuietDB(double Freq);

	//检测某个频率点的振幅是否大于听觉阈值
	bool   checkFreqPtUnderTIQ(double Freq,double fftRealVal,double maxDB);

	//求两直线交点，结果存储于 crossPt
	//交点不存在返回false 反之返回true
	//直线1 L1P1 -> L1P2
	//直线2 L2P1 -> L2P2
	bool getTwoLineCrossPoint(QPointF L1P1, QPointF L1P2, QPointF L2P1, QPointF L2P2,QPointF& crossPt);


	

};