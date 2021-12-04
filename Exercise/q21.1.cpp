#include<iostream>
#include<queue>
using namespace std;
#define MaxNumber 1001
#define INFINITE 65536
int parent[MaxNumber];
int cost[MaxNumber][MaxNumber];
int N,M;

struct Node{
    int village;
    int connectingfee;
    int operator < (const Node newNode) const
    {
        return connectingfee > newNode.connectingfee;
    }
};
priority_queue<Node> q;

int findAncestor(int a)
{
    while(parent[a] > 0)
        a = parent[a];
    return a;
}
bool checkIsConnected(int a, int b)
{
    a = findAncestor(a);
    b = findAncestor(b);
    if(a == b && a>0)
        return true;
    else
        return false;
}
void connectVillage(int a, int b)
{
    if(checkIsConnected(a,b))
        return;
    else
    {
        a = findAncestor(a);
        b = findAncestor(b);
        if( parent[a] < parent[b])
        {
            parent[b] = a;
            parent[a]--;
        }
        else
        {
            parent[a] = b;
            parent[b]--;
        }
    }
}
int Prim(int start)
{
    int finalcost = 0 ;
    int builtEdges = 0;
    
    Node n;
    n.village = start;
    n.connectingfee = 0;
    q.push(n);
    
    for(int i = 1; i <= N ; i++)
    {
        if( cost[start][i] > 0 && !checkIsConnected(start,i) )
        {
            Node newNode;
            newNode.village = i;
            newNode.connectingfee = cost[start][i];
            q.push(newNode);
        }
    }
    
    while(!q.empty() && builtEdges < N-1)
    {
        Node now = q.top();
        q.pop();
        if( !checkIsConnected(now.village,start) )
        {
            //add the village into the set
            connectVillage(now.village,start);
            finalcost += now.connectingfee;
            builtEdges++;
            //add all it's neighbour into queue
            for(int i = 1; i <= N ; i++)
            {
                if( cost[now.village][i] > 0 && !checkIsConnected(now.village,i) )
                {
                    Node newNode;
                    newNode.village = i;
                    newNode.connectingfee = cost[now.village][i];
                    q.push(newNode);
                }
            }
        }
    }
    if(builtEdges == N-1)
        return finalcost;
    else
        return -1;
}
int main()
{
    cin>>N>>M;
    for(int i = 1; i <= N;i++)
    {
        parent[i] = -1;
    }
    for(int i = 1; i <= N;i++)
    {
        for(int j = 1; j <= N;j++)
        {
            cost[i][j] = -1;
        }
    }
    int a, b, c ;
    for(int i = 0 ; i < M; i++)
    {
        cin>>a>>b>>c;
        cost[a][b] = c;
        cost[b][a] = c;
    }
    
    int finalcost ;
//     finalcost = Prim(1);
    finalcost = Kruskal();
    cout<<finalcost;
    return 0;
}