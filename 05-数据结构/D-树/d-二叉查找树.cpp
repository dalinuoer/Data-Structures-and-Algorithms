/**
 * @file d-二叉查找树.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 二叉查找树（Binary Search Tree，BST）
 * @version 0.1
 * @date 2021-02-08
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// ------ 1. 二叉查找树的定义 ------
// 一种特殊的二叉树，又名排序二叉树、二叉搜索树、二叉排序树。

// 递归定义如下：
// ① 要么二叉查找招数是一颗空树；
// ② 要么二叉查找树由根结点、左子树、右子树组成，其中左子树和右子树都是二叉查找树，且左子树上所有结点的数据域均小于或等于根结点的数据域，右子树上所有结点的数据域均大于根结点的数据域。

// ------ 2. 二叉查找树的基本操作 ------
// 基本操作有：查找、插入、建树、删除。

// --- 查找 ---
// 从树根到查找结点的一条路径,最坏的时间复杂度为 O(h)，其中 h 是二叉查找树的高度。
// 查找二叉查找树中数据域为 x 的结点
void search(node *root, int x)
{
    // 空树，查找失败
    if (root == nullptr)
    {
        printf("Search failed!\n");
        return;
    }
    
    if (root->data == x) // 查找成功
    {
        printf("%d\n", root->data);
    }
    else if (root->data > x) // 结点数据域比 x 大，往左子树搜索
    {
        search(root->lchild, x);
    }
    else //  结点数据域比 x 小，往右子树搜索 
    {
        search(root->rchild, x);
    }
}
// 和普通二叉树不同，二叉查找树的查找在于对左右子树的选择递归。

// --- 插入 ---
// 查找失败的地方就是结点需要插入的地方
void insert(node * &root, int x)
{
    // 空树，说明查找失败，也即插入点
    if (root == nullptr)
    {
        root = newNode(x);
        return;
    }

    if (x == root->data) // 查找成功，说明节点已经存在，直接返回即可
    {
        return;
    }
    else if (x < root->data) // 如果 x 比根结点的数据域小，说明需要插在左子树
    {
        insert(root->lchild, x);
    }
    else // 如果 x 比根结点的数据域大，说明需要插在右子树 
    {
        insert(root->rchild, x);
    }
}

// --- 建立 ---
// 先后插入 n 个结点
node *create(int data[], int n)
{
    node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        insert(root, data[i]);
    }
    return root;
}
// 即便是同样一组数字，如果插入它们的顺序不同，最后生成的二叉查找树也可能不同。

// --- 删除 ---
// 一般有两种常见做法，时间复杂度都是 O(h)，其中 h 为二叉查找树的高度。
// 这是简单易写的一种

// 结点的前驱：二叉树中比结点权值小的最大节点，该结点左子树中的最右结点
node *findMax(node *root)
{
    while (root->rchild != nullptr)
    {
        root = root->rchild;
    }
    return root;
}
// 结点的后继：二叉树中比结点权值大的最小节点，该结点右子树中的最左节
node *finMin(node *root)
{
    while (root->lchild != nullptr)
    {
        root = root->lchild;
    }
    return root;
}

// 思路是：用结点 N 的前驱 P 替换 N，于是问题转换为在 N 的左子树中删除结点 P，递归求解，直到递归到一个叶子节点，就可以把它直接删除了！
void deleteNode(node * &root, int x)
{
    if (root == nullptr) // 不存在权值为 x 的结点
    {
        return;
    }
    
    if (root->data == x) // 找到欲删除之结点
    {
        if (root->lchild == nullptr && root->rchild == nullptr) // 叶子节点直接删除
        {
            root = nullptr;
        }
        else if (root->lchild != nullptr) // 左子树不为空
        {
            node *pre = findMax(root->lchild); // 找到 root 前驱
            root->data = pre->data; // 用前驱覆盖 root
            deleteNode(root->lchild, pre->data); // 在左子树中删除结点 pre
        }
        else // 右子树不为空时
        {
            node *next = findMin(root->rchild); // 找到 root 后继
            root->data = next->data;
            deleteNode(root->rchild, next->data);
        }
    }
    else if (root->data > x)
    {
        deleteNode(root->lchild, x); // 往左子树中删除 x   
    }
    else
    {
        deleteNode(root->rchild, x); // 往右子树中删除 x
    }
}
// 需要注意，总是优先删除前驱（或者后继）容易导致树的左右子树高度极度不平衡，使得二叉查找树退化为一条链。解决这一问题的方法有两种：
// 一种是每次交替删除前驱或后继；另一种是记录子树的高度，总是优先在高度较高的一棵子树里删除节点。

// ------ 3. 二叉查找树的性质 ------
// 对二叉查找树进行中序遍历，遍历的结果是有序的。
// 另外，如果合理调整二叉树的形态，使得树上每个结点都尽量有两个子结点，这样整个二叉树的高度就会很低，也即树的高度大概在 log(N) 的级别，其中 N 是结点个数。能实现这个要求的一种树是平衡二叉树（AVL）。