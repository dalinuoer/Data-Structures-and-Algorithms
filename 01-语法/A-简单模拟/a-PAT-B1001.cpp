/*
* PAT B1001
* Author： Qin Hao
* Date: 2020/4/29
*/

#include <iostream>

using std::cin;
using std::cout;

int main(int argc, char **argv)
{
    int n;
    cin >> n;

    int step = 0;
    while (n != 1)
    {
        if (n % 2 == 0)
            n /= 2;
        else
        {
            n = 3 * n + 1;
            n /= 2;
        }
        ++step;
    }

    cout << step;

    return 0;
}