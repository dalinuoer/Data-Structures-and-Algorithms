/*
* 归并排序
* Author: Qin Hao
* Date: 2020/6/24
*/

// 归并排序是一种基于“归并”思想的排序方法

// 2-路归并排序是一种最基本的排序方法，其原理是：将序列两两分组，将序列归并为 n/2 上取整
// 个组，组内单独排序；然后将这些组再两两归并，生成 n/4上取整 个组，组内再单独排序；以此
// 类推，直到只剩下一个组为止。归并排序的时间复杂度为 O(nlogn)。

// 2-路归并排序的核心在于如何将两个有序序列合并为一个有序序列，这在上一小节已经讨论过了。

// 1. 递归实现

const int maxn = 100;
// 将数组 A 的 [L1, R1] 和 [R1 + 1, R2] 区间合并为有序区间
void merge(int A[], int L1, int R1, int L2, int R2)
{
    int i = L1, j = L2; // i 指向 A[L1]，j 指向 A[L2]
    int temp[maxn], index = 0; // temp 临时存放合并后的数组，index 为其下标
    while (i <= R1 && j <= R2)
    {
        if (A[i] <= A[j])
        {
            temp[index++] = A[i++];
        }
        else
        {
            temp[index++] = A[j++];
        }
    }
    // 将剩余元素加入序列temp
    while (i <= R1) temp[index++] = A[i++];
    while (j <= R2) temp[index++] = A[j++];
    // 将合并后的序列副指挥数组 A
    for (i = 0; i < index; i++)
    {
        A[L1 + i] = temp[i];
    }
}
// 将 array 数组当前区间 [left, right] 进行归并排序
void mergeSort(int A[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        // 对左右子区间进行归并排序
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        // 合并左右子区间
        merge(A, left, mid, mid + 1, right);
    }
}

// 2. 非递归实现

// 2-路归并排序的非递归实现主要考虑到这样一点:每次分组时组内元素个数上限都是2的幂次。
// 于是就可以想到这样的思路:令步长step的初值为2,然后将数组中每step个元素作为一组,
// 将其内部进行排序(即把左step/2个元素与右step/2个元素合并,而若元素个数不超过step/2,
// 则不操作);再令sep乘以2,重复上面的操作,直到step/2超过元素个数n。

void mergeSort(int A[])
{
    // step为组内元素个数, step2为左子区间元素个数,注意等号可以不取
    for (int step = 2; step / 2 < n; step *= 2)
    {
        // 每step个元素一组,组内前step/2和后step/2个元素进行合井
        for (int i = 1; 1 < n; i += step) // 对每一组
        {
            int mid = i + step / 2 - 1; // 左子区间元素个数为step/2
            if (mid + 1 <= n) // 右子区间存在元素则合并
            {
                //左子区间为[i, mid],右子区间为[mid+1, min(i+step-1, n)]
                merge(A, 1, mid, mid + 1, min(i + step - 1, n));
            }
        }
    }
}

// 当然,如果题目中只要求给出归并排序每一趟结束时的序列,那么完全可以使用sort函数来代替
// mege函数(只要时间限制允许)

void mergeSort(int A[])
{
    // step为组内元素个数,step/2为左子区间元素个数,注意等号可以不取
    for (int step = 2; step / 2 <= n; step *= 2)
    {
        // 每step个元素一组，组内[i, min(i + step, n + 1)]进行排序
        for (int i = 1; i <= n; i += step)
        {
            sort(A + i, A + min(i + step, n + 1));
        }
        // 此处可以输出归并排序的某一趟结束的序列
    }
}