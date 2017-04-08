#ifndef ANIMATIONSSETUP_H
#define ANIMATIONSSETUP_H

#include <QDialog>

namespace Ui {
class AnimationsSetup;
}

class AnimationsSetup : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationsSetup(QWidget *parent = 0);
    ~AnimationsSetup();

private:
    Ui::AnimationsSetup *ui;

signals:

    void parametersSetUp(int &type, int &speed, int &step);


private slots:
    void on_pushButton_clicked();
};




#endif // ANIMATIONSSETUP_H
