#include "stable.h"
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QDateTime>

#include "initial.h"
#include "ui_initial.h"
#include "helper/user.h"
#include "helper/myheaders.h"

extern User myUser;
QString currentKid;
QString currentCid;

Initial::Initial(QWidget *parent)
    : QWidget(parent), ui(new Ui::Initial), timer(new QTimer(this))
{
    ui->setupUi(this);
    initUI();
    init();

    // 点击最小化小化、关闭按钮图标
    connect(ui->buttonClose, &QPushButton::clicked, this, &Initial::close);                                 // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &Initial::showMinimized);                           // 点击最小化
    connect(timer, &QTimer::timeout, this, &Initial::timerUpDateSlot);                                      // 更新系统时间
    connect(ui->knowledgeClickLabel, &ClickableLabel::clicked, this, &Initial::goToKnowledgeWindowSlot);    // 进入知识库查看模块
    connect(ui->teachClickLabel, &ClickableLabel::clicked, this, &Initial::goToTeachWindowSlot);            // 进入教学模块
    connect(ui->testClickLabel, &ClickableLabel::clicked, this, &Initial::goToTestWindowSlot);              // 进入测试模块
    connect(ui->userClickLabel, &ClickableLabel::clicked, this, &Initial::goToUserWindowSlot);              // 进入用户管理模块
    connect(ui->quitButton, &QPushButton::clicked, this, &Initial::close);                                  // 关闭系统
}

Initial::~Initial()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void Initial::initUI()
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

    ui->usernameLabel->setText(QString::fromStdString(myUser.getName()));
    ui->currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss \ndddd"));
}

//初始化当前用户以及用户上次学习到的知识点
void Initial::init()
{
    openDatabase();

    mMove=false;//mouse moving
    timer->start(1000);

    QSqlQuery query(db);
    // 获取学生的历史学习行为信息；
    query.prepare("select * from behavior where sid=:sid order by end desc");
    query.bindValue(":sid", myUser.getSid());
    if(!query.exec())
    {
       qcout << query.lastError();
       return;
    }
    else
    {
        qcout << "Sql executes sucessfully!";
        // 如果存在学习记录
        if (query.first())
        {
            //用户在系统中有历史学习数据
            QString _kid = query.value(1).toString();
            currentKid = _kid;
            qcout << _kid;

            //在系统中检测到用户的历史学习数据
            QSqlQuery query1(db);
            query1.prepare("select pass from behavior where sid=:sid and kid=:kid order by end desc");
            query1.bindValue(":sid", myUser.getSid());
            query1.bindValue(":kid", currentKid);
            if(!query1.exec())
            {
                qcout << query1.lastError();
                return ;
            }
            else
            {
                qcout << "Sql executes sucessfully!";
                if(query1.next())
                {
                    int _pass = query1.value(0).toInt();
                    qcout << _pass;
                    // 如果上次学习的知识点已经通过，更新下一个知识点
                    if(_pass)
                    {
                        currentKid = nextKnowledge(currentKid);
                    }
                }
            }
            updateCurrentKidSlot();
        }
        else
        {
            // 用户没有历史学习数据
            ui->lastPointnameLabel->setText(tr("无"));
        }
    }

}

//重写鼠标函数实现窗口自由移动
void Initial::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void Initial::mouseMoveEvent(QMouseEvent *event)
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

void Initial::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

void Initial::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", "initial");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("1234");
    this->db.setDatabaseName("knowledge");
    bool ok = db.open();
    if (!ok)
    {
        qcout << "Failed to connect database login!";
        QMessageBox::critical(this, tr("严重错误"), tr("系统数据库初始化失败！"));
    }
    else
    {
        qcout << "Success!";
    }
}

void Initial::showFirstKnowledge()
{
    QSqlQuery query(db);
    query.prepare("select kid from recpath where sid=:sid and state=0 and orders=1");
    query.bindValue(":sid", myUser.getSid());
    if(!query.exec())
    {
        qcout << query.lastError();
        return ;
    }
    else
    {
        qcout << "Sql executes sucessfully!";
        if(query.next())
        {
            currentKid = query.value(0).toString();
            qcout << currentKid;
        }
    }
}

QString Initial::nextKnowledge(const QString cur)
{
    int tmpOrders;
    QString nextRetKnowledge;
    QSqlQuery query(db);
    query.prepare("select orders from recpath where sid=:sid and kid=:kid");
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", cur);
    if(!query.exec())
    {
        qcout << query.lastError();
        return "error";
    }
    else
    {
        if(query.next())
        {
            tmpOrders = query.value(0).toInt();
            ++tmpOrders;
        }
        QSqlQuery query1(db);
        query1.prepare("select kid from recpath where sid=:sid and orders=:orders");
        query1.bindValue(":sid", myUser.getSid());
        query1.bindValue(":orders", tmpOrders);
        if(!query1.exec())
        {
            qcout << query1.lastError();
            return "error";
        }
        else
        {
            while(query1.next())
            {
                nextRetKnowledge = query1.value(0).toString();
            }
        }
    }
    return nextRetKnowledge;
}

//显示系统时间
void Initial::timerUpDateSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui->currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss \ndddd"));
}

//知识可视化显示模块
void Initial::goToKnowledgeWindowSlot()
{
    hide();
    knowWindow = new Knowledge();
    knowWindow->show();
    connect(knowWindow, &Knowledge::closeSignal, this, &Initial::show);
}

//教学模块
void Initial::goToTeachWindowSlot()
{
    QString _lastPoint = ui->lastPointnameLabel->text();
    if (_lastPoint == tr("无"))
    {
        //用户无历史学习数据
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
            return;
        }
    }
    else
    {
        //在系统中检测到用户的历史学习数据
        QSqlQuery query(db);
        query.prepare("select cid from behavior where sid=:sid and kid=:kid order by end desc");
        query.bindValue(":sid", myUser.getSid());
        query.bindValue(":kid", currentKid);
        query.exec();
        if(!query.size())
        {
            query.next();
            currentCid = query.value(0).toString();
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("检测到您有历史学习记录，要从上次记录处开始学习吗？"));
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
    }
    teachWindow = new Teach();
    teachWindow->show();
    connect(teachWindow, &Teach::destroyed, this, &Initial::updateCurrentKidSlot);
}

//测试模块
void Initial::goToTestWindowSlot()
{
    hide();
    testWindow = new Test();
    testWindow->show();
    connect(testWindow, &Test::closeSignal, this, &Initial::updateCurrentKidSlot);
    connect(testWindow, &Test::closeSignal, this, &Initial::show);
}

//个人信息模块
void Initial::goToUserWindowSlot()
{
    hide();
    userInfoWindow = new UserInfoWidget();
    userInfoWindow->show();
    connect(userInfoWindow, &UserInfoWidget::closeSignal, this, &Initial::show);
}

//当前知识点测试通过后再次进入教学模块更新"正在学习标签"
void Initial::updateCurrentKidSlot()
{
    QSqlQuery query(db);
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
}

//// 解决全局变量myUser
//void Initial::setCurrentUserId(const QString &userId)
//{
//    curUserId = userId;
//}
