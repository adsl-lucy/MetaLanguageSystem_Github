/********************************************************************************
** Form generated from reading UI file 'FFTTestWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFTTESTWGT_H
#define UI_FFTTESTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FFTTestWgtClass
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_baseSig_chart;
    QHBoxLayout *HLayout_baseSig_chart;
    QGroupBox *groupBox_baseSig_panel;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_baseSig_Freq;
    QDoubleSpinBox *dSBox_baseSig_Freq;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_baseSig_StartT;
    QDoubleSpinBox *dSBox_baseSig_StartT;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_baseSig_TimeLength;
    QDoubleSpinBox *dSBox_baseSig_TimeLength;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_baseSig_Amp;
    QDoubleSpinBox *dSBox_baseSig_Amp;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_baseSig_SampleRate;
    QSpinBox *dSBos_baseSig_SampleRate;
    QPushButton *btn_drawBaseSignal;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_modSig_chart;
    QHBoxLayout *HLayout_modSig_chart;
    QGroupBox *groupBox_modSig_panel;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_modSig_Freq;
    QDoubleSpinBox *dSBox_modSig_Freq;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_modSig_StartT;
    QDoubleSpinBox *dSBox_modSig_StartT;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_modSig_TimeLength;
    QDoubleSpinBox *dSBox_modSig_TimeLength;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_modSig_Depth;
    QDoubleSpinBox *dSBox_modSig_Depth;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_modSig_SampleRate;
    QSpinBox *dSBos_modSig_SampleRate;
    QGroupBox *groupBox_modSig_Type;
    QHBoxLayout *horizontalLayout_15;
    QRadioButton *radioButton_modSig_Type_sin;
    QRadioButton *radioButton_modSig_Type_square;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_modSig_DrawContent;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *checkBox_modSig_drawModSig;
    QCheckBox *checkBox_modSig_drawSigAfterMod;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_drawmodSig;
    QPushButton *btn_saveModResultToDCenter;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_20;
    QGroupBox *groupBox_FFT_chart;
    QHBoxLayout *HLayout_FFT_Chart;
    QGroupBox *groupBox_FFT_panel;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_FFTFrom;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_FFTFrom_zhihu;
    QRadioButton *radioButton_FFTFrom_FFTW;
    QRadioButton *radioButton_FFTFrom_cudaFFt;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_FFTStartTime;
    QDoubleSpinBox *dSBox_FFTstartTime;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_FFTinputPointInPowerOf2;
    QDoubleSpinBox *dSBox_FFTInputPointInPowerOf2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_FFTSampleRate;
    QDoubleSpinBox *dSBox_FFTSampleRate;
    QPushButton *btn_drawFFTResult;
    QPushButton *btn_drawIFFT;
    QLabel *label_FFTInputPointCount;
    QLabel *label_FFTWindowLength;
    QLabel *label_FFTFreqDelta;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *FFTTestWgtClass)
    {
        if (FFTTestWgtClass->objectName().isEmpty())
            FFTTestWgtClass->setObjectName(QString::fromUtf8("FFTTestWgtClass"));
        FFTTestWgtClass->resize(1256, 901);
        verticalLayout_6 = new QVBoxLayout(FFTTestWgtClass);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        groupBox_baseSig_chart = new QGroupBox(FFTTestWgtClass);
        groupBox_baseSig_chart->setObjectName(QString::fromUtf8("groupBox_baseSig_chart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_baseSig_chart->sizePolicy().hasHeightForWidth());
        groupBox_baseSig_chart->setSizePolicy(sizePolicy);
        groupBox_baseSig_chart->setMinimumSize(QSize(1000, 250));
        groupBox_baseSig_chart->setMaximumSize(QSize(1980, 440));
        HLayout_baseSig_chart = new QHBoxLayout(groupBox_baseSig_chart);
        HLayout_baseSig_chart->setSpacing(6);
        HLayout_baseSig_chart->setContentsMargins(11, 11, 11, 11);
        HLayout_baseSig_chart->setObjectName(QString::fromUtf8("HLayout_baseSig_chart"));

        horizontalLayout_7->addWidget(groupBox_baseSig_chart);

        groupBox_baseSig_panel = new QGroupBox(FFTTestWgtClass);
        groupBox_baseSig_panel->setObjectName(QString::fromUtf8("groupBox_baseSig_panel"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_baseSig_panel->sizePolicy().hasHeightForWidth());
        groupBox_baseSig_panel->setSizePolicy(sizePolicy1);
        groupBox_baseSig_panel->setMinimumSize(QSize(230, 250));
        groupBox_baseSig_panel->setMaximumSize(QSize(16777215, 440));
        verticalLayout_2 = new QVBoxLayout(groupBox_baseSig_panel);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_baseSig_Freq = new QLabel(groupBox_baseSig_panel);
        label_baseSig_Freq->setObjectName(QString::fromUtf8("label_baseSig_Freq"));

        horizontalLayout->addWidget(label_baseSig_Freq);

        dSBox_baseSig_Freq = new QDoubleSpinBox(groupBox_baseSig_panel);
        dSBox_baseSig_Freq->setObjectName(QString::fromUtf8("dSBox_baseSig_Freq"));
        dSBox_baseSig_Freq->setMinimum(20.000000000000000);
        dSBox_baseSig_Freq->setMaximum(200000.000000000000000);
        dSBox_baseSig_Freq->setValue(969.299999999999955);

        horizontalLayout->addWidget(dSBox_baseSig_Freq);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_baseSig_StartT = new QLabel(groupBox_baseSig_panel);
        label_baseSig_StartT->setObjectName(QString::fromUtf8("label_baseSig_StartT"));

        horizontalLayout_2->addWidget(label_baseSig_StartT);

        dSBox_baseSig_StartT = new QDoubleSpinBox(groupBox_baseSig_panel);
        dSBox_baseSig_StartT->setObjectName(QString::fromUtf8("dSBox_baseSig_StartT"));
        dSBox_baseSig_StartT->setMaximum(5000.000000000000000);
        dSBox_baseSig_StartT->setValue(200.000000000000000);

        horizontalLayout_2->addWidget(dSBox_baseSig_StartT);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_baseSig_TimeLength = new QLabel(groupBox_baseSig_panel);
        label_baseSig_TimeLength->setObjectName(QString::fromUtf8("label_baseSig_TimeLength"));

        horizontalLayout_3->addWidget(label_baseSig_TimeLength);

        dSBox_baseSig_TimeLength = new QDoubleSpinBox(groupBox_baseSig_panel);
        dSBox_baseSig_TimeLength->setObjectName(QString::fromUtf8("dSBox_baseSig_TimeLength"));
        dSBox_baseSig_TimeLength->setMaximum(1000.000000000000000);
        dSBox_baseSig_TimeLength->setValue(300.000000000000000);

        horizontalLayout_3->addWidget(dSBox_baseSig_TimeLength);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_baseSig_Amp = new QLabel(groupBox_baseSig_panel);
        label_baseSig_Amp->setObjectName(QString::fromUtf8("label_baseSig_Amp"));

        horizontalLayout_4->addWidget(label_baseSig_Amp);

        dSBox_baseSig_Amp = new QDoubleSpinBox(groupBox_baseSig_panel);
        dSBox_baseSig_Amp->setObjectName(QString::fromUtf8("dSBox_baseSig_Amp"));
        dSBox_baseSig_Amp->setMinimum(0.000000000000000);
        dSBox_baseSig_Amp->setMaximum(200000.000000000000000);
        dSBox_baseSig_Amp->setValue(1.000000000000000);

        horizontalLayout_4->addWidget(dSBox_baseSig_Amp);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_baseSig_SampleRate = new QLabel(groupBox_baseSig_panel);
        label_baseSig_SampleRate->setObjectName(QString::fromUtf8("label_baseSig_SampleRate"));

        horizontalLayout_5->addWidget(label_baseSig_SampleRate);

        dSBos_baseSig_SampleRate = new QSpinBox(groupBox_baseSig_panel);
        dSBos_baseSig_SampleRate->setObjectName(QString::fromUtf8("dSBos_baseSig_SampleRate"));
        dSBos_baseSig_SampleRate->setMaximum(500000);
        dSBos_baseSig_SampleRate->setValue(44100);

        horizontalLayout_5->addWidget(dSBos_baseSig_SampleRate);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);

        btn_drawBaseSignal = new QPushButton(groupBox_baseSig_panel);
        btn_drawBaseSignal->setObjectName(QString::fromUtf8("btn_drawBaseSignal"));

        verticalLayout_2->addWidget(btn_drawBaseSignal);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_7->addWidget(groupBox_baseSig_panel);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox_modSig_chart = new QGroupBox(FFTTestWgtClass);
        groupBox_modSig_chart->setObjectName(QString::fromUtf8("groupBox_modSig_chart"));
        sizePolicy.setHeightForWidth(groupBox_modSig_chart->sizePolicy().hasHeightForWidth());
        groupBox_modSig_chart->setSizePolicy(sizePolicy);
        groupBox_modSig_chart->setMinimumSize(QSize(1000, 315));
        groupBox_modSig_chart->setMaximumSize(QSize(1980, 440));
        HLayout_modSig_chart = new QHBoxLayout(groupBox_modSig_chart);
        HLayout_modSig_chart->setSpacing(6);
        HLayout_modSig_chart->setContentsMargins(11, 11, 11, 11);
        HLayout_modSig_chart->setObjectName(QString::fromUtf8("HLayout_modSig_chart"));

        horizontalLayout_8->addWidget(groupBox_modSig_chart);

        groupBox_modSig_panel = new QGroupBox(FFTTestWgtClass);
        groupBox_modSig_panel->setObjectName(QString::fromUtf8("groupBox_modSig_panel"));
        sizePolicy1.setHeightForWidth(groupBox_modSig_panel->sizePolicy().hasHeightForWidth());
        groupBox_modSig_panel->setSizePolicy(sizePolicy1);
        groupBox_modSig_panel->setMinimumSize(QSize(230, 315));
        groupBox_modSig_panel->setMaximumSize(QSize(230, 440));
        verticalLayout_3 = new QVBoxLayout(groupBox_modSig_panel);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_modSig_Freq = new QLabel(groupBox_modSig_panel);
        label_modSig_Freq->setObjectName(QString::fromUtf8("label_modSig_Freq"));

        horizontalLayout_10->addWidget(label_modSig_Freq);

        dSBox_modSig_Freq = new QDoubleSpinBox(groupBox_modSig_panel);
        dSBox_modSig_Freq->setObjectName(QString::fromUtf8("dSBox_modSig_Freq"));
        dSBox_modSig_Freq->setMinimum(0.000000000000000);
        dSBox_modSig_Freq->setMaximum(1000.000000000000000);
        dSBox_modSig_Freq->setValue(25.000000000000000);

        horizontalLayout_10->addWidget(dSBox_modSig_Freq);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_modSig_StartT = new QLabel(groupBox_modSig_panel);
        label_modSig_StartT->setObjectName(QString::fromUtf8("label_modSig_StartT"));

        horizontalLayout_11->addWidget(label_modSig_StartT);

        dSBox_modSig_StartT = new QDoubleSpinBox(groupBox_modSig_panel);
        dSBox_modSig_StartT->setObjectName(QString::fromUtf8("dSBox_modSig_StartT"));
        dSBox_modSig_StartT->setMaximum(5000.000000000000000);

        horizontalLayout_11->addWidget(dSBox_modSig_StartT);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_modSig_TimeLength = new QLabel(groupBox_modSig_panel);
        label_modSig_TimeLength->setObjectName(QString::fromUtf8("label_modSig_TimeLength"));

        horizontalLayout_12->addWidget(label_modSig_TimeLength);

        dSBox_modSig_TimeLength = new QDoubleSpinBox(groupBox_modSig_panel);
        dSBox_modSig_TimeLength->setObjectName(QString::fromUtf8("dSBox_modSig_TimeLength"));
        dSBox_modSig_TimeLength->setMaximum(1000.000000000000000);
        dSBox_modSig_TimeLength->setValue(1000.000000000000000);

        horizontalLayout_12->addWidget(dSBox_modSig_TimeLength);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_modSig_Depth = new QLabel(groupBox_modSig_panel);
        label_modSig_Depth->setObjectName(QString::fromUtf8("label_modSig_Depth"));

        horizontalLayout_13->addWidget(label_modSig_Depth);

        dSBox_modSig_Depth = new QDoubleSpinBox(groupBox_modSig_panel);
        dSBox_modSig_Depth->setObjectName(QString::fromUtf8("dSBox_modSig_Depth"));
        dSBox_modSig_Depth->setMaximum(100.000000000000000);
        dSBox_modSig_Depth->setValue(0.000000000000000);

        horizontalLayout_13->addWidget(dSBox_modSig_Depth);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_modSig_SampleRate = new QLabel(groupBox_modSig_panel);
        label_modSig_SampleRate->setObjectName(QString::fromUtf8("label_modSig_SampleRate"));

        horizontalLayout_14->addWidget(label_modSig_SampleRate);

        dSBos_modSig_SampleRate = new QSpinBox(groupBox_modSig_panel);
        dSBos_modSig_SampleRate->setObjectName(QString::fromUtf8("dSBos_modSig_SampleRate"));
        dSBos_modSig_SampleRate->setMaximum(500000);
        dSBos_modSig_SampleRate->setValue(44100);

        horizontalLayout_14->addWidget(dSBos_modSig_SampleRate);


        verticalLayout_4->addLayout(horizontalLayout_14);


        verticalLayout_3->addLayout(verticalLayout_4);

        groupBox_modSig_Type = new QGroupBox(groupBox_modSig_panel);
        groupBox_modSig_Type->setObjectName(QString::fromUtf8("groupBox_modSig_Type"));
        horizontalLayout_15 = new QHBoxLayout(groupBox_modSig_Type);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        radioButton_modSig_Type_sin = new QRadioButton(groupBox_modSig_Type);
        radioButton_modSig_Type_sin->setObjectName(QString::fromUtf8("radioButton_modSig_Type_sin"));
        radioButton_modSig_Type_sin->setChecked(true);

        horizontalLayout_15->addWidget(radioButton_modSig_Type_sin);

        radioButton_modSig_Type_square = new QRadioButton(groupBox_modSig_Type);
        radioButton_modSig_Type_square->setObjectName(QString::fromUtf8("radioButton_modSig_Type_square"));

        horizontalLayout_15->addWidget(radioButton_modSig_Type_square);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_3);


        verticalLayout_3->addWidget(groupBox_modSig_Type);

        groupBox_modSig_DrawContent = new QGroupBox(groupBox_modSig_panel);
        groupBox_modSig_DrawContent->setObjectName(QString::fromUtf8("groupBox_modSig_DrawContent"));
        horizontalLayout_16 = new QHBoxLayout(groupBox_modSig_DrawContent);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        checkBox_modSig_drawModSig = new QCheckBox(groupBox_modSig_DrawContent);
        checkBox_modSig_drawModSig->setObjectName(QString::fromUtf8("checkBox_modSig_drawModSig"));
        checkBox_modSig_drawModSig->setChecked(true);

        horizontalLayout_16->addWidget(checkBox_modSig_drawModSig);

        checkBox_modSig_drawSigAfterMod = new QCheckBox(groupBox_modSig_DrawContent);
        checkBox_modSig_drawSigAfterMod->setObjectName(QString::fromUtf8("checkBox_modSig_drawSigAfterMod"));
        checkBox_modSig_drawSigAfterMod->setChecked(true);

        horizontalLayout_16->addWidget(checkBox_modSig_drawSigAfterMod);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(groupBox_modSig_DrawContent);

        btn_drawmodSig = new QPushButton(groupBox_modSig_panel);
        btn_drawmodSig->setObjectName(QString::fromUtf8("btn_drawmodSig"));

        verticalLayout_3->addWidget(btn_drawmodSig);

        btn_saveModResultToDCenter = new QPushButton(groupBox_modSig_panel);
        btn_saveModResultToDCenter->setObjectName(QString::fromUtf8("btn_saveModResultToDCenter"));

        verticalLayout_3->addWidget(btn_saveModResultToDCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_8->addWidget(groupBox_modSig_panel);


        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        groupBox_FFT_chart = new QGroupBox(FFTTestWgtClass);
        groupBox_FFT_chart->setObjectName(QString::fromUtf8("groupBox_FFT_chart"));
        sizePolicy.setHeightForWidth(groupBox_FFT_chart->sizePolicy().hasHeightForWidth());
        groupBox_FFT_chart->setSizePolicy(sizePolicy);
        groupBox_FFT_chart->setMinimumSize(QSize(1000, 250));
        groupBox_FFT_chart->setMaximumSize(QSize(1980, 440));
        HLayout_FFT_Chart = new QHBoxLayout(groupBox_FFT_chart);
        HLayout_FFT_Chart->setSpacing(6);
        HLayout_FFT_Chart->setContentsMargins(11, 11, 11, 11);
        HLayout_FFT_Chart->setObjectName(QString::fromUtf8("HLayout_FFT_Chart"));

        horizontalLayout_20->addWidget(groupBox_FFT_chart);

        groupBox_FFT_panel = new QGroupBox(FFTTestWgtClass);
        groupBox_FFT_panel->setObjectName(QString::fromUtf8("groupBox_FFT_panel"));
        sizePolicy1.setHeightForWidth(groupBox_FFT_panel->sizePolicy().hasHeightForWidth());
        groupBox_FFT_panel->setSizePolicy(sizePolicy1);
        groupBox_FFT_panel->setMinimumSize(QSize(230, 300));
        groupBox_FFT_panel->setMaximumSize(QSize(230, 440));
        verticalLayout_5 = new QVBoxLayout(groupBox_FFT_panel);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_FFTFrom = new QGroupBox(groupBox_FFT_panel);
        groupBox_FFTFrom->setObjectName(QString::fromUtf8("groupBox_FFTFrom"));
        groupBox_FFTFrom->setMinimumSize(QSize(0, 52));
        horizontalLayout_6 = new QHBoxLayout(groupBox_FFTFrom);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        radioButton_FFTFrom_zhihu = new QRadioButton(groupBox_FFTFrom);
        radioButton_FFTFrom_zhihu->setObjectName(QString::fromUtf8("radioButton_FFTFrom_zhihu"));
        radioButton_FFTFrom_zhihu->setChecked(true);

        horizontalLayout_6->addWidget(radioButton_FFTFrom_zhihu);

        radioButton_FFTFrom_FFTW = new QRadioButton(groupBox_FFTFrom);
        radioButton_FFTFrom_FFTW->setObjectName(QString::fromUtf8("radioButton_FFTFrom_FFTW"));

        horizontalLayout_6->addWidget(radioButton_FFTFrom_FFTW);

        radioButton_FFTFrom_cudaFFt = new QRadioButton(groupBox_FFTFrom);
        radioButton_FFTFrom_cudaFFt->setObjectName(QString::fromUtf8("radioButton_FFTFrom_cudaFFt"));

        horizontalLayout_6->addWidget(radioButton_FFTFrom_cudaFFt);


        verticalLayout_5->addWidget(groupBox_FFTFrom);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_FFTStartTime = new QLabel(groupBox_FFT_panel);
        label_FFTStartTime->setObjectName(QString::fromUtf8("label_FFTStartTime"));

        horizontalLayout_21->addWidget(label_FFTStartTime);

        dSBox_FFTstartTime = new QDoubleSpinBox(groupBox_FFT_panel);
        dSBox_FFTstartTime->setObjectName(QString::fromUtf8("dSBox_FFTstartTime"));
        dSBox_FFTstartTime->setEnabled(true);
        dSBox_FFTstartTime->setMinimumSize(QSize(88, 0));
        dSBox_FFTstartTime->setMaximumSize(QSize(88, 16777215));
        dSBox_FFTstartTime->setMinimum(0.000000000000000);
        dSBox_FFTstartTime->setMaximum(10000.000000000000000);
        dSBox_FFTstartTime->setValue(0.000000000000000);

        horizontalLayout_21->addWidget(dSBox_FFTstartTime);


        verticalLayout_5->addLayout(horizontalLayout_21);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_FFTinputPointInPowerOf2 = new QLabel(groupBox_FFT_panel);
        label_FFTinputPointInPowerOf2->setObjectName(QString::fromUtf8("label_FFTinputPointInPowerOf2"));

        horizontalLayout_18->addWidget(label_FFTinputPointInPowerOf2);

        dSBox_FFTInputPointInPowerOf2 = new QDoubleSpinBox(groupBox_FFT_panel);
        dSBox_FFTInputPointInPowerOf2->setObjectName(QString::fromUtf8("dSBox_FFTInputPointInPowerOf2"));
        dSBox_FFTInputPointInPowerOf2->setMinimumSize(QSize(88, 0));
        dSBox_FFTInputPointInPowerOf2->setMaximumSize(QSize(88, 16777215));
        dSBox_FFTInputPointInPowerOf2->setMinimum(0.000000000000000);
        dSBox_FFTInputPointInPowerOf2->setMaximum(10000.000000000000000);
        dSBox_FFTInputPointInPowerOf2->setValue(12.000000000000000);

        horizontalLayout_18->addWidget(dSBox_FFTInputPointInPowerOf2);


        verticalLayout_5->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_FFTSampleRate = new QLabel(groupBox_FFT_panel);
        label_FFTSampleRate->setObjectName(QString::fromUtf8("label_FFTSampleRate"));

        horizontalLayout_19->addWidget(label_FFTSampleRate);

        dSBox_FFTSampleRate = new QDoubleSpinBox(groupBox_FFT_panel);
        dSBox_FFTSampleRate->setObjectName(QString::fromUtf8("dSBox_FFTSampleRate"));
        dSBox_FFTSampleRate->setEnabled(true);
        dSBox_FFTSampleRate->setMinimumSize(QSize(88, 0));
        dSBox_FFTSampleRate->setMaximumSize(QSize(88, 16777215));
        dSBox_FFTSampleRate->setDecimals(0);
        dSBox_FFTSampleRate->setMinimum(0.000000000000000);
        dSBox_FFTSampleRate->setMaximum(500000.000000000000000);
        dSBox_FFTSampleRate->setValue(44100.000000000000000);

        horizontalLayout_19->addWidget(dSBox_FFTSampleRate);


        verticalLayout_5->addLayout(horizontalLayout_19);

        btn_drawFFTResult = new QPushButton(groupBox_FFT_panel);
        btn_drawFFTResult->setObjectName(QString::fromUtf8("btn_drawFFTResult"));

        verticalLayout_5->addWidget(btn_drawFFTResult);

        btn_drawIFFT = new QPushButton(groupBox_FFT_panel);
        btn_drawIFFT->setObjectName(QString::fromUtf8("btn_drawIFFT"));

        verticalLayout_5->addWidget(btn_drawIFFT);

        label_FFTInputPointCount = new QLabel(groupBox_FFT_panel);
        label_FFTInputPointCount->setObjectName(QString::fromUtf8("label_FFTInputPointCount"));

        verticalLayout_5->addWidget(label_FFTInputPointCount);

        label_FFTWindowLength = new QLabel(groupBox_FFT_panel);
        label_FFTWindowLength->setObjectName(QString::fromUtf8("label_FFTWindowLength"));

        verticalLayout_5->addWidget(label_FFTWindowLength);

        label_FFTFreqDelta = new QLabel(groupBox_FFT_panel);
        label_FFTFreqDelta->setObjectName(QString::fromUtf8("label_FFTFreqDelta"));

        verticalLayout_5->addWidget(label_FFTFreqDelta);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout_20->addWidget(groupBox_FFT_panel);


        verticalLayout_6->addLayout(horizontalLayout_20);


        retranslateUi(FFTTestWgtClass);

        QMetaObject::connectSlotsByName(FFTTestWgtClass);
    } // setupUi

    void retranslateUi(QWidget *FFTTestWgtClass)
    {
        FFTTestWgtClass->setWindowTitle(QApplication::translate("FFTTestWgtClass", "FFTTestWgt", nullptr));
        groupBox_baseSig_chart->setTitle(QApplication::translate("FFTTestWgtClass", "\345\237\272\351\242\221\344\277\241\345\217\267\347\273\230\345\210\266", nullptr));
        groupBox_baseSig_panel->setTitle(QApplication::translate("FFTTestWgtClass", "\345\237\272\351\242\221\344\277\241\345\217\267", nullptr));
        label_baseSig_Freq->setText(QApplication::translate("FFTTestWgtClass", "\351\242\221\347\216\207\357\274\210HZ\357\274\211", nullptr));
        label_baseSig_StartT->setText(QApplication::translate("FFTTestWgtClass", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\210ms\357\274\211", nullptr));
        label_baseSig_TimeLength->setText(QApplication::translate("FFTTestWgtClass", "\344\277\241\345\217\267\346\227\266\351\227\264\351\225\277\345\272\246\357\274\210ms)", nullptr));
        label_baseSig_Amp->setText(QApplication::translate("FFTTestWgtClass", "\346\214\257\345\271\205(\316\274Pa)", nullptr));
        label_baseSig_SampleRate->setText(QApplication::translate("FFTTestWgtClass", "\351\207\207\346\240\267\351\242\221\347\216\207\357\274\210HZ\357\274\211", nullptr));
        btn_drawBaseSignal->setText(QApplication::translate("FFTTestWgtClass", "\347\273\230\345\210\266\345\237\272\347\241\200\344\277\241\345\217\267", nullptr));
        groupBox_modSig_chart->setTitle(QApplication::translate("FFTTestWgtClass", "\350\260\203\345\210\266\344\277\241\345\217\267\347\273\230\345\210\266", nullptr));
        groupBox_modSig_panel->setTitle(QApplication::translate("FFTTestWgtClass", "\350\260\203\345\210\266\344\277\241\345\217\267", nullptr));
        label_modSig_Freq->setText(QApplication::translate("FFTTestWgtClass", "\351\242\221\347\216\207\357\274\210HZ\357\274\211", nullptr));
        label_modSig_StartT->setText(QApplication::translate("FFTTestWgtClass", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\210ms\357\274\211", nullptr));
        label_modSig_TimeLength->setText(QApplication::translate("FFTTestWgtClass", "\344\277\241\345\217\267\346\227\266\351\227\264\351\225\277\345\272\246\357\274\210ms)", nullptr));
        label_modSig_Depth->setText(QApplication::translate("FFTTestWgtClass", "\350\260\203\345\210\266\345\272\246\357\274\210%\357\274\211", nullptr));
        label_modSig_SampleRate->setText(QApplication::translate("FFTTestWgtClass", "\351\207\207\346\240\267\351\242\221\347\216\207\357\274\210HZ\357\274\211", nullptr));
        groupBox_modSig_Type->setTitle(QApplication::translate("FFTTestWgtClass", "\350\260\203\345\210\266\344\277\241\345\217\267\347\261\273\345\236\213", nullptr));
        radioButton_modSig_Type_sin->setText(QApplication::translate("FFTTestWgtClass", "\346\255\243\345\274\246\346\263\242", nullptr));
        radioButton_modSig_Type_square->setText(QApplication::translate("FFTTestWgtClass", "\346\226\271\346\263\242", nullptr));
        groupBox_modSig_DrawContent->setTitle(QApplication::translate("FFTTestWgtClass", "\347\273\230\345\210\266\345\206\205\345\256\271", nullptr));
        checkBox_modSig_drawModSig->setText(QApplication::translate("FFTTestWgtClass", "\350\260\203\345\210\266\344\277\241\345\217\267", nullptr));
        checkBox_modSig_drawSigAfterMod->setText(QApplication::translate("FFTTestWgtClass", "\350\260\203\345\210\266\347\273\223\346\236\234", nullptr));
        btn_drawmodSig->setText(QApplication::translate("FFTTestWgtClass", "\347\273\230\345\210\266\350\260\203\345\210\266\344\277\241\345\217\267", nullptr));
        btn_saveModResultToDCenter->setText(QApplication::translate("FFTTestWgtClass", "\345\255\230\345\202\250\350\260\203\345\210\266\344\277\241\345\217\267\357\274\210D_Center\357\274\211", nullptr));
        groupBox_FFT_chart->setTitle(QApplication::translate("FFTTestWgtClass", "FFT\347\273\223\346\236\234", nullptr));
        groupBox_FFT_panel->setTitle(QApplication::translate("FFTTestWgtClass", "FFT\350\247\243\346\236\220", nullptr));
        groupBox_FFTFrom->setTitle(QApplication::translate("FFTTestWgtClass", "FFT\346\235\245\346\272\220", nullptr));
        radioButton_FFTFrom_zhihu->setText(QApplication::translate("FFTTestWgtClass", "\347\275\221\345\217\213", nullptr));
        radioButton_FFTFrom_FFTW->setText(QApplication::translate("FFTTestWgtClass", "FFTW", nullptr));
        radioButton_FFTFrom_cudaFFt->setText(QApplication::translate("FFTTestWgtClass", "CudaFFT", nullptr));
        label_FFTStartTime->setText(QApplication::translate("FFTTestWgtClass", "\350\276\223\345\205\245\345\274\200\345\247\213\346\227\266\351\227\264(ms)", nullptr));
        label_FFTinputPointInPowerOf2->setText(QApplication::translate("FFTTestWgtClass", "\350\276\223\345\205\245\347\202\271\346\225\260\345\257\271\345\272\2242\347\232\204\346\254\241\346\225\260", nullptr));
        label_FFTSampleRate->setText(QApplication::translate("FFTTestWgtClass", "\351\207\207\346\240\267\347\216\207(HZ)", nullptr));
        btn_drawFFTResult->setText(QApplication::translate("FFTTestWgtClass", "\347\273\230\345\210\266FFT\347\273\223\346\236\234", nullptr));
        btn_drawIFFT->setText(QApplication::translate("FFTTestWgtClass", "\347\273\230\345\210\266IFFT\347\273\223\346\236\234", nullptr));
        label_FFTInputPointCount->setText(QApplication::translate("FFTTestWgtClass", "\351\207\207\346\240\267\347\202\271\346\225\260\357\274\232", nullptr));
        label_FFTWindowLength->setText(QApplication::translate("FFTTestWgtClass", "\347\252\227\345\217\243\346\227\266\351\225\277\357\274\232", nullptr));
        label_FFTFreqDelta->setText(QApplication::translate("FFTTestWgtClass", "\351\242\221\347\216\207\351\227\264\351\232\224\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FFTTestWgtClass: public Ui_FFTTestWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFTTESTWGT_H
