/*
* PAT B1022
* Author: Qin Hao
* Date: 2020/4/29
*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    // 题目要求 a 和 b 都是不大于 2^(30)-1 的非负十进制整数
    // a 和 b 相加所得结果的最大值为 2*（2^(30)-1）= 2^(31)-2
    // 而 int 型变量所能表示的最大值为 2^(31)-1
    // 所以使用 int 表示 a 和 b 相加的结果足矣
    int a, b, d;
    cin >> a >> b >> d;

    int sum = a + b;

    const int ArraySize = 20;
    int ans[ArraySize] = {0}; // 存放结果
    int num = 0; // 位数
    do {
        ans[num++] = sum % d; // 除基取余
        sum /= d;
    } while (sum != 0);

    for (int i = num - 1; i >= 0; --i) // 从高位到低位输出
    {
        cout << ans[i];
    }
    cout << endl;

    return 0;
}