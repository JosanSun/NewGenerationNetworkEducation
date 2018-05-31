/*========== 教学模块 ==========*/
#ifndef TEACH_H
#define TEACH_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>
#include <vector>

#include "usecase.h"
#include "test.h"

using std::vector;

namespace Ui{
class Teach;
}

class Teach : public QWidget
{
    Q_OBJECT

public:
    Teach(QWidget *parent = 0);
    ~Teach();

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
    void showDomainKnowledgesSlot(QString);
    void openUsecaseSlot(QString);
    void playAgainSlot();
    void changeCaseSlot();
    void goToDiscussionSlot();
    void goToTestSlot();
    void updateBehaviorTableSlot();
    //void updateCurrentKidSlot();
    //void testSlot();   
    void on_nextKnowledgeButton_clicked();

private:
    void openDatabase();
    void initUI();
    void init();
    void openXml(QString);

private:
    Ui::Teach* ui;
    QTimer* timer = nullptr;
    QSqlDatabase db;
    QWidget *domainKnowWidget;
    QTableView *bkTableView;
    QTableView *pkTableView;
    Usecase *usecaseWindow;
    Test *testWindow;
    bool haveDomainTab;
    //mouse moving
    bool        mMove;
    QPoint      mPos;
    vector<QString> caseNames;
};

#endif // TEACH_H
