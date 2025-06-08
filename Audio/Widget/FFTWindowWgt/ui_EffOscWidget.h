/********************************************************************************
** Form generated from reading UI file 'EffOscWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFOSCWIDGET_H
#define UI_EFFOSCWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EffOscWidgetClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_20;
    QGroupBox *groupBox_HotCht;
    QVBoxLayout *VLayout_STFT_Cht_HotCht;
    QGroupBox *groupBox_HotChtPanel;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_STFTFileName;
    QLabel *label_dataDuration;
    QLabel *label_STFTState;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_hotChtStartTime;
    QTimeEdit *timeEdit_hotChtStartTime;
    QLabel *label_hotChtTimeLength;
    QSpinBox *SBox_hotChtTimeLength;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_hotCht_startFreq;
    QSpinBox *SBox_HotChtStartFreq;
    QLabel *label_hotCht_endFreq;
    QSpinBox *SBox_HotchtEndFreq;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_ADSR_HotCht_StartDB;
    QSpinBox *SBox_ADSR_HotCht_StartDB;
    QLabel *label_ADSR_HotCht_endDB;
    QSpinBox *SBox_ADSR_HotCht_EndDB;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_HotChtFreqBandWidth;
    QSpinBox *SBox_HotChtFreqBandWidth;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_HotChtTimeIntervalMsec;
    QSpinBox *SBox_HotChtTimeIntervalMsec;
    QLabel *label_HotChtGenState;
    QHBoxLayout *horizontalLayout_26;
    QProgressBar *progressBar_HotCht_Genstate;
    QPushButton *btn_updateHotCht;
    QHBoxLayout *horizontalLayout_27;
    QGroupBox *groupBox_11;
    QHBoxLayout *HLayout_EffOsc_TimeSecCht;
    QTabWidget *tabWidget_OscSepPannel;
    QWidget *tab_WndSpecConstrain;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_MaxConstrainDbPos;
    QSpinBox *SBox_MaxConstrainDbPos;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_PeakFreqDriftRatio;
    QDoubleSpinBox *DSBox_PeakFreqDriftRatio;
    QCheckBox *checkBox_forcePt2DBVal;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_forcePt2DBVal;
    QDoubleSpinBox *DSBox_forcePt2DBVal;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_EnhanceConstrainPos;
    QSpinBox *SBox__EnheaceConstrainPos;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_EnhanceConstrainRatio;
    QDoubleSpinBox *DSbox_EnhanceConstrainRatio;
    QLabel *label_constrainSidePtCount;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_getWndConstrainData_UpdateCht;
    QRadioButton *radioButton_getWndConstrainData_GoBDSNR;
    QLabel *label_WndSpecConstrainGenState;
    QProgressBar *progressBar_WndSpecConstrain_GenResult;
    QPushButton *btn_WndSpecConstrain_GenResult;
    QSpacerItem *verticalSpacer_5;
    QWidget *tab_TimeSecCht;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *groupBox_HAxisRange;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_OscSep_TimeSec_startFreq;
    QSpinBox *SBox_OscSep_TimeSec_startFreq;
    QLabel *label_OscSep_TimeSec_endFreq;
    QSpinBox *SBox_OscSep_TimeSec_endFreq;
    QGroupBox *groupBox_15;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_OscSep_TimeSec_StartDB;
    QSpinBox *SBox_OscSep_TimeSec_StartDB;
    QLabel *label_OscSep_TimeSec_endDB;
    QSpinBox *SBox_OscSep_TimeSec_EndDB;
    QHBoxLayout *horizontalLayout_46;
    QLabel *label_OscSep_TimeSec_BarBandWidth;
    QSpinBox *SBox_OscSep_TimeSec_BarBandWidth;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_OscSep_UpdateTimer;
    QSpinBox *SBox_OscSep_UpdateTimer;
    QGroupBox *groupBox_16;
    QHBoxLayout *horizontalLayout_48;
    QRadioButton *radioButton_TimeSecCht_STFT;
    QRadioButton *radioButton_TimeSecCht_WndSepcConstrain;
    QGroupBox *groupBox_17;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_49;
    QCheckBox *checkBox_drawTIQLine;
    QCheckBox *checkBox_drawUnderTIQBar;
    QHBoxLayout *horizontalLayout_50;
    QCheckBox *checkBox_drawWndSpecNoise;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_TimeSecGenState;
    QHBoxLayout *horizontalLayout_52;
    QProgressBar *progressBar_OscSep_TimeSec_Genstate;
    QPushButton *btn_updateTimeSecCht;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_53;
    QGroupBox *groupBox_18;
    QVBoxLayout *verticalLayout_18;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_54;
    QLabel *label_OscSep_TimeFrameTime;
    QSlider *HSlider_OscSep_TimeFrameIndex;
    QHBoxLayout *horizontalLayout_55;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_lastFrame;
    QPushButton *btn_nextFrame;
    QPushButton *btn_play;
    QPushButton *btn_stop;
    QPushButton *btn_jump;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_19;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_OscSep_Frame_CenterTime;
    QLabel *label_OscSep_Avr_SecFrameRate;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QWidget *EffOscWidgetClass)
    {
        if (EffOscWidgetClass->objectName().isEmpty())
            EffOscWidgetClass->setObjectName(QString::fromUtf8("EffOscWidgetClass"));
        EffOscWidgetClass->resize(1375, 919);
        verticalLayout = new QVBoxLayout(EffOscWidgetClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        groupBox_HotCht = new QGroupBox(EffOscWidgetClass);
        groupBox_HotCht->setObjectName(QString::fromUtf8("groupBox_HotCht"));
        groupBox_HotCht->setMaximumSize(QSize(16777215, 16777215));
        VLayout_STFT_Cht_HotCht = new QVBoxLayout(groupBox_HotCht);
        VLayout_STFT_Cht_HotCht->setSpacing(6);
        VLayout_STFT_Cht_HotCht->setContentsMargins(11, 11, 11, 11);
        VLayout_STFT_Cht_HotCht->setObjectName(QString::fromUtf8("VLayout_STFT_Cht_HotCht"));

        horizontalLayout_20->addWidget(groupBox_HotCht);

        groupBox_HotChtPanel = new QGroupBox(EffOscWidgetClass);
        groupBox_HotChtPanel->setObjectName(QString::fromUtf8("groupBox_HotChtPanel"));
        groupBox_HotChtPanel->setMaximumSize(QSize(280, 16777215));
        verticalLayout_9 = new QVBoxLayout(groupBox_HotChtPanel);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_STFTFileName = new QLabel(groupBox_HotChtPanel);
        label_STFTFileName->setObjectName(QString::fromUtf8("label_STFTFileName"));
        label_STFTFileName->setMinimumSize(QSize(0, 20));
        label_STFTFileName->setMaximumSize(QSize(16777215, 20));

        verticalLayout_9->addWidget(label_STFTFileName);

        label_dataDuration = new QLabel(groupBox_HotChtPanel);
        label_dataDuration->setObjectName(QString::fromUtf8("label_dataDuration"));
        label_dataDuration->setMinimumSize(QSize(0, 20));
        label_dataDuration->setMaximumSize(QSize(16777215, 20));

        verticalLayout_9->addWidget(label_dataDuration);

        label_STFTState = new QLabel(groupBox_HotChtPanel);
        label_STFTState->setObjectName(QString::fromUtf8("label_STFTState"));
        label_STFTState->setMinimumSize(QSize(0, 20));
        label_STFTState->setMaximumSize(QSize(16777215, 20));

        verticalLayout_9->addWidget(label_STFTState);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_hotChtStartTime = new QLabel(groupBox_HotChtPanel);
        label_hotChtStartTime->setObjectName(QString::fromUtf8("label_hotChtStartTime"));

        horizontalLayout_21->addWidget(label_hotChtStartTime);

        timeEdit_hotChtStartTime = new QTimeEdit(groupBox_HotChtPanel);
        timeEdit_hotChtStartTime->setObjectName(QString::fromUtf8("timeEdit_hotChtStartTime"));
        timeEdit_hotChtStartTime->setMinimumSize(QSize(60, 0));
        timeEdit_hotChtStartTime->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_21->addWidget(timeEdit_hotChtStartTime);

        label_hotChtTimeLength = new QLabel(groupBox_HotChtPanel);
        label_hotChtTimeLength->setObjectName(QString::fromUtf8("label_hotChtTimeLength"));

        horizontalLayout_21->addWidget(label_hotChtTimeLength);

        SBox_hotChtTimeLength = new QSpinBox(groupBox_HotChtPanel);
        SBox_hotChtTimeLength->setObjectName(QString::fromUtf8("SBox_hotChtTimeLength"));
        SBox_hotChtTimeLength->setMaximum(20000);
        SBox_hotChtTimeLength->setValue(10000);

        horizontalLayout_21->addWidget(SBox_hotChtTimeLength);


        verticalLayout_9->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_hotCht_startFreq = new QLabel(groupBox_HotChtPanel);
        label_hotCht_startFreq->setObjectName(QString::fromUtf8("label_hotCht_startFreq"));

        horizontalLayout_22->addWidget(label_hotCht_startFreq);

        SBox_HotChtStartFreq = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotChtStartFreq->setObjectName(QString::fromUtf8("SBox_HotChtStartFreq"));
        SBox_HotChtStartFreq->setMinimumSize(QSize(60, 0));
        SBox_HotChtStartFreq->setMaximumSize(QSize(60, 16777215));
        SBox_HotChtStartFreq->setMaximum(22100);

        horizontalLayout_22->addWidget(SBox_HotChtStartFreq);

        label_hotCht_endFreq = new QLabel(groupBox_HotChtPanel);
        label_hotCht_endFreq->setObjectName(QString::fromUtf8("label_hotCht_endFreq"));

        horizontalLayout_22->addWidget(label_hotCht_endFreq);

        SBox_HotchtEndFreq = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotchtEndFreq->setObjectName(QString::fromUtf8("SBox_HotchtEndFreq"));
        SBox_HotchtEndFreq->setMinimumSize(QSize(60, 0));
        SBox_HotchtEndFreq->setMaximumSize(QSize(60, 16777215));
        SBox_HotchtEndFreq->setMaximum(22100);
        SBox_HotchtEndFreq->setValue(20000);

        horizontalLayout_22->addWidget(SBox_HotchtEndFreq);


        verticalLayout_9->addLayout(horizontalLayout_22);

        groupBox_8 = new QGroupBox(groupBox_HotChtPanel);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        horizontalLayout_23 = new QHBoxLayout(groupBox_8);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_ADSR_HotCht_StartDB = new QLabel(groupBox_8);
        label_ADSR_HotCht_StartDB->setObjectName(QString::fromUtf8("label_ADSR_HotCht_StartDB"));

        horizontalLayout_23->addWidget(label_ADSR_HotCht_StartDB);

        SBox_ADSR_HotCht_StartDB = new QSpinBox(groupBox_8);
        SBox_ADSR_HotCht_StartDB->setObjectName(QString::fromUtf8("SBox_ADSR_HotCht_StartDB"));
        SBox_ADSR_HotCht_StartDB->setMinimum(-20);
        SBox_ADSR_HotCht_StartDB->setValue(0);

        horizontalLayout_23->addWidget(SBox_ADSR_HotCht_StartDB);

        label_ADSR_HotCht_endDB = new QLabel(groupBox_8);
        label_ADSR_HotCht_endDB->setObjectName(QString::fromUtf8("label_ADSR_HotCht_endDB"));

        horizontalLayout_23->addWidget(label_ADSR_HotCht_endDB);

        SBox_ADSR_HotCht_EndDB = new QSpinBox(groupBox_8);
        SBox_ADSR_HotCht_EndDB->setObjectName(QString::fromUtf8("SBox_ADSR_HotCht_EndDB"));
        SBox_ADSR_HotCht_EndDB->setValue(60);

        horizontalLayout_23->addWidget(SBox_ADSR_HotCht_EndDB);


        verticalLayout_9->addWidget(groupBox_8);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_HotChtFreqBandWidth = new QLabel(groupBox_HotChtPanel);
        label_HotChtFreqBandWidth->setObjectName(QString::fromUtf8("label_HotChtFreqBandWidth"));

        horizontalLayout_24->addWidget(label_HotChtFreqBandWidth);

        SBox_HotChtFreqBandWidth = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotChtFreqBandWidth->setObjectName(QString::fromUtf8("SBox_HotChtFreqBandWidth"));
        SBox_HotChtFreqBandWidth->setMinimum(1);
        SBox_HotChtFreqBandWidth->setValue(11);

        horizontalLayout_24->addWidget(SBox_HotChtFreqBandWidth);


        verticalLayout_9->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_HotChtTimeIntervalMsec = new QLabel(groupBox_HotChtPanel);
        label_HotChtTimeIntervalMsec->setObjectName(QString::fromUtf8("label_HotChtTimeIntervalMsec"));

        horizontalLayout_25->addWidget(label_HotChtTimeIntervalMsec);

        SBox_HotChtTimeIntervalMsec = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotChtTimeIntervalMsec->setObjectName(QString::fromUtf8("SBox_HotChtTimeIntervalMsec"));
        SBox_HotChtTimeIntervalMsec->setMinimum(1);
        SBox_HotChtTimeIntervalMsec->setValue(20);

        horizontalLayout_25->addWidget(SBox_HotChtTimeIntervalMsec);


        verticalLayout_9->addLayout(horizontalLayout_25);

        label_HotChtGenState = new QLabel(groupBox_HotChtPanel);
        label_HotChtGenState->setObjectName(QString::fromUtf8("label_HotChtGenState"));

        verticalLayout_9->addWidget(label_HotChtGenState);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        progressBar_HotCht_Genstate = new QProgressBar(groupBox_HotChtPanel);
        progressBar_HotCht_Genstate->setObjectName(QString::fromUtf8("progressBar_HotCht_Genstate"));
        progressBar_HotCht_Genstate->setValue(0);

        horizontalLayout_26->addWidget(progressBar_HotCht_Genstate);


        verticalLayout_9->addLayout(horizontalLayout_26);

        btn_updateHotCht = new QPushButton(groupBox_HotChtPanel);
        btn_updateHotCht->setObjectName(QString::fromUtf8("btn_updateHotCht"));

        verticalLayout_9->addWidget(btn_updateHotCht);


        horizontalLayout_20->addWidget(groupBox_HotChtPanel);


        verticalLayout->addLayout(horizontalLayout_20);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        groupBox_11 = new QGroupBox(EffOscWidgetClass);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        HLayout_EffOsc_TimeSecCht = new QHBoxLayout(groupBox_11);
        HLayout_EffOsc_TimeSecCht->setSpacing(6);
        HLayout_EffOsc_TimeSecCht->setContentsMargins(11, 11, 11, 11);
        HLayout_EffOsc_TimeSecCht->setObjectName(QString::fromUtf8("HLayout_EffOsc_TimeSecCht"));

        horizontalLayout_27->addWidget(groupBox_11);

        tabWidget_OscSepPannel = new QTabWidget(EffOscWidgetClass);
        tabWidget_OscSepPannel->setObjectName(QString::fromUtf8("tabWidget_OscSepPannel"));
        tabWidget_OscSepPannel->setMaximumSize(QSize(280, 16777215));
        tab_WndSpecConstrain = new QWidget();
        tab_WndSpecConstrain->setObjectName(QString::fromUtf8("tab_WndSpecConstrain"));
        verticalLayout_10 = new QVBoxLayout(tab_WndSpecConstrain);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupBox_12 = new QGroupBox(tab_WndSpecConstrain);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setMinimumSize(QSize(0, 0));
        verticalLayout_11 = new QVBoxLayout(groupBox_12);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_MaxConstrainDbPos = new QLabel(groupBox_12);
        label_MaxConstrainDbPos->setObjectName(QString::fromUtf8("label_MaxConstrainDbPos"));

        horizontalLayout_28->addWidget(label_MaxConstrainDbPos);

        SBox_MaxConstrainDbPos = new QSpinBox(groupBox_12);
        SBox_MaxConstrainDbPos->setObjectName(QString::fromUtf8("SBox_MaxConstrainDbPos"));
        SBox_MaxConstrainDbPos->setMinimumSize(QSize(72, 0));
        SBox_MaxConstrainDbPos->setMaximumSize(QSize(72, 16777215));
        SBox_MaxConstrainDbPos->setMaximum(140);
        SBox_MaxConstrainDbPos->setValue(55);

        horizontalLayout_28->addWidget(SBox_MaxConstrainDbPos);


        verticalLayout_11->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_PeakFreqDriftRatio = new QLabel(groupBox_12);
        label_PeakFreqDriftRatio->setObjectName(QString::fromUtf8("label_PeakFreqDriftRatio"));

        horizontalLayout_29->addWidget(label_PeakFreqDriftRatio);

        DSBox_PeakFreqDriftRatio = new QDoubleSpinBox(groupBox_12);
        DSBox_PeakFreqDriftRatio->setObjectName(QString::fromUtf8("DSBox_PeakFreqDriftRatio"));
        DSBox_PeakFreqDriftRatio->setMinimumSize(QSize(72, 0));
        DSBox_PeakFreqDriftRatio->setMaximumSize(QSize(72, 16777215));
        DSBox_PeakFreqDriftRatio->setMaximum(50.000000000000000);
        DSBox_PeakFreqDriftRatio->setValue(25.000000000000000);

        horizontalLayout_29->addWidget(DSBox_PeakFreqDriftRatio);


        verticalLayout_11->addLayout(horizontalLayout_29);

        checkBox_forcePt2DBVal = new QCheckBox(groupBox_12);
        checkBox_forcePt2DBVal->setObjectName(QString::fromUtf8("checkBox_forcePt2DBVal"));
        checkBox_forcePt2DBVal->setCheckable(true);
        checkBox_forcePt2DBVal->setChecked(false);

        verticalLayout_11->addWidget(checkBox_forcePt2DBVal);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_forcePt2DBVal = new QLabel(groupBox_12);
        label_forcePt2DBVal->setObjectName(QString::fromUtf8("label_forcePt2DBVal"));

        horizontalLayout_30->addWidget(label_forcePt2DBVal);

        DSBox_forcePt2DBVal = new QDoubleSpinBox(groupBox_12);
        DSBox_forcePt2DBVal->setObjectName(QString::fromUtf8("DSBox_forcePt2DBVal"));
        DSBox_forcePt2DBVal->setEnabled(true);
        DSBox_forcePt2DBVal->setMinimumSize(QSize(72, 0));
        DSBox_forcePt2DBVal->setMaximumSize(QSize(72, 16777215));
        DSBox_forcePt2DBVal->setValue(20.000000000000000);

        horizontalLayout_30->addWidget(DSBox_forcePt2DBVal);


        verticalLayout_11->addLayout(horizontalLayout_30);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_EnhanceConstrainPos = new QLabel(groupBox_12);
        label_EnhanceConstrainPos->setObjectName(QString::fromUtf8("label_EnhanceConstrainPos"));

        horizontalLayout_31->addWidget(label_EnhanceConstrainPos);

        SBox__EnheaceConstrainPos = new QSpinBox(groupBox_12);
        SBox__EnheaceConstrainPos->setObjectName(QString::fromUtf8("SBox__EnheaceConstrainPos"));
        SBox__EnheaceConstrainPos->setMinimumSize(QSize(72, 0));
        SBox__EnheaceConstrainPos->setMaximumSize(QSize(72, 16777215));
        SBox__EnheaceConstrainPos->setMaximum(20);
        SBox__EnheaceConstrainPos->setValue(1);
        SBox__EnheaceConstrainPos->setDisplayIntegerBase(10);

        horizontalLayout_31->addWidget(SBox__EnheaceConstrainPos);


        verticalLayout_11->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        label_EnhanceConstrainRatio = new QLabel(groupBox_12);
        label_EnhanceConstrainRatio->setObjectName(QString::fromUtf8("label_EnhanceConstrainRatio"));

        horizontalLayout_32->addWidget(label_EnhanceConstrainRatio);

        DSbox_EnhanceConstrainRatio = new QDoubleSpinBox(groupBox_12);
        DSbox_EnhanceConstrainRatio->setObjectName(QString::fromUtf8("DSbox_EnhanceConstrainRatio"));
        DSbox_EnhanceConstrainRatio->setMinimumSize(QSize(72, 0));
        DSbox_EnhanceConstrainRatio->setMaximumSize(QSize(72, 16777215));
        DSbox_EnhanceConstrainRatio->setMaximum(1000.000000000000000);
        DSbox_EnhanceConstrainRatio->setValue(250.000000000000000);

        horizontalLayout_32->addWidget(DSbox_EnhanceConstrainRatio);


        verticalLayout_11->addLayout(horizontalLayout_32);


        verticalLayout_10->addWidget(groupBox_12);

        label_constrainSidePtCount = new QLabel(tab_WndSpecConstrain);
        label_constrainSidePtCount->setObjectName(QString::fromUtf8("label_constrainSidePtCount"));

        verticalLayout_10->addWidget(label_constrainSidePtCount);

        groupBox = new QGroupBox(tab_WndSpecConstrain);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_getWndConstrainData_UpdateCht = new QRadioButton(groupBox);
        radioButton_getWndConstrainData_UpdateCht->setObjectName(QString::fromUtf8("radioButton_getWndConstrainData_UpdateCht"));

        horizontalLayout->addWidget(radioButton_getWndConstrainData_UpdateCht);

        radioButton_getWndConstrainData_GoBDSNR = new QRadioButton(groupBox);
        radioButton_getWndConstrainData_GoBDSNR->setObjectName(QString::fromUtf8("radioButton_getWndConstrainData_GoBDSNR"));
        radioButton_getWndConstrainData_GoBDSNR->setChecked(true);

        horizontalLayout->addWidget(radioButton_getWndConstrainData_GoBDSNR);


        verticalLayout_10->addWidget(groupBox);

        label_WndSpecConstrainGenState = new QLabel(tab_WndSpecConstrain);
        label_WndSpecConstrainGenState->setObjectName(QString::fromUtf8("label_WndSpecConstrainGenState"));

        verticalLayout_10->addWidget(label_WndSpecConstrainGenState);

        progressBar_WndSpecConstrain_GenResult = new QProgressBar(tab_WndSpecConstrain);
        progressBar_WndSpecConstrain_GenResult->setObjectName(QString::fromUtf8("progressBar_WndSpecConstrain_GenResult"));
        progressBar_WndSpecConstrain_GenResult->setValue(0);

        verticalLayout_10->addWidget(progressBar_WndSpecConstrain_GenResult);

        btn_WndSpecConstrain_GenResult = new QPushButton(tab_WndSpecConstrain);
        btn_WndSpecConstrain_GenResult->setObjectName(QString::fromUtf8("btn_WndSpecConstrain_GenResult"));

        verticalLayout_10->addWidget(btn_WndSpecConstrain_GenResult);

        verticalSpacer_5 = new QSpacerItem(20, 145, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_5);

        tabWidget_OscSepPannel->addTab(tab_WndSpecConstrain, QString());
        tab_TimeSecCht = new QWidget();
        tab_TimeSecCht->setObjectName(QString::fromUtf8("tab_TimeSecCht"));
        verticalLayout_16 = new QVBoxLayout(tab_TimeSecCht);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        groupBox_HAxisRange = new QGroupBox(tab_TimeSecCht);
        groupBox_HAxisRange->setObjectName(QString::fromUtf8("groupBox_HAxisRange"));
        horizontalLayout_44 = new QHBoxLayout(groupBox_HAxisRange);
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        label_OscSep_TimeSec_startFreq = new QLabel(groupBox_HAxisRange);
        label_OscSep_TimeSec_startFreq->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_startFreq"));

        horizontalLayout_44->addWidget(label_OscSep_TimeSec_startFreq);

        SBox_OscSep_TimeSec_startFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_OscSep_TimeSec_startFreq->setObjectName(QString::fromUtf8("SBox_OscSep_TimeSec_startFreq"));
        SBox_OscSep_TimeSec_startFreq->setMaximum(22100);

        horizontalLayout_44->addWidget(SBox_OscSep_TimeSec_startFreq);

        label_OscSep_TimeSec_endFreq = new QLabel(groupBox_HAxisRange);
        label_OscSep_TimeSec_endFreq->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_endFreq"));

        horizontalLayout_44->addWidget(label_OscSep_TimeSec_endFreq);

        SBox_OscSep_TimeSec_endFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_OscSep_TimeSec_endFreq->setObjectName(QString::fromUtf8("SBox_OscSep_TimeSec_endFreq"));
        SBox_OscSep_TimeSec_endFreq->setMaximum(22100);
        SBox_OscSep_TimeSec_endFreq->setValue(4000);

        horizontalLayout_44->addWidget(SBox_OscSep_TimeSec_endFreq);


        verticalLayout_16->addWidget(groupBox_HAxisRange);

        groupBox_15 = new QGroupBox(tab_TimeSecCht);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        horizontalLayout_45 = new QHBoxLayout(groupBox_15);
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_OscSep_TimeSec_StartDB = new QLabel(groupBox_15);
        label_OscSep_TimeSec_StartDB->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_StartDB"));

        horizontalLayout_45->addWidget(label_OscSep_TimeSec_StartDB);

        SBox_OscSep_TimeSec_StartDB = new QSpinBox(groupBox_15);
        SBox_OscSep_TimeSec_StartDB->setObjectName(QString::fromUtf8("SBox_OscSep_TimeSec_StartDB"));
        SBox_OscSep_TimeSec_StartDB->setMinimum(0);
        SBox_OscSep_TimeSec_StartDB->setValue(0);

        horizontalLayout_45->addWidget(SBox_OscSep_TimeSec_StartDB);

        label_OscSep_TimeSec_endDB = new QLabel(groupBox_15);
        label_OscSep_TimeSec_endDB->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_endDB"));

        horizontalLayout_45->addWidget(label_OscSep_TimeSec_endDB);

        SBox_OscSep_TimeSec_EndDB = new QSpinBox(groupBox_15);
        SBox_OscSep_TimeSec_EndDB->setObjectName(QString::fromUtf8("SBox_OscSep_TimeSec_EndDB"));
        SBox_OscSep_TimeSec_EndDB->setValue(80);

        horizontalLayout_45->addWidget(SBox_OscSep_TimeSec_EndDB);


        verticalLayout_16->addWidget(groupBox_15);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        label_OscSep_TimeSec_BarBandWidth = new QLabel(tab_TimeSecCht);
        label_OscSep_TimeSec_BarBandWidth->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_BarBandWidth"));

        horizontalLayout_46->addWidget(label_OscSep_TimeSec_BarBandWidth);

        SBox_OscSep_TimeSec_BarBandWidth = new QSpinBox(tab_TimeSecCht);
        SBox_OscSep_TimeSec_BarBandWidth->setObjectName(QString::fromUtf8("SBox_OscSep_TimeSec_BarBandWidth"));
        SBox_OscSep_TimeSec_BarBandWidth->setEnabled(false);
        SBox_OscSep_TimeSec_BarBandWidth->setMinimum(1);
        SBox_OscSep_TimeSec_BarBandWidth->setMaximum(22100);
        SBox_OscSep_TimeSec_BarBandWidth->setValue(11);

        horizontalLayout_46->addWidget(SBox_OscSep_TimeSec_BarBandWidth);


        verticalLayout_16->addLayout(horizontalLayout_46);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        label_OscSep_UpdateTimer = new QLabel(tab_TimeSecCht);
        label_OscSep_UpdateTimer->setObjectName(QString::fromUtf8("label_OscSep_UpdateTimer"));

        horizontalLayout_47->addWidget(label_OscSep_UpdateTimer);

        SBox_OscSep_UpdateTimer = new QSpinBox(tab_TimeSecCht);
        SBox_OscSep_UpdateTimer->setObjectName(QString::fromUtf8("SBox_OscSep_UpdateTimer"));
        SBox_OscSep_UpdateTimer->setMinimum(1);
        SBox_OscSep_UpdateTimer->setMaximum(200);
        SBox_OscSep_UpdateTimer->setValue(20);

        horizontalLayout_47->addWidget(SBox_OscSep_UpdateTimer);


        verticalLayout_16->addLayout(horizontalLayout_47);

        groupBox_16 = new QGroupBox(tab_TimeSecCht);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        groupBox_16->setMinimumSize(QSize(0, 64));
        groupBox_16->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_48 = new QHBoxLayout(groupBox_16);
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        radioButton_TimeSecCht_STFT = new QRadioButton(groupBox_16);
        radioButton_TimeSecCht_STFT->setObjectName(QString::fromUtf8("radioButton_TimeSecCht_STFT"));
        radioButton_TimeSecCht_STFT->setChecked(false);

        horizontalLayout_48->addWidget(radioButton_TimeSecCht_STFT);

        radioButton_TimeSecCht_WndSepcConstrain = new QRadioButton(groupBox_16);
        radioButton_TimeSecCht_WndSepcConstrain->setObjectName(QString::fromUtf8("radioButton_TimeSecCht_WndSepcConstrain"));
        radioButton_TimeSecCht_WndSepcConstrain->setChecked(true);

        horizontalLayout_48->addWidget(radioButton_TimeSecCht_WndSepcConstrain);


        verticalLayout_16->addWidget(groupBox_16);

        groupBox_17 = new QGroupBox(tab_TimeSecCht);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        groupBox_17->setMinimumSize(QSize(0, 0));
        verticalLayout_17 = new QVBoxLayout(groupBox_17);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        checkBox_drawTIQLine = new QCheckBox(groupBox_17);
        checkBox_drawTIQLine->setObjectName(QString::fromUtf8("checkBox_drawTIQLine"));
        checkBox_drawTIQLine->setMinimumSize(QSize(100, 0));
        checkBox_drawTIQLine->setMaximumSize(QSize(100, 16777215));
        checkBox_drawTIQLine->setChecked(false);

        horizontalLayout_49->addWidget(checkBox_drawTIQLine);

        checkBox_drawUnderTIQBar = new QCheckBox(groupBox_17);
        checkBox_drawUnderTIQBar->setObjectName(QString::fromUtf8("checkBox_drawUnderTIQBar"));
        checkBox_drawUnderTIQBar->setChecked(false);

        horizontalLayout_49->addWidget(checkBox_drawUnderTIQBar);


        verticalLayout_17->addLayout(horizontalLayout_49);

        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        checkBox_drawWndSpecNoise = new QCheckBox(groupBox_17);
        checkBox_drawWndSpecNoise->setObjectName(QString::fromUtf8("checkBox_drawWndSpecNoise"));
        checkBox_drawWndSpecNoise->setMinimumSize(QSize(100, 0));
        checkBox_drawWndSpecNoise->setMaximumSize(QSize(100, 16777215));
        checkBox_drawWndSpecNoise->setChecked(false);

        horizontalLayout_50->addWidget(checkBox_drawWndSpecNoise);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_50->addItem(horizontalSpacer_3);


        verticalLayout_17->addLayout(horizontalLayout_50);


        verticalLayout_16->addWidget(groupBox_17);

        label_TimeSecGenState = new QLabel(tab_TimeSecCht);
        label_TimeSecGenState->setObjectName(QString::fromUtf8("label_TimeSecGenState"));

        verticalLayout_16->addWidget(label_TimeSecGenState);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setSpacing(6);
        horizontalLayout_52->setObjectName(QString::fromUtf8("horizontalLayout_52"));
        progressBar_OscSep_TimeSec_Genstate = new QProgressBar(tab_TimeSecCht);
        progressBar_OscSep_TimeSec_Genstate->setObjectName(QString::fromUtf8("progressBar_OscSep_TimeSec_Genstate"));
        progressBar_OscSep_TimeSec_Genstate->setValue(0);

        horizontalLayout_52->addWidget(progressBar_OscSep_TimeSec_Genstate);


        verticalLayout_16->addLayout(horizontalLayout_52);

        btn_updateTimeSecCht = new QPushButton(tab_TimeSecCht);
        btn_updateTimeSecCht->setObjectName(QString::fromUtf8("btn_updateTimeSecCht"));

        verticalLayout_16->addWidget(btn_updateTimeSecCht);

        verticalSpacer_8 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_8);

        tabWidget_OscSepPannel->addTab(tab_TimeSecCht, QString());

        horizontalLayout_27->addWidget(tabWidget_OscSepPannel);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(6);
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        groupBox_18 = new QGroupBox(EffOscWidgetClass);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        verticalLayout_18 = new QVBoxLayout(groupBox_18);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        horizontalLayout_54 = new QHBoxLayout();
        horizontalLayout_54->setSpacing(6);
        horizontalLayout_54->setObjectName(QString::fromUtf8("horizontalLayout_54"));
        label_OscSep_TimeFrameTime = new QLabel(groupBox_18);
        label_OscSep_TimeFrameTime->setObjectName(QString::fromUtf8("label_OscSep_TimeFrameTime"));

        horizontalLayout_54->addWidget(label_OscSep_TimeFrameTime);

        HSlider_OscSep_TimeFrameIndex = new QSlider(groupBox_18);
        HSlider_OscSep_TimeFrameIndex->setObjectName(QString::fromUtf8("HSlider_OscSep_TimeFrameIndex"));
        HSlider_OscSep_TimeFrameIndex->setOrientation(Qt::Horizontal);

        horizontalLayout_54->addWidget(HSlider_OscSep_TimeFrameIndex);


        verticalLayout_19->addLayout(horizontalLayout_54);

        horizontalLayout_55 = new QHBoxLayout();
        horizontalLayout_55->setSpacing(6);
        horizontalLayout_55->setObjectName(QString::fromUtf8("horizontalLayout_55"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_55->addItem(horizontalSpacer);

        btn_lastFrame = new QPushButton(groupBox_18);
        btn_lastFrame->setObjectName(QString::fromUtf8("btn_lastFrame"));
        btn_lastFrame->setMinimumSize(QSize(24, 0));
        btn_lastFrame->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_55->addWidget(btn_lastFrame);

        btn_nextFrame = new QPushButton(groupBox_18);
        btn_nextFrame->setObjectName(QString::fromUtf8("btn_nextFrame"));
        btn_nextFrame->setMinimumSize(QSize(24, 0));
        btn_nextFrame->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_55->addWidget(btn_nextFrame);

        btn_play = new QPushButton(groupBox_18);
        btn_play->setObjectName(QString::fromUtf8("btn_play"));

        horizontalLayout_55->addWidget(btn_play);

        btn_stop = new QPushButton(groupBox_18);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));

        horizontalLayout_55->addWidget(btn_stop);

        btn_jump = new QPushButton(groupBox_18);
        btn_jump->setObjectName(QString::fromUtf8("btn_jump"));

        horizontalLayout_55->addWidget(btn_jump);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_55->addItem(horizontalSpacer_2);


        verticalLayout_19->addLayout(horizontalLayout_55);


        verticalLayout_18->addLayout(verticalLayout_19);


        horizontalLayout_53->addWidget(groupBox_18);

        groupBox_19 = new QGroupBox(EffOscWidgetClass);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        groupBox_19->setMinimumSize(QSize(260, 0));
        groupBox_19->setMaximumSize(QSize(260, 16777215));
        verticalLayout_20 = new QVBoxLayout(groupBox_19);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_OscSep_Frame_CenterTime = new QLabel(groupBox_19);
        label_OscSep_Frame_CenterTime->setObjectName(QString::fromUtf8("label_OscSep_Frame_CenterTime"));

        verticalLayout_20->addWidget(label_OscSep_Frame_CenterTime);

        label_OscSep_Avr_SecFrameRate = new QLabel(groupBox_19);
        label_OscSep_Avr_SecFrameRate->setObjectName(QString::fromUtf8("label_OscSep_Avr_SecFrameRate"));

        verticalLayout_20->addWidget(label_OscSep_Avr_SecFrameRate);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_9);


        horizontalLayout_53->addWidget(groupBox_19);


        verticalLayout->addLayout(horizontalLayout_53);


        retranslateUi(EffOscWidgetClass);

        tabWidget_OscSepPannel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EffOscWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *EffOscWidgetClass)
    {
        EffOscWidgetClass->setWindowTitle(QApplication::translate("EffOscWidgetClass", "EffOscWidget", nullptr));
        groupBox_HotCht->setTitle(QApplication::translate("EffOscWidgetClass", "\346\225\264\344\275\223\347\273\223\346\236\234", nullptr));
        groupBox_HotChtPanel->setTitle(QApplication::translate("EffOscWidgetClass", "\347\203\255\345\212\233\345\233\276\346\216\247\345\210\266", nullptr));
        label_STFTFileName->setText(QApplication::translate("EffOscWidgetClass", "\346\226\207\344\273\266\345\220\215\347\247\260", nullptr));
        label_dataDuration->setText(QApplication::translate("EffOscWidgetClass", "\346\225\260\346\215\256\346\214\201\347\273\255\346\227\266\351\227\264", nullptr));
        label_STFTState->setText(QApplication::translate("EffOscWidgetClass", "STFT\345\217\202\346\225\260\357\274\232", nullptr));
        label_hotChtStartTime->setText(QApplication::translate("EffOscWidgetClass", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeEdit_hotChtStartTime->setDisplayFormat(QApplication::translate("EffOscWidgetClass", "mm:ss", nullptr));
        label_hotChtTimeLength->setText(QApplication::translate("EffOscWidgetClass", "\347\252\227\345\217\243\351\225\277\345\272\246", nullptr));
        label_hotCht_startFreq->setText(QApplication::translate("EffOscWidgetClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_hotCht_endFreq->setText(QApplication::translate("EffOscWidgetClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_8->setTitle(QApplication::translate("EffOscWidgetClass", "\351\242\234\350\211\262\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_ADSR_HotCht_StartDB->setText(QApplication::translate("EffOscWidgetClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_ADSR_HotCht_endDB->setText(QApplication::translate("EffOscWidgetClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_HotChtFreqBandWidth->setText(QApplication::translate("EffOscWidgetClass", "\351\242\221\347\216\207\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_HotChtTimeIntervalMsec->setText(QApplication::translate("EffOscWidgetClass", "\346\227\266\351\227\264\345\270\246\345\256\275\357\274\210ms\357\274\211", nullptr));
        label_HotChtGenState->setText(QApplication::translate("EffOscWidgetClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateHotCht->setText(QApplication::translate("EffOscWidgetClass", "\345\210\267\346\226\260", nullptr));
        groupBox_11->setTitle(QApplication::translate("EffOscWidgetClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_12->setTitle(QApplication::translate("EffOscWidgetClass", "\347\252\227\345\207\275\346\225\260\351\242\221\350\260\261\350\277\207\346\273\244\346\235\241\344\273\266", nullptr));
        label_MaxConstrainDbPos->setText(QApplication::translate("EffOscWidgetClass", "\346\234\200\345\244\247\346\212\221\345\210\266\350\214\203\345\233\264(db)", nullptr));
        label_PeakFreqDriftRatio->setText(QApplication::translate("EffOscWidgetClass", "\345\263\260\345\200\274\351\242\221\347\216\207\345\201\217\347\247\273\346\257\224\344\276\213(%)", nullptr));
        checkBox_forcePt2DBVal->setText(QApplication::translate("EffOscWidgetClass", "\345\274\272\345\210\266\347\254\254\344\272\214\347\202\271\346\225\260\345\200\274", nullptr));
        label_forcePt2DBVal->setText(QApplication::translate("EffOscWidgetClass", "\347\254\254\344\272\214\347\202\271\346\214\207\345\256\232DB\357\274\232", nullptr));
        label_EnhanceConstrainPos->setText(QApplication::translate("EffOscWidgetClass", "\345\220\257\347\224\250\345\242\236\345\274\272\346\212\221\345\210\266\344\275\215\347\275\256", nullptr));
        label_EnhanceConstrainRatio->setText(QApplication::translate("EffOscWidgetClass", "\345\242\236\345\274\272\346\212\221\345\210\266\346\257\224\344\276\213\357\274\210%\357\274\211", nullptr));
        label_constrainSidePtCount->setText(QApplication::translate("EffOscWidgetClass", "\347\252\227\345\207\275\346\225\260\351\242\221\350\260\261\346\212\221\345\210\266\350\276\271\347\274\230\347\202\271\344\270\252\346\225\260\357\274\232", nullptr));
        groupBox->setTitle(QApplication::translate("EffOscWidgetClass", "\347\224\237\346\210\220\347\273\223\346\235\237\345\220\216\346\223\215\344\275\234", nullptr));
        radioButton_getWndConstrainData_UpdateCht->setText(QApplication::translate("EffOscWidgetClass", "\345\210\267\346\226\260\345\233\276\350\241\250", nullptr));
        radioButton_getWndConstrainData_GoBDSNR->setText(QApplication::translate("EffOscWidgetClass", "\350\241\224\346\216\245BDSNR", nullptr));
        label_WndSpecConstrainGenState->setText(QApplication::translate("EffOscWidgetClass", "\345\210\267\346\226\260\347\212\266\346\200\201\357\274\232", nullptr));
        btn_WndSpecConstrain_GenResult->setText(QApplication::translate("EffOscWidgetClass", "\347\224\237\346\210\220\346\212\221\345\210\266\347\273\223\346\236\234", nullptr));
        tabWidget_OscSepPannel->setTabText(tabWidget_OscSepPannel->indexOf(tab_WndSpecConstrain), QApplication::translate("EffOscWidgetClass", "\347\252\227\350\260\261\346\212\221\345\210\266", nullptr));
        groupBox_HAxisRange->setTitle(QApplication::translate("EffOscWidgetClass", "\346\250\252\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210hz\357\274\211", nullptr));
        label_OscSep_TimeSec_startFreq->setText(QApplication::translate("EffOscWidgetClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_OscSep_TimeSec_endFreq->setText(QApplication::translate("EffOscWidgetClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_15->setTitle(QApplication::translate("EffOscWidgetClass", "\347\272\265\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_OscSep_TimeSec_StartDB->setText(QApplication::translate("EffOscWidgetClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_OscSep_TimeSec_endDB->setText(QApplication::translate("EffOscWidgetClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_OscSep_TimeSec_BarBandWidth->setText(QApplication::translate("EffOscWidgetClass", "\351\242\221\347\216\207\346\240\274\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_OscSep_UpdateTimer->setText(QApplication::translate("EffOscWidgetClass", "\345\270\247\345\210\267\346\226\260\351\227\264\351\232\224(ms)", nullptr));
        groupBox_16->setTitle(QApplication::translate("EffOscWidgetClass", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        radioButton_TimeSecCht_STFT->setText(QApplication::translate("EffOscWidgetClass", "STFT", nullptr));
        radioButton_TimeSecCht_WndSepcConstrain->setText(QApplication::translate("EffOscWidgetClass", "\346\234\211\346\225\210\351\234\207\350\215\241", nullptr));
        groupBox_17->setTitle(QApplication::translate("EffOscWidgetClass", "\345\231\252\345\243\260\347\273\230\345\210\266", nullptr));
        checkBox_drawTIQLine->setText(QApplication::translate("EffOscWidgetClass", "\345\220\254\350\247\211\351\230\210\345\200\274\346\233\262\347\272\277", nullptr));
        checkBox_drawUnderTIQBar->setText(QApplication::translate("EffOscWidgetClass", "\345\260\217\344\272\216\345\220\254\351\230\210\350\276\223\345\205\245", nullptr));
        checkBox_drawWndSpecNoise->setText(QApplication::translate("EffOscWidgetClass", "\347\252\227\350\260\261\346\212\221\345\210\266\345\231\252\345\243\260", nullptr));
        label_TimeSecGenState->setText(QApplication::translate("EffOscWidgetClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateTimeSecCht->setText(QApplication::translate("EffOscWidgetClass", "\345\210\267\346\226\260\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276", nullptr));
        tabWidget_OscSepPannel->setTabText(tabWidget_OscSepPannel->indexOf(tab_TimeSecCht), QApplication::translate("EffOscWidgetClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_18->setTitle(QApplication::translate("EffOscWidgetClass", "\346\227\266\351\227\264\346\216\247\345\210\266", nullptr));
        label_OscSep_TimeFrameTime->setText(QApplication::translate("EffOscWidgetClass", "\346\210\252\351\235\242\346\227\266\351\227\264\357\274\23200\357\274\23200.000", nullptr));
        btn_lastFrame->setText(QApplication::translate("EffOscWidgetClass", "<", nullptr));
        btn_nextFrame->setText(QApplication::translate("EffOscWidgetClass", ">", nullptr));
        btn_play->setText(QApplication::translate("EffOscWidgetClass", "\346\222\255\346\224\276", nullptr));
        btn_stop->setText(QApplication::translate("EffOscWidgetClass", "\345\201\234\346\255\242", nullptr));
        btn_jump->setText(QApplication::translate("EffOscWidgetClass", "\350\267\263\350\275\254", nullptr));
        groupBox_19->setTitle(QApplication::translate("EffOscWidgetClass", "\346\227\266\351\227\264\347\225\214\351\235\242\345\270\247\344\277\241\346\201\257", nullptr));
        label_OscSep_Frame_CenterTime->setText(QApplication::translate("EffOscWidgetClass", "\346\210\252\351\235\242\346\227\266\351\227\264", nullptr));
        label_OscSep_Avr_SecFrameRate->setText(QApplication::translate("EffOscWidgetClass", "\345\271\263\345\235\207\345\270\247\347\216\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EffOscWidgetClass: public Ui_EffOscWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFOSCWIDGET_H
