#include "usecase.h"
#include "user.h"
#include "qdatetime.h"
#include "qtimer.h"
#include "qfile.h"
#include "qurl.h"
#include <QtGui>
#include "qtextcodec.h"
#include "qwidget.h"
#include <ActiveQt\qaxwidget.h>


extern QString currentKid;
extern QString currentCid;
extern user myUser;
QString note;

usecase::usecase(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.textEdit->setReadOnly(false);
	ui.currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
	QTimer *timer = new QTimer(this);
	ui.usernameLabel->setText(QString::fromStdString(myUser.getName()));
	init();
	
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeSlot()));
	connect(ui.testButton, SIGNAL(clicked()), this, SLOT(goToTestWindowSlot()));//进入测试模块
	timer->start(1000);
}

usecase::~usecase()
{

}

void usecase::openDatabase(){
	this->db = QSqlDatabase::addDatabase("QMYSQL");
	this->db.setHostName("localhost");
	this->db.setUserName("root");
	this->db.setPassword("1234");
	this->db.setDatabaseName("knowledge");
	bool ok = db.open();
	if (!ok){
		qDebug() << "Failed to connect database login!";
	}
	else{
		qDebug() << "Success!";
	}
}

//初始化案例播放界面
void usecase::init(){
	QString casename = currentCid;
	openDatabase();
	QSqlQuery query;
	QString path;
	query.exec("select * from teach where kid='" + currentKid + "' and cid='" + currentCid + "'");
	while (query.next()){
		path = query.value(2).toString();
	}
	this->db.close();
	QString _form = casename.remove(0, 5);
	if (_form == "txt"){
		QFile _caseFile(path);
		if (!_caseFile.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QTextStream out(&_caseFile);
		while (out.atEnd() == 0){
			ui.textBrowser->setText(out.readAll());
		}
	}
	else if (_form == "html"){
		path.replace(0, 1, "file:///D:/qtest/KnowledgeModel/KnowledgeModel");
		qDebug() << path;
		QUrl url(path);		
		ui.textBrowser->setSource(url);
	}
	else if (_form == "swf"){
		path.replace(19, 1, "\\");
		path.replace(0, 1, "D:/qtest/KnowledgeModel/KnowledgeModel");		
		qDebug() << path;
		QAxWidget *flash = new QAxWidget(ui.textBrowser);      //QAxWidget使用的是ActiveX插件
		flash->resize(701,461);                    //设置该控件的初始大小
		flash->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));	
		flash->dynamicCall("LoadMovie(long,string)", 0, path);
		flash->show();
		flash->setAttribute(Qt::WA_DeleteOnClose);
		/*QTime t;
		t.start();
		while (t.elapsed()<5000)
		{
			QApplication::processEvents();
		}
		flash->close();*/
	}

}

void usecase::updateTimeSlot(){
	QDateTime time = QDateTime::currentDateTime();
	ui.currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
	note = ui.textEdit->toPlainText();
}

//进入测试模块
void usecase::goToTestWindowSlot(){
	note = ui.textEdit->toPlainText();
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
	this->close();
	testWindow = new test();
	testWindow->setWindowTitle(QStringLiteral("在线网络教学系统客户端"));
	testWindow->setWindowModality(Qt::ApplicationModal);
	testWindow->show();
	testWindow->setAttribute(Qt::WA_DeleteOnClose);
}
