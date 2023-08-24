#ifndef CPLANTPEASHOOTER_H
#define CPLANTPEASHOOTER_H

#include "cplant.h"
#include <time.h>
#include "widget1.h"
#include "cpeabox.h"

class CPlantPeaShooter : public CPlant
{
public:
    CPlantPeaShooter(Widget1* parentWidget, CPeaBox* peabox);
    virtual void InitPlant();
public slots:
    void slot_shoot_pea();
    // void slot_move_pea();

public:
    Widget1* m_parentWidget; // 存储父类的指针
    CPeaBox* m_peabox;
    QTimer* m_shoot_pea_timer; // 发射豌豆的定时器
    //QTimer* m_pea_move_timer; // 豌豆移动的定时器
    // CPeaBox m_peabox;
};

#endif // CPLANTPEASHOOTER_H
