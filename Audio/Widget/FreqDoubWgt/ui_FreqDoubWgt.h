/********************************************************************************
** Form generated from reading UI file 'FreqDoubWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREQDOUBWGT_H
#define UI_FREQDOUBWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FreqDoubWgtClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *mainTabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *HLayout_Cht_FreqDoubDistribute;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QHBoxLayout *HLayout_Cht_FreqDoubCount;
    QWidget *tab_4;
    QWidget *widget_panel;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_SampleRate;
    QSpinBox *SBox_SampleRate;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_WndPtCount;
    QSpinBox *SBox_WndPtCount;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_MaxEffectFreq;
    QSpinBox *SBox_MaxEffectFreq;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_WndSpecConstrainFreqDriftRatio;
    QDoubleSpinBox *DSBox_WndSpecConstrainFreqDriftRatio;
    QTabWidget *tabWidget_3;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_TensorEndFreq;
    QDoubleSpinBox *DSBox_TensorEndFreq;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_ParentMatrixIncludeMainFreqCount;
    QSpinBox *SBox_ParentMatrixIncludeMainFreqCount;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_MaxMultiTime;
    QSpinBox *SBox_MaxMultiTime;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_TensorStartFreq;
    QDoubleSpinBox *DSBox_TensorStartFreq;
    QCheckBox *checkBox_cutOffOnOverLappingStartPos;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_TensorResult_StartFreq;
    QLabel *label_TensorResult_EndFreq;
    QLabel *label_TensorResult_MatrixCount;
    QLabel *label_TensorResult_MatrixFreqInterval;
    QCheckBox *checkBox_UpdateChtAfterGetTensor;
    QLabel *label_tensorGenState;
    QProgressBar *progressBar_TensorGenState;
    QPushButton *btn_GenTensor;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_Cht_ShowMatricFreq;
    QSpinBox *SBox_Cht_ShowMatricFreq;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_Cht_ShowMultipleTime;
    QSpinBox *SBox_Cht_ShowMultipleTime;
    QLabel *label_cht_IsMatrixInsertFreq;
    QLabel *label_Cht_ShowFreqPtIndex;
    QLabel *label_Cht_ShowFreq;
    QLabel *label_Cht_ShowMatricMaxMultTime;
    QLabel *label_Cht_selfOverlappintStartMultiTime;
    QPushButton *btn_updateTensorCht;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *VLayout_ChtPanel;

    void setupUi(QWidget *FreqDoubWgtClass)
    {
        if (FreqDoubWgtClass->objectName().isEmpty())
            FreqDoubWgtClass->setObjectName(QString::fromUtf8("FreqDoubWgtClass"));
        FreqDoubWgtClass->resize(1257, 903);
        verticalLayout = new QVBoxLayout(FreqDoubWgtClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainTabWidget = new QTabWidget(FreqDoubWgtClass);
        mainTabWidget->setObjectName(QString::fromUtf8("mainTabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_8 = new QHBoxLayout(tab);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        HLayout_Cht_FreqDoubDistribute = new QHBoxLayout(groupBox);
        HLayout_Cht_FreqDoubDistribute->setSpacing(6);
        HLayout_Cht_FreqDoubDistribute->setContentsMargins(11, 11, 11, 11);
        HLayout_Cht_FreqDoubDistribute->setObjectName(QString::fromUtf8("HLayout_Cht_FreqDoubDistribute"));

        verticalLayout_4->addWidget(groupBox);

        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget_2->sizePolicy().hasHeightForWidth());
        tabWidget_2->setSizePolicy(sizePolicy);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        HLayout_Cht_FreqDoubCount = new QHBoxLayout(tab_3);
        HLayout_Cht_FreqDoubCount->setSpacing(6);
        HLayout_Cht_FreqDoubCount->setContentsMargins(11, 11, 11, 11);
        HLayout_Cht_FreqDoubCount->setObjectName(QString::fromUtf8("HLayout_Cht_FreqDoubCount"));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget_2->addTab(tab_4, QString());

        verticalLayout_4->addWidget(tabWidget_2);


        horizontalLayout_8->addLayout(verticalLayout_4);

        widget_panel = new QWidget(tab);
        widget_panel->setObjectName(QString::fromUtf8("widget_panel"));
        widget_panel->setMaximumSize(QSize(260, 16777215));
        verticalLayout_5 = new QVBoxLayout(widget_panel);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_3 = new QGroupBox(widget_panel);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_SampleRate = new QLabel(groupBox_3);
        label_SampleRate->setObjectName(QString::fromUtf8("label_SampleRate"));

        horizontalLayout->addWidget(label_SampleRate);

        SBox_SampleRate = new QSpinBox(groupBox_3);
        SBox_SampleRate->setObjectName(QString::fromUtf8("SBox_SampleRate"));
        SBox_SampleRate->setMinimumSize(QSize(72, 0));
        SBox_SampleRate->setMaximumSize(QSize(72, 16777215));
        SBox_SampleRate->setMaximum(96000);
        SBox_SampleRate->setValue(44100);

        horizontalLayout->addWidget(SBox_SampleRate);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_WndPtCount = new QLabel(groupBox_3);
        label_WndPtCount->setObjectName(QString::fromUtf8("label_WndPtCount"));

        horizontalLayout_2->addWidget(label_WndPtCount);

        SBox_WndPtCount = new QSpinBox(groupBox_3);
        SBox_WndPtCount->setObjectName(QString::fromUtf8("SBox_WndPtCount"));
        SBox_WndPtCount->setMinimumSize(QSize(72, 0));
        SBox_WndPtCount->setMaximumSize(QSize(72, 16777215));
        SBox_WndPtCount->setMaximum(9192);
        SBox_WndPtCount->setValue(4096);

        horizontalLayout_2->addWidget(SBox_WndPtCount);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_MaxEffectFreq = new QLabel(groupBox_3);
        label_MaxEffectFreq->setObjectName(QString::fromUtf8("label_MaxEffectFreq"));

        horizontalLayout_3->addWidget(label_MaxEffectFreq);

        SBox_MaxEffectFreq = new QSpinBox(groupBox_3);
        SBox_MaxEffectFreq->setObjectName(QString::fromUtf8("SBox_MaxEffectFreq"));
        SBox_MaxEffectFreq->setMinimumSize(QSize(72, 0));
        SBox_MaxEffectFreq->setMaximumSize(QSize(72, 16777215));
        SBox_MaxEffectFreq->setMaximum(22100);
        SBox_MaxEffectFreq->setValue(20000);

        horizontalLayout_3->addWidget(SBox_MaxEffectFreq);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_WndSpecConstrainFreqDriftRatio = new QLabel(groupBox_3);
        label_WndSpecConstrainFreqDriftRatio->setObjectName(QString::fromUtf8("label_WndSpecConstrainFreqDriftRatio"));

        horizontalLayout_7->addWidget(label_WndSpecConstrainFreqDriftRatio);

        DSBox_WndSpecConstrainFreqDriftRatio = new QDoubleSpinBox(groupBox_3);
        DSBox_WndSpecConstrainFreqDriftRatio->setObjectName(QString::fromUtf8("DSBox_WndSpecConstrainFreqDriftRatio"));
        DSBox_WndSpecConstrainFreqDriftRatio->setMinimumSize(QSize(72, 0));
        DSBox_WndSpecConstrainFreqDriftRatio->setMaximumSize(QSize(72, 16777215));
        DSBox_WndSpecConstrainFreqDriftRatio->setMaximum(50.000000000000000);
        DSBox_WndSpecConstrainFreqDriftRatio->setValue(25.000000000000000);

        horizontalLayout_7->addWidget(DSBox_WndSpecConstrainFreqDriftRatio);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_5->addWidget(groupBox_3);

        tabWidget_3 = new QTabWidget(widget_panel);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_3->sizePolicy().hasHeightForWidth());
        tabWidget_3->setSizePolicy(sizePolicy1);
        tabWidget_3->setTabBarAutoHide(false);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_7 = new QVBoxLayout(tab_5);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_TensorEndFreq = new QLabel(tab_5);
        label_TensorEndFreq->setObjectName(QString::fromUtf8("label_TensorEndFreq"));

        horizontalLayout_6->addWidget(label_TensorEndFreq);

        DSBox_TensorEndFreq = new QDoubleSpinBox(tab_5);
        DSBox_TensorEndFreq->setObjectName(QString::fromUtf8("DSBox_TensorEndFreq"));
        DSBox_TensorEndFreq->setMinimumSize(QSize(72, 0));
        DSBox_TensorEndFreq->setMaximumSize(QSize(72, 16777215));
        DSBox_TensorEndFreq->setDecimals(3);
        DSBox_TensorEndFreq->setMaximum(20000.000000000000000);
        DSBox_TensorEndFreq->setValue(4186.009000000000015);

        horizontalLayout_6->addWidget(DSBox_TensorEndFreq);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_ParentMatrixIncludeMainFreqCount = new QLabel(tab_5);
        label_ParentMatrixIncludeMainFreqCount->setObjectName(QString::fromUtf8("label_ParentMatrixIncludeMainFreqCount"));

        horizontalLayout_10->addWidget(label_ParentMatrixIncludeMainFreqCount);

        SBox_ParentMatrixIncludeMainFreqCount = new QSpinBox(tab_5);
        SBox_ParentMatrixIncludeMainFreqCount->setObjectName(QString::fromUtf8("SBox_ParentMatrixIncludeMainFreqCount"));
        SBox_ParentMatrixIncludeMainFreqCount->setMinimumSize(QSize(72, 0));
        SBox_ParentMatrixIncludeMainFreqCount->setMaximumSize(QSize(72, 16777215));
        SBox_ParentMatrixIncludeMainFreqCount->setMinimum(1);
        SBox_ParentMatrixIncludeMainFreqCount->setValue(3);

        horizontalLayout_10->addWidget(SBox_ParentMatrixIncludeMainFreqCount);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_MaxMultiTime = new QLabel(tab_5);
        label_MaxMultiTime->setObjectName(QString::fromUtf8("label_MaxMultiTime"));

        horizontalLayout_5->addWidget(label_MaxMultiTime);

        SBox_MaxMultiTime = new QSpinBox(tab_5);
        SBox_MaxMultiTime->setObjectName(QString::fromUtf8("SBox_MaxMultiTime"));
        SBox_MaxMultiTime->setMinimumSize(QSize(72, 0));
        SBox_MaxMultiTime->setMaximumSize(QSize(72, 16777215));
        SBox_MaxMultiTime->setMinimum(1);
        SBox_MaxMultiTime->setValue(50);

        horizontalLayout_5->addWidget(SBox_MaxMultiTime);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_TensorStartFreq = new QLabel(tab_5);
        label_TensorStartFreq->setObjectName(QString::fromUtf8("label_TensorStartFreq"));

        horizontalLayout_4->addWidget(label_TensorStartFreq);

        DSBox_TensorStartFreq = new QDoubleSpinBox(tab_5);
        DSBox_TensorStartFreq->setObjectName(QString::fromUtf8("DSBox_TensorStartFreq"));
        DSBox_TensorStartFreq->setMinimumSize(QSize(72, 0));
        DSBox_TensorStartFreq->setMaximumSize(QSize(72, 16777215));
        DSBox_TensorStartFreq->setDecimals(3);
        DSBox_TensorStartFreq->setMaximum(20000.000000000000000);
        DSBox_TensorStartFreq->setValue(65.406000000000006);

        horizontalLayout_4->addWidget(DSBox_TensorStartFreq);


        verticalLayout_7->addLayout(horizontalLayout_4);

        checkBox_cutOffOnOverLappingStartPos = new QCheckBox(tab_5);
        checkBox_cutOffOnOverLappingStartPos->setObjectName(QString::fromUtf8("checkBox_cutOffOnOverLappingStartPos"));
        checkBox_cutOffOnOverLappingStartPos->setChecked(true);

        verticalLayout_7->addWidget(checkBox_cutOffOnOverLappingStartPos);

        tabWidget_3->addTab(tab_5, QString());

        verticalLayout_5->addWidget(tabWidget_3);

        groupBox_2 = new QGroupBox(widget_panel);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 0));
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_TensorResult_StartFreq = new QLabel(groupBox_2);
        label_TensorResult_StartFreq->setObjectName(QString::fromUtf8("label_TensorResult_StartFreq"));

        verticalLayout_6->addWidget(label_TensorResult_StartFreq);

        label_TensorResult_EndFreq = new QLabel(groupBox_2);
        label_TensorResult_EndFreq->setObjectName(QString::fromUtf8("label_TensorResult_EndFreq"));

        verticalLayout_6->addWidget(label_TensorResult_EndFreq);

        label_TensorResult_MatrixCount = new QLabel(groupBox_2);
        label_TensorResult_MatrixCount->setObjectName(QString::fromUtf8("label_TensorResult_MatrixCount"));

        verticalLayout_6->addWidget(label_TensorResult_MatrixCount);

        label_TensorResult_MatrixFreqInterval = new QLabel(groupBox_2);
        label_TensorResult_MatrixFreqInterval->setObjectName(QString::fromUtf8("label_TensorResult_MatrixFreqInterval"));

        verticalLayout_6->addWidget(label_TensorResult_MatrixFreqInterval);


        verticalLayout_5->addWidget(groupBox_2);

        checkBox_UpdateChtAfterGetTensor = new QCheckBox(widget_panel);
        checkBox_UpdateChtAfterGetTensor->setObjectName(QString::fromUtf8("checkBox_UpdateChtAfterGetTensor"));
        checkBox_UpdateChtAfterGetTensor->setChecked(true);

        verticalLayout_5->addWidget(checkBox_UpdateChtAfterGetTensor);

        label_tensorGenState = new QLabel(widget_panel);
        label_tensorGenState->setObjectName(QString::fromUtf8("label_tensorGenState"));

        verticalLayout_5->addWidget(label_tensorGenState);

        progressBar_TensorGenState = new QProgressBar(widget_panel);
        progressBar_TensorGenState->setObjectName(QString::fromUtf8("progressBar_TensorGenState"));
        progressBar_TensorGenState->setValue(24);

        verticalLayout_5->addWidget(progressBar_TensorGenState);

        btn_GenTensor = new QPushButton(widget_panel);
        btn_GenTensor->setObjectName(QString::fromUtf8("btn_GenTensor"));

        verticalLayout_5->addWidget(btn_GenTensor);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_Cht_ShowMatricFreq = new QLabel(widget_panel);
        label_Cht_ShowMatricFreq->setObjectName(QString::fromUtf8("label_Cht_ShowMatricFreq"));

        horizontalLayout_9->addWidget(label_Cht_ShowMatricFreq);

        SBox_Cht_ShowMatricFreq = new QSpinBox(widget_panel);
        SBox_Cht_ShowMatricFreq->setObjectName(QString::fromUtf8("SBox_Cht_ShowMatricFreq"));
        SBox_Cht_ShowMatricFreq->setMinimumSize(QSize(72, 0));
        SBox_Cht_ShowMatricFreq->setMaximumSize(QSize(72, 16777215));
        SBox_Cht_ShowMatricFreq->setMinimum(1);
        SBox_Cht_ShowMatricFreq->setMaximum(20000);
        SBox_Cht_ShowMatricFreq->setValue(500);

        horizontalLayout_9->addWidget(SBox_Cht_ShowMatricFreq);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_Cht_ShowMultipleTime = new QLabel(widget_panel);
        label_Cht_ShowMultipleTime->setObjectName(QString::fromUtf8("label_Cht_ShowMultipleTime"));

        horizontalLayout_11->addWidget(label_Cht_ShowMultipleTime);

        SBox_Cht_ShowMultipleTime = new QSpinBox(widget_panel);
        SBox_Cht_ShowMultipleTime->setObjectName(QString::fromUtf8("SBox_Cht_ShowMultipleTime"));
        SBox_Cht_ShowMultipleTime->setMinimumSize(QSize(72, 0));
        SBox_Cht_ShowMultipleTime->setMaximumSize(QSize(72, 16777215));
        SBox_Cht_ShowMultipleTime->setMinimum(1);
        SBox_Cht_ShowMultipleTime->setMaximum(50);
        SBox_Cht_ShowMultipleTime->setValue(20);

        horizontalLayout_11->addWidget(SBox_Cht_ShowMultipleTime);


        verticalLayout_5->addLayout(horizontalLayout_11);

        label_cht_IsMatrixInsertFreq = new QLabel(widget_panel);
        label_cht_IsMatrixInsertFreq->setObjectName(QString::fromUtf8("label_cht_IsMatrixInsertFreq"));

        verticalLayout_5->addWidget(label_cht_IsMatrixInsertFreq);

        label_Cht_ShowFreqPtIndex = new QLabel(widget_panel);
        label_Cht_ShowFreqPtIndex->setObjectName(QString::fromUtf8("label_Cht_ShowFreqPtIndex"));

        verticalLayout_5->addWidget(label_Cht_ShowFreqPtIndex);

        label_Cht_ShowFreq = new QLabel(widget_panel);
        label_Cht_ShowFreq->setObjectName(QString::fromUtf8("label_Cht_ShowFreq"));

        verticalLayout_5->addWidget(label_Cht_ShowFreq);

        label_Cht_ShowMatricMaxMultTime = new QLabel(widget_panel);
        label_Cht_ShowMatricMaxMultTime->setObjectName(QString::fromUtf8("label_Cht_ShowMatricMaxMultTime"));

        verticalLayout_5->addWidget(label_Cht_ShowMatricMaxMultTime);

        label_Cht_selfOverlappintStartMultiTime = new QLabel(widget_panel);
        label_Cht_selfOverlappintStartMultiTime->setObjectName(QString::fromUtf8("label_Cht_selfOverlappintStartMultiTime"));

        verticalLayout_5->addWidget(label_Cht_selfOverlappintStartMultiTime);

        btn_updateTensorCht = new QPushButton(widget_panel);
        btn_updateTensorCht->setObjectName(QString::fromUtf8("btn_updateTensorCht"));

        verticalLayout_5->addWidget(btn_updateTensorCht);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout_8->addWidget(widget_panel);

        mainTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        VLayout_ChtPanel = new QVBoxLayout(tab_2);
        VLayout_ChtPanel->setSpacing(6);
        VLayout_ChtPanel->setContentsMargins(11, 11, 11, 11);
        VLayout_ChtPanel->setObjectName(QString::fromUtf8("VLayout_ChtPanel"));
        mainTabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(mainTabWidget);


        retranslateUi(FreqDoubWgtClass);

        mainTabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        tabWidget_3->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FreqDoubWgtClass);
    } // setupUi

    void retranslateUi(QWidget *FreqDoubWgtClass)
    {
        FreqDoubWgtClass->setWindowTitle(QApplication::translate("FreqDoubWgtClass", "FreqDoubWgt", nullptr));
        groupBox->setTitle(QApplication::translate("FreqDoubWgtClass", "\347\233\270\345\205\263\351\242\221\347\216\207\345\210\206\345\270\203", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("FreqDoubWgtClass", "\345\200\215\351\242\221\345\260\272\345\257\270\347\273\237\350\256\241", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("FreqDoubWgtClass", "\347\210\266\347\272\247\345\200\215\351\242\221\345\210\206\345\270\203", nullptr));
        groupBox_3->setTitle(QApplication::translate("FreqDoubWgtClass", "FFT\345\217\202\346\225\260", nullptr));
        label_SampleRate->setText(QApplication::translate("FreqDoubWgtClass", "\351\207\207\346\240\267\347\216\207", nullptr));
        label_WndPtCount->setText(QApplication::translate("FreqDoubWgtClass", "\347\252\227\345\217\243\347\202\271\346\225\260", nullptr));
        label_MaxEffectFreq->setText(QApplication::translate("FreqDoubWgtClass", "\346\234\200\345\244\247\346\216\245\345\217\227\351\242\221\347\216\207", nullptr));
        label_WndSpecConstrainFreqDriftRatio->setText(QApplication::translate("FreqDoubWgtClass", "\347\252\227\350\260\261\346\212\221\345\210\266\345\263\260\345\200\274\345\201\217\347\247\273\357\274\210%\357\274\211", nullptr));
        label_TensorEndFreq->setText(QApplication::translate("FreqDoubWgtClass", "\347\273\210\346\255\242\351\242\221\347\216\207(hz)", nullptr));
        label_ParentMatrixIncludeMainFreqCount->setText(QApplication::translate("FreqDoubWgtClass", "\347\210\266\347\272\247\345\214\205\345\220\253\345\211\215N\344\270\252\351\242\221\347\216\207", nullptr));
        label_MaxMultiTime->setText(QApplication::translate("FreqDoubWgtClass", "\346\234\200\345\244\247\345\200\215\351\242\221\346\254\241\346\225\260", nullptr));
        label_TensorStartFreq->setText(QApplication::translate("FreqDoubWgtClass", "\350\265\267\345\247\213\351\242\221\347\216\207(hz)", nullptr));
        checkBox_cutOffOnOverLappingStartPos->setText(QApplication::translate("FreqDoubWgtClass", "\346\230\257\345\220\246\345\216\273\351\231\244\350\207\252\344\272\244\345\217\240\345\200\215\351\242\221\345\214\272\345\237\237", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_5), QApplication::translate("FreqDoubWgtClass", "\345\200\215\351\242\221\345\274\240\351\207\217\345\217\202\346\225\260", nullptr));
        groupBox_2->setTitle(QApplication::translate("FreqDoubWgtClass", "\345\274\240\351\207\217\347\212\266\346\200\201", nullptr));
        label_TensorResult_StartFreq->setText(QApplication::translate("FreqDoubWgtClass", "\345\274\240\351\207\217\350\265\267\345\247\213\351\242\221\347\216\207\357\274\232", nullptr));
        label_TensorResult_EndFreq->setText(QApplication::translate("FreqDoubWgtClass", "\345\274\240\351\207\217\347\273\210\346\255\242\351\242\221\347\216\207\357\274\232", nullptr));
        label_TensorResult_MatrixCount->setText(QApplication::translate("FreqDoubWgtClass", "\345\200\215\351\242\221\347\237\251\351\230\265\344\270\252\346\225\260\357\274\232", nullptr));
        label_TensorResult_MatrixFreqInterval->setText(QApplication::translate("FreqDoubWgtClass", "\347\237\251\351\230\265\351\242\221\347\216\207\351\227\264\351\232\224\357\274\232", nullptr));
        checkBox_UpdateChtAfterGetTensor->setText(QApplication::translate("FreqDoubWgtClass", "\345\220\214\346\227\266\345\210\267\346\226\260\345\233\276\350\241\250", nullptr));
        label_tensorGenState->setText(QApplication::translate("FreqDoubWgtClass", "\345\210\206\346\236\220\347\212\266\346\200\201", nullptr));
        btn_GenTensor->setText(QApplication::translate("FreqDoubWgtClass", "\347\224\237\346\210\220\345\274\240\351\207\217", nullptr));
        label_Cht_ShowMatricFreq->setText(QApplication::translate("FreqDoubWgtClass", "\346\230\276\347\244\272\344\270\255\345\277\203\351\242\221\347\216\207", nullptr));
        label_Cht_ShowMultipleTime->setText(QApplication::translate("FreqDoubWgtClass", "\346\230\276\347\244\272\345\200\215\351\242\221\346\254\241\346\225\260", nullptr));
        label_cht_IsMatrixInsertFreq->setText(QApplication::translate("FreqDoubWgtClass", "\350\277\231\346\230\257\344\270\215\346\230\257\344\270\200\344\270\252\346\217\222\345\205\245\351\242\221\347\216\207\347\202\271\357\274\232", nullptr));
        label_Cht_ShowFreqPtIndex->setText(QApplication::translate("FreqDoubWgtClass", "\345\210\206\346\236\220\351\242\221\347\216\207FFT\347\202\271\347\264\242\345\274\225\357\274\232", nullptr));
        label_Cht_ShowFreq->setText(QApplication::translate("FreqDoubWgtClass", "\345\210\206\346\236\220\351\242\221\347\216\207FFT\347\202\271\351\242\221\347\216\207\357\274\232", nullptr));
        label_Cht_ShowMatricMaxMultTime->setText(QApplication::translate("FreqDoubWgtClass", "\346\234\211\346\225\210\345\200\215\351\242\221\346\254\241\346\225\260\357\274\232", nullptr));
        label_Cht_selfOverlappintStartMultiTime->setText(QApplication::translate("FreqDoubWgtClass", "\351\246\226\344\270\252\350\207\252\344\272\244\345\217\240\345\214\272\345\237\237\345\200\215\351\242\221\346\254\241\346\225\260\357\274\232", nullptr));
        btn_updateTensorCht->setText(QApplication::translate("FreqDoubWgtClass", "\345\210\267\346\226\260\345\233\276\350\241\250", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tab), QApplication::translate("FreqDoubWgtClass", "\345\200\215\351\242\221\347\233\270\345\205\263\346\200\247\345\210\206\346\236\220", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tab_2), QApplication::translate("FreqDoubWgtClass", "\347\275\221\347\273\234\350\276\223\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FreqDoubWgtClass: public Ui_FreqDoubWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREQDOUBWGT_H
