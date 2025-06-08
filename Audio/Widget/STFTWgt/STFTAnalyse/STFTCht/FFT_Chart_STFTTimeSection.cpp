#include "FFT_Chart_STFTTimeSection.h"

FFT_Chart_STFTTimeSection::FFT_Chart_STFTTimeSection(QWidget* parent) :QWidget(parent)
{
	init();
	setMouseTracking(true);
}

FFT_Chart_STFTTimeSection::~FFT_Chart_STFTTimeSection()
{

}

void FFT_Chart_STFTTimeSection::init()
{
	QFont titleFont;
	titleFont.setFamily("ºÚÌå");
	titleFont.setPixelSize(20);
	m_ft_titleFont = titleFont;

	m_pSTFTwatcher = new QFutureWatcher<void>(this);
	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished()));
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &FFT_Chart_STFTTimeSection::slot_GenProgressValueChanged);

}

void FFT_Chart_STFTTimeSection::setFreqBarBandWidth(int hzPerBar)
{
	m_nFreqBarBandWidth = hzPerBar;
}

void FFT_Chart_STFTTimeSection::setCurrentFrameIndex(int index)
{
	if (index <0 || index >= m_vecFrameBar.size())
	{
		qDebug() << "FFT_Chart_STFTTimeSection::setCurrentFrameIndex invalid Index : " << index;
		return;
	}

	//qDebug() << m_strTitle << QString("updateFrameIndex : %1").arg(index);	

	m_ndrawFrameIndex = index;
	update();
}

void FFT_Chart_STFTTimeSection::setDrawFreqRanged(int startFreq, int endFreq)
{
	m_nMinFreq = startFreq;
	m_nMaxFreq = endFreq;
	update();
}

void FFT_Chart_STFTTimeSection::setDrawDBRange(double min, double max)
{
	m_dMinDB = min;
	m_dMaxDB = max;
	update();
}

void FFT_Chart_STFTTimeSection::setChtType(EN_TimeSecType Type)
{
	m_showDataType = Type;
	if (Type == EN_TimeSecType::Amp)
	{
		m_strTitle = "STFT Time Section Amplitude";
	}
	else
	{
		m_strTitle = "STFT Time Section Phase";
	}
	update();
}

void FFT_Chart_STFTTimeSection::resetFrameRect(QString dataKey)
{
	const QMap<QString, ST_STFTOutputData>& STFTMapRef = DataCenterManager::instance()->getSTFTOutputMap();
	auto mapPos = STFTMapRef.find(dataKey);
	if (mapPos == STFTMapRef.end())
	{
		qDebug() << QString("FFT_Chart_STFTTimeSection::resetFrameRect STFTMapPos end! Key : %1").arg(dataKey);
		return;
	}

	const ST_STFTOutputData& dataRef = mapPos.value();
	int frameCount = dataRef.vecOutput.size();

	m_currentSTFTDataKey = dataKey;
	m_vecFrameBar.clear();
	ST_FreqBar nullBar;
	int GeneratebarCount = (m_nMaxFreq - m_nMinFreq) / m_nFreqBarBandWidth;
	QVector<ST_FreqBar> nullbarHeightVec = QVector<ST_FreqBar>(GeneratebarCount, nullBar);
	m_vecFrameBar = QVector<QVector<ST_FreqBar>>(frameCount, nullbarHeightVec);
	
	int hundredOfFrame = qMax(1, frameCount / 100);

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

	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, FFT_Chart_STFTTimeSection::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);

}

void FFT_Chart_STFTTimeSection::setSTFTResultPara(const ST_STFTInputpara& para)
{
	m_STFTPara = para;
	//AudioProtocol::duplicateSTFTData(data,m_drawData);

	//if (m_drawData.vecOutput.isEmpty())
	{
		return;
	}

}

QRect FFT_Chart_STFTTimeSection::getDrawAreaRect()
{
	QRect		thisRect = this->rect();
	QPoint		drawAreaStartPt = QPoint(m_nLeftAxisWidth, m_nTopTitleHeight);
	QPoint		drawAreaEndPt = QPoint(thisRect.width() - m_nRightColorMapRegionWidth, thisRect.height() - m_nBottomAxisWidth);
	QRect		drawAreaRect = QRect(drawAreaStartPt, drawAreaEndPt);
	return		drawAreaRect;
}

int   FFT_Chart_STFTTimeSection::FreqToPosX(double freq)
{
	QRect drawArea = getDrawAreaRect();
	double FreqRatio = (freq - (double)m_nMinFreq) / ((double)m_nMaxFreq - (double)m_nMinFreq);
	int FreqX = FreqRatio * drawArea.width() + drawArea.x();
	return FreqX;
}

int   FFT_Chart_STFTTimeSection::PosXToFreq(int posX)
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

int   FFT_Chart_STFTTimeSection::getDbHeight(const double valDb)
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

double FFT_Chart_STFTTimeSection::PosYToDb(int posY)
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

int    FFT_Chart_STFTTimeSection::getPhaseHeight(const double val)
{
	QRect drawArea = getDrawAreaRect();
	double valRatio = (val - m_dMinPhase) / (m_dMaxPhase - m_dMinPhase);

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

double FFT_Chart_STFTTimeSection::posYToPhase(int posY)
{
	QRect drawArea = getDrawAreaRect();
	if (posY < drawArea.top() && posY > drawArea.bottom())
	{
		return 0;
	}

	int realtiveY = drawArea.bottom() - posY;
	double realtiveDb = ((double)realtiveY / (double)drawArea.height()) * (m_dMaxPhase - m_dMinPhase) + m_dMinPhase;
	return realtiveDb;
}

QRect FFT_Chart_STFTTimeSection::getFreqBarRect(int startFreq, int bandWidth, double RectMaxVal)
{
	QRect nullRect = QRect(0,0,0,0);
	QRect drawArea = getDrawAreaRect();
	if (startFreq < m_nMinFreq || startFreq + bandWidth > m_nMaxFreq)
	{
		return nullRect;
	}

	int startX		= FreqToPosX(startFreq);
	int endX		= FreqToPosX(startFreq + bandWidth);
	int startY		= drawArea.bottom();
	int height = 0;
	if (m_showDataType == EN_TimeSecType::Amp)
	{
		height = getDbHeight(RectMaxVal);
	}
	else
	{
		height = getPhaseHeight(RectMaxVal);
	}
	
	int endY		= startY - height;

	QRect resultRect = QRect(QPoint(startX, startY), QPoint(endX, endY));
	return resultRect;

}

void FFT_Chart_STFTTimeSection::slot_GenFinished()
{
	emit sgn_SecRectGenerateState(100, 1, QString());
	m_currentProcessVec.clear();
	m_ndrawFrameIndex = 0;
	update();
}

void FFT_Chart_STFTTimeSection::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "FFT_Chart_STFTTimeSection::slot_GenProgressValueChanged RectVec empty!";
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

void FFT_Chart_STFTTimeSection::FillTargetFrame(const ST_SecChtThreadProcessData data)
{

	const QMap<QString, ST_STFTOutputData>& STFTMapRef = DataCenterManager::instance()->getSTFTOutputMap();
	auto mapPos = STFTMapRef.find(data.dataKey);
	if (mapPos == STFTMapRef.end())
	{
		qDebug() << "FFT_Chart_STFTTimeSection::FillTargetFrame STFTMapPos end!";
		return;
	}

	const ST_STFTOutputData& dataRef = mapPos.value();

	if (data.frameIndex < 0 || data.frameIndex >= dataRef.vecOutput.size())
	{
		qDebug() << QString("FFT_Chart_STFTTimeSection::FillTargetFrame FrameIndex outSize : %1!").arg(data.frameIndex);
		return;
	}

	const ST_FFTOutputData& frameData = dataRef.vecOutput[data.frameIndex];
	data.pCht->generateFreqBarVec(data.frameIndex, frameData);

}

bool  FFT_Chart_STFTTimeSection::generateFreqBarVec(const int BarVecIndex, const ST_FFTOutputData& frameData)
{

	if (frameData.resultVec.isEmpty())
	{
		return false;
	}

	const int barBandWidth = m_nFreqBarBandWidth;

	const QVector<ST_FFTPoint> FFTPtVecRef = frameData.resultVec;

	QVector<ST_FreqBar>& barHeightVec = m_vecFrameBar[BarVecIndex];

	for (int BarIndex = 0; BarIndex < barHeightVec.size(); BarIndex++)
	{
		ST_FreqBar& BarData = barHeightVec[BarIndex];
		BarData.startFreq = BarIndex * barBandWidth;
		BarData.bandWidth = barBandWidth;
		BarData.InCountFFTPt = 0;
		if (m_showDataType == EN_TimeSecType::Amp)
		{
			BarData.maxVal = -20;
			BarData.minVal = -20;
		}
		else
		{
			BarData.maxVal = 0;
			BarData.minVal = 0;
		}

		BarData.BarRect = QRect(0, 0, 0, 0);
	}

	auto getFFTPointIndexInBarVec = [](double FFTPtFreq, double startFreq, int bandWidth,int barVecSize)->int
		{
			if (bandWidth == 0)
			{
				return -1;
			}

			int PtInVecIndex = (FFTPtFreq - startFreq) / bandWidth;

			if (PtInVecIndex < 0 || PtInVecIndex >= barVecSize)
			{
				return -1;
			}
			return PtInVecIndex;

		};

	for (int FFTPtIndex = 0; FFTPtIndex < FFTPtVecRef.size(); FFTPtIndex++)
	{
		const ST_FFTPoint& FFTPoint = FFTPtVecRef[FFTPtIndex];
		const double fftReal = FFTPoint.amplitude;
		double fftPointDb = AudioProtocol::fftRealToDB(fftReal, const_audio_normalAudioFileMaxDB);
		double fftPhase = FFTPoint.phase;
		int PtInVecIndex = getFFTPointIndexInBarVec(FFTPoint.frequency, m_nMinFreq, barBandWidth, barHeightVec.size());
		if (PtInVecIndex == -1)
		{
			continue;
		}

		ST_FreqBar& FreqBar = barHeightVec[PtInVecIndex];
		int newHeight = getDbHeight(fftPointDb);

		FreqBar.InCountFFTPt += 1;

		if (m_showDataType == EN_TimeSecType::Amp)
		{
			FreqBar.maxVal = qMax(fftPointDb, FreqBar.maxVal);
		}
		else
		{
			FreqBar.maxVal = qMax(fftPhase, FreqBar.maxVal);
		}
		

		if (FreqBar.minVal <= 1)
		{
			if (m_showDataType == EN_TimeSecType::Amp)
			{
				FreqBar.minVal = fftPointDb;
			}
			else
			{
				FreqBar.minVal = fftPhase;
			}
		}
		else
		{
			FreqBar.minVal = qMin(fftPointDb, FreqBar.minVal);
		}
		
	}

	for (int BarIndex = 0; BarIndex < barHeightVec.size(); BarIndex++)
	{
		ST_FreqBar& BarData = barHeightVec[BarIndex];
		BarData.BarRect = getFreqBarRect(BarData.startFreq, BarData.bandWidth, BarData.maxVal);
	}

	return true;


}

void FFT_Chart_STFTTimeSection::leaveEvent(QEvent* event)
{
	m_bMouseInDrawArea = false;
	m_ptMousePos = QPoint(-1, -1);
	update();
}

void FFT_Chart_STFTTimeSection::hideEvent(QHideEvent* event)
{
	qDebug() << "FFT_Chart_STFTTimeSection::hideEvent";
	emit sgn_windowHide();
}

void FFT_Chart_STFTTimeSection::mouseMoveEvent(QMouseEvent* event)
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

	update();

}

void FFT_Chart_STFTTimeSection::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QRect thisRect = this->rect();

	QRect	drawAreaRect = getDrawAreaRect();

	QRect LeftAxisRect = QRect(QPoint(0, m_nTopTitleHeight), drawAreaRect.bottomLeft());
	QRect TopAxisRect = QRect(QPoint(m_nLeftAxisWidth, 0), drawAreaRect.topRight());
	QRect BottomAxisRect = QRect(drawAreaRect.bottomLeft(), QPoint(drawAreaRect.bottomRight().x(), thisRect.height()));
	QRect RightColorMapRect = QRect(QPoint(drawAreaRect.topRight().x(), m_nTopTitleHeight), QPoint(thisRect.right(), thisRect.height() - m_nBottomAxisWidth));

	//if (true) drawAxisRect(painter, drawAreaRect, LeftAxisRect, TopAxisRect, BottomAxisRect, RightColorMapRect);



	drawTitle(painter, TopAxisRect);
	drawValueAxis(painter, LeftAxisRect, false);
	drawFreqAxis(painter, BottomAxisRect);
	drawValueArea(painter, drawAreaRect);
	if (m_bMouseInDrawArea)
	{
		drawMousePosValue(painter, drawAreaRect);
	}

}

void FFT_Chart_STFTTimeSection::drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect)
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

void FFT_Chart_STFTTimeSection::drawTitle(QPainter& painter, QRect& TopAxisRect)
{
	painter.setBrush(Qt::NoBrush);
	painter.setFont(m_ft_titleFont);

	QPen TitlePen;
	TitlePen.setWidth(2);
	TitlePen.setColor(m_crTitle);
	painter.setPen(TitlePen);

	painter.drawText(TopAxisRect, Qt::AlignCenter, m_strTitle);
}


void FFT_Chart_STFTTimeSection::drawValueAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis)
{
	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(m_crAxis);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("ºÚÌå");
	painter.setFont(valStrFt);

	QPoint intervalStartPt = LeftAxisArea.bottomRight() - QPoint(1, -1);
	double    startVal			= 0;
	double    maxFVal			= 0;

	if (m_showDataType == EN_TimeSecType::Amp)
	{
		startVal	= m_dMinDB;
		maxFVal		= m_dMaxDB;
	}
	else
	{
		startVal	= m_dMinPhase;
		maxFVal		= m_dMaxPhase;
	}


	int    totalScaleCount = m_nDBScaleIntervalCount + 1;
	double scaleInterval = (double)LeftAxisArea.height() / (double)(totalScaleCount - 1);
	double ValInterval = (maxFVal - startVal) / (totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString valStr;
		
		if (m_showDataType == EN_TimeSecType::Amp)
		{
			valStr = QString::number(startVal + ValInterval * scaleIndex) + QString("db");
		}
		else
		{
			valStr = QString::number(startVal + ValInterval * scaleIndex,'f', 2);
		}

		
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

void FFT_Chart_STFTTimeSection::drawFreqAxis(QPainter& painter, QRect& BottomAxisArea)
{
	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(m_crAxis);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("ºÚÌå");
	painter.setFont(valStrFt);

	QPoint intervalStartPt	= BottomAxisArea.topLeft() + QPoint(0, 1);
	int    startFreq		= m_nMinFreq;
	int    EndFreq			= m_nMaxFreq;
	int    totalScaleCount	= m_nFreqScaleIntervalCount + 1;
	double scaleInterval	= (double)BottomAxisArea.width() / (double)(totalScaleCount - 1);
	double FreqInterval		= (double)(EndFreq - startFreq) / (double)(totalScaleCount - 1);

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



void FFT_Chart_STFTTimeSection::drawValueArea(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(drawArea);

	if (m_vecFrameBar.isEmpty())
	{
		return;
	}
	if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= m_vecFrameBar.size())
	{
		return;
	}

	const QVector<ST_FreqBar>& resultVec = m_vecFrameBar[m_ndrawFrameIndex];

	RectPen.setWidth(1);
	RectPen.setColor(Qt::black);

	painter.setPen(RectPen);
	painter.setBrush(Qt::blue);

	for (int barIndex = 0; barIndex < resultVec.size(); barIndex++)
	{
		const QRect& drawRect = resultVec[barIndex].BarRect;
		painter.drawRect(drawRect);
	}


}

void FFT_Chart_STFTTimeSection::drawMousePosValue(QPainter& painter, QRect& drawArea)
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
	painter.drawLine(QPoint(FreqX, FreqStartY),QPoint(FreqX, FreqEndY));
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

	if (m_showDataType == EN_TimeSecType::Amp)
	{
		double DbVal = PosYToDb(m_ptMousePos.y());
		painter.drawText(ValRect, Qt::AlignCenter, QString::number(DbVal, 'f', 1) + "db");
	}
	else
	{
		double PhaseVal = posYToPhase(m_ptMousePos.y());
		painter.drawText(ValRect, Qt::AlignCenter, QString::number(PhaseVal, 'f', 2));
	}	

	if (m_ndrawFrameIndex < 0 || m_ndrawFrameIndex >= m_vecFrameBar.size())
	{
		return;
	}

	const QVector<ST_FreqBar>& freamVecRef = m_vecFrameBar[m_ndrawFrameIndex];

	int BarIndex = (FreqVal - m_nMinFreq) / m_nFreqBarBandWidth;
	if (BarIndex < 0 || BarIndex >= freamVecRef.size())
	{
		return;
	}

	const ST_FreqBar& BarRef = freamVecRef[BarIndex];

	double frameMsec = m_STFTPara.GapInTimeLength * 1000 * m_ndrawFrameIndex;
	QTime frameTime = QTime(0, 0, 0).addMSecs(frameMsec);

	QString FrameStr	= QString("Frame Index : %1 time : %2 ").arg(m_ndrawFrameIndex).arg(frameTime.toString("mm:ss.zzz"));
	QString FreqStr		= QString("Freq : %1 - %2 ").arg(BarRef.startFreq).arg(BarRef.startFreq + BarRef.bandWidth);


	QString dbStr		= QString("DB : %1 - %2 ").arg(BarRef.minVal).arg(BarRef.maxVal);

	QSize valStrRectSize(300, 60);
	QRect valStrRect;
	valStrRect.setSize(valStrRectSize);
	valStrRect.moveTopLeft(m_ptMousePos);

	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(valStrRect);
	painter.drawText(valStrRect, Qt::AlignLeft, FrameStr + "\n" + FreqStr + "\n" + dbStr);

}