/*======== 登录模块 =========*/

#ifndef LOGIN_H
#define LOGIN_H

#include <QtWidgets/QMainWindow>
#include "ui_login.h"
#include <QtSql>
#include "qsqldatabase.h"
#include "registor.h"
#include "initial.h"

class login : public QMainWindow
{
	Q_OBJECT

public:
	login(QWidget *parent = 0);
	~login();

private:
	Ui::loginClass ui;
	QSqlDatabase db;
	registor *regWindow;
	initial *initWindow;

private slots:
	void loginSlot();
	void registorSlot();
};

#endif // LOGIN_H
