/*
* 组合数
* Author: Qin Hao
* Date: 2020/9/24
* Note: Happy birthday to me!
*/

// 1. 求 n！中有多少个质因子
// 对这个问题，最直观的一个想法就是计算从1~n的每个数各有多少个质因子，然后累加，时间复杂度 O(nlogn)
// 这种做法对 n 很大的情况是无法承受的

// 一种时间复杂度为 O(logn) 的算法
// 计算 n！中有多少个质因子p
int cal(int n, int p) {
    int ans = 0;
    while (n) {
        ans += n / p;
        n /=  p;
    }
    return ans;
}
// 利用这种算法还可以很快计算出 n！的末尾有几个0，末尾零的个数等于10的个数，又等于5的个数

// 2. 组合数的计算
// 2.1. 如何计算 C(n, m)

// 法1 通过定义式直接计算 
// C(n, m) = n! / ( m!(n - m)! ) 此法容易溢出
// 时间复杂度 O(n)

// 法2 通过递推公式计算
// C(n, m) = C(n-1, m) + C(n-1, m-1)
long long C(long long n, long long m) {
    if (m == 0 || m == n) {
        return 1;
    }
    return C(n - 1, m) + C(n - 1, m - 1);
}
// 此种方法的问题是重复计算，可以打表
// 时间复杂度 O(n^2)

// 法3 通过定义式的变形来计算
// 时间复杂度为 O(m)
long long C(long long n, long long m) {
    long long ans = 1;
    for (long long i = 1; i <= m; ++i) {
        ans = ans * (n - m + i) / i; // 注意一定要先乘再除
    }
    return ans;
}

// 2.2. 如何计算 C(n, m) % p
// 法1 通过递推公式计算
// 此种方法基于上述法2
// 此处假设两倍的p不会超过int型
// 在这种做法下，算法可以很好的支持 m<=n<=1000的情况，且对p的大小和素性没有额外限制
long long C(long long n, long long m, int p) {
    if (m == 0 || m == n) {
        return 1;
    }
    return (C(n - 1, m) + C(n - 1, m - 1)) % p;
}