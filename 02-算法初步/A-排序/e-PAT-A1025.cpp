/*
* PAT A1025
* Author: Qin Hao
* Date: 2020/4/30
*/

#include <cstdio>
#include <algorithm>

using namespace std;

struct student {
    long long id;           // 准考证号
    int score;              // 成绩
    int locationNumber;     // 考场号
    int localRank;          // 考场排名
} stu[100 * 300];

bool cmp(student a, student b)
{
    if (a.score != b.score) return a.score > b.score; // 先按成绩从高到低
    else return a.id < b.id; // 成绩相同按准考证从小到大
}

int main(int argc, char **argv)
{
    int n, k, num = 0; // n为考场数，k为某一个考场内的考生数，num为考生总数
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d %d", &stu[num].id, &stu[num].score);
            stu[num].locationNumber = i; // 考场号
            ++num;
        }
        sort(stu + num - k, stu + num, cmp); // 将该考场内考生排序
        stu[num - k].localRank = 1; // 该考场内第一名 localRank 记为 1
        for (int j = num - k + 1; j < num; ++j) // 该考场剩余考生
        {
            if (stu[j].score == stu[j - 1].score) // 成绩相等，排名相等
            {
                stu[j].localRank = stu[j - 1].localRank;
            }
            else // 成绩低于前一位考生
            {
                stu[j].localRank = j + 1 - (num - k); // localRank 为该考生前的人数
            }
        }
    }
    printf("%d\n", num); // 输出考生总数
    sort(stu, stu + num, cmp); // 对所有考生进行排序
    int r = 1; // 当前考生排名
    for (int i = 0; i < num; ++i)
    {
        if (i > 0 && stu[i].score != stu[i - 1].score)
        {
            r = i + 1; // 当前考生成绩遇上一个考生不同时，排名等于当前考生人数 +1
        }
        printf("%d %d %d %d\n", stu[i].id, r, stu[i].locationNumber, stu[i].localRank);
    }
    return 0;
}