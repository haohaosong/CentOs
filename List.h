#pragma once

/*
* note:��ν������������Ϊ������Щ��������������ָ��Ĺ���������Ԫ��
*      ��C�����У�����ָ���++��--�������ÿ��Է���Ĳ�������ȡ����
*	   ��C++�еĵ�����������ģ��ʵ������ָ��Ĺ���
*/

#include<iostream>
using namespace std;

//��������ڵ�Ľṹ��
template<typename T>
struct __ListNode
{
	__ListNode<T>* _next;
	__ListNode<T>* _prev;
	T _data;

	__ListNode(const T& data)//�����ڵ�Ĺ��캯��
		:_next(NULL)
		, _prev(NULL)
		, _data(data)
	{}
};

//���������,ģ�����ΪT,T������,T���͵�ָ��
template<typename T, typename Ref, typename Ptr>
struct __ListIterator
{
	typedef __ListNode<T> Node;//������ڵ�������Ϊ Node
	typedef __ListIterator<T, T&, T*> self; //���Լ�������������Ϊ self��������
	Node* _node;

	__ListIterator(){}
	__ListIterator(Node* node)
		:_node(node)
	{}

	//���� !=��==������
	bool operator != (const self& s)
	{
		return _node != s._node;
	}
	bool operator == (const self& s)
	{
		return _node == s._node;
	}

	//���� ++��-- ������
	self& operator ++()
	{
		_node = _node->_next;
		return (self&)_node;
	}
	self operator ++ (int)
	{
		Node* tmp = _node;
		++_node;
		return tmp;
	}
	self& operator --()
	{
		_node = _node->_prev;
		return (self&)_node;
	}
	self operator -- (int)
	{
		Node* tmp = _node;
		--_node;
		return tmp;
	}

	//����*��->������
	Ref operator*()
	{
		return (*_node)._data;
	}
	Ref operator->()
	{
		return *_node;
	}
};

//���巴�������,ģ�����ΪT,T������,T���͵�ָ��
template<typename T, typename Ref, typename Ptr>
struct __ListReverseIterator
{
	typedef __ListNode<T> Node;//������ڵ�������Ϊ Node
	typedef __ListReverseIterator<T, T&, T*> self;//���Լ�������������Ϊself��������

	Node* _node;
	__ListReverseIterator()
	{}
	__ListReverseIterator(Node* node)
		:_node(node)
	{}

	//���� ++��-- ������
	self& operator++()
	{
		_node = _node->_prev;//ע�⣺�����Ƿ����������++Ӧ��ָ��ǰһ��
							//���Ƿ����������ؼ��ĵط�
		return (self&)_node;
	}
	self operator++(int)
	{
		Node* tmp = _node;
		_node = _node->_prev;
		return tmp;
	}
	self& operator--()
	{
		_node = _node->_next;
		return (self&)_node;
	}
	self operator--(int)
	{
		Node* tmp = _node;
		_node = _node->_next;
		return tmp;
	}

	//���� !=��==������
	bool operator==(const self& s)
	{
		return _node->_data == s._node->_data;
	}
	bool operator!=(const self& s)
	{
		return _node->_data != s._node->_data;
	}

	//����*��->������
	Ref operator*()
	{
		return (*_node)._data;
	}
	Ref operator->()
	{
		return *_node;
	}
};

//��������
template<typename T>
class List
{
	typedef __ListNode<T> Node;
public:
	typedef __ListIterator<T, T&, T*> Iterator;//������Ϊ������
	typedef __ListReverseIterator<T, T&, T*> ReverseIterator;//������Ϊ���������
	
	//����һ���µĽڵ�
	Node* BuyNewNode(const T& t)
	{
		return new Node(t);
	}
	//���캯��
	List()
		:_head(BuyNewNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	//��β�����룬ɾ��һ��Ԫ��
	void PushBack(const T& x)
	{
		Node* tail = _head->_prev;
		Node* tmp = BuyNewNode(x);
		tail->_next = tmp;
		tmp->_prev = tail;
		tmp->_next = _head;
		_head->_prev = tmp;
	}

	//���巵�ص��������͵�Begin()��End()
	Iterator Begin()
	{
		return Iterator(_head->_next);
	}
	Iterator End()
	{
		return Iterator(_head);
	}

	//���巵�ص��������͵�rBegin()��rEnd()
	ReverseIterator rBegin()
	{
		return ReverseIterator(_head->_prev);
	}
	ReverseIterator rEnd()
	{
		return ReverseIterator(_head);
	}
protected:
	Node* _head;
};

//��������
void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	//��ӡl�е�Ԫ��
	List<int> ::Iterator it1 = l.Begin();//���������it1Ϊl����ʼ����
	while (it1 != l.End())
	{
		cout << *it1 << " ";//�����˽����ò����������Է���it1�е�Ԫ��
		++it1;//������++����������Է�����һ��Ԫ��
	}
	cout << endl;
}

void TestReverseIterator()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);

	List<int>::ReverseIterator it = l.rBegin();//���巴�������itΪ����������ĵ�һ��Ԫ��
	while (it != l.rEnd())
	{
		cout << *it << " ";//�����˽����ò�����������Ԫ�ص�ǰ����
		it++;//������++����������ʺ����Ԫ��
	}
	cout << endl;
}
