/*
* codeup 1934
* Author: Qin Hao
* Date: 2020/4/29
*/

#include <iostream>

using std::cin;
using std::cout;

int main(int argc, char **argv)
{
    int n;
    cin >> n;

    int *p = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i];
    }

    int x;
    cin >> x;
    int loc = -1;
    for (int i = 0; i < n; ++i)
    {
        if (p[i] == x)
        {
            loc = i;
            break;
        }
    }

    cout << loc;

    delete [] p;

    return 0;
}