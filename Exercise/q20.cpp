#include<iostream>
#include<queue>
#define INFINITY 65536
#define MaxNumber 500
using namespace std;

struct GraphNode
{
    int distance;
    int cost;
};
typedef struct Point{
    int data;
    int distance;
    bool operator<( const Point & a) const
    {
        return distance > a.distance;
    }
}point;

//only used to store the information for the existing edge, not going to change anymore
struct GraphNode graph[MaxNumber][MaxNumber];

//used to store the information from the source point during the dijkstra algorithm
bool hasCollected[MaxNumber];
int distanceArr[MaxNumber];
int cost[MaxNumber];

priority_queue<point> q;

int N, M, S, D;

void Dijkstra(int S)
{
    //initialize the source point
    distanceArr[S] = 0;
    cost[S] = 0;
    //insert the first point into priority_queue
    Point p;
    p.data = S;
    p.distance = 0;
    q.push(p);
    
    while(!q.empty())
    {
        Point thepoint = q.top();
        q.pop();
        if(hasCollected[thepoint.data])
            continue;
        else
        {
            hasCollected[thepoint.data] = true;
            for(int i = 0; i < N; i++)
            {
                if( graph[thepoint.data][i].distance != INFINITY && !hasCollected[i])
                {
                    //for all the neighbours of thepoint that haven't collect 
                    //update the distance of point if necessary
                    if(  distanceArr[thepoint.data] + graph[thepoint.data][i].distance < distanceArr[i]  )
                    {
                        distanceArr[i] = distanceArr[thepoint.data] + graph[thepoint.data][i].distance;
                        cost[i] = cost[thepoint.data] + graph[thepoint.data][i].cost;
                    }
                    else if( distanceArr[thepoint.data] + graph[thepoint.data][i].distance == distanceArr[i] && cost[thepoint.data] + graph[thepoint.data][i].cost < cost[i])
                    {
                        cost[i] = cost[thepoint.data] + graph[thepoint.data][i].cost;
                    }
                    //add the point i into the queue
                    Point p;
                    p.data = i;
                    p.distance = distanceArr[i];
                    q.push(p);
                }
            }
        }
    }
}

int main()
{
    cin>>N>>M>>S>>D;
    int a,b,c,d;
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            graph[i][j].distance = INFINITY;
            graph[i][j].cost = INFINITY;
        }
    }
    for(int i = 0 ; i < M ; i++)
    {
        cin>>a>>b>>c>>d;
        graph[a][b].distance = c;
        graph[a][b].cost = d;
        graph[b][a].distance = c;
        graph[b][a].cost = d;
    }
    for(int i = 0 ; i < N; i++ )
    {
        hasCollected[i] = false;
        distanceArr[i] = INFINITY;
        cost[i] = 0;
    }
    
    Dijkstra(S);
    
    printf("%d %d\n", distanceArr[D],cost[D]);
    return 0;
}