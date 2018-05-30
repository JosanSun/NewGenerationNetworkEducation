#ifndef LEARNINGPATTERNTEST_H
#define LEARNINGPATTERNTEST_H

#include <QScrollArea>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include <map>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
using namespace std;

namespace Ui {
class LearningPatternTest;
}

class LearningPatternTest : public QWidget
{
    Q_OBJECT

signals:
//    void getCogApproach(QString);
    void closeSignal();

public:
    explicit LearningPatternTest(QWidget *parent = 0);
    ~LearningPatternTest();

protected:
    void closeEvent(QCloseEvent* ev);

private slots:
    void on_submitButton_clicked();
    void on_exitButton_clicked();

private:
    void initUI();
    void init();
    void openDatabase();

private:
    Ui::LearningPatternTest *ui;
    QSqlDatabase db;
    QVBoxLayout *allLayout;
    QHBoxLayout *firstLayout;
    QLabel *firstTitleLabel;
    vector<QHBoxLayout*> hlayout_vec;
    vector<QLabel*> label_vec;
    vector<QRadioButton*> radiobutton_vec;
    vector<QButtonGroup*> buttongroup_vec;
    int limitScore;
    map<int, QButtonGroup*> test_map;

    QString curCogApproach;
};

#endif // PATTERNTEST_H
