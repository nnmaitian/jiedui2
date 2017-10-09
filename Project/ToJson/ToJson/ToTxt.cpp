#include "stdafx.h"
/*#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "Departments.h"
#include "Students.h"
using namespace std;

Students stu[300];
Departments dep[20];

int main()
{
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

    ofstream outfile;
    outfile.open("input_data.txt", ios::trunc);
    outfile << "{\n\"students\":[\n";
    for (int i = 0; i < stu_num; i++)
    {
        outfile << "{\n\"free_time\":[\n";
        for (int j = 0; j < 30; j++)
        {
            if (stu[i].free_t[j] != "")
            {
                if (j != 0)
                {
                    outfile << ",\n";
                }
                outfile << stu[i].free_t[j];
            }
        }
        outfile << "\n],\n\"student_no\":";
        outfile << stu[i].stu_no;
        outfile << ",\n\"applications_department\":[\n";
        for (int j = 0; j < 5; j++)
        {
            if (stu[i].app_dep[j] != "")
            {
                if (j != 0)
                {
                    outfile << ",\n";
                }
                outfile << stu[i].app_dep[j];
            }
        }
        outfile << "\n],\n\"tags\":[\n";
        for (int j = 0; j < 10; j++)
        {
            if (stu[i].s_tags[j] != "")
            {
                if (j != 0)
                {
                    outfile << ",\n";
                }
                outfile << stu[i].s_tags[j];
            }
        }
        if (i == stu_num - 1)
        {
            outfile << "\n]\n}\n";
        }
        else
        {
            outfile << "\n]\n},\n";
        }
    }
    outfile << "],\n\"departments\":[\n";
    for (int i = 0; i < dep_num; i++)
    {
        outfile << "{\n\"event_schedules\":[\n";
        for (int j = 0; j < 10; j++)
        {
            if (dep[i].e_sche[j] != "")
            {
                if (j != 0)
                {
                    outfile << ",\n";
                }
                outfile << dep[i].e_sche[j];
            }
        }
        outfile << "\n],\n\"menber_limit\":";
        outfile << dep[i].men_lmt;
        outfile << ",\n\"department_no\":";
        outfile << dep[i].dep_no;
        outfile << ",\n\"tags\":[\n";
        for (int j = 0; j < 10; j++)
        {
            if (dep[i].d_tags[j] != "")
            {
                if (j != 0)
                {
                    outfile << ",\n";
                }
                outfile << dep[i].d_tags[j];
            }
        }
        if (i == dep_num - 1)
        {
            outfile << "\n]\n}\n";
        }
        else
        {
            outfile << "\n]\n},\n";
        }
    }
    outfile << "]\n}\n";
    outfile.close();
    return 0;
}*/