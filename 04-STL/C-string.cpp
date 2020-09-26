/*
* string
* Author: Qin Hao
* Date: 2020/9/26
* Note: 
*/

// 0. 使用之前
#include <string>
using namespace std;

// 输入和输出
// 法1 使用 cin 和 cout
// 法2 printf("%s", str.c_str());

// 1. string 定义
// 定义方式同基本数据类型相同，只需在 string 后跟上变量名即可，可初始化

// 2. string 中内容访问
// 法1 通过下标访问
// 法2 通过迭代器访问
string::iterator it;
// 在常用的STL容器中，只有在vector和string中，才允许使用 vi.begin()+3 这种迭代器加上整数的写法

// 3. string 常用函数
// operator +=
// compare operator 比较规则是字典序
// length() / size()

// insert(pos, string) / insert(it, it2, it3) it 为原字符串欲插入位置，it2和it3为待插入字符串的首尾迭代器

// erase(it) / erase(first, last) / erase(pos, length)

// clear()
// substr(pos, len)
// string::npos 常数，其本身的值为-1，但由于类型为 unsigned int，也可认为是 unsigned int 类型的最大值，用以作为 find 函数失配时的返回值

// find(substr) 当substr是str的子串时，返回其在str中的第一次出现的位置；如果不是，返回string::npos
// find(substr, pos) 从str的pos号位开始匹配substr，返回值与上同

// replace(pos, len, str2) 把str从pos号位开始、长度为len的子串替换为str2
// replace(it1, it2, str2) 把str的迭代器[it1, it2)范围的子串替换为str2