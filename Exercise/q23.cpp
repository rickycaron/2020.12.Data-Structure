#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Procedure{
    public:
        bool checked;
        int start;
        int end;
        int time;
    
        Procedure(int s, int e, int t):checked(false),start(s),end(e),time(t){}
        void refresh(){checked = false;}
};
class WorkPoint{
    public:
        bool hasFinished;
        int earliestFinishedTime;
        int latestStartTime;
    
        WorkPoint():hasFinished(false),earliestFinishedTime(0),latestStartTime(0){}
        void refresh(){hasFinished = false;}
        bool canBeCritial(){return earliestFinishedTime==latestStartTime;}
};
vector<Procedure> procedures;
vector<WorkPoint> workPoints;
int N,M;

void printAllNodes(); 

int findAvailbleWork()
{
    for( int i = 1 ; i <= N ; i++)//for every point
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
int findLastWork()
{
    for( int i = 1 ; i <= N ; i++)//for every point
    {
        if(!workPoints[i].hasFinished)//Requirenment1: if it hasn't been finished
        {
            //check whether it has any more later work
            bool canCheck = true;
            for(int j = 0 ; j < M ; j++)
            {
                if( !procedures[j].checked && procedures[j].start == i)//this job still has a preprocess
                {
                    canCheck = false;
                    break;
                }
            }
            if(canCheck)//Requirenment2: if it can check now
                return i;
            else
                continue;
        }
    }
    return -1;//means 1.all the work has been checked; 2. there is a loop
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
    for( int i = 1 ; i <= N ; i++)//for every point
    {
        if(!workPoints[i].hasFinished)
        {
            return false;
        }
    }
    return true;
}
int findLongestTimePoint()
{
    int longestTime = workPoints[1].earliestFinishedTime;
    int finalPoint = 1;
    for( int i = 1 ; i <= N ; i++)//for every point
    {
        if( workPoints[i].earliestFinishedTime > longestTime )
        {
            longestTime = workPoints[i].earliestFinishedTime;
            finalPoint = i;
        }
    }
    return finalPoint;
}
bool checkAllEarlyFinishTime()
{
    int nextProcedure = findAvailbleWork();
    while( nextProcedure!= -1)
    {
        doWork(nextProcedure);
        nextProcedure =  findAvailbleWork();
    }
    if(allProcedureDone())
    {
        return true;
    }
    else
    {
        cout<<0;
        return false;
    }
}
void checkAllLateStartTime()
{
    int finalPoint = findLongestTimePoint();
    cout<<workPoints[finalPoint].earliestFinishedTime<<endl;
    //initialize all the workpoint
    for( int i = 1 ; i <= N ; i++)//for every point
    {
        workPoints[i].refresh();
        workPoints[i].latestStartTime = workPoints[finalPoint].earliestFinishedTime;
    }
    for( int i = 0 ; i <= M ; i++)//for every point
    {
        procedures[i].refresh();
    }
    
    
    //find the workpoint with no later procedure
    int lastWork = findLastWork();
    while(lastWork != -1)
    {
        workPoints[lastWork].hasFinished = true;
        for( int i = 0 ; i <= M ; i++ )
        {
            if( !procedures[i].checked && procedures[i].end == lastWork )
            {
                //for all the pre work for the last work
                if( workPoints[procedures[i].end].latestStartTime - procedures[i].time < workPoints[procedures[i].start].latestStartTime)
                {
                     workPoints[procedures[i].start].latestStartTime =  workPoints[procedures[i].end].latestStartTime - procedures[i].time;
                }
                procedures[i].checked = true;
            }
        }
        lastWork = findLastWork();
    }
    return;
}
stack<int> getCrticalPath()
{
    for( int i = 1 ; i <= N ; i++)//for every point
    {
        workPoints[i].refresh();
    }
    for( int i = 0 ; i <= M ; i++)//for every point
    {
        procedures[i].refresh();
    }
    stack<int> path;
    int lastWork = findLongestTimePoint();
    path.push(lastWork);
    int leftTime = workPoints[lastWork].latestStartTime;
    while(leftTime > 0)
    {
         for(auto pro : procedures)
        {
            if( pro.end == lastWork )
            {
                //for all the pre work for the last work
                if( workPoints[pro.start].canBeCritial() && workPoints[pro.start].earliestFinishedTime + pro.time == workPoints[pro.end].earliestFinishedTime )
                {
                    lastWork = pro.start;
                    leftTime = leftTime - pro.time;
                    path.push(lastWork);
                    continue;
                }
            }
        }
    }
    return path;
}
void printAllNodes()
{
    for(auto w:workPoints)
    {
        cout<<w.earliestFinishedTime<<" "<<w.latestStartTime<<" "<<w.hasFinished<<endl;
    }
}
int main()
{
    cin>>N>>M;
    
    //initializing the graph and the array 
    for(int i = 0 ; i <= N; i++)
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
    if(checkAllEarlyFinishTime())
    {
        checkAllLateStartTime();

        stack<int> path = getCrticalPath();
        
        int begin, end;
        begin = path.top();
        path.pop();
        while(!path.empty())
        {
            end =  path.top();
            path.pop();
            cout<<begin<<"->"<<end<<endl;
            begin = end;
        }
    }
    return 0;
}