#ifndef TSPLAY_H
#define TSPLAY_H

#include <QObject>
#include <QProcess>

class TsPlay : public QObject
{
    Q_OBJECT
public:
    explicit TsPlay(QObject *parent = nullptr);

signals:

public slots:
    void startTsPlayEthStreaming();
    void stopTsPlayEthStreaming();

private:
    QProcess m_startProcess;
    QProcess m_stopProcess;
};

#endif // TSPLAY_H
