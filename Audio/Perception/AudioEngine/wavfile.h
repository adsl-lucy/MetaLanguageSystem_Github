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

#ifndef WAVFILE_H
#define WAVFILE_H

#include <QObject>
#include <QFile>
#include <QAudioFormat>
#include <QDataStream>
#include <QMediaPlayer>
#include "../../protocol/protocol_audio.h"

class WavFile : public QFile
{
    Q_OBJECT
public:
    WavFile(QObject* parent = 0);

    //���ļ����Ҷ�ȡ�ļ�ͷ�������Ƿ��ļ�ͷ��ȡ�ɹ�
    bool openAndReadHead(const QString& fileName);
    const QAudioFormat& fileFormat() const;

    //�ļ�ͷ��С�� riff + format + List + data chunk��С
    qint64 headerLength() const;
    //data chunk�ڼ��ص����ݴ�С
    int    WavDataSize();

    bool loadWavData( ST_WavRawData& rawData);
    void seekToTime(QTime time);
    void stopMediaPlayer();

public:signals:
    //���ݼ���״̬
    void sgn_loadRawDataState(int currentByte, int totalByte,bool error,QString errStr);
    void sgn_WavPosChanged(QTime newPos);
private:
    bool readNormalHeader();
    bool readListHead();
    bool readDataHead();

    //��data���ݿ��ж�ȡ��ֵ��д��result�������˴�����ʼλ�ã���ָ�ڼ����㣬һ����16λ��ռ2���ֽڣ���0��ʼ
    //�������һ�������ļ�����ô�����Ҷ���һ�������ĵ�����
    //�������һ��˫�����ļ�����ô��ֵ���о��ǣ��� �� �� �� ...
    bool getUInt16FromRawData(int startPos,int numberCount,QVector<int>& result);

    void resetMediaPlayer();

protected slots:
    void slot_MediaPlayerPosChanged(qint64 pos);

private:
    QAudioFormat m_fileFormat;

    //riffͷ��formatͷ�ĳ���
    qint64 m_NormalHeaderLength = -1;

    //�Ƿ����LIST Chunk
    bool m_bListHeadExist = false;
    //ListChunk�������ݶεĴ�С��������chunk
    int  m_nListHeadSize = -1;

    //������Ƶchunk����ʼλ�ã�������chunk
    int  m_nDataHeadPos = -1;
    //������Ƶ����ʼλ�ã��������data
    int  m_nDataBuffPos = -1;
    //��Ƶ��Ĵ�С������������ͷ��ֻ������
    int  m_nDataSize = -1;

    QMediaPlayer* m_mediaPlayer = nullptr;

};

#endif // WAVFILE_H
