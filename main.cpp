#include "mainwindow.h"
#include <QApplication>
#include <QSet>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qRegisterMetaType<QSet<QString>>();
    return a.exec();
}
