#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <cstdlib>
#include "windows.h"

#define MAX_NODE_ID 1000
#define MAX 21000
// 边的结构体，数据成员依次是 边的id,起点id，终点id，权重(20以内)
typedef struct{
    unsigned short edgeId;
    unsigned short xNodeId;
    unsigned short yNodeId;
    unsigned short weight;
}Edge;

// 目标结构体，数据成员依次是起点id，终点id，必须经过的节点id(必经节点不超过50个)
// 以及必经节点的个数
typedef struct{
    unsigned short sNodeId;
    unsigned short dNodeId;
    unsigned short mustNodes[60];
    unsigned short mustNodesCount;
}Demand;

// record the shortest path
typedef struct{
    unsigned short sNodeId;
    unsigned short dNodeId;
    unsigned short path[MAX_NODE_ID];
    unsigned short pathNodesCount;
    unsigned int   pathLength;
}shortestPath;

// node with weight
typedef struct node{
    unsigned short edgeId;
    unsigned short endId;
    unsigned short weight;
    node *next;
}node;

typedef struct Graph{
    unsigned short nodesCount;
    node *next;
}Graph;

typedef struct pathnode
{
    shortestPath *shortp;
    pathnode *next;
}pathnode;
// result
// 从字符数组中解析出所有边的集合
// 参数分别为topo.csv对应的边信息数组,边的条数,结果数组，记录节点最大id的unsigned int指针
void get_edges(char *topo[5000], int edge_num, Edge edges[], unsigned int *max_node_id);

// 从字符数组中解析出要求信息
// 参数为demand.csv对于那个的要求信息和存放结果的结构体指针
// 必经节点个数
unsigned short get_demand(char demand[], Demand *demands);

// 将一个char数组转换为一个int数据
// 参数：char数组，char数组的长度
// 返回：对应的整形数据
unsigned short charsToInt(char *chars, int len);

// 打印图的邻接biao
void print_graph(Graph graph[], int max_node_id);

// 从输入的字符数组求解出最短路径
// 参数分别为：topo.csv文件对应的字符数组,边的条数,demand.csv对应的字符数组
void search_route(char **graph, int edge_num, char *condition);

void print_edges(Edge edges[], int edge_num);

void print_demand(Demand *demands);

/*****************************
 *build the graph
 ****************************/
void get_graph(int edge_num, Edge edges[], Graph graph[], int max_node_id);

/*****************************
 *   Dijkstra find the short path
 *   return the shortest path
 *****************************/
shortestPath *Dijkstra(int v0, Graph *graph,int *nodesflage, unsigned int max_node_id, Demand *demands);

void printShortPath(shortestPath *shortp, int length);

//find the node, to make sure if it is the mustNode
int searchMustNode(int v0, Demand *demands);
bool allNodes(int *nodesflage, int pathLength);
bool detectPath(int start, Graph *graph, Demand *demands,int *nodesflage, int *mustNodesflage, int max_node_id, int *preNodesCount);
node *nodeCp(node *t);
shortestPath *shortestPathCp(shortestPath *shortp, shortestPath *result);
int get_edgeW(Graph *graph, int start, int end);
int get_edgeId(Graph *graph, int start, int end);
void node_flage(int *nodesflage, unsigned short *nodes, int length);
void de_nodeflage(int *nodesflage, unsigned short *nodes, int length);
void testR(int *result, Demand *demands);
bool formatRe(int *result, Graph *graph);

/*******************************
 *test the circle and delete it
 *return the new length, if failed ,return -1
 *******************************/
class AntNet
{
public:
    void update()
    {
        int id = rand() % 5;
        Sleep(id * 1000);
    }
};
int deleteCircle(unsigned int graph[][MAX_NODE_ID], int *nodesflage, unsigned short *pathNodes, int length,unsigned int max_node_id,  Demand *demands);
#endif
