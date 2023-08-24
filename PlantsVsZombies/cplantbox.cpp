#include "cplantbox.h"

CPlantBox::CPlantBox(QWidget *parent) : QWidget(parent)
{

}

// 显示所有植物
 void CPlantBox::ShowAllPlant(QPainter *painter)
 {
     for (CPlant* pPlant : m_lstPlantBox) {
         pPlant->ShowPlant(painter);
     }
 }
