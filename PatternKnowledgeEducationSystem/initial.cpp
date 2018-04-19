#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QDateTime>

#include "initial.h"
#include "ui_initial.h"
#include "helper/user.h"

extern user myUser;
QString currentKid;

initial::initial(QWidget *parent)
    : QWidget(parent), ui(new Ui::initial), timer(new QTimer(this))
{
    ui->setupUi(this);

    initUI();
    openDatabase();
    init();
    // 点击最小化小化、关闭按钮图标
    connect(ui->buttonClose, &QPushButton::clicked, this, &initial::close);              // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &initial::showMinimized);
    connect(timer, &QTimer::timeout, this, &initial::timerUpDateSlot);
    connect(ui->knowledgeClickLabel, &clickablelabel::clicked, this, &initial::goToKnowledgeWindowSlot);//进入知识库查看模块
    connect(ui->teachClickLabel, &clickablelabel::clicked, this, &initial::goToTeachWindowSlot);//进入教学模块
    connect(ui->testClickLabel, &clickablelabel::clicked, this, &initial::goToTeachWindowSlot);//进入测试模块
    connect(ui->userClickLabel, &clickablelabel::clicked, this, &initial::goToUserWindowSlot);//进入用户管理模块
    connect(ui->quitButton, &QPushButton::clicked, this, &initial::close);//关闭系统

}

initial::~initial()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void initial::initUI()
{
    setWindowTitle(tr("在线网络教学系统客户端"));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//无边框且最小化任务栏还原

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);//设置窗口背景颜色：白

    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ui->buttonMin->setIcon(minPix);
    ui->buttonClose->setIcon(closePix);//获取并设置
}

//初始化当前用户以及用户上次学习到的知识点
void initial::init()
{
    mMove=false;//mouse moving
    timer->start(1000);

    ui->usernameLabel->setText(QString::fromStdString(myUser.getName()));
    ui->currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));

    QSqlQuery query;
    query.exec("select * from student where name='" + QString::fromStdString(myUser.getName()) + "'");
    while (query.next())
    {
        myUser.setSid(query.value(0).toInt());
        myUser.setSex(query.value(3).toString().toStdString());
        myUser.setAge(query.value(4).toInt());
        myUser.setEducation(query.value(5).toString().toStdString());
        //获得用户的认知模型setModel()
    }
    query.prepare("select * from behavior where sid=:sid");
    query.bindValue(":sid", myUser.getSid());
    query.exec();
    if (query.first())
    {//用户在系统中有历史学习数据
        query.last();
        QString _kid = query.value(1).toString();
        currentKid = _kid;
        QString _first = _kid.left(1);
        if (_first == "B")
        {
            query.exec("select title from bk where bid='" + _kid + "'");
            while (query.next())
            {
                ui->lastPointnameLabel->setText(query.value(0).toString());
            }
        }
        else if (_first == "P")
        {
            query.exec("select title from pk where pid='" + _kid + "'");
            while (query.next())
            {
                ui->lastPointnameLabel->setText(query.value(0).toString());
            }
        }
    }
    else
    {//用户没有历史学习数据
        ui->lastPointnameLabel->setText(tr("无"));
    }
    this->db.close();
}


//重写鼠标函数实现窗口自由移动
void initial::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void initial::mouseMoveEvent(QMouseEvent *event)
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

void initial::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

void initial::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("1234");
    this->db.setDatabaseName("knowledge");
    bool ok = db.open();
    if (!ok)
    {
        qDebug() << "Failed to connect database login!";
        QMessageBox::critical(this, tr("严重错误"), tr("系统数据库初始化失败！"));
    }
    else
    {
        qDebug() << "Success!";
    }
}



void initial::showFirstKnowledge()
{
    QSqlQuery query;
    query.prepare("select kid from recpath where sid=:sid and state=0 and orders=1");
    query.bindValue(":sid", myUser.getSid());
    query.exec();
    while (query.next())
    {
        currentKid = query.value(0).toString();
        qDebug() << currentKid;
        break;
    }
}

//显示系统时间
void initial::timerUpDateSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui->currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss \ndddd"));
}

//知识可视化显示模块
void initial::goToKnowledgeWindowSlot()
{
    knowWindow = new knowledge();
    knowWindow->setWindowTitle(tr("在线网络教学系统客户端"));
    knowWindow->setWindowModality(Qt::ApplicationModal);
    knowWindow->show();
    knowWindow->setAttribute(Qt::WA_DeleteOnClose);
}

//教学模块
void initial::goToTeachWindowSlot()
{
    QString _lastPoint = ui->lastPointnameLabel->text();
    if (_lastPoint == tr("无"))
    {//用户无历史学习数据
        QMessageBox msgBox;
        msgBox.setText(tr("提示"));
        msgBox.setInformativeText(tr("您是新用户，系统已为您推荐学习路线，是否开始学习？"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Ok:
            showFirstKnowledge();
            break;
        case QMessageBox::Cancel:
            break;
        }
    }
    else
    {//在系统中检测到用户的历史学习数据
        QSqlQuery query;
        query.prepare("select pass from behavior where sid=:sid and kid=:kid");
        query.bindValue(":sid", myUser.getSid());
        query.bindValue(":kid", currentKid);
        query.exec();
        while (query.next())
        {
            query.last();
            int _pass = query.value(0).toInt();
            qDebug() << _pass;
            if (_pass)
            {
                query.prepare("select kid from recpath where sid=:sid and state=0 order by orders");
                query.bindValue(":sid", myUser.getSid());
                query.exec();
                while (query.next())
                {
                    currentKid = query.value(0).toString();
                    break;
                }
            }
        }
        this->db.close();

        QMessageBox msgBox;
        msgBox.setText(tr("提示"));
        msgBox.setInformativeText(tr("检测到您有历史学习记录，要从上次记录处开始学习吗？"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Ok:
            break;
        case QMessageBox::Cancel:
            //20171002存在一个bug  未能正常调用goToKnowledgeWindowSlot();   它直接显示之前学的知识
            QMessageBox::information(this, tr("提示"), tr("请您在知识地图上选择要开始学习的知识"));
            goToKnowledgeWindowSlot();
            break;
        }
    }
    teachWindow = new teach();
    teachWindow->setWindowTitle(tr("在线网络教学系统客户端"));
    teachWindow->setWindowModality(Qt::ApplicationModal);
    teachWindow->show();
    teachWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(teachWindow, &teach::destroyed, this, &initial::updateCurrentKidSlot);
}

//测试模块
void initial::goToTestWindowSlot()
{
    testWindow = new test();
    testWindow->setWindowTitle(tr("在线网络教学系统客户端"));
    testWindow->setWindowModality(Qt::ApplicationModal);
    testWindow->show();
    testWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(testWindow, &test::destroyed, this, &initial::updateCurrentKidSlot);
}

//个人信息模块
void initial::goToUserWindowSlot()
{
    userInfoWindow = new UserInfoWidget();
    userInfoWindow->show();
}

//当前知识点测试通过后再次进入教学模块更新当前知识点
void initial::updateCurrentKidSlot()
{
    openDatabase();

    QSqlQuery query;
    QString _first = currentKid.left(1);
    if (_first == "B")
    {
        query.exec("select title from bk where bid='" + currentKid + "'");
        while (query.next())
        {
            ui->lastPointnameLabel->setText(query.value(0).toString());
        }
    }
    else if (_first == "P")
    {
        query.exec("select title from pk where pid='" + currentKid + "'");
        while (query.next())
        {
            ui->lastPointnameLabel->setText(query.value(0).toString());
        }
    }
    this->db.close();
}


// 解决全局变量myUser
void initial::setCurrentUserId(const QString &userId)
{
    curUserId = userId;
}
