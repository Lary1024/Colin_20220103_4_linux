#ifndef CZOMBIE_H
#define CZOMBIE_H

#include <QWidget>
#include <QPainter>
#include "cpea.h"
#include "cplant.h"

class CZombie : public QWidget
{
    Q_OBJECT
public:
    explicit CZombie(QWidget *parent = nullptr);
    ~CZombie();
signals:

public:
    int m_x;
    int m_y;
    int m_blood;
    int m_speed;
    int m_showid;

    QMovie* m_movie;
    QImage m_currentFrame;

    QMovie* m_movie_die;
    QImage m_currentFrame_die;

public:
    virtual void InitZombie() = 0;
    virtual bool IsHitPea(CPea *pPea) = 0;
    virtual bool IsHitPlant(CPlant *pPlant) = 0;
    virtual void ShowZombie(QPainter *painter);
    virtual void ShowDieZombie(QPainter *painter);
    void MoveZombie();
public slots:
    void slot_updateFrame();
    void slot_updateFrame_die();

};

#endif // CZOMBIE_H
