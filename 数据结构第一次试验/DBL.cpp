#include<iostream>
#include<string>
#include<stdlib.h>
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
	int Length()const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*Visit)(string &));

};