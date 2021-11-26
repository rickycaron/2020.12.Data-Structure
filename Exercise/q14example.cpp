//小顶堆的建立 查找
#include <iostream>
#include <vector>
using namespace std;
//还是C++比较好用，用vector不用担心容量和size，还可以直接交换元素，不需要为了节省运算成本而空出位置来，也可以函数重载，C什么函数都没有，typedef麻烦，太麻烦了
class tnode{
public:
    string c{""};
    int f{0};
    tnode* left{nullptr};
    tnode* right{nullptr};
    tnode()=default;
    tnode(string c_,int f_):c{c_},f{f_}{};
};
class minHeap{//小顶堆
public:
    vector<tnode*> heap;
    minHeap(){}
    int getSize(){return heap.size();}
    void build(vector<tnode*> list,int n)
    {
        for(int i=0;i<n;i++)
        {
            insertNode(list[i]);
        }
    }
    void insertNode(tnode* newnode)
    {
        heap.push_back(newnode);
        adjustFromBack();
    }
    void insertNode(string c,int f)
    {
        tnode* newnode =new tnode{c,f};
        heap.push_back(newnode);
        adjustFromBack();
    }
    tnode* popMinNode()
    {
        tnode* temp{nullptr};
        if(heap.size()){
            temp = heap.front();
            swap(heap.front(), heap.back());
            heap.pop_back();
            adjustFromFront();
        }
        return temp;
    }
    void adjustFromBack(){
        for(int i=getSize()-1;i>=0&&getSize()>1;i--){
            if( heap[i]->f < heap[(i-1)/2]->f ){//因为是从0开始存，所以父节点为i，左右儿子为21+1，21+2；儿子为i，父节点是（i-1）/2
                swap(heap[i], heap[(i-1)/2]);
            }
        }
    }
    void adjustFromFront(){
        for(int i=1;i<getSize()&&getSize()>1;i++){
            if(heap[i]->f < heap[(i-1)/2]->f){
                swap(heap[i], heap[(i-1)/2]);
            }
        }
    }
};

class huffmanTree{
public:
    huffmanTree()=default;
    tnode* root;
    void create(minHeap &minheap){
        tnode* n1,*n2,*newnode;
        int size=minheap.getSize();
        for(int i=0;i<size-1;i++){//一共循环N-1次
            n1 = minheap.popMinNode();
            n2 = minheap.popMinNode();
            newnode = new tnode{"",n1->f + n2->f};
            newnode->left = n1;
            newnode->right = n2;
            minheap.insertNode(newnode);
        }
        newnode = minheap.heap.front();
        root=newnode;
    }
    int WPL(tnode* p,int depth){
        if(!p->left&&!p->right) return p->f*depth;
        return WPL(p->left, depth+1) + WPL(p->right, depth+1);
    }
    int getWPL(){
        return WPL(root, 0);
    }
};

bool judge(int wpl,vector<tnode*>list){
    bool flag=true;
    int wplOfTest{0};
    string c,code;
    tnode* head=new tnode;
    tnode* tail=head;
    tnode* temp;
    //对于每一个哈夫曼码
    for(int i=0;i<list.size();i++)
    {
        cin >> c >> code;
        if(!flag)continue;//;
        wplOfTest+=(list[i]->f*code.size());
        for(auto i=code.begin();i!=code.end();i++)
        {
            //根据给定的哈夫曼码建立二叉哈夫曼树，左儿子为0，右儿子为1，每一个叶节点为可以为码，中间节点不可为码
            //对每一码开始建立二叉树，看看最后停在了什么地方
            //只有停在之前没有到过的叶节点，这个码才是可以使用的
            //以下两种情况都是不行的，直接返回false
            //停在了中间
            //停在了已经建立的节点
            if(*i=='0')
            {
                if(!tail->left)
                {
                    temp = new tnode;
                    tail->left=temp;
                }
                tail=tail->left;
            }
            else if(*i=='1')
            {
                if(!tail->right)
                {
                    temp=new tnode;
                    tail->right=temp;
                }
                tail=tail->right;
            }

            if(tail->f)
            {
                flag=false;
                break;
            }
        }
        if(tail->left||tail->right)
        {
            flag=false;
            continue;
        }
        tail->f=list[i]->f;
        tail->c=list[i]->c;
        tail=head;
    }
    if(wplOfTest!=wpl)
        return false;
    else 
        return flag;
}

int main(){
    int n,m,WPL;
    string c;
    int f;
    cin >> n;
    vector<tnode*> alpha;
    for(int i=0;i<n;i++){
        cin >> c >> f;
        tnode *newnode=new tnode{c,f};
        alpha.push_back(newnode);
    }
    minHeap minheap;
    minheap.build(alpha,n);
    huffmanTree ht;
    ht.create(minheap);
    WPL=ht.getWPL();
    cin >> m;
    for(int i=0;i<m;i++){
        if(judge(WPL,alpha)){
            cout << "Yes"<<endl;
        }else{
            cout << "No"<<endl;
        }
    }
    return 0;
}