// 02-线性结构2 一元多项式的乘法与加法运算 (20 分)
// 设计函数分别求两个一元多项式的乘积与和。

// 输入格式:
// 输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

// 输出格式:
// 输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

// 输入样例:
// 4 3 4 -5 2  6 1  -2 0
// 3 5 20  -7 4  3 1
// 结尾无空行
// 输出样例:
// 15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
// 5 20 -4 4 -5 2 9 1 -2 0

#include <stdio.h>
#include <stdlib.h>

struct PolyNode
{
    int coef; // coeffient
    int expon; // exponential
    struct PolyNode * next; // point to the next PolyNode
};
typedef struct PolyNode * Polynomial;

//將一個新的結點（項），添加在rear指向的項的後面
void attach(int c, int e, Polynomial * rear)
{
    Polynomial p;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->coef = c;
    p->expon = e;
    p->next = NULL;
    (*rear)->next = p;
    *rear = p;
}
//按照規定的格式讀入一個多項式
Polynomial readPoly()
{
    Polynomial p,rear;
    int n,c,e;
    scanf("%d", &n);
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->next = NULL;
    rear = p;
    while(n--)
    {
        scanf("%d %d", &c,&e);
        attach(c,e,&rear);
    }
    Polynomial temp = p;
    p = p->next;
    free(temp);
    return p;
}

int compare(int e1, int e2)
{
    if(e1==e2) return 0;
    else if(e1 > e2) return 1;
    else return -1;
}

Polynomial add(Polynomial p1,Polynomial p2)
{
    int sum;
    Polynomial rear = (Polynomial)malloc(sizeof(struct PolyNode));
    Polynomial front = rear;
    while(p1 && p2)
    {
        switch(compare(p1->expon,p2->expon))
        {
            case 1:
                attach(p1->coef,p1->expon,&rear);
                p1 = p1->next;
                break;
            case -1:
                attach(p2->coef,p2->expon,&rear);
                p2 = p2->next;
                break;
            case 0:
                sum = p1->coef + p2->coef;
                if(sum)
                    attach(sum,p1->expon,&rear);
                p1=p1->next;
                p2=p2->next;
                break;
        }
    }
    while(p1)
    {
        attach(p1->coef,p1->expon,&rear);
        p1 = p1->next;
    }
    while(p2)
    {
        attach(p2->coef,p2->expon,&rear);
        p2 = p2->next;
    }
    //刪掉空的頭結點
    rear->next = NULL;
    Polynomial temp = front;
    front = front -> next;
    free(temp);
    return front;
}

Polynomial mult(Polynomial p1, Polynomial p2)
{
    if(!p1||!p2){return NULL;}
    
    int c,e;
    Polynomial p = (Polynomial)malloc(sizeof(struct PolyNode));
    Polynomial rear = p;
    Polynomial temp1 = p1;
    Polynomial temp2 = p2;
    Polynomial temp;
    //首先把p1的第一項和p2整個乘一遍，得到一個最初的多項式
    while(temp2)
    {
        attach(temp1->coef * temp2->coef, temp1->expon + temp2->expon,&rear);
        temp2 = temp2 ->next;
    }
    temp1 = temp1 -> next;
    // 然後對於p1剩下的每一項，每一項都乘p2
    while(temp1)
    {
        temp2 = p2;
        rear = p;
        while(temp2)
        {
            e = temp1->expon + temp2 ->expon;
            c = temp1->coef * temp2->coef;
            //對於得到的一個結果，找到次數不大於它的第一項
            while(rear->next && rear->next->expon > e)
                rear = rear->next;
            //然後把這一項添加在這裡
            //如果已經存在了這種次數的項
            if(rear->next && rear->next->expon == e)
            {
                //第一種情況，有一項次數相同的，直接係數相加
                if(rear->next->coef+c)
                    rear->next->coef +=c;
                //第二種情況，相加以後抵消了，就刪掉這一項
                else
                {
                    Polynomial temp = rear->next;
                    rear->next = temp->next;
                    free(temp);
                }
            }
            //不然不存在這種次數的項，就新建一個
            else
            {
                temp = (Polynomial)malloc(sizeof(struct PolyNode));
                temp->coef = c;
                temp->expon = e;
                temp->next = rear->next;
                rear->next = temp;
                rear = rear->next;
            }
            temp2 = temp2->next;       
        }
        temp1 = temp1->next;
    }
    //刪掉頭結點
    temp2 = p;
    p = p->next;
    free(temp2);
    return p;
}

void printPoly(Polynomial p)
{
    if(p==NULL)
    {
        printf("0 0\n");
        return;
    }
    //這個地方的flag是為了在第一次while循環的時候，不打印空格，之後每次while循環都打印一個空格
    int flag = 0;
    while(p)
    {
        if(!flag)
            flag =1;
        else
            printf(" ");
        
        printf("%d %d",p->coef,p->expon);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    Polynomial P1,P2,PP,PS;
    
    P1 = readPoly();
    P2 = readPoly();
    
    PP = mult(P1,P2);
    printPoly(PP);
    
    PS = add(P1,P2);
    printPoly(PS);
    return 0;
}