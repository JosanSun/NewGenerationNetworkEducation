#include "knowledge.h"
#include <cmath>
#include <QDebug>
#include <vector>
#include <QMouseEvent>
#include "node.h"
#include "qstring.h"
#include <iostream>
#include "qsqlquery.h"
#include "qrect.h"
#include "qpainterpath.h"
#include "qpolygon.h"
#include "user.h"


using namespace std;
static double pi = 3.14159;
extern user myUser;
QString attribute;

knowledge::knowledge(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setMouseTracking(true);

    //追踪学习路径
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(trackLearning()));
    vector<QString> attributes = getAttributesFromDB();
    vector<vector<int>> successors = getSuccessors(attributes);
    vector<vector<int>> predecessors = getPredecessors(successors);
    int r = 10;
    generateNodes(attributes, successors, predecessors, r);
}

knowledge::~knowledge()
{

}

//打开数据库
void knowledge::openDatabase()
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

void knowledge::paintEvent(QPaintEvent *)
{
    //NOTE: 真正运行的是这个画图
    drawCircles(nodesInPic, Qt::blue);
    //显性知识层面
    drawPanel(new QPoint(200, 300), QStringLiteral("基本知识层面"), Qt::black);
    //隐性知识层面
    drawPanel(new QPoint(200, 120), QStringLiteral("模式知识层面"), Qt::red);
}

//画平面
void knowledge::drawPanel(QPoint *basePoint, QString label, QColor color)
{
    QPainter painter(this);
    painter.setPen(QPen(color, 1));
    // painter.setBrush(QBrush(Qt::white));

    int x = basePoint->x();
    int y = basePoint->y();

    //平行四边形的长度为600 高为260
    //上
    painter.drawLine(x, y - 100, x + 600, y - 100);
    //右
    painter.drawLine(x + 600, y - 100, x + 420, y + 160);
    //下
    painter.drawLine(x + 420, y + 160, x - 180, y + 160);
    //左
    painter.drawLine(x - 180, y + 160, x, y - 100);

    //标签   设置标签的位置大小，以及显示标签
    QLabel *pLabel = new QLabel(this);
    pLabel->setText(label);
    pLabel->setGeometry(x + 500, y - 80, 75, 15);
    pLabel->show();

}

////在两个圆之间连线
//void knowledge::drawLine(QPoint *startPoint, QPoint *endPoint, int r, bool isTracked)
//{
//	QPainter painter(this);
//	painter.setPen(QPen(Qt::black, 1));

//    //一些已知量
//	float x1 = startPoint->x();
//	float y1 = startPoint->y();
//	float x2 = endPoint->x();
//	float y2 = endPoint->y();
//	float distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
//    //画两个圆之间的连线
//    float xStart = x1 + (x2 - x1) * r / distance;
//	float yStart = y1 + (y2 - y1) * r / distance;
//    float xEnd = x2 - (x2 - x1) * r / distance;
//    //float xEnd = x1 + (x2 - x1) / distance * (distance - r);
//    float yEnd = y2 - (y2 - y1) * r / distance;
//    //float yEnd = y1 + (y2 - y1) / distance * (distance - r);
//    painter.drawLine(xEnd, yEnd, xStart, yStart);

//    //画两个圆之间的箭头
//    float l = 10.0;                 //箭头的长度  斜边长
//	float a = 0.5;                  //箭头与线段角度
//    float x3 = xEnd + l * cos(atan2((yEnd - yStart), (xEnd - xStart)) - a);

//	float y3 = yEnd - l * sin(atan2((yEnd - yStart), (xEnd - xStart)) - a);

//    float x4 = xEnd + l * sin(atan2((xEnd - xStart), (yEnd - yStart)) - a);

//	float y4 = yEnd - l * cos(atan2((xEnd - xStart), (yEnd - yStart)) - a);

//	painter.drawLine(xEnd, yEnd, x3, y3);

//	painter.drawLine(xEnd, yEnd, x4, y4);


//}

//根据节点在图上画圆
void knowledge::drawCircles(vector<Node> nodes, QColor color)
{
    QPainter painter(this);
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].getIsLearned())
        {
            painter.setPen(QPen(color, 1));
            painter.setBrush(QBrush(color, Qt::SolidPattern));
        }
        else if (!nodes[i].getIsModelKnowledge())
        {
            painter.setPen(QPen(Qt::black, 1));
            painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        }
        else
        {
            painter.setPen(QPen(Qt::red, 1));
            painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        }
        //画圆
        int r = nodes[i].getRadius();
        painter.drawEllipse(nodes[i].getCenter().x() - r, nodes[i].getCenter().y() - r, r * 2, r * 2);
        //画圆弧
        if (!nodes[i].getIsModelKnowledge())
        {
            if (nodes[i].getParents().size() >= 2)
            {
                painter.setPen(QPen(Qt::black, 1));
                painter.setBrush(QBrush(Qt::NoBrush));
                QRectF oval = QRectF();
                oval.setLeft(nodes[i].getCenter().x() - 2 * r);
                oval.setTop(nodes[i].getCenter().y() - 2 * r);
                oval.setRight(nodes[i].getCenter().x() + 2 * r);
                oval.setBottom(nodes[i].getCenter().y() + 2 * r);
                int x = nodes[i].getCenter().x();
                int y = nodes[i].getCenter().y();
                //20170828改动  指针不能指向临时变量；
                QPoint startParentNode = nodes[nodes[i].getParents()[0]].getCenter();
                QPoint *startParent = &startParentNode;
                QPoint endParentNode = nodes[nodes[i].getParents()[1]].getCenter();
                QPoint *endParent = &endParentNode;

                double startAngle = asin((startParent->y() - y) / sqrt(pow(startParent->x() - x, 2) + pow(startParent->y() - y, 2))) * 180 / pi * 16;
                double endAngle = asin((endParent->y() - y) / sqrt(pow(endParent->x() - x, 2) + pow(endParent->y() - y, 2))) * 180 / pi * 16;

                painter.drawArc(oval, (int)startAngle + 180 * 16, (int)abs(startAngle - endAngle));
            }
        }
        //创建label
        QLabel *pLabel = new QLabel(this);
        pLabel->setText(nodes[i].getAttribute());
        pLabel->setGeometry(nodes[i].getCenter().x() - 25, nodes[i].getCenter().y() - 25, 75, 15);
        pLabel->show();

        QPoint *endPoint = new QPoint(nodes[i].getCenter().x(), nodes[i].getCenter().y());
        vector<int> children = nodes[i].getChildren();

        QPoint *startPoint;

        painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        for (int j = 0; j < children.size(); j++)
        {
            //---------画线
            if (nodes[i].getIsLearned() && nodesInPic[children[j]].getIsLearned())
            {
                painter.setPen(QPen(color, 2));
            }
            else
            {
                painter.setPen(QPen(Qt::black, 1));
            }
            startPoint = new QPoint(nodesInPic[children[j]].getCenter().x(), nodesInPic[children[j]].getCenter().y());
            //一些已知量
            float x1 = startPoint->x();
            float y1 = startPoint->y();
            float x2 = endPoint->x();
            float y2 = endPoint->y();
            float distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
            //画两个圆之间的连线
            float xStart = x1 + (x2 - x1) * r / distance;
            float yStart = y1 + (y2 - y1) * r / distance;
            float xEnd = x2 - (x2 - x1) * r / distance;   //为什么这个不行
            //float xEnd = x1 + (x2 - x1) / distance * (distance - r);
            float yEnd = y2 - (y2 - y1) * r / distance;
            //float yEnd = y1 + (y2 - y1) / distance * (distance - r);
            painter.drawLine(xEnd, yEnd, xStart, yStart);
            //painter.drawLine(xStart, yStart, xEnd, yEnd);

            //画箭头
            float l = 10.0;                 //箭头的那长度
            float a = 0.3;                  //箭头与线段角度
            float x3 = xEnd - l * cos(atan2((yEnd - yStart), (xEnd - xStart)) - a);
            float y3 = yEnd - l * sin(atan2((yEnd - yStart), (xEnd - xStart)) - a);
            float x4 = xEnd - l * sin(atan2((xEnd - xStart), (yEnd - yStart)) - a);
            float y4 = yEnd - l * cos(atan2((xEnd - xStart), (yEnd - yStart)) - a);
            //painter.drawLine(xStart, yStart, xEnd, yEnd);
            QPoint triangle[3] = { QPoint(xEnd, yEnd), QPoint(x3, y3), QPoint(x4, y4) };
            painter.drawPolygon(triangle, 3);  //画成三角形的箭头
        }
    }
}


void knowledge::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint point = QPoint(event->x(), event->y());
        attribute = getAttributeByPosition(point);

        openDatabase();
        QSqlQuery query;
        QString sqlStr = "select a.domain,a.begintime,a.score from path a join ";
        sqlStr += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
        sqlStr += "as b on a.kid=b.kid where a.sid=";
        sqlStr += QString::number(myUser.getSid());
        sqlStr += " and b.title='";
        sqlStr += attribute;
        sqlStr += "'";
        query.exec(sqlStr);
        while (query.next())
        {
            ui.pointNameLabel->setText(attribute);
            qDebug() << query.value(1).toString();
            QDateTime _dt = query.value(1).toDateTime();
            ui.begintimeLabel->setText(_dt.toString("yyyy-MM-dd \nhh:mm:ss "));
            ui.domainLabel->setText(query.value(0).toString());
            ui.scoreLabel->setText(query.value(2).toString());
        }
        attrWindow = new attribution();
        attrWindow->setWindowTitle(QStringLiteral("知识属性"));
        attrWindow->setWindowModality(Qt::ApplicationModal);
        attrWindow->show();
        attrWindow->setAttribute(Qt::WA_DeleteOnClose);
        this->db.close();
    }
}

//移动鼠标就能显示属性
//BUG:最好能够等待几秒，否则效果不行
void knowledge::mouseMoveEvent(QMouseEvent * /* event */)
{
    QPoint point = cursor().pos();
    QString attribute = getAttributeByPosition(point);
    //ui.label->setText(attribute);
}

//根据鼠标点击坐标获取当前节点属性值
QString knowledge::getAttributeByPosition(QPoint point)
{
    if (nodesInPic.size() == 0)
    {
        return "null";
    }
    else
    {
        int x = point.x();
        int y = point.y();
        vector<Node>::iterator iter;
        for (iter = nodesInPic.begin(); iter != nodesInPic.end(); iter++)
        {
            QPoint center = (*iter).getCenter();
            if (sqrt(pow(center.x() - x, 2) + pow(center.y() - y, 2)) <= (*iter).getRadius())
            {
                return (*iter).getAttribute();
            }
        }
        return "null";
    }
}

//从数据库中获得属性值
vector<QString> knowledge::getAttributesFromDB()
{
    vector<QString> attributes;
    openDatabase();
    QSqlQuery query;
    query.exec("select title from bk union select title from pk");
    while(query.next())
    {

        attributes.push_back(query.value(0).toString());
    }
    this->db.close();
    return attributes;
}

//从数据库中获得后继节点关系
vector<vector<int>> knowledge::getSuccessors(vector<QString> &attributes)
{
    vector<vector<int>> successors = vector<vector<int>>(attributes.size());
    openDatabase();
    QSqlQuery query;
    query.exec("select kids from about where pors=1");
    int inx=0;
    while(query.next())
    {
        int num = 0;
        QString _kids=query.value(0).toString();
        QString _sep=",";
        int pos=_kids.indexOf(_sep);
        QString _ktype;
        while(pos!=-1)
        {
            QString _kid=_kids.left(pos);
            _ktype = _kid.left(1);
            if (_ktype == "B")
            {
                _kid = _kid.remove(0, 1);
                num = _kid.toInt() - 1;
            }
            else if(_ktype == "P")
            {
                _kid = _kid.remove(0, 1);
                num = _kid.toInt() + 12;
            }
            successors[inx].push_back(num);
            _kids=_kids.remove(0,pos+1);

            pos=_kids.indexOf(_sep);
        }
        _ktype = _kids.left(1);
        if (_ktype == "B")
        {
            _kids = _kids.remove(0, 1);
            num = _kids.toInt() - 1;
        }
        else if (_ktype == "P")
        {
            _kids = _kids.remove(0, 1);
            num = _kids.toInt() + 12;
        }
        successors[inx].push_back(num);
        ++inx;
    }
    this->db.close();
    return successors;
}

//从数据库中获得前驱节点关系
vector<vector<int>> knowledge::getPredecessors(vector<vector<int>> &successors)
{
    vector<vector<int>> predecessors = vector<vector<int>>(successors.size());
    for (int i = 0; i < successors.size(); i++)
    {
        for (int j = 0; j < successors[i].size(); j++)
        {
            predecessors[successors[i][j]].push_back(i);
        }
    }

    return predecessors;
}

//根据数据库中节点信息生成节点
void knowledge::generateNodes(vector<QString> attributes, vector<vector<int>> successors,
                              vector<vector<int>> predecessors, int r)
{
    for (int i = 0; i < attributes.size(); i++)
    {
        Node node;
        node.setAttribute(attributes[i]);
        node.setRadius(r);
        if (attributes[i].indexOf(QStringLiteral("模式")) >= 0)
        {
            node.setIsModelKnowledge(true);
        }
        nodesInPic.push_back(node);
        nodesAttributesMap.insert(map<QString, int>::value_type(attributes[i], i));
    }

    for (int i = 0; i < successors.size(); i++)
    {
        for (int j = 0; j < successors[i].size(); j++)
        {
            nodesInPic[i].addChild(successors[i][j]);
        }
    }

    for (int i = 0; i < predecessors.size(); i++)
    {
        for (int j = 0; j < predecessors[i].size(); j++)
        {
            nodesInPic[i].addParent(predecessors[i][j]);
        }
    }

    //设置所有结点的坐标
    setNodesCoordinate(QPoint(200, 300));
}

//设置节点坐标
void knowledge::setNodesCoordinate(QPoint basePoint)
{
    int x = basePoint.x();
    int y = basePoint.y();
    nodesInPic[0].setCenter(QPoint(x, y));  //常量
    nodesInPic[1].setCenter(QPoint(x, y + 70));  //变量
    nodesInPic[2].setCenter(QPoint(x + 40, y - 60)); //枚举
    nodesInPic[3].setCenter(QPoint(x + 70, y)); //结构体
    nodesInPic[4].setCenter(QPoint(x + 90, y + 40)); //数组
    nodesInPic[5].setCenter(QPoint(x + 120, y + 70)); //指针
    nodesInPic[6].setCenter(QPoint(x + 90, y + 140)); //引用
    nodesInPic[7].setCenter(QPoint(x + 180, y)); //结构体数组
    nodesInPic[8].setCenter(QPoint(x + 200, y + 70)); //数组指针
    nodesInPic[9].setCenter(QPoint(x + 200, y + 140)); //变量引用
    nodesInPic[10].setCenter(QPoint(x + 300, y)); //指针数组
    nodesInPic[11].setCenter(QPoint(x + 300, y + 50)); //多维数组
    nodesInPic[12].setCenter(QPoint(x + 350, y + 70)); //常引用
    nodesInPic[13].setCenter(QPoint(x + 100, y - 180)); //堆叠模式
    nodesInPic[14].setCenter(QPoint(x + 180, y - 200)); //指向模式
    nodesInPic[15].setCenter(QPoint(x + 300, y - 180)); //绑定模式
}

//获取用户学习轨迹
void knowledge::getLearningTrack(vector<QString> &lt)
{
    qDebug() << "getlearningtrack!";
    //vector<QString> learningTrack;
    openDatabase();
    QSqlQuery query;
    QString sqlStr = "select b.title from path a join ";
    sqlStr += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
    sqlStr += "as b where a.kid=b.kid and a.sid=";
    sqlStr += QString::number(myUser.getSid());
    sqlStr += " order by a.begintime";
    query.exec(sqlStr);
    while (query.next())
    {
        qDebug() << query.value(0).toString();
        lt.push_back(query.value(0).toString());
    }
    this->db.close();
}


//slots
void knowledge::trackLearning()
{
    getLearningTrack(learningTrack);
    qDebug() << "tracklearning!";
    //初始化
    for (int i = 0; i < static_cast<int>(nodesInPic.size()); i++)
    {
        nodesInPic[i].setIsLearned(false);
    }
    for (int i = 0; i < static_cast<int>(learningTrack.size()); i++)
    {
        int nodeID = nodesAttributesMap[learningTrack[i]];
        nodesInPic[nodeID].setIsLearned(true);
    }
    repaint();
    update();
}
