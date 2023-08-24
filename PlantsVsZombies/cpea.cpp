#include "cpea.h"
#include "GameConfig.h"

CPea::CPea(QWidget *parent) : QWidget(parent)
{
    m_x = 0;
    m_y = 0;
    m_speed = 0;
}

// 初始化炮弹
void CPea::InitPea(int x, int y)
{
    m_x = x;
    m_y = y;
    m_speed = STEP_MOVE_PEA;
    // 加载豌豆的图片
    m_Pea_Pix.load(":/res/Pea.gif");
    // 加载爆炸豌豆的图片
    m_Pea_Boom_Pix.load(":/res/PeaBoom.png");
}

// 显示炮弹
void CPea::ShowPea(QPainter *painter)
{
    painter->drawPixmap(m_x, m_y, m_Pea_Pix);
    update();
}

// 移动炮弹
void CPea:: MovePea()
{
    m_x += m_speed;
}
