#pragma once
#include"huffman_tree.h"
struct BufferType
{
	char ch;				//�ַ�
	unsigned int bits;		//ʵ�ʱ�����
};
class HuffmanCompress
{
protected:
	HuffmanTree<char, unsigned long> * pHuffmanTree = NULL;
	FILE * infp, *outfp;		//��������ļ�ָ��
	BufferType buf;				//�ַ�����

	void Write(unsigned int bit);		//��Ŀ���ļ�д��һ����
	void WriteToOutfp();				//ǿ�н��ַ�����д��Ŀ���ļ�

public:
	HuffmanCompress(){}
	~HuffmanCompress(){}
	void Compress();	//ѹ��
	void Decompress();	//��ѹ
	HuffmanCompress(const HuffmanCompress &copy);	//���ƹ��캯��
	HuffmanCompress &operator= (const HuffmanCompress&copy);//��ֵ���������
};

void HuffmanCompress::Write(unsigned int bit)
{//�����������Ŀ���ļ���д��һbit
	buf.bits++;			//������bit����1
	buf.ch = (buf.ch << 1) | bit;//��bit���뵽�����ַ���
	if (buf.bits == 8)
	{//��������д����д��Ŀ���ļ�
		fputc(buf.ch, outfp);		//д��Ŀ���ļ�������ļ���
		buf.bits = 0;				//����������Ϊ��
		buf.ch = 0;					//���������е��ַ����
	}
}


void HuffmanCompress::WriteToOutfp()
{//���������ǿ�н��ַ�����д��Ŀ���ļ�
	unsigned int len = buf.bits;
	if (len > 0)
	{//����ǿգ��������bit�����ӵ�8���Զ�д��Ŀ���ļ�
		for (unsigned int i = 0; i < 8 - len; i++)
			Write(0);
	}
}

void HuffmanCompress::Compress()
{//����������ù���������ѹ���ļ�
	char infName[256], outfName[256];
	cout << "Please input source file name(size less than 4GB):" << endl;
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL) throw Error("Wrong to open source file!");

	fgetc(infp);//ȡ��Դ�ļ��ĵ�һ���ַ�
	if (feof(infp)) throw Error("Source file is empty!");

	cout << "Please input code file name:" << endl;
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL) throw Error("Fail to open source file!");

	cout << "Compressing......" << endl;

	const unsigned long n = 256;	//�ַ�����
	char ch[n];						//�ַ�����
	unsigned long w[n];				//�ַ�����Ƶ�ȣ�Ȩ��
	unsigned long i, size = 0;
	char cha;

	for (i = 0; i < n; i++)
	{//��ʼ���ַ�����ch���ַ�����Ƶ��w
		ch[i] = (char)i;
		w[i] = 0;
	}
	rewind(infp);
	cha = fgetc(infp);
	while (!feof(infp))
	{//ͳ���ַ�����Ƶ��
		w[(unsigned char)cha]++;	//�ַ�cha����Ƶ���Լ�1
		size++;						//�ļ���С�Լ�1
		cha = fgetc(infp);			//ȡ��Դ�ļ�����һ���ַ�
	}

	if (pHuffmanTree != NULL)
		delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);	//���ɹ�������
	rewind(outfp);										//ʹĿ��ָ��ָ���ļ���ʼ��
	fwrite(&size, sizeof(unsigned long), 1, outfp);		//��Ŀ���ļ�д��Դ�ļ���С
	for (i = 0; i < n; i++)
	{//��Ŀ���ļ�д���ַ�����Ƶ��
		fwrite(&w[i], sizeof(unsigned long), 1, outfp);
	}

	buf.bits = 0;				//��ʼ��bits
	buf.ch = 0;					//��ʼ��ch
	rewind(infp);				//���ļ�ָ��ָ���ļ���ʼ��
	cha = fgetc(infp);			//ȡ��Դ�ļ��ĵ�һ���ַ�
	while (!feof(infp))
	{//��Դ�ļ��ַ����б��룬��������д��Ŀ���ļ�
		String strTmp = pHuffmanTree->Encode(cha);//�ַ�����
		for (i = 0; i < strTmp.Length(); i++)
		{//��Ŀ���ļ�д�����
			if (strTmp[i] == '0')
				Write(0);
			else
				Write(1);
		}
		cha = fgetc(infp);//ȡ��Դ�ļ�����һ���ַ�
	}
	WriteToOutfp();		//ǿ��д��Ŀ���ļ�

	fclose(infp);
	fclose(outfp);
	cout << "Done!" << endl;
}

void HuffmanCompress::Decompress()
{//��ѹ
	char infName[256], outfName[256];
	cout << "Please input code file name:" << endl;
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL)throw Error("Fail to open code file!");//��Դ�ļ��������ļ����Լ��쳣����
	fgetc(infp);		//ȡ��ѹ���ļ��ĵ�һ���ַ�
	if (feof(infp))throw Error("Code file is empty!");
	cout << "Please input target file name:" << endl;
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)throw Error("Fail to open target file!");//��Ŀ���ļ��Լ��쳣����
	cout << "Decompressing......" << endl;
	const unsigned long n = 256;
	char ch[n];
	unsigned long w[n];
	unsigned long i, size = 0;
	char cha;

	rewind(infp);		//ʹĿ���ļ�ָ���ļ���ʼ��
	fread(&size, sizeof(unsigned long), 1, infp);//��ȡĿ���ļ���С
	for (i = 0; i < n; i++)
	{ 
		ch[i] = (char)i;
		fread(&w[i], sizeof(unsigned long), 1, infp);
	}
	if (pHuffmanTree != NULL)
		delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long >(ch, w, n);//���ɹ�������

	unsigned long len = 0;			//��ѹ���ַ���
	cha = fgetc(infp);				//ȡ��Դ�ļ��ĵ�һ���ַ�
	while (!feof(infp))
	{//��ѹ
		String strTmp = "";		//��cha ת��Ϊ��������ʽ�Ĵ�
		unsigned char c = (unsigned char)cha; //��chaת��Ϊunsigned char ����
		for (i = 0; i < 8; i++)
		{//��cת��Ϊ��������ʽ�Ĵ�
			if (c < 128)
				Concat(strTmp, "0");//���λΪ0
			else
				Concat(strTmp, "1");//���λΪ1
			c = c << 1;				//����һλ
		}

		String strTemp(pHuffmanTree->Decode(strTmp));//����
		for (i = 1; i <= strTemp.Length(); i++)
		{//��Ŀ���ļ�д���ַ�
			len++;			//Ŀ���ļ������Լ�1
			fputc(strTemp[i - 1], outfp);	//���ַ�д��Ŀ���ļ���
			if (len == size)
				break;		//��ѹ����˳���ѭ��
		}
		if (len == size)
			break;			//��ѹ����˳���ѭ��
		cha = fgetc(infp);//ȡ���ļ�����һ���ַ�
	}
	fclose(infp);
	fclose(outfp);
	cout << "Done!" << endl;
}