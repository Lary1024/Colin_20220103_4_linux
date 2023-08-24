#ifndef WIDGET1_H
#define WIDGET1_H

#include <QWidget>
#include <QTimer>
#include <QMovie>
#include <QImage>
#include "czombiebox.h"
#include "cplantbox.h"
#include <time.h>
#include "csun.h"
#include "cpea.h"
#include "cpeabox.h"

namespace Ui {
class Widget1;
}

class Widget1 : public QWidget
{
    Q_OBJECT

public:
//    CSun* sun;
    CZombieBox m_zombiebox;
    CPlantBox m_plantbox;
    CPeaBox *m_peabox;

    QPixmap m_backgroudPix;
    QPixmap m_selectplentPix;
    QPixmap m_planttablePix;

    // 植物卡片的图片对象
    QPixmap m_SunFlower_CardPix;
    QPixmap m_PeaShooter_CardPix;
    QPixmap m_DoublePeaShooter_CardPix;
    QPixmap m_IcePeaShooter_CardPix;
    QPixmap m_WallNut_CardPix;
    QPixmap m_Chomper_CardPix;
    QPixmap m_Jalapeno_CardPix;
    QPixmap m_Squash_CardPix;

    // 植物本体的图片对象
    QPixmap m_SunFlower_Pix;
    QPixmap m_PeaShooter_Pix;
    QPixmap m_DoublePeaShooter_Pix;
    QPixmap m_IcePeaShooter_Pix;
    QPixmap m_WallNut_Pix;
    QPixmap m_Chomper_Pix;
    QPixmap m_Jalapeno_Pix;
    QPixmap m_Squash_Pix;

//    // --- 准备种植前虚化的植物本题图片 ---
//    QPixmap m_SunFlower_prepare_Pix;
//    QPixmap m_PeaShooter_prepare_Pix;
//    QPixmap m_WallNut_prepare_Pix;

    // gif对象
    QMovie* m_movie;
    QImage m_currentFrame;

    // 开始的文字
    QPixmap m_StartReadyPix;
    QPixmap m_StartSetPix;
    QPixmap m_StartPlantPix;

    // 铲子的图片
    QPixmap m_shovelPix;

    int m_x;
    int m_y;
    static int m_SunTotal;
    int m_TextShowId;
    int m_plant_id;

    // 定时器指针
    QTimer* m_background_move_right_timer;
    QTimer* m_background_move_left_timer;
    QTimer* m_changeshowText_timer;
    QTimer* m_create_zombie_timer;
    QTimer* m_create_sun;
    QTimer* m_is_Hit_timer;
    QTimer* m_die_zombie;

    // 定时器控制动画帧率
    QTimer* m_gif_timer;

    // 定时器控制僵尸移动
    QTimer* m_zombie_move_timer;

    // 定时控制炮弹的移动
    QTimer* m_pea_move_timer;

    bool backgroundmoved;
    // 选择阶段的鼠标判定
    bool choicePhase;
    // 游戏阶段的鼠标判定
    bool gamePhase;

    // 控制显示图片的bool类型
    // --- 背景界面 ---
    bool m_bool_planttablePix;
    bool m_bool_selectplentPix;
    bool m_bool_shovelPix;

    // --- 植物卡片 ---
    bool m_bool_SunFlower_CardPix;
    bool m_bool_PeaShooter_CardPix;
    bool m_bool_DoublePeaShooter_CardPix;
    bool m_bool_IcePeaShooter_CardPix;
    bool m_bool_WallNut_CardPix;
    bool m_bool_Chomper_CardPix;
    bool m_bool_Jalapeno_CardPix;
    bool m_bool_Squash_CardPix;

    // --- 文字图片 ---
    bool m_bool_StartReadyPix;
    bool m_bool_StartSetPix;
    bool m_bool_StartPlantPix;

    bool m_bool_game_officially_begins;

    // --- 是否拖动某个植物 ---
    bool m_bool_isDragging;

    // --- 拖动植物的图片 ---（将当前需要拖动的植物的图片赋值给m_draggedPlant_Pix）
    QPixmap m_draggedPlant_Pix;

    // --- 正在拖动的植物图片位置 ---
    // QPoint m_draggedPlantPos;
    static int m_dragged_X;
    static int m_dragged_Y;

    // --- Bokeh 虚化指针的坐标 ---
    int m_bokeh_plant_X;
    int m_bokeh_plant_Y;


    int arr[9][5] = {{0}};

public:
    explicit Widget1(QWidget *parent = nullptr);
    ~Widget1();
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent * event) override;

    virtual void paintEvent(QPaintEvent *event) override;
    void InitBackGround();
public slots:
    void slot_backgroundmove_right();
    void slot_backgroundmove_left();
    void slot_changeshowText();
    void slot_updateFrame();
    void slot_create_zombie();
    void slot_create_sun();
    void slot_move_zombie();
    void slot_move_pea();
    void slot_is_Hit();
    void slot_die();
private:
    Ui::Widget1 *ui;


public:

};

#endif // WIDGET1_H
