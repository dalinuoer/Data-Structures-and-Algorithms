/*
* 快速幂
* Author: Qin Hao
* Date: 2020/6/24
*/

// 给定三个正整数 a、b、m (a < 10^9, b < 10^18, 1 < m < 10^9)，求 a^b % m
// 我们不能直接先计算 a^b，再进行模运算，因为没有能表示 a^b 如此大的数的类型

// 要解决这个问题需要使用“快速幂”的做法，它基于二分思想，因此也被称为“二分幂”
// 快速幂基于以下事实：
// 1. 如果 b 是奇数，那么有 a^b = a * a^(b-1);
// 2. 如果 b 是偶数，那么有 a^b = a^(b/2) * a^(b/2).
// b 是奇数的情况总能在下一步转换为偶数的情况，而 b 是偶数的情况总能转换为 b/2 的情况
// 所以在经过 log(b) 数量级次数的转换后，就可以把 b 转换为 0

// 快速幂的递归写法，时间复杂度为 O(logb)

typedef long long LL;
// 求 a^b % m，递归写法
LL binaryPow(LL a, LL b, LL m)
{
    if (m == 1) // 任何整数模1结果都是0
    {
        return 0;
    }
    if (b == 0) // a^0 = 1
    {
        return 1;
    }

    if (b % 2 == 1) // b 为奇数的情况，转换为 b - 1
    {
        return a * binaryPow(a, b - 1, m) % m; // if (b & 1) 速度更快一点
    }
    else // b 为偶数的情况，转换为 b / 2
    {
        // 不要直接返回 binaryPow(a, b / 2, m) * binaryPow(a, b / 2, m) % m
        // 这会导致时间复杂度提高到 O(2^(log(b))) = O(b)
        LL mul = binaryPow(a, b / 2, m);
        return mul * mul % m;
    }
}

// 两个需要注意的细节：
// 1. 如果初始时 a 有可能大于等于 m，那么需要在进入函数前就让 a 对 m 取模；
// 2. 如果 m 为 1，可以在函数外部特判为 0，不需要进入函数计算。

// 快速幂的迭代写法，时间复杂度比递归写法更小

typedef long long LL;
// 求 a^b % m，迭代写法
LL binaryPow(LL a, LL b, LL m)
{
    LL ans = 1;

    if (m == 1) // 任何整数模1结果都是0
    {
        return 0;
    }
    if (b == 0) // a^0 = 1
    {
        return 1;
    }

    while (b > 0)
    {
        if (b & 1) // 如果 b 的二进制末尾为 1 (if (b % 2))
        {
            ans = ans * a % m; // 令 ans 累计上 a
        }
        a = a * a % m; // 令 a 平方
        b >>= 1; // 将 b 的二进制右移一位(b = b / 2)
    }
}

// 在实际应用中，递归写法和迭代写法在效率上的差别并不明显，可以根据喜好选择其中一种