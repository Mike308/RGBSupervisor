#ifndef SERIALDETECTOR_H
#define SERIALDETECTOR_H
#include <QObject>
#include <QThread>
#include <QMap>
#include <QList>

#include "serialscanner.h"


class SerialDetector : public QObject
{
    Q_OBJECT
    QThread * scannThread;

public:
    SerialDetector();
    ~SerialDetector();
    QSerialPortInfo getSerialPortInfo(const QString &portName);


private:
    SerialScanner *serialScanner;





public slots:
    void handleResults(const int &status, const QSet<QString> &coms);


signals:

    void onDetect(const int &status, const QSet<QString> &coms);





};

#endif // SERIALDETECTOR_H
