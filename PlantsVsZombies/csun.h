#ifndef CSUN_H
#define CSUN_H

#include <QLabel>
#include <QMovie>

class CSun : public QLabel
{
    Q_OBJECT
public:
    explicit CSun(QWidget *parent = nullptr);
    ~CSun();
public:
    QMovie* m_movie;
    int m_x; // 阳光生成的横坐标(随机)0~800
    int m_y; // 阳光生成的纵坐标(-Sun_HEIGHT)
    int m_fallX; // 阳光要落到的目标横坐标(与生成的横坐标一样)
    int m_fallY; // 阳光要落到的目标纵坐标(随机)0~600
signals:
    void SIG_clicked();
public slots:
    void slot_onSunClicked();
    void slot_onAnimationFinished();
public:
    void mousePressEvent(QMouseEvent* event) override;
    void InitSun();
    void SunFlower_Create(int x, int y);

};

#endif // CSUN_H
