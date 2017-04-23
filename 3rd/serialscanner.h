#include <QObject>
#include <QSerialPortInfo>
#include <QSet>
#ifndef SERIALSCANNER_H
#define SERIALSCANNER_H



class SerialScanner : public QObject
{
    Q_OBJECT
public:
    explicit SerialScanner(QObject *parent = 0);

private:

    QSerialPortInfo * serialPortInfo;

    QList<QString> updateCOMList();
    QList<QString> currentCOMList;
    QList<QString> startedCOMList;


public slots:
    void scannSerialPorts();

signals:
    void scannSignal(const int &status, const QSet<QString> &coms);





};

#endif // SERIALSCANNER_H
