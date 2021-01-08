/*
* 栈的应用
* Author: Qin Hao
* Date: 2020/9/28
* Note: 
*/

/*
题目描述
读入一个只包含 +, -, *, / 的非负整数计算表达式，计算该表达式的值。

输入
测试输入包含若干测试用例，每个测试用例占一行，每行不超过200个字符，整数和运算符之间用一个
空格分隔。没有非法表达式。当一行中只有0时输入结束，相应的结果不要输出。

输出
对每个测试用例输出1行，即该表达式的值，精确到小数点后2位。

样例输入 Copy
30 / 90 - 26 + 97 - 5 - 6 - 13 / 88 * 6 + 51 / 29 + 79 * 87 + 57 * 92
0

样例输出 Copy
12178.21
*/

// 两步：中缀表达式转换为后缀表达式 --> 计算后缀表达式

// 第一步
// 1. 设立一个操作符栈，用以临时存放操作数；设立一个数组或队列，用以存放后缀表达式
// 2. 从左到右扫描中缀表达式，如果碰到操作数，就把操作数加入后缀表达式
// 3. 如果碰到操作符op，就将其优先级与操作符栈的栈顶操作符的优先级比较
//     若op的优先级高于栈顶操作符的优先级，则压入操作符栈
//     若op的优先级低于或等于栈顶操作符的优先级，则将操作符栈的操作符不断弹出到后缀表达式中，直到op的优先级高于栈顶操作符的优先级
// 4. 重复上述操作，直到中缀表达式扫描完毕，之后若操作符栈中仍有元素，则将它们依次弹出至后缀表达式中
// 若有括号，只需在步骤3之前判断，如果是左括号，则压入操作符栈，若是右括号，就把操作符栈里的元素不断弹出到后缀表达式直到碰到左括号

// 第二步
// 从左到右扫描后缀表达式，如果是操作数，就压入栈；如果是操作符，就连续弹出两个操作数，然后进行操作符的操作，生成新的操作数压入栈中，反复直到后缀表达式扫描完毕，这时栈中只会存在一个数，就是最终答案

#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <queue>
#include <map>

using namespace std;

struct node
{
    double num; // 操作数
    char op;    // 操作符
    bool flag;  // true表示操作数，false表示操作符
};

string str;
stack<node> s; // 操作符栈
queue<node> q; // 后缀表达式栈
map<char, int> op;

void change()
{ // 将中缀表达式转换为后缀表达式
    double num;
    node temp;
    for (int i = 0; i < str.length();)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {                              // 数字
            temp.flag = true;          // 标记是数字
            temp.num = str[i++] - '0'; // 记录这个操作数的第一个数位
            while (i < str.length() && str[i] >= '0' && str[i] <= '9')
            {
                temp.num = temp.num * 10 + (str[i] - '0'); // 更新操作数
                i++;
            }
            q.push(temp);
        }
        else
        {                      // 操作符
            temp.flag = false; // 标记为操作符
            // 若op的优先级低于或等于栈顶操作符的优先级，则将操作符栈的操作符不断弹出到
            // 后缀表达式中，直到op的优先级高于栈顶操作符的优先级
            while (!s.empty() && op[str[i]] <= op[s.top().op])
            {
                q.push(s.top());
                s.pop();
            }
            temp.op = str[i];
            s.push(temp); // 把该操作符压入操作符栈中
            i++;
        }
    }
    // 如果操作符栈中还有操作符，就把他弹出到后缀表达式队列中
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}

double cal()
{ // 计算后缀表达式
    double temp1, temp2;
    node cur, temp;
    while (!q.empty())
    {                    // 只要后缀表达式队列非空
        cur = q.front(); // 记录队首元素
        q.pop();
        if (cur.flag)
        { // 如果是操作数直接压栈
            s.push(cur);
        }
        else
        {                        // 如果是操作符
            temp2 = s.top().num; // 弹出第二操作数
            s.pop();
            temp1 = s.top().num; // 弹出第一操作数
            s.pop();
            temp.flag = true; // 临时记录操作数
            if (cur.op == '+')
            {
                temp.num = temp1 + temp2;
            }
            else if (cur.op == '-')
            {
                temp.num = temp1 - temp2;
            }
            else if (cur.op == '*')
            {
                temp.num = temp1 * temp2;
            }
            else if (cur.op == '/')
            {
                temp.num = temp1 / temp2;
            }
            s.push(temp); // 把计算结果压栈
        }
    }
    return s.top().num; // 栈顶元素就是后缀表达式的值
}

int main(int argc, char *argv[])
{
    // 设定操作符优先级
    op['+'] = op['-'] = 1;
    op['*'] = op['/'] = 2;
    while (getline(cin, str), str != "0")
    {
        for (string::iterator it = str.end(); it != str.begin(); it--)
        {
            if (*it == ' ')
            { // 去掉表达式中的空格
                str.erase(it);
            }
        }
        while (!s.empty())
        { // 初始化栈
            s.pop();
        }
        change();
        printf("%.2f\n", cal());
    }
    return 0;
}