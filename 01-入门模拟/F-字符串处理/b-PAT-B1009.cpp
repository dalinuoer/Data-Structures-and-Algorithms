/*
* codeup 5901
* Author: Qin Hao
* Date: 2020/4/29
*/

#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    char str[80 + 1];

    gets(str);

    int len = strlen(str), row = 0, col = 0;
    char ans[81][81];

    for (int i = 0; i < len; ++i)
    {
        if (str[i] != ' ')
            ans[row][col++] = str[i];
        else
        {
            ans[row][col] = '\0';
            ++row;
            col = 0;
        }
    }

    for (int i = row; i >= 0; --i)
    {
        cout << ans[i];
        if (i > 0)
            cout << " ";
    }

    return 0;
}