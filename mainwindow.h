#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <3rd/serialdetector.h>

#include "animationssetup.h"
#include "maincontroller.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_pushButton_clicked();
    void getSetup(int &type, int &speed, int &step);

    void on_rSlider_valueChanged(int value);

    void on_gSlider_valueChanged(int value);

    void on_bSlider_valueChanged(int value);

    void on_serialCombo_activated(const QString &arg1);

    void on_serialCombo_highlighted(const QString &arg1);

    void onDetected(int,QSet<QString>);


    void setRGBSlot();





private:
    Ui::MainWindow *ui;
    AnimationsSetup *animationsSetupDialog;
    SerialDetector * serialDetector;
    QSerialPort * serialPort;
    MainController * mainController;



};

#endif // MAINWINDOW_H
