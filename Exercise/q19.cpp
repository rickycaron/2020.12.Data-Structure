// 07-图5 Saving James Bond - Hard Version (30 point(s))
// This time let us consider the situation in the movie "Live and Let Die" in which James Bond, the world's most famous spy, was captured by a 
// group of drug dealers. He was sent to a small piece of land at the center of a lake filled with crocodiles. There he performed the most daring 
// action to escape -- he jumped onto the head of the nearest crocodile! Before the animal realized what was happening, James jumped again onto 
// the next big head... Finally he reached the bank before the last crocodile could bite him (actually the stunt man was caught by the big mouth 
// and barely escaped with his extra thick boot).

// Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) and the northeast corner at (50,50). 
// The central island is a disk centered at (0,0) with the diameter of 15. A number of crocodiles are in the lake at various positions. 
// Given the coordinates of each crocodile and the distance that James could jump, you must tell him a shortest path to reach one of the banks. 
// The length of a path is the number of jumps that James has to make.

// Input Specification:
// Each input file contains one test case. Each case starts with a line containing two positive integers N (≤100), the number of crocodiles, and D, 
// the maximum distance that James could jump. Then N lines follow, each containing the (x,y) location of a crocodile. Note that no two crocodiles 
// are staying at the same position.

// Output Specification:
// For each test case, if James can escape, output in one line the minimum number of jumps he must make. Then starting from the next line, 
// output the position (x,y) of each crocodile on the path, each pair in one line, from the island to the bank. If it is impossible for James to 
// escape that way, simply give him 0 as the number of jumps. If there are many shortest paths, just output the one with the minimum first jump, 
// which is guaranteed to be unique.

// Sample Input 1:
// 17 15
// 10 -21
// 10 21
// -40 10
// 30 -50
// 20 40
// 35 10
// 0 -10
// -25 22
// 40 -40
// -30 30
// -10 22
// 0 11
// 25 21
// 25 10
// 10 10
// 10 35
// -30 10
// 结尾无空行
// Sample Output 1:
// 4
// 0 11
// 10 21
// 10 35
// 结尾无空行
// Sample Input 2:
// 4 13
// -12 12
// 12 12
// -12 -12
// 12 -12
// Sample Output 2:
// 0
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
bool canJump(int a, int b)
{
    if( sqrt (   pow( points[a].x - points[b].x ,2)  +  pow( points[a].y - points[b].y ,2)   ) <= D )
        return true;
    else
        return false;
}
bool canJump(int a)
{
    if( sqrt (   pow( points[a].x  ,2)  +  pow( points[a].y  ,2)   ) <= D + 7.5 )
        return true;
    else
        return false;
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
                if(points[i].path == v)
                {
                    //for every neighbour of v, the neighbour is i
                    q.push(i);
                    for(int j = 1 ; j <= N ; j++)
                    {
                        if( i!=j && canJump(i,j) && points[i].dist+1 < points[j].dist )
                        {
                            //for every neighbour of i
                            points[j].path = i;
                            points[j].dist = points[i].dist+1;
                        }
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
    p.dist = VeryFar;
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
        if(canJump(i))
        {
            points[i].dist = 1;
            points[i].path = 0;
        }
    }
    Dijkstra();
    int bestExit = 0;
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