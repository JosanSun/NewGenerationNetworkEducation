/*======== 登录模块 =========*/
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "ui_login.h"
#include <QtSql>
#include "qsqldatabase.h"
#include "registor.h"
#include "initial.h"

class login : public QWidget
{
	Q_OBJECT

public:
	login(QWidget *parent = 0);
	~login();

private:
    Ui::login ui;
	QSqlDatabase db;
	registor *regWindow;
	initial *initWindow;

private slots:
    //void initbar();
	void loginSlot();
	void registorSlot();
};

#endif // LOGIN_H
