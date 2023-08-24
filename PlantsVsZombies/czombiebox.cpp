#include "czombiebox.h"
#include "czombie.h"
#include "czombiebasic.h"
#include "GameConfig.h"

CZombieBox::CZombieBox(QWidget *parent) : QWidget(parent)
{

}

// 显示所有存活的僵尸
void CZombieBox::ShowAllZombie(QPainter *painter)
{
//    list<CZombie*>::iterator ite = m_lstZombieBox.begin();
//    while (ite != m_lstZombieBox.end()) {
//        (*ite)->ShowZombie();
//        ite++;
//    }
    for (CZombie* pZom : m_lstZombieBox) {
        pZom->ShowZombie(painter);
    }
}

// 显示死掉的僵尸
void CZombieBox::ShowAllDieZombie(QPainter *painter)
{
    for (CZombie* pZom : m_lstDieZombieBox) {
        pZom->ShowDieZombie(painter);
    }
}

// 移动所有存活的僵尸
void CZombieBox::MoveAllZombie()
{
    list<CZombie*>::iterator ite = m_lstZombieBox.begin();
    while (ite != m_lstZombieBox.end()) {
        if (*ite) {
            if (typeid(**ite) == typeid(CZombieBasic)) {
                (*ite)->MoveZombie();
            }
        }
        ++ite;
    }
}
