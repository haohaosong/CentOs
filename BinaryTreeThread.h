#pragma once 

/*
* author:haohaosong
* date:2016/12/24
* node:�����������������԰Ѷ�����������Ϊ�Լ���Ҫ�����У��ڴ˺�ı����У�������Ҫ�ݹ�
*      ���������������ӷ�������̺ܺ��ң�ǰ���Ļ���Ҫͨ��ʱ��������~
*/

#include<iostream>
using namespace std;

//����һ��ö�����ͣ������жϽڵ��Ƿ�������
enum PointerTag
{
	LINK,
	THREDA,
};

//��������������Ľڵ�
template<typename T>
struct BinaryTreeThdNode
{
	typedef BinaryTreeThdNode Node;

	T _data;

	Node* _left;
	Node* _right; 

	//��ǣ������жϺ�����û�б�������
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeThdNode(T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

template<typename T,typename Ref,typename Ptr>
struct  BinaryTreeTheIterator
{
	typedef BinaryTreeTheIterator<T, T&, T*> Self; //������ΪSelf
	typedef BinaryTreeThdNode<T> Node;

	Node* _node;

	BinaryTreeTheIterator(Node* node = NULL)
		:_node(node)
	{}

	//���� == �� != 
	bool operator == (const Self& s)
	{
		return _node == s._node; 
	}
	bool operator != (const Self& s)
	{
		return _node != s._node;
	}

	//���ؽ����úͼ�ͷ
	Ref operator*()
	{
		return (*_node)._data;
	}
	Ref operator->()
	{
		return &(operator*());
	}

	//����++
	Self& operator++()
	{
		//����Һ����Ǳ��������ģ�ֱ���Һ��
		if (_node->_rightTag == THREDA)
		{
			_node = _node->_right;
		}
		else
		{
			//���ҵ��Һ���
			if (_node)
				_node = _node->_right;
			
			//���Һ�����������ߵĽڵ�
			if (_node)
			{
				while (_node->_leftTag == LINK)
					_node = _node->_left;
			}
		}
		return *this;
	}
	Self operator++(int)//����++
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}

	// -- ��ʱû�����

	//Self& operator--()
	//{
	//	if (_node->_leftTag == THREDA)
	//	{
	//		_node = _node->_left;
	//	}
	//	else
	//	{
	//		Node* cur = _root;

	//		while (cur)
	//		{
	//			//����ʼ�ڵ�
	//			while (cur->_leftTag == LINK)
	//			{
	//				cur = cur->_left;
	//			}

	//			//ѭ���ҵ�this����һ��
	//			while (cur != *this)
	//			{
	//				_node = cur;
	//				++cur;
	//			}
	//		}
	//	}
	//	return *this;
	//}
	//Ref operator--(int)
	//{
	//	Self tmp(*this);
	//	--(*this);
	//	return tmp;
	//}
};

//�������������
template<typename T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;//������
public:	
	typedef BinaryTreeTheIterator<T, T&, T*> Iterator;
	typedef BinaryTreeTheIterator<T, const T&, const T*> ConstIterator;
public:
	BinaryTreeThd()
		:_root(NULL)
	{}

	BinaryTreeThd(T* arr, size_t sz, T invalid = T())
	{
		size_t index = 0;
		_root = CreateTree(arr, sz, index, invalid);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void InOrderThreadding()
	{
		Node* prev = NULL;
		_InOrderThreadding(_root, prev);
	}

	void InOrderThd()
	{
		Node* cur = _root;

		while (cur)
		{ 
			//ѭ���ҵ�����ߵĽڵ�
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			cout << cur->_data << " ";

			//�ж��ұ��ǲ��ǿ���ֱ�����ú�̣���Ҫ��whileѭ���������޷�������
			while (cur->_rightTag == THREDA)
			{
				cur = cur->_right;
				//ֻҪcur���ڣ���ô����ֱ�ӷ���
				if (cur)
					cout << cur->_data << " ";
			}

			//�Һ�����LINK�ڵ㣬û�б���������ô���з���
			cur = cur->_right;
		}
		cout << endl;
	}

	Iterator Begin()
	{
		Node* cur = _root;
		//�Ӹ���ʼ��������ߵĽڵ�
		while (cur->_leftTag == LINK)
			cur = cur->_left;

		return cur;
	}

	Iterator End()
	{
		//����ҿ���End()Ϊ��
		return NULL;
	}

protected:
	Node* CreateTree(T* arr, const size_t sz, size_t& index, T& invalid)
	{
		if (index < sz && arr[index] != invalid)
		{
			Node* root = new Node(arr[index]);
			root->_left = CreateTree(arr,sz,++index,invalid);
			root->_right = CreateTree(arr, sz,++index, invalid);
			return root;
		}
		return NULL;
	}

	void _InOrder(Node* root)
	{
		//�ڵ�Ϊ�գ�����
		if (root == NULL)
			return;

		//����ڵ�û�б���������ô�ݹ�
		if (root->_leftTag == LINK)
			_InOrder(root->_left);
		cout << root->_data << " ";
		if (root->_rightTag == LINK)
			_InOrder(root->_right);
	}

	//������������������
	void _InOrderThreadding(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		
		//����������Ƚ��еݹ飬������ߵĽڵ�
		_InOrderThreadding(cur->_left, prev);

		//����Ϊ��
		if (cur->_left == NULL)
		{
			cur->_left = prev;//����һ���ڵ㸳������
			cur->_leftTag = THREDA;//���ı��Ϊ������
		}

		//�ж���һ���ڵ���Һ��ӣ����������Ϊ��
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;//��һ���ڵ���Һ���ָ���Լ�
			prev->_rightTag = THREDA;//���ı��
		}

		//��һ��Ҫ����ѭ��������
		prev = cur;

		//�������Һ���
		_InOrderThreadding(cur->_right, prev);
	}
protected:
	//������ڵ�
	Node* _root;
};

void TestBinaryTreeThd()
{
	int arr[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd<int> t(arr, sizeof(arr) / sizeof(arr[0]),'#');

	t.InOrder();
	t.InOrderThreadding();

	t.InOrder();
	t.InOrderThd();

	BinaryTreeThd<int>::Iterator it = t.Begin();
	while (it != t.End())
	{
		cout << *it << " ";
		it++;
	}
	/*size_t count = 0;
	while (it != t.End() && count <3)
	{
		it++;
	}
	while (it != NULL)
	{
		cout << *it << " ";
		--it;
	}*/
}
