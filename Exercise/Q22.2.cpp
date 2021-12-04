#include<iostream>
#include<vector>
#define MaxNumber 100
using namespace std;
class Procedure{
    public:
        bool checked;
        int start;
        int end;
        int time;
        Procedure(int s, int e, int t):checked(false),start(s),end(e),time(t){}
};
vector<Procedure> procedures;
class WorkPoint{
    public:
        bool hasFinished;
        int earliestFinishedTime;
        WorkPoint():hasFinished(false),earliestFinishedTime(0){}
};
vector<WorkPoint> workPoints;
int N,M;

int findAvailbleWork()
{
    for( int i = 0 ; i < N ; i++)//for every point
    {
        if(!workPoints[i].hasFinished)//Requirenment1: if it hasn't been finished
        {
            //check whether it can start
            bool canStart = true;
            for(int j = 0 ; j < M ; j++)
            {
                if( !procedures[j].checked && procedures[j].end == i)//this job still has a preprocess
                {
                    canStart = false;
                    break;
                }
            }
            if(canStart)//Requirenment2: if it can start now
                return i;
            else
                continue;
        }
    }
    return -1;//means 1.all the work has been done; 2. there is a loop
}
void doWork(int procedureDoing)
{
    workPoints[procedureDoing].hasFinished = true;
    for(int i =0;i<M;i++)
    {
        if( !procedures[i].checked && procedures[i].start == procedureDoing)
        {
            if( workPoints[procedureDoing].earliestFinishedTime + procedures[i].time >  workPoints[ procedures[i].end ].earliestFinishedTime )
            {
                workPoints[ procedures[i].end ].earliestFinishedTime = workPoints[procedureDoing].earliestFinishedTime + procedures[i].time;
            }
            procedures[i].checked = true;
        }
    }
}
bool allProcedureDone()
{
    for( int i = 0 ; i < N ; i++)//for every point
    {
        if(!workPoints[i].hasFinished)
        {
            return false;
        }
    }
    return true;
}
int fingLongestTime()
{
    int longestTime = workPoints[0].earliestFinishedTime;
    for( int i = 1 ; i < N ; i++)//for every point
    {
        if( workPoints[i].earliestFinishedTime > longestTime )
        {
            longestTime = workPoints[i].earliestFinishedTime;
        }
    }
    return longestTime;
}
void work()
{
    int nextProcedure = findAvailbleWork();
    while( nextProcedure!= -1)
    {
        doWork(nextProcedure);
        nextProcedure =  findAvailbleWork();
    }
    if(allProcedureDone())
    {
        cout<<fingLongestTime();
    }
    else
    {
        cout<<"Impossible";
    }
}
int main()
{
    cin>>N>>M;
    
    //initializing the graph and the array 
    for(int i = 0 ; i < N; i++)
    {
        workPoints.push_back(WorkPoint());
    }
    int x,y,time;
    //inserting the edges, the work procedure
    for(int i=0;i<M;i++)
    {
        cin>>x>>y>>time;
        procedures.push_back(Procedure(x,y,time));
    }
    work();
    return 0;
}