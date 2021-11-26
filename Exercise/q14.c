#include <stdio.h>
#define MaxSize 63
typedef struct TreeNode* HuffmanTree;
struct TreeNode{
    int weight;
    char charachter;
    HuffmanTree left;
    HuffmanTree right;
}
HuffmanTree minHeap [MaxSize];

int N, M;
int size = 0;

void insertMinHeap(char charachter,int frequency);
HuffmanTree deleteMin();
HuffmanTree buildHuffmanTree();
int calculateWPL(HuffmanTree T);

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
        T->left = nullptr;
        T->right = nullptr;
        insertMinHeap(T);
    }
    HuffmanTree T = buildHuffmanTree();
    int minWPL = calculateWPL(T);
    
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
HuffmanTree deleteMin()
{
    HuffmanTree minNode = minHeap[0];
    int i = 0;
    int tempWeight = minHeap[size-1]->weight;
    int minweight;
    int index;
    
    while(2*i < size)
    {
        if(2*i+1 < size)
        {
            //two childs
            minweight = (minHeap[2*i]->weight < minHeap[2*i + 1]->weight) ? minHeap[2*i]->weight : minHeap[2*i + 1]->weight;
            index = (minHeap[2*i]->weight < minHeap[2*i + 1]->weight) ? 2*i : 2*i+1;
            if(minweight < tempWeight)
                break;
            else
            {
                minHeap[i] = minHeap[index];
                i = index;
            }
        }
        else
        {
            //only one child
            if(tempWeight < minHeap[2*i]->weight)
                break;
            else
            {
                minHeap[i] = minHeap[2*i];
                i = i*2;
            }
        }
    }
    minHeap[i] = minHeap[size-1];
    minHeap[size-1] = nullptr;
    size--;
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
    return deleteMin()
}
int calculateWPL(HuffmanTree T)
{
    int wpl = 0;
    if(T->left == nullptr && T->right = nullptr)
}