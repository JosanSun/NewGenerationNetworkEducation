#include "login.h"
#include "qpixmap.h"
#include "user.h"
#include <QDebug>
#include "qmessagebox.h"

user myUser;

login::login(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    setTabOrder(ui.usernameLineEdit, ui.passwordLineEdit);
    setTabOrder(ui.passwordLineEdit, ui.loginButton);
    setTabOrder(ui.loginButton, ui.registerButton);
	QPixmap pic;
    pic.load("../images/online.png");
	ui.picLabel->setPixmap(pic);
	ui.picLabel->setScaledContents(true);
	QObject::connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(loginSlot()));//点击登录按钮登录
	QObject::connect(ui.passwordLineEdit, SIGNAL(returnPressed()), this, SLOT(loginSlot()));//回车键后登录
	QObject::connect(ui.registerButton, SIGNAL(clicked()), this, SLOT(registorSlot()));//注册
	
}

login::~login()
{

}

//登录
void login::loginSlot(){
    //打开数据库
	this->db = QSqlDatabase::addDatabase("QMYSQL");
	this->db.setHostName("localhost");
	this->db.setUserName("root");
	this->db.setPassword("1234");
	this->db.setDatabaseName("knowledge");
	bool ok = db.open();
	if (ok){
		qDebug() << "Success!";
	}
	else{
		qDebug() << "Failed to connect database login!";
	}


	QString _username = ui.usernameLineEdit->text();
	QString _password = ui.passwordLineEdit->text();
	QSqlQuery query;
	query.prepare("select * from student where name=:name");
	query.bindValue(":name", _username);
	query.exec();
	/*if (ui.customRadioButton->isChecked()){*///普通用户登录
		if (query.first()){//查询结果集不为空
            //返回上一个查询结果
            query.previous();
			while (query.next()){
				if (query.value(2).toString() == _password){
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
				else{
					QMessageBox::information(this, QStringLiteral("错误！"), QStringLiteral("密码错误！"));
					ui.passwordLineEdit->clear();
				}
			}
		}
		else{//结果集为空
			QMessageBox::information(this, QStringLiteral("错误！"), QStringLiteral("您还不是系统用户！请您先注册！"));
			ui.usernameLineEdit->clear();
			ui.passwordLineEdit->clear();
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
void login::registorSlot(){
	regWindow = new registor();
	regWindow->setWindowTitle(QStringLiteral("在线网络教学系统客户端"));
    regWindow->setWindowModality(Qt::ApplicationModal);  //?
	regWindow->show();
    regWindow->setAttribute(Qt::WA_DeleteOnClose);  //?
}
