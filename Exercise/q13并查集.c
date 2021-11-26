//root parent is -M, M is the number of element of this set
//the value of element is the same as the index of array

#include <stdio.h>

#define MaxSize 10000

typedef int ElementType;
typedef struct{
    ElementType data;
    int parent;
}setType;

setType s [MaxSize];
int N;

//return the root of an element, root is a valid node, larger than 0, whose parent is smalled than 0
int find(ElementType x)
{
    if(x>N)
        return -1;//do not exist!
    while(s[x].parent>0)
        x = s[x].parent;
    return x;
}
void unionSet(ElementType x1, ElementType x2)
{
    int root1 = find(x1);
    int root2 = find(x2);
    if( root1 == root2)
        return;//already in the same set
    else
    {   
        //the two noeds are not in the same tree, insert the smaller tree into the larger one
        if(s[root1].parent <= s[root2].parent)//root1 is larger than root2, insert root2 to root1
        {
            s[root1].parent = s[root1].parent + s[root2].parent;
            s[root2].parent = root1;
        }
        else if(s[root1].parent > s[root2].parent)//root2 is a larger set, insert root1 include
        {
            s[root2].parent = s[root2].parent + s[root1].parent;
            s[root1].parent = root2;
        }
    }
    return;
}
int checkIsConnected(ElementType x1, ElementType x2)
{
    int root1 = find(x1);
    int root2 = find(x2);
    if( root1 == root2)
        return 1;//in the same set
    else
        return 0;//not on the same set
}
int main()
{
    scanf("%d\n", &N);
    for(int i = 1; i <= N; i++)
    {
        s[i].data = i;
        s[i].parent = -1;
    }
    char operator;
    int temp1, temp2;
    scanf("%c ",&operator);
    while(operator!='S')
    {
        scanf("%d %d/n ",&temp1, &temp2);
        if(operator == 'C')
        {
            if(checkIsConnected(temp1,temp2))
                printf("yes\n");
            else
                printf("no\n");
        }
        else if(operator == 'I')
            unionSet(temp1,temp2);
        scanf("%c ",&operator);
    }
    int numberOfSet=0;
    for(int i = 1; i<=N;i++)
    {
        if(s[i].parent < 0)
            numberOfSet+=1;
    }
    if(numberOfSet == 1)
        printf("The network is connected.");
    else
        printf("There are %d components.", numberOfSet);
    return 0;
}