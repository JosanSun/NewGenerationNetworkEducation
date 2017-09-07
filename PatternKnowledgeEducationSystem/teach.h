/*========== 教学模块 ==========*/

#ifndef TEACH_H
#define TEACH_H

#include <QWidget>
#include "ui_teach.h"
#include <QtSql>
#include "qsqldatabase.h"
#include "usecase.h"
#include "test.h"
//20170828  改动
#include <QTableView>


class teach : public QWidget
{
	Q_OBJECT

public:
	teach(QWidget *parent = 0);
	~teach();

private:
	Ui::teach ui;
	QSqlDatabase db;
	QWidget *domainKnowWidget;
	QTableView *bkTableView;
	QTableView *pkTableView;
	usecase *usecaseWindow;
	test *testWindow;
	
	bool haveDomainTab;
	void openDatabase();
	
	void openXml(QString);
	

signals:
	
	

private slots:
	void init();
	void timeUpdateSlot();
	void showDomainKnowledgesSlot(QString);
	void openUsecaseSlot(QString);
	void playAgainSlot();
	void changeCaseSlot();
	void goToDiscussionSlot();
	void goToTestSlot();
	void updateCurrentKidSlot();
	void updateBehaviorTableSlot();
	void testSlot();
};

#endif // TEACH_H
