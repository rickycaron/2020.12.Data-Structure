#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef int Node_Number;//Node_Number节点编号
int queue[111], now, max_time, front, rear, counts, StartNode, EndNode, NodeNum, EdgeNum, cost;

struct Edge
{
    int Target_point;//边的目标点
    int timecost;//活动花费的时间
    Edge(int d, int p) : Target_point(d), timecost(p) {}//构造函数
};

struct Node
{
    int earliest;
    int latest = 0x3f3f3f3;//最晚完成时间设为无穷大
    int indegree;//入度
    int outdegree;//出度

    vector<Edge> inedge;//入边
    vector<Edge> outedge;//出边
};

void CalculateETime(map<Node_Number, Node> &Graph);//计算事件最早完成时间
void CalculateLTime(map<Node_Number, Node> &Graph);//计算使事件最晚完成时间
void PrintKeyRoads(map<Node_Number, Node> &Graph);//输出关键路径
int main()
{
    map<Node_Number, Node> Graph;//声明图
    cin >> NodeNum >> EdgeNum;
    for (int i = 1; i <= EdgeNum; ++i)
    {
        cin >> StartNode >> EndNode >> cost;
        Graph[EndNode].inedge.push_back(Edge(StartNode, cost));
        Graph[StartNode].outedge.push_back(Edge(EndNode, cost));//建边
        Graph[EndNode].indegree++;
        Graph[StartNode].outdegree++;
    }
    CalculateETime(Graph);
    CalculateLTime(Graph);
    PrintKeyRoads(Graph);
}
void CalculateETime(map<Node_Number, Node> &Graph)
{
    for (map<Node_Number, Node>::iterator iter = Graph.begin(); iter != Graph.end(); ++iter)
        if ((*iter).second.indegree == 0)//可能有多个起点，将所有入度为零的点加入队列
        {
            queue[++rear] = (*iter).first;
            Graph[(*iter).first].earliest = 0;//初始化事件最早完成时间
        }
    while (front != rear)
    {
        counts++;//计数图中能够拓扑排序的节点个数
        now = queue[++front];//出队、
        //对于这一个顶点的每一条边
        for (vector<Edge>::iterator iter = Graph[now].outedge.begin(); iter != Graph[now].outedge.end(); ++iter)
        {
            Graph[(*iter).Target_point].earliest = max(Graph[(*iter).Target_point].earliest, Graph[now].earliest + (*iter).timecost);//spfa算法计算最长路径，最长路径就是事件最早完成时间
            if (--Graph[(*iter).Target_point].indegree == 0)//遍历到一个点就删掉一条到目标点的出边，直到目标点为入度零，将目标点加入队列
            {
                queue[++rear] = (*iter).Target_point;
                max_time = max(max_time, Graph[(*iter).Target_point].earliest);//获得最长时间，即最早完成时间
            }
        }
    }
    if (counts != Graph.size())//图中能够拓扑排序的节点个数小于图中节点的总个数，说明存在环结构，不能拓扑排序
        cout << 0, exit(0);//结束程序
    else
        cout << max_time << endl;//否则，输出最长时间，即最早完成时间
}
void CalculateLTime(map<Node_Number, Node> &Graph)
{
    for (int i = Graph.size(); i > 0;)
    {
        now = queue[i--];
        if (Graph[now].outdegree == 0 && Graph[now].earliest == max_time)//可能存在多个终点，获得出度为零的节点，且最早完成时间要等于整个工程的最早完成时间，才初始化。排除松节点，这一步很关键！！
            Graph[now].latest = Graph[now].earliest;
        for (vector<Edge>::iterator iter = Graph[now].inedge.begin(); iter != Graph[now].inedge.end(); ++iter)
            Graph[(*iter).Target_point].latest = min(Graph[now].latest - (*iter).timecost, Graph[(*iter).Target_point].latest);
    }
}
void PrintKeyRoads(map<Node_Number, Node> &Graph)
{
    for (int now = 1; now <= Graph.size(); now++)
        for (vector<Edge>::reverse_iterator r_iter = Graph[now].outedge.rbegin(); r_iter != Graph[now].outedge.rend(); ++r_iter)//题目要求起点编号相同时，与输入时任务的顺序相反，所以反过来遍历
            if (Graph[(*r_iter).Target_point].latest - (*r_iter).timecost == Graph[now].earliest)
                cout << now << "->" << (*r_iter).Target_point << endl;
}