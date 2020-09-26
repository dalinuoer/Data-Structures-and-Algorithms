/*
* pair
* Author: Qin Hao
* Date: 2020/9/26
* Note: 
*/

// 当想要将两个元素绑在一起作为一个合成元素，又不想要因此定义结构体时，使用pair可以很方便的作为一个替代品
// 换句话说，pair实际上可以看作是一个内部有两个元素的结构体，且这两个元素的类型是可以指定的
struct pair1 {
    typename1 first;
    typename2 second;
};

// 1. pair 定义
#include <utility> // 若使用了map，就无需额外添加此头文件
using namespace std;
pair<typename1, typename2> p(val1, val2); // 定义并初始化

// 如果想在代码中临时构建一个 pair，有如下两种方法：
pair<typename1, typename2>(val1, val2);
make_pair(val1, val2);

// 2. pair 中元素访问
// pair 中只有两个元素，分别是 first， second，只需要按照正常结构体的方式去访问即可

// 3. pair 常用函数
// 比较操作数
// 两个pair类型的元素可以直接使用比较运算符进行大小比较，比较规则是先以 first 的大小作为标准
// 只有当 first 相等时才去判断 second 的大小

// 4. pair 常见用途
// 用来代替二元结构及其构造函数，可以节省编码时间
// 作为 map 的键值对来进行插入
mp.insert(pair<typename1, typename2>(val1, val2));
mp.insert(make_pair(val1, val2));