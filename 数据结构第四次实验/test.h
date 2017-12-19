//#include "stdafx.h"
#include"utility.h"

class Course
{
public:
	char CourseNumber[5];		//课程编号
	char CourseName[100];		//课程名称
	int Period;					//学时数
	int term;					//指定开课学期
	char prerequisite1[5];		//先决条件1
	char prerequisite2[5];		//先决条件2

	Course(){}
	~Course(){}
	void SetTheTerm(int term0);	//设置开课学期
};

class Syllabus
{
private:
	ifstream * pInFile;			//输入文件
	int CourseCount[8];			//每学期的课程数
	Course courses[38];			//课程对象数组
public:
	Syllabus(){}
	Syllabus(ifstream * pTempIn)
	{//构造函数
		pInFile = pTempIn;
	}
	virtual ~Syllabus() {}//析构函数
	void Read(char * doc);			//读入文件数据并储存到各个节点中
	void SetAllTerm();		//进行排序并设置相应学期
	void Show();			//将结果打印到屏幕上
};

void Syllabus::Read(char * doc)
{
	int NoOFCourse = 0;
	char linebuf[100];
	(*pInFile).open(doc);
	int tempi = 0;
	(*pInFile) >> linebuf;
	while (!((*pInFile).eof()))
	{
		
		//先储存每学期的课程数
		
		if((linebuf[0]>='0'&&linebuf[0]<='9'))
		{
			if(linebuf[1]=='*')
			{
				CourseCount[tempi] = linebuf[0] - '0';
				tempi++;
			}
		}
		
		//再储存
		else if (linebuf[0] == 'c')
		{
			if (NoOFCourse == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					courses[NoOFCourse].CourseNumber[i] = linebuf[i];
				}
			}
			else
			{ 
				(*pInFile) >> courses[NoOFCourse].CourseNumber;		//课程编号
			}
			(*pInFile) >> courses[NoOFCourse].CourseName;		//课程名称
			(*pInFile) >> courses[NoOFCourse].Period;			//学时数
			(*pInFile) >> courses[NoOFCourse].term;				//开课学期
			(*pInFile) >> courses[NoOFCourse].prerequisite1;	//先决条件1
			(*pInFile) >> courses[NoOFCourse].prerequisite2;	//先决条件2
			NoOFCourse++;		//下标自增1
			if (NoOFCourse == 38)
				break;
			continue;
		}
		(*pInFile) >> linebuf;	
	}
}

void Syllabus::SetAllTerm()
{//设置每个课程所在学期，相当于进行拓扑排序的过程
	int TermCourseCnt[8];//用于检验某学期课程是否已经安排完毕的数组
	for (int i = 0; i < 8; i++)//初始化
		TermCourseCnt[i] = 0;

	//先将已经确定相应学期的课程安排进相应学期
	for (int i = 0; i < 38; i++)
	{
		if (courses[i].term != 0)
		{
			TermCourseCnt[courses[i].term - 1]++;
		}
	}

	for (int i = 0; i < 38; i++)
	{
		if (courses[i].term == 0)
		{//未安排学期的课程
			string temp1 = courses[i].prerequisite1;
			string temp2 = courses[i].prerequisite2;
			if ((temp1 == temp2) && temp1 == "c00")
			{
				for (int term = 1; term <= 8; term++)
				{//对于每个没有先决条件的课程，按学期轮排下去
					if (TermCourseCnt[term-1] < CourseCount[term-1])
					{
						courses[i].SetTheTerm(term);
						TermCourseCnt[term-1]++;
						break;
					}
				}
			}

			else if (temp1 > temp2)
			{
				for (int j = 0; j < 38; j++)
				{
					string tempcom = courses[j].CourseNumber;
					if (temp1 == tempcom)
					{//用较大的先决条件去匹配相应的课程
						for (int temp = courses[j].term; temp <= 8; temp++)
						{
							if (TermCourseCnt[temp] < CourseCount[temp])
							{
								courses[i].SetTheTerm(temp + 1);
								TermCourseCnt[temp]++;
								break;
							}
						}
					}
				}
			}

			else if (temp2 > temp1)
			{
				for (int j = 0; j < 38; j++)
				{
					string tempcom = courses[j].CourseNumber;
					if (temp2 == tempcom)
					{
						for (int temp = courses[j].term; temp <= 8; temp++)
						{
							if (TermCourseCnt[temp] < CourseCount[temp])
							{
								courses[i].SetTheTerm(temp + 1);
								TermCourseCnt[temp]++;
								break;
							}
						}
					}
				}
			}

		}
	}
}

void Syllabus::Show()
{
	for (int i = 1; i <= 8; i++)
	{
		cout << "第" << i << "学期课程：";
		for (int j = 0; j < 38; j++)
		{
			if (courses[j].term == i)
			{
				cout << courses[j].CourseName << " ";
			}
		}
		cout << endl;
	}
}

void Course::SetTheTerm(int term0)
{
	term = term0;
}