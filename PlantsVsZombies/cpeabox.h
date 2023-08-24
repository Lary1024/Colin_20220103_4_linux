#ifndef CPEABOX_H
#define CPEABOX_H

#include <QWidget>
#include <list>
#include "cpea.h"

using namespace std;

class CPeaBox : public QWidget
{
    Q_OBJECT
public:
    explicit CPeaBox(QWidget *parent = nullptr);
    ~CPeaBox();
signals:

public slots:

public:
    list<CPea*> m_lstPeaBox;
public:
    void ShowAllPea(QPainter *painter);
    void MoveAllPea();
};

#endif // CPEABOX_H
