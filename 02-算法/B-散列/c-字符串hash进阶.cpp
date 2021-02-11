/**
 * @file c-字符串hash进阶.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-10
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

/**
 * 字符串 hash 是指将一个字符串 S 映射为一个整数，使得该整数可以尽可能唯一地代表字符串 S。
 * 那么在一定程度上，如果两个字符串转换成的整数相等，就可以认为这两个字符串相同。
 */
H[i] = H[i - 1] * 26 + index(str[i])

/**
 * 如果字符串长度较长时，产生的整数会非常大，没法用一般的数据类型保存。
 * 
 * 为了应对这种情况，只能舍弃一些“唯一性”，将产生的结果对一个整数 mod 取模。
 */
H[i] = (H[i - 1] * 26 + index(str[i])) % mod

/** 
 * 但这又会产生新的问题，可能有多个字符串的 hash 值相同，导致冲突。
 * 
 * 幸运的是，在实践中发现，在 int 型数据范围内，如果把进制数设置为一个 10^7 级别的素数（如 1e7+19）
 * 同时把 mod 设置为一个 10^9 级别的素数（如 1e9+7）,那么冲突的概率将会非常小，很难发生冲突。
 * 
 */
H[i] = (H[i - 1] * p + index(str[i])) % mod

// 看一个问题：给出 N 个只有小写字母的字符串，求其中不同的字符串的个数
// 只需要将这 N 个字符串使用字符串 hash 函数转化为 N 个整数，然后将它们排序去重即可
// (也可以用 set 或 map 直接一步实现，但是速度比字符串 hash 会慢一点点)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int P = 1e7 + 19;
vector<int> ans;

// 字符串 hash
long long hashFunc(string str)
{
    long long H = 0; // 使用 long long 避免溢出
    for (int i = 0; i < str.length(); ++i)
    {
        H = (H * P + str[i] - 'a') % MOD;
    }
    return H;
}

int main(int argc, char **argv)
{
    string str;
    while (getline(cin, str), str != "#")
    {
        long long id = hashFunc(str);
        ans.push_back(id);
    }
    sort(ans.begin(), ans.end());
    int count = 0;
    for (int i = 0; i < ans.size(); ++i)
    {
        if (i == 0 || ans[i] != ans[i - 1])
        {
            ++count;
        }
    }
    cout << count << endl;
    return 0;
}

/**
 * 继续讨论求解字符串的子串的 hash 值，也就是求解 H[i...j]。
 * 首先，从进制转换的角度考虑，H[i...j] 实际上等于把 str[i...j] 从 p 进制转换为十进制的结果。
 * 经过推到可以得出下面的结论：
 */
H[i...j] = H[j] - H[i - 1] * p^(j - i + 1)
// 所以有 hash 值为：
H[i...j] = (H[j] - H[i - 1] * p^(j - i + 1)) % mod
// 由于括号内部可能小于 0，因此为了使结果非负，需要先对结果取模，然后再加上 mod 后再次取模
H[i...j] = ((H[j] - H[i - 1] * p^(j - i + 1)) % mod + mod) % mod

// 再看一个问题：输入两个长度均不超过 1000 的字符串，求它们的最长公共子串的长度。
// 对这个问题，可以先分别对两个字符串的每个子串求出 hash 值，同时记录对应长度，
// 然后找出两堆子串对应的 hash 值中相等的那些，便可以找出最大长度。
// 时间复杂度 O(n^2 + m^2)
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map> // 引入 map 就可以使用 pair 
#include <algorithm>
using namespace std;

using LL = long long;

const LL MOD = 1e9 + 7;
const LL P = 1e7 + 19;
const LL MAXN = 1010; // 字符串最长长度

// powP[i] 存放 p^i%MOD, H1 和 H2 分别存放 str1 和 str2 的 hash 值
LL powP[MAXN], H1[MAXN] = {0}, H2[MAXN] = {0};
// pr1 存放 str1 的所有 <子串hash值， 子串长度>，pr2 同理
vector<pair<int, int>> pr1, pr2;

// 初始化 powP 数组 p^(j - i + 1)
void init(int len)
{
    powP[0] = 1;
    for (int i = 1; i <= len; i++)
    {
        powP[i] = (powP[i - 1] * P) % MOD;
    } 
}

// 计算字符串 str 的 hash 值
void calH(LL H[], string &str) // 使用引用避免构造析构等
{
    H[0] = str[0]; // H[0] 单独处理
    for (int i = 1; i < str.length(); i++)
    {
        H[i] = (H[i - 1] * P + str[i]) % MOD;
    }
}

// 计算 H[i...j]
int calSingleSubH(LL H[], int i, int j)
{
    if (i == 0)
    {
        return H[j]; // H[0...j] 单独处理
    }
    return ((H[j] - H[i - 1] * powP[j - i + 1]) % MOD + MOD) % MOD;
}

// 计算所有字串的 hash 值，并将 <子串 hash 值，字串长度> 存入 pr
void calSubH(LL H[], int len, vector<pair<int, int>> &pr)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            int hashValue = calSingleSubH(H, i, j);
            pr.push_back(make_pair(hashValue, j - i + 1));
        }
    }
}

// 计算 pr1 和 pr2 中相同的 hash 值，维护最大长度
pair<int, string> getMax()
{
    int ans = 0;
    string ansStr = "";
    for (int i = 0; i < pr1.size(); i++)
    {
        for (int j = 0; j < pr2.size(); j++)
        {
            if (pr1[i].first == pr2[j].first)
            {
                ans = max(ans, pr1[i].second);
                ansStr = pr1[i].first;
            }
        }
    }
    return make_pair(ans, ansStr);
}

int main(int argc, char **argv)
{
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    
    // 初始化 powP 数组
    init(max(str1.length(), str2.length()));
    // 分别计算 str1 和 str2 的 hash 值
    calH(H1, str1);
    calH(H2, str2);
    // 分别计算所有 H[i...j]
    calSubH(H1, str1.length(), pr1);
    calSubH(H2, str2.length(), pr2);
    // 输出最大公共子串
    printf("ans = %d\n", getMax().first);
    printf("ansStr = %s\n", getMax().second);
    return 0;
}

// TODO 学完 动态规划-最长回文子串 再回来看下

/*
 * 最后，如果确实碰到极其针对进制数 p=1e7+19、模数 mod=1e9+7 的数据，只需要调整 p 和 mod 就可以使其不冲突
 * 或者使用效果更强的双 hash 法。
 * 双 hash 法是指用两个 hash 函数生成的整数组合表示一个字符串，基本就可以保证不冲突。
 * 
 * 除了这里讨论的 hash 函数以外，还有许多优秀的字符串 hash 函数，如 BKDRHash、ELFHash等。
 */
// TODO BKDRHash、ELFHash函数