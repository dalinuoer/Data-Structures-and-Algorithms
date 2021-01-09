/*
* 活用递推
* Author: Qin Hao
* Date: 2020/9/23
*/

// 有很多题目需要细心考虑过程中是否可能存在递推关系，如果能找到这样的关系，就能使时间复
// 杂度下降不少

/* PAT B1040
题目描述：
字符串 APPAPT 中包含了两个单词 PAT，其中第一个 PAT 是第 2 位(P)，第 4 位(A)，
第 6 位(T)；第二个 PAT 是第 3 位(P)，第 4 位(A)，第 6 位(T)。
现给定字符串，问一共可以形成多少个 PAT？

输入格式：
输入只有一行，包含一个字符串，长度不超过10^5，只包含 P、A、T 三种字母。

输出格式：
在一行中输出给定字符串中包含多少个 PAT。由于结果可能比较大，只输出对 1000000007 取余数的结果。

输入样例：
APPAPT

输出样例：
2
*/

/*
思路：
对一个确定的A来说，以他形成的PAT的个数等于它左边P的个数乘以右边T的个数

注意点：
1. 分别采取遍历P、A、T的位置来统计的方法会超时
2. 记得取模
*/

#include <cstdio>
#include <cstring>

const int MAXN = 100001;
const int MOD = 1000000007;

char str[MAXN]; // 字符串
int leftNumP[MAXN] = {0}; // 每一位左边（含）P的个数

int main(int argc, char** argv)
{
    gets(str);
    int len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        if (i > 0)
        {
            leftNumP[i] = leftNumP[i - 1];
        }
        if (str[i] == 'P')
        {
            ++leftNumP[i];
        }
    }
    int ans = 0, rightNumT = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (str[i] == 'T')
        {
            ++rightNumT;
        }
        else if (str[i] == 'A')
        {
            ans = (ans + leftNumP[i] * rightNumT) % MOD;
        }
    }
    printf("%d\n", ans);
    return 0;
}