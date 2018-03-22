/*========== 注册模块 ============*/
#ifndef REGISTOR_H
#define REGISTOR_H

#include <QWidget>
#include "ui_registor.h"
#include <QtSql>
#include <qsqldatabase.h>

class registor : public QWidget
{
	Q_OBJECT

public:
	registor(QWidget *parent = 0);
	~registor();

private:
	Ui::registor ui;
	QSqlDatabase db;

private slots:
	void registerSlot();
};

#endif // REGISTOR_H
