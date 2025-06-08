/********************************************************************************
** Form generated from reading UI file 'STFTAnalysePanel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STFTANALYSEPANEL_H
#define UI_STFTANALYSEPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_STFTAnalysePanelClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_HotCht;
    QVBoxLayout *VLayout_STFT_Cht_HotCht;
    QGroupBox *groupBox_HotChtPanel;
    QVBoxLayout *verticalLayout;
    QLabel *label_STFTFileName;
    QLabel *label_DataStartTime;
    QLabel *label_dataEndTime;
    QLabel *label_FFTFreqInterval;
    QLabel *label_STFTGapIntervalMsec;
    QLabel *label_FFTFreqCount;
    QLabel *label_TimeFrameCount;
    QHBoxLayout *horizontalLayout;
    QLabel *label_hotChtStartTime;
    QTimeEdit *timeEdit_hotChtStartTime;
    QLabel *label_hotChtTimeLength;
    QSpinBox *SBox_hotChtTimeLength;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_hotCht_startFreq;
    QSpinBox *SBox_HotChtStartFreq;
    QLabel *label_hotCht_endFreq;
    QSpinBox *SBox_HotchtEndFreq;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_STFT_HotCht_StartDB;
    QSpinBox *SBox_STFT_HotCht_StartDB;
    QLabel *label_STFT_HotCht_endDB;
    QSpinBox *SBox_STFT_HotCht_EndDB;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_HotChtFreqBandWidth;
    QSpinBox *SBox_HotChtFreqBandWidth;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_HotChtTimeIntervalMsec;
    QSpinBox *SBox_HotChtTimeIntervalMsec;
    QLabel *label_HotChtGenState;
    QHBoxLayout *horizontalLayout_16;
    QProgressBar *progressBar_STFT_HotCht_Genstate;
    QPushButton *btn_updateHotCht;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_14;
    QGroupBox *groupBox_3;
    QVBoxLayout *VLayout_STFT_Cht_TimeSection;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_HAxisRange;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_STFT_TimeSec_startFreq;
    QSpinBox *SBox_STFT_TimeSec_startFreq;
    QLabel *label_STFT_TimeSec_endFreq;
    QSpinBox *SBox_STFT_TimeSec_endFreq;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_STFT_TimeSec_StartDB;
    QSpinBox *SBox_STFT_TimeSec_StartDB;
    QLabel *label_STFT_TimeSec_endDB;
    QSpinBox *SBox_STFT_TimeSec_EndDB;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_STFT_TimeSec_BarBandWidth;
    QSpinBox *SBox_STFT_TimeSec_BarBandWidth;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_STFTUpdateTimer;
    QSpinBox *SBox_STFTUpdateTimer;
    QLabel *label_TimeSecGenState;
    QHBoxLayout *horizontalLayout_11;
    QProgressBar *progressBar_STFT_TimeSec_Genstate;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *checkBox_genPhaseSec;
    QPushButton *btn_showPhaseTimeSec;
    QPushButton *btn_updateTimeSecCht;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_15;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_STFTTimeFrameTime;
    QSlider *HSlider_STFTTimeFrameIndex;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_lastFrame;
    QPushButton *btn_nextFrame;
    QPushButton *btn_play;
    QPushButton *btn_stop;
    QPushButton *btn_jump;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_STFT_Frame_startTime;
    QLabel *label_STFT_Frame_midTime;
    QLabel *label_STFT_Frame_endTime;

    void setupUi(QWidget *STFTAnalysePanelClass)
    {
        if (STFTAnalysePanelClass->objectName().isEmpty())
            STFTAnalysePanelClass->setObjectName(QString::fromUtf8("STFTAnalysePanelClass"));
        STFTAnalysePanelClass->resize(1301, 894);
        verticalLayout_4 = new QVBoxLayout(STFTAnalysePanelClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_HotCht = new QGroupBox(STFTAnalysePanelClass);
        groupBox_HotCht->setObjectName(QString::fromUtf8("groupBox_HotCht"));
        VLayout_STFT_Cht_HotCht = new QVBoxLayout(groupBox_HotCht);
        VLayout_STFT_Cht_HotCht->setSpacing(6);
        VLayout_STFT_Cht_HotCht->setContentsMargins(11, 11, 11, 11);
        VLayout_STFT_Cht_HotCht->setObjectName(QString::fromUtf8("VLayout_STFT_Cht_HotCht"));

        horizontalLayout_3->addWidget(groupBox_HotCht);

        groupBox_HotChtPanel = new QGroupBox(STFTAnalysePanelClass);
        groupBox_HotChtPanel->setObjectName(QString::fromUtf8("groupBox_HotChtPanel"));
        groupBox_HotChtPanel->setMaximumSize(QSize(260, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_HotChtPanel);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_STFTFileName = new QLabel(groupBox_HotChtPanel);
        label_STFTFileName->setObjectName(QString::fromUtf8("label_STFTFileName"));
        label_STFTFileName->setMinimumSize(QSize(0, 20));
        label_STFTFileName->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_STFTFileName);

        label_DataStartTime = new QLabel(groupBox_HotChtPanel);
        label_DataStartTime->setObjectName(QString::fromUtf8("label_DataStartTime"));
        label_DataStartTime->setMinimumSize(QSize(0, 20));
        label_DataStartTime->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_DataStartTime);

        label_dataEndTime = new QLabel(groupBox_HotChtPanel);
        label_dataEndTime->setObjectName(QString::fromUtf8("label_dataEndTime"));
        label_dataEndTime->setMinimumSize(QSize(0, 20));
        label_dataEndTime->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_dataEndTime);

        label_FFTFreqInterval = new QLabel(groupBox_HotChtPanel);
        label_FFTFreqInterval->setObjectName(QString::fromUtf8("label_FFTFreqInterval"));
        label_FFTFreqInterval->setMinimumSize(QSize(0, 20));
        label_FFTFreqInterval->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_FFTFreqInterval);

        label_STFTGapIntervalMsec = new QLabel(groupBox_HotChtPanel);
        label_STFTGapIntervalMsec->setObjectName(QString::fromUtf8("label_STFTGapIntervalMsec"));
        label_STFTGapIntervalMsec->setMinimumSize(QSize(0, 20));
        label_STFTGapIntervalMsec->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_STFTGapIntervalMsec);

        label_FFTFreqCount = new QLabel(groupBox_HotChtPanel);
        label_FFTFreqCount->setObjectName(QString::fromUtf8("label_FFTFreqCount"));
        label_FFTFreqCount->setMinimumSize(QSize(0, 20));
        label_FFTFreqCount->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_FFTFreqCount);

        label_TimeFrameCount = new QLabel(groupBox_HotChtPanel);
        label_TimeFrameCount->setObjectName(QString::fromUtf8("label_TimeFrameCount"));
        label_TimeFrameCount->setMinimumSize(QSize(0, 20));
        label_TimeFrameCount->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_TimeFrameCount);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_hotChtStartTime = new QLabel(groupBox_HotChtPanel);
        label_hotChtStartTime->setObjectName(QString::fromUtf8("label_hotChtStartTime"));

        horizontalLayout->addWidget(label_hotChtStartTime);

        timeEdit_hotChtStartTime = new QTimeEdit(groupBox_HotChtPanel);
        timeEdit_hotChtStartTime->setObjectName(QString::fromUtf8("timeEdit_hotChtStartTime"));
        timeEdit_hotChtStartTime->setMinimumSize(QSize(60, 0));
        timeEdit_hotChtStartTime->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(timeEdit_hotChtStartTime);

        label_hotChtTimeLength = new QLabel(groupBox_HotChtPanel);
        label_hotChtTimeLength->setObjectName(QString::fromUtf8("label_hotChtTimeLength"));

        horizontalLayout->addWidget(label_hotChtTimeLength);

        SBox_hotChtTimeLength = new QSpinBox(groupBox_HotChtPanel);
        SBox_hotChtTimeLength->setObjectName(QString::fromUtf8("SBox_hotChtTimeLength"));
        SBox_hotChtTimeLength->setMaximum(20000);
        SBox_hotChtTimeLength->setValue(10000);

        horizontalLayout->addWidget(SBox_hotChtTimeLength);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_hotCht_startFreq = new QLabel(groupBox_HotChtPanel);
        label_hotCht_startFreq->setObjectName(QString::fromUtf8("label_hotCht_startFreq"));

        horizontalLayout_2->addWidget(label_hotCht_startFreq);

        SBox_HotChtStartFreq = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotChtStartFreq->setObjectName(QString::fromUtf8("SBox_HotChtStartFreq"));
        SBox_HotChtStartFreq->setMinimumSize(QSize(60, 0));
        SBox_HotChtStartFreq->setMaximumSize(QSize(60, 16777215));
        SBox_HotChtStartFreq->setMaximum(22100);

        horizontalLayout_2->addWidget(SBox_HotChtStartFreq);

        label_hotCht_endFreq = new QLabel(groupBox_HotChtPanel);
        label_hotCht_endFreq->setObjectName(QString::fromUtf8("label_hotCht_endFreq"));

        horizontalLayout_2->addWidget(label_hotCht_endFreq);

        SBox_HotchtEndFreq = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotchtEndFreq->setObjectName(QString::fromUtf8("SBox_HotchtEndFreq"));
        SBox_HotchtEndFreq->setMinimumSize(QSize(60, 0));
        SBox_HotchtEndFreq->setMaximumSize(QSize(60, 16777215));
        SBox_HotchtEndFreq->setMaximum(22100);
        SBox_HotchtEndFreq->setValue(4500);

        horizontalLayout_2->addWidget(SBox_HotchtEndFreq);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox_6 = new QGroupBox(groupBox_HotChtPanel);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_6);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_STFT_HotCht_StartDB = new QLabel(groupBox_6);
        label_STFT_HotCht_StartDB->setObjectName(QString::fromUtf8("label_STFT_HotCht_StartDB"));

        horizontalLayout_10->addWidget(label_STFT_HotCht_StartDB);

        SBox_STFT_HotCht_StartDB = new QSpinBox(groupBox_6);
        SBox_STFT_HotCht_StartDB->setObjectName(QString::fromUtf8("SBox_STFT_HotCht_StartDB"));
        SBox_STFT_HotCht_StartDB->setMinimum(-20);
        SBox_STFT_HotCht_StartDB->setValue(0);

        horizontalLayout_10->addWidget(SBox_STFT_HotCht_StartDB);

        label_STFT_HotCht_endDB = new QLabel(groupBox_6);
        label_STFT_HotCht_endDB->setObjectName(QString::fromUtf8("label_STFT_HotCht_endDB"));

        horizontalLayout_10->addWidget(label_STFT_HotCht_endDB);

        SBox_STFT_HotCht_EndDB = new QSpinBox(groupBox_6);
        SBox_STFT_HotCht_EndDB->setObjectName(QString::fromUtf8("SBox_STFT_HotCht_EndDB"));
        SBox_STFT_HotCht_EndDB->setValue(80);

        horizontalLayout_10->addWidget(SBox_STFT_HotCht_EndDB);


        verticalLayout->addWidget(groupBox_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_HotChtFreqBandWidth = new QLabel(groupBox_HotChtPanel);
        label_HotChtFreqBandWidth->setObjectName(QString::fromUtf8("label_HotChtFreqBandWidth"));

        horizontalLayout_5->addWidget(label_HotChtFreqBandWidth);

        SBox_HotChtFreqBandWidth = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotChtFreqBandWidth->setObjectName(QString::fromUtf8("SBox_HotChtFreqBandWidth"));
        SBox_HotChtFreqBandWidth->setMinimum(1);
        SBox_HotChtFreqBandWidth->setValue(11);

        horizontalLayout_5->addWidget(SBox_HotChtFreqBandWidth);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_HotChtTimeIntervalMsec = new QLabel(groupBox_HotChtPanel);
        label_HotChtTimeIntervalMsec->setObjectName(QString::fromUtf8("label_HotChtTimeIntervalMsec"));

        horizontalLayout_6->addWidget(label_HotChtTimeIntervalMsec);

        SBox_HotChtTimeIntervalMsec = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotChtTimeIntervalMsec->setObjectName(QString::fromUtf8("SBox_HotChtTimeIntervalMsec"));
        SBox_HotChtTimeIntervalMsec->setMinimum(1);
        SBox_HotChtTimeIntervalMsec->setValue(20);

        horizontalLayout_6->addWidget(SBox_HotChtTimeIntervalMsec);


        verticalLayout->addLayout(horizontalLayout_6);

        label_HotChtGenState = new QLabel(groupBox_HotChtPanel);
        label_HotChtGenState->setObjectName(QString::fromUtf8("label_HotChtGenState"));

        verticalLayout->addWidget(label_HotChtGenState);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        progressBar_STFT_HotCht_Genstate = new QProgressBar(groupBox_HotChtPanel);
        progressBar_STFT_HotCht_Genstate->setObjectName(QString::fromUtf8("progressBar_STFT_HotCht_Genstate"));
        progressBar_STFT_HotCht_Genstate->setValue(0);

        horizontalLayout_16->addWidget(progressBar_STFT_HotCht_Genstate);


        verticalLayout->addLayout(horizontalLayout_16);

        btn_updateHotCht = new QPushButton(groupBox_HotChtPanel);
        btn_updateHotCht->setObjectName(QString::fromUtf8("btn_updateHotCht"));

        verticalLayout->addWidget(btn_updateHotCht);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(groupBox_HotChtPanel);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        groupBox_3 = new QGroupBox(STFTAnalysePanelClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 300));
        groupBox_3->setMaximumSize(QSize(16777215, 16777215));
        VLayout_STFT_Cht_TimeSection = new QVBoxLayout(groupBox_3);
        VLayout_STFT_Cht_TimeSection->setSpacing(6);
        VLayout_STFT_Cht_TimeSection->setContentsMargins(11, 11, 11, 11);
        VLayout_STFT_Cht_TimeSection->setObjectName(QString::fromUtf8("VLayout_STFT_Cht_TimeSection"));

        horizontalLayout_14->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(STFTAnalysePanelClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(260, 0));
        groupBox_4->setMaximumSize(QSize(260, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_HAxisRange = new QGroupBox(groupBox_4);
        groupBox_HAxisRange->setObjectName(QString::fromUtf8("groupBox_HAxisRange"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_HAxisRange);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_STFT_TimeSec_startFreq = new QLabel(groupBox_HAxisRange);
        label_STFT_TimeSec_startFreq->setObjectName(QString::fromUtf8("label_STFT_TimeSec_startFreq"));

        horizontalLayout_4->addWidget(label_STFT_TimeSec_startFreq);

        SBox_STFT_TimeSec_startFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_STFT_TimeSec_startFreq->setObjectName(QString::fromUtf8("SBox_STFT_TimeSec_startFreq"));
        SBox_STFT_TimeSec_startFreq->setMaximum(22100);

        horizontalLayout_4->addWidget(SBox_STFT_TimeSec_startFreq);

        label_STFT_TimeSec_endFreq = new QLabel(groupBox_HAxisRange);
        label_STFT_TimeSec_endFreq->setObjectName(QString::fromUtf8("label_STFT_TimeSec_endFreq"));

        horizontalLayout_4->addWidget(label_STFT_TimeSec_endFreq);

        SBox_STFT_TimeSec_endFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_STFT_TimeSec_endFreq->setObjectName(QString::fromUtf8("SBox_STFT_TimeSec_endFreq"));
        SBox_STFT_TimeSec_endFreq->setMaximum(22100);
        SBox_STFT_TimeSec_endFreq->setValue(4500);

        horizontalLayout_4->addWidget(SBox_STFT_TimeSec_endFreq);


        verticalLayout_2->addWidget(groupBox_HAxisRange);

        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_2);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_STFT_TimeSec_StartDB = new QLabel(groupBox_2);
        label_STFT_TimeSec_StartDB->setObjectName(QString::fromUtf8("label_STFT_TimeSec_StartDB"));

        horizontalLayout_8->addWidget(label_STFT_TimeSec_StartDB);

        SBox_STFT_TimeSec_StartDB = new QSpinBox(groupBox_2);
        SBox_STFT_TimeSec_StartDB->setObjectName(QString::fromUtf8("SBox_STFT_TimeSec_StartDB"));
        SBox_STFT_TimeSec_StartDB->setMinimum(-20);
        SBox_STFT_TimeSec_StartDB->setValue(0);

        horizontalLayout_8->addWidget(SBox_STFT_TimeSec_StartDB);

        label_STFT_TimeSec_endDB = new QLabel(groupBox_2);
        label_STFT_TimeSec_endDB->setObjectName(QString::fromUtf8("label_STFT_TimeSec_endDB"));

        horizontalLayout_8->addWidget(label_STFT_TimeSec_endDB);

        SBox_STFT_TimeSec_EndDB = new QSpinBox(groupBox_2);
        SBox_STFT_TimeSec_EndDB->setObjectName(QString::fromUtf8("SBox_STFT_TimeSec_EndDB"));
        SBox_STFT_TimeSec_EndDB->setValue(80);

        horizontalLayout_8->addWidget(SBox_STFT_TimeSec_EndDB);


        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_STFT_TimeSec_BarBandWidth = new QLabel(groupBox_4);
        label_STFT_TimeSec_BarBandWidth->setObjectName(QString::fromUtf8("label_STFT_TimeSec_BarBandWidth"));

        horizontalLayout_12->addWidget(label_STFT_TimeSec_BarBandWidth);

        SBox_STFT_TimeSec_BarBandWidth = new QSpinBox(groupBox_4);
        SBox_STFT_TimeSec_BarBandWidth->setObjectName(QString::fromUtf8("SBox_STFT_TimeSec_BarBandWidth"));
        SBox_STFT_TimeSec_BarBandWidth->setMinimum(1);
        SBox_STFT_TimeSec_BarBandWidth->setMaximum(22100);
        SBox_STFT_TimeSec_BarBandWidth->setValue(11);

        horizontalLayout_12->addWidget(SBox_STFT_TimeSec_BarBandWidth);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_STFTUpdateTimer = new QLabel(groupBox_4);
        label_STFTUpdateTimer->setObjectName(QString::fromUtf8("label_STFTUpdateTimer"));

        horizontalLayout_7->addWidget(label_STFTUpdateTimer);

        SBox_STFTUpdateTimer = new QSpinBox(groupBox_4);
        SBox_STFTUpdateTimer->setObjectName(QString::fromUtf8("SBox_STFTUpdateTimer"));
        SBox_STFTUpdateTimer->setMinimum(1);
        SBox_STFTUpdateTimer->setMaximum(200);
        SBox_STFTUpdateTimer->setValue(20);

        horizontalLayout_7->addWidget(SBox_STFTUpdateTimer);


        verticalLayout_2->addLayout(horizontalLayout_7);

        label_TimeSecGenState = new QLabel(groupBox_4);
        label_TimeSecGenState->setObjectName(QString::fromUtf8("label_TimeSecGenState"));

        verticalLayout_2->addWidget(label_TimeSecGenState);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        progressBar_STFT_TimeSec_Genstate = new QProgressBar(groupBox_4);
        progressBar_STFT_TimeSec_Genstate->setObjectName(QString::fromUtf8("progressBar_STFT_TimeSec_Genstate"));
        progressBar_STFT_TimeSec_Genstate->setValue(0);

        horizontalLayout_11->addWidget(progressBar_STFT_TimeSec_Genstate);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        checkBox_genPhaseSec = new QCheckBox(groupBox_4);
        checkBox_genPhaseSec->setObjectName(QString::fromUtf8("checkBox_genPhaseSec"));

        horizontalLayout_17->addWidget(checkBox_genPhaseSec);

        btn_showPhaseTimeSec = new QPushButton(groupBox_4);
        btn_showPhaseTimeSec->setObjectName(QString::fromUtf8("btn_showPhaseTimeSec"));

        horizontalLayout_17->addWidget(btn_showPhaseTimeSec);


        verticalLayout_2->addLayout(horizontalLayout_17);

        btn_updateTimeSecCht = new QPushButton(groupBox_4);
        btn_updateTimeSecCht->setObjectName(QString::fromUtf8("btn_updateTimeSecCht"));

        verticalLayout_2->addWidget(btn_updateTimeSecCht);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_14->addWidget(groupBox_4);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        groupBox_5 = new QGroupBox(STFTAnalysePanelClass);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_6 = new QVBoxLayout(groupBox_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_STFTTimeFrameTime = new QLabel(groupBox_5);
        label_STFTTimeFrameTime->setObjectName(QString::fromUtf8("label_STFTTimeFrameTime"));

        horizontalLayout_9->addWidget(label_STFTTimeFrameTime);

        HSlider_STFTTimeFrameIndex = new QSlider(groupBox_5);
        HSlider_STFTTimeFrameIndex->setObjectName(QString::fromUtf8("HSlider_STFTTimeFrameIndex"));
        HSlider_STFTTimeFrameIndex->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(HSlider_STFTTimeFrameIndex);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        btn_lastFrame = new QPushButton(groupBox_5);
        btn_lastFrame->setObjectName(QString::fromUtf8("btn_lastFrame"));
        btn_lastFrame->setMinimumSize(QSize(24, 0));
        btn_lastFrame->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_13->addWidget(btn_lastFrame);

        btn_nextFrame = new QPushButton(groupBox_5);
        btn_nextFrame->setObjectName(QString::fromUtf8("btn_nextFrame"));
        btn_nextFrame->setMinimumSize(QSize(24, 0));
        btn_nextFrame->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_13->addWidget(btn_nextFrame);

        btn_play = new QPushButton(groupBox_5);
        btn_play->setObjectName(QString::fromUtf8("btn_play"));

        horizontalLayout_13->addWidget(btn_play);

        btn_stop = new QPushButton(groupBox_5);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));

        horizontalLayout_13->addWidget(btn_stop);

        btn_jump = new QPushButton(groupBox_5);
        btn_jump->setObjectName(QString::fromUtf8("btn_jump"));

        horizontalLayout_13->addWidget(btn_jump);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_13);


        verticalLayout_6->addLayout(verticalLayout_3);


        horizontalLayout_15->addWidget(groupBox_5);

        groupBox = new QGroupBox(STFTAnalysePanelClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(260, 0));
        groupBox->setMaximumSize(QSize(260, 16777215));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_STFT_Frame_startTime = new QLabel(groupBox);
        label_STFT_Frame_startTime->setObjectName(QString::fromUtf8("label_STFT_Frame_startTime"));

        verticalLayout_5->addWidget(label_STFT_Frame_startTime);

        label_STFT_Frame_midTime = new QLabel(groupBox);
        label_STFT_Frame_midTime->setObjectName(QString::fromUtf8("label_STFT_Frame_midTime"));

        verticalLayout_5->addWidget(label_STFT_Frame_midTime);

        label_STFT_Frame_endTime = new QLabel(groupBox);
        label_STFT_Frame_endTime->setObjectName(QString::fromUtf8("label_STFT_Frame_endTime"));

        verticalLayout_5->addWidget(label_STFT_Frame_endTime);


        horizontalLayout_15->addWidget(groupBox);


        verticalLayout_4->addLayout(horizontalLayout_15);


        retranslateUi(STFTAnalysePanelClass);

        QMetaObject::connectSlotsByName(STFTAnalysePanelClass);
    } // setupUi

    void retranslateUi(QWidget *STFTAnalysePanelClass)
    {
        STFTAnalysePanelClass->setWindowTitle(QApplication::translate("STFTAnalysePanelClass", "STFTAnalysePanel", nullptr));
        groupBox_HotCht->setTitle(QApplication::translate("STFTAnalysePanelClass", "\346\225\264\344\275\223\347\273\223\346\236\234", nullptr));
        groupBox_HotChtPanel->setTitle(QApplication::translate("STFTAnalysePanelClass", "\347\203\255\345\212\233\345\233\276\346\216\247\345\210\266", nullptr));
        label_STFTFileName->setText(QApplication::translate("STFTAnalysePanelClass", "\346\226\207\344\273\266\345\220\215\347\247\260", nullptr));
        label_DataStartTime->setText(QApplication::translate("STFTAnalysePanelClass", "\346\225\260\346\215\256\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_dataEndTime->setText(QApplication::translate("STFTAnalysePanelClass", "\346\225\260\346\215\256\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label_FFTFreqInterval->setText(QApplication::translate("STFTAnalysePanelClass", "FFT\351\242\221\347\216\207\351\227\264\351\232\224", nullptr));
        label_STFTGapIntervalMsec->setText(QApplication::translate("STFTAnalysePanelClass", "STFT\346\255\245\351\225\277\357\274\232", nullptr));
        label_FFTFreqCount->setText(QApplication::translate("STFTAnalysePanelClass", "\351\242\221\347\216\207\347\202\271\346\225\260", nullptr));
        label_TimeFrameCount->setText(QApplication::translate("STFTAnalysePanelClass", "\346\227\266\351\227\264\347\202\271\346\225\260", nullptr));
        label_hotChtStartTime->setText(QApplication::translate("STFTAnalysePanelClass", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeEdit_hotChtStartTime->setDisplayFormat(QApplication::translate("STFTAnalysePanelClass", "mm:ss", nullptr));
        label_hotChtTimeLength->setText(QApplication::translate("STFTAnalysePanelClass", "\347\252\227\345\217\243\351\225\277\345\272\246", nullptr));
        label_hotCht_startFreq->setText(QApplication::translate("STFTAnalysePanelClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_hotCht_endFreq->setText(QApplication::translate("STFTAnalysePanelClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_6->setTitle(QApplication::translate("STFTAnalysePanelClass", "\351\242\234\350\211\262\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_STFT_HotCht_StartDB->setText(QApplication::translate("STFTAnalysePanelClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_STFT_HotCht_endDB->setText(QApplication::translate("STFTAnalysePanelClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_HotChtFreqBandWidth->setText(QApplication::translate("STFTAnalysePanelClass", "\351\242\221\347\216\207\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_HotChtTimeIntervalMsec->setText(QApplication::translate("STFTAnalysePanelClass", "\346\227\266\351\227\264\345\270\246\345\256\275\357\274\210ms\357\274\211", nullptr));
        label_HotChtGenState->setText(QApplication::translate("STFTAnalysePanelClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateHotCht->setText(QApplication::translate("STFTAnalysePanelClass", "\345\210\267\346\226\260", nullptr));
        groupBox_3->setTitle(QApplication::translate("STFTAnalysePanelClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_4->setTitle(QApplication::translate("STFTAnalysePanelClass", "\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276\346\216\247\345\210\266", nullptr));
        groupBox_HAxisRange->setTitle(QApplication::translate("STFTAnalysePanelClass", "\346\250\252\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210hz\357\274\211", nullptr));
        label_STFT_TimeSec_startFreq->setText(QApplication::translate("STFTAnalysePanelClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_STFT_TimeSec_endFreq->setText(QApplication::translate("STFTAnalysePanelClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_2->setTitle(QApplication::translate("STFTAnalysePanelClass", "\347\272\265\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_STFT_TimeSec_StartDB->setText(QApplication::translate("STFTAnalysePanelClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_STFT_TimeSec_endDB->setText(QApplication::translate("STFTAnalysePanelClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_STFT_TimeSec_BarBandWidth->setText(QApplication::translate("STFTAnalysePanelClass", "\351\242\221\347\216\207\346\240\274\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_STFTUpdateTimer->setText(QApplication::translate("STFTAnalysePanelClass", "\345\270\247\345\210\267\346\226\260\351\227\264\351\232\224(ms)", nullptr));
        label_TimeSecGenState->setText(QApplication::translate("STFTAnalysePanelClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        checkBox_genPhaseSec->setText(QApplication::translate("STFTAnalysePanelClass", "\347\224\237\346\210\220\347\233\270\344\275\215\345\233\276", nullptr));
        btn_showPhaseTimeSec->setText(QApplication::translate("STFTAnalysePanelClass", "\346\230\276\347\244\272\347\233\270\344\275\215\345\233\276", nullptr));
        btn_updateTimeSecCht->setText(QApplication::translate("STFTAnalysePanelClass", "\345\210\267\346\226\260", nullptr));
        groupBox_5->setTitle(QApplication::translate("STFTAnalysePanelClass", "\346\227\266\351\227\264\346\216\247\345\210\266", nullptr));
        label_STFTTimeFrameTime->setText(QApplication::translate("STFTAnalysePanelClass", "\346\210\252\351\235\242\346\227\266\351\227\264\357\274\23200\357\274\23200.000", nullptr));
        btn_lastFrame->setText(QApplication::translate("STFTAnalysePanelClass", "<", nullptr));
        btn_nextFrame->setText(QApplication::translate("STFTAnalysePanelClass", ">", nullptr));
        btn_play->setText(QApplication::translate("STFTAnalysePanelClass", "\346\222\255\346\224\276", nullptr));
        btn_stop->setText(QApplication::translate("STFTAnalysePanelClass", "\345\201\234\346\255\242", nullptr));
        btn_jump->setText(QApplication::translate("STFTAnalysePanelClass", "\350\267\263\350\275\254", nullptr));
        groupBox->setTitle(QApplication::translate("STFTAnalysePanelClass", "\346\227\266\351\227\264\347\225\214\351\235\242\345\270\247\344\277\241\346\201\257", nullptr));
        label_STFT_Frame_startTime->setText(QApplication::translate("STFTAnalysePanelClass", "\346\210\252\351\235\242\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_STFT_Frame_midTime->setText(QApplication::translate("STFTAnalysePanelClass", "\346\210\252\351\235\242\344\270\255\345\277\203\346\227\266\351\227\264", nullptr));
        label_STFT_Frame_endTime->setText(QApplication::translate("STFTAnalysePanelClass", "\346\210\252\351\235\242\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class STFTAnalysePanelClass: public Ui_STFTAnalysePanelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STFTANALYSEPANEL_H
