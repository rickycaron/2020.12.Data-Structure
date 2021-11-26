#include <stdio.h>
#include <stdlib.h>
#define MaxSize 63
typedef struct TreeNode* HuffmanTree;
struct TreeNode{
    int weight;
    char charachter;
    HuffmanTree left;
    HuffmanTree right;
};
HuffmanTree minHeap [MaxSize];
int weights [MaxSize];

int N, M;
int size = 1;

void insertMinHeap(HuffmanTree T);
HuffmanTree deleteMin();
HuffmanTree buildHuffmanTree();
int calculateWPL(HuffmanTree T, int height );
int length(char string []);
int main()
{
    scanf("%d\n",&N);
    char charachter;
    int weight;
    for(int i =0; i<N;i++)
    {
        scanf("%c %d ",&charachter,&weight);
        HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));
        T->weight = weight;
        T->charachter = charachter;
        T->left = NULL;
        T->right = NULL;
        insertMinHeap(T);
        weights[i] = weight;
    }
    HuffmanTree T = buildHuffmanTree();
    int minWPL = calculateWPL(T,1);
    scanf("%d\n",&M);
    char string[64];
    for(int i = 0 ; i < M ; i++)
    {
        int wpl = 0;
        for(int j = 0 ; j < N ; j++)
        {
            scanf("%c %s\n", &charachter,string);
            wpl = wpl + weights[j] * length(string);
        }
        if(wpl == minWPL)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

void insertMinHeap(HuffmanTree T)
{
    size++;
    int i = size; 
    for( ;  i/2 > 0 && minHeap[i/2]->weight > T->weight ; i=i/2)
        minHeap[i] = minHeap[i/2];
    minHeap[i] = T;
    return;
}
// HuffmanTree deleteMin()
// {
//     if(size == 0)
//         return NULL;
//     HuffmanTree minNode = minHeap[0];
//     int i = 0;
//     int tempWeight = minHeap[size-1]->weight;
//     int minweight;
//     int index;
    
//     while(2*i+1 < size)
//     {
//         if(2*i+2 < size)
//         {
//             //two childs
//             minweight = (minHeap[2*i+1]->weight < minHeap[2*i + 2]->weight) ? minHeap[2*i+1]->weight : minHeap[2*i + 2]->weight;
//             index = (minHeap[2*i+1]->weight < minHeap[2*i + 2]->weight) ? 2*i+1 : 2*i+2;
//             if(tempWeight < minweight )
//                 break;
//             else
//             {
//                 minHeap[i] = minHeap[index];
//                 i = index;
//             }
//         }
//         else
//         {
//             //only one child
//             if(tempWeight < minHeap[2*i+1]->weight)
//                 break;
//             else
//             {
//                 minHeap[i] = minHeap[2*i+1];
//                 i = i*2+1;
//             }
//         }
//     }
//     minHeap[i] = minHeap[size-1];
//     minHeap[size-1] = NULL;
//     size--;
//     return minNode;
// }
HuffmanTree deleteMin()
{
    if(size == 1)
        return;
    int parent, child;
    HuffmanTree minNode = minHeap[1];
    int tempWeight = minHeap[size]->weight;
    size--;
    for(parent = 1; parent*2 <= size;parent = child)
    {
        child = parent*2;
        if((child != size) && minHeap[child]->weight < minHeap[child+1]->weight )
            child++;
        if(tempWeight <= minHeap[child])
            break;
        else
            minHeap[parent] = minHeap[child];
    }
    minHeap[parent] = minHeap[size];
    minHeap[size] = NULL;
    return minNode;
}

HuffmanTree buildHuffmanTree()
{
    HuffmanTree T;
    for(int i = 1 ; i < N ; i++)//size - 1 times combination
    {
        T = malloc(sizeof(struct TreeNode));
        T->left = deleteMin();
        T->right = deleteMin();
        T->weight = T->left->weight + T->right->weight;
        insertMinHeap(T);
    }
    return deleteMin();
}
int calculateWPL(HuffmanTree T, int height )
{
    if(T->left == NULL && T->right == NULL)
        return (T->weight * height);
    int wpl = 0;
    if(T->left != NULL)
        wpl = wpl + calculateWPL(T->left,height+1);
    if(T->right != NULL)
        wpl = wpl + calculateWPL(T->right,height+1);
    return wpl;
}
int length(char string [])
{
    for(int i = 0 ; i < 64; i++)
    {
        if(string[i] == 48 || string[i] == 49)
            string [i] = 0;
        else
            return i;
    }
}
