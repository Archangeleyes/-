#pragma once
#include "utility"
using namespace std;



struct DblNode//�ڵ���
{
	string ColData;//ÿ������
	DblNode * back;//ָ��ǰһ���ڵ�
	DblNode * next;//ָ���һ���ڵ�

	DblNode();//���캯��
	DblNode(DblNode * linkBack = NULL, DblNode * linkNext = NULL);//��֪���ݺ�ָ�������ṹ
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

class DblLinkList//˫������
{
protected:
	DblNode * head;
	DblNode * GetElemPtr(int position) const;
	void Init();

public:
	DblLinkList();
	virtual ~DblLinkList();
	int Length()const;		//�����Ա���
	bool Empty() const;		//�ж����Ա��Ƿ�Ϊ��
	void Clear();			//�����Ա����
	void Traverse(void(*Visit)(string &));			//�������Ա�
	StatusCode 

};