/*======= 知识库查看模块 ========*/
#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <QPainter>
#include <vector>
#include <QWidget>
#include <QtSql>
#include <map>

#include "helper/node.h"
#include "helper/attribution.h"
using namespace std;

namespace Ui {
class Knowledge;
}

class Knowledge : public QWidget
{
    Q_OBJECT

public:
    Knowledge(QWidget *parent = 0);
    ~Knowledge();

signals:
    void closeSignal();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent* ev);
//    //mouse func
//    virtual void mousePressEvent(QMouseEvent *event);
//    virtual void mouseMoveEvent(QMouseEvent *event);
//    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //根据用户学习轨迹变换节点颜色
    void trackLearning();

private:
    void initUI();
    void init();
    void openDatabase();
    void paintEvent(QPaintEvent *);

    //根据节点在图上画圆
    void drawCircles(vector<Node> nodes, QColor color);

    //	//在两个圆之间连线
    //	void drawLine(QPoint *startPoint, QPoint *endPoint, int r, bool isTracked);

    //画平面
    void drawPanel(QPoint *basePoint, QString label, QColor color);

    //从数据库中获得属性值
    vector<QString> getAttributesFromDB(); //ymm

    //从数据库中获得后继节点关系
    vector<vector<int>> getSuccessors(vector<QString> &attributes); //ymm

    //从数据库中获得前驱节点关系
    vector<vector<int>> getPredecessors(vector<vector<int>> &successors);

    //根据数据库中节点信息生成节点
    void generateNodes(vector<QString> attributes, vector<vector<int>> successors, vector<vector<int>> predecessors, int r);

    //设置节点坐标
    void setNodesCoordinate(QPoint basePoint);

    //根据鼠标点击坐标获取当前节点属性值
    QString getAttributeByPosition(QPoint point);

    //获取用户学习轨迹
    void getLearningTrack(vector<QString>&); //ymm

private:
    Ui::Knowledge* ui;
    QSqlDatabase db;
    Attribution *attrWindow;
    vector<QString> learningTrack;
    vector<Node> nodesInPic;
    map<QString, int> nodesAttributesMap;

    bool        mMove;
    QPoint      mPos;
};

#endif // KNOWLEDGE_H
