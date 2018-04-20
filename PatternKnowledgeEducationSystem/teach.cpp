#include <QDateTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QTableView>
#include <QtXml>
#include <QDomDocument>
#include <QDesktopServices>

#include "teach.h"
#include "helper/user.h"
#include "helper/mypushbutton.h"
#include "helper/myheaders.h"

extern user myUser;
extern QString currentKid;
QString currentCid;
extern QString note;

teach::teach(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this))
{
    ui.setupUi(this);
    initUI();
    openDatabase();
    init();

    connect(timer, &QTimer::timeout, this, &teach::timeUpdateSlot);                         //更新系统时间
    connect(ui.playAgainButton, &QPushButton::clicked, this, &teach::playAgainSlot);        //重新播放案例
    connect(ui.changeCaseButton, &QPushButton::clicked, this, &teach::changeCaseSlot);      //更换案例
    connect(ui.discussionButton, &QPushButton::clicked, this, &teach::goToDiscussionSlot);  //进入讨论区
    connect(ui.beginTestButton, &QPushButton::clicked, this, &teach::goToTestSlot);         //进入测试模块
    connect(ui.quitButton, &QPushButton::clicked, this, &teach::close);                     //关闭系统

}

teach::~teach()
{
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void teach::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", "teach");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("1234");
    this->db.setDatabaseName("knowledge");
    bool ok = db.open();
    if (!ok)
    {
        qcout << "Failed to connect database login!";
    }
    else
    {
        qcout << "Success!";
    }
}

//更新系统时间槽
void teach::timeUpdateSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui.currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
}

void teach::initUI()
{
    setWindowTitle(tr("在线网络教学系统客户端"));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    ui.currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
    ui.usernameLabel->setText(QString::fromStdString(myUser.getName()));
}

//初始化教学界面
void teach::init()
{
    haveDomainTab = false;
    currentCid = "";
    timer->start(1000);

    QSqlQuery query(db);
    QString _first = currentKid.left(1);//根据系统当前知识点查询数据库
    qcout << currentKid;
    if (_first == "B")
    {
        //当前知识点是基本知识节点
        query.exec("select * from bk where bid='" + currentKid + "'");
        while (query.next())
        {
            ui.pointnameLabel->setText(query.value(1).toString());
            //显示当前知识的description信息
            QString _descFileName = query.value(3).toString();
            _descFileName.replace(0, 1, "../PatternKnowledgeEducationSystem");
            // qcout << _descFileName;
            QFile _descFile(_descFileName);
            if (!_descFile.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream out(&_descFile);
            while (!out.atEnd())
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
                void (myPushButton::*pfn)(QString) = myPushButton::clicked;
                // connect(domainButton, pfn, this, SLOT(showDomainKnowledgesSlot(QString)));
                connect(domainButton, pfn, this, &teach::showDomainKnowledgesSlot);
                _domain = _domain.remove(0, pos+1);
                ++inx;
                pos = _domain.indexOf(_sep);
            }
            //处理最后一个领域知识按钮
            myPushButton *domainButton = new myPushButton(ui.groupBox_2);
            domainButton->setGeometry(110 + 100 * (inx - 1), 230, 75, 20);
            domainButton->setText(_domain);
            void (myPushButton::*pfn1)(QString) = myPushButton::clicked;
            //connect(domainButton, pfn1, this, SLOT(showDomainKnowledgesSlot(QString)));
            connect(domainButton, pfn1, this, &teach::showDomainKnowledgesSlot);

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
            void (myPushButton::*pfn2)(QString) = myPushButton::clicked;
            //connect(usecaseButton, pfn2, this, SLOT(openUsecaseSlot(QString)));
            connect(usecaseButton, pfn2, this, &teach::openUsecaseSlot);
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
                            QSqlQuery query(db);
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query(db);
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
                        QSqlQuery query1(db);
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next()){
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P"){
                        QSqlQuery query1(db);
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
                            QSqlQuery query(db);
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query(db);
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
                QString _singleKid = _about.left(4);
                while (!_singleKid.isEmpty())
                {
                    QString _first = _singleKid.left(1);
                    if (_first == "B")
                    {
                        QSqlQuery query1(db);
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P")
                    {
                        QSqlQuery query1(db);
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
    {
        //当前知识节点是模式知识节点
        query.exec("select * from pk where pid='" + currentKid + "'");
        while (query.next())
        {
            ui.pointnameLabel->setText(query.value(1).toString());
            QString _patternFile = query.value(3).toString();
            _patternFile.replace(0, 1, "../PatternKnowledgeEducationSystem");
            qcout << _patternFile;
            // 成功打开xml文件
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
                            QSqlQuery query(db);
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query(db);
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
                        QSqlQuery query1(db);
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P")
                    {
                        QSqlQuery query1(db);
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
                            QSqlQuery query(db);
                            query.exec("select title from bk where bid='" + _singleKid + "'");
                            while (query.next())
                            {
                                buttonText += query.value(0).toString();
                            }
                        }
                        else if (_first == "P")
                        {
                            QSqlQuery query(db);
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
                        QSqlQuery query1(db);
                        query1.exec("select title from bk where bid='" + _singleKid + "'");
                        while (query1.next())
                        {
                            buttonText += query1.value(0).toString();
                        }
                    }
                    else if (_first == "P")
                    {
                        QSqlQuery query1(db);
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
}

//模式知识模式属性读取xml文档
void teach::openXml(QString filename)
{
    QDomDocument doc;
    QFile xmlFile(filename);
    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        qcout << "Failed to open xml file!";
    }
    if (!doc.setContent(&xmlFile))
    {
        xmlFile.close();
        qcout << "Failed!";
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
                ui.descriptionTextBrowser->append(tr("模式：") + e.text());
            }
            else if (e.tagName() == "pproblem")
            {
                ui.descriptionTextBrowser->append(tr("解决问题：") + e.text());
            }
            else if (e.tagName() == "psolution")
            {
                ui.descriptionTextBrowser->append(tr("解决方案：") + e.text());
            }
            else if (e.tagName() == "pcharacteries")
            {
                ui.descriptionTextBrowser->append(tr("特征点："));
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
                ui.descriptionTextBrowser->append(tr("参考："));
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

//显示领域相关知识节点信息
void teach::showDomainKnowledgesSlot(QString domain)
{
    if (haveDomainTab)
    {
        //之前，已经存在领域tab,则更新领域tab
        qcout << haveDomainTab;
        QSqlQueryModel *model = new QSqlQueryModel;
        qcout << domain;
        model->setQuery("select bid,title,domain from bk where domain like '%" + domain
                        + "%' union all select pid,title,domain from pk where domain like '%" + domain + "%'");
        model->setHeaderData(0, Qt::Horizontal, tr("编号"));
        model->setHeaderData(1, Qt::Horizontal, tr("标题"));
        model->setHeaderData(2, Qt::Horizontal, tr("领域"));
        bkTableView->setModel(model);
    }
    else
    {
        //如果没有，则新建一个窗口用来保存领域知识tab
        qcout << haveDomainTab;
        qcout << domain;
        haveDomainTab = true;
        domainKnowWidget = new QWidget();
        bkTableView = new QTableView(domainKnowWidget);
        bkTableView->setGeometry(12, 10, 680, 220);
        ui.tabWidget->addTab(domainKnowWidget, tr("领域相关知识"));
        QSqlQueryModel *model = new QSqlQueryModel;
        QString sqlString = "select bid,title,domain from bk where domain like '%" + domain
                + "%' union all select pid,title,domain from pk where domain like '%" + domain + "%'";
        model->setQuery(sqlString);
        model->setHeaderData(0, Qt::Horizontal, tr("编号"));
        model->setHeaderData(1, Qt::Horizontal, tr("标题"));
        model->setHeaderData(2, Qt::Horizontal, tr("领域"));
        bkTableView->setModel(model);
        bkTableView->horizontalHeader()->setStretchLastSection(true);
        bkTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        bkTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
}

//打开案例
void teach::openUsecaseSlot(QString casename)
{
    QSqlQuery query(db);
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
        path.replace(0, 1, "file:///E:/MyCode/qt/NewGenerationNetworkEducation/"
                           "PatternKnowledgeEducationSystem");//此处可根据本地文件夹名称更改
        // qcout << path;
        // path这种绝对路径可以打开file:///E:/MyCode/qt/NewGenerationNetworkEducation/PatternKnowledgeEducationSystem/knowledge/usecase/U002.ppsx
        // 如何更改为相对路径呢？
        QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
        //记录用户behavior
    }
    else
    {//否则进入案例播放界面
        usecaseWindow = new usecase();
        usecaseWindow->setWindowTitle(tr("在线网络教学系统客户端"));
        usecaseWindow->setWindowModality(Qt::ApplicationModal);
        usecaseWindow->show();
        usecaseWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(usecaseWindow, &usecase::destroyed, this, &teach::updateBehaviorTableSlot);
    }
}

//重新播放案例
void teach::playAgainSlot()
{
    //首先记录上次学习的案例的结束时间以及通过情况
    QSqlQuery query(db);
    query.prepare("update behavior set end=:end,pass=0 where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();
    //重新播放刚刚的实例
    openUsecaseSlot(currentCid);
}

void teach::changeCaseSlot()
{
    QSqlQuery query(db);
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
}

//进入讨论区模块
void teach::goToDiscussionSlot()
{

}

//进入测试模块
void teach::goToTestSlot()
{
    QSqlQuery query;
    //首先记录上次学习的案例的结束时间以及通过情况
    query.prepare("update behavior set end=:end,pass=0,note=:note where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":note", note);
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();

    //进入测试
    testWindow = new test();
    testWindow->show();
    connect(testWindow, &test::destroyed, this, &teach::close);
}

////更新当前知识节点
//void teach::updateCurrentKidSlot(){
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
//}

//更新行为记录表
void teach::updateBehaviorTableSlot()
{
    QSqlQuery query(db);
    query.prepare("update behavior set end=:end,pass=0,note=:note where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":note", note);
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();
}
