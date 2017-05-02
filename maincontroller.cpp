#include "maincontroller.h"
#include <QDebug>

MainController::MainController()
{
    serialPort = new QSerialPort(this);

}



void MainController::connectToController(QString comName, int baud){

    if (!serialPort->isOpen()){

        qDebug () << "Connected to : " << comName;
        serialPort->setPortName(comName);
        serialPort->setBaudRate(baud);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->open(QIODevice::ReadWrite);
        connect(serialPort,SIGNAL(readyRead()),this,SLOT(onRead()));

    }
}

void MainController::sendToController(QString command){

    const QByteArray &commandArray = command.toLocal8Bit();
    serialPort->write(commandArray);


}

void MainController::setRGB(int r, int g, int b){

    sendToController("AT+RGB="+QString::number(r)+","+QString::number(g)+","+QString::number(b)+"\r\n");
    qDebug() << "AT+RGB="+QString::number(r)+","+QString::number(g)+","+QString::number(b)+"\r\n";


}

void MainController::setHSV(int h, int s, int v){

    sendToController("AT+HSV="+QString::number(h)+","+QString::number(s)+","+QString::number(v)+"\r\n");


}

void MainController::setAnimation(int mode, int speed, int step){

    sendToController("AT+ANIM="+QString::number(mode)+","+QString::number(speed)+","+QString::number(step)+"\r\n");

}

void MainController::temperatureRequest(){

    sendToController("AT+TEMP?\r\n");

}



void MainController::disconnect(){

    serialPort->close();

}

bool MainController::isControllerConnected(){

    return serialPort->isOpen();

}


void MainController::onRead(){

    if (serialPort->canReadLine()){

        QString resultStr = QString::fromLatin1(serialPort->readAll());
        qDebug() << "Result: " << resultStr;
        float temperature = resultStr.toFloat();
        emit onGetTemp(temperature);

    }



}










