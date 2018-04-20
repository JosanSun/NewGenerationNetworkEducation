/*========= 测试模块 ==========*/
#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QtSql>
#include <map>
#include <vector>
#include <QRadioButton>
#include <QScrollArea>
#include <QTimer>

#include "ui_test.h"
using namespace std;

class test : public QWidget
{
    Q_OBJECT

public:
    test(QWidget *parent = 0);
    ~test();

private slots:
    void timeUpdateSlot();
    void restTimeUpdateSlot();
    void startTestSlot();
    void submitTestSlot();
    void nextKnowledgeSlot();
    void againKnowledgeSlot();

private:
    void initUI();
    void init();
    void openDatabase();

private:
    Ui::test ui;
    // timer1用于更新系统当前时间
    QTimer* timer1 = nullptr;
    QTimer* timer2 = nullptr;
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
};

#endif // TEST_H
