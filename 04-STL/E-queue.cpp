/*
* queue
* Author: Qin Hao
* Date: 2020/9/26
* Note: 
*/

// 0. 使用之前
// queue 翻译为队列，一个先进先出的容器
#include <queue>
using namespace std;

// 1. queue 的定义
// queue<typename> name; typename可以是任何基本类型（包括STL容器）

// 2. queue 容器内元素访问
// 由于队列本身就是一种先进先出的限制性数据结构，
// 因此在STL中只能通过 front() 来访问队首元素，或是通过 back() 访问队尾元素

// 3. queue 常用函数
q.push(x)                 压进队尾
front() / back()
pop()                     弹出队首元素
empty()                   检测queue是否为空
size()
// 清空操作的实现
void clear(queue<typename> &q) {
    while (!st.empty()) {
        q.pop();
    }
}

// 4. queue 常见用途
// 当需要实现广度优先搜索时，可以不用自己实现一个队列，而是用queue作为代替，以提高程序的准确性
// 使用 front() 和 back() 之前需要先判断队列是否为空，否则会出问题