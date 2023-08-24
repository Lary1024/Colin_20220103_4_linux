#include "cpeabox.h"
#include "GameConfig.h"

CPeaBox::CPeaBox(QWidget *parent) : QWidget(parent)
{

}

CPeaBox::~CPeaBox()
{
    list<CPea*>::iterator ite = m_lstPeaBox.begin();
    while (ite != m_lstPeaBox.end()) {
        if (*ite) { // 判断炮弹的指针是否为空
            delete (*ite); // 回收炮弹
            (*ite) = nullptr;
        }

        // 删除节点
        // 方法一
        // ite = m_lstGun(ite); // 自带++效果
        ite++;
    }
    m_lstPeaBox.clear(); // 清空所有的节点

}

// 显示所有豌豆
void CPeaBox::ShowAllPea(QPainter *painter)
{
    for (CPea *pPea : m_lstPeaBox) {
        pPea->ShowPea(painter);
    }
}

// 移动所有豌豆(并判断豌豆是否出界)
void CPeaBox::MoveAllPea()
{
    list<CPea*>::iterator ite = m_lstPeaBox.begin();
    while (ite != m_lstPeaBox.end()) {
        if (*ite) {
            (*ite)->MovePea();

            if ((*ite)->m_y >= BACKGROUND_WIDTH) { // 判断是否出界
                delete (*ite); // 回收炮弹
                (*ite) = nullptr;

                ite = m_lstPeaBox.erase(ite); // 删除对应的节点
                continue; // 继续下一次循环
            }
        }
        ++ite;
    }
}
