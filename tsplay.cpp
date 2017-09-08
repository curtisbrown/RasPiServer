#include "tsplay.h"

#include <QDebug>

TsPlay::TsPlay(QObject *parent) :
    QObject(parent)
{

}

void TsPlay::startTsPlayEthStreaming()
{
    qDebug() << "Starting TsPlay";
    m_startProcess.startDetached("/usr/bin/tsplay -v -maxnowait off -pwait 4 -cwait 1 -loop /root/cbr.ts 192.168.2.200:5000 &");
}

void TsPlay::stopTsPlayEthStreaming()
{
    qDebug() << "Stopping TsPlay";
    m_stopProcess.startDetached("killall tsplay");
}
