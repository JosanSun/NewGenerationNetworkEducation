/*======== 登录模块 =========*/
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>

#include "registor.h"
#include "initial.h"

namespace Ui {
class login;
}

class login : public QWidget
{
	Q_OBJECT

public:
	login(QWidget *parent = 0);
	~login();

private:
    Ui::login* ui;
	QSqlDatabase db;
	registor *regWindow;
	initial *initWindow;

private slots:
    //void initbar();
	void loginSlot();
	void registorSlot();
private:
    void openDatabase();
};

#endif // LOGIN_H
