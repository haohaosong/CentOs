#pragma once

/*
* author:haohaosong
* date:2017/3/5
* note:���鼯��ʵ�֣����ڽ������Ȧ����
*/

#include<iostream>
using namespace std;

#include<vector>

//���岢�鼯
class UnionFindSet
{
public:
	//���캯��������ʼֵ��Ϊ-1
	//����������
	UnionFindSet(size_t n)
	{
		v.resize(n+1, -1);
	}

	//�ҵ����ڵ�
	size_t FindRoot(size_t x)
	{
		size_t ret = x;

		while (v[ret] >= 0)
			ret = v[ret];

		return ret;
	}

	//�������˵�����Ȧ���кϲ�
	void Union(size_t x1,size_t x2)
	{
		size_t root1 = FindRoot(x1);
		size_t root2 = FindRoot(x2);

		//ͬ�����Ѿ���һ������
		if (root1 == root2)
			return;

		v[root1] += v[root2];
		v[root2] = root1;
	}

	//�ж��Ƿ���һ������
	bool IsInSet(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}

	//�󼯺�(����Ȧ)�ĸ���
	size_t SetSize()
	{
		size_t count = 0;
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (v[i] < 0)
				count++;
		}

		return count-1;
	}
protected:
	vector<int> v;
};

void TestUnionFindSet()
{
	//����ˣ����ĸ�����Ȧ��ϵ
	const int n = 5;
	const int m = 4;

	UnionFindSet ufs(n);
	int r[m][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 2, 4 } };
	for (size_t i = 0; i < m; ++i)
	{
		ufs.Union(r[i][0], r[i][1]);
	}

	cout << "����Ȧ�ĸ���Ϊ:" << ufs.SetSize() << endl;
}