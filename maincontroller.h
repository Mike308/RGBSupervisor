#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QSerialPort>
#include <QObject>

class MainController : QObject

{

    Q_OBJECT

public:
    MainController();
    void connectToController(QString comName, int baud);
    void disconnect();
    void setRGB(int r, int g, int b);
    void setHSV(int h, int s, int v);
    void setAnimation(int mode, int speed, int step);



private:
    QSerialPort * serialPort;
    void sendToController(QString command);

};

#endif // MAINCONTROLLER_H
