#include "stable.h"
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
#include "ui_teach.h"
#include "helper/user.h"
#include "helper/mypushbutton.h"
#include "helper/myheaders.h"

extern User myUser;
extern QString currentKid;
QString currentCid;
extern QString note;

Teach::Teach(QWidget *parent)
    : QWidget(parent), ui(new Ui::Teach), timer(new QTimer(this))
{
    ui->setupUi(this);
    initUI();
    init();

    connect(ui->buttonClose, &QPushButton::clicked, this, &Teach::close);                                 // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &Teach::showMinimized);                           // 点击最小化
    connect(timer, &QTimer::timeout, this, &Teach::timeUpdateSlot);                         //更新系统时间
    connect(ui->playAgainButton, &QPushButton::clicked, this, &Teach::playAgainSlot);        //重新播放案例
    connect(ui->changeCaseButton, &QPushButton::clicked, this, &Teach::changeCaseSlot);      //更换案例
    connect(ui->discussionButton, &QPushButton::clicked, this, &Teach::goToDiscussionSlot);  //进入讨论区
    connect(ui->beginTestButton, &QPushButton::clicked, this, &Teach::goToTestSlot);         //进入测试模块
    connect(ui->quitButton, &QPushButton::clicked, this, &Teach::close);                     //关闭系统
}

Teach::~Teach()
{
    delete ui;

    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void Teach::openDatabase()
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
void Teach::timeUpdateSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui->currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
}

void Teach::initUI()
{
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//无边框且最小化任务栏还原

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);//设置窗口背景颜色：白

    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ui->buttonMin->setIcon(minPix);
    ui->buttonClose->setIcon(closePix);//获取并设置

    ui->currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
    ui->usernameLabel->setText(QString::fromStdString(myUser.getName()));
}

//初始化教学界面
void Teach::init()
{
    mMove=false;//mouse moving
    haveDomainTab = false;
    currentCid = "";
    timer->start(1000);

    openDatabase();
    QSqlQuery query(db);
    QString _first = currentKid.left(1);//根据系统当前知识点查询数据库
    qcout << currentKid;
    if (_first == "B")
    {
        //当前知识点是基本知识节点
        query.exec("select * from bk where bid='" + currentKid + "'");
        while (query.next())
        {
            ui->pointnameLabel->setText(query.value(1).toString());
            //显示当前知识的description信息
            QString _descFileName = query.value(3).toString();
            _descFileName.replace(0, 1, "../PatternKnowledgeEducationSystem");
            qcout << _descFileName;
            QFile _descFile(_descFileName);
            // QIODevice::Text 会改变原来文件的换行方式，不推荐这种打开方式
            if(!_descFile.open(QIODevice::ReadOnly))
            {
                QMessageBox::warning(this, tr("网络教学系统"),
                                     tr("Cannot read file %1.\n%2.")
                                     .arg(_descFile.fileName())
                                     .arg(_descFile.errorString()));
                return;
            }
            //qcout << _descFile.readAll();
            ui->descriptionTextBrowser->clear();

            QTime t1, t2, t3, t4;
            t1 = QTime::currentTime();
            const QByteArray data = _descFile.readAll();
            t2 = QTime::currentTime();
            qcout << t1.msecsTo(t2);
            QTextCodec::ConverterState state;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            const QString text = codec->toUnicode(data.constData(), data.size(), &state);
            //qcout << text;
            t3 = QTime::currentTime();
            qcout << t2.msecsTo(t3);
            if (state.invalidChars > 0)
            {
                // Not a UTF-8 text - using system default locale
                QTextCodec * codec1 = QTextCodec::codecForLocale();
                qcout << codec1->name();
                if (!codec1)
                    return ;
                qcout << "invalidChars > 0";
                ui->descriptionTextBrowser->setText(codec1->toUnicode(data));
            }
            else
            {
                qcout << "invalidChars = 0";
                ui->descriptionTextBrowser->setText(text);
            }
            t4 = QTime::currentTime();
            qcout << t3.msecsTo(t4);

//            if (!_descFile.open(QIODevice::ReadOnly | QIODevice::Text))
//                return;
//            // QTextStream out(&_descFile);
//            qcout << out.readAll();
//            out.seek(0);
//            while (!out.atEnd())
//            {
//                //知识点描述窗口
//                ui->descriptionTextBrowser->setText(out.readAll());
//            }
            //领域知识按钮---查找与显示
            //显示当前知识的领域信息  领域信息以,相分隔
            QString _domain = query.value(2).toString();
            QString _sep = ",";
            int inx = 1;
            int pos=_domain.indexOf(_sep);
            while (pos != -1)
            {
                MyPushButton *domainButton = new MyPushButton(ui->groupBox_2);
                domainButton->setGeometry(110 + 100 * (inx - 1), 230, 80, 23);
                domainButton->setText(_domain.left(pos));
                //点击领域知识按钮，触发显示领域知识信息   不点击的话，默认不显示
                void (MyPushButton::*pfn)(QString) = MyPushButton::clicked;
                // connect(domainButton, pfn, this, SLOT(showDomainKnowledgesSlot(QString)));
                connect(domainButton, pfn, this, &Teach::showDomainKnowledgesSlot);
                _domain = _domain.remove(0, pos+1);
                ++inx;
                pos = _domain.indexOf(_sep);
            }
            //处理最后一个领域知识按钮
            MyPushButton *domainButton = new MyPushButton(ui->groupBox_2);
            domainButton->setGeometry(110 + 100 * (inx - 1), 230, 80, 23);
            domainButton->setText(_domain);
            void (MyPushButton::*pfn1)(QString) = MyPushButton::clicked;
            //connect(domainButton, pfn1, this, SLOT(showDomainKnowledgesSlot(QString)));
            connect(domainButton, pfn1, this, &Teach::showDomainKnowledgesSlot);

        }
        //显示当前知识的案例按钮
        query.exec("select * from teach where kid='" + currentKid + "'");
        int inx = 1;
        while (query.next())
        {
            MyPushButton *usecaseButton = new MyPushButton(ui->groupBox_2);
            usecaseButton->setGeometry(110 + 100 * (inx - 1), 270, 80, 23);
            usecaseButton->setText(query.value(1).toString());
            //点击案例按钮，触发打开案例界面
            void (MyPushButton::*pfn2)(QString) = MyPushButton::clicked;
            //connect(usecaseButton, pfn2, this, SLOT(openUsecaseSlot(QString)));
            connect(usecaseButton, pfn2, this, &Teach::openUsecaseSlot);
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
                    MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 80, 23);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                //处理最后一个前驱
                MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 80, 23);
            }
            else if (query.value(1).toInt() == 1)
            {//后继
                QString _about = query.value(2).toString();
                QString _sep = ",";
                int inx = 1;
                int pos = _about.indexOf(_sep);
                while (pos != -1)
                {
                    MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 80, 23);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                //处理最后一个后继
                MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 80, 23);
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
            ui->pointnameLabel->setText(query.value(1).toString());
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
                MyPushButton *domainButton = new MyPushButton(ui->groupBox_2);
                domainButton->setGeometry(110 + 100 * (inx - 1), 230, 80, 23);
                domainButton->setText(_domain.left(pos));
                void (MyPushButton::*pfn3)(QString) = MyPushButton::clicked;
                connect(domainButton, pfn3, this, &Teach::showDomainKnowledgesSlot);
                _domain = _domain.remove(0, pos + 1);
                ++inx;
                pos = _domain.indexOf(_sep);
            }
            MyPushButton *domainButton = new MyPushButton(ui->groupBox_2);
            domainButton->setGeometry(110 + 100 * (inx - 1), 230, 80, 23);
            domainButton->setText(_domain);
            void (MyPushButton::*pfn4)(QString) = MyPushButton::clicked;
            connect(domainButton, pfn4, this, &Teach::showDomainKnowledgesSlot);
        }


        //显示当前知识的案例按钮
        query.exec("select * from teach where kid='" + currentKid + "'");
        int inx = 1;
        while (query.next())
        {
            MyPushButton *usecaseButton = new MyPushButton(ui->groupBox_2);
            usecaseButton->setGeometry(110 + 100 * (inx - 1), 270, 80, 23);
            usecaseButton->setText(query.value(1).toString());
            void (MyPushButton::*pfn5)(QString) = MyPushButton::clicked;
            connect(usecaseButton, pfn5, this, &Teach::openUsecaseSlot);
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
                    MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 80, 23);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 310, 80, 23);
            }
            else if (query.value(1).toInt() == 1)
            {//后继
                QString _about = query.value(2).toString();
                QString _sep = ",";
                int inx = 1;
                int pos = _about.indexOf(_sep);
                while (pos != -1)
                {
                    MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                    aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 80, 23);
                    _about = _about.remove(0, pos + 1);
                    ++inx;
                    pos = _about.indexOf(_sep);
                }
                MyPushButton *aboutKnowButton = new MyPushButton(ui->groupBox_2);
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
                aboutKnowButton->setGeometry(110 + 100 * (inx - 1), 350, 80, 23);
            }
        }
    }
}

//重写鼠标函数实现窗口自由移动
void Teach::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void Teach::mouseMoveEvent(QMouseEvent *event)
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

void Teach::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

//模式知识模式属性读取xml文档
void Teach::openXml(QString filename)
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
                ui->descriptionTextBrowser->append(tr("模式：") + e.text());
            }
            else if (e.tagName() == "pproblem")
            {
                ui->descriptionTextBrowser->append(tr("解决问题：") + e.text());
            }
            else if (e.tagName() == "psolution")
            {
                ui->descriptionTextBrowser->append(tr("解决方案：") + e.text());
            }
            else if (e.tagName() == "pcharacteries")
            {
                ui->descriptionTextBrowser->append(tr("特征点："));
                QDomNode cnode = e.firstChild();
                while (!cnode.isNull())
                {
                    QDomElement ce = cnode.toElement();
                    if (!ce.isNull())
                    {
                        ui->descriptionTextBrowser->append(ce.text());
                    }
                    cnode = cnode.nextSibling();
                }
            }
            else if (e.tagName() == "preference")
            {
                ui->descriptionTextBrowser->append(tr("参考："));
                QDomNode pnode = e.firstChild();
                while (!pnode.isNull())
                {
                    QDomElement pe = pnode.toElement();
                    if (!pe.isNull())
                    {
                        ui->descriptionTextBrowser->append(pe.text());
                    }
                    pnode = pnode.nextSibling();
                }
            }
        }
        node = node.nextSibling();
    }

}

//显示领域相关知识节点信息
void Teach::showDomainKnowledgesSlot(QString domain)
{
    //ERROR: 这部分逻辑有问题
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
        ui->tabWidget->addTab(domainKnowWidget, tr("领域相关知识"));
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
void Teach::openUsecaseSlot(QString casename)
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
    {
        //如果用户点击的案例为ppt类型，则直接显示该案例
        QString path;
        query.exec("select * from teach where kid='" + currentKid + "' and cid='" + currentCid + "'");
        while (query.next())
        {
            path = query.value(2).toString();
        }
        QString curpath = QDir::currentPath();
        //qcout << curpath;
        int loc = curpath.lastIndexOf('/');
        //qcout << loc;
        curpath.remove(loc, curpath.size());
        curpath.append("/PatternKnowledgeEducationSystem");
        curpath.prepend("file:///");
        //curpath.replace('\\', '/');
        //qcout << curpath;
        path.replace(0, 1, curpath);//此处可根据本地文件夹名称更改
        // qcout << path;
        // path这种绝对路径可以打开file:///E:/MyCode/qt/github/NewGenerationNetworkEducation/PatternKnowledgeEducationSystem/knowledge/usecase/U002.ppsx
        // 如何更改为相对路径呢？   已解决！
        QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
        //记录用户behavior
    }
    else
    {//否则进入案例播放界面
        usecaseWindow = new Usecase();
        usecaseWindow->show();
        connect(usecaseWindow, &Usecase::destroyed, this, &Teach::updateBehaviorTableSlot);
    }
}

//重新播放案例
void Teach::playAgainSlot()
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

void Teach::changeCaseSlot()
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
void Teach::goToDiscussionSlot()
{

}

//进入测试模块
void Teach::goToTestSlot()
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
    testWindow = new Test();
    testWindow->show();
    connect(testWindow, &Test::destroyed, this, &Teach::close);
}

////更新当前知识节点
//void Teach::updateCurrentKidSlot(){
//	QSqlQuery query;
//	QString _first = currentKid.left(1);
//	if (_first == "B"){
//		query.exec("select title from bk where bid='" + currentKid + "'");
//		while (query.next()){
//			ui->pointnameLabel->setText(query.value(0).toString());
//		}
//	}
//	else if (_first == "P"){
//		query.exec("select title from pk where pid='" + currentKid + "'");
//		while (query.next()){
//			ui->pointnameLabel->setText(query.value(0).toString());
//		}
//	}
//}

//更新行为记录表
void Teach::updateBehaviorTableSlot()
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

//下一个知识节点
void Teach::on_nextKnowledgeButton_clicked()
{
    QString beforeKid = currentKid;
    QSqlQuery query(db);
    query.prepare("select kid from recpath where sid=:sid and state=0 order by orders");
    query.bindValue(":sid", myUser.getSid());
    query.exec();
    while (query.next())
    {
        currentKid = query.value(0).toString();
        qcout << currentKid;
        break;
    }
    QString _first = beforeKid.left(1);
    if (_first=="P")
    {
        query.prepare("update recpath set state=0 where sid=:sid and kid=:kid");
        query.bindValue(":sid", myUser.getSid());
        query.bindValue(":kid", beforeKid);
        query.exec();
    }
    this->close();
}
