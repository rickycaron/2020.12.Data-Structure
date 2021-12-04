#include<iostream>
#include<queue>
#include<set>
using namespace std;
#define MaxNumber 1001
#define INFINITE 65536
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

int Prim(int start)
{
    int finalcost = 0 ;
    int builtEdges = 0;
    set<int> villageSet;
    
    Node n;
    n.village = start;
    n.connectingfee = 0;
    q.push(n);
    villageSet.insert(start);
    
    for(int i = 1; i <= N ; i++)
    {
        if( cost[start][i] > 0 )
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
        if( villageSet.find (now.village) == villageSet.end() )
        {
            //add the village into the set
            villageSet.insert(now.village);
            finalcost += now.connectingfee;
            builtEdges++;
            //add all it's neighbour into queue
            for(int i = 1; i <= N ; i++)
            {
                if( cost[now.village][i] > 0 && villageSet.find (i) == villageSet.end() )
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
    finalcost = Prim(1);
    cout<<finalcost;
    return 0;
}