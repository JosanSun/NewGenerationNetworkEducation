#include "node.h"
#include <vector>

using namespace std;

Node::Node()
{
	isLearned = false;
	isModelKnowledge = false;
}

Node::Node(QPoint c, QString a, int r) :center(c), attribute(a), radius(r)
{
	isLearned = false;
	isModelKnowledge = false;
}

Node::~Node()
{

}

QPoint Node::getCenter() const
{
	return center;
}

QString Node::getAttribute() const
{
	return attribute;
}

vector<int> Node::getChildren()
{
	return children;
}

vector<int> Node::getParents()
{
	return parents;
}

int Node::getRadius() const
{
	return radius;
}

bool Node::getIsLearned() const
{
	return isLearned;
}

bool Node::getIsModelKnowledge() const
{
	return isModelKnowledge;
}

void Node::setCenter(QPoint c)
{
	center = c;
}

void Node::setRadius(int r)
{
	radius = r;
}

void Node::setAttribute(QString a)
{
	attribute = a;
}

void Node::setIsLearned(bool il)
{
	isLearned = il;
}

void Node::setIsModelKnowledge(bool imk)
{
	isModelKnowledge = imk;
}


void Node::addChild(int childId)
{
	children.push_back(childId);
}

void Node::addParent(int parent)
{
	parents.push_back(parent);
}
