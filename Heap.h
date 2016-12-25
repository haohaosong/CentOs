/*
* author:haohaosong
* date:2016/12/25
* note:�ѵ�ʵ�� 
*/ 
#include<iostream>
using namespace std;

#include<vector>

template<typename T>
class Heap
{
public:
	Heap()
	{}

	Heap(T arr[], size_t n)
		:_a(arr, arr + n)
	{
		for (int i = (_a.size()-2)/2; i >= 0; i--)
		{
			_AdjustDown(i);
		}
	}

	void Pop()
	{
		swap(_a[0], _a[_a.size()-1]);
		_a.pop_back();
		_AdjustDown(0);
	}

	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size()-1);
	}
protected:
	vector<T> _a;
protected:
	void _AdjustUp(int i)
	{
		int child = i;
		int parent = (i - 1) / 2;

		//���ӽڵ�û�дﵽ�Ѷ�
		while (child >= 0)
		{
			//����ӱȸ��״��򽻻������ҽ�����һ�ֵ��ж�
			if (_a[child]>_a[parent])
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (parent - 1) / 2;
			}
			else//���ý����ѣ�ֱ�ӽ���
			{
				break;
			}
		}
	}
	void _AdjustDown(int root)
	{
		int parent = root;
		int child = 2 * parent+1;

		//child���ܴ��ڽڵ��ܵĸ���
		while (child<_a.size())
		{
			//����ҽڵ���ڲ��ұ���߽ڵ��
			if (child + 1 < _a.size() && _a[child+1] > _a[child])
			{
				child++;
			}

			//������ӱȸ��״�,�򽻻���������һ��ѭ��
			//��������ѭ��
			if (_a[child] > _a[parent])
			{
				swap(_a[child], _a[parent]);
				//���׺���������
				parent = child;
				child = child * 2 + 1;
			}			
			else
			{
				break;
			}
		}

	}
};

void TestHeap()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	Heap<int> hp1(a, sizeof(a) / sizeof(a[0]));
	hp1.Push(20);
	hp1.Pop();
}
