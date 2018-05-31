#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QMessageBox>

#include "learningpatterntest.h"
#include "ui_learningpatterntest.h"
#include "myheaders.h"

#define qcout qDebug()

LearningPatternTest::LearningPatternTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LearningPatternTest)
{
    ui->setupUi(this);
    init();

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//无边框且最小化任务栏还原

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);//设置窗口背景颜色：白

    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ui->buttonMin->setIcon(minPix);
    ui->buttonClose->setIcon(closePix);//获取并设置

    connect(ui->buttonClose, &QPushButton::clicked, this, &LearningPatternTest::close);                                 // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &LearningPatternTest::showMinimized);                           // 点击最小化

}

LearningPatternTest::~LearningPatternTest()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void LearningPatternTest::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", "LearningPatternTest");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("1234");
    this->db.setDatabaseName("knowledge");
    bool ok = this->db.open();
    if (!ok)
    {
        qcout << "Failed to connect database login!";
    }
    else
    {
        qcout << "Success!";
    }
}


void LearningPatternTest::init()
{
    openDatabase();
    mMove=false;//mouse moving
    allLayout = new QVBoxLayout;
    firstLayout = new QHBoxLayout;
    firstTitleLabel = new QLabel;
    firstTitleLabel->setText(tr("学习特征调查问卷"));
    firstTitleLabel->setStyleSheet("QLabel{font: 20pt ""黑体"";"
                                   "padding-left: 250px}");
    firstLayout->addWidget(firstTitleLabel);
    firstLayout->addStretch();
    //ui->scrollArea->setLayout(firstLayout);
    allLayout->addLayout(firstLayout);
    int numRows;                //记录查询的行数
    QSqlQuery query(db);
    query.exec("select * from studyfeaturetest;");
    numRows = query.size();
    qcout << numRows;
//     int debugInt = 0;
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
        //选项c
        QHBoxLayout *cLayout = new QHBoxLayout;
        hlayout_vec.push_back(cLayout);
        QRadioButton *cRadioButton = new QRadioButton;
        radiobutton_vec.push_back(cRadioButton);
        cRadioButton->setText(query.value(4).toString());
        cLayout->addWidget(cRadioButton);
        cLayout->addStretch();
        //选项d
        QHBoxLayout *dLayout = new QHBoxLayout;
        hlayout_vec.push_back(dLayout);
        QRadioButton *dRadioButton = new QRadioButton;
        radiobutton_vec.push_back(dRadioButton);
        dRadioButton->setText(query.value(5).toString());
        dLayout->addWidget(dRadioButton);
        dLayout->addStretch();
        //选项e
        QHBoxLayout *eLayout = new QHBoxLayout;
        hlayout_vec.push_back(eLayout);
        QRadioButton *eRadioButton = new QRadioButton;
        radiobutton_vec.push_back(eRadioButton);
        eRadioButton->setText(query.value(6).toString());
        eLayout->addWidget(eRadioButton);
        eLayout->addStretch();
        //整理全部布局
        QButtonGroup *choiceGroup = new QButtonGroup;
        buttongroup_vec.push_back(choiceGroup);
        choiceGroup->addButton(aRadioButton);
        choiceGroup->addButton(bRadioButton);
        choiceGroup->addButton(cRadioButton);
        choiceGroup->addButton(dRadioButton);
        choiceGroup->addButton(eRadioButton);
        choiceGroup->setId(aRadioButton, 1);
        choiceGroup->setId(bRadioButton, 2);
        choiceGroup->setId(cRadioButton, 3);
        choiceGroup->setId(dRadioButton, 4);
        choiceGroup->setId(eRadioButton, 5);
        test_map.insert(make_pair(questionId, choiceGroup));
        //question_vec.push_back(choiceGroup);
        allLayout->addLayout(contentLayout);
        allLayout->addLayout(aLayout);
        allLayout->addLayout(bLayout);
        allLayout->addLayout(cLayout);
        allLayout->addLayout(dLayout);
        allLayout->addLayout(eLayout);
    }
    QWidget *allWidget = new QWidget(ui->scrollArea);
    allWidget->setLayout(allLayout);
    ui->scrollArea->setWidget(allWidget);
    // ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

//重写鼠标函数实现窗口自由移动
void LearningPatternTest::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void LearningPatternTest::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (mMove && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-mPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mPos);
        mPos = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void LearningPatternTest::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

void LearningPatternTest::on_submitButton_clicked()
{
    map<int, QButtonGroup*>::const_iterator it = test_map.begin();
    while(it != test_map.end())
    {
        int i = (it->second)->checkedId();
        switch(i)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
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
        ++it;
    }
    int ret = QMessageBox::information(this, tr("提示"), tr("提交成功"));
    if(ret == QMessageBox::Ok)
    {
        close();
    }
}

void LearningPatternTest::on_exitButton_clicked()
{
    close();
}

void LearningPatternTest::closeEvent(QCloseEvent * /* ev */)
{
    emit closeSignal();
}
