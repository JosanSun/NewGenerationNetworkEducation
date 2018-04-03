/*========== 教学模块 ==========*/
#ifndef TEACH_H
#define TEACH_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>

#include "ui_teach.h"
#include "usecase.h"
#include "test.h"

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
    void init();
	void openXml(QString);

private slots:
	void timeUpdateSlot();
	void showDomainKnowledgesSlot(QString);
	void openUsecaseSlot(QString);
	void playAgainSlot();
	void changeCaseSlot();
	void goToDiscussionSlot();
	void goToTestSlot();
	void updateBehaviorTableSlot();
    //void updateCurrentKidSlot();
    //void testSlot();
};

#endif // TEACH_H
