#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    animationsSetupDialog = new AnimationsSetup();
    connect(animationsSetupDialog,SIGNAL(parametersSetUp(int&,int&,int&)),this,SLOT(getSetup(int&,int&,int&)));

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
