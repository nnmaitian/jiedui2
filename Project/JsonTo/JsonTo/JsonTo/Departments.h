#pragma once
#include <string>
using namespace std;

class Departments
{

private:
    string e_sche[10];//���Żʱ��
    int mem_lmt;//������������
    string dep_no;//���ź�
    string d_tags[10];//���ű�ǩ
    
public:
    struct acc_stu
    {
        acc_stu() { s_no = 0; s_sum = 0; }
        int s_no;
        int s_sum;
    };//���³�Ա�ṹ��
    acc_stu a_s[15];//���³�Ա�ṹ������

    int d_time[7][20];//�ʱ������

    void set_e_sche(string es[]);//�ʱ�丳ֵ
    void set_mem_lmt(int ml);//����������ֵ
    void set_dep_no(string dn);//���źŸ�ֵ
    void set_d_tags(string dt[]);//��ǩ��ֵ

    void get_time();//����ʱ��
    int get_mem_lmt();//��ò�����������
    string get_dep_no();//��ò��ű��
    string *get_d_tags();//��ò��ű�ǩ

};
