/*
* algorithm 头文件下常用函数
* Author: Qin Hao
* Date: 2020/9/26
* Note: 
*/

/*
max() / min() / abs()

swap()

reverse(it1, it2)

next_permutation() 给出一个序列在全排列中的下一个序列，在达到全排列最后一个时会返回false

fill(first, last, val) 和memset不同，这里的赋值可以是数组类型对应范围中的任意值 01-G-a

sort() 02-A-d

lower_bound() 和 upper_bound() 需要用在一个有序数组或容器中
lower_bound(first, last, val) 用来寻找数组或容器[first, last)范围内第一个值大于或等于val的元素的位置，如果是数组，则返回该位置的指针；如果是容器，则返回该位置的迭代器
upper_bound(first, last, val) 用来寻找数组或容器[first, last)范围内第一个值大于val的元素的位置，如果是数组，则返回该位置的指针；如果是容器，则返回该位置的迭代器
显然，若数组或容器中没有需要寻找的元素，则lower_bound()和upper_bound()军返回可以插入该元素的位置的指针或迭代器
*/