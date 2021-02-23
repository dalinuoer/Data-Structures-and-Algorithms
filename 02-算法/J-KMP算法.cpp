/**
 * @file J-KMP算法.cpp
 * @author Qin Hao (qinhao2020@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-22
 * 
 * @copyright Copyright (c) 2021 Qin Hao
 * 
 */

// 
// 当时学的时候就感觉这个算法很困难，而且不幸的是，现在仍然还是这么觉得。
// 

// KMP 算法是一种非常优秀的字符串匹配算法
// 时间复杂度 O(n + m)（其中 n 和 m 分别是文本串和模式串的长度）

// 为什么叫 KMP 算法呢? 因为是由 Knuth、Morris、Pratt 三人共同发现的

// ------ 1. next 数组 ------

// 假设有一个字符串 s（下标从 0 开始），那么它以 i 号位作为结尾的字串就是 s[0...i]。
// 对该子串来说，长度为 k + 1 的前缀和后缀分别是 s[0...k] 和 s[i - k...i]。

// 现在定义一个 int 型的数组 next，其中 next[i] 表示使子串 s[0...i] 的前缀 s[0...k] 
// 等于后缀 s[i - k...i] 的最大 k（前后缀可以部分重叠，但不能是 s[0...i] 本身）；
// 如果找不到相等的前缀和后缀，那么就令 next[i] = -1。

// 显然，next[i] 就是所求最长相等前后缀中前缀最后一位的下标。

// 下面就来求解 next 数组
int next[len];
void getNext(char s[], int len)
{
    int j = -1;
    next[0] = -1; // 初始化 j = next[0] = -1
    for (int i = 0; i < len; ++i) // 求解 next[1] -- next[len - 1]
    {
        while (j != -1 && s[i] != s[j + 1]) // 直到 j 回退到 -1，或是 s[i] == s[j + 1]
        {
            j = next[j]; // 反复令 j = next[j]
        } 
        if (s[i] == s[j + 1])
        {
            ++j; // next[i] = j + 1,先令 j 指向这个位置
        }
        next[i] = j;
    }
}

// ------ 2. KMP 算法 ------

// 给定文本串 text 和模式串 pattern，判断模式串是否是文本串的子串

// next 数组的含义就是当 j + 1 位失配时，j 应该回退到的位置

int KMP(char text[], char pattern[]) // 统计模式串在文本串中出现的次数
{
    int n = strlen(text), m = strlen(pattern);
    getNext(pattern, m);
    int ans = 0; // 匹配次数
    int j = -1;
    for (int i = 0; i < n; ++i) // 试图匹配 text[i]
    {
        while (j != -1 && text[i] != pattern[j + 1])
        {
            j = next[j]; // 不断回退
        }
        if (text[i] == pattern[j + 1])
        {
            ++j;
        }
        if (j == m - 1) // 完全匹配
        {
            ++ans;
            j = next[j]; // 回退
        }
    }
    return ans;
}