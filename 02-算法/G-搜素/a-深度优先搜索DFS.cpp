/**
 * @file a-深度优先搜索DFS.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 深度优先搜索算法（Depth First Search，DFS）
 * @version 0.1
 * @date 2021-01-08
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 深度优先搜索是一种枚举所有完整路径以遍历所有情况的搜索方法
// 以深度为第一关键词，即当碰到岔道口时总是先选择其中的一条岔路前进，而不管其他岔路，
// 直到碰到死胡同才返回岔道口并选择其他岔路。

// 算法实现：
// 1. 使用栈（stack）实现，听着很容易，但实现起来并不轻松
// 2. 使用递归实现。
// 这个说法并不是说深度优先搜索就是递归，只能说递归是深度优先搜索的一种实现方式，
// 因为使用非递归也是可以实现DFS的思想的，但是一般情况下会比递归麻烦。不过，使用递归时，
// 系统会调用一个叫系统栈的东西来存放递归中每一层的状态，因此使用递归来实现DFS的本质其实还是栈。

// 一个例子：
// 有 n 件物品，每件物品的重量为 w[i]，价值为 c[i]。现在需要选出若干件物品放入一个容量为 V 的
// 背包中，使得在选入背包的物品重量和不超过容量 V 的前提下，让背包中物品的价值之和最大，求最大价值。
// （1<=n<=20）
#include <cstdio>
const int maxn = 30;
int n, V, maxValue = 0; // 物品件数 n，背包容量 V，最大价值 maxValue
int w[maxn], c[maxn];   // w[i]为每件物品的重量，c[i]为每件物品的价值
// DFS，index为当前处理物品的编号
// sumW 和 sumC 分别是当前总重量和当前总价值
void DFS(int index, int sumW, int sumC)
{
    // 死胡同
    if (index == n) // 已完成对 n 件物品的选择
    {
        if (sumW <= V && sumC > maxValue) // 不超过背包容量时更新最大价值 maxValue
        {
            maxValue = sumC;
        }
        return;
    }
    // 岔道口
    DFS(index + 1, sumW, sumC);                       // 不选择第 index 件物品
    DFS(index + 1, sumW + w[index], sumC + c[index]); // 选择第 index 件物品
}
// 上述代码复杂度为 O(n^2)
// 总是把 n 件物品的选择全部确定之后才去更新最大价值，但是事实上忽视了背包容量不超过 V 这个特点
// 也就是说，完全可以把对 sumW 的判断加入“岔道口”中，只有当 sumW <= V 时才进入岔道，这样效率会高很多
void DFS(int index, int sumW, int sumC)
{
    // 死胡同
    if (index == n) // 已完成对 n 件物品的选择
    {
        return;
    }
    // 岔道口
    DFS(index + 1, sumW, sumC); // 不选择第 index 件物品
    // 只有加入第 index 件物品后未超过容量 V，才能继续
    if (sumW + w[index] <= V)
    {
        if (sumC + c[index] > maxValue) // 更新最大价值
        {
            maxValue = sumC + c[index];
        }
        DFS(index + 1, sumW + w[index], sumC + c[index]); // 选择第 index 件物品
    }
}
// 这种通过题目条件限制来节省DFS计算量的方法称作剪枝（前提是剪枝之后算法仍然正确）。剪枝是一门艺术。

// 上面的问题给出了一类常见 DFS 问题的解决方法，即给定一个序列，枚举这个序列的所有子序列（可以不连续），
// 枚举所有子序列的目的很明确————可以从中选择一个“最优”子序列，使它的某个特征是所有序列中最优的，
// 如果有需要，还可以把这个序列保存下来。
// 显然，这个问题也等价于 枚举从 N 个整数中选择 K 个数的所有方案。

// 再举一个例子：
// 给定 N 个整数（其中可能有负数），从中选择 K 个数，使得这 K 个数之和恰好等于一个给定的整数 X，‘
// 如果有多种方案，选择它们中元素平方和最大的一个。数据保证这样的方案唯一。

#include <vector>
using namespace std;

int n, k, x, maxSumSqu = -1, A[maxn];
// temp 存放临时方案，ans 存放平方和最大的方案
vector<int> temp, ans;
// 当前处理 index 号整数，当前已选整数个数为 nowK
// 当前已选整数之和为 sum，当前已选整数平方和为 sumSqu
void DFS(int index, int nowK, int sum, int sumSqu)
{
    if (nowK == k && sum == x) // 找到 k 个数的和为 x
    {
        if (sumSqu > maxSumSqu) // 如果比当前找到的更优
        {
            maxSumSqu = sumSqu; // 更新最大平方和
            ans = temp;         // 更新最优方案
        }
        return;
    }
    // 已经处理完 n 个数，或者超过 k 个数，或者和超过 x，返回
    if (index == n || nowK > k || sum > x)
    {
        return;
    }
    // 选 index 号数
    temp.push_back(A[index]);
    DFS(index + 1, nowK + 1, sum + A[index], sumSqu + A[index] * A[index]);
    temp.pop_back(); // 此条分支结束，将其从 temp 中去除，使它不会影响“不选index号数”分支
    // 不选 index 号数
    DFS(index + 1, nowK, sum, sumSqu);
}

// 上述问题中的每个数都只能使用一次，若每一个数都可被选择多次，何如？
// 当选择了 index 号数时，不应直接进入 index+1 号数的处理，，应能继续选择 index 号数，
// 直到某个时候决定不再选用 index号数，就会通过“不选 index 号数”这条分支进入 index+1 号数的处理。
void DFS(int index, int nowK, int sum, int sumSqu)
{
    if (nowK == k && sum == x) // 找到 k 个数的和为 x
    {
        if (sumSqu > maxSumSqu) // 如果比当前找到的更优
        {
            maxSumSqu = sumSqu; // 更新最大平方和
            ans = temp;         // 更新最优方案
        }
        return;
    }
    // 已经处理完 n 个数，或者超过 k 个数，或者和超过 x，返回
    if (index == n || nowK > k || sum > x)
    {
        return;
    }
    // 选 index 号数
    temp.push_back(A[index]);
    /******** 改动的地方 *********/
    DFS(index, nowK + 1, sum + A[index], sumSqu + A[index] * A[index]);
    /***************************/
    temp.pop_back(); // 此条分支结束，将其从 temp 中去除，使它不会影响“不选index号数”分支
    // 不选 index 号数
    DFS(index + 1, nowK, sum, sumSqu);
}