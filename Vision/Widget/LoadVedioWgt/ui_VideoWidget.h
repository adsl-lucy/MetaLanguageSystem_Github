/********************************************************************************
** Form generated from reading UI file 'VideoWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWIDGET_H
#define UI_VIDEOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoWidgetClass
{
public:
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *HLayout_VideoFrame;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label_file_FileName;
    QLabel *label_file_Duration;
    QLabel *label_video_codec;
    QLabel *label_video_resolution;
    QLabel *label_video_frameRate;
    QLabel *label_video_BitRate;
    QLabel *label_video_pixFmt;
    QLabel *label_video_colorType;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_totalFrameCount;
    QLabel *label_FrameCount_I;
    QLabel *label_FrameCount_P;
    QLabel *label_FrameCount_B;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_currentFrameIndex;
    QLabel *label_currentFrameType;
    QLabel *label_currentFrameTime;
    QLabel *label_currentFrameDuartion;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_currentFrameTime_2;
    QSlider *HSlider_currentFrameIndex;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_play;
    QPushButton *btn_pause;
    QPushButton *btn_stop;
    QPushButton *btn_nextFrame;
    QPushButton *btn_nextIFrame;
    QPushButton *btn_ExtraWindow;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *VideoWidgetClass)
    {
        if (VideoWidgetClass->objectName().isEmpty())
            VideoWidgetClass->setObjectName(QString::fromUtf8("VideoWidgetClass"));
        VideoWidgetClass->resize(1099, 818);
        verticalLayout_6 = new QVBoxLayout(VideoWidgetClass);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_2 = new QGroupBox(VideoWidgetClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        HLayout_VideoFrame = new QHBoxLayout(groupBox_2);
        HLayout_VideoFrame->setSpacing(6);
        HLayout_VideoFrame->setContentsMargins(11, 11, 11, 11);
        HLayout_VideoFrame->setObjectName(QString::fromUtf8("HLayout_VideoFrame"));

        verticalLayout_6->addWidget(groupBox_2);

        widget = new QWidget(VideoWidgetClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 240));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(160, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_file_FileName = new QLabel(groupBox);
        label_file_FileName->setObjectName(QString::fromUtf8("label_file_FileName"));

        verticalLayout->addWidget(label_file_FileName);

        label_file_Duration = new QLabel(groupBox);
        label_file_Duration->setObjectName(QString::fromUtf8("label_file_Duration"));

        verticalLayout->addWidget(label_file_Duration);

        label_video_codec = new QLabel(groupBox);
        label_video_codec->setObjectName(QString::fromUtf8("label_video_codec"));

        verticalLayout->addWidget(label_video_codec);

        label_video_resolution = new QLabel(groupBox);
        label_video_resolution->setObjectName(QString::fromUtf8("label_video_resolution"));

        verticalLayout->addWidget(label_video_resolution);

        label_video_frameRate = new QLabel(groupBox);
        label_video_frameRate->setObjectName(QString::fromUtf8("label_video_frameRate"));

        verticalLayout->addWidget(label_video_frameRate);

        label_video_BitRate = new QLabel(groupBox);
        label_video_BitRate->setObjectName(QString::fromUtf8("label_video_BitRate"));

        verticalLayout->addWidget(label_video_BitRate);

        label_video_pixFmt = new QLabel(groupBox);
        label_video_pixFmt->setObjectName(QString::fromUtf8("label_video_pixFmt"));

        verticalLayout->addWidget(label_video_pixFmt);

        label_video_colorType = new QLabel(groupBox);
        label_video_colorType->setObjectName(QString::fromUtf8("label_video_colorType"));

        verticalLayout->addWidget(label_video_colorType);


        horizontalLayout_4->addWidget(groupBox);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(160, 0));
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_totalFrameCount = new QLabel(groupBox_4);
        label_totalFrameCount->setObjectName(QString::fromUtf8("label_totalFrameCount"));

        verticalLayout_3->addWidget(label_totalFrameCount);

        label_FrameCount_I = new QLabel(groupBox_4);
        label_FrameCount_I->setObjectName(QString::fromUtf8("label_FrameCount_I"));

        verticalLayout_3->addWidget(label_FrameCount_I);

        label_FrameCount_P = new QLabel(groupBox_4);
        label_FrameCount_P->setObjectName(QString::fromUtf8("label_FrameCount_P"));

        verticalLayout_3->addWidget(label_FrameCount_P);

        label_FrameCount_B = new QLabel(groupBox_4);
        label_FrameCount_B->setObjectName(QString::fromUtf8("label_FrameCount_B"));

        verticalLayout_3->addWidget(label_FrameCount_B);


        verticalLayout_4->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(160, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_currentFrameIndex = new QLabel(groupBox_3);
        label_currentFrameIndex->setObjectName(QString::fromUtf8("label_currentFrameIndex"));

        verticalLayout_2->addWidget(label_currentFrameIndex);

        label_currentFrameType = new QLabel(groupBox_3);
        label_currentFrameType->setObjectName(QString::fromUtf8("label_currentFrameType"));

        verticalLayout_2->addWidget(label_currentFrameType);

        label_currentFrameTime = new QLabel(groupBox_3);
        label_currentFrameTime->setObjectName(QString::fromUtf8("label_currentFrameTime"));

        verticalLayout_2->addWidget(label_currentFrameTime);

        label_currentFrameDuartion = new QLabel(groupBox_3);
        label_currentFrameDuartion->setObjectName(QString::fromUtf8("label_currentFrameDuartion"));

        verticalLayout_2->addWidget(label_currentFrameDuartion);


        verticalLayout_4->addWidget(groupBox_3);


        horizontalLayout_4->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, -1, 0, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, 9, -1);
        label_currentFrameTime_2 = new QLabel(widget);
        label_currentFrameTime_2->setObjectName(QString::fromUtf8("label_currentFrameTime_2"));

        horizontalLayout_2->addWidget(label_currentFrameTime_2);

        HSlider_currentFrameIndex = new QSlider(widget);
        HSlider_currentFrameIndex->setObjectName(QString::fromUtf8("HSlider_currentFrameIndex"));
        HSlider_currentFrameIndex->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(HSlider_currentFrameIndex);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btn_play = new QPushButton(widget);
        btn_play->setObjectName(QString::fromUtf8("btn_play"));

        horizontalLayout_3->addWidget(btn_play);

        btn_pause = new QPushButton(widget);
        btn_pause->setObjectName(QString::fromUtf8("btn_pause"));

        horizontalLayout_3->addWidget(btn_pause);

        btn_stop = new QPushButton(widget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));

        horizontalLayout_3->addWidget(btn_stop);

        btn_nextFrame = new QPushButton(widget);
        btn_nextFrame->setObjectName(QString::fromUtf8("btn_nextFrame"));

        horizontalLayout_3->addWidget(btn_nextFrame);

        btn_nextIFrame = new QPushButton(widget);
        btn_nextIFrame->setObjectName(QString::fromUtf8("btn_nextIFrame"));

        horizontalLayout_3->addWidget(btn_nextIFrame);

        btn_ExtraWindow = new QPushButton(widget);
        btn_ExtraWindow->setObjectName(QString::fromUtf8("btn_ExtraWindow"));

        horizontalLayout_3->addWidget(btn_ExtraWindow);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_5);


        verticalLayout_6->addWidget(widget);


        retranslateUi(VideoWidgetClass);

        QMetaObject::connectSlotsByName(VideoWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *VideoWidgetClass)
    {
        VideoWidgetClass->setWindowTitle(QApplication::translate("VideoWidgetClass", "VideoWidget", nullptr));
        groupBox_2->setTitle(QApplication::translate("VideoWidgetClass", "\345\233\276\345\203\217", nullptr));
        groupBox->setTitle(QApplication::translate("VideoWidgetClass", "\345\257\274\345\205\245\344\277\241\346\201\257", nullptr));
        label_file_FileName->setText(QApplication::translate("VideoWidgetClass", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_file_Duration->setText(QApplication::translate("VideoWidgetClass", "\346\214\201\347\273\255\346\227\266\351\227\264\357\274\232", nullptr));
        label_video_codec->setText(QApplication::translate("VideoWidgetClass", "\350\247\206\351\242\221\347\274\226\347\240\201\345\231\250\357\274\232", nullptr));
        label_video_resolution->setText(QApplication::translate("VideoWidgetClass", "\345\212\240\350\275\275\345\210\206\350\276\250\347\216\207\357\274\232", nullptr));
        label_video_frameRate->setText(QApplication::translate("VideoWidgetClass", "\345\270\247\347\216\207\357\274\232", nullptr));
        label_video_BitRate->setText(QApplication::translate("VideoWidgetClass", "\350\247\206\351\242\221\346\257\224\347\211\271\347\216\207\357\274\232", nullptr));
        label_video_pixFmt->setText(QApplication::translate("VideoWidgetClass", "\345\203\217\347\264\240\346\240\274\345\274\217\357\274\232", nullptr));
        label_video_colorType->setText(QApplication::translate("VideoWidgetClass", "\351\242\234\350\211\262\346\240\274\345\274\217\357\274\232", nullptr));
        groupBox_4->setTitle(QApplication::translate("VideoWidgetClass", "\345\257\274\345\205\245\345\270\247\346\225\264\344\275\223\344\277\241\346\201\257", nullptr));
        label_totalFrameCount->setText(QApplication::translate("VideoWidgetClass", "\346\200\273\345\270\247\346\225\260\357\274\232", nullptr));
        label_FrameCount_I->setText(QApplication::translate("VideoWidgetClass", "I\345\270\247\346\225\260\351\207\217\357\274\232", nullptr));
        label_FrameCount_P->setText(QApplication::translate("VideoWidgetClass", "P\345\270\247\346\225\260\351\207\217\357\274\232", nullptr));
        label_FrameCount_B->setText(QApplication::translate("VideoWidgetClass", "B\345\270\247\346\225\260\351\207\217\357\274\232", nullptr));
        groupBox_3->setTitle(QApplication::translate("VideoWidgetClass", "\345\275\223\345\211\215\345\270\247\344\277\241\346\201\257", nullptr));
        label_currentFrameIndex->setText(QApplication::translate("VideoWidgetClass", "\345\270\247\347\264\242\345\274\225\357\274\232", nullptr));
        label_currentFrameType->setText(QApplication::translate("VideoWidgetClass", "\345\270\247\347\261\273\345\236\213\357\274\232", nullptr));
        label_currentFrameTime->setText(QApplication::translate("VideoWidgetClass", "\345\270\247\346\211\200\345\234\250\346\227\266\351\227\264\357\274\232", nullptr));
        label_currentFrameDuartion->setText(QApplication::translate("VideoWidgetClass", "\345\270\247\346\214\201\347\273\255\346\227\266\351\227\264\357\274\232", nullptr));
        label_currentFrameTime_2->setText(QApplication::translate("VideoWidgetClass", "\345\275\223\345\211\215\346\227\266\351\227\264:00:00:00.000", nullptr));
        btn_play->setText(QApplication::translate("VideoWidgetClass", "play", nullptr));
        btn_pause->setText(QApplication::translate("VideoWidgetClass", "pause", nullptr));
        btn_stop->setText(QApplication::translate("VideoWidgetClass", "stop", nullptr));
        btn_nextFrame->setText(QApplication::translate("VideoWidgetClass", "\344\270\213\344\270\200\345\270\247", nullptr));
        btn_nextIFrame->setText(QApplication::translate("VideoWidgetClass", "\344\270\213\344\270\200\344\270\252I\345\270\247", nullptr));
        btn_ExtraWindow->setText(QApplication::translate("VideoWidgetClass", "\345\274\271\347\252\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoWidgetClass: public Ui_VideoWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWIDGET_H
