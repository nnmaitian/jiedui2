#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Departments.h"
using namespace std;

//�ʱ�丳ֵ
void Departments::set_e_sche(string es[])
{
    for (int i = 0; i < 10; i++)
    {
        e_sche[i] = es[i];
    }
}

//����������ֵ
void Departments::set_mem_lmt(int ml)
{
    mem_lmt = ml;
}

//���źŸ�ֵ
void Departments::set_dep_no(string dn)
{
    dep_no = dn;
}

//��ǩ��ֵ
void Departments::set_d_tags(string dt[])
{
    for (int i = 0; i < 10; i++)
    {
        d_tags[i] = dt[i];
    }
}

//��ò�����������
int Departments::get_mem_lmt()
{
    return mem_lmt;
}

//��ò��ű��
string Departments::get_dep_no()
{
    return dep_no;
}

//��ñ�ǩ
string * Departments::get_d_tags()
{
    string *d_t = d_tags;
    return d_t;
}

//����ʱ�� �������ʱ������
void Departments::get_time()
{
    for (int i = 0; i < 10; i++)
    {
        //���ڴ���
        if (e_sche[i] == "")
            break;
        int day = 0;
        string str = e_sche[i];
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

        //��ʼʱ��-Сʱ
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

        //��ʼʱ��-����
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
        d_time[day][2 * i] = begin;
        
        //����ʱ��-Сʱ
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

        //����ʱ��-����
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
        d_time[day][2 * i + 1] = end;
    }
}
