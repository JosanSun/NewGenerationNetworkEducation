#include "registor.h"
#include <qmessagebox.h>

registor::registor(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.registerButton, &QPushButton::clicked,
            this, &registor::registerSlot);//点击注册用户
    connect(ui.cancelButton, &QPushButton::clicked,
            this, &registor::close);//关闭注册界面
}

registor::~registor()
{

}

//用户注册槽
void registor::registerSlot()
{
    QString _username = ui.usernameLineEdit->text();
    if (_username.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("错误！"),
                                 QStringLiteral("请输入合法的用户名！"));
        return;
    }
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
        qDebug() << "Failed to connect database registor!";
    }

    QSqlQuery query;
    query.exec("select * from student where name='" + _username + "'");
    if (query.first())
    {//注册的用户已存在
        QMessageBox::information(this, QStringLiteral("注意！"), QStringLiteral("您已经注册过！请直接登录！"));
        this->close();
    }
    //未注册过开始注册
    QString _password = ui.passwordLineEdit->text();
    if (_password.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("错误！"), QStringLiteral("请输入合法的密码！"));
        return;
    }
    //密码输入错误
    QString _okpassword = ui.doublePasswordLineEdit->text();
    if (_password != _okpassword)
    {
        QMessageBox::information(this, QStringLiteral("错误！"), QStringLiteral("请确认密码后重新输入！"));
        ui.passwordLineEdit->clear();
        ui.doublePasswordLineEdit->clear();
        return;
    }
    QString _sex = ui.sexComboBox->currentText();
    QString _age = ui.ageLineEdit->text();
    QString _education = ui.educationComboBox->currentText();

    query.prepare("insert into student(name,password,sex,age,education) values(:name,:password,:sex,:age,:education)");
    query.bindValue(":name", _username);
    query.bindValue(":password", _password);
    query.bindValue(":sex", _sex);
    query.bindValue(":age", _age);
    query.bindValue(":education", _education);
    query.exec();

    this->db.close();
    QMessageBox::information(this, QStringLiteral("恭喜！"), QStringLiteral("您已经注册成功！请登录！"));
    this->close();
}
