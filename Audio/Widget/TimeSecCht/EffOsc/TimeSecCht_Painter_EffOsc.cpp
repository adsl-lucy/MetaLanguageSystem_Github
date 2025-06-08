#include "TimeSecCht_Painter_EffOsc.h"

TimeSecCht_Painter_EffOsc::TimeSecCht_Painter_EffOsc(QObject* parent)
	:TimeSecCht_Painter(parent)
{
	m_pSTFTwatcher = new QFutureWatcher<void>(this);
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &TimeSecCht_Painter_EffOsc::slot_GenProgressValueChanged);
}

void TimeSecCht_Painter_EffOsc::resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	bool checkEffOscDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, dataKey);
	if (!checkSTFTDataExist)
	{
		qDebug() << QString("TimeSecCht_Painter_EffOsc::resetFrameRect STFTMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("STFT Data empty!"));
		return;
	}

	if (!checkEffOscDataExist)
	{
		qDebug() << QString("TimeSecCht_Painter_EffOsc::resetFrameRect WndSpecConstrainMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("WndSpec Constrain Data empty!"));
		return;
	}

	emit sgn_SecRectGenerateState(0, QThreadPool::globalInstance()->activeThreadCount(), QString("开始预分配截面图资源"));

	const ST_STFTOutputData& dataRef = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	int frameCount = dataRef.vecOutput.size();

	m_dFreqBarBandWidth = dataRef.vecOutput[0].para.DeltaFreq;

	m_strDataKey = dataKey;
	updateTitleText(EN_TimeSecCht_PaintType::EffOsc);
	m_vecFrameBar_STFT.clear();
	ST_FFTFreqBar nullBar;
	QVector<ST_FFTFreqBar> nullbarHeightVec;

	m_vecFrameBar_UnderTIQ.clear();
	m_vecFrameBar_WndSpecNoise.clear();
	m_vecFrameBar_EffectiveOscillation.clear();

	m_vecFrameBar_UnderTIQ = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_WndSpecNoise = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_EffectiveOscillation = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);


	int GeneratebarCount = 0;
	int		currentFFTPtIndex = ceil((double)m_DataRange.minFreq / m_dFreqBarBandWidth);
	double	currentFFTPtCenterFreq = currentFFTPtIndex * m_dFreqBarBandWidth;
	while (currentFFTPtCenterFreq < m_DataRange.maxFreq)
	{
		ST_FFTFreqBar newFreqBar;
		newFreqBar.centerFreq = currentFFTPtCenterFreq;
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

	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, TimeSecCht_Painter_EffOsc::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);
}

void TimeSecCht_Painter_EffOsc::drawValueArea(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	if (m_paintSetting.EffOsc_UnderTIQBar)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_UnderTIQ.size())
		{
			const QVector<ST_FFTFreqBar>& UnderTIQBarVec = m_vecFrameBar_UnderTIQ[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_EffOsc_UnderTIQBar);

			for (int barIndex = 0; barIndex < UnderTIQBarVec.size(); barIndex++)
			{
				const QRect& drawRect = UnderTIQBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_paintSetting.EffOsc_WndSepcNoise)
	{
		if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_WndSpecNoise.size())
		{
			const QVector<ST_FFTFreqBar>& WndSpecNoiseBarVec = m_vecFrameBar_WndSpecNoise[m_nCurrentFrameIndex];
			painter.setBrush(TimeSecCht_Audio::const_Cr_EffOsc_WndSpecNoiseBar);

			for (int barIndex = 0; barIndex < WndSpecNoiseBarVec.size(); barIndex++)
			{
				const QRect& drawRect = WndSpecNoiseBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_nCurrentFrameIndex >= 0 && m_nCurrentFrameIndex < m_vecFrameBar_EffectiveOscillation.size())
	{
		const QVector<ST_FFTFreqBar>& EffectiveOscillationBarVec = m_vecFrameBar_EffectiveOscillation[m_nCurrentFrameIndex];
		painter.setBrush(TimeSecCht_Audio::const_Cr_EffOsc_EffectiveOscillationBar);

		for (int barIndex = 0; barIndex < EffectiveOscillationBarVec.size(); barIndex++)
		{
			const QRect& drawRect = EffectiveOscillationBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}
}

void TimeSecCht_Painter_EffOsc::drawMousePosValue(QPainter& painter, QRect& drawArea)
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

	bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, m_strDataKey);
	if (!checkDataExist)
	{
		return;
	}
	int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::WndSpecConstrain, m_strDataKey);

	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= frameCount)
	{
		return;
	}

	const ST_WndSpecConstrainFrame& FrameRef = DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(m_strDataKey).value().FrameVec[m_nCurrentFrameIndex];
	if (BarRef.FFTPtIndex < 0 || BarRef.FFTPtIndex >= FrameRef.VecSTFTPtState.size())
	{
		return;
	}
	valStrRectSize = QSize(350, 150);
	const ST_WndSpecConstrainPtTag& ptTag = FrameRef.VecSTFTPtState[BarRef.FFTPtIndex];

	QString ConstrainSourceIndexStr = QString("ConstrainSourceIndex	: %1 \n").arg(ptTag.ConstrainSourceIndex);
	QString ConstrainSourceFreqStr	= QString("ConstrainSourceFreq	: %1 \n").arg(ptTag.ConstrainSourceFreq, 0, 'f', 2);
	QString MaxConstrainValStr		= QString("ConstrainVal			: %1 \n").arg(ptTag.MaxConstrainVal_Compare, 0, 'f', 8);
	QString MaxConstrainDBStr		= QString("ConstrainDB			: %1 \n").arg(ptTag.MaxConstrainDB_Compare, 0, 'f', 2);
	QString ptStateStr				= QString("ptState				: %1 \n").arg(WndSpecConstrainNetwork::instance()->getWndConstrainStateStr(ptTag.ptConstrainState));

	showStr += ConstrainSourceIndexStr + ConstrainSourceFreqStr + MaxConstrainValStr + MaxConstrainDBStr + ptStateStr;

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

void TimeSecCht_Painter_EffOsc::drawLengend(QPainter& painter, QRect& RightColorMapRect)
{
	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	painter.setPen(NormalTextPen);

	const QString UnderTIQLegendStr = QString("UnderTIQ");
	const QString WndSpecNoiseLegendStr = QString("WndSpecNoise");
	const QString EffectiveOscillationLegendStr = QString("effectOsc");

	drawCrRectLegend(painter, RightColorMapRect, 1, UnderTIQLegendStr				, TimeSecCht_Audio::const_Cr_EffOsc_UnderTIQBar);
	drawCrRectLegend(painter, RightColorMapRect, 2, WndSpecNoiseLegendStr			, TimeSecCht_Audio::const_Cr_EffOsc_WndSpecNoiseBar);
	drawCrRectLegend(painter, RightColorMapRect, 3, EffectiveOscillationLegendStr	, TimeSecCht_Audio::const_Cr_EffOsc_EffectiveOscillationBar);
}

bool TimeSecCht_Painter_EffOsc::generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& frameData)
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

	bool WndSpecConstrainDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, m_strDataKey);

	if (!WndSpecConstrainDataExist)
	{
		return false;
	}

	const ST_WndSpecConstrainResult& WndSpecConstrainDataRef = DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(m_strDataKey).value();
	const ST_WndSpecConstrainFrame& WndConstrainFrameRef = WndSpecConstrainDataRef.FrameVec[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& UnderTIQFrameVecRef = m_vecFrameBar_UnderTIQ[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& WndSpecNoiseFrameVecRef = m_vecFrameBar_WndSpecNoise[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& EffectiveOscillationFrameVecRef = m_vecFrameBar_EffectiveOscillation[STFTFrameIndex];

	UnderTIQFrameVecRef.clear();
	WndSpecNoiseFrameVecRef.clear();
	EffectiveOscillationFrameVecRef.clear();

	for (int FFTFreqBarIndex = 0; FFTFreqBarIndex < barHeightVec.size(); FFTFreqBarIndex++)
	{
		const ST_FFTFreqBar& FreqBarRef = barHeightVec[FFTFreqBarIndex];
		const ST_WndSpecConstrainPtTag& ptTag = WndConstrainFrameRef.VecSTFTPtState[FreqBarRef.FFTPtIndex];

		switch (ptTag.ptConstrainState)
		{
			case EN_WndSepcConstrainState::UnderTIQ:UnderTIQFrameVecRef.push_back(FreqBarRef); break;
			case EN_WndSepcConstrainState::WndSpecNoise:WndSpecNoiseFrameVecRef.push_back(FreqBarRef); break;
			case EN_WndSepcConstrainState::EffectiveOscillation:EffectiveOscillationFrameVecRef.push_back(FreqBarRef); break;
		}
	}

	return true;

}

void TimeSecCht_Painter_EffOsc::slot_GenFinished()
{
	emit  sgn_GenFinished();
	m_currentProcessVec.clear();
}

void TimeSecCht_Painter_EffOsc::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "TimeSecCht_Painter_EffOsc::slot_GenProgressValueChanged RectVec empty!";
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
