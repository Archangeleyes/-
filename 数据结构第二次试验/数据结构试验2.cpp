// ���ݽṹ����2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "calculator.h"

int main()
{
	try
	{
		bool Continue;

		do
		{
			Calculator Cal1;
			Cal1.Run();
			cout << "continue?";
			Continue = UserSaysYes();
		} while (Continue);
	}
	catch (Error err)
	{
		err.Show();
	}
	system("PAUSE");
    return 0;
}

