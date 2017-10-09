#pragma once
#include <string>
using namespace std;

class Departments
{

private:
    string e_sche[10];//部门活动时间
    int mem_lmt;//部门纳新人数
    string dep_no;//部门号
    string d_tags[10];//部门标签
    
public:
    struct acc_stu
    {
        acc_stu() { s_no = 0; s_sum = 0; }
        int s_no;
        int s_sum;
    };//纳新成员结构体
    acc_stu a_s[15];//纳新成员结构体数组

    int d_time[7][20];//活动时间数组

    void set_e_sche(string es[]);//活动时间赋值
    void set_mem_lmt(int ml);//纳新人数赋值
    void set_dep_no(string dn);//部门号赋值
    void set_d_tags(string dt[]);//标签赋值

    void get_time();//计算活动时间
    int get_mem_lmt();//获得部门纳新人数
    string get_dep_no();//获得部门编号
    string *get_d_tags();//获得部门标签

};
