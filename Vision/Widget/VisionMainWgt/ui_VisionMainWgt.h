/********************************************************************************
** Form generated from reading UI file 'VisionMainWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISIONMAINWGT_H
#define UI_VISIONMAINWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisionMainWgtClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_loadImg;
    QVBoxLayout *VLayout_LoadImg;
    QWidget *tab_loadVedio;
    QVBoxLayout *VLayout_LoadVedioFile;
    QWidget *tab_ColorMetric;
    QVBoxLayout *VLayout_ColorMetricWgt;

    void setupUi(QWidget *VisionMainWgtClass)
    {
        if (VisionMainWgtClass->objectName().isEmpty())
            VisionMainWgtClass->setObjectName(QString::fromUtf8("VisionMainWgtClass"));
        VisionMainWgtClass->resize(1110, 620);
        verticalLayout = new QVBoxLayout(VisionMainWgtClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(VisionMainWgtClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_loadImg = new QWidget();
        tab_loadImg->setObjectName(QString::fromUtf8("tab_loadImg"));
        VLayout_LoadImg = new QVBoxLayout(tab_loadImg);
        VLayout_LoadImg->setSpacing(6);
        VLayout_LoadImg->setContentsMargins(11, 11, 11, 11);
        VLayout_LoadImg->setObjectName(QString::fromUtf8("VLayout_LoadImg"));
        tabWidget->addTab(tab_loadImg, QString());
        tab_loadVedio = new QWidget();
        tab_loadVedio->setObjectName(QString::fromUtf8("tab_loadVedio"));
        VLayout_LoadVedioFile = new QVBoxLayout(tab_loadVedio);
        VLayout_LoadVedioFile->setSpacing(6);
        VLayout_LoadVedioFile->setContentsMargins(11, 11, 11, 11);
        VLayout_LoadVedioFile->setObjectName(QString::fromUtf8("VLayout_LoadVedioFile"));
        tabWidget->addTab(tab_loadVedio, QString());
        tab_ColorMetric = new QWidget();
        tab_ColorMetric->setObjectName(QString::fromUtf8("tab_ColorMetric"));
        VLayout_ColorMetricWgt = new QVBoxLayout(tab_ColorMetric);
        VLayout_ColorMetricWgt->setSpacing(6);
        VLayout_ColorMetricWgt->setContentsMargins(11, 11, 11, 11);
        VLayout_ColorMetricWgt->setObjectName(QString::fromUtf8("VLayout_ColorMetricWgt"));
        tabWidget->addTab(tab_ColorMetric, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(VisionMainWgtClass);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(VisionMainWgtClass);
    } // setupUi

    void retranslateUi(QWidget *VisionMainWgtClass)
    {
        VisionMainWgtClass->setWindowTitle(QApplication::translate("VisionMainWgtClass", "VisionMainWgt", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_loadImg), QApplication::translate("VisionMainWgtClass", "\345\233\276\347\211\207\345\212\240\350\275\275", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_loadVedio), QApplication::translate("VisionMainWgtClass", "\350\247\206\351\242\221\350\247\243\347\240\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_ColorMetric), QApplication::translate("VisionMainWgtClass", "\351\242\234\350\211\262\345\272\246\351\207\217\347\251\272\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VisionMainWgtClass: public Ui_VisionMainWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISIONMAINWGT_H
