#include "TimeSecCht_Painter_VibState.h"

TimeSecCht_Painter_VibState::TimeSecCht_Painter_VibState(QObject* parent)
	:TimeSecCht_Painter(parent)
{
	m_pSTFTwatcher = new QFutureWatcher<void>(this);
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &TimeSecCht_Painter_VibState::slot_GenProgressValueChanged);
}

void TimeSecCht_Painter_VibState::resetTimeSecChtRect(const QString dataKey, const ST_STFTInputpara& para)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);

	if (!checkSTFTDataExist)
	{
		qDebug() << QString("TimeSecCht_Painter_EffSigBuff::resetFrameRect STFTMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("STFT Data empty!"));
		return;
	}

	emit sgn_SecRectGenerateState(0, QThreadPool::globalInstance()->activeThreadCount(), QString("开始预分配截面图资源"));

	const ST_STFTOutputData& dataRef = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();

	int frameCount = dataRef.vecOutput.size();

	m_dFreqBarBandWidth = dataRef.vecOutput[0].para.DeltaFreq;

	m_strDataKey = dataKey;
	updateTitleText(EN_TimeSecCht_PaintType::VibState);
	m_vecFrameBar_STFT.clear();
	ST_FFTFreqBar nullBar;
	QVector<ST_FFTFreqBar> nullbarHeightVec;
	m_vecFrameBar_Atk.clear();
	m_vecFrameBar_Increase.clear();
	m_vecFrameBar_Sustain.clear();
	m_vecFrameBar_Decrease.clear();

	m_vecFrameBar_transfer_NotTransfer.clear();
	m_vecFrameBar_transfer_Atk.clear();
	m_vecFrameBar_transfer_Increase.clear();
	m_vecFrameBar_transfer_Sustain.clear();
	m_vecFrameBar_transfer_Decrease.clear();

	m_vecFrameBar_Atk		= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_Increase	= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_Sustain	= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_Decrease	= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);

	m_vecFrameBar_transfer_NotTransfer = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_transfer_Atk = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_transfer_Increase = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_transfer_Sustain = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_transfer_Decrease = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);

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

	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, TimeSecCht_Painter_VibState::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);
}

void TimeSecCht_Painter_VibState::drawValueArea(QPainter& painter, QRect& drawArea)
{
	if (m_vecFrameBar_STFT.isEmpty())
	{
		return;
	}
	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= m_vecFrameBar_STFT.size())
	{
		return;
	}

	QPen RectPen;
	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	auto drawVecRec = [&painter](const QColor BrushCr, const QVector<ST_FFTFreqBar>& PaintVec)
		{
			painter.setBrush(BrushCr);
			for (const ST_FFTFreqBar& FreqBar : PaintVec)
			{
				painter.drawRect(FreqBar.BarRect);
			}
		};

	if (m_paintSetting.VibState_transferOnly)
	{
		if (m_paintSetting.VibState_NotTransfer)	drawVecRec(TimeSecCht_Audio::const_Cr_VibState_NotTransfer	, m_vecFrameBar_transfer_NotTransfer[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Atk)			drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Atk			, m_vecFrameBar_transfer_Atk[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Increase)		drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Increase		, m_vecFrameBar_transfer_Increase[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Sustain)		drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Sustain		, m_vecFrameBar_transfer_Sustain[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Decrease)		drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Decrease		, m_vecFrameBar_transfer_Decrease[m_nCurrentFrameIndex]);

	}
	else
	{
		if (m_paintSetting.VibState_Atk)		drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Atk			, m_vecFrameBar_Atk[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Increase)	drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Increase		, m_vecFrameBar_Increase[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Sustain)	drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Sustain		, m_vecFrameBar_Sustain[m_nCurrentFrameIndex]);
		if (m_paintSetting.VibState_Decrease)	drawVecRec(TimeSecCht_Audio::const_Cr_VibState_Decrease		, m_vecFrameBar_Decrease[m_nCurrentFrameIndex]);
	}

}

void TimeSecCht_Painter_VibState::drawMousePosValue(QPainter& painter, QRect& drawArea)
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

	bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::VibState, m_strDataKey);
	if (!checkDataExist)
	{
		return;
	}
	int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::VibState, m_strDataKey);

	if (m_nCurrentFrameIndex < 0 || m_nCurrentFrameIndex >= frameCount)
	{
		return;
	}

	const ST_VibrateStateNetworkFrame& FrameRef = DataCenterManager::instance()->getVibStateOutputMap().find(m_strDataKey).value().FrameVec[m_nCurrentFrameIndex];
	if (BarRef.FFTPtIndex < 0 || BarRef.FFTPtIndex >= FrameRef.VecVibratePt.size())
	{
		return;
	}
	valStrRectSize = QSize(350, 150);
	const ST_VibrateStatePt& ptTag = FrameRef.VecVibratePt[BarRef.FFTPtIndex];

	
	QString EffSigVal_DB			= QString("EffDB	: %1 \n").arg(AudioProtocol::fftRealToDB(ptTag.EffSigVal,const_audio_normalAudioFileMaxDB), 0, 'f',1);
	QString FirstOrderDiffVal		= QString("Diff		:[Ratio][Val]	: [%1%][%2] \n").arg(ptTag.FirstOrderDiffRatio * 100, 0, 'f', 2).arg(ptTag.FirstOrderDiffVal, 0, 'f',5);
	QString ptStateStr				= QString("[ptState][isTransfer]	: [%1][%2] \n")
		.arg(VibrateStateRelvanceNetwork::instance()->getVibStateStr(ptTag.ptState),AudioProtocol::boolToStr(ptTag.isTransferPt));
	QString StateCountStr			= QString("state Count:[Exist][current]	:[%1][%2] \n").arg(ptTag.PersistentExistFrameCount).arg(ptTag.StatePersisFrame);
	

	showStr += EffSigVal_DB + FirstOrderDiffVal + ptStateStr + StateCountStr;

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

void TimeSecCht_Painter_VibState::drawLengend(QPainter& painter, QRect& RightColorMapRect)
{
	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	painter.setPen(NormalTextPen);

	QString AtkStr		= QString("Atk");
	QString InCreaseStr = QString("Increase");
	QString SustainStr	= QString("Sustain");
	QString DecreaseStr = QString("Decrease");
	QString notTransferStr = QString("notTransfer");

	drawCrRectLegend(painter, RightColorMapRect, 1, AtkStr			, TimeSecCht_Audio::const_Cr_VibState_Atk);
	drawCrRectLegend(painter, RightColorMapRect, 2, InCreaseStr		, TimeSecCht_Audio::const_Cr_VibState_Increase);
	drawCrRectLegend(painter, RightColorMapRect, 3, SustainStr		, TimeSecCht_Audio::const_Cr_VibState_Sustain);
	drawCrRectLegend(painter, RightColorMapRect, 4, DecreaseStr, TimeSecCht_Audio::const_Cr_VibState_Decrease);
	drawCrRectLegend(painter, RightColorMapRect, 5, notTransferStr	, TimeSecCht_Audio::const_Cr_VibState_NotTransfer);
}

bool TimeSecCht_Painter_VibState::generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& frameData)
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

	bool VibStateDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::VibState, m_strDataKey);

	if (!VibStateDataExist)
	{
		return false;
	}

	const ST_VibrateStateNetworkNetworkData&	VibStateDataRef		= DataCenterManager::instance()->getVibStateOutputMap().find(m_strDataKey).value();
	const ST_VibrateStateNetworkFrame&			VibStateFrameRef	= VibStateDataRef.FrameVec[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& AtkFrameVecRef		= m_vecFrameBar_Atk[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& IncreaseFrameVecRef = m_vecFrameBar_Increase[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& SustainFrameVecRef	= m_vecFrameBar_Sustain[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& DecreasFrameVecRef	= m_vecFrameBar_Decrease[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& transfer_NotTransferFrameVecRef = m_vecFrameBar_transfer_NotTransfer[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& transfer_AtkFrameVecRef			= m_vecFrameBar_transfer_Atk[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& transfer_IncreaseFrameVecRef	= m_vecFrameBar_transfer_Increase[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& transfer_SustainFrameVecRef		= m_vecFrameBar_transfer_Sustain[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& transfer_DecreaseFrameVecRef	= m_vecFrameBar_transfer_Decrease[STFTFrameIndex];

	AtkFrameVecRef.clear();
	IncreaseFrameVecRef.clear();
	SustainFrameVecRef.clear();
	DecreasFrameVecRef.clear();

	transfer_NotTransferFrameVecRef.clear();
	transfer_AtkFrameVecRef.clear();
	transfer_IncreaseFrameVecRef.clear();
	transfer_SustainFrameVecRef.clear();
	transfer_DecreaseFrameVecRef.clear();

	for (int FFTFreqBarIndex = 0; FFTFreqBarIndex < barHeightVec.size(); FFTFreqBarIndex++)
	{
		const ST_FFTFreqBar& FreqBarRef = barHeightVec[FFTFreqBarIndex];
		const ST_VibrateStatePt& ptTag = VibStateFrameRef.VecVibratePt[FreqBarRef.FFTPtIndex];

		switch (ptTag.ptState)
		{
			case EN_VibrateState::null:/**/; break;
			case EN_VibrateState::Attack	:AtkFrameVecRef.push_back(FreqBarRef); break;
			case EN_VibrateState::Increase	:IncreaseFrameVecRef.push_back(FreqBarRef); break;
			case EN_VibrateState::Sustain	:SustainFrameVecRef.push_back(FreqBarRef); break;
			case EN_VibrateState::Decrease	:DecreasFrameVecRef.push_back(FreqBarRef); break;
		}

		if (ptTag.isTransferPt)
		{
			switch (ptTag.ptState)
			{
				case EN_VibrateState::null:/**/; break;
				case EN_VibrateState::Attack:transfer_AtkFrameVecRef.push_back(FreqBarRef); break;
				case EN_VibrateState::Increase:transfer_IncreaseFrameVecRef.push_back(FreqBarRef); break;
				case EN_VibrateState::Sustain:transfer_SustainFrameVecRef.push_back(FreqBarRef); break;
				case EN_VibrateState::Decrease:transfer_DecreaseFrameVecRef.push_back(FreqBarRef); break;
			}
		}
		else if(ptTag.ptState != EN_VibrateState::null)
		{
			transfer_NotTransferFrameVecRef.push_back(FreqBarRef);
		}

	}

	return true;

}

void TimeSecCht_Painter_VibState::slot_GenFinished()
{
	emit  sgn_GenFinished();
	m_currentProcessVec.clear();
}

void TimeSecCht_Painter_VibState::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "TimeSecCht_Painter_VibState::slot_GenProgressValueChanged RectVec empty!";
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
