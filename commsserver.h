#ifndef COMMSSERVER_H
#define COMMSSERVER_H

#include <QObject>
#include <QString>

#include "serialclient.h"
#include "tsplay.h"
#include "hddrecording.h"

class CommsServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int promptAnswer READ promptAnswer WRITE setPromptAnswer NOTIFY promptAnswerChanged)
    Q_PROPERTY(QString promptQuestion READ promptQuestion WRITE setPromptQuestion)
    Q_PROPERTY(QString frontPanelInfo READ frontPanelInfo WRITE setFrontPanelInfo)

public:
    explicit CommsServer(QObject *parent = nullptr);

signals:
    void displayOperatorPrompt();
    void promptAnswerChanged();
    void displayFrontPanelInfo();
    void stopFrontPanelInfo();
    void stopGuiPrompt();
    void displayInfoDialog();

public slots:
    void ProcessData();

    QString promptQuestion() const;
    void setPromptQuestion(const QString &promptQuestion);

    int promptAnswer() const;
    void setPromptAnswer(int promptAnswer);
    void sendPromptAnswer();
    void sendInfoDialogAnswer();

    QString frontPanelInfo() const;
    void setFrontPanelInfo(const QString &frontPanelInfo);

private:
    SerialClient m_serialClient;
    TsPlay m_tsPlay;
    HddRecording m_hddRecord;

    QString m_promptQuestion;
    int m_promptAnswer;
    QString m_frontPanelInfo;
};

#endif // COMMSSERVER_H
