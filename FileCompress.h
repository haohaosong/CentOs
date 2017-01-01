/*
* author:haohaosong
* date:2017/1/1
* note:�ļ�ѹ��С��Ŀ������ 
*/ 

#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<assert.h>
#include<string>
#include<algorithm>
#include"HuffmanTree.h"
typedef long long LongType;

struct CharInfo
{
	char _ch;
	LongType _count;
	string _code;

	CharInfo(LongType count = 0)
		:_count(count)
	{}

	bool operator !=(const CharInfo& c)
	{
		return 	_count != c._count;
	}

	bool operator<(const CharInfo& c)
	{
		return _count < c._count;
	}

	CharInfo operator+(const CharInfo&c)
	{
		return CharInfo(_count+c._count);
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	//��infos��ʼ����������0
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
	}

	void Compress(const char* filename)
	{
		assert(filename);

		//1.ͳ���ַ����ֵĸ���
		FILE* fout = fopen(filename, "r");
		assert(fout);
		char ch = fgetc(fout);
		while (ch != EOF)
		{
			_infos[ch]._count++;
			ch = fgetc(fout);
		}

		//2.���ɹ�������
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> huff(_infos,256,invalid);
		
		//���ɹ���������
		GetHuffmanCode(huff.GerRoot());

		//����ѹ��
		string ComFilename = (string)filename;
		ComFilename += ".huff";
		FILE* fIn = fopen(ComFilename.c_str(), "w");//c_str()����ֵΪconst����
		
		char value = 0;
		int pos = 0;
		fseek(fout, 0, SEEK_SET);
		ch = fgetc(fout);
		int i = 0;
		while (ch != EOF)
		{
			string& code = _infos[ch]._code;
			while (pos<8)
			{
				value <<= 1;

				if (code.at(i++) == '1')
					value |= 1;

				pos++;

				if (i == code.length())
					break;
			}

			if (pos == 8)
			{
				fputc(value, fIn);
				pos = 0;
				value = 0;
			}

			if (i == code.length())
			{
				i = 0;
				ch = fgetc(fout);
			}
		}
		if (pos < 8)
		{
			value <<= (8 - pos);
			fputc(value, fIn);
		}

		fclose(fIn);
		fclose(fout);
		//while (ch != EOF)
		//{
		//	//if (ch == '1')
		//	string& code = _infos[ch]._code;

		//	/*if (code.at(1) == '1')
		//		value |= 1;

		//	value <<= 1;*/

		//	bool flag = true;
		//	for (int i = 0; i < code.length(); ++i)
		//	{
		//		if (code.at(i) == '1')
		//			value |= 1;

		//		value <<= 1;
		//		pos++;

		//		if (pos == 8&& i+1 != code.length())
		//		{
		//			flag = false;
		//			break;
		//		}
		//	}

		//	if (pos == 8)
		//	{
		//		fputc(value,fIn);
		//		value = 0;
		//		pos = 0;
		//	}
		//	if (flag == true)
		//		ch = fgetc(fout);
		//	else
		//}
		////if (pos>0 && pos < 8)
		//{
		//	//value <<= (8 - pos);
		//	fputc(value, fIn);
		//}
		//fclose(fout);
		//fclose(fIn);
	}

	//��ѹ��
	void Uncompress(const char* filename)
	{}

	//�õ�����������
	void GetHuffmanCode(const Node* root)
	{
		if (root == NULL)
			return;

		//�ҵ�Ҷ�ӽڵ㣬������룬������
		//����ݹ����Ѱ��
		if (root->_left == NULL && root->_right == NULL)
		{
			//�������ã����ٿ����Ŀ���
			string& code = _infos[root->_weight._ch]._code;

			//��ȡhuffman���룬����¼�ڸ��ڵ���
			Node* parent = root->_parent;
			Node* child = (Node*)root;
			while (parent)
			{
				if (parent->_right == child)
					code.push_back('1');
				else
					code.push_back('0');

				child = parent;
				parent = parent->_parent;
			}
			//����
			reverse(code.begin(), code.end());

			return;
		}

		//�ݹ����
		GetHuffmanCode(root->_left);
		GetHuffmanCode(root->_right);
	}

protected:
	CharInfo _infos[256];
};

void TestFileCompress()
{
	FileCompress f;
	f.Compress("input.txt");
}
