// ���ݽṹʵ����.cpp : �������̨Ӧ�ó������ڵ㡣
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
			select = getchar();//��ȡѡ��
			switch (select)
			{
			case '1':
				hf1.Compress();
				cin.get();			//�����������еĶ���Ļ��з�
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

