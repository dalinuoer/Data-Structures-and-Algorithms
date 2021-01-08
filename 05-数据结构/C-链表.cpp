/*
* 链表的应用
* Author: Qin Hao
* Date: 2020/9/28
* Note: 
*/

/*******动态链表*******/

struct node
{
    typename data;
    node *next;
};

node *p = (node *)malloc(sizeof(node));
free(p);

node *p = new node;
delete (p);

// 创建链表
node *create(int Array[], int arraySize)
{
    node *p, *pre, *head;

    head = new node;
    head->next = nullptr;
    pre = head;

    for (int i = 0; i < arraySize; ++i)
    {
        p = new node;
        p->data = Array[i];
        p->next = nullptr;
        pre->next = p;
        pre = p;
    }
    return head;
}

// 查找元素
node *search(node *head, int x)
{
    node *p = head->next;
    while (p != nullptr)
    {
        if (p->data == x)
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

// 插入元素
void insert(node *head, int pos, int x)
{
    node *p = head;
    for (int i = 0; i < pos - 1; ++i)
    {
        p = p->next;
    }

    node *q = new node;
    q->data = x;
    q->next = p->next;
    p->next = q;
}

// 删除元素
void del(node *head, int x)
{
    node *p = head->next;
    node *pre = head;
    while (p != nullptr)
    {
        if (p->data == x)
        {
            pre->next = p->next;
            delete (p);
            p = p->next;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}

/*******静态链表*******/

// 如果结点的地址比较小，这样就没必要去建立动态链表，而应直接使用方便得多的静态链表

// 静态链表的实现原理是hash，即通过建立一个结构体数组，并令数组的下标直接表示节点的地址
// 来达到直接访问数组中的元素就能访问节点的效果

// 另，由于结点的访问非常方便，所以不需要头节点

struct Node
{
    typename data;
    int next;
} node[size];
// 在使用静态链表时，尽量不要把结构体类型名和结构体变量名取成相同的名字

// 一类问题的通用解题步骤：
// 1. 定义静态链表
struct Node
{
    int address;
    typename data;
    int next;
    xxx; // 结点的某个性质，不同的题目会有不同的设置
} node[maxn];
// 2. 在程序的开始，对静态链表进行初始化。一般来说需要对定义中的xxx进行初始化，
//    将其定义为正常情况下达不到的数字
for (int i = 0; i < maxn; ++i)
{
    node[i].xxx = x;
}
// 3. 题目一般都会给出一条链表的首结点地址，那么我们可以依据这个地址来遍历得到整条链表
//    需注意的是，这一步的同时也是我们对结点的性质xxx进行标记、并且对有效节点的个数进行计数的时候
int p = begin, count = 0;
while (p != -1)
{
    xxx = 1;
    ++count;
    p = node[p]->next;
}
// 4.
// TODO: