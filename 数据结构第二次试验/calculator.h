#pragma once

#include "lk_stack.h"


class Calculator
{
public:
	void Run();			//执行表达式
	Calculator() {};
	virtual~Calculator() {};
private:
	LinkStack<double>OPND;	//操作数栈
	LinkStack<char>OPTR;	//操作符栈
	int isp(char op);		//栈内优先数
	int icp(char op);		//栈外优先数
	double DoOperator(double x, char op, double y);
	//形成运算指令，进行运算
	void GETCHAR(char &ch);	//从输入流获取一字符ch并跳过空格及回车
	bool IsOperator(char ch);//判断ch是否为操作符
};

int Calculator::icp(char op)
{//栈外优先数
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
{//栈内优先数
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
{//形成运算指令，进行运算
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
{//从输入流获取一字符ch,并跳过空格及回车(雾，制表符)
	ch = GetChar();
}

bool Calculator::IsOperator(char ch)
{//判断ch是否为操作符
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
	OPTR.Clear();//清空optr栈与opnd栈
	OPTR.Push('=');//为方便编程，先加入一个=
	cout << "Please input expression :" << endl;
	char ch;//读入一个字符
	char priorChar;
	char optrTop;//临时OPTR栈的栈顶
	double operand;//操作数
	char op;//操作符

	priorChar = '=';
	GETCHAR(ch);
	if (OPTR.Top(optrTop) == UNDER_FLOW) throw Error("表达式有错！");

	while (optrTop != '=' || ch != '=')
	{
		if (isdigit(ch) || ch == '.')
		{//遇操作数，一律进入操作数栈
			cin.putback(ch);
			cin >> operand;
			OPND.Push(operand);//将操作数压栈
			priorChar = '0';
			GETCHAR(ch);		//读入下一个字符
		}
		
	//	else if (IsOperator(ch))
	//	{
	//		throw Error("表达式有错1");
	//	}
		else
		{//遇到运算符，则应与运算符栈optr的栈顶比较，
		//若栈顶运算符优先级低于当前运算符，
		//则当前运算符进栈，否则栈顶运算符退栈
		//若optr栈顶为“(”，当前运算符为“)”，则将“(”出栈。继续处理后续输入
			if ((priorChar == '=' || priorChar == '(') && (ch == '+' || ch == '-'))
			{
				OPND.Push(0);
				priorChar = '0';
			}
			if (optrTop == '('&&ch == ')')
			{
				if(OPTR.Pop(optrTop)==UNDER_FLOW) throw Error("表达式有错2");//将‘（’出栈
				GETCHAR(ch);//读入下一字符
				priorChar = ')';
			}
			else if (ch == '(' || isp(optrTop) < icp(ch))
			{
				OPTR.Push(ch);
				priorChar = ch;
				GETCHAR(ch);
			}
			else
			{//栈顶元素优先级大于当前字符优先级
				if (OPTR.Pop(op) == UNDER_FLOW) throw Error("表达式有错3");
				double left, right;
				OPND.Pop(right);
				OPND.Pop(left);//从OPND栈中取出两个操作数
				OPND.Push(DoOperator(left, op, right));//进行计算并将结果放入OPND
			}
		}
		if (OPTR.Top(optrTop) == UNDER_FLOW) throw Error("0004");
	}
	if (OPND.Top(operand) == UNDER_FLOW)throw Error("表达式有错5");
	cout << operand << endl;
}