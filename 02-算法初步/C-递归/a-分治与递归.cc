/*
* 分治与递归
* Author: Qin Hao
* Date: 2020/5/1
*/

// 分治法，分而治之，将原问题划分为若干规模较小而结构与原问题相同或相似的子问题，
// 然后分别解决这些子问题，最后合并子问题的解，即可得到原问题的解。
// 三部曲：分解、解决、合并

// 一般把子问题个数为 1 的情况称为 减治，而把子问题个数大于 1 的情况称为 分治。
// 分治法作为一种算法思想，既可以使用递归的手段实现，也可以通过非递归的手段实现。
// 一般使用递归实现比较容易。

// 递归的两个重要概念：递归边界、递归式

// 求n的阶乘
int func(int n)
{
    if (n == 0)
    {
        return 1; // 0! = 1 递归边界
    }
    else
    {
        return func(n - 1) * n; // n! = (n - 1)! * n 递归式
    }
}
// Fibonacci数列
int fibonacci(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

// 全排列：一般把1 -- n这n个整数按某个顺序摆放的结果称为这n个数的一个排列，而全排列指这n个数能形成的所有排列。
// 现要求实现按字典序从小到大的顺序输出1 -- n的全排列，其中（a1，a2，a3...an）的字典序小于（b1，b2，b3...bn）
// 是指存在一个i，使得a1 = b1, a2 = b2,...,ai-1 = bi-1, ai < bi 成立

#include <cstdio>

const int maxn = 11; // n的最大值
int n, P[maxn]; // P 为当前排列
bool hashTable[maxn] = {false}; // 记录X是否已经在P中

// 当前处理排列的第 index 位
void generateP(int index)
{
    if (index == n) // 递归边界，已经处理完排列的 0-n-1 位
    {
        for (int i = 0; i < n; ++i)
        {
            printf("%d ", P[i]); // 输出当前排列
        }
        printf("\n");
        return;
    }
    for (int x = 1; x <= n; ++x) // 枚举 1-n，试图将 x 填入 P[index]
    {
        if (hashTable[x] == false) // x 不在 P[0] - P[index - 1] 中
        {
            P[index] = x; // 把 x 加入当前排列
            hashTable[x] = true; // 记 x 已在 P 中
            generateP(index + 1); // 处理排列的第 index+1 位
            hashTable[x] = false; // 已经处理完 P[index] 为 x 的子问题，还原状态
        }
    }
}

// n 皇后问题：
// 一个 n*n 的国际象棋棋盘上放置 n 个皇后，使得这 n 个皇后两两均不在同一行、同一列、同一条对角线上的合法方案数
#include <cmath>
int count = 0; // 方案数
void nQueens(int index)
{
    if (index == n) // 递归边界，生成一个排列
    {
        bool flag = true; // flag 为 true 表示当前排列合法
        for (int i = 0; i < n; ++i) // 遍历任意两个皇后
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (abs(i - j) == abs(P[i] - P[j])) // 如果在一条对角线上
                {
                    flag = false; // 不合法
                }
            }
        }
        if (flag)
        {
            ++count; // 当前方案合法
        }
        return;
    }
    for (int x = 1; x <= n; ++x)
    {
        if (hashTable[x] == false)
        {
            P[index] = x;
            hashTable[x] = true;
            nQueens(index + 1);
            hashTable[x] = false;
        }
    }
}

// 当已经放置了一部分皇后时，可能剩余的皇后无论如何都不可能合法，此时没有必要往下递归了,
// 直接返回上层即可，这样做可以减少很多计算量。
// 一般来说，如果在到达递归边界前的某层，由于一些事实导致已经不再需要往任何一个子问题递归，
// 就可以直接返回上一层。一般把这种做法称为回溯法。

void nQueens(int index)
{
    if (index == n) // 递归边界，生成一个合法方案
    {
        ++count; // 能到达这里的一定是合法方案
        return;
    }
    for (int x = 1; x <= n; ++x) // 第 x 行
    {
        if (hashTable[x] == false) // 第 x 行还没有皇后
        {
            bool flag = true; // flag 为 true 表示当前皇后不会和之前的皇后冲突
            for (int pre = 0; pre < index; ++pre) // 遍历之前的皇后
            { // 第 index 列皇后的行号为 x，第 pre 列皇后的行号为 P[pre]
                if (abs(index - pre) == abs(x - P[pre]))
                {
                    flag = false; // 与之前的皇后在一条对角线，冲突
                    break;
                }
            }
            if (flag) // 如果可以把皇后放在第 x 行
            {
                P[index] = x; // 令第 index 烈皇后的行号为 x
                hashTable[x] = true; // 第 x 行已被占用
                nQueens(index + 1); // 递归处理第 index+1 行皇后
                hashTable[x] = false; // 递归完毕，还原第 x 行为未占用
            }
        }
    }
}