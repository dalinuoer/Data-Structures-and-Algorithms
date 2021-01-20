/**
 * @file b-二叉树的遍历.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 二叉树的遍历是指通过一定的顺序访问二叉树的所有结点。

// 遍历的方法一般有四种：先序遍历、中序遍历、后序遍历以及层次遍历。
// 其中前三种一般使用深度优先搜索（DFS）实现，而层次遍历一般使用广度优先搜索（BFS）实现。

// 所谓“先中后”，都是指根结点 root 在遍历中的位置。

/****** 1. 先序遍历 ******/

// 递归式：根结点 --> 左子树 --> 右子树
// 递归边界：子树为空

void preOrder(node *root)
{
    if (root == nullptr) // 达到空树（递归边界）
    {
        return;
    }
    // 访问根结点 root，此处是打印数据
    printf("%d\n", root->data);
    // 访问左子树
    preOrder(root->lchild);
    // 访问右子树
    preOrder(root->rchild);
}

// 先序遍历序列的性质：由于先序遍历先访问根结点，因此对一棵二叉树的先序遍历序列，序列的第一个一定是根结点。

/****** 2. 中序遍历 ******/

// 递归式：左子树 --> 根结点 --> 右子树
// 递归边界：子树为空

void inOrder(node *root)
{
    if (root == nullptr) // 达到空树（递归边界）
    {
        return;
    }
    // 访问左子树
    preOrder(root->lchild);
    // 访问根结点 root，此处是打印数据
    printf("%d\n", root->data);
    // 访问右子树
    preOrder(root->rchild);
}

// 中序遍历序列的性质：由于中序遍历总是把根结点放在左子树和右子树中间，因此只要知道根结点，
// 就可以通过根结点在中序遍历中的位置区分出左子树和右子树。

/****** 3. 后序遍历 ******/

// 递归式：左子树 --> 右子树 --> 根结点
// 递归边界：子树为空

void postOrder(node *root)
{
    if (root == nullptr) // 达到空树（递归边界）
    {
        return;
    }
    // 访问左子树
    preOrder(root->lchild);
    // 访问右子树
    preOrder(root->rchild);
    // 访问根结点 root，此处是打印数据
    printf("%d\n", root->data);
}

// 后序遍历序列的性质：后序遍历总是把根结点放在最后访问，这和先序遍历相反，因此对后序遍历序列来说，
// 序列的最后一个一定是根结点。

// 总的来说，无论是先序遍历序列还是后序遍历序列，都必须知道中序遍历序列才能唯一的确定一棵树。

/****** 4. 层序遍历 ******/
// 层序遍历是指按层次的顺序从根节点向下逐层进行遍历，且对同一层的结点为从左到右遍历。
// 层次遍历相当于是对二叉树从根节点开始的广度优先搜索

void layerOrder(node *root)
{
    queue<node *> q; // 队列里边存的是地址
    q.push(root);    // 根结点地址入队
    while (!q.empty())
    {
        node *now = q.front(); // 取出队首元素
        q.pop();
        printf("%d\n", now->data);
        if (now->lchild != nullptr)
            q.push(now->lchild); // 左子树非空
        if (now->rchild != nullptr)
            q.push(now->rchild); // 右子树非空
    }
}

// 许多题目要求计算出每个结点所处的层次，这时需要在二叉树结点的定义中添加一个记录层次 layer 的变量
struct node
{
    int data;     // 数据域
    int layer;    // 层次
    node *lchild; // 左指针域
    node *rchild; // 右指针域
};
// 需要在根结点入队前就先令根结点的 layer 为 1 来表示根结点是第一层，之后在 now->lchild 和
// now->rchild 入队前，把它们的层号记为结点 now 的层号加 1.
void layerOrder(node *root)
{
    queue<node *> q; // 队列里边存的是地址
    root->layer = 1; // 根结点的层号为 1
    q.push(root);    // 根结点地址入队
    while (!q.empty())
    {
        node *now = q.front(); // 取出队首元素
        q.pop();
        printf("%d\n", now->data);
        if (now->lchild != nullptr) // 左子树非空
        {
            now->lchild->layer = now->layer + 1; // 左孩子的层号为当前层号 +1
            q.push(now->lchild);
        }
        if (now->rchild != nullptr) // 右子树非空
        {
            now->rchild->layer = now->layer + 1; // 右孩子的层号为当前层号 +1
            q.push(now->rchild);
        }
    }
}

/****** 5. 一个重要的问题 ******/

// 给定一棵二叉树的先序遍历序列和中序遍历序列，重建这棵二叉树。

// 当前先序序列区间为 [preL, preR]，中序序列区间为 [inL. inR]，返回根结点地址
node *create(int preL, int preR, int inL, int inR)
{
    if (preL > preR) // 先序序列长度小于等于 0， 直接返回
    {
        return nullptr;
    }

    node *root = new node;  // 新建一个新的结点，用来存放当前二叉树的根结点
    root->data = pre[preL]; // 新结点数据域为根结点的值
    int k;
    // 在中序序列中寻找根结点位置
    for (k = inL; k <= inR; ++k)
    {
        if (in[k] == pre[preL])
        {
            break;
        }
    }
    int numLeft = k - inL; // 左子树结点个数

    // 左子树的先序区间为 [preL + 1, preL + numLeft]，中序区间为 [inL, k - 1]
    // 返回左子树的根结点地址，赋值给 root 的左指针
    root->lchild = create(preL + 1, pre + numLeft, inL, k - 1);

    // 右子树的先序区间为 [preL + numLeft + 1, preR]，中序区间为 [k + 1, inR]
    // 返回右子树的根结点地址，赋值给 root 的右指针
    root->rchild = create(preL + numLeft + 1, preR, k + 1, inR);

    return root; // 返回根结点地址
}

// 结论：中序序列可以与先序序列、后序序列、层序序列中的任意一个来构建唯一的二叉树，而后三者两两搭配
// 或者是三个一起上都无法构建一棵二叉树。
// 原因是：先序、后序、层序均是提供根结点，作用是相同的，都必须由中序序列来区分左右子树。
