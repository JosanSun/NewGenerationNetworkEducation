#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QMessageBox>

#include "patterntest.h"
#include "ui_patterntest.h"

#define qcout qDebug()

PatternTest::PatternTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatternTest)
{
    ui->setupUi(this);
    init();
}

PatternTest::~PatternTest()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void PatternTest::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", "patternTest");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("1234");
    this->db.setDatabaseName("knowledge");
    bool ok = this->db.open();
    if (!ok)
    {
        qDebug() << "Failed to connect database login!";
    }
    else
    {
        qDebug() << "Success!";
    }
}


void PatternTest::init()
{
    openDatabase();

    allLayout = new QVBoxLayout;
    firstLayout = new QHBoxLayout;
    firstTitleLabel = new QLabel;
    firstTitleLabel->setText(tr("所罗门学习风格自测问卷表"));
    firstTitleLabel->setStyleSheet("QLabel{font: 20pt ""黑体"";"
                                   "padding-left: 250px}");
    firstLayout->addWidget(firstTitleLabel);
    firstLayout->addStretch();
    //ui->scrollArea->setLayout(firstLayout);
    allLayout->addLayout(firstLayout);
    int numRows;                //记录查询的行数
    QSqlQuery query(db);
    query.exec("select * from patternTest;");
    numRows = query.size();
    qcout << numRows;
//    int debugInt = 0;
    while (query.next())
    {
//        if(debugInt++ > 7)
//        {
//            break;
//        }
        //题目标题
        int questionId = query.value(0).toInt();
        QHBoxLayout *contentLayout = new QHBoxLayout;
        hlayout_vec.push_back(contentLayout);
        QString _question = query.value(0).toString() + "." + query.value(1).toString();
        QLabel *questionLabel = new QLabel;
        label_vec.push_back(questionLabel);
        questionLabel->setText(_question);
        questionLabel->setStyleSheet("QLabel{background:yellow}");
        contentLayout->addWidget(questionLabel);
        contentLayout->addStretch();
        //选项a
        QHBoxLayout *aLayout = new QHBoxLayout;
        hlayout_vec.push_back(aLayout);
        QRadioButton *aRadioButton = new QRadioButton;
        radiobutton_vec.push_back(aRadioButton);
        aRadioButton->setText(query.value(2).toString());
        aLayout->addWidget(aRadioButton);
        aLayout->addStretch();
        //选项b
        QHBoxLayout *bLayout = new QHBoxLayout;
        hlayout_vec.push_back(bLayout);
        QRadioButton *bRadioButton = new QRadioButton;
        radiobutton_vec.push_back(bRadioButton);
        bRadioButton->setText(query.value(3).toString());
        bLayout->addWidget(bRadioButton);
        bLayout->addStretch();
        //整理全部布局
        QButtonGroup *choiceGroup = new QButtonGroup;
        buttongroup_vec.push_back(choiceGroup);
        choiceGroup->addButton(aRadioButton);
        choiceGroup->addButton(bRadioButton);
        choiceGroup->setId(aRadioButton, 1);
        choiceGroup->setId(bRadioButton, 2);
        test_map.insert(make_pair(questionId, choiceGroup));
        //question_vec.push_back(choiceGroup);
        allLayout->addLayout(contentLayout);
        allLayout->addLayout(aLayout);
        allLayout->addLayout(bLayout);
    }
    QWidget *allWidget = new QWidget(ui->scrollArea);
    allWidget->setLayout(allLayout);
    ui->scrollArea->setWidget(allWidget);
    // ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void PatternTest::on_submitButton_clicked()
{
    vector<int> ivec(8, 0);
    int kindNum = 0;
    map<int, QButtonGroup*>::const_iterator it = test_map.begin();
    while(it != test_map.end())
    {
        int i = (it->second)->checkedId();
        switch(i)
        {
        case 1:
            ++ivec[2 * kindNum];
            break;
        case 2:
            ++ivec[2 * kindNum + 1];
            break;
        default:
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("您仍有问题未作答，请继续作答"));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            return ;
        }

        kindNum = (kindNum + 1) % 4;
        ++it;
    }
    int res[4];
    for(int i = 0; i < 4; ++i)
    {
        res[i] = ivec[2 * i] - ivec[2 * i + 1];
    }

    int resPositive[4];
    for(int i = 0; i < 4; ++i)
    {
        resPositive[i] = res[i] > 0 ? res[i] : -res[i];
    }

    int maxId = 0;
    for(int i = 1; i < 4; ++i)
    {
        if(resPositive[i]>resPositive[maxId])
        {
            maxId = i;
        }
    }

    switch(maxId)
    {
    case 0:
        curCogApproach = res[0] > 0 ? tr("活跃型") : tr("沉思型");
        break;
    case 1:
        curCogApproach = res[1] > 0 ? tr("感悟型") : tr("直觉型");
        break;
    case 2:
        curCogApproach = res[2] > 0 ? tr("视觉型") : tr("言语型");
        break;
    case 3:
        curCogApproach = res[3] > 0 ? tr("序列型") : tr("综合型");
        break;
    }

    emit getCogApproach(curCogApproach);
    on_exitButton_clicked();
}

void PatternTest::on_exitButton_clicked()
{
    if(!curCogApproach.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("您的初始认知方式"));
        msgBox.setText(curCogApproach);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    close();
}

void PatternTest::closeEvent(QCloseEvent * /* ev */)
{
    emit closeSignal();
}
