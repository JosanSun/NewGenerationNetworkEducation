/*========= 初始化模块 ========*/
#ifndef INITIAL_H
#define INITIAL_H

#include <QWidget>
#include "ui_initial.h"
#include "clickablelabel.h"
#include <QtSql>
#include "knowledge.h"
#include "teach.h"
#include "qsqldatabase.h"
#include "test.h"
#include "administrate.h"

class initial : public QWidget
{
	Q_OBJECT

public:
	initial(QWidget *parent = 0);
	~initial();

private:
	Ui::initial ui;
	QSqlDatabase db;
	clickablelabel *knowledgeClickLabel;
	clickablelabel *teachClickLabel;
	clickablelabel *testClickLabel;
	clickablelabel *userClickLabel;
	knowledge *knowWindow;
	teach *teachWindow;
	test *testWindow;
	administrate *adminWindow;
	void openDatabase();
	void init();
	void showFirstKnowledge();

    //mouse moving
    bool        mMove;
    QPoint      mPos;

protected:
    //mouse func
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void timerUpDateSlot();
	void goToKnowledgeWindowSlot();
	void goToTeachWindowSlot();
	void goToTestWindowSlot();
	void goToUserWindowSlot();
	void updateCurrentKidSlot();
};

#endif // INITIAL_H
