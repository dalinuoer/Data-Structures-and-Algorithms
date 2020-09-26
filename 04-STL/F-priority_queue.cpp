/*
* priority_queue
* Author: Qin Hao
* Date: 2020/9/26
* Note: 
*/

// 0. 使用之前
// priority_queue 翻译为优先队列，底层使用堆实现，队首元素一定是当前队列中优先级最高的那一个
#include <queue>
using namespace std;

// 1. priority_queue 的定义
// priority_queue<typename> name;

// 2. priority_queue 内元素访问
// 优先队列只能通过 top() 函数访问队首元素（也可称之为堆顶元素），也就是优先级最高的元素

// 3. priority_queue 常用函数
// push(x)
// top()
// pop()
// empty()
// size()

// 4. priority_queue 内元素的优先级设置

// 4.1. 基本数据类型的优先级设置
// 一般是数字越大的优先级越高
// 对基本数据类型来说，下面两种优先队列的定义是等价的（以int为例）：
priority_queue<int> pq;
priority_queue<int, vector<int>, less<int>> pq;
// vector<int> 填写的是承载底层数据结构堆的容器
// less<int> 则是对第一个参数的比较类，less<int> 表示数字越大的优先级越高，而 greater<int> 表示数字小的优先级高

// 4.2. 结构体优先级设置
#include <string>
struct fruit {
    string name;
    int price;
    // 按水果价格高的为优先级高
    friend bool operator < (fruit f1, fruit f2) {
        return f1.price < f2.price;
    }
};
// 重载大于号会编译错误，因为从数学上讲，大于、等于都可以借助小于号实现
// 优先队列的这个函数与 sort 中的 cmp 函数的效果是相反的

// 把 sort 函数写在函数体外
struct cmp {
    bool operator () (fruit f1, fruit f2) {
        return f1.price > f2.price;
    }
};
// 在这种情况下需要使用上述第二种方法来定义优先队列
priority_queue<int, vector<int>, cmp> pq;
// 即便是基本数据类型或者其他STL容器，也可以通过类似的方法来定义优先级

// 如果结构体内的的数据较为庞大（如出现了字符串或者数组），建议使用引用来提高效率，此时比较类参数中需加上“const”和“&”

// 5. priority_queue 常见用途
// 解决一些贪心问题，也可对Dijkstra算法进行优化