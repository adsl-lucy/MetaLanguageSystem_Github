#include "FFT_Chart_STFTHotGram.h"
#pragma execution_character_set("utf-8")

FFT_Chart_STFTHotGram::FFT_Chart_STFTHotGram(QWidget* parent) :QWidget(parent)
{
	init();
	setMouseTracking(true);
}

FFT_Chart_STFTHotGram::~FFT_Chart_STFTHotGram()
{

}

void FFT_Chart_STFTHotGram::init()
{
	QFont titleFont;
	titleFont.setPixelSize(20);
	m_ft_titleFont = titleFont;
	m_pSTFTwatcher = new QFutureWatcher<void>(this);

	//connect(m_pSTFTwatcher, SIGNAL(finished()), this, SLOT(slot_GenFinished())); bug 不发送这个信号
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &FFT_Chart_STFTHotGram::slot_GenProgressValueChanged);
}

void FFT_Chart_STFTHotGram::setSTFTResultPara(const ST_STFTInputpara& para)
{
	m_para = para;
}

void FFT_Chart_STFTHotGram::setFreqRange(int startFreq, int endFreq)
{
	m_nMinFreq = startFreq;
	m_nMaxFreq = endFreq;
}

void FFT_Chart_STFTHotGram::setCurrentTime(QTime currentTime)
{
	m_currentTime = currentTime;
	//qDebug() << QString("FFT_Chart_STFTHotGram::setCurrentTime : %1").arg(currentTime.toString("mm:ss:zzz"));
	update();
}

void FFT_Chart_STFTHotGram::setTimeRange(QTime startTime, int chtTimeLength)
{
	m_StartTime = startTime;
	m_ChtTimeLengthMsec = chtTimeLength;
	//qDebug() << QString("FFT_Chart_STFTHotGram::setTimeRange : startTime %1 chtTimeLength %2").arg(startTime.toString("ss.zzz")).arg(m_ChtTimeLengthMsec);
	update();
}

void FFT_Chart_STFTHotGram::getCurrentTimeRange(QTime& startTime, QTime& endTime)
{
	startTime = m_StartTime;
	endTime = startTime.addMSecs(m_ChtTimeLengthMsec);
}

void FFT_Chart_STFTHotGram::setDbRange(int startDB, int endDB)
{
	m_dMinDB = startDB;
	m_dMaxDB = endDB;
}

void  FFT_Chart_STFTHotGram::setFreqBandWidth(int hz)
{
	m_nColorRectBandWidth = hz;
}
void  FFT_Chart_STFTHotGram::setTimeInterval(int msec)
{
	m_nColorRectTimeIntervalMsec = msec;
}

void FFT_Chart_STFTHotGram::setCurrentFrameIndex(int frameIndex)
{
	//qDebug() << m_strTitle << QString("updateFrameIndex : %1").arg(frameIndex);
	m_nCurrentFrameIndex = frameIndex;
	update();
}

void FFT_Chart_STFTHotGram::resetColorRect(QString dataKey)
{
	const QMap<QString, ST_STFTOutputData>& STFTMapRef = DataCenterManager::instance()->getSTFTOutputMap();
	auto mapPos = STFTMapRef.find(dataKey);
	if (mapPos == STFTMapRef.end())
	{
		qDebug() << "FFT_Chart_STFTTimeSection::resetFrameRect STFTMapPos end!";
		return;
	}

	const ST_STFTOutputData& dataRef = mapPos.value();
	m_currentSTFTDataKey = dataKey;

	QRect drawArea = getDrawAreaRect();

	//int   MinIntervalOnY = drawArea.height() / m_nMaxRectOnFreq;
	//int   MinIntervalOnX = drawArea.width()  / m_nMaxRectOnTime;

	int   MinIntervalOnY = 1;
	int   MinIntervalOnX = 1;

	int DrawAreaBandWidth	= m_nMaxFreq - m_nMinFreq;
	int FreqBandCount		= DrawAreaBandWidth / m_nColorRectBandWidth;
	m_nCrRectFreqIntervalY	= qMax(MinIntervalOnY, drawArea.height() / FreqBandCount);

	int TimeIntervalCount	= m_ChtTimeLengthMsec / m_nColorRectTimeIntervalMsec;
	m_nCrRectTimeIntervalX	= qMax(MinIntervalOnX, drawArea.width() / TimeIntervalCount);
	
	int totalRectYCountInWnd	= drawArea.height() / m_nCrRectFreqIntervalY;
	int totalRectXCountInWnd	= drawArea.width() / m_nCrRectTimeIntervalX;

	if (totalRectYCountInWnd <= 0 || totalRectXCountInWnd <= 0)
	{
		return;
	}	
	
	m_dCrRectFreqBandWidth	= (double)DrawAreaBandWidth		/ (double)totalRectYCountInWnd;
	m_dCrRectTimeLengthMsec = (double)m_ChtTimeLengthMsec	/ (double)totalRectXCountInWnd;

	int totalRectXCount = dataRef.InputPara.timeLength * 1000.0 / m_dCrRectTimeLengthMsec;

	ST_FFTFreqColorRect nullRect;
	QVector<ST_FFTFreqColorRect> nullFrameVec = QVector<ST_FFTFreqColorRect>(totalRectYCountInWnd, nullRect);
	m_vecCrFrame.clear();
	m_vecCrFrame = QVector<QVector<ST_FFTFreqColorRect>>(totalRectXCount, nullFrameVec);

	ST_HotChtThreadProcessData nullData;
	nullData.dataKey = m_currentSTFTDataKey;
	nullData.pCht = this;
	nullData.frameIndex = -1;
	m_currentProcessVec.clear();
	m_currentProcessVec = QVector<ST_HotChtThreadProcessData>(totalRectXCount, nullData);
	for (int index = 0; index < m_currentProcessVec.size(); index++)
	{
		m_currentProcessVec[index].frameIndex = index;
	}
	m_bOnGenerate = true;
	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, FFT_Chart_STFTHotGram::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);


}

void FFT_Chart_STFTHotGram::FillTargetFrame(const ST_HotChtThreadProcessData data)
{
	const QMap<QString, ST_STFTOutputData>& STFTMapRef = DataCenterManager::instance()->getSTFTOutputMap();
	auto mapPos = STFTMapRef.find(data.dataKey);
	if (mapPos == STFTMapRef.end())
	{
		qDebug() << "FFT_Chart_STFTHotGram::FillTargetFrame STFTMapPos end!";
		return;
	}

	const ST_STFTOutputData& dataRef = mapPos.value();

	data.pCht->FillSTFTDataIntoFrame(data.frameIndex, dataRef.InputPara, dataRef.vecOutput);
}

void FFT_Chart_STFTHotGram::slot_GenFinished()
{
	emit sgn_HotRectGenerateState(100, 1, QString());	
	m_currentProcessVec.clear();
	m_currentTime = QTime(0, 0, 0);
	m_bOnGenerate = false;
	qDebug() << "FFT_Chart_STFTHotGram::slot_GenFinished";
	GenPixmap();
	update();
}

void FFT_Chart_STFTHotGram::GenPixmap()
{
	if (m_vecCrFrame.isEmpty())
	{
		return;
	}

	if (m_vecCrFrame[0].isEmpty())
	{
		return;
	}

	QSize ImageSize = QSize(m_nCrRectTimeIntervalX * m_vecCrFrame.size(), m_nCrRectFreqIntervalY * m_vecCrFrame[0].size());
	QRect drawArea = getDrawAreaRect();

	m_HotChtImage = QImage(ImageSize, QImage::Format_RGB32);

	for (int frameIndex = 0; frameIndex < m_vecCrFrame.size(); frameIndex++)
	{
		const QVector<ST_FFTFreqColorRect>& FrameRectVec = m_vecCrFrame[frameIndex];
		for (int FreqRectIndex = 0; FreqRectIndex < FrameRectVec.size(); FreqRectIndex++)
		{
			const ST_FFTFreqColorRect& CrRectRef = FrameRectVec[FreqRectIndex];
			const QRect& CrRect = CrRectRef.rectFromTime0;
			for (int X = CrRect.left(); X <= CrRect.right(); X++)
			{
				for (int Y = CrRect.top(); Y <= CrRect.bottom(); Y++)
				{
					m_HotChtImage.setPixelColor(QPoint(X,Y - drawArea.top()), CrRectRef.BarColor.rgb());
				}
			}
		}
	}
	int CrCount = m_HotChtImage.colorCount();

	//QString saveDir = QApplication::applicationDirPath() + QString("/TestAudio") + QString("/%1").arg("test.png");
	//bool saveState = m_HotChtImage.save(saveDir,"PNG",100);
	//int a = 0;

}

void FFT_Chart_STFTHotGram::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "FFT_Chart_STFTHotGram::slot_GenProgressValueChanged RectVec empty!";
		return;
	}

	int frameCount = m_currentProcessVec.size();
	int hunderdsOfFrame = qMax(1, frameCount / 100);
	int processedCount = val;
	int percentage = processedCount / hunderdsOfFrame;
	if (percentage > m_nLastReportPercantage)
	{
		if (processedCount >= frameCount)
		{
			slot_GenFinished();
		}
		else
		{
			emit sgn_HotRectGenerateState(percentage, QThreadPool::globalInstance()->activeThreadCount(), QString("%1 / %2 ").arg(processedCount).arg(frameCount));;
			m_nLastReportPercantage = percentage;
		}

	}
	qDebug() << QString("slot_GenProgressValueChanged :%1 / %2 ").arg(processedCount).arg(frameCount);

}

void FFT_Chart_STFTHotGram::FillSTFTDataIntoFrame(const int TimeFrameIndex, const ST_STFTInputpara& para, const QVector<ST_FFTOutputData>& dataVec)
{
	if (TimeFrameIndex < 0 || TimeFrameIndex >= m_vecCrFrame.size())
	{
		return;
	}

	QRect drawAreaRect = getDrawAreaRect();
	QVector<ST_FFTFreqColorRect>& TimeFrameVecRef = m_vecCrFrame[TimeFrameIndex];

	int frameMaxDb		= -20;
	int frameIncountPt	= 0;

	for (int FreqRectIndex = 0; FreqRectIndex < TimeFrameVecRef.size(); FreqRectIndex++)
	{
		ST_FFTFreqColorRect& CrRectRef = TimeFrameVecRef[FreqRectIndex];
		CrRectRef.startFreq		= m_dCrRectFreqBandWidth * FreqRectIndex;
		CrRectRef.startMsec		= m_dCrRectTimeLengthMsec * TimeFrameIndex;
		CrRectRef.InCountFFTPt	= 0;

		int startTimeFrameIndex		= 0;
		int endTimeFrameIndex		= 0;
		int startFreqRectIndex		= 0; 
		int endFreqRectIndex		= 0;

		if (FreqRectIndex == TimeFrameVecRef.size() / 2)
		{
			int a = 0;
		}

		bool searchState = getCrRectInDataVecIndex(CrRectRef.startFreq, CrRectRef.startMsec, dataVec,
												startTimeFrameIndex, endTimeFrameIndex, startFreqRectIndex, endFreqRectIndex);




		if (!searchState)
		{
			CrRectRef.BarColor	= getColorFromDB(CrRectRef.maxDB);
			CrRectRef.rectFromTime0 = QRect(QPoint(-1, -1), QSize(0,0));
			continue;
		}
		else
		{
			int BarStartX = TimeFrameIndex * m_nCrRectTimeIntervalX;
			int BarStartY = drawAreaRect.bottom() - FreqRectIndex * m_nCrRectFreqIntervalY;
			CrRectRef.rectFromTime0 = QRect(QPoint(BarStartX, BarStartY), QSize(m_nCrRectTimeIntervalX, m_nCrRectFreqIntervalY));
		}	
		
		for (int currentFFTFrameIndex = startTimeFrameIndex; currentFFTFrameIndex <= endTimeFrameIndex; currentFFTFrameIndex++)
		{
			const ST_FFTOutputData& FFTFrameRef = dataVec[currentFFTFrameIndex];
			for (int currentFFTPtIndex = startFreqRectIndex; currentFFTPtIndex <= endFreqRectIndex; currentFFTPtIndex++)
			{
				const ST_FFTPoint& FFTPt = FFTFrameRef.resultVec[currentFFTPtIndex];
				double currentPtDb = AudioProtocol::fftRealToDB(FFTPt.amplitude, const_audio_normalAudioFileMaxDB);

				if (currentPtDb > 50)
				{
					int a = 0;
				}

				if (CrRectRef.InCountFFTPt == 0)
				{
					CrRectRef.minDB = CrRectRef.maxDB = currentPtDb;
				}
				else
				{
					CrRectRef.minDB = qMin(currentPtDb, CrRectRef.minDB);
					CrRectRef.maxDB = qMax(currentPtDb, CrRectRef.maxDB);
					frameMaxDb = qMax((int)currentPtDb, frameMaxDb);
				}

				CrRectRef.InCountFFTPt += 1;
				frameIncountPt += 1;
			}
			CrRectRef.BarColor = getColorFromDB(CrRectRef.maxDB);
		}

		

	}

	//qDebug() << QString("FFT_Chart_STFTHotGram::FillSTFTDataIntoFrame index : %1 frameMaxDb : %2 frameIncountPt %3").arg(TimeFrameIndex).arg(frameMaxDb).arg(frameIncountPt);

}

bool FFT_Chart_STFTHotGram::getCrRectInDataVecIndex(double frameStartFreq, double frameStartMsec, const QVector<ST_FFTOutputData>& dataVec,
	int& startTimeFrameIndex, int& endTimeFrameIndex, int& startFreqRectIndex, int& endFreqRectIndex)
{
	if (frameStartFreq < 0)
	{
		return false;
	}

	double frameStartSec = frameStartMsec / 1000.0;

	if (frameStartSec < m_para.startTime || frameStartSec > m_para.startTime + m_para.timeLength)
	{
		return false;
	}

	auto checkIndexValid = [](int startIndex, int& endIndex, int vecSize) ->bool
		{
			if (startIndex < 0 || startIndex >= vecSize)
			{
				return false;
			}

			if (endIndex < 0)
			{
				return false;
			}
			if (endIndex >= vecSize)
			{
				endIndex = vecSize - 1;
			}
			return true;
		};

	double CrRectTimeLengthSec	= m_dCrRectTimeLengthMsec / 1000.0;
	endTimeFrameIndex			= (frameStartSec + CrRectTimeLengthSec) / m_para.GapInTimeLength;
	startTimeFrameIndex			= frameStartSec / m_para.GapInTimeLength;

	bool FFtFrameValid = checkIndexValid(startTimeFrameIndex, endTimeFrameIndex, dataVec.size());
	if (!FFtFrameValid)
	{
		return false;
	}

	const ST_FFTOutputData& frame = dataVec[startTimeFrameIndex];
	double FreqDelta = frame.para.DeltaFreq;

	startFreqRectIndex = frameStartFreq / FreqDelta;
	endFreqRectIndex = (frameStartFreq + m_dCrRectFreqBandWidth) / FreqDelta;

	bool FFtBarValid = checkIndexValid(startFreqRectIndex, endFreqRectIndex, frame.resultVec.size());
	return FFtBarValid;

}

int FFT_Chart_STFTHotGram::getTimeIndexInCrVec(int timeMsec)
{

	int frameIndex = timeMsec / m_dCrRectTimeLengthMsec;

	if (frameIndex < 0 || frameIndex >= m_vecCrFrame.size())
	{
		return -1;
	}



	return frameIndex;
}

int FFT_Chart_STFTHotGram::getFreqIndexInCrVec(int Freq)
{
	if (m_vecCrFrame.isEmpty())
	{
		return -1;
	}

	int FreqIndex = Freq / m_dCrRectFreqBandWidth;
	const QVector<ST_FFTFreqColorRect>& frame0 = m_vecCrFrame[0];
	if (FreqIndex < 0 || FreqIndex >= m_vecCrFrame.size())
	{
		return -1;
	}

	return FreqIndex;
}

QRect FFT_Chart_STFTHotGram::getDrawAreaRect()
{
	QRect		thisRect			= this->rect();
	QPoint		drawAreaStartPt		= QPoint(m_nLeftAxisWidth, m_nTopTitleHeight);
	QPoint		drawAreaEndPt		= QPoint(thisRect.width() - m_nRightColorMapRegionWidth, thisRect.height() - m_nBottomAxisWidth);
	QRect		drawAreaRect		= QRect(drawAreaStartPt, drawAreaEndPt);
	return		drawAreaRect;
}

void FFT_Chart_STFTHotGram::mouseMoveEvent(QMouseEvent* event)
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

void FFT_Chart_STFTHotGram::leaveEvent(QEvent* event)
{
	m_bMouseInDrawArea = false;
	m_ptMousePos = QPoint(-1, -1);
	update();
}

void FFT_Chart_STFTHotGram::paintEvent(QPaintEvent* event)
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

	drawColorMap(painter, RightColorMapRect);
	drawFreqAxis(painter, LeftAxisRect, false);
	drawTimeAxis(painter, BottomAxisRect);
	drawValueArea(painter, drawAreaRect);
	drawCurrentTime(painter, drawAreaRect);
	if (m_bMouseInDrawArea)
	{
		drawMousePosValue(painter, drawAreaRect);
	}


}

void FFT_Chart_STFTHotGram::drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect)
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

void FFT_Chart_STFTHotGram::drawTitle(QPainter& painter, QRect& TopAxisRect)
{
	painter.setBrush(Qt::NoBrush);
	painter.setFont(m_ft_titleFont);

	QPen TitlePen;
	TitlePen.setWidth(2);
	TitlePen.setColor(m_crTitle);
	painter.setPen(TitlePen);

	painter.drawText(TopAxisRect, Qt::AlignCenter, m_strTitle);
}

void FFT_Chart_STFTHotGram::drawColorMap(QPainter& painter, QRect& RightColorMapRect)
{
	QRect colorMapRect(QPoint(0, 0), QSize(m_nColorMapWidth, RightColorMapRect.height()));
	colorMapRect.moveCenter(RightColorMapRect.center() - QPoint(m_nColorMapWidth / 2, 0));

	QPen colorMapPen;
	colorMapPen.setWidth(2);
	colorMapPen.setColor(Qt::black);


	QPoint gradientStartPt = colorMapRect.bottomLeft();
	QPoint gradientEndPt = colorMapRect.topLeft();

	QLinearGradient valueGradient;
	valueGradient.setStart(gradientStartPt);
	valueGradient.setFinalStop(gradientEndPt);

	QPoint gradientArrow = gradientEndPt - gradientStartPt;

	valueGradient.setColorAt(0, m_nColorMap00Percent);
	valueGradient.setColorAt(0.33, m_nColorMap33Percent);
	valueGradient.setColorAt(0.66, m_nColorMap66Percent);
	valueGradient.setColorAt(1, m_nColorMap100Percent);

	QBrush RectMapBrush(valueGradient);

	painter.setPen(colorMapPen);
	painter.setBrush(RectMapBrush);
	painter.drawRect(colorMapRect);

	QPoint intervalStartPt = colorMapRect.bottomRight() + QPoint(1, 1);
	int    totalScaleCount = m_nTotalValueCount + 1;
	double scaleInterval = (double)colorMapRect.height() / (double)(totalScaleCount - 1);
	double scaleValInterval = std::max(0.001, (m_dMaxDB - m_dMinDB) / m_nTotalValueCount);

	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(Qt::black);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("黑体");
	painter.setFont(valStrFt);

	//QFontDatabase ftDataBase;
	//QStringList list = ftDataBase.families();

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString valStr = QString::number(m_dMinDB + scaleIndex * scaleValInterval) + QString("dB");
		QPoint scaleStartPt = QPoint(intervalStartPt.x(), intervalStartPt.y() - scaleInterval * scaleIndex);
		QPoint scaleEndPt = scaleStartPt + QPoint(m_nAxiesScaleLength, 0);

		painter.setPen(AxisPen);
		painter.drawLine(scaleStartPt, scaleEndPt);

		QRectF boundingRect = painter.boundingRect(colorMapRect, valStr);
		boundingRect.moveCenter(QPointF(0, scaleStartPt.y()));
		boundingRect.moveLeft(scaleEndPt.x() + m_nAxiesValStrMargin);

		painter.drawText(boundingRect, Qt::AlignCenter, valStr);

	}

}

void FFT_Chart_STFTHotGram::drawFreqAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis)
{
	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(m_crAxis);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("黑体");
	painter.setFont(valStrFt);

	QPoint intervalStartPt = LeftAxisArea.bottomRight() - QPoint(1, -1);
	int    startFreq = m_nMinFreq;
	int    maxFreq = m_nMaxFreq;
	int    totalScaleCount = m_nFreqScaleIntervalCount + 1;
	double scaleInterval = (double)LeftAxisArea.height() / (double)(totalScaleCount - 1);
	double FreqInterval = (m_nMaxFreq - m_nMinFreq) / (totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString valStr = QString::number(startFreq + FreqInterval * scaleIndex) + QString("hz");
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

void FFT_Chart_STFTHotGram::drawTimeAxis(QPainter& painter, QRect& BottomAxisArea)
{
	QPen AxisPen;
	AxisPen.setWidth(2);
	AxisPen.setColor(m_crAxis);

	QFont valStrFt;
	valStrFt.setPixelSize(m_nAxiesValStrFontSize);
	valStrFt.setFamily("黑体");
	painter.setFont(valStrFt);

	QPoint intervalStartPt = BottomAxisArea.topLeft() + QPoint(0, 1);
	int    startSec = QTime(0, 0, 0).secsTo(m_StartTime);
	int    EndSec = QTime(0, 0, 0).secsTo(getChtEndTime());
	int    totalScaleCount = m_nTimeScaleIntervalCount + 1;
	double scaleInterval = (double)BottomAxisArea.width() / (double)(totalScaleCount - 1);
	double timeInterval = (double)(EndSec - startSec) / (double)(totalScaleCount - 1);

	for (int scaleIndex = 0; scaleIndex < totalScaleCount; scaleIndex++)
	{
		QString valStr = QString::number(startSec + timeInterval * scaleIndex) + QString("s");
		QPoint scaleStartPt = QPoint(intervalStartPt.x() + scaleInterval * scaleIndex, intervalStartPt.y());
		QPoint scaleEndPt = scaleStartPt + QPoint(0, m_nAxiesScaleLength);

		painter.setPen(AxisPen);
		painter.drawLine(scaleStartPt, scaleEndPt);

		QRectF boundingRect = painter.boundingRect(BottomAxisArea, valStr);
		boundingRect.moveCenter(QPointF(scaleStartPt.x(), 0));
		boundingRect.moveTop(scaleEndPt.y() + m_nAxiesValStrMargin);

		painter.drawText(boundingRect, Qt::AlignCenter, valStr);

	}
}

double FFT_Chart_STFTHotGram::getValueInPixel(QPoint pt)
{

	double resultVal = 0;

	return resultVal;

}

QTime FFT_Chart_STFTHotGram::getChtEndTime()
{
	QTime endTime = m_StartTime.addMSecs(m_ChtTimeLengthMsec);
	return endTime;
}

int FFT_Chart_STFTHotGram::PosYoFreq(int posY)
{
	QRect drawArea = getDrawAreaRect();

	if (posY < drawArea.top() || posY > drawArea.bottom())
	{
		return -1;
	}

	double YRatio = ((double)drawArea.bottom() - (double)posY) / (double)drawArea.height();
	double TotalFreqWidth = m_nMaxFreq - m_nMinFreq;
	double resultFreq = YRatio * TotalFreqWidth + m_nMinFreq;
	return resultFreq;
}

int FFT_Chart_STFTHotGram::FreqToPosY(int Freq)
{
	
	if (Freq < m_nMinFreq || Freq > m_nMaxFreq)
	{
		return -1;
	}

	if (m_nMaxFreq - m_nMinFreq < 0.001)
	{
		return -1;
	}

	QRect	drawArea			= getDrawAreaRect();
	double	FreqRatio			= ((double)Freq - (double)m_nMinFreq) / ((double)m_nMaxFreq - (double)m_nMinFreq);
	double	TotalFreqHeight		= drawArea.height();
	double	resultFreq			= FreqRatio * TotalFreqHeight + drawArea.top();
	return	resultFreq;


}

int FFT_Chart_STFTHotGram::PosXToTimeMsec(int posX)
{
	QRect drawArea = getDrawAreaRect();

	if (posX < drawArea.left() || posX > drawArea.right())
	{
		return -1;
	}

	double XRatio = ((double)posX - (double)drawArea.left()) / (double)drawArea.width();
	double resultMsec = QTime(0,0,0).msecsTo(m_StartTime.addMSecs(XRatio * m_ChtTimeLengthMsec));
	return resultMsec;
}

int FFT_Chart_STFTHotGram::MsecToPosX(int Msec)
{
	QTime testTime = QTime(0, 0, 0).addMSecs(Msec);

	if (testTime < m_StartTime || testTime > getChtEndTime())
	{
		return -1;
	}

	if (m_ChtTimeLengthMsec < 1)
	{
		return -1;
	}

	QRect	drawArea		= getDrawAreaRect();
	double	MsecRatio		= (double)m_StartTime.msecsTo(testTime) / (double)m_ChtTimeLengthMsec;
	double	TotalMsecWidth	= drawArea.width();
	int		resultY			= MsecRatio * TotalMsecWidth + drawArea.left();
	return	resultY;
}

QColor FFT_Chart_STFTHotGram::getColorFromDB(double dbVal)
{
	if (dbVal <= m_dMinDB)
	{
		return Qt::black;
	}
	else if (m_dMaxDB - m_dMinDB <= 0.001)
	{
		return Qt::black;
	}

	QLinearGradient valueGradient;
	valueGradient.setStart(QPoint(0, 0));
	valueGradient.setFinalStop(QPoint(0, 1));

	valueGradient.setColorAt(0, m_nColorMap00Percent);
	valueGradient.setColorAt(0.33, m_nColorMap33Percent);
	valueGradient.setColorAt(0.66, m_nColorMap66Percent);
	valueGradient.setColorAt(1, m_nColorMap100Percent);

	QColor startColor;
	QColor endColor;

	double ValInPercentage = (dbVal - m_dMinDB) / (m_dMaxDB - m_dMinDB);
	double startValInPercentage = 0;

	if (ValInPercentage < 0.33)
	{
		startColor = m_nColorMap00Percent;
		endColor = m_nColorMap33Percent;
		startValInPercentage = 0;
	}
	else if (ValInPercentage < 0.66)
	{
		startColor = m_nColorMap33Percent;
		endColor = m_nColorMap66Percent;
		startValInPercentage = 0.33;
	}
	else
	{
		startColor = m_nColorMap66Percent;
		endColor = m_nColorMap100Percent;
		startValInPercentage = 0.66;
	}

	int			startR = startColor.red();
	int			endR = endColor.red();
	double		resultR = (endR - startR) * (ValInPercentage - startValInPercentage) + startR;

	int			startG = startColor.green();
	int			endG = endColor.green();
	double		resultG = (endG - startG) * (ValInPercentage - startValInPercentage) + startG;

	int			startB = startColor.blue();
	int			endB = endColor.blue();
	double		resultB = (endB - startB) * (ValInPercentage - startValInPercentage) + startB;

	return QColor(resultR, resultG, resultB);

}


void FFT_Chart_STFTHotGram::drawValueArea(QPainter& painter, QRect& drawArea)
{
	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(m_crAxis);

	painter.setPen(RectPen);
	painter.setBrush(Qt::black);
	painter.drawRect(drawArea);

	if (m_bOnGenerate)
	{
		return;
	}

	int startMsec = QTime(0, 0, 0).msecsTo(m_StartTime);
	int endMsec = startMsec + m_ChtTimeLengthMsec - 1;

	int startFrameIndex = getTimeIndexInCrVec(startMsec);
	int endFrameIndex = getTimeIndexInCrVec(endMsec);

	painter.setPen(Qt::NoPen);

	if (startFrameIndex != -1 /* && endFrameIndex != -1 && endFrameIndex >= startFrameIndex*/)
	{
		int CurrentWndLeftFromTime0 = (QTime(0, 0, 0).msecsTo(m_StartTime) / m_dCrRectTimeLengthMsec) * m_nCrRectTimeIntervalX;

		if (true)
		{
			QRect ImageArea =QRect(QPoint(0,0), drawArea.size());
			ImageArea.moveLeft(CurrentWndLeftFromTime0);

			painter.drawImage(drawArea, m_HotChtImage, ImageArea);
		}
		else
		{
			for (int FrameIndex = startFrameIndex; FrameIndex <= endFrameIndex; FrameIndex++)
			{
				const QVector<ST_FFTFreqColorRect>& FrameVecRef = m_vecCrFrame[FrameIndex];
				int FrameXPos = drawArea.left() + FrameIndex * m_nCrRectTimeIntervalX - CurrentWndLeftFromTime0;

				bool RightAlign = false;
				if (FrameIndex == endFrameIndex)
				{
					RightAlign = (FrameXPos + m_nCrRectTimeIntervalX > drawArea.right());
				}

				for (int RectIndex = 0; RectIndex < FrameVecRef.size(); RectIndex++)
				{
					const ST_FFTFreqColorRect& CrRect = FrameVecRef[RectIndex];
					QRect drawRect = CrRect.rectFromTime0;
					drawRect.moveLeft(FrameXPos);

					if (RightAlign)
					{
						drawRect.setRight(drawArea.right());
					}

					painter.setBrush(CrRect.BarColor);
					painter.drawRect(drawRect);
				}

			}
		}
		

		
	}
	
	

	

}

void FFT_Chart_STFTHotGram::drawCurrentTime(QPainter& painter, QRect& drawArea)
{
	QPen linePen;
	linePen.setWidth(2);
	linePen.setColor(Qt::red);

	int TimeX = MsecToPosX(QTime(0,0,0).msecsTo(m_currentTime));
	int TimeStartY = drawArea.bottom();
	int TimeEndY = drawArea.top();
	painter.setPen(linePen);
	painter.drawLine(QPoint(TimeX, TimeStartY), QPoint(TimeX, TimeEndY));
}

void FFT_Chart_STFTHotGram::drawMousePosValue(QPainter& painter, QRect& drawArea)
{
	QPen linePen;
	linePen.setWidth(2);
	linePen.setColor(Qt::blue);

	int TimeX		= m_ptMousePos.x();
	int TimeStartY	= drawArea.bottom();
	int TimeEndY	= drawArea.top();

	int FreqY		= m_ptMousePos.y();
	int FreqStartX  = drawArea.left();
	int FreqEndY	= drawArea.right();

	painter.setPen(linePen);
	painter.drawLine(QPoint(TimeX, TimeStartY), QPoint(TimeX, TimeEndY));
	painter.drawLine(QPoint(FreqStartX, FreqY), QPoint(FreqEndY, FreqY));

	QSize valRectSize(80, 20);

	QRect TimeRect;
	TimeRect.setSize(valRectSize);
	TimeRect.moveCenter(QPoint(TimeX, drawArea.bottom() + valRectSize.height() / 2));

	QRect FreqRect;
	FreqRect.setSize(valRectSize);
	FreqRect.moveCenter(QPoint(drawArea.left() - valRectSize.width() / 2, m_ptMousePos.y()));

	QPen RectPen;
	RectPen.setWidth(2);
	RectPen.setColor(Qt::black);
	painter.setPen(RectPen);
	painter.setBrush(Qt::white);

	painter.drawRect(TimeRect);
	painter.drawRect(FreqRect);

	int Msec	= PosXToTimeMsec(m_ptMousePos.x());
	int FreqVal	= PosYoFreq(m_ptMousePos.y());	

	QTime MousePosTime = QTime(0, 0, 0).addMSecs(Msec);

	painter.drawText(FreqRect, Qt::AlignCenter, QString::number(FreqVal) + "hz");
	painter.drawText(TimeRect, Qt::AlignCenter, MousePosTime.toString("mm:ss.zzz"));

	int TimeFrameIndex = getTimeIndexInCrVec(QTime(0,0,0).msecsTo(MousePosTime));
	int FreqBarIndex = getFreqIndexInCrVec(FreqVal);

	if (TimeFrameIndex == -1 || FreqBarIndex == -1)
	{
		return;
	}

	const ST_FFTFreqColorRect& drawRectRef = m_vecCrFrame[TimeFrameIndex][FreqBarIndex];

	QTime BarStartTime	= QTime(0,0,0).addMSecs(drawRectRef.startMsec);
	QTime BarEndTime	= QTime(0,0,0).addMSecs(drawRectRef.startMsec + m_dCrRectTimeLengthMsec);
	int   BarStartFreq	= drawRectRef.startFreq;
	int   BarEndFreq	= BarStartFreq + m_dCrRectFreqBandWidth;
	double   minDb = drawRectRef.minDB;
	double	maxDb = drawRectRef.maxDB;
	int   RectPtCount = drawRectRef.InCountFFTPt;

	QString FrameStr	= QString("Frame Index : [%1][%2]").arg(TimeFrameIndex).arg(FreqBarIndex);
	QString TimeStr		= QString("time : %1 - %2 ").arg(BarStartTime.toString("mm:ss.zzz")).arg(BarEndTime.toString("mm:ss.zzz"));
	QString FreqStr		= QString("Freq : %1 - %2 ").arg(BarStartFreq).arg(BarEndFreq);
	QString DBStr		= QString("DB : %1 - %2 ").arg(minDb).arg(maxDb);
	QString CountStr	= QString("ptCount : %1").arg(RectPtCount);

	QSize valStrRectSize(300, 80);
	QRect valStrRect;
	valStrRect.setSize(valStrRectSize);
	valStrRect.moveTopLeft(m_ptMousePos);
	if (valStrRect.right() > drawArea.right())
	{
		valStrRect.moveTopRight(m_ptMousePos);
	}
	painter.setPen(RectPen);
	painter.setBrush(Qt::white);
	painter.drawRect(valStrRect);
	painter.drawText(valStrRect, Qt::AlignLeft, FrameStr + "\n" + TimeStr + "\n" + FreqStr + "\n" + DBStr + "\n" + CountStr);
	
}