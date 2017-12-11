#pragma once
#include"huffman_tree.h"
struct BufferType
{
	char ch;				//字符
	unsigned int bits;		//实际比特数
};
class HuffmanCompress
{
protected:
	HuffmanTree<char, unsigned long> * pHuffmanTree = NULL;
	FILE * infp, *outfp;		//输入输出文件指针
	BufferType buf;				//字符缓存

	void Write(unsigned int bit);		//向目标文件写入一比特
	void WriteToOutfp();				//强行将字符缓存写入目标文件

public:
	HuffmanCompress(){}
	~HuffmanCompress(){}
	void Compress();	//压缩
	void Decompress();	//解压
	HuffmanCompress(const HuffmanCompress &copy);	//复制构造函数
	HuffmanCompress &operator= (const HuffmanCompress&copy);//赋值运算符重载
};

void HuffmanCompress::Write(unsigned int bit)
{//操作结果：向目标文件中写入一bit
	buf.bits++;			//缓存数bit自增1
	buf.ch = (buf.ch << 1) | bit;//将bit加入到缓存字符中
	if (buf.bits == 8)
	{//缓存区已写满，写入目标文件
		fputc(buf.ch, outfp);		//写入目标文件（输出文件）
		buf.bits = 0;				//缓存区现在为空
		buf.ch = 0;					//将缓存区中的字符清空
	}
}


void HuffmanCompress::WriteToOutfp()
{//操作结果：强行将字符缓存写入目标文件
	unsigned int len = buf.bits;
	if (len > 0)
	{//缓存非空，将缓存的bit数增加到8，自动写入目标文件
		for (unsigned int i = 0; i < 8 - len; i++)
			Write(0);
	}
}

void HuffmanCompress::Compress()
{//操作结果：用哈夫曼编码压缩文件
	char infName[256], outfName[256];
	cout << "Please input source file name(size less than 4GB):" << endl;
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL) throw Error("Wrong to open source file!");

	fgetc(infp);//取出源文件的第一个字符
	if (feof(infp)) throw Error("Source file is empty!");

	cout << "Please input code file name:" << endl;
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL) throw Error("Fail to open source file!");

	cout << "Compressing......" << endl;

	const unsigned long n = 256;	//字符个数
	char ch[n];						//字符数组
	unsigned long w[n];				//字符出现频度（权）
	unsigned long i, size = 0;
	char cha;

	for (i = 0; i < n; i++)
	{//初始化字符数组ch和字符出现频度w
		ch[i] = (char)i;
		w[i] = 0;
	}
	rewind(infp);
	cha = fgetc(infp);
	while (!feof(infp))
	{//统计字符出现频度
		w[(unsigned char)cha]++;	//字符cha出现频度自加1
		size++;						//文件大小自加1
		cha = fgetc(infp);			//取出源文件的下一个字符
	}

	if (pHuffmanTree != NULL)
		delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);	//生成哈夫曼树
	rewind(outfp);										//使目标指针指向文件开始处
	fwrite(&size, sizeof(unsigned long), 1, outfp);		//向目标文件写入源文件大小
	for (i = 0; i < n; i++)
	{//向目标文件写入字符出现频度
		fwrite(&w[i], sizeof(unsigned long), 1, outfp);
	}

	buf.bits = 0;				//初始化bits
	buf.ch = 0;					//初始化ch
	rewind(infp);				//是文件指针指向文件开始处
	cha = fgetc(infp);			//取出源文件的第一个字符
	while (!feof(infp))
	{//对源文件字符进行编码，并将编码写入目标文件
		String strTmp = pHuffmanTree->Encode(cha);//字符编码
		for (i = 0; i < strTmp.Length(); i++)
		{//向目标文件写入编码
			if (strTmp[i] == '0')
				Write(0);
			else
				Write(1);
		}
		cha = fgetc(infp);//取出源文件的下一个字符
	}
	WriteToOutfp();		//强行写入目标文件

	fclose(infp);
	fclose(outfp);
	cout << "Done!" << endl;
}

void HuffmanCompress::Decompress()
{//解压
	char infName[256], outfName[256];
	cout << "Please input code file name:" << endl;
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL)throw Error("Fail to open code file!");//打开源文件（编码文件）以及异常处理
	fgetc(infp);		//取出压缩文件的第一个字符
	if (feof(infp))throw Error("Code file is empty!");
	cout << "Please input target file name:" << endl;
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)throw Error("Fail to open target file!");//打开目标文件以及异常处理
	cout << "Decompressing......" << endl;
	const unsigned long n = 256;
	char ch[n];
	unsigned long w[n];
	unsigned long i, size = 0;
	char cha;

	rewind(infp);		//使目标文件指向文件开始处
	fread(&size, sizeof(unsigned long), 1, infp);//读取目标文件大小
	for (i = 0; i < n; i++)
	{ 
		ch[i] = (char)i;
		fread(&w[i], sizeof(unsigned long), 1, infp);
	}
	if (pHuffmanTree != NULL)
		delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long >(ch, w, n);//生成哈夫曼树

	unsigned long len = 0;			//解压的字符数
	cha = fgetc(infp);				//取出源文件的第一个字符
	while (!feof(infp))
	{//解压
		String strTmp = "";		//将cha 转换为二进制形式的串
		unsigned char c = (unsigned char)cha; //将cha转换为unsigned char 类型
		for (i = 0; i < 8; i++)
		{//将c转换为二进制形式的串
			if (c < 128)
				Concat(strTmp, "0");//最高位为0
			else
				Concat(strTmp, "1");//最高位为1
			c = c << 1;				//左移一位
		}

		String strTemp(pHuffmanTree->Decode(strTmp));//译码
		for (i = 1; i <= strTemp.Length(); i++)
		{//向目标文件写入字符
			len++;			//目标文件长度自加1
			fputc(strTemp[i - 1], outfp);	//将字符写入目标文件中
			if (len == size)
				break;		//解压完毕退出内循环
		}
		if (len == size)
			break;			//解压完毕退出外循环
		cha = fgetc(infp);//取出文件的下一个字符
	}
	fclose(infp);
	fclose(outfp);
	cout << "Done!" << endl;
}