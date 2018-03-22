#include "administrate.h"
#include "user.h"
#include "qtableview.h"
#include "qmessagebox.h"

extern user myUser; //全局用户变量

administrate::administrate(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
	QTimer *timer = new QTimer(this);
	havePathTab = 0;
	haveBehaviorTab = 0;

    init();

    connect(timer, &QTimer::timeout, this, &administrate::updateTimeSlot);//更新系统时间
    connect(ui.modifyButton, &QPushButton::clicked, this, &administrate::modifyInformationSlot);//修改个人信息
    connect(ui.saveButton, &QPushButton::clicked, this, &administrate::saveInformationSlot);//保存个人信息
    connect(ui.quitButton, &QPushButton::clicked, this, &administrate::close);//关闭用户管理
	timer->start(1000);
}

administrate::~administrate()
{

}

//打开数据库
void administrate::openDatabase()
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


//初始化用户管理界面
void administrate::init()
{
    //初始化各个显示标签的信息以及标签属性
	ui.usernameLabel->setText(QString::fromStdString(myUser.getName()));
	ui.usernameLineEdit->setText(QString::fromStdString(myUser.getName()));
	ui.usernameLineEdit->setReadOnly(true);
	ui.passwordLineEdit->setText(QString::fromStdString(myUser.getPassword()));
	ui.passwordLineEdit->setReadOnly(true);
	ui.sexComboBox->setCurrentText(QString::fromStdString(myUser.getSex()));
	ui.sexComboBox->setDisabled(true);
	ui.ageLineEdit->setText(QString::number(myUser.getAge()));
	ui.ageLineEdit->setReadOnly(true);
	ui.educationComboBox->setCurrentText(QString::fromStdString(myUser.getEducation()));
	ui.educationComboBox->setDisabled(true);

	openDatabase();


    if (!havePathTab)
    {//如果当前没有用户路径记录表 则new一个
		pathWidget = new QWidget();
		pathTableView = new QTableView(pathWidget);
		pathTableView->setGeometry(8, 8, 521, 271);
		ui.tabWidget->addTab(pathWidget, QStringLiteral("用户学习路径表"));
		havePathTab = 1;
	}
	//显示用户学习路径表
	QSqlQueryModel *pathmodel = new QSqlQueryModel;
	QString sqlString = "select a.domain,b.title,a.begintime,a.score from path a join ";
	sqlString += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
	sqlString += "as b where a.kid=b.kid and a.sid=";
	sqlString += QString::number(myUser.getSid());
	sqlString += " order by a.begintime";
	pathmodel->setQuery(sqlString);
	pathmodel->setHeaderData(0, Qt::Horizontal, QStringLiteral("领域"));
	pathmodel->setHeaderData(1, Qt::Horizontal, QStringLiteral("知识名称"));
	pathmodel->setHeaderData(2, Qt::Horizontal, QStringLiteral("开始学习时间"));
	pathmodel->setHeaderData(3, Qt::Horizontal, QStringLiteral("得分"));
	pathTableView->setModel(pathmodel);
	pathTableView->horizontalHeader()->setStretchLastSection(true);
	pathTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	pathTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    if (!haveBehaviorTab)
    {//如果当前没有用户学习记录表 则new一个
		behaviorWidget = new QWidget();
		behaviorTableView = new QTableView(behaviorWidget);
		behaviorTableView->setGeometry(8, 8, 521, 271);
		ui.tabWidget->addTab(behaviorWidget, QStringLiteral("用户学习记录表"));
		haveBehaviorTab = 1;
	}
	//显示用户学习记录表
	QSqlQueryModel *behaviormodel = new QSqlQueryModel;
	QString sqlString2 = "select b.title,a.cid,a.begin,a.end,a.note from behavior a join ";
	sqlString2 += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
	sqlString2 += "as b where a.kid=b.kid and a.sid=";
	sqlString2 += QString::number(myUser.getSid());
	sqlString2 += " order by a.begin";
	behaviormodel->setQuery(sqlString2);
	behaviormodel->setHeaderData(0, Qt::Horizontal, QStringLiteral("知识名称"));
	behaviormodel->setHeaderData(1, Qt::Horizontal, QStringLiteral("教学案例"));
	behaviormodel->setHeaderData(2, Qt::Horizontal, QStringLiteral("开始学习时间"));
	behaviormodel->setHeaderData(3, Qt::Horizontal, QStringLiteral("结束学习时间"));
	behaviormodel->setHeaderData(4, Qt::Horizontal, QStringLiteral("笔记记录"));
	behaviorTableView->setModel(behaviormodel);
	behaviorTableView->horizontalHeader()->setStretchLastSection(true);
	behaviorTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	behaviorTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	this->db.close();
}

//更新系统时间槽
void administrate::updateTimeSlot()
{
	QDateTime time = QDateTime::currentDateTime();
	ui.currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
}

//修改用户信息槽
void administrate::modifyInformationSlot()
{
	ui.usernameLineEdit->setReadOnly(false);
	ui.passwordLineEdit->setReadOnly(false);
	ui.sexComboBox->setDisabled(false);
	ui.ageLineEdit->setReadOnly(false);
	ui.educationComboBox->setDisabled(false);
}

//保存用户信息槽  //BUG  保存完之后，还需要将各个标签设置为只读属性。
void administrate::saveInformationSlot()
{
    //获取用户修改的信息，以便来更新myUser信息和数据库中的用户信息
	int _sid = myUser.getSid();
	QString _username = ui.usernameLineEdit->text();
    QString _password = ui.passwordLineEdit->text();
	QString _sex = ui.sexComboBox->currentText();
	int _age = ui.ageLineEdit->text().toInt();
	QString _education = ui.educationComboBox->currentText();

    //更新全局的myUser信息
	myUser.setName(_username.toStdString());
	myUser.setPassword(_password.toStdString());
	myUser.setAge(_age);
	myUser.setSex(_sex.toStdString());
	myUser.setEducation(_education.toStdString());

    //更新数据库中的用户信息
	openDatabase();
	QSqlQuery query;
	query.prepare("update student set name=:name,password=:password,sex=:sex,age=:age,education=:education where sid=:sid");
	query.bindValue(":name", _username);
	query.bindValue(":password", _password);
	query.bindValue(":sex", _sex);
	query.bindValue(":age", _age);
	query.bindValue(":education", _education);
	query.bindValue(":sid", _sid);
	query.exec();
	this->db.close();
	QMessageBox::information(this, QStringLiteral("恭喜"), QStringLiteral("您的信息已修改并保存成功！"));
    //必须等QMessageBox关闭，才能执行init()
    init();
}
