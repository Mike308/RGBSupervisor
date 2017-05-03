#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QKeyEvent>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QIcon temperatureIcon(":/ico/res/thermometer_snowflake.ico");
    QIcon ico(":/ico/res/colours_rgb.ico");
    QMenu * contextMenu = new QMenu("Show temperature");
    QAction *temperatureNotificationAction = contextMenu->addAction(temperatureIcon,"Show temperature");




    ui->setupUi(this);
    animationsSetupDialog = new AnimationsSetup();
    mainController = new MainController();
    serialDetector = new SerialDetector();
    timer = new QTimer();
    dialog = new QColorDialog();

    tray = new QSystemTrayIcon(ico,this);
    tray->show();
    tray->setContextMenu(contextMenu);

    this->setWindowIcon(ico);
    animationsSetupDialog->setWindowIcon(ico);
    dialog->setWindowIcon(ico);


    connect(animationsSetupDialog,SIGNAL(parametersSetup(int&,int&,int&)),this,SLOT(getSetup(int&,int&,int&)));
    connect(serialDetector,SIGNAL(onDetect(int,QSet<QString>)),this,SLOT(onDetected(int,QSet<QString>)));
    connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));
    connect(mainController,SIGNAL(onGetTemp(float)),this,SLOT(onGetTempSlot(float)));
    connect(dialog,SIGNAL(currentColorChanged(QColor)),this,SLOT(onColorGet(QColor)));
    connect(temperatureNotificationAction,SIGNAL(triggered(bool)),this,SLOT(showTemperatureNotification()));



    QSerialPortInfo serialPortInfo;
    QList<QSerialPortInfo> availablePorts = serialPortInfo.availablePorts();


    foreach (QSerialPortInfo availablePort, availablePorts){

        ui->serialCombo->addItem(availablePort.portName());


    }









}





MainWindow::~MainWindow()
{
    delete ui;
    delete mainController;
    delete animationsSetupDialog;
    delete dialog;
    delete tray;


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

           ui->serialCombo->clear();
           ui->serialCombo->addItem(comName);
           ui->serialCombo->setCurrentText(comName);

        }else{


            mainController->disconnect();
            ui->pushButton_2->setText("Connect");
            timer->stop();
            qDebug () << "Disconnected...";
            tray->show();
            tray->showMessage("Infomration","Device disconnected");
           // ui->serialCombo->removeItem(ui->serialCombo->ind);

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



}

void MainWindow::on_hsvDial_actionTriggered(int action)
{


}

void MainWindow::on_pushButton_2_clicked()
{
    if (!mainController->isControllerConnected()){

        mainController->connectToController(ui->serialCombo->currentText(),9600);
        mainController->setRGB(0,0,0);
        mainController->temperatureRequest();
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

void MainWindow::showTemperatureNotification(){

    tray->show();
    tray->showMessage("Temperature","Temperature: "+QString::number(ui->lcdNumber->value()));

}
