#pragma once

#include <QString>
#include <QVector>
#include <QImage>
#include "../../Audio/protocol/protocol_audio.h"

const double const_vision_pi = 3.1415926;

#pragma region ��Ƶ����

//��Ƶ�ļ�����
enum class EN_VideoFileType :int
{
	undefine,
	mp4,
	mkv,
	mov,
	wmv,
	avi,
};

enum class EN_ColorDecodeType : int	//ɫ����ɫ��������
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
	int					width = -1;			//��
	int					height = -1;		//��
	double				frameRate = -1;		//֡��
	QTime				Duration = QTime();	//ʱ��
	int					FrameCount = -1;	//��֡��
	double				time_base = -1;		//ʱ����ף�����ĳһ֡��ʱ��λ���ã�

	QString				pixelFormat;
	QString				colorDecodeType;

	int					BitRate = -1;

	int		IFrameCount = -1;
	int		PFrameCount = -1;
	int		BFrameCount = -1;

};

//���ط�ʽ
enum EN_VideoLoadType : int
{
	DecodeOnly,			//����+����
	LoadOnly,			//������
	DecodeAndLoad	//������
};

//���ؾ������
//û�취ԭʼ4k��Ƶ̫���ˣ� 10s���治�£�ֻ������ѹ��һ��
struct ST_VideoLoadSetting
{
	EN_VideoLoadType	loadType		= EN_VideoLoadType::DecodeOnly;
	int					loadFrameRate	= -1;	//����֡��
	
	QSize				loadFrameSize	= QSize(0,0);//����֡�ߴ�

	int					LoadFrameCount		= -1;//����֡������
	int					LoadFrameCount_I	= -1;//����I֡�ʵ�����
	int					LoadFrameCount_P	= -1;//����P֡�ʵ�����
	int					LoadFrameCount_B	= -1;//����B֡�ʵ�����
};

//h264������ĳһ֡������
enum class EN_VideoH264FrameType : int
{
	I,	//I֡ Intra-coded Frame			�ؼ�֡		����ͼ����Ϣ				������
	P,	//P֡ Predicted Frame			Ԥ��֡		ֻ��¼�仯���õ�����Ϣ		������
	B	//B֡ BidirectionalFrame		˫��Ԥ��֡	ǰ����Ϣ��ϵõ���֡		���
};

//h264������һ֡����Ϣ
struct ST_VideoH264FrameTag
{
	int FrameIndex						= -1;//�ڼ�֡
	EN_VideoH264FrameType frameType		= EN_VideoH264FrameType::I;//֡����

	int width	= -1;	//ͼ���
	int height	= -1;	//ͼ���

	int		FrameTime_Base	= -1;	//����ʱ�������֡�����꣨Ҫ���time_base�������ʱ�䣩
	double	FrameTime_sec	= -1;	//֡��Ӧ��ʱ�䣨��λ��s��
	double	duration_base	= -1;	//֡����ʱ��(��λ��time_base)
	double	duration_sec	= -1;	//֡����ʱ�䣨��λ��s��
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

#pragma region ��ɫ�����ռ�

//��������Ĵ�Сд��
//�����ֵ��Χ��	0-1				����Сд���� ����sRgb/CIExyz
//�����Χ��		0-100������ߣ�	���ô�д��д���� ����QColor/LAB

//srgb��һ���� (0-1)
//һ����Ļ��ʾ�������ֵ��gamma���Ȱ汾
struct ST_sRgbPoint
{
	double r = 0;
	double g = 0;
	double b = 0;
};

//CIE ��ϵ�µ�һ��xyz ���꣨0-1��
struct ST_xyzPoint
{
	double x = 0;
	double y = 0;
	double z = 0;
};

//��μ���LAB�ռ�������ľ���
enum class EN_LAB_Metric_Type :int
{
	CIE_1976,	//LAB����ŷʽ����
	CIE_1984,	//�������
	CIE_1994,	//�򵥺��� ������
	CIE_2000,	//������ϣ�����
};

//CIE LAB��ϵ�µ�һ����ɫ���� ���۵Ŀ��ӷ�Χ�ǣ��������磩
// L���� 0   - 100��
// A����-200 - 200��
// B����-200 - 200��
//sRgb�µ�AB��Χ��������һ��
struct ST_LABPoint
{
	double L = 0;
	double A = 0;
	double B = 0;
};

#pragma endregion

//�Ӿ�ͼ���һ������
struct ST_VisualPixel
{
	QColor		OriginCr;	//ԭʼRGB����
	ST_LABPoint LabVal;		//ת�����Labֵ
};

//�Ӿ����������ͼ��
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