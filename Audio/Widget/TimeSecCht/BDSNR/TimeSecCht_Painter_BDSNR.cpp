#include "TimeSecCht_Painter_BDSNR.h"

TimeSecCht_Painter_BDSNR::TimeSecCht_Painter_BDSNR(QObject* parent)
	:TimeSecCht_Painter(parent)
{
	m_pSTFTwatcher = new QFutureWatcher<void>(this);
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &TimeSecCht_Painter_BDSNR::slot_GenProgressValueChanged);
}

void TimeSecCht_Painter_BDSNR::resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	bool checkBDSNRDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, dataKey);
	if (!checkSTFTDataExist)
	{
		qDebug() << QString("OscillationSeparatorTimeSecCht::resetFrameRect STFTMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("STFT Data empty!"));
		return;
	}

	if (!checkBDSNRDataExist)
	{
		qDebug() << QString("OscillationSeparatorTimeSecCht::resetFrameRect BDSNRMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("BDSNR Data empty!"));
		return;
	}
	m_strDataKey = dataKey;
	updateTitleText(EN_TimeSecCht_PaintType::BDSNR);

	emit sgn_SecRectGenerateState(0, QThreadPool::globalInstance()->activeThreadCount(), QString("开始预分配截面图资源"));

	const ST_STFTOutputData& dataRef = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	int frameCount = dataRef.vecOutput.size();

	m_drawFilterData = DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value().FilterData;

	QVector<ST_BandWidthFilterActiveRect>	FilterRectBasicVec;
	QVector<ST_FFTFreqBar>					FilterBasicFrame;
	GenBasicFilterRect(m_drawFilterData.FilterVec, FilterRectBasicVec, FilterBasicFrame);
	m_vecDrawBandWidthFilterRect.clear();
	m_vecDrawBandWidthFilterRect = QVector<QVector<ST_BandWidthFilterActiveRect>>(frameCount, FilterRectBasicVec);
	m_vecFrameBar_BDSNR_ActiveFilter_Main = QVector<QVector<ST_FFTFreqBar>>(frameCount, FilterBasicFrame);
	m_vecFrameBar_BDSNR_ActiveFilter_Sub = QVector<QVector<ST_FFTFreqBar>>(frameCount, FilterBasicFrame);

	m_dFreqBarBandWidth = dataRef.vecOutput[0].para.DeltaFreq;

	
	m_vecFrameBar_STFT.clear();
	ST_FFTFreqBar nullBar;
	QVector<ST_FFTFreqBar> nullbarHeightVec;

	m_vecFrameBar_BDSNR_Noise.clear();
	m_vecFrameBar_BDSNR_Constrain.clear();
	m_vecFrameBar_BDSNR_EffectPt_Main.clear();
	m_vecFrameBar_BDSNR_EffectPt_Sub.clear();

	m_vecFrameBar_BDSNR_Noise = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_Constrain = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_EffectPt_Main = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_EffectPt_Sub = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);

	int GeneratebarCount = 0;
	int		currentFFTPtIndex = ceil((double)m_DataRange.minFreq / m_dFreqBarBandWidth);
	double	currentFFTPtCenterFreq = currentFFTPtIndex * m_dFreqBarBandWidth;
	while (currentFFTPtCenterFreq < m_DataRange.maxFreq)
	{
		ST_FFTFreqBar newFreqBar;
		newFreqBar.centerFreq = currentFFTPtCenterFreq;
		//newFreqBar.bandWidth = FreqDelta;
		newFreqBar.FFTPtIndex = currentFFTPtIndex;
		newFreqBar.BarRect = QRect(0, 0, 0, 0);
		nullbarHeightVec.push_back(newFreqBar);
		currentFFTPtIndex += 1;
		currentFFTPtCenterFreq = currentFFTPtIndex * m_dFreqBarBandWidth;
	}

	m_vecFrameBar_STFT = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);

	ST_SecChtThreadProcessData nullData;
	nullData.dataKey = m_strDataKey;
	nullData.pPainter = this;
	nullData.frameIndex = -1;
	m_currentProcessVec.clear();
	m_currentProcessVec = QVector<ST_SecChtThreadProcessData>(frameCount, nullData);
	for (int index = 0; index < frameCount; index++)
	{
		m_currentProcessVec[index].frameIndex = index;
	}

	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, TimeSecCht_Painter_BDSNR::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);
}

void TimeSecCht_Painter_BDSNR::drawValueArea(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	if (m_paintSetting.BDSNR_Noise)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_BDSNR_Noise.size())
		{
			const QVector<ST_FFTFreqBar>& BDSNR_NoiseBarVec = m_vecFrameBar_BDSNR_Noise[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_Noise);

			for (int barIndex = 0; barIndex < BDSNR_NoiseBarVec.size(); barIndex++)
			{
				const QRect& drawRect = BDSNR_NoiseBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_BDSNR_EffectPt_Main.size())
	{
		const QVector<ST_FFTFreqBar>& BDSNR_EffectMainPtBarVec = m_vecFrameBar_BDSNR_EffectPt_Main[m_nCurrentFrameIndex];
		painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_Signal_Effective_Main);

		for (int barIndex = 0; barIndex < BDSNR_EffectMainPtBarVec.size(); barIndex++)
		{
			const QRect& drawRect = BDSNR_EffectMainPtBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}

	if (m_paintSetting.BDSNR_ActiveFilter && m_paintSetting.BDSNR_ActiveFilter_Main)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter_Main.size())
		{
			const QVector<ST_FFTFreqBar>& NDSNR_ActiveMainFilterBarVec = m_vecFrameBar_BDSNR_ActiveFilter_Main[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilterBar_Active_Main);
			for (int barIndex = 0; barIndex < NDSNR_ActiveMainFilterBarVec.size(); barIndex++)
			{
				const QRect& drawRect = NDSNR_ActiveMainFilterBarVec[barIndex].BarRect;
				if (drawRect.height() > 0)
				{
					painter.drawRect(drawRect);
				}
			}
		}
	}

	if (m_paintSetting.BDSNR_EffectSubPt)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_BDSNR_EffectPt_Sub.size())
		{
			const QVector<ST_FFTFreqBar>& BDSNR_EffectSubPtBarVec = m_vecFrameBar_BDSNR_EffectPt_Sub[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_Signal_Effective_Sub);

			for (int barIndex = 0; barIndex < BDSNR_EffectSubPtBarVec.size(); barIndex++)
			{
				const QRect& drawRect = BDSNR_EffectSubPtBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_paintSetting.BDSNR_ActiveFilter)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter_Sub.size())
		{
			const QVector<ST_FFTFreqBar>& NDSNR_ActiveSubFilterBarVec = m_vecFrameBar_BDSNR_ActiveFilter_Sub[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilterBar_Active_Sub);
			for (int barIndex = 0; barIndex < NDSNR_ActiveSubFilterBarVec.size(); barIndex++)
			{
				const QRect& drawRect = NDSNR_ActiveSubFilterBarVec[barIndex].BarRect;
				if (drawRect.height() > 0)
				{
					painter.drawRect(drawRect);
				}
			}
		}
	}

	if (m_paintSetting.BDSNR_ConstrainPt)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_BDSNR_Constrain.size())
		{
			const QVector<ST_FFTFreqBar>& BDSNR_ConstrainBarVec = m_vecFrameBar_BDSNR_Constrain[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_Signal_Constrain);
			for (int barIndex = 0; barIndex < BDSNR_ConstrainBarVec.size(); barIndex++)
			{
				const QRect& drawRect = BDSNR_ConstrainBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}
}

void TimeSecCht_Painter_BDSNR::drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea)
{
	if (m_vecDrawBandWidthFilterRect.isEmpty())
	{
		return;
	}

	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= m_vecDrawBandWidthFilterRect.size())
	{
		return;
	}

	painter.setPen(Qt::white);
	const QVector<ST_BandWidthFilterActiveRect>& FrameVec = m_vecDrawBandWidthFilterRect[m_nCurrentFrameIndex];

	for (int FilterRectIndex = 0; FilterRectIndex < FrameVec.size(); FilterRectIndex++)
	{
		const ST_BandWidthFilterActiveRect& FilterRectRef = FrameVec[FilterRectIndex];
		if (FilterRectRef.isFilterActive)
		{
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilter_Active);
		}
		else
		{
			painter.setBrush(TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilter_InActive);
		}
		painter.drawRect(FilterRectRef.FilterPosRect);
	}
}

void TimeSecCht_Painter_BDSNR::drawMousePosValue(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);
	painter.setBrush(Qt::white);

	int FreqVal = PosXToFreq(m_ptMousePos.x());

	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= m_vecFrameBar_STFT.size())
	{
		return;
	}

	const QVector<ST_FFTFreqBar>& freamVecRef = m_vecFrameBar_STFT[m_nCurrentFrameIndex];

	int BarIndex = (double)(FreqVal - m_DataRange.minFreq) / m_dFreqBarBandWidth;
	if (BarIndex < 0 || BarIndex >= freamVecRef.size())
	{
		return;
	}

	const ST_FFTFreqBar& BarRef = freamVecRef[BarIndex];

	double frameMsec = m_STFTPara.GapInTimeLength * 1000 * m_nCurrentFrameIndex;
	QTime frameTime = QTime(0, 0, 0).addMSecs(frameMsec);

	QString IndexStr = QString("[Frame][Freq] : [%1][%2] \n").arg(m_nCurrentFrameIndex).arg(BarRef.FFTPtIndex);
	QString PosValStr = QString("CenterFreq   : %1 hz	time : %2 \n").arg(BarRef.centerFreq, 0, 'f', 1).arg(frameTime.toString("mm:ss.zzz"));

	QString doubleValStr = QString("val : %1 \n").arg(BarRef.doubleVal, 0, 'f', 8);
	QString dbStr = QString("DB : %1 \n").arg(BarRef.DBVal, 0, 'f', 2);

	QSize valStrRectSize;
	QString showStr;

	showStr = IndexStr + PosValStr + doubleValStr + dbStr;

	bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, m_strDataKey);
	if (!checkDataExist)
	{
		return;
	}
	int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::BDSNR, m_strDataKey);

	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= frameCount)
	{
		return;
	}

	const ST_BandWidthSNRConstrainFrame& FrameRef = DataCenterManager::instance()->getBDSNROutputMap().find(m_strDataKey).value().FrameVec[m_nCurrentFrameIndex];
	if (BarRef.FFTPtIndex < 0 || BarRef.FFTPtIndex >= FrameRef.vecBDSNRptTag.size())
	{
		return;
	}
	valStrRectSize = QSize(350, 150);
	const ST_BandWidthSNRPtTag& ptTag = FrameRef.vecBDSNRptTag[BarRef.FFTPtIndex];

	QString ptStateStr = QString("ptState				: %1 isMainAreaPt : %2\n")
		.arg(BandWidthFilterManager::instance()->ConstrainPtTypeToStr(ptTag.ptSNRConstrainType))
		.arg(AudioProtocol::boolToStr(ptTag.isMainAreaSignal));
	QString MaskedByFilterIndexStr = QString("MaskedByFilterIndex	: %1 \n").arg(ptTag.MaskedByFilterIndex);
	QString MaskMainStr = QString("MainMask :[Amp][DB]	: [%1][%2] \n")
		.arg(ptTag.MaskAmp_Main, 0, 'f', 8).arg(AudioProtocol::fftRealToDB(ptTag.MaskAmp_Main, const_audio_normalAudioFileMaxDB));
	QString MaskSubStr = QString("SubMask	:[Amp][DB]	: [%1][%2] \n")
		.arg(ptTag.MaskAmp_Sub, 0, 'f', 8).arg(AudioProtocol::fftRealToDB(ptTag.MaskAmp_Sub, const_audio_normalAudioFileMaxDB));

	showStr += ptStateStr + MaskedByFilterIndexStr + MaskMainStr + MaskSubStr;
	;
	QRect valStrRect;
	valStrRect.setSize(valStrRectSize);

	int RectStartX = m_ptMousePos.x();
	int RectStartY = m_ptMousePos.y();

	if (RectStartX + valStrRectSize.width() > drawArea.right())
	{
		RectStartX -= valStrRectSize.width();
	}

	if (RectStartY + valStrRectSize.height() > m_ChtRect.bottom())
	{
		RectStartY -= valStrRectSize.height();
	}

	valStrRect.moveTopLeft(QPoint(RectStartX, RectStartY));

	QRect valBgRect;
	valBgRect.setSize(valStrRectSize + QSize(3, 3));
	valBgRect.moveCenter(valStrRect.center());

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(valBgRect);
	painter.drawText(valStrRect, Qt::AlignLeft, showStr);
}

void TimeSecCht_Painter_BDSNR::drawLengend(QPainter& painter, QRect& RightColorMapRect)
{
	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	painter.setPen(NormalTextPen);

	QString NoiseLegendStr = QString("Noise");
	QString ConstrainLegendStr = QString("Sig_Constrain");
	QString EffMainLegendStr = QString("Sig_Eff_Main");
	QString EffSubLegendStr = QString("Sig_Eff_Sub");
	QString InActFilterLegendStr = QString("Flt_InAct");
	QString ActFilterLegendStr = QString("Flt_Act");
	QString ActFilterMainLegendStr = QString("Flt_Act_Main");
	QString ActFilterSubLegendStr = QString("Flt_Act_Sub");

	drawCrRectLegend(painter, RightColorMapRect, 0, NoiseLegendStr			, TimeSecCht_Audio::const_Cr_BDSNR_Noise);
	drawCrRectLegend(painter, RightColorMapRect, 1, ConstrainLegendStr		, TimeSecCht_Audio::const_Cr_BDSNR_Signal_Constrain);
	drawCrRectLegend(painter, RightColorMapRect, 2, EffMainLegendStr		, TimeSecCht_Audio::const_Cr_BDSNR_Signal_Effective_Main);
	drawCrRectLegend(painter, RightColorMapRect, 3, EffSubLegendStr			, TimeSecCht_Audio::const_Cr_BDSNR_Signal_Effective_Sub);
	drawCrRectLegend(painter, RightColorMapRect, 4, InActFilterLegendStr	, TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilter_InActive);
	drawCrRectLegend(painter, RightColorMapRect, 5, ActFilterLegendStr		, TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilter_Active);
	drawCrRectLegend(painter, RightColorMapRect, 6, ActFilterMainLegendStr	, TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilterBar_Active_Main);
	drawCrRectLegend(painter, RightColorMapRect, 7, ActFilterSubLegendStr	, TimeSecCht_Audio::const_Cr_BDSNR_ConstrainFilterBar_Active_Sub);
}

void TimeSecCht_Painter_BDSNR::drawActiveRectValue(QPainter& painter)
{
	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= m_vecDrawBandWidthFilterRect.size())
	{
		return;
	}

	const QVector<ST_BandWidthFilterActiveRect>& freamVecRef = m_vecDrawBandWidthFilterRect[m_nCurrentFrameIndex];

	int FilterRectIndex = MousePosToMFCCFilterRectIndex(m_ptMousePos);
	if (FilterRectIndex < 0 || FilterRectIndex >= freamVecRef.size())
	{
		return;
	}

	const ST_BandWidthFilterActiveRect& MFCCActRect = freamVecRef[FilterRectIndex];

	int		FilterIndex = MFCCActRect.FilterIndex;

	const ST_BandWidthSNRConstrainData& BDSNRData = DataCenterManager::instance()->getBDSNROutputMap().find(m_strDataKey).value();

	const ST_BandWidthFilterPt& FilterPtRef = BDSNRData.FrameVec[m_nCurrentFrameIndex].vecBDFilterValue[FilterIndex];
	const ST_BandWidthFilter& FilterData = BDSNRData.FilterData.FilterVec[FilterIndex];

	double frameMsec = m_STFTPara.GapInTimeLength * 1000 * m_nCurrentFrameIndex;
	QTime frameTime = QTime(0, 0, 0).addMSecs(frameMsec);


	QString FrameStr = QString("Frame Index	: %1 time : %2 \n").arg(m_nCurrentFrameIndex).arg(frameTime.toString("mm:ss.zzz"));
	QString FreqStr = QString(" FilterIndex : %1 centerFreq : %2 bandwidth %3 \n").arg(MFCCActRect.FilterIndex).arg(FilterData.CenterFreq, 0, 'f', 1).arg(FilterData.Width);
	QString ActiveStr = QString("isActive		: %1 \n").arg(AudioProtocol::boolToStr(FilterPtRef.isActive));

	QString MaxAmpValStr = QString("MaxAmp		:[Index][Val][Db]: [%1][%2][%3] \n")
		.arg(FilterPtRef.BandWidthMaxAmpIndex).arg(FilterPtRef.BandWidthMaxAmp, 0, 'f', 8).arg(FilterPtRef.BandWidthMaxAmp_DB, 0, 'f', 1);
	QString MaxAmp_WeightValStr = QString("MaxAmp_Weight:[Index][Val][Db][Weight]: [%1][%2][%3][%4%] \n")
		.arg(FilterPtRef.BandWidthMaxWeightAmpIndex).arg(FilterPtRef.BandWidthMaxWeightAmp, 0, 'f', 8).arg(FilterPtRef.BandWidthMaxWeightAmp_DB, 0, 'f', 1)
		.arg(FilterPtRef.BandWidthMaxWeightAmpWeight * 100, 0, 'f', 2);
	QString FilterValStr_Main = QString("FltVal_Main	:[Val][Db]: [%1][%2] \n")
		.arg(FilterPtRef.BandWidthFilterVal_MainArea, 0, 'f', 8).arg(FilterPtRef.BandWidthFilterVal_MainArea_DB, 0, 'f', 1);
	QString FilterValStr_Sub = QString("FltVal_Sub	:[Val][Db]: [%1][%2] \n")
		.arg(FilterPtRef.BandWidthFilterVal_SubArea, 0, 'f', 8).arg(FilterPtRef.BandWidthFilterVal_SubArea_DB, 0, 'f', 1);


	QSize valStrRectSize = QSize(450, 150);
	QString showStr;

	showStr = FrameStr + FreqStr + ActiveStr + MaxAmpValStr + MaxAmp_WeightValStr + FilterValStr_Main + FilterValStr_Sub;

	QRect valStrRect;
	valStrRect.setSize(valStrRectSize);

	int RectStartX = m_ptMousePos.x();
	int RectStartY = m_ptMousePos.y();

	QRect bottomAxisRect = getBottomAxisRect();

	if (RectStartX + valStrRectSize.width() > bottomAxisRect.right())
	{
		RectStartX -= valStrRectSize.width();
	}

	if (RectStartY + valStrRectSize.height() > m_ChtRect.bottom())
	{
		RectStartY -= valStrRectSize.height();
	}

	valStrRect.moveTopLeft(QPoint(RectStartX, RectStartY));

	QRect valBgRect;
	valBgRect.setSize(valStrRectSize + QSize(3, 3));
	valBgRect.moveCenter(valStrRect.center());

	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(Qt::black);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(valBgRect);
	painter.drawText(valStrRect, Qt::AlignLeft, showStr);
}

int TimeSecCht_Painter_BDSNR::MousePosToMFCCFilterRectIndex(QPoint mousePos)
{
	if (m_vecDrawBandWidthFilterRect.isEmpty())
	{
		return -1;
	}

	for (int DrawFilterIndex = 0; DrawFilterIndex < m_vecDrawBandWidthFilterRect[0].size(); DrawFilterIndex++)
	{
		const ST_BandWidthFilterActiveRect& RectRef = m_vecDrawBandWidthFilterRect[0][DrawFilterIndex];
		if (RectRef.FilterPosRect.contains(mousePos))
		{
			return DrawFilterIndex;
		}
	}

	return -1;
}

void TimeSecCht_Painter_BDSNR::GenBasicFilterRect(const QVector<ST_BandWidthFilter>& FilterVec, QVector<ST_BandWidthFilterActiveRect>& MFCCActiveVec, QVector<ST_FFTFreqBar>& MFCCFreqBarVec)
{
	QRect thisRect = m_ChtRect;
	QRect drawAreaRect = getDrawAreaRect();
	QRect BottomAxisRect = QRect(drawAreaRect.bottomLeft(), QPoint(drawAreaRect.bottomRight().x(), thisRect.height()));

	int OddFilterStartY = BottomAxisRect.bottom() - 2 * m_nFilterRectHeight - 2;
	int EvenFilterStartY = BottomAxisRect.bottom() - m_nFilterRectHeight - 2;

	MFCCActiveVec.clear();
	MFCCFreqBarVec.clear();

	QVector<int> drawFilterIndexVec;

	for (int FilterIndex = 0; FilterIndex < FilterVec.size(); FilterIndex++)
	{
		const ST_BandWidthFilter& FilterData = FilterVec[FilterIndex];

		if (FilterData.CenterFreq < m_DataRange.minFreq)
		{
			continue;
		}

		if (FilterData.CenterFreq > m_DataRange.maxFreq)
		{
			break;
		}
		drawFilterIndexVec.push_back(FilterIndex);

	}

	for (int drawFilterIndex = 0; drawFilterIndex < drawFilterIndexVec.size(); drawFilterIndex++)
	{
		int FilterIndex = drawFilterIndexVec[drawFilterIndex];
		const ST_BandWidthFilter& FilterRef = FilterVec[FilterIndex];

		int FilterStartX = qMax(drawAreaRect.left(), FreqToPosX(FilterRef.startFreq));
		int FilterEndX = qMin(drawAreaRect.right(), FreqToPosX(FilterRef.endFreq));

		int FilterStartY = 0;
		if (FilterIndex % 2 == 0)
		{
			FilterStartY = EvenFilterStartY;
		}
		else
		{
			FilterStartY = OddFilterStartY;
		}

		int FilterCenterX = (FilterStartX + FilterEndX) / 2;
		int FilterCenterY = (FilterStartY + FilterStartY + m_nFilterRectHeight) / 2;
		int FilterWidth = FilterEndX - FilterStartX;
		int FilterMargin = 1;

		QRect FilterPosRect;
		FilterPosRect.setSize(QSize(FilterWidth - FilterMargin, m_nFilterRectHeight - FilterMargin));
		FilterPosRect.moveCenter(QPoint(FilterCenterX, FilterCenterY));

		ST_BandWidthFilterActiveRect FilterRect;
		FilterRect.FilterIndex = FilterIndex;
		FilterRect.FilterPosRect = FilterPosRect;
		FilterRect.isFilterActive = false;

		MFCCActiveVec.push_back(FilterRect);

		ST_FFTFreqBar NewMFCCFreqBar;
		NewMFCCFreqBar.centerFreq = FilterRef.CenterFreq;
		NewMFCCFreqBar.FilterBandWidth = FilterRef.Width;
		NewMFCCFreqBar.BarRect.setBottom(drawAreaRect.bottom());
		NewMFCCFreqBar.BarRect.setTop(drawAreaRect.bottom());
		NewMFCCFreqBar.BarRect.setLeft(FilterStartX);
		NewMFCCFreqBar.BarRect.setRight(FilterEndX);
		NewMFCCFreqBar.FilterIndex = FilterIndex;
		MFCCFreqBarVec.push_back(NewMFCCFreqBar);

	}
}

bool TimeSecCht_Painter_BDSNR::generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& frameData)
{
	if (frameData.resultVec.isEmpty())
	{
		return false;
	}

	const QVector<ST_FFTPoint> FFTPtVecRef = frameData.resultVec;

	QVector<ST_FFTFreqBar>& barHeightVec = m_vecFrameBar_STFT[STFTFrameIndex];

	for (int FreqBarIndex = 0; FreqBarIndex < barHeightVec.size(); FreqBarIndex++)
	{
		ST_FFTFreqBar& FreqBarRef = barHeightVec[FreqBarIndex];
		const ST_FFTPoint& FFTPoint = FFTPtVecRef[FreqBarRef.FFTPtIndex];
		FreqBarRef.doubleVal = FFTPoint.amplitude;
		FreqBarRef.DBVal = AudioProtocol::fftRealToDB(FreqBarRef.doubleVal, const_audio_normalAudioFileMaxDB);
		int						newHeight = getDbHeight(FreqBarRef.DBVal);
		double					startFreq = FreqBarRef.centerFreq - m_dFreqBarBandWidth / 2;
		FreqBarRef.BarRect = getFreqBarRect(startFreq, m_dFreqBarBandWidth, FreqBarRef.DBVal);
	}

	const ST_BandWidthSNRConstrainData& BDSNRResult = DataCenterManager::instance()->getBDSNROutputMap().find(m_strDataKey).value();
	const ST_BandWidthSNRConstrainFrame& BDSNRFrame = BDSNRResult.FrameVec[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& BDSNR_Noise_FrameVecRef = m_vecFrameBar_BDSNR_Noise[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& BDSNR_Constrain_FrameVecRef = m_vecFrameBar_BDSNR_Constrain[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& BDSNR_EffectMain_FrameVecRef = m_vecFrameBar_BDSNR_EffectPt_Main[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& BDSNR_EffectSub_FrameVecRef = m_vecFrameBar_BDSNR_EffectPt_Sub[STFTFrameIndex];

	for (int FFTFreqBarIndex = 0; FFTFreqBarIndex < barHeightVec.size(); FFTFreqBarIndex++)
	{
		const ST_FFTFreqBar& FreqBarRef = barHeightVec[FFTFreqBarIndex];
		const ST_BandWidthSNRPtTag& ptTag = BDSNRFrame.vecBDSNRptTag[FreqBarRef.FFTPtIndex];

		switch (ptTag.ptSNRConstrainType)
		{
		case EN_BDSNRPtType::WndSpecNoise:BDSNR_Noise_FrameVecRef.push_back(FreqBarRef); break;
		case EN_BDSNRPtType::BDSNR_ConstrainPt:BDSNR_Constrain_FrameVecRef.push_back(FreqBarRef); break;
		case EN_BDSNRPtType::BDSNR_EffectivePt:
		{
			if (ptTag.isMainAreaSignal)
			{
				BDSNR_EffectMain_FrameVecRef.push_back(FreqBarRef);
			}
			else
			{
				BDSNR_EffectSub_FrameVecRef.push_back(FreqBarRef);
			}

		}break;
		}
	}

	QVector<ST_BandWidthFilterActiveRect>& FilterActiveRectVecRef = m_vecDrawBandWidthFilterRect[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& ActiveFilterBarVecRef_Main = m_vecFrameBar_BDSNR_ActiveFilter_Main[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& ActiveFilterBarVecRef_Sub = m_vecFrameBar_BDSNR_ActiveFilter_Sub[STFTFrameIndex];

	for (int FilterActiveRectIndex = 0; FilterActiveRectIndex < FilterActiveRectVecRef.size(); FilterActiveRectIndex++)
	{
		ST_BandWidthFilterActiveRect& ActiveRectRef = FilterActiveRectVecRef[FilterActiveRectIndex];
		const ST_BandWidthFilterPt& FilterPt = BDSNRFrame.vecBDFilterValue[ActiveRectRef.FilterIndex];
		ActiveRectRef.isFilterActive = FilterPt.isActive;
	}

	QRect drawArea = getDrawAreaRect();

	for (int FilterBarIndex = 0; FilterBarIndex < ActiveFilterBarVecRef_Main.size(); FilterBarIndex++)
	{
		ST_FFTFreqBar& FreqBarRef_Main = ActiveFilterBarVecRef_Main[FilterBarIndex];
		ST_FFTFreqBar& FreqBarRef_Sub = ActiveFilterBarVecRef_Sub[FilterBarIndex];
		const ST_BandWidthFilterPt& FilterPt = BDSNRFrame.vecBDFilterValue[FreqBarRef_Main.FilterIndex];
		if (!FilterPt.isActive)
		{
			FreqBarRef_Main.BarRect.setHeight(0);
			FreqBarRef_Sub.BarRect.setHeight(0);
		}
		else
		{
			double MFCCVal = FilterPt.BandWidthFilterVal_MainArea;
			double MFCCDB = AudioProtocol::fftRealToDB(MFCCVal, const_audio_normalAudioFileMaxDB);
			int DBHeight = getDbHeight(MFCCDB);
			FreqBarRef_Main.BarRect.setHeight(DBHeight);

			MFCCVal = FilterPt.BandWidthFilterVal_SubArea;
			MFCCDB = AudioProtocol::fftRealToDB(MFCCVal, const_audio_normalAudioFileMaxDB);
			DBHeight = getDbHeight(MFCCDB);
			FreqBarRef_Sub.BarRect.setHeight(DBHeight);

		}
		FreqBarRef_Main.BarRect.moveBottom(drawArea.bottom());
		FreqBarRef_Sub.BarRect.moveBottom(drawArea.bottom());
	}

	return true;

}

void TimeSecCht_Painter_BDSNR::slot_GenFinished()
{
	emit  sgn_GenFinished();
	m_currentProcessVec.clear();
}

void TimeSecCht_Painter_BDSNR::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "TimeSecCht_Painter_BDSNR::slot_GenProgressValueChanged RectVec empty!";
		return;
	}

	int frameCount = m_currentProcessVec.size();
	int hunderdsOfFrame = qMax(1, frameCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_SecRectGenerateState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("STFT :%1 / %2 ").arg(processedCount).arg(frameCount));;
		m_nLastReportPercantage = percentage;
	}
	qDebug() << QString("slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(frameCount);
	if (percentage == 100)
	{
		slot_GenFinished();
	}
}
