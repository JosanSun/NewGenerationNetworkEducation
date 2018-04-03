#include "teach.h"
#include "qdatetime.h"
#include "qtimer.h"
#include "helper/user.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qtableview.h"
#include "helper/mypushbutton.h"
#include <QtXml>
#include <QDomDocument>
#include "qdesktopservices.h"
#include "qfiledialog.h"

extern user myUser;
extern QString currentKid;
QString currentCid;
extern QString note;

teach::teach(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    haveDomainTab = false;
    currentCid = "";
    ui.currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
    ui.usernameLabel->setText(QString::fromStdString(myUser.getName()));
    QTimer *timer = new QTimer(this);
    init();
    connect(timer, &QTimer::timeout, this, &teach::timeUpdateSlot);//更新系统时间
    connect(ui.playAgainButton, &QPushButton::clicked, this, &teach::playAgainSlot);//重新播放案例
    connect(ui.changeCaseButton, &QPushButton::clicked, this, &teach::changeCaseSlot);//更换案例
    connect(ui.discussionButton, &QPushButton::clicked, this, &teach::goToDiscussionSlot);//进入讨论区
    connect(ui.beginTestButton, &QPushButton::clicked, this, &teach::goToTestSlot);//进入测试模块
    connect(ui.quitButton, &QPushButton::clicked, this, &teach::close);//关闭系统
    timer->start(1000);
}

teach::~teach()
{

}

void teach::openDatabase()
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
    }
    else
    {
        qDebug() << "Success!";
    }
}


//初始化教学界面
void teach::init()
{
    openDatabase();
    QSqlQuery query;
    QString _first = currentKid.left(1);//根据系统当前知识点查询数据库
    qDebug() << currentKid;
    if (_first == "B")
    {//当前知识点是基本知识节点
        query.exec("select * from bk where bid='" + currentKid + "'");
        while (query.next())
        {
            ui.pointnameLabel->setText(query.value(1).toString());
            //显示当前知识的description信息
            QString _descFileName = query.value(3).toString();
            QFile _descFile(_descFileName);
            if (!_descFile.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream out(&_descFile);
            while (out.atEnd() == 0)
            {
                //知识点描述窗口
                ui.descriptionTextBrowser->setText(out.readAll());
            }
            //领域知识按钮---查找与显示
            //显示当前知识的领域信息  领域信息以,相分隔
            QString _domain = query.value(2).toString();
            QString _sep = ",";
            int inx = 1;
            int pos=_domain.indexOf(_sep);
            while (pos != -1)
            {
                myPushButton *domainButton = new myPushButton(ui.groupBox_2);
                domainButton->setGeometry(110 + 100 * (inx - 1), 230, 75, 20);
                domainButton->setText(_domain.left(pos));
                //点击领域知识按钮，触发显示领域知识信息   不点击的话，默认不显示
                connect(domainButton, SIGNAL(clicked(QString)), this, SLOT(showDomainKnowledgesSlot(QString)));
                _domain = _domain.remove(0, pos+1);
                ++inx;
                pos = _domain.indexOf(_sep);
            }
            //处理最后一个领域知识按钮
            myPushButton *domainButton = new myPushButton(ui.groupBox_2);
            domainButton->setGeometry(110 + 100 * (inx - 1), 230, 75, 20);
            domainButton->setText(_domain);
            connect(domainButton, SIGNAL(clicked(QString)), this, SLOT(showDomainKnowledgesSlot(QString)));

        }
        //显示当前知识的案例按钮
        query.exec("select * from teach where kid='" + currentKid + "'");
        int inx = 1;
        while (query.next())
        {
            myPushButton *usecaseButton = new myPushButton(ui.groupBox_2);
            usecaseButton->setGeometry(110 + 100 * (inx - 1), 270, 75, 20);
            usecaseButton->setText(query.value(1).toString());
            //点击案例按钮，触发打开案例界面
            connect(usecaseButton, SIGNAL(clicked(QString)), this, SLOT(openUsecaseSlot(QString)));
            ++inx;
        }
        //显示当前知识的前驱后继
        query.exec("select * from about where kid='" + currentKid + "'");
        while (query.next())
        {
            if (query.value(1).toInt() == 0){//前驱
                QString _about = query.value(2).toString();
                QString _sep = ",";
                int inx = 1;
                int pos = _about.indexOf(_sep);
                while (pos != -1)
                {
                    myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                    QString buttonText = "";
                    QString _aboutKid = _about.left(pos);
                    QString _singleKid = _aboutKid.left(4);
                    while (!_singleKid.isEmpty())
                    {
                        QString _first = _singleKid.left(1);
                        if (_first == "B")
                        {
                            QSqlQuery query;
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query;
                            query.exec("select title from pk where kid='" + _aboutKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        _aboutKid = _aboutKid.remove(0, 4);
                        _singleKid = _aboutKid.left(4);
                    }
                    aboutKnowButton->setText(buttonText);
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 75, 20);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                //处理最后一个前驱
                myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                QString buttonText = "";
                QString _singleKid = _about.left(4);
                while (!_singleKid.isEmpty())
                {
                    QString _first = _singleKid.left(1);
                    if (_first == "B"){
                        QSqlQuery query1;
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next()){
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P"){
                        QSqlQuery query1;
                        query1.exec("select title from pk where pid='" + _singleKid + "'");
                        while (query1.next()){
                            buttonText += query1.value(0).toString();
                        }
                    }
                    _about = _about.remove(0, 4);
                    _singleKid = _about.left(4);
                }
                aboutKnowButton->setText(buttonText);
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 75, 20);
            }
            else if (query.value(1).toInt() == 1)
            {//后继
                QString _about = query.value(2).toString();
                QString _sep = ",";
                int inx = 1;
                int pos = _about.indexOf(_sep);
                while (pos != -1)
                {
                    myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                    QString buttonText = "";
                    QString _aboutKid = _about.left(pos);
                    QString _singleKid = _aboutKid.left(4);
                    while (!_singleKid.isEmpty())
                    {
                        QString _first = _singleKid.left(1);
                        if (_first == "B")
                        {
                            QSqlQuery query;
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query;
                            query.exec("select title from pk where kid='" + _aboutKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        _aboutKid = _aboutKid.remove(0, 4);
                        _singleKid = _aboutKid.left(4);
                    }
                    aboutKnowButton->setText(buttonText);
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 75, 20);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                //处理最后一个后继
                myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                QString buttonText = "";
                QSqlQuery query1;
                QString _singleKid = _about.left(4);
                while (!_singleKid.isEmpty())
                {
                    QString _first = _singleKid.left(1);
                    if (_first == "B")
                    {
                        QSqlQuery query1;
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P")
                    {
                        QSqlQuery query1;
                        query1.exec("select title from pk where pid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    _about = _about.remove(0, 4);
                    _singleKid = _about.left(4);
                }
                aboutKnowButton->setText(buttonText);
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 75, 20);
            }
        }
    }
    //跟上面"B"类似
    else if (_first == "P")
    {//当前知识节点是模式知识节点
        query.exec("select * from pk where pid='" + currentKid + "'");
        while (query.next())
        {
            ui.pointnameLabel->setText(query.value(1).toString());
            QString _patternFile = query.value(3).toString();
            //成功打开xml文件
            openXml(_patternFile);
            //显示当前知识的领域信息
            QString _domain = query.value(2).toString();
            QString _sep = ",";
            int inx = 1;
            int pos = _domain.indexOf(_sep);
            while (pos != -1)
            {
                myPushButton *domainButton = new myPushButton(ui.groupBox_2);
                domainButton->setGeometry(110 + 100 * (inx - 1), 230, 75, 20);
                domainButton->setText(_domain.left(pos));
                connect(domainButton, &myPushButton::clicked, this, &teach::showDomainKnowledgesSlot);
                _domain = _domain.remove(0, pos + 1);
                ++inx;
                pos = _domain.indexOf(_sep);
            }
            myPushButton *domainButton = new myPushButton(ui.groupBox_2);
            domainButton->setGeometry(110 + 100 * (inx - 1), 230, 75, 20);
            domainButton->setText(_domain);
            connect(domainButton, &myPushButton::clicked, this, &teach::showDomainKnowledgesSlot);
        }
        //显示当前知识的案例按钮
        query.exec("select * from teach where kid='" + currentKid + "'");
        int inx = 1;
        while (query.next())
        {
            myPushButton *usecaseButton = new myPushButton(ui.groupBox_2);
            usecaseButton->setGeometry(110 + 100 * (inx - 1), 270, 75, 20);
            usecaseButton->setText(query.value(1).toString());
            connect(usecaseButton, &myPushButton::clicked, this, &teach::openUsecaseSlot);
            ++inx;
        }
        //显示当前知识的前驱后继
        query.exec("select * from about where kid='" + currentKid + "'");
        while (query.next())
        {
            if (query.value(1).toInt() == 0)
            {//前驱
                QString _about = query.value(2).toString();
                QString _sep = ",";
                int inx = 1;
                int pos = _about.indexOf(_sep);
                while (pos != -1)
                {
                    myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                    QString buttonText = "";
                    QString _aboutKid = _about.left(pos);
                    QString _singleKid = _aboutKid.left(4);
                    while (!_singleKid.isEmpty())
                    {
                        QString _first = _singleKid.left(1);
                        if (_first == "B")
                        {
                            QSqlQuery query;
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query;
                            query.exec("select title from pk where kid='" + _aboutKid + "'");
                            while (query.next()){
                                buttonText += query.value(0).toString();
                            }
                        }
                        _aboutKid = _aboutKid.remove(0, 4);
                        _singleKid = _aboutKid.left(4);
                    }
                    aboutKnowButton->setText(buttonText);
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 75, 20);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                QString buttonText = "";

                QString _singleKid = _about.left(4);
                while (!_singleKid.isEmpty())
                {
                    QString _first = _singleKid.left(1);
                    if (_first == "B")
                    {
                        QSqlQuery query1;
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P")
                    {
                        QSqlQuery query1;
                        query1.exec("select title from pk where pid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    _about = _about.remove(0, 4);
                    _singleKid = _about.left(4);
                }
                aboutKnowButton->setText(buttonText);
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 75, 20);
            }
            else if (query.value(1).toInt() == 1)
            {//后继
                QString _about = query.value(2).toString();
                QString _sep = ",";
                int inx = 1;
                int pos = _about.indexOf(_sep);
                while (pos != -1)
                {
                    myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                    QString buttonText = "";
                    QString _aboutKid = _about.left(pos);
                    QString _singleKid = _aboutKid.left(4);
                    while (!_singleKid.isEmpty())
                    {
                        QString _first = _singleKid.left(1);
                        if (_first == "B")
                        {
                            QSqlQuery query;
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query;
                            query.exec("select title from pk where kid='" + _aboutKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        _aboutKid = _aboutKid.remove(0, 4);
                        _singleKid = _aboutKid.left(4);
                    }
                    aboutKnowButton->setText(buttonText);
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 75, 20);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                myPushButton *aboutKnowButton = new myPushButton(ui.groupBox_2);
                QString buttonText = "";

                QString _singleKid = _about.left(4);
                while (!_singleKid.isEmpty()){
                    QString _first = _singleKid.left(1);
                    if (_first == "B")
                    {
                        QSqlQuery query1;
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P")
                    {
                        QSqlQuery query1;
                        query1.exec("select title from pk where pid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    _about = _about.remove(0, 4);
                    _singleKid = _about.left(4);
                }
                aboutKnowButton->setText(buttonText);
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 75, 20);
            }
        }
    }
    this->db.close();
}

//模式知识模式属性读取xml文档
void teach::openXml(QString filename)
{
    QDomDocument doc;
    QFile xmlFile(filename);
    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open xml file!";
    }
    if (!doc.setContent(&xmlFile))
    {
        xmlFile.close();
        qDebug() << "Failed!";
    }
    xmlFile.close();
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        QDomElement e = node.toElement();
        if (!e.isNull())
        {
            if (e.tagName() == "pname")
            {
                ui.descriptionTextBrowser->append(QStringLiteral("模式：") + e.text());
            }
            else if (e.tagName() == "pproblem")
            {
                ui.descriptionTextBrowser->append(QStringLiteral("解决问题：") + e.text());
            }
            else if (e.tagName() == "psolution")
            {
                ui.descriptionTextBrowser->append(QStringLiteral("解决方案：") + e.text());
            }
            else if (e.tagName() == "pcharacteries")
            {
                ui.descriptionTextBrowser->append(QStringLiteral("特征点："));
                QDomNode cnode = e.firstChild();
                while (!cnode.isNull())
                {
                    QDomElement ce = cnode.toElement();
                    if (!ce.isNull())
                    {
                        ui.descriptionTextBrowser->append(ce.text());
                    }
                    cnode = cnode.nextSibling();
                }
            }
            else if (e.tagName() == "preference")
            {
                ui.descriptionTextBrowser->append(QStringLiteral("参考："));
                QDomNode pnode = e.firstChild();
                while (!pnode.isNull())
                {
                    QDomElement pe = pnode.toElement();
                    if (!pe.isNull())
                    {
                        ui.descriptionTextBrowser->append(pe.text());
                    }
                    pnode = pnode.nextSibling();
                }
            }
        }
        node = node.nextSibling();
    }

}

//更新系统时间槽
void teach::timeUpdateSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui.currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
}

//显示领域相关知识节点信息
void teach::showDomainKnowledgesSlot(QString domain)
{
    if (haveDomainTab)
    {
        //之前，已经存在领域tab,则更新领域tab
        openDatabase();
        qDebug() << haveDomainTab;
        QSqlQueryModel *model = new QSqlQueryModel;
        qDebug() << domain;
        model->setQuery("select bid,title,domain from bk where domain like '%" + domain
                        + "%' union all select pid,title,domain from pk where domain like '%" + domain + "%'");
        model->setHeaderData(0, Qt::Horizontal, QStringLiteral("编号"));
        model->setHeaderData(1, Qt::Horizontal, QStringLiteral("标题"));
        model->setHeaderData(2, Qt::Horizontal, QStringLiteral("领域"));
        bkTableView->setModel(model);
        this->db.close();
    }
    else
    {
        //如果没有，则新建一个窗口用来保存领域知识tab
        qDebug() << haveDomainTab;
        qDebug() << domain;
        haveDomainTab = true;
        domainKnowWidget = new QWidget();
        bkTableView = new QTableView(domainKnowWidget);
        bkTableView->setGeometry(12, 10, 680, 220);
        ui.tabWidget->addTab(domainKnowWidget, QStringLiteral("领域相关知识"));
        openDatabase();
        QSqlQueryModel *model = new QSqlQueryModel;
        QString sqlString = "select bid,title,domain from bk where domain like '%" + domain
                + "%' union all select pid,title,domain from pk where domain like '%" + domain + "%'";
        model->setQuery(sqlString);
        model->setHeaderData(0, Qt::Horizontal, QStringLiteral("编号"));
        model->setHeaderData(1, Qt::Horizontal, QStringLiteral("标题"));
        model->setHeaderData(2, Qt::Horizontal, QStringLiteral("领域"));
        bkTableView->setModel(model);
        bkTableView->horizontalHeader()->setStretchLastSection(true);
        bkTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        bkTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->db.close();
    }
}

//打开案例
void teach::openUsecaseSlot(QString casename)
{
    openDatabase();
    QSqlQuery query;
    currentCid = casename;
    query.prepare("insert into behavior(sid,kid,cid,begin) values(:sid,:kid,:cid,:begin)");
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.bindValue(":begin", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.exec();
    QString _form = casename.remove(0, 5);
    if (_form == "ppt")
    {//如果用户点击的案例为ppt类型，则直接显示该案例
        QString path;
        query.exec("select * from teach where kid='" + currentKid + "' and cid='" + currentCid + "'");
        while (query.next())
        {
            path = query.value(2).toString();
        }
        path.replace(0, 1, "file:///D://mycode//Github//NewGenerationNetworkEducation");//此处可根据本地文件夹名称更改
        QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
        //记录用户behavior
    }
    else
    {//否则进入案例播放界面
        usecaseWindow = new usecase();
        usecaseWindow->setWindowTitle(QStringLiteral("在线网络教学系统客户端"));
        usecaseWindow->setWindowModality(Qt::ApplicationModal);
        usecaseWindow->show();
        usecaseWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(usecaseWindow, SIGNAL(destroyed()), this, SLOT(updateBehaviorTableSlot()));
    }
    db.close();
}

//重新播放案例
void teach::playAgainSlot()
{
    //首先记录上次学习的案例的结束时间以及通过情况
    openDatabase();
    QSqlQuery query;
    query.prepare("update behavior set end=:end,pass=0 where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();
    //重新播放刚刚的实例
    openUsecaseSlot(currentCid);
    this->db.close();
}

void teach::changeCaseSlot()
{
    openDatabase();
    QSqlQuery query;
    //首先记录上次学习的案例的结束时间以及通过情况
    query.prepare("update behavior set end=:end,pass=0 where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();
    //更换案例
    query.prepare("select cid from teach where kid=:kid and cid not in (select cid from behavior where sid=:sid and kid=:kid)");
    query.bindValue(":kid", currentKid);
    query.bindValue(":sid", myUser.getSid());
    query.exec();
    while (query.next())
    {
        currentCid = query.value(0).toString();
        openUsecaseSlot(query.value(0).toString());
        break;
    }
    this->db.close();
}

//进入讨论区模块
void teach::goToDiscussionSlot()
{

}

//进入测试模块
void teach::goToTestSlot()
{
    openDatabase();
    QSqlQuery query;
    //首先记录上次学习的案例的结束时间以及通过情况
    query.prepare("update behavior set end=:end,pass=0,note=:note where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":note", note);
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();
    this->db.close();

    //进入测试
    testWindow = new test();
    testWindow->setWindowTitle(QStringLiteral("在线网络教学系统客户端"));
    testWindow->setWindowModality(Qt::ApplicationModal);
    testWindow->show();
    testWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(testWindow, SIGNAL(destroyed()), this, SLOT(close()));

}

////更新当前知识节点
//void teach::updateCurrentKidSlot(){
//	openDatabase();
//	QSqlQuery query;
//	QString _first = currentKid.left(1);
//	if (_first == "B"){
//		query.exec("select title from bk where bid='" + currentKid + "'");
//		while (query.next()){
//			ui.pointnameLabel->setText(query.value(0).toString());
//		}
//	}
//	else if (_first == "P"){
//		query.exec("select title from pk where pid='" + currentKid + "'");
//		while (query.next()){
//			ui.pointnameLabel->setText(query.value(0).toString());
//		}
//	}
//	this->db.close();
//}

//更新行为记录表
void teach::updateBehaviorTableSlot()
{
    openDatabase();
    QSqlQuery query;
    query.prepare("update behavior set end=:end,pass=0,note=:note where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":note", note);
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();
    this->db.close();
}

//void teach::testSlot(){
//	qDebug() << "test";
//}
