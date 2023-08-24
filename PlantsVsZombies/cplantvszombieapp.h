#ifndef CPLANTVSZOMBIEAPP_H
#define CPLANTVSZOMBIEAPP_H

#include <QWidget>
#include "widget.h"
#include "widget1.h"


class CPlantVsZombieApp : public QWidget
{
    Q_OBJECT
public:
    Widget widget;
    Widget1 widget1;
//    CGameMenu m_gamemenu;
//    CBackGround m_back;
public:
    explicit CPlantVsZombieApp(QWidget *parent = nullptr);
    ~CPlantVsZombieApp();
    void setMyTimer();



signals:
    void SIG_backgroundmove_right();

public slots:
    void slot_gamestart();

};

#endif // CPLANTVSZOMBIEAPP_H
