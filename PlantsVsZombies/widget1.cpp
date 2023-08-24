#include "widget1.h"
#include "ui_widget1.h"
#include <QDebug>
#include "cplantvszombieapp.h"
#include <QPainter>
#include <GameConfig.h>
#include <iostream>
#include <windows.h>
#include <QMouseEvent>
#include <QRect>
#include "czombie.h"
#include "czombiebasic.h"
#include "czombiebox.h"
#include "cplant.h"
#include "cplantbox.h"
#include "cplantpeashooter.h"
#include "cplantsunflower.h"
#include "cplantwallnut.h"

#include <list>
#include <QRandomGenerator>
#include <QPropertyAnimation>

using namespace std;

int Widget1::m_SunTotal = 25;
int Widget1::m_dragged_X = 0;
int Widget1::m_dragged_Y = 0;


Widget1::Widget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget1)
{
    ui->setupUi(this);
    m_x = 0;
    m_y = 0;
    m_dragged_X = 0;
    m_dragged_Y = 0;
    m_bokeh_plant_X = 0;
    m_bokeh_plant_Y = 0;



//    m_SunTotal = 0;
    choicePhase = false;
    gamePhase = false;
    m_TextShowId = 1;
    m_plant_id = 0;

    m_bool_SunFlower_CardPix = false;
    m_bool_PeaShooter_CardPix = false;
    m_bool_DoublePeaShooter_CardPix = false;
    m_bool_IcePeaShooter_CardPix = false;
    m_bool_WallNut_CardPix = false;
    m_bool_Chomper_CardPix = false;
    m_bool_Jalapeno_CardPix = false;
    m_bool_Squash_CardPix = false;

    m_bool_shovelPix = false;

    backgroundmoved = false;
    m_bool_planttablePix = true;
    m_bool_selectplentPix = true;

    m_bool_StartReadyPix = false;
    m_bool_StartSetPix = false;
    m_bool_StartPlantPix = false;

    m_bool_game_officially_begins = false;

    m_bool_isDragging = false;


    //m_back.InitBackGround();
    // 背景向右移的定时器
    m_background_move_right_timer = new QTimer(this);
    connect(m_background_move_right_timer, SIGNAL(timeout()), this, SLOT(slot_backgroundmove_right()));

    // 背景向左移的定时器
    m_background_move_left_timer = new QTimer(this);
    connect(m_background_move_left_timer, SIGNAL(timeout()), this, SLOT(slot_backgroundmove_left()));

    // 显示文字的定时器
    m_changeshowText_timer = new QTimer(this);
    connect(m_changeshowText_timer, SIGNAL(timeout()), this, SLOT(slot_changeshowText()));

    // 生成僵尸的定时器
    m_create_zombie_timer = new QTimer(this);
    connect(m_create_zombie_timer, SIGNAL(timeout()), this, SLOT(slot_create_zombie()));

    // 控制僵尸移动的定时器
    m_zombie_move_timer = new QTimer(this);
    connect(m_zombie_move_timer, SIGNAL(timeout()), this, SLOT(slot_move_zombie()));

    // 控制生成阳光的的定时器
    m_create_sun = new QTimer(this);
    connect(m_create_sun, SIGNAL(timeout()), this, SLOT(slot_create_sun()));

    // 控制豌豆移动的定时器
    m_pea_move_timer = new QTimer(this);
    connect(m_pea_move_timer, SIGNAL(timeout()), this, SLOT(slot_move_pea()));

    // 判断僵尸和植物是否碰撞的定时器
    m_is_Hit_timer = new QTimer(this);
    connect(m_is_Hit_timer, SIGNAL(timeout()), this, SLOT(slot_is_Hit()));

    // 僵尸死亡动画的gif
    m_die_zombie = new QTimer(this);
    connect(m_die_zombie, SIGNAL(timeout()), this, SLOT(slot_die()));

    // 开启鼠标追踪，以便捕捉鼠标移动事件
    setMouseTracking(true);

    m_peabox = new CPeaBox(this); // 给m_peabox分配内存
}

Widget1::~Widget1()
{
    delete ui;
}

// 重写鼠标点击事件
void Widget1::mousePressEvent(QMouseEvent *event)
{
    // qDebug() << __func__;
    // 卡片选择阶段
    if (choicePhase == true) { // 进入选择阶段才会在这里判断选择了什么植物
        int x = event->x();
        int y = event->y();
//        cout << x << " " << y << endl;
        if (20 <= x && x <= 80 && 140 <= y && y <= 225) {
            m_bool_SunFlower_CardPix = true;
            update();
        }
        if (85 <= x && x <= 145 && 140 <= y && y <= 225) {
            m_bool_PeaShooter_CardPix = true;
            update();
        }
        if (150 <= x && x <= 210 && 140 <= y && y <= 225) {
            m_bool_DoublePeaShooter_CardPix = true;
            update();
        }
        if (215 <= x && x <= 275 && 140 <= y && y <= 225) {
            m_bool_IcePeaShooter_CardPix = true;
            update();
        }
        if (280 <= x && x <= 340 && 140 <= y && y <= 225) {
            m_bool_WallNut_CardPix = true;
            update();
        }
        if (345 <= x && x <= 405 && 140 <= y && y <= 225) {
            m_bool_Chomper_CardPix = true;
            update();
        }
        if (410 <= x && x <= 470 && 140 <= y && y <= 225) {
            m_bool_Jalapeno_CardPix = true;
            update();
        }
        if (475 <= x && x <= 535 && 140 <= y && y <= 225) {
            m_bool_Squash_CardPix = true;
            update();
        }

        // 判断是否点击开始排队（开始游戏）
        // cout << x << " " << y << endl;
        if (192 <= x && x <= 362 && 563 <= y && y <= 596) {
            cout << "start party!!!" << endl;

            m_bool_selectplentPix = false;
            slot_backgroundmove_left();
            choicePhase = false;
            gamePhase = true;

        }
        cout << x << " " << y << endl;
    }
    // 游戏阶段
    if (gamePhase == true) {
        int x = event->x();
        int y = event->y();
        cout << x << " " << y << endl;
        // 太阳花
        if (122 <= x && x <= 182 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_draggedPlant_Pix = m_SunFlower_Pix;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 1;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 豌豆射手
        if (187 <= x && x <= 247 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_draggedPlant_Pix = m_PeaShooter_Pix;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 2;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 双重豌豆射手
        if (252 <= x && x <= 312 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 3;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 寒冰豌豆射手
        if (317 <= x && x <= 377 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 4;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 坚果
        if (382 <= x && x <= 442 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 5;
            m_draggedPlant_Pix = m_WallNut_Pix;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 食人花
        if (447 <= x && x <= 507 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_draggedPlant_Pix = m_Chomper_Pix;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 6;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 辣椒
        if (512 <= x && x <= 572 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 7;
            //m_draggedPlantPos = event->pos();
            update();
        }
        // 倭瓜
        if (577 <= x && x <= 637 && 7 <= y && y <= 92) {
            m_bool_isDragging = true;
            m_dragged_X = event->x();
            m_dragged_Y = event->y();
            m_plant_id = 8;
            //m_draggedPlantPos = event->pos();
            update();
        }
    }
}

// 重写鼠标移动事件
void Widget1::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bool_isDragging) {
        // m_draggedPlantPos = event->pos();
        m_dragged_X = event->x();
        m_dragged_Y = event->y();

        // 根据当前的m_plant_id来判断虚化放置什么植物
        m_bokeh_plant_X = 50 + ((Widget1::m_dragged_X - 40) / 80) * 80;
        m_bokeh_plant_Y = 85 + ((Widget1::m_dragged_Y - 40) / 96) * 96;

        update();
    }
}


// m_x = 50 + ((Widget1::m_dragged_X - 40) / 80) * 80;
// m_y = 85 + ((Widget1::m_dragged_Y - 40) / 96) * 96;


// 重写鼠标释放事件
void Widget1::mouseReleaseEvent(QMouseEvent * event)
{
    if (m_bool_isDragging) {
        m_bool_isDragging = false;
        // 将植物放置在鼠标的位置
        switch (m_plant_id) {
            case SUNFLOWER : {
                if (m_SunTotal >= COST_SUNFLOWER) {

                    if ( arr[(m_dragged_X - 40) / 80][(m_dragged_Y - 40) / 96] == 0) {
                        m_SunTotal -= COST_SUNFLOWER;
                        CPlant *pPlant = new CPlantSunFlower(this);
                        // 将数组置 1
                        arr[(m_dragged_X - 40) / 80][(m_dragged_Y - 40) / 96] = 1;
                        pPlant->InitPlant();

                        m_plantbox.m_lstPlantBox.push_back(pPlant);
                    }
                }

                break;
            }
            case PEASHOOTER : {
                if (m_SunTotal >= COST_PEASHOOTER) {
                    if ( arr[(m_dragged_X - 40) / 80][(m_dragged_Y - 40) / 96] == 0) {
                    m_SunTotal -= COST_PEASHOOTER;
                    CPlant *pPlant = new CPlantPeaShooter(this, m_peabox);
                    arr[(m_dragged_X - 40) / 80][(m_dragged_Y - 40) / 96] = 1;
                    pPlant->InitPlant();
                    m_pea_move_timer->start(SHOOT_MOVE_TIME);
                    m_plantbox.m_lstPlantBox.push_back(pPlant);
                    }
                }

                break;
            }
            case DOUBLEPEASHOOTER : {

                break;
            }
            case ICEPEASHOOTER : {

                break;
            }
            case WALLNUT : {
                if (m_SunTotal >= COST_WALLNUT) {
                    if ( arr[(m_dragged_X - 40) / 80][(m_dragged_Y - 40) / 96] == 0) {
                    m_SunTotal -= COST_WALLNUT;
                    CPlant *pPlant = new CPlantWallNut;
                    arr[(m_dragged_X - 40) / 80][(m_dragged_Y - 40) / 96] = 1;
                    pPlant->InitPlant();
                    m_plantbox.m_lstPlantBox.push_back(pPlant);
                    }
                }

                break;
            }
            case CHOMPER : {

                break;
            }
            case JALAPENO : {

                break;
            }
            case SQUASH : {

                break;
            }
            default : {
                break;
            }
        }
    }
}

// 重写绘制事件
void Widget1::paintEvent(QPaintEvent *event)
{
    // qDebug() << __func__;

    QPainter painter(this); // 问问chatgpt为什么要有这个this?


    painter.drawPixmap(m_x, m_y, 1400, 600, m_backgroudPix);
    // 显示游戏背景
    //m_back.ShowBackGround(&painter);
    if (backgroundmoved) {

        // 显示游戏文字
        {
            // 出现的顺序是Ready Set Plant!
            if (m_bool_StartReadyPix) {
                painter.drawPixmap(250,250,333,111, m_StartReadyPix);
            }

            if (m_bool_StartSetPix) {
                painter.drawPixmap(250,250,333,111, m_StartSetPix);
            }

            if (m_bool_StartPlantPix) {
                painter.drawPixmap(250,250,333,111, m_StartPlantPix);
            }
        }

        // 显示游戏背景
        {
            // 展示植物选择的框(上方)
            if (m_bool_selectplentPix) {
                painter.drawPixmap( 20, 100, 520, 513, m_selectplentPix);
            }

            // 展示植物待选的框(下方)
            if (m_bool_planttablePix) {
                painter.drawPixmap( 20, 0, 650, 100, m_planttablePix);
            }

            // 展示阳光的数值
            painter.setPen(QPen(Qt::black, 5)); // 设置绘制字体的颜色和线宽
            QRect rect = QRect(67, 80, 25, 20); // 设置绘制文本的区域
            QString SunTotalString = QString::number(m_SunTotal); // 将阳光数值转换成字符串
            painter.drawText(rect, SunTotalString);

            // 展示铲子
            if (m_bool_shovelPix) {
                painter.drawPixmap( 672, 0, 88, 88, m_shovelPix);
            }
        }

        // 展示植物卡片
        {
            if (!m_bool_game_officially_begins) {
                if (m_bool_SunFlower_CardPix) {
                    painter.drawPixmap( 122, 7, 60, 85, m_SunFlower_CardPix);
                } else {
                    painter.drawPixmap( 20, 140, 60, 85, m_SunFlower_CardPix);
                }

                if (m_bool_PeaShooter_CardPix) {
                    painter.drawPixmap( 187, 7, 60, 85, m_PeaShooter_CardPix);
                } else {
                    painter.drawPixmap( 85, 140, 60, 85, m_PeaShooter_CardPix);
                }

                if (m_bool_DoublePeaShooter_CardPix) {
                    painter.drawPixmap( 252, 7, 60, 85, m_DoublePeaShooter_CardPix);
                } else {
                    painter.drawPixmap( 150, 140, 60, 85, m_DoublePeaShooter_CardPix);
                }

                if (m_bool_IcePeaShooter_CardPix) {
                    painter.drawPixmap( 317, 7, 60, 85, m_IcePeaShooter_CardPix);
                } else {
                    painter.drawPixmap( 215, 140, 60, 85, m_IcePeaShooter_CardPix);
                }

                if (m_bool_WallNut_CardPix) {
                    painter.drawPixmap( 382, 6, 60, 85, m_WallNut_CardPix);
                } else {
                    painter.drawPixmap( 280, 140, 60, 85, m_WallNut_CardPix);
                }

                if (m_bool_Chomper_CardPix) {
                    painter.drawPixmap( 447, 7, 60, 85, m_Chomper_CardPix);
                } else {
                    painter.drawPixmap( 345, 140, 60, 85, m_Chomper_CardPix);
                }

                if (m_bool_Jalapeno_CardPix) {
                    painter.drawPixmap( 512, 7, 60, 85, m_Jalapeno_CardPix);
                } else {
                    painter.drawPixmap( 410, 140, 60, 85, m_Jalapeno_CardPix);
                }

                if (m_bool_Squash_CardPix) {
                    painter.drawPixmap( 577, 7, 60, 85, m_Squash_CardPix);
                } else {
                    painter.drawPixmap( 475, 140, 60, 85, m_Squash_CardPix);
                }
            } else {
                // 正式进入游戏后对植物卡片的绘制
                if (m_bool_SunFlower_CardPix) {
                    if (m_SunTotal < COST_SUNFLOWER) {
                        painter.setOpacity(0.5); // 设置透明度为0.5，实现阴影效果
                    }
                    painter.drawPixmap( 122, 7, 60, 85, m_SunFlower_CardPix);
                    painter.setOpacity(1); // 恢复正常
                } else {
                    painter.drawPixmap( 20, 140, 60, 85, m_SunFlower_CardPix);
                }

                if (m_bool_PeaShooter_CardPix) {
                    if (m_SunTotal < COST_PEASHOOTER) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 187, 7, 60, 85, m_PeaShooter_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 85, 140, 60, 85, m_PeaShooter_CardPix);
                }

                if (m_bool_DoublePeaShooter_CardPix) {
                    if (m_SunTotal < COST_DOUBLEPEASHOOTER) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 252, 7, 60, 85, m_DoublePeaShooter_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 150, 140, 60, 85, m_DoublePeaShooter_CardPix);
                }

                if (m_bool_IcePeaShooter_CardPix) {
                    if (m_SunTotal < COST_ICEPEASHOOTER) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 317, 7, 60, 85, m_IcePeaShooter_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 215, 140, 60, 85, m_IcePeaShooter_CardPix);
                }

                if (m_bool_WallNut_CardPix) {
                    if (m_SunTotal < COST_WALLNUT) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 382, 6, 60, 85, m_WallNut_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 280, 140, 60, 85, m_WallNut_CardPix);
                }

                if (m_bool_Chomper_CardPix) {
                    if (m_SunTotal < COST_CHOMPER) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 447, 7, 60, 85, m_Chomper_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 345, 140, 60, 85, m_Chomper_CardPix);
                }

                if (m_bool_Jalapeno_CardPix) {
                    if (m_SunTotal < COST_JALAPENO) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 512, 7, 60, 85, m_Jalapeno_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 410, 140, 60, 85, m_Jalapeno_CardPix);
                }

                if (m_bool_Squash_CardPix) {
                    if (m_SunTotal < COST_SQUASH) {
                        painter.setOpacity(0.5);
                    }
                    painter.drawPixmap( 577, 7, 60, 85, m_Squash_CardPix);
                    painter.setOpacity(1);
                } else {
                    painter.drawPixmap( 475, 140, 60, 85, m_Squash_CardPix);
                }
                if (m_bool_isDragging) {
                    painter.drawPixmap(m_dragged_X - 30, m_dragged_Y - 30, m_draggedPlant_Pix);
                    painter.setOpacity(0.5);
                    painter.drawPixmap(m_bokeh_plant_X, m_bokeh_plant_Y, m_draggedPlant_Pix);
                    painter.setOpacity(1);
                }
            }

        }

        // 显示僵尸gif
        // test
        m_zombiebox.ShowAllZombie(&painter);
        //painter.drawImage(675, 430, m_currentFrame); // 在指定位置绘制僵尸GIF

        // 显示死亡僵尸gif
        m_zombiebox.ShowAllDieZombie(&painter);

        // 显示植物gif
        m_plantbox.ShowAllPlant(&painter);

        // 显示豌豆
        m_peabox->ShowAllPea(&painter);
    }

}

// 初始化背景(图片)
void Widget1::InitBackGround()
{
    qDebug() << __func__;

    // 加载游戏背景的图片
    m_backgroudPix.load(":/res/background.bmp");
    // 加载植物选择的图片
    m_selectplentPix.load(":/res/SelectPaint.bmp");
    // 加载植物选择列表的图片
    m_planttablePix.load(":/res/planttable.png");

    // 加载太阳花图片
    m_SunFlower_Pix.load(":/res/SunFlower.gif");
    // 加载豌豆射手图片
    m_PeaShooter_Pix.load(":/res/Peashooter.gif");
    // m_DoublePeaShooter_Pix.load("");
    // m_IcePeaShooter_Pix;
    // 加载坚果墙图片
    m_WallNut_Pix.load(":/res/Wallnut_body.png");
    // 加载食人花图片
    m_Chomper_Pix.load(":/res/Chomper.gif");
    // m_Jalapeno_Pix;
    // m_Squash_Pix;

    // 加载太阳花卡片图片
    m_SunFlower_CardPix.load(":/res/SunFlower.png");
    // 加载豌豆射手卡片图片
    m_PeaShooter_CardPix.load(":/res/PeaShooter.png");
    // 加载双重豌豆射手卡片图片
    m_DoublePeaShooter_CardPix.load(":/res/DoublePeaShooter.png");
    // 加载寒冰豌豆射手卡片图片
    m_IcePeaShooter_CardPix.load(":/res/IcePeaShooter.png");
    // 加载坚果墙卡片图片
    m_WallNut_CardPix.load(":/res/WallNut.png");
    // 加载食人花卡片图片
    m_Chomper_CardPix.load(":/res/Chomper.png");
    // 加载辣椒卡片图片
    m_Jalapeno_CardPix.load(":/res/Jalapeno .png");
    // 加载倭瓜卡片图片
    m_Squash_CardPix.load(":/res/Squash.png");

//    // 加载虚化的太阳花图片
//    m_SunFlower_prepare_Pix.load(":/res/sunflower_prepare.bmp");
//    // 加载虚化的豌豆射手图片
//    m_PeaShooter_prepare_Pix.load(":/res/peashooter_prepare.bmp");
//    // 加载虚化的坚果墙图片
//    m_WallNut_prepare_Pix.load(":/res/wallnut_prepare.bmp");

    // 加载铲子的图片
    m_shovelPix.load(":/res/shovel.png");

    // 加载文字的图片
    m_StartReadyPix.load(":/res/StartReady.png");
    m_StartSetPix.load(":/res/StartSet.png");
    m_StartPlantPix.load(":/res/StartPlant.png");

    // 加载gif
    m_movie = new QMovie(":/res/ZombieBasic.gif");
    m_movie->start();
    connect(m_movie, &QMovie::frameChanged, this, &Widget1::slot_updateFrame);
}

// 将背景图片移动到最右边，进行植物的选择
void Widget1::slot_backgroundmove_right()
{
    // qDebug() << __func__;
    m_background_move_right_timer->start(5);

    if (m_x > -600) {
        m_x -= SPEED_MOVE_BACKGROUND;
        // cout << m_x << endl;
        update();  //通知系统更新绘画界面
    } else {
        m_background_move_right_timer->stop();
        backgroundmoved = true;
        choicePhase = 1;
        update();  //通知系统更新绘画界面
    }

}

// 将背景图片移动到最左边，开始游戏
void Widget1::slot_backgroundmove_left()
{
    // qDebug() << __func__;
    m_background_move_left_timer->start(2);

    if (m_x < -200) {
        m_x += SPEED_MOVE_BACKGROUND;
        // cout << m_x << endl;
        update();  //通知系统更新绘画界面
    } else {
        m_background_move_left_timer->stop();
        m_bool_shovelPix = true;

        update();  //通知系统更新绘画界面
        // 启动文字说明的定时器
        m_changeshowText_timer->start(1000);
    }
}

// 展示三段图片(文字)，顺序分别是Ready Set Plant!
void Widget1::slot_changeshowText()
{
    qDebug() << __func__;
    // 定时器每次调用该槽函数的时候增加显示图片的ID，然后每次根据显示图片的ID来设置展示图片的bool类型，当ID大于显示图片的ID的时候关闭定时器
    if (m_TextShowId == 1) {
        m_bool_StartReadyPix = true;
        update();
        m_TextShowId++;
        return;
    }
    if (m_TextShowId == 2) {
        m_bool_StartReadyPix = false;
        m_bool_StartSetPix = true;
        update();
        m_TextShowId++;
        return;
    }
    if (m_TextShowId == 3) {
        m_bool_StartSetPix = false;
        m_bool_StartPlantPix = true;
        update();
        m_TextShowId++;
        return;
    }
    if (m_TextShowId == 4) {
        m_bool_StartPlantPix = false;
        m_bool_game_officially_begins = true;
        m_create_zombie_timer->start(8000);
        m_zombie_move_timer->start(200);
        m_create_sun->start(5000);
        m_is_Hit_timer->start(300);
        m_die_zombie->start(1000);

        update();
        m_changeshowText_timer->stop();
        return;
    }
}

// 触发重绘，更新当前帧
void Widget1::slot_updateFrame()
{
    m_currentFrame = m_movie->currentImage();
    update(); // 触发重绘，更新当前帧
}

// 随机生成僵尸
void Widget1::slot_create_zombie()
{
    qDebug() << __func__;

    CZombie *pZombie = new CZombieBasic;
    pZombie->InitZombie();
    m_zombiebox.m_lstZombieBox.push_back(pZombie);
}

// 随机生成阳光
void Widget1::slot_create_sun()
{
    qDebug() << __func__;
    // CSun* sun;
    CSun* pSun= new CSun(this);
    pSun->InitSun();
}

// 定时移动僵尸
void Widget1::slot_move_zombie()
{
    m_zombiebox.MoveAllZombie();
}

// 定时移动豌豆
void Widget1::slot_move_pea()
{
    m_peabox->MoveAllPea();
}

// 定时判断僵尸和植物是否碰撞、并判断僵尸和豌豆是否碰撞
void Widget1::slot_is_Hit()
{
    // 遍历僵尸盒子链表，判断僵尸和豌豆是否碰撞，判断僵尸和植物是否碰撞
    list<CZombie*>::iterator iteZom = m_zombiebox.m_lstZombieBox.begin();
    while (iteZom != m_zombiebox.m_lstZombieBox.end()) { // 如果迭代器不遍历到end()
        // 遍历炮弹链表，判断僵尸是否撞击豌豆
        list<CPea*>::iterator itePea = m_peabox->m_lstPeaBox.begin();
        while (itePea != m_peabox->m_lstPeaBox.end()) {
            if ((*iteZom)->IsHitPea(*itePea)) { // 调用僵尸的是否碰撞豌豆的方法
                // 撞击到了豌豆
                delete (*itePea); // 回收炮弹
                (*itePea) = nullptr;

                itePea = m_peabox->m_lstPeaBox.erase(itePea); // 回收炮弹节点,注意这里接的是删除的下一个的迭代器

                (*iteZom)->m_blood -= PEA_HURT; // 僵尸掉血
                if((*iteZom)->m_blood <= 0) { // 如果僵尸血量为0，僵尸死亡
                    m_zombiebox.m_lstDieZombieBox.push_back(*iteZom); // 添加到死亡僵尸列表
                    iteZom = m_zombiebox.m_lstZombieBox.erase(iteZom); // 删除正常的敌人飞机节点,注意这里接的是删除的下一个的迭代器

                    break; // 退出内循环(内循环是遍历所有豌豆，外循环是遍历所有僵尸，如果当前僵尸死亡，那么退出内循环，去判断下一个僵尸的情况)
                }
                continue; //如果 撞击了豌豆，回收炮弹节点，并接了删除的下一个的迭代器， 所以结束本轮循环，继续下一轮循环
            }
            itePea++; // 该豌豆没有撞击僵尸，itePea++判断下一个僵尸
        }

        // 遍历植物链表,判断僵尸是否撞击植物
        list<CPlant*>::iterator itePlant = m_plantbox.m_lstPlantBox.begin();
        while (itePlant != m_plantbox.m_lstPlantBox.end()) {
            if (*iteZom) {
                if ((*iteZom)->IsHitPlant(*itePlant)) { // 调用僵尸的是否碰撞植物的方法
                    // 撞击到了植物
                    // 僵尸的移动速度变为0
                    (*iteZom)->m_speed = 0;
                } else {
                     // (*iteZom)->m_speed = 1;
                }
            }
            itePlant++;
        }
        iteZom++;
    }
}

void Widget1::slot_die()
{
    list<CZombie*>::iterator iteDieZom = m_zombiebox.m_lstDieZombieBox.begin();
    while (iteDieZom != m_zombiebox.m_lstDieZombieBox.end()) {
        if (*iteDieZom) {
            (*iteDieZom)->m_showid--;

            if ((*iteDieZom)->m_showid < 0) {
                delete(*iteDieZom);
                (*iteDieZom) = nullptr;

                iteDieZom = m_zombiebox.m_lstDieZombieBox.erase(iteDieZom); // 回收节点
                continue;
            }
        }
        iteDieZom++;
    }
}










