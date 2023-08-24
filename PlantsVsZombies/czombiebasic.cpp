#include "czombiebasic.h"
#include <QMovie>
#include <QRandomGenerator>
#include "GameConfig.h"

CZombieBasic::CZombieBasic()
{

}

// 初始化普通僵尸
void CZombieBasic::InitZombie()
{
    m_showid = 2;
    m_movie = new QMovie(":/res/ZombieBasic.gif");
    m_movie->start();
    connect(m_movie, &QMovie::frameChanged, this, &CZombie::slot_updateFrame);

    m_movie_die = new QMovie(":/res/ZombieBasicDie.gif");
    m_movie_die->start();
    connect(m_movie_die, &QMovie::frameChanged, this, &CZombie::slot_updateFrame_die);

    m_x = 800;
    // 生成一个随机数
    int randomNum = QRandomGenerator::global()->bounded(5); // 生成0~4之间的随机数
    m_y = 46 + 96 * randomNum;


    m_blood = 5;
    m_speed = 1;
}

// 判断普通僵尸是否碰撞豌豆
bool CZombieBasic::IsHitPea(CPea *pPea)
{
    // 豌豆右边的点x,y
    int x = pPea->m_x + PEA_WIDTH;
    int y = pPea->m_y + PEA_HEIGHT / 2;

    if (m_x <= x && x < m_x + ZOMBIE_BASIC_WIDTH && m_y <= y && y <= m_y + ZOMBIE_BASIC_HEIGHT) {
        return true;
    }
    return false;
}

// 判断普通僵尸是否碰撞植物
bool CZombieBasic::IsHitPlant(CPlant *pPlant)
{
    //
    int x = pPlant->m_x;
    int y = pPlant->m_y + PLANT_HEIGHT / 2;

    if (m_x <= x && x < m_x + ZOMBIE_BASIC_WIDTH && m_y <= y && y <= m_y + ZOMBIE_BASIC_HEIGHT) {
        m_movie = new QMovie(":/res/ZombieBasicEat.gif");
        m_movie->start();
        connect(m_movie, &QMovie::frameChanged, this, &CZombie::slot_updateFrame);
        return true;
    }
    return false;
}
















