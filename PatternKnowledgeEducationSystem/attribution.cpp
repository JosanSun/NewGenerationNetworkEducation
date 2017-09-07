#include "attribution.h"
#include <QDomDocument>

extern QString attribute;

attribution::attribution(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

attribution::~attribution()
{

}

//初始化属性界面
void attribution::init(){
	ui.tabWidget->setTabText(0, QStringLiteral("属性信息"));
	ui.tabWidget->setTabText(1, QStringLiteral("特征信息"));
	openDB();
	QSqlQuery query;
	QString sqlStr = "select * from pk where title='";
	sqlStr += attribute;
	sqlStr += "'";
	query.exec(sqlStr);
	while (query.next()){
		ui.idLineEdit->setText(query.value(0).toString());
		ui.titleLineEdit->setText(attribute);
		ui.domainLineEdit->setText(query.value(2).toString());
		ui.textEdit->setText(QStringLiteral("数据的简单堆叠形成堆叠模式"));
		QString _patternFile = query.value(3).toString();
		openXml(_patternFile);
	}
	query.exec("select pors,kids from about join pk on about.kid=pk.pid where pk.title='" + attribute + "'");
	while (query.next()){
		if (query.value(0).toString() == "0"){
			ui.qianLineEdit->setText(query.value(1).toString());
		}
		else{
			ui.houLineEdit->setText(query.value(1).toString());
		}
	}
	
	ui.houLineEdit->setText(QStringLiteral("无"));
	ui.tipsLabel->setText(QStringLiteral("无"));
	this->db.close();
}

//打开数据库
void attribution::openDB(){
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

//读模式知识的特征xml文档
void attribution::openXml(QString filename){
	QDomDocument doc;
	QFile xmlFile(filename);
	if (!xmlFile.open(QIODevice::ReadOnly)){
		qDebug() << "Failed to open xml file!";
	}
	if (!doc.setContent(&xmlFile)){
		xmlFile.close();
		qDebug() << "Failed!";
	}
	xmlFile.close();
	QDomElement root = doc.documentElement();
	QDomNode node = root.firstChild();
	while (!node.isNull()){
		QDomElement e = node.toElement();
		if (!e.isNull()){
			if (e.tagName() == "pname"){
				ui.patternLabel->setText(e.text());
				
			}
			else if (e.tagName() == "pproblem"){
				ui.problemLabel->setText(e.text());
				
			}
			else if (e.tagName() == "psolution"){
				ui.solutionLabel->setText(e.text());
				
			}
			else if (e.tagName() == "pcharacteries"){

				
				QDomNode cnode = e.firstChild();
				
					QDomElement ce = cnode.toElement();
					if (!ce.isNull()){
						ui.feature1Label->setText(ce.text());
						
					}
					cnode = cnode.nextSibling();
					ce = cnode.toElement();
					if (!ce.isNull()){
						ui.feature2Label->setText(ce.text());

					}
					cnode = cnode.nextSibling();
					ce = cnode.toElement();
					if (!ce.isNull()){
						ui.feature3Label->setText(ce.text());

					}
					
			}
			else if (e.tagName() == "preference"){
				QString str = "";
				QDomNode pnode = e.firstChild();
				while (!pnode.isNull()){
					QDomElement pe = pnode.toElement();
					if (!pe.isNull()){
						str += pe.text();
						
					}
					pnode = pnode.nextSibling();
				}
				ui.exampleLabel->setText(str);
			}
		}
		node = node.nextSibling();
	}

}