#pragma once
#include <QThread>

#include "../../../Audio/Perception/AudioEngine/AudioEngine.h"
#include "../../../Audio/protocol/protocol_audio.h"
#include "../../../vision/protocol/protocol_vision.h"

class ExtractAudioThread :public QThread
{
	Q_OBJECT
public:
	ExtractAudioThread(QObject* parent);

	void runWithArgument(const ST_VideoFileTag& VedioFileTag, const ST_AudioFileTag& AudioFileTag);

	ST_WavDoubleData& getWavData() {return m_WavDoubleData;};

public:signals:
	void sgn_loadState(bool state, QString errStr);

protected:
	void run() override;

private:
	ST_VideoFileTag m_VedioFileTag;
	ST_AudioFileTag m_AudioFileTag;

	ST_WavDoubleData m_WavDoubleData;

};

