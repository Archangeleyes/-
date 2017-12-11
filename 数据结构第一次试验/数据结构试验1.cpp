// 数据结构试验1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Dbllinklist.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void OutputCurCol(DblLinkList<string> * TheBuffer)
{//输出当前行字符串
	string tempcol;
	TheBuffer->GetElem((TheBuffer->GetCurPosition()), tempcol);//得到当前行的字符串，并将其储存在tempcol里
	cout << "current colume: "			//输出当前行的字符串
		<< TheBuffer->GetCurPosition()
		<< "  string :  "
		<< tempcol
		<< endl
		<<"c: ";
}

void Read_f(ifstream * File_read, DblLinkList<string> * TheBuffer)
{//将读取的字符串放入缓冲区
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
{//跳转到首行
	TheBuffer->SetCurPosition(1);
}

void Change(DblLinkList<string> * TheBuffer)
{
	string OldStr;
	string PartStr;
	string NewStr;
	//取出当前行的字符串
	TheBuffer->GetElem(TheBuffer->GetCurPosition(), OldStr);
	cin.get();//清除输入流中的‘/n'
	//从键盘上获取想改变的片段
	cout << "What segment do you want to replace? ";
	getline(cin, PartStr);
	cout << "there!";
	//从键盘上获取新片段
	cout << "What new text segment do you want to add in? ";
	getline(cin, NewStr);
	//查找想要改变的片段
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
{//删除一整行
	string temp;
	TheBuffer->Delete(TheBuffer->GetCurPosition(),temp);
}

void End(DblLinkList<string> * TheBuffer)
{//跳转到最后一行
	TheBuffer->SetCurPosition(TheBuffer->Length());
}

void Find(DblLinkList<string> * TheBuffer)
{//查找从键盘获取的字符串
	cout << "Enter string to serch for: " << endl;
	cin.get();
	string oldstring;
	string target;
	getline(cin, target);//获取目标子串
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
{//跳转至指定行
	int linenum;
	cout << "What line number do you want to go? ";
	cin >> linenum;
	if (linenum<1 || linenum>TheBuffer->Length())
		cout << "No such line" << endl;
	else
		TheBuffer->SetCurPosition(linenum);
}


void Help()
{//帮助
	cout << "Valid commands are: b(egin) c(hange) d(el) e(nd)"
		<< endl
		<< "f(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior)"
		<< endl
		<< "q(uit) r(ead) s(ubstitue) v(iew) w(rite)"
		<< endl;
}


void Insert(DblLinkList<string> * TheBuffer)
{//在目标行前插入新的一行
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
{//在屏幕上输出当前文件总行数和当前行数包含字符串的长度
	string curline;
	TheBuffer->GetElem(TheBuffer->GetCurPosition(), curline);
	cout << "There is " << TheBuffer->Length() << " lines in the file. " << endl
		<< "Current line length is " << curline.length() << endl;
}

void NextLine(DblLinkList<string> * TheBuffer)
{//跳转至下一行
	if (TheBuffer->GetCurPosition() != TheBuffer->Length())
		TheBuffer->SetCurPosition(TheBuffer->GetCurPosition() + 1);
	else
		cout << "Warning: at the end of buffer!" << endl;
}

void PriorLine(DblLinkList<string> * TheBuffer)
{//跳转至上一行
	if (TheBuffer->GetCurPosition() > 1)
		TheBuffer->SetCurPosition(TheBuffer->GetCurPosition() - 1);
	else
		cout << "Warning: at the start of buffer!" << endl;
}


void Substitue(DblLinkList<string> * TheBuffer)
{//删除指定行的字符串，用新的从键盘获取的字符串替换
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
	Infile.open((file_input.c_str()));//读操作
	cout << "Please input outputfile name(eg. file_out.txt): " << endl;
	cin >> file_output;
	Outfile.open((file_output.c_str()));//写操作

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