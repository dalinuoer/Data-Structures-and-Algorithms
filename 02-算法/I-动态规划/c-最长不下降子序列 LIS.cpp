/**
 * @file c-最长不下降子序列 LIS.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief Longest Increasing Sequence，LIS
 * @version 0.1
 * @date 2021-02-21
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 在一个数字序列中，找到一个最长的子序列（可以不连续），使得这个子序列是不下降（非递减）的。

// 对这个问题可以使用类似解决背包问题的算法，即枚举每种情况，对每个元素有取和不取两种选择，
// 然后判断序列是否为不下降序列。如果是，则更新最大长度，直到枚举完所有情况并得到最大长度。
// 但是时间复杂度高达 O(2^n)，这是不可承受的！

// 事实上这种解法包含了大量的重复计算。
// 每次碰到子问题“以 A[i] 结尾的最长不下降子序列”时，都去重新遍历所有子序列，
// 而不是直接记录这个子问题的结果。

// 下面介绍动态规划的解法，时间复杂度为 O(n^2)：
// 1. 令 dp[i] 表示以 A[i] 结尾的最长不下降子序列长度。这样对 A[i] 来说就会有两种可能：
// ① 如果存在 A[i] 之前的元素 A[j]，使得 A[j] <= A[i] 且 dp[j] + 1 > dp[i]（即把 A[i]
// 跟在以 A[j] 结尾的 LIS 后面时能比当前以 A[i] 结尾的 LIS 长），那么就把 A[i] 放在以 A[j] 
// 结尾的 LIS 后面，形成一条更长的不下降子序列（令 dp[i] = dp[j] + 1）。
// ② 如果 A[i] 之前的元素都比 A[i] 大，那么 A[i] 就只好自己形成一条 LIS，但是长度为 1，
// 即这个子序列里面只有一个 A[i]。
// 2. 最后以 A[i] 结尾的 LIS 长度就是①②中能形成的最大长度。

// 状态转移方程 dp[i] = max{ 1, dp[j] + 1 }(j = 1, 2,..., i - 1 && A[j] < A[i])
// 边界 dp[i] = 1 (1 <= i <= n)

#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100;
int A[N], dp[N];

int main(int argc, char *argv[])
{
    // 输入数据，初始化
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
    }

    int ans = -1;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = 1; // 边界
        for (int j = 1; j < i; ++j)
        {
            if (A[i] >= A[j] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1; // 状态转移方程
            }
        }
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);

    return 0;
}
