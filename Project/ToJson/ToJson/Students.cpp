#include "stdafx.h"
#include <iostream>
#include <string>
#include "common.h"
#include "Students.h"
using namespace std;

/*
string free_t[20];
string stu_no;
string app_dep[5];
string s_tags[10];
*/

void Students::construct()
{
    //空闲时间
    int ft_num = rand() % 16 + 5;
    for (int i = 0; i < ft_num; i++)
    {
        string s_week = week[rand() % 7];
        int clock = rand() % 13 + 8;
        string s_time = to_string(clock) + ":00~" + to_string(clock + 2) + ":00";
        free_t[i] = s_week + s_time;
    }

    //学号
    stu_no = "";

    int clg = rand() % 15 + 1;
    if (clg < 10)
    {
        stu_no += '0';
    }
    stu_no += to_string(clg);

    int year = rand() % 4 + 14;
    stu_no += to_string(year);

    int dept = rand() % 12 + 1;
    if (dept < 10)
    {
        stu_no += '0';
    }
    stu_no += to_string(dept);

    int cls = rand() % 6 + 1;
    stu_no += to_string(cls);

    int no = rand() % 50 + 1;
    if (no < 10)
    {
        stu_no += '0';
    }
    stu_no += to_string(no);
    
    //志愿部门
    int ad_num = rand() % 5 + 1;
    int ad_arr[10];
    for (int i = 0; i < ad_num; i++)
    {
        int rdd = rand() % 10;
        while (inArray(ad_arr, ad_num, rdd))
        {
            rdd = rand() % 10;
        }
        ad_arr[i] = rdd;
    }
    for (int i = 0; i < ad_num; i++)
    {
        app_dep[i] = dep[ad_arr[i]];
    }

    //标签
    int tags_num = rand() % 2 + 9;
    int tags_arr[20];
    for (int i = 0; i < tags_num; i++)
    {
        int rdd = rand() % 20;
        while (inArray(tags_arr, tags_num, rdd))
        {
            rdd = rand() % 20;
        }
        tags_arr[i] = rdd;
    }
    for (int i = 0; i < tags_num; i++)
    {
        s_tags[i] = tags[tags_arr[i]];
    }
}