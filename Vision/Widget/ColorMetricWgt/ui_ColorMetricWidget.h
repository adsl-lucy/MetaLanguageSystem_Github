/********************************************************************************
** Form generated from reading UI file 'ColorMetricWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORMETRICWIDGET_H
#define UI_COLORMETRICWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
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

class Ui_ColorMetricWidgetClass
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget_main;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_22;
    QGroupBox *groupBox_2;
    QHBoxLayout *HLayout_Cht_Lab;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_MousePos_Current_Lab;
    QLabel *label_MousePos_Current_XYZ;
    QLabel *label_MousePos_Current_sRgbGamma;
    QLabel *label_MousePos_Current_sRgb;
    QLabel *label_MousePos_Current_Cr255;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_MousePos_Current_CrPaint;
    QLabel *label_MousePos_CurrentToPress;
    QLabel *label_MousePos_Press_CrPaint;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_MousePos_Press_Lab;
    QLabel *label_MousePos_Press_XYZ;
    QLabel *label_MousePos_Press_sRgbGamma;
    QLabel *label_MousePos_Press_sRgb;
    QLabel *label_MousePos_Press_Cr255;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_CrMetric_RGB_255;
    QLabel *label_CrMetric_LAB_1976;
    QLabel *label_CrMetric_LAB_1984;
    QLabel *label_CrMetric_LAB_1994;
    QLabel *label_CrMetric_LAB_2000;
    QSpacerItem *verticalSpacer_2;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_AxiSet;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_Axi_Fix_L;
    QRadioButton *radioButton_Axi_Fix_R;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButton_Axi_Interval_pixel;
    QRadioButton *radioButton_Axi_Interval_Density;
    QCheckBox *checkBox_GammaExist;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_PlaneStartPos;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_PlaneStart_L;
    QDoubleSpinBox *DSBox_PlaneStart_L;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_PlaneStart_A;
    QDoubleSpinBox *DSBox_PlaneStart_A;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_PlaneStart_B;
    QDoubleSpinBox *DSBox_PlaneStart_B;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_PlaneStart_R;
    QDoubleSpinBox *DSBox_PlaneStart_R;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_PlaneEnd_L;
    QDoubleSpinBox *DSBox_PlaneEnd_L;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_PlaneEnd_A;
    QDoubleSpinBox *DSBox_PlaneEnd_A;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_PlaneEnd_B;
    QDoubleSpinBox *DSBox_PlaneEnd_B;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_PlaneEnd_R;
    QDoubleSpinBox *DSBox_PlaneEnd_R;
    QTabWidget *tabWidget_3;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_Interval_Cr_Radius;
    QDoubleSpinBox *DSBox_Interval_Cr_Radius;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_Interval_Cr_L;
    QDoubleSpinBox *DSBox_Interval_Cr_L;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_Interval_Cr_AB;
    QDoubleSpinBox *DSBox_Interval_Cr_AB;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_Interval_Grid_Radius;
    QDoubleSpinBox *DSBox_Interval_Grid_Radius;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_Interval_Grid_L;
    QDoubleSpinBox *DSBox_Interval_Grid_L;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_Interval_Grid_AB;
    QDoubleSpinBox *DSBox_Interval_Grid_AB;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_drawAxis;
    QCheckBox *checkBox_drawGrid;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_CrRectWidth;
    QSpinBox *SBox_CrRectWidth;
    QLabel *label_CaculateRectCount;
    QLabel *label_ValidRectCount;
    QLabel *label_CrGenState;
    QProgressBar *progressBar_RectGenState;
    QPushButton *btn_updateChtOnly;
    QPushButton *btn_GenLABDistribute;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_26;
    QGroupBox *groupBox_8;
    QHBoxLayout *HLayout_ImagePainter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_selImg;
    QComboBox *comboBox_selImg;
    QPushButton *btn_LoadImg;
    QCheckBox *checkBox_autoLabTransfer;
    QGroupBox *groupBox_selFileTag_2;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_Img_FileName;
    QFrame *line;
    QLabel *label_img_Size;
    QLabel *label_Img_CrDepth;
    QLabel *label_Img_CrFormat;
    QLabel *label_transferState;
    QProgressBar *progressBar_transferState;
    QPushButton *btn_transferImg;
    QGroupBox *groupBox_CrMode;
    QHBoxLayout *horizontalLayout_28;
    QRadioButton *radioButton_CrMode_RGB;
    QRadioButton *radioButton_CrMode_LAB_L;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *ColorMetricWidgetClass)
    {
        if (ColorMetricWidgetClass->objectName().isEmpty())
            ColorMetricWidgetClass->setObjectName(QString::fromUtf8("ColorMetricWidgetClass"));
        ColorMetricWidgetClass->resize(1228, 792);
        horizontalLayout = new QHBoxLayout(ColorMetricWidgetClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget_main = new QTabWidget(ColorMetricWidgetClass);
        tabWidget_main->setObjectName(QString::fromUtf8("tabWidget_main"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_22 = new QHBoxLayout(groupBox);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        HLayout_Cht_Lab = new QHBoxLayout(groupBox_2);
        HLayout_Cht_Lab->setSpacing(6);
        HLayout_Cht_Lab->setContentsMargins(11, 11, 11, 11);
        HLayout_Cht_Lab->setObjectName(QString::fromUtf8("HLayout_Cht_Lab"));

        horizontalLayout_22->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(270, 0));
        groupBox_3->setMaximumSize(QSize(270, 16777215));
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_8 = new QVBoxLayout(groupBox_4);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_MousePos_Current_Lab = new QLabel(groupBox_4);
        label_MousePos_Current_Lab->setObjectName(QString::fromUtf8("label_MousePos_Current_Lab"));

        verticalLayout_8->addWidget(label_MousePos_Current_Lab);

        label_MousePos_Current_XYZ = new QLabel(groupBox_4);
        label_MousePos_Current_XYZ->setObjectName(QString::fromUtf8("label_MousePos_Current_XYZ"));

        verticalLayout_8->addWidget(label_MousePos_Current_XYZ);

        label_MousePos_Current_sRgbGamma = new QLabel(groupBox_4);
        label_MousePos_Current_sRgbGamma->setObjectName(QString::fromUtf8("label_MousePos_Current_sRgbGamma"));

        verticalLayout_8->addWidget(label_MousePos_Current_sRgbGamma);

        label_MousePos_Current_sRgb = new QLabel(groupBox_4);
        label_MousePos_Current_sRgb->setObjectName(QString::fromUtf8("label_MousePos_Current_sRgb"));

        verticalLayout_8->addWidget(label_MousePos_Current_sRgb);

        label_MousePos_Current_Cr255 = new QLabel(groupBox_4);
        label_MousePos_Current_Cr255->setObjectName(QString::fromUtf8("label_MousePos_Current_Cr255"));

        verticalLayout_8->addWidget(label_MousePos_Current_Cr255);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_MousePos_Current_CrPaint = new QLabel(groupBox_4);
        label_MousePos_Current_CrPaint->setObjectName(QString::fromUtf8("label_MousePos_Current_CrPaint"));
        label_MousePos_Current_CrPaint->setMinimumSize(QSize(36, 36));
        label_MousePos_Current_CrPaint->setMaximumSize(QSize(36, 36));

        horizontalLayout_9->addWidget(label_MousePos_Current_CrPaint);

        label_MousePos_CurrentToPress = new QLabel(groupBox_4);
        label_MousePos_CurrentToPress->setObjectName(QString::fromUtf8("label_MousePos_CurrentToPress"));
        label_MousePos_CurrentToPress->setMinimumSize(QSize(36, 36));
        label_MousePos_CurrentToPress->setMaximumSize(QSize(36, 36));
        QFont font;
        font.setPointSize(16);
        label_MousePos_CurrentToPress->setFont(font);
        label_MousePos_CurrentToPress->setLayoutDirection(Qt::LeftToRight);
        label_MousePos_CurrentToPress->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_MousePos_CurrentToPress);

        label_MousePos_Press_CrPaint = new QLabel(groupBox_4);
        label_MousePos_Press_CrPaint->setObjectName(QString::fromUtf8("label_MousePos_Press_CrPaint"));
        label_MousePos_Press_CrPaint->setMinimumSize(QSize(36, 36));
        label_MousePos_Press_CrPaint->setMaximumSize(QSize(36, 36));

        horizontalLayout_9->addWidget(label_MousePos_Press_CrPaint);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);


        verticalLayout_8->addLayout(horizontalLayout_9);


        verticalLayout_7->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(0, 0));
        verticalLayout_9 = new QVBoxLayout(groupBox_5);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_MousePos_Press_Lab = new QLabel(groupBox_5);
        label_MousePos_Press_Lab->setObjectName(QString::fromUtf8("label_MousePos_Press_Lab"));

        verticalLayout_9->addWidget(label_MousePos_Press_Lab);

        label_MousePos_Press_XYZ = new QLabel(groupBox_5);
        label_MousePos_Press_XYZ->setObjectName(QString::fromUtf8("label_MousePos_Press_XYZ"));

        verticalLayout_9->addWidget(label_MousePos_Press_XYZ);

        label_MousePos_Press_sRgbGamma = new QLabel(groupBox_5);
        label_MousePos_Press_sRgbGamma->setObjectName(QString::fromUtf8("label_MousePos_Press_sRgbGamma"));

        verticalLayout_9->addWidget(label_MousePos_Press_sRgbGamma);

        label_MousePos_Press_sRgb = new QLabel(groupBox_5);
        label_MousePos_Press_sRgb->setObjectName(QString::fromUtf8("label_MousePos_Press_sRgb"));

        verticalLayout_9->addWidget(label_MousePos_Press_sRgb);

        label_MousePos_Press_Cr255 = new QLabel(groupBox_5);
        label_MousePos_Press_Cr255->setObjectName(QString::fromUtf8("label_MousePos_Press_Cr255"));

        verticalLayout_9->addWidget(label_MousePos_Press_Cr255);


        verticalLayout_7->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(0, 0));
        verticalLayout_10 = new QVBoxLayout(groupBox_6);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_CrMetric_RGB_255 = new QLabel(groupBox_6);
        label_CrMetric_RGB_255->setObjectName(QString::fromUtf8("label_CrMetric_RGB_255"));

        verticalLayout_10->addWidget(label_CrMetric_RGB_255);

        label_CrMetric_LAB_1976 = new QLabel(groupBox_6);
        label_CrMetric_LAB_1976->setObjectName(QString::fromUtf8("label_CrMetric_LAB_1976"));

        verticalLayout_10->addWidget(label_CrMetric_LAB_1976);

        label_CrMetric_LAB_1984 = new QLabel(groupBox_6);
        label_CrMetric_LAB_1984->setObjectName(QString::fromUtf8("label_CrMetric_LAB_1984"));

        verticalLayout_10->addWidget(label_CrMetric_LAB_1984);

        label_CrMetric_LAB_1994 = new QLabel(groupBox_6);
        label_CrMetric_LAB_1994->setObjectName(QString::fromUtf8("label_CrMetric_LAB_1994"));

        verticalLayout_10->addWidget(label_CrMetric_LAB_1994);

        label_CrMetric_LAB_2000 = new QLabel(groupBox_6);
        label_CrMetric_LAB_2000->setObjectName(QString::fromUtf8("label_CrMetric_LAB_2000"));

        verticalLayout_10->addWidget(label_CrMetric_LAB_2000);


        verticalLayout_7->addWidget(groupBox_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);


        horizontalLayout_22->addWidget(groupBox_3);


        horizontalLayout_2->addWidget(groupBox);

        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setMaximumSize(QSize(280, 16777215));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_6 = new QVBoxLayout(tab_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_AxiSet = new QGroupBox(tab_3);
        groupBox_AxiSet->setObjectName(QString::fromUtf8("groupBox_AxiSet"));
        verticalLayout = new QVBoxLayout(groupBox_AxiSet);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButton_Axi_Fix_L = new QRadioButton(groupBox_AxiSet);
        radioButton_Axi_Fix_L->setObjectName(QString::fromUtf8("radioButton_Axi_Fix_L"));
        radioButton_Axi_Fix_L->setChecked(false);

        horizontalLayout_4->addWidget(radioButton_Axi_Fix_L);

        radioButton_Axi_Fix_R = new QRadioButton(groupBox_AxiSet);
        radioButton_Axi_Fix_R->setObjectName(QString::fromUtf8("radioButton_Axi_Fix_R"));
        radioButton_Axi_Fix_R->setChecked(true);

        horizontalLayout_4->addWidget(radioButton_Axi_Fix_R);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        radioButton_Axi_Interval_pixel = new QRadioButton(groupBox_AxiSet);
        radioButton_Axi_Interval_pixel->setObjectName(QString::fromUtf8("radioButton_Axi_Interval_pixel"));
        radioButton_Axi_Interval_pixel->setChecked(false);

        horizontalLayout_7->addWidget(radioButton_Axi_Interval_pixel);

        radioButton_Axi_Interval_Density = new QRadioButton(groupBox_AxiSet);
        radioButton_Axi_Interval_Density->setObjectName(QString::fromUtf8("radioButton_Axi_Interval_Density"));
        radioButton_Axi_Interval_Density->setChecked(true);

        horizontalLayout_7->addWidget(radioButton_Axi_Interval_Density);


        verticalLayout->addLayout(horizontalLayout_7);


        verticalLayout_6->addWidget(groupBox_AxiSet);

        checkBox_GammaExist = new QCheckBox(tab_3);
        checkBox_GammaExist->setObjectName(QString::fromUtf8("checkBox_GammaExist"));
        checkBox_GammaExist->setChecked(true);

        verticalLayout_6->addWidget(checkBox_GammaExist);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        groupBox_PlaneStartPos = new QGroupBox(tab_3);
        groupBox_PlaneStartPos->setObjectName(QString::fromUtf8("groupBox_PlaneStartPos"));
        verticalLayout_4 = new QVBoxLayout(groupBox_PlaneStartPos);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_PlaneStart_L = new QLabel(groupBox_PlaneStartPos);
        label_PlaneStart_L->setObjectName(QString::fromUtf8("label_PlaneStart_L"));
        label_PlaneStart_L->setMinimumSize(QSize(12, 0));
        label_PlaneStart_L->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_14->addWidget(label_PlaneStart_L);

        DSBox_PlaneStart_L = new QDoubleSpinBox(groupBox_PlaneStartPos);
        DSBox_PlaneStart_L->setObjectName(QString::fromUtf8("DSBox_PlaneStart_L"));
        DSBox_PlaneStart_L->setEnabled(false);
        DSBox_PlaneStart_L->setMaximum(100.000000000000000);
        DSBox_PlaneStart_L->setValue(75.000000000000000);

        horizontalLayout_14->addWidget(DSBox_PlaneStart_L);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_PlaneStart_A = new QLabel(groupBox_PlaneStartPos);
        label_PlaneStart_A->setObjectName(QString::fromUtf8("label_PlaneStart_A"));
        label_PlaneStart_A->setMinimumSize(QSize(12, 0));
        label_PlaneStart_A->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_15->addWidget(label_PlaneStart_A);

        DSBox_PlaneStart_A = new QDoubleSpinBox(groupBox_PlaneStartPos);
        DSBox_PlaneStart_A->setObjectName(QString::fromUtf8("DSBox_PlaneStart_A"));
        DSBox_PlaneStart_A->setEnabled(false);
        DSBox_PlaneStart_A->setMinimum(-180.000000000000000);
        DSBox_PlaneStart_A->setMaximum(180.000000000000000);
        DSBox_PlaneStart_A->setValue(-120.000000000000000);

        horizontalLayout_15->addWidget(DSBox_PlaneStart_A);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_PlaneStart_B = new QLabel(groupBox_PlaneStartPos);
        label_PlaneStart_B->setObjectName(QString::fromUtf8("label_PlaneStart_B"));
        label_PlaneStart_B->setMinimumSize(QSize(12, 0));
        label_PlaneStart_B->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_16->addWidget(label_PlaneStart_B);

        DSBox_PlaneStart_B = new QDoubleSpinBox(groupBox_PlaneStartPos);
        DSBox_PlaneStart_B->setObjectName(QString::fromUtf8("DSBox_PlaneStart_B"));
        DSBox_PlaneStart_B->setEnabled(false);
        DSBox_PlaneStart_B->setMinimum(-180.000000000000000);
        DSBox_PlaneStart_B->setMaximum(180.000000000000000);
        DSBox_PlaneStart_B->setValue(-120.000000000000000);

        horizontalLayout_16->addWidget(DSBox_PlaneStart_B);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_PlaneStart_R = new QLabel(groupBox_PlaneStartPos);
        label_PlaneStart_R->setObjectName(QString::fromUtf8("label_PlaneStart_R"));
        label_PlaneStart_R->setMinimumSize(QSize(12, 0));
        label_PlaneStart_R->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_20->addWidget(label_PlaneStart_R);

        DSBox_PlaneStart_R = new QDoubleSpinBox(groupBox_PlaneStartPos);
        DSBox_PlaneStart_R->setObjectName(QString::fromUtf8("DSBox_PlaneStart_R"));
        DSBox_PlaneStart_R->setEnabled(false);
        DSBox_PlaneStart_R->setMinimum(-200.000000000000000);
        DSBox_PlaneStart_R->setMaximum(200.000000000000000);
        DSBox_PlaneStart_R->setValue(-120.000000000000000);

        horizontalLayout_20->addWidget(DSBox_PlaneStart_R);


        verticalLayout_4->addLayout(horizontalLayout_20);


        horizontalLayout_6->addWidget(groupBox_PlaneStartPos);

        groupBox_7 = new QGroupBox(tab_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_5 = new QVBoxLayout(groupBox_7);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_PlaneEnd_L = new QLabel(groupBox_7);
        label_PlaneEnd_L->setObjectName(QString::fromUtf8("label_PlaneEnd_L"));
        label_PlaneEnd_L->setMinimumSize(QSize(12, 0));
        label_PlaneEnd_L->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_17->addWidget(label_PlaneEnd_L);

        DSBox_PlaneEnd_L = new QDoubleSpinBox(groupBox_7);
        DSBox_PlaneEnd_L->setObjectName(QString::fromUtf8("DSBox_PlaneEnd_L"));
        DSBox_PlaneEnd_L->setEnabled(false);
        DSBox_PlaneEnd_L->setMaximum(100.000000000000000);
        DSBox_PlaneEnd_L->setValue(100.000000000000000);

        horizontalLayout_17->addWidget(DSBox_PlaneEnd_L);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_PlaneEnd_A = new QLabel(groupBox_7);
        label_PlaneEnd_A->setObjectName(QString::fromUtf8("label_PlaneEnd_A"));
        label_PlaneEnd_A->setMinimumSize(QSize(12, 0));
        label_PlaneEnd_A->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_18->addWidget(label_PlaneEnd_A);

        DSBox_PlaneEnd_A = new QDoubleSpinBox(groupBox_7);
        DSBox_PlaneEnd_A->setObjectName(QString::fromUtf8("DSBox_PlaneEnd_A"));
        DSBox_PlaneEnd_A->setEnabled(false);
        DSBox_PlaneEnd_A->setMinimum(-180.000000000000000);
        DSBox_PlaneEnd_A->setMaximum(180.000000000000000);
        DSBox_PlaneEnd_A->setValue(120.000000000000000);

        horizontalLayout_18->addWidget(DSBox_PlaneEnd_A);


        verticalLayout_5->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_PlaneEnd_B = new QLabel(groupBox_7);
        label_PlaneEnd_B->setObjectName(QString::fromUtf8("label_PlaneEnd_B"));
        label_PlaneEnd_B->setMinimumSize(QSize(12, 0));
        label_PlaneEnd_B->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_19->addWidget(label_PlaneEnd_B);

        DSBox_PlaneEnd_B = new QDoubleSpinBox(groupBox_7);
        DSBox_PlaneEnd_B->setObjectName(QString::fromUtf8("DSBox_PlaneEnd_B"));
        DSBox_PlaneEnd_B->setEnabled(false);
        DSBox_PlaneEnd_B->setMaximum(200.000000000000000);
        DSBox_PlaneEnd_B->setValue(120.000000000000000);

        horizontalLayout_19->addWidget(DSBox_PlaneEnd_B);


        verticalLayout_5->addLayout(horizontalLayout_19);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_PlaneEnd_R = new QLabel(groupBox_7);
        label_PlaneEnd_R->setObjectName(QString::fromUtf8("label_PlaneEnd_R"));
        label_PlaneEnd_R->setMinimumSize(QSize(12, 0));
        label_PlaneEnd_R->setMaximumSize(QSize(12, 16777215));

        horizontalLayout_21->addWidget(label_PlaneEnd_R);

        DSBox_PlaneEnd_R = new QDoubleSpinBox(groupBox_7);
        DSBox_PlaneEnd_R->setObjectName(QString::fromUtf8("DSBox_PlaneEnd_R"));
        DSBox_PlaneEnd_R->setEnabled(false);
        DSBox_PlaneEnd_R->setMinimum(-200.000000000000000);
        DSBox_PlaneEnd_R->setMaximum(200.000000000000000);
        DSBox_PlaneEnd_R->setValue(120.000000000000000);

        horizontalLayout_21->addWidget(DSBox_PlaneEnd_R);


        verticalLayout_5->addLayout(horizontalLayout_21);


        horizontalLayout_6->addWidget(groupBox_7);


        verticalLayout_6->addLayout(horizontalLayout_6);

        tabWidget_3 = new QTabWidget(tab_3);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget_3->sizePolicy().hasHeightForWidth());
        tabWidget_3->setSizePolicy(sizePolicy);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_2 = new QVBoxLayout(tab_5);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_Interval_Cr_Radius = new QLabel(tab_5);
        label_Interval_Cr_Radius->setObjectName(QString::fromUtf8("label_Interval_Cr_Radius"));

        horizontalLayout_8->addWidget(label_Interval_Cr_Radius);

        DSBox_Interval_Cr_Radius = new QDoubleSpinBox(tab_5);
        DSBox_Interval_Cr_Radius->setObjectName(QString::fromUtf8("DSBox_Interval_Cr_Radius"));
        DSBox_Interval_Cr_Radius->setEnabled(false);
        DSBox_Interval_Cr_Radius->setMaximum(360.000000000000000);
        DSBox_Interval_Cr_Radius->setValue(2.000000000000000);

        horizontalLayout_8->addWidget(DSBox_Interval_Cr_Radius);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_Interval_Cr_L = new QLabel(tab_5);
        label_Interval_Cr_L->setObjectName(QString::fromUtf8("label_Interval_Cr_L"));

        horizontalLayout_10->addWidget(label_Interval_Cr_L);

        DSBox_Interval_Cr_L = new QDoubleSpinBox(tab_5);
        DSBox_Interval_Cr_L->setObjectName(QString::fromUtf8("DSBox_Interval_Cr_L"));
        DSBox_Interval_Cr_L->setEnabled(false);
        DSBox_Interval_Cr_L->setMaximum(360.000000000000000);
        DSBox_Interval_Cr_L->setValue(2.000000000000000);

        horizontalLayout_10->addWidget(DSBox_Interval_Cr_L);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_Interval_Cr_AB = new QLabel(tab_5);
        label_Interval_Cr_AB->setObjectName(QString::fromUtf8("label_Interval_Cr_AB"));

        horizontalLayout_11->addWidget(label_Interval_Cr_AB);

        DSBox_Interval_Cr_AB = new QDoubleSpinBox(tab_5);
        DSBox_Interval_Cr_AB->setObjectName(QString::fromUtf8("DSBox_Interval_Cr_AB"));
        DSBox_Interval_Cr_AB->setEnabled(false);
        DSBox_Interval_Cr_AB->setMaximum(360.000000000000000);
        DSBox_Interval_Cr_AB->setValue(2.000000000000000);

        horizontalLayout_11->addWidget(DSBox_Interval_Cr_AB);


        verticalLayout_2->addLayout(horizontalLayout_11);

        tabWidget_3->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_3 = new QVBoxLayout(tab_6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_Interval_Grid_Radius = new QLabel(tab_6);
        label_Interval_Grid_Radius->setObjectName(QString::fromUtf8("label_Interval_Grid_Radius"));

        horizontalLayout_13->addWidget(label_Interval_Grid_Radius);

        DSBox_Interval_Grid_Radius = new QDoubleSpinBox(tab_6);
        DSBox_Interval_Grid_Radius->setObjectName(QString::fromUtf8("DSBox_Interval_Grid_Radius"));
        DSBox_Interval_Grid_Radius->setEnabled(false);
        DSBox_Interval_Grid_Radius->setMaximum(360.000000000000000);
        DSBox_Interval_Grid_Radius->setValue(20.000000000000000);

        horizontalLayout_13->addWidget(DSBox_Interval_Grid_Radius);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_Interval_Grid_L = new QLabel(tab_6);
        label_Interval_Grid_L->setObjectName(QString::fromUtf8("label_Interval_Grid_L"));

        horizontalLayout_25->addWidget(label_Interval_Grid_L);

        DSBox_Interval_Grid_L = new QDoubleSpinBox(tab_6);
        DSBox_Interval_Grid_L->setObjectName(QString::fromUtf8("DSBox_Interval_Grid_L"));
        DSBox_Interval_Grid_L->setEnabled(false);
        DSBox_Interval_Grid_L->setMaximum(360.000000000000000);
        DSBox_Interval_Grid_L->setValue(20.000000000000000);

        horizontalLayout_25->addWidget(DSBox_Interval_Grid_L);


        verticalLayout_3->addLayout(horizontalLayout_25);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_Interval_Grid_AB = new QLabel(tab_6);
        label_Interval_Grid_AB->setObjectName(QString::fromUtf8("label_Interval_Grid_AB"));

        horizontalLayout_12->addWidget(label_Interval_Grid_AB);

        DSBox_Interval_Grid_AB = new QDoubleSpinBox(tab_6);
        DSBox_Interval_Grid_AB->setObjectName(QString::fromUtf8("DSBox_Interval_Grid_AB"));
        DSBox_Interval_Grid_AB->setEnabled(false);
        DSBox_Interval_Grid_AB->setMaximum(360.000000000000000);
        DSBox_Interval_Grid_AB->setValue(20.000000000000000);

        horizontalLayout_12->addWidget(DSBox_Interval_Grid_AB);


        verticalLayout_3->addLayout(horizontalLayout_12);

        tabWidget_3->addTab(tab_6, QString());

        verticalLayout_6->addWidget(tabWidget_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox_drawAxis = new QCheckBox(tab_3);
        checkBox_drawAxis->setObjectName(QString::fromUtf8("checkBox_drawAxis"));
        checkBox_drawAxis->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_drawAxis);

        checkBox_drawGrid = new QCheckBox(tab_3);
        checkBox_drawGrid->setObjectName(QString::fromUtf8("checkBox_drawGrid"));
        checkBox_drawGrid->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_drawGrid);


        verticalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_CrRectWidth = new QLabel(tab_3);
        label_CrRectWidth->setObjectName(QString::fromUtf8("label_CrRectWidth"));

        horizontalLayout_5->addWidget(label_CrRectWidth);

        SBox_CrRectWidth = new QSpinBox(tab_3);
        SBox_CrRectWidth->setObjectName(QString::fromUtf8("SBox_CrRectWidth"));
        SBox_CrRectWidth->setValue(2);
        SBox_CrRectWidth->setDisplayIntegerBase(10);

        horizontalLayout_5->addWidget(SBox_CrRectWidth);


        verticalLayout_6->addLayout(horizontalLayout_5);

        label_CaculateRectCount = new QLabel(tab_3);
        label_CaculateRectCount->setObjectName(QString::fromUtf8("label_CaculateRectCount"));

        verticalLayout_6->addWidget(label_CaculateRectCount);

        label_ValidRectCount = new QLabel(tab_3);
        label_ValidRectCount->setObjectName(QString::fromUtf8("label_ValidRectCount"));

        verticalLayout_6->addWidget(label_ValidRectCount);

        label_CrGenState = new QLabel(tab_3);
        label_CrGenState->setObjectName(QString::fromUtf8("label_CrGenState"));

        verticalLayout_6->addWidget(label_CrGenState);

        progressBar_RectGenState = new QProgressBar(tab_3);
        progressBar_RectGenState->setObjectName(QString::fromUtf8("progressBar_RectGenState"));
        progressBar_RectGenState->setValue(0);

        verticalLayout_6->addWidget(progressBar_RectGenState);

        btn_updateChtOnly = new QPushButton(tab_3);
        btn_updateChtOnly->setObjectName(QString::fromUtf8("btn_updateChtOnly"));

        verticalLayout_6->addWidget(btn_updateChtOnly);

        btn_GenLABDistribute = new QPushButton(tab_3);
        btn_GenLABDistribute->setObjectName(QString::fromUtf8("btn_GenLABDistribute"));

        verticalLayout_6->addWidget(btn_GenLABDistribute);

        verticalSpacer = new QSpacerItem(20, 156, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        tabWidget_2->addTab(tab_3, QString());

        horizontalLayout_2->addWidget(tabWidget_2);

        tabWidget_main->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_26 = new QHBoxLayout(tab_2);
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        groupBox_8 = new QGroupBox(tab_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        HLayout_ImagePainter = new QHBoxLayout(groupBox_8);
        HLayout_ImagePainter->setSpacing(6);
        HLayout_ImagePainter->setContentsMargins(11, 11, 11, 11);
        HLayout_ImagePainter->setObjectName(QString::fromUtf8("HLayout_ImagePainter"));

        horizontalLayout_26->addWidget(groupBox_8);

        widget = new QWidget(tab_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(240, 16777215));
        verticalLayout_11 = new QVBoxLayout(widget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_selImg = new QLabel(widget);
        label_selImg->setObjectName(QString::fromUtf8("label_selImg"));
        label_selImg->setMinimumSize(QSize(64, 0));
        label_selImg->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_27->addWidget(label_selImg);

        comboBox_selImg = new QComboBox(widget);
        comboBox_selImg->setObjectName(QString::fromUtf8("comboBox_selImg"));

        horizontalLayout_27->addWidget(comboBox_selImg);


        verticalLayout_11->addLayout(horizontalLayout_27);

        btn_LoadImg = new QPushButton(widget);
        btn_LoadImg->setObjectName(QString::fromUtf8("btn_LoadImg"));

        verticalLayout_11->addWidget(btn_LoadImg);

        checkBox_autoLabTransfer = new QCheckBox(widget);
        checkBox_autoLabTransfer->setObjectName(QString::fromUtf8("checkBox_autoLabTransfer"));
        checkBox_autoLabTransfer->setChecked(true);

        verticalLayout_11->addWidget(checkBox_autoLabTransfer);

        groupBox_selFileTag_2 = new QGroupBox(widget);
        groupBox_selFileTag_2->setObjectName(QString::fromUtf8("groupBox_selFileTag_2"));
        verticalLayout_12 = new QVBoxLayout(groupBox_selFileTag_2);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        label_Img_FileName = new QLabel(groupBox_selFileTag_2);
        label_Img_FileName->setObjectName(QString::fromUtf8("label_Img_FileName"));

        verticalLayout_12->addWidget(label_Img_FileName);

        line = new QFrame(groupBox_selFileTag_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line);

        label_img_Size = new QLabel(groupBox_selFileTag_2);
        label_img_Size->setObjectName(QString::fromUtf8("label_img_Size"));

        verticalLayout_12->addWidget(label_img_Size);

        label_Img_CrDepth = new QLabel(groupBox_selFileTag_2);
        label_Img_CrDepth->setObjectName(QString::fromUtf8("label_Img_CrDepth"));

        verticalLayout_12->addWidget(label_Img_CrDepth);

        label_Img_CrFormat = new QLabel(groupBox_selFileTag_2);
        label_Img_CrFormat->setObjectName(QString::fromUtf8("label_Img_CrFormat"));

        verticalLayout_12->addWidget(label_Img_CrFormat);


        verticalLayout_11->addWidget(groupBox_selFileTag_2);

        label_transferState = new QLabel(widget);
        label_transferState->setObjectName(QString::fromUtf8("label_transferState"));

        verticalLayout_11->addWidget(label_transferState);

        progressBar_transferState = new QProgressBar(widget);
        progressBar_transferState->setObjectName(QString::fromUtf8("progressBar_transferState"));
        progressBar_transferState->setValue(0);

        verticalLayout_11->addWidget(progressBar_transferState);

        btn_transferImg = new QPushButton(widget);
        btn_transferImg->setObjectName(QString::fromUtf8("btn_transferImg"));

        verticalLayout_11->addWidget(btn_transferImg);

        groupBox_CrMode = new QGroupBox(widget);
        groupBox_CrMode->setObjectName(QString::fromUtf8("groupBox_CrMode"));
        horizontalLayout_28 = new QHBoxLayout(groupBox_CrMode);
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        radioButton_CrMode_RGB = new QRadioButton(groupBox_CrMode);
        radioButton_CrMode_RGB->setObjectName(QString::fromUtf8("radioButton_CrMode_RGB"));
        radioButton_CrMode_RGB->setChecked(true);

        horizontalLayout_28->addWidget(radioButton_CrMode_RGB);

        radioButton_CrMode_LAB_L = new QRadioButton(groupBox_CrMode);
        radioButton_CrMode_LAB_L->setObjectName(QString::fromUtf8("radioButton_CrMode_LAB_L"));

        horizontalLayout_28->addWidget(radioButton_CrMode_LAB_L);


        verticalLayout_11->addWidget(groupBox_CrMode);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_3);


        horizontalLayout_26->addWidget(widget);

        tabWidget_main->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget_main);


        retranslateUi(ColorMetricWidgetClass);

        tabWidget_main->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        tabWidget_3->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ColorMetricWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ColorMetricWidgetClass)
    {
        ColorMetricWidgetClass->setWindowTitle(QApplication::translate("ColorMetricWidgetClass", "ColorMetricWidget", nullptr));
        groupBox->setTitle(QApplication::translate("ColorMetricWidgetClass", "LAB\345\233\276\345\203\217", nullptr));
        groupBox_2->setTitle(QApplication::translate("ColorMetricWidgetClass", "\350\211\262\345\275\251", nullptr));
        groupBox_3->setTitle(QApplication::translate("ColorMetricWidgetClass", "\351\274\240\346\240\207", nullptr));
        groupBox_4->setTitle(QApplication::translate("ColorMetricWidgetClass", "\345\275\223\345\211\215", nullptr));
        label_MousePos_Current_Lab->setText(QApplication::translate("ColorMetricWidgetClass", "LAB:", nullptr));
        label_MousePos_Current_XYZ->setText(QApplication::translate("ColorMetricWidgetClass", "XYZ:", nullptr));
        label_MousePos_Current_sRgbGamma->setText(QApplication::translate("ColorMetricWidgetClass", "sRgbGamma:", nullptr));
        label_MousePos_Current_sRgb->setText(QApplication::translate("ColorMetricWidgetClass", "sRgb:", nullptr));
        label_MousePos_Current_Cr255->setText(QApplication::translate("ColorMetricWidgetClass", "QColor:", nullptr));
        label_MousePos_Current_CrPaint->setText(QString());
        label_MousePos_CurrentToPress->setText(QApplication::translate("ColorMetricWidgetClass", "<-", nullptr));
        label_MousePos_Press_CrPaint->setText(QString());
        groupBox_5->setTitle(QApplication::translate("ColorMetricWidgetClass", "\347\202\271\345\207\273", nullptr));
        label_MousePos_Press_Lab->setText(QApplication::translate("ColorMetricWidgetClass", "LAB:", nullptr));
        label_MousePos_Press_XYZ->setText(QApplication::translate("ColorMetricWidgetClass", "XYZ:", nullptr));
        label_MousePos_Press_sRgbGamma->setText(QApplication::translate("ColorMetricWidgetClass", "sRgbGamma:", nullptr));
        label_MousePos_Press_sRgb->setText(QApplication::translate("ColorMetricWidgetClass", "sRgb:", nullptr));
        label_MousePos_Press_Cr255->setText(QApplication::translate("ColorMetricWidgetClass", "QColor:", nullptr));
        groupBox_6->setTitle(QApplication::translate("ColorMetricWidgetClass", "\345\272\246\351\207\217", nullptr));
        label_CrMetric_RGB_255->setText(QApplication::translate("ColorMetricWidgetClass", "RGB_255 :", nullptr));
        label_CrMetric_LAB_1976->setText(QApplication::translate("ColorMetricWidgetClass", "LAB_1976:", nullptr));
        label_CrMetric_LAB_1984->setText(QApplication::translate("ColorMetricWidgetClass", "LAB_1984:", nullptr));
        label_CrMetric_LAB_1994->setText(QApplication::translate("ColorMetricWidgetClass", "LAB_1994:", nullptr));
        label_CrMetric_LAB_2000->setText(QApplication::translate("ColorMetricWidgetClass", "LAB_2000:", nullptr));
        groupBox_AxiSet->setTitle(QApplication::translate("ColorMetricWidgetClass", "\345\235\220\346\240\207\347\263\273", nullptr));
        radioButton_Axi_Fix_L->setText(QApplication::translate("ColorMetricWidgetClass", "\345\233\272\345\256\232\344\272\256\345\272\246", nullptr));
        radioButton_Axi_Fix_R->setText(QApplication::translate("ColorMetricWidgetClass", "\345\233\272\345\256\232AB\346\226\271\345\220\221", nullptr));
        radioButton_Axi_Interval_pixel->setText(QApplication::translate("ColorMetricWidgetClass", "\345\257\206\351\223\272\345\203\217\347\264\240", nullptr));
        radioButton_Axi_Interval_Density->setText(QApplication::translate("ColorMetricWidgetClass", "\351\227\264\351\232\224\350\211\262\345\235\227", nullptr));
        checkBox_GammaExist->setText(QApplication::translate("ColorMetricWidgetClass", "Gamma\346\230\240\345\260\204", nullptr));
        groupBox_PlaneStartPos->setTitle(QApplication::translate("ColorMetricWidgetClass", "\350\265\267\345\247\213/\345\233\272\345\256\232\344\275\215\347\275\256", nullptr));
        label_PlaneStart_L->setText(QApplication::translate("ColorMetricWidgetClass", "L", nullptr));
        label_PlaneStart_A->setText(QApplication::translate("ColorMetricWidgetClass", "A", nullptr));
        label_PlaneStart_B->setText(QApplication::translate("ColorMetricWidgetClass", "B", nullptr));
        label_PlaneStart_R->setText(QApplication::translate("ColorMetricWidgetClass", "R", nullptr));
        groupBox_7->setTitle(QApplication::translate("ColorMetricWidgetClass", "\347\273\223\346\235\237\344\275\215\347\275\256", nullptr));
        label_PlaneEnd_L->setText(QApplication::translate("ColorMetricWidgetClass", "L", nullptr));
        label_PlaneEnd_A->setText(QApplication::translate("ColorMetricWidgetClass", "A", nullptr));
        label_PlaneEnd_B->setText(QApplication::translate("ColorMetricWidgetClass", "B", nullptr));
        label_PlaneEnd_R->setText(QApplication::translate("ColorMetricWidgetClass", "R", nullptr));
        label_Interval_Cr_Radius->setText(QApplication::translate("ColorMetricWidgetClass", "\345\276\204\345\220\221\351\227\264\351\232\224\357\274\210r\357\274\211", nullptr));
        label_Interval_Cr_L->setText(QApplication::translate("ColorMetricWidgetClass", "\344\272\256\345\272\246\351\227\264\351\232\224(\316\224L)", nullptr));
        label_Interval_Cr_AB->setText(QApplication::translate("ColorMetricWidgetClass", "\350\211\262\347\233\270\351\227\264\351\232\224\357\274\210AB\357\274\211", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_5), QApplication::translate("ColorMetricWidgetClass", "\351\242\234\350\211\262\345\257\206\345\272\246", nullptr));
        label_Interval_Grid_Radius->setText(QApplication::translate("ColorMetricWidgetClass", "\345\276\204\345\220\221\351\227\264\351\232\224\357\274\210r\357\274\211", nullptr));
        label_Interval_Grid_L->setText(QApplication::translate("ColorMetricWidgetClass", "\344\272\256\345\272\246\351\227\264\351\232\224(\316\224L)", nullptr));
        label_Interval_Grid_AB->setText(QApplication::translate("ColorMetricWidgetClass", "\350\211\262\347\233\270\351\227\264\351\232\224\357\274\210AB\357\274\211", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_6), QApplication::translate("ColorMetricWidgetClass", "\347\275\221\346\240\274\345\257\206\345\272\246", nullptr));
        checkBox_drawAxis->setText(QApplication::translate("ColorMetricWidgetClass", "\347\273\230\345\210\266\345\235\220\346\240\207\347\263\273", nullptr));
        checkBox_drawGrid->setText(QApplication::translate("ColorMetricWidgetClass", "\347\273\230\345\210\266\347\275\221\346\240\274\347\272\277", nullptr));
        label_CrRectWidth->setText(QApplication::translate("ColorMetricWidgetClass", "\350\211\262\345\235\227\345\256\275\345\272\246\357\274\210\345\203\217\347\264\240\357\274\211", nullptr));
        label_CaculateRectCount->setText(QApplication::translate("ColorMetricWidgetClass", "\350\256\241\347\256\227\350\211\262\345\235\227\346\225\260\351\207\217\357\274\232", nullptr));
        label_ValidRectCount->setText(QApplication::translate("ColorMetricWidgetClass", "\346\234\211\346\225\210\350\211\262\345\235\227\346\225\260\351\207\217\357\274\232", nullptr));
        label_CrGenState->setText(QApplication::translate("ColorMetricWidgetClass", "\347\224\237\346\210\220\347\212\266\346\200\201\357\274\232", nullptr));
        btn_updateChtOnly->setText(QApplication::translate("ColorMetricWidgetClass", "\344\273\205\345\210\267\346\226\260\345\233\276\350\241\250", nullptr));
        btn_GenLABDistribute->setText(QApplication::translate("ColorMetricWidgetClass", "\351\207\215\346\226\260\347\224\237\346\210\220\350\211\262\345\235\227", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("ColorMetricWidgetClass", "LAB\351\242\234\350\211\262\345\210\206\345\270\203", nullptr));
        tabWidget_main->setTabText(tabWidget_main->indexOf(tab), QApplication::translate("ColorMetricWidgetClass", "CIE_LAB\357\274\210D65\357\274\211", nullptr));
        groupBox_8->setTitle(QApplication::translate("ColorMetricWidgetClass", "\350\247\206\350\247\211\345\244\204\347\220\206\345\233\276\345\203\217", nullptr));
        label_selImg->setText(QApplication::translate("ColorMetricWidgetClass", "\345\257\274\345\205\245\345\233\276\347\211\207:", nullptr));
        btn_LoadImg->setText(QApplication::translate("ColorMetricWidgetClass", "\345\257\274\345\205\245\345\233\276\347\211\207", nullptr));
        checkBox_autoLabTransfer->setText(QApplication::translate("ColorMetricWidgetClass", "\350\207\252\345\212\250LAB\350\275\254\346\215\242", nullptr));
        groupBox_selFileTag_2->setTitle(QApplication::translate("ColorMetricWidgetClass", "\346\226\207\344\273\266\346\240\207\347\255\276", nullptr));
        label_Img_FileName->setText(QApplication::translate("ColorMetricWidgetClass", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_img_Size->setText(QApplication::translate("ColorMetricWidgetClass", "\345\233\276\345\203\217\345\260\272\345\257\270\357\274\232", nullptr));
        label_Img_CrDepth->setText(QApplication::translate("ColorMetricWidgetClass", "\351\242\234\350\211\262\346\267\261\345\272\246\357\274\232", nullptr));
        label_Img_CrFormat->setText(QApplication::translate("ColorMetricWidgetClass", "\351\242\234\350\211\262\346\240\274\345\274\217\357\274\232", nullptr));
        label_transferState->setText(QApplication::translate("ColorMetricWidgetClass", "\350\275\254\346\215\242\347\212\266\346\200\201:", nullptr));
        btn_transferImg->setText(QApplication::translate("ColorMetricWidgetClass", "\345\274\200\345\247\213\350\275\254\346\215\242", nullptr));
        groupBox_CrMode->setTitle(QApplication::translate("ColorMetricWidgetClass", "\351\242\234\350\211\262\346\250\241\345\274\217", nullptr));
        radioButton_CrMode_RGB->setText(QApplication::translate("ColorMetricWidgetClass", "RGB", nullptr));
        radioButton_CrMode_LAB_L->setText(QApplication::translate("ColorMetricWidgetClass", "lAB_L", nullptr));
        tabWidget_main->setTabText(tabWidget_main->indexOf(tab_2), QApplication::translate("ColorMetricWidgetClass", "\347\273\235\345\257\271\350\211\262\345\235\227\345\210\206\345\211\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorMetricWidgetClass: public Ui_ColorMetricWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORMETRICWIDGET_H
