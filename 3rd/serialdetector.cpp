#include "serialdetector.h"

SerialDetector::SerialDetector()
{
    scannThread = new QThread();
    serialScanner = new SerialScanner();
    serialScanner->moveToThread(scannThread);
    connect(scannThread,SIGNAL(started()),serialScanner,SLOT(scannSerialPorts()));
    connect(serialScanner,SIGNAL(scannSignal(int,QSet<QString>)),this,SLOT(handleResults(int,QSet<QString>)));
    scannThread->start();

}

SerialDetector::~SerialDetector(){

    scannThread->quit();
    scannThread->wait();
}


QSerialPortInfo SerialDetector::getSerialPortInfo(const QString &portName){


     QSerialPortInfo portInfo(portName);


     return portInfo;



}

void SerialDetector::handleResults(const int &status, const QSet<QString> &coms){


    emit onDetect(status,coms);

}


