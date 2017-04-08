#include "animationssetup.h"
#include "ui_animationssetup.h"

AnimationsSetup::AnimationsSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationsSetup)
{
    ui->setupUi(this);
}

AnimationsSetup::~AnimationsSetup()
{
    delete ui;
}

void AnimationsSetup::on_pushButton_clicked()
{
    int mode = ui->animationsCombo->currentIndex();
    int speed =  ui->speedSpin->value();
    int step = ui->stepSpin->value();
    emit parametersSetUp(mode,speed,step);


}
