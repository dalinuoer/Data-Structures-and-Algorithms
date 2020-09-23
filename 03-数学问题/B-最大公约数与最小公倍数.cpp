/*
* 最大公约数与最小公倍数
* Author: Qin Hao
* Date: 2020/9/23
*/

// 1. 最大公约数
// 辗转相除法
int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

// 2. 最小公倍数
int lcm(int a, int b)
{
    // lcm(a, b) = a * b / gcd(a, b)
    // ab在实际计算时有可能溢出
    return a / gcd(a, b) * b;
}