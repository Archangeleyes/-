// 数据结构实验4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"

int main()
{
	ifstream test;
	ifstream * pTest = &test;
	Syllabus TestSyllabus(pTest);
	cout << "请输入文件名：";
	char doc[100];
	cin >> doc;
	TestSyllabus.Read(doc);
	TestSyllabus.SetAllTerm();
	TestSyllabus.Show();
	system("PAUSE");
    return 0;
}

