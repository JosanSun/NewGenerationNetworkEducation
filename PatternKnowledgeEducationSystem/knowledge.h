/*======= 知识库查看模块 ========*/
#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <QPainter>
#include <vector>
#include <QWidget>
#include <QtSql>
#include <map>

#include "helper/node.h"
#include "ui_knowledge.h"
#include "attribution.h"

using namespace std;

class knowledge : public QWidget
{
	Q_OBJECT

public:
	knowledge(QWidget *parent = 0);
	~knowledge();

protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
	//根据用户学习轨迹变换节点颜色
	void trackLearning();

private:
	Ui::knowledge ui;
	QSqlDatabase db;
	attribution *attrWindow;
	vector<QString> learningTrack;
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

	vector<Node> nodesInPic;
	map<QString, int> nodesAttributesMap;
};

#endif // KNOWLEDGE_H
