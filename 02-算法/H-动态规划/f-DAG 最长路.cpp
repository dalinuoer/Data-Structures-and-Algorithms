/**
 * @file f-DAG 最长路.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-21
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// DAG最长路和最短路的思想是一致的

// ------ 1. 求整个 DAG 中的最长路径（即不固定起点和终点） ------

// 令 dp[i] 表示从 i 号顶点出发能获得的最长路径长度，这样所有 dp[i] 的最大值就是整个 DAG 的最长路径长度

// 如果从 i 号顶点出发能直接到达顶点 j1,j2,...,jk,而 dp[j1],dp[j2],...,dp[jk] 均已知，
// 那么就有状态转移方程： dp[i] = max{ dp[j] + length[i->j] | (i, j) ∈ E }
// 显然，根据上述，需要按照逆拓扑序列的顺序来求解 dp 数组
// 当然也有不求出逆拓扑序列也能计算 dp 数组的方法，递归法
int DP(int i) // 以邻接矩阵方式存储图
{
    if (dp[i] > 0)
    {
        return dp[i];
    }
    for (int j = 0; j < n; ++j) // 遍历 i 的所有出边
    {
        if (G[i][j] != INF)
        {
            dp[i] = max(dp[i], DP(j) + G[i][j]);
        }
    }
    return dp[i];
}

// 边界：从出度为 0 的顶点出发的最长路径长度为 0，但具体实现中不妨对整个 dp 数组初始化为 0，
// 这样 dp 函数当前访问的顶点 i 的出度为 0 时就会返回 dp[i] = 0，而出度不是 0 的顶点则会递归求解，
// 递归过程中遇到已经计算过的顶点则直接返回对应的 dp 值，于是就从程序逻辑上按照逆拓扑排序的顺序进行。

// 开一个 int 数组存放顶点的后继顶点
int DP(int i)
{
    if (dp[i] > 0)
    {
        return dp[i];
    }
    for (int j = 0; j < n; ++j) // 遍历 i 的所有出边，因为是从小到大遍历，所以得到的是字典序最小的那条
    {
        if (G[i][j] != INF)
        {
            int temp = DP(j) + G[i][j]; // 单独计算，防止 if 中调用 DP 函数两次
            if (temp > dp[i]) // 可以获得更长路径
            {
                dp[i] = temp; // 覆盖 dp[i]
                choice[i] = j; // i 号顶点的后继顶点 j
            }
        }
    }
    return dp[i];
}
// 调用 printPath 前需要先得到最大 dp[i]，然后将 i 作为路径起点传入
void printPath(int i)
{
    printf("%d", i);
    while (choice[i] != -1)
    {
        i = choice[i];
        printf("->%d", i);
    }
}

// 如果令 dp[i] 表示以 i 号顶点结尾能获得的最长路径长度，只要把求解的公示变为
// dp[i] = max{ dp[j] + length[j->i] | (j, i) ∈ E }，就可以同样得到最长路径长度，
// 但不能得到字典序最小方案。
// 因为字典序的大小总是先根据序列中较前的部分来判断，所以序列中越靠前的顶点，其 dp 值应当越后
// 计算（对一般的序列性动态规划问题也应当如此）。

// ------ 2. 固定终点，求 DAG 的最长路径 ------

// 假设规定的终点为 T，那么可令 dp[i] 表示从 i 号顶点出发到达终点 T 能获得的最长路径长度
// 状态转移方程和第一个问题是一样的，区别在于边界.

// 在这个问题中边界就不是出度为 0 的顶点，而是 dp[T] = 0，整个 dp 数组也不能都赋为 0，
// 合适的做法是：初始化 dp 数组为一个负的大数，来保证“无法到达终点”的含义得到表达，
// 然后设置一个 vis 数组表示顶点是否已被计算。

int DP(int i)
{
    if (vis[i] == true)
    {
        return dp[i];
    }
    vis[i] = true;
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != INF)
        {
            dp[i] = max(dp[i], DP(j) + G[i][j]);
        }
    }
    return dp[i];
}

// 其他的问题，如记录方案、选择字典序最小的方案，均与问题 1 相同

// TODO 矩形嵌套问题 可以转化为DAG最长路问题