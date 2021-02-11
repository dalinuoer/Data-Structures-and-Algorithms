/**
 * @file d-最短路径 .cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-11
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// ------ 1. Dijkstra 算法 ------
// 适用场景：解决单源最短路径问题，即给定图 G 和起点 s，通过算法得到 S 到达其他每个顶点的最短距离。

// 基本思想：对图 G(V, E) 设置集合 S，存放已被访问的顶点，然后每次从集合 V-S 中选择与起点 s 
// 的最短距离最小的一个顶点（记为 u），访问并加入集合 S。之后，令顶点 u 为中介点，优化起点 s 与
// 所有从 u 能到达的顶点 v 之间的最短距离。这样的操作执行 n 次（n 为顶点个数），直到集合 S 已包含所有顶点。

// 伪代码：
Dijkstra(G, d[], s)
{
    初始化;
    for (循环 n 次)
    {
        u = 使 d[u] 最小的还未被访问的顶点的编号;
        记 u 已被访问；
        for (从 u 出发能到达的所有顶点 v)
        {
            if (v 未被访问 && 以 u 为中介点使 s 到顶点 v 的最短距离 d[v] 更优)
            {
                优化 d[v];
            }
        }
    }
}

// 邻接表实现：
struct Node
{
    int v, dis; // v 为边的目标顶点，dis 为边权
};

const int MAXV = 1000; // 最大顶点数
const int INF = 1e9;

vector<Node> Adj[MAXV]; // 图 G，Adj[u] 存放从顶点 u 出发可以到达的所有顶点
int n; // n 为顶点数，图 G 使用邻接表实现，MAXV 为最大顶点数
int d[MAXV]; // 起点到达各点的最短路径
bool vis[MAXV] = {false}; // 标记数组，true 表示已访问，false 表示未访问

void Dijkstra(int s) // 时间复杂度 O(n^2)
{
    fill(d, d + MAXV, INF); // fill 函数将整个 d 数组初始化为 INF（慎用 menset）
    d[s] = 0; // 起点到自身的距离为 0
    for (int i = 0; i < n; ++i) // 循环 n 次
    {
        // TODO 寻找最小 d[u] 的过程可以使用优先队列优化，降低复杂度，降至 O(VlogV + E)
        int u = -1, MIN = INF; // u 使 d[u] 最小，MIN 存放该最小的 d[u]
        for (int j = 0; j < n; ++j) // 找到未访问的顶点中 d[] 最小的
        {
            if (vis[j] == false && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        }
        if (u == -1) // 找不到小于 INF 的 d[u]，说明剩下的顶点和起点不连通
        {
            return;
        }
        vis[u] = true; // 标记 u 已被访问
        // 只有下面这个 for 循环与邻接矩阵的写法不同
        for (int j = 0; j < Adj[u].size(); ++j)
        {
            int v = Adj[u][j].v; // 通过邻接表直接获得 u 能到达的顶点 v
            if (vis[v] == false && d[u] + Adj[u][j].dis < d[v])
            {
                // 如果 v 未被访问到，且以 u 为中介点可以使 d[v] 更优
                d[v] = d[u] + Adj[u][j].dis; // 优化 d[v]
            }
        }
    }
}

// ------ 2. Bellman-Ford 算法 ------
// TODO

// ------ 3. SPFA 算法 ------
// TODO

// ------ 4. Floyd 算法 ------
// 适用场景：全源最短路问题，即对给定的图求任意两点之间最短路径的问题
// 时间复杂度 O(n^3)
// 顶点数在 200 以内，邻接矩阵表示的图，非常适合使用弗洛伊德算法
void Floyd()
{
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j]; // 找到更短路径
                }
            }
        }
    }
}