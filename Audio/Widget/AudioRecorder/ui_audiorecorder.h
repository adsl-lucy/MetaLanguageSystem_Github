/********************************************************************************
** Form generated from reading UI file 'audiorecorder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIORECORDER_H
#define UI_AUDIORECORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioRecorder
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QComboBox *audioDeviceBox;
    QComboBox *sampleRateBox;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label;
    QComboBox *audioCodecBox;
    QComboBox *containerBox;
    QLabel *label_3;
    QLabel *label_2;
    QComboBox *channelsBox;
    QLabel *label_outputDir;
    QPushButton *btn_choseOutputDir;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *constantQualityRadioButton;
    QSpacerItem *horizontalSpacer_2;
    QSlider *qualitySlider;
    QRadioButton *constantBitrateRadioButton;
    QSpacerItem *horizontalSpacer;
    QComboBox *bitrateBox;
    QPushButton *outputButton;
    QPushButton *recordButton;
    QPushButton *pauseButton;
    QLabel *levelLabel;
    QVBoxLayout *levelsLayout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AudioRecorder)
    {
        if (AudioRecorder->objectName().isEmpty())
            AudioRecorder->setObjectName(QString::fromUtf8("AudioRecorder"));
        AudioRecorder->resize(348, 374);
        centralwidget = new QWidget(AudioRecorder);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        audioDeviceBox = new QComboBox(centralwidget);
        audioDeviceBox->setObjectName(QString::fromUtf8("audioDeviceBox"));

        gridLayout_2->addWidget(audioDeviceBox, 0, 1, 1, 1);

        sampleRateBox = new QComboBox(centralwidget);
        sampleRateBox->setObjectName(QString::fromUtf8("sampleRateBox"));

        gridLayout_2->addWidget(sampleRateBox, 3, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        audioCodecBox = new QComboBox(centralwidget);
        audioCodecBox->setObjectName(QString::fromUtf8("audioCodecBox"));

        gridLayout_2->addWidget(audioCodecBox, 1, 1, 1, 1);

        containerBox = new QComboBox(centralwidget);
        containerBox->setObjectName(QString::fromUtf8("containerBox"));

        gridLayout_2->addWidget(containerBox, 2, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        channelsBox = new QComboBox(centralwidget);
        channelsBox->setObjectName(QString::fromUtf8("channelsBox"));

        gridLayout_2->addWidget(channelsBox, 4, 1, 1, 1);

        label_outputDir = new QLabel(centralwidget);
        label_outputDir->setObjectName(QString::fromUtf8("label_outputDir"));

        gridLayout_2->addWidget(label_outputDir, 5, 0, 1, 1);

        btn_choseOutputDir = new QPushButton(centralwidget);
        btn_choseOutputDir->setObjectName(QString::fromUtf8("btn_choseOutputDir"));

        gridLayout_2->addWidget(btn_choseOutputDir, 5, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        constantQualityRadioButton = new QRadioButton(groupBox);
        constantQualityRadioButton->setObjectName(QString::fromUtf8("constantQualityRadioButton"));
        constantQualityRadioButton->setChecked(true);

        gridLayout->addWidget(constantQualityRadioButton, 0, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        qualitySlider = new QSlider(groupBox);
        qualitySlider->setObjectName(QString::fromUtf8("qualitySlider"));
        qualitySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(qualitySlider, 1, 1, 1, 1);

        constantBitrateRadioButton = new QRadioButton(groupBox);
        constantBitrateRadioButton->setObjectName(QString::fromUtf8("constantBitrateRadioButton"));

        gridLayout->addWidget(constantBitrateRadioButton, 2, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        bitrateBox = new QComboBox(groupBox);
        bitrateBox->setObjectName(QString::fromUtf8("bitrateBox"));
        bitrateBox->setEnabled(false);

        gridLayout->addWidget(bitrateBox, 3, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 3);

        outputButton = new QPushButton(centralwidget);
        outputButton->setObjectName(QString::fromUtf8("outputButton"));

        gridLayout_3->addWidget(outputButton, 2, 0, 1, 1);

        recordButton = new QPushButton(centralwidget);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));

        gridLayout_3->addWidget(recordButton, 2, 1, 1, 1);

        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setEnabled(false);

        gridLayout_3->addWidget(pauseButton, 2, 2, 1, 1);

        levelLabel = new QLabel(centralwidget);
        levelLabel->setObjectName(QString::fromUtf8("levelLabel"));

        gridLayout_3->addWidget(levelLabel, 3, 0, 1, 1);

        levelsLayout = new QVBoxLayout();
        levelsLayout->setObjectName(QString::fromUtf8("levelsLayout"));

        gridLayout_3->addLayout(levelsLayout, 3, 1, 1, 2);

        AudioRecorder->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AudioRecorder);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AudioRecorder->setStatusBar(statusbar);

        retranslateUi(AudioRecorder);
        QObject::connect(constantQualityRadioButton, SIGNAL(toggled(bool)), qualitySlider, SLOT(setEnabled(bool)));
        QObject::connect(constantBitrateRadioButton, SIGNAL(toggled(bool)), bitrateBox, SLOT(setEnabled(bool)));
        QObject::connect(outputButton, SIGNAL(clicked()), AudioRecorder, SLOT(setOutputLocation()));
        QObject::connect(recordButton, SIGNAL(clicked()), AudioRecorder, SLOT(toggleRecord()));
        QObject::connect(pauseButton, SIGNAL(clicked()), AudioRecorder, SLOT(togglePause()));

        QMetaObject::connectSlotsByName(AudioRecorder);
    } // setupUi

    void retranslateUi(QMainWindow *AudioRecorder)
    {
        AudioRecorder->setWindowTitle(QApplication::translate("AudioRecorder", "MainWindow", nullptr));
        label_5->setText(QApplication::translate("AudioRecorder", "\351\200\232\351\201\223\346\225\260\351\207\217:", nullptr));
        label_4->setText(QApplication::translate("AudioRecorder", "\351\207\207\346\240\267\347\216\207:", nullptr));
        label->setText(QApplication::translate("AudioRecorder", "\350\276\223\345\205\245\350\256\276\345\244\207:", nullptr));
        label_3->setText(QApplication::translate("AudioRecorder", "\345\256\271\345\231\250:", nullptr));
        label_2->setText(QApplication::translate("AudioRecorder", "\347\274\226\347\240\201\345\231\250:", nullptr));
        label_outputDir->setText(QApplication::translate("AudioRecorder", "\351\273\230\350\256\244\350\276\223\345\207\272\344\275\215\347\275\256\357\274\232", nullptr));
        btn_choseOutputDir->setText(QApplication::translate("AudioRecorder", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        groupBox->setTitle(QApplication::translate("AudioRecorder", "Encoding Mode:", nullptr));
        constantQualityRadioButton->setText(QApplication::translate("AudioRecorder", "Constant Quality:", nullptr));
        constantBitrateRadioButton->setText(QApplication::translate("AudioRecorder", "Constant Bitrate:", nullptr));
        outputButton->setText(QApplication::translate("AudioRecorder", "Output...", nullptr));
        recordButton->setText(QApplication::translate("AudioRecorder", "Record", nullptr));
        pauseButton->setText(QApplication::translate("AudioRecorder", "Pause", nullptr));
        levelLabel->setText(QApplication::translate("AudioRecorder", "Audio Level:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioRecorder: public Ui_AudioRecorder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIORECORDER_H
