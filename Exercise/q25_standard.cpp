#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

typedef int ElementType;

//判断两个数组是否一样
bool JudgeTheSame(int origin[],int changed[],int len) 
{
    for(int i=0;i<len;i++)
    {
        if(origin[i]!=changed[i])
            return false;
    }
    return true;
}

//进行一次插入排序，参数：待排序数组，数组长度，当前排序次数，已有序元素Nums-1个
void InsertSort(ElementType origin[],int N,int Nums)
{
    int i;
    ElementType temp=origin[Nums]; //取出未排序列中的第一个元素
    for(i=Nums;i>0&&origin[i-1]>temp;i--)
    {
        origin[i]=origin[i-1];   //从小到大排序，未找到插入位置，元素依次向后移动
    }
    origin[i]=temp;
}

void Insert_Sort(int origin[],int N,int changed[])
{
    for(int i=1;i<N;i++) //从第二个元素开始插入排序
    {
        InsertSort(origin,N,i);
        if(JudgeTheSame(origin,changed,N)) //一轮插入排序后判断结果
        {
            cout<<"Insertion Sort"<<endl;
            InsertSort(origin,N,i+1);
            for(int j=0;j<N-1;j++)
                cout<<origin[j]<<" ";
            cout<<origin[N-1]<<endl;
            return;
        }
    }
}

/*L=左边的起始位置，R=右边起始位置，RightEnd=右边终点位置*/
void Merge(ElementType A[],ElementType TempA[],int L,int R,int RightEnd)
{
    /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd=R-1;
    int temp=L; //有序序列的起始位置
    int NumElements=RightEnd-L+1;
    
    while(L<=LeftEnd&&R<=RightEnd)
    {
        if(A[L]<=A[R])
            TempA[temp++]=A[L++]; /*注意下标的使用temp*/
        else 
            TempA[temp++]=A[R++];
    }
    while(L<=LeftEnd)
        TempA[temp++]=A[L++];
    while(R<=RightEnd)
        TempA[temp++]=A[R++];
    
    //for(int i=0;i<NumElements;i++,RightEnd--) //由于L，R等数组下标已经改变，RightEnd没有变
    //    A[RightEnd]=TempA[RightEnd]; //拷贝数据到原始数组中
}

/*length = 当前有序子列的长度，两两归并相邻有序子列*/
void Merge_pass(ElementType A[],ElementType TempA[],int N,int length)
{
    int i,j;
    for(i=0;i<=N-2*length;i+=2*length)
        Merge(A,TempA,i,i+length,i+2*length-1);
    if(i+length<N)  //归并最后2个子列
        Merge(A,TempA,i,i+length,N-1);
    else  //最后只剩一个子列
    {
        for(j=i;j<N;j++)
            TempA[j]=A[j];
    }
}

void Merge_Sort(ElementType A[],int N,int changed[])
{
    int length=1; //初始化子序列长度
    ElementType *TempA;
    TempA=(ElementType*)malloc(N*sizeof(ElementType)); //提前分配好空间
    
    if(TempA!=NULL)
    {
        while(length<N)
        {
            Merge_pass(A,TempA,N,length);
            if(JudgeTheSame(TempA,changed,N)) //归并排序后的结果
            {
                cout<<"Merge Sort\n";
                length*=2;
                Merge_pass(TempA,A,N,length); //再归并一次,交换了顺序,节约空间，反复利用A,TempA
                for(int i=0;i<N-1;i++)
                    cout<<A[i]<<" ";
                cout<<A[N-1]<<endl;
                return;
            }
            
            length*=2;
            Merge_pass(TempA,A,N,length);
            if(JudgeTheSame(TempA,changed,N)) //归并排序后的结果
            {
                cout<<"Merge Sort\n";
                length*=2;
                Merge_pass(A,TempA,N,length); //再归并一次,交换了顺序
                for(int i=0;i<N-1;i++)
					cout << TempA[i] << " ";
				cout << TempA[N - 1] << endl;
                return;
            }
            
            length*=2;
        }
        free(TempA);
    }
    else
    {
        cout<<"空间不足"<<endl;
    }
}

int main()
{
    int N;
    int origin[105],origin_copy[105],changed[105];
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>origin[i];
        origin_copy[i]=origin[i];
    }
    
    for(int i=0;i<N;i++)  //中间排序结果
        cin>>changed[i];
    
    Insert_Sort(origin,N,changed);
    Merge_Sort(origin_copy,N,changed);
    
    return 0;
}
