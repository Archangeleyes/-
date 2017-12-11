// ���ݽṹ����1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "Dbllinklist.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void OutputCurCol(DblLinkList<string> * TheBuffer)
{//�����ǰ���ַ���
	string tempcol;
	TheBuffer->GetElem((TheBuffer->GetCurPosition()), tempcol);//�õ���ǰ�е��ַ����������䴢����tempcol��
	cout << "current colume: "			//�����ǰ�е��ַ���
		<< TheBuffer->GetCurPosition()
		<< "  string :  "
		<< tempcol
		<< endl
		<<"c: ";
}

void Read_f(ifstream * File_read, DblLinkList<string> * TheBuffer)
{//����ȡ���ַ������뻺����
	while (!(*File_read).eof())
	{
		string TemCol;
		char temstr[100];
		File_read->getline(temstr, 100);
		TemCol = temstr;
		TheBuffer->FstNode(TemCol);	
	}
}

void Begin(DblLinkList<string> * TheBuffer)
{//��ת������
	TheBuffer->SetCurPosition(1);
}

void Change(DblLinkList<string> * TheBuffer)
{
	string OldStr;
	string PartStr;
	string NewStr;
	//ȡ����ǰ�е��ַ���
	TheBuffer->GetElem(TheBuffer->GetCurPosition(), OldStr);
	cin.get();//����������еġ�/n'
	//�Ӽ����ϻ�ȡ��ı��Ƭ��
	cout << "What segment do you want to replace? ";
	getline(cin, PartStr);
	cout << "there!";
	//�Ӽ����ϻ�ȡ��Ƭ��
	cout << "What new text segment do you want to add in? ";
	getline(cin, NewStr);
	//������Ҫ�ı��Ƭ��
	if (OldStr.find(PartStr)+1)
	{
		int temPosition = (int)OldStr.find(PartStr);
		OldStr.erase(temPosition, (int)PartStr.length());
		OldStr.insert(temPosition, NewStr);
		TheBuffer->SetElem(TheBuffer->GetCurPosition(),OldStr);
		return;
	}
	cout << "Error: can't find the text segment" << endl;
}


void Delete(DblLinkList<string> * TheBuffer)
{//ɾ��һ����
	string temp;
	TheBuffer->Delete(TheBuffer->GetCurPosition(),temp);
}

void End(DblLinkList<string> * TheBuffer)
{//��ת�����һ��
	TheBuffer->SetCurPosition(TheBuffer->Length());
}

void Find(DblLinkList<string> * TheBuffer)
{//���ҴӼ��̻�ȡ���ַ���
	cout << "Enter string to serch for: " << endl;
	cin.get();
	string oldstring;
	string target;
	getline(cin, target);//��ȡĿ���Ӵ�
	TheBuffer->GetElem(TheBuffer->GetCurPosition(), oldstring);
	if (oldstring.find(target)+1)
	{
		int counti = (int)oldstring.find(target);
		cout << oldstring << endl;
		for (int i = 0; i < counti; i++)
			cout << " ";
		for (int i = 0; i < target.length(); i++)
			cout << "^";
		cout << endl;
		//char shiyishi;
		//shiyishi = getchar();
		return;
	}
	cout << "can't find the string " << endl;
}


void Go(DblLinkList<string> * TheBuffer)
{//��ת��ָ����
	int linenum;
	cout << "What line number do you want to go? ";
	cin >> linenum;
	if (linenum<1 || linenum>TheBuffer->Length())
		cout << "No such line" << endl;
	else
		TheBuffer->SetCurPosition(linenum);
}


void Help()
{//����
	cout << "Valid commands are: b(egin) c(hange) d(el) e(nd)"
		<< endl
		<< "f(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior)"
		<< endl
		<< "q(uit) r(ead) s(ubstitue) v(iew) w(rite)"
		<< endl;
}


void Insert(DblLinkList<string> * TheBuffer)
{//��Ŀ����ǰ�����µ�һ��
	cout << "Insert what line number? ";
	int linenum;
	cin >> linenum;
	cout << "What is the new line to insert? ";
	string newline;
	cin.get();
	getline(cin, newline);
	TheBuffer->Insert(linenum, newline);
}


void LineLength(DblLinkList<string> * TheBuffer)
{//����Ļ�������ǰ�ļ��������͵�ǰ���������ַ����ĳ���
	string curline;
	TheBuffer->GetElem(TheBuffer->GetCurPosition(), curline);
	cout << "There is " << TheBuffer->Length() << " lines in the file. " << endl
		<< "Current line length is " << curline.length() << endl;
}

void NextLine(DblLinkList<string> * TheBuffer)
{//��ת����һ��
	if (TheBuffer->GetCurPosition() != TheBuffer->Length())
		TheBuffer->SetCurPosition(TheBuffer->GetCurPosition() + 1);
	else
		cout << "Warning: at the end of buffer!" << endl;
}

void PriorLine(DblLinkList<string> * TheBuffer)
{//��ת����һ��
	if (TheBuffer->GetCurPosition() > 1)
		TheBuffer->SetCurPosition(TheBuffer->GetCurPosition() - 1);
	else
		cout << "Warning: at the start of buffer!" << endl;
}


void Substitue(DblLinkList<string> * TheBuffer)
{//ɾ��ָ���е��ַ��������µĴӼ��̻�ȡ���ַ����滻
	int linenum;
	cout << "Substitue what line number? ";
	cin >> linenum;
	string newline;
	cout << "What is the new line to substitue? ";
	cin.get();
	getline(cin, newline);
	TheBuffer->SetElem(linenum, newline);
}

void View(DblLinkList<string> * TheBuffer)
{
	for (int i = 0; i < (TheBuffer->Length()); i++)
	{
		string temstr;
		TheBuffer->GetElem(i+1, temstr);
		cout << temstr << endl;
	}
}

void Write_f(ofstream * File_write, DblLinkList<string> * TheBuffer)
{
	for (int i = 0; i < (TheBuffer->Length()); i++)
	{
		string temstr;
		TheBuffer->GetElem(i + 1, temstr);
		*File_write << temstr << endl;
	}
}


int main()
{
	DblLinkList<string> * buffer = new DblLinkList<string>();
	string file_input, file_output;
	ifstream Infile;
	ofstream Outfile;
	cout << "Please input inputfile name(eg. file_in.txt): " << endl;
	cin >> file_input;
	Infile.open((file_input.c_str()));//������
	cout << "Please input outputfile name(eg. file_out.txt): " << endl;
	cin >> file_output;
	Outfile.open((file_output.c_str()));//д����

	cout << "File buffer is empty(please use command r to read file to buffer)." << endl;
	
	ifstream * File_Point = &Infile;
	ofstream * Ofile_Point = &Outfile;

	char ch = 'z';
	cin.get();
	
	while(((ch = getchar())!=('q'))&&(ch != 'Q'))
	{
		if (ch >= 'A'&&ch <= 'Z')
			ch -= 32;
		switch (ch)
		{
		case'b':
			Begin(buffer);
			OutputCurCol(buffer);
			char ch1;
			ch1 = getchar();
			break;
		case'c':
			Change(buffer);
			OutputCurCol(buffer);
			//char ch2;
			//ch2 = getchar();
			break;
		case'd':
			Delete(buffer);
			OutputCurCol(buffer);
			char ch3;
			ch3 = getchar();
			break;
		case'e':
			End(buffer);
			OutputCurCol(buffer);
			char ch4;
			ch4 = getchar();
			break;
		case'f':
			Find(buffer);
			OutputCurCol(buffer);
			//char ch5;
			//ch5 = getchar();
			break;
		case'g':
			Go(buffer);
			OutputCurCol(buffer);
			char ch6;
			ch6 = getchar();
			break;
		case'?':
		case'h':
			Help();
			OutputCurCol(buffer);
			char ch7;
			ch7 = getchar();
			break;
		case'i':
			Insert(buffer);
			OutputCurCol(buffer);
			//char ch8;
			//ch8 = getchar();
			break;
		case'l':
			LineLength(buffer);
			OutputCurCol(buffer);
			char ch9;
			ch9 = getchar();
			break;
		case'n':
			NextLine(buffer);
			OutputCurCol(buffer);
			char ch10;
			ch10 = getchar();
			break;
		case'p':
			PriorLine(buffer);
			OutputCurCol(buffer);
			char ch11;
			ch11 = getchar();
			break;
		case'r':
			Read_f(File_Point,buffer);
			OutputCurCol(buffer);
			char ch12;
			ch12 = getchar();
			break;
		case's':
			Substitue(buffer);
			OutputCurCol(buffer);
			char ch13;
			ch13 = getchar();
			break;
		case'v':
			View(buffer);
			OutputCurCol(buffer);
			char ch14;
			ch14 = getchar();
			break;
		case'w':
			Write_f(Ofile_Point,buffer);
			OutputCurCol(buffer);
			char ch15;
			ch15 = getchar();
			break;
		default:
			cout << "Please press h or ? for help or enter a valid command :" << endl;
			OutputCurCol(buffer);
			break;
		}
		//break;
	}

	return 0;
}