#include <QtWidgets/QApplication>
#include "./Audio/Widget/AudioMainWgt/AudioMainWgt.h"
#include "./Vision/Widget/VisionMainWgt/VisionMainWgt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto autoMoveScreenCenter = [](QWidget* pWgt)
        {
            QRect rect = pWgt->frameGeometry();
            QDesktopWidget desktop;
            QPoint centerPoint = desktop.availableGeometry().center();
            rect.moveCenter(centerPoint);
            pWgt->move(rect.topLeft());
        };

    QSize MainWidgetSize(1500, 905);

   //if(false)
    {
        AudioMainWgt* pAudioMainWidget = new AudioMainWgt(nullptr);
        pAudioMainWidget->resize(MainWidgetSize);
        //autoMoveScreenCenter(pAudioMainWidget);
        pAudioMainWidget->show();
    }

    if(false)
    {
        VisionMainWgt* pVisionMainWidget = new VisionMainWgt(nullptr);
        pVisionMainWidget->resize(QSize(1818,956));
        autoMoveScreenCenter(pVisionMainWidget);
        pVisionMainWidget->show();
    }

    return a.exec();
}
