#include "stable.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>

#include "login.h"
#include "ui_login.h"


User myUser;

Login::Login(QWidget *parent)
    :  QWidget(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
    initUI();

    // usernambox栏安装事件过滤器
    ui->usernamebox->installEventFilter(this);
    mMove=false;//mouse moving

    connect(ui->buttonLogin, &QPushButton::clicked, this, &Login::loginSlot);          // 点击登录按钮登录
    connect(ui->passwordtext, &QLineEdit::returnPressed, this, &Login::loginSlot);     // 回车键后登录
    connect(ui->buttonRegister, &QPushButton::clicked, this, &Login::registorSlot);    // 注册
    connect(ui->buttonClose, &QPushButton::clicked, this, &Login::close);              // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &Login::showMinimized);        // 点击最小化

    openDatabase();
}

// 事件过滤器
bool Login::eventFilter(QObject *obj, QEvent *event)
{
    //用户在输入用户名时，按下回车键，可以直接转密码的输入.
    if(obj == ui->usernamebox)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            if (keyEvent->key() == Qt::Key_Return || keyEvent->key()==Qt::Key_Enter)
            {
                ui->passwordtext->setFocus();
                return true;
            }
        }
    }

    return QObject::eventFilter(obj,event);
}


Login::~Login()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void Login::initUI()
{
    this->setFixedSize(432, 330);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//无边框且最小化任务栏还原
    //setAttribute(Qt::WA_TranslucentBackground);//窗口背景透明
    //setAttribute(Qt::WA_DeleteOnClose);
    QPixmap pixmap = QPixmap(":/images/bj.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);//设置窗口背景图

    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ui->buttonMin->setIcon(minPix);
    ui->buttonClose->setIcon(closePix);//获取并设置最小化、关闭按钮图标

    // ui->usernamebox->setEditable(true);    // 见ui设置
    QLineEdit* lineEdit = ui->usernamebox->lineEdit();
    lineEdit->setPlaceholderText(tr("用户名"));

    // 设置焦点以及tab顺序
    ui->usernamebox->setFocus();
}

void Login::updateCogModel(CogModel &model)
{
    // 更新全局用户的认知风格
    myUser.getModel().setCogApproach(model.getCogApproach());
    myUser.getModel().setCogStrategy(model.getCogStrategy());

    // 更新数据库
    QSqlQuery query;
    query.prepare("update student set cogApproach=:cogApproach , "
                  "cogStrategy=:cogStrategy where sid=:sid;");
    query.bindValue(":cogApproach", QString(model.getCogApproach().data()));
    query.bindValue(":cogStrategy", QString(model.getCogStrategy().data()));
    query.bindValue(":sid", myUser.getSid());
    query.exec();
}


//重写鼠标函数实现窗口自由移动
void Login::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void Login::mouseMoveEvent(QMouseEvent *event)
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

void Login::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

void Login::openDatabase()
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

// 登录
void Login::loginSlot()
{
    QString _username = ui->usernamebox->currentText();
    if(_username.isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请您输入用户名后再登录"));
        return;
    }
    QString _password = ui->passwordtext->text();
    if(_password.isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请您输入密码后再登录"));
        return;
    }

    QSqlQuery query;
    query.prepare("select * from student where name=:name");
    query.bindValue(":name", _username);
    query.exec();
    /*if (ui->customRadioButton->isChecked()){*///普通用户登录
    if (query.first())
    {//查询结果集不为空
        //返回上一个查询结果
        query.previous();
        while (query.next())
        {
            if (query.value(2).toString() == _password)
            {
                //对全局myUser进行部分初始化
                myUser.setName(_username.toStdString());
                myUser.setPassword(_password.toStdString());
                myUser.setSid(query.value(0).toInt());
                myUser.setAge(query.value(3).toInt());
                myUser.setEducation(query.value(4).toString().toStdString());
                CogModel tmp;
                tmp.setCogApproach(query.value(5).toString().toStdString());
                tmp.setCogStrategy(query.value(6).toString().toStdString());
                tmp.setCogExperience(query.value(7).toString().toStdString());
                tmp.setMetaCogAbility(query.value(8).toString().toStdString());
                myUser.setModel(tmp);

                string curCogApproach = myUser.getModel().getCogApproach();
                CogModel model;

                if(!curCogApproach.empty())
                {
                    hide();
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(tr("警告"));
                    msgBox.setText(tr("系统检测到您是初次学习本系统。强烈建议您通过问卷测量表初始化您的认知方式，这样系统能"
                                      "更加准确地为您推荐学习案例。否则，系统会采用默认值作为初始值。\n是否现在进行问卷调查？"));
                    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    msgBox.setDefaultButton(QMessageBox::Yes);
                    int ret = msgBox.exec();
                    if(ret == QMessageBox::Yes)
                    {
                        patternTestWindow = new PatternTest();
                        patternTestWindow->show();
                        connect(patternTestWindow, &PatternTest::getCogApproach,
                                [=](QString curStr) mutable
                        {
                            QString str = curStr;
                            model.setCogApproach(str.toStdString());
                            model.setCogStrategy(string("复述策略"));
                            updateCogModel(model);

                        });
                        connect(patternTestWindow, &PatternTest::closeSignal,
                                [=]()
                        {
                            initWindow = new Initial();
                            // initWindow->setCurrentUserId(query.value(0).toString());   // 这个用来解决全局变量的设定
                            initWindow->show();
                            //关闭登录窗口
                            this->close();
                            return ;
                        });
                    }
                    else
                    {
                        model.setCogApproach("活跃型");
                        model.setCogStrategy("复述策略");
                        updateCogModel(model);

                        initWindow = new Initial();
                        initWindow->show();
                        this->close();
                    }
                }
                else
                {
                    initWindow = new Initial();
                    initWindow->show();
                    this->close();
                }
            }
            else
            {
                QMessageBox::information(this, tr("错误！"), tr("密码错误！"));
                ui->passwordtext->clear();
            }
        }
    }
    else
    {//结果集为空
        QMessageBox::information(this, tr("错误！"), tr("您还不是系统用户！请您先注册！"));
        ui->usernamebox->clear();
        ui->passwordtext->clear();
        //调用registorSlot()槽函数
        registorSlot();
    }
    //}
    //else if (ui->adminRadioButton->isChecked()){//管理员登录

    //}
}

//进入注册模块
void Login::registorSlot()
{
    hide();
    regWindow = new Registor();

    connect(regWindow, &Registor::registerUser,
            [=]()
    {
        QString _username = regWindow->getUserName();
        if (_username.isEmpty())
        {
            QMessageBox::information(this, tr("错误！"),
                                     tr("请输入合法的用户名！"));
            return;
        }

        QSqlQuery query;
        query.exec("select * from student where name='" + _username + "'");
        if (query.first())
        {//注册的用户已存在
            QMessageBox::information(this, tr("注意！"), tr("此账号已被注册，请重新输入用户名"));
            regWindow->resetUserName();
            return;
        }

        //未注册过开始注册
        QString _password = regWindow->getPassword();
        if (_password.isEmpty())
        {
            QMessageBox::information(this, tr("错误！"), tr("请输入合法的密码！"));
            return;
        }
        //密码输入错误
        QString _okpassword = regWindow->getDoublePassword();
        if (_password != _okpassword)
        {
            QMessageBox::information(this, tr("错误！"), tr("请确认密码后重新输入！"));
            regWindow->resetPassword();
            regWindow->resetDoublePassword();
            return;
        }
        QString _sex = regWindow->getSex();
        QString _age = regWindow->getAge();
        QString _education = regWindow->getEducation();

        query.prepare("insert into student(name,password,sex,age,education) values(:name,:password,:sex,:age,:education)");
        query.bindValue(":name", _username);
        query.bindValue(":password", _password);
        query.bindValue(":sex", _sex);
        query.bindValue(":age", _age);
        query.bindValue(":education", _education);
        query.exec();

        QMessageBox::information(this, tr("恭喜！"), tr("您已经注册成功！请登录！"));
        regWindow->close();
    });
    connect(regWindow, &Registor::closeSignal,
            [=]()
    {
        this->show();
    });

    regWindow->show();
}
