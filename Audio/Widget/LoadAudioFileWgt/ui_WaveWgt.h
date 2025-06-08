/********************************************************************************
** Form generated from reading UI file 'WaveWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVEWGT_H
#define UI_WAVEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaveWgtClass
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_leftCh;
    QVBoxLayout *VLayout_LeftCh;
    QGroupBox *groupBox_rightCh;
    QVBoxLayout *VLayout_rightCh;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_cht_load_startTime;
    QTimeEdit *timeEdit_chtLoadStartTime;
    QLabel *label_cht_load_endTime;
    QTimeEdit *timeEdit_chtLoadEndTime;
    QPushButton *btn_reloadCht;
    QPushButton *btn_loadToDataCenter;
    QPushButton *btn_loadAll;
    QLabel *label_reloadState;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_windowStartTime;
    QScrollBar *HScrollBar_windowPos;
    QLabel *label_windowEndTime;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_windowLength;
    QSlider *hSlider_windowScale;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_currentTime;
    QSlider *hSlider_currentTime;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_stop;
    QPushButton *btn_play;
    QPushButton *btn_pause;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QVBoxLayout *VLayout_volumnBar;

    void setupUi(QWidget *WaveWgtClass)
    {
        if (WaveWgtClass->objectName().isEmpty())
            WaveWgtClass->setObjectName(QString::fromUtf8("WaveWgtClass"));
        WaveWgtClass->resize(1225, 505);
        verticalLayout = new QVBoxLayout(WaveWgtClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_leftCh = new QGroupBox(WaveWgtClass);
        groupBox_leftCh->setObjectName(QString::fromUtf8("groupBox_leftCh"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_leftCh->sizePolicy().hasHeightForWidth());
        groupBox_leftCh->setSizePolicy(sizePolicy);
        VLayout_LeftCh = new QVBoxLayout(groupBox_leftCh);
        VLayout_LeftCh->setSpacing(6);
        VLayout_LeftCh->setContentsMargins(11, 11, 11, 11);
        VLayout_LeftCh->setObjectName(QString::fromUtf8("VLayout_LeftCh"));

        verticalLayout->addWidget(groupBox_leftCh);

        groupBox_rightCh = new QGroupBox(WaveWgtClass);
        groupBox_rightCh->setObjectName(QString::fromUtf8("groupBox_rightCh"));
        sizePolicy.setHeightForWidth(groupBox_rightCh->sizePolicy().hasHeightForWidth());
        groupBox_rightCh->setSizePolicy(sizePolicy);
        VLayout_rightCh = new QVBoxLayout(groupBox_rightCh);
        VLayout_rightCh->setSpacing(6);
        VLayout_rightCh->setContentsMargins(11, 11, 11, 11);
        VLayout_rightCh->setObjectName(QString::fromUtf8("VLayout_rightCh"));

        verticalLayout->addWidget(groupBox_rightCh);

        groupBox = new QGroupBox(WaveWgtClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_cht_load_startTime = new QLabel(groupBox);
        label_cht_load_startTime->setObjectName(QString::fromUtf8("label_cht_load_startTime"));

        horizontalLayout_5->addWidget(label_cht_load_startTime);

        timeEdit_chtLoadStartTime = new QTimeEdit(groupBox);
        timeEdit_chtLoadStartTime->setObjectName(QString::fromUtf8("timeEdit_chtLoadStartTime"));

        horizontalLayout_5->addWidget(timeEdit_chtLoadStartTime);

        label_cht_load_endTime = new QLabel(groupBox);
        label_cht_load_endTime->setObjectName(QString::fromUtf8("label_cht_load_endTime"));

        horizontalLayout_5->addWidget(label_cht_load_endTime);

        timeEdit_chtLoadEndTime = new QTimeEdit(groupBox);
        timeEdit_chtLoadEndTime->setObjectName(QString::fromUtf8("timeEdit_chtLoadEndTime"));

        horizontalLayout_5->addWidget(timeEdit_chtLoadEndTime);

        btn_reloadCht = new QPushButton(groupBox);
        btn_reloadCht->setObjectName(QString::fromUtf8("btn_reloadCht"));

        horizontalLayout_5->addWidget(btn_reloadCht);

        btn_loadToDataCenter = new QPushButton(groupBox);
        btn_loadToDataCenter->setObjectName(QString::fromUtf8("btn_loadToDataCenter"));

        horizontalLayout_5->addWidget(btn_loadToDataCenter);

        btn_loadAll = new QPushButton(groupBox);
        btn_loadAll->setObjectName(QString::fromUtf8("btn_loadAll"));

        horizontalLayout_5->addWidget(btn_loadAll);

        label_reloadState = new QLabel(groupBox);
        label_reloadState->setObjectName(QString::fromUtf8("label_reloadState"));

        horizontalLayout_5->addWidget(label_reloadState);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_windowStartTime = new QLabel(groupBox);
        label_windowStartTime->setObjectName(QString::fromUtf8("label_windowStartTime"));
        label_windowStartTime->setMinimumSize(QSize(140, 0));
        label_windowStartTime->setMaximumSize(QSize(140, 20));

        horizontalLayout->addWidget(label_windowStartTime);

        HScrollBar_windowPos = new QScrollBar(groupBox);
        HScrollBar_windowPos->setObjectName(QString::fromUtf8("HScrollBar_windowPos"));
        HScrollBar_windowPos->setMaximumSize(QSize(16777215, 20));
        HScrollBar_windowPos->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(HScrollBar_windowPos);

        label_windowEndTime = new QLabel(groupBox);
        label_windowEndTime->setObjectName(QString::fromUtf8("label_windowEndTime"));
        label_windowEndTime->setMinimumSize(QSize(140, 0));
        label_windowEndTime->setMaximumSize(QSize(140, 20));

        horizontalLayout->addWidget(label_windowEndTime);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_windowLength = new QLabel(groupBox);
        label_windowLength->setObjectName(QString::fromUtf8("label_windowLength"));
        label_windowLength->setMinimumSize(QSize(120, 0));
        label_windowLength->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_2->addWidget(label_windowLength);

        hSlider_windowScale = new QSlider(groupBox);
        hSlider_windowScale->setObjectName(QString::fromUtf8("hSlider_windowScale"));
        hSlider_windowScale->setMinimum(1);
        hSlider_windowScale->setMaximum(10);
        hSlider_windowScale->setPageStep(1);
        hSlider_windowScale->setSliderPosition(5);
        hSlider_windowScale->setOrientation(Qt::Horizontal);
        hSlider_windowScale->setTickPosition(QSlider::TicksAbove);

        horizontalLayout_2->addWidget(hSlider_windowScale);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_currentTime = new QLabel(groupBox);
        label_currentTime->setObjectName(QString::fromUtf8("label_currentTime"));
        label_currentTime->setMinimumSize(QSize(120, 0));
        label_currentTime->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(label_currentTime);

        hSlider_currentTime = new QSlider(groupBox);
        hSlider_currentTime->setObjectName(QString::fromUtf8("hSlider_currentTime"));
        hSlider_currentTime->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hSlider_currentTime);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        btn_stop = new QPushButton(groupBox);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));

        horizontalLayout_4->addWidget(btn_stop);

        btn_play = new QPushButton(groupBox);
        btn_play->setObjectName(QString::fromUtf8("btn_play"));

        horizontalLayout_4->addWidget(btn_play);

        btn_pause = new QPushButton(groupBox);
        btn_pause->setObjectName(QString::fromUtf8("btn_pause"));

        horizontalLayout_4->addWidget(btn_pause);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_2);

        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(40, 0));
        widget->setMaximumSize(QSize(40, 16777215));
        VLayout_volumnBar = new QVBoxLayout(widget);
        VLayout_volumnBar->setSpacing(6);
        VLayout_volumnBar->setContentsMargins(11, 11, 11, 11);
        VLayout_volumnBar->setObjectName(QString::fromUtf8("VLayout_volumnBar"));
        VLayout_volumnBar->setContentsMargins(2, 2, 2, 2);

        horizontalLayout_6->addWidget(widget);


        verticalLayout->addWidget(groupBox);


        retranslateUi(WaveWgtClass);

        QMetaObject::connectSlotsByName(WaveWgtClass);
    } // setupUi

    void retranslateUi(QWidget *WaveWgtClass)
    {
        WaveWgtClass->setWindowTitle(QApplication::translate("WaveWgtClass", "WaveWgt", nullptr));
        groupBox_leftCh->setTitle(QApplication::translate("WaveWgtClass", "leftCh", nullptr));
        groupBox_rightCh->setTitle(QApplication::translate("WaveWgtClass", "rightCh", nullptr));
        groupBox->setTitle(QApplication::translate("WaveWgtClass", "pannel", nullptr));
        label_cht_load_startTime->setText(QApplication::translate("WaveWgtClass", "\350\275\275\345\205\245\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeEdit_chtLoadStartTime->setDisplayFormat(QApplication::translate("WaveWgtClass", "mm:ss.zzz", nullptr));
        label_cht_load_endTime->setText(QApplication::translate("WaveWgtClass", "\350\275\275\345\205\245\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        timeEdit_chtLoadEndTime->setDisplayFormat(QApplication::translate("WaveWgtClass", "mm:ss.zzz", nullptr));
        btn_reloadCht->setText(QApplication::translate("WaveWgtClass", "\351\207\215\346\226\260\345\212\240\350\275\275\346\227\266\351\227\264\350\214\203\345\233\264", nullptr));
        btn_loadToDataCenter->setText(QApplication::translate("WaveWgtClass", "\345\255\230\345\202\250\345\210\260DCenter", nullptr));
        btn_loadAll->setText(QApplication::translate("WaveWgtClass", "\345\212\240\350\275\275\345\205\250\351\203\250", nullptr));
        label_reloadState->setText(QApplication::translate("WaveWgtClass", "\351\207\215\346\226\260\350\275\275\345\205\245\347\212\266\346\200\201\357\274\232", nullptr));
        label_windowStartTime->setText(QApplication::translate("WaveWgtClass", "\347\252\227\345\217\243\345\274\200\345\247\213\346\227\266\351\227\264:00:00:00", nullptr));
        label_windowEndTime->setText(QApplication::translate("WaveWgtClass", "\347\252\227\345\217\243\347\273\223\346\235\237\346\227\266\351\227\264:00:00:00", nullptr));
        label_windowLength->setText(QApplication::translate("WaveWgtClass", "\347\252\227\345\217\243\351\225\277\345\272\246\357\274\23260s", nullptr));
        label_currentTime->setText(QApplication::translate("WaveWgtClass", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\23200:00:00", nullptr));
        btn_stop->setText(QApplication::translate("WaveWgtClass", "stop", nullptr));
        btn_play->setText(QApplication::translate("WaveWgtClass", "play", nullptr));
        btn_pause->setText(QApplication::translate("WaveWgtClass", "pause", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaveWgtClass: public Ui_WaveWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVEWGT_H
