/**
 * @file e-平衡二叉树.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 平衡二叉树由前苏联两位数学家 G.M.Adelse-Velskil 和 E.M.Landis提出，因此一般也称作AVL树
 * @version 0.1
 * @date 2021-02-08
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// ------ 1. 平衡二叉树的定义 ------
// 二叉查找树的缺陷：考虑使用序列 {1,2,3,4,5} 构建二叉查找树，得到的会是一棵链式的二叉查找树。
// 那么，一旦需要对 10^5 级别个递增元素的序列构建二叉查找树，也将会得到一棵长长的链式的树，
// 此时对这棵树中结点进行查找的复杂度就会达到 O(n)，起不到使用二叉查找树进行数据查询优化的目的。
// 于是需要对树的结构进行调整，使树的高度在每次插入元素后仍然能保持 O(logn) 的级别，
// 这样能让查询操作仍然是 O(logn) 的时间复杂度，于是就产生了平衡二叉树（AVL树）。

// AVL树仍然是一棵二叉查找树，只是在其基础上增加了“平衡”的要求。
// 所谓“平衡”是指，对AVL树的任意结点来说，其左子树与右子树的高度之差的绝对值不超过 1，
// 其中左子树与右子树的高度之差称为该结点的平衡因子。

struct node
{
    int v, height; // v 为结点权值，height 为以当前结点为根结点的子树的高度
    node *lchild, *rchild; // 左右孩子结点地址
};

node *newNode(int v)
{
    node *Node = new node; // 申请一个 node 型变量的地址空间
    Node->v = v; // 结点权值为 v
    Node->height = 1; // 结点的高度初始为 1
    Node->lchild = Node->rchild = nullptr; // 初始状态下没有左右孩子
    return Node; // 返回新建结点地址
}

// 获取以 root 为根结点的子树的当前 height
int getHeight(node *root)
{
    if (root == nullptr)
    {
        return 0; // 空结点高度为 0
    }
    return root->height;
}

// 计算结点 root 的平衡因子
int getBalanceFactor(node *root)
{
    // 左子树高度 - 右子树高度
    return getHeight(root->lchild) - getHeight(root->rchild);
}

// 更新结点 root 的 height
void updateHeight(node *root)
{
    // max(左孩子的 height，右孩子的 height) + 1
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

// ------ 2. 平衡二叉树的基本操作 ------
// 与二叉查找树相同，AVL树的基本操作有查找、插入、建树、删除

// --- 查找 ---
// 时间复杂度为 O(logn)
// 操作与二叉查找树的操作一致

// --- 插入 ---

//     A                      B
//   /  \        左旋         / \
// ⭐   B      <---->       A   □
//     /  \      右旋       / \
//    ■   □              ⭐   ■

// 左旋
void leftRatation(node * &root)
{
    node *temp = root->rchild; // root --> A, temp --> B
    root->rchild = temp->lchild; // step 1
    temp->lchild = root; // step 2
    updateHeight(root);
    updateHeight(temp);
    root = temp; // step 3
}
// 右旋
void rightRatation(node * &root)
{
    node *temp = root->lchild; // root --> B, temp --> A
    root->lchild = temp->rchild; // step 1
    temp->rchild = root; // step 2
    updateHeight(root);
    updateHeight(temp);
    root = temp; // step 3
}

// 假设现有一棵平衡二叉树，那么，再往其中插入一个结点时，一定会有结点的平衡因子发生变化，
// 此时可能会有结点的平衡因子的绝对值大于 1（2 或 -2），这样以该结点为根结点的子树就是失衡的，
// 需要进行调整。
// 可以证明，只要把最靠近插入结点的失衡结点调整到正常，路径上的所有结点就都会平衡。

// 假设最靠近插入结点的失衡结点是 A，显然它的平衡因子只可能是 2 或 -2，很容易发现这两种情况
// 完全对称，
// 因此主要讨论点 A 的平衡因子是 2 的情况。
// 由上述，左子树高度比右子树大 2，于是以结点 A 为根结点的子树一定是下述两种形态 LL型与 LR型之一
//        A                    A
//       / \                  / \
//      B   □                C   □
//     / \                  / \
//    C   ■               ⭐   B
//   / \                      / \
// ⭐  ※                    ※   ■
//  Left Left (LL)        Left Right (LR)
// 结点A、B、C权值满足：A > B > C
// 可以发现，当结点 A 的左孩子的平衡因子是 1 是为 LL 型，是 -1 时为 LR 型。

// LL型：把以 C 为根结点的子树看作一整体，然后以结点 A 为 root 进行右旋，即可
// LR型：先忽略结点 A，以结点 C 为 root 进行左旋，然后就把情况转化为 LL型，然后再按上面 LL型的做法进行一次右旋即可

// RR 型与 LL 型相反，RL 型与 LR 型相反。

void insert(node * &root, int v)
{
    if (root == nullptr) // 到达空结点
    {
        root = newNode(x);
        return;
    }

    if (v < root->v) // v 比根结点的权值小
    {
        insert(root->lchild, v); // 往左子树插入
        updateHeight(root); // 更新树高
        if (getBalanceFactor(root) == 2)
        {
            if (getBalanceFactor(root->lchild) == 1) // LL型
            {
                rightRatation(root); // 右旋
            }
            else if (getBalanceFactor(root->lchild) == -1) // LR型
            {
                leftRatation(root->lchild); // 左子树左旋
                rightRatation(root); // 右旋
            }            
        }
    }
    else // v 比根结点的权值大
    {
        insert(root->rchild, v); // 往右子树插入
        updateHeight(root); // 更新树高
        if (getBalanceFactor(root->rchild) == -1) // RR型
        {
            leftRatation(root); // 左旋
        }
        else if (getBalanceFactor(root->rchild) == 1) // RL型
        {
            rightRatation(root->rchild); // 右子树右旋
            leftRatation(root); // 左旋
        }
    }
}

// --- 建树 ---
// 操作与二叉查找树的操作一致