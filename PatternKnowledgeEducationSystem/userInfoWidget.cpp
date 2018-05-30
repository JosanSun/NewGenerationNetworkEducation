#include "stable.h"
#include <QTableView>
#include <QMessageBox>

#include "userinfowidget.h"
#include "ui_userinfowidget.h"
#include "helper/user.h"

extern User myUser; //全局用户变量

UserInfoWidget::UserInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::UserInfoWidget),
      timer(new QTimer(this))
{
    ui->setupUi(this);
    initUI();
    init();

    connect(ui->buttonClose, &QPushButton::clicked, this, &UserInfoWidget::close);                                // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &UserInfoWidget::showMinimized);                          // 点击最小化
    connect(timer, &QTimer::timeout, this, &UserInfoWidget::updateTimeSlot);                                      // 更新系统时间
    connect(ui->modifyButton, &QPushButton::clicked, this, &UserInfoWidget::modifyInformationSlot);               // 修改个人信息
    connect(ui->saveButton, &QPushButton::clicked, this, &UserInfoWidget::saveInformationSlot);                   // 保存个人信息
    connect(ui->quitButton, &QPushButton::clicked, this, &UserInfoWidget::close);                                 // 关闭用户管理
}

UserInfoWidget::~UserInfoWidget()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

//打开数据库
void UserInfoWidget::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", tr("userInfo"));
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

void UserInfoWidget::initUI()
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


    ui->modifyButton->setEnabled(true);
    ui->saveButton->setEnabled(false);
    ui->quitButton->setEnabled(true);
    ui->usernameLineEdit->setEnabled(false);
    ui->passwordLineEdit->setEnabled(false);
    ui->ageLineEdit->setEnabled(false);
    ui->sexComboBox->setDisabled(true);
    ui->educationComboBox->setDisabled(true);

    ui->currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));

    //初始化各个显示标签的信息以及标签属性
    ui->usernameLabel->setText(QString::fromStdString(myUser.getName()));
    ui->usernameLineEdit->setText(QString::fromStdString(myUser.getName()));
    ui->usernameLineEdit->setReadOnly(true);
    ui->passwordLineEdit->setText(QString::fromStdString(myUser.getPassword()));
    ui->passwordLineEdit->setReadOnly(true);
    ui->sexComboBox->setCurrentText(QString::fromStdString(myUser.getSex()));
    ui->sexComboBox->setDisabled(true);
    ui->ageLineEdit->setText(QString::number(myUser.getAge()));
    ui->ageLineEdit->setReadOnly(true);
    ui->educationComboBox->setCurrentText(QString::fromStdString(myUser.getEducation()));
    ui->educationComboBox->setDisabled(true);
}

//初始化用户管理界面
void UserInfoWidget::init()
{
    openDatabase();
    mMove=false;//mouse moving
    if (!havePathTab)
    {//如果当前没有用户路径记录表 则new一个
        pathWidget = new QWidget();
        pathTableView = new QTableView(pathWidget);
        pathTableView->setGeometry(8, 8, 521, 271);
        ui->tabWidget->addTab(pathWidget, tr("用户学习路径表"));
        havePathTab = true;
    }
    //显示用户学习路径表
    QSqlQueryModel *pathmodel = new QSqlQueryModel;
    QString sqlString = "select a.domain,b.title,a.begintime,a.score from path a join ";
    sqlString += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
    sqlString += "as b where a.kid=b.kid and a.sid=";
    sqlString += QString::number(myUser.getSid());
    sqlString += " order by a.begintime";
    pathmodel->setQuery(sqlString, db);
    pathmodel->setHeaderData(0, Qt::Horizontal, tr("领域"));
    pathmodel->setHeaderData(1, Qt::Horizontal, tr("知识名称"));
    pathmodel->setHeaderData(2, Qt::Horizontal, tr("开始学习时间"));
    pathmodel->setHeaderData(3, Qt::Horizontal, tr("得分"));
    pathTableView->setModel(pathmodel);
    pathTableView->horizontalHeader()->setStretchLastSection(true);
    pathTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pathTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    if (!haveBehaviorTab)
    {//如果当前没有用户学习记录表 则new一个
        behaviorWidget = new QWidget();
        behaviorTableView = new QTableView(behaviorWidget);
        behaviorTableView->setGeometry(8, 8, 521, 271);
        ui->tabWidget->addTab(behaviorWidget, tr("用户学习记录表"));
        haveBehaviorTab = 1;
    }
    //显示用户学习记录表
    QSqlQueryModel *behaviormodel = new QSqlQueryModel;
    QString sqlString2 = "select b.title,a.cid,a.begin,a.end,a.note from behavior a join ";
    sqlString2 += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
    sqlString2 += "as b where a.kid=b.kid and a.sid=";
    sqlString2 += QString::number(myUser.getSid());
    sqlString2 += " order by a.begin";
    behaviormodel->setQuery(sqlString2, db);
    behaviormodel->setHeaderData(0, Qt::Horizontal, tr("知识名称"));
    behaviormodel->setHeaderData(1, Qt::Horizontal, tr("教学案例"));
    behaviormodel->setHeaderData(2, Qt::Horizontal, tr("开始学习时间"));
    behaviormodel->setHeaderData(3, Qt::Horizontal, tr("结束学习时间"));
    behaviormodel->setHeaderData(4, Qt::Horizontal, tr("笔记记录"));
    behaviorTableView->setModel(behaviormodel);
    behaviorTableView->horizontalHeader()->setStretchLastSection(true);
    behaviorTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    behaviorTableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    timer->start(1000);
    havePathTab = false;
    haveBehaviorTab = false;
}

//重写鼠标函数实现窗口自由移动
void UserInfoWidget::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void UserInfoWidget::mouseMoveEvent(QMouseEvent *event)
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

void UserInfoWidget::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

//更新系统时间槽
void UserInfoWidget::updateTimeSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui->currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
}

//修改用户信息槽
void UserInfoWidget::modifyInformationSlot()
{
    ui->modifyButton->setEnabled(false);
    ui->saveButton->setEnabled(true);

    ui->usernameLineEdit->setEnabled(true);
    ui->usernameLineEdit->setReadOnly(false);
    ui->passwordLineEdit->setEnabled(true);
    ui->passwordLineEdit->setReadOnly(false);
    ui->ageLineEdit->setEnabled(true);
    ui->ageLineEdit->setReadOnly(false);
    ui->sexComboBox->setDisabled(false);
    ui->educationComboBox->setDisabled(false);
}

//保存用户信息槽
void UserInfoWidget::saveInformationSlot()
{
    //获取用户修改的信息，以便来更新myUser信息和数据库中的用户信息
    int _sid = myUser.getSid();
    QString _username = ui->usernameLineEdit->text();
    QString _password = ui->passwordLineEdit->text();
    QString _sex = ui->sexComboBox->currentText();
    int _age = ui->ageLineEdit->text().toInt();
    QString _education = ui->educationComboBox->currentText();

    //更新全局的myUser信息
    myUser.setName(_username.toStdString());
    myUser.setPassword(_password.toStdString());
    myUser.setAge(_age);
    myUser.setSex(_sex.toStdString());
    myUser.setEducation(_education.toStdString());

    //关掉用户信息的编辑状态
    ui->modifyButton->setEnabled(true);
    ui->saveButton->setEnabled(false);

    ui->usernameLineEdit->setEnabled(false);
    ui->passwordLineEdit->setEnabled(false);
    ui->ageLineEdit->setEnabled(false);
    ui->sexComboBox->setDisabled(true);
    ui->educationComboBox->setDisabled(true);


    //更新数据库中的用户信息
    QSqlQuery query(db);
    query.prepare("update student set name=:name,password=:password,sex=:sex,age=:age,education=:education where sid=:sid");
    query.bindValue(":name", _username);
    query.bindValue(":password", _password);
    query.bindValue(":sex", _sex);
    query.bindValue(":age", _age);
    query.bindValue(":education", _education);
    query.bindValue(":sid", _sid);
    query.exec();

    QMessageBox::information(this, tr("恭喜"), tr("您的信息已修改并保存成功！"));
}

void UserInfoWidget::on_learningTestButton_clicked()
{
    hide();
    testWidget = new LearningPatternTest;
    testWidget->show();
    connect(testWidget, &LearningPatternTest::closeSignal,
            [=]()
            {
                show();
            });
}
