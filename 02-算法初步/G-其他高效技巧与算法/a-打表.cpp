/*
* 打表
* Author: Qin Hao
* Date: 2020/9/23
*/

// 一种典型的用空间换时间的技巧
// 一般指将所有可能需要用到的结果事先计算出来，这样后面需要用到时就可以直接查表获得

// 打表常见的用法有：

// 1. 在程序中一次性计算出所有需要用到的结果，之后的查询直接取这些结果；
//    - 这个是最常用到的用法

// 2. 在程序B中分一次或多次计算出需要用到的结果，手工把结果写在程序A的数组中，然后在程序
//    A中就可以直接使用这些结果；
//    - 这种用法一般是当程序的一部分过程消耗的时间过多，或者是没有想到好的算法，因此在另一
//      个程序中使用暴力算法求出结果，这样就能直接在原程序中使用这些结果

// 3. 对一些感觉不会的题目，先用暴力程序计算小范围内的结果，然后找规律，或许就能发现一些
//    “蛛丝马迹”。
//    - 这种办法在数据范围非常大时容易用到，因为这样的题目可能不是用直接能想到的算法来
//      解决的，需要寻找一些规律才能得到结果