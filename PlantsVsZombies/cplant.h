#ifndef CPLANT_H
#define CPLANT_H

#include <QWidget>
#include <QPainter>

class CPlant : public QWidget
{
    Q_OBJECT
public:
    int m_blood;
    int m_cost;
    int m_x;
    int m_y;
    QMovie* m_movie;
    QImage m_currentFrame;
public:
    explicit CPlant(QWidget *parent = nullptr);
    ~CPlant();

public:
    virtual void InitPlant() = 0;
    virtual void ShowPlant(QPainter* painter);
signals:

public slots:
    void slot_updateFrame();
};

#endif // CPLANT_H
