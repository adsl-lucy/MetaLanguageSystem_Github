/********************************************************************************
** Form generated from reading UI file 'BandWidthSNRSelWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANDWIDTHSNRSELWGT_H
#define UI_BANDWIDTHSNRSELWGT_H

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

class Ui_BandWidthSNRSelWgtClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_Filter;
    QWidget *tab_BandWidthFilter;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *groupBox;
    QHBoxLayout *HLayout_BandWidthFilterCht;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_chtStartFreq;
    QSpinBox *SBox_chtStartFreq;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_chtEndFreq;
    QSpinBox *SBox_chtEndFreq;
    QPushButton *btn_updateBandWidthFilterCht;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_EqualWidthAreaMaxFreq;
    QSpinBox *SBox_EqualWidthAreaMaxFreq;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_EqualWidthAreaFilterCount;
    QSpinBox *SBox_EqualWidthAreaFilterCount;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_LogAreaFilterCount;
    QSpinBox *SBox_LogAreaFilterCount;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_STFTSampleRate;
    QSpinBox *SBox_STFTSampleRate;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_STFTWndPtCount;
    QSpinBox *SBox_STFTWndPtCount;
    QLabel *label_EqualWidthAreaFilterWidth;
    QLabel *label_totalFilterCount;
    QPushButton *btn_GenFilterAndUpdateCht;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_hotCht;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_20;
    QGroupBox *groupBox_HotCht;
    QVBoxLayout *VLayout_Cht_HotCht;
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
    QSpinBox *SBox_HotCht_StartDB;
    QLabel *label_ADSR_HotCht_endDB;
    QSpinBox *SBox_HotCht_EndDB;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_HotCht_FreqBandWidth;
    QSpinBox *SBox_HotCht_FreqBandWidth;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_HotCht_TimeIntervalMsec;
    QSpinBox *SBox_HotCht_TimeIntervalMsec;
    QLabel *label_HotChtGenState;
    QHBoxLayout *horizontalLayout_26;
    QProgressBar *progressBar_HotCht_Genstate;
    QPushButton *btn_updateHotCht;
    QHBoxLayout *horizontalLayout_27;
    QGroupBox *groupBox_11;
    QHBoxLayout *HLayout_BDSNR_TimeSecCht;
    QTabWidget *tabWidget_BDSNR_Panel;
    QWidget *tab_SNRConstrainCond;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_BDMaxValType;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_BDMaxVal_Max;
    QRadioButton *radioButton_BDMaxVal_WeightMax;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_FilterValDecreaseRatio_MainArea;
    QDoubleSpinBox *DSBox_FilterValDecreaseRatio_MainArea;
    QLabel *label_FilterValDecrease_DB_MainArea;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_FilterValDecreaseRatio_SubArea;
    QDoubleSpinBox *DSBox_FilterValDecreaseRatio_SubArea;
    QLabel *label_FilterValDecrease_DB_SubArea;
    QGroupBox *groupBox_FilterCond;
    QHBoxLayout *horizontalLayout_10;
    QRadioButton *radioButton_FilterCond_MainArea_Strong;
    QRadioButton *radioButton_FilterCond_MainArea_Weak;
    QRadioButton *radioButton_FilterCond_MainArea_Weight;
    QGroupBox *groupBox_FilterCond_2;
    QHBoxLayout *horizontalLayout_17;
    QRadioButton *radioButton_FilterCond_SubArea_Strong;
    QRadioButton *radioButton_FilterCond_SubArea_Weak;
    QRadioButton *radioButton_FilterCond_SubArea_Weight;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_15;
    QRadioButton *radioButton_getBDSNRData_GoTimeSecCht;
    QRadioButton *radioButton_getBDSNRData_GoEffSigBuff;
    QLabel *label_BDSNR_GenState;
    QProgressBar *progressBar_BDSNR_GenState;
    QPushButton *btn_GenBDSNRResult;
    QSpacerItem *verticalSpacer;
    QWidget *tab_TimeSecCht;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *groupBox_HAxisRange;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_OscSep_TimeSec_startFreq;
    QSpinBox *SBox_TimeSecCht_startFreq;
    QLabel *label_OscSep_TimeSec_endFreq;
    QSpinBox *SBox_TimeSecCht_endFreq;
    QGroupBox *groupBox_15;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_OscSep_TimeSec_StartDB;
    QSpinBox *SBox_TimeSecCht_StartDB;
    QLabel *label_OscSep_TimeSec_endDB;
    QSpinBox *SBox_TimeSecCht_EndDB;
    QGroupBox *groupBox_16;
    QHBoxLayout *horizontalLayout_48;
    QRadioButton *radioButton_TimeSecCht_STFT;
    QRadioButton *radioButton_TimeSecCht_WndSepcConstrain;
    QRadioButton *radioButton_TimeSecHct_BDSNR;
    QGroupBox *groupBox_17;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_49;
    QCheckBox *checkBox_TimeSecCht_drawTIQLine;
    QCheckBox *checkBox_TimeSecCht_drawUnderTIQBar;
    QHBoxLayout *horizontalLayout_50;
    QCheckBox *checkBox_TimeSecCht_drawWndSpecNoise;
    QCheckBox *checkBox_TimeSecCht_drawBDSNRNoisePt;
    QHBoxLayout *horizontalLayout_18;
    QCheckBox *checkBox_TimeSecCht_drawBDSNR_ConstrainPt;
    QCheckBox *checkBox_TimeSecCht_drawBDSNR_SubPt;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox_TimeSecCht_drawBDSNR_Filter;
    QCheckBox *checkBox_TimeSecCht_drawBDSNR_FilterMain;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_TimeSecCht_UpdateTimer;
    QSpinBox *SBox_TimeSecCht_UpdateTimer;
    QLabel *label_TimeSecGenState;
    QHBoxLayout *horizontalLayout_52;
    QProgressBar *progressBar_TimeSecCht_Genstate;
    QPushButton *btn_updateTimeSecCht;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_53;
    QGroupBox *groupBox_18;
    QVBoxLayout *verticalLayout_18;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_54;
    QLabel *labe_HSliderTime;
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
    QLabel *label_TimeSecCht_Frame_CenterTime;
    QLabel *label_TimeSecCht_Avr_SecFrameRate;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QWidget *BandWidthSNRSelWgtClass)
    {
        if (BandWidthSNRSelWgtClass->objectName().isEmpty())
            BandWidthSNRSelWgtClass->setObjectName(QString::fromUtf8("BandWidthSNRSelWgtClass"));
        BandWidthSNRSelWgtClass->resize(1263, 990);
        verticalLayout = new QVBoxLayout(BandWidthSNRSelWgtClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget_Filter = new QTabWidget(BandWidthSNRSelWgtClass);
        tabWidget_Filter->setObjectName(QString::fromUtf8("tabWidget_Filter"));
        tab_BandWidthFilter = new QWidget();
        tab_BandWidthFilter->setObjectName(QString::fromUtf8("tab_BandWidthFilter"));
        horizontalLayout_9 = new QHBoxLayout(tab_BandWidthFilter);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        groupBox = new QGroupBox(tab_BandWidthFilter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 300));
        HLayout_BandWidthFilterCht = new QHBoxLayout(groupBox);
        HLayout_BandWidthFilterCht->setSpacing(6);
        HLayout_BandWidthFilterCht->setContentsMargins(11, 11, 11, 11);
        HLayout_BandWidthFilterCht->setObjectName(QString::fromUtf8("HLayout_BandWidthFilterCht"));

        horizontalLayout_12->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_BandWidthFilter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(280, 0));
        groupBox_2->setMaximumSize(QSize(280, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_chtStartFreq = new QLabel(groupBox_2);
        label_chtStartFreq->setObjectName(QString::fromUtf8("label_chtStartFreq"));

        horizontalLayout->addWidget(label_chtStartFreq);

        SBox_chtStartFreq = new QSpinBox(groupBox_2);
        SBox_chtStartFreq->setObjectName(QString::fromUtf8("SBox_chtStartFreq"));
        SBox_chtStartFreq->setMaximumSize(QSize(80, 16777215));
        SBox_chtStartFreq->setMaximum(20000);

        horizontalLayout->addWidget(SBox_chtStartFreq);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_chtEndFreq = new QLabel(groupBox_2);
        label_chtEndFreq->setObjectName(QString::fromUtf8("label_chtEndFreq"));

        horizontalLayout_2->addWidget(label_chtEndFreq);

        SBox_chtEndFreq = new QSpinBox(groupBox_2);
        SBox_chtEndFreq->setObjectName(QString::fromUtf8("SBox_chtEndFreq"));
        SBox_chtEndFreq->setMaximumSize(QSize(80, 16777215));
        SBox_chtEndFreq->setMaximum(22000);
        SBox_chtEndFreq->setValue(20000);

        horizontalLayout_2->addWidget(SBox_chtEndFreq);


        verticalLayout_2->addLayout(horizontalLayout_2);

        btn_updateBandWidthFilterCht = new QPushButton(groupBox_2);
        btn_updateBandWidthFilterCht->setObjectName(QString::fromUtf8("btn_updateBandWidthFilterCht"));

        verticalLayout_2->addWidget(btn_updateBandWidthFilterCht);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_EqualWidthAreaMaxFreq = new QLabel(groupBox_2);
        label_EqualWidthAreaMaxFreq->setObjectName(QString::fromUtf8("label_EqualWidthAreaMaxFreq"));

        horizontalLayout_3->addWidget(label_EqualWidthAreaMaxFreq);

        SBox_EqualWidthAreaMaxFreq = new QSpinBox(groupBox_2);
        SBox_EqualWidthAreaMaxFreq->setObjectName(QString::fromUtf8("SBox_EqualWidthAreaMaxFreq"));
        SBox_EqualWidthAreaMaxFreq->setMinimumSize(QSize(80, 0));
        SBox_EqualWidthAreaMaxFreq->setMaximumSize(QSize(80, 16777215));
        SBox_EqualWidthAreaMaxFreq->setMaximum(20000);
        SBox_EqualWidthAreaMaxFreq->setValue(5000);

        horizontalLayout_3->addWidget(SBox_EqualWidthAreaMaxFreq);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_EqualWidthAreaFilterCount = new QLabel(groupBox_2);
        label_EqualWidthAreaFilterCount->setObjectName(QString::fromUtf8("label_EqualWidthAreaFilterCount"));

        horizontalLayout_4->addWidget(label_EqualWidthAreaFilterCount);

        SBox_EqualWidthAreaFilterCount = new QSpinBox(groupBox_2);
        SBox_EqualWidthAreaFilterCount->setObjectName(QString::fromUtf8("SBox_EqualWidthAreaFilterCount"));
        SBox_EqualWidthAreaFilterCount->setMinimumSize(QSize(80, 0));
        SBox_EqualWidthAreaFilterCount->setMaximumSize(QSize(80, 16777215));
        SBox_EqualWidthAreaFilterCount->setValue(20);

        horizontalLayout_4->addWidget(SBox_EqualWidthAreaFilterCount);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_LogAreaFilterCount = new QLabel(groupBox_2);
        label_LogAreaFilterCount->setObjectName(QString::fromUtf8("label_LogAreaFilterCount"));

        horizontalLayout_5->addWidget(label_LogAreaFilterCount);

        SBox_LogAreaFilterCount = new QSpinBox(groupBox_2);
        SBox_LogAreaFilterCount->setObjectName(QString::fromUtf8("SBox_LogAreaFilterCount"));
        SBox_LogAreaFilterCount->setMinimumSize(QSize(80, 0));
        SBox_LogAreaFilterCount->setMaximumSize(QSize(80, 16777215));
        SBox_LogAreaFilterCount->setValue(28);

        horizontalLayout_5->addWidget(SBox_LogAreaFilterCount);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_STFTSampleRate = new QLabel(groupBox_2);
        label_STFTSampleRate->setObjectName(QString::fromUtf8("label_STFTSampleRate"));

        horizontalLayout_7->addWidget(label_STFTSampleRate);

        SBox_STFTSampleRate = new QSpinBox(groupBox_2);
        SBox_STFTSampleRate->setObjectName(QString::fromUtf8("SBox_STFTSampleRate"));
        SBox_STFTSampleRate->setMinimumSize(QSize(80, 0));
        SBox_STFTSampleRate->setMaximumSize(QSize(80, 16777215));
        SBox_STFTSampleRate->setMaximum(48000);
        SBox_STFTSampleRate->setValue(48000);

        horizontalLayout_7->addWidget(SBox_STFTSampleRate);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_STFTWndPtCount = new QLabel(groupBox_2);
        label_STFTWndPtCount->setObjectName(QString::fromUtf8("label_STFTWndPtCount"));

        horizontalLayout_8->addWidget(label_STFTWndPtCount);

        SBox_STFTWndPtCount = new QSpinBox(groupBox_2);
        SBox_STFTWndPtCount->setObjectName(QString::fromUtf8("SBox_STFTWndPtCount"));
        SBox_STFTWndPtCount->setMinimumSize(QSize(80, 0));
        SBox_STFTWndPtCount->setMaximumSize(QSize(80, 16777215));
        SBox_STFTWndPtCount->setMaximum(100000);
        SBox_STFTWndPtCount->setValue(4096);

        horizontalLayout_8->addWidget(SBox_STFTWndPtCount);


        verticalLayout_2->addLayout(horizontalLayout_8);

        label_EqualWidthAreaFilterWidth = new QLabel(groupBox_2);
        label_EqualWidthAreaFilterWidth->setObjectName(QString::fromUtf8("label_EqualWidthAreaFilterWidth"));

        verticalLayout_2->addWidget(label_EqualWidthAreaFilterWidth);

        label_totalFilterCount = new QLabel(groupBox_2);
        label_totalFilterCount->setObjectName(QString::fromUtf8("label_totalFilterCount"));

        verticalLayout_2->addWidget(label_totalFilterCount);

        btn_GenFilterAndUpdateCht = new QPushButton(groupBox_2);
        btn_GenFilterAndUpdateCht->setObjectName(QString::fromUtf8("btn_GenFilterAndUpdateCht"));

        verticalLayout_2->addWidget(btn_GenFilterAndUpdateCht);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout_12->addWidget(groupBox_2);


        horizontalLayout_9->addLayout(horizontalLayout_12);

        tabWidget_Filter->addTab(tab_BandWidthFilter, QString());
        tab_hotCht = new QWidget();
        tab_hotCht->setObjectName(QString::fromUtf8("tab_hotCht"));
        horizontalLayout_13 = new QHBoxLayout(tab_hotCht);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        groupBox_HotCht = new QGroupBox(tab_hotCht);
        groupBox_HotCht->setObjectName(QString::fromUtf8("groupBox_HotCht"));
        groupBox_HotCht->setMaximumSize(QSize(16777215, 16777215));
        VLayout_Cht_HotCht = new QVBoxLayout(groupBox_HotCht);
        VLayout_Cht_HotCht->setSpacing(6);
        VLayout_Cht_HotCht->setContentsMargins(11, 11, 11, 11);
        VLayout_Cht_HotCht->setObjectName(QString::fromUtf8("VLayout_Cht_HotCht"));

        horizontalLayout_20->addWidget(groupBox_HotCht);

        groupBox_HotChtPanel = new QGroupBox(tab_hotCht);
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

        SBox_HotCht_StartDB = new QSpinBox(groupBox_8);
        SBox_HotCht_StartDB->setObjectName(QString::fromUtf8("SBox_HotCht_StartDB"));
        SBox_HotCht_StartDB->setMinimum(-20);
        SBox_HotCht_StartDB->setValue(0);

        horizontalLayout_23->addWidget(SBox_HotCht_StartDB);

        label_ADSR_HotCht_endDB = new QLabel(groupBox_8);
        label_ADSR_HotCht_endDB->setObjectName(QString::fromUtf8("label_ADSR_HotCht_endDB"));

        horizontalLayout_23->addWidget(label_ADSR_HotCht_endDB);

        SBox_HotCht_EndDB = new QSpinBox(groupBox_8);
        SBox_HotCht_EndDB->setObjectName(QString::fromUtf8("SBox_HotCht_EndDB"));
        SBox_HotCht_EndDB->setValue(60);

        horizontalLayout_23->addWidget(SBox_HotCht_EndDB);


        verticalLayout_9->addWidget(groupBox_8);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_HotCht_FreqBandWidth = new QLabel(groupBox_HotChtPanel);
        label_HotCht_FreqBandWidth->setObjectName(QString::fromUtf8("label_HotCht_FreqBandWidth"));

        horizontalLayout_24->addWidget(label_HotCht_FreqBandWidth);

        SBox_HotCht_FreqBandWidth = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotCht_FreqBandWidth->setObjectName(QString::fromUtf8("SBox_HotCht_FreqBandWidth"));
        SBox_HotCht_FreqBandWidth->setMinimum(1);
        SBox_HotCht_FreqBandWidth->setValue(11);

        horizontalLayout_24->addWidget(SBox_HotCht_FreqBandWidth);


        verticalLayout_9->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_HotCht_TimeIntervalMsec = new QLabel(groupBox_HotChtPanel);
        label_HotCht_TimeIntervalMsec->setObjectName(QString::fromUtf8("label_HotCht_TimeIntervalMsec"));

        horizontalLayout_25->addWidget(label_HotCht_TimeIntervalMsec);

        SBox_HotCht_TimeIntervalMsec = new QSpinBox(groupBox_HotChtPanel);
        SBox_HotCht_TimeIntervalMsec->setObjectName(QString::fromUtf8("SBox_HotCht_TimeIntervalMsec"));
        SBox_HotCht_TimeIntervalMsec->setMinimum(1);
        SBox_HotCht_TimeIntervalMsec->setValue(20);

        horizontalLayout_25->addWidget(SBox_HotCht_TimeIntervalMsec);


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


        horizontalLayout_13->addLayout(horizontalLayout_20);

        tabWidget_Filter->addTab(tab_hotCht, QString());

        verticalLayout->addWidget(tabWidget_Filter);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(9, -1, 9, -1);
        groupBox_11 = new QGroupBox(BandWidthSNRSelWgtClass);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        HLayout_BDSNR_TimeSecCht = new QHBoxLayout(groupBox_11);
        HLayout_BDSNR_TimeSecCht->setSpacing(6);
        HLayout_BDSNR_TimeSecCht->setContentsMargins(11, 11, 11, 11);
        HLayout_BDSNR_TimeSecCht->setObjectName(QString::fromUtf8("HLayout_BDSNR_TimeSecCht"));

        horizontalLayout_27->addWidget(groupBox_11);

        tabWidget_BDSNR_Panel = new QTabWidget(BandWidthSNRSelWgtClass);
        tabWidget_BDSNR_Panel->setObjectName(QString::fromUtf8("tabWidget_BDSNR_Panel"));
        tabWidget_BDSNR_Panel->setMaximumSize(QSize(280, 16777215));
        tab_SNRConstrainCond = new QWidget();
        tab_SNRConstrainCond->setObjectName(QString::fromUtf8("tab_SNRConstrainCond"));
        verticalLayout_3 = new QVBoxLayout(tab_SNRConstrainCond);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_BDMaxValType = new QGroupBox(tab_SNRConstrainCond);
        groupBox_BDMaxValType->setObjectName(QString::fromUtf8("groupBox_BDMaxValType"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_BDMaxValType);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        radioButton_BDMaxVal_Max = new QRadioButton(groupBox_BDMaxValType);
        radioButton_BDMaxVal_Max->setObjectName(QString::fromUtf8("radioButton_BDMaxVal_Max"));

        horizontalLayout_6->addWidget(radioButton_BDMaxVal_Max);

        radioButton_BDMaxVal_WeightMax = new QRadioButton(groupBox_BDMaxValType);
        radioButton_BDMaxVal_WeightMax->setObjectName(QString::fromUtf8("radioButton_BDMaxVal_WeightMax"));
        radioButton_BDMaxVal_WeightMax->setChecked(true);

        horizontalLayout_6->addWidget(radioButton_BDMaxVal_WeightMax);


        verticalLayout_3->addWidget(groupBox_BDMaxValType);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_FilterValDecreaseRatio_MainArea = new QLabel(tab_SNRConstrainCond);
        label_FilterValDecreaseRatio_MainArea->setObjectName(QString::fromUtf8("label_FilterValDecreaseRatio_MainArea"));

        horizontalLayout_11->addWidget(label_FilterValDecreaseRatio_MainArea);

        DSBox_FilterValDecreaseRatio_MainArea = new QDoubleSpinBox(tab_SNRConstrainCond);
        DSBox_FilterValDecreaseRatio_MainArea->setObjectName(QString::fromUtf8("DSBox_FilterValDecreaseRatio_MainArea"));
        DSBox_FilterValDecreaseRatio_MainArea->setMaximumSize(QSize(72, 16777215));
        DSBox_FilterValDecreaseRatio_MainArea->setValue(57.829999999999998);

        horizontalLayout_11->addWidget(DSBox_FilterValDecreaseRatio_MainArea);


        verticalLayout_3->addLayout(horizontalLayout_11);

        label_FilterValDecrease_DB_MainArea = new QLabel(tab_SNRConstrainCond);
        label_FilterValDecrease_DB_MainArea->setObjectName(QString::fromUtf8("label_FilterValDecrease_DB_MainArea"));

        verticalLayout_3->addWidget(label_FilterValDecrease_DB_MainArea);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_FilterValDecreaseRatio_SubArea = new QLabel(tab_SNRConstrainCond);
        label_FilterValDecreaseRatio_SubArea->setObjectName(QString::fromUtf8("label_FilterValDecreaseRatio_SubArea"));

        horizontalLayout_16->addWidget(label_FilterValDecreaseRatio_SubArea);

        DSBox_FilterValDecreaseRatio_SubArea = new QDoubleSpinBox(tab_SNRConstrainCond);
        DSBox_FilterValDecreaseRatio_SubArea->setObjectName(QString::fromUtf8("DSBox_FilterValDecreaseRatio_SubArea"));
        DSBox_FilterValDecreaseRatio_SubArea->setMaximumSize(QSize(72, 16777215));
        DSBox_FilterValDecreaseRatio_SubArea->setValue(82.209999999999994);

        horizontalLayout_16->addWidget(DSBox_FilterValDecreaseRatio_SubArea);


        verticalLayout_3->addLayout(horizontalLayout_16);

        label_FilterValDecrease_DB_SubArea = new QLabel(tab_SNRConstrainCond);
        label_FilterValDecrease_DB_SubArea->setObjectName(QString::fromUtf8("label_FilterValDecrease_DB_SubArea"));

        verticalLayout_3->addWidget(label_FilterValDecrease_DB_SubArea);

        groupBox_FilterCond = new QGroupBox(tab_SNRConstrainCond);
        groupBox_FilterCond->setObjectName(QString::fromUtf8("groupBox_FilterCond"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_FilterCond);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        radioButton_FilterCond_MainArea_Strong = new QRadioButton(groupBox_FilterCond);
        radioButton_FilterCond_MainArea_Strong->setObjectName(QString::fromUtf8("radioButton_FilterCond_MainArea_Strong"));
        radioButton_FilterCond_MainArea_Strong->setChecked(true);

        horizontalLayout_10->addWidget(radioButton_FilterCond_MainArea_Strong);

        radioButton_FilterCond_MainArea_Weak = new QRadioButton(groupBox_FilterCond);
        radioButton_FilterCond_MainArea_Weak->setObjectName(QString::fromUtf8("radioButton_FilterCond_MainArea_Weak"));

        horizontalLayout_10->addWidget(radioButton_FilterCond_MainArea_Weak);

        radioButton_FilterCond_MainArea_Weight = new QRadioButton(groupBox_FilterCond);
        radioButton_FilterCond_MainArea_Weight->setObjectName(QString::fromUtf8("radioButton_FilterCond_MainArea_Weight"));
        radioButton_FilterCond_MainArea_Weight->setChecked(false);

        horizontalLayout_10->addWidget(radioButton_FilterCond_MainArea_Weight);


        verticalLayout_3->addWidget(groupBox_FilterCond);

        groupBox_FilterCond_2 = new QGroupBox(tab_SNRConstrainCond);
        groupBox_FilterCond_2->setObjectName(QString::fromUtf8("groupBox_FilterCond_2"));
        horizontalLayout_17 = new QHBoxLayout(groupBox_FilterCond_2);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        radioButton_FilterCond_SubArea_Strong = new QRadioButton(groupBox_FilterCond_2);
        radioButton_FilterCond_SubArea_Strong->setObjectName(QString::fromUtf8("radioButton_FilterCond_SubArea_Strong"));

        horizontalLayout_17->addWidget(radioButton_FilterCond_SubArea_Strong);

        radioButton_FilterCond_SubArea_Weak = new QRadioButton(groupBox_FilterCond_2);
        radioButton_FilterCond_SubArea_Weak->setObjectName(QString::fromUtf8("radioButton_FilterCond_SubArea_Weak"));

        horizontalLayout_17->addWidget(radioButton_FilterCond_SubArea_Weak);

        radioButton_FilterCond_SubArea_Weight = new QRadioButton(groupBox_FilterCond_2);
        radioButton_FilterCond_SubArea_Weight->setObjectName(QString::fromUtf8("radioButton_FilterCond_SubArea_Weight"));
        radioButton_FilterCond_SubArea_Weight->setChecked(true);

        horizontalLayout_17->addWidget(radioButton_FilterCond_SubArea_Weight);


        verticalLayout_3->addWidget(groupBox_FilterCond_2);

        groupBox_3 = new QGroupBox(tab_SNRConstrainCond);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 0));
        horizontalLayout_15 = new QHBoxLayout(groupBox_3);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        radioButton_getBDSNRData_GoTimeSecCht = new QRadioButton(groupBox_3);
        radioButton_getBDSNRData_GoTimeSecCht->setObjectName(QString::fromUtf8("radioButton_getBDSNRData_GoTimeSecCht"));

        horizontalLayout_15->addWidget(radioButton_getBDSNRData_GoTimeSecCht);

        radioButton_getBDSNRData_GoEffSigBuff = new QRadioButton(groupBox_3);
        radioButton_getBDSNRData_GoEffSigBuff->setObjectName(QString::fromUtf8("radioButton_getBDSNRData_GoEffSigBuff"));
        radioButton_getBDSNRData_GoEffSigBuff->setChecked(true);

        horizontalLayout_15->addWidget(radioButton_getBDSNRData_GoEffSigBuff);


        verticalLayout_3->addWidget(groupBox_3);

        label_BDSNR_GenState = new QLabel(tab_SNRConstrainCond);
        label_BDSNR_GenState->setObjectName(QString::fromUtf8("label_BDSNR_GenState"));

        verticalLayout_3->addWidget(label_BDSNR_GenState);

        progressBar_BDSNR_GenState = new QProgressBar(tab_SNRConstrainCond);
        progressBar_BDSNR_GenState->setObjectName(QString::fromUtf8("progressBar_BDSNR_GenState"));
        progressBar_BDSNR_GenState->setValue(0);

        verticalLayout_3->addWidget(progressBar_BDSNR_GenState);

        btn_GenBDSNRResult = new QPushButton(tab_SNRConstrainCond);
        btn_GenBDSNRResult->setObjectName(QString::fromUtf8("btn_GenBDSNRResult"));

        verticalLayout_3->addWidget(btn_GenBDSNRResult);

        verticalSpacer = new QSpacerItem(20, 209, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget_BDSNR_Panel->addTab(tab_SNRConstrainCond, QString());
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

        SBox_TimeSecCht_startFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_TimeSecCht_startFreq->setObjectName(QString::fromUtf8("SBox_TimeSecCht_startFreq"));
        SBox_TimeSecCht_startFreq->setMaximum(22100);

        horizontalLayout_44->addWidget(SBox_TimeSecCht_startFreq);

        label_OscSep_TimeSec_endFreq = new QLabel(groupBox_HAxisRange);
        label_OscSep_TimeSec_endFreq->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_endFreq"));

        horizontalLayout_44->addWidget(label_OscSep_TimeSec_endFreq);

        SBox_TimeSecCht_endFreq = new QSpinBox(groupBox_HAxisRange);
        SBox_TimeSecCht_endFreq->setObjectName(QString::fromUtf8("SBox_TimeSecCht_endFreq"));
        SBox_TimeSecCht_endFreq->setMaximum(22100);
        SBox_TimeSecCht_endFreq->setValue(4000);

        horizontalLayout_44->addWidget(SBox_TimeSecCht_endFreq);


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

        SBox_TimeSecCht_StartDB = new QSpinBox(groupBox_15);
        SBox_TimeSecCht_StartDB->setObjectName(QString::fromUtf8("SBox_TimeSecCht_StartDB"));
        SBox_TimeSecCht_StartDB->setMinimum(0);
        SBox_TimeSecCht_StartDB->setValue(0);

        horizontalLayout_45->addWidget(SBox_TimeSecCht_StartDB);

        label_OscSep_TimeSec_endDB = new QLabel(groupBox_15);
        label_OscSep_TimeSec_endDB->setObjectName(QString::fromUtf8("label_OscSep_TimeSec_endDB"));

        horizontalLayout_45->addWidget(label_OscSep_TimeSec_endDB);

        SBox_TimeSecCht_EndDB = new QSpinBox(groupBox_15);
        SBox_TimeSecCht_EndDB->setObjectName(QString::fromUtf8("SBox_TimeSecCht_EndDB"));
        SBox_TimeSecCht_EndDB->setValue(80);

        horizontalLayout_45->addWidget(SBox_TimeSecCht_EndDB);


        verticalLayout_16->addWidget(groupBox_15);

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
        radioButton_TimeSecCht_WndSepcConstrain->setChecked(false);

        horizontalLayout_48->addWidget(radioButton_TimeSecCht_WndSepcConstrain);

        radioButton_TimeSecHct_BDSNR = new QRadioButton(groupBox_16);
        radioButton_TimeSecHct_BDSNR->setObjectName(QString::fromUtf8("radioButton_TimeSecHct_BDSNR"));
        radioButton_TimeSecHct_BDSNR->setCheckable(true);
        radioButton_TimeSecHct_BDSNR->setChecked(true);

        horizontalLayout_48->addWidget(radioButton_TimeSecHct_BDSNR);


        verticalLayout_16->addWidget(groupBox_16);

        groupBox_17 = new QGroupBox(tab_TimeSecCht);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        groupBox_17->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(groupBox_17);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        checkBox_TimeSecCht_drawTIQLine = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawTIQLine->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawTIQLine"));
        checkBox_TimeSecCht_drawTIQLine->setMinimumSize(QSize(100, 0));
        checkBox_TimeSecCht_drawTIQLine->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_drawTIQLine->setChecked(false);

        horizontalLayout_49->addWidget(checkBox_TimeSecCht_drawTIQLine);

        checkBox_TimeSecCht_drawUnderTIQBar = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawUnderTIQBar->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawUnderTIQBar"));
        checkBox_TimeSecCht_drawUnderTIQBar->setChecked(false);

        horizontalLayout_49->addWidget(checkBox_TimeSecCht_drawUnderTIQBar);


        verticalLayout_4->addLayout(horizontalLayout_49);

        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        checkBox_TimeSecCht_drawWndSpecNoise = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawWndSpecNoise->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawWndSpecNoise"));
        checkBox_TimeSecCht_drawWndSpecNoise->setMinimumSize(QSize(100, 0));
        checkBox_TimeSecCht_drawWndSpecNoise->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_drawWndSpecNoise->setChecked(false);

        horizontalLayout_50->addWidget(checkBox_TimeSecCht_drawWndSpecNoise);

        checkBox_TimeSecCht_drawBDSNRNoisePt = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawBDSNRNoisePt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNRNoisePt"));
        checkBox_TimeSecCht_drawBDSNRNoisePt->setChecked(true);

        horizontalLayout_50->addWidget(checkBox_TimeSecCht_drawBDSNRNoisePt);


        verticalLayout_4->addLayout(horizontalLayout_50);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        checkBox_TimeSecCht_drawBDSNR_ConstrainPt = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawBDSNR_ConstrainPt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNR_ConstrainPt"));
        checkBox_TimeSecCht_drawBDSNR_ConstrainPt->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_drawBDSNR_ConstrainPt->setChecked(true);

        horizontalLayout_18->addWidget(checkBox_TimeSecCht_drawBDSNR_ConstrainPt);

        checkBox_TimeSecCht_drawBDSNR_SubPt = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawBDSNR_SubPt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNR_SubPt"));
        checkBox_TimeSecCht_drawBDSNR_SubPt->setChecked(true);

        horizontalLayout_18->addWidget(checkBox_TimeSecCht_drawBDSNR_SubPt);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        checkBox_TimeSecCht_drawBDSNR_Filter = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawBDSNR_Filter->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNR_Filter"));
        checkBox_TimeSecCht_drawBDSNR_Filter->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_drawBDSNR_Filter->setChecked(false);

        horizontalLayout_14->addWidget(checkBox_TimeSecCht_drawBDSNR_Filter);

        checkBox_TimeSecCht_drawBDSNR_FilterMain = new QCheckBox(groupBox_17);
        checkBox_TimeSecCht_drawBDSNR_FilterMain->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNR_FilterMain"));

        horizontalLayout_14->addWidget(checkBox_TimeSecCht_drawBDSNR_FilterMain);


        verticalLayout_4->addLayout(horizontalLayout_14);


        verticalLayout_16->addWidget(groupBox_17);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        label_TimeSecCht_UpdateTimer = new QLabel(tab_TimeSecCht);
        label_TimeSecCht_UpdateTimer->setObjectName(QString::fromUtf8("label_TimeSecCht_UpdateTimer"));

        horizontalLayout_47->addWidget(label_TimeSecCht_UpdateTimer);

        SBox_TimeSecCht_UpdateTimer = new QSpinBox(tab_TimeSecCht);
        SBox_TimeSecCht_UpdateTimer->setObjectName(QString::fromUtf8("SBox_TimeSecCht_UpdateTimer"));
        SBox_TimeSecCht_UpdateTimer->setMinimum(1);
        SBox_TimeSecCht_UpdateTimer->setMaximum(200);
        SBox_TimeSecCht_UpdateTimer->setValue(20);

        horizontalLayout_47->addWidget(SBox_TimeSecCht_UpdateTimer);


        verticalLayout_16->addLayout(horizontalLayout_47);

        label_TimeSecGenState = new QLabel(tab_TimeSecCht);
        label_TimeSecGenState->setObjectName(QString::fromUtf8("label_TimeSecGenState"));

        verticalLayout_16->addWidget(label_TimeSecGenState);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setSpacing(6);
        horizontalLayout_52->setObjectName(QString::fromUtf8("horizontalLayout_52"));
        progressBar_TimeSecCht_Genstate = new QProgressBar(tab_TimeSecCht);
        progressBar_TimeSecCht_Genstate->setObjectName(QString::fromUtf8("progressBar_TimeSecCht_Genstate"));
        progressBar_TimeSecCht_Genstate->setValue(0);

        horizontalLayout_52->addWidget(progressBar_TimeSecCht_Genstate);


        verticalLayout_16->addLayout(horizontalLayout_52);

        btn_updateTimeSecCht = new QPushButton(tab_TimeSecCht);
        btn_updateTimeSecCht->setObjectName(QString::fromUtf8("btn_updateTimeSecCht"));

        verticalLayout_16->addWidget(btn_updateTimeSecCht);

        verticalSpacer_8 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_8);

        tabWidget_BDSNR_Panel->addTab(tab_TimeSecCht, QString());

        horizontalLayout_27->addWidget(tabWidget_BDSNR_Panel);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(6);
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        horizontalLayout_53->setContentsMargins(-1, -1, 12, -1);
        groupBox_18 = new QGroupBox(BandWidthSNRSelWgtClass);
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
        labe_HSliderTime = new QLabel(groupBox_18);
        labe_HSliderTime->setObjectName(QString::fromUtf8("labe_HSliderTime"));

        horizontalLayout_54->addWidget(labe_HSliderTime);

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

        groupBox_19 = new QGroupBox(BandWidthSNRSelWgtClass);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        groupBox_19->setMinimumSize(QSize(280, 0));
        groupBox_19->setMaximumSize(QSize(280, 16777215));
        verticalLayout_20 = new QVBoxLayout(groupBox_19);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_TimeSecCht_Frame_CenterTime = new QLabel(groupBox_19);
        label_TimeSecCht_Frame_CenterTime->setObjectName(QString::fromUtf8("label_TimeSecCht_Frame_CenterTime"));

        verticalLayout_20->addWidget(label_TimeSecCht_Frame_CenterTime);

        label_TimeSecCht_Avr_SecFrameRate = new QLabel(groupBox_19);
        label_TimeSecCht_Avr_SecFrameRate->setObjectName(QString::fromUtf8("label_TimeSecCht_Avr_SecFrameRate"));

        verticalLayout_20->addWidget(label_TimeSecCht_Avr_SecFrameRate);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_9);


        horizontalLayout_53->addWidget(groupBox_19);


        verticalLayout->addLayout(horizontalLayout_53);


        retranslateUi(BandWidthSNRSelWgtClass);

        tabWidget_Filter->setCurrentIndex(0);
        tabWidget_BDSNR_Panel->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(BandWidthSNRSelWgtClass);
    } // setupUi

    void retranslateUi(QWidget *BandWidthSNRSelWgtClass)
    {
        BandWidthSNRSelWgtClass->setWindowTitle(QApplication::translate("BandWidthSNRSelWgtClass", "BandWidthSNRSelWgt", nullptr));
        groupBox->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\345\270\246\345\256\275\346\273\244\346\263\242\345\231\250", nullptr));
        groupBox_2->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\347\224\237\346\210\220\346\216\247\345\210\266", nullptr));
        label_chtStartFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\233\276\350\241\250\346\230\276\347\244\272\345\210\235\345\247\213\351\242\221\347\216\207", nullptr));
        label_chtEndFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\233\276\350\241\250\346\230\276\347\244\272\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        btn_updateBandWidthFilterCht->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\344\273\205\345\210\267\346\226\260\345\233\276\350\241\250\350\214\203\345\233\264", nullptr));
        label_EqualWidthAreaMaxFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\255\211\351\227\264\350\267\235\345\214\272\345\237\237\346\234\200\345\244\247\351\242\221\347\216\207", nullptr));
        label_EqualWidthAreaFilterCount->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\255\211\351\227\264\350\267\235\345\214\272\345\237\237\346\273\244\346\263\242\345\231\250\346\225\260\351\207\217", nullptr));
        label_LogAreaFilterCount->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\257\271\346\225\260\345\242\236\345\256\275\345\214\272\345\237\237\346\273\244\346\263\242\345\231\250\346\225\260\351\207\217", nullptr));
        label_STFTSampleRate->setText(QApplication::translate("BandWidthSNRSelWgtClass", "STFT\351\207\207\346\240\267\347\216\207", nullptr));
        label_STFTWndPtCount->setText(QApplication::translate("BandWidthSNRSelWgtClass", "STFT\347\252\227\345\217\243\347\202\271\346\225\260", nullptr));
        label_EqualWidthAreaFilterWidth->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\255\211\351\227\264\350\267\235\345\214\272\345\237\237\346\273\244\346\263\242\345\231\250\345\270\246\345\256\275", nullptr));
        label_totalFilterCount->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\205\250\345\261\200\346\273\244\346\263\242\345\231\250\346\225\260\351\207\217", nullptr));
        btn_GenFilterAndUpdateCht->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\224\237\346\210\220\345\271\266\345\210\267\346\226\260", nullptr));
        tabWidget_Filter->setTabText(tabWidget_Filter->indexOf(tab_BandWidthFilter), QApplication::translate("BandWidthSNRSelWgtClass", "\345\270\246\345\256\275\346\273\244\346\263\242\345\231\250", nullptr));
        groupBox_HotCht->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\225\264\344\275\223\347\273\223\346\236\234", nullptr));
        groupBox_HotChtPanel->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\347\203\255\345\212\233\345\233\276\346\216\247\345\210\266", nullptr));
        label_STFTFileName->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\226\207\344\273\266\345\220\215\347\247\260", nullptr));
        label_dataDuration->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\225\260\346\215\256\346\214\201\347\273\255\346\227\266\351\227\264", nullptr));
        label_STFTState->setText(QApplication::translate("BandWidthSNRSelWgtClass", "STFT\345\217\202\346\225\260\357\274\232", nullptr));
        label_hotChtStartTime->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeEdit_hotChtStartTime->setDisplayFormat(QApplication::translate("BandWidthSNRSelWgtClass", "mm:ss", nullptr));
        label_hotChtTimeLength->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\252\227\345\217\243\351\225\277\345\272\246", nullptr));
        label_hotCht_startFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_hotCht_endFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_8->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\351\242\234\350\211\262\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_ADSR_HotCht_StartDB->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_ADSR_HotCht_endDB->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_HotCht_FreqBandWidth->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\351\242\221\347\216\207\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_HotCht_TimeIntervalMsec->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\227\266\351\227\264\345\270\246\345\256\275\357\274\210ms\357\274\211", nullptr));
        label_HotChtGenState->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateHotCht->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\210\267\346\226\260", nullptr));
        tabWidget_Filter->setTabText(tabWidget_Filter->indexOf(tab_hotCht), QApplication::translate("BandWidthSNRSelWgtClass", "HotCht", nullptr));
        groupBox_11->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_BDMaxValType->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\212\221\345\210\266\345\200\274\346\235\245\346\272\220", nullptr));
        radioButton_BDMaxVal_Max->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\270\246\345\256\275\345\206\205\346\234\200\345\200\274", nullptr));
        radioButton_BDMaxVal_WeightMax->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\270\246\345\256\275\345\206\205\345\212\240\346\235\203\346\234\200\345\200\274", nullptr));
        label_FilterValDecreaseRatio_MainArea->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\344\270\273\345\257\271\350\261\241\345\214\272\350\241\260\345\207\217\345\271\205\345\272\246\357\274\210%\357\274\211", nullptr));
        label_FilterValDecrease_DB_MainArea->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\344\270\273\345\257\271\350\261\241\345\214\272\347\255\211\344\273\267\345\223\215\345\272\246\350\241\260\345\207\217\357\274\232", nullptr));
        label_FilterValDecreaseRatio_SubArea->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\254\241\345\257\271\350\261\241\345\214\272\350\241\260\345\207\217\345\271\205\345\272\246\357\274\210%\357\274\211", nullptr));
        label_FilterValDecrease_DB_SubArea->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\254\241\345\257\271\350\261\241\345\214\272\347\255\211\344\273\267\345\223\215\345\272\246\350\241\260\345\207\217\357\274\232", nullptr));
        groupBox_FilterCond->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\344\270\273\345\214\272\345\237\237\346\273\244\346\263\242\346\226\271\346\241\210", nullptr));
        radioButton_FilterCond_MainArea_Strong->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\272\346\273\244\346\263\242", nullptr));
        radioButton_FilterCond_MainArea_Weak->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\261\346\273\244\346\263\242", nullptr));
        radioButton_FilterCond_MainArea_Weight->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\212\240\346\235\203\346\273\244\346\263\242", nullptr));
        groupBox_FilterCond_2->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\254\241\345\214\272\345\237\237\346\273\244\346\263\242\346\226\271\346\241\210", nullptr));
        radioButton_FilterCond_SubArea_Strong->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\272\346\273\244\346\263\242", nullptr));
        radioButton_FilterCond_SubArea_Weak->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\261\346\273\244\346\263\242", nullptr));
        radioButton_FilterCond_SubArea_Weight->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\212\240\346\235\203\346\273\244\346\263\242", nullptr));
        groupBox_3->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\347\224\237\346\210\220\347\273\223\346\235\237\345\220\216\346\223\215\344\275\234", nullptr));
        radioButton_getBDSNRData_GoTimeSecCht->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\210\267\346\226\260\345\233\276\350\241\250", nullptr));
        radioButton_getBDSNRData_GoEffSigBuff->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\350\241\224\346\216\245\346\234\211\346\225\210\344\277\241\345\217\267\347\274\223\345\206\262", nullptr));
        label_BDSNR_GenState->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\224\237\346\210\220\347\212\266\346\200\201\357\274\232", nullptr));
        btn_GenBDSNRResult->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\200\345\247\213\347\224\237\346\210\220\346\212\221\345\210\266\347\273\223\346\236\234", nullptr));
        tabWidget_BDSNR_Panel->setTabText(tabWidget_BDSNR_Panel->indexOf(tab_SNRConstrainCond), QApplication::translate("BandWidthSNRSelWgtClass", "\346\212\221\345\210\266\346\235\241\344\273\266", nullptr));
        groupBox_HAxisRange->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\250\252\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210hz\357\274\211", nullptr));
        label_OscSep_TimeSec_startFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_OscSep_TimeSec_endFreq->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_15->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\347\272\265\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_OscSep_TimeSec_StartDB->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_OscSep_TimeSec_endDB->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        groupBox_16->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        radioButton_TimeSecCht_STFT->setText(QApplication::translate("BandWidthSNRSelWgtClass", "STFT", nullptr));
        radioButton_TimeSecCht_WndSepcConstrain->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\234\211\346\225\210\351\234\207\350\215\241", nullptr));
        radioButton_TimeSecHct_BDSNR->setText(QApplication::translate("BandWidthSNRSelWgtClass", "SNR\346\212\221\345\210\266", nullptr));
        groupBox_17->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\345\231\252\345\243\260\347\273\230\345\210\266", nullptr));
        checkBox_TimeSecCht_drawTIQLine->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\220\254\350\247\211\351\230\210\345\200\274\346\233\262\347\272\277", nullptr));
        checkBox_TimeSecCht_drawUnderTIQBar->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\260\217\344\272\216\345\220\254\351\230\210\350\276\223\345\205\245", nullptr));
        checkBox_TimeSecCht_drawWndSpecNoise->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\347\252\227\350\260\261\346\212\221\345\210\266\345\231\252\345\243\260", nullptr));
        checkBox_TimeSecCht_drawBDSNRNoisePt->setText(QApplication::translate("BandWidthSNRSelWgtClass", "BDSNR\345\231\252\345\243\260", nullptr));
        checkBox_TimeSecCht_drawBDSNR_ConstrainPt->setText(QApplication::translate("BandWidthSNRSelWgtClass", "BDSNR\346\212\221\345\210\266\345\200\274", nullptr));
        checkBox_TimeSecCht_drawBDSNR_SubPt->setText(QApplication::translate("BandWidthSNRSelWgtClass", "BDSNR\346\254\241\345\214\272\345\237\237\345\200\274", nullptr));
        checkBox_TimeSecCht_drawBDSNR_Filter->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\273\244\346\263\242\345\231\250\345\200\274", nullptr));
        checkBox_TimeSecCht_drawBDSNR_FilterMain->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\273\244\346\263\242\345\231\250\344\270\273\345\200\274", nullptr));
        label_TimeSecCht_UpdateTimer->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\270\247\345\210\267\346\226\260\351\227\264\351\232\224(ms)", nullptr));
        label_TimeSecGenState->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateTimeSecCht->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\210\267\346\226\260\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276", nullptr));
        tabWidget_BDSNR_Panel->setTabText(tabWidget_BDSNR_Panel->indexOf(tab_TimeSecCht), QApplication::translate("BandWidthSNRSelWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_18->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\227\266\351\227\264\346\216\247\345\210\266", nullptr));
        labe_HSliderTime->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\210\252\351\235\242\346\227\266\351\227\264\357\274\23200\357\274\23200.000", nullptr));
        btn_lastFrame->setText(QApplication::translate("BandWidthSNRSelWgtClass", "<", nullptr));
        btn_nextFrame->setText(QApplication::translate("BandWidthSNRSelWgtClass", ">", nullptr));
        btn_play->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\222\255\346\224\276", nullptr));
        btn_stop->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\201\234\346\255\242", nullptr));
        btn_jump->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\350\267\263\350\275\254", nullptr));
        groupBox_19->setTitle(QApplication::translate("BandWidthSNRSelWgtClass", "\346\227\266\351\227\264\347\225\214\351\235\242\345\270\247\344\277\241\346\201\257", nullptr));
        label_TimeSecCht_Frame_CenterTime->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\346\210\252\351\235\242\346\227\266\351\227\264", nullptr));
        label_TimeSecCht_Avr_SecFrameRate->setText(QApplication::translate("BandWidthSNRSelWgtClass", "\345\271\263\345\235\207\345\270\247\347\216\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BandWidthSNRSelWgtClass: public Ui_BandWidthSNRSelWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANDWIDTHSNRSELWGT_H
