/*
* 直接插入排序算法
* Author: Qin Hao
* Date: 2020/4/30
*/

#include <cstdio>

/*
* 对序列A的 n 个元素A[1] -- A[n]，令 i 从 2 到 n 枚举，进行 n - 1 趟操作
* 假设某一趟时，序列A的前 i - 1 个元素A[1] --  A[i - 1] 已经有序，而范围[i, n]还未有序
* 那么该趟从范围[1, i - 1]中寻找某个位置j，使得将A[i]插入位置 j 后范围[1, j]有序
* 时间复杂度： O(n^3)
*/
void insertSort(int* a, int n)
{
    for (int i = 1; i < n; ++i) // n - 1 趟
    {
        int temp = a[i]; // 临时存放a[i]，方便后续移动元素
        for (int j = 0; j < i; ++j) // i 次
        {
            if (a[j] > temp) // 找到插入的位置 j
            {
                for (int k = i - 1; k >= j; --k) // 把a[j] -- a[i - 1]元素向后移动一个位置
                {
                    a[k + 1] = a[k];
                }
                a[j] = temp; // 把a[i]插入a[j]位置
                break;
            }
        }
    }
}

int main(int argc, char **argv)
{
    const int ArraySize = 5;
    int a[ArraySize] = {1, 3, 4, 2, 5};

    insertSort(a, ArraySize);

    for (int i = 0; i < ArraySize; ++i)
    {
        printf("%d ", a[i]);
    }

    return 0;
}