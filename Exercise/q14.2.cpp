#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <stack>
#define MaxNumber 100
#define VeryFar 65536
using namespace std;

struct point{
    int x;
    int y;
    int dist;//the distance from the source 
    int path;//last point to jump to here
    bool canExit;
};
int N,D;
vector<point> points;
queue<int> q;
bool canJump(int a, int b = 0)
{
    if(b == 0 )
    {
        if( sqrt (   pow( points[a].x  ,2)  +  pow( points[a].y  ,2)   ) <= D + 7.5 )
            return true;
        else
            return false;
    }
    else
    {
        if( sqrt (   pow( points[a].x - points[b].x ,2)  +  pow( points[a].y - points[b].y ,2)   ) <= D )
            return true;
        else
            return false;
    }
}
bool canSucceed(int a)
{
    if( points[a].x + D >= 50 || points[a].x - D <= -50 || points[a].y + D >= 50 || points[a].y - D <= -50)
        return true;
    else
        return false;
}
float firstjump(int a)
{
    while(points[a].path !=0)
    {
        a = points[a].path;
    }
    return sqrt (   pow( points[a].x  ,2)  +  pow( points[a].y  ,2)   ) ;
}
void Dijkstra()
{
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        if(canSucceed(v))
        {
            points[v].canExit = true;
            continue;
        }      
        else
        {
            for(int i = 1 ; i <= N ; i++)
            {
                if(canJump(i,v) && v!=i)
                {
                    //for every neighbour of v, the neighbour is i
                    if(points[i].dist == VeryFar)
                    {
                        points[i].dist = points[v].dist+1;
                        points[i].path = v;
                        q.push(i);
                    }
                }
            }
        }
    }
}
int main()
{
    cin>>N>>D;
    if(D>=50)
    {
        cout<<1<<endl;
        return 0;
    }
    
    point p;
    p.x = 0;
    p.y = 0;    
    p.dist = 0;
    p.path = -1;
    p.canExit = false;
    
    points.push_back(p);
    q.push(0);
    
    for(int i = 1 ; i<=N;i++)
    {
        point p;
        cin>>p.x>>p.y;
        p.dist = VeryFar;
        p.path = -1;
        p.canExit = false;
        points.push_back(p);
    }
    Dijkstra();
//     for(int i = 1 ; i<=N;i++)
//     {
//         printf("The %d th point, x is %d, y is %d, distance is %d, parent is %d can succeed %d \n",i,points[i].x,points[i].y,points[i].dist,points[i].path,points[i].canExit);
//     }
    int bestExit = 0;
    points[bestExit].dist = VeryFar;
    for(int i = 1 ; i<=N;i++)
    {
        if( points[i].canExit )
        {
            if( points[i].dist < points[bestExit].dist)
                bestExit = i;
            else if( points[i].dist == points[bestExit].dist && firstjump(i) < firstjump(bestExit))
                bestExit = i;
        }
    }
    if(bestExit == 0)
    {
        cout<<0;
    }
    else
    {
        cout << points[bestExit].dist + 1<<endl;
        stack<int> printstack;
        while(bestExit !=0)
        {
            printstack.push(bestExit);
            bestExit = points[bestExit].path;
        }
        while(!printstack.empty())
        {
            int bestExit = printstack.top();
            printstack.pop();
            cout<<points[bestExit].x<<" "<<points[bestExit].y<<endl;
        }
    }
    return 0;
}