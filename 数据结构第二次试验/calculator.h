#pragma once

#include "lk_stack.h"


class Calculator
{
public:
	void Run();			//ִ�б��ʽ
	Calculator() {};
	virtual~Calculator() {};
private:
	LinkStack<double>OPND;	//������ջ
	LinkStack<char>OPTR;	//������ջ
	int isp(char op);		//ջ��������
	int icp(char op);		//ջ��������
	double DoOperator(double x, char op, double y);
	//�γ�����ָ���������
	void GETCHAR(char &ch);	//����������ȡһ�ַ�ch�������ո񼰻س�
	bool IsOperator(char ch);//�ж�ch�Ƿ�Ϊ������
};

int Calculator::icp(char op)
{//ջ��������
	switch (op)
	{
	case'=':
		return 1;
		break;
	case'(':
	case')':
		return 2;
		break;
	case'+':
	case'-':
		return 3;
		break;
	case'*':
	case'/':
	case'%':
		return 4;
		break;
	case'^':
		return 5;
		break;
	default:
		cout << "Operator Error! Please input currect operator!" << endl;
		break;
	}
}

int Calculator::isp(char op)
{//ջ��������
	switch (op)
	{
	case'=':
		return 1;
		break;
	case'(':
	case')':
		return 2;
		break;
	case'+':
	case'-':
		return 3;
		break;
	case'*':
	case'/':
	case'%':
		return 4;
		break;
	case'^':
		return 5;
		break;
	default:
		cout << "Operator Error! Please input currect operator!" << endl;
		break;
	}
}

double Calculator::DoOperator(double x, char op, double y)
{//�γ�����ָ���������
	switch (op)
	{
	case '+':
		return x + y;
		break;
	case '-':
		return x - y;
		break;
	case '*':
		return x * y;
		break;
	case '/':
		return x / y;
		break;
	case '^':
		return pow(x, y);
		break;
	case '%':
		return (int)x % (int)y;
		break;
	default:
		break;
	}
}

void Calculator::GETCHAR(char &ch)
{//����������ȡһ�ַ�ch,�������ո񼰻س�(���Ʊ��)
	ch = GetChar();
}

bool Calculator::IsOperator(char ch)
{//�ж�ch�Ƿ�Ϊ������
	switch (ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		return true;
		break;
	default:
		return false;
		break;
	}
}

void Calculator::Run()
{
	OPND.Clear();
	OPTR.Clear();//���optrջ��opndջ
	OPTR.Push('=');//Ϊ�����̣��ȼ���һ��=
	cout << "Please input expression :" << endl;
	char ch;//����һ���ַ�
	char priorChar;
	char optrTop;//��ʱOPTRջ��ջ��
	double operand;//������
	char op;//������

	priorChar = '=';
	GETCHAR(ch);
	if (OPTR.Top(optrTop) == UNDER_FLOW) throw Error("���ʽ�д�");

	while (optrTop != '=' || ch != '=')
	{
		if (isdigit(ch) || ch == '.')
		{//����������һ�ɽ��������ջ
			cin.putback(ch);
			cin >> operand;
			OPND.Push(operand);//��������ѹջ
			priorChar = '0';
			GETCHAR(ch);		//������һ���ַ�
		}
		
	//	else if (IsOperator(ch))
	//	{
	//		throw Error("���ʽ�д�1");
	//	}
		else
		{//�������������Ӧ�������ջoptr��ջ���Ƚϣ�
		//��ջ����������ȼ����ڵ�ǰ�������
		//��ǰ�������ջ������ջ���������ջ
		//��optrջ��Ϊ��(������ǰ�����Ϊ��)�����򽫡�(����ջ�����������������
			if ((priorChar == '=' || priorChar == '(') && (ch == '+' || ch == '-'))
			{
				OPND.Push(0);
				priorChar = '0';
			}
			if (optrTop == '('&&ch == ')')
			{
				if(OPTR.Pop(optrTop)==UNDER_FLOW) throw Error("���ʽ�д�2");//����������ջ
				GETCHAR(ch);//������һ�ַ�
				priorChar = ')';
			}
			else if (ch == '(' || isp(optrTop) < icp(ch))
			{
				OPTR.Push(ch);
				priorChar = ch;
				GETCHAR(ch);
			}
			else
			{//ջ��Ԫ�����ȼ����ڵ�ǰ�ַ����ȼ�
				if (OPTR.Pop(op) == UNDER_FLOW) throw Error("���ʽ�д�3");
				double left, right;
				OPND.Pop(right);
				OPND.Pop(left);//��OPNDջ��ȡ������������
				OPND.Push(DoOperator(left, op, right));//���м��㲢���������OPND
			}
		}
		if (OPTR.Top(optrTop) == UNDER_FLOW) throw Error("0004");
	}
	if (OPND.Top(operand) == UNDER_FLOW)throw Error("���ʽ�д�5");
	cout << operand << endl;
}