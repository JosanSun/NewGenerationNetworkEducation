/*======== 登录模块 =========*/
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>

#include "registor.h"
#include "initial.h"
#include "helper/patterntest.h"
#include "helper/user.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = 0);
    ~Login();
protected:
    //mouse func
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
    //void initbar();
    void loginSlot();
    void registorSlot();

private:
    void openDatabase();
    void initUI();
    void updateCogModel(CogModel& model);

private:
    Ui::Login*   ui;
    QSqlDatabase db;
    Registor*    regWindow;
    Initial*     initWindow;
    PatternTest* patternTestWindow;
    //mouse moving
    bool         mMove;
    QPoint       mPos;
};

#endif // LOGIN_H
