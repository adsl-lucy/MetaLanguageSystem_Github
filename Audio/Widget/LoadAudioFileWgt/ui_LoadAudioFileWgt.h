/********************************************************************************
** Form generated from reading UI file 'LoadAudioFileWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADAUDIOFILEWGT_H
#define UI_LOADAUDIOFILEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadAudioFileWgtClass
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *VLayout_loadWavCht;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_progressState;
    QVBoxLayout *verticalLayout;
    QLabel *label_ffmpegState;
    QLabel *label_ffprobeState;
    QPushButton *btn_selLoadFile;
    QLabel *label_loadState;
    QGroupBox *groupBox_selFileTag;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_selFileName;
    QLabel *label_selFilePath;
    QLabel *label_selFileType;
    QLabel *label_selFileChannelNum;
    QLabel *label_selFileDuration;
    QLabel *label_selFileBitRate;
    QLabel *label_selFileBitrate;
    QLabel *label_selFileBitPerSample;
    QProgressBar *progressBar_loadData;
    QPushButton *btn_loadWavFile;
    QPushButton *btn_transferIntoWavAndLoad;
    QCheckBox *checkBox_autoGenSTFTResult;
    QGroupBox *groupBoxDeviceState;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_currentInputDevice;
    QLabel *label_currentOutputDevice;
    QPushButton *btn_showAudioDeviceDialog;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoadAudioFileWgtClass)
    {
        if (LoadAudioFileWgtClass->objectName().isEmpty())
            LoadAudioFileWgtClass->setObjectName(QString::fromUtf8("LoadAudioFileWgtClass"));
        LoadAudioFileWgtClass->resize(1538, 845);
        horizontalLayout = new QHBoxLayout(LoadAudioFileWgtClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox = new QGroupBox(LoadAudioFileWgtClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 300));
        VLayout_loadWavCht = new QVBoxLayout(groupBox);
        VLayout_loadWavCht->setSpacing(6);
        VLayout_loadWavCht->setContentsMargins(11, 11, 11, 11);
        VLayout_loadWavCht->setObjectName(QString::fromUtf8("VLayout_loadWavCht"));

        verticalLayout_5->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout_5);

        widget = new QWidget(LoadAudioFileWgtClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(200, 0));
        widget->setMaximumSize(QSize(200, 16777215));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
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


        verticalLayout_4->addWidget(groupBox_progressState);

        btn_selLoadFile = new QPushButton(widget);
        btn_selLoadFile->setObjectName(QString::fromUtf8("btn_selLoadFile"));

        verticalLayout_4->addWidget(btn_selLoadFile);

        label_loadState = new QLabel(widget);
        label_loadState->setObjectName(QString::fromUtf8("label_loadState"));

        verticalLayout_4->addWidget(label_loadState);

        groupBox_selFileTag = new QGroupBox(widget);
        groupBox_selFileTag->setObjectName(QString::fromUtf8("groupBox_selFileTag"));
        verticalLayout_2 = new QVBoxLayout(groupBox_selFileTag);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_selFileName = new QLabel(groupBox_selFileTag);
        label_selFileName->setObjectName(QString::fromUtf8("label_selFileName"));

        verticalLayout_2->addWidget(label_selFileName);

        label_selFilePath = new QLabel(groupBox_selFileTag);
        label_selFilePath->setObjectName(QString::fromUtf8("label_selFilePath"));

        verticalLayout_2->addWidget(label_selFilePath);

        label_selFileType = new QLabel(groupBox_selFileTag);
        label_selFileType->setObjectName(QString::fromUtf8("label_selFileType"));

        verticalLayout_2->addWidget(label_selFileType);

        label_selFileChannelNum = new QLabel(groupBox_selFileTag);
        label_selFileChannelNum->setObjectName(QString::fromUtf8("label_selFileChannelNum"));

        verticalLayout_2->addWidget(label_selFileChannelNum);

        label_selFileDuration = new QLabel(groupBox_selFileTag);
        label_selFileDuration->setObjectName(QString::fromUtf8("label_selFileDuration"));

        verticalLayout_2->addWidget(label_selFileDuration);

        label_selFileBitRate = new QLabel(groupBox_selFileTag);
        label_selFileBitRate->setObjectName(QString::fromUtf8("label_selFileBitRate"));

        verticalLayout_2->addWidget(label_selFileBitRate);

        label_selFileBitrate = new QLabel(groupBox_selFileTag);
        label_selFileBitrate->setObjectName(QString::fromUtf8("label_selFileBitrate"));

        verticalLayout_2->addWidget(label_selFileBitrate);

        label_selFileBitPerSample = new QLabel(groupBox_selFileTag);
        label_selFileBitPerSample->setObjectName(QString::fromUtf8("label_selFileBitPerSample"));

        verticalLayout_2->addWidget(label_selFileBitPerSample);


        verticalLayout_4->addWidget(groupBox_selFileTag);

        progressBar_loadData = new QProgressBar(widget);
        progressBar_loadData->setObjectName(QString::fromUtf8("progressBar_loadData"));
        progressBar_loadData->setValue(0);

        verticalLayout_4->addWidget(progressBar_loadData);

        btn_loadWavFile = new QPushButton(widget);
        btn_loadWavFile->setObjectName(QString::fromUtf8("btn_loadWavFile"));
        btn_loadWavFile->setEnabled(false);

        verticalLayout_4->addWidget(btn_loadWavFile);

        btn_transferIntoWavAndLoad = new QPushButton(widget);
        btn_transferIntoWavAndLoad->setObjectName(QString::fromUtf8("btn_transferIntoWavAndLoad"));
        btn_transferIntoWavAndLoad->setEnabled(false);

        verticalLayout_4->addWidget(btn_transferIntoWavAndLoad);

        checkBox_autoGenSTFTResult = new QCheckBox(widget);
        checkBox_autoGenSTFTResult->setObjectName(QString::fromUtf8("checkBox_autoGenSTFTResult"));
        checkBox_autoGenSTFTResult->setChecked(true);

        verticalLayout_4->addWidget(checkBox_autoGenSTFTResult);

        groupBoxDeviceState = new QGroupBox(widget);
        groupBoxDeviceState->setObjectName(QString::fromUtf8("groupBoxDeviceState"));
        verticalLayout_3 = new QVBoxLayout(groupBoxDeviceState);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_currentInputDevice = new QLabel(groupBoxDeviceState);
        label_currentInputDevice->setObjectName(QString::fromUtf8("label_currentInputDevice"));

        verticalLayout_3->addWidget(label_currentInputDevice);

        label_currentOutputDevice = new QLabel(groupBoxDeviceState);
        label_currentOutputDevice->setObjectName(QString::fromUtf8("label_currentOutputDevice"));

        verticalLayout_3->addWidget(label_currentOutputDevice);


        verticalLayout_4->addWidget(groupBoxDeviceState);

        btn_showAudioDeviceDialog = new QPushButton(widget);
        btn_showAudioDeviceDialog->setObjectName(QString::fromUtf8("btn_showAudioDeviceDialog"));

        verticalLayout_4->addWidget(btn_showAudioDeviceDialog);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);


        retranslateUi(LoadAudioFileWgtClass);

        QMetaObject::connectSlotsByName(LoadAudioFileWgtClass);
    } // setupUi

    void retranslateUi(QWidget *LoadAudioFileWgtClass)
    {
        LoadAudioFileWgtClass->setWindowTitle(QApplication::translate("LoadAudioFileWgtClass", "LoadAudioFileWgt", nullptr));
        groupBox->setTitle(QApplication::translate("LoadAudioFileWgtClass", "waveCht", nullptr));
        groupBox_progressState->setTitle(QApplication::translate("LoadAudioFileWgtClass", "\350\277\233\347\250\213\347\212\266\346\200\201", nullptr));
        label_ffmpegState->setText(QApplication::translate("LoadAudioFileWgtClass", "ffmpeg\347\212\266\346\200\201\357\274\232", nullptr));
        label_ffprobeState->setText(QApplication::translate("LoadAudioFileWgtClass", "ffprobe\347\212\266\346\200\201\357\274\232", nullptr));
        btn_selLoadFile->setText(QApplication::translate("LoadAudioFileWgtClass", "\351\200\211\346\213\251\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
        label_loadState->setText(QApplication::translate("LoadAudioFileWgtClass", "\345\257\274\345\205\245\347\212\266\346\200\201\357\274\232", nullptr));
        groupBox_selFileTag->setTitle(QApplication::translate("LoadAudioFileWgtClass", "\346\226\207\344\273\266\346\240\207\347\255\276", nullptr));
        label_selFileName->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_selFilePath->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_selFileType->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\226\207\344\273\266\347\261\273\345\236\213\357\274\232", nullptr));
        label_selFileChannelNum->setText(QApplication::translate("LoadAudioFileWgtClass", "\351\200\232\351\201\223\346\225\260\357\274\232", nullptr));
        label_selFileDuration->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\214\201\347\273\255\346\227\266\351\227\264\357\274\232", nullptr));
        label_selFileBitRate->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\257\224\347\211\271\347\216\207\357\274\232", nullptr));
        label_selFileBitrate->setText(QApplication::translate("LoadAudioFileWgtClass", "\351\207\207\346\240\267\347\216\207\357\274\232", nullptr));
        label_selFileBitPerSample->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\257\224\347\211\271\346\267\261\345\272\246\357\274\232", nullptr));
        btn_loadWavFile->setText(QApplication::translate("LoadAudioFileWgtClass", "\345\257\274\345\205\245wav\346\226\207\344\273\266", nullptr));
        btn_transferIntoWavAndLoad->setText(QApplication::translate("LoadAudioFileWgtClass", "\350\275\254\346\215\242\346\210\220wav\346\240\274\345\274\217\345\271\266\345\257\274\345\205\245", nullptr));
        checkBox_autoGenSTFTResult->setText(QApplication::translate("LoadAudioFileWgtClass", "\350\207\252\345\212\250\350\241\224\346\216\245STFT\345\210\206\346\236\220", nullptr));
        groupBoxDeviceState->setTitle(QApplication::translate("LoadAudioFileWgtClass", "\350\256\276\345\244\207\347\212\266\346\200\201", nullptr));
        label_currentInputDevice->setText(QApplication::translate("LoadAudioFileWgtClass", "\350\276\223\345\205\245\350\256\276\345\244\207\357\274\232", nullptr));
        label_currentOutputDevice->setText(QApplication::translate("LoadAudioFileWgtClass", "\350\276\223\345\207\272\350\256\276\345\244\207\357\274\232", nullptr));
        btn_showAudioDeviceDialog->setText(QApplication::translate("LoadAudioFileWgtClass", "\346\230\276\347\244\272\350\256\276\345\244\207\347\256\241\347\220\206\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadAudioFileWgtClass: public Ui_LoadAudioFileWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADAUDIOFILEWGT_H
