/*
* PAT B1020
* Author: Qin Hao
* Date: 2020/5/9
*/
#include <cstdio>
#include <algorithm>

using namespace std;

struct mooncake {
    double store;   // 库存
    double sell;    // 总售价
    double price;   // 单价
} mc[1000];

bool cmp(mooncake a, mooncake b) // 单价从高到低
{
    return a.price > b.price;
}

int main(int argc, char *argv[])
{
    int n; // n 表示月饼种类
    double d; // d 表示市场最大需求量
    scanf("%d %lf", &n, &d);

    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &mc[i].store);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &mc[i].sell);
        mc[i].price = mc[i].sell / mc[i].store; // 单价
    }

    sort(mc, mc + n, cmp); // 排序

    double ans; // 收益
    for (int i = 0; i < n; ++i)
    {
        if (mc[i].store <= d) // 需求量高于库存量
        {
            d -= mc[i].store;
            ans += mc[i].sell;
        }
        else // 需求量低于库存量
        {
            ans += mc[i].price * d;
            break;
        }
    }

    printf("%.2lf", ans);

    return 0;
}