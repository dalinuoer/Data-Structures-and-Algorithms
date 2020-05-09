/*
* PAT B1023
* Author: Qin Hao
* Date: 2020/5/9
*/
#include <cstdio>

int main(int argc, char **argv)
{
    int num[10]; // 记录数字0-9的个数
    for (int i = 0; i < 10; ++i)
    {
        scanf("%d", &num[i]);
    }
    for (int i = 1; i < 10; ++i) // 从1-9中选择个数不为0的最小数字输出
    {
        if (num[i] != 0)
        {
            printf("%d", i);
            --num[i];
            break;
        }
    }
    for (int i = 0; i < 10; ++i) // 输出0-9对应个数的数字
    {
        for (int j = 0; j < num[i]; ++j)
        {
            printf("%d", i);
        }
    }
    return 0;
}