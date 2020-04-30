/*
* 一些需要注意的地方
* Author: Qin Hao
* Date: 2020/4/30
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    int arraySize = 5;
    int a[arraySize] = {1, 2, 3, 4, 5};
    int b[arraySize][arraySize] = {0};

    // 使用 memset 函数对数组中每一个元素赋相同的值
    // memset(数组名， 值， sizeof(数组名));
    // 建议使用 memset 赋 0 或 -1
    // 如果对数组赋其他数字，使用函数 fill()
    // memset 在头文件 string.h 中
    memset(a, -1, sizeof(a));
    memset(b, -1, sizeof(b));

    // fill()可以把数组或容器中的某一段区间赋为某个相同的值
    // 所赋的值可以是数组类型对应范围内的任意值
    // fill 函数在头文件 algorithm 中
    // 命名空间 std
    fill(a, a + 5, 123);
    fill(b[0], b[0] + arraySize * arraySize, 456); // 注意！


    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", a[i]);
    }

    printf("\n\n");

    for (int i = 0; i < arraySize; ++i)
    {
        for (int j = 0; j < arraySize; ++j)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    return 0;
}