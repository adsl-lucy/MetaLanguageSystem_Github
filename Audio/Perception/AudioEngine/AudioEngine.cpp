#include "AudioEngine.h"

#pragma execution_character_set("utf-8")

AudioEngine* AudioEngine::m_instance = nullptr;

AudioEngine* AudioEngine::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new AudioEngine();
	}
	return m_instance;
}

AudioEngine::AudioEngine() :QObject(nullptr)
{
	updateAudioDevice();
	m_pDeviceDialog = new AudioDeviceDialog(nullptr);
	connect(m_pDeviceDialog, &AudioDeviceDialog::sgn_switchDevice, this, &AudioEngine::slot_swtichIODevice);
	m_pDeviceDialog->hide();

	m_pWavFile = new WavFile(this);
	connect(m_pWavFile, &WavFile::sgn_loadRawDataState, this, &AudioEngine::sgn_loadRawDataState);

}

void AudioEngine::updateAudioDevice()
{

	auto dupRemove = [=](QList<QAudioDeviceInfo> dupList, QMap<QString, QAudioDeviceInfo>& targetMap)
		{
			targetMap.clear();
			for (auto pos = dupList.begin(); pos != dupList.end(); pos++)
			{
				QAudioDeviceInfo currentInfo = *pos;
				auto mapPos = targetMap.find(currentInfo.deviceName());
				if (mapPos == targetMap.end())
				{
					targetMap.insert(currentInfo.deviceName(), currentInfo);
				}
			}
		};

	dupRemove(QAudioDeviceInfo::availableDevices(QAudio::AudioInput), m_mapAvaAudioInputDevices);
	dupRemove(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput), m_mapAvaAudioOutputDevices);

	resetToDefaultDevice();
	
	//slot_swtichIODevice(m_CurrentAudioInputDevice, m_CurrentAudioOutputDevice);

}

void AudioEngine::resetToDefaultDevice()
{

	if (m_mapAvaAudioInputDevices.isEmpty())
	{
		m_CurrentAudioInputDevice = QAudioDeviceInfo::defaultInputDevice().deviceName();
	}
	else
	{
		m_CurrentAudioInputDevice = m_mapAvaAudioInputDevices.begin().key();
	}

	if (m_mapAvaAudioOutputDevices.isEmpty())
	{
		m_CurrentAudioOutputDevice = QAudioDeviceInfo::defaultOutputDevice().deviceName();
	}
	else
	{
		auto resultPos = m_mapAvaAudioOutputDevices.begin();
		while(resultPos != m_mapAvaAudioOutputDevices.end())
		{
			QString posString = resultPos.key();
			if (posString.contains(QString("ÑïÉùÆ÷")))
			{
				break;
			}
			resultPos++;
		}

		if (resultPos == m_mapAvaAudioOutputDevices.end())
		{
			m_CurrentAudioOutputDevice = QAudioDeviceInfo::defaultOutputDevice().deviceName();
		}
		else
		{
			m_CurrentAudioOutputDevice = resultPos.key();
		}
	}
}

void AudioEngine::resetAudioInputDevice(QAudioDeviceInfo inputDevice)
{
	m_CurrentAudioInputDevice = inputDevice.deviceName();
	emit sgn_InputDeviceChanged(m_CurrentAudioInputDevice);
}

void AudioEngine::resetAudioOutputDevice(QAudioDeviceInfo outputDevice)
{
	if (m_audioOutput != nullptr)
	{
		delete m_audioOutput;
		m_audioOutput = nullptr;
	}

	m_CurrentAudioOutputDevice = outputDevice.deviceName();

	if (m_pWavFile != nullptr)
	{
		m_audioOutput = new QAudioOutput(outputDevice, m_pWavFile->fileFormat(), this);
		m_audioOutput->setNotifyInterval(m_nMediaUpdateIntervalMs);
		connect(m_audioOutput, &QAudioOutput::stateChanged,this, &AudioEngine::slot_audioStateChanged);
		connect(m_audioOutput, &QAudioOutput::notify,this, &AudioEngine::slot_audioNotify);
		//m_audioOutput->setCategory(m_audioOutputCategory);		
	}
	emit sgn_OutputDeviceChanged(m_CurrentAudioOutputDevice);

}



const QAudioDeviceInfo AudioEngine::getCurrentInputDevice()
{
	auto pos = m_mapAvaAudioInputDevices.find(m_CurrentAudioInputDevice);
	if (pos != m_mapAvaAudioInputDevices.end())
	{
		return pos.value();
	}
	else
	{
		return QAudioDeviceInfo();
	}
}

const QAudioDeviceInfo AudioEngine::getCurrentOutputDevice()
{
	auto pos = m_mapAvaAudioOutputDevices.find(m_CurrentAudioOutputDevice);
	if (pos != m_mapAvaAudioOutputDevices.end())
	{
		return pos.value();
	}
	else
	{
		return QAudioDeviceInfo();
	}
}

void AudioEngine::showAudioDeviceDialog()
{
	updateAudioDevice();

	auto formMapToList = [=](const QMap<QString, QAudioDeviceInfo>& fromMap,QList<QString>& toList)
		{
			toList.clear();
			for (auto pos = fromMap.begin(); pos != fromMap.end(); pos++)
			{
				QString deviceName = pos.key();
				toList.push_back(deviceName);
			}
		};

	QList<QString> inputList, outputList;
	formMapToList(m_mapAvaAudioInputDevices, inputList);
	formMapToList(m_mapAvaAudioOutputDevices, outputList);

	m_pDeviceDialog->setDeivceItem(	inputList, m_CurrentAudioInputDevice,
									outputList, m_CurrentAudioOutputDevice);
	m_pDeviceDialog->show();
}

QList<QString> AudioEngine::getInputDeviceList()
{
	auto formMapToList = [=](const QMap<QString, QAudioDeviceInfo>& fromMap, QList<QString>& toList)
		{
			toList.clear();
			for (auto pos = fromMap.begin(); pos != fromMap.end(); pos++)
			{
				QString deviceName = pos.key();
				toList.push_back(deviceName);
			}
		};

	QList<QString> inputList;
	formMapToList(m_mapAvaAudioInputDevices, inputList);
	return inputList;
}

void AudioEngine::slot_swtichIODevice(const QString inputDevice, const QString outputDevcie)
{
	const QAudioDeviceInfo inputDeviceInfo		= m_mapAvaAudioInputDevices.find(inputDevice).value();
	const QAudioDeviceInfo outputDeviceInfo		= m_mapAvaAudioOutputDevices.find(outputDevcie).value();
	resetAudioInputDevice(inputDeviceInfo);
	resetAudioOutputDevice(outputDeviceInfo);
}


QString AudioEngine::getFullWavFilePath(const ST_AudioFileTag& fileTag)
{
	QString fileName = fileTag.fileName;
	QString filePath = fileTag.filePath;
	QString fileSuffix = AudioProtocol::AudioFileTypeToStr(fileTag.fileType);
	QString result = filePath + '/' + fileName + '.' + fileSuffix;
	return result;
}

bool AudioEngine::loadWavFile(const QString fileDir, ST_WavRawData& rawData)
{
	qDebug() << "AudioEngine::loadWavFile :";
	qDebug() << "file path		: " << fileDir;
	bool readState = m_pWavFile->openAndReadHead(fileDir);

	if (!readState)
	{
		qDebug() << "m_pWavFile read head error";
		return readState;
	}
	else
	{
		qDebug() << "m_pWavFile read head success";
	}

	bool isPCM16Le					= false;
	bool fileHeadAlign				= false;
	bool TimeCaculateDataSizeDiff	= false;
	bool caculateTimeEqual			= false;

	bool fileValidity = AudioEngine::instance()->checkCaculateValidity(rawData.fileTag, isPCM16Le, fileHeadAlign, TimeCaculateDataSizeDiff, caculateTimeEqual);

	bool currentValidity = isPCM16Le && fileHeadAlign && TimeCaculateDataSizeDiff;

	if (!currentValidity)
	{
		qDebug() << "m_pWavFile Invalid!";
		return currentValidity;
	}
	else
	{
		qDebug() << "m_pWavFile valid startLoad rawData";
	}
	
	bool loadState = m_pWavFile->loadWavData(rawData);

	return loadState;


}

bool AudioEngine::PcmDataToDoubleData(const ST_WavRawData& rawData, ST_WavDoubleData& doubleData)
{
	doubleData.fileTag = rawData.fileTag;

	double sampleRate	= rawData.fileTag.sampleRate;
	double secPerPt		= 1.0 / sampleRate;
	int	   hunderdsOfPt = rawData.LeftChannel.size() / 100;


	auto fromRawVecToDoubleVec = [=](bool isLeft,const QVector<int>& rawVec, QVector<ST_AudioPoint>& doubleVec)->bool
		{
			doubleVec.clear();
			if (rawVec.isEmpty())
			{
				return true;
			}

			int hundersOfPt = qMax(1,rawVec.size() / 100);

			ST_AudioPoint nullPt;
			doubleVec = QVector<ST_AudioPoint>(rawVec.size(), nullPt);
			for (int ptIndex = 0; ptIndex < doubleVec.size(); ptIndex++)
			{
				ST_AudioPoint newPt;
				newPt.pTime		= secPerPt * ptIndex;
				int   pcmVal = rawVec[ptIndex];

				if (pcmVal > const_PCMS16MaxAmplitude || pcmVal < const_PCMS16MinAmplitude)
				{
					QString errStr = QString("invalid pcmVal index : %1 val: %2").arg(ptIndex).arg(pcmVal);
					qDebug() << errStr;
					emit sgn_transFerRawDataState(0, 0, true, errStr);
					return false;
				}

				newPt.pVal		= AudioProtocol::pcmToReal(rawVec[ptIndex]);
				doubleVec[ptIndex] = newPt;

				if (ptIndex % hundersOfPt == 0)
				{
					emit sgn_transFerRawDataState(isLeft, ptIndex / hundersOfPt,false,QString());
				}

			}
			return true;
		};


	bool leftState	= fromRawVecToDoubleVec(true	,rawData.LeftChannel	, doubleData.LeftChannel);
	bool rightState = fromRawVecToDoubleVec(false	,rawData.RightChannel	, doubleData.RightChannel);

	emit sgn_transFerRawDataState(false, 100, false, QString());

	return leftState && rightState;

}

bool AudioEngine::checkCaculateValidity(const ST_AudioFileTag& fileTag, bool& isPCM16Le, bool& fileHeadAlign, bool& DataSizeToTimeEqual, bool& TimeCaculateDataSizeDiff)
{
	qDebug() << QString("AudioEngine::checkCaculateValidity checkFile : %1").arg(getFullWavFilePath(fileTag));

	TimeCaculateDataSizeDiff	= false;
	TimeCaculateDataSizeDiff	= false;
	fileHeadAlign				= false;

	const QAudioFormat& format = m_pWavFile->fileFormat();
	isPCM16Le = isPCMS16LE(format);

	if (!isPCM16Le)
	{
		qDebug() << "AudioEngine::checkCaculateValidity :file is not PCM16LE!";
		return false;
	}
	else
	{
		qDebug() << "AudioEngine::checkCaculateValidity : file format Valid : " << getWavFileFormatStr(format);
	}

	double ptPerMsec		= (double)fileTag.sampleRate / 1000.0;

	int  wavFileLength		= m_pWavFile->size();
	int  headLength			= m_pWavFile->headerLength();
	int  dataLength			= m_pWavFile->WavDataSize();
	fileHeadAlign			= (headLength + dataLength) == wavFileLength;
	if (!fileHeadAlign)
	{
		qDebug() << "AudioEngine::checkCaculateValidity :file head data is not Align!";
	}
	else
	{
		qDebug() << "AudioEngine::checkCaculateValidity :file head data Align!";
	}

	QTime dataCaculateDuation = buffterLengthToTimeLength(wavFileLength - headLength, format);
	DataSizeToTimeEqual = dataCaculateDuation == fileTag.Duration;
	if (!DataSizeToTimeEqual)
	{
		qDebug() << QString("AudioEngine::checkCaculateValidity :DataSizeToTime diff! ffprobe : %1 caculate : %2")
			.arg(fileTag.Duration.toString("hh:mm:ss")).arg(dataCaculateDuation.toString("hh:mm:ss"));
	}
	else
	{
		qDebug() << QString("AudioEngine::checkCaculateValidity :DataSizeToTime : Equal!");
	}

	int  TimeCaculateSize		= headLength + timeLengthToBufferLength(fileTag.Duration, format);	
	int timeCaculateDataDiff	= TimeCaculateSize - wavFileLength;
	int maxDiff					= ptPerMsec * fileTag.ChannelNum;
	TimeCaculateDataSizeDiff	=  abs(timeCaculateDataDiff)< maxDiff;
	if (!TimeCaculateDataSizeDiff)
	{
		qDebug() << QString("AudioEngine::checkCaculateValidity :timeCaculateDataSize diff : %1 bigger than maxDiff : %2").arg(timeCaculateDataDiff).arg(maxDiff);	
	}
	else
	{
		qDebug() << QString("AudioEngine::checkCaculateValidity :timeCaculateDataSize diff : %1 smaller than maxDiff : %2").arg(timeCaculateDataDiff).arg(maxDiff);
	}

	return isPCM16Le && fileHeadAlign && DataSizeToTimeEqual && TimeCaculateDataSizeDiff;

}

bool AudioEngine::isPCM(const QAudioFormat& format)
{
	return (format.codec() == "audio/pcm");
}

bool AudioEngine::isPCMS16LE(const QAudioFormat& format)
{
	return isPCM(format) &&
		format.sampleType() == QAudioFormat::SignedInt &&
		format.sampleSize() == 16 &&
		format.byteOrder() == QAudioFormat::LittleEndian;
}

QString AudioEngine::getWavFileFormatStr(const QAudioFormat& format)
{
	QString result;

	if (QAudioFormat() != format) {
		if (format.codec() == "audio/pcm") {
			Q_ASSERT(format.sampleType() == QAudioFormat::SignedInt);

			const QString formatEndian = (format.byteOrder() == QAudioFormat::LittleEndian)
				? QString("LE") : QString("BE");

			QString formatType;
			switch (format.sampleType()) {
			case QAudioFormat::SignedInt:
				formatType = "signed";
				break;
			case QAudioFormat::UnSignedInt:
				formatType = "unsigned";
				break;
			case QAudioFormat::Float:
				formatType = "float";
				break;
			case QAudioFormat::Unknown:
				formatType = "unknown";
				break;
			}

			QString formatChannels = QString("%1 channels").arg(format.channelCount());
			switch (format.channelCount()) {
			case 1:
				formatChannels = "mono";
				break;
			case 2:
				formatChannels = "stereo";
				break;
			}

			result = QString("%1 Hz %2 bit %3 %4 %5")
				.arg(format.sampleRate())
				.arg(format.sampleSize())
				.arg(formatType)
				.arg(formatEndian)
				.arg(formatChannels);
		}
		else {
			result = format.codec();
		}
	}

	return result;
}

QTime AudioEngine::buffterLengthToTimeLength(qint64 buffterLength, const QAudioFormat& format)
{
	int sampleSizeInByte	= format.sampleSize() / 8;
	int pointCount			= buffterLength / sampleSizeInByte;
	int sampleRate			= format.sampleRate();
	
	int channelCount = format.channelCount();
	if (channelCount <= 0)
	{
		return QTime(0, 0, 0);
	}

	int oneChannelPtCount = pointCount / channelCount;

	double MsecPerPt = 1000.0 / sampleRate;
	double totalMsec = MsecPerPt * oneChannelPtCount;
	QTime resultTimeLength = QTime(0, 0, 0).addMSecs(totalMsec);
	return resultTimeLength;

}

qint64 AudioEngine::timeLengthToBufferLength(QTime timeLength, const QAudioFormat& format)
{
	int sampleSizeInBtype		= format.sampleSize() / 8;
	int MsecCount				= QTime(0,0,0).msecsTo(timeLength);
	int sampleRate				= format.sampleRate();
	int channelCount			= format.channelCount();

	if (channelCount <= 0)
	{
		return -1;
	}

	int		totalPtCount		= (double)MsecCount * (double)sampleRate  * (double)channelCount / (double)1000;
	int		totalBuffterSize	= totalPtCount * sampleSizeInBtype;
	return	totalBuffterSize;

}

void AudioEngine::slot_startPlay()
{
	if (m_audioOutput == nullptr)
	{
		const QAudioDeviceInfo outputDeviceInfo = m_mapAvaAudioOutputDevices.find(m_CurrentAudioOutputDevice).value();
		resetAudioOutputDevice(outputDeviceInfo);
	}

	if (m_audioOutput) {
		if (QAudio::AudioOutput == m_mode &&
			QAudio::SuspendedState == m_state) {
#ifdef Q_OS_WIN
			// The Windows backend seems to internally go back into ActiveState
			// while still returning SuspendedState, so to ensure that it doesn't
			// ignore the resume() call, we first re-suspend
			m_audioOutput->suspend();
#endif
			m_audioOutput->resume();
		}
		else {
			//m_spectrumAnalyser.cancelCalculation();
			//spectrumChanged(0, 0, FrequencySpectrum());
			setPlayPosition(0, true);
			stopRecording();
			m_mode = QAudio::AudioOutput;

			m_count = 0;
			if (m_pWavFile) {
				m_pWavFile->seek(0);
				m_pWavFile->stopMediaPlayer();
				//m_bufferPosition = 0;
				//m_dataLength = 0;
				m_audioOutput->start(m_pWavFile);
			}
			else {
				/*
				m_audioOutputIODevice.close();
				m_audioOutputIODevice.setBuffer(&m_buffer);
				m_audioOutputIODevice.open(QIODevice::ReadOnly);
				m_audioOutput->start(&m_audioOutputIODevice);
				*/
			}
		}
	}
}

void AudioEngine::slot_jump(QTime jumpTime)
{
	slot_stopPlay();
	m_pWavFile->seekToTime(jumpTime);
	//m_audioOutput->start(m_pWavFile);
}

void AudioEngine::slot_stopPlay()
{
	if (m_audioOutput) {
		m_audioOutput->stop();
		QCoreApplication::instance()->processEvents();
		m_audioOutput->disconnect();
		setPlayPosition(0);
		delete m_audioOutput;
		m_audioOutput = nullptr;
	}

	if (m_pWavFile)
	{
		m_pWavFile->stopMediaPlayer();
	}
}

void AudioEngine::setPlayPosition(qint64 position, bool forceEmit)
{
	const bool changed = (m_playPosition != position);
	m_playPosition = position;
	if (changed || forceEmit)
		emit sgn_playPositionChanged(m_playPosition,m_nMediaUpdateIntervalMs);
}

void AudioEngine::stopRecording()
{
	if (m_audioInput) {
		m_audioInput->stop();
		QCoreApplication::instance()->processEvents();
		m_audioInput->disconnect();
	}
	m_audioInputIODevice = 0;
}

void AudioEngine::slot_audioStateChanged(QAudio::State state)
{
	qDebug() << "AudioEngine::slot_audioStateChanged from" << m_state
		<< "to" << state;

	if (QAudio::IdleState == state && m_pWavFile && m_pWavFile->pos() == m_pWavFile->size()) {
		slot_stopPlay();
	}
	else {
		if (QAudio::StoppedState == state) {
			// Check error
			QAudio::Error error = QAudio::NoError;
			switch (m_mode) {
			case QAudio::AudioInput:
				error = m_audioInput->error();
				break;
			case QAudio::AudioOutput:
				error = m_audioOutput->error();
				break;
			}
			if (QAudio::NoError != error) {
				reset();
				return;
			}
		}
		setState(state);
	}
}

void AudioEngine::reset()
{
	/*
	stopRecording();
	slot_stopPlay();
	setState(QAudio::AudioInput, QAudio::StoppedState);
	setFormat(QAudioFormat());
	m_generateTone = false;
	delete m_file;
	m_file = 0;
	delete m_analysisFile;
	m_analysisFile = 0;
	m_buffer.clear();
	m_bufferPosition = 0;
	m_bufferLength = 0;
	m_dataLength = 0;
	emit dataLengthChanged(0);
	resetAudioDevices();
	*/
}

void AudioEngine::setState(QAudio::State state)
{
	const bool changed = (m_state != state);
	m_state = state;
	if (changed)
		emit sgn_stateChanged(m_mode, m_state);
}

void AudioEngine::setState(QAudio::Mode mode, QAudio::State state)
{
	const bool changed = (m_mode != mode || m_state != state);
	m_mode = mode;
	m_state = state;
	if (changed)
		emit sgn_stateChanged(m_mode, m_state);
}

void AudioEngine::slot_audioNotify()
{
	switch (m_mode) {
	case QAudio::AudioInput: {
		/*
		const qint64 recordPosition = qMin(m_bufferLength, audioLength(m_format, m_audioInput->processedUSecs()));
		setRecordPosition(recordPosition);
		const qint64 levelPosition = m_dataLength - m_levelBufferLength;
		if (levelPosition >= 0)
			calculateLevel(levelPosition, m_levelBufferLength);
		if (m_dataLength >= m_spectrumBufferLength) {
			const qint64 spectrumPosition = m_dataLength - m_spectrumBufferLength;
			calculateSpectrum(spectrumPosition);
		}
		emit bufferChanged(0, m_dataLength, m_buffer);
		*/
	} break;
	case QAudio::AudioOutput: {
		const qint64 playPosition = m_audioOutput->processedUSecs();
		int currentMSec = playPosition / 1000;
		qDebug() << QString("AudioEngine::slot_audioNotify :%1").arg(QTime(0,0,0).addMSecs(currentMSec).toString("mm:ss.zzz"));
		emit sgn_playPositionChanged(currentMSec,m_nMediaUpdateIntervalMs);
		/*
		const qint64 playPosition = audioLength(m_format, m_audioOutput->processedUSecs());
		setPlayPosition(qMin(bufferLength(), playPosition));
		const qint64 levelPosition = playPosition - m_levelBufferLength;
		const qint64 spectrumPosition = playPosition - m_spectrumBufferLength;
		if (m_file) {
			if (levelPosition > m_bufferPosition ||
				spectrumPosition > m_bufferPosition ||
				qMax(m_levelBufferLength, m_spectrumBufferLength) > m_dataLength) {
				m_bufferPosition = 0;
				m_dataLength = 0;
				// Data needs to be read into m_buffer in order to be analysed
				const qint64 readPos = qMax(qint64(0), qMin(levelPosition, spectrumPosition));
				const qint64 readEnd = qMin(m_analysisFile->size(), qMax(levelPosition + m_levelBufferLength, spectrumPosition + m_spectrumBufferLength));
				const qint64 readLen = readEnd - readPos + audioLength(m_format, WaveformWindowDuration);
				qDebug() << "Engine::audioNotify [1]"
					<< "analysisFileSize" << m_analysisFile->size()
					<< "readPos" << readPos
					<< "readLen" << readLen;
				if (m_analysisFile->seek(readPos + m_analysisFile->headerLength())) {
					m_buffer.resize(readLen);
					m_bufferPosition = readPos;
					m_dataLength = m_analysisFile->read(m_buffer.data(), readLen);
					qDebug() << "Engine::audioNotify [2]" << "bufferPosition" << m_bufferPosition << "dataLength" << m_dataLength;
				}
				else {
					qDebug() << "Engine::audioNotify [2]" << "file seek error";
				}
				emit bufferChanged(m_bufferPosition, m_dataLength, m_buffer);
			}
		}
		else {
			if (playPosition >= m_dataLength)
				stopPlayback();
		}
		if (levelPosition >= 0 && levelPosition + m_levelBufferLength < m_bufferPosition + m_dataLength)
			calculateLevel(levelPosition, m_levelBufferLength);
		if (spectrumPosition >= 0 && spectrumPosition + m_spectrumBufferLength < m_bufferPosition + m_dataLength)
			calculateSpectrum(spectrumPosition);
			*/
	}
							break;
	}
}