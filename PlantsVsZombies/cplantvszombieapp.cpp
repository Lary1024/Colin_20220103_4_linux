#include "cplantvszombieapp.h"
#include <QDebug>
#include <QTimer>
#include "GameConfig.h"

CPlantVsZombieApp::CPlantVsZombieApp(QWidget *parent) : QWidget(parent)
{
    qDebug() << __func__;
    widget.InitGameMenu();
    widget1.InitBackGround();
    widget.show();
    setMyTimer();
    QObject::connect(&widget, SIGNAL(SIG_gamestart()), this, SLOT(slot_gamestart()));
    QObject::connect(this, SIGNAL(SIG_backgroundmove_right()), &widget1, SLOT(slot_backgroundmove_right()));
}

CPlantVsZombieApp::~CPlantVsZombieApp()
{

}

void CPlantVsZombieApp::slot_gamestart()
{
    qDebug() << __func__;
    widget.hide();
    widget1.show();
    Q_EMIT SIG_backgroundmove_right();
}

void CPlantVsZombieApp::setMyTimer()
{
    qDebug() << __func__;

//    QTimer *moveBackGroundTimer = new QTimer(this);
//    moveBackGroundTimer->setInterval(TIMER_MOVE_BACKGROUND);

//    connect(moveBackGroundTimer, SIGNAL(timeout()), &widget1, SLOT(MoveBackGround()));

//    moveBackGroundTimer->start(10);


}
