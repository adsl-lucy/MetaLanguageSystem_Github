/********************************************************************************
** Form generated from reading UI file 'FFTWindowWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFTWINDOWWGT_H
#define UI_FFTWINDOWWGT_H

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
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FFTWindowWgtClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_Main;
    QWidget *tab_WndSpecAns;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget_2;
    QWidget *tab_GenWndPt;
    QHBoxLayout *horizontalLayout_22;
    QGroupBox *groupBox_baseSig_chart;
    QHBoxLayout *HLayout_FFTWnd_TimeCht;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_WndType;
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
    QLabel *label_WndSTFTFreqDelta;
    QLabel *label_GenState;
    QProgressBar *progressBar_dataLoadState;
    QPushButton *btn_GenWndTimeGraph;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_23;
    QGroupBox *groupBox_ActiveSig_chart;
    QHBoxLayout *HLayout_FFTWnd_ActiveFunc_Cht;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_ActiveWnd_sampleRate;
    QLabel *label_ActiveWnd_WndType;
    QLabel *label_ActiveWnd_FFTWndPtCount;
    QGroupBox *groupBox_ActiveStartType;
    QHBoxLayout *horizontalLayout_24;
    QRadioButton *radioButton_ActiveStartType_Time;
    QRadioButton *radioButton_ActiveStartType_Ratio;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_ActiveStartTime;
    QDoubleSpinBox *DSBox_ActiveStartTime;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_ActiveStartRatio;
    QDoubleSpinBox *DSBox_ActiveStartRatio;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_IncreaseTime;
    QDoubleSpinBox *DSBox_IncreaseTime;
    QProgressBar *progressBar_ActiveFuncLoadState;
    QPushButton *btn_GenActiveFunc;
    QGroupBox *groupBox_ActiveWnd_ShowType;
    QHBoxLayout *horizontalLayout_34;
    QCheckBox *checkBox_ActiveWnd_ShowType_STFTWnd;
    QCheckBox *checkBox_ActiveWnd_ShowType_ActiveVal;
    QCheckBox *checkBox_ActiveWnd_ShowType_ActiveWnd;
    QTabWidget *tabWidget;
    QWidget *tab_spectrum;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *VLayout_FFTWndSpectrum_Cht;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_WndFFTValType_AbsoluteVal;
    QRadioButton *radioButton_WndFFTValType_db;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_WndFFTShowMaxFreq_2;
    QSpinBox *SBox_WndFFTShowPointCount;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_WndFFTShowMaxFreq;
    QSpinBox *SBox_WndFFTShowMaxFreq;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_WndFFTShowMinVal;
    QSpinBox *SBox_WndFFTShowMinVal;
    QPushButton *btn_GenWndFFTGraph;
    QPushButton *btn_updateWndFFTCht;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_WndFFTDeltaFreq;
    QLabel *label_WndFFTSubPartCount;
    QLabel *label_mainPartMaxFFTError;
    QLabel *label_mainPart10dbHalfWidth;
    QLabel *label_firstPartHeight;
    QLabel *label_firstPartFreq;
    QLabel *label_SecondPartHeight;
    QLabel *label_SecondPartFreq;
    QWidget *tab_WndFFTPartEst;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_6;
    QHBoxLayout *HLayout_WndFFTPart_Cht;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_WndPartCht_PartCount;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_WndPartCht_showPartCount;
    QSpinBox *SBox_WndPartCht_PartCount;
    QPushButton *btn_updateWndFFTPartCht;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_WndFFTPartResult;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_SpecConstrainRatio;
    QHBoxLayout *HLayout_WndSepcConstrainOutput;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_MaxConstrainDbPos;
    QSpinBox *SBox_MaxConstrainDbPos;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_PeakFreqDriftRatio;
    QDoubleSpinBox *DSBox_PeakFreqDriftRatio;
    QCheckBox *checkBox_forcePt2DBVal;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_forcePt2DBVal;
    QDoubleSpinBox *DSBox_forcePt2DBVal;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_EnhanceConstrainPos;
    QSpinBox *SBox__EnheaceConstrainPos;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_EnhanceConstrainRatio;
    QDoubleSpinBox *DSbox_EnhanceConstrainRatio;
    QLabel *label_constrainSidePtCount;
    QLabel *label_NoiseUnConstrainFreqInterval;
    QLabel *label_NoiseToBeSignalFreqInterval;
    QPushButton *btn_GenWndSpecConstrainResult;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_activeWndSpec;
    QHBoxLayout *horizontalLayout_30;
    QGroupBox *groupBox_15;
    QVBoxLayout *VLayout_ActiveFFTWndSpectrum_Cht;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_13;
    QHBoxLayout *horizontalLayout_26;
    QRadioButton *radioButton_ActiveWndFFTValType_AbsoluteVal;
    QRadioButton *radioButton_ActiveWndFFTValType_db;
    QRadioButton *radioButton_ActiveWndFFTValType_AbsDb;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_ActiveWndFFTShowPointCount;
    QSpinBox *SBox_ActiveWndFFTShowPointCount;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_ActiveWndFFTShowMaxFreq;
    QSpinBox *SBox_ActiveWndFFTShowMaxFreq;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_ActiveWndFFTShowMinVal;
    QSpinBox *SBox_ActiveWndFFTShowMinVal;
    QHBoxLayout *horizontalLayout_35;
    QPushButton *btn_GenActiveWndFFTGraph;
    QPushButton *btn_updateActiveWndFFTCht;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_4;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_5;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QPushButton *btn_GenActiveWndFFTGraph_2;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_8;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_6;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_7;
    QSlider *horizontalSlider_2;
    QSpacerItem *verticalSpacer;
    QWidget *tab_WndSpecConstrainOutput;
    QVBoxLayout *VLayout_EffOscWidget;

    void setupUi(QWidget *FFTWindowWgtClass)
    {
        if (FFTWindowWgtClass->objectName().isEmpty())
            FFTWindowWgtClass->setObjectName(QString::fromUtf8("FFTWindowWgtClass"));
        FFTWindowWgtClass->resize(1298, 983);
        verticalLayout = new QVBoxLayout(FFTWindowWgtClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget_Main = new QTabWidget(FFTWindowWgtClass);
        tabWidget_Main->setObjectName(QString::fromUtf8("tabWidget_Main"));
        tab_WndSpecAns = new QWidget();
        tab_WndSpecAns->setObjectName(QString::fromUtf8("tab_WndSpecAns"));
        verticalLayout_8 = new QVBoxLayout(tab_WndSpecAns);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabWidget_2 = new QTabWidget(tab_WndSpecAns);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_GenWndPt = new QWidget();
        tab_GenWndPt->setObjectName(QString::fromUtf8("tab_GenWndPt"));
        horizontalLayout_22 = new QHBoxLayout(tab_GenWndPt);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        groupBox_baseSig_chart = new QGroupBox(tab_GenWndPt);
        groupBox_baseSig_chart->setObjectName(QString::fromUtf8("groupBox_baseSig_chart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_baseSig_chart->sizePolicy().hasHeightForWidth());
        groupBox_baseSig_chart->setSizePolicy(sizePolicy);
        groupBox_baseSig_chart->setMinimumSize(QSize(800, 250));
        groupBox_baseSig_chart->setMaximumSize(QSize(1980, 440));
        HLayout_FFTWnd_TimeCht = new QHBoxLayout(groupBox_baseSig_chart);
        HLayout_FFTWnd_TimeCht->setSpacing(6);
        HLayout_FFTWnd_TimeCht->setContentsMargins(11, 11, 11, 11);
        HLayout_FFTWnd_TimeCht->setObjectName(QString::fromUtf8("HLayout_FFTWnd_TimeCht"));

        horizontalLayout_22->addWidget(groupBox_baseSig_chart);

        groupBox_5 = new QGroupBox(tab_GenWndPt);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(240, 0));
        groupBox_5->setMaximumSize(QSize(240, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_5);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_WndType = new QComboBox(groupBox_5);
        comboBox_WndType->addItem(QString());
        comboBox_WndType->addItem(QString());
        comboBox_WndType->setObjectName(QString::fromUtf8("comboBox_WndType"));

        horizontalLayout->addWidget(comboBox_WndType);


        verticalLayout_3->addLayout(horizontalLayout);

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

        label_WndSTFTFreqDelta = new QLabel(groupBox_5);
        label_WndSTFTFreqDelta->setObjectName(QString::fromUtf8("label_WndSTFTFreqDelta"));

        verticalLayout_3->addWidget(label_WndSTFTFreqDelta);

        label_GenState = new QLabel(groupBox_5);
        label_GenState->setObjectName(QString::fromUtf8("label_GenState"));

        verticalLayout_3->addWidget(label_GenState);

        progressBar_dataLoadState = new QProgressBar(groupBox_5);
        progressBar_dataLoadState->setObjectName(QString::fromUtf8("progressBar_dataLoadState"));
        progressBar_dataLoadState->setValue(24);

        verticalLayout_3->addWidget(progressBar_dataLoadState);

        btn_GenWndTimeGraph = new QPushButton(groupBox_5);
        btn_GenWndTimeGraph->setObjectName(QString::fromUtf8("btn_GenWndTimeGraph"));

        verticalLayout_3->addWidget(btn_GenWndTimeGraph);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_22->addWidget(groupBox_5);

        tabWidget_2->addTab(tab_GenWndPt, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_23 = new QHBoxLayout(tab_3);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        groupBox_ActiveSig_chart = new QGroupBox(tab_3);
        groupBox_ActiveSig_chart->setObjectName(QString::fromUtf8("groupBox_ActiveSig_chart"));
        sizePolicy.setHeightForWidth(groupBox_ActiveSig_chart->sizePolicy().hasHeightForWidth());
        groupBox_ActiveSig_chart->setSizePolicy(sizePolicy);
        groupBox_ActiveSig_chart->setMinimumSize(QSize(800, 250));
        groupBox_ActiveSig_chart->setMaximumSize(QSize(1980, 440));
        HLayout_FFTWnd_ActiveFunc_Cht = new QHBoxLayout(groupBox_ActiveSig_chart);
        HLayout_FFTWnd_ActiveFunc_Cht->setSpacing(6);
        HLayout_FFTWnd_ActiveFunc_Cht->setContentsMargins(11, 11, 11, 11);
        HLayout_FFTWnd_ActiveFunc_Cht->setObjectName(QString::fromUtf8("HLayout_FFTWnd_ActiveFunc_Cht"));

        horizontalLayout_23->addWidget(groupBox_ActiveSig_chart);

        groupBox_8 = new QGroupBox(tab_3);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setMaximumSize(QSize(240, 16777215));
        verticalLayout_9 = new QVBoxLayout(groupBox_8);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox_11 = new QGroupBox(groupBox_8);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setMinimumSize(QSize(0, 0));
        groupBox_11->setMaximumSize(QSize(16777215, 408));
        verticalLayout_10 = new QVBoxLayout(groupBox_11);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_ActiveWnd_sampleRate = new QLabel(groupBox_11);
        label_ActiveWnd_sampleRate->setObjectName(QString::fromUtf8("label_ActiveWnd_sampleRate"));

        verticalLayout_10->addWidget(label_ActiveWnd_sampleRate);

        label_ActiveWnd_WndType = new QLabel(groupBox_11);
        label_ActiveWnd_WndType->setObjectName(QString::fromUtf8("label_ActiveWnd_WndType"));

        verticalLayout_10->addWidget(label_ActiveWnd_WndType);

        label_ActiveWnd_FFTWndPtCount = new QLabel(groupBox_11);
        label_ActiveWnd_FFTWndPtCount->setObjectName(QString::fromUtf8("label_ActiveWnd_FFTWndPtCount"));

        verticalLayout_10->addWidget(label_ActiveWnd_FFTWndPtCount);


        verticalLayout_9->addWidget(groupBox_11);

        groupBox_ActiveStartType = new QGroupBox(groupBox_8);
        groupBox_ActiveStartType->setObjectName(QString::fromUtf8("groupBox_ActiveStartType"));
        groupBox_ActiveStartType->setMinimumSize(QSize(0, 48));
        horizontalLayout_24 = new QHBoxLayout(groupBox_ActiveStartType);
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        radioButton_ActiveStartType_Time = new QRadioButton(groupBox_ActiveStartType);
        radioButton_ActiveStartType_Time->setObjectName(QString::fromUtf8("radioButton_ActiveStartType_Time"));

        horizontalLayout_24->addWidget(radioButton_ActiveStartType_Time);

        radioButton_ActiveStartType_Ratio = new QRadioButton(groupBox_ActiveStartType);
        radioButton_ActiveStartType_Ratio->setObjectName(QString::fromUtf8("radioButton_ActiveStartType_Ratio"));
        radioButton_ActiveStartType_Ratio->setChecked(true);

        horizontalLayout_24->addWidget(radioButton_ActiveStartType_Ratio);


        verticalLayout_9->addWidget(groupBox_ActiveStartType);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_ActiveStartTime = new QLabel(groupBox_8);
        label_ActiveStartTime->setObjectName(QString::fromUtf8("label_ActiveStartTime"));

        horizontalLayout_20->addWidget(label_ActiveStartTime);

        DSBox_ActiveStartTime = new QDoubleSpinBox(groupBox_8);
        DSBox_ActiveStartTime->setObjectName(QString::fromUtf8("DSBox_ActiveStartTime"));
        DSBox_ActiveStartTime->setMinimum(-50.000000000000000);
        DSBox_ActiveStartTime->setMaximum(50.000000000000000);

        horizontalLayout_20->addWidget(DSBox_ActiveStartTime);


        verticalLayout_9->addLayout(horizontalLayout_20);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_ActiveStartRatio = new QLabel(groupBox_8);
        label_ActiveStartRatio->setObjectName(QString::fromUtf8("label_ActiveStartRatio"));

        horizontalLayout_25->addWidget(label_ActiveStartRatio);

        DSBox_ActiveStartRatio = new QDoubleSpinBox(groupBox_8);
        DSBox_ActiveStartRatio->setObjectName(QString::fromUtf8("DSBox_ActiveStartRatio"));
        DSBox_ActiveStartRatio->setMinimum(0.000000000000000);
        DSBox_ActiveStartRatio->setMaximum(100.000000000000000);
        DSBox_ActiveStartRatio->setValue(34.000000000000000);

        horizontalLayout_25->addWidget(DSBox_ActiveStartRatio);


        verticalLayout_9->addLayout(horizontalLayout_25);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_IncreaseTime = new QLabel(groupBox_8);
        label_IncreaseTime->setObjectName(QString::fromUtf8("label_IncreaseTime"));

        horizontalLayout_21->addWidget(label_IncreaseTime);

        DSBox_IncreaseTime = new QDoubleSpinBox(groupBox_8);
        DSBox_IncreaseTime->setObjectName(QString::fromUtf8("DSBox_IncreaseTime"));
        DSBox_IncreaseTime->setMaximum(50.000000000000000);
        DSBox_IncreaseTime->setValue(15.000000000000000);

        horizontalLayout_21->addWidget(DSBox_IncreaseTime);


        verticalLayout_9->addLayout(horizontalLayout_21);

        progressBar_ActiveFuncLoadState = new QProgressBar(groupBox_8);
        progressBar_ActiveFuncLoadState->setObjectName(QString::fromUtf8("progressBar_ActiveFuncLoadState"));
        progressBar_ActiveFuncLoadState->setValue(0);

        verticalLayout_9->addWidget(progressBar_ActiveFuncLoadState);

        btn_GenActiveFunc = new QPushButton(groupBox_8);
        btn_GenActiveFunc->setObjectName(QString::fromUtf8("btn_GenActiveFunc"));

        verticalLayout_9->addWidget(btn_GenActiveFunc);

        groupBox_ActiveWnd_ShowType = new QGroupBox(groupBox_8);
        groupBox_ActiveWnd_ShowType->setObjectName(QString::fromUtf8("groupBox_ActiveWnd_ShowType"));
        groupBox_ActiveWnd_ShowType->setMinimumSize(QSize(0, 0));
        horizontalLayout_34 = new QHBoxLayout(groupBox_ActiveWnd_ShowType);
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        checkBox_ActiveWnd_ShowType_STFTWnd = new QCheckBox(groupBox_ActiveWnd_ShowType);
        checkBox_ActiveWnd_ShowType_STFTWnd->setObjectName(QString::fromUtf8("checkBox_ActiveWnd_ShowType_STFTWnd"));
        checkBox_ActiveWnd_ShowType_STFTWnd->setChecked(true);

        horizontalLayout_34->addWidget(checkBox_ActiveWnd_ShowType_STFTWnd);

        checkBox_ActiveWnd_ShowType_ActiveVal = new QCheckBox(groupBox_ActiveWnd_ShowType);
        checkBox_ActiveWnd_ShowType_ActiveVal->setObjectName(QString::fromUtf8("checkBox_ActiveWnd_ShowType_ActiveVal"));
        checkBox_ActiveWnd_ShowType_ActiveVal->setChecked(true);

        horizontalLayout_34->addWidget(checkBox_ActiveWnd_ShowType_ActiveVal);

        checkBox_ActiveWnd_ShowType_ActiveWnd = new QCheckBox(groupBox_ActiveWnd_ShowType);
        checkBox_ActiveWnd_ShowType_ActiveWnd->setObjectName(QString::fromUtf8("checkBox_ActiveWnd_ShowType_ActiveWnd"));
        checkBox_ActiveWnd_ShowType_ActiveWnd->setChecked(true);

        horizontalLayout_34->addWidget(checkBox_ActiveWnd_ShowType_ActiveWnd);


        verticalLayout_9->addWidget(groupBox_ActiveWnd_ShowType);


        horizontalLayout_23->addWidget(groupBox_8);

        tabWidget_2->addTab(tab_3, QString());

        horizontalLayout_2->addWidget(tabWidget_2);


        verticalLayout_8->addLayout(horizontalLayout_2);

        tabWidget = new QTabWidget(tab_WndSpecAns);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_spectrum = new QWidget();
        tab_spectrum->setObjectName(QString::fromUtf8("tab_spectrum"));
        horizontalLayout_3 = new QHBoxLayout(tab_spectrum);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox = new QGroupBox(tab_spectrum);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(1024, 0));
        VLayout_FFTWndSpectrum_Cht = new QVBoxLayout(groupBox);
        VLayout_FFTWndSpectrum_Cht->setSpacing(6);
        VLayout_FFTWndSpectrum_Cht->setContentsMargins(11, 11, 11, 11);
        VLayout_FFTWndSpectrum_Cht->setObjectName(QString::fromUtf8("VLayout_FFTWndSpectrum_Cht"));

        horizontalLayout_3->addWidget(groupBox);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_4 = new QGroupBox(tab_spectrum);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 80));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 0));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButton_WndFFTValType_AbsoluteVal = new QRadioButton(groupBox_3);
        radioButton_WndFFTValType_AbsoluteVal->setObjectName(QString::fromUtf8("radioButton_WndFFTValType_AbsoluteVal"));

        horizontalLayout_4->addWidget(radioButton_WndFFTValType_AbsoluteVal);

        radioButton_WndFFTValType_db = new QRadioButton(groupBox_3);
        radioButton_WndFFTValType_db->setObjectName(QString::fromUtf8("radioButton_WndFFTValType_db"));
        radioButton_WndFFTValType_db->setChecked(true);

        horizontalLayout_4->addWidget(radioButton_WndFFTValType_db);


        verticalLayout_4->addWidget(groupBox_3);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_WndFFTShowMaxFreq_2 = new QLabel(groupBox_4);
        label_WndFFTShowMaxFreq_2->setObjectName(QString::fromUtf8("label_WndFFTShowMaxFreq_2"));

        horizontalLayout_14->addWidget(label_WndFFTShowMaxFreq_2);

        SBox_WndFFTShowPointCount = new QSpinBox(groupBox_4);
        SBox_WndFFTShowPointCount->setObjectName(QString::fromUtf8("SBox_WndFFTShowPointCount"));
        SBox_WndFFTShowPointCount->setEnabled(true);
        SBox_WndFFTShowPointCount->setMaximum(100000);
        SBox_WndFFTShowPointCount->setSingleStep(20000);
        SBox_WndFFTShowPointCount->setValue(20000);

        horizontalLayout_14->addWidget(SBox_WndFFTShowPointCount);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_WndFFTShowMaxFreq = new QLabel(groupBox_4);
        label_WndFFTShowMaxFreq->setObjectName(QString::fromUtf8("label_WndFFTShowMaxFreq"));

        horizontalLayout_11->addWidget(label_WndFFTShowMaxFreq);

        SBox_WndFFTShowMaxFreq = new QSpinBox(groupBox_4);
        SBox_WndFFTShowMaxFreq->setObjectName(QString::fromUtf8("SBox_WndFFTShowMaxFreq"));
        SBox_WndFFTShowMaxFreq->setEnabled(true);
        SBox_WndFFTShowMaxFreq->setMaximum(100000);
        SBox_WndFFTShowMaxFreq->setValue(200);

        horizontalLayout_11->addWidget(SBox_WndFFTShowMaxFreq);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_WndFFTShowMinVal = new QLabel(groupBox_4);
        label_WndFFTShowMinVal->setObjectName(QString::fromUtf8("label_WndFFTShowMinVal"));

        horizontalLayout_13->addWidget(label_WndFFTShowMinVal);

        SBox_WndFFTShowMinVal = new QSpinBox(groupBox_4);
        SBox_WndFFTShowMinVal->setObjectName(QString::fromUtf8("SBox_WndFFTShowMinVal"));
        SBox_WndFFTShowMinVal->setEnabled(true);
        SBox_WndFFTShowMinVal->setMinimum(-10000);
        SBox_WndFFTShowMinVal->setMaximum(100000);
        SBox_WndFFTShowMinVal->setValue(-100);

        horizontalLayout_13->addWidget(SBox_WndFFTShowMinVal);


        verticalLayout_4->addLayout(horizontalLayout_13);

        btn_GenWndFFTGraph = new QPushButton(groupBox_4);
        btn_GenWndFFTGraph->setObjectName(QString::fromUtf8("btn_GenWndFFTGraph"));

        verticalLayout_4->addWidget(btn_GenWndFFTGraph);

        btn_updateWndFFTCht = new QPushButton(groupBox_4);
        btn_updateWndFFTCht->setObjectName(QString::fromUtf8("btn_updateWndFFTCht"));

        verticalLayout_4->addWidget(btn_updateWndFFTCht);


        verticalLayout_5->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(tab_spectrum);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setMaximumSize(QSize(240, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_WndFFTDeltaFreq = new QLabel(groupBox_2);
        label_WndFFTDeltaFreq->setObjectName(QString::fromUtf8("label_WndFFTDeltaFreq"));

        verticalLayout_2->addWidget(label_WndFFTDeltaFreq);

        label_WndFFTSubPartCount = new QLabel(groupBox_2);
        label_WndFFTSubPartCount->setObjectName(QString::fromUtf8("label_WndFFTSubPartCount"));

        verticalLayout_2->addWidget(label_WndFFTSubPartCount);

        label_mainPartMaxFFTError = new QLabel(groupBox_2);
        label_mainPartMaxFFTError->setObjectName(QString::fromUtf8("label_mainPartMaxFFTError"));

        verticalLayout_2->addWidget(label_mainPartMaxFFTError);

        label_mainPart10dbHalfWidth = new QLabel(groupBox_2);
        label_mainPart10dbHalfWidth->setObjectName(QString::fromUtf8("label_mainPart10dbHalfWidth"));

        verticalLayout_2->addWidget(label_mainPart10dbHalfWidth);

        label_firstPartHeight = new QLabel(groupBox_2);
        label_firstPartHeight->setObjectName(QString::fromUtf8("label_firstPartHeight"));

        verticalLayout_2->addWidget(label_firstPartHeight);

        label_firstPartFreq = new QLabel(groupBox_2);
        label_firstPartFreq->setObjectName(QString::fromUtf8("label_firstPartFreq"));

        verticalLayout_2->addWidget(label_firstPartFreq);

        label_SecondPartHeight = new QLabel(groupBox_2);
        label_SecondPartHeight->setObjectName(QString::fromUtf8("label_SecondPartHeight"));

        verticalLayout_2->addWidget(label_SecondPartHeight);

        label_SecondPartFreq = new QLabel(groupBox_2);
        label_SecondPartFreq->setObjectName(QString::fromUtf8("label_SecondPartFreq"));

        verticalLayout_2->addWidget(label_SecondPartFreq);


        verticalLayout_5->addWidget(groupBox_2);


        horizontalLayout_3->addLayout(verticalLayout_5);

        tabWidget->addTab(tab_spectrum, QString());
        tab_WndFFTPartEst = new QWidget();
        tab_WndFFTPartEst->setObjectName(QString::fromUtf8("tab_WndFFTPartEst"));
        horizontalLayout_5 = new QHBoxLayout(tab_WndFFTPartEst);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_6 = new QGroupBox(tab_WndFFTPartEst);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        HLayout_WndFFTPart_Cht = new QHBoxLayout(groupBox_6);
        HLayout_WndFFTPart_Cht->setSpacing(6);
        HLayout_WndFFTPart_Cht->setContentsMargins(11, 11, 11, 11);
        HLayout_WndFFTPart_Cht->setObjectName(QString::fromUtf8("HLayout_WndFFTPart_Cht"));

        horizontalLayout_5->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(tab_WndFFTPartEst);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(240, 80));
        groupBox_7->setMaximumSize(QSize(240, 16777215));
        verticalLayout_6 = new QVBoxLayout(groupBox_7);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_WndPartCht_PartCount = new QLabel(groupBox_7);
        label_WndPartCht_PartCount->setObjectName(QString::fromUtf8("label_WndPartCht_PartCount"));

        verticalLayout_6->addWidget(label_WndPartCht_PartCount);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_WndPartCht_showPartCount = new QLabel(groupBox_7);
        label_WndPartCht_showPartCount->setObjectName(QString::fromUtf8("label_WndPartCht_showPartCount"));

        horizontalLayout_15->addWidget(label_WndPartCht_showPartCount);

        SBox_WndPartCht_PartCount = new QSpinBox(groupBox_7);
        SBox_WndPartCht_PartCount->setObjectName(QString::fromUtf8("SBox_WndPartCht_PartCount"));
        SBox_WndPartCht_PartCount->setEnabled(true);
        SBox_WndPartCht_PartCount->setMaximum(30);
        SBox_WndPartCht_PartCount->setSingleStep(20000);
        SBox_WndPartCht_PartCount->setValue(6);

        horizontalLayout_15->addWidget(SBox_WndPartCht_PartCount);


        verticalLayout_6->addLayout(horizontalLayout_15);

        btn_updateWndFFTPartCht = new QPushButton(groupBox_7);
        btn_updateWndFFTPartCht->setObjectName(QString::fromUtf8("btn_updateWndFFTPartCht"));

        verticalLayout_6->addWidget(btn_updateWndFFTPartCht);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);


        horizontalLayout_5->addWidget(groupBox_7);

        tabWidget->addTab(tab_WndFFTPartEst, QString());
        tab_WndFFTPartResult = new QWidget();
        tab_WndFFTPartResult->setObjectName(QString::fromUtf8("tab_WndFFTPartResult"));
        horizontalLayout_6 = new QHBoxLayout(tab_WndFFTPartResult);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        groupBox_SpecConstrainRatio = new QGroupBox(tab_WndFFTPartResult);
        groupBox_SpecConstrainRatio->setObjectName(QString::fromUtf8("groupBox_SpecConstrainRatio"));
        HLayout_WndSepcConstrainOutput = new QHBoxLayout(groupBox_SpecConstrainRatio);
        HLayout_WndSepcConstrainOutput->setSpacing(6);
        HLayout_WndSepcConstrainOutput->setContentsMargins(11, 11, 11, 11);
        HLayout_WndSepcConstrainOutput->setObjectName(QString::fromUtf8("HLayout_WndSepcConstrainOutput"));

        horizontalLayout_6->addWidget(groupBox_SpecConstrainRatio);

        groupBox_10 = new QGroupBox(tab_WndFFTPartResult);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setMinimumSize(QSize(240, 80));
        groupBox_10->setMaximumSize(QSize(240, 16777215));
        verticalLayout_7 = new QVBoxLayout(groupBox_10);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_MaxConstrainDbPos = new QLabel(groupBox_10);
        label_MaxConstrainDbPos->setObjectName(QString::fromUtf8("label_MaxConstrainDbPos"));

        horizontalLayout_7->addWidget(label_MaxConstrainDbPos);

        SBox_MaxConstrainDbPos = new QSpinBox(groupBox_10);
        SBox_MaxConstrainDbPos->setObjectName(QString::fromUtf8("SBox_MaxConstrainDbPos"));
        SBox_MaxConstrainDbPos->setMinimumSize(QSize(72, 0));
        SBox_MaxConstrainDbPos->setMaximumSize(QSize(72, 16777215));
        SBox_MaxConstrainDbPos->setMaximum(140);
        SBox_MaxConstrainDbPos->setValue(55);

        horizontalLayout_7->addWidget(SBox_MaxConstrainDbPos);


        verticalLayout_7->addLayout(horizontalLayout_7);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_PeakFreqDriftRatio = new QLabel(groupBox_10);
        label_PeakFreqDriftRatio->setObjectName(QString::fromUtf8("label_PeakFreqDriftRatio"));

        horizontalLayout_18->addWidget(label_PeakFreqDriftRatio);

        DSBox_PeakFreqDriftRatio = new QDoubleSpinBox(groupBox_10);
        DSBox_PeakFreqDriftRatio->setObjectName(QString::fromUtf8("DSBox_PeakFreqDriftRatio"));
        DSBox_PeakFreqDriftRatio->setMinimumSize(QSize(72, 0));
        DSBox_PeakFreqDriftRatio->setMaximumSize(QSize(72, 16777215));
        DSBox_PeakFreqDriftRatio->setMaximum(50.000000000000000);
        DSBox_PeakFreqDriftRatio->setValue(25.000000000000000);

        horizontalLayout_18->addWidget(DSBox_PeakFreqDriftRatio);


        verticalLayout_7->addLayout(horizontalLayout_18);

        checkBox_forcePt2DBVal = new QCheckBox(groupBox_10);
        checkBox_forcePt2DBVal->setObjectName(QString::fromUtf8("checkBox_forcePt2DBVal"));
        checkBox_forcePt2DBVal->setCheckable(false);
        checkBox_forcePt2DBVal->setChecked(false);

        verticalLayout_7->addWidget(checkBox_forcePt2DBVal);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_forcePt2DBVal = new QLabel(groupBox_10);
        label_forcePt2DBVal->setObjectName(QString::fromUtf8("label_forcePt2DBVal"));

        horizontalLayout_19->addWidget(label_forcePt2DBVal);

        DSBox_forcePt2DBVal = new QDoubleSpinBox(groupBox_10);
        DSBox_forcePt2DBVal->setObjectName(QString::fromUtf8("DSBox_forcePt2DBVal"));
        DSBox_forcePt2DBVal->setEnabled(true);
        DSBox_forcePt2DBVal->setMinimumSize(QSize(72, 0));
        DSBox_forcePt2DBVal->setMaximumSize(QSize(72, 16777215));
        DSBox_forcePt2DBVal->setValue(20.000000000000000);

        horizontalLayout_19->addWidget(DSBox_forcePt2DBVal);


        verticalLayout_7->addLayout(horizontalLayout_19);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_EnhanceConstrainPos = new QLabel(groupBox_10);
        label_EnhanceConstrainPos->setObjectName(QString::fromUtf8("label_EnhanceConstrainPos"));

        horizontalLayout_16->addWidget(label_EnhanceConstrainPos);

        SBox__EnheaceConstrainPos = new QSpinBox(groupBox_10);
        SBox__EnheaceConstrainPos->setObjectName(QString::fromUtf8("SBox__EnheaceConstrainPos"));
        SBox__EnheaceConstrainPos->setMinimumSize(QSize(72, 0));
        SBox__EnheaceConstrainPos->setMaximumSize(QSize(72, 16777215));
        SBox__EnheaceConstrainPos->setMaximum(20);
        SBox__EnheaceConstrainPos->setValue(1);
        SBox__EnheaceConstrainPos->setDisplayIntegerBase(10);

        horizontalLayout_16->addWidget(SBox__EnheaceConstrainPos);


        verticalLayout_7->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_EnhanceConstrainRatio = new QLabel(groupBox_10);
        label_EnhanceConstrainRatio->setObjectName(QString::fromUtf8("label_EnhanceConstrainRatio"));

        horizontalLayout_17->addWidget(label_EnhanceConstrainRatio);

        DSbox_EnhanceConstrainRatio = new QDoubleSpinBox(groupBox_10);
        DSbox_EnhanceConstrainRatio->setObjectName(QString::fromUtf8("DSbox_EnhanceConstrainRatio"));
        DSbox_EnhanceConstrainRatio->setMinimumSize(QSize(72, 0));
        DSbox_EnhanceConstrainRatio->setMaximumSize(QSize(72, 16777215));
        DSbox_EnhanceConstrainRatio->setMaximum(1000.000000000000000);
        DSbox_EnhanceConstrainRatio->setValue(250.000000000000000);

        horizontalLayout_17->addWidget(DSbox_EnhanceConstrainRatio);


        verticalLayout_7->addLayout(horizontalLayout_17);

        label_constrainSidePtCount = new QLabel(groupBox_10);
        label_constrainSidePtCount->setObjectName(QString::fromUtf8("label_constrainSidePtCount"));

        verticalLayout_7->addWidget(label_constrainSidePtCount);

        label_NoiseUnConstrainFreqInterval = new QLabel(groupBox_10);
        label_NoiseUnConstrainFreqInterval->setObjectName(QString::fromUtf8("label_NoiseUnConstrainFreqInterval"));

        verticalLayout_7->addWidget(label_NoiseUnConstrainFreqInterval);

        label_NoiseToBeSignalFreqInterval = new QLabel(groupBox_10);
        label_NoiseToBeSignalFreqInterval->setObjectName(QString::fromUtf8("label_NoiseToBeSignalFreqInterval"));

        verticalLayout_7->addWidget(label_NoiseToBeSignalFreqInterval);

        btn_GenWndSpecConstrainResult = new QPushButton(groupBox_10);
        btn_GenWndSpecConstrainResult->setObjectName(QString::fromUtf8("btn_GenWndSpecConstrainResult"));

        verticalLayout_7->addWidget(btn_GenWndSpecConstrainResult);

        verticalSpacer_4 = new QSpacerItem(20, 231, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);


        horizontalLayout_6->addWidget(groupBox_10);

        tabWidget->addTab(tab_WndFFTPartResult, QString());
        tab_activeWndSpec = new QWidget();
        tab_activeWndSpec->setObjectName(QString::fromUtf8("tab_activeWndSpec"));
        horizontalLayout_30 = new QHBoxLayout(tab_activeWndSpec);
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        groupBox_15 = new QGroupBox(tab_activeWndSpec);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        groupBox_15->setMinimumSize(QSize(0, 0));
        VLayout_ActiveFFTWndSpectrum_Cht = new QVBoxLayout(groupBox_15);
        VLayout_ActiveFFTWndSpectrum_Cht->setSpacing(6);
        VLayout_ActiveFFTWndSpectrum_Cht->setContentsMargins(11, 11, 11, 11);
        VLayout_ActiveFFTWndSpectrum_Cht->setObjectName(QString::fromUtf8("VLayout_ActiveFFTWndSpectrum_Cht"));

        horizontalLayout_30->addWidget(groupBox_15);

        groupBox_12 = new QGroupBox(tab_activeWndSpec);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setMinimumSize(QSize(0, 80));
        groupBox_12->setMaximumSize(QSize(250, 16777215));
        verticalLayout_11 = new QVBoxLayout(groupBox_12);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_13 = new QGroupBox(groupBox_12);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setMinimumSize(QSize(0, 0));
        horizontalLayout_26 = new QHBoxLayout(groupBox_13);
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        radioButton_ActiveWndFFTValType_AbsoluteVal = new QRadioButton(groupBox_13);
        radioButton_ActiveWndFFTValType_AbsoluteVal->setObjectName(QString::fromUtf8("radioButton_ActiveWndFFTValType_AbsoluteVal"));

        horizontalLayout_26->addWidget(radioButton_ActiveWndFFTValType_AbsoluteVal);

        radioButton_ActiveWndFFTValType_db = new QRadioButton(groupBox_13);
        radioButton_ActiveWndFFTValType_db->setObjectName(QString::fromUtf8("radioButton_ActiveWndFFTValType_db"));
        radioButton_ActiveWndFFTValType_db->setChecked(false);

        horizontalLayout_26->addWidget(radioButton_ActiveWndFFTValType_db);

        radioButton_ActiveWndFFTValType_AbsDb = new QRadioButton(groupBox_13);
        radioButton_ActiveWndFFTValType_AbsDb->setObjectName(QString::fromUtf8("radioButton_ActiveWndFFTValType_AbsDb"));
        radioButton_ActiveWndFFTValType_AbsDb->setChecked(true);

        horizontalLayout_26->addWidget(radioButton_ActiveWndFFTValType_AbsDb);


        verticalLayout_11->addWidget(groupBox_13);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_ActiveWndFFTShowPointCount = new QLabel(groupBox_12);
        label_ActiveWndFFTShowPointCount->setObjectName(QString::fromUtf8("label_ActiveWndFFTShowPointCount"));

        horizontalLayout_27->addWidget(label_ActiveWndFFTShowPointCount);

        SBox_ActiveWndFFTShowPointCount = new QSpinBox(groupBox_12);
        SBox_ActiveWndFFTShowPointCount->setObjectName(QString::fromUtf8("SBox_ActiveWndFFTShowPointCount"));
        SBox_ActiveWndFFTShowPointCount->setEnabled(true);
        SBox_ActiveWndFFTShowPointCount->setMaximum(100000);
        SBox_ActiveWndFFTShowPointCount->setSingleStep(1);
        SBox_ActiveWndFFTShowPointCount->setValue(2000);

        horizontalLayout_27->addWidget(SBox_ActiveWndFFTShowPointCount);


        verticalLayout_11->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_ActiveWndFFTShowMaxFreq = new QLabel(groupBox_12);
        label_ActiveWndFFTShowMaxFreq->setObjectName(QString::fromUtf8("label_ActiveWndFFTShowMaxFreq"));

        horizontalLayout_28->addWidget(label_ActiveWndFFTShowMaxFreq);

        SBox_ActiveWndFFTShowMaxFreq = new QSpinBox(groupBox_12);
        SBox_ActiveWndFFTShowMaxFreq->setObjectName(QString::fromUtf8("SBox_ActiveWndFFTShowMaxFreq"));
        SBox_ActiveWndFFTShowMaxFreq->setEnabled(true);
        SBox_ActiveWndFFTShowMaxFreq->setMaximum(100000);
        SBox_ActiveWndFFTShowMaxFreq->setValue(1000);

        horizontalLayout_28->addWidget(SBox_ActiveWndFFTShowMaxFreq);


        verticalLayout_11->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_ActiveWndFFTShowMinVal = new QLabel(groupBox_12);
        label_ActiveWndFFTShowMinVal->setObjectName(QString::fromUtf8("label_ActiveWndFFTShowMinVal"));

        horizontalLayout_29->addWidget(label_ActiveWndFFTShowMinVal);

        SBox_ActiveWndFFTShowMinVal = new QSpinBox(groupBox_12);
        SBox_ActiveWndFFTShowMinVal->setObjectName(QString::fromUtf8("SBox_ActiveWndFFTShowMinVal"));
        SBox_ActiveWndFFTShowMinVal->setEnabled(true);
        SBox_ActiveWndFFTShowMinVal->setMinimum(-10000);
        SBox_ActiveWndFFTShowMinVal->setMaximum(100000);
        SBox_ActiveWndFFTShowMinVal->setValue(-100);

        horizontalLayout_29->addWidget(SBox_ActiveWndFFTShowMinVal);


        verticalLayout_11->addLayout(horizontalLayout_29);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        btn_GenActiveWndFFTGraph = new QPushButton(groupBox_12);
        btn_GenActiveWndFFTGraph->setObjectName(QString::fromUtf8("btn_GenActiveWndFFTGraph"));

        horizontalLayout_35->addWidget(btn_GenActiveWndFFTGraph);

        btn_updateActiveWndFFTCht = new QPushButton(groupBox_12);
        btn_updateActiveWndFFTCht->setObjectName(QString::fromUtf8("btn_updateActiveWndFFTCht"));

        horizontalLayout_35->addWidget(btn_updateActiveWndFFTCht);


        verticalLayout_11->addLayout(horizontalLayout_35);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_3 = new QLabel(groupBox_12);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_31->addWidget(label_3);

        label_2 = new QLabel(groupBox_12);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_31->addWidget(label_2);


        verticalLayout_11->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        label_4 = new QLabel(groupBox_12);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_32->addWidget(label_4);

        spinBox = new QSpinBox(groupBox_12);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_32->addWidget(spinBox);

        spinBox_2 = new QSpinBox(groupBox_12);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        horizontalLayout_32->addWidget(spinBox_2);

        spinBox_3 = new QSpinBox(groupBox_12);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        horizontalLayout_32->addWidget(spinBox_3);


        verticalLayout_11->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_5 = new QLabel(groupBox_12);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_33->addWidget(label_5);

        spinBox_4 = new QSpinBox(groupBox_12);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

        horizontalLayout_33->addWidget(spinBox_4);

        spinBox_5 = new QSpinBox(groupBox_12);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));

        horizontalLayout_33->addWidget(spinBox_5);

        spinBox_6 = new QSpinBox(groupBox_12);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));

        horizontalLayout_33->addWidget(spinBox_6);


        verticalLayout_11->addLayout(horizontalLayout_33);

        btn_GenActiveWndFFTGraph_2 = new QPushButton(groupBox_12);
        btn_GenActiveWndFFTGraph_2->setObjectName(QString::fromUtf8("btn_GenActiveWndFFTGraph_2"));

        verticalLayout_11->addWidget(btn_GenActiveWndFFTGraph_2);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        label_8 = new QLabel(groupBox_12);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_38->addWidget(label_8);

        progressBar = new QProgressBar(groupBox_12);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        horizontalLayout_38->addWidget(progressBar);


        verticalLayout_11->addLayout(horizontalLayout_38);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        label_6 = new QLabel(groupBox_12);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_36->addWidget(label_6);

        horizontalSlider = new QSlider(groupBox_12);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_36->addWidget(horizontalSlider);


        verticalLayout_11->addLayout(horizontalLayout_36);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        label_7 = new QLabel(groupBox_12);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_37->addWidget(label_7);

        horizontalSlider_2 = new QSlider(groupBox_12);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_37->addWidget(horizontalSlider_2);


        verticalLayout_11->addLayout(horizontalLayout_37);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer);


        horizontalLayout_30->addWidget(groupBox_12);

        tabWidget->addTab(tab_activeWndSpec, QString());

        verticalLayout_8->addWidget(tabWidget);

        tabWidget_Main->addTab(tab_WndSpecAns, QString());
        tab_WndSpecConstrainOutput = new QWidget();
        tab_WndSpecConstrainOutput->setObjectName(QString::fromUtf8("tab_WndSpecConstrainOutput"));
        VLayout_EffOscWidget = new QVBoxLayout(tab_WndSpecConstrainOutput);
        VLayout_EffOscWidget->setSpacing(6);
        VLayout_EffOscWidget->setContentsMargins(11, 11, 11, 11);
        VLayout_EffOscWidget->setObjectName(QString::fromUtf8("VLayout_EffOscWidget"));
        tabWidget_Main->addTab(tab_WndSpecConstrainOutput, QString());

        verticalLayout->addWidget(tabWidget_Main);


        retranslateUi(FFTWindowWgtClass);

        tabWidget_Main->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);
        comboBox_WndType->setCurrentIndex(1);
        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(FFTWindowWgtClass);
    } // setupUi

    void retranslateUi(QWidget *FFTWindowWgtClass)
    {
        FFTWindowWgtClass->setWindowTitle(QApplication::translate("FFTWindowWgtClass", "FFTWindowWgt", nullptr));
        groupBox_baseSig_chart->setTitle(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260\347\273\230\345\210\266", nullptr));
        groupBox_5->setTitle(QApplication::translate("FFTWindowWgtClass", "\346\227\266\345\237\237\347\252\227\345\236\213\346\216\247\345\210\266", nullptr));
        label->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\236\213", nullptr));
        comboBox_WndType->setItemText(0, QApplication::translate("FFTWindowWgtClass", "\347\237\251\345\275\242", nullptr));
        comboBox_WndType->setItemText(1, QApplication::translate("FFTWindowWgtClass", "Hann", nullptr));

        groupBox_9->setTitle(QApplication::translate("FFTWindowWgtClass", "\351\225\277\345\272\246\345\256\232\344\271\211", nullptr));
        radioBtn_WndLengthType_Point->setText(QApplication::translate("FFTWindowWgtClass", "\347\202\271\346\225\260", nullptr));
        radioBtn_WndLengthType_Time->setText(QApplication::translate("FFTWindowWgtClass", "\346\227\266\351\225\277", nullptr));
        label_WndLengthPoint->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\236\213\347\202\271\346\225\260\357\274\232", nullptr));
        label_WndLength_Time->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\236\213\346\227\266\351\225\277(ms)\357\274\232", nullptr));
        label_WndSampleRate->setText(QApplication::translate("FFTWindowWgtClass", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_resultWndLength_Point->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\236\213\347\255\211\344\273\267\347\202\271\346\225\260\357\274\232", nullptr));
        label_resultWndLength_Time->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\236\213\347\255\211\344\273\267\346\227\266\351\225\277\357\274\232", nullptr));
        label_WndSTFTFreqDelta->setText(QApplication::translate("FFTWindowWgtClass", "FFT\350\276\223\345\207\272\351\242\221\347\216\207\351\227\264\351\232\224\357\274\232", nullptr));
        label_GenState->setText(QApplication::translate("FFTWindowWgtClass", "\347\224\237\346\210\220\347\212\266\346\200\201\357\274\232", nullptr));
        btn_GenWndTimeGraph->setText(QApplication::translate("FFTWindowWgtClass", "\347\224\237\346\210\220\347\252\227\345\236\213", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_GenWndPt), QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260", nullptr));
        groupBox_ActiveSig_chart->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\206\262\345\207\273\350\260\203\345\210\266\345\207\275\346\225\260\347\273\230\345\210\266", nullptr));
        groupBox_8->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\206\262\345\207\273\350\260\203\345\210\266\345\207\275\346\225\260", nullptr));
        groupBox_11->setTitle(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260\345\217\202\346\225\260", nullptr));
        label_ActiveWnd_sampleRate->setText(QApplication::translate("FFTWindowWgtClass", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_ActiveWnd_WndType->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260\347\261\273\345\236\213", nullptr));
        label_ActiveWnd_FFTWndPtCount->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260\347\202\271\346\225\260", nullptr));
        groupBox_ActiveStartType->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\206\262\345\207\273\345\274\200\345\247\213\346\227\266\351\227\264\347\261\273\345\236\213", nullptr));
        radioButton_ActiveStartType_Time->setText(QApplication::translate("FFTWindowWgtClass", "\346\227\266\351\227\264", nullptr));
        radioButton_ActiveStartType_Ratio->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\217\243\346\257\224\344\276\213", nullptr));
        label_ActiveStartTime->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\210ms\357\274\211", nullptr));
        label_ActiveStartRatio->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\200\345\247\213\344\275\215\347\275\256\346\257\224\344\276\213\357\274\210%\357\274\211", nullptr));
        label_IncreaseTime->setText(QApplication::translate("FFTWindowWgtClass", "\344\270\212\345\215\207\346\227\266\351\227\264\357\274\210ms\357\274\211", nullptr));
        btn_GenActiveFunc->setText(QApplication::translate("FFTWindowWgtClass", "\347\224\237\346\210\220\350\260\203\345\210\266\345\207\275\346\225\260", nullptr));
        groupBox_ActiveWnd_ShowType->setTitle(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\345\257\271\350\261\241", nullptr));
        checkBox_ActiveWnd_ShowType_STFTWnd->setText(QApplication::translate("FFTWindowWgtClass", "STFT\347\252\227", nullptr));
        checkBox_ActiveWnd_ShowType_ActiveVal->setText(QApplication::translate("FFTWindowWgtClass", "\346\277\200\345\217\221\345\207\275\346\225\260", nullptr));
        checkBox_ActiveWnd_ShowType_ActiveWnd->setText(QApplication::translate("FFTWindowWgtClass", "\346\277\200\345\217\221\347\252\227", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("FFTWindowWgtClass", "\346\277\200\345\217\221\350\260\203\345\210\266\345\207\275\346\225\260", nullptr));
        groupBox->setTitle(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\275\242\351\242\221\350\260\261", nullptr));
        groupBox_4->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\210\206\346\236\220\346\216\247\345\210\266", nullptr));
        groupBox_3->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\200\274\346\230\276\347\244\272\346\226\271\345\274\217", nullptr));
        radioButton_WndFFTValType_AbsoluteVal->setText(QApplication::translate("FFTWindowWgtClass", "\347\273\235\345\257\271\345\200\274", nullptr));
        radioButton_WndFFTValType_db->setText(QApplication::translate("FFTWindowWgtClass", "db", nullptr));
        label_WndFFTShowMaxFreq_2->setText(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\346\200\273\347\202\271\346\225\260", nullptr));
        label_WndFFTShowMaxFreq->setText(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\346\234\200\345\244\247\351\242\221\347\216\207", nullptr));
        label_WndFFTShowMinVal->setText(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\346\234\200\345\260\217\346\225\260\345\200\274", nullptr));
        btn_GenWndFFTGraph->setText(QApplication::translate("FFTWindowWgtClass", "\351\242\221\350\260\261\345\210\206\346\236\220", nullptr));
        btn_updateWndFFTCht->setText(QApplication::translate("FFTWindowWgtClass", "\345\210\267\346\226\260\345\233\276\345\203\217", nullptr));
        groupBox_2->setTitle(QApplication::translate("FFTWindowWgtClass", "\351\242\221\350\260\261\346\225\260\345\200\274", nullptr));
        label_WndFFTDeltaFreq->setText(QApplication::translate("FFTWindowWgtClass", "\345\233\276\345\203\217\351\242\221\347\216\207\351\227\264\351\232\224\357\274\232", nullptr));
        label_WndFFTSubPartCount->setText(QApplication::translate("FFTWindowWgtClass", "\347\273\237\350\256\241\346\227\201\347\223\243\344\270\252\346\225\260\357\274\232", nullptr));
        label_mainPartMaxFFTError->setText(QApplication::translate("FFTWindowWgtClass", "\344\270\273\345\263\260\346\234\200\345\244\247\350\257\257\345\267\256\357\274\232", nullptr));
        label_mainPart10dbHalfWidth->setText(QApplication::translate("FFTWindowWgtClass", "\344\270\273\345\263\26010db\345\215\212\345\256\275\357\274\232", nullptr));
        label_firstPartHeight->setText(QApplication::translate("FFTWindowWgtClass", "\347\254\254\344\270\200\346\227\201\347\223\243\351\253\230\345\272\246\357\274\232", nullptr));
        label_firstPartFreq->setText(QApplication::translate("FFTWindowWgtClass", "\347\254\254\344\270\200\346\227\201\347\223\243\344\275\215\347\275\256\357\274\232", nullptr));
        label_SecondPartHeight->setText(QApplication::translate("FFTWindowWgtClass", "\347\254\254\344\272\214\346\227\201\347\223\243\351\253\230\345\272\246\357\274\232", nullptr));
        label_SecondPartFreq->setText(QApplication::translate("FFTWindowWgtClass", "\347\254\254\344\272\214\346\227\201\347\223\243\344\275\215\347\275\256\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_spectrum), QApplication::translate("FFTWindowWgtClass", "STFT\347\252\227\351\242\221\350\260\261", nullptr));
        groupBox_6->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\263\260\345\200\274\345\275\242\346\200\201\347\273\237\350\256\241", nullptr));
        groupBox_7->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\210\206\346\236\220\346\216\247\345\210\266", nullptr));
        label_WndPartCht_PartCount->setText(QApplication::translate("FFTWindowWgtClass", "\347\273\237\350\256\241\345\263\260\345\200\274\346\225\260\351\207\217\357\274\232", nullptr));
        label_WndPartCht_showPartCount->setText(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\346\200\273\345\263\260\346\225\260\351\207\217", nullptr));
        btn_updateWndFFTPartCht->setText(QApplication::translate("FFTWindowWgtClass", "\345\210\267\346\226\260\345\233\276\345\203\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_WndFFTPartEst), QApplication::translate("FFTWindowWgtClass", "\345\263\260\345\200\274\345\275\242\346\200\201\347\273\237\350\256\241", nullptr));
        groupBox_SpecConstrainRatio->setTitle(QApplication::translate("FFTWindowWgtClass", "\350\276\271\347\274\230\345\263\260\345\200\274\346\212\221\345\210\266\346\257\224\344\276\213", nullptr));
        groupBox_10->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\210\206\346\236\220\346\216\247\345\210\266", nullptr));
        label_MaxConstrainDbPos->setText(QApplication::translate("FFTWindowWgtClass", "\346\234\200\345\244\247\346\212\221\345\210\266\350\214\203\345\233\264(db)", nullptr));
        label_PeakFreqDriftRatio->setText(QApplication::translate("FFTWindowWgtClass", "\345\263\260\345\200\274\351\242\221\347\216\207\345\201\217\347\247\273\346\257\224\344\276\213(%)", nullptr));
        checkBox_forcePt2DBVal->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\272\345\210\266\347\254\254\344\272\214\347\202\271\346\225\260\345\200\274", nullptr));
        label_forcePt2DBVal->setText(QApplication::translate("FFTWindowWgtClass", "\347\254\254\344\272\214\347\202\271\346\214\207\345\256\232DB\357\274\232", nullptr));
        label_EnhanceConstrainPos->setText(QApplication::translate("FFTWindowWgtClass", "\345\220\257\347\224\250\345\242\236\345\274\272\346\212\221\345\210\266\344\275\215\347\275\256", nullptr));
        label_EnhanceConstrainRatio->setText(QApplication::translate("FFTWindowWgtClass", "\345\242\236\345\274\272\346\212\221\345\210\266\346\257\224\344\276\213\357\274\210%\357\274\211", nullptr));
        label_constrainSidePtCount->setText(QApplication::translate("FFTWindowWgtClass", "\346\212\221\345\210\266\350\276\271\347\274\230\347\202\271\344\270\252\346\225\260\357\274\232", nullptr));
        label_NoiseUnConstrainFreqInterval->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\350\260\261\345\231\252\345\243\260\346\227\240\346\263\225\346\212\221\345\210\266\350\267\235\347\246\273\357\274\232", nullptr));
        label_NoiseToBeSignalFreqInterval->setText(QApplication::translate("FFTWindowWgtClass", "\347\252\227\350\260\261\345\231\252\345\243\260\345\216\213\345\210\266\344\270\273\344\277\241\345\217\267\350\267\235\347\246\273\357\274\232", nullptr));
        btn_GenWndSpecConstrainResult->setText(QApplication::translate("FFTWindowWgtClass", "\347\224\237\346\210\220\346\212\221\345\210\266\347\273\223\346\236\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_WndFFTPartResult), QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260\351\242\221\350\260\261\346\212\221\345\210\266\350\276\223\345\207\272", nullptr));
        groupBox_15->setTitle(QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\275\242\351\242\221\350\260\261", nullptr));
        groupBox_12->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\210\206\346\236\220\346\216\247\345\210\266", nullptr));
        groupBox_13->setTitle(QApplication::translate("FFTWindowWgtClass", "\345\200\274\346\230\276\347\244\272\346\226\271\345\274\217", nullptr));
        radioButton_ActiveWndFFTValType_AbsoluteVal->setText(QApplication::translate("FFTWindowWgtClass", "\347\273\235\345\257\271\345\200\274", nullptr));
        radioButton_ActiveWndFFTValType_db->setText(QApplication::translate("FFTWindowWgtClass", "db", nullptr));
        radioButton_ActiveWndFFTValType_AbsDb->setText(QApplication::translate("FFTWindowWgtClass", "\347\273\235\345\257\271db", nullptr));
        label_ActiveWndFFTShowPointCount->setText(QApplication::translate("FFTWindowWgtClass", "\350\256\241\347\256\227\346\200\273\347\202\271\346\225\260", nullptr));
        label_ActiveWndFFTShowMaxFreq->setText(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\346\234\200\345\244\247\351\242\221\347\216\207", nullptr));
        label_ActiveWndFFTShowMinVal->setText(QApplication::translate("FFTWindowWgtClass", "\346\230\276\347\244\272\346\234\200\345\260\217\346\225\260\345\200\274", nullptr));
        btn_GenActiveWndFFTGraph->setText(QApplication::translate("FFTWindowWgtClass", "\351\242\221\350\260\261\345\210\206\346\236\220", nullptr));
        btn_updateActiveWndFFTCht->setText(QApplication::translate("FFTWindowWgtClass", "\345\210\267\346\226\260\345\233\276\345\203\217", nullptr));
        label_3->setText(QApplication::translate("FFTWindowWgtClass", "\346\211\253\346\217\217\351\227\264\351\232\224\357\274\232", nullptr));
        label_2->setText(QApplication::translate("FFTWindowWgtClass", "[\345\274\200\345\247\213][\347\273\223\346\235\237][\351\227\264\351\232\224]", nullptr));
        label_4->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\200\345\247\213\346\257\224\344\276\213\357\274\232", nullptr));
        label_5->setText(QApplication::translate("FFTWindowWgtClass", "\344\270\212\345\215\207\346\227\266\351\227\264\357\274\232", nullptr));
        btn_GenActiveWndFFTGraph_2->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\200\345\247\213\346\211\253\346\217\217", nullptr));
        label_8->setText(QApplication::translate("FFTWindowWgtClass", "\346\211\253\346\217\217\350\277\233\345\272\246", nullptr));
        label_6->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\200\345\247\213\344\275\215\347\275\256\346\257\224\344\276\213\357\274\232\357\274\2100%\357\274\211", nullptr));
        label_7->setText(QApplication::translate("FFTWindowWgtClass", "\345\274\200\345\247\213\344\275\215\347\275\256\346\257\224\344\276\213\357\274\232\357\274\2100%\357\274\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_activeWndSpec), QApplication::translate("FFTWindowWgtClass", "\346\277\200\345\217\221\350\260\203\345\210\266\347\252\227\351\242\221\350\260\261", nullptr));
        tabWidget_Main->setTabText(tabWidget_Main->indexOf(tab_WndSpecAns), QApplication::translate("FFTWindowWgtClass", "\347\252\227\345\207\275\346\225\260\345\210\206\346\236\220", nullptr));
        tabWidget_Main->setTabText(tabWidget_Main->indexOf(tab_WndSpecConstrainOutput), QApplication::translate("FFTWindowWgtClass", "\347\252\227\350\260\261\346\212\221\345\210\266\350\276\223\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FFTWindowWgtClass: public Ui_FFTWindowWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFTWINDOWWGT_H
