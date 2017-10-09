#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include "json.h"
#include "Students.h"
#include "Departments.h"
using namespace std;

Students stu[300];
Departments dep[20];

int main()
{
    srand((int)time(0));
    int stu_num, dep_num;
    cout << "学生数(不超过300):";
    cin >> stu_num;
    cout << "部门数(不超过20):";
    cin >> dep_num;
    for (int i = 0; i < stu_num; i++)
    {
        stu[i].construct();
    }
    for (int i = 0; i < dep_num; i++)
    {
        dep[i].construct();
    }
    
    Json::Value root;

    Json::Value students;
    Json::Value departments;

    root["students"] = Json::Value(students);
    root["departments"] = Json::Value(departments);
    
    for (int i = 0; i < stu_num; i++)
    {
        Json::Value Stu;
        for each(string s in stu[i].free_t)
        {
            if (s == "") break;
            Stu["free_time"].append(s);
        }
        Stu["student_no"] = Json::Value(stu[i].stu_no);
        for each(string s in stu[i].app_dep)
        {
            if (s == "") break;
            Stu["applications_department"].append(s);
        }
        for each(string s in stu[i].s_tags)
        {
            if (s == "") break;
            Stu["tags"].append(s);
        }
        root["students"].append(Stu);
    }

    for (int i = 0; i < dep_num; i++)
    {
        Json::Value Dep;
        for each(string s in dep[i].e_sche)
        {
            if (s == "") break;
            Dep["event_schedules"].append(s);
        }
        Dep["member_limit"] = Json::Value(dep[i].mem_lmt);
        Dep["department_no"] = Json::Value(dep[i].dep_no);
        for each(string s in dep[i].d_tags)
        {
            if (s == "") break;
            Dep["tags"].append(s);
        }       
        root["departments"].append(Dep);
    }

    //缩进输出
    Json::StyledWriter sw;

    //输出到文件
    ofstream os;
    os.open("intput_data.json", ios::trunc);
    os << sw.write(root);
    os.close();
    cout << "生成input_data.json成功！" << endl;
    return 0;
}