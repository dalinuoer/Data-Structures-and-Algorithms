/*
* PAT B1032
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

    const int ArraySize = 100001;
    int school[ArraySize] = {0};
    int sno, grade;
    for (int i = 0; i < n; ++i)
    {
        cin >> sno >> grade;
        school[sno] += grade;
    }

    int maxSno = 1, maxGrade = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (school[i] > maxGrade)
        {
            maxSno = i;
            maxGrade = school[i];
        }
    }

    cout << maxSno << " " << maxGrade;

    return 0;
}