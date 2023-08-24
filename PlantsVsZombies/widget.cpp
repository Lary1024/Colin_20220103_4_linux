#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <qDebug>
#include <QMouseEvent>
#include <iostream>
#include <windows.h>
#include "cplantvszombieapp.h"
#include <QPainter>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 初始化游戏背景
    //m_back.InitBackGround();
    // 初始化游戏菜单界面
    //m_gamemenu.InitGameMenu();
}

Widget::~Widget()
{
    delete ui;
}

// 重写绘画事件
void Widget::paintEvent(QPaintEvent *event)
{
    qDebug() << __func__;

    QPainter painter(this); // 问问chatgpt为什么要有这个this?

    // 绘制游戏菜单图片
    painter.drawPixmap(0,0,800,600,m_pix);


    // 显示游戏背景
    // m_back.ShowBackGround(&painter);

    // 显示游戏菜单
    //m_gamemenu.ShowGameMenu(&painter);
}

// 重写鼠标事件
void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << __func__;
//    if( event->button() == Qt::LeftButton ){ //如果是鼠标左键按下：
//        cout << "x:" << event->x() << " y:" << event->y() << endl;
//        // 开始冒险的区域：左上：393 112 右上：703 112 左下：392 222 右下：690 222
//    }
    int x = event->x();
    int y = event->y();
    if (393 <= x && x <= 703 && 112 <= y && y <= 222) {
        //game start
        //Sleep(3000); // 按正常游戏来说，这里点击开始游戏之后，首先放BGM过了3秒再进入游戏
        Q_EMIT SIG_gamestart();
    }
}

void Widget::InitGameMenu()
{
    qDebug() << __func__;
    // 加载游戏菜单的图片(选择开始游戏的菜单)
    bool flag = m_pix.load(":/res/game_menu.png");
}
