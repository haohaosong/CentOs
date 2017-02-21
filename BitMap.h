#pragma once

/*
* author:haohaosong
* date:2017/2/21
* note:λͼ��ʵ�� 
*/ 

#include<iostream>
using namespace std;

#include<vector>

//����λͼ
class BitMap
{
public:
	//λͼ�Ĺ��캯��
	BitMap(size_t size = 1024)
		:_size(0)
	{
		//һ���޷�������(size_t)������32��λ�ֱ��ʾ32����
		_v.resize(size / 32 + 1);
	}

	//���룬��num������λ��Ϊ1
	void Set(size_t num)
	{
		//index�����ж���vector�ĵڼ���Ԫ����
		//value��ʾ�ڸ�Ԫ���дӵ�λ���λ���������һλ
		//index������5λ���൱�ڳ�32������λ����Ч�ʸ�
		int index = num >> 5;
		int value = num % 32;

		//���û����㣬����λ��Ϊ1
		_v[index] |= 1 << (value-1);
		_size++;
	}

	//�Ƴ�����num������λ��Ϊ0
	void Reset(size_t num)
	{
		//index�����ж���vector�ĵڼ���Ԫ����
		//value��ʾ�ڸ�Ԫ���дӵ�λ���λ���������һλ
		//index������5λ���൱�ڳ�32������λ����Ч�ʸ�
		int index = num >> 5;
		int value = num % 32;

		//����������㣬����λ��Ϊ0
		_v[index] ^= 1 << (value-1);
		_size--;
	}

	//�����ж�һ�����Ƿ��Ѿ�����λͼ��
	bool Find(size_t num)
	{
		int index = num >> 5;
		int value = num % 32;

		//�жϸ�λ�Ƿ�Ϊ1
		return (_v[index] >> (value-1)) & 1;
	}
protected:
	vector<size_t> _v;
	size_t _size;
};

void TestBitMap()
{
	BitMap bp;
	bp.Set(1);
	cout << "1:" << bp.Find(1) << endl;

	bp.Set(2);
	bp.Set(3);

	cout << "1:" << bp.Find(1) << endl;
	cout << "2:" << bp.Find(2) << endl;
	cout << "5:" << bp.Find(5) << endl;
}
