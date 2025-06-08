#include "AudioDeviceDialog.h"

AudioDeviceDialog::AudioDeviceDialog(QWidget* parent):QDialog(parent)
{
	ui.setupUi(this);
    connect(ui.btn_ok,      &QPushButton::clicked, this, &AudioDeviceDialog::slot_ok);
    connect(ui.btn_cancel,  &QPushButton::clicked, this, &QWidget::hide);
}

void AudioDeviceDialog::setDeivceItem(  const QList<QString> inputDeviceList, QString currentInputDev,
                                        const QList<QString> outputDeviceList, QString currentoutputDev)
{
    auto initDevCombox = [](QComboBox* cBox,const QList<QString> DeviceList, QString currentDev)
    {
            cBox->clear();
            int currentComboxIndex = 0;
            int defaultComboxIndex = -1;
            for(auto pos = DeviceList.begin();pos != DeviceList.end();pos++)
            {
                QString deviceName = *pos;
                cBox->addItem(deviceName, QVariant::fromValue(deviceName));
                if (deviceName == currentDev)
                {
                    defaultComboxIndex = currentComboxIndex;
                }
                currentComboxIndex += 1;
            }
            cBox->setCurrentIndex(defaultComboxIndex == -1 ? 0 : defaultComboxIndex);
     };

    initDevCombox(ui.comboBox_inputDevice, inputDeviceList, currentInputDev);
    initDevCombox(ui.comboBox_outputDevice, outputDeviceList, currentoutputDev);
      
}

void AudioDeviceDialog::slot_ok()
{
    QString currentInputDevcie = ui.comboBox_inputDevice->currentData().toString();
    QString currentOutputDevcie = ui.comboBox_outputDevice->currentData().toString();
    qDebug() << QString("current inputDevice    : %1").arg(currentInputDevcie);
    qDebug() << QString("current outputDevice   : %1").arg(currentOutputDevcie);
    emit sgn_switchDevice(currentInputDevcie, currentOutputDevcie);
    hide();
}
