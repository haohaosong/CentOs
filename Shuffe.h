#pragma once

/*
* author:haohaosong
* date:2017/3/1
* note:ϴ���㷨��ʵ��
*/

#include<iostream>
using namespace std;

#include<time.h>

//��ӡ����
void Print(int* a, size_t n)
{
	for (size_t i = 0; i<n; ++i)
		cout << a[i] << " ";

	cout << endl;
}

//����ϴ��
void Shuffe(int* a, int n)
{
	for (int i = n - 1; i > 0; --i)
	{
		srand((unsigned)time(NULL));//���Ӵ����Ļ���ÿ����������᲻��
		swap(a[i], a[rand() % (i + 1)]);
	}
}

//����ϴ���㷨
void TestShuffe()
{
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Shuffe(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}