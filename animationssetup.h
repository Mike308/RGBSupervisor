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
};

#endif // ANIMATIONSSETUP_H
