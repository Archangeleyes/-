// ���ݽṹʵ��4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "test.h"

int main()
{
	ifstream test;
	ifstream * pTest = &test;
	Syllabus TestSyllabus(pTest);
	cout << "�������ļ�����";
	char doc[100];
	cin >> doc;
	TestSyllabus.Read(doc);
	TestSyllabus.SetAllTerm();
	TestSyllabus.Show();
	system("PAUSE");
    return 0;
}

