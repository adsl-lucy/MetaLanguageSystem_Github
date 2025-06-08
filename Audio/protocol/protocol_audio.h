#pragma once
#include <QString>
#include <QTime>
#include <QVector>
#include <QAudioFormat>
#include <qDebug>

#pragma region AudioBase

const double const_audio_pi = 3.1415926;

//һ����Ƶ�ļ�Ĭ�ϵ����������ӦDB
const double const_audio_normalAudioFileMaxDB = 80.0;

//���Դ������Ƶ�ļ�����
enum class EN_AudioFileType :int
{
	undefine,
	wav,
	mp3,
	flac,
	aac,
};

//һ����Ƶ�ļ���ʽ�ı�ǩ
struct ST_AudioFileTag
{
	QString				fileName;
	QString				filePath;
	EN_AudioFileType	fileType;
	int					ChannelNum		= -1;
	QTime				Duration		= QTime();
	int					BitRate			= -1;
	int					sampleRate		= -1;
	int					BitBerSample	= -1;	//һ���������м���λ��һ��pcm16����һ������16λ��2���ֽڣ�
};

const int const_PCMS16MaxAmplitude = 32768; // because minimum is -32768
const int const_PCMS16MinAmplitude = -32768; // because minimum is -32768

//��ȡ��wav�ļ���ֵ���ļ�����ǵþ�����Щ������û�д�pcm��ɸ�����
struct ST_WavRawData
{
	ST_AudioFileTag		fileTag;
	QVector<int>		LeftChannel;
	QVector<int>		RightChannel;
};

//һ����Ƶ������
struct ST_AudioPoint
{
	//ʱ�䣬��λ����
	double pTime = 0;	

	//��ֵ����λ����������λ������ 
	//����pcm16����
	//��¼��ֵΪ32767	ʱ������ķ�ֵΪ1
	//��¼��ֵΪ-32768	ʱ������ķ�ֵΪ-1
	double pVal = 0;	
};

//ʵ�ʷ����Ķ���
//����ԭʼ�ļ���ǩ
//��ͬ�����Ĳ����������Ϣ
//ÿ�������������Ƶ��Ӧ��ʱ��͸������
struct ST_WavDoubleData
{
	ST_AudioFileTag		fileTag;

	QVector<ST_AudioPoint>		LeftChannel;
	QVector<ST_AudioPoint>		RightChannel;
};

//��Ƶ�ź�����
struct ST_AudioBaseSignalPara
{
	double	baseFrequency		= 100;			//��ƵƵ��
	double	startTime			= 0;			//��ʼʱ�䣨s��
	double	signalTimeLength	= 1;			//�ź�ʱ�䳤��(s)
	double	amplitude			= 1;			//�����ǿ�� ��pa��
	int		sampleRate			= 44100;		//������
};

//��Ƶ�źŽ��
struct ST_AudioBaseSignal
{
	ST_AudioBaseSignalPara signalPara;
	QVector<ST_AudioPoint> vecPoint;
};

//�����źŲ���
enum EN_ModuleSignalType : int
{
	tri_sin,		//����
	square			//����
};

//�����ź�����
struct ST_AudioModuleSignalPara
{
	EN_ModuleSignalType signalType = EN_ModuleSignalType::tri_sin;

	double		moduleFrequency		= 100;			//����Ƶ��
	double		startTime			= 0;			//��ʼʱ�䣨s��
	double		signalTimeLength	= 1;			//�ź�ʱ�䳤��(s)
	double		depth				= 100;			//���ƶ�,����һ���ٷ���
	int			sampleRate			= 441000;		//������
};

//��Ƶ�źŽ��
struct ST_AudioModuleSignal
{
	ST_AudioBaseSignalPara		basePara;
	ST_AudioModuleSignalPara	modulePara;
	QVector<ST_AudioPoint>		vecModuleSignal;		//�����ź�
	QVector<ST_AudioPoint>		vecModuleResultSignal;	//��Ƶ�����ƺ�Ľ��
};
#pragma endregion

#pragma region FFT + STFT

//��˭��FFT����
enum EN_FFTType
{
	Zhihu,		//֪������
	FFTW,		//FFTW
	CudaFFT		//Cuda
};

//һ��FFT�����Ĳ���
struct ST_FFTInputPara
{
	EN_FFTType FFTType	= EN_FFTType::Zhihu;
	double startTime	= 0;		//��ʼʱ�䣨��λ��S��
	double inputPointCountInPowerOf2 = 100;		//����ʱ���Ӧ2����  ��������ĵ���2�ļ��η�
	double timeLength	= 0;
	double sampleRate	= 44100;	//������
};

//һ��FFT����������
struct ST_FFTInputData
{
	ST_FFTInputPara para;
	QVector<ST_AudioPoint>	AudioPtVec;					//�������Ƶ��
};

//FFT�����һ��Ƶ�ʵ�ǿ����Ϣ
struct ST_FFTPoint
{
	double frequency = 0;	//Ƶ��
	double amplitude = 0;	//ǿ��
	double phase	 = 0;	//��λ
};

//һ��FFT����������������
struct ST_FFTOutputPara
{
	double startFreq	= 0;	//��ʼƵ��
	double endFreq		= 0;	//����Ƶ��
	double DeltaFreq	= 0;	//Ƶ�ʼ��

	double maxAmp		= 0;	//���ǿ��

	double startTime	= 0;	//֡��ʼʱ�䣨��λs��
	double timeLength	= 0;	//������ʱ�䳤��

};

//һ��FFT�����Ľ��
struct ST_FFTOutputData
{
	bool concurentValid = false;	//���߳�STFTר�ñ�ǩ
	ST_FFTOutputPara para;
	QVector<ST_FFTPoint> resultVec;
};

//ʱ����
enum class EN_STFTWndType :int
{
	Rect = 0,	//���δ�������1
	Hann = 1,	//Hann��
};

//ʱ�򴰲���
struct ST_STFTWndPara
{
	EN_STFTWndType WndType			= EN_STFTWndType::Rect;
	int				sampleRate		= -1;	//�������Ӧ�Ĳ�����
	int				pointCount		= -1;	//��������ж��ٸ���
	double			WndMsec			= -1;	//������ȼ����ж��ٺ���
};

//ʱ�򴰽��
struct ST_STFTWnd
{
	ST_STFTWndPara WndPara;
	QVector<double> VecWndPt;
};

//ʱ�򴰼������
enum EN_STFTWndGapType
{
	timelength,	//����ʱ����
	WndRatio	//���մ��ڳߴ����
};

//һ��STFT�������������
struct ST_STFTInputpara
{
	
	QString     fileName;					//�����������
	bool		multiThreadMode = false;	//�Ƿ���̣߳����ܲ���/ʵ�����Ƶȶ෽��Ҫ�ؿ���

	//���β���
	double		startTime = 0;		//��ʼʱ�䣨��λ��S��
	double		timeLength = 0;
	double		sampleRate = 44100;	//������
	

	//FFT����
	EN_FFTType	FFTType		= EN_FFTType::Zhihu;//FFT����
	double		FFTPOW2		= 100;		//FFT ����ʱ���Ӧ2����  ��������ĵ���2�ļ��η�


	//������
	ST_STFTWndPara		WndPara;
	EN_STFTWndGapType	WndGapType			= EN_STFTWndGapType::WndRatio;
	double				GapInWndRatio		= 0;	//��������ȼ��ڴ��ı����ߴ�
	double				GapInTimeLength		= 0;	//��������ȼ���ʱ��ĳ��ȣ���λ��S��

};

//һ��STFT����������
struct ST_STFTInputData
{
	ST_STFTInputpara para;
	QVector<ST_AudioPoint> vecPoint;	//�������Ƶ��
};

//һ��STFT���������
struct ST_STFTOutputData
{
	QString DatacenterName;
	ST_STFTInputpara InputPara;	
	QVector<ST_FFTOutputData> vecOutput;
};

#pragma endregion

#pragma region WndSpecConstrain + BDSNR

//ʱ��Ƶ������Ĳ���
struct ST_STFTWndAnsPara
{
	ST_STFTWndPara WndPara;
	int showMaxFreq = 0;
	int showFreqPtCount = 0;
};

//ʱ�򴰼������ƺ����Ĳ���
struct ST_STFTActiveWndPara
{
	ST_STFTWndPara STFTWndPara;		//STFT������
	double startTimePos = 0;		//������ʼʱ�䣨��λ��S��
	double startRatioPos = -1;		//������ʼ����
	int    startPointPos = -1;		//������ʼ�ĵ�λ��
	double IncreaseTime = 0;		//��������ʱ�䣨��λ��S��
	int    IncreasePtCount = 0;		//�����������ٸ���
};

//ʱ��Ƶ������Ĳ���
struct ST_ActiveWndAnsPara
{
	ST_STFTActiveWndPara WndPara;
	int showMaxFreq			= 0;
	int showFreqPtCount		= 0;
};

//ʱ�򴰽��
struct ST_ActvieWnd
{
	ST_STFTActiveWndPara WndPara;
	QVector<double> VecSTFTWndPt;		//STFT��������
	QVector<double> VecActivePt;		//�������ƺ����㣨�������ߣ�û��STFT����
	QVector<double> VecActiveWndPt;		//�����������㣨�������� X STFT��������
};

//ʱ��FFT�����һ���԰꣨����Ŀ������ȫ���һ�룩
struct ST_STFTWndPart
{
	double PartMaxVal = 0; //�԰����߶�
	double PartMaxValFreq = 0; //�԰����߶�����Ƶ��
	double PartMaxValPtIndex = 0; //�԰����߶����������ڵ�����
	double PartMaxErrorPercent = 0; //����Ƶ�ʵ��µ�����ֵ����������ʧ�ı�����
	double PartMaxErrorDb = 0; //����Ƶ�ʵ��µ�����ֵ���db����ʧ�ı�����

	double totalRightWidth = 0; //����ͳ�Ƶ����Ҳ�����ȣ����㸨���ã�
	double db10RightWidth = 0; //�Ҳ�10db˥����Է�ֵλ��
	double db20RightWidth = 0; //�Ҳ�20db˥����Է�ֵλ��
	double db30RightWidth = 0; //�Ҳ�30db˥����Է�ֵλ��
};

//ʱ�򴰷������
struct ST_STFTWndAnsResult
{
	ST_STFTWndAnsPara AnsPara;

	double DeltaFreq = 0;
	double maxAmp = 0;

	QVector<ST_FFTPoint> VecWndFFTPt;
	QVector<ST_STFTWndPart> VecWndFFTPart;

};

//ʱ�򴰷������
struct ST_ActiveWndAnsResult
{
	ST_ActiveWndAnsPara AnsPara;

	double DeltaFreq	= 0;
	double maxAmp		= 0;

	QVector<ST_FFTPoint> VecWndFFTPt;
};

//������Ƶ���������ɿ���
struct ST_WndSpecConstrainPara
{
	ST_STFTWndPara WndPara;

	double	ConstrainDBRange = 60;			//���ڶ�������������Ʒ�Χ
	double  PeakValDriftRatio = 0.0;		//��ֵƵ��ƫ�Ƶı��������ڵ�һ������ƫ�ƶ���ǿ������ķ�ֵ���䣩
	bool    isForcePt2DBVal = false;		//�Ƿ�ǿ��ָ���ڶ������Ʊ�����������ֵ��
	double  forcePt2DBVal = 0;
	double  forcePt2Ratio = 0;
	int		startEnhanceSidePos = -1;		//��ʼ��ǿ���Ƶĵ�
	double	EnhanceRatio = 1;				//��ǿ���Ʊ���
};

//������Ƶ��������Բ���
struct ST_WndSpecConstrainDistribute
{
	ST_WndSpecConstrainPara GenPara;
	int ConstrainSidePtCount = -1;
	double NoiseUnConstrainFreqInterval = 0;	//�����պ������ӳ����޷����Ƶ�������Ƶ�ʼ�����������ֱ��ʣ�
	double NoiseToBeSignalFreqInterval = 0;		//�����պ�������ʹ���м�ĵ��Ѿ��������ź�һ�����Ƶ�ʼ�����ϲ��ֱ��ʣ�

	QVector<double> VecConstrain_PeakRatio;		//�԰�ֵ��Դ��׷�ֵ�ı���
	QVector<double> VecConstrain_PeakDB;		//�԰�ֵ��Դ��׷�ֵ��������ȣ�DB��

	QVector<double> VecConstrain_DriftPeak_Ratio_beforeEnhance;   //��ǿ����֮ǰ�԰�ֵ��Ա��˷�ֵ�����ֵ������ֵ������
	QVector<double> VecConstrain_DriftPeak_DB_beforeEnhance;	  //��ǿ����֮ǰ�԰�ֵ��Ա��˷�ֵ����ȣ�DB��
	QVector<double> VecConstrain_DriftPeak_Ratio_afterEnhance;    //��ǿ����֮������ֵ������ֵ������
	QVector<double> VecConstrain_DriftPeak_DB_AfterEnhance;		  //��ǿ����֮������ֵ��DB��
};

//��������������Կ���������˴�����Ƶ��������
enum class EN_WndSepcConstrainState :int
{
	UnderTIQ,				//����������ֵ
	WndSpecNoise,			//��Ч����
	EffectiveOscillation,	//��Ч��	
};

//һ��������ƽ��
struct ST_WndSpecConstrainPtTag
{
	double						ptFreq				= -1;
	
	EN_WndSepcConstrainState	ptConstrainState	= EN_WndSepcConstrainState::UnderTIQ;

	double MaxConstrainVal_Compare	= 0;
	double MaxConstrainDB_Compare	= 0;
	int    ConstrainSourceIndex		= -1;
	double ConstrainSourceFreq		= 0;

	int	   affliationMfccFilterIndex = -1;	//������б����ж������ĸ�MFCC�˲���

};

//һ������֮���֡
struct ST_WndSpecConstrainFrame
{
	int FrameIndex = 0;
	QVector<ST_WndSpecConstrainPtTag> VecSTFTPtState;
};

//һ�����ƽ��
struct ST_WndSpecConstrainResult
{
	QString dataKey;
	ST_WndSpecConstrainDistribute WndConstrainPara;
	QVector<ST_WndSpecConstrainFrame> FrameVec;
};


//�˲������ɲ���
struct ST_BandWidthFilterPara
{
	int startFreq = 0;
	int EndFreq = 0;

	int EqualWidthFilterMaxFreq = 0;
	int EqualWidthFilterCount = 0;
	int LogWidthFilterCount = 0;

	//����Ƶ�ʼ���õĲ���
	int sampleRate = 0;
	int WndPtCount = 0;

};

//һ�������˲�����ĳ��Ƶ�ʵ��Ȩ��
struct ST_BandWidthFilterWeightPt
{
	int     ptIndexInFFT = -1;
	double	Freq = 0;
	double	Weight = 0;
};

//һ����������˲�������
struct ST_BandWidthFilter
{
	double startFreq	= 0;
	double endFreq		= 0;
	double CenterFreq	= 0;
	double Width		= 0;
	double maxWeight	= 0;
	double centerPtArea = 0; //���Ȩ�ص�����

	int    startFFTPtIndex	= -1;
	int    endFFTPtIndex	= -1;
	QVector<ST_BandWidthFilterWeightPt> FilterPointVec;
};

//����STFT�㶨λ�����˲����ĸ�������
struct ST_FFTPtInBDFilterLocation
{
	double	FFTPtFreq = 0;
	int		FirstFilterIndex = -1;		//λ���ĸ��˲���
	int		FirstFilterPtIndex = -1;	//λ���˲����ڵڼ���Ȩ�ص�

	int		SecondFileterIndex = -1;
	int		SecondFilterPtIndex = -1;

	int		ThirdFilterIndex = -1;
	int		ThirdFilterPtIndex = -1;
};

//һ�����Ĵ����˲����ṹ
struct ST_BandWidthFilterData
{
	ST_BandWidthFilterPara para;
	double maxWeight = 0;
	QVector<ST_BandWidthFilter>			FilterVec;				//ÿ���˲�����ɶ��
	QVector<ST_FFTPtInBDFilterLocation> FilterFFTPtIndexVec;	//STFT�����˲�������ô���˲���
};

//�����˲����������˲���ֵ��Դ
enum class EN_BDSNR_FilterMaxValType : int
{
	maxVal,				//��ֵ��Ȩ��
	maxVal_Weight		//��ֵ��Ȩ�У����Խ��Ȩ��Խ��
};

//�����˲����˲���ʽ
enum class EN_BDSNR_FilterCondition : int
{
	filter_strong,	//ǿ�˲���С������һ�������˲�������ֵ������
	filter_weak,	//���˲���С�����������˲�������ֵ�Ź���
	filter_weight,	//��Ȩ�˲���С�������˲���Ȩ���˲�ֵ���˲�
};

//����SNR�˲�������������
struct ST_BandWidthFilter_workPara
{
	EN_BDSNR_FilterMaxValType FilterMaxValType			= EN_BDSNR_FilterMaxValType::maxVal;
	EN_BDSNR_FilterCondition  FilterCondition_MainArea	= EN_BDSNR_FilterCondition::filter_strong;	//�������˲�����
	EN_BDSNR_FilterCondition  FilterCondition_SubArea	= EN_BDSNR_FilterCondition::filter_strong;	//�������˲�����

	double					  FilterValDecrease_MainArea_Ratio = 0.1;	//�˲�����ֵ˥���ı���������������
	double					  FilterValDecrease_MainArea_DB = 0;		//�˲�����ֵ˥���ȼ۵����ֵ������������

	double					  FilterValDecrease_SubArea_Ratio	= 0.1;	//�˲�����ֵ˥���ı������ζ�����/��������
	double					  FilterValDecrease_SubArea_DB		= 0;	//�˲�����ֵ˥���ȼ۵����ֵ���ζ�����/��������
};

//һ�������˲����������ֵ
struct ST_BandWidthFilterPt
{
	bool		isActive					= false;	//�Ƿ񱻼���(ֵ���ֵ����0DB)

	double		BandWidthMaxAmpIndex		= -1;		//��������ֵ������	
	double		BandWidthMaxAmp				= -1;		//��������ֵ�������
	double		BandWidthMaxAmp_DB			= -1;		//��������ֵ����ȣ�
	
	double		BandWidthMaxWeightAmpIndex	= -1;		//�����ڼ�Ȩ��ֵ������
	double		BandWidthMaxWeightAmpWeight = -1;		//�����ڼ�Ȩ��ֵ���˲����ڵ�Ȩ��
	double		BandWidthMaxWeightAmp		= -1;		//�����ڼ�Ȩ��ֵ�������
	double		BandWidthMaxWeightAmp_DB	= -1;		//�����ڼ�Ȩ��ֵ����ȣ�

	double		BandWidthFilterVal_MainArea		= -1;		//�����˲���������˲�ֵ������������
	double		BandWidthFilterVal_MainArea_DB	= -1;		//�����˲���������˲�ֵ(���)������������

	double		BandWidthFilterVal_SubArea		= -1;		//�����˲�������Ĵ������˲�ֵ���ζ�����/��������
	double		BandWidthFilterVal_SubArea_DB	= -1;		//�����˲�������Ĵ������˲�ֵ(���)���ζ�����/��������

};

//�𵴷������Ե�ķ�����������STFT����MFCC��
enum class EN_BDSNRPtType :int
{
	WndSpecNoise,		//��Ч�������㣨��һ�������ˣ�
	BDSNR_ConstrainPt,	//��������Ƶ�
	BDSNR_EffectivePt,	//�������Ч�㣨�����Ƶ㣩
};

//һ��������������Ƶı��
struct ST_BandWidthSNRPtTag
{
	int			ptIndex = -1;
	double		ptFreq = 0;

	EN_BDSNRPtType ptSNRConstrainType = EN_BDSNRPtType::WndSpecNoise;

	bool		isMainAreaSignal = false;	//�ǲ������������źţ�False��ʾ�ڻ�������������ڷ������ź�����Ч
	int			MaskedByFilterIndex = -1;
	double		MaskAmp_Main	= 0;
	double		MaskAmp_Sub		= 0;
};

//�����˲��������һ֡
struct ST_BandWidthSNRConstrainFrame
{
	int								FrameInSTFTIndex = -1;	//��һ֡��ӦSTFT�е���һ֡
	double							FrameStartTime = -1;	//��һ֡��ʼʱ��
	QVector<ST_BandWidthFilterPt>	vecBDFilterValue;		//ÿһ�������˲�����ֵ
	QVector<ST_BandWidthSNRPtTag>	vecBDSNRptTag;			//�����˲������ƺ�Ľ��
};

//�����˲�����������ս��
struct ST_BandWidthSNRConstrainData
{
	QString									DataKey;
	ST_BandWidthFilterData					FilterData;
	ST_BandWidthFilter_workPara				WorkPara;
	QVector<ST_BandWidthSNRConstrainFrame>	FrameVec;
};

#pragma endregion


#pragma region Correlation Separation

//�������
enum class EN_DiffNetGroupIntervalType
{
	Same,	//�ȼ��
	Double	//˫��
};

//���������Ϊ��Ч�㣨����㣩���Ŀ�ʼ
enum class EN_DiffNetPtEffectType
{
	STFT,
	EffOsc,
	BDSNR,
};

//��������������ÿһ��Ƶ�ʵ�ı仯�ʷֵ�һ��˫�������
struct ST_DiffNetPara
{
	////˫�����ּ��飬(-a,a)�ǵ�0��,(a,2a)�ǵ�1��(-2a,-a)�ǵ�-1��
	//��һ֡����ʧ��Ϊ����һ��
	int		bidirectionalGroupCount				= 0;		 
	double	BidirectionGroupStartInterval		= 0.00;		//��һ��ĳ����Ƕ��٣�a/2��

	EN_DiffNetGroupIntervalType IntervalType	= EN_DiffNetGroupIntervalType::Same;
	EN_DiffNetPtEffectType		EffPtType		= EN_DiffNetPtEffectType::STFT;
};

//��ֱ�����˫����飬����ͻȻ���ֵ������Լ���ʧ����������һ����Ч֡���������Ķ����������
//����һ�������䣬���Բ�������Ե��ֵ
struct ST_DiffNetBiDirectGroup
{
	bool	isASideGroup	= 0;//���ǲ���һ����Ե�飬��Ե����ζ�Ű�����������������С�ı���
	int		groupIndex		= 0;//����������������С��0�����Ǹ�����һ��һ�����м䣩����0���������������������������/���ҵ��飬��ô��һ��ֵ����Ч�����0
	double	startRatio		= 0;//������ߵ�ֵ/��Сֵ
	double  endRatio		= 0;//�����ұߵ�ֵ/���ֵ
};

//һ��������������״̬
struct ST_DiffNetState
{
	double		SideStartRatio		= 0;//��Ե�����һ��������ʼ
	int			totalGroupCount		= 0;//�ܹ��ж����飨����ͻȻ���ֵ������ʧ�飩
	QMap<int,ST_DiffNetBiDirectGroup>  mapDiffGroup;//����ÿһ���������ᱻ�ֵ��������
};

//����һ��FFT�ĵ㻹�Ǵ����˲���
enum class EN_DiffPtType : int
{
	FFTpoint,	//FFT�������
	MFCCFilter	//MFCC�˲���
};

//һ����ֵ�
struct ST_DiffNetPoint
{
	double			ptCenterFreq		= 0;
	EN_DiffPtType	ptType				= EN_DiffPtType::FFTpoint;
	
	//��һ�������������������
	
	//�ǲ�����ʧ�飨������飩
	bool			isDisappear = false;
	//�ǲ���ͻȻ���ֵĵ�һ֡��������飩
	bool			isSuddenAppear		= false;
	
	//����Ȳ�����ʧ�飬Ҳ����ͻȻ���ֵ��飬��ô��������ķ���
	//��һ֡����һ֡��ֵ����һ֡�ı��ʣ�����ǳ��ֵĵ�һ֡����ô���������-1;
	
	double			DiffRatio			= 0;	
	double			Diffval				= 0;//��һ֡����һ֡��ֵ
	int				BidirectGroupIndex	= 0;//����˫�����ĵڼ���
	bool			getAGroup			= false;//�Ƿ񱻷��飨Debug ������
};

//һ�����֡
struct ST_DiffFrame
{
	int FrameInSTFTIndex = 0;
	double FrameStartTime = 0;
	QVector<ST_DiffNetPoint> vecFFTPoint;				//FFT��仯
	QVector<ST_DiffNetPoint> vecBandWidthFilterPoint;	//�����˲����仯
};

//һ��������
struct ST_DiffNetOutput
{
	QString DataKey;
	ST_DiffNetPara	inputPara;
	ST_DiffNetState DiffNetState;
	QVector<ST_DiffFrame> FrameVec;
};


//��Ƶ�������ɲ���
struct ST_FreqMultipleTensorGenPara
{
	int		sampleRate				= 0;//��Ƶ������
	int		WndPtCount				= 0;//������������
	double	MaxEffectFreq			= 0;//�����ЧƵ�ʣ�������Ч��Χ��
	double	FFTWndPeakDriftRatio	= 0;//�������η�ֵƫ�Ʊ���
	double	startFreq				= 0;//������ʼƵ��
	double	endFreq					= 0;//��������Ƶ�ʣ������ߵļ���Ƶ�ʣ�
	int		maxMultipleTime			= 0;//����г������

	bool	isCutOffOnSelOverlappingStartPos = false;//�Ƿ�ȥ���Խ����������֮��ı�Ƶ����

	int		ParentRealtionIncludeStartFreqCount = 0;//���ӱ�Ƶ�����ϵҪ�����ǰN��г��������
};

//һ����Ƶ�㣬����ĳ����Ƶ��N�α�Ƶ
struct ST_FreqMultiplePos
{
	int	   multipleTime			= 0;		//���ǵڼ��α�Ƶ
	int	   startFreqIndex		= 0;		//ʵ�ʼ���ʱ����ʼƵ������(FFT)
	int	   endFreqIndex			= 0;		//ʵ�ʼ���ʱ�Ľ���Ƶ������(FFT)
	int	   startMatrixIndex		= 0;		//��ʼ��Ӧ�ı�Ƶ������������������Χ����-1����ʱʹ��FFT������
	int	   endMatrixIndex		= 0;		//������Ӧ�ı�Ƶ���������������Χ����������ô����-1����������Ƶ�ʷ�Χ�ڣ�ʹ�����������Χ���ڴ˷�Χ֮�⣬ʹ��FFT������

	double ExactStartFreq		= 0;		//��Χ��СƵ�ʣ����㾫ȷֵ��
	double ExactEndFreq			= 0;		//��Χ���Ƶ�ʣ����㾫ȷֵ��
	double TruncateStartFreq	= 0;		//��Χ��СƵ�ʣ��ض�ֵ��
	double TruncateEndFreq		= 0;		//��Χ���Ƶ�ʣ��ض�ֵ��
};

//��Ϊ��һ��ϡ���������ֻ��¼����Ч�㣬��Ȼ���ɵ�����̫����
struct ST_FreqMultipleMaxtrix
{	
	bool	isInsertFreq				= false;	//�ǲ���һ������Ƶ�ʣ����Ƶ��λ������FFT����м䣬��������Ϊǰ��������ƫ�Ƹ���ȥ����Ĳ���

	int		BaseFreqIndex_int		= 0;			//���λ�Ƶ�������������һ��FFTƵ�ʣ���ô�������������ڲ���Ƶ�ʣ�����-1��
	double  BaseFreqIndex_double	= 0;			//�����Ƶ�������������һ������Ƶ�ʣ���ô���Ƕ�Ӧ�������������FFT���ڵ�Ƶ�ʣ��Ǿ���-1��
	double	BaseFreq				= 0;			//��ƵƵ��
	double	IntervalHalfWidth		= 0;			//������
	int		totalPtCount_FFT		= 0;			//�����������������

	//�Խ������ֵĵ�һ����Ƶ����,����������������һ�������ཻ
	//���ֵ�Ǳ�Ƶ����������-1���Ƕ��������ڵ�����
	int		selfOverlappingStartMultipleTime = 0;	

	QVector<ST_FreqMultiplePos> vecMultiplePos;
};

//���������Ľ������
struct ST_FreqMultipleTensorResultPara
{	
	double	FFTFreqInterval				= 0;	//FFT��Ƶ�ʼ��
	double	TensorFreqInterval			= 0;	//����֮��ʵ��Ƶ�ʼ��

	//�����ߴ�
	int		tensorStartFFTFreqIndex		= 0;	//������ʼƵ������
	int		tensorEndFFTFreqIndex		= 0;	//�������Ƶ������
	double  tensorStartFreqVal			= 0;	//������ʼƵ��ֵ
	double	tensorEndFreqVal			= 0;	//�������Ƶ��ֵ

	int		tensorEffectFFTPtCount		= 0;	//������һ���ж��ٸ�Ƶ�ʵ�(���󣬳���һ��)
	double  tensorMaxEffectFFTPtFreq	= 0;	//������������ЧƵ��
	int		tensorTotalPtCount			= 0;	//��������һ���ж��ٵ�

	double  tensorFillRate				= 0;	//���������
	int     tensorTotalEffectPtCount	= 0;	//����һ���ж��ٷ����
};

//��Ƶ������������Դ
enum EN_FMTSourceType :int
{
	EffOsc,
	BDSNR
};

//���󼤻��趨
struct ST_FMTActiveCond
{
	EN_FMTSourceType MatrixActiveSource	= EN_FMTSourceType::EffOsc;	//���󼤻���Դ
	EN_FMTSourceType MatrixSearchSource	= EN_FMTSourceType::EffOsc;	//�������������Դ

	double	ChildDiffRatioMaxDistance				= 0;
	int		ChildFreqDiffSameGroupTimeCount			= 0;			//���ɾ���Ҫ�أ�Ҫ���ַ����ۼ�һ�´���
	bool	ChildFreqSplitOnceOnDiffInConsistant	= true;			//����Ҫ�ز�ַ���һ��ʱ���̷���
	int		ChildFreqSplitDiffDirectInconsistCount	= 1;			//����Ҫ�أ���ַ���һ�¼��βŷ���
};

//һ������ı�Ƶ����
//�����䲻ͬ����ļ����FFTƵ�ʵ�һ�룬�����м�Ƶ�ʵľ��󣬿�����Ч���ǰ��Ƶ�ʱ�Ƶ�����ص�������
struct ST_FreqMultipleTensor
{
	ST_FreqMultipleTensorGenPara	GenPara;
	ST_FreqMultipleTensorResultPara resultPara;
	QVector<ST_FreqMultipleMaxtrix> VecMultipleMatrix;
};

//��Ƶ��������е�һ�����㣬�������еľ���һһ��Ӧ
//���Դ�����ĳһ��������
struct ST_FreqMultipleNetworkParentPt
{
	int		MatrixIndex					= -1;
	bool	isInsertFreq				= false;
	bool	isActive					= false;	//������Ƿ�̽�⵽
	bool	HasParent					= false;	//������Ƿ񱻸��������
	int		ParentMatrixIndex			= -1;
	int		ActiveMultipleFreqCount		= -1;		//�ۼƻ�ö��ٴλ�Ƶ
	int		BaseDiffGroup				= -1;
	double	DiffVal						= 0;
	double  DiffRatio					= 0;
	bool	isDiffSuddenAppear			= false;
};

//��Ƶ��������е�һ�ӵ㣬��FFT��һһ��Ӧ
//���Դ�����ĳ����Ƶ�����Ǹ���Ƶ����δ����һ��FFT��
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
	QVector<ST_FreqMultipleNetworkParentPt>	VecParentPt;	//��Ƶ���󼤻����(�������еľ���һһ��Ӧ��
	QVector<ST_FreqMultipleNetworkChildPt>	VecChildPt;		//FFT��������,������������Ȼ��EFFOSCһ�������Ǵ�����Ƶ�ʷ�Χ֮�⿪ʼ����Ч
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

//��״̬������ֵ
//����������[AtkMin , + ��]
//��ͨ������[SusMax , AtkMin]
//��ͨ������[SusMin , SusMax]
//��ͨ�½���[- �� , SusMin]
struct ST_VibrateStateThreshHold
{
	double AttackMinRatio	= 0; //����������С���������������֮�϶��Ǿ�������
	double SustainMaxRatio = 0;  //��ͨ�����������������֮�Ͻ�����ͨ����
	double SustainMinRatio = 0;  //��ͨ������ͱ����������֮���ǲ�����֮�����½�
	//double DecreaseMaxRatio = 0;
};

//һ�������״̬
enum class EN_VibrateState : int
{
	null,		//���źţ���״̬
	Attack,		//�����������𵴽���
	Increase,	//��ͨ����
	Sustain,	//ά��״̬����һ��С��Χ�ڲ���
	Decrease,	//��ͨ�½�
};

//һ���źŵ����״̬
//��һ����һ��FFT��
struct ST_VibrateStatePt
{
	double  ptFreq = 0;

	//��ֵ���ͳ����
	double	EffSigVal = 0;					//��Ч�ź�ǿ�� ����ȥ���ĵ�Чǿ�ȣ�������˵���ô����0���������ԭʼ��ֵ��
	double  FirstOrderDiffVal = 0;			//����һ֡��Ч�ź�ǿ�ȵĲ����ֵ	
	double  FirstOrderDiffRatio = 0;		//����һ֡��ȵ��������� ����ǵ�һ֡��ô�����ֵ��Ч

	//������ֵ��ֵ�״̬����
	EN_VibrateState ptState = EN_VibrateState::null;//��ǰ֡��״̬
	int		PersistentExistFrameCount = 0;	//�ۼ���Ч�����˶���֡
	int     StatePersisFrame = 0;//��ǰ״̬�����˶���֡
	bool	isTransferPt = false;//��һ֡����һ֡��״̬�Ƿ�ͬ ���ؼ��㣩

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

	//������֪��ֵ��dB��
	//0     HZ  : 70 db
	//200   HZ  : 15 db
	//500   HZ  : 0  db
	//5000  HZ  : 0  db
	//10000 HZ  : 0  db
	//18000 HZ  : 16 db
	//20000 HZ  : 80 db
	double getHearingThreshHoldInQuietDB(double Freq);

	//���ĳ��Ƶ�ʵ������Ƿ����������ֵ
	bool   checkFreqPtUnderTIQ(double Freq,double fftRealVal,double maxDB);

	//����ֱ�߽��㣬����洢�� crossPt
	//���㲻���ڷ���false ��֮����true
	//ֱ��1 L1P1 -> L1P2
	//ֱ��2 L2P1 -> L2P2
	bool getTwoLineCrossPoint(QPointF L1P1, QPointF L1P2, QPointF L2P1, QPointF L2P2,QPointF& crossPt);


	

};