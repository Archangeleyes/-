//#include "stdafx.h"
#include"utility.h"

class Course
{
public:
	char CourseNumber[5];		//�γ̱��
	char CourseName[100];		//�γ�����
	int Period;					//ѧʱ��
	int term;					//ָ������ѧ��
	char prerequisite1[5];		//�Ⱦ�����1
	char prerequisite2[5];		//�Ⱦ�����2

	Course(){}
	~Course(){}
	void SetTheTerm(int term0);	//���ÿ���ѧ��
};

class Syllabus
{
private:
	ifstream * pInFile;			//�����ļ�
	int CourseCount[8];			//ÿѧ�ڵĿγ���
	Course courses[38];			//�γ̶�������
public:
	Syllabus(){}
	Syllabus(ifstream * pTempIn)
	{//���캯��
		pInFile = pTempIn;
	}
	virtual ~Syllabus() {}//��������
	void Read(char * doc);			//�����ļ����ݲ����浽�����ڵ���
	void SetAllTerm();		//��������������Ӧѧ��
	void Show();			//�������ӡ����Ļ��
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
		
		//�ȴ���ÿѧ�ڵĿγ���
		
		if((linebuf[0]>='0'&&linebuf[0]<='9'))
		{
			if(linebuf[1]=='*')
			{
				CourseCount[tempi] = linebuf[0] - '0';
				tempi++;
			}
		}
		
		//�ٴ���
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
				(*pInFile) >> courses[NoOFCourse].CourseNumber;		//�γ̱��
			}
			(*pInFile) >> courses[NoOFCourse].CourseName;		//�γ�����
			(*pInFile) >> courses[NoOFCourse].Period;			//ѧʱ��
			(*pInFile) >> courses[NoOFCourse].term;				//����ѧ��
			(*pInFile) >> courses[NoOFCourse].prerequisite1;	//�Ⱦ�����1
			(*pInFile) >> courses[NoOFCourse].prerequisite2;	//�Ⱦ�����2
			NoOFCourse++;		//�±�����1
			if (NoOFCourse == 38)
				break;
			continue;
		}
		(*pInFile) >> linebuf;	
	}
}

void Syllabus::SetAllTerm()
{//����ÿ���γ�����ѧ�ڣ��൱�ڽ�����������Ĺ���
	int TermCourseCnt[8];//���ڼ���ĳѧ�ڿγ��Ƿ��Ѿ�������ϵ�����
	for (int i = 0; i < 8; i++)//��ʼ��
		TermCourseCnt[i] = 0;

	//�Ƚ��Ѿ�ȷ����Ӧѧ�ڵĿγ̰��Ž���Ӧѧ��
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
		{//δ����ѧ�ڵĿγ�
			string temp1 = courses[i].prerequisite1;
			string temp2 = courses[i].prerequisite2;
			if ((temp1 == temp2) && temp1 == "c00")
			{
				for (int term = 1; term <= 8; term++)
				{//����ÿ��û���Ⱦ������Ŀγ̣���ѧ��������ȥ
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
					{//�ýϴ���Ⱦ�����ȥƥ����Ӧ�Ŀγ�
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
		cout << "��" << i << "ѧ�ڿγ̣�";
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