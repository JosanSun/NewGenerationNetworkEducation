/*========= 测试模块 ==========*/
#ifndef TEST_H
#define TEST_H

#include "stable.h"
#include <QtSql>
#include <map>
#include <vector>
using namespace std;

namespace Ui {
class Test;
}

class Test : public QWidget
{
    Q_OBJECT

public:
    Test(QWidget *parent = 0);
    ~Test();

signals:
    void closeSignal();

protected:
    //mouse func
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent* ev);

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
    void updateUserInfo();

private:
    Ui::Test* ui;
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
    //mouse moving
    bool        mMove;
    QPoint      mPos;
};

#endif // TEST_H
