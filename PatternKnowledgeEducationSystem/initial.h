/*========= 初始化模块 ========*/
#ifndef INITIAL_H
#define INITIAL_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

#include "helper/clickablelabel.h"
#include "knowledge.h"
#include "teach.h"
#include "test.h"
#include "userinfowidget.h"

namespace Ui {
class Initial;
}

class Initial : public QWidget
{
    Q_OBJECT

public:
    Initial(QWidget *parent = 0);
    ~Initial();

//    void setCurrentUserId(const QString& userId);

protected:
    //mouse func
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void timerUpDateSlot();
    void goToKnowledgeWindowSlot();
    void goToTeachWindowSlot();
    void goToTestWindowSlot();
    void goToUserWindowSlot();
    void updateCurrentKidSlot();

private:
    void initUI();
    void openDatabase();
    void init();
    void showFirstKnowledge();
    QString nextKnowledge(QString cur);
    void updateCurrentLearnLabel();

private:
    Ui::Initial* ui;
    QSqlDatabase db;
    QString curUserId;
    QTimer* timer                  = nullptr;
    Knowledge* knowWindow          = nullptr;
    Teach* teachWindow             = nullptr;
    Test* testWindow               = nullptr;
    UserInfoWidget* userInfoWindow = nullptr;
    //mouse moving
    bool        mMove;
    QPoint      mPos;
};

#endif // INITIAL_H
