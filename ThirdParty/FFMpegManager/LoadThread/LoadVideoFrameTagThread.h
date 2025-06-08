#pragma once
#include <QThread>
#include <QProcess>
#include <QByteArray>
#include <QJsonDocument>

#include "../../protocol/protocol_vision.h"

class LoadVideoFrameTagThread :public QThread
{
    Q_OBJECT
public:
    LoadVideoFrameTagThread(QObject* parent);

    void runWithArgument(QString ffProbeDir, const ST_VideoLoadSetting& LoadSetting,QStringList argument);

    int getIFrameCount() { return m_nIFrameCount; };
    int getPFrameCount() { return m_nPFrameCount; };
    int getNFrameCount() { return m_nBFrameCount; };

public:signals:
    void sgn_loadTagState(int precentage, QString errstr);
    void sgn_loadTagFinished(bool loadSuccess);

protected:
    void run() override;
    void FFProbedStreamJsonObjToFrameTag(QJsonObject& decodeDataObj, ST_VideoH264FrameTag& frameTag);

protected slots:
    void slot_readyReadProcessStandardOutput();
    void slot_readyReadProcessStandardError();
    void slot_ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);




private:
    QString m_FFProbePath;
    QProcess* m_pFFProbeProcess = nullptr;
    
    QStringList m_arguments;
    QByteArray m_tempDataArray;

    int m_nIFrameCount = -1;
    int m_nPFrameCount = -1;
    int m_nBFrameCount = -1;

    ST_VideoLoadSetting m_LoadSetting;
    QVector<ST_VideoH264FrameTag> m_tempFrameTagVec;

};

