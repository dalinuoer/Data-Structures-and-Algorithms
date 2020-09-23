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

