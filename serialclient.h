#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <QtSerialPort/QSerialPort>
#include <QObject>

class SerialClient : public QObject
{
    Q_OBJECT
public:
    explicit SerialClient(QObject *parent = nullptr);

    typedef enum {
        CMD_EXIT,
        CMD_START_ETHERNET_STREAMING,
        CMD_STOP_ETHERNET_STREAMING,
        CMD_CHECK_LINK,
        CMD_HDD_RECORDING,
        CMD_OPERATOR_PROMPT,
        CMD_OPERATOR_INFO_START,
        CMD_OPERATOR_INFO_STOP,
        CMD_STOP_GUI_DISPLAY,
        CMD_OPERATOR_INFO_DIALOG
    } PiCommand;

    QByteArray data();

    bool recievePromptString() const;
    void setRecievePromptString(bool recievePromptString);

    bool recieveFrontPanelString() const;
    void setRecieveFrontPanelString(bool recieveFrontPanelString);

    bool recieveInfoDialogString() const;
    void setRecieveInfoDialogString(bool recieveInfoDialogString);

signals:
    void dataAvailable();

public slots:
    void configureSerial(QString name, qint32 baud, QSerialPort::DataBits dataBits,
                         QSerialPort::Parity parity, QSerialPort::StopBits stopBits,
                         QSerialPort::FlowControl flowControl);
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void removeBytesFromReadBuffer(QString stringMatched);
    void clearDataBuffer();
private:
    QSerialPort m_serial;
    QByteArray m_data;
    bool m_recievePromptString;
    bool m_recieveFrontPanelString;
    bool m_recieveInfoDialogString;
};

#endif // SERIALCLIENT_H
