#include "cplantsunflower.h"
#include <QMovie>
#include "csun.h"
#include <QTimer>

CPlantSunFlower::CPlantSunFlower(Widget1* parentWidget) : m_parentWidget(parentWidget)
{
    m_create_sun_timer = new QTimer(this);
    connect(m_create_sun_timer, &QTimer::timeout, this, &CPlantSunFlower::slot_create_sun);
// QObject::connect: No such slot CPlant::slot_create_sun() in ..\PlantsVsZombies\cplantsunflower.cpp:9
    m_create_sun_timer->start(8000);
}

// 初始化太阳花
void CPlantSunFlower::InitPlant()
{
    m_movie = new QMovie(":/res/SunFlower.gif");
    m_movie->start();
    connect(m_movie, &QMovie::frameChanged, this, &CPlant::slot_updateFrame);

    m_blood = 5;

    m_x = 50 + ((Widget1::m_dragged_X - 40) / 80) * 80;
    m_y = 85 + ((Widget1::m_dragged_Y - 40) / 96) * 96;
}

// 生成阳光的的频率为八秒
void CPlantSunFlower::slot_create_sun()
{
    CSun* pSun= new CSun(m_parentWidget);
    pSun->SunFlower_Create(CPlant::m_x, CPlant::m_y);
}
