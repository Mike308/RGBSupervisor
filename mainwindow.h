#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QColorDialog>
#include <3rd/serialdetector.h>
#include <QSystemTrayIcon>


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

    void on_dial_actionTriggered(int action);

    void on_hsvDial_actionTriggered(int action);

    void on_pushButton_2_clicked();

    void onTick();

    void onGetTempSlot(float temperature);

    void onColorGet(QColor color);

    void on_pushButton_3_clicked();

    void showTemperatureNotification();

    void exit();

    void showed();

private:
    Ui::MainWindow *ui;
    AnimationsSetup *animationsSetupDialog;
    QColorDialog *dialog;
    SerialDetector * serialDetector;
    QSerialPort * serialPort;
    MainController * mainController;
    QTimer *timer;
    QSystemTrayIcon *tray;

protected:

    void closeEvent(QCloseEvent * event);







};

#endif // MAINWINDOW_H
