/*========== 案例播放模块 =========*/
#ifndef USECASE_H
#define USECASE_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QTimer>

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

private slots:
    void updateTimeSlot();
    void goToTestWindowSlot();
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
};

#endif // USECASE_H
