#include "VideoWidget.h"
#pragma execution_character_set("utf-8")

VideoWidget::VideoWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUI();
	initUpdateTimer();
	initFrameWidget();
}

VideoWidget::~VideoWidget()
{}

void VideoWidget::initUI()
{
	connect(ui.btn_play, &QPushButton::clicked, this, &VideoWidget::slot_play);
	connect(ui.btn_pause, &QPushButton::clicked, this, &VideoWidget::slot_pause);
	connect(ui.btn_stop, &QPushButton::clicked, this, &VideoWidget::slot_stop);
	connect(ui.btn_nextFrame, &QPushButton::clicked, this, &VideoWidget::slot_nextFrame);
	connect(ui.btn_nextIFrame, &QPushButton::clicked, this, &VideoWidget::slot_nextIFrame);
	connect(ui.btn_ExtraWindow, &QPushButton::clicked, this, &VideoWidget::slot_btnExtraWindowClicked);

	connect(ui.HSlider_currentFrameIndex, &QSlider::sliderMoved, this, &VideoWidget::slot_FrameIndexSliderMoved);
}

void VideoWidget::initUpdateTimer()
{
	m_pUpdateFrameTimer = new QTimer(this);
	m_pUpdateFrameTimer->setSingleShot(false);
	m_pUpdateFrameTimer->setTimerType(Qt::PreciseTimer);

	connect(m_pUpdateFrameTimer, &QTimer::timeout, this, &VideoWidget::slot_UpdateTimerTimeout);
}

void VideoWidget::initFrameWidget()
{
	m_pVideoFrameWidget = new VideoFrameWidget(this);
	ui.HLayout_VideoFrame->insertWidget(0, m_pVideoFrameWidget);

	m_pExtraFrameWindow = new VideoFrameWidget(nullptr);
	m_pExtraFrameWindow->hide();
	connect(m_pExtraFrameWindow, &VideoFrameWidget::sgn_windowHide, this, &VideoWidget::slot_FrameWindowHide);
}

void VideoWidget::printVideoTagInfo(const ST_VideoFileTag& vedioFileTag, const ST_VideoLoadSetting& loadSetting)
{
	ui.label_file_FileName->setText(QString("文件名：%1").arg(vedioFileTag.fileName));
	ui.label_file_Duration->setText(QString("持续时间：%1").arg(vedioFileTag.Duration.toString("hh:mm:ss")));
	ui.label_video_codec->setText(QString("视频编码器：%1").arg(vedioFileTag.codec));

	QString resolutionStr = QString("%1 %2").arg(loadSetting.loadFrameSize.width()).arg(loadSetting.loadFrameSize.height());

	ui.label_video_resolution->setText(QString("加载分辨率：%1").arg(resolutionStr));
	ui.label_video_frameRate->setText(QString("帧率：%1").arg(loadSetting.loadFrameRate));
	ui.label_video_BitRate->setText(QString("视频比特率：%1").arg(vedioFileTag.BitRate));
	ui.label_video_pixFmt->setText(QString("像素格式：%1").arg(vedioFileTag.pixelFormat));
	ui.label_video_colorType->setText(QString("颜色格式：%1").arg(vedioFileTag.colorDecodeType));

	ui.label_totalFrameCount->setText(QString("总帧数：%1").arg(loadSetting.LoadFrameCount));
	ui.label_FrameCount_I->setText(QString("I帧数量：%1").arg(loadSetting.LoadFrameCount_I));
	ui.label_FrameCount_P->setText(QString("P帧数量：%1").arg(loadSetting.LoadFrameCount_P));
	ui.label_FrameCount_B->setText(QString("B帧数量：%1").arg(loadSetting.LoadFrameCount_B));
}

void VideoWidget::slot_FrameIndexSliderMoved(int index)
{
	int FrameCount = FFMpegManager::instance()->getTempVideoDataVecRef().size();
	if (index < 0 || index >= FrameCount)
	{
		return;
	}

	if (m_bLoadFrameOnWindow)
	{
		m_pExtraFrameWindow->loadFrame(index);
	}
	else
	{
		m_pVideoFrameWidget->loadFrame(index);
	}
	
	printCurrentFrameInfo(index);
}

void VideoWidget::printCurrentFrameInfo(int index)
{
	ST_VideoFileTag& VideoFileTag = FFMpegManager::instance()->getTmepVideoFileTag();
	ST_VideoH264FrameTag& frameTag = FFMpegManager::instance()->getVideoFrameTagRef(index);
	int currentMSec = frameTag.FrameTime_sec * 1000;
	QTime currentFrameTime = QTime(0, 0, 0).addMSecs(currentMSec);
	int durationMsec = frameTag.duration_sec * 1000;
	
	ui.label_currentFrameIndex->setText(QString("帧索引：%1").arg(index));
	ui.label_currentFrameType->setText(QString("帧类型：%1").arg(VisionProtocol::FrameTypeToStr(frameTag.frameType)));
	ui.label_currentFrameTime->setText(QString("帧所在时间：%1").arg(currentFrameTime.toString("mm:ss.zzz")));
	ui.label_currentFrameDuartion->setText(QString("帧持续时间：%1").arg(durationMsec));
	ui.label_currentFrameTime_2->setText(QString("当前时间:%1").arg(currentFrameTime.toString("hh:mm:ss.zzz")));

	if (m_bLoadFrameOnWindow)
	{
		m_pExtraFrameWindow->setWindowTitle(QString("VideoWidget : File : %1 FrameType : %2 Frame index : %3 FrameTime : %4")
			.arg(VideoFileTag.fileName).arg(VisionProtocol::FrameTypeToStr(frameTag.frameType)).arg(index).arg(currentFrameTime.toString("mm:ss.zzz")));
	}
	

}

void VideoWidget::loadVideoFrame(const ST_VideoFileTag& fileTag, const ST_VideoLoadSetting& loadSetting)
{
	if (fileTag.FrameCount <= 0)
	{
		return;
	}

	m_currentFileTag = fileTag;
	m_VideoLoadSetting = loadSetting;

	m_pVideoFrameWidget->setVideoFrameTag(fileTag, loadSetting);
	m_pExtraFrameWindow->setVideoFrameTag(fileTag, loadSetting);

	ui.HSlider_currentFrameIndex->setMaximum(loadSetting.LoadFrameCount);
	ui.HSlider_currentFrameIndex->setMinimum(0);
	ui.HSlider_currentFrameIndex->setValue(0);

}

void VideoWidget::slot_play()
{
	m_nUpdateMsec = 1.0 / (double)m_VideoLoadSetting.loadFrameRate * 1000;
	m_nCurrentFrame = 0;
	ui.HSlider_currentFrameIndex->setValue(m_nCurrentFrame);
	slot_FrameIndexSliderMoved(m_nCurrentFrame);
	m_pUpdateFrameTimer->setInterval(m_nUpdateMsec);
	m_pUpdateFrameTimer->start();
	emit sgn_playVideo();
}

void VideoWidget::slot_pause()
{

}

void VideoWidget::slot_stop()
{
	m_pUpdateFrameTimer->stop();
	emit sgn_stopVideo();
}

void VideoWidget::slot_nextFrame()
{
	m_nCurrentFrame += 1;
	if (m_nCurrentFrame >= m_currentFileTag.FrameCount)
	{
		m_nCurrentFrame = m_currentFileTag.FrameCount - 1;
	}
	ui.HSlider_currentFrameIndex->setValue(m_nCurrentFrame);
	slot_FrameIndexSliderMoved(m_nCurrentFrame);
}
void VideoWidget::slot_nextIFrame()
{
	QVector<ST_VideoH264Frame>& vecRef = FFMpegManager::instance()->getTempVideoDataVecRef();
	if (vecRef.isEmpty())
	{
		return;
	}
	else if (m_nCurrentFrame < 0 || m_nCurrentFrame + 1 >= vecRef.size())
	{
		return;
	}


	for (int currentFrameIndex = m_nCurrentFrame + 1; currentFrameIndex < vecRef.size(); currentFrameIndex++)
	{
		ST_VideoH264FrameTag& FramTag = vecRef[currentFrameIndex].FrameTag;
		if (FramTag.frameType != EN_VideoH264FrameType::I)
		{
			continue;
		}
		else
		{
			m_nCurrentFrame = currentFrameIndex;
			ui.HSlider_currentFrameIndex->setValue(m_nCurrentFrame);
			slot_FrameIndexSliderMoved(m_nCurrentFrame);
			return;
		}
	}
	QMessageBox::information(this, QString("I帧搜索失败"), QString("当前帧后没有I帧"),QMessageBox::Yes);
}

void VideoWidget::slot_UpdateTimerTimeout()
{
	m_nCurrentFrame += 1;
	if (m_nCurrentFrame >= m_currentFileTag.FrameCount)
	{
		slot_stop();
		return;
	}

	ui.HSlider_currentFrameIndex->setValue(m_nCurrentFrame);
	slot_FrameIndexSliderMoved(m_nCurrentFrame);
}

void VideoWidget::slot_btnExtraWindowClicked()
{
	m_pExtraFrameWindow->show();
	m_pExtraFrameWindow->resize(this->size());
	m_pExtraFrameWindow->loadFrame(m_nCurrentFrame);
	ui.btn_ExtraWindow->setEnabled(false);
	m_bLoadFrameOnWindow = true;
	m_pVideoFrameWidget->loadFrame(-1);
}

void VideoWidget::slot_FrameWindowHide()
{
	m_bLoadFrameOnWindow = false;
	m_pExtraFrameWindow->loadFrame(-1);
	ui.btn_ExtraWindow->setEnabled(true);
	m_pVideoFrameWidget->loadFrame(m_nCurrentFrame);
}
