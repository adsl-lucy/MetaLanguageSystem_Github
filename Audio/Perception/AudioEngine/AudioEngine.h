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

//��Ƶ���Ŷ�ȡ���
//��Ƶ����ʹ��QAudioOutput
//��Ƶ��תʹ��wavfile�ڵ�QMediaPlayer 
//��Ϊ���ֲ����������ص㣬��������ô�պ���

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

	//����ļ��Ƿ���Ч������wav�ļ���ǩ��ͨ�����÷��ؽ��
	//isPCM16Le					: ���ǲ���һ��PCM16�ļ���������ǣ���ô���ܽ���
	//fileHeadAlign				��wav��ע���ļ�ͷ�ʹ�data chunk��ȡ����ֵ��С �������ǲ���wav�ļ��Ĵ�С
	//DataSizeToTimeEqual		��ffprobe�ļ����ص��ļ�ʱ���������ݶγ��ȼ���������ļ�ʱ���Ƿ��Ǻ�
	//TimeCaculateDataSizeDiff	������ͨ��ffprobe���ص��ļ�ʱ������������ݶδ�С����ʵ�����ݶδ�С�Ĳ�ֵ����λΪ�ֽڣ�byte���������ֵ������Ƿ�1ms��Ӧ�Ĳ���������֮�ڣ�����44.1kHz ��������44.1֮�ڣ�	
	//��������ȫ��Ϊ�棬��ô����ļ���Ч������true
	//ʵ���� ���һ����ʱ���������ĵ������������������󣬵�������û��Խ���Լ������ݳ��ȼ��������ʱ�䳤����һ�µ�
	
	bool checkCaculateValidity(const ST_AudioFileTag& fileTag, bool& isPCM16Le, bool& fileHeadAlign,bool& DataSizeToTimeEqual, bool& TimeCaculateDataSizeDiff);

public:signals:
	//���ݼ���״̬
	void sgn_loadRawDataState(int currentByte, int totalByte, bool error, QString errStr);

	//����ת��״̬
	void sgn_transFerRawDataState(bool isLeftCh,int percentage,bool error, QString errStr);

protected:
	bool isPCM(const QAudioFormat& format);
	bool isPCMS16LE(const QAudioFormat& format);

	QString getWavFileFormatStr(const QAudioFormat& format);

	//�ӻ��������ȵ�����������ʱ��
	QTime buffterLengthToTimeLength(qint64 buffterLength, const QAudioFormat& format);
	//��ʱ�䳤�Ȼ��㵽����������м����ֽ�
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

