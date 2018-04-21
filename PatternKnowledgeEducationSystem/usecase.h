/*========== 案例播放模块 =========*/
#ifndef USECASE_H
#define USECASE_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QTimer>

#include "ui_usecase.h"
#include "test.h"

class usecase : public QWidget
{
    Q_OBJECT

public:
    usecase(QWidget *parent = 0);
    ~usecase();

private slots:
    void updateTimeSlot();
    void goToTestWindowSlot();
    void on_testButton_clicked();

private:
    void openDatabase();
    void initUI();
    void init();

private:
    Ui::usecase ui;
    QTimer* timer;
    test *testWindow;
    QSqlDatabase db;
};

#endif // USECASE_H
