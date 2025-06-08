#include "FFMpegManager.h"
#pragma execution_character_set("utf-8")

FFMpegManager* FFMpegManager::m_instance = nullptr;

FFMpegManager* FFMpegManager::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new FFMpegManager();
	}
	return m_instance;
}

FFMpegManager::FFMpegManager() :QObject(nullptr)
{
	m_pLoadVideoFrameTagThread = new LoadVideoFrameTagThread(this);
	connect(m_pLoadVideoFrameTagThread, &LoadVideoFrameTagThread::sgn_loadTagState, this, &FFMpegManager::sgn_loadVideoTagState);
	connect(m_pLoadVideoFrameTagThread, &LoadVideoFrameTagThread::sgn_loadTagFinished, this, &FFMpegManager::slot_loadVideoFrameTagFinished);

	m_pExtractAudioThread = new ExtractAudioThread(this);
	connect(m_pExtractAudioThread,&ExtractAudioThread::sgn_loadState,this,&FFMpegManager::slot_updateExtractAudioLoadState);

	m_pLoadVideoFrameImageThread = LoadVideoFrameImageThread::instance();
	connect(m_pLoadVideoFrameImageThread, &LoadVideoFrameImageThread::sgn_VideoFrameLoadState, this, &FFMpegManager::sgn_VideoFrameLoadState);
	connect(m_pLoadVideoFrameImageThread, &LoadVideoFrameImageThread::sgn_VideoLoadFinished, this, &FFMpegManager::sgn_VideoLoadFinished);

}

bool FFMpegManager::checkFFMpegState()
{
	QString currentAPPDir = QApplication::applicationDirPath();
	QString ffmpegPath = QString("/ThirdParty/ffmpeg.exe");
	m_strFFMpegPath = currentAPPDir + ffmpegPath;
	bool programeState = QFile::exists(m_strFFMpegPath);
	return programeState;

}

bool FFMpegManager::checkFFProbeState()
{
	QString currentAPPDir = QApplication::applicationDirPath();
	QString ffProbePath = QString("/ThirdParty/ffprobe.exe");
	m_strFFProbePath = currentAPPDir + ffProbePath;
	bool programeState = QFile::exists(m_strFFProbePath);
	return programeState;
}

const ST_AudioFileTag FFMpegManager::getNormalAudioFileTag(QString AudioFilePath, bool& processState)
{
	ST_AudioFileTag resultTag;
	QFileInfo AudioFileInfo(AudioFilePath);
	resultTag.fileName = AudioFileInfo.baseName();
	resultTag.filePath = AudioFileInfo.absolutePath();
	resultTag.fileType = getAudioFileType(AudioFilePath);

	QFileInfo ffProbeInfo(m_strFFProbePath);
	QString ffProbeName			= ffProbeInfo.baseName();
	QString ffProbePath			= ffProbeInfo.absolutePath();
	QString targetProcessPath	= ffProbePath + "/" + ffProbeName;

	QProcess ffProbeProgess;
	QStringList arguments;
	arguments << "-hide_banner"<<"-show_format" << "-show_streams" << "-print_format" << "json" << AudioFilePath;
	ffProbeProgess.start(targetProcessPath, arguments);

	if (!ffProbeProgess.waitForStarted())
	{
		processState = false;
		return resultTag;
	}
	
	if (!ffProbeProgess.waitForFinished())
	{
		processState = false;
		return resultTag;
	}
	
	QByteArray standardData		= ffProbeProgess.readAllStandardOutput();
	QByteArray errorData		= ffProbeProgess.readAllStandardError();
	QByteArray allData			= ffProbeProgess.readAll();


	qDebug() << "Progress Data:"	<< standardData;
	qDebug() << "error Data:"		<< errorData;
	qDebug() << "all Data:"			<< allData;

	QJsonDocument	resultJsonDoc	= QJsonDocument::fromJson(standardData);
	QJsonObject		decodeDataObj(resultJsonDoc.object());
	QJsonArray	    streamArray		= decodeDataObj["streams"].toArray();

	for (int streamIndex = 0; streamIndex < streamArray.size(); streamIndex++)
	{
		QJsonObject streamObject = streamArray[streamIndex].toObject();
		QString streamTypeStr = streamObject["codec_type"].toString();

		if (streamTypeStr != QString("audio"))
		{
			continue;
		}

		FFProbedStreamJsonObjToAudioTag(decodeDataObj, streamObject, resultTag);

		processState = true;
		break;
	}
	
	return resultTag;

}

void FFMpegManager::FFProbedStreamJsonObjToAudioTag(QJsonObject& decodeDataObj, QJsonObject& streamObject, ST_AudioFileTag& resultTag)
{
	double durationSec		= streamObject["duration"].toString().toDouble();
	resultTag.Duration		= QTime(0, 0, 0).addMSecs(durationSec * 1000);
	resultTag.sampleRate	= streamObject["sample_rate"].toString().toInt();
	resultTag.ChannelNum	= streamObject["channels"].toInt();

	switch (resultTag.fileType)
	{
		case EN_AudioFileType::wav:
		{
			resultTag.BitBerSample = streamObject["bits_per_sample"].toInt();
			resultTag.BitRate = streamObject["bit_rate"].toString().toInt();
		}break;
		case EN_AudioFileType::mp3:
		{
			resultTag.BitBerSample = streamObject["bits_per_sample"].toInt();
			resultTag.BitRate = streamObject["bit_rate"].toString().toInt();
		}break;
		case EN_AudioFileType::flac:
		{
			resultTag.BitBerSample = streamObject["bits_per_raw_sample"].toString().toInt();
		}break;
		case EN_AudioFileType::aac:
		{
			resultTag.BitRate = streamObject["bit_rate"].toString().toInt();
		}break;
	}

	if (resultTag.fileType == EN_AudioFileType::flac)
	{
		QJsonObject		formatDataObj = decodeDataObj["format"].toObject();
		resultTag.BitRate = formatDataObj["bit_rate"].toString().toInt();
	}
}



bool  FFMpegManager::transferIntoWavFormat(const ST_AudioFileTag& targetFileTag, QString targetDir, QString& resultFile)
{
	QString ArgTargetSuffix		= AudioProtocol::AudioFileTypeToStr(targetFileTag.fileType);
	QString ArgTargetFile		= targetFileTag.filePath + '/' + targetFileTag.fileName +'.' + ArgTargetSuffix;
	QString ArgResultSuffix		= AudioProtocol::AudioFileTypeToStr(EN_AudioFileType::wav);
	resultFile = targetDir + '/' + targetFileTag.fileName + '.' + ArgResultSuffix;

	QProcess ffMpegProgess;
	QStringList arguments;

	arguments << "-i" << ArgTargetFile << "-c:a" << "pcm_s16le" << resultFile;

	QFileInfo ffMpegInfo(m_strFFMpegPath);
	QString ffMpegName = ffMpegInfo.baseName();
	QString ffMpegPath = ffMpegInfo.absolutePath();
	QString targetProcessPath = ffMpegPath + "/" + ffMpegName;
	
	ffMpegProgess.start(targetProcessPath, arguments);

	if (!ffMpegProgess.waitForStarted())
	{
		return false;
	}

	if (!ffMpegProgess.waitForFinished())
	{
		return false;
	}

	QByteArray standardData		= ffMpegProgess.readAllStandardOutput();
	QByteArray errorData		= ffMpegProgess.readAllStandardError();
	QByteArray allData			= ffMpegProgess.readAll();

	qDebug() << "Progress Data:" << standardData;
	qDebug() << "error Data:" << errorData;
	qDebug() << "all Data:" << allData;

	bool existState = QFile::exists(resultFile);
	return existState;
}


EN_AudioFileType FFMpegManager::getAudioFileType(QString fileDir)
{
	QFileInfo fileInfo(fileDir);
	QString suffix = fileInfo.suffix();

	EN_AudioFileType fileType = AudioProtocol::AudioFileSuffixToType(suffix);

	return fileType;

}

void FFMpegManager::saveHelpFile()
{
	QString currentAPPDir = QApplication::applicationDirPath();
	QString ffProbeHelpPath = QString("/TestAudio/ffprobeHelp.txt");
	QString targetPath = currentAPPDir + ffProbeHelpPath;
	QFile* file = new QFile(targetPath);
	file->open(QIODevice::ReadWrite);

	QFileInfo ffProbeInfo(m_strFFProbePath);
	QString ffProbeName = ffProbeInfo.baseName();
	QString ffProbePath = ffProbeInfo.absolutePath();
	QString targetProcessPath = ffProbePath + "/" + ffProbeName;

	QProcess* ffProbeProgess = new QProcess(this);

	QStringList arguments;
	arguments << "--help";
	ffProbeProgess->start(targetProcessPath, arguments);

	if (!ffProbeProgess->waitForStarted())
	{
		return;
	}

	if (!ffProbeProgess->waitForFinished())
	{
		return;
	}

	QByteArray Standarddata = ffProbeProgess->readAllStandardOutput();
	file->write(Standarddata);
	return;

	qDebug() << "Progress Data:" << Standarddata;
	qDebug() << "error Data:" << ffProbeProgess->readAllStandardError();
	qDebug() << "all Data:" << ffProbeProgess->readAll();

	int a = 0;

}

EN_VideoFileType FFMpegManager::getVedioFileType(QString fileDir)
{
	QFileInfo fileInfo(fileDir);
	QString suffix = fileInfo.suffix();

	EN_VideoFileType fileType = VisionProtocol::VedioFileSuffixToFileType(suffix);

	return fileType;
}

bool FFMpegManager::getVedioFileTag(QString VedioFilePath, ST_VideoFileTag& VedioFileTag, ST_AudioFileTag& audioFileTag)
{

	QFileInfo AudioFileInfo(VedioFilePath);
	VedioFileTag.fileName = AudioFileInfo.baseName();
	VedioFileTag.filePath = AudioFileInfo.absolutePath();
	VedioFileTag.fileType = getVedioFileType(VedioFilePath);

	audioFileTag.fileName = AudioFileInfo.baseName();
	audioFileTag.filePath = AudioFileInfo.absolutePath();
	//audioFileTag.fileType = getVedioFileType(filePath);



	QFileInfo ffProbeInfo(m_strFFProbePath);
	QString ffProbeName = ffProbeInfo.baseName();
	QString ffProbePath = ffProbeInfo.absolutePath();
	QString targetProcessPath = ffProbePath + "/" + ffProbeName;

	QProcess ffProbeProgess;
	QStringList arguments;
	arguments << "-hide_banner" << "-show_format" << "-show_streams" << "-print_format" << "json" << VedioFilePath;
	ffProbeProgess.start(targetProcessPath, arguments);

	if (!ffProbeProgess.waitForStarted())
	{
		return false;
	}

	if (!ffProbeProgess.waitForFinished())
	{
		return false;
	}

	QByteArray standardData = ffProbeProgess.readAllStandardOutput();
	QByteArray errorData = ffProbeProgess.readAllStandardError();
	QByteArray allData = ffProbeProgess.readAll();


	qDebug() << "Progress Data:" << standardData;
	qDebug() << "error Data:" << errorData;
	qDebug() << "all Data:" << allData;

	QJsonDocument	resultJsonDoc = QJsonDocument::fromJson(standardData);
	QJsonObject		decodeDataObj(resultJsonDoc.object());
	QJsonArray	    streamArray = decodeDataObj["streams"].toArray();

	for (int streamIndex = 0; streamIndex < streamArray.size(); streamIndex++)
	{
		QJsonObject streamObject = streamArray[streamIndex].toObject();
		QString streamTypeStr = streamObject["codec_type"].toString();

		if (streamTypeStr != QString("video"))
		{
			if (streamIndex == streamArray.size() - 1)
			{
				return false;
			}
			continue;
		}

		FFProbedStreamJsonObjToVedioTag(streamObject, VedioFileTag);

		break;
	}

	for (int streamIndex = 0; streamIndex < streamArray.size(); streamIndex++)
	{
		QJsonObject streamObject = streamArray[streamIndex].toObject();
		QString streamTypeStr = streamObject["codec_type"].toString();

		if (streamTypeStr != QString("audio"))
		{
			continue;
		}

		QString audioTypeStr = streamObject["codec_name"].toString();
		audioFileTag.fileType = AudioProtocol::AudioFileSuffixToType(audioTypeStr);

		FFProbedStreamJsonObjToAudioTag(decodeDataObj, streamObject, audioFileTag);

		break;
	}

	return true;

}

void FFMpegManager::FFProbedStreamJsonObjToVedioTag(QJsonObject& streamObject, ST_VideoFileTag& resultTag)
{
	resultTag.codec = streamObject["codec_name"].toString();

	resultTag.width		= streamObject["width"].toInt();
	resultTag.height	= streamObject["height"].toInt();
	


	double durationSec = streamObject["duration"].toString().toDouble();
	resultTag.Duration = QTime(0, 0, 0).addMSecs(durationSec * 1000);
	
	resultTag.FrameCount = streamObject["nb_frames"].toString().toInt();

	resultTag.pixelFormat = streamObject["pix_fmt"].toString();
	resultTag.colorDecodeType = streamObject["color_space"].toString();
	resultTag.BitRate = streamObject["bit_rate"].toString().toInt();


	auto fromRatioStrToRatioNum = [](QString RatioStr, int& numerator, int& denominator)->bool
	{
			int indexOfCompare = RatioStr.indexOf('/', 0);
			if (indexOfCompare == -1)
			{
				return false;
			}
			QString numeratorStr	= RatioStr.section('/', 0, 0);
			QString denominatorStr	= RatioStr.section('/', 1, 1);
			numerator = numeratorStr.toInt();
			denominator = denominatorStr.toInt();
			return true;
	};

	int RatioUp = -1;
	int RatioDown = -1;
	QString RFrameRate = streamObject["r_frame_rate"].toString();
	if (fromRatioStrToRatioNum(RFrameRate, RatioUp, RatioDown))
	{
		resultTag.frameRate = (double)RatioUp / (double)RatioDown;
	}
	else
	{
		resultTag.frameRate = -1;
	}

	QString STimeBase = streamObject["time_base"].toString();
	if (fromRatioStrToRatioNum(STimeBase, RatioUp, RatioDown))
	{
		resultTag.time_base = (double)RatioUp / (double)RatioDown;
	}
	else
	{
		resultTag.frameRate = -1;
	}


	int a = 0;
}

QString FFMpegManager::VedioFileTagToFileName(const ST_VideoFileTag& VedioFileTag)
{
	QString TargetVedioFile = VedioFileTag.filePath + "/" + VedioFileTag.fileName + "." + VisionProtocol::VedioFileTypeToSuffix(VedioFileTag.fileType);
	return TargetVedioFile;
}

QString FFMpegManager::VedioFileTagToDecodeDir(const ST_VideoFileTag& VedioFileTag)
{
	QString TargetCopyDir = VedioFileTag.filePath + "/" + "DecodeResult" + "/" + VedioFileTag.fileName;
	return TargetCopyDir;
}

QString FFMpegManager::VedioFileTagToImageDir(const ST_VideoFileTag& VedioFileTag)
{
	QString TargetDir		= VedioFileTagToDecodeDir(VedioFileTag);
	QString TargetOutputDir = TargetDir + "/" + "ImageOutput";
	return TargetOutputDir;

}

QString FFMpegManager::VedioFileTagToExtractAudioFileDir(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag)
{
	QString TargetCopyDir = VedioFileTagToDecodeDir(VedioFileTag);
	QString TargetExtractAudioFile = TargetCopyDir + "/" + VedioFileTag.fileName + "." + AudioProtocol::AudioFileTypeToStr(audioFileTag.fileType);
	return TargetExtractAudioFile;
}

QString FFMpegManager::VedioFileTagToTransCodeWavFileDir(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag)
{
	QString TargetCopyDir = VedioFileTagToDecodeDir(VedioFileTag);
	QString TargetWavFile = TargetCopyDir + "/" + VedioFileTag.fileName + "." + AudioProtocol::AudioFileTypeToStr(EN_AudioFileType::wav);
	return TargetWavFile;
}

void  FFMpegManager::generateDecodeImgNameList(const ST_VideoFileTag& VedioFileTag, const ST_VideoLoadSetting& LoadSetting, QVector<QString>& nameVec)
{
	nameVec.clear();
	int loadFrameCount = VisionProtocol::getVideoLoadFrameCount(VedioFileTag, LoadSetting);
	nameVec = QVector<QString>(loadFrameCount,QString());

	int totalFrameCount = m_currentLoadTempData.VisionData.FrameVec.size();
	double FrameStrechRatio = (double)VedioFileTag.frameRate / (double)LoadSetting.loadFrameRate;

	for (int currentImageIndex = 0; currentImageIndex < totalFrameCount; currentImageIndex++)
	{
		QString fileDir = VedioFileTagToImageDir(VedioFileTag);

		int loadImageIndex = (currentImageIndex + 1) * FrameStrechRatio;

		QString fileName = QString("output-%1.jpg").arg(loadImageIndex,5,10,QChar('0'));
		QString result = fileDir + "/" + fileName;
		nameVec[currentImageIndex] = result;
	}
}

bool FFMpegManager::checkDecodeFileExist(const ST_VideoFileTag& VedioFileTag)
{
	QString decodeDirStr = VedioFileTagToDecodeDir(VedioFileTag);
	QDir    decodeDir(decodeDirStr);
	if (!decodeDir.exists())
	{
		return false;
	}
	else
	{
		QString ImageDirStr = VedioFileTagToImageDir(VedioFileTag);
		QDir    ImageDir(ImageDirStr);
		ImageDir.setFilter(QDir::Files);
		int fileCount = ImageDir.count();
		if (fileCount > 0)
		{
			return true;
		}
	}
	return false;
}

bool FFMpegManager::extractVedioAudioToWavFile(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag, QString& resultWavFile)
{
	QFileInfo ffMpegInfo(m_strFFMpegPath);
	QString ffMpegName = ffMpegInfo.baseName();
	QString ffMpegPath = ffMpegInfo.absolutePath();
	QString targetProcessPath = ffMpegPath + "/" + ffMpegName;

	QString VedioFile = VedioFileTagToFileName(VedioFileTag);
	QString ExtractAudioFile = VedioFileTagToExtractAudioFileDir(VedioFileTag, audioFileTag);
	QString TransCodeWavFile = VedioFileTagToTransCodeWavFileDir(VedioFileTag, audioFileTag);

	QString decodeDirStr = VedioFileTagToDecodeDir(VedioFileTag);
	QDir    decodeDir(decodeDirStr);
	if (!decodeDir.exists())
	{
		bool mkState = decodeDir.mkpath(decodeDirStr);
		if (!mkState)
		{
			qDebug() << "FFMpegManager::extractVedioAudioToWavFile can 't create outputPath!";
			return false;
		}
	}
	
	auto FFMpegToTargetFile = [](QString ffmpegPath,QString inputFile, QStringList arguments, QString outputFile)->bool
		{
			if (!QFile::exists(inputFile))
			{
				qDebug() << "FFMpegManager::extractVedioAudioToWavFile unexist inputFile :" << inputFile;
				return false;
			}

			if (QFile::exists(outputFile))
			{
				qDebug() << "FFMpegManager::extractVedioAudioToWavFile outputFile exist! remove file : " << outputFile;
				if (!QFile::remove(outputFile))
				{
					qDebug() << "FFMpegManager::extractVedioAudioToWavFile can not remove outputFile : " << outputFile;
					return false;
				}
				
			}

			QProcess ffMpegProgess;
			ffMpegProgess.start(ffmpegPath, arguments);

			if (!ffMpegProgess.waitForStarted())
			{
				qDebug() << "FFMpegManager::extractVedioAudioToWavFile process cant start";
				return false;
			}

			if (!ffMpegProgess.waitForFinished())
			{
				qDebug() << "FFMpegManager::extractVedioAudioToWavFile process cant finished";
				return false;
			}

			QByteArray standardData = ffMpegProgess.readAllStandardOutput();
			QByteArray errorData = ffMpegProgess.readAllStandardError();
			QByteArray allData = ffMpegProgess.readAll();

			qDebug() << "Progress Data:" << standardData;
			qDebug() << "error Data:" << errorData;
			qDebug() << "all Data:" << allData;

			return QFile::exists(outputFile);

		};

	QStringList ExtractArguments;
	ExtractArguments << "-i" << VedioFile << "-vn" << "-y" << "-acodec" << "copy" << ExtractAudioFile;
	bool extractState = FFMpegToTargetFile(targetProcessPath, VedioFile, ExtractArguments, ExtractAudioFile);

	if (!extractState)
	{
		return false;
	}

	QStringList TranscodeArguments;
	TranscodeArguments << "-i" << ExtractAudioFile << "-c:a" << "pcm_s16le" << TransCodeWavFile;
	bool transcodeState = FFMpegToTargetFile(targetProcessPath, ExtractAudioFile, TranscodeArguments, TransCodeWavFile);

	if (!transcodeState)
	{
		return false;
	}

	resultWavFile = TransCodeWavFile;
	return true;

}



void FFMpegManager::startDecodeVideoFile(const ST_VideoFileTag& VideoFileTag, const ST_VideoLoadSetting& LoadSetting)
{
	VisionProtocol::initVideoData(VideoFileTag, LoadSetting,m_currentLoadTempData.VisionData);

	QFileInfo ffProbeInfo(m_strFFProbePath);
	QString ffProbeName = ffProbeInfo.baseName();
	QString ffProbePath = ffProbeInfo.absolutePath();
	QString targetFFProbePath = ffProbePath + "/" + ffProbeName;

	QString VedioFilePath = VedioFileTagToFileName(VideoFileTag);

	QStringList ReadFrameTag_Arguments;
	ReadFrameTag_Arguments << "-hide_banner" << "-select_streams" << "v:0" << "-show_frames" << "-of" << "json" << VedioFilePath;

	QFileInfo ffMpegInfo(m_strFFMpegPath);
	QString ffMpegName = ffMpegInfo.baseName();
	QString ffMpegPath = ffMpegInfo.absolutePath();
	QString targetFFMpegPath = ffMpegPath + "/" + ffMpegName;

	QString decodeDirStr = VedioFileTagToDecodeDir(VideoFileTag);
	QString outputDirStr = VedioFileTagToImageDir(VideoFileTag);
	QString outputImageFormat = outputDirStr + "/" + QString("output-%5d.jpg");
	
	QStringList ReadFrameImage_arguments;
	ReadFrameImage_arguments << "-i" << VedioFilePath << "-f" << "image2" << outputImageFormat;

	QVector<QString> loadFileVec;
	generateDecodeImgNameList(VideoFileTag, LoadSetting,loadFileVec);

	m_pLoadVideoFrameTagThread->runWithArgument(targetFFProbePath, LoadSetting, ReadFrameTag_Arguments);
	m_pLoadVideoFrameImageThread->runWithArgument(targetFFMpegPath, VideoFileTag, ReadFrameImage_arguments, outputDirStr, loadFileVec, LoadSetting);

}

ST_VideoH264FrameTag& FFMpegManager::getVideoFrameTagRef(int index)
{
	return m_currentLoadTempData.VisionData.FrameVec[index].FrameTag;
}

QImage& FFMpegManager::getVideoFrameImageRef(int index)
{
	return m_currentLoadTempData.VisionData.FrameVec[index].Frame;
}

void FFMpegManager::startExtractAndLoadWavFileFromVideo(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& audioFileTag)
{
	m_pExtractAudioThread->runWithArgument(VedioFileTag, audioFileTag);
}

void FFMpegManager::slot_loadVideoFrameTagFinished(bool loadSuccess)
{
	emit sgn_loadVideoTagFinished(loadSuccess);
}

void FFMpegManager::slot_updateExtractAudioLoadState(bool state, QString errStr)
{
	emit sgn_ExtractAudioState(state, errStr);
	if (state)
	{
		emit sgn_ExtractAudioFinished(m_pExtractAudioThread->getWavData());
	}
}