#include <stdio.h>
#define MaxNumber 1001
#define MinValue -10001
int minHeap[MaxNumber];

void readInput(int N);
void adjustMinHeap(int N);
int Min(int a,int b);
void switchNode(int a, int b);
void printRoute(int index);
void insert(int M);
int main()
{
    int N;
    int M;
    scanf("%d %d\n", &N, &M);
//     readInput(N);
//     adjustMinHeap(N);
    minHeap[0] = MinValue;
    insert(N);
    int index;
    for(int i = 0 ;i< M;i++)
    {
        scanf("%d ", &index);
        printRoute(index);
    }
    return 0;
}
//一个一个地把元素插入堆中，简单但是不太高效
void insert(int M)
{
    int temp;
    int size = 0;
    for(int i = 1; i <= M ; i++)
    {
        scanf("%d",&temp);
        int fillingplace;
        for(fillingplace = size+1; minHeap[fillingplace/2] > temp;fillingplace/=2)
            minHeap[fillingplace] = minHeap[fillingplace/2];
  
        minHeap[fillingplace] = temp;
        size++;
    }
    return;   
}
void printRoute(int index)
{
    int firstLetter = 1;
    while(index > 0)
    {
        if(firstLetter)
        {
            printf("%d", minHeap[index]);
            firstLetter = 0;
        }
        else
        {
            printf(" %d", minHeap[index]);
        }
            index = index/2;
    }
    printf("\n");
}
//这种方法是先把所有的元素插入，然后再调整成最小堆，代码比较复杂，而且最后形成的堆和用上一种方法的不一样，打印出来的路径不同，编译不嫩那个通过，所以舍弃此法
// void readInput(int N)
// {
//     minHeap[0] = -1005;
//     for(int i = 1; i <= N; i++)
//     {   
//         scanf("%d ", &(minHeap[i]));
//     }
// }
// void adjustMinHeap(int N)
// {
//     int i = N/2;
//     int temp;
//     int lastSwitch;
//     //浮
//     while(i >= 1)
//     {
//         if(2*i+1 <= N)
//         {
//             //has two childs
//             temp = Min(2*i,2*i+1);
//             if(  minHeap[i] > minHeap[temp] )
//             {
//                 switchNode(i,temp);
//                 lastSwitch = temp;
//             }
//             if(minHeap[2*i] < minHeap[2*i+1])
//                 switchNode(2*i, 2*i+1);
//         }
//         else
//         {
//             //has only one child
//             if(minHeap[2*i] < minHeap[i])
//             {
//                 switchNode(i,2i);
//                 lastSwitch = 2i;
//             }
//         }
//         i = i - 1;
//     }
//     //沉
//     if( lastSwitch == 2 || lastSwitch == 3)
//     {
//         i = lastSwitch;
//         while(i<=N/2)
//         {
//             if(2*i+1 > N)
//             {
//                 //only one child
//                 if(minHeap[2*i] < minHeap[i])
//                 {
//                     switchNode(i,2*i);
//                     i = 2*i;
//                 }
//             }
//             else
//             {
//                 //has two childs
//                 temp = Min(2*i,2*i+1);
//                 if(  minHeap[i] > minHeap[temp] )
//                 {
//                     switchNode(i,temp);
//                     if(minHeap[2*i] < minHeap[2*i+1])
//                         switchNode(2*i, 2*i+1);
//                     i = temp;
//                 }
//                 else
//                     break;
//             }
//         }
//     }
//     return;
// }
// int Min(int a,int b)
// {
//     return (minHeap[a] < minHeap[b]?a:b);
// }
// void switchNode(int a, int b)
// {
//     int temp = minHeap[a];
//     minHeap[a] = minHeap[b];
//     minHeap[b] = temp;
// }

// void insert(int M)
// {
//     int temp;
//     for(int i = 1; i <= M ; i++)
//     {
//         scanf("%d",&temp);
//         int fillingplace = i;
//         while(fillingplace > 1 && minHeap[fillingplace/2] > temp)
//         {
//             minHeap[fillingplace] = minHeap[fillingplace/2];
//             fillingplace/=2;
//         }
//         minHeap[fillingplace] = temp;
//     }
//     return;   
// }
