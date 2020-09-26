/*
* set
* Author: Qin Hao
* Date: 2020/9/25
* Note: 
*/

// 0. 使用之前
#include <set>
using namespace std;
// 内部自动递增有序且不含重复元素

// 1. set的定义
// set<typename> name;

// 2. set容器内元素的访问
// 只能通过迭代器访问
// 在常用的STL容器中，只有在vector和string中，才允许使用 vi.begin()+3 这种迭代器加上整数的写法
// 所以只能按照加下的方式枚举

// 3. set常用函数实例解析
// st.insert(x);            将x插入容器中并自动递增排序和去重，时间复杂度 O(logn)
// st.find(x);              返回set中对应值为x的迭代器，时间复杂度 O(logn)

// st.erase(it);            删除单个元素，it为所需删除元素的迭代器，时间复杂度 O(1)
// st.arase(x);             删除单个元素，x为所需删除元素的值，时间复杂度 O(logn)
// st.erase(first, last);   删除 [first, last) 间内的所有元素，其中first，last均为迭代器,时间复杂度 O(last-first) 

// unsigned len = st.size(); 获取元素个数，时间复杂度 O(1)
// st.clear();              清空所有元素，时间复杂度 O(n)

// 4. set的常见用法
// 主要就是自动去重并按升序排列