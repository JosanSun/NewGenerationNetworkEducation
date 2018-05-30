#include "stable.h"
#include <QFile>
#include <QUrl>
#include <QTimer>
#include <QDateTime>
#include <QTextCodec>
#include <QWidget>
#include <QtGui>
#include <QMessageBox>
#include <ActiveQt\qaxwidget.h>

#include "usecase.h"
#include "ui_usecase.h"
#include "helper/user.h"
#include "helper/myheaders.h"

extern QString currentKid;
extern QString currentCid;
extern User myUser;
QString note;

Usecase::Usecase(QWidget *parent)
    : QWidget(parent), ui(new Ui::Usecase), timer(new QTimer(this))
{
    ui->setupUi(this);
    initUI();
    init();

    connect(ui->buttonClose, &QPushButton::clicked, this, &Usecase::close);                                 // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &Usecase::showMinimized);                           // 点击最小化
    connect(timer, &QTimer::timeout, this, &Usecase::updateTimeSlot);                   // 更新系统时间
    connect(ui->testButton, &QPushButton::clicked, this, &Usecase::goToTestWindowSlot);  // 进入测试模块
}

Usecase::~Usecase()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void Usecase::openDatabase()
{

    this->db = QSqlDatabase::addDatabase("QMYSQL", "usecase");
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

void Usecase::initUI()
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



    ui->textBrowser->setWordWrapMode(QTextOption::WrapAnywhere);
    ui->textEdit->setReadOnly(false);
    ui->textEdit->setText(tr("开始测试"));
    ui->currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd \nhh:mm:ss dddd"));
    ui->usernameLabel->setText(QString::fromStdString(myUser.getName()));
}

//初始化案例播放界面
void Usecase::init()
{
    openDatabase();

    QString casename = currentCid;
    QSqlQuery query(db);
    QString path;
    query.exec("select * from teach where kid='" + currentKid + "' and cid='" + currentCid + "'");
    while (query.next())
    {
        path = query.value(2).toString();
    }
    //BUG:这是一个坑点，这样取后缀，必须确保只能4个字节的文件名
    QString _form = casename.remove(0, 5);
    if (_form == "txt")
    {
        path.replace(0, 1, "../PatternKnowledgeEducationSystem");
        qcout << path;

        QFile inFile(path);
        // QIODevice::Text 会改变原来文件的换行方式，不推荐这种打开方式
        if(!inFile.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, tr("TextEditor"),
                                 tr("Cannot read file %1.\n%2.")
                                 .arg(inFile.fileName())
                                 .arg(inFile.errorString()));
            return ;
        }
        QApplication::setOverrideCursor(Qt::WaitCursor);
        const QByteArray data = inFile.readAll();
        QTextCodec::ConverterState state;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        const QString text = codec->toUnicode(data.constData(), data.size(), &state);

        if (state.invalidChars > 0)
        {
            // Not a UTF-8 text - using system default locale
            QTextCodec * codec1 = QTextCodec::codecForLocale();
            // qcout << codec1->name();
            if (!codec1)
                return ;
            // qcout << "invalidChars > 0";
            ui->textBrowser->setText(codec1->toUnicode(data));
        }
        else
        {
            qcout << "invalidChars = 0";
            ui->textBrowser->setText(text);
        }

        QApplication::restoreOverrideCursor();

    }
    else if (_form == "html")
    {
        path.replace(0, 1, "file:///E:/MyCode/qt/github/NewGenerationNetworkEducation/PatternKnowledgeEducationSystem");
        qcout << path;
        QUrl url(path);
        ui->textBrowser->setSource(url);
    }
    else if (_form == "swf")
    {
        //path.replace(19, 1, "\\");
        //NOTE:如何改为绝对路径呢？
        qcout << path;   //../knowledge/usecase/U008.swf输出是这个
        // 无法使用相对路径
        // path.replace(0, 1, "../PatternKnowledgeEducationSystem");
        path.replace(0, 1, "E:/MyCode/qt/github/NewGenerationNetworkEducation/PatternKnowledgeEducationSystem");
        qcout << path;

        //BUG:这个会不停的运行，然后占据着  使得不能触发按钮点击事件
        QAxWidget *flash = new QAxWidget(ui->textBrowser);       //QAxWidget使用的是ActiveX插件
        flash->resize(701,461);                                 //设置该控件的初始大小
        flash->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
        flash->dynamicCall("LoadMovie(long,string)", 0, path);
        flash->show();
        flash->setAttribute(Qt::WA_DeleteOnClose);
    }

    timer->start(1000);
}

void Usecase::updateTimeSlot()
{
    QDateTime time = QDateTime::currentDateTime();
    ui->currentTimeLabel->setText(time.toString("yyyy-MM-dd \nhh:mm:ss dddd"));
    note = ui->textEdit->toPlainText();
}

//进入测试模块
void Usecase::goToTestWindowSlot()
{
    qcout << "This can be run ";
}

void Usecase::on_testButton_clicked()
{
    note = ui->textEdit->toPlainText();

    QSqlQuery query(db);
    //首先记录上次学习的案例的结束时间以及通过情况
    query.prepare("update behavior set end=:end,pass=0,note=:note where sid=:sid and kid=:kid and cid=:cid");
    query.bindValue(":end", QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
    query.bindValue(":note", note);
    query.bindValue(":sid", myUser.getSid());
    query.bindValue(":kid", currentKid);
    query.bindValue(":cid", currentCid);
    query.exec();

    qcout << "This can be run    ";
    testWindow = new Test();
    testWindow->show();
    connect(testWindow, &Test::destroyed, this, &Usecase::close);

    this->close();
}
