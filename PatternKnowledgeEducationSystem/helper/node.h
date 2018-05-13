/*========= 节点类 =========*/
#ifndef NODE_H
#define NODE_H

#include <QPainter>
#include <string>
#include <vector>
using namespace std;

class Node
{
public:
    Node();
    Node(QPoint center, QString attribute, int r);
    ~Node();
    void setCenter(QPoint center);
    void setRadius(int r);
    void setAttribute(QString attribute);
    void setIsLearned(bool isLearned);
    void setIsModelKnowledge(bool isModelKnowledge);
    void addChild(int childId);
    void addParent(int parent);

    QPoint getCenter() const;
    int getRadius() const;
    QString getAttribute() const;
    vector<int> getChildren();
    vector<int> getParents();
    bool getIsLearned() const;
    bool getIsModelKnowledge() const;

private:
    QPoint center;
    QString attribute;
    int radius;
    vector<int> children;
    vector<int> parents;
    bool isLearned;
    bool isModelKnowledge;
};

#endif // NODE_H
