/*
* 简单选择排序算法
* Author: Qin Hao
* Date: 2020/4/30
*/

#include <cstdio>

/*
* 对一个序列A中的元素A[1] - A[n]，令 i 从 1 到 n 枚举，进行 n 趟操作
* 每趟从待排序部分[i, n]中选择最小的元素，令其与待排序部分的第一个元素A[i]进行交换
* 这样元素A[i]就会与当前有序区间[1, i - 1]形成新的有序区间[1, i]
* 于是在 n 趟操作后所有元素就会使有序的
* 时间复杂度： O(n^2)
*/
void selectSort(int* a, int n) // 待排序数组 数组元素个数
{
    for (int i = 0; i < n; ++i) // 进行 n 趟操作
    {
        int k = i; // 记录 a[i] -- a[n-1] 最小元素位置
        for (int j = i; j < n; ++j) // 每趟 n - i 次
            if (a[j] < a[k])
            {
                k = j;
            }
        }
        if (k == i) continue;
        // 交换 a[i] 和 a[k] 的位置
        a[i] = a[i] + a[k];
        a[k] = a[i] - a[k];
        a[i] = a[i] - a[k];
    }
}

int main(int argc, char **argv)
{
    const int ArraySize = 5;
    int a[ArraySize] = {5, 3, 4, 2, 1};

    selectSort(a, ArraySize);

    for (int i = 0; i < ArraySize; ++i)
    {
        printf("%d ", a[i]);
    }

    return 0;
}