#include <QDomDocument>

#include "helper/attribution.h"
#include "ui_attribution.h"
#include "helper/myheaders.h"

extern QString attribute;

Attribution::Attribution(QWidget *parent)
    : QWidget(parent), ui(new Ui::Attribution)
{
    ui->setupUi(this);
    initUI();
    init();

    connect(ui->buttonClose, &QPushButton::clicked, this, &Attribution::close);                                 // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &Attribution::showMinimized);                           // 点击最小化
}

Attribution::~Attribution()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

void Attribution::initUI()
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

    ui->tabWidget->setTabText(0, tr("属性信息"));
    ui->tabWidget->setTabText(1, tr("特征信息"));
    ui->houLineEdit->setText(tr("无"));
    ui->tipsLabel->setText(tr("无"));
}

//初始化属性界面
void Attribution::init()
{
    openDatabase();
    QSqlQuery query;
    QString sqlStr = "select * from pk where title='";
    sqlStr += attribute;
    sqlStr += "'";
    query.exec(sqlStr);
    while (query.next())
    {
        ui->idLineEdit->setText(query.value(0).toString());
        ui->titleLineEdit->setText(attribute);
        ui->domainLineEdit->setText(query.value(2).toString());
        ui->textEdit->setText(tr("数据的简单堆叠形成堆叠模式"));
        QString _patternFile = query.value(3).toString();
        _patternFile.replace(0, 1, "../PatternKnowledgeEducationSystem");
        qcout << _patternFile;

        openXml(_patternFile);
    }
    query.exec("select pors,kids from about join pk on about.kid=pk.pid where pk.title='" + attribute + "'");
    while (query.next())
    {
        if (query.value(0).toString() == "0")
        {
            ui->qianLineEdit->setText(query.value(1).toString());
        }
        else
        {
            ui->houLineEdit->setText(query.value(1).toString());
        }
    }
}

//打开数据库
void Attribution::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", "attribution");
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

//读模式知识的特征xml文档
void Attribution::openXml(QString filename)
{
    QDomDocument doc;
    QFile xmlFile(filename);
    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        qcout << "Failed to open xml file!";
    }
    if (!doc.setContent(&xmlFile))
    {
        xmlFile.close();
        qcout << "Failed!";
    }
    xmlFile.close();
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        QDomElement e = node.toElement();
        if (!e.isNull())
        {
            if (e.tagName() == "pname")
            {
                ui->patternLabel->setText(e.text());

            }
            else if (e.tagName() == "pproblem")
            {
                ui->problemLabel->setText(e.text());

            }
            else if (e.tagName() == "psolution")
            {
                ui->solutionLabel->setText(e.text());

            }
            else if (e.tagName() == "pcharacteries")
            {
                QDomNode cnode = e.firstChild();
                QDomElement ce = cnode.toElement();
                if (!ce.isNull())
                {
                    ui->feature1Label->setText(ce.text());

                }
                cnode = cnode.nextSibling();
                ce = cnode.toElement();
                if (!ce.isNull())
                {
                    ui->feature2Label->setText(ce.text());

                }
                cnode = cnode.nextSibling();
                ce = cnode.toElement();
                if (!ce.isNull())
                {
                    ui->feature3Label->setText(ce.text());

                }
            }
            else if (e.tagName() == "preference")
            {
                QString str = "";
                QDomNode pnode = e.firstChild();
                while (!pnode.isNull())
                {
                    QDomElement pe = pnode.toElement();
                    if (!pe.isNull())
                    {
                        str += pe.text();

                    }
                    pnode = pnode.nextSibling();
                }
                ui->exampleLabel->setText(str);
            }
        }
        node = node.nextSibling();
    }

}
