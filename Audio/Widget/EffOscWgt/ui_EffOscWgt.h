/********************************************************************************
** Form generated from reading UI file 'EffOscWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFOSCWGT_H
#define UI_EFFOSCWGT_H

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

class Ui_EffOscWgtClass
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab_WndSpecAns;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_baseSig_chart;
    QHBoxLayout *HLayout_TimeCht_Wnd;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
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
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_WndSampleRate;
    QSpinBox *SBox_WndSampleRate;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_WndLength_Time;
    QDoubleSpinBox *DSBox_WndLength_TimeMSec;
    QLabel *label_resultWndLength_Point;
    QLabel *label_resultWndLength_Time;
    QLabel *label_WndSTFTFreqDelta;
    QPushButton *btn_GenWndTimeGraph;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_ActiveWnd_sampleRate;
    QLabel *label_ActiveWnd_WndType;
    QLabel *label_ActiveWnd_FFTWndPtCount;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_ActiveStartRatio;
    QDoubleSpinBox *DSBox_ActiveStartRatio;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_IncreaseTime;
    QDoubleSpinBox *DSBox_IncreaseTime;
    QPushButton *btn_GenActiveWndTimeGraph;
    QGroupBox *groupBox_ActiveWnd_ShowType;
    QHBoxLayout *horizontalLayout_34;
    QCheckBox *checkBox_ActiveWnd_ShowType_STFTWnd;
    QCheckBox *checkBox_ActiveWnd_ShowType_ActiveVal;
    QCheckBox *checkBox_ActiveWnd_ShowType_ActiveWnd;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget_3;
    QWidget *tab_activeWndSpec;
    QHBoxLayout *horizontalLayout_30;
    QGroupBox *groupBox_15;
    QVBoxLayout *VLayout_ActiveFFTWndSpectrum_Cht;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_4;
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
    QLabel *label_ActvieWndFFTGenState;
    QProgressBar *progressBar_ActvieWndFFTGenState;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_GenActiveWndFFTGraph;
    QPushButton *btn_updateActiveWndFFTCht;
    QSpacerItem *verticalSpacer_5;
    QWidget *tab_4;

    void setupUi(QWidget *EffOscWgtClass)
    {
        if (EffOscWgtClass->objectName().isEmpty())
            EffOscWgtClass->setObjectName(QString::fromUtf8("EffOscWgtClass"));
        EffOscWgtClass->resize(1283, 881);
        verticalLayout_3 = new QVBoxLayout(EffOscWgtClass);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget_2 = new QTabWidget(EffOscWgtClass);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_WndSpecAns = new QWidget();
        tab_WndSpecAns->setObjectName(QString::fromUtf8("tab_WndSpecAns"));
        verticalLayout_9 = new QVBoxLayout(tab_WndSpecAns);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_baseSig_chart = new QGroupBox(tab_WndSpecAns);
        groupBox_baseSig_chart->setObjectName(QString::fromUtf8("groupBox_baseSig_chart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_baseSig_chart->sizePolicy().hasHeightForWidth());
        groupBox_baseSig_chart->setSizePolicy(sizePolicy);
        groupBox_baseSig_chart->setMinimumSize(QSize(800, 250));
        groupBox_baseSig_chart->setMaximumSize(QSize(1980, 440));
        HLayout_TimeCht_Wnd = new QHBoxLayout(groupBox_baseSig_chart);
        HLayout_TimeCht_Wnd->setSpacing(6);
        HLayout_TimeCht_Wnd->setContentsMargins(11, 11, 11, 11);
        HLayout_TimeCht_Wnd->setObjectName(QString::fromUtf8("HLayout_TimeCht_Wnd"));

        horizontalLayout_2->addWidget(groupBox_baseSig_chart);

        tabWidget = new QTabWidget(tab_WndSpecAns);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMaximumSize(QSize(250, 16777215));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_WndType = new QComboBox(tab);
        comboBox_WndType->addItem(QString());
        comboBox_WndType->addItem(QString());
        comboBox_WndType->setObjectName(QString::fromUtf8("comboBox_WndType"));

        horizontalLayout->addWidget(comboBox_WndType);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_9 = new QGroupBox(tab);
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


        verticalLayout->addWidget(groupBox_9);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_WndLengthPoint = new QLabel(tab);
        label_WndLengthPoint->setObjectName(QString::fromUtf8("label_WndLengthPoint"));

        horizontalLayout_9->addWidget(label_WndLengthPoint);

        SBox_WndLengthPointCount = new QSpinBox(tab);
        SBox_WndLengthPointCount->setObjectName(QString::fromUtf8("SBox_WndLengthPointCount"));
        SBox_WndLengthPointCount->setEnabled(false);
        SBox_WndLengthPointCount->setMaximum(100000);
        SBox_WndLengthPointCount->setValue(4096);

        horizontalLayout_9->addWidget(SBox_WndLengthPointCount);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_WndSampleRate = new QLabel(tab);
        label_WndSampleRate->setObjectName(QString::fromUtf8("label_WndSampleRate"));

        horizontalLayout_12->addWidget(label_WndSampleRate);

        SBox_WndSampleRate = new QSpinBox(tab);
        SBox_WndSampleRate->setObjectName(QString::fromUtf8("SBox_WndSampleRate"));
        SBox_WndSampleRate->setMaximum(100000);
        SBox_WndSampleRate->setValue(44100);

        horizontalLayout_12->addWidget(SBox_WndSampleRate);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_WndLength_Time = new QLabel(tab);
        label_WndLength_Time->setObjectName(QString::fromUtf8("label_WndLength_Time"));

        horizontalLayout_10->addWidget(label_WndLength_Time);

        DSBox_WndLength_TimeMSec = new QDoubleSpinBox(tab);
        DSBox_WndLength_TimeMSec->setObjectName(QString::fromUtf8("DSBox_WndLength_TimeMSec"));
        DSBox_WndLength_TimeMSec->setEnabled(false);
        DSBox_WndLength_TimeMSec->setMaximum(100000.000000000000000);
        DSBox_WndLength_TimeMSec->setValue(100.000000000000000);

        horizontalLayout_10->addWidget(DSBox_WndLength_TimeMSec);


        verticalLayout->addLayout(horizontalLayout_10);

        label_resultWndLength_Point = new QLabel(tab);
        label_resultWndLength_Point->setObjectName(QString::fromUtf8("label_resultWndLength_Point"));

        verticalLayout->addWidget(label_resultWndLength_Point);

        label_resultWndLength_Time = new QLabel(tab);
        label_resultWndLength_Time->setObjectName(QString::fromUtf8("label_resultWndLength_Time"));

        verticalLayout->addWidget(label_resultWndLength_Time);

        label_WndSTFTFreqDelta = new QLabel(tab);
        label_WndSTFTFreqDelta->setObjectName(QString::fromUtf8("label_WndSTFTFreqDelta"));

        verticalLayout->addWidget(label_WndSTFTFreqDelta);

        btn_GenWndTimeGraph = new QPushButton(tab);
        btn_GenWndTimeGraph->setObjectName(QString::fromUtf8("btn_GenWndTimeGraph"));

        verticalLayout->addWidget(btn_GenWndTimeGraph);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_11 = new QGroupBox(tab_2);
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


        verticalLayout_2->addWidget(groupBox_11);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_ActiveStartRatio = new QLabel(tab_2);
        label_ActiveStartRatio->setObjectName(QString::fromUtf8("label_ActiveStartRatio"));

        horizontalLayout_25->addWidget(label_ActiveStartRatio);

        DSBox_ActiveStartRatio = new QDoubleSpinBox(tab_2);
        DSBox_ActiveStartRatio->setObjectName(QString::fromUtf8("DSBox_ActiveStartRatio"));
        DSBox_ActiveStartRatio->setMinimum(0.000000000000000);
        DSBox_ActiveStartRatio->setMaximum(100.000000000000000);
        DSBox_ActiveStartRatio->setValue(34.000000000000000);

        horizontalLayout_25->addWidget(DSBox_ActiveStartRatio);


        verticalLayout_2->addLayout(horizontalLayout_25);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_IncreaseTime = new QLabel(tab_2);
        label_IncreaseTime->setObjectName(QString::fromUtf8("label_IncreaseTime"));

        horizontalLayout_21->addWidget(label_IncreaseTime);

        DSBox_IncreaseTime = new QDoubleSpinBox(tab_2);
        DSBox_IncreaseTime->setObjectName(QString::fromUtf8("DSBox_IncreaseTime"));
        DSBox_IncreaseTime->setMaximum(50.000000000000000);
        DSBox_IncreaseTime->setValue(15.000000000000000);

        horizontalLayout_21->addWidget(DSBox_IncreaseTime);


        verticalLayout_2->addLayout(horizontalLayout_21);

        btn_GenActiveWndTimeGraph = new QPushButton(tab_2);
        btn_GenActiveWndTimeGraph->setObjectName(QString::fromUtf8("btn_GenActiveWndTimeGraph"));

        verticalLayout_2->addWidget(btn_GenActiveWndTimeGraph);

        groupBox_ActiveWnd_ShowType = new QGroupBox(tab_2);
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


        verticalLayout_2->addWidget(groupBox_ActiveWnd_ShowType);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout_2->addWidget(tabWidget);


        verticalLayout_9->addLayout(horizontalLayout_2);

        tabWidget_3 = new QTabWidget(tab_WndSpecAns);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
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
        verticalLayout_4 = new QVBoxLayout(groupBox_12);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
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


        verticalLayout_4->addWidget(groupBox_13);

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


        verticalLayout_4->addLayout(horizontalLayout_27);

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


        verticalLayout_4->addLayout(horizontalLayout_28);

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


        verticalLayout_4->addLayout(horizontalLayout_29);

        label_ActvieWndFFTGenState = new QLabel(groupBox_12);
        label_ActvieWndFFTGenState->setObjectName(QString::fromUtf8("label_ActvieWndFFTGenState"));

        verticalLayout_4->addWidget(label_ActvieWndFFTGenState);

        progressBar_ActvieWndFFTGenState = new QProgressBar(groupBox_12);
        progressBar_ActvieWndFFTGenState->setObjectName(QString::fromUtf8("progressBar_ActvieWndFFTGenState"));
        progressBar_ActvieWndFFTGenState->setValue(24);

        verticalLayout_4->addWidget(progressBar_ActvieWndFFTGenState);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_GenActiveWndFFTGraph = new QPushButton(groupBox_12);
        btn_GenActiveWndFFTGraph->setObjectName(QString::fromUtf8("btn_GenActiveWndFFTGraph"));

        horizontalLayout_3->addWidget(btn_GenActiveWndFFTGraph);

        btn_updateActiveWndFFTCht = new QPushButton(groupBox_12);
        btn_updateActiveWndFFTCht->setObjectName(QString::fromUtf8("btn_updateActiveWndFFTCht"));

        horizontalLayout_3->addWidget(btn_updateActiveWndFFTCht);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);


        horizontalLayout_30->addWidget(groupBox_12);

        tabWidget_3->addTab(tab_activeWndSpec, QString());

        verticalLayout_9->addWidget(tabWidget_3);

        tabWidget_2->addTab(tab_WndSpecAns, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget_2->addTab(tab_4, QString());

        verticalLayout_3->addWidget(tabWidget_2);


        retranslateUi(EffOscWgtClass);

        tabWidget_2->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);
        comboBox_WndType->setCurrentIndex(1);
        tabWidget_3->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EffOscWgtClass);
    } // setupUi

    void retranslateUi(QWidget *EffOscWgtClass)
    {
        EffOscWgtClass->setWindowTitle(QApplication::translate("EffOscWgtClass", "EffOscWgt", nullptr));
        groupBox_baseSig_chart->setTitle(QApplication::translate("EffOscWgtClass", "\350\260\203\345\210\266\347\252\227\345\207\275\346\225\260\347\273\230\345\210\266", nullptr));
        label->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\236\213", nullptr));
        comboBox_WndType->setItemText(0, QApplication::translate("EffOscWgtClass", "\347\237\251\345\275\242", nullptr));
        comboBox_WndType->setItemText(1, QApplication::translate("EffOscWgtClass", "Hann", nullptr));

        groupBox_9->setTitle(QApplication::translate("EffOscWgtClass", "\351\225\277\345\272\246\345\256\232\344\271\211", nullptr));
        radioBtn_WndLengthType_Point->setText(QApplication::translate("EffOscWgtClass", "\347\202\271\346\225\260", nullptr));
        radioBtn_WndLengthType_Time->setText(QApplication::translate("EffOscWgtClass", "\346\227\266\351\225\277", nullptr));
        label_WndLengthPoint->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\236\213\347\202\271\346\225\260\357\274\232", nullptr));
        label_WndSampleRate->setText(QApplication::translate("EffOscWgtClass", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_WndLength_Time->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\236\213\346\227\266\351\225\277(ms)\357\274\232", nullptr));
        label_resultWndLength_Point->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\236\213\347\255\211\344\273\267\347\202\271\346\225\260\357\274\232", nullptr));
        label_resultWndLength_Time->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\236\213\347\255\211\344\273\267\346\227\266\351\225\277\357\274\232", nullptr));
        label_WndSTFTFreqDelta->setText(QApplication::translate("EffOscWgtClass", "FFT\350\276\223\345\207\272\351\242\221\347\216\207\351\227\264\351\232\224\357\274\232", nullptr));
        btn_GenWndTimeGraph->setText(QApplication::translate("EffOscWgtClass", "\347\224\237\346\210\220\347\252\227\345\236\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("EffOscWgtClass", "STFT\347\252\227\345\217\202\346\225\260", nullptr));
        groupBox_11->setTitle(QApplication::translate("EffOscWgtClass", "\347\252\227\345\207\275\346\225\260\345\217\202\346\225\260", nullptr));
        label_ActiveWnd_sampleRate->setText(QApplication::translate("EffOscWgtClass", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_ActiveWnd_WndType->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\207\275\346\225\260\347\261\273\345\236\213", nullptr));
        label_ActiveWnd_FFTWndPtCount->setText(QApplication::translate("EffOscWgtClass", "\347\252\227\345\207\275\346\225\260\347\202\271\346\225\260", nullptr));
        label_ActiveStartRatio->setText(QApplication::translate("EffOscWgtClass", "\345\274\200\345\247\213\344\275\215\347\275\256\346\257\224\344\276\213\357\274\210%\357\274\211", nullptr));
        label_IncreaseTime->setText(QApplication::translate("EffOscWgtClass", "\344\270\212\345\215\207\346\227\266\351\227\264\357\274\210ms\357\274\211", nullptr));
        btn_GenActiveWndTimeGraph->setText(QApplication::translate("EffOscWgtClass", "\347\224\237\346\210\220\350\260\203\345\210\266\345\207\275\346\225\260", nullptr));
        groupBox_ActiveWnd_ShowType->setTitle(QApplication::translate("EffOscWgtClass", "\346\230\276\347\244\272\345\257\271\350\261\241", nullptr));
        checkBox_ActiveWnd_ShowType_STFTWnd->setText(QApplication::translate("EffOscWgtClass", "STFT\347\252\227", nullptr));
        checkBox_ActiveWnd_ShowType_ActiveVal->setText(QApplication::translate("EffOscWgtClass", "\346\277\200\345\217\221\345\207\275\346\225\260", nullptr));
        checkBox_ActiveWnd_ShowType_ActiveWnd->setText(QApplication::translate("EffOscWgtClass", "\346\277\200\345\217\221\347\252\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("EffOscWgtClass", "\345\206\262\346\277\200\350\260\203\345\210\266\345\217\202\346\225\260", nullptr));
        groupBox_15->setTitle(QApplication::translate("EffOscWgtClass", "\347\252\227\345\275\242\351\242\221\350\260\261", nullptr));
        groupBox_12->setTitle(QApplication::translate("EffOscWgtClass", "\345\210\206\346\236\220\346\216\247\345\210\266", nullptr));
        groupBox_13->setTitle(QApplication::translate("EffOscWgtClass", "\345\200\274\346\230\276\347\244\272\346\226\271\345\274\217", nullptr));
        radioButton_ActiveWndFFTValType_AbsoluteVal->setText(QApplication::translate("EffOscWgtClass", "\347\273\235\345\257\271\345\200\274", nullptr));
        radioButton_ActiveWndFFTValType_db->setText(QApplication::translate("EffOscWgtClass", "db", nullptr));
        radioButton_ActiveWndFFTValType_AbsDb->setText(QApplication::translate("EffOscWgtClass", "\347\273\235\345\257\271db", nullptr));
        label_ActiveWndFFTShowPointCount->setText(QApplication::translate("EffOscWgtClass", "\346\200\273\347\202\271\346\225\260", nullptr));
        label_ActiveWndFFTShowMaxFreq->setText(QApplication::translate("EffOscWgtClass", "\346\230\276\347\244\272\346\234\200\345\244\247\351\242\221\347\216\207", nullptr));
        label_ActiveWndFFTShowMinVal->setText(QApplication::translate("EffOscWgtClass", "\346\230\276\347\244\272\346\234\200\345\260\217\346\225\260\345\200\274", nullptr));
        label_ActvieWndFFTGenState->setText(QApplication::translate("EffOscWgtClass", "\347\224\237\346\210\220\347\212\266\346\200\201", nullptr));
        btn_GenActiveWndFFTGraph->setText(QApplication::translate("EffOscWgtClass", "\351\242\221\350\260\261\345\210\206\346\236\220", nullptr));
        btn_updateActiveWndFFTCht->setText(QApplication::translate("EffOscWgtClass", "\345\210\267\346\226\260\345\233\276\345\203\217", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_activeWndSpec), QApplication::translate("EffOscWgtClass", "\346\277\200\345\217\221\350\260\203\345\210\266\347\252\227\351\242\221\350\260\261", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_WndSpecAns), QApplication::translate("EffOscWgtClass", "\347\252\227\350\260\261\345\210\206\346\236\220", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("EffOscWgtClass", "\347\252\227\350\260\261\346\212\221\345\210\266\350\276\223\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EffOscWgtClass: public Ui_EffOscWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFOSCWGT_H
