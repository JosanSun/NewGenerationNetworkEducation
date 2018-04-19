/*------- 个人信息管理模块 --------*/

#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H

#include <QWidget>
#include <QtSql>
//20170828 加入
#include <QTableView>
#include <QTimer>
#include "qsqldatabase.h"

namespace Ui {
class UserInfoWidget;
}

class UserInfoWidget : public QWidget
{
    Q_OBJECT

public:
    UserInfoWidget(QWidget *parent = 0);
    ~UserInfoWidget();

private slots:
    void updateTimeSlot();
    void modifyInformationSlot();
    void saveInformationSlot();

private:
    void openDatabase();
    void initUI();
    void init();

private:
    Ui::UserInfoWidget* ui;
    QSqlDatabase db;
    bool havePathTab;
    bool haveBehaviorTab;
    QWidget *pathWidget;
    QWidget *behaviorWidget;
    QTableView *pathTableView;
    QTableView *behaviorTableView;
    QTimer *timer = nullptr;
};

#endif // userinfowidget_H
