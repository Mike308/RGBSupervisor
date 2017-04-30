#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QSerialPort>
#include <QObject>

class MainController : public QObject

{

    Q_OBJECT

public:
    MainController();
    void connectToController(QString comName, int baud);
    void disconnect();
    void setRGB(int r, int g, int b);
    void setHSV(int h, int s, int v);
    void setAnimation(int mode, int speed, int step);
    bool isControllerConnected();
    void temperatureRequest();



private:
    QSerialPort * serialPort;
    void sendToController(QString command);

public slots:

    void onRead();




signals:

    void onGetTemp(float temperature);

};

#endif // MAINCONTROLLER_H
