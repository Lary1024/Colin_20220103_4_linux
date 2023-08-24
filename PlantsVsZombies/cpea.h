#ifndef CPEA_H
#define CPEA_H

#include <QWidget>
#include <QPainter>

class CPea : public QWidget
{
    Q_OBJECT
public:
    explicit CPea(QWidget *parent = nullptr);
public:
    int m_x;
    int m_y;
    int m_speed;
    QPixmap m_Pea_Pix;
    QPixmap m_Pea_Boom_Pix;
signals:

public:
    void InitPea(int x, int y);
    void ShowPea(QPainter *painter);
    void MovePea();
};

#endif // CPEA_H
