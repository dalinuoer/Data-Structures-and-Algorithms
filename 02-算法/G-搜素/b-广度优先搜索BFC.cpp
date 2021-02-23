/**
 * @file b-广度优先搜索BFC.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 广度优先搜索算法（Breadth First Search，BFS）
 * @version 0.1
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 以广度为第一关键词，当碰到岔道口时，总是先依次访问从该岔道口能直接到达的所有结点，然后再按这
// 些结点被访问的顺序去依次访问他们能直接到达的所有结点，以此类推，直到所有节点都被访问为止。

// 算法实现：一般使用队列（queue）实现，且总是按层次的顺序进行遍历
// 基本写法如下（可作为模板用）：
#include <queue>
using namespace std;
void BFS(int s)
{
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        // 取出队首元素 top；
        // 访问队首元素 top;
        // 将队首元素出队；
        // 将 top 的下一层节点中未曾入队的节点全部入队，并设置为已入队；
    }
}

// 一个例子：
// 给出一个 m*n 的矩阵，矩阵中的元素为 0 或 1。称位置（x，y）与其上下左右四个位置（x，y+1）、
// （x，y-1）、（x+1，y）、（x-1，y）是相邻的。如果矩阵中有若干个 1 是相邻的（不必两两相邻），
// 那么称这些 1 构成了一个“块”。求给定矩阵中“块”的个数。

// 解题思路：枚举每一个位置的元素，如果为 0，则跳过；如果为 1，则使用 BFS 查询该位置相邻的 4
// 个位置（前提是不出界），判断它们是否为 1（如果某个相邻的位置为 1，则同样去查询与该位置相邻的
// 4 个位置，直到整个“1”块访问完毕）。
// 为防止走回头路，一般可以设置一个 bool 型的数组 inq，来记录每个位置是否在 BFS 中已入过队。

#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 100;
struct node
{
    int x, y; // 位置（x，y）
} Node;

int n, m;               // 矩阵大小n*m
int matrix[maxn][maxn]; // 01矩阵
bool inq[maxn][maxn];   // 记录位置（x，y）是否已经入过队
// 增量数组
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};

// 判断坐标（x，y）是否需要访问
bool judge(int x, int y)
{
    // 越界返回 false
    if (x >= n || x < 0 || y >= m || y < 0)
    {
        return false;
    }
    // 当前位置为 0，或（x，y）已入过队，返回 false
    if (matrix[x][y] == 0 || inq[x][y] == true)
    {
        return false;
    }
    // 以上都不满足，返回 true
    return true;
}
// BFS 函数访问位置（x，y）所在的块，将该块中所有“1”的 inq 都设置为 true
void BFS(int x, int y)
{
    queue<node> Q;
    Node.x = x, Node.y = y;
    Q.push(Node);
    inq[x][y] = true; // 设置（x，y）已入过队
    while (!Q.empty())
    {
        node top = Q.front(); // 取出队首元素
        Q.pop();              // 队首元素出队
        for (int i = 0; i < 4; ++i)
        {
            int newX = top.x + X[i];
            int newY = top.y + Y[i];
            if (judge(newX, newY))
            {
                Node.x = newX, Node.y = newY;
                Q.push(Node);
                inq[newX][newY] = true;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    scanf("%d%d", &n, &m);
    for (int x = 0; x < n; ++x)
    {
        for (int y = 0; y < m; ++y)
        {
            scanf("%d", &matrix[x][y]);
        }
    }
    int ans = 0;
    for (int x = 0; x < n; ++x)
    {
        for (int y = 0; y < m; ++y)
        {
            if (matrix[x][y] == 1 && inq[x][y] == false)
            {
                ++ans;
                BFS(x, y);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}

// 再来一个例子：
// 给定一个 n*m 大小的迷宫，其中 * 代表不可通过的墙壁，而 . 代表平地，S 代表起点，T 代表终点。
// 移动过程中，如果当前位置（x，y）（下标从 0 开始），且每次只能前往上下左右四个位置的平地，求
// 从起点 S 到达终点 T 的最少步数。

// 解题思路：BFS 是通过层次的顺序来遍历的，可以从起点 S 开始计数遍历的层数，那么在到达终点 T 时
// 的层数就是需要求解的起点 S 到达终点 T 的最少步数。

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 100;
struct node
{
    int x, y; // 位置（x，y）
    int step; // 从起点 S 到达该位置的最少步数，即层数
} S, T, Node; // S 为起点，T 为终点，Node 为临时结点

int n, m;
char maze[maxn][maxn];          // 迷宫信息
bool inq[maxn][maxn] = {false}; // 记录位置（x，y）是否已入过队
// 增量数组
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};

// 检测位置（x，y）是否有效
bool test(int x, int y)
{
    // 越界返回 false
    if (x >= n || x < 0 || y >= m || y < 0)
    {
        return false;
    }
    // 墙壁
    if (maze[x][y] == '*')
    {
        return false;
    }
    // 已入过队
    if (inq[x][y] == true)
    {
        return false;
    }
    // 有效位置
    return true;
}

int BFS()
{
    queue<node> q;
    q.push(S);
    while (!q.empty())
    {
        node top = q.front();
        q.pop();
        if (top.x == T.x && top.y == T.y) // 终点，直接返回最少步数
        {
            return top.step;
        }
        for (int i = 0; i < 4; ++i)
        {
            int newX = top.x + X[i];
            int newY = top.y + Y[i];
            if (test(newX, newY)) // 位置（newX，newY）有效
            {
                // 设置 Node 的坐标为（newX，newY）
                Node.x = newX, Node.y = newY;
                Node.step = top.step + 1; // Node 层数为 top 层数加 1
                q.push(Node);
                inq[newX][newY] = true; // 设置位置（x，y）已入过队
            }
        }
    }
    return -1; // 无法到达终点 T 时返回 -1
}

int main(int argc, char *argv[])
{
    scanf("%d%d", &n， & m);
    for (int i = 0; i < n; ++i)
    {
        getchar(); // 过滤掉每行后面的换行符
        for (int j = 0; j < m; ++j)
        {
            maze[i][j] = getchar();
        }
    }
    scanf("%d%d%d%d", &S.x, &S.y, &T.x, &T.y);
    S.step = 0;
    printf("%d\n", BFS());
    return 0;
}

// 当使用 STL 的 queue 时，元素入队的 push 操作只是制造了该元素的一个副本入队，因此在入队后
// 原元素的修改不会影响队列中的副本，而队列中副本的修改也不会改变原元素，需要注意由此可能引入的
// bug（一般由结构体产生）。

// 也就是说，当需要对队列中的元素进行修改而不仅仅是访问时，队列中存放的元素最好不要是元素本身，
// 而是它们的编号（如果是数组的话则是下标）。
// 这个小技巧可以避免很多由使用 queue 不当导致的错误。
