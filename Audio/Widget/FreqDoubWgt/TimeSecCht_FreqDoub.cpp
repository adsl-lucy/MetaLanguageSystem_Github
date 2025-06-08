#include "TimeSecCht_FreqDoub.h"


#pragma execution_character_set("utf-8")

TimeSecCht_FreqDoub::TimeSecCht_FreqDoub(QWidget* parent) :QWidget(parent)
{
	init();
	setMouseTracking(true);
}

TimeSecCht_FreqDoub::~TimeSecCht_FreqDoub()
{

}

void TimeSecCht_FreqDoub::init()
{

	QFont titleFont;
	titleFont.setFamily("黑体");
	titleFont.setPixelSize(20);
	m_ft_titleFont = titleFont;

	QFont legendFont;
	legendFont.setFamily("黑体");
	legendFont.setPixelSize(m_nLegendFontSize);
	m_ft_LegendFont = legendFont;

	m_pSTFTwatcher = new QFutureWatcher<void>(this);
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &TimeSecCht_FreqDoub::slot_GenProgressValueChanged);

	ResetDiffGroupColorMap(9);

}

void TimeSecCht_FreqDoub::setCurrentFrameIndex(int index)
{
	if (index < 0 || index >= m_vecFrameBar_STFT.size())
	{
		qDebug() << "TimeSecCht_FreqDoub::setCurrentFrameIndex invalid Index : " << index;
		return;
	}

	//qDebug() << m_strTitle << QString("updateFrameIndex : %1").arg(index);	

	m_ndrawFrameIndex = index;
	update();
}

void TimeSecCht_FreqDoub::setDrawFreqRanged(int startFreq, int endFreq)
{
	m_nMinFreq = startFreq;
	m_nMaxFreq = endFreq;
	update();
}

void TimeSecCht_FreqDoub::setDrawDBRange(double min, double max)
{
	m_dMinDB = min;
	m_dMaxDB = max;
	update();
}

void TimeSecCht_FreqDoub::setChtType(EN_FreqDoub_TimeSecChtBarType Type)
{
	m_showDataType = Type;
	update();
}

void TimeSecCht_FreqDoub::setNoisePaintSetting(bool TIQLine, bool UnderTIQBar, bool WndSepcNoise, bool BDSNR_Noise, bool BDSNR_Constrain, bool BDSNR_ActiveFilter, bool FreqDoubChild)
{
	m_bDrawTIQLine = TIQLine;
	m_bDrawUnderTIQBar = UnderTIQBar;
	m_bDrawWndSpecNoise = WndSepcNoise;

	m_bDraw_BDSNR_Noise = BDSNR_Noise;
	m_bDraw_BDSNR_ConstrainPt = BDSNR_Constrain;
	m_bDraw_BDSNR_ActiveFilter = BDSNR_ActiveFilter;
	m_bDraw_FreqDoub_Child = FreqDoubChild;
	update();
}

void  TimeSecCht_FreqDoub::ResetDiffGroupColorMap(int DiffGroupCount)
{
	int oneSideGroupCount = (DiffGroupCount - 3) / 2;

	m_mapSideGroupColor.clear();

	for (int GroupIndex = oneSideGroupCount * -1; GroupIndex <= oneSideGroupCount; GroupIndex++)
	{
		if (GroupIndex == 0)
		{
			m_mapSideGroupColor.insert(0, m_cr_Diff_StableGroup);
		}
		else
		{
			double SideRatio = abs((double)GroupIndex / (double)oneSideGroupCount);
			int red = 0;
			int green = 0;
			int blue = 0;
			if (GroupIndex < 0)
			{
				red = m_cr_Diff_DecreaseSideGroup.red() * SideRatio + m_cr_Diff_StableGroup.red() * (1 - SideRatio);
				green = m_cr_Diff_DecreaseSideGroup.green() * SideRatio + m_cr_Diff_StableGroup.green() * (1 - SideRatio);
				blue = m_cr_Diff_DecreaseSideGroup.blue() * SideRatio + m_cr_Diff_StableGroup.blue() * (1 - SideRatio);

			}
			else
			{
				red = m_cr_Diff_IncreaseSideGroup.red() * SideRatio + m_cr_Diff_StableGroup.red() * (1 - SideRatio);
				green = m_cr_Diff_IncreaseSideGroup.green() * SideRatio + m_cr_Diff_StableGroup.green() * (1 - SideRatio);
				blue = m_cr_Diff_IncreaseSideGroup.blue() * SideRatio + m_cr_Diff_StableGroup.blue() * (1 - SideRatio);
			}
			QColor newColor(red, green, blue);
			m_mapSideGroupColor.insert(GroupIndex, newColor);
		}
	}


}

void TimeSecCht_FreqDoub::GenBasicFilterRect(const QVector<ST_BandWidthFilter>& FilterVec, QVector<ST_BandWidthFilterActiveRect>& MFCCActiveVec, QVector<ST_FFTFreqBar>& MFCCFreqBarVec)
{
	QRect thisRect = this->rect();
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

		if (FilterData.CenterFreq < m_nMinFreq)
		{
			continue;
		}

		if (FilterData.CenterFreq > m_nMaxFreq)
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

void TimeSecCht_FreqDoub::resetFrameRect(QString dataKey)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	bool checkEffOscDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, dataKey);
	bool checkBDSNRDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, dataKey);
	bool DiffDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::Diff, dataKey);
	if (!checkSTFTDataExist)
	{
		qDebug() << QString("TimeSecCht_Diff::resetFrameRect STFTMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("STFT Data empty!"));
		return;
	}

	if (!checkEffOscDataExist)
	{
		qDebug() << QString("TimeSecCht_Diff::resetFrameRect WndSpecConstrainMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("WndSpec Constrain Data empty!"));
		return;
	}

	if (!checkBDSNRDataExist)
	{
		qDebug() << QString("TimeSecCht_Diff::resetFrameRect BDSNRMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("BDSNR Data empty!"));
		return;
	}

	if (!DiffDataExist)
	{
		qDebug() << QString("TimeSecCht_Diff::resetFrameRect DiffMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("Diff Data empty!"));
		return;
	}

	emit sgn_SecRectGenerateState(0, QThreadPool::globalInstance()->activeThreadCount(), QString("开始预分配截面图资源"));

	const ST_STFTOutputData& dataRef = DataCenterManager::instance()->getSTFTOutputMap().find(dataKey).value();
	const ST_DiffNetOutput& DiffDataRef = DataCenterManager::instance()->getDiffOutputMap().find(dataKey).value();

	int frameCount = dataRef.vecOutput.size();

	m_drawFilterData = DataCenterManager::instance()->getBDSNROutputMap().find(dataKey).value().FilterData;

	QVector<ST_BandWidthFilterActiveRect>	FilterRectBasicVec;
	QVector<ST_FFTFreqBar>					FilterBasicFrame;
	GenBasicFilterRect(m_drawFilterData.FilterVec, FilterRectBasicVec, FilterBasicFrame);
	m_vecDrawBandWidthFilterRect.clear();
	m_vecDrawBandWidthFilterRect = QVector<QVector<ST_BandWidthFilterActiveRect>>(frameCount, FilterRectBasicVec);
	m_vecFrameBar_BDSNR_ActiveFilter = QVector<QVector<ST_FFTFreqBar>>(frameCount, FilterBasicFrame);

	m_dFreqBarBandWidth = dataRef.vecOutput[0].para.DeltaFreq;

	m_currentSTFTDataKey = dataKey;
	m_vecFrameBar_STFT.clear();
	ST_FFTFreqBar nullBar;
	QVector<ST_FFTFreqBar> nullbarHeightVec;

	m_vecFrameBar_UnderTIQ.clear();
	m_vecFrameBar_WndSpecNoise.clear();
	m_vecFrameBar_EffectiveOscillation.clear();
	m_vecFrameBar_BDSNR_Noise.clear();
	m_vecFrameBar_BDSNR_Constrain.clear();
	m_vecFrameBar_BDSNR_EffectPt.clear();
	m_vecFrameBar_Diff_SideGroupMap.clear();
	m_vecFrameBar_FreqDoub_ActiveParentMatrix.clear();
	m_vecFrameBar_FreqDoub_ActiveChildMatrix.clear();

	m_vecFrameBar_UnderTIQ = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_WndSpecNoise = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_EffectiveOscillation = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_Noise = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_Constrain = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_EffectPt = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_FreqDoub_ActiveParentMatrix	= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_FreqDoub_ActiveChildMatrix	= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);


	m_vecFrameBar_Diff_DisAppearGroup		= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_Diff_SuddenAppearGroup	= QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);

	int DiffGroupCount = DiffDataRef.DiffNetState.totalGroupCount;
	ResetDiffGroupColorMap(DiffGroupCount);
	int SideGroupCount = DiffDataRef.DiffNetState.mapDiffGroup.size();
	int startSideGroupIndex = (SideGroupCount - 1) / 2;

	QMap<int, QVector<ST_FFTFreqBar>> nullDiffFrameVec;

	for (int startIndex = startSideGroupIndex * -1; startIndex <= startSideGroupIndex; startIndex++)
	{
		nullDiffFrameVec.insert(startIndex, QVector<ST_FFTFreqBar>());
	}
	m_vecFrameBar_Diff_SideGroupMap = QVector<QMap<int, QVector<ST_FFTFreqBar>>>(frameCount, nullDiffFrameVec);

	int	 GeneratebarCount = 0;
	int		currentFFTPtIndex = ceil((double)m_nMinFreq / m_dFreqBarBandWidth);
	double	currentFFTPtCenterFreq = currentFFTPtIndex * m_dFreqBarBandWidth;
	while (currentFFTPtCenterFreq < m_nMaxFreq)
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
	nullData.dataKey = m_currentSTFTDataKey;
	nullData.pCht = this;
	nullData.frameIndex = -1;
	m_currentProcessVec.clear();
	m_currentProcessVec = QVector<ST_SecChtThreadProcessData>(frameCount, nullData);
	for (int index = 0; index < frameCount; index++)
	{
		m_currentProcessVec[index].frameIndex = index;
	}

	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, TimeSecCht_FreqDoub::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);

}

void TimeSecCht_FreqDoub::setSTFTResultPara(const ST_STFTInputpara& para)
{
	m_STFTPara = para;
	//AudioProtocol::duplicateSTFTData(data,m_drawData);

	//if (m_drawData.vecOutput.isEmpty())
	{
		return;
	}

}

QRect TimeSecCht_FreqDoub::getDrawAreaRect()
{
	QRect		thisRect = this->rect();
	QPoint		drawAreaStartPt = QPoint(m_nLeftAxisWidth, m_nTopTitleHeight);
	QPoint		drawAreaEndPt = QPoint(thisRect.width() - m_nRightColorMapRegionWidth, thisRect.height() - m_nBottomAxisHeight);
	QRect		drawAreaRect = QRect(drawAreaStartPt, drawAreaEndPt);
	return		drawAreaRect;
}

QRect TimeSecCht_FreqDoub::getBottomAxisRect()
{
	QRect  drawAreaRect = getDrawAreaRect();
	QRect  BottomAxisRect = QRect(drawAreaRect.bottomLeft(), QPoint(drawAreaRect.bottomRight().x(), this->rect().height()));
	return BottomAxisRect;
}

int   TimeSecCht_FreqDoub::FreqToPosX(double freq)
{
	QRect drawArea = getDrawAreaRect();
	double FreqRatio = (freq - (double)m_nMinFreq) / ((double)m_nMaxFreq - (double)m_nMinFreq);
	int FreqX = FreqRatio * drawArea.width() + drawArea.x();
	return FreqX;
}

int   TimeSecCht_FreqDoub::PosXToFreq(int posX)
{
	QRect drawArea = getDrawAreaRect();

	if (posX < drawArea.left() || posX > drawArea.right())
	{
		return -1;
	}

	double XRatio = ((double)posX - (double)drawArea.left()) / (double)drawArea.width();
	double TotalFreqWidth = m_nMaxFreq - m_nMinFreq;
	double resultFreq = XRatio * TotalFreqWidth + m_nMinFreq;
	return resultFreq;

}

int   TimeSecCht_FreqDoub::getDbHeight(const double valDb)
{
	QRect drawArea = getDrawAreaRect();
	double valRatio = (valDb - m_dMinDB) / (m_dMaxDB - m_dMinDB);

	if (valRatio < 0)
	{
		return 0;
	}
	else if (valRatio > 1)
	{
		return drawArea.height();
	}

	double ratioHeight = drawArea.height() * valRatio;
	return (int)ratioHeight;

}

double TimeSecCht_FreqDoub::PosYToDb(int posY)
{
	QRect drawArea = getDrawAreaRect();
	if (posY < drawArea.top() && posY > drawArea.bottom())
	{
		return 0;
	}

	int realtiveY = drawArea.bottom() - posY;
	double realtiveDb = ((double)realtiveY / (double)drawArea.height()) * (m_dMaxDB - m_dMinDB) + m_dMinDB;
	return realtiveDb;

}

int TimeSecCht_FreqDoub::MousePosToMFCCFilterRectIndex(QPoint mousePos)
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

QRect TimeSecCht_FreqDoub::getFreqBarRect(int startFreq, int bandWidth, double RectMaxVal)
{
	QRect nullRect = QRect(0, 0, 0, 0);
	QRect drawArea = getDrawAreaRect();
	if (startFreq < m_nMinFreq || startFreq + bandWidth > m_nMaxFreq)
	{
		return nullRect;
	}

	int startX = FreqToPosX(startFreq);
	int endX = FreqToPosX(startFreq + bandWidth);
	int startY = drawArea.bottom();
	int height = 0;
	height = getDbHeight(RectMaxVal);

	int endY = startY - height;

	QRect resultRect = QRect(QPoint(startX, startY), QPoint(endX, endY));
	return resultRect;

}


void TimeSecCht_FreqDoub::slot_GenFinished()
{
	emit sgn_SecRectGenerateState(100, 1, QString());
	m_currentProcessVec.clear();
	m_ndrawFrameIndex = 0;
	update();
}

void TimeSecCht_FreqDoub::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "TimeSecCht_Diff::slot_GenProgressValueChanged RectVec empty!";
		return;
	}

	int frameCount = m_currentProcessVec.size();
	int hunderdsOfFrame = qMax(1, frameCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastReportPercantage)
	{
		emit sgn_SecRectGenerateState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(frameCount));;
		m_nLastReportPercantage = percentage;
	}
	qDebug() << QString("slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(frameCount);
	if (percentage == 100)
	{
		slot_GenFinished();
	}
}

void TimeSecCht_FreqDoub::FillTargetFrame(const ST_SecChtThreadProcessData data)
{

	const QMap<QString, ST_STFTOutputData>& STFTMapRef = DataCenterManager::instance()->getSTFTOutputMap();
	auto mapPos = STFTMapRef.find(data.dataKey);
	if (mapPos == STFTMapRef.end())
	{
		qDebug() << "BDSNR_TimeSecCht::FillTargetFrame STFTMapPos end!";
		return;
	}

	const ST_STFTOutputData& dataRef = mapPos.value();

	if (data.frameIndex < 0 || data.frameIndex >= dataRef.vecOutput.size())
	{
		qDebug() << QString("BDSNR_TimeSecCht::FillTargetFrame FrameIndex outSize : %1!").arg(data.frameIndex);
		return;
	}

	const ST_FFTOutputData& frameData = dataRef.vecOutput[data.frameIndex];
	data.pCht->generateFreqBarVec(data.frameIndex, frameData);

}

bool  TimeSecCht_FreqDoub::generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& frameData)
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

	bool WndSpecConstrainDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, m_currentSTFTDataKey);

	if (!WndSpecConstrainDataExist)
	{
		return false;
	}

	const ST_WndSpecConstrainResult& WndSpecConstrainDataRef = DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(m_currentSTFTDataKey).value();
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

	bool BDSNRDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, m_currentSTFTDataKey);

	if (!BDSNRDataExist)
	{
		return false;
	}

	const ST_BandWidthSNRConstrainData& BDSNRResult = DataCenterManager::instance()->getBDSNROutputMap().find(m_currentSTFTDataKey).value();
	const ST_BandWidthSNRConstrainFrame& BDSNRFrame = BDSNRResult.FrameVec[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& BDSNR_Noise_FrameVecRef = m_vecFrameBar_BDSNR_Noise[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& BDSNR_Constrain_FrameVecRef = m_vecFrameBar_BDSNR_Constrain[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& BDSNR_Effect_FrameVecRef = m_vecFrameBar_BDSNR_EffectPt[STFTFrameIndex];

	for (int FFTFreqBarIndex = 0; FFTFreqBarIndex < barHeightVec.size(); FFTFreqBarIndex++)
	{
		const ST_FFTFreqBar& FreqBarRef = barHeightVec[FFTFreqBarIndex];
		const ST_BandWidthSNRPtTag& ptTag = BDSNRFrame.vecBDSNRptTag[FreqBarRef.FFTPtIndex];

		switch (ptTag.ptSNRConstrainType)
		{
		case EN_BDSNRPtType::WndSpecNoise:BDSNR_Noise_FrameVecRef.push_back(FreqBarRef); break;
		case EN_BDSNRPtType::BDSNR_ConstrainPt:BDSNR_Constrain_FrameVecRef.push_back(FreqBarRef); break;
		case EN_BDSNRPtType::BDSNR_EffectivePt:BDSNR_Effect_FrameVecRef.push_back(FreqBarRef); break;
		}
	}

	QVector<ST_BandWidthFilterActiveRect>& FilterActiveRectVecRef = m_vecDrawBandWidthFilterRect[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& ActiveFilterBarVecRef = m_vecFrameBar_BDSNR_ActiveFilter[STFTFrameIndex];

	for (int FilterActiveRectIndex = 0; FilterActiveRectIndex < FilterActiveRectVecRef.size(); FilterActiveRectIndex++)
	{
		ST_BandWidthFilterActiveRect& ActiveRectRef = FilterActiveRectVecRef[FilterActiveRectIndex];
		const ST_BandWidthFilterPt& FilterPt = BDSNRFrame.vecBDFilterValue[ActiveRectRef.FilterIndex];
		ActiveRectRef.isFilterActive = FilterPt.isActive;
	}

	QRect drawArea = getDrawAreaRect();

	for (int FilterBarIndex = 0; FilterBarIndex < ActiveFilterBarVecRef.size(); FilterBarIndex++)
	{
		ST_FFTFreqBar& FreqBarRef = ActiveFilterBarVecRef[FilterBarIndex];
		const ST_BandWidthFilterPt& FilterPt = BDSNRFrame.vecBDFilterValue[FreqBarRef.FilterIndex];
		if (!FilterPt.isActive)
		{
			FreqBarRef.BarRect.setHeight(0);
		}
		else
		{
			double MFCCVal = FilterPt.BandWidthFilterVal_SubArea;
			double MFCCDB = AudioProtocol::fftRealToDB(MFCCVal, const_audio_normalAudioFileMaxDB);
			int DBHeight = getDbHeight(MFCCDB);
			FreqBarRef.BarRect.setHeight(DBHeight);
		}
		FreqBarRef.BarRect.moveBottom(drawArea.bottom());
	}


	bool DiffDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::Diff, m_currentSTFTDataKey);

	if (!DiffDataExist)
	{
		return false;
	}

	const ST_DiffNetOutput& DiffResult = DataCenterManager::instance()->getDiffOutputMap().find(m_currentSTFTDataKey).value();
	const ST_DiffFrame& DiffFrame = DiffResult.FrameVec[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& Diff_DisAppearGroupVecRef = m_vecFrameBar_Diff_DisAppearGroup[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& Diff_SuddenAppearGroupVecRef = m_vecFrameBar_Diff_SuddenAppearGroup[STFTFrameIndex];

	QMap<int, QVector<ST_FFTFreqBar>>& Diff_SideGroupVecRef = m_vecFrameBar_Diff_SideGroupMap[STFTFrameIndex];

	int FFTBarCount = barHeightVec.size();

	for (int ptIndex = 0; ptIndex < FFTBarCount; ptIndex++)
	{
		const ST_FFTFreqBar& FreqBarRef = barHeightVec[ptIndex];
		const ST_DiffNetPoint& DiffptTag = DiffFrame.vecFFTPoint[FreqBarRef.FFTPtIndex];
		if (DiffptTag.isSuddenAppear)
		{
			Diff_SuddenAppearGroupVecRef.push_back(FreqBarRef);
		}
		else if (DiffptTag.isDisappear)
		{
			Diff_DisAppearGroupVecRef.push_back(FreqBarRef);
		}
		else
		{
			if (DiffptTag.getAGroup)
			{
				Diff_SideGroupVecRef.find(DiffptTag.BidirectGroupIndex).value().push_back(FreqBarRef);
			}
		}

	}

	bool FreqDoubDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::FreqDoub, m_currentSTFTDataKey);

	if (!FreqDoubDataExist)
	{
		return false;
	}

	const ST_FreqDoubleNetworkOutput&	FreqDoubResult = DataCenterManager::instance()->getFreqDoubeOutputMap().find(m_currentSTFTDataKey).value();
	const ST_FreqDoubleNetworkFrame&	FreqDoubFrame = FreqDoubResult.FrameVec[STFTFrameIndex];

	QVector<ST_FFTFreqBar>& FreqDoub_ActiveParentVecRef = m_vecFrameBar_FreqDoub_ActiveParentMatrix[STFTFrameIndex];
	QVector<ST_FFTFreqBar>& FreqDoub_ActvieChildVecRef	= m_vecFrameBar_FreqDoub_ActiveChildMatrix[STFTFrameIndex];

	for (int MatrixIndex = 0; MatrixIndex < FreqDoubFrame.VecParentPt.size(); MatrixIndex++)
	{
		const ST_FreqMultipleMaxtrix&			matrixRef	= FreqDoubResult.Tensor.VecMultipleMatrix[MatrixIndex];
		const ST_FreqMultipleNetworkParentPt&	parentPtRef = FreqDoubFrame.VecParentPt[MatrixIndex];
		bool BarExist = parentPtRef.isActive || parentPtRef.HasParent;

		if (!BarExist)
		{
			continue;
		}

		double BarAmp = 0;
		if (!parentPtRef.isInsertFreq)
		{
			BarAmp =  FFTPtVecRef[matrixRef.BaseFreqIndex_int].amplitude;
		}
		else
		{
			double LeftAmp = FFTPtVecRef[floor(matrixRef.BaseFreqIndex_double)].amplitude;
			double RightAmp = FFTPtVecRef[ceil(matrixRef.BaseFreqIndex_double)].amplitude;
			BarAmp = (LeftAmp + RightAmp) / 2;
		}

		ST_FFTFreqBar newBar;
		newBar.centerFreq = matrixRef.BaseFreq;
		newBar.DBVal = AudioProtocol::fftRealToDB(BarAmp, const_audio_normalAudioFileMaxDB);
		newBar.matrixIndex = MatrixIndex;
		int						newHeight = getDbHeight(newBar.DBVal);
		double					startFreq = newBar.centerFreq - m_dFreqBarBandWidth / 2;
		newBar.BarRect = getFreqBarRect(startFreq, m_dFreqBarBandWidth, newBar.DBVal);

		if (parentPtRef.HasParent)
		{
			FreqDoub_ActvieChildVecRef.push_back(newBar);
		}
		else
		{
			FreqDoub_ActiveParentVecRef.push_back(newBar);
		}

	}

	return true;

}

void TimeSecCht_FreqDoub::leaveEvent(QEvent* event)
{
	m_bMouseInDrawArea = false;
	m_ptMousePos = QPoint(-1, -1);
	m_bMouseInFilterActiveArea = false;
	m_ptMousePos_ActiveMFCCRect = QPoint(-1, -1);
	update();
}

void TimeSecCht_FreqDoub::hideEvent(QHideEvent* event)
{
	qDebug() << "FFT_Chart_STFTTimeSection::hideEvent";
	emit sgn_windowHide();
}

void TimeSecCht_FreqDoub::mouseMoveEvent(QMouseEvent* event)
{
	QPoint mousePos = event->pos();
	QRect  DrawArea = getDrawAreaRect();

	if (DrawArea.contains(mousePos))
	{
		m_bMouseInDrawArea = true;
		m_ptMousePos = mousePos;
	}
	else
	{
		m_bMouseInDrawArea = false;
		m_ptMousePos = QPoint(-1, -1);
	}

	if (m_showDataType == EN_FreqDoub_TimeSecChtBarType::BDSNR)
	{
		QRect BottomAxisRect = getBottomAxisRect();
		if (BottomAxisRect.contains(mousePos))
		{
			m_bMouseInFilterActiveArea = true;
			m_ptMousePos_ActiveMFCCRect = mousePos;
		}
		else
		{
			m_bMouseInFilterActiveArea = false;
			m_ptMousePos_ActiveMFCCRect = QPoint(-1, -1);
		}
	}
	else
	{
		m_bMouseInFilterActiveArea = false;
		m_ptMousePos_ActiveMFCCRect = QPoint(-1, -1);
	}

	update();

}

void TimeSecCht_FreqDoub::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QRect thisRect = this->rect();

	QRect	drawAreaRect = getDrawAreaRect();

	QRect LeftAxisRect = QRect(QPoint(0, m_nTopTitleHeight), drawAreaRect.bottomLeft());
	QRect TopAxisRect = QRect(QPoint(m_nLeftAxisWidth, 0), drawAreaRect.topRight());
	QRect BottomAxisRect = getBottomAxisRect();
	QRect RightColorMapRect = QRect(QPoint(drawAreaRect.topRight().x(), m_nTopTitleHeight), QPoint(thisRect.right(), thisRect.height() - m_nBottomAxisHeight));

	drawTitle(painter, TopAxisRect);
	drawValueAxis(painter, LeftAxisRect, false);

	switch (m_showDataType)
	{
	case EN_FreqDoub_TimeSecChtBarType::STFT:drawValueArea_STFT(painter, drawAreaRect); break;
	case EN_FreqDoub_TimeSecChtBarType::EffectiveOscillation:drawValueArea_EffectiveOsc(painter, drawAreaRect); break;
	case EN_FreqDoub_TimeSecChtBarType::BDSNR:drawValueArea_BDSNR(painter, drawAreaRect); break;
	case EN_FreqDoub_TimeSecChtBarType::DiffGroup:drawValueArea_Diff(painter, drawAreaRect); break;
	case EN_FreqDoub_TimeSecChtBarType::FreqDoub:drawValueArea_FreqDoub(painter, drawAreaRect); break;
	}

	if (m_showDataType == EN_FreqDoub_TimeSecChtBarType::BDSNR)
	{
		drawFilterActvateState(painter, BottomAxisRect);
	}

	if (m_bDrawTIQLine)
	{
		drawThreshHoldInQuiet(painter, drawAreaRect);
	}

	drawFreqAxis(painter, BottomAxisRect);

	if (m_bMouseInDrawArea)
	{
		drawMousePosValue(painter, drawAreaRect);
	}

	if (m_bMouseInFilterActiveArea)
	{
		drawActiveRectValue(painter);
	}


	drawLengend(painter, RightColorMapRect);
	drawPtCount(painter, RightColorMapRect);
}

void TimeSecCht_FreqDoub::drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect)
{
	QRect thisRect = this->rect();
	painter.setBrush(Qt::NoBrush);

	QPen AreaPen;
	AreaPen.setWidth(2);

	AreaPen.setColor(Qt::red);
	painter.setPen(AreaPen);
	painter.drawRect(thisRect);


	AreaPen.setColor(Qt::black);
	painter.setPen(AreaPen);
	painter.drawRect(LeftAxisRect);
	painter.drawText(LeftAxisRect, Qt::AlignCenter, QString("L"));

	AreaPen.setColor(Qt::green);
	painter.setPen(AreaPen);
	painter.drawRect(TopAxisRect);
	painter.drawText(TopAxisRect, Qt::AlignCenter, QString("T"));

	AreaPen.setColor(Qt::blue);
	painter.setPen(AreaPen);
	painter.drawRect(BottomAxisRect);
	painter.drawText(BottomAxisRect, Qt::AlignCenter, QString("B"));


	AreaPen.setColor(Qt::magenta);
	painter.setPen(AreaPen);
	painter.drawRect(RightColorMapRect);
	painter.drawText(RightColorMapRect, Qt::AlignCenter, QString("R"));
}

void TimeSecCht_FreqDoub::drawTitle(QPainter& painter, QRect& TopAxisRect)
{
	painter.setBrush(Qt::NoBrush);
	painter.setFont(m_ft_titleFont);

	QPen TitlePen;
	TitlePen.setWidth(2);
	TitlePen.setColor(m_crTitle);
	painter.setPen(TitlePen);

	painter.drawText(TopAxisRect, Qt::AlignCenter, m_strTitle);
}


void TimeSecCht_FreqDoub::drawValueAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis)
{
	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(m_crAxis);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("黑体");
	painter.setFont(valStrFt);

	QPoint intervalStartPt = LeftAxisArea.bottomRight() - QPoint(1, -1);
	double    startVal = 0;
	double    maxFVal = 0;
	startVal = m_dMinDB;
	maxFVal = m_dMaxDB;


	int    totalScaleCount = m_nDBScaleIntervalCount + 1;
	double scaleInterval = (double)LeftAxisArea.height() / (double)(totalScaleCount - 1);
	double ValInterval = (maxFVal - startVal) / (totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString valStr;

		valStr = QString::number(startVal + ValInterval * scaleIndex) + QString("db");


		QPoint scaleStartPt = QPoint(intervalStartPt.x(), intervalStartPt.y() - scaleInterval * scaleIndex);
		QPoint scaleEndPt = scaleStartPt - QPoint(m_nAxiesScaleLength, 0);

		painter.setPen(AxisPen);
		painter.drawLine(scaleStartPt, scaleEndPt);

		QRectF boundingRect = painter.boundingRect(LeftAxisArea, valStr);
		boundingRect.moveCenter(QPointF(0, scaleStartPt.y()));
		boundingRect.moveRight(scaleEndPt.x() - m_nAxiesValStrMargin);

		painter.drawText(boundingRect, Qt::AlignCenter, valStr);

	}
}

void TimeSecCht_FreqDoub::drawFreqAxis(QPainter& painter, QRect& BottomAxisArea)
{
	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(m_crAxis);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("黑体");
	painter.setFont(valStrFt);

	QPoint intervalStartPt = BottomAxisArea.topLeft() + QPoint(0, 1);
	int    startFreq = m_nMinFreq;
	int    EndFreq = m_nMaxFreq;
	int    totalScaleCount = m_nFreqScaleIntervalCount + 1;
	double scaleInterval = (double)BottomAxisArea.width() / (double)(totalScaleCount - 1);
	double FreqInterval = (double)(EndFreq - startFreq) / (double)(totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString FreqStr = QString::number(startFreq + FreqInterval * scaleIndex) + QString("hz");
		QPoint scaleStartPt = QPoint(intervalStartPt.x() + scaleInterval * scaleIndex, intervalStartPt.y());
		QPoint scaleEndPt = scaleStartPt + QPoint(0, m_nAxiesScaleLength);

		painter.setPen(AxisPen);
		painter.drawLine(scaleStartPt, scaleEndPt);

		QRectF boundingRect = painter.boundingRect(BottomAxisArea, FreqStr);
		boundingRect.moveCenter(QPointF(scaleStartPt.x(), 0));
		boundingRect.moveTop(scaleEndPt.y() + m_nAxiesValStrMargin);

		painter.drawText(boundingRect, Qt::AlignCenter, FreqStr);
	}
}

void TimeSecCht_FreqDoub::drawThreshHoldInQuiet(QPainter& painter, QRect& drawArea)
{
	int startY = drawArea.bottom();

	int    X1 = FreqToPosX(0);
	double DBY1 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(0));

	int    X2 = FreqToPosX(200);
	double DBY2 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(200));

	int    X3 = FreqToPosX(500);
	double DBY3 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(500));

	int    X4 = FreqToPosX(10000);
	double DBY4 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(10000));

	int    X5 = FreqToPosX(18000);
	double DBY5 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(18000));

	int    X6 = FreqToPosX(20000);
	double DBY6 = startY - getDbHeight(AudioProtocol::getHearingThreshHoldInQuietDB(20000));

	QPen ThreshHoldPen;
	ThreshHoldPen.setWidth(2);
	ThreshHoldPen.setStyle(Qt::DashLine);
	ThreshHoldPen.setColor(m_crThreshHoldLine);
	painter.setPen(ThreshHoldPen);

	QRect clipRect = drawArea;
	clipRect.setWidth(drawArea.width() - 4);
	clipRect.setHeight(drawArea.height() - 4);
	clipRect.moveCenter(drawArea.center());
	painter.setClipRect(clipRect);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawLine(X1, DBY1, X2, DBY2);
	painter.drawLine(X2, DBY2, X3, DBY3);
	painter.drawLine(X3, DBY3, X4, DBY4);
	painter.drawLine(X4, DBY4, X5, DBY5);
	painter.drawLine(X5, DBY5, X6, DBY6);

	painter.setClipRect(clipRect, Qt::NoClip);
	painter.setRenderHint(QPainter::Antialiasing, false);
}

void TimeSecCht_FreqDoub::drawValueArea_STFT(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(drawArea);

	if (m_vecFrameBar_STFT.isEmpty())
	{
		return;
	}
	if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= m_vecFrameBar_STFT.size())
	{
		return;
	}

	const QVector<ST_FFTFreqBar>& resultVec = m_vecFrameBar_STFT[m_ndrawFrameIndex];

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);

	painter.setPen(RectPen);
	painter.setBrush(m_crSTFTOnlyBar);

	for (int barIndex = 0; barIndex < resultVec.size(); barIndex++)
	{
		const QRect& drawRect = resultVec[barIndex].BarRect;
		painter.drawRect(drawRect);
	}


}
void TimeSecCht_FreqDoub::drawValueArea_EffectiveOsc(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(drawArea);

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	if (m_bDrawUnderTIQBar)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_UnderTIQ.size())
		{
			const QVector<ST_FFTFreqBar>& UnderTIQBarVec = m_vecFrameBar_UnderTIQ[m_ndrawFrameIndex];
			painter.setBrush(m_cr_EffOsc_UnderTIQBar);

			for (int barIndex = 0; barIndex < UnderTIQBarVec.size(); barIndex++)
			{
				const QRect& drawRect = UnderTIQBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_bDrawWndSpecNoise)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_WndSpecNoise.size())
		{
			const QVector<ST_FFTFreqBar>& WndSpecNoiseBarVec = m_vecFrameBar_WndSpecNoise[m_ndrawFrameIndex];
			painter.setBrush(m_cr_EffOsc_WndSpecNoiseBar);

			for (int barIndex = 0; barIndex < WndSpecNoiseBarVec.size(); barIndex++)
			{
				const QRect& drawRect = WndSpecNoiseBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_EffectiveOscillation.size())
	{
		const QVector<ST_FFTFreqBar>& EffectiveOscillationBarVec = m_vecFrameBar_EffectiveOscillation[m_ndrawFrameIndex];
		painter.setBrush(m_cr_EffOsc_EffectiveOscillationBar);

		for (int barIndex = 0; barIndex < EffectiveOscillationBarVec.size(); barIndex++)
		{
			const QRect& drawRect = EffectiveOscillationBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}
}

void TimeSecCht_FreqDoub::drawValueArea_BDSNR(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(drawArea);

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	if (m_bDraw_BDSNR_Noise)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_Noise.size())
		{
			const QVector<ST_FFTFreqBar>& BDSNR_NoiseBarVec = m_vecFrameBar_BDSNR_Noise[m_ndrawFrameIndex];
			painter.setBrush(m_cr_BDSNR_Noise);

			for (int barIndex = 0; barIndex < BDSNR_NoiseBarVec.size(); barIndex++)
			{
				const QRect& drawRect = BDSNR_NoiseBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_EffectPt.size())
	{
		const QVector<ST_FFTFreqBar>& BDSNR_EffectPtBarVec = m_vecFrameBar_BDSNR_EffectPt[m_ndrawFrameIndex];
		painter.setBrush(m_cr_BDSNR_Signal_Effective);

		for (int barIndex = 0; barIndex < BDSNR_EffectPtBarVec.size(); barIndex++)
		{
			const QRect& drawRect = BDSNR_EffectPtBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}

	if (m_bDraw_BDSNR_ConstrainPt)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_Constrain.size())
		{
			const QVector<ST_FFTFreqBar>& BDSNR_ConstrainBarVec = m_vecFrameBar_BDSNR_Constrain[m_ndrawFrameIndex];
			painter.setBrush(m_cr_BDSNR_Signal_Constrain);
			for (int barIndex = 0; barIndex < BDSNR_ConstrainBarVec.size(); barIndex++)
			{
				const QRect& drawRect = BDSNR_ConstrainBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_bDraw_BDSNR_ActiveFilter)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter.size())
		{
			const QVector<ST_FFTFreqBar>& NDSNR_ActiveFilterBarVec = m_vecFrameBar_BDSNR_ActiveFilter[m_ndrawFrameIndex];
			painter.setBrush(m_cr_BDSNR_ConstrainFilter_Active);

			for (int barIndex = 0; barIndex < NDSNR_ActiveFilterBarVec.size(); barIndex++)
			{
				const QRect& drawRect = NDSNR_ActiveFilterBarVec[barIndex].BarRect;
				if (drawRect.height() > 0)
				{
					painter.drawRect(drawRect);
				}

			}
		}
	}
}

void TimeSecCht_FreqDoub::drawValueArea_Diff(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(drawArea);

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	if (m_bDraw_Diff_Disappear)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_Diff_DisAppearGroup.size())
		{
			const QVector<ST_FFTFreqBar>& Diff_DisAppearBarVec = m_vecFrameBar_Diff_DisAppearGroup[m_ndrawFrameIndex];
			painter.setBrush(m_cr_Diff_DisappearGroup);

			for (int barIndex = 0; barIndex < Diff_DisAppearBarVec.size(); barIndex++)
			{
				const QRect& drawRect = Diff_DisAppearBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_Diff_SuddenAppearGroup.size())
	{
		const QVector<ST_FFTFreqBar>& SuddenAppearPtBarVec = m_vecFrameBar_Diff_SuddenAppearGroup[m_ndrawFrameIndex];
		painter.setBrush(m_cr_Diff_SuddenAppearGroup);

		for (int barIndex = 0; barIndex < SuddenAppearPtBarVec.size(); barIndex++)
		{
			const QRect& drawRect = SuddenAppearPtBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}

	if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_Diff_SideGroupMap.size())
	{
		QMap<int, QVector<ST_FFTFreqBar>>& SideGroupMap = m_vecFrameBar_Diff_SideGroupMap[m_ndrawFrameIndex];

		for (auto MapPos = SideGroupMap.cbegin(); MapPos != SideGroupMap.cend(); MapPos++)
		{
			int GroupIndex = MapPos.key();
			QColor GroupCr = m_mapSideGroupColor.find(GroupIndex).value();
			painter.setBrush(GroupCr);
			const QVector<ST_FFTFreqBar>& GroupVec = MapPos.value();
			for (int barIndex = 0; barIndex < GroupVec.size(); barIndex++)
			{
				const QRect& drawRect = GroupVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

}

void TimeSecCht_FreqDoub::drawValueArea_FreqDoub(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(drawArea);

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);

	if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_FreqDoub_ActiveParentMatrix.size())
	{
		const QVector<ST_FFTFreqBar>& ParentBarVec = m_vecFrameBar_FreqDoub_ActiveParentMatrix[m_ndrawFrameIndex];
		painter.setBrush(m_cr_FreqDoub_ParentMatrix);

		for (int barIndex = 0; barIndex < ParentBarVec.size(); barIndex++)
		{
			const QRect& drawRect = ParentBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}

	if (m_bDraw_FreqDoub_Child)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_FreqDoub_ActiveChildMatrix.size())
		{
			const QVector<ST_FFTFreqBar>& ChildBarVec = m_vecFrameBar_FreqDoub_ActiveChildMatrix[m_ndrawFrameIndex];
			painter.setBrush(m_cr_FreqDoub_ChildMatrix);

			for (int barIndex = 0; barIndex < ChildBarVec.size(); barIndex++)
			{
				const QRect& drawRect = ChildBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

}

void TimeSecCht_FreqDoub::drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea)
{
	if (m_vecDrawBandWidthFilterRect.isEmpty())
	{
		return;
	}

	if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= m_vecDrawBandWidthFilterRect.size())
	{
		return;
	}

	painter.setPen(Qt::white);
	const QVector<ST_BandWidthFilterActiveRect>& FrameVec = m_vecDrawBandWidthFilterRect[m_ndrawFrameIndex];

	for (int FilterRectIndex = 0; FilterRectIndex < FrameVec.size(); FilterRectIndex++)
	{
		const ST_BandWidthFilterActiveRect& FilterRectRef = FrameVec[FilterRectIndex];
		if (FilterRectRef.isFilterActive)
		{
			painter.setBrush(m_cr_BDSNR_ConstrainFilter_Active);
		}
		else
		{
			painter.setBrush(m_cr_BDSNR_ConstrainFilter_InActive);
		}
		painter.drawRect(FilterRectRef.FilterPosRect);
	}
}

void TimeSecCht_FreqDoub::drawMousePosValue(QPainter& painter, QRect& drawArea)
{
	QPen linePen;
	linePen.setWidth(2);
	linePen.setColor(Qt::blue);

	int FreqX = m_ptMousePos.x();
	int FreqStartY = drawArea.bottom();
	int FreqEndY = drawArea.top();

	int ValY = m_ptMousePos.y();
	int ValStartX = drawArea.left();
	int ValEndY = drawArea.right();

	painter.setPen(linePen);
	painter.drawLine(QPoint(FreqX, FreqStartY), QPoint(FreqX, FreqEndY));
	painter.drawLine(QPoint(ValStartX, ValY), QPoint(ValEndY, ValY));

	QSize valRectSize(80, 20);

	QRect ValRect;
	ValRect.setSize(valRectSize);
	ValRect.moveCenter(QPoint(drawArea.left() - valRectSize.width() / 2, m_ptMousePos.y()));

	QRect FreqRect;
	FreqRect.setSize(valRectSize);
	FreqRect.moveCenter(QPoint(FreqX, drawArea.bottom() + valRectSize.height() / 2));

	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);
	painter.setBrush(Qt::white);

	painter.drawRect(ValRect);
	painter.drawRect(FreqRect);

	int FreqVal = PosXToFreq(m_ptMousePos.x());
	painter.drawText(FreqRect, Qt::AlignCenter, QString::number(FreqVal) + "hz");
	double DbVal = PosYToDb(m_ptMousePos.y());
	painter.drawText(ValRect, Qt::AlignCenter, QString::number(DbVal, 'f', 1) + "db");

	if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= m_vecFrameBar_STFT.size())
	{
		return;
	}

	const QVector<ST_FFTFreqBar>& freamVecRef = m_vecFrameBar_STFT[m_ndrawFrameIndex];

	int BarIndex = (double)(FreqVal - m_nMinFreq) / m_dFreqBarBandWidth;
	if (BarIndex < 0 || BarIndex >= freamVecRef.size())
	{
		return;
	}

	const ST_FFTFreqBar& BarRef = freamVecRef[BarIndex];

	double frameMsec = m_STFTPara.GapInTimeLength * 1000 * m_ndrawFrameIndex;
	QTime frameTime = QTime(0, 0, 0).addMSecs(frameMsec);

	QString IndexStr = QString("[Frame][Freq] : [%1][%2] \n").arg(m_ndrawFrameIndex).arg(BarRef.FFTPtIndex);
	QString PosValStr = QString("CenterFreq   : %1 hz	time : %2 \n").arg(BarRef.centerFreq, 0, 'f', 1).arg(frameTime.toString("mm:ss.zzz"));

	QString doubleValStr = QString("val : %1 \n").arg(BarRef.doubleVal, 0, 'f', 8);
	QString dbStr = QString("DB : %1 \n").arg(BarRef.DBVal, 0, 'f', 2);

	QSize valStrRectSize;
	QString showStr;

	showStr = IndexStr + PosValStr + doubleValStr + dbStr;

	switch (m_showDataType)
	{
	case EN_FreqDoub_TimeSecChtBarType::STFT:
	{
		valStrRectSize = QSize(300, 70);
	}break;
	case EN_FreqDoub_TimeSecChtBarType::EffectiveOscillation:
	{

		bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, m_currentSTFTDataKey);
		if (!checkDataExist)
		{
			return;
		}
		int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::WndSpecConstrain, m_currentSTFTDataKey);

		if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= frameCount)
		{
			return;
		}

		const ST_WndSpecConstrainFrame& FrameRef = DataCenterManager::instance()->getWndSpecConstrainOutputMap().find(m_currentSTFTDataKey).value().FrameVec[m_ndrawFrameIndex];
		if (BarRef.FFTPtIndex < 0 || BarRef.FFTPtIndex >= FrameRef.VecSTFTPtState.size())
		{
			return;
		}
		valStrRectSize = QSize(300, 150);
		const ST_WndSpecConstrainPtTag& ptTag = FrameRef.VecSTFTPtState[BarRef.FFTPtIndex];

		QString ConstrainSourceIndexStr = QString("ConstrainSourceIndex	: %1 \n").arg(ptTag.ConstrainSourceIndex);
		QString ConstrainSourceFreqStr = QString("ConstrainSourceFreq	: %1 \n").arg(ptTag.ConstrainSourceFreq, 0, 'f', 2);
		QString MaxConstrainValStr = QString("ConstrainVal			: %1 \n").arg(ptTag.MaxConstrainVal_Compare, 0, 'f', 8);
		QString MaxConstrainDBStr = QString("ConstrainDB			: %1 \n").arg(ptTag.MaxConstrainDB_Compare, 0, 'f', 2);
		QString ptStateStr = QString("ptState				: %1 \n").arg(WndSpecConstrainNetwork::instance()->getWndConstrainStateStr(ptTag.ptConstrainState));

		showStr += ConstrainSourceIndexStr + ConstrainSourceFreqStr + MaxConstrainValStr + MaxConstrainDBStr + ptStateStr;

	}break;
	case EN_FreqDoub_TimeSecChtBarType::BDSNR:
	{

		bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, m_currentSTFTDataKey);
		if (!checkDataExist)
		{
			return;
		}
		int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::BDSNR, m_currentSTFTDataKey);

		if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= frameCount)
		{
			return;
		}

		const ST_BandWidthSNRConstrainFrame& FrameRef = DataCenterManager::instance()->getBDSNROutputMap().find(m_currentSTFTDataKey).value().FrameVec[m_ndrawFrameIndex];
		if (BarRef.FFTPtIndex < 0 || BarRef.FFTPtIndex >= FrameRef.vecBDSNRptTag.size())
		{
			return;
		}
		valStrRectSize = QSize(300, 150);
		const ST_BandWidthSNRPtTag& ptTag = FrameRef.vecBDSNRptTag[BarRef.FFTPtIndex];

		QString ptStateStr = QString("ptState				: %1 \n").arg(BandWidthFilterManager::instance()->ConstrainPtTypeToStr(ptTag.ptSNRConstrainType));
		QString MaskedByFilterIndexStr = QString("MaskedByFilterIndex	: %1 \n").arg(ptTag.MaskedByFilterIndex);
		QString MaskAvrAmpStr = QString("MaskAmp				: %1 \n").arg(ptTag.MaskAmp_Sub, 0, 'f', 8);
		//QString MaskSigmaStr			= QString("MaskSigma			: %1 \n").arg(ptTag.MaskSigma, 0, 'f', 8);

		showStr += ptStateStr + MaskedByFilterIndexStr + MaskAvrAmpStr;

	}break;
	case EN_FreqDoub_TimeSecChtBarType::DiffGroup:
	{

		bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::Diff, m_currentSTFTDataKey);
		if (!checkDataExist)
		{
			return;
		}
		int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::Diff, m_currentSTFTDataKey);

		if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= frameCount)
		{
			return;
		}

		const ST_DiffFrame& FrameRef = DataCenterManager::instance()->getDiffOutputMap().find(m_currentSTFTDataKey).value().FrameVec[m_ndrawFrameIndex];
		if (BarRef.FFTPtIndex < 0 || BarRef.FFTPtIndex >= FrameRef.vecFFTPoint.size())
		{
			return;
		}
		valStrRectSize = QSize(300, 170);
		const ST_DiffNetPoint& ptTag = FrameRef.vecFFTPoint[BarRef.FFTPtIndex];

		QString isDisappearStr = QString("isDisappear			: %1 \n").arg(AudioProtocol::boolToStr(ptTag.isDisappear));
		QString isSuddenAppearStr = QString("isSuddenAppear		: %1 \n").arg(AudioProtocol::boolToStr(ptTag.isSuddenAppear));
		QString absDiffvalStr = QString("absDiffval			: %1 \n").arg(ptTag.Diffval, 0, 'f', 8);
		QString DiffRatioStr = QString("DiffRatio			: %1 \n").arg(ptTag.DiffRatio * 100, 0, 'f', 2);
		QString GroupIndexStr = QString("BidirectGroupIndex	: %1 \n").arg(ptTag.BidirectGroupIndex);
		QString getAGroupStr = QString("getAGroup			: %1 \n").arg(AudioProtocol::boolToStr(ptTag.getAGroup));

		showStr += isDisappearStr + isSuddenAppearStr + absDiffvalStr + DiffRatioStr + GroupIndexStr + getAGroupStr;

	}break;
	case EN_FreqDoub_TimeSecChtBarType::FreqDoub:
	{

		bool checkDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::FreqDoub, m_currentSTFTDataKey);
		if (!checkDataExist)
		{
			return;
		}
		int frameCount = DataCenterManager::instance()->getDaraFrameCount(EN_DataCenterAudioDataType::FreqDoub, m_currentSTFTDataKey);

		if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= frameCount)
		{
			return;
		}

		const ST_FreqDoubleNetworkOutput&	FDData			= DataCenterManager::instance()->getFreqDoubeOutputMap().find(m_currentSTFTDataKey).value();
		const ST_FreqMultipleTensor&		Tensor			= FDData.Tensor;
		const ST_FreqDoubleNetworkFrame&	FreqDoubFrame	= FDData.FrameVec[m_ndrawFrameIndex];
		const ST_DiffFrame&					DiffFrame		= DataCenterManager::instance()->getDiffOutputMap().find(m_currentSTFTDataKey).value().FrameVec[m_ndrawFrameIndex];
		int MatrixIndex = FreqDoubleNetwork::instance()->getMatrixIndex(FDData.Tensor, FreqVal);
		if (MatrixIndex < 0 || MatrixIndex >= FreqDoubFrame.VecParentPt.size())
		{
			return;
		}
		valStrRectSize = QSize(500, 170);
		const ST_FreqMultipleMaxtrix&			matrix	= Tensor.VecMultipleMatrix[MatrixIndex];
		const ST_FreqMultipleNetworkParentPt&	ptTag	= FreqDoubFrame.VecParentPt[MatrixIndex];

		QString activeStr		= QString("[active][hasParent]:[%1][%2] \n").arg(AudioProtocol::boolToStr(ptTag.isActive)).arg(AudioProtocol::boolToStr(ptTag.HasParent));
		QString matrixStr		= QString("[matrix][Freq][isInsert]: [%1][%2][%3] \n")
			.arg(MatrixIndex).arg(matrix.BaseFreq, 0, 'f', 2).arg(AudioProtocol::boolToStr(matrix.isInsertFreq));
		QString matrixDiffStr	= QString("[Sudden][DiffRatio][diffVal]: [%1][%2%][%3]  \n")
			.arg(AudioProtocol::boolToStr(ptTag.isDiffSuddenAppear)).arg(ptTag.DiffRatio * 100, 0, 'f', 2).arg(ptTag.DiffVal, 0, 'f', 8);

		showStr += activeStr + matrixStr + matrixDiffStr;
			
		if (ptTag.HasParent)
		{
			const int ParentMatrixIndex = ptTag.ParentMatrixIndex;
			const ST_FreqMultipleMaxtrix&			parentMatrix	= Tensor.VecMultipleMatrix[ParentMatrixIndex];
			const ST_FreqMultipleNetworkParentPt&	parenPtTag		= FreqDoubFrame.VecParentPt[ParentMatrixIndex];

			QString parentMatrixStr = QString("parent: [Index][Freq][isInsert]:[%1][%2][%3] \n")
				.arg(ParentMatrixIndex).arg(parentMatrix.BaseFreq, 0, 'f', 2).arg(AudioProtocol::boolToStr(parentMatrix.isInsertFreq));
			QString parentDiffStr	= QString("[Sudden][DiffRatio][diffVal]: [%1][%2%][%3] \n")
				.arg(AudioProtocol::boolToStr(parenPtTag.isDiffSuddenAppear)).arg(parenPtTag.DiffRatio * 100, 0, 'f', 2).arg(parenPtTag.DiffVal, 0, 'f', 8);
			showStr += parentMatrixStr + parentDiffStr;
		}
		else
		{
			QString subMatrixStr = QString("activeMultipleFreqCount : %1 \n").arg(ptTag.ActiveMultipleFreqCount);
			showStr += subMatrixStr;
		}		

	}break;
	}
	;
	QRect valStrRect;
	valStrRect.setSize(valStrRectSize);

	int RectStartX = m_ptMousePos.x();
	int RectStartY = m_ptMousePos.y();

	if (RectStartX + valStrRectSize.width() > drawArea.right())
	{
		RectStartX -= valStrRectSize.width();
	}

	if (RectStartY + valStrRectSize.height() > this->rect().bottom())
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

void TimeSecCht_FreqDoub::drawActiveRectValue(QPainter& painter)
{
	if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= m_vecDrawBandWidthFilterRect.size())
	{
		return;
	}

	const QVector<ST_BandWidthFilterActiveRect>& freamVecRef = m_vecDrawBandWidthFilterRect[m_ndrawFrameIndex];

	int FilterRectIndex = MousePosToMFCCFilterRectIndex(m_ptMousePos_ActiveMFCCRect);
	if (FilterRectIndex < 0 || FilterRectIndex >= freamVecRef.size())
	{
		return;
	}

	//const ST_BandWidthFilterActiveRect& MFCCActRect = freamVecRef[FilterRectIndex];

	//int		FilterIndex = MFCCActRect.FilterIndex;

	//const ST_BandWidthSNRConstrainData& BDSNRData = DataCenterManager::instance()->getBDSNROutputMap().find(m_currentSTFTDataKey).value();

	//const ST_BandWidthFilterPt& FilterPtRef = BDSNRData.FrameVec[m_ndrawFrameIndex].vecBDFilterValue[FilterIndex];
	//const ST_BandWidthFilter& FilterData = BDSNRData.FilterData.FilterVec[FilterIndex];

	//double frameMsec = m_STFTPara.GapInTimeLength * 1000 * m_ndrawFrameIndex;
	//QTime frameTime = QTime(0, 0, 0).addMSecs(frameMsec);


	//QString FrameStr = QString("Frame Index	: %1 time : %2 \n").arg(m_ndrawFrameIndex).arg(frameTime.toString("mm:ss.zzz"));
	//QString FreqStr = QString(" FilterIndex : %1 centerFreq : %2 bandwidth %3 \n").arg(MFCCActRect.FilterIndex).arg(FilterData.CenterFreq, 0, 'f', 1).arg(FilterData.Width);
	//QString ActiveStr = QString("isActive		: %1 \n").arg(AudioProtocol::boolToStr(FilterPtRef.isActive));

	//QString EffOscAvrValStr = QString("EffOscAvrOutputAmp		: %1 \n").arg(FilterPtRef.EffOscAvrOutputAmp, 0, 'f', 8);
	//QString EffOscAvrDBStr = QString("EffOscAvrOutputAmp DB	: %1 \n").arg(AudioProtocol::fftRealToDB(FilterPtRef.EffOscAvrOutputAmp, const_audio_normalAudioFileMaxDB), 0, 'f', 2);
	//QString EffOscWeiValStr = QString("EffOscWeightOutputAmp	: %1 \n").arg(FilterPtRef.EffOscWeightOutputAmp, 0, 'f', 8);
	//QString EffOscWeiDBStr = QString("EffOscWeightOutputAmp DB	: %1 \n").arg(AudioProtocol::fftRealToDB(FilterPtRef.EffOscWeightOutputAmp, const_audio_normalAudioFileMaxDB), 0, 'f', 2);

	//QString EffOscptCountStr = QString("EffOscPtCount			: %1 \n").arg(FilterPtRef.EffOscPtCount);
	//QString EffOscActRatioStr = QString("EffOscActRatio		: %1 \n").arg(FilterPtRef.EffOscPtRatio * 100, 0, 'f', 2);

	//QSize valStrRectSize = QSize(450, 150);
	//QString showStr;

	//showStr = FrameStr + FreqStr + ActiveStr + EffOscAvrValStr + EffOscAvrDBStr + EffOscWeiValStr + EffOscWeiDBStr
	//	+ EffOscptCountStr + EffOscActRatioStr;

	//QRect valStrRect;
	//valStrRect.setSize(valStrRectSize);

	//int RectStartX = m_ptMousePos_ActiveMFCCRect.x();
	//int RectStartY = m_ptMousePos_ActiveMFCCRect.y();

	//QRect bottomAxisRect = getBottomAxisRect();

	//if (RectStartX + valStrRectSize.width() > bottomAxisRect.right())
	//{
	//	RectStartX -= valStrRectSize.width();
	//}

	//if (RectStartY + valStrRectSize.height() > this->rect().bottom())
	//{
	//	RectStartY -= valStrRectSize.height();
	//}

	//valStrRect.moveTopLeft(QPoint(RectStartX, RectStartY));

	//QRect valBgRect;
	//valBgRect.setSize(valStrRectSize + QSize(3, 3));
	//valBgRect.moveCenter(valStrRect.center());

	//QPen RectPen;
	//RectPen.setWidth(2);
	//RectPen.setColor(Qt::black);

	//painter.setPen(RectPen);
	//painter.setBrush(Qt::white);
	//painter.drawRect(valBgRect);
	//painter.drawText(valStrRect, Qt::AlignLeft, showStr);
}

void TimeSecCht_FreqDoub::drawLengend(QPainter& painter, QRect& RightColorMapRect)
{
	int		LengendStrRectWidth = RightColorMapRect.width() - m_nLegendTextMargin - m_szLegend.width() - m_nLegendLeftMargin * 2;

	QPoint  LegendThreshHoldInQuietStartPt = RightColorMapRect.topLeft() + QPoint(m_nLegendLeftMargin, m_nLegendTopMargin);
	QPoint	LegendStrThreshHoldTopLeft = LegendThreshHoldInQuietStartPt + QPoint(20 + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QRect	LegendStrThreshHoldInQuiet = QRect(LegendStrThreshHoldTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));

	QPoint	LegendRectStartTopLeft = LegendThreshHoldInQuietStartPt + QPoint(0, m_szLegend.height() + m_nLegendSpacing);
	QRect   firstLegendRect(LegendRectStartTopLeft, m_szLegend);
	QRect   secondLegendRect(LegendRectStartTopLeft + QPoint(0, firstLegendRect.height() + m_nLegendSpacing), m_szLegend);
	QRect   ThirdLegendRect(secondLegendRect.topLeft() + QPoint(0, secondLegendRect.height() + m_nLegendSpacing), m_szLegend);
	QRect   ForthLegendRect(ThirdLegendRect.topLeft() + QPoint(0, ThirdLegendRect.height() + m_nLegendSpacing), m_szLegend);
	QRect   FifthLegendRect(ForthLegendRect.topLeft() + QPoint(0, ForthLegendRect.height() + m_nLegendSpacing), m_szLegend);


	QPoint	LegendStrFirstTopLeft = firstLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QPoint	LegendStrSecondTopLeft = secondLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QPoint	LegendStrThirdTopLeft = ThirdLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QPoint	LegendStrForthTopLeft = ForthLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QPoint	LegendStrFifthTopLeft = FifthLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);

	QRect	LegendStrFirstRect = QRect(LegendStrFirstTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	QRect	LegendStrSecondRect = QRect(LegendStrSecondTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	QRect	LegendStrThirdRect = QRect(LegendStrThirdTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	QRect	LegendStrForthRect = QRect(LegendStrForthTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	QRect	LegendStrFifthRect = QRect(LegendStrFifthTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));

	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	if (m_bDrawTIQLine)
	{
		QPen ThreshHoldPen;
		ThreshHoldPen.setWidth(2);
		ThreshHoldPen.setStyle(Qt::DashLine);
		ThreshHoldPen.setColor(m_crThreshHoldLine);
		painter.setPen(ThreshHoldPen);
		painter.drawLine(LegendThreshHoldInQuietStartPt + QPoint(0, m_szLegend.height() / 2), LegendThreshHoldInQuietStartPt + QPoint(20, m_szLegend.height() / 2));

		painter.setPen(NormalTextPen);
		QString ThreshholdInQuietLegendStr = QString("TIQ");
		painter.drawText(LegendStrThreshHoldInQuiet, Qt::AlignLeft | Qt::AlignVCenter, ThreshholdInQuietLegendStr);
	}

	painter.setPen(NormalTextPen);

	switch (m_showDataType)
	{
	case EN_FreqDoub_TimeSecChtBarType::STFT:
	{

		QString STFTLegendStr = QString("STFT Val");

		painter.setBrush(m_crSTFTOnlyBar);
		painter.drawRect(firstLegendRect);
		//painter.setFont(m_ft_LegendFont);

		painter.drawText(LegendStrFirstRect, Qt::AlignLeft | Qt::AlignVCenter, STFTLegendStr);
	}break;
	case EN_FreqDoub_TimeSecChtBarType::EffectiveOscillation:
	{
		QString UnderTIQLegendStr = QString("UnderTIQ");
		QString WndSpecNoiseLegendStr = QString("WndSpecNoise");
		QString EffectiveOscillationLegendStr = QString("effectOsc");

		painter.setBrush(m_cr_EffOsc_UnderTIQBar);
		painter.drawRect(firstLegendRect);

		painter.setBrush(m_cr_EffOsc_WndSpecNoiseBar);
		painter.drawRect(secondLegendRect);

		painter.setBrush(m_cr_EffOsc_EffectiveOscillationBar);
		painter.drawRect(ThirdLegendRect);

		//painter.setFont(m_ft_LegendFont);
		painter.drawText(LegendStrFirstRect, Qt::AlignLeft | Qt::AlignVCenter, UnderTIQLegendStr);
		painter.drawText(LegendStrSecondRect, Qt::AlignLeft | Qt::AlignVCenter, WndSpecNoiseLegendStr);
		painter.drawText(LegendStrThirdRect, Qt::AlignLeft | Qt::AlignVCenter, EffectiveOscillationLegendStr);
	}break;
	case EN_FreqDoub_TimeSecChtBarType::BDSNR:
	{
		QString NoiseLegendStr = QString("Noise");
		QString SolidOscLegendStr = QString("Sig_Constrain");
		QString FluidOscLegendStr = QString("Sig_Effective");
		QString InActMFCCLegendStr = QString("Filter_InActive");
		QString ActMFCCLegendStr = QString("Filter_Active");


		painter.setBrush(m_cr_BDSNR_Noise);
		painter.drawRect(firstLegendRect);

		painter.setBrush(m_cr_BDSNR_Signal_Constrain);
		painter.drawRect(secondLegendRect);

		painter.setBrush(m_cr_BDSNR_Signal_Effective);
		painter.drawRect(ThirdLegendRect);

		painter.setBrush(m_cr_BDSNR_ConstrainFilter_InActive);
		painter.drawRect(ForthLegendRect);

		painter.setBrush(m_cr_BDSNR_ConstrainFilter_Active);
		painter.drawRect(FifthLegendRect);

		//painter.setFont(m_ft_LegendFont);
		painter.drawText(LegendStrFirstRect, Qt::AlignLeft | Qt::AlignVCenter, NoiseLegendStr);
		painter.drawText(LegendStrSecondRect, Qt::AlignLeft | Qt::AlignVCenter, SolidOscLegendStr);
		painter.drawText(LegendStrThirdRect, Qt::AlignLeft | Qt::AlignVCenter, FluidOscLegendStr);
		painter.drawText(LegendStrForthRect, Qt::AlignLeft | Qt::AlignVCenter, InActMFCCLegendStr);
		painter.drawText(LegendStrFifthRect, Qt::AlignLeft | Qt::AlignVCenter, ActMFCCLegendStr);
	}break;
	case EN_FreqDoub_TimeSecChtBarType::DiffGroup:
	{
		QString DisappearLegendStr = QString("Disappear");
		QString SuddenAppearLegendStr = QString("Sudden Appear");
		QString DecreaseSideLegendStr = QString("DecreaseSide");
		QString StableSideStr = QString("Stable");
		QString increaseSideLegendStr = QString("increaseSide");

		painter.setBrush(m_cr_Diff_DisappearGroup);
		painter.drawRect(firstLegendRect);

		painter.setBrush(m_cr_Diff_SuddenAppearGroup);
		painter.drawRect(secondLegendRect);

		painter.setBrush(m_cr_Diff_DecreaseSideGroup);
		painter.drawRect(ThirdLegendRect);

		painter.setBrush(m_cr_Diff_StableGroup);
		painter.drawRect(ForthLegendRect);

		painter.setBrush(m_cr_Diff_IncreaseSideGroup);
		painter.drawRect(FifthLegendRect);

		//painter.setFont(m_ft_LegendFont);
		painter.drawText(LegendStrFirstRect, Qt::AlignLeft | Qt::AlignVCenter, DisappearLegendStr);
		painter.drawText(LegendStrSecondRect, Qt::AlignLeft | Qt::AlignVCenter, SuddenAppearLegendStr);
		painter.drawText(LegendStrThirdRect, Qt::AlignLeft | Qt::AlignVCenter, DecreaseSideLegendStr);
		painter.drawText(LegendStrForthRect, Qt::AlignLeft | Qt::AlignVCenter, StableSideStr);
		painter.drawText(LegendStrFifthRect, Qt::AlignLeft | Qt::AlignVCenter, increaseSideLegendStr);
	}break;
	case EN_FreqDoub_TimeSecChtBarType::FreqDoub:
	{
		QString ActiveParentLegendStr = QString("Act Parent");
		QString ActiveChildLegendStr	= QString("Act Child");

		painter.setBrush(m_cr_FreqDoub_ParentMatrix);
		painter.drawRect(firstLegendRect);

		painter.setBrush(m_cr_FreqDoub_ChildMatrix);
		painter.drawRect(secondLegendRect);


		//painter.setFont(m_ft_LegendFont);
		painter.drawText(LegendStrFirstRect, Qt::AlignLeft | Qt::AlignVCenter, ActiveParentLegendStr);
		painter.drawText(LegendStrSecondRect, Qt::AlignLeft | Qt::AlignVCenter, ActiveChildLegendStr);

	}break;
	}
}

void TimeSecCht_FreqDoub::drawPtCount(QPainter& painter, QRect& RightColorMapRect)
{
	int		LengendStrRectWidth = RightColorMapRect.width() - m_nLegendTextMargin - m_szLegend.width() - m_nLegendLeftMargin * 2;

	QPoint  LegendTotalPtCountStartPt = RightColorMapRect.bottomLeft() - QPoint(m_nLegendLeftMargin, m_nLegendTopMargin - m_szLegend.height());
	QPoint	LegendStrTotalPtCountTopLeft = LegendTotalPtCountStartPt + QPoint(20 + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QRect	LegendStrTotalPtCountRect = QRect(LegendStrTotalPtCountTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));

	//QPoint	LegendRectStartTopLeft = LegendThreshHoldInQuietStartPt + QPoint(0, m_szLegend.height() + m_nLegendSpacing);
	//QRect   firstLegendRect(LegendRectStartTopLeft, m_szLegend);
	//QRect   secondLegendRect(LegendRectStartTopLeft + QPoint(0, firstLegendRect.height() + m_nLegendSpacing), m_szLegend);
	//QRect   ThirdLegendRect(secondLegendRect.topLeft() + QPoint(0, secondLegendRect.height() + m_nLegendSpacing), m_szLegend);
	//QRect   ForthLegendRect(ThirdLegendRect.topLeft() + QPoint(0, ThirdLegendRect.height() + m_nLegendSpacing), m_szLegend);
	//QRect   FifthLegendRect(ForthLegendRect.topLeft() + QPoint(0, ForthLegendRect.height() + m_nLegendSpacing), m_szLegend);

	//QPoint	LegendStrFirstTopLeft = firstLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	//QPoint	LegendStrSecondTopLeft = secondLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	//QPoint	LegendStrThirdTopLeft = ThirdLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	//QPoint	LegendStrForthTopLeft = ForthLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	//QPoint	LegendStrFifthTopLeft = FifthLegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);

	//QRect	LegendStrFirstRect = QRect(LegendStrFirstTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	//QRect	LegendStrSecondRect = QRect(LegendStrSecondTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	//QRect	LegendStrThirdRect = QRect(LegendStrThirdTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	//QRect	LegendStrForthRect = QRect(LegendStrForthTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));
	//QRect	LegendStrFifthRect = QRect(LegendStrFifthTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));

	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	int totalPtCount = 0;

	switch (m_showDataType)
	{
	case EN_FreqDoub_TimeSecChtBarType::STFT:
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_STFT.size())
		{
			totalPtCount += m_vecFrameBar_STFT[m_ndrawFrameIndex].size();
		}

	}break;
	case EN_FreqDoub_TimeSecChtBarType::EffectiveOscillation:
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_STFT.size())
		{
			if (m_bDrawUnderTIQBar)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_UnderTIQ.size())
				{
					totalPtCount += m_vecFrameBar_UnderTIQ[m_ndrawFrameIndex].size();
				}
			}

			if (m_bDrawWndSpecNoise)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_WndSpecNoise.size())
				{
					totalPtCount += m_vecFrameBar_WndSpecNoise[m_ndrawFrameIndex].size();
				}
			}

			if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_EffectiveOscillation.size())
			{
				totalPtCount += m_vecFrameBar_EffectiveOscillation[m_ndrawFrameIndex].size();
			}
		}
	}break;
	case EN_FreqDoub_TimeSecChtBarType::BDSNR:
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_STFT.size())
		{
			if (m_bDraw_BDSNR_Noise)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_Noise.size())
				{
					totalPtCount += m_vecFrameBar_BDSNR_Noise[m_ndrawFrameIndex].size();
				}
			}

			if (m_bDraw_BDSNR_ConstrainPt)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_Constrain.size())
				{
					totalPtCount += m_vecFrameBar_BDSNR_Constrain[m_ndrawFrameIndex].size();
				}
			}

			if (m_bDraw_BDSNR_ActiveFilter)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter.size())
				{
					totalPtCount += m_vecFrameBar_BDSNR_ActiveFilter[m_ndrawFrameIndex].size();
				}
			}

			if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_EffectPt.size())
			{
				totalPtCount += m_vecFrameBar_BDSNR_EffectPt[m_ndrawFrameIndex].size();
			}
		}
	}break;
	}

	QString totalPtText = QString("Pt Count : %1").arg(totalPtCount);

	painter.drawText(LegendStrTotalPtCountRect, Qt::AlignLeft | Qt::AlignVCenter, totalPtText);


}