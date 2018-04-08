/*========== 案例播放模块 =========*/
#ifndef USECASE_H
#define USECASE_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

#include "ui_usecase.h"
#include "test.h"

class usecase : public QWidget
{
    Q_OBJECT

public:
    usecase(QWidget *parent = 0);
    ~usecase();

private:
    Ui::usecase ui;
    test *testWindow;
    QSqlDatabase db;
    void openDatabase();
    void init();

private slots:
    void updateTimeSlot();
    void goToTestWindowSlot();
    void on_testButton_clicked();
    void on_pushButton_clicked();
};

#endif // USECASE_H
