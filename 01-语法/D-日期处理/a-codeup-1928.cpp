/*
* codeup 1928
* Author: Qin Hao
* Date: 2020/4/29
* https://dalinuoer.github.io/2020/04/29/%E6%97%A5%E6%9C%9F%E5%A4%84%E7%90%86%E9%97%AE%E9%A2%98/
*/

#include <iostream>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;

// 判断一年是否是闰年
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

// 把YYYYMMDD形式的日期分别转换为年，月和日
void getDate(int date, int &year, int &month, int &day)
{
    day = date % 100;
    month = date % 10000 / 100;
    year = date / 10000;
}

int main(int argc, char **argv)
{
    // YYYYMMDD 是一个千万级别的整数，可以使用 int 存储，不需要使用字符串
    int date1, date2;
    int y1, m1, d1;
    int y2, m2, d2;

    while (scanf("%d%d", &date1, &date2) != EOF)
    {
        // 保证第二个日期晚于第一个日期
        if (date1 > date2)
        {
            date1 = date1 + date2;
            date2 = date1 - date2;
            date1 = date1 - date2;
        }

        getDate(date1, y1, m1, d1);
        getDate(date2, y2, m2, d2);

        int months[13][2] = { // 平年和闰年每个月的天数
            {0, 0}, {31, 31}, {28, 29}, {31, 31}, {30, 30}, {31, 31}, {30, 30},
                    {31, 31}, {31, 31}, {30, 30}, {31, 31}, {30, 30}, {31, 31}};

        int ans = 1; // 结果

        // 在第一个日期还没有到达第二个日期时循环
        while (y1 < y2 || m1 < m2 || d1 < d2)
        {
            ++d1;
            if (d1 == months[m1][isLeapYear(y1)] + 1)
            {
                ++m1;
                d1 = 1;
            }
            if (m1 == 13)
            {
                ++y1;
                m1 = 1;
            }
            ++ans;
        }

        cout << ans << endl;
    }

    return 0;
}