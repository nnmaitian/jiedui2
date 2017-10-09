#include "stdafx.h"
#include <iostream>
using namespace std;

bool inArray(int a[], int num, int val)
{
    for (int i = 0; i < num; i++)
    {
        if (val == a[i])
        {
            return true;
        }
    }
    return false;
}