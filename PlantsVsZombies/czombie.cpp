#include "czombie.h"
#include <QMovie>

CZombie::CZombie(QWidget *parent) : QWidget(parent)
{

}
CZombie::~CZombie()
{
//    m_movie->stop();
//    delete m_movie;
}

// 控制僵尸的移动
void CZombie::MoveZombie()
{
   m_x -= m_speed;
}

// 显示僵尸
void CZombie::ShowZombie(QPainter *painter)
{
    painter->drawImage(m_x, m_y, m_currentFrame); // 在指定位置绘制僵尸
    update();
}

// 显示死亡的僵尸，注意这里不仅要显示僵尸的死亡，还要显示僵尸头的掉落
void CZombie::ShowDieZombie(QPainter *painter)
{
    painter->drawImage(m_x, m_y, m_currentFrame_die); // 在指定位置绘制僵尸
    update();
}

// 触发重绘，更新当前帧
void CZombie::slot_updateFrame()
{
    m_currentFrame = m_movie->currentImage();
    update(); // 触发重绘，更新当前帧
}

// 触发重绘，更新当前帧
void CZombie::slot_updateFrame_die()
{
    m_currentFrame_die = m_movie_die->currentImage();
    update(); // 触发重绘，更新当前帧
}
