/*
* 快速排序
* Author: Qin Hao
* Date: 2020/9/23
*/

// 快速排序平均时间复杂度O(nlogn)

// 其实现需要先解决这样一个问题：对一个序列A[1],A[2],...,A[n]，调整序列中的元素的位置，
// 使得A[1]左侧所有元素都不超过A[1]、右侧所有元素都大于A[1]。

// 对这个问题可能有多种方案，这里是速度最快的一种，其思想就是双指针：
// 1. 先将A[1]存至某个临时变量temp，并令两个下标left，right分别指向序列首尾；
// 2. 只要right指向的元素A[right]大于temp，就将right不断左移；当某个时候A[right]<=temp
//    时，将元素A[right]挪到left指向的元素A[left]处；
// 3. 只要left指向的元素A[left]不超过temp，就将left不断右移；当某个时候A[left]>temp时，
//    将元素A[left]挪到right指向的元素A[right]处；
// 4. 重复2、3，直到left与right相遇，把temp放到相遇的地方。

// 用以划分区间的元素A[left]被称为主元

// 代码实现：
// 对区间[left, right]进行划分
int Partition(int A[], int left, int right)
{
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

// 快速排序的思路：
// 1. 调整序列中的元素，使当前序列最左端的元素在调整后满足左侧所有元素均不超过该元素，右侧
//    所有元素均大于该元素；
// 2. 对该元素的左侧和右侧分别递归进行1.的调整，直到当前调整区间的长度不超过1。

// 代码实现：
// 快排，left与right初值为序列首尾下标
void quickSort(int A[], int left, int right)
{
    if (left < right) // 当前区间长度不超过1
    {
        // 将[left, right]按照A[left]一分为二
        int pos = Partition(A, left, right);
        // 分别对左右子区间进行快速排序
        quickSort(A, left, pos - 1);
        quickSort(A, pos + 1, right);
    }
}

// 快速排序算法当序列中的元素的排列比较随机时效率最高，但是当序列中元素接近有序时，会达到
// 最坏时间复杂度O(n^2)。
// 产生这种情况的主要原因在于主元没有把当前区间划分为两个长度接近的子区间
// 解决问题的一个办法是随机选择主元，虽然这样算法的最坏时间复杂度仍为O(n^2)，但对任意输入
// 数据的期望时间复杂度都能达到O(nlogn)，也就是说，不存在一组特定数据能使这个算法出现最坏情况

// 随机快排
// 选取随机主元对区间[left, right]进行划分
#include <cstdlib>
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