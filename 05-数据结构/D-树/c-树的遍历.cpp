/**
 * @file c-树的遍历.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-19
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

/****** 0. 树的静态写法 ******/

struct node 
{
    int layer; // 记录层号
    typename data; // 数据域
    vector<typename> child; // 指针域，存放所有子结点的下标
} Node[maxn];

/****** 1. 树的先根遍历 ******/

// 思路与二叉树的先根遍历类似
void preOrder(int root)
{
    printf("%d\n", Node[root].data);
    for (int i = 0; i < Node[root].child.size(); ++i) // 递归边界
    {
        preOrder(Node[root].child[i]); // 递归式
    }
}

/****** 2. 树的层序遍历 ******/

void layerOrder(int root)
{
    queue<int> q;
    q.push(root);
    Node[root].layer = 0; // 根结点层号为 0
    while (!q.empty())
    {
        int front = q.front();
        printf("%d\n", Node[front].data);
        q.pop();
        for (int i = 0; i < Node[front].child.size(); ++i)
        {
            int child = Node[front].child[i]; // 当前结点的第 i 个子结点的编号
            Node[child].layer = Node[front].layer + 1;
            q.push(Node[front].child[i]);
        }
    }
}

/****** 3. 从树的遍历看 DFS 与 BFS ******/

// 事实上,对所有合法的 DFS 求解过程,都可以把它画成树的形式,对这棵树的 DFS 遍历过程就是树的先根遍历过程.

// 对所有合法的 BFS 的求解过程,都可以像 DFS 中那样画出一棵树,并且将广度优先搜索问题转换为树的层序遍历问题.

