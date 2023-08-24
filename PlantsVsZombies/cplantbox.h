#ifndef CPLANTBOX_H
#define CPLANTBOX_H

#include <QWidget>
#include <list>
#include "cplant.h"

using namespace std;

class CPlantBox : public QWidget
{
    Q_OBJECT
public:
    explicit CPlantBox(QWidget *parent = nullptr);

signals:

public slots:

public:
    list<CPlant*> m_lstPlantBox;
public:
    void ShowAllPlant(QPainter *painter);
};

#endif // CPLANTBOX_H
