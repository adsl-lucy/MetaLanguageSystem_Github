#pragma once

#include <QString>
#include <QVector>
#include <QImage>
#include "../../Audio/protocol/protocol_audio.h"

const double const_vision_pi = 3.1415926;

#pragma region 视频解码

//视频文件类型
enum class EN_VideoFileType :int
{
	undefine,
	mp4,
	mkv,
	mov,
	wmv,
	avi,
};

enum class EN_ColorDecodeType : int	//色域：颜色编码类型
{
	BT2020_HDR,
	BT709_SDR,
	DCI_P3,
	REC709_HDTV,
	NTSC
};

struct ST_VideoFileTag
{
	QString				fileName;
	QString				filePath;
	EN_VideoFileType	fileType;

	QString				codec;
	int					width = -1;			//宽
	int					height = -1;		//高
	double				frameRate = -1;		//帧率
	QTime				Duration = QTime();	//时长
	int					FrameCount = -1;	//总帧数
	double				time_base = -1;		//时间基底（计算某一帧的时间位置用）

	QString				pixelFormat;
	QString				colorDecodeType;

	int					BitRate = -1;

	int		IFrameCount = -1;
	int		PFrameCount = -1;
	int		BFrameCount = -1;

};

//加载方式
enum EN_VideoLoadType : int
{
	DecodeOnly,			//解码+加载
	LoadOnly,			//仅加载
	DecodeAndLoad	//仅解码
};

//加载具体参数
//没办法原始4k视频太大了， 10s都存不下，只能这样压缩一下
struct ST_VideoLoadSetting
{
	EN_VideoLoadType	loadType		= EN_VideoLoadType::DecodeOnly;
	int					loadFrameRate	= -1;	//导入帧率
	
	QSize				loadFrameSize	= QSize(0,0);//导入帧尺寸

	int					LoadFrameCount		= -1;//导入帧的总数
	int					LoadFrameCount_I	= -1;//导入I帧率的总数
	int					LoadFrameCount_P	= -1;//导入P帧率的总数
	int					LoadFrameCount_B	= -1;//导入B帧率的总数
};

//h264编码下某一帧的类型
enum class EN_VideoH264FrameType : int
{
	I,	//I帧 Intra-coded Frame			关键帧		完整图像信息				最清晰
	P,	//P帧 Predicted Frame			预测帧		只记录变化量得到的信息		次清晰
	B	//B帧 BidirectionalFrame		双向预测帧	前后信息结合得到的帧		最糊
};

//h264编码下一帧的信息
struct ST_VideoH264FrameTag
{
	int FrameIndex						= -1;//第几帧
	EN_VideoH264FrameType frameType		= EN_VideoH264FrameType::I;//帧类型

	int width	= -1;	//图像宽
	int height	= -1;	//图像高

	int		FrameTime_Base	= -1;	//基于时间基地下帧的坐标（要结合time_base计算具体时间）
	double	FrameTime_sec	= -1;	//帧对应的时间（单位：s）
	double	duration_base	= -1;	//帧持续时间(单位：time_base)
	double	duration_sec	= -1;	//帧持续时间（单位：s）
};

struct ST_VideoH264Frame
{
	ST_VideoH264FrameTag FrameTag;
	QImage	Frame;
};

//
struct ST_VideoH264VisionData
{
	ST_VideoFileTag FileTag;
	ST_VideoLoadSetting LoadSetting;
	QVector<ST_VideoH264Frame> FrameVec;
};

struct ST_VideoH264Data
{
	ST_VideoH264VisionData	VisionData;
	ST_WavDoubleData		AudioData;
};
#pragma endregion

#pragma region 颜色度量空间

//关于坐标的大小写：
//如果数值范围是	0-1				就用小写坐标 比如sRgb/CIExyz
//如果范围是		0-100（或更高）	就用大写大写坐标 比如QColor/LAB

//srgb的一个点 (0-1)
//一般屏幕显示的是这个值的gamma亮度版本
struct ST_sRgbPoint
{
	double r = 0;
	double g = 0;
	double b = 0;
};

//CIE 体系下的一个xyz 坐标（0-1）
struct ST_xyzPoint
{
	double x = 0;
	double y = 0;
	double z = 0;
};

//如何计算LAB空间两个点的距离
enum class EN_LAB_Metric_Type :int
{
	CIE_1976,	//LAB坐标欧式距离
	CIE_1984,	//抽象拟合
	CIE_1994,	//简单好用 就你了
	CIE_2000,	//逆天拟合，废弃
};

//CIE LAB体系下的一个颜色坐标 人眼的可视范围是（物理世界）
// L：（ 0   - 100）
// A：（-200 - 200）
// B：（-200 - 200）
//sRgb下的AB范围差不多上面的一半
struct ST_LABPoint
{
	double L = 0;
	double A = 0;
	double B = 0;
};

#pragma endregion

//视觉图像的一个像素
struct ST_VisualPixel
{
	QColor		OriginCr;	//原始RGB数据
	ST_LABPoint LabVal;		//转化后的Lab值
};

//视觉处理输入的图像
struct ST_VisualImage
{
	QString fileName;
	QSize	ImageSize;
	QImage  Img_Origin;
	QImage  Img_Lab_L;
	QVector<QVector<ST_VisualPixel>> pixelVec;
};


namespace VisionProtocol
{
	QString			boolToStr(bool state);
	double			ArcToDegree(double Arc);
	double			DegreeToArc(double Degree);

	EN_VideoFileType VedioFileSuffixToFileType(QString suffix);
	QString VedioFileTypeToSuffix(const EN_VideoFileType fileType);

	int  getVideoLoadFrameCount(const ST_VideoFileTag& FileTag, const ST_VideoLoadSetting LoadSetting);
	void initVideoData(const ST_VideoFileTag& FileTag, const ST_VideoLoadSetting LoadSetting, ST_VideoH264VisionData& data);

	QString FrameTypeToStr(EN_VideoH264FrameType FrameType);

};