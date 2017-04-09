#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    animationsSetupDialog = new AnimationsSetup();
    connect(animationsSetupDialog,SIGNAL(parametersSetup(int&,int&,int&)),this,SLOT(getSetup(int&,int&,int&)));

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
