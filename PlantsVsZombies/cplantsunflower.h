#ifndef CPLANTSUNFLOWER_H
#define CPLANTSUNFLOWER_H

#include "cplant.h"
#include <time.h>
#include "widget1.h"

class CPlantSunFlower : public CPlant
{
public:
    CPlantSunFlower(Widget1* parentWidget);
    virtual void InitPlant();
public slots:
    void slot_create_sun();
public:
    Widget1* m_parentWidget; // 存储父类的指针
    QTimer* m_create_sun_timer;
};

#endif // CPLANTSUNFLOWER_H
