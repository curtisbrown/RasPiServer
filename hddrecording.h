#ifndef HDDRECORDING_H
#define HDDRECORDING_H

#include <QObject>

class HddRecording : public QObject
{
    Q_OBJECT
public:
    explicit HddRecording(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HDDRECORDING_H