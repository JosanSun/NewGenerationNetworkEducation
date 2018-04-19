/*======== 登录模块 =========*/
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>

#include "registor.h"
#include "initial.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = 0);
    ~login();
protected:
    //mouse func
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //void initbar();
    void loginSlot();
    void registorSlot();

private:
    void openDatabase();
    void initUI();

private:
    Ui::login* ui;
    QSqlDatabase db;
    registor *regWindow;
    initial *initWindow;
    //mouse moving
    bool        mMove;
    QPoint      mPos;
};

#endif // LOGIN_H
