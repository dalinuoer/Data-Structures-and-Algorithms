/*
* 二分法拓展
* Author: Qin Hao
* Date: 2020/5/25
*/

// 二分法除了二分查找之外,还有许多其他的"妙用"
// 二分法的本质是单调区间上的"逼近"问题

// 拓展:

// 1. 单点函数区间求根问题

// 给定一个定义在 [L, R] 上的单点函数 f(x)，求方程 f(x) = 0 的根。假设函数单调递增。

const double eps = 1e-5; // 精度

double f(double x) // 计算 f(x)
{
    return f(x);
}

double solve(double L, double R)
{
    double left = L, right = R, mid;
    while (right - left > eps)
    {
        mid = (left + right) / 2;
        if (f(mid) > 0)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    return mid;
}

// 2. 装水问题

// 有一个从侧面看起来是一个半圆的储水装置，该半圆半径为 R，要求往里面注入高度为 h 的水，
// 使其在侧面看去的面积与半圆面积的比例恰好为 r，给定 R 和 r，求高度 h。

# include <cmath>

const double eps = 1e-5; // 精度
const double pi = acos(-1.0); // 圆周率

double f(double R, double h) // 计算 r = f(R, h)
{
    double S1 = pi * R * R / 2; // 半圆面积
    double alpha = 2 * acos((R - h) / R); // 扇形角度大小
    double S2 = alpha * R * R / 2 - 2 * sqrt(R * R - (R - h) * (R - h)) * (R - h) / 2; // 拱形面积
    return S2 / S1;
}

double solve(double R, double r)
{
    double left = 0, right = R, mid;
    while (right - left > eps)
    {
        mid = (left + right) / 2;
        if (f(R, mid) > r)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    return mid;
}

// 3. 木棒切割问题

// 给出N根木棒，长度均已知，现在希望通过切割它们来得到至少K段长度相等的木棒（长度必须为整数），
// 问这些长度相等的木棒最长能有多长。

// 对于该问题，如果长度相等的木棒的长度L越长，那么可以得到的木棒段数k越少。
// 从这个角度出发，我们便可以想到运用二分法的思想，
// 根据对当前长度L来说能得到的木棒段数k与K的大小关系来进行二分。
// 由于这个问题可以写成求解最后一个满足条件“k>=K”的长度L，
// 因不妨转换为求解第一个满足“k<K”的长度L，然后减1即可。

#include <algorithm>

const int maxn = 10010;
int len[maxn] = {10, 24, 15};
int N = 3, K = 7; // 木棒段数、切割得到的木棒段数

int calculatek(int L)
{
    int total = 0;
    for (int i = 0; i < N; ++i)
    {
        total += len[i] / L;
    }
    return total;
}

int solve(int left, int right)
{
    int mid;
    while (left + 1 < right) // 左开右闭区间
    {
        mid = (left + right) / 2;
        if (calculatek(mid) < K)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    return right;
}