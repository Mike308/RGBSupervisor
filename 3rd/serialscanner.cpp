#include "serialscanner.h"
#include <QSerialPortInfo>
#include <QThread>


SerialScanner::SerialScanner(QObject *parent) : QObject(parent)
{

    startedCOMList = this->updateCOMList();
}

QList<QString> SerialScanner::updateCOMList(){

    serialPortInfo = new QSerialPortInfo();

    QList<QSerialPortInfo> comList = serialPortInfo->availablePorts();
    QList<QString> comNames;

    foreach (QSerialPortInfo items, comList) {

        comNames.append(items.portName());


    }

    serialPortInfo->~QSerialPortInfo();

    return comNames;


}

void SerialScanner::scannSerialPorts(){


    while (1) {



        currentCOMList = this->updateCOMList();

        if ((startedCOMList.count()-currentCOMList.count())>0){

            QSet<QString> coms = startedCOMList.toSet().subtract(currentCOMList.toSet());
           // qDebug() << "Something disconnected: ";
            emit scannSignal(0,coms);
            startedCOMList = currentCOMList;


        }else if ((startedCOMList.count()-currentCOMList.count())<0){

            QSet<QString> coms = currentCOMList.toSet().subtract(startedCOMList.toSet());
           // qDebug() <<"Something connected: ";
            emit scannSignal(1,coms);
            startedCOMList = currentCOMList;



        }

        QThread::msleep(100);



    }



}









