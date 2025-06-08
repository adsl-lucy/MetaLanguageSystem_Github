/********************************************************************************
** Form generated from reading UI file 'BandWidthInputWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANDWIDTHINPUTWGT_H
#define UI_BANDWIDTHINPUTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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

class Ui_BandWidthInputWgtClass
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QWidget *tab_2;
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
    QTabWidget *tabWidget_DiffNetPannel;
    QWidget *tab_FreqDoubNetPara;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_getData;
    QHBoxLayout *horizontalLayout_17;
    QRadioButton *radioButton_getData_GoTimeSecCht;
    QLabel *label_BandWidthInputNet_GenState;
    QProgressBar *progressBar_BandWidthInputNet_GenResult;
    QPushButton *btn_BandWidthInputNet_GenResult;
    QSpacerItem *verticalSpacer;
    QWidget *tab_TimeSecCht;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_HAxisRange;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_OscSep_TimeSec_startFreq;
    QSpinBox *SBox_OscSep_TimeSec_startFreq;
    QLabel *label_OscSep_TimeSec_endFreq;
    QSpinBox *SBox_OscSep_TimeSec_endFreq;
    QGroupBox *groupBox_15;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_Diff_TimeSec_StartDB;
    QSpinBox *SBox_Diff_TimeSec_StartDB;
    QLabel *label_Diff_TimeSec_endDB;
    QSpinBox *SBox_Diff_TimeSec_EndDB;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_Diff_UpdateTimer;
    QSpinBox *SBox_Diff_UpdateTimer;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_TimeSecChtBarType;
    QGroupBox *groupBox_20;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_49;
    QCheckBox *checkBox_TimeSecCht_drawTIQLine;
    QCheckBox *checkBox_TimeSecCht_drawUnderTIQBar;
    QHBoxLayout *horizontalLayout_50;
    QCheckBox *checkBox_TimeSecCht_drawWndSpecNoise;
    QCheckBox *checkBox_TimeSecCht_drawBDSNRNoisePt;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_TimeSecCht_drawBDSNRConstrainPt;
    QCheckBox *checkBox_TimeSecCht_drawBDSNRActiveFilter;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_TimeSecCht_drawFreqDoubChild;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
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

    void setupUi(QWidget *BandWidthInputWgtClass)
    {
        if (BandWidthInputWgtClass->objectName().isEmpty())
            BandWidthInputWgtClass->setObjectName(QString::fromUtf8("BandWidthInputWgtClass"));
        BandWidthInputWgtClass->resize(1128, 868);
        verticalLayout_3 = new QVBoxLayout(BandWidthInputWgtClass);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget_2 = new QTabWidget(BandWidthInputWgtClass);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        groupBox_HotCht = new QGroupBox(tab_2);
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

        groupBox_HotChtPanel = new QGroupBox(tab_2);
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
        groupBox_TimeSecCht = new QGroupBox(tab_2);
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

        tabWidget_DiffNetPannel = new QTabWidget(tab_2);
        tabWidget_DiffNetPannel->setObjectName(QString::fromUtf8("tabWidget_DiffNetPannel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget_DiffNetPannel->sizePolicy().hasHeightForWidth());
        tabWidget_DiffNetPannel->setSizePolicy(sizePolicy2);
        tabWidget_DiffNetPannel->setMaximumSize(QSize(280, 16777215));
        tab_FreqDoubNetPara = new QWidget();
        tab_FreqDoubNetPara->setObjectName(QString::fromUtf8("tab_FreqDoubNetPara"));
        verticalLayout_2 = new QVBoxLayout(tab_FreqDoubNetPara);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
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

        label_BandWidthInputNet_GenState = new QLabel(tab_FreqDoubNetPara);
        label_BandWidthInputNet_GenState->setObjectName(QString::fromUtf8("label_BandWidthInputNet_GenState"));

        verticalLayout_2->addWidget(label_BandWidthInputNet_GenState);

        progressBar_BandWidthInputNet_GenResult = new QProgressBar(tab_FreqDoubNetPara);
        progressBar_BandWidthInputNet_GenResult->setObjectName(QString::fromUtf8("progressBar_BandWidthInputNet_GenResult"));
        progressBar_BandWidthInputNet_GenResult->setValue(0);

        verticalLayout_2->addWidget(progressBar_BandWidthInputNet_GenResult);

        btn_BandWidthInputNet_GenResult = new QPushButton(tab_FreqDoubNetPara);
        btn_BandWidthInputNet_GenResult->setObjectName(QString::fromUtf8("btn_BandWidthInputNet_GenResult"));

        verticalLayout_2->addWidget(btn_BandWidthInputNet_GenResult);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget_DiffNetPannel->addTab(tab_FreqDoubNetPara, QString());
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


        verticalLayout_5->addWidget(groupBox_HAxisRange);

        groupBox_15 = new QGroupBox(tab_3);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        horizontalLayout_45 = new QHBoxLayout(groupBox_15);
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_Diff_TimeSec_StartDB = new QLabel(groupBox_15);
        label_Diff_TimeSec_StartDB->setObjectName(QString::fromUtf8("label_Diff_TimeSec_StartDB"));

        horizontalLayout_45->addWidget(label_Diff_TimeSec_StartDB);

        SBox_Diff_TimeSec_StartDB = new QSpinBox(groupBox_15);
        SBox_Diff_TimeSec_StartDB->setObjectName(QString::fromUtf8("SBox_Diff_TimeSec_StartDB"));
        SBox_Diff_TimeSec_StartDB->setMinimum(0);
        SBox_Diff_TimeSec_StartDB->setValue(0);

        horizontalLayout_45->addWidget(SBox_Diff_TimeSec_StartDB);

        label_Diff_TimeSec_endDB = new QLabel(groupBox_15);
        label_Diff_TimeSec_endDB->setObjectName(QString::fromUtf8("label_Diff_TimeSec_endDB"));

        horizontalLayout_45->addWidget(label_Diff_TimeSec_endDB);

        SBox_Diff_TimeSec_EndDB = new QSpinBox(groupBox_15);
        SBox_Diff_TimeSec_EndDB->setObjectName(QString::fromUtf8("SBox_Diff_TimeSec_EndDB"));
        SBox_Diff_TimeSec_EndDB->setValue(80);

        horizontalLayout_45->addWidget(SBox_Diff_TimeSec_EndDB);


        verticalLayout_5->addWidget(groupBox_15);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        label_Diff_UpdateTimer = new QLabel(tab_3);
        label_Diff_UpdateTimer->setObjectName(QString::fromUtf8("label_Diff_UpdateTimer"));

        horizontalLayout_47->addWidget(label_Diff_UpdateTimer);

        SBox_Diff_UpdateTimer = new QSpinBox(tab_3);
        SBox_Diff_UpdateTimer->setObjectName(QString::fromUtf8("SBox_Diff_UpdateTimer"));
        SBox_Diff_UpdateTimer->setMinimum(1);
        SBox_Diff_UpdateTimer->setMaximum(200);
        SBox_Diff_UpdateTimer->setValue(20);

        horizontalLayout_47->addWidget(SBox_Diff_UpdateTimer);


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
        comboBox_TimeSecChtBarType->addItem(QString());
        comboBox_TimeSecChtBarType->setObjectName(QString::fromUtf8("comboBox_TimeSecChtBarType"));

        horizontalLayout->addWidget(comboBox_TimeSecChtBarType);


        verticalLayout_7->addLayout(horizontalLayout);

        groupBox_20 = new QGroupBox(tab_4);
        groupBox_20->setObjectName(QString::fromUtf8("groupBox_20"));
        groupBox_20->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(groupBox_20);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        checkBox_TimeSecCht_drawTIQLine = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawTIQLine->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawTIQLine"));
        checkBox_TimeSecCht_drawTIQLine->setMinimumSize(QSize(100, 0));
        checkBox_TimeSecCht_drawTIQLine->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_drawTIQLine->setChecked(false);

        horizontalLayout_49->addWidget(checkBox_TimeSecCht_drawTIQLine);

        checkBox_TimeSecCht_drawUnderTIQBar = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawUnderTIQBar->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawUnderTIQBar"));
        checkBox_TimeSecCht_drawUnderTIQBar->setChecked(false);

        horizontalLayout_49->addWidget(checkBox_TimeSecCht_drawUnderTIQBar);


        verticalLayout_4->addLayout(horizontalLayout_49);

        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        checkBox_TimeSecCht_drawWndSpecNoise = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawWndSpecNoise->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawWndSpecNoise"));
        checkBox_TimeSecCht_drawWndSpecNoise->setMinimumSize(QSize(100, 0));
        checkBox_TimeSecCht_drawWndSpecNoise->setMaximumSize(QSize(100, 16777215));
        checkBox_TimeSecCht_drawWndSpecNoise->setChecked(false);

        horizontalLayout_50->addWidget(checkBox_TimeSecCht_drawWndSpecNoise);

        checkBox_TimeSecCht_drawBDSNRNoisePt = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawBDSNRNoisePt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNRNoisePt"));

        horizontalLayout_50->addWidget(checkBox_TimeSecCht_drawBDSNRNoisePt);


        verticalLayout_4->addLayout(horizontalLayout_50);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        checkBox_TimeSecCht_drawBDSNRConstrainPt = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawBDSNRConstrainPt->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNRConstrainPt"));
        checkBox_TimeSecCht_drawBDSNRConstrainPt->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_15->addWidget(checkBox_TimeSecCht_drawBDSNRConstrainPt);

        checkBox_TimeSecCht_drawBDSNRActiveFilter = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawBDSNRActiveFilter->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawBDSNRActiveFilter"));

        horizontalLayout_15->addWidget(checkBox_TimeSecCht_drawBDSNRActiveFilter);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox_TimeSecCht_drawFreqDoubChild = new QCheckBox(groupBox_20);
        checkBox_TimeSecCht_drawFreqDoubChild->setObjectName(QString::fromUtf8("checkBox_TimeSecCht_drawFreqDoubChild"));
        checkBox_TimeSecCht_drawFreqDoubChild->setChecked(true);

        horizontalLayout_2->addWidget(checkBox_TimeSecCht_drawFreqDoubChild);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        verticalLayout_7->addWidget(groupBox_20);

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

        tabWidget_DiffNetPannel->addTab(tab_TimeSecCht, QString());

        horizontalLayout_27->addWidget(tabWidget_DiffNetPannel);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(6);
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        horizontalLayout_53->setSizeConstraint(QLayout::SetDefaultConstraint);
        groupBox_18 = new QGroupBox(tab_2);
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

        groupBox_19 = new QGroupBox(tab_2);
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

        tabWidget_2->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget_2);


        retranslateUi(BandWidthInputWgtClass);

        tabWidget_2->setCurrentIndex(1);
        tabWidget_DiffNetPannel->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);
        comboBox_TimeSecChtBarType->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(BandWidthInputWgtClass);
    } // setupUi

    void retranslateUi(QWidget *BandWidthInputWgtClass)
    {
        BandWidthInputWgtClass->setWindowTitle(QApplication::translate("BandWidthInputWgtClass", "BandWidthInputWgt", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QApplication::translate("BandWidthInputWgtClass", "Tab 1", nullptr));
        groupBox_HotCht->setTitle(QApplication::translate("BandWidthInputWgtClass", "\346\225\264\344\275\223\347\273\223\346\236\234", nullptr));
        groupBox_HotChtPanel->setTitle(QApplication::translate("BandWidthInputWgtClass", "\347\203\255\345\212\233\345\233\276\346\216\247\345\210\266", nullptr));
        label_STFTFileName->setText(QApplication::translate("BandWidthInputWgtClass", "\346\226\207\344\273\266\345\220\215\347\247\260", nullptr));
        label_dataDuration->setText(QApplication::translate("BandWidthInputWgtClass", "\346\225\260\346\215\256\346\214\201\347\273\255\346\227\266\351\227\264", nullptr));
        label_STFTState->setText(QApplication::translate("BandWidthInputWgtClass", "STFT\345\217\202\346\225\260\357\274\232", nullptr));
        label_hotChtStartTime->setText(QApplication::translate("BandWidthInputWgtClass", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeEdit_hotChtStartTime->setDisplayFormat(QApplication::translate("BandWidthInputWgtClass", "mm:ss", nullptr));
        label_hotChtTimeLength->setText(QApplication::translate("BandWidthInputWgtClass", "\347\252\227\345\217\243\351\225\277\345\272\246", nullptr));
        label_hotCht_startFreq->setText(QApplication::translate("BandWidthInputWgtClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_hotCht_endFreq->setText(QApplication::translate("BandWidthInputWgtClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_8->setTitle(QApplication::translate("BandWidthInputWgtClass", "\351\242\234\350\211\262\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_HotCht_StartDB->setText(QApplication::translate("BandWidthInputWgtClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_HotCht_endDB->setText(QApplication::translate("BandWidthInputWgtClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_HotChtFreqBandWidth->setText(QApplication::translate("BandWidthInputWgtClass", "\351\242\221\347\216\207\345\270\246\345\256\275\357\274\210hz\357\274\211", nullptr));
        label_HotChtTimeIntervalMsec->setText(QApplication::translate("BandWidthInputWgtClass", "\346\227\266\351\227\264\345\270\246\345\256\275\357\274\210ms\357\274\211", nullptr));
        label_HotChtGenState->setText(QApplication::translate("BandWidthInputWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateHotCht->setText(QApplication::translate("BandWidthInputWgtClass", "\345\210\267\346\226\260", nullptr));
        groupBox_TimeSecCht->setTitle(QApplication::translate("BandWidthInputWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_getData->setTitle(QApplication::translate("BandWidthInputWgtClass", "\347\224\237\346\210\220\345\220\216\350\241\224\346\216\245", nullptr));
        radioButton_getData_GoTimeSecCht->setText(QApplication::translate("BandWidthInputWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276", nullptr));
        label_BandWidthInputNet_GenState->setText(QApplication::translate("BandWidthInputWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201\357\274\232", nullptr));
        btn_BandWidthInputNet_GenResult->setText(QApplication::translate("BandWidthInputWgtClass", "\347\224\237\346\210\220\347\273\223\346\236\234", nullptr));
        tabWidget_DiffNetPannel->setTabText(tabWidget_DiffNetPannel->indexOf(tab_FreqDoubNetPara), QApplication::translate("BandWidthInputWgtClass", "\345\200\215\351\242\221\347\275\221\347\273\234\346\277\200\346\264\273", nullptr));
        groupBox_HAxisRange->setTitle(QApplication::translate("BandWidthInputWgtClass", "\346\250\252\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210hz\357\274\211", nullptr));
        label_OscSep_TimeSec_startFreq->setText(QApplication::translate("BandWidthInputWgtClass", "\345\274\200\345\247\213\351\242\221\347\216\207", nullptr));
        label_OscSep_TimeSec_endFreq->setText(QApplication::translate("BandWidthInputWgtClass", "\347\273\223\346\235\237\351\242\221\347\216\207", nullptr));
        groupBox_15->setTitle(QApplication::translate("BandWidthInputWgtClass", "\347\272\265\345\235\220\346\240\207\350\214\203\345\233\264\357\274\210db\357\274\211", nullptr));
        label_Diff_TimeSec_StartDB->setText(QApplication::translate("BandWidthInputWgtClass", "\346\234\200\345\260\217\345\271\205\345\200\274", nullptr));
        label_Diff_TimeSec_endDB->setText(QApplication::translate("BandWidthInputWgtClass", "\346\234\200\345\244\247\345\271\205\345\200\274", nullptr));
        label_Diff_UpdateTimer->setText(QApplication::translate("BandWidthInputWgtClass", "\345\270\247\345\210\267\346\226\260\351\227\264\351\232\224(ms)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("BandWidthInputWgtClass", "\345\235\220\346\240\207\347\263\273", nullptr));
        label->setText(QApplication::translate("BandWidthInputWgtClass", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        comboBox_TimeSecChtBarType->setItemText(0, QApplication::translate("BandWidthInputWgtClass", "STFT", nullptr));
        comboBox_TimeSecChtBarType->setItemText(1, QApplication::translate("BandWidthInputWgtClass", "EffOsc", nullptr));
        comboBox_TimeSecChtBarType->setItemText(2, QApplication::translate("BandWidthInputWgtClass", "BDSNR", nullptr));
        comboBox_TimeSecChtBarType->setItemText(3, QApplication::translate("BandWidthInputWgtClass", "Diff", nullptr));
        comboBox_TimeSecChtBarType->setItemText(4, QApplication::translate("BandWidthInputWgtClass", "FreqDoub", nullptr));

        groupBox_20->setTitle(QApplication::translate("BandWidthInputWgtClass", "\345\231\252\345\243\260\347\273\230\345\210\266", nullptr));
        checkBox_TimeSecCht_drawTIQLine->setText(QApplication::translate("BandWidthInputWgtClass", "\345\220\254\350\247\211\351\230\210\345\200\274\346\233\262\347\272\277", nullptr));
        checkBox_TimeSecCht_drawUnderTIQBar->setText(QApplication::translate("BandWidthInputWgtClass", "\345\260\217\344\272\216\345\220\254\351\230\210\350\276\223\345\205\245", nullptr));
        checkBox_TimeSecCht_drawWndSpecNoise->setText(QApplication::translate("BandWidthInputWgtClass", "\347\252\227\350\260\261\346\212\221\345\210\266\345\231\252\345\243\260", nullptr));
        checkBox_TimeSecCht_drawBDSNRNoisePt->setText(QApplication::translate("BandWidthInputWgtClass", "BDSNR\345\231\252\345\243\260", nullptr));
        checkBox_TimeSecCht_drawBDSNRConstrainPt->setText(QApplication::translate("BandWidthInputWgtClass", "BDSNR\346\212\221\345\210\266\345\200\274", nullptr));
        checkBox_TimeSecCht_drawBDSNRActiveFilter->setText(QApplication::translate("BandWidthInputWgtClass", "BDSNR\346\277\200\346\264\273\346\273\244\346\263\242\345\231\250", nullptr));
        checkBox_TimeSecCht_drawFreqDoubChild->setText(QApplication::translate("BandWidthInputWgtClass", "\345\200\215\351\242\221\345\255\220\351\242\221", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("BandWidthInputWgtClass", "\345\206\205\345\256\271", nullptr));
        label_TimeSecGenState->setText(QApplication::translate("BandWidthInputWgtClass", "\345\210\267\346\226\260\347\212\266\346\200\201:", nullptr));
        btn_updateTimeSecCht->setText(QApplication::translate("BandWidthInputWgtClass", "\345\210\267\346\226\260\346\227\266\351\227\264\346\210\252\351\235\242\345\233\276", nullptr));
        tabWidget_DiffNetPannel->setTabText(tabWidget_DiffNetPannel->indexOf(tab_TimeSecCht), QApplication::translate("BandWidthInputWgtClass", "\346\227\266\351\227\264\346\210\252\351\235\242", nullptr));
        groupBox_18->setTitle(QApplication::translate("BandWidthInputWgtClass", "\346\227\266\351\227\264\346\216\247\345\210\266", nullptr));
        label_TimeFrameTime->setText(QApplication::translate("BandWidthInputWgtClass", "\346\210\252\351\235\242\346\227\266\351\227\264\357\274\23200\357\274\23200.000", nullptr));
        btn_lastFrame->setText(QApplication::translate("BandWidthInputWgtClass", "<", nullptr));
        btn_nextFrame->setText(QApplication::translate("BandWidthInputWgtClass", ">", nullptr));
        btn_play->setText(QApplication::translate("BandWidthInputWgtClass", "\346\222\255\346\224\276", nullptr));
        btn_stop->setText(QApplication::translate("BandWidthInputWgtClass", "\345\201\234\346\255\242", nullptr));
        btn_jump->setText(QApplication::translate("BandWidthInputWgtClass", "\350\267\263\350\275\254", nullptr));
        groupBox_19->setTitle(QApplication::translate("BandWidthInputWgtClass", "\346\227\266\351\227\264\347\225\214\351\235\242\345\270\247\344\277\241\346\201\257", nullptr));
        label_TimeSecCht_FrameCenterTime->setText(QApplication::translate("BandWidthInputWgtClass", "\346\210\252\351\235\242\346\227\266\351\227\264", nullptr));
        label_TimeSecCht_AvrSecFrameRate->setText(QApplication::translate("BandWidthInputWgtClass", "\345\271\263\345\235\207\345\270\247\347\216\207", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QApplication::translate("BandWidthInputWgtClass", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BandWidthInputWgtClass: public Ui_BandWidthInputWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANDWIDTHINPUTWGT_H
