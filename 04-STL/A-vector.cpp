/*
* vector
* Author: Qin Hao
* Date: 2020/9/24
* Note: Happy birthday to me!
*/

// 0. 使用之前
#include <vector>
using namespace std;

// 1. vector的定义

// 一维
// vector<typename> name;

// 二维
// vector<vector<typename>> name;

// 2. vector容器内元素的访问

// 通过下标访问

// 通过迭代器访问
// vector<typename>::iterator it;
#include <cstdio>
#include <vector>

using namespace std;

vector<int> vi = {1, 2, 3, 4, 5};

int main(int argc, char* argv[]) {
    for (vector<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
        printf("%d\n", *it);
    }
    return 0;
}
// 在常用的STL容器中，只有在vector和string中，才允许使用 vi.begin()+3 这种迭代器加上整数的写法

// 3. vector常用函数实例解析

// vi.push_back(x);                在vector，末尾添加一个元素，时间复杂度 O(1)

// vi.pop_back();                  删除末尾元素，时间复杂度 O(1)

// unsigned len = vi.size();       获取vector中元素个数，时间复杂度 O(1)，返回类型是 unsigned

// vi.clear();                     清空vector中的元素，时间复杂度 O(n)

// insert(it, x);                  vector的任意迭代器it处插入一个元素，时间复杂度 O(n)

// erase(it);                      删除单个元素
// erase(first, last);             删除[first, last)内的所有元素

// 4. vector的常见用途
// 存储数据
//      本身可以作为数组使用，而且在一些元素个数不确定的而场合可以很好的节省空间
//      有些场合需要根据一些条件把部分数据输出在同一行，数据中间用空格隔开，为了更方便地处理
//      最后一个满足条件的数据而后面不输出额外的空格，可以先用vector记录所有需要输出的数据，
//      然后一次性输出
// 用邻接表存储图