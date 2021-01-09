/*
* C++ STL sort() 函数学习
* Author: Qin Hao
* Date: 2020/4/30
*/

// C语言中qsort函数使用比较繁琐，涉及到很多指针操作
// C++标准库中的sort函数在实现中规避了经典快速排序中可能出现的会导致实际复杂度退化到O(n^2)的极端情况

#include <cstdio>
#include <vector>
#include <algorithm> // 需要头文件 algorithm

using namespace std; // 命名空间 std

// 比较函数（cmp函数）的写法
// 比较函数cmp “告诉” sort 何时交换元素

// sort(首元素地址， 尾元素地址的下一个地址， [比较函数])
// 如省略比较函数，则默认对前面给出的区间进行 递增 排序

// 1. 基本数据类型数组的排序
// 记忆方法:如果要把数据从小到大排列那么就用“<”,因为“a<b”就是左小右大;
//         如果要把数据从大到小排列,那么就用“>”因为“a>b”就是左大右小。
//         而当不确定或者忘记时,不妨两种都试下,就会知道该用哪种了。
bool cmp1(int a, int b)
{
    return a > b; // 当 a > b 时把 a 放在 b 前面
}

// 2. 结构体数组的排序
struct node {
    int x, y;
} ssd[10];

bool cmp2(node a, node b)
{
    return a.x > b.x; // 按 x 从大到小排序
}

bool cmp3(node a, node b)
{
    // 若 x 不等，则按 x 从大到小顺序排列
    // 否则，按 y 从小到大排序
    if (a.x != b.x) return a.x > b.x;
    else return a.y < b.y;
}

// 3. 容器排序
// 在STL标准容器中，只有 vector、string、deque 可以使用 sort
bool cmp4(int a, int b)
{
    return a > b;
}

int main(int argc, char **argv)
{
    /*1. 基本数据类型数组的排序*/
    const int ArraySize = 5;
    int a[ArraySize] = {1, 3, 4, 2, 5};

    //sort(a, a + 5); // 省略比较函数，按从小到大排序
    sort(a, a + 5, cmp1); // 比较函数cmp，按从大到小排序

    for (int i = 0; i < ArraySize; ++i)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    /*2. 结构体数组的排序*/
    ssd[0].x = 2;
    ssd[0].y = 2;

    ssd[1].x = 1;
    ssd[1].y = 3;

    ssd[2].x = 2;
    ssd[2].y = 1;

    sort(ssd, ssd + 3, cmp3);

    for (int i = 0; i < 3; ++i)
    {
        printf("%d %d ", ssd[i].x, ssd[i].y);
    }

    printf("\n");

    /*3. 容器排序*/
    vector<int> vi;
    vi.push_back(3);
    vi.push_back(1);
    vi.push_back(2);

    sort(vi.begin(), vi.end(), cmp4);

    for (int i = 0; i < 3; ++i)
    {
        printf("%d ", vi[i]);
    }

    printf("\n");

    return 0;
}