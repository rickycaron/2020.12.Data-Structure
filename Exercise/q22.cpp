// 08-图8 How Long Does It Take (25 point(s))
// Given the relations of all the activities of a project, you are supposed to find the earliest completion time of the project.

// Input Specification:
// Each input file contains one test case. Each case starts with a line containing two positive integers N (≤100), the number of activity check points 
// (hence it is assumed that the check points are numbered from 0 to N−1), and M, the number of activities. Then M lines follow, each gives the description of an activity.
//  For the i-th activity, three non-negative numbers are given: S[i], E[i], and L[i], where S[i] is the index of the starting check point, E[i] of the ending check point, and 
//  L[i] the lasting time of the activity. The numbers in a line are separated by a space.

// Output Specification:
// For each test case, if the scheduling is possible, print in a line its earliest completion time; or simply output "Impossible".

// Sample Input 1:
// 9 12
// 0 1 6
// 0 2 4
// 0 3 5
// 1 4 1
// 2 4 1
// 3 5 2
// 5 4 0
// 4 6 9
// 4 7 7
// 5 7 4
// 6 8 2
// 7 8 4
// 结尾无空行
// Sample Output 1:
// 18
// 结尾无空行
// Sample Input 2:
// 4 5
// 0 1 1
// 0 2 2
// 2 1 3
// 1 3 4
// 3 2 5
// Sample Output 2:
// Impossible

#include<iostream>

#define MaxNumber 100
using namespace std;
int procedureTime [MaxNumber][MaxNumber];
bool hasFinished[MaxNumber];
int  earliestFinishedTime[MaxNumber];
int N,M;
int findAvailbleWork()
{
    for( int i = 0 ; i < N ; i++)//for every point
    {
        if(!hasFinished[i])//Requirenment1: if it hasn't been finished
        {
            //check whether it can start
            bool canStart = true;
            for(int j = 0 ; j < N ; j++)
            {
                if(procedureTime[j][i] > 0)//this job still has a preprocess
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
    hasFinished[procedureDoing] = true;
    for(int i =0;i<N;i++)
    {
        if(procedureTime[procedureDoing][i] > 0)
        {
            if( earliestFinishedTime[procedureDoing] + procedureTime[procedureDoing][i] > earliestFinishedTime[i]   )
            {
                earliestFinishedTime[i] = earliestFinishedTime[procedureDoing] + procedureTime[procedureDoing][i];
            }
            procedureTime[procedureDoing][i] = -1;
        }
    }
}
bool allProcedureDone()
{
    for( int i = 0 ; i < N ; i++)//for every point
    {
        if(!hasFinished[i])
        {
            return false;
        }
    }
    return true;
}
int fingLongestTime()
{
    int longestTime = earliestFinishedTime[0];
    for( int i = 1 ; i < N ; i++)//for every point
    {
        if( earliestFinishedTime[i] > longestTime )
        {
            longestTime = earliestFinishedTime[i];
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
        hasFinished[i] = false;
        earliestFinishedTime[i] = 0;
        for(int j = 0 ; j < N; j++)
        {
            procedureTime[i][j] = -1;
        }
    }
    int x,y,time;
    //inserting the edges, the work procedure
    for(int i=0;i<M;i++)
    {
        cin>>x>>y>>time;
        procedureTime[x][y] = time;
    }
    work();
    return 0;
}