/*
* PAT B1036
* Author: Qin Hao
* Date: 2020/4/29
*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    int n;
    char c;
    cin >> n >> c;

    // n 为偶数，行数为 n / 2，奇数为 n / 2 + 1
    int row = n / 2;
    if (n % 2 == 1)
        row += 1;
    int col = n;

    for (int i = 0; i < row; ++i)
    {
        if (i == 0 || i == row - 1) // 第一行或者最后一行，打印 col 个
        {
            for (int j = 0; j < col; ++j)
                cout << c;
            cout << endl;
            continue;
        }
        // 第二行到倒数第二行，开头和结尾各一个字符，其余 col - 2 个为空格
        cout << c;
        for (int k = 0; k < col - 2; ++k)
            cout << " ";
        cout << c << endl;
    }

    return 0;
}