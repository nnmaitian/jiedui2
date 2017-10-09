#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "json.h"
#include "Students.h"
#include "Departments.h"
using namespace std;

int readJson(Students Stu[], Departments Dep[])
{
    Json::Reader reader;
    Json::Value root;

    //从文件中读取
    ifstream ifs;
    ifs.open("intput_data.txt");

    if (reader.parse(ifs, root))
    {   
        //学生
        for (int i = 0; i < root["students"].size(); i++)
        {
            //空闲时间表
            string ft[20];
            for (int j = 0; j < root["students"][i]["free_time"].size(); j++)
            {
                string free_t = root["students"][i]["free_time"][j].asString();
                ft[j] = free_t;
            }
            Stu[i].set_free_t(ft);

            //学号
            string stu_no = root["students"][i]["student_no"].asString();
            Stu[i].set_stu_no(stu_no);

            //志愿部门
            string ad[5];
            for (int j = 0; j < root["students"][i]["applications_department"].size(); j++)
            {
                string app_dep = root["students"][i]["applications_department"][j].asString();
                ad[j] = app_dep;
            }
            Stu[i].set_app_dep(ad);

            //标签
            string st[10];
            for (int j = 0; j < root["students"][i]["tags"].size(); j++)
            {
                string s_tag = root["students"][i]["tags"][j].asString();
                st[j] = s_tag;
            }
            Stu[i].set_s_tags(st);
        }


        //部门
        for (int i = 0; i < root["departments"].size(); i++)
        {
            //活动时间表
            string es[10];
            for (int j = 0; j < root["departments"][i]["event_schedules"].size(); j++)
            {
                string e_sche = root["departments"][i]["event_schedules"][j].asString();
                es[j] = e_sche;
            }
            Dep[i].set_e_sche(es);

            //纳新人数限制
            int mem_lmt = root["departments"][i]["member_limit"].asInt();
            Dep[i].set_mem_lmt(mem_lmt);

            //部门号
            string dep_no = root["departments"][i]["department_no"].asString();
            Dep[i].set_dep_no(dep_no);

            //标签
            string dt[10];
            for (int j = 0; j < root["departments"][i]["tags"].size(); j++)
            {
                string d_tag = root["departments"][i]["tags"][j].asString();
                dt[j] = d_tag;
            }
            Dep[i].set_d_tags(dt);
        }
    }

    ifs.close();

    //返回(学生数量 * 100 + 部门数量) 用于计算学生和部门数量
    return root["students"].size() * 100 + root["departments"].size();
}
