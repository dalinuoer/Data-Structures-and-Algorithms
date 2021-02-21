/**
 * @file f-拓扑排序.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief Topological Sort
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// ------ 1. 有向无环图 ------

// 如果一个有向图的任意顶点都无法通过一些有向边回到自身，那么称这个有向图为有向无环图
// （Directed Acyclic Graph，DAG）。

// ------ 2. 拓扑排序 ------

// 将有向无环图 G 的所有顶点排列成一个线性序列，使得对图 G 中的任意两个顶点 u、v，如果存在边
// u->v，那么在序列中 u 一定在 v 前面。这个序列又称为拓扑序列。

// 基本思路：
// 1. 定义一个队列 Q，并把所有入度为 0 的节点加入队列。
// 2. 取队首节点，输出，然后删去所有从它出发的边，并令这些边到达的顶点的入度减 1，如果某个顶点
// 的入度减为 0，则将其加入队列。
// 3. 反复进行步骤 2，直到队列为空。如果队列为空时入过队列的节点数恰好为 N，说明拓扑排序成功，
// 图 G 为有向无环图；否则，拓扑排序失败，图 G 中有环。

// 拓扑排序的很重要的应用就是判断一个给定的图是否是有向无环图。

vector<int> G[MAXV]; // 邻接表
int n, m, inDegree[MAXV]; // 顶点数、入度

bool topologicalSort()
{
    int num = 0; // 记录加入拓扑序列的顶点数
    queue<int> q;
    for (int i = 0; i < n; ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push(i); // 入度为 0 的顶点入队
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < G[u].size(); ++i)
        {
            int v = G[u][v];
            inDegree[v]--; // 顶点 v 的入度减 1
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
        // G[u].clear(); // 清空顶点 u 的所有出边
        ++num; // 加入拓扑排序的顶点数加 1
    }
    if (num == n) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 如果要求有多个入度为 0 的顶点，选择编号最小的顶点，那么把 queue 改成 priority_queue，
// 并保持队首元素是优先队列中最小的元素即可（也可用 set）。