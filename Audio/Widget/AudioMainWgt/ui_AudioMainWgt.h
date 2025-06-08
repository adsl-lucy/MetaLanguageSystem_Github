/********************************************************************************
** Form generated from reading UI file 'AudioMainWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOMAINWGT_H
#define UI_AUDIOMAINWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioMainWgtClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_AudiofileOpen;
    QVBoxLayout *VLayout_AudioFileOpenTab;
    QWidget *tab_recorder;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *HLayout_tab_recorder;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *tab_FFTTest;
    QVBoxLayout *VLayout_FFT_Test;
    QWidget *tab_STFT;
    QVBoxLayout *VLayout_STFT;
    QWidget *tab_EffOscMask;
    QVBoxLayout *VLayout_EffOscWgt;
    QWidget *tab_FFTWnd;
    QVBoxLayout *VLayout_FFT_Wnd;
    QWidget *tab_SNRSelect;
    QVBoxLayout *VLayout_SNRSelWgt;
    QWidget *tab_EffSigBuffer;
    QVBoxLayout *VLayout_EffSigBuffWgt;
    QWidget *tab_FDR;
    QVBoxLayout *VLayout_FDRWgt;
    QWidget *tab_BandWidthInput;
    QVBoxLayout *VLayout_BandWidthInput;
    QWidget *tab_AudioObject;
    QVBoxLayout *VLayout_AudioObject;

    void setupUi(QWidget *AudioMainWgtClass)
    {
        if (AudioMainWgtClass->objectName().isEmpty())
            AudioMainWgtClass->setObjectName(QString::fromUtf8("AudioMainWgtClass"));
        AudioMainWgtClass->resize(1341, 840);
        verticalLayout = new QVBoxLayout(AudioMainWgtClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(AudioMainWgtClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_AudiofileOpen = new QWidget();
        tab_AudiofileOpen->setObjectName(QString::fromUtf8("tab_AudiofileOpen"));
        VLayout_AudioFileOpenTab = new QVBoxLayout(tab_AudiofileOpen);
        VLayout_AudioFileOpenTab->setSpacing(6);
        VLayout_AudioFileOpenTab->setContentsMargins(11, 11, 11, 11);
        VLayout_AudioFileOpenTab->setObjectName(QString::fromUtf8("VLayout_AudioFileOpenTab"));
        tabWidget->addTab(tab_AudiofileOpen, QString());
        tab_recorder = new QWidget();
        tab_recorder->setObjectName(QString::fromUtf8("tab_recorder"));
        verticalLayout_2 = new QVBoxLayout(tab_recorder);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        HLayout_tab_recorder = new QHBoxLayout();
        HLayout_tab_recorder->setSpacing(6);
        HLayout_tab_recorder->setObjectName(QString::fromUtf8("HLayout_tab_recorder"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HLayout_tab_recorder->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(HLayout_tab_recorder);

        verticalSpacer = new QSpacerItem(20, 691, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab_recorder, QString());
        tab_FFTTest = new QWidget();
        tab_FFTTest->setObjectName(QString::fromUtf8("tab_FFTTest"));
        VLayout_FFT_Test = new QVBoxLayout(tab_FFTTest);
        VLayout_FFT_Test->setSpacing(6);
        VLayout_FFT_Test->setContentsMargins(11, 11, 11, 11);
        VLayout_FFT_Test->setObjectName(QString::fromUtf8("VLayout_FFT_Test"));
        tabWidget->addTab(tab_FFTTest, QString());
        tab_STFT = new QWidget();
        tab_STFT->setObjectName(QString::fromUtf8("tab_STFT"));
        VLayout_STFT = new QVBoxLayout(tab_STFT);
        VLayout_STFT->setSpacing(6);
        VLayout_STFT->setContentsMargins(11, 11, 11, 11);
        VLayout_STFT->setObjectName(QString::fromUtf8("VLayout_STFT"));
        tabWidget->addTab(tab_STFT, QString());
        tab_EffOscMask = new QWidget();
        tab_EffOscMask->setObjectName(QString::fromUtf8("tab_EffOscMask"));
        VLayout_EffOscWgt = new QVBoxLayout(tab_EffOscMask);
        VLayout_EffOscWgt->setSpacing(6);
        VLayout_EffOscWgt->setContentsMargins(11, 11, 11, 11);
        VLayout_EffOscWgt->setObjectName(QString::fromUtf8("VLayout_EffOscWgt"));
        tabWidget->addTab(tab_EffOscMask, QString());
        tab_FFTWnd = new QWidget();
        tab_FFTWnd->setObjectName(QString::fromUtf8("tab_FFTWnd"));
        VLayout_FFT_Wnd = new QVBoxLayout(tab_FFTWnd);
        VLayout_FFT_Wnd->setSpacing(6);
        VLayout_FFT_Wnd->setContentsMargins(11, 11, 11, 11);
        VLayout_FFT_Wnd->setObjectName(QString::fromUtf8("VLayout_FFT_Wnd"));
        tabWidget->addTab(tab_FFTWnd, QString());
        tab_SNRSelect = new QWidget();
        tab_SNRSelect->setObjectName(QString::fromUtf8("tab_SNRSelect"));
        VLayout_SNRSelWgt = new QVBoxLayout(tab_SNRSelect);
        VLayout_SNRSelWgt->setSpacing(6);
        VLayout_SNRSelWgt->setContentsMargins(11, 11, 11, 11);
        VLayout_SNRSelWgt->setObjectName(QString::fromUtf8("VLayout_SNRSelWgt"));
        tabWidget->addTab(tab_SNRSelect, QString());
        tab_EffSigBuffer = new QWidget();
        tab_EffSigBuffer->setObjectName(QString::fromUtf8("tab_EffSigBuffer"));
        VLayout_EffSigBuffWgt = new QVBoxLayout(tab_EffSigBuffer);
        VLayout_EffSigBuffWgt->setSpacing(6);
        VLayout_EffSigBuffWgt->setContentsMargins(11, 11, 11, 11);
        VLayout_EffSigBuffWgt->setObjectName(QString::fromUtf8("VLayout_EffSigBuffWgt"));
        tabWidget->addTab(tab_EffSigBuffer, QString());
        tab_FDR = new QWidget();
        tab_FDR->setObjectName(QString::fromUtf8("tab_FDR"));
        VLayout_FDRWgt = new QVBoxLayout(tab_FDR);
        VLayout_FDRWgt->setSpacing(6);
        VLayout_FDRWgt->setContentsMargins(11, 11, 11, 11);
        VLayout_FDRWgt->setObjectName(QString::fromUtf8("VLayout_FDRWgt"));
        tabWidget->addTab(tab_FDR, QString());
        tab_BandWidthInput = new QWidget();
        tab_BandWidthInput->setObjectName(QString::fromUtf8("tab_BandWidthInput"));
        VLayout_BandWidthInput = new QVBoxLayout(tab_BandWidthInput);
        VLayout_BandWidthInput->setSpacing(6);
        VLayout_BandWidthInput->setContentsMargins(11, 11, 11, 11);
        VLayout_BandWidthInput->setObjectName(QString::fromUtf8("VLayout_BandWidthInput"));
        tabWidget->addTab(tab_BandWidthInput, QString());
        tab_AudioObject = new QWidget();
        tab_AudioObject->setObjectName(QString::fromUtf8("tab_AudioObject"));
        VLayout_AudioObject = new QVBoxLayout(tab_AudioObject);
        VLayout_AudioObject->setSpacing(6);
        VLayout_AudioObject->setContentsMargins(11, 11, 11, 11);
        VLayout_AudioObject->setObjectName(QString::fromUtf8("VLayout_AudioObject"));
        tabWidget->addTab(tab_AudioObject, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(AudioMainWgtClass);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(AudioMainWgtClass);
    } // setupUi

    void retranslateUi(QWidget *AudioMainWgtClass)
    {
        AudioMainWgtClass->setWindowTitle(QApplication::translate("AudioMainWgtClass", "AudioMainWgt", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_AudiofileOpen), QApplication::translate("AudioMainWgtClass", "\346\226\207\344\273\266\345\257\274\345\205\245", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_recorder), QApplication::translate("AudioMainWgtClass", "\345\275\225\351\237\263", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_FFTTest), QApplication::translate("AudioMainWgtClass", "FFT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_STFT), QApplication::translate("AudioMainWgtClass", "STFT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_EffOscMask), QApplication::translate("AudioMainWgtClass", "\346\234\211\346\225\210\351\234\207\350\215\241\345\261\217\350\224\275", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_FFTWnd), QApplication::translate("AudioMainWgtClass", "\347\252\227\345\207\275\346\225\260\345\210\206\346\236\220", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_SNRSelect), QApplication::translate("AudioMainWgtClass", "BDSNR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_EffSigBuffer), QApplication::translate("AudioMainWgtClass", "\346\234\211\346\225\210\344\277\241\345\217\267\347\274\223\345\206\262\345\214\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_FDR), QApplication::translate("AudioMainWgtClass", "\345\200\215\351\242\221\347\233\270\345\205\263\346\200\247", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_BandWidthInput), QApplication::translate("AudioMainWgtClass", "\345\256\275\345\270\246\350\276\223\345\205\245", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_AudioObject), QApplication::translate("AudioMainWgtClass", "\345\220\254\350\247\211\345\257\271\350\261\241\345\210\244\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioMainWgtClass: public Ui_AudioMainWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOMAINWGT_H
