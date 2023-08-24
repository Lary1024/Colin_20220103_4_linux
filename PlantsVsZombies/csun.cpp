#include "csun.h"
#include <QRandomGenerator> // 生成随机数的头文件
#include "GameConfig.h"
#include "widget1.h"
#include <QPropertyAnimation>
#include <iostream>
#include <QDebug>

using namespace std;

CSun::CSun(QWidget *parent) : QLabel(parent)
{
//    this->setFixedSize(50, 50); // 设置阳光贴图的大小
//    this->setPixmap(QPixmap(":/res/Sun.gif")); // 替换为实际的阳光贴图路径
//    this->setScaledContents(true);
    int m_x = 0;
    int m_y = 0;
    int m_fallX = 0;
    int m_fallY = 0;
}

CSun::~CSun()
{
    if (m_movie) {
        delete(m_movie);
        m_movie = nullptr;
    }
}

void CSun::InitSun()
{
    int m_x = QRandomGenerator::global()->bounded(BACKGROUND_WIDTH - SUN_WIDTH);
    int m_y = -SUN_HEIGHT;
    int m_fallX = m_x;
    int m_fallY = QRandomGenerator::global()->bounded(BACKGROUND_HEIGHT - SUN_HEIGHT);


    m_movie = new QMovie(":/res/Sun.gif"); // 替换为实际的动态GIF图像路径
    this->setMovie(m_movie);
    this->setFixedSize(50, 50);
    this->setScaledContents(true);
    m_movie->start();

    connect(this, SIGNAL(SIG_clicked()), this, SLOT(slot_onSunClicked()));
    this->move(m_x, m_y);
    this->show();
    // 创建平移动画，将阳光降落到地图上的随机位置
    QPropertyAnimation* animation_fall = new QPropertyAnimation(this, "pos");
    animation_fall->setDuration(m_fallY * 20); // 动画持续时间（毫秒）
//    animation_fall->setEasingCurve(QEasingCurve::Linear);v = s / t;     m_fallY * 20
//    animation_fall->setEasingCurve(QEasingCurve::InOutQuad);
    animation_fall->setStartValue(this->pos()); // 起始位置
    animation_fall->setEndValue(QPoint(m_fallX, m_fallY)); // 随机位置

    animation_fall->start();

    update();
}

void CSun::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit SIG_clicked(); // 发送点击信号
}

void CSun::slot_onSunClicked()
{
    qDebug() << __func__;
    // 创建平移动画，将阳光移动到左上方的特定位置
    QPropertyAnimation* animation_recycle = new QPropertyAnimation(this, "pos");
    animation_recycle->setDuration(1000); // 动画持续时间（毫秒）
    animation_recycle->setStartValue(this->pos()); // 起始位置
    animation_recycle->setEndValue(QPoint(46, 18)); // 左上方的特定位置 // 画框上特定的位置
    connect(animation_recycle, &QPropertyAnimation::finished, this, &CSun::slot_onAnimationFinished);
    Widget1::m_SunTotal += 25;

    animation_recycle->start();

}

void CSun::slot_onAnimationFinished()
{
    qDebug() << __func__;
    delete(this);
}

void CSun::SunFlower_Create(int x, int y)
{
    qDebug() << __func__;
    int m_x = x;
    int m_y = y;
    int m_fallX = x;
    int m_fallY = y + 70;

    m_movie = new QMovie(":/res/Sun.gif"); // 替换为实际的动态GIF图像路径
    this->setMovie(m_movie);
    this->setFixedSize(50, 50);
    this->setScaledContents(true);
    m_movie->start();

    connect(this, SIGNAL(SIG_clicked()), this, SLOT(slot_onSunClicked()));
    this->move(m_x, m_y);
    this->show();
    // 创建平移动画，将阳光降落到地图上的随机位置
    QPropertyAnimation* animation_fall = new QPropertyAnimation(this, "pos");
    animation_fall->setDuration(2000); // 动画持续时间（毫秒）
//    animation_fall->setEasingCurve(QEasingCurve::Linear);v = s / t;     m_fallY * 20
//    animation_fall->setEasingCurve(QEasingCurve::InOutQuad);
    animation_fall->setStartValue(this->pos()); // 起始位置
    animation_fall->setEndValue(QPoint(m_fallX, m_fallY)); // 随机位置

    animation_fall->start();

    update();

}

