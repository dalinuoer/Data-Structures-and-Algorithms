/*
* stack
* Author: Qin Hao
* Date: 2020/9/26
* Update：2021/1/17
* Note: 增加部分注释以及修改代码格式
*/

// stack 翻译为栈，是STL中定义的一个先进后出的容器

// 1. stack 定义
#include <stack>
using namespace std;
stack<typename> name; // typename 可以是任意基本数据类型或容器

// 2. stack 容器内元素的访问
// 只能通过 top() 来访问栈顶元素

// 3. stack 常用函数
push(x)         压栈
top()           取栈顶元素值
pop()           栈顶元素出栈
empty()         判断栈是否为空
size()          计算栈的大小
// 清空操作的实现
void clear(stack<typename> &st) 
{
    while (!st.empty()) 
    {
        st.pop();
    }
}
// 4. stack 常见用途
// stack 用来模拟实现一些递归，防止程序对栈内存的限制而导致程序运行出错
