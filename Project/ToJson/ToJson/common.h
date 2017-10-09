#pragma once
#include <string>
using namespace std;

const string week[] = { "Mon.","Tues." ,"Wed." ,"Thu." ,"Fri.","Sat.","Sun." };
const string dep[] = { "D001", "D002", "D003", "D004", "D005",
"D006", "D007", "D008", "D009", "D010",
"D011", "D012", "D013", "D014", "D015",
"D016", "D017", "D018", "D019", "D020" };
const string tags[] = { "film", "English", "reading", "music", "dance",
"basketball", "chess", "swim", "soccer", "pingpong",  
"writing", "sports", "volleyball", "jogging", "painting", 
"anime", "game", "football", "kungfu", "food" };
bool inArray(int a[], int num, int val);