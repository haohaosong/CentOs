#pragma once

/*
* author:haohaosong
* date:2017/2/15
* note:����ջʵ��һ������ 
*/ 

#include<iostream>
using namespace std;

#include<assert.h>
#include<stack>

//����ջʵ��һ������
template<typename T>
class QueueBTS
{
public:
	void Push(const T& x)
	{
		sin.push(x);
	}
	void Pop()
	{
		assert(!sin.empty() || !sout.empty());
		if (sout.empty())
		{
			while (!sin.empty())
			{
				sout.push(sin.top());
				sin.pop();
			}
		}
		sout.pop();
	}

	const T& Front()
	{
		assert(!sin.empty() || !sout.empty());
		if (sout.empty())
		{
			while (!sin.empty())
			{
				sout.push(sin.top());
				sin.pop();
			}
		}
		return sout.top();
	}
protected:
	stack<T> sin;//���е�ջ
	stack<T> sout;//���е�ջ
};

//����ջʵ��һ������
void TestForQueueByTwoStack()
{
	QueueBTS<int> q;
	q.Push(1);
	cout << q.Front() << endl;
	q.Push(2);
	cout << q.Front() << endl;
	q.Pop();
	cout << q.Front() << endl;
	q.Push(3);
	cout << q.Front() << endl;
	q.Pop();
	cout << q.Front() << endl;
}
