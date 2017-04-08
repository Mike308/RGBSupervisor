#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "animationssetup.h"


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

private:
    Ui::MainWindow *ui;
    AnimationsSetup *animationsSetupDialog;

};

#endif // MAINWINDOW_H
