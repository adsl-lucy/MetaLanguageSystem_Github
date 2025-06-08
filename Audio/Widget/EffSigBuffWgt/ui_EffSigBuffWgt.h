/********************************************************************************
** Form generated from reading UI file 'EffSigBuffWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFSIGBUFFWGT_H
#define UI_EFFSIGBUFFWGT_H

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
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EffSigBuffWgtClass
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab_unReasonable;
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
    QLabel *label_HotCht_StartDB;
    QSpinBox *SBox_HotCht_StartDB;
    QLabel *label_HotCht_endDB;
    QSpinBox *SBox_HotCht_EndDB;
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
    QGroupBox *groupBox_TimeSecCht;
    QHBoxLayout *HLayout_TimeSecCht;
    QTabWidget *tabWidget_EffSigBuffPannel;
    QWidget *tab_FreqDoubNetPara;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_AtkMinRatio;
    QDoubleSpinBox *DSBox_AtkMinRatio;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_SusMaxRatio;
    QDoubleSpinBox *DSBox_SusMaxRatio;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_SusMinRatio;
    QDoubleSpinBox *DSBox_SusMinRatio;
    QLabel *label_AtkMinRatio_DBVal;
    QLabel *label_SusMaxRatio_DBVal;
    QLabel *label_SusMinRatio_DBVal;
    QGroupBox *groupBox_getData;
    QHBoxLayout *horizontalLayout_17;
    QRadioButton *radioButton_getData_GoTimeSecCht;
    QLabel *label_VibState_GenState;
    QProgressBar *progressBar_VibState_GenResult;
    QPushButton *btn_VibStateRel_GenResult;
    QSpacerItem *verticalSpacer;
    QWidget *tab_TimeSecCht;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_HAxisRange;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_TimeSecCht_startFreq;
    QSpinBox *SBox_TimeSecCht_minFreq;
    QLabel *label_TimeSecCht_endFreq;
    QSpinBox *SBox_TimeSecCht_maxFreq;
    QGroupBox *groupBox_15;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_TimeSecCht_minDB;
    QSpinBox *SBox_TimeSecCht_minDB;
    QLabel *label_TimeSecCht_maxDB;
    QSpinBox *SBox_TimeSecCht_maxDB;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_UpdateTimer;
    QSpinBox *SBox_UpdateTimer;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_TimeSecChtBarType;
    QTabWidget *tabWidget_3;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBox_TimeSecCht_EffOsc_drawUnderTIQBar;
    QCheckBox *checkBox_TimeSecCht_EffOsc_drawTIQLine;
    QCheckBox *checkBox_TimeSecCht_EffOsc_drawWndSpecNoise;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox_TimeSecCht_BDSNR_drawFilter;
    QCheckBox *checkBox_TimeSecCht_BDSNR_drawFilterMain;
    QHBoxLayout *horizontalLayout_18;
    QCheckBox *checkBox_TimeSecCht_BDSNR_drawConstrainPt;
    QCheckBox *checkBox_TimeSecCht_BDSNR_drawSubPt;
    QHBoxLayout *horizontalLayout_50;
    QCheckBox *checkBox_TimeSecCht_BDSNR_drawNoisePt;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_VibState_AllState;
    QRadioButton *radioButton_VibState_transferState;
    QCheckBox *checkBox_VibState_Paint_NotTransfer;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_VibState_Paint_Atk;
    QCheckBox *checkBox_VibState_Paint_Increase;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_VibState_Paint_Sustain;
    QCheckBox *checkBox_VibState_Paint_Decrease;
    QLabel *label_TimeSecGenState;
    QHBoxLayout *horizontalLayout_52;
    QProgressBar *progressBar_TimeSec_Genstate;
    QPushButton *btn_updateTimeSecCht;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_53;
    QGroupBox *groupBox_18;
    QVBoxLayout *verticalLayout_18;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_54;
    QLabel *label_TimeFrameTime;
    QSlider *HSlider_TimeFrameIndex;
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
    QLabel *label_TimeSecCht_FrameCenterTime;
    QLabel *label_TimeSecCht_AvrSecFrameRate;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QWidget *EffSigBuffWgtClass)
    {
        if (EffSigBuffWgtClass->objectName().isEmpty())
            EffSigBuffWgtClass->setObjectName(QString::fromUtf8("EffSigBuffWgtClass"));
        EffSigBuffWgtClass->resize(1232, 851);
        verticalLayout_3 = new QVBoxLayout(EffSigBuffWgtClass);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget_2 = new QTabWidget(EffSigBuffWgtClass);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_unReasonable = new QWidget();
        tab_unReasonable->setObjectName(QString::fromUtf8("tab_unReasonable"));
        verticalLayout = new QVBoxLayout(tab_unReasonable);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        groupBox_HotCht = new QGroupBox(tab_unReasonable);
        groupBox_HotCht->setObjectName(QString::fromUtf8("groupBox_HotCht"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_HotCht->sizePolicy().hasHeightForWidth());
        groupBox_HotCht->setSizePolicy(sizePolicy);
        groupBox_HotCht->setMaximumSize(QSize(16777215, 16777215));
        VLayout_STFT_Cht_HotCht = new QVBoxLayout(groupBox_HotCht);
        VLayout_STFT_Cht_HotCht->setSpacing(6);
        VLayout_STFT_Cht_HotCht->setContentsMargins(11, 11, 11, 11);
        VLayout_STFT_Cht_HotCht->setObjectName(QString::fromUtf8("VLayout_STFT_Cht_HotCht"));

        horizontalLayout_20->addWidget(groupBox_HotCht);

        groupBox_HotChtPanel = new QGroupBox(tab_unReasonable);
        groupBox_HotChtPanel->setObjectName(QString::fromUtf8("groupBox_HotChtPanel"));
        sizePolicy.setHeightForWidth(groupBox_HotChtPanel->sizePolicy().hasHeightForWidth());
        groupBox_HotChtPanel->setSizePolicy(sizePolicy);
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
        label_HotCht_StartDB = new QLabel(groupBox_8);
        label_HotCht_StartDB->setObjectName(QString::fromUtf8("label_HotCht_StartDB"));

        horizontalLayout_23->addWidget(label_HotCht_StartDB);

        SBox_HotCht_StartDB = new QSpinBox(groupBox_8);
        SBox_HotCht_StartDB->setObjectName(QString::fromUtf8("SBox_HotCht_StartDB"));
        SBox_HotCht_StartDB->setMinimum(-20);
        SBox_HotCht_StartDB->setValue(0);

        horizontalLayout_23->addWidget(SBox_HotCht_StartDB);

        label_HotCht_endDB = new QLabel(groupBox_8);
        label_HotCht_endDB->setObjectName(QString::fromUtf8("label_HotCht_endDB"));

        horizontalLayout_23->addWidget(label_HotCht_endDB);

        SBox_HotCht_EndDB = new QSpinBox(groupBox_8);
        SBox_HotCht_EndDB->setObjectName(QString::fromUtf8("SBox_HotCht_EndDB"));
        SBox_HotCht_EndDB->setValue(60);

        horizontalLayout_23->addWidget(SBox_HotCht_EndDB);


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
        horizontalLayout_27->setSizeConstraint(QLayout::SetMaximumSize);
        groupBox_TimeSecCht = new QGroupBox(tab_unReasonable);
        groupBox_TimeSecCht->setObjectName(QString::fromUtf8("groupBox_TimeSecCht"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_TimeSecCht->sizePolicy().hasHeightForWidth());
        groupBox_TimeSecCht->setSizePolicy(sizePolicy1);
        HLayout_TimeSecCht = new QHBoxLayout(groupBox_TimeSecCht);
        HLayout_TimeSecCht->setSpacing(6);
        HLayout_TimeSecCht->setContentsMargins(11, 11, 11, 11);
        HLayout_TimeSecCht->setObjectName(QString::fromUtf8("HLayout_TimeSecCht"));

        horizontalLayout_27->addWidget(groupBox_TimeSecCht);

        tabWidget_EffSigBuffPannel = new QTabWidget(tab_unReasonable);
        tabWidget_EffSigBuffPannel->setObjectName(QString::fromUtf8("tabWidget_EffSigBuffPannel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget_EffSigBuffPannel->sizePolicy().hasHeightForWidth());
        tabWidget_EffSigBuffPannel->setSizePolicy(sizePolicy2);
        tabWidget_EffSigBuffPannel->setMaximumSize(QSize(280, 16777215));
        tab_FreqDoubNetPara = new QWidget();
        tab_FreqDoubNetPara->setObjectName(QString::fromUtf8("tab_FreqDoubNetPara"));
        verticalLayout_2 = new QVBoxLayout(tab_FreqDoubNetPara);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_AtkMinRatio = new QLabel(tab_FreqDoubNetPara);
        label_AtkMinRatio->setObjectName(QString::fromUtf8("label_AtkMinRatio"));

        horizontalLayout_28->addWidget(label_AtkMinRatio);

        DSBox_AtkMinRatio = new QDoubleSpinBox(tab_FreqDoubNetPara);
        DSBox_AtkMinRatio->setObjectName(QString::fromUtf8("DSBox_AtkMinRatio"));
        DSBox_AtkMinRatio->setMinimum(-200.000000000000000);
        DSBox_AtkMinRatio->setMaximum(4000.000000000000000);
        DSBox_AtkMinRatio->setValue(75.000000000000000);

        horizontalLayout_28->addWidget(DSBox_AtkMinRatio);


        verticalLayout_2->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_SusMaxRatio = new QLabel(tab_FreqDoubNetPara);
        label_SusMaxRatio->setObjectName(QString::fromUtf8("label_SusMaxRatio"));

        horizontalLayout_29->addWidget(label_SusMaxRatio);

        DSBox_SusMaxRatio = new QDoubleSpinBox(tab_FreqDoubNetPara);
        DSBox_SusMaxRatio->setObjectName(QString::fromUtf8("DSBox_SusMaxRatio"));
        DSBox_SusMaxRatio->setMinimum(-200.000000000000000);
        DSBox_SusMaxRatio->setMaximum(4000.000000000000000);
        DSBox_SusMaxRatio->setValue(20.000000000000000);

        horizontalLayout_29->addWidget(DSBox_SusMaxRatio);


        verticalLayout_2->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_SusMinRatio = new QLabel(tab_FreqDoubNetPara);
        label_SusMinRatio->setObjectName(QString::fromUtf8("label_SusMinRatio"));

        horizontalLayout_30->addWidget(label_SusMinRatio);

        DSBox_SusMinRatio = new QDoubleSpinBox(tab_FreqDoubNetPara);
        DSBox_SusMinRatio->setObjectName(QString::fromUtf8("DSBox_SusMinRatio"));
        DSBox_SusMinRatio->setMinimum(-200.000000000000000);
        DSBox_SusMinRatio->setMaximum(200.000000000000000);
        DSBox_SusMinRatio->setValue(-20.000000000000000);

        horizontalLayout_30->addWidget(DSBox_SusMinRatio);


        verticalLayout_2->addLayout(horizontalLayout_30);

        label_AtkMinRatio_DBVal = new QLabel(tab_FreqDoubNetPara);
        label_AtkMinRatio_DBVal->setObjectName(QString::fromUtf8("label_AtkMinRatio_DBVal"));

        verticalLayout_2->addWidget(label_AtkMinRatio_DBVal);

        label_SusMaxRatio_DBVal = new QLabel(tab_FreqDoubNetPara);
        label_SusMaxRatio_DBVal->setObjectName(QString::fromUtf8("label_SusMaxRatio_DBVal"));

        verticalLayout_2->addWidget(label_SusMaxRatio_DBVal);

        label_SusMinRatio_DBVal = new QLabel(tab_FreqDoubNetPara);
        label_SusMinRatio_DBVal->setObjectName(QString::fromUtf8("label_SusMinRatio_DBVal"));

        verticalLayout_2->addWidget(label_SusMinRatio_DBVal);

        groupBox_getData = new QGroupBox(tab_FreqDoubNetPara);
        groupBox_getData->setObjectName(QString::fromUtf8("groupBox_getData"));
        groupBox_getData->setMinimumSize(QSize(0, 0));
        horizontalLayout_17 = new QHBoxLayout(groupBox_getData);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        radioButton_getData_GoTimeSecCht = new QRadioButton(groupBox_getData);
        radioButton_getData_GoTimeSecCht->setObjectName(QString::fromUtf8("radioButton_getData_GoTimeSecCht"));
        radioButton_getData_GoTimeSecCht->setChecked(true);

        horizontalLayout_17->addWidget(radioButton_getData_GoTimeSecCht);


        verticalLayout_2->addWidget(groupBox_getData);

        label_VibState_GenState = new QLabel(tab_FreqDoubNetPara);
        label_VibState_GenState->setObjectName(QString::fromUtf8("label_VibState_GenState"));

        verticalLayout_2->addWidget(label_VibState_GenState);

        progressBar_VibState_GenResult = new QProgressBar(tab_FreqDoubNetPara);
        progressBar_VibState_GenResult->setObjectName(QString::fromUtf8("progressBar_VibState_GenResult"));
        progressBar_VibState_GenResult->setValue(0);

        verticalLayout_2->addWidget(progressBar_VibState_GenResult);

        btn_VibStateRel_GenResult = new QPushButton(tab_FreqDoubNetPara);
        btn_VibStateRel_GenResult->setObjectName(QString::fromUtf8("btn_VibStateRel_GenResult"));

        verticalLayout_2->addWidget(btn_VibStateRel_GenResult);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget_EffSigBuffPannel->addTab(tab_FreqDoubNetPara, QString());
        tab_TimeSecCht = new QWidget();
        tab_TimeSecCht->setObjectName(QString::fromUtf8("tab_TimeSecCht"));
        verticalLayout_6 = new QVBoxLayout(tab_TimeSecCht);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabWidget = new QTabWidget(tab_TimeSecCht);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_5 = new QVBoxLayout(tab_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_HAxisRange = new QGroupBox(tab_3);
        groupBox_HAxisRange->setObjectName(QString::fromUtf8("groupBox_HAxisRange"));
        horizontalLayout_44 = new QHBoxLayout(groupBox_HAxisRange);
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        label_TimeSecCht_startFreq = new QLabel(groupBox_HAxisRange);
        label_TimeSecCht_startFreq->setObjectName(QString::fromUtf8("label_TimeSecCht_startFreq"));

        horizontalLayout_44->addWidget(label_TimeSecCht_startFreq);

        SBox_TimeSecCht_minFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_TimeSecCht_minFreq->setObjectName(QString::fromUtf8("SBox_TimeSecCht_minFreq"));
        SBox_TimeSecCht_minFreq->setMaximum(22100);

        horizontalLayout_44->addWidget(SBox_TimeSecCht_minFreq);

        label_TimeSecCht_endFreq = new QLabel(groupBox_HAxisRange);
        label_TimeSecCht_endFreq->setObjectName(QString::fromUtf8("label_TimeSecCht_endFreq"));

        horizontalLayout_44->addWidget(label_TimeSecCht_endFreq);

        SBox_TimeSecCht_maxFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_TimeSecCht_maxFreq->setObjectName(QString::fromUtf8("SBox_TimeSecCht_maxFreq"));
        SBox_TimeSecCht_maxFreq->setMaximum(22100);
        SBox_TimeSecCht_maxFreq->setValue(4000);

        horizontalLayout_44->addWidget(SBox_TimeSecCht_maxFreq);


        verticalLayout_5->addWidget(groupBox_HAxisRange);

        groupBox_15 = new QGroupBox(tab_3);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        horizontalLayout_45 = new QHBoxLayout(groupBox_15);
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_TimeSecCht_minDB = new QLabel(groupBox_15);
        label_TimeSecCht_minDB->setObjectName(QString::fromUtf8("label_TimeSecCht_minDB"));

        horizontalLayout_45->addWidget(label_TimeSecCht_minDB);

        SBox_TimeSecCht_minDB = new QSpinBox(groupBox_15);
        SBox_TimeSecCht_minDB->setObjectName(QString::fromUtf8("SBox_TimeSecCht_minDB"));
        SBox_TimeSecCht_minDB->setMinimum(-20);
        SBox_TimeSecCht_minDB->setValue(0);

        horizontalLayout_45->addWidget(SBox_TimeSecCht_minDB);

        label_TimeSecCht_maxDB = new QLabel(groupBox_15);
        label_TimeSecCht_maxDB->setObjectName(QString::fromUtf8("label_TimeSecCht_maxDB"));

        horizontalLayout_45->addWidget(label_TimeSecCht_maxDB);

        SBox_TimeSecCht_maxDB = new QSpinBox(groupBox_15);
        SBox_TimeSecCht_maxDB->setObjectName(QString::fromUtf8("SBox_TimeSecCht_maxDB"));
        SBox_TimeSecCht_maxDB->setValue(80);

        horizontalLayout_45->addWidget(SBox_TimeSecCht_maxDB);


        verticalLayout_5->addWidget(groupBox_15);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        label_UpdateTimer = new QLabel(tab_3);
        label_UpdateTimer->setObjectName(QString::fromUtf8("label_UpdateTimer"));

        horizontalLayout_47->addWidget(label_UpdateTimer);

        SBox_UpdateTimer = new QSpinBox(tab_3);
        SBox_UpdateTimer->setObjectName(QString::fromUtf8("SBox_UpdateTimer"));
        SBox_UpdateTimer->setMinimum(1);
        SBox_UpdateTimer->setMaximum(200);
        SBox_UpdateTimer->setValue(20);

        horizontalLayout_47->addWidget(SBox_UpdateTimer);


        verticalLayout_5->addLayout(horizontalLayout_47);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_TimeSecChtBarType = new QComboBox(tab_4);
        comboBox_TimeSecChtBarType->addItem(QString());
        comboBox_TimeSecChtBarType->addItem(QString());
        comboBox_TimeSecChtBarType->addItem(QString());
        comboBox_TimeSecChtBarType->addItem(QString());
        comboBox_TimeSecChtBarType->setObjectName(QString::fromUtf8("comboBox_TimeSecChtBarType"));

        horizontalLayout->addWidget(comboBox_TimeSecChtBarType);


        verticalLayout_7->addLayout(horizontalLayout);

        tabWidget_3 = new QTabWidget(tab_4);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        checkBox_TimeSecCht_EffOsc_drawUnderTIQBar = new QCheckBox(tab_2);
        checkBox_TimeSecCht_EffOsc_drawUnderTIQBar->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_EffOsc_drawUnderTIQBar"));
        checkBox_TimeSecCht_EffOsc_drawUnderTIQBar->setChecked(false);

        verticalLayout_4->addWidget(checkBox_TimeSecCht_EffOsc_drawUnderTIQBar);

        checkBox_TimeSecCht_EffOsc_drawTIQLine = new QCheckBox(tab_2);
        checkBox_TimeSecCht_EffOsc_drawTIQLine->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_EffOsc_drawTIQLine"));
        checkBox_TimeSecCht_EffOsc_drawTIQLine->setMinimumSize(QSize(100, 0));
        checkBox_TimeSecCht_EffOsc_drawTIQLine->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_EffOsc_drawTIQLine->setChecked(false);

        verticalLayout_4->addWidget(checkBox_TimeSecCht_EffOsc_drawTIQLine);

        checkBox_TimeSecCht_EffOsc_drawWndSpecNoise = new QCheckBox(tab_2);
        checkBox_TimeSecCht_EffOsc_drawWndSpecNoise->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_EffOsc_drawWndSpecNoise"));
        checkBox_TimeSecCht_EffOsc_drawWndSpecNoise->setMinimumSize(QSize(100, 0));
        checkBox_TimeSecCht_EffOsc_drawWndSpecNoise->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_EffOsc_drawWndSpecNoise->setChecked(false);

        verticalLayout_4->addWidget(checkBox_TimeSecCht_EffOsc_drawWndSpecNoise);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        tabWidget_3->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_8 = new QVBoxLayout(tab_5);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        checkBox_TimeSecCht_BDSNR_drawFilter = new QCheckBox(tab_5);
        checkBox_TimeSecCht_BDSNR_drawFilter->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_BDSNR_drawFilter"));
        checkBox_TimeSecCht_BDSNR_drawFilter->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_BDSNR_drawFilter->setChecked(false);

        horizontalLayout_14->addWidget(checkBox_TimeSecCht_BDSNR_drawFilter);

        checkBox_TimeSecCht_BDSNR_drawFilterMain = new QCheckBox(tab_5);
        checkBox_TimeSecCht_BDSNR_drawFilterMain->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_BDSNR_drawFilterMain"));

        horizontalLayout_14->addWidget(checkBox_TimeSecCht_BDSNR_drawFilterMain);


        verticalLayout_8->addLayout(horizontalLayout_14);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        checkBox_TimeSecCht_BDSNR_drawConstrainPt = new QCheckBox(tab_5);
        checkBox_TimeSecCht_BDSNR_drawConstrainPt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_BDSNR_drawConstrainPt"));
        checkBox_TimeSecCht_BDSNR_drawConstrainPt->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_BDSNR_drawConstrainPt->setChecked(true);

        horizontalLayout_18->addWidget(checkBox_TimeSecCht_BDSNR_drawConstrainPt);

        checkBox_TimeSecCht_BDSNR_drawSubPt = new QCheckBox(tab_5);
        checkBox_TimeSecCht_BDSNR_drawSubPt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_BDSNR_drawSubPt"));
        checkBox_TimeSecCht_BDSNR_drawSubPt->setChecked(true);

        horizontalLayout_18->addWidget(checkBox_TimeSecCht_BDSNR_drawSubPt);


        verticalLayout_8->addLayout(horizontalLayout_18);

        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        checkBox_TimeSecCht_BDSNR_drawNoisePt = new QCheckBox(tab_5);
        checkBox_TimeSecCht_BDSNR_drawNoisePt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_BDSNR_drawNoisePt"));
        checkBox_TimeSecCht_BDSNR_drawNoisePt->setChecked(false);

        horizontalLayout_50->addWidget(checkBox_TimeSecCht_BDSNR_drawNoisePt);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_50->addItem(horizontalSpacer_3);


        verticalLayout_8->addLayout(horizontalLayout_50);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_3);

        tabWidget_3->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_10 = new QVBoxLayout(tab_6);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButton_VibState_AllState = new QRadioButton(tab_6);
        radioButton_VibState_AllState->setObjectName(QString::fromUtf8("radioButton_VibState_AllState"));
        radioButton_VibState_AllState->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_VibState_AllState);

        radioButton_VibState_transferState = new QRadioButton(tab_6);
        radioButton_VibState_transferState->setObjectName(QString::fromUtf8("radioButton_VibState_transferState"));

        horizontalLayout_2->addWidget(radioButton_VibState_transferState);


        verticalLayout_10->addLayout(horizontalLayout_2);

        checkBox_VibState_Paint_NotTransfer = new QCheckBox(tab_6);
        checkBox_VibState_Paint_NotTransfer->setObjectName(QString::fromUtf8("checkBox_VibState_Paint_NotTransfer"));
        checkBox_VibState_Paint_NotTransfer->setChecked(true);

        verticalLayout_10->addWidget(checkBox_VibState_Paint_NotTransfer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox_VibState_Paint_Atk = new QCheckBox(tab_6);
        checkBox_VibState_Paint_Atk->setObjectName(QString::fromUtf8("checkBox_VibState_Paint_Atk"));
        checkBox_VibState_Paint_Atk->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_VibState_Paint_Atk);

        checkBox_VibState_Paint_Increase = new QCheckBox(tab_6);
        checkBox_VibState_Paint_Increase->setObjectName(QString::fromUtf8("checkBox_VibState_Paint_Increase"));
        checkBox_VibState_Paint_Increase->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_VibState_Paint_Increase);


        verticalLayout_10->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBox_VibState_Paint_Sustain = new QCheckBox(tab_6);
        checkBox_VibState_Paint_Sustain->setObjectName(QString::fromUtf8("checkBox_VibState_Paint_Sustain"));
        checkBox_VibState_Paint_Sustain->setChecked(true);

        horizontalLayout_4->addWidget(checkBox_VibState_Paint_Sustain);

        checkBox_VibState_Paint_Decrease = new QCheckBox(tab_6);
        checkBox_VibState_Paint_Decrease->setObjectName(QString::fromUtf8("checkBox_VibState_Paint_Decrease"));
        checkBox_VibState_Paint_Decrease->setChecked(true);

        horizontalLayout_4->addWidget(checkBox_VibState_Paint_Decrease);


        verticalLayout_10->addLayout(horizontalLayout_4);

        tabWidget_3->addTab(tab_6, QString());

        verticalLayout_7->addWidget(tabWidget_3);

        tabWidget->addTab(tab_4, QString());

        verticalLayout_6->addWidget(tabWidget);

        label_TimeSecGenState = new QLabel(tab_TimeSecCht);
        label_TimeSecGenState->setObjectName(QString::fromUtf8("label_TimeSecGenState"));

        verticalLayout_6->addWidget(label_TimeSecGenState);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setSpacing(6);
        horizontalLayout_52->setObjectName(QString::fromUtf8("horizontalLayout_52"));
        progressBar_TimeSec_Genstate = new QProgressBar(tab_TimeSecCht);
        progressBar_TimeSec_Genstate->setObjectName(QString::fromUtf8("progressBar_TimeSec_Genstate"));
        progressBar_TimeSec_Genstate->setValue(0);

        horizontalLayout_52->addWidget(progressBar_TimeSec_Genstate);


        verticalLayout_6->addLayout(horizontalLayout_52);

        btn_updateTimeSecCht = new QPushButton(tab_TimeSecCht);
        btn_updateTimeSecCht->setObjectName(QString::fromUtf8("btn_updateTimeSecCht"));

        verticalLayout_6->addWidget(btn_updateTimeSecCht);

        verticalSpacer_8 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        tabWidget_EffSigBuffPannel->addTab(tab_TimeSecCht, QString());

        horizontalLayout_27->addWidget(tabWidget_EffSigBuffPannel);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(6);
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        horizontalLayout_53->setSizeConstraint(QLayout::SetDefaultConstraint);
        groupBox_18 = new QGroupBox(tab_unReasonable);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        sizePolicy.setHeightForWidth(groupBox_18->sizePolicy().hasHeightForWidth());
        groupBox_18->setSizePolicy(sizePolicy);
        groupBox_18->setMinimumSize(QSize(0, 92));
        groupBox_18->setMaximumSize(QSize(16777215, 92));
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
        label_TimeFrameTime = new QLabel(groupBox_18);
        label_TimeFrameTime->setObjectName(QString::fromUtf8("label_TimeFrameTime"));

        horizontalLayout_54->addWidget(label_TimeFrameTime);

        HSlider_TimeFrameIndex = new QSlider(groupBox_18);
        HSlider_TimeFrameIndex->setObjectName(QString::fromUtf8("HSlider_TimeFrameIndex"));
        HSlider_TimeFrameIndex->setOrientation(Qt::Horizontal);

        horizontalLayout_54->addWidget(HSlider_TimeFrameIndex);


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

        groupBox_19 = new QGroupBox(tab_unReasonable);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        sizePolicy.setHeightForWidth(groupBox_19->sizePolicy().hasHeightForWidth());
        groupBox_19->setSizePolicy(sizePolicy);
        groupBox_19->setMinimumSize(QSize(260, 92));
        groupBox_19->setMaximumSize(QSize(260, 92));
        verticalLayout_20 = new QVBoxLayout(groupBox_19);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_TimeSecCht_FrameCenterTime = new QLabel(groupBox_19);
        label_TimeSecCht_FrameCenterTime->setObjectName(QString::fromUtf8("label_TimeSecCht_FrameCenterTime"));

        verticalLayout_20->addWidget(label_TimeSecCht_FrameCenterTime);

        label_TimeSecCht_AvrSecFrameRate = new QLabel(groupBox_19);
        label_TimeSecCht_AvrSecFrameRate->setObjectName(QString::fromUtf8("label_TimeSecCht_AvrSecFrameRate"));

        verticalLayout_20->addWidget(label_TimeSecCht_AvrSecFrameRate);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_9);


        horizontalLayout_53->addWidget(groupBox_19);


        verticalLayout->addLayout(horizontalLayout_53);

        tabWidget_2->addTab(tab_unReasonable, QString());

        verticalLayout_3->addWidget(tabWidget_2);


        retranslateUi(EffSigBuffWgtClass);

        tabWidget_2->setCurrentIndex(0);
        tabWidget_EffSigBuffPannel->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        comboBox_TimeSecChtBarType->setCurrentIndex(3);
        tabWidget_3->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(EffSigBuffWgtClass);
    } // setupUi

    void retranslateUi(QWidget *EffSigBuffWgtClass)
    {
        EffSigBuffWgtClass->setWindowTitle(QApplication::translate("EffSigBuffWgtClass", "EffSigBuffWgt", nullptr));
        groupBox_HotCht->setTitle(QApplication::translate("EffSigBuffWgtClass", "\346\225\264\344\275\223\347\273\223\346\236\234", nullptr));
        groupBox_HotChtPanel->setTitle(QApplication::translate("EffSigBuffWgtClass", "\347\203\255\345\212\233\345\233\276\346\216\247\345\210\266", nullptr));
        label_STFTFileName->setText(QApplication::translate("EffSigBuffWgtClass", "\346\226\207\344\273\266\345\220\215\347\247\260", nullptr));
        label_dataDuration->setText(QApplication::translate("EffSigBuffWgtClass", "\346\225\260\346\215\256\346\214\201\347\273\255\346\227\266\351\227\264", nullptr));
        label_STFTState->setText(QApplication::translate("EffSigBuffWgtClass", "STFT\345\217\202\346\225\260\357\274\232", nullptr));
        label_hotChtStartTime->setText(QApplication::translate("EffSigBuffWgtClass", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeEdit_hotChtStartTime->setDisplayFormat(QApplication::translate("EffSigBuffWgtClass", "mm:ss", nullptr));
        label_hotChtTimeLength->setText(QApplication::translate("EffSigBuffWgtClass", "\347\252\227\345\217\243\351\225\277\345\272\246", nullptr));
        label_hotCht_startFreq->setText(QApplication::translate("EffSigBuffWgtClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_hotCht_endFreq->setText(QApplication::translate("EffSigBuffWgtClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_8->setTitle(QApplication::translate("EffSigBuffWgtClass", "\351\242\234\350\211\262\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_HotCht_StartDB->setText(QApplication::translate("EffSigBuffWgtClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_HotCht_endDB->setText(QApplication::translate("EffSigBuffWgtClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_HotChtFreqBandWidth->setText(QApplication::translate("EffSigBuffWgtClass", "\351\242\221\347\216\207\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_HotChtTimeIntervalMsec->setText(QApplication::translate("EffSigBuffWgtClass", "\346\227\266\351\227\264\345\270\246\345\256\275\357\274\210ms\357\274\211", nullptr));
        label_HotChtGenState->setText(QApplication::translate("EffSigBuffWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateHotCht->setText(QApplication::translate("EffSigBuffWgtClass", "\345\210\267\346\226\260", nullptr));
        groupBox_TimeSecCht->setTitle(QApplication::translate("EffSigBuffWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        label_AtkMinRatio->setText(QApplication::translate("EffSigBuffWgtClass", "\345\211\247\347\203\210\344\270\212\345\215\207\346\234\200\345\260\217\351\230\210\345\200\274\357\274\210%\357\274\211", nullptr));
        label_SusMaxRatio->setText(QApplication::translate("EffSigBuffWgtClass", "\345\260\217\346\263\242\345\212\250\346\234\200\345\244\247\351\230\210\345\200\274\357\274\210%\357\274\211", nullptr));
        label_SusMinRatio->setText(QApplication::translate("EffSigBuffWgtClass", "\345\260\217\346\263\242\345\212\250\346\234\200\345\260\217\351\230\210\345\200\274\357\274\210%\357\274\211", nullptr));
        label_AtkMinRatio_DBVal->setText(QApplication::translate("EffSigBuffWgtClass", "\345\211\247\347\203\210\344\270\212\345\215\207\346\234\200\345\260\217DB\345\242\236\345\271\205\357\274\232", nullptr));
        label_SusMaxRatio_DBVal->setText(QApplication::translate("EffSigBuffWgtClass", "\345\260\217\346\263\242\345\212\250\346\234\200\345\244\247DB\345\242\236\345\271\205\357\274\232", nullptr));
        label_SusMinRatio_DBVal->setText(QApplication::translate("EffSigBuffWgtClass", "\345\260\217\346\263\242\345\212\250\346\234\200\345\244\247DB\351\231\215\345\271\205\357\274\232", nullptr));
        groupBox_getData->setTitle(QApplication::translate("EffSigBuffWgtClass", "\347\224\237\346\210\220\345\220\216\350\241\224\346\216\245", nullptr));
        radioButton_getData_GoTimeSecCht->setText(QApplication::translate("EffSigBuffWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276", nullptr));
        label_VibState_GenState->setText(QApplication::translate("EffSigBuffWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201\357\274\232", nullptr));
        btn_VibStateRel_GenResult->setText(QApplication::translate("EffSigBuffWgtClass", "\347\224\237\346\210\220\347\273\223\346\236\234", nullptr));
        tabWidget_EffSigBuffPannel->setTabText(tabWidget_EffSigBuffPannel->indexOf(tab_FreqDoubNetPara), QApplication::translate("EffSigBuffWgtClass", "\346\214\257\345\212\250\347\212\266\346\200\201\351\230\210\345\200\274", nullptr));
        groupBox_HAxisRange->setTitle(QApplication::translate("EffSigBuffWgtClass", "\346\250\252\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210hz\357\274\211", nullptr));
        label_TimeSecCht_startFreq->setText(QApplication::translate("EffSigBuffWgtClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_TimeSecCht_endFreq->setText(QApplication::translate("EffSigBuffWgtClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_15->setTitle(QApplication::translate("EffSigBuffWgtClass", "\347\272\265\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_TimeSecCht_minDB->setText(QApplication::translate("EffSigBuffWgtClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_TimeSecCht_maxDB->setText(QApplication::translate("EffSigBuffWgtClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_UpdateTimer->setText(QApplication::translate("EffSigBuffWgtClass", "\345\270\247\345\210\267\346\226\260\351\227\264\351\232\224(ms)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("EffSigBuffWgtClass", "\345\235\220\346\240\207\347\263\273", nullptr));
        label->setText(QApplication::translate("EffSigBuffWgtClass", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        comboBox_TimeSecChtBarType->setItemText(0, QApplication::translate("EffSigBuffWgtClass", "STFT", nullptr));
        comboBox_TimeSecChtBarType->setItemText(1, QApplication::translate("EffSigBuffWgtClass", "EffOsc", nullptr));
        comboBox_TimeSecChtBarType->setItemText(2, QApplication::translate("EffSigBuffWgtClass", "BDSNR", nullptr));
        comboBox_TimeSecChtBarType->setItemText(3, QApplication::translate("EffSigBuffWgtClass", "VibState", nullptr));

        checkBox_TimeSecCht_EffOsc_drawUnderTIQBar->setText(QApplication::translate("EffSigBuffWgtClass", "\345\260\217\344\272\216\345\220\254\351\230\210\350\276\223\345\205\245", nullptr));
        checkBox_TimeSecCht_EffOsc_drawTIQLine->setText(QApplication::translate("EffSigBuffWgtClass", "\345\220\254\350\247\211\351\230\210\345\200\274\346\233\262\347\272\277", nullptr));
        checkBox_TimeSecCht_EffOsc_drawWndSpecNoise->setText(QApplication::translate("EffSigBuffWgtClass", "\347\252\227\350\260\261\346\212\221\345\210\266\345\231\252\345\243\260", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_2), QApplication::translate("EffSigBuffWgtClass", "EFFOSC", nullptr));
        checkBox_TimeSecCht_BDSNR_drawFilter->setText(QApplication::translate("EffSigBuffWgtClass", "\346\273\244\346\263\242\345\231\250\345\200\274", nullptr));
        checkBox_TimeSecCht_BDSNR_drawFilterMain->setText(QApplication::translate("EffSigBuffWgtClass", "\346\273\244\346\263\242\345\231\250\344\270\273\345\200\274", nullptr));
        checkBox_TimeSecCht_BDSNR_drawConstrainPt->setText(QApplication::translate("EffSigBuffWgtClass", "BDSNR\346\212\221\345\210\266\345\200\274", nullptr));
        checkBox_TimeSecCht_BDSNR_drawSubPt->setText(QApplication::translate("EffSigBuffWgtClass", "BDSNR\346\254\241\345\214\272\345\237\237\345\200\274", nullptr));
        checkBox_TimeSecCht_BDSNR_drawNoisePt->setText(QApplication::translate("EffSigBuffWgtClass", "BDSNR\345\231\252\345\243\260", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_5), QApplication::translate("EffSigBuffWgtClass", "BDSNR", nullptr));
        radioButton_VibState_AllState->setText(QApplication::translate("EffSigBuffWgtClass", "\345\205\250\347\212\266\346\200\201", nullptr));
        radioButton_VibState_transferState->setText(QApplication::translate("EffSigBuffWgtClass", "\344\273\205\350\275\254\345\214\226", nullptr));
        checkBox_VibState_Paint_NotTransfer->setText(QApplication::translate("EffSigBuffWgtClass", "notTransfer", nullptr));
        checkBox_VibState_Paint_Atk->setText(QApplication::translate("EffSigBuffWgtClass", "Atk", nullptr));
        checkBox_VibState_Paint_Increase->setText(QApplication::translate("EffSigBuffWgtClass", "Increase", nullptr));
        checkBox_VibState_Paint_Sustain->setText(QApplication::translate("EffSigBuffWgtClass", "Sustain", nullptr));
        checkBox_VibState_Paint_Decrease->setText(QApplication::translate("EffSigBuffWgtClass", "Decrease", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_6), QApplication::translate("EffSigBuffWgtClass", "VibState", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("EffSigBuffWgtClass", "\345\206\205\345\256\271", nullptr));
        label_TimeSecGenState->setText(QApplication::translate("EffSigBuffWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateTimeSecCht->setText(QApplication::translate("EffSigBuffWgtClass", "\345\210\267\346\226\260\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276", nullptr));
        tabWidget_EffSigBuffPannel->setTabText(tabWidget_EffSigBuffPannel->indexOf(tab_TimeSecCht), QApplication::translate("EffSigBuffWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_18->setTitle(QApplication::translate("EffSigBuffWgtClass", "\346\227\266\351\227\264\346\216\247\345\210\266", nullptr));
        label_TimeFrameTime->setText(QApplication::translate("EffSigBuffWgtClass", "\346\210\252\351\235\242\346\227\266\351\227\264\357\274\23200\357\274\23200.000", nullptr));
        btn_lastFrame->setText(QApplication::translate("EffSigBuffWgtClass", "<", nullptr));
        btn_nextFrame->setText(QApplication::translate("EffSigBuffWgtClass", ">", nullptr));
        btn_play->setText(QApplication::translate("EffSigBuffWgtClass", "\346\222\255\346\224\276", nullptr));
        btn_stop->setText(QApplication::translate("EffSigBuffWgtClass", "\345\201\234\346\255\242", nullptr));
        btn_jump->setText(QApplication::translate("EffSigBuffWgtClass", "\350\267\263\350\275\254", nullptr));
        groupBox_19->setTitle(QApplication::translate("EffSigBuffWgtClass", "\346\227\266\351\227\264\347\225\214\351\235\242\345\270\247\344\277\241\346\201\257", nullptr));
        label_TimeSecCht_FrameCenterTime->setText(QApplication::translate("EffSigBuffWgtClass", "\346\210\252\351\235\242\346\227\266\351\227\264", nullptr));
        label_TimeSecCht_AvrSecFrameRate->setText(QApplication::translate("EffSigBuffWgtClass", "\345\271\263\345\235\207\345\270\247\347\216\207", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_unReasonable), QApplication::translate("EffSigBuffWgtClass", "(\346\227\240\346\263\225\350\247\243\351\207\212\347\232\204\346\200\247\350\203\275\350\246\201\347\264\240)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EffSigBuffWgtClass: public Ui_EffSigBuffWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFSIGBUFFWGT_H
