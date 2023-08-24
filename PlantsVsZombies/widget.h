#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cgamemenu.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    void InitGameMenu();
signals:
    void SIG_gamestart();
private:
    Ui::Widget *ui;
public:
    QPixmap m_pix;
    // CGameMenu m_gamemenu;
};
#endif // WIDGET_H
