/**
 * @file e-最小生成树.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief Minimum Spanning Tree，MST
 * @version 0.1
 * @date 2021-02-20
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// ------ 1. 最小生成树及其性质 ------

// 最小生成树：在一个给定的无向图 G(V, E) 中求一棵树 T，使得这棵树拥有图 G 中的所有顶点，且
// 所有边都是来自图 G 中的边，并且满足整棵树的边权值和最小。

// 3个性质：
// 1. 最小生成树是树，因此其边数等于顶点数减 1，且数内一定不会有环。
// 2. 对给定的图 G(V, E)，其最小生成树可以不唯一，但其边权之和一定是唯一的。
// 3. 由于最小生成树是在无向图上生成的，因此其根节点可以是这棵树上的任意一个节点。

// ------ 2. 求解最小生成树的算法 ------

// --- prim 算法（普里姆算法） ---

// 基本思想：（与 Dijkstra 算法相同）
// 对图 G(V, E) 设置集合 S，存放已被访问的顶点，然后每次从集合 V-S 中选择与集合 S 的最短距离
// 最小的一个顶点（记为 u），访问并加入集合 S。
// 之后，令顶点 u 为中介点，优化所有从 u 能到达的顶点 v 与集合 S 之间的最短距离。
// 这样操作执行 n 次，直到集合 S 已包含所有顶点。

// G 为图，一般设成全局变量；数组 d 为顶点与集合 S 的最短距离
Prim(G, d[])
{
    初始化；
    for (循环 n 次)
    {
        u = 使 d[u] 最小的还未被访问的顶点的标号；
        记 u 已被访问；
        for (从 u 出发能到达的所有顶点 v)
        {
            if (v 未被访问 && 以 u 为中介点使得 v 与集合 S 的最短距离 d[v] 更优)
            {
                将 G[u][v] 赋值给 v 与集合 S 的最短距离 d[v];
            }
        }
    }
}

// 邻接表实现代码：
const int MAXV = 1000;
const int INF = 1e9;
struct Node
{
    int v, dis; // v 为边的目标顶点，dis 为边权
};
vector<Node> Adj[MAXV]; // 图 G，Adj[u] 存放从顶点 u 出发可以到达的所有顶点
int n; // n 为顶点数，图 G 使用邻接表实现，MAXV 为最大顶点值
int d[MAXV]; // 顶点与集合 S 的最短距离
bool vis[MAXV] = {false}; // 标记数组，true 表示已被访问，初始值均为 false

/**
 * @brief 普里姆算法
 * 
 * @return int 小生成树边权之和
 */
int prim() // 默认 0 号位初始点
{
    fill(d, d + MAXV, INF);
    d[0] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, MIN = INF;
        for (int j = 0; j < n; ++j)
        {
            if (vis[j] == false && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        }
        if (u == -1) return -1;
        vis[u] = true;
        ans += d[u];
        for (int j = 0; j < Adj[u].size(); ++j)
        {
            int v = Adj[u][j].v;
            if (vis[v] == false && Adj[u][j].dis < d[v])
            {
                d[v] = G[u][v];
            }
        }
    }
    return ans;
}

// 和迪杰斯特拉算法一样，时间复杂度为 O(V^2)，使用堆优化能降到 O(VlogV + E)
// 适用于顶点数目较少而边数较多的情况

// --- kruskal 算法（克鲁斯卡尔算法） ---

// 基本思想：
// 在初始状态时隐去图中的所有边，这样每个顶点都自成一个连通块。之后执行下面的步骤：
// 1. 对所有边按边权从小到大进行排序。
// 2. 按边权从小到大测试所有边，如果当前测试边所连接的两个顶点不在同一个连通块中，则把这条测试边
// 加入当前最小生成树中；否则，将边舍弃。
// 3. 执行步骤 2，直到最小生成树中的边数等于总顶点数减 1, 或是测试完所有边时结束。而当结束时
// 如果最小生成树的边数小于总顶点数减 1，说明该图不连通。

struct edge
{
    int u, v; // 边的两个端点编号
    int cost; // 边权

} E[MAXE];

bool cmp(edge a, edge b)
{
    return a.cost < b.cost;
}

int father[N]; // 并查集数组
int findFather(int x) // 并查集查询函数
{
    while (x != father[x])
    {
        x = father[x];
    }
    return x;
}

/**
 * @brief 克鲁斯卡尔算法
 * 
 * @param n 顶点个数
 * @param m 边数
 * @return int 最小生成树边权之和
 */
int kruskal(int n, int m)
{
    int ans = 0;
    int Num_Edge = 0;
    for (int i = 1; i <= n; ++i)
    {
        father[i] = i;
    }
    sort(E, E + m, cmp);
    for (int i = 0; i < m; ++i)
    {
        int faU = findFather(E[i].u);
        int faV = findFather(E[i].v);
        if (faU != faV)
        {
            father[faU] = faV;
            ans += E[i].cost;
            Num_Edge++;
            if (Num_Edge == n - 1) break;
        }
    }
    if (Num_Edge != n - 1) return -1;
    else return ans;
}

// 时间复杂度 O(ElogE)，适合顶点数较多，边较少的情况