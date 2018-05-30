#include "stable.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <QDebug>
#include <QPolygon>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QPainterPath>
#include <QRect>

#include "knowledge.h"
#include "ui_knowledge.h"
#include "helper/node.h"
#include "helper/user.h"
#include "helper/myheaders.h"

using namespace std;
const double pi = 3.14159;
extern User myUser;
QString attribute;

Knowledge::Knowledge(QWidget *parent)
    : QWidget(parent), ui(new Ui::Knowledge)
{
    ui->setupUi(this);
    initUI();
    init();

    connect(ui->buttonClose, &QPushButton::clicked, this, &Knowledge::close);                                 // 点击关闭
    connect(ui->buttonMin, &QPushButton::clicked, this, &Knowledge::showMinimized);                           // 点击最小化
}

Knowledge::~Knowledge()
{
    delete ui;
    QString connectName = db.connectionName();
    db = QSqlDatabase();
    db.removeDatabase(connectName);
    db.close();
}

//打开数据库
void Knowledge::openDatabase()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL", "knowledge");
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

void Knowledge::initUI()
{
    setMouseTracking(true);
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
}

void Knowledge::init()
{
    openDatabase();
    mMove=false;//mouse moving
    //追踪学习路径
    connect(ui->pushButton, &QPushButton::clicked, this, &Knowledge::trackLearning);
    vector<QString> attributes = getAttributesFromDB();
    vector<vector<int>> successors = getSuccessors(attributes);
    vector<vector<int>> predecessors = getPredecessors(successors);
    int r = 10;
   // generateNodes(attributes, successors, predecessors, r);
}

//重写鼠标函数实现窗口自由移动
void Knowledge::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void Knowledge::mouseMoveEvent(QMouseEvent *event)
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

void Knowledge::mouseReleaseEvent(QMouseEvent* /* event */)
{
    mMove = false;
}
//mouse END

void Knowledge::paintEvent(QPaintEvent *)
{
    //NOTE: 真正运行的是这个画图
    drawCircles(nodesInPic, Qt::blue);
    //显性知识层面
    drawPanel(new QPoint(200, 300), tr("基本知识层面"), Qt::black);
    //隐性知识层面
    drawPanel(new QPoint(200, 120), tr("模式知识层面"), Qt::red);
}

//画平面
void Knowledge::drawPanel(QPoint *basePoint, QString label, QColor color)
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
//void Knowledge::drawLine(QPoint *startPoint, QPoint *endPoint, int r, bool isTracked)
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
void Knowledge::drawCircles(vector<Node> nodes, QColor color)
{
    QPainter painter(this);
    for (int i = 0; i < static_cast<int>(nodes.size()); i++)
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
        for (int j = 0; j < static_cast<int>(children.size()); j++)
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


void Knowledge::mousePressEventK(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint point = QPoint(event->x(), event->y());
        attribute = getAttributeByPosition(point);

        QSqlQuery query(db);
        QString sqlStr = "select a.domain,a.begintime,a.score from path a join ";
        sqlStr += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
        sqlStr += "as b on a.kid=b.kid where a.sid=";
        sqlStr += QString::number(myUser.getSid());
        sqlStr += " and b.title='";
        sqlStr += attribute;
        sqlStr += "'";
        if(query.exec(sqlStr))
        {
            qcout << "exec success";
            while (query.next())
            {
                qcout << "have the res";
                ui->pointNameLabel->setText(attribute);
                qcout << query.value(1).toString();
                QDateTime _dt = query.value(1).toDateTime();
                ui->begintimeLabel->setText(_dt.toString("yyyy-MM-dd \nhh:mm:ss "));
                ui->domainLabel->setText(query.value(0).toString());
                ui->scoreLabel->setText(query.value(2).toString());
            }
            qcout << "nothing";
            attrWindow = new Attribution();
            attrWindow->show();
        }
        else
        {
            QWidget::mousePressEvent(event);
        }

    }
}

//移动鼠标就能显示属性
//BUG:最好能够等待几秒，否则效果不行
void Knowledge::mouseMoveEventK(QMouseEvent * /* event */)
{
    QPoint point = cursor().pos();
    QString attribute = getAttributeByPosition(point);
    //ui->label->setText(attribute);
}

//根据鼠标点击坐标获取当前节点属性值
QString Knowledge::getAttributeByPosition(QPoint point)
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
vector<QString> Knowledge::getAttributesFromDB()
{
    vector<QString> attributes;
    QSqlQuery query(db);
    query.exec("select title from bk union select title from pk");
    while(query.next())
    {

        attributes.push_back(query.value(0).toString());
    }
    return attributes;
}

//从数据库中获得后继节点关系
vector<vector<int>> Knowledge::getSuccessors(vector<QString> &attributes)
{
    vector<vector<int>> successors = vector<vector<int>>(attributes.size());
    QSqlQuery query(db);
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
    return successors;
}

//从数据库中获得前驱节点关系
vector<vector<int>> Knowledge::getPredecessors(vector<vector<int>> &successors)
{
    vector<vector<int>> predecessors = vector<vector<int>>(successors.size());
    for (int i = 0; i < static_cast<int>(successors.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(successors[i].size()); j++)
        {
            predecessors[successors[i][j]].push_back(i);
        }
    }

    return predecessors;
}

//根据数据库中节点信息生成节点
void Knowledge::generateNodes(vector<QString> attributes, vector<vector<int>> successors,
                              vector<vector<int>> predecessors, int r)
{
    for (int i = 0; i < static_cast<int>(attributes.size()); i++)
    {
        Node node;
        node.setAttribute(attributes[i]);
        node.setRadius(r);
        if (attributes[i].indexOf(tr("模式")) >= 0)
        {
            node.setIsModelKnowledge(true);
        }
        nodesInPic.push_back(node);
        nodesAttributesMap.insert(map<QString, int>::value_type(attributes[i], i));
    }

    for (int i = 0; i < static_cast<int>(successors.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(successors[i].size()); j++)
        {
            nodesInPic[i].addChild(successors[i][j]);
        }
    }

    for (int i = 0; i < static_cast<int>(predecessors.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(predecessors[i].size()); j++)
        {
            nodesInPic[i].addParent(predecessors[i][j]);
        }
    }

    //设置所有结点的坐标
    setNodesCoordinate(QPoint(200, 300));
}

//设置节点坐标
void Knowledge::setNodesCoordinate(QPoint basePoint)
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
void Knowledge::getLearningTrack(vector<QString> &lt)
{
    qcout << "getlearningtrack!";
    //vector<QString> learningTrack;
    QSqlQuery query(db);
    QString sqlStr = "select b.title from path a join ";
    sqlStr += "(select bid as kid,title as title from bk as c union select pid as kid,title as title from pk as d) ";
    sqlStr += "as b where a.kid=b.kid and a.sid=";
    sqlStr += QString::number(myUser.getSid());
    sqlStr += " order by a.begintime";
    query.exec(sqlStr);
    while (query.next())
    {
        qcout << query.value(0).toString();
        lt.push_back(query.value(0).toString());
    }

}


//slots
void Knowledge::trackLearning()
{
    getLearningTrack(learningTrack);
    qcout << "tracklearning!";
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
