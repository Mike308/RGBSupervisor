#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    animationsSetupDialog = new AnimationsSetup();
    connect(animationsSetupDialog,SIGNAL(parametersSetup(int&,int&,int&)),this,SLOT(getSetup(int&,int&,int&)));
    serialDetector = new SerialDetector();
    connect(serialDetector,SIGNAL(onDetect(int,QSet<QString>)),this,SLOT(onDetected(int,QSet<QString>)));
    serialPort = new QSerialPort(this);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    animationsSetupDialog->show();
}

void MainWindow::getSetup(int &type, int &speed, int &step){

    qDebug () << "Type: " << type << "Speed: " << speed << "Step: " << step;

}

void MainWindow::on_rSlider_valueChanged(int value)
{
    QPalette pal = palette();
    QColor color;
    color.setRgb(ui->rSlider->value(),ui->gSlider->value(),ui->bSlider->value());
    pal.setColor(QPalette::Background,color);
    ui->colorProbe->setPalette(pal);
    ui->colorProbe->setAutoFillBackground(true);
    ui->rLabel->setText(QString::number(value));

}

void MainWindow::on_gSlider_valueChanged(int value)
{
    QPalette pal = palette();
    QColor color;
    color.setRgb(ui->rSlider->value(),ui->gSlider->value(),ui->bSlider->value());
    pal.setColor(QPalette::Background,color);
    ui->colorProbe->setPalette(pal);
    ui->colorProbe->setAutoFillBackground(true);
    ui->gLabel->setText(QString::number(value));
}

void MainWindow::on_bSlider_valueChanged(int value)
{
    QPalette pal = palette();
    QColor color;
    color.setRgb(ui->rSlider->value(),ui->gSlider->value(),ui->bSlider->value());
    pal.setColor(QPalette::Background,color);
    ui->colorProbe->setPalette(pal);
    ui->colorProbe->setAutoFillBackground(true);
    ui->bLabel->setText(QString::number(value));

}


void MainWindow::onDetected(int status, QSet<QString> coms){

    foreach (QString comName, coms) {

        qDebug () << status << " " << comName;

    }

    if (status == 1){

        serialPort->setBaudRate(9600);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->open(QIODevice::ReadWrite);

    }else{

        serialPort->close();
    }







}

void MainWindow::readyRead(){


}







void MainWindow::on_serialCombo_activated(const QString &arg1)
{




}

void MainWindow::on_serialCombo_highlighted(const QString &arg1)
{

}
