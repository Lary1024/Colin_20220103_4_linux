#include "cplantwallnut.h"
#include <QMovie>
#include "widget1.h"

CPlantWallNut::CPlantWallNut()
{

}

// 初始化坚果墙
void CPlantWallNut::InitPlant()
{
    m_movie = new QMovie(":/res/WallNut.gif");
    m_movie->start();
    connect(m_movie, &QMovie::frameChanged, this, &CPlant::slot_updateFrame);

    m_blood = 5;

    m_x = 50 + ((Widget1::m_dragged_X - 40) / 80) * 80;
    m_y = 85 + ((Widget1::m_dragged_Y - 40) / 96) * 96;
}
