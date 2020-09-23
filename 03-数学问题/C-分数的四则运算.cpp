/*
* 分数的四则运算
* Author: Qin Hao
* Date: 2020/9/23
*/

// 1. 分数的表示和化简

struct Fraction { // 分数
    long long int up, down; // 分子、分母
};

// 三项规则：
// （1）使down为非负数；
// （2）如果该分数恰为0，那么规定其分子为0，分母为1；
// （3）分子和分母没有除了1以外的公约数。

// 分数化简的三步：
// （1）如果分母down为负数，那么令分子up和分母down都变为相反数；
// （2）如果分子up为0，那么规定分母为1；
// （3）约分：求出分子和分母的绝对值的最大公约数d，然后令分子和分母同时除以d。
Fraction reduction(Fraction result)
{
    if (result.down < 0) {
        result.up = -result.up;
        result.down = -result.down;
    }
    if (result.up == 0) {
        result.down = 1;
    } else {
        int d = gcd(abs(result.up), abs(result.down));
        result.up /= d;
        result.down /= d;
    }
    return result;
}

// 2. 分数的四则运算

// 由于分数的四则运算过程中可能使分子或分母超过int型表示范围，因此一般情况下，分子和分母
// 应当使用 long long 型存储。

// 2.1. 加法
Fraction add(Fraction f1, Fraction f2)
{
    Fraction result;
    result.up = f1.up * f2.down + f2.up * f1.down;
    result.down = f1.down * f2.down;
    return reduction(result); // 返回结果分数，注意化简
}

// 2.2. 减法
Fraction minu(Fraction f1, Fraction f2)
{
    Fraction result;
    result.up = f1.up * f2.down - f2.up * f1.down;
    result.down = f1.down * f2.down;
    return reduction(result); // 返回结果分数，注意化简
}

// 2.3. 乘法
Fraction multi(Fraction f1, Fraction f2)
{
    Fraction result;
    result.up = f1.up * f2.up;
    result.down = f1.down * f2.down;
    return reduction(result); // 返回结果分数，注意化简
}

// 2.4. 除法
Fraction divide(Fraction f1, Fraction f2)
{
    Fraction result;
    result.up = f1.up * f2.down;
    result.down = f1.down * f2.up;
    return reduction(result); // 返回结果分数，注意化简
}

// 3. 分数的输出

#include <cstdio>
void showFraction(Fraction r)
{
    r = reduction(r);
    if (r.down == 1) { // 整数
        printf("%lld", r.up);
    } else if (abs(r.up) > r.down) { // 假分数
        printf("%d %d/%d", r.up / r.down, abs(r.up) % r.down, r.down);
    } else { // 真分数
        printf("%d %d", r.up, r.down);
    }
}