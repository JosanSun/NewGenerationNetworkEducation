/*========== 案例播放模块 =========*/
#ifndef USECASE_H
#define USECASE_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QTimer>
#include <QDateTime>

#include "test.h"

namespace Ui {
class Usecase;
}

class Usecase : public QWidget
{
    Q_OBJECT

public:
    Usecase(QWidget *parent = 0);
    ~Usecase();

protected:
    //mouse func
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void updateTimeSlot();
    void on_testButton_clicked();

private:
    void openDatabase();
    void initUI();
    void init();

private:
    Ui::Usecase* ui;
    QTimer* timer;
    Test *testWindow;
    QSqlDatabase db;
    //mouse moving
    bool        mMove;
    QPoint      mPos;
    QDateTime   startTime;
};

#endif // USECASE_H
