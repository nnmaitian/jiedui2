#pragma once
#include <string>
using namespace std;

class Students
{

private:
    string free_t[20];//ѧ������ʱ��
    string stu_no;//ѧ����
    string app_dep[5];//ѧ��־Ը����
    string s_tags[10];//ѧ����ǩ

public:
    int s_time[7][40];//����ʱ������   

    void set_free_t(string ft[]);//����ʱ�丳ֵ
    void set_stu_no(string sn);//ѧ���Ÿ�ֵ
    void set_app_dep(string ad[]);//־Ը���Ÿ�ֵ
    void set_s_tags(string st[]);//��ǩ��ֵ

    void get_time();//����ʱ�����
    string get_stu_no();//���ѧ����
    string get_app_dep(int n);//���־Ը����
    string *get_s_tags();//��ñ�ǩ

};