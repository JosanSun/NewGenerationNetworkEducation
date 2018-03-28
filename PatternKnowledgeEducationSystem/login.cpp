#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>

#include "user.h"
#include "login.h"

user myUser;

login::login(QWidget *parent)
    :  QWidget(parent)
{
    ui.setupUi(this);

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
    ui.buttonMin->setIcon(minPix);
    ui.buttonClose->setIcon(closePix);//获取并设置最小化、关闭按钮图标
    ui.buttonMin->setStyleSheet("background-color:transparent;");
    ui.buttonClose->setStyleSheet("background-color:transparent;");//最小化、关闭按钮无边框且透明

    // ui.buttonFindBackPassword->setStyleSheet("color:rgb(38 , 133 , 227);background-color:transparent;");
    // ui.buttonRegister->setStyleSheet("color:rgb(38 , 133 , 227);background-color:transparent;");
    // ui.buttonLogin->setStyleSheet("color:white;background-color:rgb(14 , 150 , 254);border-radius:5px;");//设置其他按钮样式

    ui.usernamebox->setEditable(true);
    QLineEdit* lineEdit = ui.usernamebox->lineEdit();
    lineEdit->setPlaceholderText(QStringLiteral("用户名"));
    ui.passwordtext->setPlaceholderText(QStringLiteral("密码"));//用户名和密码的暗注释

    // 设置焦点
    ui.usernamebox->setFocus();
    setTabOrder(ui.usernamebox,ui.passwordtext);
    setTabOrder(ui.passwordtext, ui.buttonLogin);
    setTabOrder(ui.buttonLogin, ui.buttonRegister);//Tab键顺序

    QPixmap pic;
    pic.load(":/images/icon.png");
    ui.piclabel->setPixmap(pic);
    ui.piclabel->setScaledContents(true);//设置头像图

    QObject::connect(ui.buttonLogin, &QPushButton::clicked, this, &login::loginSlot);//点击登录按钮登录
    QObject::connect(ui.passwordtext, &QLineEdit::returnPressed, this, &login::loginSlot);//回车键后登录
    QObject::connect(ui.buttonRegister, &QPushButton::clicked, this, &login::registorSlot);//注册
    QObject::connect(ui.buttonClose, &QPushButton::clicked, this, &QWidget::close);//点击关闭
    QObject::connect(ui.buttonMin, &QPushButton::clicked, this, &QWidget::showMinimized);//点击最小化
}

login::~login()
{

}

//登录
void login::loginSlot()
{
    //打开数据库
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("1234");
    this->db.setDatabaseName("knowledge");
    bool ok = db.open();
    if (ok)
    {
        qDebug() << "Success!";
    }
    else
    {
        qDebug() << "Failed to connect database login!";
    }


    QString _username = ui.usernamebox->currentText();
    QString _password = ui.passwordtext->text();
    QSqlQuery query;
    query.prepare("select * from student where name=:name");
    query.bindValue(":name", _username);
    query.exec();
    /*if (ui.customRadioButton->isChecked()){*///普通用户登录
    if (query.first())
    {//查询结果集不为空
        //返回上一个查询结  果
        query.previous();
        while (query.next())
        {
            if (query.value(2).toString() == _password)
            {
                //对全局myUser进行部分初始化
                myUser.setName(_username.toStdString());
                myUser.setPassword(_password.toStdString());
                initWindow = new initial();
                initWindow->setWindowTitle(QStringLiteral("在线网络教学系统客户端"));
                initWindow->show();
                initWindow->setAttribute(Qt::WA_DeleteOnClose);
                //关闭登录窗口
                this->close();
            }
            else
            {
                QMessageBox::information(this, QStringLiteral("错误！"), QStringLiteral("密码错误！"));
                ui.passwordtext->clear();
            }
        }
    }
    else
    {//结果集为空
        QMessageBox::information(this, QStringLiteral("错误！"), QStringLiteral("您还不是系统用户！请您先注册！"));
        ui.usernamebox->clear();
        ui.passwordtext->clear();
        //调用registorSlot()槽函数
        registorSlot();
    }
    //}
    //else if (ui.adminRadioButton->isChecked()){//管理员登录

    //}
    //关闭数据库
    this->db.close();
}

//进入注册模块
void login::registorSlot()
{
    regWindow = new registor();
    regWindow->setWindowTitle(QStringLiteral("在线网络教学系统客户端"));
    regWindow->setWindowModality(Qt::ApplicationModal);  //?
    regWindow->show();
    regWindow->setAttribute(Qt::WA_DeleteOnClose);  //?
}
