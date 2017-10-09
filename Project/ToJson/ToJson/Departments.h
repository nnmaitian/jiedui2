#pragma once
#include <string>
using namespace std;

class Departments
{
public:
    string e_sche[10];
    int mem_lmt;
    string dep_no;
    string d_tags[10];

    static int d_exist[20];

    void construct();
};
