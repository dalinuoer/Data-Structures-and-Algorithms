/**
 * @file d-最长公共子序列 LCS.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief Longest Common Subsequence，LCS
 * @version 0.1
 * @date 2021-02-21
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 给定两个字符串（或数字字符串）A 和 B，求一个字符串，使得这个字符串是 A 和 B 的最长公共部分
// （子序列可以不连续）。

// 还是先看看暴力解法：
// 设字符串 A 和 B 的长度分别是 n 和 m，那么对两个字符串中的每个字符，
// 分别有选与不选两个决策，而得到两个子序列后，比较两个子序列是否相同又需要 O(max(m, n))，
// 这样总的时间复杂度就是 O(2^(m + n) * max(m, n))。无法承受数据规模较大的情况。

// 下面介绍动态规划的解法，时间复杂度为 O(nm)：
// 令 dp[i][j] 表示字符串 A 的 i 号位和字符串 B 的 j 号位之前的 LCS 长度，那么有两种决策：
// ① 若 A[i] == B[j]，则字符串 A 与字符串 B 的 LCS 增加了 1 位，
// 即有 dp[i][j] = dp[i - 1][j - 1] + 1
// ② 若 A[i] ！= B[j]，则字符串 A 的 i 号位与字符串 B 的 j 号位之前的 LCS 无法延长，
// 因此 dp[i][j] 将会继承 dp[i - 1][j] 与 dp[i][j - 1] 中的较大值，即有
// dp[i][j] = max{ dp[i - 1][j], dp[i][j - 1] }

// 状态转移方程 dp[i][j] = dp[i][j] = dp[i - 1][j - 1] + 1, A[i] == B[j]
//                       dp[i][j] = max{ dp[i - 1][j], dp[i][j - 1] }, A[i] ！= B[j]
// 边界 dp[i][0] = dp[0][j] = 0 （0 <= i <= n, 0 <= j <= m）

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100;
char A[N], B[N];
int dp[N][N];

int main(int argv, char **argv)
{
    // 读入数据，初始化
    int n;
    // 从下标为 1 开始读入
    get(A + 1);
    get(B + 1);
    // 由于从下标为 1 开始读入，因此读取长度也从 +1 开始
    int lenA = strlen(A + 1);
    int lenB = strlen(B + 1);

    // 边界
    for (int i = 0; i <= lenA; ++i)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= lenB; ++j)
    {
        dp[0][j] = 0;
    }

    // 状态转移方程
    for (int i = 1; i <= lenA; ++i)
    {
        for (int j = 1; j <= lenB; ++j)
        {
            if (A[i] == B[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[lenA][lenB]);

    return 0;
}
