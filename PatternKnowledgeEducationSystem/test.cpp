#include "test.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "user.h"
#include "qradiobutton.h"
#include "qmessagebox.h"

extern user myUser;
extern QString currentKid;
extern QString currentCid;

test::test(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	pass = false;
	currentTid = "";
	currentDomain = "";
	limitScore = 0;
	init();
	ui.currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdateSlot()));//更新系统时间
	connect(ui.submitButton, SIGNAL(clicked()), this, SLOT(submitTestSlot()));//提交测试
	timer->start(1000);
}

test::~test()
{

}

//初始化测试界面
void test::init(){
	ui.usernameLabel->setText(QString::fromStdString(myUser.getName()));
	ui.submitButton->setDisabled(true);
	openDatabase();
	QSqlQuery query;
	_first = currentKid.left(1);//根据当前知识节点查询数据库获得该知识节点的所需测试时间
	if (_first == "B"){
		query.exec("select title,domain from bk where bid='" + currentKid + "'");
	}
	else{
		query.exec("select title,domain from pk where pid='" + currentKid + "'");
	}
	while (query.next()){
		ui.currentPointNameLabel->setText(query.value(0).toString());
		currentDomain = query.value(1).toString();
	}
	query.exec("select * from test where kid='" + currentKid + "'");
	while (query.next()){
		currentTid = query.value(1).toString();
		QPalette pa;
		pa.setColor(QPalette::WindowText, Qt::red);
		ui.testHourLabel->setText(query.value(2).toString());
		ui.testHourLabel->setPalette(pa);
		ui.testMinuteLabel->setText(query.value(3).toString());
		ui.testMinuteLabel->setPalette(pa);
		ui.restHourLabel->setText(query.value(2).toString());
		ui.restHourLabel->setPalette(pa);
		ui.restMinuteLabel->setText(query.value(3).toString());
		ui.restMinuteLabel->setPalette(pa);	
		limitScore = query.value(4).toInt();
	}
	this->db.close();

	//提示用户开始测试
	initLabel = new QLabel(ui.scrollArea);
	initLabel->setText(QStringLiteral("请点击开始测试按钮开始测试！"));
	initLabel->setGeometry(150, 100, 390, 50);
	QFont ft;
	ft.setPointSize(20);
	ft.setFamily(QStringLiteral("楷体"));
	initLabel->setFont(ft);
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::red);
	initLabel->setPalette(pa);
	startButton = new QPushButton(ui.scrollArea);
	startButton->setGeometry(280, 180, 110, 30);
	startButton->setText(QStringLiteral("开始测试"));
	ft.setPointSize(12);
	startButton->setFont(ft);
	connect(startButton, SIGNAL(clicked()), this, SLOT(startTestSlot()));//点击开始测试按钮进入测试
}

void test::openDatabase(){
	this->db = QSqlDatabase::addDatabase("QMYSQL");
	this->db.setHostName("localhost");
	this->db.setUserName("root");
	this->db.setPassword("1234");
	this->db.setDatabaseName("knowledge");
	bool ok = this->db.open();
	if (!ok){
		qDebug() << "Failed to connect database login!";
	}
	else{
		qDebug() << "Success!";
	}
}

//显示系统时间
void test::timeUpdateSlot(){
	QDateTime time = QDateTime::currentDateTime();
	ui.currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
}

//更新当前测试剩余时间
void test::restTimeUpdateSlot(){
	int alreadyHour = QDateTime::currentDateTime().time().hour() - startTestTime.time().hour();
	int alreadyMinute = QDateTime::currentDateTime().time().minute() - startTestTime.time().minute();
	if (alreadyMinute < 0){
		alreadyMinute += 60;
		alreadyHour -= 1;
	}
	int restHour = ui.testHourLabel->text().toInt() - alreadyHour;
	int restMinute = ui.testMinuteLabel->text().toInt() - alreadyMinute;
	ui.restHourLabel->setText(QString::number(restHour));
	ui.restMinuteLabel->setText(QString::number(restMinute));
}

//动态显示测试界面
void test::startTestSlot(){
	if (initLabel != NULL){
		delete initLabel;
	}
	if (startButton != NULL){
		delete startButton;
	}
	QTimer *timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(restTimeUpdateSlot()));
	timer->start(1000);
	startTestTime = QDateTime::currentDateTime();
	QDateTime start = QDateTime::currentDateTime();
	ui.submitButton->setDisabled(false);
	//ui.scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	//ui.scrollArea->setWidgetResizable(true);
	allLayout = new QVBoxLayout;
	firstLayout = new QHBoxLayout;
	firstTitleLabel = new QLabel;
	firstTitleLabel->setText(QStringLiteral("一、单项选择题"));
	firstLayout->addWidget(firstTitleLabel);
	firstLayout->addStretch();
	//ui.scrollArea->setLayout(firstLayout);
	allLayout->addLayout(firstLayout);
	openDatabase();
	int numRows;//记录查询的行数
	QSqlQuery query;
	query.exec("select * from testcase where tid='" + currentTid + "'");
	QSqlDatabase defaultDB = QSqlDatabase::database();
	if (defaultDB.driver()->hasFeature(QSqlDriver::QuerySize)) {
		numRows = query.size();
	}
	else{
		// this can be very slow
		query.last();
		numRows = query.at() + 1;
	}
	while (query.next()){
		int questionId = query.value(1).toInt();
		QHBoxLayout *contentLayout = new QHBoxLayout;
		hlayout_vec.push_back(contentLayout);
		QString _question = query.value(1).toString() + "." + query.value(2).toString();
		QLabel *questionLabel = new QLabel;
		label_vec.push_back(questionLabel);
		questionLabel->setText(_question);
		questionLabel->setStyleSheet("QLabel{background:yellow}");
		contentLayout->addWidget(questionLabel);
		contentLayout->addStretch();
		
		QHBoxLayout *aLayout = new QHBoxLayout;
		hlayout_vec.push_back(aLayout);
		QRadioButton *aRadioButton = new QRadioButton;
		radiobutton_vec.push_back(aRadioButton);
		aRadioButton->setText(query.value(4).toString());
		aLayout->addWidget(aRadioButton);
		aLayout->addStretch();

		QHBoxLayout *bLayout = new QHBoxLayout;
		hlayout_vec.push_back(bLayout);
		QRadioButton *bRadioButton = new QRadioButton;
		radiobutton_vec.push_back(bRadioButton);
		bRadioButton->setText(query.value(5).toString());
		bLayout->addWidget(bRadioButton);
		bLayout->addStretch();

		QHBoxLayout *cLayout = new QHBoxLayout;
		hlayout_vec.push_back(cLayout);
		QRadioButton *cRadioButton = new QRadioButton;
		radiobutton_vec.push_back(cRadioButton);
		cRadioButton->setText(query.value(6).toString());
		cLayout->addWidget(cRadioButton);
		cLayout->addStretch();

		QHBoxLayout *dLayout = new QHBoxLayout;
		hlayout_vec.push_back(dLayout);
		QRadioButton *dRadioButton = new QRadioButton;
		radiobutton_vec.push_back(dRadioButton);
		dRadioButton->setText(query.value(7).toString());
		dLayout->addWidget(dRadioButton);
		dLayout->addStretch();

		QButtonGroup *choiceGroup = new QButtonGroup;
		buttongroup_vec.push_back(choiceGroup);
		choiceGroup->addButton(aRadioButton);
		choiceGroup->addButton(bRadioButton);
		choiceGroup->addButton(cRadioButton);
		choiceGroup->addButton(dRadioButton);
		choiceGroup->setId(aRadioButton, 1);
		choiceGroup->setId(bRadioButton, 2);
		choiceGroup->setId(cRadioButton, 3);
		choiceGroup->setId(dRadioButton, 4);
		test_map.insert(make_pair(questionId, choiceGroup));
		//question_vec.push_back(choiceGroup);
		allLayout->addLayout(contentLayout);
		allLayout->addLayout(aLayout);
		allLayout->addLayout(bLayout);
		allLayout->addLayout(cLayout);
		allLayout->addLayout(dLayout);
	}
	allLayout->addSpacing(5000);
	ui.scrollArea->setLayout(allLayout);	
}


//提交测试结果
void test::submitTestSlot(){
	QMessageBox msgBox;
	msgBox.setText(QStringLiteral("提示"));
	msgBox.setInformativeText(QStringLiteral("您确定要提交试卷吗？"));
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int ret = msgBox.exec();
	switch (ret)
	{
	case QMessageBox::Ok:
		break;
	case QMessageBox::Cancel:
		return;
	}
	int score = 0;
	map<int, QButtonGroup*>::const_iterator it = test_map.begin();
	openDatabase();
	while (it != test_map.end()){
		int i = (it->second)->checkedId();
		QString _answer;
		switch (i)
		{
		case 1:
			_answer = "A";
			break;
		case 2:
			_answer = "B";                                
			break;
		case 3:
			_answer = "C";
			break;
		case 4:
			_answer = "D";
			break;
		}
		
		QSqlQuery query;
		query.prepare("select answer,score from testcase where tid=:tid and qid=:qid");
		query.bindValue(":tid", currentTid);
		query.bindValue(":qid", it->first);
		query.exec();
		while (query.next()){
			if (query.value(0).toString() == _answer){
				score += query.value(1).toInt();
			}
		}		
		++it;
	}
	QSqlQuery query;
	//在测试结果表中插入用户测试记录
	query.prepare("insert into testresult(sid,kid,tid,score) values(:sid,:kid,:tid,:score)");
	query.bindValue(":sid", myUser.getSid());
	query.bindValue(":kid", currentKid);
	query.bindValue(":tid", currentTid);
	query.bindValue(":score", score);
	query.exec();
	//更新学习行为记录表中当前用户的最后一条学习记录，修改通过情况
	QString beginTime;
	query.prepare("select begin from behavior where sid=:sid and kid=:kid");
	query.bindValue(":sid", myUser.getSid());
	query.bindValue(":kid", currentKid);
	query.exec();
	while (query.next()){
		query.last();
		 beginTime = query.value(0).toString();
		qDebug() << score;
	}
	if (score >= limitScore){
		pass = true;
		//更新学习行为记录表中当前用户的最后一条学习记录，修改通过情况
		query.prepare("update behavior set pass=1 where sid=:sid and kid=:kid and begin=:begin");
		query.bindValue(":sid", myUser.getSid());
		query.bindValue(":kid", currentKid);
		query.bindValue(":begin", beginTime);
		query.exec();
		//更新推荐路径表
		query.prepare("update recpath set state=1 where sid=:sid and kid=:kid");
		query.bindValue(":sid", myUser.getSid());
		query.bindValue(":kid", currentKid);
		query.exec();
		
	}
	else{
		pass = false;
		//更新学习行为记录表中当前用户的最后一条学习记录，修改通过情况
		query.prepare("update behavior set pass=0 where sid=:sid and kid=:kid and begin=:begin");
		query.bindValue(":sid", myUser.getSid());
		query.bindValue(":kid", currentKid);
		query.bindValue(":begin", beginTime);
		query.exec();
		if (_first == "P"){
			//更新推荐路径表
			query.prepare("update recpath set state=1 where sid=:sid and kid=:kid");
			query.bindValue(":sid", myUser.getSid());
			query.bindValue(":kid", currentKid);
			query.exec();
		}
		
	}
	//更新学习路径记录表
	query.prepare("insert into path(sid,domain,kid,begintime,score) values(:sid,:domain,:kid,:begintime,:score)");
	query.bindValue(":sid", myUser.getSid());
	query.bindValue(":domain", currentDomain);
	query.bindValue(":kid", currentKid);
	query.bindValue(":begintime", beginTime);
	query.bindValue(":score", score);
	query.exec();
	

	this->db.close();
	QMessageBox::information(this, QStringLiteral("恭喜"), QStringLiteral("您已经提交成功！"));
	if (firstLayout != NULL && firstTitleLabel != NULL){
		delete firstLayout;
		firstLayout = NULL;
		delete firstTitleLabel;
		firstTitleLabel = NULL;
	}
	for (vector<QHBoxLayout*>::iterator it = hlayout_vec.begin(); 
		it != hlayout_vec.end(); ++it){
		if ((*it) != NULL){
			delete *it;
			(*it) = NULL;
		}
	}
	for (vector<QLabel*>::iterator it = label_vec.begin();
		it != label_vec.end(); ++it){
		if ((*it) != NULL){
			delete *it;
			(*it) = NULL;
		}
	}
	for (vector<QRadioButton*>::iterator it = radiobutton_vec.begin();
		it != radiobutton_vec.end(); ++it){
		if ((*it) != NULL){
			delete *it;
			(*it) = NULL;
		}
	}
	for (vector<QButtonGroup*>::iterator it = buttongroup_vec.begin();
		it != buttongroup_vec.end(); ++it){
		if ((*it) != NULL){
			delete *it;
			(*it) = NULL;
		}
	}
	if (allLayout != NULL){
		delete allLayout;
		allLayout = NULL;
	}
	allLayout = new QVBoxLayout;	
	QWidget *w = new QWidget;
	QLabel *endLabel = new QLabel(w);
	if (pass){//如果通过测试
		endLabel->setText(QStringLiteral("本次考试已经结束，您的分数为： ") + QString::number(score) + QStringLiteral(" ,恭喜您已通过测试，您要继续学习吗？"));
		QPushButton *nextButton = new QPushButton(w);
		nextButton->setText(QStringLiteral("下一知识点"));
		nextButton->setGeometry(280, 180, 110, 30);
		connect(nextButton, SIGNAL(clicked()), this, SLOT(nextKnowledgeSlot()));
	}
	else{//没有通过测试
		endLabel->setText(QStringLiteral("本次考试已经结束，您的分数为： ") + QString::number(score) + QStringLiteral(" ,您没有通过测试，请重新学习"));
		QPushButton *againButton = new QPushButton(w);
		againButton->setText(QStringLiteral("返回教学模块"));
		againButton->setGeometry(280, 180, 110, 30);
		if (_first == "B"){
			connect(againButton, SIGNAL(clicked()), this, SLOT(againKnowledgeSlot()));
		}
		else{
			connect(againButton, SIGNAL(clicked()), this, SLOT(nextKnowledgeSlot()));
		}
		
		
		
	}
	endLabel->setGeometry(100, 100, 500, 50);	
	allLayout->addWidget(w);
	ui.scrollArea->setLayout(allLayout);
}

//下一个知识节点
void test::nextKnowledgeSlot(){
	beforeKid = currentKid;
	openDatabase();
	QSqlQuery query;
	query.prepare("select kid from recpath where sid=:sid and state=0 order by orders");
	query.bindValue(":sid", myUser.getSid());
	query.exec();
	while (query.next()){
		currentKid = query.value(0).toString();
		qDebug() << currentKid;
		break;
	}
	if (_first=="P"){
		query.prepare("update recpath set state=0 where sid=:sid and kid=:kid");
		query.bindValue(":sid", myUser.getSid());
		query.bindValue(":kid", beforeKid);
		query.exec();
	}
	/*query.exec("select cid from teach where kid='"+currentKid+"'");
	while (query.next()){
		currentCid = query.value(0).toString();
		break;
	}*/
	/*query.prepare("insert into behavior(sid,kid) values(:sid,:kid,:cid,:begin)");
	query.bindValue(":sid", myUser.getSid());
	query.bindValue(":kid", currentKid);
	query.bindValue(":cid", currentCid);
	query.bindValue(":begin", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
	query.exec();*/
	this->db.close();
	
	this->close();
}

//重新学习当前知识点
void test::againKnowledgeSlot(){
	this->close();
}
