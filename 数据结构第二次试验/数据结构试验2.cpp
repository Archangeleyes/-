// 数据结构试验2.cpp : 定义控制台应用程序的入口点。
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

