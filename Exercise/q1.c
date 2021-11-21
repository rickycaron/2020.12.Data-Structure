// 01-复杂度1 最大子列和问题 (20 分)
// 给定K个整数组成的序列{ N1, N 2 , ..., NK}，“连续子列”被定义为{ Ni, Ni+1, ..., Nj​}，其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。
// 本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：
// 数据1：与样例等价，测试基本正确性；
// 数据2：102个随机整数；
// 数据3：103个随机整数；
// 数据4：104个随机整数；
// 数据5：105个随机整数；
// 输入格式:
// 输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

// 输出格式:
// 在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

// 输入样例:
// 6
// -2 11 -4 13 -5 -2
// 输出样例:
// 20
// 结尾无空行

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000

//the most stupid method
int MaxSubseqSum1(int a[],int n)
{
    int thisSum, maxSum = 0;
    for( int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            thisSum = 0;
            for(int k = i ; k <=j ; k++)
            {
                thisSum +=a[k];
                if(thisSum > maxSum)
                    maxSum = thisSum;
            }
        }
    }
    return maxSum;
} 

//the most stupid method
int MaxSubseqSum2(int a[],int n)
{
    int thisSum, maxSum = 0;
    for( int i = 0 ; i < n ; i++)
    {
        thisSum = 0;
        for(int j = i ; j < n ; j++)
        {
            thisSum +=a[j];
            if(thisSum > maxSum)
                maxSum = thisSum;            
        }
    }
    return maxSum;
} 

int MaxSubseqSum4(int a[],int n)
{
    int thisSum, maxSum = 0;
    for( int i = 0 ; i < n ; i++)
    {
        thisSum +=a[i];
        if(thisSum > maxSum)
            maxSum = thisSum; 
        else if(thisSum < 0)
        {
            thisSum = 0;
        }
    }
    return maxSum;
} 

int Max3(int A, int B, int C){
    return A>B?(A>C?A:C):(B>C?B:C);
}

int DivideAndConquer(int List[],int left,int right)
{
    int MaxLeftSum, MaxRightSum;
    int MaxLeftBorderSum, MaxRightBorderSum;
    
    int LeftBorderSum, RightBorderSum;
    int center,i;
    
    if(left==right){
        if(List[left]>0) return List[left];
        else return 0;
    }
    
    center = (left + right)/2;
    MaxLeftSum = DivideAndConquer(List, left,center);
    MaxRightSum = DivideAndConquer(List,center+1,right);
    
    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for( i = center;i>=left;i--)
    {
        LeftBorderSum +=List[i];
        if(LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for(i = center+1;i<=right;i++)
    {
        RightBorderSum +=List[i];
        if(RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    
    return Max3(MaxLeftSum,MaxRightSum,MaxLeftBorderSum+MaxRightBorderSum);
}
int MaxSubseqSum3(int a[],int n)
{
    return DivideAndConquer(a,0,n-1);
}

int main()
{
    int a[N],K;
    scanf("%d",&K);
    for(int i = 0 ; i < K;i++)
    {
        scanf("%d",&a[i]);
    }
//     printf("MaxSubseqSum1 = %d\n",MaxSubseqSum1(a,K));
//     printf("MaxSubseqSum2 = %d\n",MaxSubseqSum1(a,K));
//      printf("MaxSubseqSum4 = %d\n",MaxSubseqSum4(a,K));
    
    
//     printf("%d", MaxSubseqSum1(a,K));
//     printf("%d", MaxSubseqSum2(a,K));
    printf("%d", MaxSubseqSum3(a,K));
//     printf("%d", MaxSubseqSum4(a,K));
    
    return 0 ;
}