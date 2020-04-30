/*
* 冒泡排序算法
* Author: Qin Hao
* Date: 2020/4/30
*/

#include <cstdio>

// 冒泡排序，从小到大
// 时间复杂度： O(n^2)
void bubbleSort(int* a, int n)
{
    for (int i = 1; i <= n - 1; ++i) // n - 1 趟
    {
        for (int j = 0; j <= n - 1 - i; ++j) // n - 1 - i 次
        {
            if (a[j] > a[j + 1]) // 如果左边的数比右边大，则交换位置
            {
                a[j] = a[j] + a[j + 1];
                a[j + 1] = a[j] - a[j + 1];
                a[j] = a[j] - a[j + 1];
            }
        }
    }
}

int main(int argc, char **argv)
{
    int arraySize = 5;
    int a[arraySize] = {5, 4, 3, 2, 1};

    bubbleSort(a, arraySize);
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", a[i]);
    }

    return 0;
}