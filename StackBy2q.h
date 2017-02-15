#pragma once

/*
* author:haohaosong
* data:2017/2/15
* note:��������ʵ��һ��ջ 
*/ 

#include<iostream>
using namespace std;

#include<queue>
#include<assert.h>

//��������ʵ��һ��ջ
template<typename T>
class StackBTQ
{
public:
	void Push(const T& x)
	{
		//��ջ��Ԫ��ֱ��push��qin����
		qin.push(x);
	}

	void Pop()
	{
		assert(!qin.empty() || !qout.empty());
		//qin����Ϊ��
		if (qin.empty())
		{
			while (qout.size() > 1)
			{
				qin.push(qout.front());
				qout.pop();
			}
			qout.pop();
		}
		else//qin���в�Ϊ��
		{
			while (qin.size() > 1)
			{
				qout.push(qin.front());
				qin.pop();
			}
			qin.pop();
		}
	}

	T&Top()
	{
		assert(!qin.empty() || !qout.empty());
		//qin����Ϊ��
		if (qin.empty())
		{
			while (qout.size() > 1)
			{
				qin.push(qout.front());
				qout.pop();
			}
			return qout.front();
		}
		else//qin���в�Ϊ��
		{
			while (qin.size() > 1)
			{
				qout.push(qin.front());
				qin.pop();
			}
			return qin.front();
		}
	}
protected:
	queue<T> qin;
	queue<T> qout;
};

//��������ʵ��һ��ջ
void TestForStackByTwoQueue()
{
	StackBTQ<int> s;
	s.Push(1);
	cout << s.Top() << endl;
	s.Push(2);
	cout << s.Top() << endl;
	s.Pop();
	cout << s.Top() << endl;
	s.Push(3);
	cout << s.Top() << endl;
	s.Pop();
	cout << s.Top() << endl;
}
