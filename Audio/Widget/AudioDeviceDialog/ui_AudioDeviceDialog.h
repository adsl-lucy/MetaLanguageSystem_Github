/********************************************************************************
** Form generated from reading UI file 'AudioDeviceDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIODEVICEDIALOG_H
#define UI_AUDIODEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioDeviceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_inputDevice;
    QComboBox *comboBox_inputDevice;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_outputDevice;
    QComboBox *comboBox_outputDevice;
    QWidget *widget_2;
    QPushButton *btn_cancel;
    QPushButton *btn_ok;

    void setupUi(QWidget *AudioDeviceDialog)
    {
        if (AudioDeviceDialog->objectName().isEmpty())
            AudioDeviceDialog->setObjectName(QString::fromUtf8("AudioDeviceDialog"));
        AudioDeviceDialog->resize(280, 150);
        AudioDeviceDialog->setMinimumSize(QSize(280, 150));
        AudioDeviceDialog->setMaximumSize(QSize(280, 150));
        verticalLayout = new QVBoxLayout(AudioDeviceDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(AudioDeviceDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_inputDevice = new QLabel(widget);
        label_inputDevice->setObjectName(QString::fromUtf8("label_inputDevice"));
        label_inputDevice->setMinimumSize(QSize(64, 0));
        label_inputDevice->setMaximumSize(QSize(64, 16777215));

        horizontalLayout->addWidget(label_inputDevice);

        comboBox_inputDevice = new QComboBox(widget);
        comboBox_inputDevice->setObjectName(QString::fromUtf8("comboBox_inputDevice"));

        horizontalLayout->addWidget(comboBox_inputDevice);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_outputDevice = new QLabel(widget);
        label_outputDevice->setObjectName(QString::fromUtf8("label_outputDevice"));
        label_outputDevice->setMinimumSize(QSize(64, 24));
        label_outputDevice->setMaximumSize(QSize(64, 24));

        horizontalLayout_2->addWidget(label_outputDevice);

        comboBox_outputDevice = new QComboBox(widget);
        comboBox_outputDevice->setObjectName(QString::fromUtf8("comboBox_outputDevice"));

        horizontalLayout_2->addWidget(comboBox_outputDevice);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(AudioDeviceDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        btn_cancel = new QPushButton(widget_2);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));
        btn_cancel->setGeometry(QRect(180, 10, 75, 23));
        btn_ok = new QPushButton(widget_2);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));
        btn_ok->setGeometry(QRect(10, 10, 75, 23));

        verticalLayout->addWidget(widget_2);


        retranslateUi(AudioDeviceDialog);

        QMetaObject::connectSlotsByName(AudioDeviceDialog);
    } // setupUi

    void retranslateUi(QWidget *AudioDeviceDialog)
    {
        AudioDeviceDialog->setWindowTitle(QApplication::translate("AudioDeviceDialog", "Form", nullptr));
        label_inputDevice->setText(QApplication::translate("AudioDeviceDialog", "\350\276\223\345\205\245\350\256\276\345\244\207\357\274\232", nullptr));
        label_outputDevice->setText(QApplication::translate("AudioDeviceDialog", "\350\276\223\345\207\272\350\256\276\345\244\207\357\274\232", nullptr));
        btn_cancel->setText(QApplication::translate("AudioDeviceDialog", "\350\277\224\345\233\236", nullptr));
        btn_ok->setText(QApplication::translate("AudioDeviceDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioDeviceDialog: public Ui_AudioDeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIODEVICEDIALOG_H
