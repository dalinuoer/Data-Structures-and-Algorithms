/**
 * @file f-并查集.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-09
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// ------ 1. 并查集的定义 ------
// 并查集是一种维护集合的数据结构，它的名字中“并“”查”“集”分别取自 Union（合并）、Find（查找）、
// Set（集合）这三个单词。也就是说，并查集支持下面两个操作：
// ① 合并：合并两个集合
// ② 查找：判断两个元素是否在一个集合

// 并查集使用数组实现，int father[N];
// 其中 father[i] 表示元素 i 的父亲结点，而父亲结点本身也是这个集合的元素（1<=i<=N）。
// 如果 father[i] = i，则说明元素 i 是该集合的根结点，但对同一个集合来说只存在一个根节点，
// 且将其作为所属集合的标识。

// ------ 2. 并查集的基本操作 ------
// 总的来说，并查集的使用需要先初始化 father 数组，然后再根据需要进行查找或合并的操作。

// --- 初始化 ---
// 一开始，每个元素都是独立的一个集合
for (int i = 1; i <= N; ++i)
{
    father[i] = i;
}

// --- 查找 ---
// 对给定结点寻找其根结点
int findFather(int x) // 递推
{
    while (x != father[x])
    {
        x = father[x];
    }
    return x;
}
int findFather(int x) // 递归
{
    if (x == father[x])
    {
        return x;
    }
    else
    {
        return findFather(father[x]);
    }
}

// --- 合并 ---
// 合并指把两个集合合并成一个集合，题目中一般给出两个元素，要求把这两个元素所在的集合合并。

// 具体实现上一般是先判断两个元素是否属于同一个集合，只有当两个元素属于不同集合时才合并，
// 而合并的过程一般是把其中一个集合的根结点的父亲指向另一个集合的根结点。
void union(int a, int b)
{
    int faA = findFather(a);
    int faB = findFather(b);
    if (faA != faB)
    {
        father[faA] = faB;
    }
}

// 在合并的过程中，只对两个不同的集合进行合并，如果两个元素在相同的集合中，那么就不会对它们进行
// 操作，这就保证了在同一个集合中一定不会产生环。
// 即，并查集产生的每一个集合都是一棵树。

// ------ 3. 路径压缩 ------
// 上述并查集查找函数是没有经过优化的，在极端情况下效率较低。
// 现在考虑这样一种情况，即题目给出的元素数量很多并且形成一条链，那么这个查找函数的效率就会非常低

// 把当前查询结点的路径上的所有结点的父亲都指向根结点。
// ① 按原先的写法获得 x 的根结点 r
// ② 重新从 r 开始走一遍寻找根结点的路径，把路径上经过的所有结点的父亲全部改为根结点 r
int findFather(int x) // 递推写法
{
    int a = x; // 由于 x 在下面的 while 中会变成根结点，因此先把原先的 x 保存一下
    // step 1
    while (x != father[x])
    {
        x = father[x];
    }
    // 此时 x 存放的是根结点
    // 下面把路径上的所有结点的 father 都改成根结点
    // step 2
    while (a != father[a])
    {
        int z = a; // 因为 a 要被 father[a] 覆盖，所以先保存 a 的值，以修改 father[a]
        a = father[a]; // a 回溯父亲结点
        father[z] = x; // 将原先的结点 a 的父亲修改为根结点 x
    }
    return x; // 返回根结点
}
// 这样就可以在查找时把寻找根结点的路径压缩了。
int findFather(int v) // 递归写法
{
    if (v == father[v])
    {
        return v;
    }
    else
    {
        int F = findFather(father[v]);
        father[v] = F;
        return F;
    }
}
// 可以把路径压缩后的并查集查找函数均摊效率认为是一个几乎为 O(1) 的操作。
