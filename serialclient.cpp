#include "serialclient.h"

#include <QDebug>

SerialClient::SerialClient(QObject *parent) :
    QObject(parent),
    m_data(),
    m_recievePromptString(false),
    m_recieveFrontPanelString(false)
{
    qDebug() << Q_FUNC_INFO;

    connect(&m_serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this, &SerialClient::handleError);
    connect(&m_serial, &QSerialPort::readyRead, this, &SerialClient::readData);
}

void SerialClient::configureSerial(QString name, qint32 baud, QSerialPort::DataBits dataBits,
                                   QSerialPort::Parity parity, QSerialPort::StopBits stopBits,
                                   QSerialPort::FlowControl flowControl)
{
    qDebug() << "Configuring Serial Connection charcteristics";

    m_serial.setPortName(name);
    m_serial.setBaudRate(baud);
    m_serial.setDataBits(dataBits);
    m_serial.setParity(parity);
    m_serial.setStopBits(stopBits);
    m_serial.setFlowControl(flowControl);
}

void SerialClient::openSerialPort()
{
    if (m_serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port configured";
    } else {
        qDebug() << "Open Error: " << m_serial.errorString();
    }
}

void SerialClient::closeSerialPort()
{
    qDebug() << "Disconnecting from Serial Client";
    if (m_serial.isOpen())
        m_serial.close();
}

void SerialClient::writeData(const QByteArray &data)
{
    m_serial.write(data);
}

void SerialClient::readData()
{
    m_data += m_serial.readAll();
    qDebug() << m_data;
    emit dataAvailable();
}

void SerialClient::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qDebug() << "Critical Error:" << m_serial.errorString();
        closeSerialPort();
    }
}

QByteArray SerialClient::data()
{
    return m_data;
}

/*!
 * \brief BtSerialCommands::removeBytes(QByteArray &buffer, QString stringMatched)
 * A command response returns in the format of "$<ANSWER>#XX\n", this
 * function removes a string from the buffer that is specified.
 * \param buffer; the QByteArray in which to remove the value from
 * \param stringMatched; the string to remove from buffer
 * \return N/A
 */
void SerialClient::removeBytesFromReadBuffer(QString stringMatched)
{
    int bytesToRemove = m_data.indexOf(stringMatched) + stringMatched.length();
    qDebug() << "Removing" << bytesToRemove << "bytes from buffer";
    m_data.remove(0, bytesToRemove);
    qDebug() << "New Buffer Contents:" << m_data;
}

void SerialClient::clearDataBuffer()
{
    m_data.clear();
}

bool SerialClient::recieveInfoDialogString() const
{
    return m_recieveInfoDialogString;
}

void SerialClient::setRecieveInfoDialogString(bool recieveInfoDialogString)
{
    m_recieveInfoDialogString = recieveInfoDialogString;
}

bool SerialClient::recieveFrontPanelString() const
{
    return m_recieveFrontPanelString;
}

void SerialClient::setRecieveFrontPanelString(bool recieveFrontPanelString)
{
    m_recieveFrontPanelString = recieveFrontPanelString;
}

bool SerialClient::recievePromptString() const
{
    return m_recievePromptString;
}

void SerialClient::setRecievePromptString(bool processCmdBytes)
{
    m_recievePromptString = processCmdBytes;
}
