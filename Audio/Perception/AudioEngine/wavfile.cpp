/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qendian.h>
#include "wavfile.h"
#include <QDebug>

struct chunk
{
    char        id[4];
    quint32     size;
};

struct RIFFHeader
{
    chunk       descriptor;     // "RIFF"
    char        type[4];        // "WAVE"
};

struct WAVEHeader
{
    chunk       descriptor;
    quint16     audioFormat;
    quint16     numChannels;
    quint32     sampleRate;
    quint32     byteRate;
    quint16     blockAlign;
    quint16     bitsPerSample;
};

struct DATAHeader
{
    chunk       descriptor;
};

struct ListHeader
{
    chunk       descriptor;
    char        ListTypeId[4];        // "WAVE"
};

struct CombinedHeader
{
    RIFFHeader  riff;
    WAVEHeader  wave;
};

WavFile::WavFile(QObject* parent)
    : QFile(parent)
    , m_NormalHeaderLength(0)
{

}

bool WavFile::openAndReadHead(const QString& fileName)
{
    close();
    setFileName(fileName);
    bool fileOpenState      = QFile::open(QIODevice::ReadOnly);
    bool normalHeadState    = readNormalHeader();
    m_bListHeadExist        = readListHead();
    bool dataHeadState      = readDataHead();
    return fileOpenState && normalHeadState && dataHeadState;
}

const QAudioFormat& WavFile::fileFormat() const
{
    return m_fileFormat;
}

qint64 WavFile::headerLength() const
{
    return m_nDataBuffPos;
}

int WavFile::WavDataSize()
{
    return m_nDataSize;
}

bool WavFile::readNormalHeader()
{
    seek(0);
    CombinedHeader header;
    bool result = read(reinterpret_cast<char*>(&header), sizeof(CombinedHeader)) == sizeof(CombinedHeader);
    if (result) {
        if ((memcmp(&header.riff.descriptor.id, "RIFF", 4) == 0
            || memcmp(&header.riff.descriptor.id, "RIFX", 4) == 0)
            && memcmp(&header.riff.type, "WAVE", 4) == 0
            && memcmp(&header.wave.descriptor.id, "fmt ", 4) == 0
            && (header.wave.audioFormat == 1 || header.wave.audioFormat == 0)) {

           

            if (qFromLittleEndian<quint32>(header.wave.descriptor.size) > sizeof(WAVEHeader)) {
                // Extended data available
                quint16 extraFormatBytes;
                if (peek((char*)&extraFormatBytes, sizeof(quint16)) != sizeof(quint16))
                    return false;
                const qint64 throwAwayBytes = sizeof(quint16) + qFromLittleEndian<quint16>(extraFormatBytes);
                if (read(throwAwayBytes).size() != throwAwayBytes)
                    return false;
            }

            /*
            // Read off remaining header information
            DATAHeader dataHeader;

            if (read((char*)&dataHeader, sizeof(DATAHeader)) != sizeof(DATAHeader))
                return false;
             */

            // Establish format
            if (memcmp(&header.riff.descriptor.id, "RIFF", 4) == 0)
                m_fileFormat.setByteOrder(QAudioFormat::LittleEndian);
            else
                m_fileFormat.setByteOrder(QAudioFormat::BigEndian);

            int bps = qFromLittleEndian<quint16>(header.wave.bitsPerSample);
            m_fileFormat.setChannelCount(qFromLittleEndian<quint16>(header.wave.numChannels));
            m_fileFormat.setCodec("audio/pcm");
            m_fileFormat.setSampleRate(qFromLittleEndian<quint32>(header.wave.sampleRate));
            m_fileFormat.setSampleSize(qFromLittleEndian<quint16>(header.wave.bitsPerSample));
            m_fileFormat.setSampleType(bps == 8 ? QAudioFormat::UnSignedInt : QAudioFormat::SignedInt);
        }
        else {
            result = false;
        }
    }
    m_NormalHeaderLength = pos();
    qDebug() << "m_headerLength : " << m_NormalHeaderLength;
    return result;
}

bool WavFile::readListHead()
{
    seek(sizeof(CombinedHeader));
    ListHeader tempHead;
    m_nListHeadSize = -1;

    bool result = read(reinterpret_cast<char*>(&tempHead), sizeof(tempHead)) == sizeof(tempHead);
    if (result)
    {
        if (memcmp(&tempHead.descriptor.id, "LIST", 4) == 0)
        {
            m_nListHeadSize = tempHead.descriptor.size;
            return true;
        }
    }

    return false;

}

bool WavFile::readDataHead()
{   
    m_nDataHeadPos  = -1;    
    m_nDataSize     = -1;
    if (m_bListHeadExist)
    {
        m_nDataHeadPos = sizeof(CombinedHeader) + sizeof(chunk) + m_nListHeadSize ;
    }
    else
    {
        m_nDataHeadPos = sizeof(CombinedHeader);
    }

    seek(m_nDataHeadPos);
    chunk tempHead;

    bool result = read(reinterpret_cast<char*>(&tempHead), sizeof(chunk)) == sizeof(chunk);
    if (result)
    {
        if (memcmp(&tempHead.id, "data", 4) == 0)
        {
            m_nDataSize = tempHead.size;
            m_nDataBuffPos = m_nDataHeadPos + sizeof(chunk);
            return true;
        }
    }

    return false;

}

bool WavFile::loadWavData(ST_WavRawData& rawData)
{
    if (m_nDataBuffPos == -1 || m_nDataSize <= 0)
    {
        qDebug() << QString("WavFile::loadWavData() : invalid load case dataBuffPos : %1 dataSize : %2").arg(m_nDataBuffPos).arg(m_nDataSize);
        return false;
    }
    
    int channelCount    = rawData.fileTag.ChannelNum;
    int sampleSize      = rawData.fileTag.BitBerSample;
    int totalPoint      = m_nDataSize / (sampleSize / 8);
    int pointPerChannel = totalPoint  / channelCount;


    if (channelCount == 1)
    {
        rawData.LeftChannel     = QVector<int>(pointPerChannel, 0);
        rawData.RightChannel.clear();
    }
    else if(channelCount == 2)
    {
        rawData.LeftChannel     = QVector<int>(pointPerChannel, 0);
        rawData.RightChannel    = QVector<int>(pointPerChannel, 0);
    }
    else
    {
        return false;
    }

    int pointReadPerTime    = 1024;
    int totalReadTime       = ((totalPoint - 1) / pointReadPerTime) + 1;

    for (int currentReadTime = 0; currentReadTime < totalReadTime; currentReadTime++)
    {
        int currentStartPos = currentReadTime * pointReadPerTime;
        int currentEndPos   = qMin(totalPoint - 1, currentStartPos + pointReadPerTime - 1);
        int readCount       = currentEndPos - currentStartPos + 1;

        QVector<int> tempVec;

        bool readState = getUInt16FromRawData(currentStartPos, readCount, tempVec);

        if (!readState)
        {
            emit sgn_loadRawDataState(currentEndPos, totalPoint, true, QString("∂¡»°¥Æ %1  ß∞‹").arg(currentReadTime));
            return false;
        }

        emit sgn_loadRawDataState(currentEndPos, totalPoint, false, QString());

        for (int tempVecPos = 0; tempVecPos < tempVec.size(); tempVecPos++)
        {
            int currentVal = tempVec[tempVecPos];
            int posInData = tempVecPos + currentStartPos;

            if (channelCount == 1)
            {
                rawData.LeftChannel[posInData] = currentVal;
            }
            else if (channelCount == 2)
            {
                bool posInLeft      = (posInData % 2 == 0);
                int posInChannel    =  posInData / 2;
                if (posInLeft)
                {
                    rawData.LeftChannel[posInChannel]   = currentVal;
                }
                else
                {
                    rawData.RightChannel[posInChannel]  = currentVal;
                }
            }
        }
    }
    emit sgn_loadRawDataState(totalPoint, totalPoint, false, QString());
    return true;

}

bool WavFile::getUInt16FromRawData(int startPos, int numberCount, QVector<int>& result)
{

    if (true)
    {
        qDebug() << QString("WavFile::getUInt16FromRawData: startPos %1 askDataCount : %2 ").arg(startPos).arg(numberCount);
    }
    
    result.clear();
    result = QVector<int>(numberCount,0);

    seek(m_nDataBuffPos + startPos * 2);

    QByteArray readArray = read(numberCount * 2);
    int getInt16Count = readArray.size() / 2;

    if (getInt16Count != numberCount)
    {
        qDebug() << QString("WavFile::getUInt16FromRawData: data notEnough! getData : %1 ").arg(getInt16Count);
        return false;
    }

    const qint16* base = reinterpret_cast<const qint16*>(readArray.constData());

    for (int index = 0; index < getInt16Count; index++)
    {
        qint16 val = base[index];
        result[index] = val;
    }
    return true;

}

void WavFile::resetMediaPlayer()
{
    if (m_mediaPlayer != nullptr)
    {
        m_mediaPlayer->stop();
        delete m_mediaPlayer;
        m_mediaPlayer = nullptr;
    }

    m_mediaPlayer = new QMediaPlayer(this);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &WavFile::slot_MediaPlayerPosChanged);

}

void WavFile::slot_MediaPlayerPosChanged(qint64 pos)
{
    QTime newPos = QTime(0, 0, 0).addMSecs(pos);
    qDebug() << "WavFile::slot_MediaPlayerPosChanged : " << newPos.toString("mm.ss.zzz");
    emit sgn_WavPosChanged(newPos);
}

void WavFile::seekToTime(QTime time)
{
    resetMediaPlayer();
    int totalMsec = QTime(0, 0, 0).msecsTo(time);
    QString fileName = this->fileName();
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
    m_mediaPlayer->setPosition(totalMsec);
    m_mediaPlayer->setVolume(100);
    m_mediaPlayer->play();
}

void WavFile::stopMediaPlayer()
{
    if (m_mediaPlayer != nullptr)
    {
        m_mediaPlayer->stop();
    }
}