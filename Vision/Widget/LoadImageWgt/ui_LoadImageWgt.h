/********************************************************************************
** Form generated from reading UI file 'LoadImageWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADIMAGEWGT_H
#define UI_LOADIMAGEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadImageWgtClass
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *HLayout_ImagePainter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_selLoadImg;
    QGroupBox *groupBox_selFileTag_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_Img_FileName;
    QLabel *label_file_Path;
    QLabel *label_Img_FileType;
    QFrame *line;
    QLabel *label_img_LoadState;
    QLabel *label_img_Size;
    QLabel *label_Img_CrDepth;
    QLabel *label_Img_CrFormat;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *SBox_LoadPicWidth;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *SBox_LoadPicHeight;
    QCheckBox *checkBox_autoShrink;
    QPushButton *btn_shrinkImg;
    QCheckBox *checkBox_autoSaveDataCenter;
    QPushButton *btn_saveImgToDataCenter;
    QCheckBox *checkBox_CrMetric;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoadImageWgtClass)
    {
        if (LoadImageWgtClass->objectName().isEmpty())
            LoadImageWgtClass->setObjectName(QString::fromUtf8("LoadImageWgtClass"));
        LoadImageWgtClass->resize(1221, 780);
        horizontalLayout = new QHBoxLayout(LoadImageWgtClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(LoadImageWgtClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        HLayout_ImagePainter = new QHBoxLayout(groupBox);
        HLayout_ImagePainter->setSpacing(6);
        HLayout_ImagePainter->setContentsMargins(11, 11, 11, 11);
        HLayout_ImagePainter->setObjectName(QString::fromUtf8("HLayout_ImagePainter"));

        horizontalLayout->addWidget(groupBox);

        widget = new QWidget(LoadImageWgtClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(240, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btn_selLoadImg = new QPushButton(widget);
        btn_selLoadImg->setObjectName(QString::fromUtf8("btn_selLoadImg"));

        verticalLayout->addWidget(btn_selLoadImg);

        groupBox_selFileTag_2 = new QGroupBox(widget);
        groupBox_selFileTag_2->setObjectName(QString::fromUtf8("groupBox_selFileTag_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_selFileTag_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_Img_FileName = new QLabel(groupBox_selFileTag_2);
        label_Img_FileName->setObjectName(QString::fromUtf8("label_Img_FileName"));

        verticalLayout_3->addWidget(label_Img_FileName);

        label_file_Path = new QLabel(groupBox_selFileTag_2);
        label_file_Path->setObjectName(QString::fromUtf8("label_file_Path"));

        verticalLayout_3->addWidget(label_file_Path);

        label_Img_FileType = new QLabel(groupBox_selFileTag_2);
        label_Img_FileType->setObjectName(QString::fromUtf8("label_Img_FileType"));

        verticalLayout_3->addWidget(label_Img_FileType);

        line = new QFrame(groupBox_selFileTag_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        label_img_LoadState = new QLabel(groupBox_selFileTag_2);
        label_img_LoadState->setObjectName(QString::fromUtf8("label_img_LoadState"));

        verticalLayout_3->addWidget(label_img_LoadState);

        label_img_Size = new QLabel(groupBox_selFileTag_2);
        label_img_Size->setObjectName(QString::fromUtf8("label_img_Size"));

        verticalLayout_3->addWidget(label_img_Size);

        label_Img_CrDepth = new QLabel(groupBox_selFileTag_2);
        label_Img_CrDepth->setObjectName(QString::fromUtf8("label_Img_CrDepth"));

        verticalLayout_3->addWidget(label_Img_CrDepth);

        label_Img_CrFormat = new QLabel(groupBox_selFileTag_2);
        label_Img_CrFormat->setObjectName(QString::fromUtf8("label_Img_CrFormat"));

        verticalLayout_3->addWidget(label_Img_CrFormat);


        verticalLayout->addWidget(groupBox_selFileTag_2);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        SBox_LoadPicWidth = new QSpinBox(groupBox_2);
        SBox_LoadPicWidth->setObjectName(QString::fromUtf8("SBox_LoadPicWidth"));
        SBox_LoadPicWidth->setMaximum(4080);
        SBox_LoadPicWidth->setValue(1920);

        horizontalLayout_4->addWidget(SBox_LoadPicWidth);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        SBox_LoadPicHeight = new QSpinBox(groupBox_2);
        SBox_LoadPicHeight->setObjectName(QString::fromUtf8("SBox_LoadPicHeight"));
        SBox_LoadPicHeight->setMaximum(4080);
        SBox_LoadPicHeight->setValue(1080);

        horizontalLayout_5->addWidget(SBox_LoadPicHeight);


        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout->addWidget(groupBox_2);

        checkBox_autoShrink = new QCheckBox(widget);
        checkBox_autoShrink->setObjectName(QString::fromUtf8("checkBox_autoShrink"));
        checkBox_autoShrink->setChecked(true);

        verticalLayout->addWidget(checkBox_autoShrink);

        btn_shrinkImg = new QPushButton(widget);
        btn_shrinkImg->setObjectName(QString::fromUtf8("btn_shrinkImg"));
        btn_shrinkImg->setEnabled(false);

        verticalLayout->addWidget(btn_shrinkImg);

        checkBox_autoSaveDataCenter = new QCheckBox(widget);
        checkBox_autoSaveDataCenter->setObjectName(QString::fromUtf8("checkBox_autoSaveDataCenter"));
        checkBox_autoSaveDataCenter->setChecked(true);

        verticalLayout->addWidget(checkBox_autoSaveDataCenter);

        btn_saveImgToDataCenter = new QPushButton(widget);
        btn_saveImgToDataCenter->setObjectName(QString::fromUtf8("btn_saveImgToDataCenter"));
        btn_saveImgToDataCenter->setEnabled(false);

        verticalLayout->addWidget(btn_saveImgToDataCenter);

        checkBox_CrMetric = new QCheckBox(widget);
        checkBox_CrMetric->setObjectName(QString::fromUtf8("checkBox_CrMetric"));
        checkBox_CrMetric->setChecked(true);

        verticalLayout->addWidget(checkBox_CrMetric);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);


        retranslateUi(LoadImageWgtClass);

        QMetaObject::connectSlotsByName(LoadImageWgtClass);
    } // setupUi

    void retranslateUi(QWidget *LoadImageWgtClass)
    {
        LoadImageWgtClass->setWindowTitle(QApplication::translate("LoadImageWgtClass", "LoadImageWgt", nullptr));
        groupBox->setTitle(QApplication::translate("LoadImageWgtClass", "\345\233\276\345\203\217\345\257\274\345\205\245\347\273\223\346\236\234", nullptr));
        btn_selLoadImg->setText(QApplication::translate("LoadImageWgtClass", "\351\200\211\346\213\251\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
        groupBox_selFileTag_2->setTitle(QApplication::translate("LoadImageWgtClass", "\346\226\207\344\273\266\346\240\207\347\255\276", nullptr));
        label_Img_FileName->setText(QApplication::translate("LoadImageWgtClass", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        label_file_Path->setText(QApplication::translate("LoadImageWgtClass", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_Img_FileType->setText(QApplication::translate("LoadImageWgtClass", "\346\226\207\344\273\266\347\261\273\345\236\213\357\274\232", nullptr));
        label_img_LoadState->setText(QApplication::translate("LoadImageWgtClass", "\345\212\240\350\275\275\347\212\266\346\200\201\357\274\232", nullptr));
        label_img_Size->setText(QApplication::translate("LoadImageWgtClass", "\345\233\276\345\203\217\345\260\272\345\257\270\357\274\232", nullptr));
        label_Img_CrDepth->setText(QApplication::translate("LoadImageWgtClass", "\351\242\234\350\211\262\346\267\261\345\272\246\357\274\232", nullptr));
        label_Img_CrFormat->setText(QApplication::translate("LoadImageWgtClass", "\351\242\234\350\211\262\346\240\274\345\274\217\357\274\232", nullptr));
        groupBox_2->setTitle(QApplication::translate("LoadImageWgtClass", "\345\257\274\345\205\245\345\260\272\345\257\270", nullptr));
        label_2->setText(QApplication::translate("LoadImageWgtClass", "\346\234\200\345\244\247\345\256\275\345\272\246", nullptr));
        label_3->setText(QApplication::translate("LoadImageWgtClass", "\346\234\200\345\244\247\351\253\230\345\272\246", nullptr));
        checkBox_autoShrink->setText(QApplication::translate("LoadImageWgtClass", "\350\207\252\345\212\250\345\260\272\345\257\270\350\275\254\345\214\226", nullptr));
        btn_shrinkImg->setText(QApplication::translate("LoadImageWgtClass", "\345\260\272\345\257\270\350\275\254\345\214\226", nullptr));
        checkBox_autoSaveDataCenter->setText(QApplication::translate("LoadImageWgtClass", "\350\207\252\345\212\250\345\255\230\345\205\245\346\225\260\346\215\256\344\270\255\345\277\203", nullptr));
        btn_saveImgToDataCenter->setText(QApplication::translate("LoadImageWgtClass", "\345\255\230\345\205\245\346\225\260\346\215\256\344\270\255\345\277\203", nullptr));
        checkBox_CrMetric->setText(QApplication::translate("LoadImageWgtClass", "\351\242\234\350\211\262\345\272\246\351\207\217\347\251\272\351\227\264\350\207\252\345\212\250\345\257\274\345\205\245\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadImageWgtClass: public Ui_LoadImageWgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADIMAGEWGT_H
