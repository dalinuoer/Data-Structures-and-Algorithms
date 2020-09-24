/*
* 大整数运算
* Author: Qin Hao
* Date: 2020/9/24
* Note: Happy birthday to me!
*/

// 0. 什么是大整数？
// 大整数又称高精度整数，其含义就是用基本数据类型无法存储其精度的整数。

// 1. 大整数的存储
// 使用数组即可，整数的高位存储在数组的高位，整数的低位存储在数组的低位。

// 为方便随时获取大整数的长度，一般定义一个int型的变量len来记录其长度，并和d数组组成结构体
#include <string>
struct bign {
    int d[1000];
    int len;
    bign () {
        memset(d, 0, sizeof(d));
        len = 0;
    }
};

// 输入大整数时，一般都是读入字符串，然后把字符串另存为至bign结构体。
bign change(char str[]) {
    bign a;
    a.len = strlen(str);
    for (int i = 0; i < a.len; ++i) {
        a.d[i] = str[a.len - i - 1] - '0';
    }
    return a;
}

// 比较两个bign变量的大小
int compare(bign a, bign b) { // a大、相等、a小分别返回1、0、-1 
    if (a.len > b.len) {
        return 1;
    } else if (a.len < b.len) {
        return -1;
    } else {
        for (int i = a.len - 1; i >= 0; --i) {
            if (a.d[i] > b.d[i]) {
                return 1;
            } else if (a.d[i] < b.d[i]) {
                return -1;
            }
        }
    }
    return 0;
}

// 2. 大整数的四则运算

// 2.1. 高精度加法 a + b
bign add(bign a, bign b) {
    bign c;
    int carry = 0; // 进位
    for (int i = 0; i < a.len || b.len; ++i) { // 以较长的为界限
        int temp = a.d[i] + b.d[i] + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    if (carry != 0) { // 如果最后进位不为0，则直接赋给结果的最高位
        c.d[c.len++] = carry;
    }
}
// 此写法的条件是两个数都是非负整数，
// 如有一方为负，可在转换到数组的一步去掉负号，转换为减法
// 如两数都是负，就都去掉负号，加法，结果加负号

// 2.2. 高精度减法 a - b
bign sub(bign a, bign b) {
    bign c;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        if (a.d[i] < b.d[i]) {
            a.d[i + 1]--;
            a.d[i] += 10;
        }
        c.d[c.len++] = a.d[i] - b.d[i];
    }
    while (c.len - 1 >= 1 && a.d[c.len - 1] == 0) { // 去除高位0，同时至少保留一位最低位
        c.len--;
    }
    return c;
}
// 使用sub函数前需比较两个数的大小

// 2.3. 高精度与低精度乘法
bign multi(bign a, int b) {
    bign c;
    int carry = 0; // 进位
    for (int i = 0; i < a.len; ++i) {
        int temp = a.d[i] * b + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    while (carry != 0) { // 和加法不同，乘法的进位可能不止一位，因此用while
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
}
// 如果a，b中存在负数，需要先记下其负号，然后取绝对值代入函数

// 2.4. 高精度与低精度除法
bign divide(bign a, int b, int& r) { // r为余数
    bign c;
    c.len = a.len; // 被除数的每一位和商的每一位是一一对应的，因此先令长度相等
    for (int i = a.len - 1; i >= 0; --i) {
        r = r * 10 + a.d[i];
        if (r < b) { // 不够除
            c.d[i] = 0;
        } else { // 够除
            c.d[i] = r / b;
            r = r % b;
        }
    }
    while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) { // 去除最高位的0，同时至少保留一位最低位
        c.len--;
    }
    return c;
}