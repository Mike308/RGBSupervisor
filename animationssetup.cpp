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
