#include "cplant.h"
#include <QMovie>

CPlant::CPlant(QWidget *parent) : QWidget(parent)
{

}

CPlant::~CPlant()
{

}

// 触发重绘，更新当前帧
void CPlant::slot_updateFrame()
{
    m_currentFrame = m_movie->currentImage();
    update(); // 触发重绘，更新当前帧
}

// 显示植物
void CPlant::ShowPlant(QPainter *painter)
{
    painter->drawImage(m_x, m_y, m_currentFrame); // 在指定位置绘制植物
    update();
}
