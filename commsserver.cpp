#include "commsserver.h"

#include <QDebug>

CommsServer::CommsServer(QObject *parent) :
    QObject(parent),
    m_promptAnswer(0)
{
    qDebug() << Q_FUNC_INFO;

    connect(&m_serialClient, &SerialClient::dataAvailable, this, &CommsServer::ProcessData);

    connect(this, &CommsServer::promptAnswerChanged, this, &CommsServer::sendPromptAnswer);

    m_serialClient.configureSerial("/dev/ttyUSB0", QSerialPort::Baud115200, QSerialPort::Data8,
                                   QSerialPort::NoParity, QSerialPort::OneStop,
                                   QSerialPort::NoFlowControl);
    m_serialClient.openSerialPort();
}

void CommsServer::ProcessData()
{
    qDebug() << "Buffer contents: " << m_serialClient.data();

    /* Commands being sent here come in the form
     * xxx# where xxx represents the actual command to be
     * used in the switch case below and # signals the
     * end of that string
     */

    // Read to find the "#"
    int index = m_serialClient.data().indexOf('#');
    if (index == -1) {
        return;
    } else {
        qDebug() << "Found \'#\'";
        QList<QByteArray> stringList = m_serialClient.data().split('#');
        QString dataString = stringList.first();

        m_serialClient.removeBytesFromReadBuffer("#");

        if (m_serialClient.recievePromptString()) {
            setPromptQuestion(dataString);
            emit displayOperatorPrompt();
        } else if (m_serialClient.recieveFrontPanelString()) {
            m_serialClient.setRecieveFrontPanelString(false);
            setFrontPanelInfo(dataString);
            emit displayFrontPanelInfo();
        } else {
            SerialClient::PiCommand cmd = (SerialClient::PiCommand) dataString.toInt();
            qDebug() << "CMD to process:" << cmd;

            // Act on the cmd value received
            switch (cmd) {
            case SerialClient::CMD_EXIT:
                qDebug() << "Recieved Exit cmd, quitting";
                exit(EXIT_SUCCESS);
                break;
            case SerialClient::CMD_START_ETHERNET_STREAMING:
                qDebug() << "Recieved \"Start Eth Streaming\"";
                m_tsPlay.startTsPlayEthStreaming();
                break;
            case SerialClient::CMD_STOP_ETHERNET_STREAMING:
                qDebug() << "Recieved \"Stop Eth Streaming\"";
                m_tsPlay.stopTsPlayEthStreaming();
                break;
            case SerialClient::CMD_CHECK_LINK:
                qDebug() << "Recieved \"Test Link\", sending ACK packet...";
                m_serialClient.writeData("ACK#");
                break;
            case SerialClient::CMD_HDD_RECORDING:
                qDebug() << "Recieved \"HDD Record\"";
                break;
            case SerialClient::CMD_OPERATOR_PROMPT:
                qDebug() << "Recieved \"Operator Prompt\"";
                m_serialClient.setRecievePromptString(true);
                break;
            case SerialClient::CMD_OPERATOR_INFO_START:
                qDebug() << "Recieved \"Operator Info Start\"";
                m_serialClient.setRecieveFrontPanelString(true);
                break;
            case SerialClient::CMD_OPERATOR_INFO_STOP:
                qDebug() << "Recieved \"Operator Info Stop\"";
                m_serialClient.setRecieveFrontPanelString(false);
                emit stopFrontPanelInfo();
                break;
            }
        }
    }
}

int CommsServer::promptAnswer() const
{
    return m_promptAnswer;
}

void CommsServer::setPromptAnswer(int promptAnswer)
{
    qDebug() << Q_FUNC_INFO << promptAnswer;
    m_promptAnswer = promptAnswer;
    emit promptAnswerChanged();
}

void CommsServer::sendPromptAnswer()
{
    // re-set process status for next iteration of loop
    m_serialClient.setRecievePromptString(false);

    qDebug() << "Sending prompt response: " << QString("%1").arg(m_promptAnswer == 1 ? "YES" : "NO");
    QByteArray ba = QString::number(m_promptAnswer).toLatin1();
    m_serialClient.writeData(ba);
}

QString CommsServer::promptQuestion() const
{
    return m_promptQuestion;
}

void CommsServer::setPromptQuestion(const QString &promptQuestion)
{
    m_promptQuestion = promptQuestion;
}

QString CommsServer::frontPanelInfo() const
{
    return m_frontPanelInfo;
}

void CommsServer::setFrontPanelInfo(const QString &frontPanelInfo)
{
    m_frontPanelInfo = frontPanelInfo;
}
