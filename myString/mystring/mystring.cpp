// mystring.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<cstring>
#include<iostream>
using namespace std;


/*
 * 取字符串s的start位置开始到end结束长度的子串
 */

void strsubstr(string s,int start,int end)
{
	cout << s.substr(start, end) << endl;
	
}

/*
 * 获得字符串大小
 */
void strgetlength(string s)
{
	cout << s.size() << endl;
}


/*
 * 比较两个字符串，compare（）返回值大于0，则s>t；返回值=0，则s=t；返回值小于0，则s<t；
 */
void strcompare(string s,string t)
{
	if(s.compare(t)<0)
	{
		cout << s << " is smaller than " << t << endl;
	}else if(s.compare(t)==0)
	{
		cout << s << " is equal to "<<t << endl;
	}else
	{
		cout << s << "is bigger than " << t << endl;
	}
}

/*
 * 清空字符串
 */
void clearstring(string &s)
{
	s.clear();
	cout << "The string is empty now" << endl;
}


/*
 * 获得字串sub在字符串s中的位置
 */
void index(string s,string sub)
{
	cout<<"The index of  "<<sub<<" in "<<s<<" is "<<s.find(sub)<<endl;
}

/*
 * 连接字符串，将t连接到s后面
 */
void stringcontac(string &s,string t)
{
	stringcontac(s, t);
	cout << s << endl;
}

/*
 * 替换字符串，将s中的t子串替换为v
 */
void replacestr(string &s,string t,string v)
{
	s.replace(s.find(t),t.size(),v);
	cout << s << endl;
}





int main()
{
	string s = "abcdefghijklmnopqrstuvwxyz";
	string t="efghijk";
	string v = "stuvwxyz";
	int n;
	cout << "测试字符串为：" << endl;
	cout << s << endl;
	cout << t << endl;
	cout << v << endl;
	cout << "请选择字符串操作:1. 取子串  2.获取字符串大小  3.字符串比较  4.清空字符串  5.获取子串位置  6.连接字符串  7.替换字符串   0.退出" << endl;
	
	while(true)
	{
		cin >> n;
		switch(n)
		{
		case 1:
			int start, end;
			cout << "请输入获取s的子串的起始和终止位置：" << endl;
			cin >> start >> end;
			strsubstr(s, start, end);
			break;
		case 2:
			strgetlength(s);
			break;
		case 3:
			strcompare(s, t);
			break;
		case 4:
			clearstring(v);
			break;
		case 5:
			index(s, t);
			break;
		case 6:
			stringcontac(s, t);
			break;
		case 7:
			replacestr(s, t, v);
			break;
		case 0:
			return 0;
			break;
			
		}
	}
    return 0;
}

