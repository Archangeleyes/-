// 数据结构实验三.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "huffmancompress.h"

int main()
{
	try
	{
		bool Continue = true;

		do
		{
			HuffmanCompress hf1;
			cout << "1.Huffman compress." << endl;
			cout << "2.Huffman decompress." << endl;
			cout << "3.Exit." << endl;
			cout << "Please select:";
			char select;
			select = getchar();//获取选项
			switch (select)
			{
			case '1':
				hf1.Compress();
				cin.get();			//消除缓冲流中的多余的换行符
				break;
			case '2':
				hf1.Decompress();
				cin.get();
				break;
			case '3':
				Continue = false;
				break;
			default:
				cin.get();
				break;
			}
		} while (Continue);
	}
	catch (Error err)
	{
		err.Show();
	}
	system("PAUSE");
    return 0;
}

