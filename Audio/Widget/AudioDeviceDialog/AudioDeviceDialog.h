#pragma once
#include <QDialog>
#include "./ui_AudioDeviceDialog.h"
#include <QAudioDeviceInfo>
#include <QMap>
#include <qDebug>


class AudioDeviceDialog :public QDialog
{
    Q_OBJECT
public:
    AudioDeviceDialog(QWidget* parent);

    void setDeivceItem( const QList<QString> inputDeviceList,  QString currentInputDev,
                        const QList<QString> outputDeviceList, QString currentoutputDev);

protected slots:
    void slot_ok();

public:signals:
    void sgn_switchDevice(const QString inputDevice, const QString outputDevcie);

private:
    Ui::AudioDeviceDialog ui;
};

