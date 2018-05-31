#include "route.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <iostream>
#include <math.h>
#include <time.h>

#include <sys/time.h> // 用于实现定时器
#include "myheaders.h"

#define TIME_LIMIT 2*1000 // 定时时间阈值，超过该值，就结束蚁群
#if TEST
const double UPPER = 30.0; // 信息素上限
//unsigned short CARE_WEIGHT = 0;

const int MAX_CITY_COUNT = 600;

double ALPHA=5.0; //启发因子，信息素的重要程度
double BETA=1.0;   //期望因子，城市间距离的重要程度
double ROU=1; //信息素残留参数

const int N_ANT_COUNT=400; //蚂蚁数量
const int N_IT_COUNT=40000; //迭代次数
int N_CITY_COUNT = 0; //城市数量
const double DBQ=10.0; //总的信息素
const double DB_MAX=12000.0; //一个标志数，10的9次方

double g_Trial[MAX_CITY_COUNT][MAX_CITY_COUNT]; //两两城市间信息素，就是环境信息素
double g_Distance[MAX_CITY_COUNT][MAX_CITY_COUNT]; //两两城市间距离

unsigned int matrix_graph[MAX_NODE_ID][MAX_NODE_ID] = {}; // 邻接矩阵表示的图

Graph graph[MAX_CITY_COUNT];
Graph graphr[MAX_CITY_COUNT];
Demand demands;

Edge edges[5000];                    // 从字符串中解析出的所有边的信息


//-------------------------------------------------------------------------------------------------
//
#define MAX_WEIGHT 20*600 // 边的权重不超过20，最多６００个不同节点

unsigned short final_nodes_seq[MAX_NODE_ID] = {}; // 蚁群求得的节点序列，用于后续的dijk优化
unsigned short final_nodes_count = 0;             // 结果节点的个数
unsigned short final_must_nodes_seq[52] = {};     // 结果节点中必经节点的顺序
unsigned short final_must_nodes_count = 0;        // 结果节点中必经点个数，包括起点和终点
unsigned short final_weight = MAX_WEIGHT;

// 记录最优解的节点序列，节点个数和权重信息，每找到一个解就对比更新
unsigned short best_nodes_seq[] = {};
unsigned short best_nodes_count = 0;
unsigned short best_weight = MAX_WEIGHT; // 最优权重
unsigned short best_path[MAX_NODE_ID] = {}; // 最优解的边序
unsigned short best_pathLen = 0; // 最优解含有的边的个数

// 放到前面，Ant计算节点选择概率的时候会用
//unsigned int matrix_graph[MAX_NODE_ID][MAX_NODE_ID] = {}; // 邻接矩阵表示的图

unsigned short global_accessed_node[MAX_NODE_ID] = {}; // 标记节点是否被访问，已经访问过就设置为１否则设置为０
unsigned short global_is_mustnode[MAX_NODE_ID] = {}; // 判断节点是否是必经节点，节点ID为下标，对应的值为1则是必经节点，否则非必经
unsigned short global_prev[MAX_NODE_ID] = {}; // 全局前驱数组

unsigned int max_node_id = 0; // 记录最大的节点id，用于遍历邻接矩阵
//---------------------------------------------------------------------------------------------------

unsigned long getCurTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec*1000 + tv.tv_usec/1000;
}

unsigned long g_start_time = 0l; // 程序开始执行的时间
unsigned long g_cur_time = 0l; //
unsigned long g_time_itvl = 0l; // 连续两次获取时间的时间间隔

//返回指定范围内的随机整数
int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}
//返回指定范围内的随机浮点数
double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}
//返回浮点数四舍五入取整后的浮点数
double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}

unsigned short charsToInt(char *chars, int len) {
    unsigned short result = 0;
    for (int i = 0; i < len; i++) {
    result = result + (chars[i] - '0') * pow(10, len - 1 - i);
    }
    return result;
}

void print_graph1(double graph[][MAX_CITY_COUNT], int len) {
    printf("\n******************** graph adjacency matrix ********************\n");
    for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
        printf("%0.2f    ", graph[i][j]);
    }
    printf("\n");
    }
}

// 从topo字符数组中将边的信息解析出来存放到edges数组中
// 参数一：包含边信息的topo字符数组
// 参数二：边的个数
// 参数三：边的结果数组
// 参数四：最大节点id的指针
void get_edges(char *topo[5000], int edge_num, Edge edges[],unsigned int *max_node_id) {
    int lineIndex = 0; // 记录当前字符所在字符数组中的下标
    char chars[100]; // 临时字符数组，用于将字符形式的数转换为整形数
    unsigned short charLen = 0; // 记录当前数字一字符形式表示时占用几位
    unsigned short count = 0; //记录当前的数字是该行中的第几个：只能为0,1,2,3

    for (int i = 0; i < edge_num; i++) {
    lineIndex = 0;
    charLen = 0;
    count = 0;
    while (topo[i][lineIndex] != '\0') {
        if (topo[i][lineIndex] == '\n') {
        edges[i].weight = charsToInt(chars, charLen);
        break;
        } else if (topo[i][lineIndex] == ',') {
        if (count == 0) { // 每一行的第一个数是边的id
            edges[i].edgeId = charsToInt(chars, charLen);
        } else if (count == 1) { // 第二个数是边的起点id
            edges[i].xNodeId = charsToInt(chars, charLen);
            (*max_node_id) =
            edges[i].xNodeId > (*max_node_id) ?
            edges[i].xNodeId : (*max_node_id);
        } else if (count == 2) { // 第三个数是终点id
            edges[i].yNodeId = charsToInt(chars, charLen);
            (*max_node_id) =
            edges[i].yNodeId > (*max_node_id) ?
            edges[i].yNodeId : (*max_node_id);
        }
        ++count;
        charLen = 0;
        } else if(topo[i][lineIndex] >= '0' && topo[i][lineIndex] <= '9'){
        chars[charLen] = topo[i][lineIndex];
        ++charLen;
        }
        ++lineIndex;
    }
    // 最后一行没有换行符，单独处理
    if (i == (edge_num - 1) && topo[i][lineIndex] == '\0') {
        edges[i].weight = charsToInt(chars, charLen);
    }
    }
}

void print_edges(Edge edges[], int edge_num) {
    printf("\n******************** edges info ********************\n");
    for (int i = 0; i < edge_num; i++) {
    printf("edge %d xNodeId %d yNodeId %d weight %d \n", edges[i].edgeId,
        edges[i].xNodeId, edges[i].yNodeId, edges[i].weight);
    }
}

// 从字符数组中将需求信息解析出来
// 参数一：包含需求信息的字符数组
// 参数二：存放解析出的需求信息的结构体指针
// 返回值：必经节点的个数，该值也可以直接从Demand结构体中的mustNodeCout字段中获取
unsigned short get_demand(char demand[], Demand *demands) {
    int lineIndex = 0; // 记录当前字符所在字符数组中的下标
    char chars[100]; // 临时字符数组，用于将字符形式的数转换为整形数
    unsigned short charLen = 0; // 记录当前数字一字符形式表示时占用几位
    unsigned short count = 0; //记录当前的数字是该行中的第几个：只能为0,1,2,3
    unsigned short mustNodesCount = 0; // 必经节点个数
    // 形如： 1,2，3|4
    while (demand[lineIndex] != '\0') {
    // '|'前的数字都是必经节点的id
    if (demand[lineIndex] == '|') {
        (*demands).mustNodes[mustNodesCount] = charsToInt(chars, charLen);
        charLen = 0;
        mustNodesCount++;
    } else if (demand[lineIndex] == ',') {
        if (count == 0) { // 第一个数字是起点id
        (*demands).sNodeId = charsToInt(chars, charLen);
        } else if (count == 1) { // 第二个数字是目标点id
        (*demands).dNodeId = charsToInt(chars, charLen);
        }
        charLen = 0;
        count++;
    } else if(demand[lineIndex] >= '0' && demand[lineIndex] <= '9'){
        chars[charLen] = demand[lineIndex];
        charLen++;
    }
    lineIndex++;
    }
    // 最后一个必经节点同样单独处理
    (*demands).mustNodes[mustNodesCount] = charsToInt(chars, charLen);
    mustNodesCount++;
    (*demands).mustNodesCount = mustNodesCount;

    return mustNodesCount;
}

void print_demand(Demand *demands) {
    printf("\n******************** demand info ********************\n");
    printf("demands.sNodeId = %d \ndemands.dNodeId = %d \ndemands.mustNodesCount = %d \n",
        demands->sNodeId, demands->dNodeId, demands->mustNodesCount);
    for (int i = 0; i < demands->mustNodesCount - 1; i++) {
    printf("%d|", demands->mustNodes[i]);
    }
    printf("%d\n", demands->mustNodes[demands->mustNodesCount - 1]);
}


/*****************************
 *build the graph
 ****************************/
void get_graph(int edge_num, Edge edges[], Graph graph[], int max_node_id){

    for(int i = 0; i <= max_node_id; i ++){
    graph[i].next = NULL;
    graph[i].nodesCount = 0;
    }
    //printf("edge nums = %d\n", edge_num);
    for(int i = 0; i < edge_num; i ++){

    node *t = (node *)malloc(sizeof(node));
    t->edgeId = edges[i].edgeId;
    t->endId = edges[i].yNodeId;
    t->weight = edges[i].weight;
    t->next = NULL;
    if(graph[edges[i].xNodeId].next == NULL || (graph[edges[i].xNodeId].next)->weight >= t->weight){
        t->next = graph[edges[i].xNodeId].next;
        graph[edges[i].xNodeId].next = t;
    }
    else{
        node *q = graph[edges[i].xNodeId].next;
        while(q->next != NULL && q->next->weight < t->weight){
        q = q->next;
        }
        t->next = q->next;
        q->next = t;
    }
    graph[edges[i].xNodeId].nodesCount ++;
    }
}

void get_graphR(int edge_num, Edge edges[], Graph graph[], int max_node_id){

    for(int i = 0; i <= max_node_id; i ++){
    graph[i].next = NULL;
    graph[i].nodesCount = 0;
    }
    for(int i = 0; i < edge_num; i ++){

    node *t = (node *)malloc(sizeof(node));
    t->edgeId = edges[i].edgeId;
    t->endId = edges[i].xNodeId;
    t->weight = edges[i].weight;
    t->next = NULL;
    if(graph[edges[i].yNodeId].next == NULL || (graph[edges[i].yNodeId].next)->weight >= t->weight){
        t->next = graph[edges[i].yNodeId].next;
        graph[edges[i].yNodeId].next = t;
    }
    else{
        node *q = graph[edges[i].yNodeId].next;
        while(q->next != NULL && q->next->weight < t->weight){
        q = q->next;
        }
        t->next = q->next;
        q->next = t;
    }
    graph[edges[i].yNodeId].nodesCount ++;
    }
}

void print_graph(Graph graph[], int max_node_id){
    int count = 0;
    for(int i = 0; i <= max_node_id; i ++){
    printf("start : %d count :%d |||||||", i,graph[i].nodesCount);
    node *t = graph[i].next;
    while(t != NULL){
        printf(" ->%d", t->endId);
        t = t->next;
        count ++;
    }
    printf("\n");
    }
    printf("count edge : %d\n", count);
}

/*****************************
 *   Dijkstra find the short path
 *   return the shortest path
 *****************************/
shortestPath *Dijkstra(int v0, Graph *graph,int *nodesflage, unsigned int max_node_id, Demand *demands) {
    unsigned int dist[max_node_id+1];
    memset(dist,0,sizeof(int)*(max_node_id+1));                                // record the distance
    int prev[max_node_id+1];              // record the previous node
    bool S[max_node_id+1];                                  // 判断是否已存入该点到S集合中
    int n = max_node_id;
    /*add the end node to the mustNodes*/
    demands->mustNodes[demands->mustNodesCount] = demands->dNodeId;
    demands->mustNodesCount ++;
    //printf("demands mustNodesCount : %d\n", demands->mustNodesCount);
    shortestPath *shortp = (shortestPath *)malloc(sizeof(shortestPath)*(demands->mustNodesCount)); //[(demands->mustNodesCount-1)];
    //int routeIndex[max_node_id] = { 0 };

    node *t = graph[v0].next;

    while(t != NULL){
    if(nodesflage[t->endId] == -1){
        dist[t->endId] = t->weight;
    }
    t = t->next;
    }
    for (int i = 0; i <= n; ++i) {
    S[i] = false;                                // 初始都未用过该点
    if (dist[i] == 0)
        prev[i] = -1;
    else
        prev[i] = v0;
    }
    dist[v0] = 0;
    S[v0] = true;
    for (int i = 0; i <= n; i++) {
    unsigned int mindist = MAX;
    int u = v0;
    // 找出当前未使用的点j的dist[j]最小值
    for (int j = 0; j <= n; ++j)
        if ((!S[j]) && dist[j] > 0) {
        if( dist[j] < mindist){
            u = j;                             // u保存当前邻接点中距离最小的点的号码
            mindist = dist[j];
        }
        }
    S[u] = true;
    t = graph[u].next;
    while(t != NULL){
        if ((!S[t->endId]) && nodesflage[t->endId] == -1) {
        if ((dist[u] + t->weight < dist[t->endId]) || dist[t->endId] == 0) {   //在通过新加入的u点路径找到离v0点更短的路径
            dist[t->endId] = dist[u] + t->weight;     //更新dist
            prev[t->endId] = u;                    //记录前驱顶点
        }
        }
        t = t->next;
    }
    }
    //record the path. Please careful, the path is reversed!
    for (int i = 0; i < (demands->mustNodesCount); i++){
    //printf("+++++++++++++++++++++++++++++++++\n");
    int q = demands->mustNodes[i];
    shortp[i].sNodeId = v0;
    shortp[i].dNodeId = q;
    shortp[i].pathLength = dist[q];
    int count = 0;
    while(q != v0){
        if(prev[q] == -1 || prev[q] == v0)
        break;
        shortp[i].path[count ++] = prev[q];
        q = prev[q];
    }
    shortp[i].pathNodesCount = count;
    }
    demands->mustNodes[demands->mustNodesCount] = 0;
    demands->mustNodesCount --;
    return (shortestPath *)shortp;
}

void printShortPath(shortestPath *shortp, int length){
    printf("the length is : %d\n",length);
    for(int i = 0; i < length; i ++){
    int t = shortp[i].pathNodesCount;
    //printf("int t = shortp[i].pathNodesCount:  %d\n", t);
    printf("start from node %d, end at %d , weight is %d.\n", shortp[i].sNodeId, shortp[i].dNodeId, shortp[i].pathLength);
    while(t != 0){
        printf("%d  ",shortp[i].path[--t]);
    }
    printf("\n");
    }
}

bool allNodes(int *nodesflage, int pathLength){
    for(int i = 0; i < pathLength; i ++)
    if(nodesflage[i] == -1){
        return false;
    }
    return true;
}

//find the node, to make sure if it is the mustNode
int searchMustNode(int v0, Demand *demands){
    for(int i = 0; i < demands->mustNodesCount; i ++){
    if(v0 == demands->mustNodes[i])
        return i;
    }
    return -1;
}

//test the path if it is derect to the must Node.
bool testDerect(shortestPath *shortp){
    for (int i = 0; i < shortp->pathNodesCount; ++i)
    {
    if(searchMustNode(shortp->path[i], &demands) != -1)
        return false;
    }
    return true;
}

node *nodeCp(node *t){
    if(t == NULL)
    return NULL;
    node *no = (node *)malloc(sizeof(node));
    no->edgeId = t->edgeId;
    no->endId = t->endId;
    no->weight = t->weight;
    no->next = NULL;
    return no;
}

shortestPath *shortestPathCp(shortestPath *shortp, shortestPath *result){
    //shortestPath *result = (shortestPath *)malloc(sizeof(shortestPath));
    if(shortp == NULL || result == NULL)
    return NULL;
    result->sNodeId = shortp->sNodeId;
    result->dNodeId = shortp->dNodeId;
    for(int i = 0; i < shortp->pathNodesCount; i ++)
    result->path[i] = shortp->path[i];
    result->pathNodesCount = shortp->pathNodesCount;
    result->pathLength = shortp->pathLength;
    return result;
}

//return the edge weight
int get_edgeW(Graph *graph, int start, int end){
    node *t = graph[start].next;
    while(t != NULL){
    if(t->endId == end)
        return t->weight;
    t = t->next;
    }
    return 0;
}

//return the edge Id
int get_edgeId(Graph *graph, int start, int end){
    node *t = graph[start].next;
    while(t != NULL){
    if(t->endId == end)
        return t->edgeId;
    t = t->next;
    }
    return -1;
}

//nodesflage
void node_flage(int *nodesflage, unsigned short *nodes, int length){
    for(int i = 0; i < length; i ++)
    nodesflage[nodes[i]] = 1;
}

void de_nodeflage(int *nodesflage, unsigned short *nodes, int length){
    for(int i = 0; i < length; i ++)
    nodesflage[nodes[i]] = -1;
}

bool testR(int *result, Demand *demands, int length){
    for(int j = 0; j < length; j ++){
    for(int k = 1; k < length; k ++){
        if(result[k] == result[j] && k != j){
        printf("this is a wrong result circle at: %d !!!!!!\n", result[k]);
        return false;
        }
    }
    }
    if(result[0] != demands->sNodeId){
    printf("start is wrong !!!!!!!!!\n");
    return false;
    }
    if(result[length-1] != demands->dNodeId){
    printf("end is wrong !!!!!!!!!!!\n");
    return false;
    }
    for(int i = 0; i < demands->mustNodesCount; i ++){
    int flage = 0;
    for(int j = 0; j < length; j ++){
        if(result[j] == demands->mustNodes[i]){
        flage = 1;
        break;
        }
    }
    if(flage == 0){
        printf("mustNode %d not reached!!!!!\n", demands->mustNodes[i]);
        return false;
    }
    }
    printf("it is a good result!!!!!\n");
    return true;
}

//result format
bool formatRe(int *road, int length, int *result, Graph *graph){
    int weight = 0;
    for(int i = 0; i < length-1; i ++){
    //printf("%d->", result[i]);
    node *t = graph[road[i]].next;
    while(t != NULL){
        if(t->endId == road[i+1]){
        weight += t->weight;
        result[i] = t->edgeId;
        break;
        }
        t = t->next;
    }
    if(t == NULL){
        printf("this is a wrong path, can not get to the end\n");
        return false;
    }
    }
    return true;
}

//reverse the
void reverse(int *data, int length){
    int pre = 0;
    int end = length-1;
    while(pre < length){
    int t = data[pre];
    data[pre] = data[end];
    data[end] = t;
    pre ++;
    length--;
    }
}

//定义蚂蚁类
class CAnt
{
    public:
    CAnt(void);
    ~CAnt(void);
    public:
    int m_nPath[MAX_CITY_COUNT]; //蚂蚁走的路径
    double m_dbPathLength; //蚂蚁走过的路径长度
    int m_nAllowedCity[MAX_CITY_COUNT]; //没去过的城市
    int m_nCurCityNo; //当前所在城市编号
    int m_nMovedCityCount; //已经去过的城市数量
    int endId;   // the end node Id
    int mustNodesflage[50];
    int preNodesCount[50];
    int mustNodesCount;
    public:
    int ChooseNextCity(); //选择下一个城市
    void Init(); //初始化
    void Move(int nCityNo); //蚂蚁在城市间移动
    void Search(); //搜索路径
    void CalPathLength(); //计算蚂蚁走过的路径长度
};
CAnt::CAnt(void){}

CAnt::~CAnt(void){}

void CAnt::Init(){
    mustNodesCount = 0;
    memset(mustNodesflage,0,sizeof(mustNodesflage));
    memset(preNodesCount,0,sizeof(preNodesCount));
    for (int i=0;i<N_CITY_COUNT;i++)
    {
    m_nAllowedCity[i]=-1; //设置全部城市为没有去过
    m_nPath[i]=-1; //蚂蚁走的路径全部设置为-1
    }
    //蚂蚁走过的路径长度设置为0
    m_dbPathLength=0.0;
    //随机选择一个出发城市
    //m_nCurCityNo=rnd(0,N_CITY_COUNT);
    m_nCurCityNo = demands.sNodeId;
    //把出发城市保存入路径数组中
    m_nPath[0]=m_nCurCityNo;
    //标识出发城市为已经去过了
    m_nAllowedCity[m_nCurCityNo]=1;
    //已经去过的城市数量设置为1
    m_nMovedCityCount=1;
    //end node id
    endId = demands.dNodeId;
}
//选择下一个城市
//返回值 为城市编号
int CAnt::ChooseNextCity()
{
    //printf("%d\n", m_nCurCityNo);
    int nSelectedCity=-1; //返回结果，先暂时把其设置为-1
    //==============================================================================
    //计算当前城市和没去过的城市之间的信息素总和

    double dbTotal=0.0;
    double prob[N_CITY_COUNT]; //保存各个城市被选中的概率
    memset(prob,0,sizeof(int)*N_CITY_COUNT);
    node *t = graph[m_nCurCityNo].next;
    while(t != NULL){
    if (m_nAllowedCity[t->endId] == -1) //城市没去过
    {
        //m_nAllowedCity[t->endId] = 1;
        m_nAllowedCity[demands.dNodeId] = -1;
        //prob[t->endId] = (g_Trial[m_nCurCityNo][t->endId] * g_Trial[m_nCurCityNo][t->endId]); //*ALPHA
        prob[t->endId] = (g_Trial[m_nCurCityNo][t->endId] * g_Trial[m_nCurCityNo][t->endId]); //*ALPHA
        //+ (21-(matrix_graph[m_nCurCityNo][t->endId]&0xff))*(21-(matrix_graph[m_nCurCityNo][t->endId]&0xff))*BETA*CARE_WEIGHT;

        //*10.0/g_Distance[m_nCurCityNo][t->endId]*10.0/g_Distance[m_nCurCityNo][t->endId];
        ////pow(g_Trial[m_nCurCityNo][t->endId],ALPHA);//*pow(1.0/g_Distance[m_nCurCityNo][t->endId],BETA); //该城市和当前城市间的信息素
        //printf("prob is : %f\n", prob[t->endId]);
        dbTotal=dbTotal+prob[t->endId]; //累加信息素，得到总和
        m_nAllowedCity[t->endId] = -1;
        if(demands.mustNodesCount == mustNodesCount)
        m_nAllowedCity[demands.dNodeId] = -1;
        else
        m_nAllowedCity[demands.dNodeId] = 1;
    }
    t = t->next;
    }

    //进行轮盘选择
    double dbTemp=0.0;
    if (dbTotal > 0.0) //总的信息素值大于0
    {
    dbTemp=rnd(0.0,dbTotal); //取一个随机数
    node *t = graph[m_nCurCityNo].next;
    while(t != NULL)
    {
        if (m_nAllowedCity[t->endId] == -1) //城市没去过
        {
        dbTemp=dbTemp-prob[t->endId]; //相当于转动轮盘
        if (dbTemp < 0.0) //轮盘停止转动，记下城市编号，直接跳出循环
        {
            nSelectedCity=t->endId;
            break;
        }
        }
        t = t->next;
    }
    }
    if (nSelectedCity == -1)
    {
    node *t = graph[m_nCurCityNo].next;
    while(t != NULL)
    {
        if (m_nAllowedCity[t->endId] == -1) //城市没去过
        {
        nSelectedCity=t->endId;
        break;
        }
        t = t->next;
    }
    }

    return nSelectedCity;
}

//蚂蚁在城市间移动
void CAnt::Move(int nCityNo)
{
    //int nCityNo=ChooseNextCity(); //选择下一个城市
    m_nPath[m_nMovedCityCount]=nCityNo; //保存蚂蚁走的路径
    m_nAllowedCity[nCityNo]=1;//把这个城市设置成已经去过了
    m_nCurCityNo=nCityNo; //改变当前所在城市为选择的城市
    m_nMovedCityCount++; //已经去过的城市数量加1
    int index = searchMustNode(nCityNo, &demands);
    if(index != -1){
    mustNodesflage[index] = 1;
    mustNodesCount ++;
    }
}

//蚂蚁进行搜索一次
void CAnt::Search()
{
    Init(); //蚂蚁搜索前，先初始化
    //如果蚂蚁去过的城市数量小于城市数量，就继续移动

    if(demands.mustNodesCount > mustNodesCount)
    m_nAllowedCity[demands.dNodeId] = 1;

    int nCityNo=ChooseNextCity();
    while (nCityNo != -1)
    {
    //if the add node is mustnode, add the mustNodesCount
    Move(nCityNo);

    //if add the end node , it is a good path ,break
    if(mustNodesCount == demands.mustNodesCount){

        m_nAllowedCity[demands.dNodeId] = -1;

        shortestPath *shortp = Dijkstra(nCityNo, graph, m_nAllowedCity, N_CITY_COUNT-1, &demands);

        if(shortp[demands.mustNodesCount].pathLength != 0){

        for (int i = shortp[demands.mustNodesCount].pathNodesCount-1; i >= 0; --i)
        {
            Move(shortp[demands.mustNodesCount].path[i]);
        }

        Move(shortp[demands.mustNodesCount].dNodeId);
        nCityNo = shortp[demands.mustNodesCount].dNodeId;
        }

        break;
    }
    nCityNo=ChooseNextCity();
    }
    CalPathLength();

    return;
}

//计算蚂蚁走过的路径长度
void CAnt::CalPathLength()
{
    m_dbPathLength=0.0; //先把路径长度置0
    for (int i=0;i<m_nMovedCityCount-1;i++)
    {
    m_dbPathLength+=get_edgeW(graph, m_nPath[i], m_nPath[i+1]);
    }
}

//revers
class RAnt
{
    public:
    RAnt(void);
    ~RAnt(void);
    public:
    int m_nPath[MAX_CITY_COUNT]; //蚂蚁走的路径
    double m_dbPathLength; //蚂蚁走过的路径长度
    int m_nAllowedCity[MAX_CITY_COUNT]; //没去过的城市
    int m_nCurCityNo; //当前所在城市编号
    int m_nMovedCityCount; //已经去过的城市数量
    int endId;   // the end node Id
    int mustNodesflage[50];
    int preNodesCount[50];
    int mustNodesCount;
    public:
    int ChooseNextCity(); //选择下一个城市
    void Init(); //初始化
    void Move(int nCityNo); //蚂蚁在城市间移动
    void Search(); //搜索路径
    void CalPathLength(); //计算蚂蚁走过的路径长度
};

RAnt::RAnt(void){}

RAnt::~RAnt(void){}

//初始化函数，蚂蚁搜索前调用
void RAnt::Init()
{
    mustNodesCount = 0;
    memset(mustNodesflage,0,sizeof(mustNodesflage));
    memset(preNodesCount,0,sizeof(preNodesCount));
    for (int i=0;i<N_CITY_COUNT;i++)
    {
    m_nAllowedCity[i]=-1; //设置全部城市为没有去过
    m_nPath[i]=-1; //蚂蚁走的路径全部设置为-1
    }
    //蚂蚁走过的路径长度设置为0
    m_dbPathLength=0.0;
    //随机选择一个出发城市
    //m_nCurCityNo=rnd(0,N_CITY_COUNT);
    m_nCurCityNo = demands.dNodeId;
    //把出发城市保存入路径数组中
    m_nPath[0]=m_nCurCityNo;
    //标识出发城市为已经去过了
    m_nAllowedCity[m_nCurCityNo]=1;
    //已经去过的城市数量设置为1
    m_nMovedCityCount=1;
    //end node id
    endId = demands.sNodeId;
}
//选择下一个城市
//返回值 为城市编号
int RAnt::ChooseNextCity()
{
    int nSelectedCity=-1; //返回结果，先暂时把其设置为-1

    double dbTotal=0.0;
    double prob[N_CITY_COUNT]; //保存各个城市被选中的概率
    memset(prob,0,sizeof(int)*N_CITY_COUNT);
    node *t = graphr[m_nCurCityNo].next;
    while(t != NULL){
    if (m_nAllowedCity[t->endId] == -1) //城市没去过
    {
        //prob[t->endId]=g_Trial[m_nCurCityNo][t->endId] * g_Trial[m_nCurCityNo][t->endId];
        //prob[t->endId] = (g_Trial[m_nCurCityNo][t->endId] * g_Trial[m_nCurCityNo][t->endId]); //*ALPHA
        prob[t->endId] = (g_Trial[m_nCurCityNo][t->endId] * g_Trial[m_nCurCityNo][t->endId]); //*ALPHA
        //+ (21-(matrix_graph[m_nCurCityNo][t->endId]&0xff))*(21-(matrix_graph[m_nCurCityNo][t->endId]&0xff))*BETA*CARE_WEIGHT;

        //*1.0/g_Distance[m_nCurCityNo][t->endId];//pow(g_Trial[m_nCurCityNo][t->endId],ALPHA);
        ////*pow(1.0/g_Distance[m_nCurCityNo][t->endId],BETA); //该城市和当前城市间的信息素
        //printf("prob is : %f\n", prob[t->endId]);
        dbTotal=dbTotal+prob[t->endId]; //累加信息素，得到总和
    }
    t = t->next;
    }

    double dbTemp=0.0;
    if (dbTotal > 0.0) //总的信息素值大于0
    {
    dbTemp=rnd(0.0,dbTotal); //取一个随机数
    node *t = graphr[m_nCurCityNo].next;
    while(t != NULL)
    {
        if (m_nAllowedCity[t->endId] == -1) //城市没去过
        {
        dbTemp=dbTemp-prob[t->endId]; //这个操作相当于转动轮盘
        if (dbTemp < 0.0) //轮盘停止转动，记下城市编号，直接跳出循环
        {
            nSelectedCity=t->endId;
            break;
        }
        }
        t = t->next;
    }
    }
    if (nSelectedCity == -1)
    {
    node *t = graphr[m_nCurCityNo].next;
    while(t != NULL)
    {
        if (m_nAllowedCity[t->endId] == -1) //城市没去过
        {
        nSelectedCity=t->endId;
        break;
        }
        t = t->next;
    }
    }

    return nSelectedCity;
}

//蚂蚁在城市间移动
void RAnt::Move(int nCityNo)
{
    //int nCityNo=ChooseNextCity(); //选择下一个城市
    m_nPath[m_nMovedCityCount]=nCityNo; //保存蚂蚁走的路径
    m_nAllowedCity[nCityNo]=1;//把这个城市设置成已经去过了
    m_nCurCityNo=nCityNo; //改变当前所在城市为选择的城市
    m_nMovedCityCount++; //已经去过的城市数量加1
    int index = searchMustNode(nCityNo, &demands);
    if(index != -1){
    mustNodesflage[index] = 1;
    mustNodesCount ++;
    }
}
//蚂蚁进行搜索一次
void RAnt::Search()
{
    Init(); //蚂蚁搜索前，先初始化
    //如果蚂蚁去过的城市数量小于城市数量，就继续移动

    if(demands.mustNodesCount > mustNodesCount)
    m_nAllowedCity[demands.sNodeId] = 1;
    int nCityNo=ChooseNextCity();
    while (nCityNo != -1)
    {
    //if the add node is mustnode, add the mustNodesCount
    Move(nCityNo);

    //if add the end node , it is a good path ,break
    if(mustNodesCount == demands.mustNodesCount){
        int index = searchMustNode(nCityNo, &demands);
        m_nAllowedCity[demands.sNodeId] = -1;
        shortestPath *shortp = Dijkstra(demands.sNodeId, graph, m_nAllowedCity, N_CITY_COUNT-1, &demands);
        if(shortp[index].pathLength != 0){
        for (int i = 0; i < shortp[index].pathNodesCount; ++i)
        {
            Move(shortp[index].path[i]);
        }
        Move(shortp[index].sNodeId);
        nCityNo = shortp[index].sNodeId;
        }
        break;
    }
    nCityNo=ChooseNextCity();
    }
    CalPathLength();

    return;
}

//计算蚂蚁走过的路径长度
void RAnt::CalPathLength()
{
    m_dbPathLength=0.0; //先把路径长度置0
    for (int i=0;i<m_nMovedCityCount-1;i++)
    {
    m_dbPathLength+=get_edgeW(graphr, m_nPath[i], m_nPath[i+1]);
    }
}


//tsp类
class CTsp
{
    public:
    CTsp(void);
    ~CTsp(void);
    public:
    CAnt m_cAntAry[N_ANT_COUNT]; //蚂蚁数组
    CAnt m_cBestAnt; //定义一个蚂蚁变量，用来保存搜索过程中的最优结果,该蚂蚁不参与搜索，只是用来保存最优结果
    RAnt m_rAntAry[N_ANT_COUNT];
    RAnt m_rBestAnt;
    int minMust;
    public:
    //初始化数据
    void InitData();
    //开始搜索
    void Search();

    void detectPath();

    void mustNodesTrial(int mustNode, double d, Graph *graph);
    //更新环境信息素
    void UpdateTrial();

};

//构造函数
CTsp::CTsp(void){}

CTsp::~CTsp(void){}

void CTsp::InitData()
{
    minMust = demands.mustNodesCount/2;
    //先把最优蚂蚁的路径长度设置成一个很大的值
    m_cBestAnt.m_dbPathLength=DB_MAX;
    m_rBestAnt.m_dbPathLength=DB_MAX;
    //计算两两城市间距离
    for (int i=0;i<N_CITY_COUNT;i++)
    {
    for (int j=0;j<N_CITY_COUNT;j++)
    {
        g_Distance[i][j]=0;
    }
    }
    for (int i=0;i<N_CITY_COUNT;i++)
    {
    node *t = graph[i].next;
    while(t != NULL){
        g_Distance[i][t->endId] = t->weight;
        t = t->next;
    }
    }
    //初始化环境信息素，先把城市间的信息素设置成一样
    //这里设置成1.0，设置成多少对结果影响不是太大，对算法收敛速度有些影响
    for (int i=0;i<N_CITY_COUNT;i++)
    {
    for (int j=0;j<N_CITY_COUNT;j++)
    {
        g_Trial[i][j]=1.0;
    }
    }
    // 递归设置信息素：与关键节点相连的边直接初始化为３其次是２
    int d = 2.0;
    for(int i = 0; i < demands.mustNodesCount; i ++){
    mustNodesTrial(demands.mustNodes[i],d,graph);
    mustNodesTrial(demands.mustNodes[i],d,graphr);
    }
}

void CTsp::mustNodesTrial(int mustNode, double d, Graph *graph){
    if(d == 0.0)
    return;
    node *t = graph[mustNode].next;
    while(t != NULL){
    if(g_Trial[t->endId][mustNode] == 1.0){
        g_Trial[t->endId][mustNode] += d;
        mustNodesTrial(t->endId, d-1.0,graph);
    }
    t = t->next;
    }
}

void CTsp::detectPath(){

    //临时数组，保存各只蚂蚁在两两城市间新留下的信息素
    double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
    memset(dbTempAry,0.0,sizeof(dbTempAry)); //先全部设置为0
    //计算新增加的信息素,保存到临时数组里
    int nodesflage[N_CITY_COUNT];
    memset(nodesflage,-1,sizeof(nodesflage));
    shortestPath *mustNodesGraph[demands.mustNodesCount];
    for(int i = 0; i < demands.mustNodesCount; i ++)
    mustNodesGraph[i] = Dijkstra(demands.mustNodes[i], graph, nodesflage, N_CITY_COUNT-1, &demands);

    for(int i = 0; i < demands.mustNodesCount; i ++){
    for(int j = 0; j <= demands.mustNodesCount; j ++){
        if (testDerect(&mustNodesGraph[i][j]) && i != j)
        {
        dbTempAry[mustNodesGraph[i][j].sNodeId][mustNodesGraph[i][j].path[mustNodesGraph[i][j].pathNodesCount-1]] = DBQ;
        //+=  DBQ/((mustNodesGraph[i][j].pathLength)*(demands.mustNodesCount+1)*(demands.mustNodesCount+1));

        for (int k = mustNodesGraph[i][j].pathNodesCount-1; k > 0; --k)
        {
            dbTempAry[mustNodesGraph[i][j].path[k]][mustNodesGraph[i][j].path[k-1]] = DBQ;
            //+= DBQ/((mustNodesGraph[i][j].pathLength)*(demands.mustNodesCount+1)*(demands.mustNodesCount+1));
            /* code */
        }
        dbTempAry[mustNodesGraph[i][j].path[0]][mustNodesGraph[i][j].dNodeId] = DBQ;
        //+=  DBQ/((mustNodesGraph[i][j].pathLength)*(demands.mustNodesCount+1)*(demands.mustNodesCount+1));
        }
    }
    }

    for (int i = 0; i < demands.mustNodesCount; ++i)
    {
    free(mustNodesGraph[i]);
    /* code */
    }
    mustNodesGraph[0] = Dijkstra(demands.sNodeId, graph, nodesflage, N_CITY_COUNT-1, &demands);
    for(int j = 0; j <= demands.mustNodesCount; j ++){
    if (testDerect(&mustNodesGraph[0][j])){
        dbTempAry[mustNodesGraph[0][j].sNodeId][mustNodesGraph[0][j].path[mustNodesGraph[0][j].pathNodesCount-1]] = DBQ;
        //+=  DBQ/((mustNodesGraph[0][j].pathLength)*(demands.mustNodesCount+1)*(demands.mustNodesCount+1));
        for (int k = mustNodesGraph[0][j].pathNodesCount-1; k > 0; --k)
        {
        dbTempAry[mustNodesGraph[0][j].path[k]][mustNodesGraph[0][j].path[k-1]] = DBQ;
        //+= DBQ/((mustNodesGraph[0][j].pathLength)*(demands.mustNodesCount+1)*(demands.mustNodesCount+1));
        /* code */
        }
        dbTempAry[mustNodesGraph[0][j].path[0]][mustNodesGraph[0][j].dNodeId] = DBQ;
        //+=  DBQ/((mustNodesGraph[0][j].pathLength)*(demands.mustNodesCount+1)*(demands.mustNodesCount+1));
    }
    }

    for (int i=0;i<N_CITY_COUNT;i++)
    {
    for (int j=0;j<N_CITY_COUNT;j++)
    {
        g_Trial[i][j]=g_Trial[i][j]+dbTempAry[i][j]; //最新的环境信息素 = 留存的信息素 + 新留下的信息素
    }
    }
}

//更新环境信息素
void CTsp::UpdateTrial()
{
    //临时数组，保存各只蚂蚁在两两城市间新留下的信息素
    double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
    memset(dbTempAry,0,sizeof(dbTempAry)); //先全部设置为0
    //计算新增加的信息素,保存到临时数组里
    int m=0;
    int n=0;
    int maxMustC = 0;
    int maxMustR = 0;
    int indexC = -1;
    int indexR = -1;
    for (int i=0;i<N_ANT_COUNT;i++) //计算每只蚂蚁留下的信息素
    {
    if(m_cAntAry[i].mustNodesCount > maxMustC){
        maxMustC = m_cAntAry[i].mustNodesCount;
        indexC = i;
    }

    }
    if(maxMustC > minMust){
    //printf("minMust is : %d\n", minMust);
    for (int j=1;j<m_cAntAry[indexC].m_nMovedCityCount;j++)
    {
        m=m_cAntAry[indexC].m_nPath[j];
        n=m_cAntAry[indexC].m_nPath[j-1];
        dbTempAry[n][m] += 2*minMust/demands.mustNodesCount; //700/m_cAntAry[i].m_dbPathLength;
    }
    }

    for (int i=0;i<N_ANT_COUNT;i++) //计算每只蚂蚁留下的信息素
    {
    if(m_rAntAry[i].mustNodesCount > maxMustR){
        maxMustR = m_rAntAry[i].mustNodesCount;
        indexR = i;
    }

    }
    if(maxMustR > minMust-demands.mustNodesCount/2){
    for (int j=m_rAntAry[indexR].m_nMovedCityCount-1;j>0;j--)
    {
        m=m_rAntAry[indexR].m_nPath[j];
        n=m_rAntAry[indexR].m_nPath[j-1];
        dbTempAry[m][n] += 2*maxMustR/demands.mustNodesCount; //700/m_cAntAry[i].m_dbPathLength;
    }
    }
    int max = maxMustR > maxMustC ? maxMustR : maxMustC;
    if(max > minMust)
    minMust = max;

    // TODO:当前最短路径信息素更新- final_XXX
    //for(int i=0; i<(final_nodes_count-1); i++){
    // 直接更新为原来的1.25倍，增加１/ 4
    //g_Trial[final_nodes_seq[i]][final_nodes_seq[i+1]] = 1.25*g_Trial[final_nodes_seq[i]][final_nodes_seq[i+1]];
    //}

    // TODO:全局最短路径信息素更新－best_XXX
    //for(int i=0; i<best_pathLen; i++){
    // 直接更新为原来的1.5倍
    //g_Trial[edges[best_path[i]].xNodeId][edges[best_path[i]].yNodeId] = 1.5*g_Trial[edges[best_path[i]].xNodeId][edges[best_path[i]].yNodeId];
    //}

    for (int i=0;i<N_CITY_COUNT;i++)
    {
    for (int j=0;j<N_CITY_COUNT;j++)
    {
        if (g_Trial[i][j] < UPPER)
        {
        g_Trial[i][j]=(g_Trial[i][j]*ROU+dbTempAry[i][j]); //最新的环境信息素 = 留存的信息素 + 新留下的信息素
        }else{
        g_Trial[i][j]=UPPER;
        }

    }
    }


}

void CTsp::Search()
{
    //在迭代次数内进行循环
    for (int i=0;i<N_IT_COUNT;i++)
    {
    //每只蚂蚁搜索一遍
    for (int j=0;j<N_ANT_COUNT;j++)
    {
        m_cAntAry[j].Init();
        m_cAntAry[j].Search();
    }
    //保存最佳结果
    for (int j=0;j<N_ANT_COUNT;j++)
    {
        if (m_cAntAry[j].m_nPath[m_cAntAry[j].m_nMovedCityCount-1] == demands.dNodeId && m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
        {
        m_cBestAnt=m_cAntAry[j];
        }
    }
    if (m_cBestAnt.m_nMovedCityCount != 0)
    {
        // if(i%100 == 0)printf("%d weight is %f\n", __LINE__, m_cBestAnt.m_dbPathLength);


        //TODO:添加蚁群优化参数设置:比如开始考虑信息素和权重，信息素衰减的问题
        // 简单的添加并没有什么暖用，可能需要花大量的时间调整一组适合这１５个case的参数

        //if(m_cBestAnt.m_dbPathLength < 10){ break;}

        //if(CARE_WEIGHT == 0){
        //CARE_WEIGHT = 1;
        //ROU = 0.9;
        //}


        /*
           if(i%100 == 0){
           if(g_cur_time > 0){
           g_time_itvl = getCurTime() - g_cur_time;
           }
           g_cur_time = getCurTime();
           if(((g_cur_time - g_start_time) > TIME_LIMIT) || ((g_cur_time + g_time_itvl - g_start_time)) > TIME_LIMIT){
           break;
           }else{
           continue;
           }
           }
           */


        // TODO:找到路径就退出
        break;
        /* code */
    }


    for (int j=0;j<N_ANT_COUNT;j++)
    {
        m_rAntAry[j].Init();
        m_rAntAry[j].Search();
    }
    //保存最佳结果
    for (int j=0;j<N_ANT_COUNT;j++)
    {
        if (m_rAntAry[j].m_nPath[m_rAntAry[j].m_nMovedCityCount-1] == demands.sNodeId && m_rAntAry[j].m_dbPathLength < m_rBestAnt.m_dbPathLength)
        {
        //printf("%d  %d\n", m_rAntAry[j].m_nPath[m_rAntAry[j].m_nMovedCityCount-1], demands.sNodeId);
        //printf("=====================yes, get the path!!!\n");
        m_rBestAnt=m_rAntAry[j];
        }
    }
    if (m_rBestAnt.m_nMovedCityCount != 0)
    {
        //if(i%100 == 0)printf("%d weight is %f\n", __LINE__, m_rBestAnt.m_dbPathLength);

        //if(m_rBestAnt.m_dbPathLength < 10){ break;}

        //if(CARE_WEIGHT == 0){
        //CARE_WEIGHT = 1;
        //ROU = 0.9;
        //}
        /*
           if(i%100 == 0){
           if(g_cur_time > 0){
           g_time_itvl = getCurTime() - g_cur_time;
           }
           g_cur_time = getCurTime();
           if(((g_cur_time - g_start_time) > TIME_LIMIT) || ((g_cur_time + g_time_itvl - g_start_time)) > TIME_LIMIT){
           break;
           }else{
           continue;
           }
           }
           */
        //TODO:
        break;
        /* code */
    }
    //更新环境信息素
    UpdateTrial();
    }
}

//=========================================================================================================
// added for dijkstra

void resetArray(unsigned short array[], unsigned short value, unsigned short len){
    for(int i=0; i<len; i++)
    array[i] = value;
}

void init_graph(unsigned int graph[][MAX_NODE_ID], Edge edges[], int edge_num, Demand* demands){

    for(int i=0; i<edge_num; i++){
    if(graph[edges[i].xNodeId][edges[i].yNodeId] != 0){
        // 如果当前边存在多条路径，那么取较小的一条
        if((graph[edges[i].xNodeId][edges[i].yNodeId]&0xff) > edges[i].weight){
        //printf("\nint InitGraph : %d -- %d \n",(graph[edges[i].xNodeId][edges[i].yNodeId]&0xff), edges[i].weight);
        graph[edges[i].xNodeId][edges[i].yNodeId] = ((0<<24) + (edges[i].edgeId<<8) + edges[i].weight);
        }
    }else{
        graph[edges[i].xNodeId][edges[i].yNodeId] = (0<<24) + (edges[i].edgeId<<8) + edges[i].weight;
    }
    }

    // 如果源节点到目标节点之间有边，那么直接将其置为０，否则算法会直接从sNode到dNode
    graph[demands->sNodeId][demands->dNodeId] = 0;
}

void prevToPath(unsigned short prev[], unsigned int g[][MAX_NODE_ID], unsigned short start,
    unsigned short dest, unsigned short path[], unsigned short *pathLen){

    (*pathLen) = 0;
    bool flag = true; // 判断前驱节点数组是否可以构成一条路径,true可以false不可以
    while((dest != MAX_NODE_ID) && (dest != start)){
    if(prev[dest] == MAX_NODE_ID){
        flag = false;
        //printf("\nerror in prevToPath prev[%d] = %d\n", dest, prev[dest]);
        break;
    }
    path[(*pathLen)++] = ((g[prev[dest]][dest]>>8)&0xffff);
    dest = prev[dest];
    }
    //path[(*pathLen)++] = ((g[dest][start]>>8)&0xffff);

    if(flag == false){
    resetArray(path, MAX_NODE_ID, (*pathLen));
    (*pathLen) = 0;
    }else{ // 调整顺序
    unsigned short i=0,j=(*pathLen)-1;
    unsigned short temp = 0;
    while(i<j){
        temp = path[i];
        path[i] = path[j];
        path[j] = temp;
        i++;
        j--;
    }
    }
}

unsigned short dijkstra(unsigned int g[][MAX_NODE_ID], unsigned short start,unsigned short dest, unsigned short maxNodeId){
    //printf("\n******************* in dijkstra **************************\n");
    resetArray(global_prev, MAX_NODE_ID, MAX_NODE_ID);
    bool S[MAX_NODE_ID] = {false};
    unsigned short dist[MAX_NODE_ID];
    resetArray(dist, MAX_WEIGHT, MAX_NODE_ID);

    for(int i=0; i<maxNodeId; i++){
    if((g[start][i]&0xff) != 0 && (global_accessed_node[i] == 0)){
        dist[i] = (g[start][i]&0xff);
    }else{
        dist[i] = MAX_WEIGHT;
    }
    S[i] = false;
    if(dist[i] == MAX_WEIGHT){ // 此处图中没有边相连设置权重为MAX
        global_prev[i] = MAX_NODE_ID;
    }else{
        global_prev[i] = start;
    }
    }
    dist[start] = 0;
    S[start] = true;

    for(int i=1; i<maxNodeId; i++){
    unsigned short tempDist = MAX_WEIGHT;
    unsigned short tempNode = 0;

    // 找到当前dist最小的节点，用tempNode记录并将其加入到S[]中标记为已访问
    for(int j=0;j<maxNodeId; j++){
        if((!S[j]) && (global_accessed_node[j] == 0) && (dist[j] < tempDist)){
        tempNode = j;
        tempDist  = dist[j];
        }
    }
    S[tempNode] = true;

    // 使用新加入的tempNode，对dist[]进行松弛操作
    for(int j=0; j<maxNodeId; j++){
        if((!S[j]) && (global_accessed_node[j] == 0) && (g[tempNode][j]&0xff) != 0){
        if((dist[tempNode] + (g[tempNode][j]&0xff)) < dist[j]){
            dist[j] = dist[tempNode] + (g[tempNode][j]&0xff);
            global_prev[j] = tempNode;
        }
        }
    }

    // 如果当前将目标节点添加到了最短路径中，那么终止查找
    if(tempNode == dest){
        return dist[tempNode];
    }
    }
    // 如果整个图的节点全部扩展完成之后，没有扩展到目标结点dest，那么直接返回不可达权重，代表着两个节点之间是没有路径的
    return MAX_WEIGHT;
}

// 迭代优化：根据蚁群找到的一个解，逐步缩减该解的权重
// 蚁群将路径赋值给final_XXX，然后shrink_1将final_XXX的结果进行初步优化，优化后的结果继续存入final_XXX
// 然后shrink_2以final_XXX为输入，继续对其进行优化，
// 如果可以优化并求出了一个更优的解，那么就存入best_XXX，否则直接将final_XXX的内容写入best_XXX
void shrink_1(){
    unsigned short cur_start_index = 0;
    unsigned short start = MAX_NODE_ID;
    unsigned short end = MAX_NODE_ID;

    unsigned short new_path[MAX_NODE_ID];
    unsigned short new_pathLen = 0;
    unsigned short new_pathWeight = 0;
    unsigned short sub_path[MAX_NODE_ID];
    unsigned short sub_pathLen = 0;

    unsigned short pre_weight = MAX_WEIGHT; // 记录前一次优化的权重，如果相邻两次优化权重没有变化，那么结束优化

    // 对于蚁群找到的解，此处至少可以执行一次成功的优化
    while(true){

    memset(global_accessed_node, 0, MAX_NODE_ID);

    //printf("\nthe final nodes of path is : \n");
    for(unsigned short i=0;i<final_nodes_count; i++){
        //printf("%d ", final_nodes_seq[i]);
        global_accessed_node[final_nodes_seq[i]] = 1; // 路径上的节点都标记为已经访问
    }

    // 构造dijk的寻路环境：子路径的节点访问状态设置为未访问
    // 设置dijk的节点访问状态之后，循环使用dijk进行子路径的更新
    cur_start_index = 0;
    start = MAX_NODE_ID;
    end = MAX_NODE_ID;

    new_pathLen = 0;
    new_pathWeight = 0;
    sub_pathLen = 0;

    resetArray(new_path, MAX_NODE_ID, MAX_NODE_ID);

    for(int k=0; k<=(demands.mustNodesCount); k++){
        // 起点并设置节点访问状态
        start = final_nodes_seq[cur_start_index];
        global_accessed_node[start] = 0;

        // 找到终点并设置节点访问状态
        for(unsigned short i=(cur_start_index+1); i<final_nodes_count; i++){

        if(global_is_mustnode[final_nodes_seq[i]] == 1){
            global_accessed_node[final_nodes_seq[i]] = 0;
            end = final_nodes_seq[i];
            cur_start_index = i; // 更新起点下标
            break;
        }else{
            global_accessed_node[final_nodes_seq[i]] = 0;
        }

        }

        // 开始用dijk求start到end之间的路径
        dijkstra(matrix_graph, start, end, max_node_id+1);
        prevToPath(global_prev, matrix_graph, start, end, sub_path, &sub_pathLen);

        // 求得的子路径更新到新路径中
        if(sub_pathLen != 0){
        // 将当前子路径添加到全路径中
        for(int i=0; i<sub_pathLen; i++){
            new_path[new_pathLen++] = sub_path[i];
            new_pathWeight += edges[sub_path[i]].weight;
            //printf("%d ", path[pathLen-1]);
            // TODO:设置节点访问标志
            global_accessed_node[edges[sub_path[i]].xNodeId] = 1;
            global_accessed_node[edges[sub_path[i]].yNodeId] = 1;
        }

        resetArray(sub_path, MAX_NODE_ID, sub_pathLen);
        sub_pathLen = 0;

        }else{ // 说明当前的排列无法找到一条路径
        //printf("\n %d error: failed to find a path, sub_pathLen = 0\n", __LINE__);
        new_pathLen = 0;
        break;
        }
    }

    // 当前循环优化出了一条路径，那么复制之后继续优化
    if(new_pathLen != 0){

        if(new_pathWeight >= pre_weight){
        break;
        }

        pre_weight = new_pathWeight;

        final_nodes_count = 0;
        for(int i=0; i<new_pathLen; i++){
        final_nodes_seq[final_nodes_count++] = edges[new_path[i]].xNodeId;
        }
        final_nodes_seq[final_nodes_count++] = edges[new_path[new_pathLen-1]].yNodeId;

        // 如果出现了更好的解，那么将其写入最优解数组中
        if(new_pathWeight < best_weight){
        best_weight = new_pathWeight;

        best_pathLen = 0;
        for(int i=0; i<new_pathLen; i++){
            best_path[best_pathLen++] = new_path[i];
        }
        }

        continue;
    }else{ // 当前无法再优化下去，那么结束
        break;
    }
    } // end while
}

/*
 * 给定节点序列，求出该序列对应的路径以及路径权重
 *
 * 参数一：图的邻接矩阵
 * 参数二：图的最大节点id,用于遍历图
 * 参数三：节点数组－包括起始节点和目标节点
 * 参数四：序列的长度－必经节点个数加上２
 * 参数五：结果权重的指针
 * 参数六：结果路径数组
 * 参数七：结果路径数组的大小－下标范围
 */
void sequence_to_path_and_weight(unsigned int g[][MAX_NODE_ID], unsigned short maxNodeId, unsigned short nodes[],
    unsigned short sequenceLen, unsigned short *result_w, unsigned short result_p[], unsigned short *result_pathLen){

    unsigned short sub_path[MAX_NODE_ID];
    unsigned short sub_pathLen = 0;
    (*result_pathLen) = 0;
    (*result_w) = 0;
    // 恢复全局节点访问状态
    resetArray(global_accessed_node, 0, MAX_NODE_ID);
    // TODO:设置必经点为已访问
    for(int i=0; i<sequenceLen; i++){
    global_accessed_node[nodes[i]] = 1;
    }

    for(int i=0; i<sequenceLen-1; i++){
    // 设置nodes[i]和nodes[i+1]为未访问
    global_accessed_node[nodes[i]] = 0;
    global_accessed_node[nodes[i+1]] = 0;
    dijkstra(g, nodes[i], nodes[i+1], maxNodeId);
    prevToPath(global_prev, g, nodes[i], nodes[i+1], sub_path, &sub_pathLen);

    if(sub_pathLen != 0){
        for(int i=0; i<sub_pathLen; i++){
        result_p[(*result_pathLen)++] = sub_path[i];
        (*result_w)+=edges[sub_path[i]].weight;

        global_accessed_node[edges[sub_path[i]].xNodeId] = 1;
        global_accessed_node[edges[sub_path[i]].yNodeId] = 1;

        }
        resetArray(sub_path, MAX_NODE_ID, sub_pathLen);
        sub_pathLen = 0;
    }else{
        //printf("\n%d in sequence_to_path_and_weight(), cant find path from %d - %d\n", __LINE__, nodes[i], nodes[i+1]);
        resetArray(result_p, MAX_NODE_ID, (*result_pathLen));
        (*result_pathLen) = 0;
        (*result_w) = 0;
        break;
    }
    }
}

// 激进的优化：在shrink_1进行优化完成之后，得到一个较优的解，然后从该较优的解中取出必经节点顺序
// 按该必经节点顺序依次调用dijk求出一个比shrink_1更优的解，也有可能是找不到.
// 所以在求出该更优解之前是不能破坏已知解的
// 步骤：
// １．从final_nodes_seq[]获取节点数组，将必经节点抽取到final_must_nodes[]中
// ２．将节点访问状态全部设置为未访问，必经节点设置为已访问
// ３．依次求相邻必经节点之间的最短路径－直到求出一条新的路径
// ４．对比３中求出的新路径的权重和当前的best_weight，如果比best_weight 更优，那么更新新的路径信息到best_XXX中
void shrink_2(unsigned int g[][MAX_NODE_ID], unsigned short maxNodeId){

    // TODO:从final_nodes_seq中获取必经节点并存入final_must_nodes中，作为sequence_to_path_and_weight的参数
    unsigned short path[MAX_NODE_ID] = {};
    unsigned short weight = 0;
    unsigned short pathLen = 0;

    final_must_nodes_count = 0;

    for(int i=0; i<final_nodes_count; i++){
    if(global_is_mustnode[final_nodes_seq[i]] == 1){
        final_must_nodes_seq[final_must_nodes_count++] = final_nodes_seq[i];
    }
    }

    sequence_to_path_and_weight(g, maxNodeId, final_must_nodes_seq, final_must_nodes_count, &weight, path, &pathLen);

    // 更新最短路径信息
    if(weight != 0){
    // 记录当前的全局最优解
    if(weight < best_weight){
        best_pathLen = pathLen;
        best_weight = weight;
        for(int i=0; i<pathLen; i++){
        best_path[i] = path[i];
        }
    }else{
        // 如果没有比全局最优更小，那么只更新到final_XXX－当前搜索的最优解，但非全局最优
        final_nodes_count = 0;
        for(int i=0; i<pathLen; i++){
        final_nodes_seq[final_nodes_count++] = edges[path[i]].xNodeId;
        }
        final_nodes_seq[final_nodes_count++] = edges[path[pathLen-1]].yNodeId;
    }

    }
}

int get_index(unsigned short array[], unsigned short arrayLen, unsigned short target){
    for(int i=0; i< arrayLen; i++){

    if(target == array[i]){
        return i;
    }

    }
    return -1;
}

unsigned short get_path_weight(unsigned short sNodeId, unsigned short dNodeId){
    unsigned short sub_path[MAX_NODE_ID];
    unsigned short sub_pathLen = 0;

    dijkstra(matrix_graph, sNodeId, dNodeId, max_node_id+1);
    prevToPath(global_prev, matrix_graph, sNodeId, dNodeId, sub_path, &sub_pathLen);

    unsigned short new_weight = 0;

    if(sub_pathLen != 0){
    for(int i=0; i<sub_pathLen; i++){
        new_weight += edges[sub_path[i]].weight;
    }
    }else{
    return MAX_WEIGHT;
    }

    return new_weight;
}

//　给定一个路径，进行子路径的拆分
//　如果所有的子路径拆分成功且求得一个更优的解，那么用这个更优的解去替换best_XXX
// １．全局访问数组设置为０
void shrink_3(unsigned int g[][MAX_NODE_ID], unsigned short maxNodeId){

    // 解析出必经点的顺序
    final_must_nodes_count = 0;
    //printf("\n==========================final_nodes_seq\n");
    for(int i=0; i<final_nodes_count; i++){
    //printf("%d ", final_nodes_seq[i]);
    if(global_is_mustnode[final_nodes_seq[i]] == 1){
        final_must_nodes_seq[final_must_nodes_count++] = final_nodes_seq[i];
    }
    }
    //printf("\n\n");

    //printf("\n%d\n", __LINE__);
    //getchar();

    unsigned short new_path[MAX_NODE_ID] = {};
    unsigned short new_pathLen = 0;
    unsigned short new_weight = 0;

    unsigned short start = MAX_NODE_ID;
    unsigned short end = MAX_NODE_ID;
    unsigned short nextNodeId = MAX_NODE_ID; // 下一个备选点
    unsigned short judge = MAX_WEIGHT;
    // 按相邻必经点进行子路径的替换

    resetArray(global_accessed_node, 0, MAX_NODE_ID);
    //for(int i=0; i<final_must_nodes_count; i++){
//	global_accessed_node[final_must_nodes_seq[i]] = 1;
  //  }

    for(int i=0; i<(final_must_nodes_count-1); i++){

    start = final_must_nodes_seq[i];
    end = final_must_nodes_seq[i+1];
    judge = MAX_WEIGHT;
    nextNodeId = MAX_NODE_ID;

    // 设置连续的三个点是可以访问的
    //global_accessed_node[start] = 0; // 是否可访问意义不大
    global_accessed_node[end] = 0;
    if(i<(final_must_nodes_count-2)){
        global_accessed_node[final_nodes_seq[i+2]] = 0;
    }

    int index_1 = 0, index_2 = 0;

    index_1 = get_index(final_nodes_seq, final_nodes_count, start);
    index_2 = get_index(final_nodes_seq, final_nodes_count, end);
    //printf("\n%d start = %d index = %d end = %d index = %d\n", __LINE__, start, index_1, end, index_2);

    // 直接相连的两个必经节点不需优化
    if((index_1 >= 0) && (index_2 >= 0)){
        if((index_2 - index_1) == 1){
        continue;
        }
    }else{
        printf("\n%d error, out of index\n", __LINE__);
        break;
    }

    //找使得weight最小的下一节点
    for(int j=0; j<maxNodeId; j++){

        if((g[final_must_nodes_seq[i]][j]&0xff) != 0){

        unsigned short weight = MAX_WEIGHT;

        // 倒数第二个必经点的时候不需要向后看了
        if(i == (final_must_nodes_count-2)){
            // TODO:dijkstra的参数
            //weight = (g[start][j]&0xff) + get_path_weight(j, end);
            weight = (g[start][j]&0xff) + dijkstra(g, j, end, maxNodeId);
        }else{
            //weight = (g[start][j]&0xff) + get_path_weight(j, end) + get_path_weight(end, final_must_nodes_seq[i+2]);
            weight = (g[start][j]&0xff) + dijkstra(g, j, end, maxNodeId) + dijkstra(g, end, final_must_nodes_seq[i+2], maxNodeId);
        }

        //printf("\n%d start = %d j = %d tota_ weight = %d \n", __LINE__, start, j, weight);

        if((weight < MAX_WEIGHT) && (weight < judge)){
            judge = weight;
            nextNodeId = j;
        }

        }
    }

    // 针对找到的nextNode,求其start -> nextNode + nextNode -> end之间的距离以替换原来的路径

    if(nextNodeId == MAX_NODE_ID){ // 如果没有找到下一个节点
        continue;
    }

    new_path[new_pathLen++] = (g[start][nextNodeId]>>8)&0xffff;
    new_weight += (g[start][nextNodeId]&0xff);

    //printf("\n%d nextNodeId = %d\n", __LINE__, nextNodeId);

    unsigned short sub_path[MAX_NODE_ID];
    unsigned short sub_pathLen = 0;

    global_accessed_node[nextNodeId] = 0;
    global_accessed_node[end] = 0;
    if(i<(final_must_nodes_count-2)){ // 第三个必经节点设置为不可访问避免子路径中出现必经节点
        global_accessed_node[final_nodes_seq[i+2]] = 1;
    }

    dijkstra(g, nextNodeId, end, maxNodeId);
    prevToPath(global_prev, g, nextNodeId, end, sub_path, &sub_pathLen);

    if(sub_pathLen != 0){
        for(int i=0; i<sub_pathLen; i++){
        new_path[new_pathLen++] = sub_path[i];
        new_weight += edges[sub_path[i]].weight;

        global_accessed_node[edges[sub_path[i]].xNodeId] = 1;
        global_accessed_node[edges[sub_path[i]].yNodeId] = 1;
        }

        resetArray(sub_path, MAX_NODE_ID, sub_pathLen);
        sub_pathLen = 0;
    }else{

        new_pathLen = 0;
        i = MAX_NODE_ID; // 只要有一段子路径无法找到，那么就直接退出
        break;
    }
    }

    // 找出新路径，和best对比，如果小于best那么替换：同时写入best_XXX和final_XXX中
    // 如果没有找到(new_pathLen == 0)或者找到的解更大了,那么直接退出即可，final和best都不修改
    if(new_pathLen != 0){
    //printf("\n%d new path is : \n", __LINE__);
    if(new_weight < best_weight){

        printf("\n%d !!!!!!!!! get a better path from %d decrease to %d\n", __LINE__, best_weight, new_weight);

        best_weight = new_weight;
        best_pathLen = 0;
        final_nodes_count = 0;
        for(int i=0; i<new_pathLen; i++){
        best_path[best_pathLen++] = new_path[i];
        final_nodes_seq[final_nodes_count++] = edges[new_path[i]].xNodeId;
        //printf("%d", edges[new_path[i]].xNodeId);
        }
        final_nodes_seq[final_nodes_count++] = edges[new_path[new_pathLen-1]].yNodeId;
        //printf("%d\n", edges[new_path[new_pathLen-1]].yNodeId);
    }else{
        printf("\n%d !!!!!!!!! get a worse path from %d increase to %d\n", __LINE__, best_weight, new_weight);
    }
    }else{
    // do nothing
    printf("\n%d !!!!!!!!! get noting\n", __LINE__);
    }

}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand) {
    // 1. 从输入的字符串中解析出边的信息和必经节点信息

    g_start_time = getCurTime(); // 开始计时

    //Edge edges[5000];                    // 从字符串中解析出的所有边的信息
    //Demand demands; // 从字符串中解析出的需求信息：起始节点，目标节点和必经节点

    //unsigned int max_node_id = 0; // 记录最大的节点id，用于遍历邻接矩阵

    //Graph graph[600];
    get_edges(topo, edge_num, edges, &max_node_id);
    //print_edges(edges, edge_num);

    get_demand(demand, &demands);
    //print_demand(&demands);
    //Graph mustNodesPre[demands.mustNodesCount];


    //=============================================================================================
    //
    resetArray(global_accessed_node, 0, MAX_NODE_ID); // 标记节点为都没有被访问过
    resetArray(global_prev, MAX_NODE_ID, MAX_NODE_ID);

    resetArray(global_is_mustnode, 0, MAX_NODE_ID);
    global_is_mustnode[demands.sNodeId] = 1;
    for(int i=1; i<=demands.mustNodesCount; i++){
    global_is_mustnode[demands.mustNodes[i-1]] = 1;
    }
    global_is_mustnode[demands.dNodeId] = 1;
    //=============================================================================================


    // 2. 将入的边的信息构造一个有向图
    get_graph(edge_num, edges, graph, max_node_id);
    get_graphR(edge_num, edges, graphr, max_node_id);
    //print_graph(graph, max_node_id);
    //print_graph(graphr, max_node_id);
    N_CITY_COUNT = max_node_id+1;

    // 图的邻接矩阵，用于dijk优化结果数组
    memset(matrix_graph, 0, sizeof(graph)*sizeof(unsigned int));
    init_graph(matrix_graph, edges, edge_num, &demands);

    time_t tm;
    time(&tm);
    unsigned int nSeed=(unsigned int)tm;
    srand(nSeed);

    //int result[max_node_id+1];
    int finalR[max_node_id+1];
    CTsp tsp;

    tsp.InitData(); //初始化

    while(true){

    //tsp.InitData(); //初始化
    tsp.Search(); //开始搜索

    bool re;
    if (tsp.m_cBestAnt.m_nMovedCityCount > 2)
    {
        re = formatRe(tsp.m_cBestAnt.m_nPath, tsp.m_cBestAnt.m_nMovedCityCount, finalR, graph);
    }else{
        reverse(tsp.m_rBestAnt.m_nPath, tsp.m_rBestAnt.m_nMovedCityCount);
        re = formatRe(tsp.m_rBestAnt.m_nPath, tsp.m_rBestAnt.m_nMovedCityCount, finalR, graph);
    }
    if (re)
    {

        // TODO:考虑信息素的挥发,同时也可以在后续的信息素更新的时候将已经找到并且收敛过的路径加到信息素表里面
        if(ROU >= 1){ ROU = 0.5; }

        //===========================================================================================
        // code added for dijkstra and its the first level optimize
        memset(final_nodes_seq, MAX_NODE_ID, sizeof(final_nodes_seq));
        final_nodes_count = 0;
        memset(final_must_nodes_seq, MAX_NODE_ID, sizeof(final_must_nodes_seq));
        final_must_nodes_count = 0;

        //memset(matrix_graph, 0, sizeof(graph)*sizeof(unsigned int));
        //init_graph(matrix_graph, edges, edge_num, &demands);

        for (int i = 0; i < tsp.m_cBestAnt.m_nMovedCityCount-1; i++){
        final_nodes_seq[final_nodes_count++] = edges[finalR[i]].xNodeId;
        }
        final_nodes_seq[final_nodes_count++] = edges[finalR[tsp.m_cBestAnt.m_nMovedCityCount-2]].yNodeId;

        shrink_1();

        shrink_2(matrix_graph, max_node_id+1);

        //shrink_3(matrix_graph, max_node_id+1);

        // TODO:时间判断，如果有时间就继续否则退出

        if(g_cur_time > 0){
        g_time_itvl = getCurTime() - g_cur_time;
        }
        g_cur_time = getCurTime();
        if(((g_cur_time - g_start_time) > TIME_LIMIT) || ((g_cur_time + g_time_itvl - g_start_time)) > TIME_LIMIT){
        break;
        }else{
        continue;
        }
    }
    }
    /*
       printf("\n\n%d the new path edges: \n", __LINE__);
       for(int i=0; i<new_pathLen; i++){
       printf("%d ", new_path[i]);
       }
       if(new_pathLen > 0){printf("\nthe new weight is : %d\n", new_pathWeight);}
       printf("%d the new path nodes: \n", __LINE__);
       for(int i=0; i<new_pathLen; i++){
       printf("%d ", edges[new_path[i]].xNodeId);
       }
       if(new_pathLen > 0){printf("%d\n\n", edges[new_path[new_pathLen-1]].yNodeId);}
       */

    //===========================================================================================

    unsigned short weight_1 = 0;
    printf("\n%d final nodes seq of path is :\n", __LINE__);
    for(int i=0; i<(final_nodes_count-1); i++){
    weight_1 += (matrix_graph[final_nodes_seq[i]][final_nodes_seq[i+1]]&0xff);
    printf("%d, ", final_nodes_seq[i]);
    }
    printf("%d\nfinal weight is : %d\n", final_nodes_seq[final_nodes_count-1], weight_1);

    printf("\nbest weight is : %d\n", best_weight);

    if((best_pathLen != 0) && (best_weight < MAX_WEIGHT)){
    for(int i=0; i<(best_pathLen); i++){
        record_result(best_path[i]);
    }
    }else{
    for(int i=0; i<(final_nodes_count-1); i++){
        record_result((matrix_graph[final_nodes_seq[i]][final_nodes_seq[i+1]]>>8)&0xffff);
    }
    }

    /*
       if(new_pathLen > 0){
       for(int i=0; i<new_pathLen; i++){
       record_result(new_path[i]);
       }
       }else{
       printf("\n%d the final edge of path is :\n", __LINE__);
       unsigned short weight = 0;
       for (int i = 0; i < tsp.m_cBestAnt.m_nMovedCityCount-1; i++){
       weight += edges[finalR[i]].weight;
       record_result(finalR[i]);
       printf("%d ", finalR[i]);
       }
       printf("\nfinal weight is %d \n", weight);
       }
       */
    //return;
    //}
}
#endif
