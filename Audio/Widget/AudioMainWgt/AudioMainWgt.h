#pragma once

#include <QWidget>
#include "./ui_AudioMainWgt.h"
#include "../LoadAudioFileWgt/LoadAudioFileWgt.h"
#include "../AudioRecorder/audiorecorder.h"
#include "../FFTTestWgt/FFTTestWgt.h"
#include "../STFTWgt/STFTWgt.h"
#include "../FFTWindowWgt/FFTWindowWgt.h"
#include "../BandWidthSNRSelWgt/BandWidthSNRSelWgt.h"
#include "../FreqDoubWgt/FreqDoubWgt.h"
#include "../EffSigBuffWgt/EffSigBuffWgt.h"
#include "../BandWidthInputWgt/BandWidthInputWgt.h"
#include "../AudioObjWgt/AudioObjWgt.h"
#include "../EffOscWgt/EffOscWgt.h"

class AudioMainWgt : public QWidget
{
	Q_OBJECT

public:
	AudioMainWgt(QWidget *parent = nullptr);
	~AudioMainWgt();

private:
	Ui::AudioMainWgtClass ui;

	LoadAudioFileWgt*	m_pLoadAudioFileWgt = nullptr;
	AudioRecorder*		m_pRecorderWgt		= nullptr;
	FFTTestWgt*			m_pFFTTestWgt		= nullptr;
	STFTWgt*			m_pSTFTWgt			= nullptr;
	EffOscWgt*			m_pEffOscWgt		= nullptr;
	FFTWindowWgt*		m_pFFTWndWgt		= nullptr;
	BandWidthSNRSelWgt* m_pBandWidthSelWgt	= nullptr;
	EffSigBuffWgt*		m_pEffSigBuffWgt	= nullptr;
	FreqDoubWgt*		m_pFDRWgt			= nullptr;
	BandWidthInputWgt*	m_pBDIWgt			= nullptr;
	AudioObjWgt*		m_pAudioObjWgt		= nullptr;

};
