#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Students.h"
using namespace std;

//空闲时间赋值
void Students::set_free_t(string ft[])
{
    for (int i = 0; i < 20; i++)
    {
        if (ft[i] == "")break;
        free_t[i] = ft[i];
    }
}

//学生号赋值
void Students::set_stu_no(string sn)
{
    stu_no = sn;
}

//志愿部门赋值
void Students::set_app_dep(string ad[])
{
    for (int i = 0; i < 5; i++)
    {
        if (ad[i] == "")break;
        app_dep[i] = ad[i];
    }
}

//标签赋值
void Students::set_s_tags(string st[])
{
    for (int i = 0; i < 10; i++)
    {
        if (st[i] == "")break;
        s_tags[i] = st[i];
    }
}

//获得标签
string * Students::get_s_tags()
{
    string *s_t = s_tags;
    return s_t;
}

//获得学生号
string Students::get_stu_no()
{
    return stu_no;
}

//获得志愿部门
string Students::get_app_dep(int n)
{
    return app_dep[n - 1];
}

//空闲时间计算 结果存入空闲时间数组
void Students::get_time()
{
    for (int i = 0; i < 10; i++)
    {
        //日期处理
        if (free_t[i] == "")
            break;
        int day = 0;
        string str = free_t[i];
        if (str[2] == 'e')
            day = 1;
        else if (str[0] == 'W')
            day = 2;
        else if (str[1] == 'h')
            day = 3;
        else if (str[0] == 'F')
            day = 4;
        else if (str[1] == 'a')
            day = 5;
        else
            day = 6;

        //开始时间-小时
        stringstream h1_ss;
        int begin = 0;
        string h1_s = "";
        int h1;
        int loc = 4;
        if (str[loc] < '0' || str[loc] > '9')
            loc++;
        h1_s += str[loc];
        loc++;
        if (str[loc] >= '0' && str[loc] <= '9')
        {
            h1_s += str[loc];
            loc++;
        }
        h1_ss << h1_s;
        h1_ss >> h1;
        begin = begin + h1 * 60;

        //开始时间-分钟
        stringstream m1_ss;
        loc++;
        string m1_s = "";
        int m1;

        m1_s += str[loc];
        loc++;
        m1_s += str[loc];
        m1_ss << m1_s;
        m1_ss >> m1;
        begin += m1;
        s_time[day][2 * i] = begin;

        //结束时间-小时
        stringstream h2_ss;
        int end = 0;
        string h2_s = "";
        int h2;
        loc++;
        if (str[loc] < '0' || str[loc] > '9')
            loc++;
        h2_s += str[loc];
        loc++;
        if (str[loc] >= '0' && str[loc] <= '9')
        {
            h2_s += str[loc];
            loc++;
        }
        h2_ss << h2_s;
        h2_ss >> h2;
        end = end + h2 * 60;

        //结束时间-分钟
        stringstream m2_ss;
        loc++;
        string m2_s = "";
        int m2;
        m2_s += str[loc];
        loc++;
        m2_s += str[loc];
        m2_ss << m2_s;
        m2_ss >> m2;
        end += m2;
        s_time[day][2 * i + 1] = end;
    }
}