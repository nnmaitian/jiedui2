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
int acc[20];//��ȡ������������
int assign[300];//ѧ�������������

/*
�/����ʱ��ƥ�亯��
���룺����ѧ������󣬵������������
���أ�ѧ���Ͳ��Ŷ���ʱ��ƥ�����
*/
int cmp_time(Students s, Departments d)
{
    int cnt = 0;//����ͳ��

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (d.d_time[i][j] == 0)
            //����ǰʱ���Ϊ0�������ȡ(һ��ʱ�����ʱ��������ռ2��λ�ã������λ������һʱ��ζ�ȡ)
            {
                j++;
                continue;
            }
            for (int k = 0; k < 40; k++)
            {
                if (s.s_time[i][k] == 0)
                //����ǰʱ���Ϊ0�������ȡ(һ��ʱ�����ʱ��������ռ2��λ�ã������λ������һʱ��ζ�ȡ)
                {
                    k++;
                    continue;
                }
                if (d.d_time[i][j] >= s.s_time[i][k] && d.d_time[i][j + 1] <= s.s_time[i][k + 1])
                //��ʱ���ƥ���������һ
                    cnt++;
                //�����������ȡ(һ��ʱ�����ʱ��������ռ2��λ�ã������λ������һʱ��ζ�ȡ)
                k++;
            }
        }
    }
    return cnt;
}

//���ѧ����ǩ�Ƿ��ڲ��ű�ǩ��
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

//���ѧ���Ƿ��ڲ������³�Ա��
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
��Ȥƥ�亯��
���룺����ѧ������󣬵������������
���أ�ѧ���Ͳ��Ŷ�����Ȥƥ�����
*/
int cmp_tags(Students s, Departments d)
{
    int cnt = 0;

    //��ȡѧ���Ͳ�����Ȥ����
    string *s_t = s.get_s_tags();
    string *d_t = d.get_d_tags();

    //ƥ��
    for (int i = 0; i < 10; i++)
    {
        if (s_t[i] == "")
            break;
        if (tagInArray(d_t, s_t[i]))
            cnt++;
    }

    return cnt;
}

//sort����-cmp
bool cmp(Departments::acc_stu &a, Departments::acc_stu &b)
{
    return a.s_sum > b.s_sum ? true : false;
}

//������ֵΪsum�����Ϊno��ѧ���������³�Ա���鲢����
void insert(Departments::acc_stu *arr, int sum, int no, int lmt)
{
    arr[lmt - 1].s_no = no;
    arr[lmt - 1].s_sum = sum;
    sort(arr, arr + lmt, cmp);
}

int main()
{
    int num = readJson(Stu, Dep);//���ļ�����

    int stu_num = num / 100;//ѧ����
    int dep_num = num % 100;//������
    int sum = 0;//���ȼ���ֵ

    //����ѧ������ʱ�� �������ʱ������
    for (int i = 0; i < stu_num; i++)
    {
        Stu[i].get_time();
    }

    //���㲿�Żʱ�� ����ʱ������
    for (int i = 0; i < dep_num; i++)
    {
        Dep[i].get_time();
    }

    //ǰ���ַ���
    //־Ը����ԭ�� ѧ�����ȼ�����־Ըλ�á�ʱ��ƥ���������ǩƥ���������Ȩ�ؼ��� Ȩ�طֱ�Ϊ 10��5��2
    for (int q = 0; q < 5; q++)
    {
        for (int i = 0; i < stu_num; i++)
        {
            if (Stu[i].get_app_dep(q + 1) != "")
                //ѧ����q��־ԸΪ���򲻽��в���
            {
                for (int j = 0; j < dep_num; j++)
                    //��־Ը�벿��ƥ��
                {
                    if (Stu[i].get_app_dep(q + 1) == Dep[j].get_dep_no())
                        //��ƥ��
                    {
                        if (noInArray(Dep[j].a_s, i))
                            //��ѧ���ѽ���ò������³�Ա������������
                        {
                            continue;
                        }

                        if (acc[j] < Dep[j].get_mem_lmt() && cmp_time(Stu[i], Dep[j]) >= 1)
                            //־Ը��������δ����ʱ������ƥ��һ��
                        {
                            acc[j]++;//��������������һ
                            sum = (5 - q) * 10 + cmp_time(Stu[i], Dep[j]) * 5 + cmp_tags(Stu[i], Dep[j]) * 2;//����ѧ�����ȼ�
                            insert(Dep[j].a_s, sum, i, Dep[j].get_mem_lmt());//���������������ѧ��
                            assign[i]++;//����ѧ�������������
                        }
                        else if (acc[j] == Dep[j].get_mem_lmt() && cmp_time(Stu[i], Dep[j]) >= 1)
                            //־Ը��������������ʱ������ƥ��һ��
                        {
                            sum = (5 - q) * 10 + cmp_time(Stu[i], Dep[j]) * 5 + cmp_tags(Stu[i], Dep[j]) * 2;//����ѧ�����ȼ�
                            if (sum > Dep[j].a_s[Dep[j].get_mem_lmt() - 1].s_sum)
                                //��ѧ�����ȼ����ڲ����������������ȼ���ͳ�Ա����ȡ��
                            {
                                assign[Dep[j].a_s[Dep[j].get_mem_lmt() - 1].s_no]--;//��̭ѧ�������������
                                insert(Dep[j].a_s, sum, i, Dep[j].get_mem_lmt());//���������������ѧ��
                                assign[i]++;//����ѧ�������������
                            }
                        }
                    }
                }

            }
        }
    }

    //�����ַ���
    for (int k = 0; k < dep_num; k++)
    {
        if (acc[k] < Dep[k].get_mem_lmt())
            //�ҳ�δ���Ĳ���
        {
            for (int w = 0; w < stu_num; w++)
            {
                if (assign[w] == 0)
                    //��ѧ��δ�����κβ���
                {
                    if (acc[k] < Dep[k].get_mem_lmt() && cmp_time(Stu[w], Dep[k]) >= 1 && cmp_tags(Stu[w], Dep[k]) >= 1)
                        //־Ը��������δ����ʱ������ƥ��һ���ұ�ǩ����ƥ��һ��
                    {
                        acc[k]++;//��������������һ
                        sum = cmp_time(Stu[w], Dep[k]) + 2 * cmp_tags(Stu[w], Dep[k]);//����ѧ�����ȼ�
                        insert(Dep[k].a_s, sum, w, Dep[k].get_mem_lmt());//���������������ѧ��
                        assign[w]++;//����ѧ�������������
                    }
                    else if (acc[k] == Dep[k].get_mem_lmt() && cmp_time(Stu[w], Dep[k]) >= 1 && cmp_tags(Stu[w], Dep[k]) >= 1)
                        //־Ը��������������ʱ������ƥ��һ���ұ�ǩ����ƥ��һ��
                    {
                        sum = cmp_time(Stu[w], Dep[k]) + 2 * cmp_tags(Stu[w], Dep[k]);//����ѧ�����ȼ�
                        if (sum > Dep[k].a_s[Dep[k].get_mem_lmt() - 1].s_sum)
                        {
                            assign[Dep[k].a_s[Dep[k].get_mem_lmt() - 1].s_no]--;//��̭ѧ�������������
                            insert(Dep[k].a_s, sum, w, Dep[k].get_mem_lmt());//���������������ѧ��
                            assign[w]++;//����ѧ�������������
                        }
                    }
                }
            }
        }
    }

    //дJson
    Json::Value root;//���ڵ�

    Json::Value unlucky_student;//��ù���ӽڵ�233
    Json::Value admitted;//������������ڵ�
    Json::Value unlucky_department;//��ù���Žڵ�

    //�ڵ㸳ֵ
    root["unlucky_student"] = Json::Value(unlucky_student);
    root["admitted"] = Json::Value(admitted);
    root["unlucky_department"] = Json::Value(unlucky_department);

    //unlucky_student ��ֵ
    for (int i = 0; i < stu_num; i++)
    {
        if (assign[i] == 0)
        {
            root["unlucky_student"].append(Stu[i].get_stu_no());
        }
    }

    //admitted ��ֵ
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

    //unlucky_department ��ֵ
    for (int i = 0; i < dep_num; i++)
    {
        if (acc[i] == 0)
        {
            root["unlucky_department"].append(Dep[i].get_dep_no());
        }
    }

    //�������
    Json::StyledWriter sw;

    //������ļ�
    ofstream os;
    os.open("output_data.txt", ios::trunc);
    os << sw.write(root);
    os.close();

    return 0;
}