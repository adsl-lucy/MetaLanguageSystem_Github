/********************************************************************************
** Form generated from reading UI file 'STFTWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STFTWGT_H
#define UI_STFTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_STFTWgtClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_STFTPara;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *VLayout_Cht_Sig;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_SigFrom;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioBtn_SigFrom_Gen;
    QRadioButton *radioBtn_SigFrom_Wav;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_GenSig;
    QComboBox *comboBox_GenSig;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_WavSig;
    QComboBox *comboBox_WavSig;
    QLabel *label_SigChnNum;
    QLabel *label_SigDuration;
    QLabel *label_SigPotintCount;
    QLabel *label_SigSampleRate;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_dataLoadState;
    QProgressBar *progressBar_dataLoadState;
    QPushButton *btn_loadSig;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *VLayout_Cht_STFTWnd;
    QWidget *widget;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioBtn_Wnd_Null;
    QRadioButton *radioBtn_Wnd_Hann;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radioBtn_WndLengthType_Point;
    QRadioButton *radioBtn_WndLengthType_Time;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_WndLengthPoint;
    QSpinBox *SBox_WndLengthPointCount;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_WndLength_Time;
    QDoubleSpinBox *DSBox_WndLength_TimeMSec;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_WndSampleRate;
    QSpinBox *SBox_WndSampleRate;
    QLabel *label_resultWndLength_Point;
    QLabel *label_resultWndLength_Time;
    QPushButton *btn_GenWnd;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_6;
    QVBoxLayout *VLayout_STFTResult_Hot;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_FFT_source;
    QComboBox *combox_FFTSource;
    QCheckBox *checkBox_STFT_MultiThreadMode;
    QGroupBox *groupBox_STFTGapType;
    QHBoxLayout *horizontalLayout_13;
    QRadioButton *radioBtn_STFTGapType_WndRatio;
    QRadioButton *radioBtn_STFTGapType_Time;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_WndLength_Time_2;
    QDoubleSpinBox *DSBox_STFTGapLength_timeMSec;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_WndLengthPoint_2;
    QDoubleSpinBox *DSBox_STFTGapWndLenghtRatio;
    QLabel *label_STFTGapInTime;
    QLabel *label_STFTGapInWndRatio;
    QCheckBox *checkBox_genWndSpecConstrainAfterSTFTResult;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_dataLoadState_2;
    QProgressBar *progressBar_STFTGenerateState;
    QLabel *label_processState;
    QPushButton *btn_genSTFTResult;
    QSpacerItem *verticalSpacer;
    QWidget *tab_detailShow;
    QVBoxLayout *VLayout_STFT_detail;

    void setupUi(QWidget *STFTWgtClass)
    {
        if (STFTWgtClass->objectName().isEmpty())
            STFTWgtClass->setObjectName(QString::fromUtf8("STFTWgtClass"));
        STFTWgtClass->resize(1293, 991);
        verticalLayout_2 = new QVBoxLayout(STFTWgtClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(STFTWgtClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_STFTPara = new QWidget();
        tab_STFTPara->setObjectName(QString::fromUtf8("tab_STFTPara"));
        verticalLayout_5 = new QVBoxLayout(tab_STFTPara);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox = new QGroupBox(tab_STFTPara);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        VLayout_Cht_Sig = new QVBoxLayout(groupBox);
        VLayout_Cht_Sig->setSpacing(6);
        VLayout_Cht_Sig->setContentsMargins(11, 11, 11, 11);
        VLayout_Cht_Sig->setObjectName(QString::fromUtf8("VLayout_Cht_Sig"));

        horizontalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_STFTPara);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(240, 0));
        groupBox_2->setMaximumSize(QSize(240, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_SigFrom = new QGroupBox(groupBox_2);
        groupBox_SigFrom->setObjectName(QString::fromUtf8("groupBox_SigFrom"));
        horizontalLayout = new QHBoxLayout(groupBox_SigFrom);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioBtn_SigFrom_Gen = new QRadioButton(groupBox_SigFrom);
        radioBtn_SigFrom_Gen->setObjectName(QString::fromUtf8("radioBtn_SigFrom_Gen"));
        radioBtn_SigFrom_Gen->setChecked(true);

        horizontalLayout->addWidget(radioBtn_SigFrom_Gen);

        radioBtn_SigFrom_Wav = new QRadioButton(groupBox_SigFrom);
        radioBtn_SigFrom_Wav->setObjectName(QString::fromUtf8("radioBtn_SigFrom_Wav"));

        horizontalLayout->addWidget(radioBtn_SigFrom_Wav);


        verticalLayout->addWidget(groupBox_SigFrom);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_GenSig = new QLabel(groupBox_2);
        label_GenSig->setObjectName(QString::fromUtf8("label_GenSig"));

        horizontalLayout_3->addWidget(label_GenSig);

        comboBox_GenSig = new QComboBox(groupBox_2);
        comboBox_GenSig->setObjectName(QString::fromUtf8("comboBox_GenSig"));
        comboBox_GenSig->setMinimumSize(QSize(120, 0));
        comboBox_GenSig->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(comboBox_GenSig);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_WavSig = new QLabel(groupBox_2);
        label_WavSig->setObjectName(QString::fromUtf8("label_WavSig"));

        horizontalLayout_2->addWidget(label_WavSig);

        comboBox_WavSig = new QComboBox(groupBox_2);
        comboBox_WavSig->setObjectName(QString::fromUtf8("comboBox_WavSig"));
        comboBox_WavSig->setMinimumSize(QSize(120, 0));
        comboBox_WavSig->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_2->addWidget(comboBox_WavSig);


        verticalLayout->addLayout(horizontalLayout_2);

        label_SigChnNum = new QLabel(groupBox_2);
        label_SigChnNum->setObjectName(QString::fromUtf8("label_SigChnNum"));

        verticalLayout->addWidget(label_SigChnNum);

        label_SigDuration = new QLabel(groupBox_2);
        label_SigDuration->setObjectName(QString::fromUtf8("label_SigDuration"));

        verticalLayout->addWidget(label_SigDuration);

        label_SigPotintCount = new QLabel(groupBox_2);
        label_SigPotintCount->setObjectName(QString::fromUtf8("label_SigPotintCount"));

        verticalLayout->addWidget(label_SigPotintCount);

        label_SigSampleRate = new QLabel(groupBox_2);
        label_SigSampleRate->setObjectName(QString::fromUtf8("label_SigSampleRate"));

        verticalLayout->addWidget(label_SigSampleRate);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_dataLoadState = new QLabel(groupBox_2);
        label_dataLoadState->setObjectName(QString::fromUtf8("label_dataLoadState"));

        horizontalLayout_11->addWidget(label_dataLoadState);

        progressBar_dataLoadState = new QProgressBar(groupBox_2);
        progressBar_dataLoadState->setObjectName(QString::fromUtf8("progressBar_dataLoadState"));
        progressBar_dataLoadState->setValue(24);

        horizontalLayout_11->addWidget(progressBar_dataLoadState);


        verticalLayout->addLayout(horizontalLayout_11);

        btn_loadSig = new QPushButton(groupBox_2);
        btn_loadSig->setObjectName(QString::fromUtf8("btn_loadSig"));

        verticalLayout->addWidget(btn_loadSig);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_4 = new QGroupBox(tab_STFTPara);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 320));
        VLayout_Cht_STFTWnd = new QVBoxLayout(groupBox_4);
        VLayout_Cht_STFTWnd->setSpacing(6);
        VLayout_Cht_STFTWnd->setContentsMargins(11, 11, 11, 11);
        VLayout_Cht_STFTWnd->setObjectName(QString::fromUtf8("VLayout_Cht_STFTWnd"));
        widget = new QWidget(groupBox_4);
        widget->setObjectName(QString::fromUtf8("widget"));

        VLayout_Cht_STFTWnd->addWidget(widget);


        horizontalLayout_5->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(tab_STFTPara);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(240, 0));
        groupBox_5->setMaximumSize(QSize(240, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_8 = new QGroupBox(groupBox_5);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_8);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        radioBtn_Wnd_Null = new QRadioButton(groupBox_8);
        radioBtn_Wnd_Null->setObjectName(QString::fromUtf8("radioBtn_Wnd_Null"));
        radioBtn_Wnd_Null->setChecked(false);

        horizontalLayout_7->addWidget(radioBtn_Wnd_Null);

        radioBtn_Wnd_Hann = new QRadioButton(groupBox_8);
        radioBtn_Wnd_Hann->setObjectName(QString::fromUtf8("radioBtn_Wnd_Hann"));
        radioBtn_Wnd_Hann->setChecked(true);

        horizontalLayout_7->addWidget(radioBtn_Wnd_Hann);


        verticalLayout_3->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(groupBox_5);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_9);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        radioBtn_WndLengthType_Point = new QRadioButton(groupBox_9);
        radioBtn_WndLengthType_Point->setObjectName(QString::fromUtf8("radioBtn_WndLengthType_Point"));
        radioBtn_WndLengthType_Point->setChecked(true);

        horizontalLayout_8->addWidget(radioBtn_WndLengthType_Point);

        radioBtn_WndLengthType_Time = new QRadioButton(groupBox_9);
        radioBtn_WndLengthType_Time->setObjectName(QString::fromUtf8("radioBtn_WndLengthType_Time"));

        horizontalLayout_8->addWidget(radioBtn_WndLengthType_Time);


        verticalLayout_3->addWidget(groupBox_9);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_WndLengthPoint = new QLabel(groupBox_5);
        label_WndLengthPoint->setObjectName(QString::fromUtf8("label_WndLengthPoint"));

        horizontalLayout_9->addWidget(label_WndLengthPoint);

        SBox_WndLengthPointCount = new QSpinBox(groupBox_5);
        SBox_WndLengthPointCount->setObjectName(QString::fromUtf8("SBox_WndLengthPointCount"));
        SBox_WndLengthPointCount->setEnabled(false);
        SBox_WndLengthPointCount->setMaximum(100000);
        SBox_WndLengthPointCount->setValue(4096);

        horizontalLayout_9->addWidget(SBox_WndLengthPointCount);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_WndLength_Time = new QLabel(groupBox_5);
        label_WndLength_Time->setObjectName(QString::fromUtf8("label_WndLength_Time"));

        horizontalLayout_10->addWidget(label_WndLength_Time);

        DSBox_WndLength_TimeMSec = new QDoubleSpinBox(groupBox_5);
        DSBox_WndLength_TimeMSec->setObjectName(QString::fromUtf8("DSBox_WndLength_TimeMSec"));
        DSBox_WndLength_TimeMSec->setEnabled(false);
        DSBox_WndLength_TimeMSec->setMaximum(100000.000000000000000);
        DSBox_WndLength_TimeMSec->setValue(100.000000000000000);

        horizontalLayout_10->addWidget(DSBox_WndLength_TimeMSec);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_WndSampleRate = new QLabel(groupBox_5);
        label_WndSampleRate->setObjectName(QString::fromUtf8("label_WndSampleRate"));

        horizontalLayout_12->addWidget(label_WndSampleRate);

        SBox_WndSampleRate = new QSpinBox(groupBox_5);
        SBox_WndSampleRate->setObjectName(QString::fromUtf8("SBox_WndSampleRate"));
        SBox_WndSampleRate->setMaximum(100000);
        SBox_WndSampleRate->setValue(44100);

        horizontalLayout_12->addWidget(SBox_WndSampleRate);


        verticalLayout_3->addLayout(horizontalLayout_12);

        label_resultWndLength_Point = new QLabel(groupBox_5);
        label_resultWndLength_Point->setObjectName(QString::fromUtf8("label_resultWndLength_Point"));

        verticalLayout_3->addWidget(label_resultWndLength_Point);

        label_resultWndLength_Time = new QLabel(groupBox_5);
        label_resultWndLength_Time->setObjectName(QString::fromUtf8("label_resultWndLength_Time"));

        verticalLayout_3->addWidget(label_resultWndLength_Time);

        btn_GenWnd = new QPushButton(groupBox_5);
        btn_GenWnd->setObjectName(QString::fromUtf8("btn_GenWnd"));

        verticalLayout_3->addWidget(btn_GenWnd);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_5->addWidget(groupBox_5);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        groupBox_6 = new QGroupBox(tab_STFTPara);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        VLayout_STFTResult_Hot = new QVBoxLayout(groupBox_6);
        VLayout_STFTResult_Hot->setSpacing(6);
        VLayout_STFTResult_Hot->setContentsMargins(11, 11, 11, 11);
        VLayout_STFTResult_Hot->setObjectName(QString::fromUtf8("VLayout_STFTResult_Hot"));

        horizontalLayout_6->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(tab_STFTPara);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(240, 0));
        groupBox_7->setMaximumSize(QSize(240, 16777215));
        verticalLayout_4 = new QVBoxLayout(groupBox_7);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_FFT_source = new QLabel(groupBox_7);
        label_FFT_source->setObjectName(QString::fromUtf8("label_FFT_source"));

        horizontalLayout_17->addWidget(label_FFT_source);

        combox_FFTSource = new QComboBox(groupBox_7);
        combox_FFTSource->setObjectName(QString::fromUtf8("combox_FFTSource"));

        horizontalLayout_17->addWidget(combox_FFTSource);

        checkBox_STFT_MultiThreadMode = new QCheckBox(groupBox_7);
        checkBox_STFT_MultiThreadMode->setObjectName(QString::fromUtf8("checkBox_STFT_MultiThreadMode"));
        checkBox_STFT_MultiThreadMode->setChecked(true);

        horizontalLayout_17->addWidget(checkBox_STFT_MultiThreadMode);


        verticalLayout_4->addLayout(horizontalLayout_17);

        groupBox_STFTGapType = new QGroupBox(groupBox_7);
        groupBox_STFTGapType->setObjectName(QString::fromUtf8("groupBox_STFTGapType"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_STFTGapType);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        radioBtn_STFTGapType_WndRatio = new QRadioButton(groupBox_STFTGapType);
        radioBtn_STFTGapType_WndRatio->setObjectName(QString::fromUtf8("radioBtn_STFTGapType_WndRatio"));
        radioBtn_STFTGapType_WndRatio->setChecked(false);

        horizontalLayout_13->addWidget(radioBtn_STFTGapType_WndRatio);

        radioBtn_STFTGapType_Time = new QRadioButton(groupBox_STFTGapType);
        radioBtn_STFTGapType_Time->setObjectName(QString::fromUtf8("radioBtn_STFTGapType_Time"));
        radioBtn_STFTGapType_Time->setChecked(true);

        horizontalLayout_13->addWidget(radioBtn_STFTGapType_Time);


        verticalLayout_4->addWidget(groupBox_STFTGapType);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_WndLength_Time_2 = new QLabel(groupBox_7);
        label_WndLength_Time_2->setObjectName(QString::fromUtf8("label_WndLength_Time_2"));

        horizontalLayout_14->addWidget(label_WndLength_Time_2);

        DSBox_STFTGapLength_timeMSec = new QDoubleSpinBox(groupBox_7);
        DSBox_STFTGapLength_timeMSec->setObjectName(QString::fromUtf8("DSBox_STFTGapLength_timeMSec"));
        DSBox_STFTGapLength_timeMSec->setEnabled(true);
        DSBox_STFTGapLength_timeMSec->setMaximum(100000.000000000000000);
        DSBox_STFTGapLength_timeMSec->setValue(20.000000000000000);

        horizontalLayout_14->addWidget(DSBox_STFTGapLength_timeMSec);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_WndLengthPoint_2 = new QLabel(groupBox_7);
        label_WndLengthPoint_2->setObjectName(QString::fromUtf8("label_WndLengthPoint_2"));

        horizontalLayout_15->addWidget(label_WndLengthPoint_2);

        DSBox_STFTGapWndLenghtRatio = new QDoubleSpinBox(groupBox_7);
        DSBox_STFTGapWndLenghtRatio->setObjectName(QString::fromUtf8("DSBox_STFTGapWndLenghtRatio"));
        DSBox_STFTGapWndLenghtRatio->setEnabled(false);
        DSBox_STFTGapWndLenghtRatio->setMaximum(1.000000000000000);
        DSBox_STFTGapWndLenghtRatio->setSingleStep(0.010000000000000);
        DSBox_STFTGapWndLenghtRatio->setValue(0.250000000000000);

        horizontalLayout_15->addWidget(DSBox_STFTGapWndLenghtRatio);


        verticalLayout_4->addLayout(horizontalLayout_15);

        label_STFTGapInTime = new QLabel(groupBox_7);
        label_STFTGapInTime->setObjectName(QString::fromUtf8("label_STFTGapInTime"));

        verticalLayout_4->addWidget(label_STFTGapInTime);

        label_STFTGapInWndRatio = new QLabel(groupBox_7);
        label_STFTGapInWndRatio->setObjectName(QString::fromUtf8("label_STFTGapInWndRatio"));

        verticalLayout_4->addWidget(label_STFTGapInWndRatio);

        checkBox_genWndSpecConstrainAfterSTFTResult = new QCheckBox(groupBox_7);
        checkBox_genWndSpecConstrainAfterSTFTResult->setObjectName(QString::fromUtf8("checkBox_genWndSpecConstrainAfterSTFTResult"));
        checkBox_genWndSpecConstrainAfterSTFTResult->setChecked(true);

        verticalLayout_4->addWidget(checkBox_genWndSpecConstrainAfterSTFTResult);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_dataLoadState_2 = new QLabel(groupBox_7);
        label_dataLoadState_2->setObjectName(QString::fromUtf8("label_dataLoadState_2"));

        horizontalLayout_16->addWidget(label_dataLoadState_2);

        progressBar_STFTGenerateState = new QProgressBar(groupBox_7);
        progressBar_STFTGenerateState->setObjectName(QString::fromUtf8("progressBar_STFTGenerateState"));
        progressBar_STFTGenerateState->setValue(24);

        horizontalLayout_16->addWidget(progressBar_STFTGenerateState);


        verticalLayout_4->addLayout(horizontalLayout_16);

        label_processState = new QLabel(groupBox_7);
        label_processState->setObjectName(QString::fromUtf8("label_processState"));
        label_processState->setMinimumSize(QSize(0, 20));
        label_processState->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(label_processState);

        btn_genSTFTResult = new QPushButton(groupBox_7);
        btn_genSTFTResult->setObjectName(QString::fromUtf8("btn_genSTFTResult"));

        verticalLayout_4->addWidget(btn_genSTFTResult);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout_6->addWidget(groupBox_7);


        verticalLayout_5->addLayout(horizontalLayout_6);

        tabWidget->addTab(tab_STFTPara, QString());
        tab_detailShow = new QWidget();
        tab_detailShow->setObjectName(QString::fromUtf8("tab_detailShow"));
        VLayout_STFT_detail = new QVBoxLayout(tab_detailShow);
        VLayout_STFT_detail->setSpacing(6);
        VLayout_STFT_detail->setContentsMargins(11, 11, 11, 11);
        VLayout_STFT_detail->setObjectName(QString::fromUtf8("VLayout_STFT_detail"));
        tabWidget->addTab(tab_detailShow, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(STFTWgtClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(STFTWgtClass);
    } // setupUi

    void retranslateUi(QWidget *STFTWgtClass)
    {
        STFTWgtClass->setWindowTitle(QApplication::translate("STFTWgtClass", "STFTWgt", nullptr));
        groupBox->setTitle(QApplication::translate("STFTWgtClass", "\345\216\237\345\247\213\344\277\241\345\217\267", nullptr));
        groupBox_2->setTitle(QApplication::translate("STFTWgtClass", "\345\216\237\345\247\213\344\277\241\345\217\267\345\257\274\345\205\245", nullptr));
        groupBox_SigFrom->setTitle(QApplication::translate("STFTWgtClass", "\346\235\245\346\272\220\357\274\210\345\275\223\345\211\215\344\277\241\345\217\267\357\274\211", nullptr));
        radioBtn_SigFrom_Gen->setText(QApplication::translate("STFTWgtClass", "\345\220\210\346\210\220\344\277\241\345\217\267", nullptr));
        radioBtn_SigFrom_Wav->setText(QApplication::translate("STFTWgtClass", "\346\226\207\344\273\266\345\257\274\345\205\245", nullptr));
        label_GenSig->setText(QApplication::translate("STFTWgtClass", "\345\220\210\346\210\220\344\277\241\345\217\267\346\272\220", nullptr));
        label_WavSig->setText(QApplication::translate("STFTWgtClass", "\346\226\207\344\273\266\344\277\241\345\217\267\346\272\220", nullptr));
        label_SigChnNum->setText(QApplication::translate("STFTWgtClass", "\351\200\232\351\201\223\346\225\260\357\274\232", nullptr));
        label_SigDuration->setText(QApplication::translate("STFTWgtClass", "\346\214\201\347\273\255\346\227\266\351\227\264\357\274\232", nullptr));
        label_SigPotintCount->setText(QApplication::translate("STFTWgtClass", "\350\275\275\345\205\245\347\202\271\346\225\260\357\274\232", nullptr));
        label_SigSampleRate->setText(QApplication::translate("STFTWgtClass", "\351\207\207\346\240\267\347\216\207\357\274\232", nullptr));
        label_dataLoadState->setText(QApplication::translate("STFTWgtClass", "\345\257\274\345\205\245\347\212\266\346\200\201\357\274\232", nullptr));
        btn_loadSig->setText(QApplication::translate("STFTWgtClass", "\345\257\274\345\205\245", nullptr));
        groupBox_4->setTitle(QApplication::translate("STFTWgtClass", "\347\252\227\345\275\242", nullptr));
        groupBox_5->setTitle(QApplication::translate("STFTWgtClass", "\346\227\266\345\237\237\347\252\227\345\236\213\346\216\247\345\210\266", nullptr));
        groupBox_8->setTitle(QApplication::translate("STFTWgtClass", "\345\275\242\347\212\266", nullptr));
        radioBtn_Wnd_Null->setText(QApplication::translate("STFTWgtClass", "\346\227\240", nullptr));
        radioBtn_Wnd_Hann->setText(QApplication::translate("STFTWgtClass", "Hann", nullptr));
        groupBox_9->setTitle(QApplication::translate("STFTWgtClass", "\351\225\277\345\272\246\345\256\232\344\271\211", nullptr));
        radioBtn_WndLengthType_Point->setText(QApplication::translate("STFTWgtClass", "\347\202\271\346\225\260", nullptr));
        radioBtn_WndLengthType_Time->setText(QApplication::translate("STFTWgtClass", "\346\227\266\351\225\277", nullptr));
        label_WndLengthPoint->setText(QApplication::translate("STFTWgtClass", "\347\252\227\345\236\213\347\202\271\346\225\260\357\274\232", nullptr));
        label_WndLength_Time->setText(QApplication::translate("STFTWgtClass", "\347\252\227\345\236\213\346\227\266\351\225\277(ms)\357\274\232", nullptr));
        label_WndSampleRate->setText(QApplication::translate("STFTWgtClass", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_resultWndLength_Point->setText(QApplication::translate("STFTWgtClass", "\347\252\227\345\236\213\347\255\211\344\273\267\347\202\271\346\225\260\357\274\232", nullptr));
        label_resultWndLength_Time->setText(QApplication::translate("STFTWgtClass", "\347\252\227\345\236\213\347\255\211\344\273\267\346\227\266\351\225\277\357\274\232", nullptr));
        btn_GenWnd->setText(QApplication::translate("STFTWgtClass", "\347\224\237\346\210\220\347\252\227\345\236\213", nullptr));
        groupBox_6->setTitle(QApplication::translate("STFTWgtClass", "STFT\347\273\223\346\236\234", nullptr));
        groupBox_7->setTitle(QApplication::translate("STFTWgtClass", "STFT\346\216\247\345\210\266", nullptr));
        label_FFT_source->setText(QApplication::translate("STFTWgtClass", "FFT\346\235\245\346\272\220", nullptr));
        checkBox_STFT_MultiThreadMode->setText(QApplication::translate("STFTWgtClass", "\345\244\232\347\272\277\347\250\213\346\250\241\345\274\217", nullptr));
        groupBox_STFTGapType->setTitle(QApplication::translate("STFTWgtClass", "\346\255\245\351\225\277\347\261\273\345\236\213", nullptr));
        radioBtn_STFTGapType_WndRatio->setText(QApplication::translate("STFTWgtClass", "\347\252\227\345\217\243\346\257\224\344\276\213", nullptr));
        radioBtn_STFTGapType_Time->setText(QApplication::translate("STFTWgtClass", "\346\227\266\351\227\264\351\225\277\345\272\246", nullptr));
        label_WndLength_Time_2->setText(QApplication::translate("STFTWgtClass", "\346\255\245\351\225\277\346\227\266\351\227\264(ms)\357\274\232", nullptr));
        label_WndLengthPoint_2->setText(QApplication::translate("STFTWgtClass", "\347\252\227\345\217\243\346\257\224\344\276\213", nullptr));
        label_STFTGapInTime->setText(QApplication::translate("STFTWgtClass", "\346\255\245\351\225\277\347\255\211\344\273\267\346\227\266\351\227\264\357\274\232", nullptr));
        label_STFTGapInWndRatio->setText(QApplication::translate("STFTWgtClass", "\346\255\245\351\225\277\347\255\211\344\273\267\347\252\227\345\217\243\346\257\224\344\276\213\357\274\232", nullptr));
        checkBox_genWndSpecConstrainAfterSTFTResult->setText(QApplication::translate("STFTWgtClass", "\344\271\213\345\220\216\347\224\237\346\210\220\347\252\227\350\260\261\346\212\221\345\210\266\350\276\223\345\207\272", nullptr));
        label_dataLoadState_2->setText(QApplication::translate("STFTWgtClass", "\347\224\237\346\210\220\347\212\266\346\200\201\357\274\232", nullptr));
        label_processState->setText(QApplication::translate("STFTWgtClass", "\346\264\273\350\267\203\347\272\277\347\250\213\357\274\232", nullptr));
        btn_genSTFTResult->setText(QApplication::translate("STFTWgtClass", "\347\224\237\346\210\220STFT\347\273\223\346\236\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_STFTPara), QApplication::translate("STFTWgtClass", "\345\210\206\346\236\220\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_detailShow), QApplication::translate("STFTWgtClass", "\350\257\246\347\273\206\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class STFTWgtClass: public Ui_STFTWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STFTWGT_H
