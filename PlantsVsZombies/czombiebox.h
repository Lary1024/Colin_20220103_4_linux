#ifndef CZOMBIEBOX_H
#define CZOMBIEBOX_H

#include <QWidget>
#include <list>
#include "czombie.h"

using namespace std;

class CZombieBox : public QWidget
{
    Q_OBJECT
public:
    explicit CZombieBox(QWidget *parent = nullptr);

signals:

public slots:

public:
    list<CZombie*> m_lstZombieBox;
    list<CZombie*> m_lstDieZombieBox;
public:
    void ShowAllZombie(QPainter *painter);
    void ShowAllDieZombie(QPainter *painter);
    void MoveAllZombie();
};

#endif // CZOMBIEBOX_H
