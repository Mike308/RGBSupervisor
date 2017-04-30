#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QKeyEvent>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    animationsSetupDialog = new AnimationsSetup();
    connect(animationsSetupDialog,SIGNAL(parametersSetup(int&,int&,int&)),this,SLOT(getSetup(int&,int&,int&)));
    serialDetector = new SerialDetector();
    connect(serialDetector,SIGNAL(onDetect(int,QSet<QString>)),this,SLOT(onDetected(int,QSet<QString>)));
    mainController = new MainController();
    QSerialPortInfo serialPortInfo;
    QList<QSerialPortInfo> availablePorts = serialPortInfo.availablePorts();

    foreach (QSerialPortInfo availablePort, availablePorts){

        ui->serialCombo->addItem(availablePort.portName());


    }







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
    mainController->setAnimation(type,speed,step);

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
    QTimer::singleShot(1000,this,SLOT(setRGBSlot()));


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
    QTimer::singleShot(10000,this,SLOT(setRGBSlot()));
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
    QTimer::singleShot(1000,this,SLOT(setRGBSlot()));

}


void MainWindow::onDetected(int status, QSet<QString> coms){

    foreach (QString comName, coms) {

        if (status == 1){

           mainController->connectToController(comName,9600);
           qDebug () << "Connected: " << comName;

        }else{


            mainController->disconnect();
            qDebug () << "Disconnected...";

        }

    }









}

void MainWindow::setRGBSlot(){

    mainController->setRGB(ui->rSlider->value(),ui->gSlider->value(),ui->bSlider->value());
    qDebug () << "Fire: " << ui->rSlider->value();
}







void MainWindow::on_serialCombo_activated(const QString &arg1)
{




}

void MainWindow::on_serialCombo_highlighted(const QString &arg1)
{

}
