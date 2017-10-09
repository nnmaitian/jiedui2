#include "stdafx.h"
#include "Students.h"
#include "Departments.h"
#include "ReadJson.h"
#include "json.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <fstream>
using namespace std;

Students Stu[300];
Departments Dep[20];
int acc[20];//存取部门纳新人数
int assign[300];//学生分配情况数组

/*
活动/空闲时间匹配函数
输入：单个学生类对象，单个部门类对象
返回：学生和部门对象时间匹配次数
*/
int cmp_time(Students s, Departments d)
{
    int cnt = 0;//次数统计

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (d.d_time[i][j] == 0)
            //若当前时间点为0则继续读取(一个时间段在时间数组中占2个位置，向后两位进行下一时间段读取)
            {
                j++;
                continue;
            }
            for (int k = 0; k < 40; k++)
            {
                if (s.s_time[i][k] == 0)
                //若当前时间点为0则继续读取(一个时间段在时间数组中占2个位置，向后两位进行下一时间段读取)
                {
                    k++;
                    continue;
                }
                if (d.d_time[i][j] >= s.s_time[i][k] && d.d_time[i][j + 1] <= s.s_time[i][k + 1])
                //若时间段匹配则计数加一
                    cnt++;
                //计数后继续读取(一个时间段在时间数组中占2个位置，向后两位进行下一时间段读取)
                k++;
            }
        }
    }
    return cnt;
}

//检测学生标签是否在部门标签中
bool tagInArray(string a[], string val)
{
    for (int i = 0; i < 10; i++)
    {
        if (a[i] == "")
            break;
        if (a[i] == val)
            return true;
    }
    return false;
}

//检测学生是否在部门纳新成员中
bool noInArray(Departments::acc_stu a[], int val)
{
    for (int i = 0; i < 15; i++)
    {
        if (a[i].s_no == 0)
            break;
        if (a[i].s_no == val)
            return true;
    }
    return false;
}

/*
兴趣匹配函数
输入：单个学生类对象，单个部门类对象
返回：学生和部门对象兴趣匹配次数
*/
int cmp_tags(Students s, Departments d)
{
    int cnt = 0;

    //获取学生和部门兴趣数组
    string *s_t = s.get_s_tags();
    string *d_t = d.get_d_tags();

    //匹配
    for (int i = 0; i < 10; i++)
    {
        if (s_t[i] == "")
            break;
        if (tagInArray(d_t, s_t[i]))
            cnt++;
    }

    return cnt;
}

//sort函数-cmp
bool cmp(Departments::acc_stu &a, Departments::acc_stu &b)
{
    return a.s_sum > b.s_sum ? true : false;
}

//将优先值为sum，序号为no的学生插入纳新成员数组并排序
void insert(Departments::acc_stu *arr, int sum, int no, int lmt)
{
    arr[lmt - 1].s_no = no;
    arr[lmt - 1].s_sum = sum;
    sort(arr, arr + lmt, cmp);
}

int main()
{
    int num = readJson(Stu, Dep);//从文件读入

    int stu_num = num / 100;//学生数
    int dep_num = num % 100;//部门数
    int sum = 0;//优先级数值

    //计算学生空闲时间 存入空闲时间数组
    for (int i = 0; i < stu_num; i++)
    {
        Stu[i].get_time();
    }

    //计算部门活动时间 存入活动时间数组
    for (int i = 0; i < dep_num; i++)
    {
        Dep[i].get_time();
    }

    //前五轮分配
    //志愿优先原则 学生优先级按照志愿位置、时间匹配次数、标签匹配次数进行权重计算 权重分别为 10、5、2
    for (int q = 0; q < 5; q++)
    {
        for (int i = 0; i < stu_num; i++)
        {
            if (Stu[i].get_app_dep(q + 1) != "")
                //学生第q个志愿为空则不进行操作
            {
                for (int j = 0; j < dep_num; j++)
                    //将志愿与部门匹配
                {
                    if (Stu[i].get_app_dep(q + 1) == Dep[j].get_dep_no())
                        //若匹配
                    {
                        if (noInArray(Dep[j].a_s, i))
                            //若学生已进入该部门纳新成员数组则不做考虑
                        {
                            continue;
                        }

                        if (acc[j] < Dep[j].get_mem_lmt() && cmp_time(Stu[i], Dep[j]) >= 1)
                            //志愿部门人数未满且时间至少匹配一次
                        {
                            acc[j]++;//部门纳新人数加一
                            sum = (5 - q) * 10 + cmp_time(Stu[i], Dep[j]) * 5 + cmp_tags(Stu[i], Dep[j]) * 2;//计算学生优先级
                            insert(Dep[j].a_s, sum, i, Dep[j].get_mem_lmt());//向部门纳新数组插入学生
                            assign[i]++;//纳入学生分配情况更新
                        }
                        else if (acc[j] == Dep[j].get_mem_lmt() && cmp_time(Stu[i], Dep[j]) >= 1)
                            //志愿部门人数已满且时间至少匹配一次
                        {
                            sum = (5 - q) * 10 + cmp_time(Stu[i], Dep[j]) * 5 + cmp_tags(Stu[i], Dep[j]) * 2;//计算学生优先级
                            if (sum > Dep[j].a_s[Dep[j].get_mem_lmt() - 1].s_sum)
                                //若学生优先级大于部门纳新数组中优先级最低成员则将其取代
                            {
                                assign[Dep[j].a_s[Dep[j].get_mem_lmt() - 1].s_no]--;//淘汰学生分配情况更新
                                insert(Dep[j].a_s, sum, i, Dep[j].get_mem_lmt());//向部门纳新数组插入学生
                                assign[i]++;//纳入学生分配情况更新
                            }
                        }
                    }
                }

            }
        }
    }

    //第六轮分配
    for (int k = 0; k < dep_num; k++)
    {
        if (acc[k] < Dep[k].get_mem_lmt())
            //找出未满的部门
        {
            for (int w = 0; w < stu_num; w++)
            {
                if (assign[w] == 0)
                    //若学生未进入任何部门
                {
                    if (acc[k] < Dep[k].get_mem_lmt() && cmp_time(Stu[w], Dep[k]) >= 1 && cmp_tags(Stu[w], Dep[k]) >= 1)
                        //志愿部门人数未满且时间至少匹配一次且标签至少匹配一次
                    {
                        acc[k]++;//部门纳新人数加一
                        sum = cmp_time(Stu[w], Dep[k]) + 2 * cmp_tags(Stu[w], Dep[k]);//计算学生优先级
                        insert(Dep[k].a_s, sum, w, Dep[k].get_mem_lmt());//向部门纳新数组插入学生
                        assign[w]++;//纳入学生分配情况更新
                    }
                    else if (acc[k] == Dep[k].get_mem_lmt() && cmp_time(Stu[w], Dep[k]) >= 1 && cmp_tags(Stu[w], Dep[k]) >= 1)
                        //志愿部门人数已满且时间至少匹配一次且标签至少匹配一次
                    {
                        sum = cmp_time(Stu[w], Dep[k]) + 2 * cmp_tags(Stu[w], Dep[k]);//计算学生优先级
                        if (sum > Dep[k].a_s[Dep[k].get_mem_lmt() - 1].s_sum)
                        {
                            assign[Dep[k].a_s[Dep[k].get_mem_lmt() - 1].s_no]--;//淘汰学生分配情况更新
                            insert(Dep[k].a_s, sum, w, Dep[k].get_mem_lmt());//向部门纳新数组插入学生
                            assign[w]++;//纳入学生分配情况更新
                        }
                    }
                }
            }
        }
    }

    //写Json
    Json::Value root;//根节点

    Json::Value unlucky_student;//倒霉孩子节点233
    Json::Value admitted;//部门纳新情况节点
    Json::Value unlucky_department;//倒霉部门节点

    //节点赋值
    root["unlucky_student"] = Json::Value(unlucky_student);
    root["admitted"] = Json::Value(admitted);
    root["unlucky_department"] = Json::Value(unlucky_department);

    //unlucky_student 赋值
    for (int i = 0; i < stu_num; i++)
    {
        if (assign[i] == 0)
        {
            root["unlucky_student"].append(Stu[i].get_stu_no());
        }
    }

    //admitted 赋值
    for (int i = 0; i < dep_num; i++)
    {
        Json::Value JDep;
        for (int j = 0; j < Dep[i].get_mem_lmt(); j++)
        {
            JDep["menber"].append(Stu[Dep[i].a_s[j].s_no].get_stu_no());
        }
        JDep["department_no"] = Json::Value(Dep[i].get_dep_no());
        root["admitted"].append(JDep);
    }

    //unlucky_department 赋值
    for (int i = 0; i < dep_num; i++)
    {
        if (acc[i] == 0)
        {
            root["unlucky_department"].append(Dep[i].get_dep_no());
        }
    }

    //缩进输出
    Json::StyledWriter sw;

    //输出到文件
    ofstream os;
    os.open("output_data.txt", ios::trunc);
    os << sw.write(root);
    os.close();

    return 0;
}