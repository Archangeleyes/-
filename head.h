#pragma once
#include "utility"
using namespace std;



struct DblNode//节点类
{
	string ColData;//每行数据
	DblNode * back;//指向前一个节点
	DblNode * next;//指向后一个节点

	DblNode();//构造函数
	DblNode(DblNode * linkBack = NULL, DblNode * linkNext = NULL);//已知数据和指针域建立结构
};

DblNode::DblNode()
{
	next = NULL;
}

DblNode::DblNode(DblNode * linkBack, DblNode * linkNext)
{
	ColData = string;
	back = linkBack;
	next = linkNext;
}

class DblLinkList//双向链表
{
protected:
	DblNode * head;
	DblNode * GetElemPtr(int position) const;
	void Init();

public:
	DblLinkList();
	virtual ~DblLinkList();
	int Length()const;		//求线性表长度
	bool Empty() const;		//判断线性表是否为空
	void Clear();			//将线性表清空
	void Traverse(void(*Visit)(string &));			//遍历线性表
	StatusCode 

};