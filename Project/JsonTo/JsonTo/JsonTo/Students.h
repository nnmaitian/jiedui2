#pragma once
#include <string>
using namespace std;

class Students
{

private:
    string free_t[20];//学生空闲时间
    string stu_no;//学生号
    string app_dep[5];//学生志愿部门
    string s_tags[10];//学生标签

public:
    int s_time[7][40];//空闲时间数组   

    void set_free_t(string ft[]);//空闲时间赋值
    void set_stu_no(string sn);//学生号赋值
    void set_app_dep(string ad[]);//志愿部门赋值
    void set_s_tags(string st[]);//标签赋值

    void get_time();//空闲时间计算
    string get_stu_no();//获得学生号
    string get_app_dep(int n);//获得志愿部门
    string *get_s_tags();//获得标签

};