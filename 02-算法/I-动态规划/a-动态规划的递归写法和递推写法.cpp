/**
 * @file a-动态规划的递归写法和递推写法.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 动态规划（Dynamic Programming，DP）
 * @version 0.1
 * @date 2021-01-19
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 动态规划是一种非常精妙的算法思想，它没有固定的写法、极其灵活，常常需要具体问题具体分析。
// 不要畏惧，多训练、多思考、多总结是学习动态规划的重点。

/****** 1. 什么是动态规划 ******/

// 动态规划是一种用来解决一类 **最优化问题** 的算法思想。
// 简单来说，动态规划将一个复杂的问题分解成若干个子问题，通过综合子问题的最优解来得到原问题的最优解。

// 需要注意的是，动态规划会将每个求解过的子问题的解记录下来，这样当下一次碰到同样的子问题时，
// 就可以直接使用之前记录的结果，而不是重复计算。

// 注意：虽然动态规划采用这种方式来提高计算效率，但不能说这种做法就是动态规划的核心。

// 一般可以使用递归或者递推的写法来实现动态规划，其中递归写法在此处又称作 **记忆化搜索**。

/****** 2. 动态规划的递归写法 ******/

// 学习目的：理解动态规划是如何记录子问题的解，来避免下次遇到相同的子问题时的重复计算的。

// Fibonacci 数列为例
int f(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        return f(n - 1) + f(n - 2);
    }  
}
// 以上是我们在学习递归算法时所写代码，事实上，这个递归会涉及到很多重复的计算，比如 f(5) = f(4) + f(3), f(4) = f(3) + f(2)。

// 可以推知，如果 n 很大，重复计算的次数将难以想象。事实上，由于没有及时保存中间计算的结果，
// 实际复杂度会高达 O(2^n)，基本不能承受 n 较大的情况。

// 为了避免重复计算，可以开辟一个一维数组 dp，用以保存已经计算过的结果，其中 dp[n] 记录 f(n) 的结果，-1 表示未被计算过。
int dp[maxn] = {-1};
int f(int n)
{
    if (n == 1 || n == 2) // 递归边界
    {
        return 1;
    }

    if (dp[n] != -1) // 已经计算过，直接返回结果，不再重复计算
    {
        return dp[n];
    }
    else
    {
        dp[n] = f(n - 1) + f(n - 2); // 计算 f(n)，并保存至 dp[n]
        return dp[n];
    }
}
// 这样就把已经计算过的内容保存下来了，于是当下次需要计算相同的内容时，就能直接使用上次计算的结果，
// 这样可以省去大半无效计算，而这也是 记忆化搜索 这个名字的由来。

/************/
// 引申出一个概念：如果一个问题可以被分解为若干个子问题，且这些子问题会重复出现，那么就称这个问题
// 拥有 **重叠子问题（Overlapping Subproblem）**。

// DP 通过记录重叠子问题的解，来使下次碰到相同的子问题时直接使用之前记录的结果，以此避免大量重复计算。
// 因此，一个问题必须拥有重叠子问题，才能使用 DP 去解决。
/************/

/****** 3. 动态规划的递推写法 ******/

// 经典的 “数塔问题”
/*
      5
     / \
     8  3
    / \/ \
    12 7 16
   / \/ \/ \
  4  10 11 6
 / \/ \/ \/ \
9  5  3  9  4
*/
// 将一些数字排成数塔的形状，第 n 层有 n 个数字。现在要从第一层走到第 n 层，每次只能走向下一
// 层连接的两个数字中的一个，问：最后将路径上所有数字相加后得到的和最大是多少？

// 思路：使用数组 dp 记录当前位置到第 n 层所有路径中能得到的最大值，dp[1][1] 就是最终答案。
// 如果要求出 dp[i][j]，那么一定要先求出它的两个子问题 “从位置（i+1，j）到达最底层的最大和 dp[i+1][j]”
// 和 “从位置（i+1，j+1）到达最底层的最大和 dp[i+1][j+1]”，即进行了一次决策：走左下还是右下。
// dp[i][j] = max{dp[i + 1][j], dp[i + 1][j + 1]} + f[i][j]
// 把 dp[i][j] 称为问题的状态，上式称为 状态转移方程

// 那么什么时候是个头呢？
// 可以发现，数塔最后一层的 dp 值总是等于元素本身，即 dp[n][j] == f[n][j]（1 <= j <= n）
// 把这种可以直接确定其结果的部分称为 边界，而动态规划的递推写法总是从这些边界出发，通过状态转
// 移方程扩散到整个 dp 数组

#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1000;
int f[maxn][maxn] = {0};
int dp[maxn][maxn] = {0};

int main(int argc, char **argv)
{
    // 数据输入
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            scanf("%d", &f[i][j]);
        }
    }
    // 边界
    for (int j = 1; j <= n; ++j)
    {
        dp[n][j] = f[n][j];
    }
    // 从第 n - 1 层不断往上计算出 dp[i][j]
    for (int i = n - 1; i >= 1; --i)
    {
        for (int j = 1; j <= i; ++j)
        {
            // 状态转移方程
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + f[i][j];
        }
    }
    printf("%d\n", dp[1][1]);
    return 0;
}

// 显然，使用递归也可以实现上面的例子，两者区别在于：
// 使用递推写法的计算方式是自底向上（Bottom-up Approach），即从边界开始，不断向上解决问题，直到解决了目标问题；
// 使用递归写法的计算方式是自顶向下（Top-down Approach），即从目标问题开始，将它分解为子问题的组合，直到分解至边界为止。

/************/
// 再引申出一个概念：如果一个问题的最优解可以由其子问题的最优解有效地构造出来，那么就称这个问题拥有 最优子结构。
// 最优子结构保证了动态规划中原问题可以由子问题的最优解推导而来。
// 因此，一个问题必须拥有最优子结构，才能使用动态规划去解决。
/************/

// 注意：一个问题必须拥有重叠子问题和最优子结构，才能使用动态规划去解决。

