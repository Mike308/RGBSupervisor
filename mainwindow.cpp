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
    mainController = new MainController();
    serialDetector = new SerialDetector();
    timer = new QTimer();

    connect(animationsSetupDialog,SIGNAL(parametersSetup(int&,int&,int&)),this,SLOT(getSetup(int&,int&,int&)));
    connect(serialDetector,SIGNAL(onDetect(int,QSet<QString>)),this,SLOT(onDetected(int,QSet<QString>)));
    connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));
    connect(mainController,SIGNAL(onGetTemp(float)),this,SLOT(onGetTempSlot(float)));

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
    QTimer::singleShot(1000,this,SLOT(setRGBSlot()));
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

    timer->stop();
    mainController->setRGB(ui->rSlider->value(),ui->gSlider->value(),ui->bSlider->value());
    qDebug () << "Fire: " << ui->rSlider->value();
    timer->start(10000);
}







void MainWindow::on_serialCombo_activated(const QString &arg1)
{




}

void MainWindow::on_serialCombo_highlighted(const QString &arg1)
{

}

void MainWindow::on_dial_actionTriggered(int action)
{
    QColor color;
    QPalette pal;
    color.setHsv(ui->hsvDial->value(),100,100);
    pal.setBrush(QPalette::Background,color);


}

void MainWindow::on_hsvDial_actionTriggered(int action)
{
    QColor color;
    QColor rgbColor;
    QPalette pal;
    color.setHsv(ui->hsvDial->value(),100,100);
    pal.setBrush(QPalette::Background,color);
    rgbColor = color.toRgb();
    ui->colorProbe->setPalette(pal);
    ui->colorProbe->setAutoFillBackground(true);
    ui->rSlider->setValue(color.red());
    ui->gSlider->setValue(color.green());
    ui->bSlider->setValue(color.blue());

}

void MainWindow::on_pushButton_2_clicked()
{
    if (!mainController->isControllerConnected()){

        mainController->connectToController(ui->serialCombo->currentText(),9600);
        mainController->setRGB(0,0,0);
        ui->pushButton_2->setText("Disconnect");
        timer->start(10000);


    }else {

        mainController->disconnect();
        ui->pushButton_2->setText("Connect");
        timer->stop();

    }

}

void MainWindow::onTick(){

    mainController->temperatureRequest();

}

void MainWindow::onGetTempSlot(float temperature){

    ui->lcdNumber->display(temperature);
}



void MainWindow::on_pushButton_3_clicked()
{

    dialog->setOption(QColorDialog::NoButtons);
    dialog->setOption(QColorDialog::ShowAlphaChannel);
    dialog->show();



}

void MainWindow::onColorGet(QColor color){

    ui->rSlider->setValue(color.red());
    ui->gSlider->setValue(color.green());
    ui->bSlider->setValue(color.blue());
}
