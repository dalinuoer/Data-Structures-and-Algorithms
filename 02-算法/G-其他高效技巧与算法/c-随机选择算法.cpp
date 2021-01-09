/*
* 随机选择算法
* Author: Qin Hao
* Date: 2020/9/23
*/

// 如何从一个无序的数组中求出第K大的数（假设是数组中的数各不相同）

// 最直接的想法是先对数组进行排序，然后直接取出第K大的数，时间复杂度为O(nlogn)
// 虽然看起来很好，但是还有更优的算法————随机选择算法

// 随机选择算法对任何输入都可以达到O(n)的期望时间复杂度.

// 随机选择算法的原理类似于随机快速排序算法。当对A[left, right]执行一次randPartition函数
// 之后，主元左侧的元素个数就是确定的，且它们都小于主元。假设此时主元是A[p]，那么A[p]就是
// A[left, right]中的第 p-left+1 大的数。不妨令 M 表示 p-left+1，
// 如果 K==M 成立，说明第K大的数就是主元A[p]；
// 如果 K<M 成立，就说明第K大的数在主元左侧，往左递归即可；
// 如果 K<M 成立，就说明第K大的数在主元左侧，往左递归即可。
// 算法以 left==right 作为递归边界，返回A[left]。

// 随机选择算法，从A[left, right]中返回第K大的数
#include <cstdlib>
#include <algorithm>
using namespace std;
int randPartition(int A[], int left, int right)
{
    // 生成[left, right]内的随机数p
    int p = (round(1.0 * rand() / RAND_MAX * (right - left) + left));
    swap(A[p], A[left]); // 交换A[p]和A[left]

    // 以下为原Partition函数的划分过程
    int temp = A[left];
    while (left < right)
    {
        while (left < right && A[right] > temp)
        {
            --right;
        }
        A[left] = A[right];

        while (left < right && A[left] <= temp)
        {
            ++left;
        }
        A[right] = A[left];
    }
    A[left] = temp;
    return left; // 返回相遇的下标
}
int randSelect(int A[], int left, int right, int K)
{
    if (left == right) // 边界
    {
        return A[left];
    }

    int p = randPartition(A, left, right); // 划分后主元的位置
    int M = p - left + 1;

    if (K == M)
    {
        return A[p];
    }
    else if (K < M) // 左侧
    {
        return randSelect(A, left, p - 1, K);
    }
    else if (K > M) // 右侧
    {
        return randSelect(A, p + 1, right, K);
    }
}

// 可以证明，虽然随机选择算法的最坏时间复杂度是O(n^2)，但是其对任意输入的期望时间复杂度
// 却是O(n)，这意味着不存在一组特定的数据能使这个算法出现最坏情况，是个相当实用和出色的算法。