/*------- 个人信息管理模块 --------*/

#ifndef ADMINISTRATE_H
#define ADMINISTRATE_H

#include <QWidget>
#include "ui_administrate.h"
#include <QtSql>
//20170828 加入
#include <QTableView>
#include "qsqldatabase.h"

class administrate : public QWidget
{
    Q_OBJECT

public:
    administrate(QWidget *parent = 0);
    ~administrate();

private:
    Ui::administrate ui;
    QSqlDatabase db;
    bool havePathTab;
    bool haveBehaviorTab;
    QWidget *pathWidget;
    QWidget *behaviorWidget;
    QTableView *pathTableView;
    QTableView *behaviorTableView;
    void openDatabase();
    void init();

private slots:
    void updateTimeSlot();
    void modifyInformationSlot();
    void saveInformationSlot();
};

#endif // ADMINISTRATE_H
