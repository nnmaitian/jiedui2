#include "stdafx.h"
#include <iostream>
#include <string>
#include "common.h"
#include "Departments.h"
using namespace std;
int Departments::d_exist[20] = {};
void Departments::construct()
{
    //事务时间表
    int es_num = rand() % 8 + 3;
    for (int i = 0; i < es_num; i++)
    {
        string d_week = week[rand() % 7];
        int clock = rand() % 13 + 8;
        string d_time = to_string(clock) + ":00~" + to_string(clock + 1) + ":00";
        e_sche[i] = d_week + d_time;
    }

    //纳新数限制
    mem_lmt = rand() % 6 + 10;

    //部门号
    
    int rd = rand() % 20;
    while (d_exist[rd] == 1)
    {
        rd = rand() % 20;
    }
    dep_no = dep[rd];
    d_exist[rd] = 1;

    //标签
    int tags_num = rand() % 4 + 2;
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
        d_tags[i] = tags[tags_arr[i]];
    }

}