/*
* 素数
* Author: Qin Hao
* Date: 2020/9/23
*/

// 0. 素数是什么？
// 素数又称质数，是指除了1和本身之外，不能被其他数整除的一类数。
// 注意：1既不是素数也不是合数！！！

// 1. 如何判断给定的正整数n是否是质数？
#include <cmath>
bool isPrime(int n)
{
    if (n <= 1) { // 特判
        return false;
    }
    int sqr = (int)sqrt(1.0 * n);
    for (int i = 2; i < sqr; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
// 时间复杂度 O(sqrt(n))

// 2. 如何在较短时间里得到1~n内的素数表

// 埃氏筛法，时间复杂度 O(nloglogn)
// 算法从小到大枚举所有数，对每一个素数，筛去它的所有倍数，剩下的就是素数
const int maxn = 101; // 表长
int prime[maxn], pNum = 0;
bool p[maxn] = {0}; // 如果i为素数，则p[i]为false，否则为true
void findPrime() 
{
    for (int i = 2; i < maxn; ++i) {
        if (p[i] == false) {
            prime[pNum++] = i;
            for (int j = i + 1; j < maxn; j += i) {
                p[j] = true;
            }
        }
    }
}

// 欧拉筛法，时间复杂度 O(n)
// TODO 待学习