/*
* map
* Author: Qin Hao
* Date: 2020/9/26
* Note: 
*/

// 0. 使用之前
// map 翻译为映射，可以将任何基本类型（包括STL容器）映射到任何基本类型（包括STL容器）
#include <map>
using namespace std;

// 1. map 定义
// map<typename1, typename2> mp;  typename1是键key的类型，typename2是值value的类型

// 2. map 容器内元素的访问

// 法1 通过下标访问
// mp[key] = value; key是唯一的

// 法2 通过迭代器访问
// map<typename1, typename2>::iterator it;
// it->first 访问键；it->second 访问值

// map 会以键从小到大的顺序自动排序

// 3. map 常用函数
// map<typenme1, typename2>::iterator it = mp.find(key);
// mp.erase(it) / mp.erase(key)
// mp.erase(first, last)
// mp.size()
// mp.clear()

// 4. map 的常见用途
// 需要建立字符（串）与整数之间映射的题目，使用map可减少代码量
// 判断大整数或者其他类型数据是否存在的题目，可以把map当成bool数组使用
// 字符串和字符串的映射亦有可能遇到