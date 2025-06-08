#pragma once
#include <QObject>
#include <QList>
#include <QDir>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <QAudioOutput>
#include <QAudioInput>

#include "../../Widget/AudioDeviceDialog/AudioDeviceDialog.h"
#include "./wavfile.h"
#include "../../protocol/protocol_audio.h"

//音频播放读取入口
//音频播放使用QAudioOutput
//音频跳转使用wavfile内的QMediaPlayer 
//因为音乐播放器不是重点，所以先这么凑合用

class AudioEngine : public QObject
{
    Q_OBJECT
public:
	static AudioEngine* instance();
protected:
	AudioEngine();
	static AudioEngine* m_instance;

public:

	void showAudioDeviceDialog();

	const QAudioDeviceInfo getCurrentInputDevice();
	const QAudioDeviceInfo getCurrentOutputDevice();

	QList<QString> getInputDeviceList();

public:signals:
	void sgn_InputDeviceChanged(const QString inputDevice);
	void sgn_OutputDeviceChanged(const QString outputDevice);

protected:
	void updateAudioDevice();
	void resetAudioInputDevice(QAudioDeviceInfo inputDevice);
	void resetAudioOutputDevice(QAudioDeviceInfo outputDevice);
	void resetToDefaultDevice();


protected slots:
	void slot_swtichIODevice(const QString inputDevice, const QString outputDevcie);

private:
	QMap<QString, QAudioDeviceInfo> m_mapAvaAudioInputDevices;
	QMap<QString, QAudioDeviceInfo> m_mapAvaAudioOutputDevices;

	QString		m_CurrentAudioInputDevice;
	QString		m_CurrentAudioOutputDevice;

	AudioDeviceDialog* m_pDeviceDialog = nullptr;


public:
	QString getFullWavFilePath(const ST_AudioFileTag& fileTag);
	bool loadWavFile(const QString fileDir,ST_WavRawData& rawData);
	bool PcmDataToDoubleData(const ST_WavRawData& rawData, ST_WavDoubleData& doubleData);

	//检测文件是否有效，输入wav文件标签，通过引用返回结果
	//isPCM16Le					: 这是不是一个PCM16文件，如果不是，那么不能解码
	//fileHeadAlign				：wav标注的文件头和从data chunk读取的数值大小 加起来是不是wav文件的大小
	//DataSizeToTimeEqual		：ffprobe文件返回的文件时长，和数据段长度计算出来的文件时长是否吻合
	//TimeCaculateDataSizeDiff	：返回通过ffprobe返回的文件时长所计算的数据段大小，和实际数据段大小的差值（单位为字节（byte）），这个值的误差是否1ms对应的采样点数量之内（对于44.1kHz 这个误差在44.1之内）	
	//上述内容全部为真，那么这个文件有效，返回true
	//实践中 最后一个从时间计算出来的点和最大误差比理论误差更大，但是数据没有越界以及从数据长度计算出来的时间长度是一致的
	
	bool checkCaculateValidity(const ST_AudioFileTag& fileTag, bool& isPCM16Le, bool& fileHeadAlign,bool& DataSizeToTimeEqual, bool& TimeCaculateDataSizeDiff);

public:signals:
	//数据加载状态
	void sgn_loadRawDataState(int currentByte, int totalByte, bool error, QString errStr);

	//数据转换状态
	void sgn_transFerRawDataState(bool isLeftCh,int percentage,bool error, QString errStr);

protected:
	bool isPCM(const QAudioFormat& format);
	bool isPCMS16LE(const QAudioFormat& format);

	QString getWavFileFormatStr(const QAudioFormat& format);

	//从缓冲区长度倒退这个区域的时长
	QTime buffterLengthToTimeLength(qint64 buffterLength, const QAudioFormat& format);
	//从时间长度换算到这个缓冲区有几个字节
	qint64 timeLengthToBufferLength(QTime timeLength, const QAudioFormat& format);

private:
	WavFile* m_pWavFile = nullptr;


public slots:
	void slot_startPlay();
	void slot_jump(QTime jumpTime);
	void slot_stopPlay();

public:signals:
	void sgn_playPositionChanged(qint64 msec,int updateInterval);
	void sgn_stateChanged(QAudio::Mode mode, QAudio::State state);

protected:
	void reset();
	void setState(QAudio::State state);
	void setState(QAudio::Mode mode, QAudio::State state);
	void setPlayPosition(qint64 position, bool forceEmit = false);
	void stopRecording();

protected slots:
	void slot_audioStateChanged(QAudio::State state);
	void slot_audioNotify();

private:
	QAudioDeviceInfo    m_audioInputDevice;
	QAudioInput*		m_audioInput;
	QIODevice*			m_audioInputIODevice;
	qint64              m_recordPosition;


	QAudioOutput*		m_audioOutput = nullptr;
	QAudio::Mode		m_mode = QAudio::AudioInput;
	QAudio::State		m_state = QAudio::StoppedState;
	qint64				m_playPosition;

	int                 m_count = 0;
	int					m_nMediaUpdateIntervalMs = 200;
};

