#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>

#include "helper/user.h"
#include "login.h"
#include "ui_login.h"

user myUser;

login::login(QWidget *parent)
    :  QWidget(parent), ui(new Ui::login)
{
    ui->setupUi(this);

    mMove=false;//mouse moving

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
    // 20180328 -- 关于placeholderText提示符的设置，以后统一在ui完成。 QLineEdit
    // ui->passwordtext->setPlaceholderText(tr("密码"));//用户名和密码的暗注释

    // 设置焦点以及tab顺序
    ui->usernamebox->setFocus();
    // 20180328 -- 以后关于setTabOrder的处理统一到UI上搞定
    //    setTabOrder(ui->usernamebox,ui->passwordtext);
    //    setTabOrder(ui->passwordtext, ui->buttonLogin);
    //    setTabOrder(ui->buttonLogin, ui->buttonRegister);//Tab键顺序

    // 20180328 -- 关于label设定图标的，统一用UI设计，图片统一用资源文件，这样设计图标位置更方便。
    //    QPixmap pic;
    //    pic.load(":/images/icon.png");
    //    ui->piclabel->setPixmap(pic);
    //    ui->piclabel->setScaledContents(true);//设置头像图

    QObject::connect(ui->buttonLogin, &QPushButton::clicked, this, &login::loginSlot);          // 点击登录按钮登录
    QObject::connect(ui->passwordtext, &QLineEdit::returnPressed, this, &login::loginSlot);     // 回车键后登录
    QObject::connect(ui->buttonRegister, &QPushButton::clicked, this, &login::registorSlot);    // 注册
    QObject::connect(ui->buttonClose, &QPushButton::clicked, this, &login::close);              // 点击关闭
    QObject::connect(ui->buttonMin, &QPushButton::clicked, this, &login::showMinimized);        // 点击最小化

    openDatabase();
}

login::~login()
{
    db.close();
}

//重写鼠标函数实现窗口自由移动
void login::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void login::mouseMoveEvent(QMouseEvent *event)
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

void login::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

void login::openDatabase()
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
void login::loginSlot()
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
                initWindow = new initial();
                initWindow->setWindowTitle(tr("在线网络教学系统客户端"));
                initWindow->show();
                initWindow->setAttribute(Qt::WA_DeleteOnClose);
                //关闭登录窗口
                this->close();
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
void login::registorSlot()
{
    hide();
    regWindow = new registor();
    regWindow->setWindowTitle(tr("在线网络教学系统客户端"));
    regWindow->setWindowModality(Qt::ApplicationModal);
    regWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(regWindow, &registor::registerUser,
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
    connect(regWindow, &registor::closeSignal,
            [=]()
    {
        this->show();
    });

    regWindow->show();
}
