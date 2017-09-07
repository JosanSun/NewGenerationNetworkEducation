/*========= 测试模块 ==========*/

#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include "ui_test.h"
#include <QtSql>
#include <map>
#include <vector>
#include "qradiobutton.h"
#include "qscrollarea.h"
using namespace std;

class test : public QWidget
{
	Q_OBJECT

public:
	test(QWidget *parent = 0);
	~test();	

private:
	Ui::test ui;
	bool pass;
	QString _first;
	QString beforeKid;
	QString currentTid;
	QString currentDomain;
	QSqlDatabase db;
	
	QLabel *initLabel;
	QPushButton *startButton;
	QVBoxLayout *allLayout;
	QHBoxLayout *firstLayout;
	QLabel *firstTitleLabel;
	vector<QHBoxLayout*> hlayout_vec;
	vector<QLabel*> label_vec;
	vector<QRadioButton*> radiobutton_vec;
	vector<QButtonGroup*> buttongroup_vec;
	QDateTime startTestTime;
	int limitScore;
	map<int, QButtonGroup*> test_map;
	void init();
	void openDatabase();


private slots:
	void timeUpdateSlot();
	void restTimeUpdateSlot();
	void startTestSlot();
	void submitTestSlot();
	void nextKnowledgeSlot();
	void againKnowledgeSlot();
};

#endif // TEST_H
