/********************************************************************************
** Form generated from reading UI file 'LoadVedioWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADVEDIOWGT_H
#define UI_LOADVEDIOWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadVedioWgtClass
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_VideoFrame;
    QVBoxLayout *VLayout_LoadVideo;
    QWidget *tab_Audio;
    QVBoxLayout *VLayout_LoadAudio;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_progressState;
    QVBoxLayout *verticalLayout;
    QLabel *label_ffmpegState;
    QLabel *label_ffprobeState;
    QPushButton *btn_selLoadFile;
    QLabel *label_fileTagLoadState;
    QProgressBar *progressBar_fileTagLoadState;
    QGroupBox *groupBox_selFileTag_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_file_FileName;
    QLabel *label_file_Path;
    QLabel *label_file_FileType;
    QLabel *label_file_Duration;
    QFrame *line;
    QLabel *label_video_codec;
    QLabel *label_video_resolution;
    QLabel *label_video_frameRate;
    QLabel *label_video_BitRate;
    QLabel *label_video_pixFmt;
    QLabel *label_video_colorType;
    QFrame *line_2;
    QLabel *label_audio_codec;
    QLabel *label_audio_ChanelNum;
    QLabel *label_audio_sampleRate;
    QLabel *label_audio_Bitrate;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *SBox_LoadFrameRate;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *SBox_LoadPicWidth;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *SBox_LoadPicHeight;
    QPushButton *btn_DecodeAndLoad;
    QPushButton *btn_decodeOnly;
    QPushButton *btn_loadOnly;
    QLabel *label_videoLoadState;
    QProgressBar *progressBar_VideoLoadState;
    QLabel *label_audioLoadState;
    QProgressBar *progressBar_audioLoadState;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoadVedioWgtClass)
    {
        if (LoadVedioWgtClass->objectName().isEmpty())
            LoadVedioWgtClass->setObjectName(QString::fromUtf8("LoadVedioWgtClass"));
        LoadVedioWgtClass->resize(1147, 780);
        horizontalLayout = new QHBoxLayout(LoadVedioWgtClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(LoadVedioWgtClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_VideoFrame = new QWidget();
        tab_VideoFrame->setObjectName(QString::fromUtf8("tab_VideoFrame"));
        VLayout_LoadVideo = new QVBoxLayout(tab_VideoFrame);
        VLayout_LoadVideo->setSpacing(6);
        VLayout_LoadVideo->setContentsMargins(11, 11, 11, 11);
        VLayout_LoadVideo->setObjectName(QString::fromUtf8("VLayout_LoadVideo"));
        tabWidget->addTab(tab_VideoFrame, QString());
        tab_Audio = new QWidget();
        tab_Audio->setObjectName(QString::fromUtf8("tab_Audio"));
        VLayout_LoadAudio = new QVBoxLayout(tab_Audio);
        VLayout_LoadAudio->setSpacing(6);
        VLayout_LoadAudio->setContentsMargins(11, 11, 11, 11);
        VLayout_LoadAudio->setObjectName(QString::fromUtf8("VLayout_LoadAudio"));
        tabWidget->addTab(tab_Audio, QString());

        horizontalLayout_2->addWidget(tabWidget);


        horizontalLayout->addWidget(groupBox);

        widget = new QWidget(LoadVedioWgtClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(240, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_progressState = new QGroupBox(widget);
        groupBox_progressState->setObjectName(QString::fromUtf8("groupBox_progressState"));
        verticalLayout = new QVBoxLayout(groupBox_progressState);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_ffmpegState = new QLabel(groupBox_progressState);
        label_ffmpegState->setObjectName(QString::fromUtf8("label_ffmpegState"));

        verticalLayout->addWidget(label_ffmpegState);

        label_ffprobeState = new QLabel(groupBox_progressState);
        label_ffprobeState->setObjectName(QString::fromUtf8("label_ffprobeState"));

        verticalLayout->addWidget(label_ffprobeState);


        verticalLayout_2->addWidget(groupBox_progressState);

        btn_selLoadFile = new QPushButton(widget);
        btn_selLoadFile->setObjectName(QString::fromUtf8("btn_selLoadFile"));

        verticalLayout_2->addWidget(btn_selLoadFile);

        label_fileTagLoadState = new QLabel(widget);
        label_fileTagLoadState->setObjectName(QString::fromUtf8("label_fileTagLoadState"));

        verticalLayout_2->addWidget(label_fileTagLoadState);

        progressBar_fileTagLoadState = new QProgressBar(widget);
        progressBar_fileTagLoadState->setObjectName(QString::fromUtf8("progressBar_fileTagLoadState"));
        progressBar_fileTagLoadState->setValue(0);

        verticalLayout_2->addWidget(progressBar_fileTagLoadState);

        groupBox_selFileTag_2 = new QGroupBox(widget);
        groupBox_selFileTag_2->setObjectName(QString::fromUtf8("groupBox_selFileTag_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_selFileTag_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_file_FileName = new QLabel(groupBox_selFileTag_2);
        label_file_FileName->setObjectName(QString::fromUtf8("label_file_FileName"));

        verticalLayout_3->addWidget(label_file_FileName);

        label_file_Path = new QLabel(groupBox_selFileTag_2);
        label_file_Path->setObjectName(QString::fromUtf8("label_file_Path"));

        verticalLayout_3->addWidget(label_file_Path);

        label_file_FileType = new QLabel(groupBox_selFileTag_2);
        label_file_FileType->setObjectName(QString::fromUtf8("label_file_FileType"));

        verticalLayout_3->addWidget(label_file_FileType);

        label_file_Duration = new QLabel(groupBox_selFileTag_2);
        label_file_Duration->setObjectName(QString::fromUtf8("label_file_Duration"));

        verticalLayout_3->addWidget(label_file_Duration);

        line = new QFrame(groupBox_selFileTag_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        label_video_codec = new QLabel(groupBox_selFileTag_2);
        label_video_codec->setObjectName(QString::fromUtf8("label_video_codec"));

        verticalLayout_3->addWidget(label_video_codec);

        label_video_resolution = new QLabel(groupBox_selFileTag_2);
        label_video_resolution->setObjectName(QString::fromUtf8("label_video_resolution"));

        verticalLayout_3->addWidget(label_video_resolution);

        label_video_frameRate = new QLabel(groupBox_selFileTag_2);
        label_video_frameRate->setObjectName(QString::fromUtf8("label_video_frameRate"));

        verticalLayout_3->addWidget(label_video_frameRate);

        label_video_BitRate = new QLabel(groupBox_selFileTag_2);
        label_video_BitRate->setObjectName(QString::fromUtf8("label_video_BitRate"));

        verticalLayout_3->addWidget(label_video_BitRate);

        label_video_pixFmt = new QLabel(groupBox_selFileTag_2);
        label_video_pixFmt->setObjectName(QString::fromUtf8("label_video_pixFmt"));

        verticalLayout_3->addWidget(label_video_pixFmt);

        label_video_colorType = new QLabel(groupBox_selFileTag_2);
        label_video_colorType->setObjectName(QString::fromUtf8("label_video_colorType"));

        verticalLayout_3->addWidget(label_video_colorType);

        line_2 = new QFrame(groupBox_selFileTag_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        label_audio_codec = new QLabel(groupBox_selFileTag_2);
        label_audio_codec->setObjectName(QString::fromUtf8("label_audio_codec"));

        verticalLayout_3->addWidget(label_audio_codec);

        label_audio_ChanelNum = new QLabel(groupBox_selFileTag_2);
        label_audio_ChanelNum->setObjectName(QString::fromUtf8("label_audio_ChanelNum"));

        verticalLayout_3->addWidget(label_audio_ChanelNum);

        label_audio_sampleRate = new QLabel(groupBox_selFileTag_2);
        label_audio_sampleRate->setObjectName(QString::fromUtf8("label_audio_sampleRate"));

        verticalLayout_3->addWidget(label_audio_sampleRate);

        label_audio_Bitrate = new QLabel(groupBox_selFileTag_2);
        label_audio_Bitrate->setObjectName(QString::fromUtf8("label_audio_Bitrate"));

        verticalLayout_3->addWidget(label_audio_Bitrate);


        verticalLayout_2->addWidget(groupBox_selFileTag_2);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 120));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        SBox_LoadFrameRate = new QSpinBox(groupBox_2);
        SBox_LoadFrameRate->setObjectName(QString::fromUtf8("SBox_LoadFrameRate"));
        SBox_LoadFrameRate->setValue(30);

        horizontalLayout_3->addWidget(SBox_LoadFrameRate);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        SBox_LoadPicWidth = new QSpinBox(groupBox_2);
        SBox_LoadPicWidth->setObjectName(QString::fromUtf8("SBox_LoadPicWidth"));
        SBox_LoadPicWidth->setMaximum(4080);
        SBox_LoadPicWidth->setValue(1920);

        horizontalLayout_4->addWidget(SBox_LoadPicWidth);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        SBox_LoadPicHeight = new QSpinBox(groupBox_2);
        SBox_LoadPicHeight->setObjectName(QString::fromUtf8("SBox_LoadPicHeight"));
        SBox_LoadPicHeight->setMaximum(4080);
        SBox_LoadPicHeight->setValue(1080);

        horizontalLayout_5->addWidget(SBox_LoadPicHeight);


        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(groupBox_2);

        btn_DecodeAndLoad = new QPushButton(widget);
        btn_DecodeAndLoad->setObjectName(QString::fromUtf8("btn_DecodeAndLoad"));

        verticalLayout_2->addWidget(btn_DecodeAndLoad);

        btn_decodeOnly = new QPushButton(widget);
        btn_decodeOnly->setObjectName(QString::fromUtf8("btn_decodeOnly"));

        verticalLayout_2->addWidget(btn_decodeOnly);

        btn_loadOnly = new QPushButton(widget);
        btn_loadOnly->setObjectName(QString::fromUtf8("btn_loadOnly"));

        verticalLayout_2->addWidget(btn_loadOnly);

        label_videoLoadState = new QLabel(widget);
        label_videoLoadState->setObjectName(QString::fromUtf8("label_videoLoadState"));

        verticalLayout_2->addWidget(label_videoLoadState);

        progressBar_VideoLoadState = new QProgressBar(widget);
        progressBar_VideoLoadState->setObjectName(QString::fromUtf8("progressBar_VideoLoadState"));
        progressBar_VideoLoadState->setValue(0);

        verticalLayout_2->addWidget(progressBar_VideoLoadState);

        label_audioLoadState = new QLabel(widget);
        label_audioLoadState->setObjectName(QString::fromUtf8("label_audioLoadState"));

        verticalLayout_2->addWidget(label_audioLoadState);

        progressBar_audioLoadState = new QProgressBar(widget);
        progressBar_audioLoadState->setObjectName(QString::fromUtf8("progressBar_audioLoadState"));
        progressBar_audioLoadState->setValue(0);

        verticalLayout_2->addWidget(progressBar_audioLoadState);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);


        retranslateUi(LoadVedioWgtClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoadVedioWgtClass);
    } // setupUi

    void retranslateUi(QWidget *LoadVedioWgtClass)
    {
        LoadVedioWgtClass->setWindowTitle(QApplication::translate("LoadVedioWgtClass", "LoadVedioWgt", nullptr));
        groupBox->setTitle(QApplication::translate("LoadVedioWgtClass", "\350\247\206\351\242\221\345\257\274\345\205\245\347\273\223\346\236\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_VideoFrame), QApplication::translate("LoadVedioWgtClass", "\347\224\273\351\235\242\345\270\247\344\277\241\346\201\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Audio), QApplication::translate("LoadVedioWgtClass", "\345\243\260\351\237\263\344\277\241\346\201\257", nullptr));
        groupBox_progressState->setTitle(QApplication::translate("LoadVedioWgtClass", "\350\277\233\347\250\213\347\212\266\346\200\201", nullptr));
        label_ffmpegState->setText(QApplication::translate("LoadVedioWgtClass", "ffmpeg\347\212\266\346\200\201\357\274\232", nullptr));
        label_ffprobeState->setText(QApplication::translate("LoadVedioWgtClass", "ffprobe\347\212\266\346\200\201\357\274\232", nullptr));
        btn_selLoadFile->setText(QApplication::translate("LoadVedioWgtClass", "\351\200\211\346\213\251\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
        label_fileTagLoadState->setText(QApplication::translate("LoadVedioWgtClass", "\346\226\207\344\273\266\345\244\264\350\257\273\345\217\226\347\212\266\346\200\201\357\274\232", nullptr));
        groupBox_selFileTag_2->setTitle(QApplication::translate("LoadVedioWgtClass", "\346\226\207\344\273\266\346\240\207\347\255\276", nullptr));
        label_file_FileName->setText(QApplication::translate("LoadVedioWgtClass", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_file_Path->setText(QApplication::translate("LoadVedioWgtClass", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_file_FileType->setText(QApplication::translate("LoadVedioWgtClass", "\346\226\207\344\273\266\347\261\273\345\236\213\357\274\232", nullptr));
        label_file_Duration->setText(QApplication::translate("LoadVedioWgtClass", "\346\214\201\347\273\255\346\227\266\351\227\264\357\274\232", nullptr));
        label_video_codec->setText(QApplication::translate("LoadVedioWgtClass", "\350\247\206\351\242\221\347\274\226\347\240\201\345\231\250\357\274\232", nullptr));
        label_video_resolution->setText(QApplication::translate("LoadVedioWgtClass", "\345\210\206\350\276\250\347\216\207\357\274\232", nullptr));
        label_video_frameRate->setText(QApplication::translate("LoadVedioWgtClass", "\345\270\247\347\216\207\357\274\232", nullptr));
        label_video_BitRate->setText(QApplication::translate("LoadVedioWgtClass", "\350\247\206\351\242\221\346\257\224\347\211\271\347\216\207\357\274\232", nullptr));
        label_video_pixFmt->setText(QApplication::translate("LoadVedioWgtClass", "\345\203\217\347\264\240\346\240\274\345\274\217\357\274\232", nullptr));
        label_video_colorType->setText(QApplication::translate("LoadVedioWgtClass", "\351\242\234\350\211\262\346\240\274\345\274\217\357\274\232", nullptr));
        label_audio_codec->setText(QApplication::translate("LoadVedioWgtClass", "\351\237\263\351\242\221\347\274\226\347\240\201\345\231\250\357\274\232", nullptr));
        label_audio_ChanelNum->setText(QApplication::translate("LoadVedioWgtClass", "\351\200\232\351\201\223\346\225\260\357\274\232", nullptr));
        label_audio_sampleRate->setText(QApplication::translate("LoadVedioWgtClass", "\351\207\207\346\240\267\347\216\207\357\274\232", nullptr));
        label_audio_Bitrate->setText(QApplication::translate("LoadVedioWgtClass", "\351\237\263\351\242\221\346\257\224\347\211\271\347\216\207\357\274\232", nullptr));
        groupBox_2->setTitle(QApplication::translate("LoadVedioWgtClass", "\345\257\274\345\205\245\345\217\202\346\225\260", nullptr));
        label->setText(QApplication::translate("LoadVedioWgtClass", "\345\270\247\347\216\207", nullptr));
        label_2->setText(QApplication::translate("LoadVedioWgtClass", "\346\234\200\345\244\247\345\256\275\345\272\246", nullptr));
        label_3->setText(QApplication::translate("LoadVedioWgtClass", "\346\234\200\345\244\247\351\253\230\345\272\246", nullptr));
        btn_DecodeAndLoad->setText(QApplication::translate("LoadVedioWgtClass", "\350\247\243\347\240\201\345\271\266\345\257\274\345\205\245\350\247\206\351\242\221", nullptr));
        btn_decodeOnly->setText(QApplication::translate("LoadVedioWgtClass", "\344\273\205\350\247\243\347\240\201", nullptr));
        btn_loadOnly->setText(QApplication::translate("LoadVedioWgtClass", "\344\273\205\345\257\274\345\205\245", nullptr));
        label_videoLoadState->setText(QApplication::translate("LoadVedioWgtClass", "\350\247\206\351\242\221\350\257\273\345\217\226\347\212\266\346\200\201\357\274\232", nullptr));
        label_audioLoadState->setText(QApplication::translate("LoadVedioWgtClass", "\351\237\263\351\242\221\350\257\273\345\217\226\347\212\266\346\200\201\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadVedioWgtClass: public Ui_LoadVedioWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADVEDIOWGT_H
