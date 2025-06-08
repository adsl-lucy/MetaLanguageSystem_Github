#include "AudioMainWgt.h"

AudioMainWgt::AudioMainWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_pLoadAudioFileWgt = new LoadAudioFileWgt(this);
	ui.VLayout_AudioFileOpenTab->insertWidget(0, m_pLoadAudioFileWgt);

	m_pRecorderWgt = new AudioRecorder(this);
	ui.HLayout_tab_recorder->insertWidget(0, m_pRecorderWgt);

	m_pFFTTestWgt = new FFTTestWgt(this);
	ui.VLayout_FFT_Test->insertWidget(0, m_pFFTTestWgt);

	m_pSTFTWgt = new STFTWgt(this);
	ui.VLayout_STFT->insertWidget(0, m_pSTFTWgt);

	connect(m_pLoadAudioFileWgt,&LoadAudioFileWgt::sgn_autoGenSTFTData,this, [=](QString dataKey)
		{
			ui.tabWidget->setCurrentIndex(3);
			m_pSTFTWgt->slot_AudoGenSTFTData(dataKey);
		});

	m_pEffOscWgt = new EffOscWgt(this);
	ui.VLayout_EffOscWgt->insertWidget(0, m_pEffOscWgt);

	m_pFFTWndWgt = new FFTWindowWgt(this);
	ui.VLayout_FFT_Wnd->insertWidget(0, m_pFFTWndWgt);

	connect(m_pSTFTWgt, &STFTWgt::sgn_startGenWndSpecConstrainResult, this, [=](QString dataKey) 
		{
			ui.tabWidget->setCurrentIndex(4);
			m_pFFTWndWgt->slot_AudoGenWndSpecConstrainResult(dataKey);
		});

	m_pBandWidthSelWgt = new BandWidthSNRSelWgt(this);
	ui.VLayout_SNRSelWgt->insertWidget(0, m_pBandWidthSelWgt);

	connect(m_pFFTWndWgt, &FFTWindowWgt::sgn_GoBDSNRResult, this, [=](QString dataKey)
		{
			ui.tabWidget->setCurrentIndex(5);
			m_pBandWidthSelWgt->slot_autoGenBDSNRResult(dataKey);
		});


	m_pEffSigBuffWgt = new EffSigBuffWgt(this);
	ui.VLayout_EffSigBuffWgt->insertWidget(0, m_pEffSigBuffWgt);

	connect(m_pBandWidthSelWgt, &BandWidthSNRSelWgt::sgn_goEffSigBuffWgt, this, [=](QString dataKey)
		{
			ui.tabWidget->setCurrentIndex(6);
			m_pEffSigBuffWgt->slot_AutoGenEffSigBuffData(dataKey);
		});


	m_pFDRWgt = new FreqDoubWgt(this);
	ui.VLayout_FDRWgt->insertWidget(0, m_pFDRWgt);

	m_pBDIWgt = new BandWidthInputWgt(this);
	ui.VLayout_BandWidthInput->insertWidget(0, m_pBDIWgt);

	m_pAudioObjWgt = new AudioObjWgt(this);
	ui.VLayout_AudioObject->insertWidget(0, m_pAudioObjWgt);

}

AudioMainWgt::~AudioMainWgt()
{}
