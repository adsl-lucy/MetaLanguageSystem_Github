#include "TimeSecCht_BDSNR_OpenGL.h"
#pragma execution_character_set("utf-8")

OpenGLWindow::OpenGLWindow(QWindow* parent)
    : QOpenGLWindow(QOpenGLWindow::PartialUpdateBlit,parent)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::render(QPainter* painter)
{
    Q_UNUSED(painter);
}

void OpenGLWindow::initializeGL()
{
}

void OpenGLWindow::paintGL()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    QPainter painter(m_device);
    render(&painter);
}

void OpenGLWindow::renderLater()
{
    requestUpdate();
}

bool OpenGLWindow::event(QEvent* event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent* event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void OpenGLWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initializeGL();
    }

    paintGL();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
{

    m_pUpdateSectionTimer = new QTimer(this);
    m_pUpdateSectionTimer->setSingleShot(false);
    m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
    m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
    connect(m_pUpdateSectionTimer, &QTimer::timeout, [this]() 
        {
            renderNow();
        });
}

void TriangleWindow::initializeGL()
{
    const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";


    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    m_pUpdateSectionTimer->setTimerType(Qt::PreciseTimer);
    m_pUpdateSectionTimer->setInterval(m_nUpdateMsec);
    m_pUpdateSectionTimer->start();

}

void TriangleWindow::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    GLfloat vertices[] = {
        0.0f, 0.707f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;
}



TimeSecCht_BDSNR_OpenGL::TimeSecCht_BDSNR_OpenGL()
{
	init();
	setAnimating(false);
}

TimeSecCht_BDSNR_OpenGL::~TimeSecCht_BDSNR_OpenGL()
{

}

void TimeSecCht_BDSNR_OpenGL::init()
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
	connect(m_pSTFTwatcher, &QFutureWatcher<void>::progressValueChanged, this, &TimeSecCht_BDSNR_OpenGL::slot_GenProgressValueChanged);

}

void TimeSecCht_BDSNR_OpenGL::initializeGL()
{

}

QRect TimeSecCht_BDSNR_OpenGL::getThisRect()
{
	return QRect(0,0,width(),height());
}

void TimeSecCht_BDSNR_OpenGL::setCurrentFrameIndex(int index)
{
	if (index < 0 || index >= m_vecFrameBar_STFT.size())
	{
		qDebug() << "EffOscTimeSecCht::setCurrentFrameIndex invalid Index : " << index;
		return;
	}

	//qDebug() << m_strTitle << QString("updateFrameIndex : %1").arg(index);	

	m_ndrawFrameIndex = index;
	update();
}

void TimeSecCht_BDSNR_OpenGL::setDrawFreqRanged(int startFreq, int endFreq)
{
	m_nMinFreq = startFreq;
	m_nMaxFreq = endFreq;
	update();
}

void TimeSecCht_BDSNR_OpenGL::setDrawDBRange(double min, double max)
{
	m_dMinDB = min;
	m_dMaxDB = max;
	update();
}

void TimeSecCht_BDSNR_OpenGL::setChtType(EN_BDSNR_TimeSecChtBarType_GL Type)
{
	m_showDataType = Type;
	update();
}

void TimeSecCht_BDSNR_OpenGL::setNoisePaintSetting_EffOsc(bool TIQLine, bool UnderTIQBar, bool WndSepcNoise)
{
	m_bDraw_EffOsc_TIQLine = TIQLine;
	m_bDraw_EffOsc_UnderTIQBar = UnderTIQBar;
	m_bDraw_EffOsc_WndSpecNoise = WndSepcNoise;
	update();
}

void TimeSecCht_BDSNR_OpenGL::setNoisePaintSetting_BDSNR(bool BDSNR_Noise, bool BDSNR_ConstrainPt, bool BDSNR_EffectSubPt, bool BDSNR_ActiveFilter, bool BDSNR_ActiveFilter_Main)
{
	m_bDraw_BDSNR_Noise = BDSNR_Noise;
	m_bDraw_BDSNR_ConstrainPt = BDSNR_ConstrainPt;
	m_bDraw_BDSNR_EffectSubPt = BDSNR_EffectSubPt;
	m_bDraw_BDSNR_ActiveFilter = BDSNR_ActiveFilter;
	m_bDraw_BDSNR_ActiveFilter_Main = BDSNR_ActiveFilter_Main;
	update();
}

void TimeSecCht_BDSNR_OpenGL::GenBasicFilterRect(const QVector<ST_BandWidthFilter>& FilterVec, QVector<ST_BandWidthFilterActiveRect>& MFCCActiveVec, QVector<ST_FFTFreqBar>& MFCCFreqBarVec)
{
	QRect thisRect = getThisRect();
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

void TimeSecCht_BDSNR_OpenGL::resetFrameRect(QString dataKey)
{
	bool checkSTFTDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::STFTOutputData, dataKey);
	bool checkEffOscDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::WndSpecConstrain, dataKey);
	bool checkBDSNRDataExist = DataCenterManager::instance()->checkDataExist(EN_DataCenterAudioDataType::BDSNR, dataKey);
	if (!checkSTFTDataExist)
	{
		qDebug() << QString("OscillationSeparatorTimeSecCht::resetFrameRect STFTMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("STFT Data empty!"));
		return;
	}

	if (!checkEffOscDataExist)
	{
		qDebug() << QString("OscillationSeparatorTimeSecCht::resetFrameRect WndSpecConstrainMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("WndSpec Constrain Data empty!"));
		return;
	}

	if (!checkBDSNRDataExist)
	{
		qDebug() << QString("OscillationSeparatorTimeSecCht::resetFrameRect BDSNRMapPos end! Key : %1").arg(dataKey);
		emit  sgn_SecRectGenerateState(0, 0, QString("BDSNR Data empty!"));
		return;
	}

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

	m_currentSTFTDataKey = dataKey;
	m_vecFrameBar_STFT.clear();
	ST_FFTFreqBar nullBar;
	QVector<ST_FFTFreqBar> nullbarHeightVec;

	m_vecFrameBar_UnderTIQ.clear();
	m_vecFrameBar_WndSpecNoise.clear();
	m_vecFrameBar_EffectiveOscillation.clear();
	m_vecFrameBar_BDSNR_Noise.clear();
	m_vecFrameBar_BDSNR_Constrain.clear();
	m_vecFrameBar_BDSNR_EffectPt_Main.clear();
	m_vecFrameBar_BDSNR_EffectPt_Sub.clear();

	m_vecFrameBar_UnderTIQ = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_WndSpecNoise = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_EffectiveOscillation = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_Noise = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_Constrain = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_EffectPt_Main = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);
	m_vecFrameBar_BDSNR_EffectPt_Sub = QVector<QVector<ST_FFTFreqBar>>(frameCount, nullbarHeightVec);

	int GeneratebarCount = 0;
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

	QFuture<void> future = QtConcurrent::map(m_currentProcessVec, TimeSecCht_BDSNR_OpenGL::FillTargetFrame);
	m_pSTFTwatcher->setFuture(future);
	m_nLastReportPercantage = -1;
	slot_GenProgressValueChanged(0);

}

void TimeSecCht_BDSNR_OpenGL::setSTFTResultPara(const ST_STFTInputpara& para)
{
	m_STFTPara = para;
	//AudioProtocol::duplicateSTFTData(data,m_drawData);

	//if (m_drawData.vecOutput.isEmpty())
	{
		return;
	}

}

QRect TimeSecCht_BDSNR_OpenGL::getDrawAreaRect()
{
	QRect		thisRect = getThisRect();
	QPoint		drawAreaStartPt = QPoint(m_nLeftAxisWidth, m_nTopTitleHeight);
	QPoint		drawAreaEndPt = QPoint(thisRect.width() - m_nRightColorMapRegionWidth, thisRect.height() - m_nBottomAxisHeight);
	QRect		drawAreaRect = QRect(drawAreaStartPt, drawAreaEndPt);
	return		drawAreaRect;
}

QRect TimeSecCht_BDSNR_OpenGL::getBottomAxisRect()
{
	QRect  drawAreaRect = getDrawAreaRect();
	QRect  BottomAxisRect = QRect(drawAreaRect.bottomLeft(), QPoint(drawAreaRect.bottomRight().x(), getThisRect().height()));
	return BottomAxisRect;
}

int   TimeSecCht_BDSNR_OpenGL::FreqToPosX(double freq)
{
	QRect drawArea = getDrawAreaRect();
	double FreqRatio = (freq - (double)m_nMinFreq) / ((double)m_nMaxFreq - (double)m_nMinFreq);
	int FreqX = FreqRatio * drawArea.width() + drawArea.x();
	return FreqX;
}

int   TimeSecCht_BDSNR_OpenGL::PosXToFreq(int posX)
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

int   TimeSecCht_BDSNR_OpenGL::getDbHeight(const double valDb)
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

double TimeSecCht_BDSNR_OpenGL::PosYToDb(int posY)
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

int TimeSecCht_BDSNR_OpenGL::MousePosToMFCCFilterRectIndex(QPoint mousePos)
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

QRect TimeSecCht_BDSNR_OpenGL::getFreqBarRect(int startFreq, int bandWidth, double RectMaxVal)
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


void TimeSecCht_BDSNR_OpenGL::slot_GenFinished()
{
	emit sgn_SecRectGenerateState(100, 1, QString());
	m_currentProcessVec.clear();
	m_ndrawFrameIndex = 0;
	update();
}

void TimeSecCht_BDSNR_OpenGL::slot_GenProgressValueChanged(int val)
{
	if (m_currentProcessVec.isEmpty())
	{
		qDebug() << "EffOscTimeSecCht::slot_GenProgressValueChanged RectVec empty!";
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

void TimeSecCht_BDSNR_OpenGL::FillTargetFrame(const ST_SecChtThreadProcessData data)
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

bool  TimeSecCht_BDSNR_OpenGL::generateFreqBarVec(const int STFTFrameIndex, const ST_FFTOutputData& frameData)
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

void TimeSecCht_BDSNR_OpenGL::leaveEvent(QEvent* event)
{
	m_bMouseInDrawArea = false;
	m_ptMousePos = QPoint(-1, -1);
	m_bMouseInFilterActiveArea = false;
	m_ptMousePos_ActiveMFCCRect = QPoint(-1, -1);
	update();
}

void TimeSecCht_BDSNR_OpenGL::hideEvent(QHideEvent* event)
{
	qDebug() << "FFT_Chart_STFTTimeSection::hideEvent";
	emit sgn_windowHide();
}

void TimeSecCht_BDSNR_OpenGL::mouseMoveEvent(QMouseEvent* event)
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

	if (m_showDataType == EN_BDSNR_TimeSecChtBarType_GL::BDSNR)
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

void TimeSecCht_BDSNR_OpenGL::render(QPainter* p_painter)
{
	QPainter& painter = *p_painter;

	QRect  thisRect = getThisRect();

	painter.setBrush(Qt::white);
	painter.drawRect(thisRect);

	QRect	drawAreaRect = getDrawAreaRect();

	QRect LeftAxisRect = QRect(QPoint(0, m_nTopTitleHeight), drawAreaRect.bottomLeft());
	QRect TopAxisRect = QRect(QPoint(m_nLeftAxisWidth, 0), drawAreaRect.topRight());
	QRect BottomAxisRect = getBottomAxisRect();
	QRect RightColorMapRect = QRect(QPoint(drawAreaRect.topRight().x(), m_nTopTitleHeight), QPoint(thisRect.right(), thisRect.height() - m_nBottomAxisHeight));

	drawTitle(painter, TopAxisRect);
	drawValueAxis(painter, LeftAxisRect, false);

	switch (m_showDataType)
	{
	case EN_BDSNR_TimeSecChtBarType_GL::STFT:drawValueArea_STFT(painter, drawAreaRect); break;
	case EN_BDSNR_TimeSecChtBarType_GL::EffectiveOscillation:drawValueArea_EffectiveOsc(painter, drawAreaRect); break;
	case EN_BDSNR_TimeSecChtBarType_GL::BDSNR:drawValueArea_BDSNR(painter, drawAreaRect); break;
	}

	if (m_showDataType == EN_BDSNR_TimeSecChtBarType_GL::BDSNR)
	{
		drawFilterActvateState(painter, BottomAxisRect);
	}

	if (m_bDraw_EffOsc_TIQLine)
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

void TimeSecCht_BDSNR_OpenGL::drawAxisRect(QPainter& painter, QRect& drawAreaRect, QRect& LeftAxisRect, QRect& TopAxisRect, QRect& BottomAxisRect, QRect& RightColorMapRect)
{
	QRect thisRect = getThisRect();
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

void TimeSecCht_BDSNR_OpenGL::drawTitle(QPainter& painter, QRect& TopAxisRect)
{
	painter.setBrush(Qt::NoBrush);
	painter.setFont(m_ft_titleFont);

	QPen TitlePen;
	TitlePen.setWidth(2);
	TitlePen.setColor(m_crTitle);
	painter.setPen(TitlePen);

	painter.drawText(TopAxisRect, Qt::AlignCenter, m_strTitle);
}


void TimeSecCht_BDSNR_OpenGL::drawValueAxis(QPainter& painter, QRect& LeftAxisArea, bool isLogAxis)
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

void TimeSecCht_BDSNR_OpenGL::drawFreqAxis(QPainter& painter, QRect& BottomAxisArea)
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

void TimeSecCht_BDSNR_OpenGL::drawThreshHoldInQuiet(QPainter& painter, QRect& drawArea)
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

void TimeSecCht_BDSNR_OpenGL::drawValueArea_STFT(QPainter& painter, QRect& drawArea)
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
void TimeSecCht_BDSNR_OpenGL::drawValueArea_EffectiveOsc(QPainter& painter, QRect& drawArea)
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

	if (m_bDraw_EffOsc_UnderTIQBar)
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

	if (m_bDraw_EffOsc_WndSpecNoise)
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

void TimeSecCht_BDSNR_OpenGL::drawValueArea_BDSNR(QPainter& painter, QRect& drawArea)
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

	if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_EffectPt_Main.size())
	{
		const QVector<ST_FFTFreqBar>& BDSNR_EffectMainPtBarVec = m_vecFrameBar_BDSNR_EffectPt_Main[m_ndrawFrameIndex];
		painter.setBrush(m_cr_BDSNR_Signal_Effective_Main);

		for (int barIndex = 0; barIndex < BDSNR_EffectMainPtBarVec.size(); barIndex++)
		{
			const QRect& drawRect = BDSNR_EffectMainPtBarVec[barIndex].BarRect;
			painter.drawRect(drawRect);
		}
	}

	if (m_bDraw_BDSNR_ActiveFilter && m_bDraw_BDSNR_ActiveFilter_Main)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter_Main.size())
		{
			const QVector<ST_FFTFreqBar>& NDSNR_ActiveMainFilterBarVec = m_vecFrameBar_BDSNR_ActiveFilter_Main[m_ndrawFrameIndex];
			painter.setBrush(m_cr_BDSNR_ConstrainFilterBar_Active_Main);
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

	if (m_bDraw_BDSNR_EffectSubPt)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_EffectPt_Sub.size())
		{
			const QVector<ST_FFTFreqBar>& BDSNR_EffectSubPtBarVec = m_vecFrameBar_BDSNR_EffectPt_Sub[m_ndrawFrameIndex];
			painter.setBrush(m_cr_BDSNR_Signal_Effective_Sub);

			for (int barIndex = 0; barIndex < BDSNR_EffectSubPtBarVec.size(); barIndex++)
			{
				const QRect& drawRect = BDSNR_EffectSubPtBarVec[barIndex].BarRect;
				painter.drawRect(drawRect);
			}
		}
	}

	if (m_bDraw_BDSNR_ActiveFilter)
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter_Sub.size())
		{
			const QVector<ST_FFTFreqBar>& NDSNR_ActiveSubFilterBarVec = m_vecFrameBar_BDSNR_ActiveFilter_Sub[m_ndrawFrameIndex];
			painter.setBrush(m_cr_BDSNR_ConstrainFilterBar_Active_Sub);
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


}

void TimeSecCht_BDSNR_OpenGL::drawFilterActvateState(QPainter& painter, QRect& BottomAxisArea)
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

void TimeSecCht_BDSNR_OpenGL::drawMousePosValue(QPainter& painter, QRect& drawArea)
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
	case EN_BDSNR_TimeSecChtBarType_GL::STFT:
	{
		valStrRectSize = QSize(350, 70);
	}break;
	case EN_BDSNR_TimeSecChtBarType_GL::EffectiveOscillation:
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
		valStrRectSize = QSize(350, 150);
		const ST_WndSpecConstrainPtTag& ptTag = FrameRef.VecSTFTPtState[BarRef.FFTPtIndex];

		QString ConstrainSourceIndexStr = QString("ConstrainSourceIndex	: %1 \n").arg(ptTag.ConstrainSourceIndex);
		QString ConstrainSourceFreqStr = QString("ConstrainSourceFreq	: %1 \n").arg(ptTag.ConstrainSourceFreq, 0, 'f', 2);
		QString MaxConstrainValStr = QString("ConstrainVal			: %1 \n").arg(ptTag.MaxConstrainVal_Compare, 0, 'f', 8);
		QString MaxConstrainDBStr = QString("ConstrainDB			: %1 \n").arg(ptTag.MaxConstrainDB_Compare, 0, 'f', 2);
		QString ptStateStr = QString("ptState				: %1 \n").arg(WndSpecConstrainNetwork::instance()->getWndConstrainStateStr(ptTag.ptConstrainState));

		showStr += ConstrainSourceIndexStr + ConstrainSourceFreqStr + MaxConstrainValStr + MaxConstrainDBStr + ptStateStr;

	}break;
	case EN_BDSNR_TimeSecChtBarType_GL::BDSNR:
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

	if (RectStartY + valStrRectSize.height() > getThisRect().bottom())
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

void TimeSecCht_BDSNR_OpenGL::drawActiveRectValue(QPainter& painter)
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

	const ST_BandWidthFilterActiveRect& MFCCActRect = freamVecRef[FilterRectIndex];

	int		FilterIndex = MFCCActRect.FilterIndex;

	const ST_BandWidthSNRConstrainData& BDSNRData = DataCenterManager::instance()->getBDSNROutputMap().find(m_currentSTFTDataKey).value();

	const ST_BandWidthFilterPt& FilterPtRef = BDSNRData.FrameVec[m_ndrawFrameIndex].vecBDFilterValue[FilterIndex];
	const ST_BandWidthFilter& FilterData = BDSNRData.FilterData.FilterVec[FilterIndex];

	double frameMsec = m_STFTPara.GapInTimeLength * 1000 * m_ndrawFrameIndex;
	QTime frameTime = QTime(0, 0, 0).addMSecs(frameMsec);


	QString FrameStr = QString("Frame Index	: %1 time : %2 \n").arg(m_ndrawFrameIndex).arg(frameTime.toString("mm:ss.zzz"));
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

	int RectStartX = m_ptMousePos_ActiveMFCCRect.x();
	int RectStartY = m_ptMousePos_ActiveMFCCRect.y();

	QRect bottomAxisRect = getBottomAxisRect();

	if (RectStartX + valStrRectSize.width() > bottomAxisRect.right())
	{
		RectStartX -= valStrRectSize.width();
	}

	if (RectStartY + valStrRectSize.height() > getThisRect().bottom())
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

void TimeSecCht_BDSNR_OpenGL::drawLengend(QPainter& painter, QRect& RightColorMapRect)
{
	int		LengendStrRectWidth = RightColorMapRect.width() - m_nLegendTextMargin - m_szLegend.width() - m_nLegendLeftMargin * 2;

	QPoint  LegendThreshHoldInQuietStartPt = RightColorMapRect.topLeft() + QPoint(m_nLegendLeftMargin, m_nLegendTopMargin);
	QPoint	LegendStrThreshHoldTopLeft = LegendThreshHoldInQuietStartPt + QPoint(20 + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QRect	LegendStrThreshHoldInQuiet = QRect(LegendStrThreshHoldTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));

	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	if (m_bDraw_EffOsc_TIQLine)
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
	case EN_BDSNR_TimeSecChtBarType_GL::STFT:
	{
		QString STFTLegendStr = QString("STFT Val");
		drawCrRectLegend(painter, RightColorMapRect, 0, STFTLegendStr, m_crSTFTOnlyBar);

	}break;
	case EN_BDSNR_TimeSecChtBarType_GL::EffectiveOscillation:
	{
		QString UnderTIQLegendStr = QString("UnderTIQ");
		QString WndSpecNoiseLegendStr = QString("WndSpecNoise");
		QString EffectiveOscillationLegendStr = QString("effectOsc");

		drawCrRectLegend(painter, RightColorMapRect, 0, UnderTIQLegendStr, m_cr_EffOsc_UnderTIQBar);
		drawCrRectLegend(painter, RightColorMapRect, 1, WndSpecNoiseLegendStr, m_cr_EffOsc_WndSpecNoiseBar);
		drawCrRectLegend(painter, RightColorMapRect, 2, EffectiveOscillationLegendStr, m_cr_EffOsc_EffectiveOscillationBar);

	}break;
	case EN_BDSNR_TimeSecChtBarType_GL::BDSNR:
	{
		QString NoiseLegendStr = QString("Noise");
		QString ConstrainLegendStr = QString("Sig_Constrain");
		QString EffMainLegendStr = QString("Sig_Eff_Main");
		QString EffSubLegendStr = QString("Sig_Eff_Sub");
		QString InActFilterLegendStr = QString("Flt_InAct");
		QString ActFilterLegendStr = QString("Flt_Act");
		QString ActFilterMainLegendStr = QString("Flt_Act_Main");
		QString ActFilterSubLegendStr = QString("Flt_Act_Sub");

		drawCrRectLegend(painter, RightColorMapRect, 0, NoiseLegendStr, m_cr_BDSNR_Noise);
		drawCrRectLegend(painter, RightColorMapRect, 1, ConstrainLegendStr, m_cr_BDSNR_Signal_Constrain);
		drawCrRectLegend(painter, RightColorMapRect, 2, EffMainLegendStr, m_cr_BDSNR_Signal_Effective_Main);
		drawCrRectLegend(painter, RightColorMapRect, 3, EffSubLegendStr, m_cr_BDSNR_Signal_Effective_Sub);
		drawCrRectLegend(painter, RightColorMapRect, 4, InActFilterLegendStr, m_cr_BDSNR_ConstrainFilter_InActive);
		drawCrRectLegend(painter, RightColorMapRect, 5, ActFilterLegendStr, m_cr_BDSNR_ConstrainFilter_Active);
		drawCrRectLegend(painter, RightColorMapRect, 6, ActFilterMainLegendStr, m_cr_BDSNR_ConstrainFilterBar_Active_Main);
		drawCrRectLegend(painter, RightColorMapRect, 7, ActFilterSubLegendStr, m_cr_BDSNR_ConstrainFilterBar_Active_Sub);

	}break;
	}
}

void TimeSecCht_BDSNR_OpenGL::drawCrRectLegend(QPainter& painter, QRect& RightColorMapRect, int index, QString text, QColor Cr)
{
	int		LengendStrRectWidth = RightColorMapRect.width() - m_nLegendTextMargin - m_szLegend.width() - m_nLegendLeftMargin * 2;

	QPoint  LegendThreshHoldInQuietStartPt = RightColorMapRect.topLeft() + QPoint(m_nLegendLeftMargin, m_nLegendTopMargin);
	QPoint	LegendRectStartTopLeft = LegendThreshHoldInQuietStartPt + QPoint(0, m_szLegend.height() + m_nLegendSpacing);
	QRect   LegendRect(LegendRectStartTopLeft + QPoint(0, (m_szLegend.height() + m_nLegendSpacing) * index), m_szLegend);
	QPoint	LegendStrTopLeft = LegendRect.topLeft() + QPoint(m_szLegend.width() + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QRect	LegendStrRect = QRect(LegendStrTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));

	painter.setBrush(Cr);
	painter.drawRect(LegendRect);
	painter.drawText(LegendStrRect, Qt::AlignLeft | Qt::AlignVCenter, text);

}

void TimeSecCht_BDSNR_OpenGL::drawPtCount(QPainter& painter, QRect& RightColorMapRect)
{
	int		LengendStrRectWidth = RightColorMapRect.width() - m_nLegendTextMargin - m_szLegend.width() - m_nLegendLeftMargin * 2;

	QPoint  LegendTotalPtCountStartPt = RightColorMapRect.bottomLeft() - QPoint(m_nLegendLeftMargin, m_nLegendTopMargin - m_szLegend.height());
	QPoint	LegendStrTotalPtCountTopLeft = LegendTotalPtCountStartPt + QPoint(20 + m_nLegendTextMargin, (m_szLegend.height() - m_nLegendFontSize) / 2);
	QRect	LegendStrTotalPtCountRect = QRect(LegendStrTotalPtCountTopLeft, QSize(LengendStrRectWidth, m_nLegendFontSize));


	QPen NormalTextPen;
	NormalTextPen.setColor(Qt::black);
	NormalTextPen.setStyle(Qt::SolidLine);
	NormalTextPen.setWidth(1);
	painter.setFont(m_ft_LegendFont);

	int totalPtCount = 0;

	switch (m_showDataType)
	{
	case EN_BDSNR_TimeSecChtBarType_GL::STFT:
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_STFT.size())
		{
			totalPtCount += m_vecFrameBar_STFT[m_ndrawFrameIndex].size();
		}

	}break;
	case EN_BDSNR_TimeSecChtBarType_GL::EffectiveOscillation:
	{
		if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_STFT.size())
		{
			if (m_bDraw_EffOsc_UnderTIQBar)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_UnderTIQ.size())
				{
					totalPtCount += m_vecFrameBar_UnderTIQ[m_ndrawFrameIndex].size();
				}
			}

			if (m_bDraw_EffOsc_WndSpecNoise)
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
	case EN_BDSNR_TimeSecChtBarType_GL::BDSNR:
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

			if (m_bDraw_BDSNR_EffectSubPt)
			{
				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_EffectPt_Sub.size())
				{
					totalPtCount += m_vecFrameBar_BDSNR_EffectPt_Sub[m_ndrawFrameIndex].size();
				}
			}

			if (m_bDraw_BDSNR_ActiveFilter)
			{

				if (m_bDraw_BDSNR_ActiveFilter_Main)
				{
					if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter_Main.size())
					{
						totalPtCount += m_vecFrameBar_BDSNR_ActiveFilter_Main[m_ndrawFrameIndex].size();
					}
				}

				if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_ActiveFilter_Sub.size())
				{
					totalPtCount += m_vecFrameBar_BDSNR_ActiveFilter_Sub[m_ndrawFrameIndex].size();
				}

			}

			if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecDrawBandWidthFilterRect.size())
			{
				totalPtCount += m_vecDrawBandWidthFilterRect[m_ndrawFrameIndex].size();
			}

			if (m_ndrawFrameIndex >= 0 && m_ndrawFrameIndex < m_vecFrameBar_BDSNR_EffectPt_Main.size())
			{
				totalPtCount += m_vecFrameBar_BDSNR_EffectPt_Main[m_ndrawFrameIndex].size();
			}

		}
	}break;
	}

	QString totalPtText = QString("Pt Count : %1").arg(totalPtCount);

	painter.drawText(LegendStrTotalPtCountRect, Qt::AlignLeft | Qt::AlignVCenter, totalPtText);


}