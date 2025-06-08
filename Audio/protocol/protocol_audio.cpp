#include "./protocol_audio.h"

QString AudioProtocol::boolToStr(bool state)
{
	return state ? QString("true") : QString("false");
}

QString AudioProtocol::AudioFileTypeToStr(EN_AudioFileType fileType)
{
	switch (fileType)
	{
		case EN_AudioFileType::wav		:return QString("wav");
		case EN_AudioFileType::mp3		:return QString("mp3");
		case EN_AudioFileType::flac		:return QString("flac");
		case EN_AudioFileType::aac		:return QString("aac");
	}
	return QString("undefine");
}

EN_AudioFileType AudioProtocol::AudioFileSuffixToType(QString suffix)
{
	EN_AudioFileType fileType;

	if (suffix == QString("wav"))
	{
		fileType = EN_AudioFileType::wav;
	}
	else if (suffix == QString("mp3"))
	{
		fileType = EN_AudioFileType::mp3;
	}
	else if (suffix == QString("flac"))
	{
		fileType = EN_AudioFileType::flac;
	}
	else if(suffix == QString("aac"))
	{
		fileType = EN_AudioFileType::aac;
	}
	else
	{
		fileType = EN_AudioFileType::undefine;
	}

	return fileType;
}

const qint16  PCMS16MaxValue = 32767;
const quint16 PCMS16MaxAmplitude = 32768; // because minimum is -32768

qreal AudioProtocol::pcmToReal(qint16 pcm)
{
	return qreal(pcm) / PCMS16MaxAmplitude;
}

qint16 AudioProtocol::realToPcm(qreal real)
{
	return real * PCMS16MaxValue;
}

qint64 AudioProtocol::audioLength(const QAudioFormat& format, qint64 microSeconds)
{
	qint64 result = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
		* microSeconds / 1000000;
	result -= result % (format.channelCount() * format.sampleSize());
	return result;
}

qint64 AudioProtocol::audioDuration(const QAudioFormat& format, qint64 bytes)
{
	return (bytes * 1000000) /
		(format.sampleRate() * format.channelCount() * (format.sampleSize() / 8));
}

void AudioProtocol::duplicateAudioVec(const QVector<ST_AudioPoint>& fromVec, QVector<ST_AudioPoint>& toVec)
{
	toVec.clear();
	ST_AudioPoint nullPt;
	toVec = QVector<ST_AudioPoint>(fromVec.size(), nullPt);
	for (int ptIndex = 0; ptIndex < fromVec.size(); ptIndex++)
	{
		toVec[ptIndex] = fromVec[ptIndex];
	}
}

bool AudioProtocol::initSTFTData(int frameCount, int FFTPointCountInFrame, ST_STFTOutputData& InitData)
{
	InitData.vecOutput.clear();
	if (frameCount <= 0 || FFTPointCountInFrame <=0)
	{
		return false;
	}

	ST_FFTPoint			nullFFTPoint;
	ST_FFTOutputData	nullFFTData;
	nullFFTData.resultVec = QVector<ST_FFTPoint>(FFTPointCountInFrame, nullFFTPoint);
	InitData.vecOutput = QVector<ST_FFTOutputData>(frameCount, nullFFTData);
	return true;
}

void AudioProtocol::duplicateSTFTData(const ST_STFTOutputData& fromData, ST_STFTOutputData& toData)
{
	toData.InputPara = fromData.InputPara;
	toData.vecOutput.clear();
	if (fromData.vecOutput.isEmpty())
	{
		return;
	}

	int FFTPointCountInFrame = fromData.vecOutput[0].resultVec.size();
	int FrameCount = fromData.vecOutput.size();

	initSTFTData(FrameCount, FFTPointCountInFrame, toData);

	for (int frameIndex = 0; frameIndex < FrameCount; frameIndex++)
	{
		const ST_FFTOutputData& fromFrameData = fromData.vecOutput[frameIndex];
		ST_FFTOutputData& toframeData	= toData.vecOutput[frameIndex];

		toframeData.para = fromFrameData.para;

		int fromVecSize = fromFrameData.resultVec.size();
		int toVecSize	= toframeData.resultVec.size();

		if (fromVecSize != toVecSize)
		{
			qDebug() << QString("AudioProtocol::duplicateSTFTData frame %1 FFTVec size diff fromVec: %2 toVec :3")
				.arg(frameIndex).arg(fromVecSize).arg(toVecSize);
			break;
		}

		for (int FFTPtIndex = 0; FFTPtIndex < fromVecSize; FFTPtIndex++)
		{
			toframeData.resultVec[FFTPtIndex] = fromFrameData.resultVec[FFTPtIndex];
		}

	}

}

double AudioProtocol::fftRealToDB(double fftReal, double maxDb)
{
	if (fftReal > 1.0)
	{
		return maxDb;
	}
	else if (fftReal <= 0)
	{
		return 0;
	}

	double RelativeDB = 20 * log10(fftReal / 1.0);
	double AbsoluteDB = RelativeDB + maxDb;
	return AbsoluteDB;
}

double AudioProtocol::getRelativeDB(double realVal, double maxVal)
{
	double RelativeDB = 20 * log10(realVal / maxVal);
	return RelativeDB;
}

double AudioProtocol::getFFTRealFromDB(double fftDB, double maxDb)
{
	double power   = (fftDB - maxDb) / 20.0;
	double FFTReal = pow(10, power);
	return FFTReal;
}

double AudioProtocol::getHearingThreshHoldInQuietDB(double Freq)
{
	if (Freq <= 0 || Freq >= 20000)
	{
		return 80;
	}

	if (Freq <= 10000.0 && Freq >= 500.0)
	{
		return 0;
	}

	if (Freq >= 0 && Freq < 200)
	{
		return Freq * -1 * (11.0 / 40.0) + 70.0;
	}

	if (Freq >= 200 && Freq < 500)
	{
		return Freq * -1 / 20.0 + 25.0;
	}

	if (Freq >= 10000 && Freq < 18000)
	{
		return Freq / 500.0 - 20.0;
	}

	if (Freq >= 18000 && Freq < 20000)
	{
		return Freq * 4 / 125.0 - 560.0;
	}

	return 80;

}

bool   AudioProtocol::checkFreqPtUnderTIQ(double Freq, double fftRealVal, double maxDB)
{
	if (Freq < 0 || Freq >= 20000)
	{
		return true;
	}

	double TIQDB = getHearingThreshHoldInQuietDB(Freq);
	double TIQreal = getFFTRealFromDB(TIQDB, maxDB);
	return TIQreal >= fftRealVal;

}

bool AudioProtocol::getTwoLineCrossPoint(QPointF L1P1, QPointF L1P2, QPointF L2P1, QPointF L2P2, QPointF& crossPt)
{
	double a11 =   L1P2.x() - L1P1.x();
	double a12 = ( L2P2.x() - L2P1.x() ) * -1;
	double b1  =   L2P1.x() - L1P1.x();

	double a21 =   L1P2.y() - L1P1.y();
	double a22 = ( L2P2.y() - L2P1.y() ) * -1;
	double b2  =   L2P1.y() - L1P1.y();

	double detMain = a11 * a22 - a12 * a21;
	if (detMain != 0)//两直线非平行
	{
		double lambda = (a22 * b1 - a12 * b2) / detMain;
		//double miu    = (a21 * b1 - a11 * b2) / detMain;

		crossPt.rx() = L1P1.x() + lambda * a11;
		crossPt.ry() = L1P1.y() + lambda * a21;

		return true;
	}

	//两直线平行 计算是否共线

	double K1 = a21 / a11;
	double K12 = (L2P1.y() - L1P1.y()) / (L2P1.x() - L1P1.x());

	if (abs(K1) == abs(K12))
	{
		crossPt = L1P1;
		return true;
	}
	else
	{
		return false;
	}


}