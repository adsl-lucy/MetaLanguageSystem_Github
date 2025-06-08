#include "./protocol_vision.h"

QString VisionProtocol::boolToStr(bool state)
{
	return state ? QString("true") : QString("false");
}

double VisionProtocol::ArcToDegree(double Arc)
{
	return ((Arc / const_vision_pi) * 180.0);
}

double VisionProtocol::DegreeToArc(double Degree)
{
	return  (Degree / 180.0) * const_vision_pi;
}


EN_VideoFileType VisionProtocol::VedioFileSuffixToFileType(QString suffix)
{
	EN_VideoFileType fileType;

	if (suffix == QString("mp4"))
	{
		fileType = EN_VideoFileType::mp4;
	}
	else if (suffix == QString("mkv"))
	{
		fileType = EN_VideoFileType::mkv;
	}
	else if (suffix == QString("mov"))
	{
		fileType = EN_VideoFileType::mov;
	}
	else if (suffix == QString("wmv"))
	{
		fileType = EN_VideoFileType::wmv;
	}
	else if (suffix == QString("avi"))
	{
		fileType = EN_VideoFileType::avi;
	}
	else
	{
		fileType = EN_VideoFileType::undefine;
	}
	return fileType;
}

QString VisionProtocol::VedioFileTypeToSuffix(const EN_VideoFileType fileType)
{
	switch (fileType)
	{
		case EN_VideoFileType::mp4:return QString("mp4");
		case EN_VideoFileType::mkv:return QString("mkv");
		case EN_VideoFileType::mov:return QString("mov");
		case EN_VideoFileType::wmv:return QString("wmv");
		case EN_VideoFileType::avi:return QString("avi");
	}
	return QString("undefine");
}

int  VisionProtocol::getVideoLoadFrameCount(const ST_VideoFileTag& FileTag, const ST_VideoLoadSetting LoadSetting)
{
	int frameCount = (double)FileTag.FrameCount * ((double)LoadSetting.loadFrameRate / (double)FileTag.frameRate);
	return frameCount;
}

void VisionProtocol::initVideoData(const ST_VideoFileTag& FileTag, const ST_VideoLoadSetting LoadSetting, ST_VideoH264VisionData& data)
{
	data.FileTag = FileTag;
	data.LoadSetting = LoadSetting;
	ST_VideoH264Frame nullFrame;
	data.FrameVec.clear();

	int loadFrameCount = getVideoLoadFrameCount(FileTag, LoadSetting);

	data.FrameVec = QVector<ST_VideoH264Frame>(loadFrameCount, nullFrame);
}

QString VisionProtocol::FrameTypeToStr(EN_VideoH264FrameType FrameType)
{
	switch (FrameType)
	{
		case EN_VideoH264FrameType::I:return QString("I");
		case EN_VideoH264FrameType::P:return QString("P");
		case EN_VideoH264FrameType::B:return QString("B");
	}
	return QString("undefine");
}