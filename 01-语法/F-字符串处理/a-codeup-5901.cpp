/*
* codeup 5901
* Author: Qin Hao
* Date: 2020/4/29
*/

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    string str;
    cin >> str;

    int len = str.size();
    string ans = "YES";

    for (int i = 0; i < len / 2; ++i)
    {
        if (str[i] != str[len - 1 - i])
        {
            ans = "NO";
            break;
        }
    }

    cout << ans << endl;

    return 0;
}