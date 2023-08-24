#include "cplantpeashooter.h"
#include <QMovie>
#include "widget1.h"
#include "cpea.h"


CPlantPeaShooter::CPlantPeaShooter(Widget1* parentWidget, CPeaBox* peabox) : m_parentWidget(parentWidget), m_peabox(peabox)
{
    m_shoot_pea_timer = new QTimer(this);
    connect(m_shoot_pea_timer, &QTimer::timeout, this, &CPlantPeaShooter::slot_shoot_pea);
    m_shoot_pea_timer->start(2000);

//    m_pea_move_timer = new QTimer(this);
//    connect(m_pea_move_timer, &QTimer::timeout, this, &CPlantPeaShooter::slot_move_pea);
//    m_pea_move_timer->start(1000);
}


// 初始化豌豆射手
void CPlantPeaShooter::InitPlant()
{
    m_movie = new QMovie(":/res/Peashooter.gif");
    m_movie->start();
    connect(m_movie, &QMovie::frameChanged, this, &CPlant::slot_updateFrame);

    m_blood = 5;

//    m_x = Widget1::m_dragged_X;
//    m_y = Widget1::m_dragged_Y;
    m_x = 50 + ((Widget1::m_dragged_X - 40) / 80) * 80;
    m_y = 85 + ((Widget1::m_dragged_Y - 40) / 96) * 96;
}

// 豌豆射手射出豌豆
void CPlantPeaShooter::slot_shoot_pea()
{
    CPea* pPea = new CPea(m_parentWidget);
    pPea->InitPea(CPlant::m_x, CPlant::m_y);
    m_peabox->m_lstPeaBox.push_back(pPea);
}

//// 移动豌豆
//void CPlantPeaShooter::slot_move_pea()
//{
//    m_peabox->MoveAllPea();
//    // m_peabox->ShowAllPea();
//}
