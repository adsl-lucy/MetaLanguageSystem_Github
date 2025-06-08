#pragma once

#include <QColor>
#include <QSize>

enum class EN_TimeSecCht_PaintType
{
	STFT,
	EffOsc,
	BDSNR,
	VibState,
};

struct ST_TimeSecChtGenSetting
{
	bool Gen_STFT		= false;
	bool Gen_EffOsc		= false;
	bool Gen_BDSNR		= false;
	bool Gen_VibState	= false;
};

struct ST_TimeSecChtDataRange
{
	int minFreq	= 0;
	int maxFreq	= 20000;
	int minDB	= 0;
	int maxDB	= 80;
};

struct ST_TimeSecChtPaintSetting
{
	bool EffOsc_UnderTIQBar			= false;
	bool EffOsc_TIQLine				= false;	
	bool EffOsc_WndSepcNoise		= false;

	bool BDSNR_Noise				= false;
	bool BDSNR_ConstrainPt			= false;
	bool BDSNR_EffectSubPt			= false;
	bool BDSNR_ActiveFilter			= false;
	bool BDSNR_ActiveFilter_Main	= false;

	bool VibState_transferOnly		= false;
	bool VibState_NotTransfer		= false;
	bool VibState_Atk				= false;
	bool VibState_Increase			= false;
	bool VibState_Sustain			= false;
	bool VibState_Decrease			= false;
};

namespace TimeSecCht_Audio
{
	const int		const_n_FreqScaleIntervalCount			= 10;	//频率刻度尺画几个间隔
	const int		const_n_DBScaleIntervalCount			= 10;  //值刻度尺话几个间隔
	const int		const_n_AxiesScaleLength				= 5;
	const int		const_n_AxiesValStrMargin				= 5;
	const int		const_n_AxiesValStrFontSize				= 15;

	const int		const_n_LeftAxisWidth				= 80;
	const int		const_n_BottomAxisHeight			= 60;
	const int		const_n_TopTitleHeight				= 30;
	const int		const_n_RightColorMapRegionWidth	= 140;

	const int		const_n_LegendFontSize		= 12;
	const QSize		const_sz_Legend				= QSize(8, 8);
	const int		const_n_LegendLeftMargin	= 16;
	const int		const_n_LegendTopMargin		= 16;
	const int		const_n_LegendTextMargin	= 8;
	const int		const_n_LegendSpacing		= 16;

	const QColor	const_Cr_Title			= Qt::black;
	const QColor	const_Cr_Axis			= Qt::black;
	const QColor	const_Cr_STFTOnlyBar	= Qt::blue;

	const QColor	const_Cr_ThreshHoldLine						= Qt::black;
	const QColor	const_Cr_EffOsc_UnderTIQBar					= Qt::darkGray;
	const QColor	const_Cr_EffOsc_WndSpecNoiseBar				= Qt::gray;
	const QColor	const_Cr_EffOsc_EffectiveOscillationBar		= Qt::green;

	const QColor	const_Cr_BDSNR_Noise							= Qt::darkGray;
	const QColor	const_Cr_BDSNR_Signal_Constrain					= Qt::magenta;
	const QColor	const_Cr_BDSNR_Signal_Effective_Main			= Qt::red;
	const QColor	const_Cr_BDSNR_Signal_Effective_Sub				= Qt::yellow;
	const QColor	const_Cr_BDSNR_ConstrainFilter_InActive			= Qt::gray;
	const QColor	const_Cr_BDSNR_ConstrainFilter_Active			= Qt::green;
	const QColor	const_Cr_BDSNR_ConstrainFilterBar_Active_Main	= Qt::yellow;
	const QColor	const_Cr_BDSNR_ConstrainFilterBar_Active_Sub	= Qt::green;

	const QColor	const_Cr_VibState_NotTransfer = Qt::gray;
	const QColor	const_Cr_VibState_Atk			= Qt::red;
	const QColor	const_Cr_VibState_Increase		= Qt::yellow;
	const QColor	const_Cr_VibState_Sustain		= Qt::green;
	const QColor	const_Cr_VibState_Decrease		= Qt::blue;
	
};
