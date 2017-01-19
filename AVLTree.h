#pragma once

#include<assert.h>
#include<iostream>
using namespace std;

template<typename K, typename V>
struct AVLTreeNode
{
	typedef AVLTreeNode<K, V> Node;

	Node* _left;
	Node* _right;
	Node* _parent;

	//ƽ������
	int _bf;

	K _key;
	V _value;

	AVLTreeNode(const K&key, const V&value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
		, _key(key)
		, _value(value)
	{}
};

template<typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	//������ɺ����ƽ������ 
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (key > cur->_key)
				cur = cur->_right;
			else if (key < cur->_key)
				cur = cur->_left;
			else
				return false;
		}

		Node* newNode = new Node(key, value);
		if (parent->_key > key)
			parent->_left = newNode;
		else
			parent->_right = newNode;

		newNode->_parent = parent;

		//����ƽ������
		while (parent)
		{
			if (parent->_left == newNode)
				parent->_bf -= 1;
			else
				parent->_bf += 1;

			//ƽ������Ϊ0���������ϸ��� 
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1
				|| parent->_bf == -1)//��0�䵽1��-1������������ϸ��� 
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2
				|| parent->_bf == -2)//2��-2��������ת 
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
						//����
						RotateL(parent);
					else
						RotateRL(parent); 
				}
				else
				{
					if (cur->_bf == 1)
						RotateLR(parent); 
					else
						//����
						RotateR(parent);
				}

				break;
			}
			else//-3����3 
			{
				cout << "ƽ�������쳣" << endl;
				assert(false);
			}
		}

		return true;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
				cur = cur->_right;
			else if (key < cur->_key)
				cur = cur->_left;
			else
				return cur;
		}
		return NULL;
	}

	//�ж�һ��AVL���ǲ���ƽ��
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	bool IsBalanceOP()
	{
		size_t depth = 0;
		return _IsBalanceOP(_root,depth);
	}

	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode)
		{
			if (ppNode->_right == parent)
				ppNode->_right = subR;
			else
				ppNode->_left = subR;

			subR->_parent = ppNode;
		}
		else
		{
			subR->_parent = NULL;
			_root = subR;
		}

		parent->_bf = subR->_bf = 0;

	}

	//����
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent; 

		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode)
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		else
		{
			_root = subL;
			subL->_parent = NULL;
		}

		parent->_bf = subL->_bf = 0;
	}
	
	//������
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);

		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = subRL->_bf = 0;
		}

		subRL->_bf = 0;
	}

	//������
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);

		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else
		{
			parent->_bf = subLR->_bf = 0;
		}

		subLR->_bf = 0;
	}


	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;

		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}

	//ʱ�临�Ӷȣ�O(n^2)
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;

		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return abs(leftDepth - rightDepth) <= 1
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

	bool _IsBalanceOP(Node* root, size_t& depth)
	{
		if (root == NULL)
		{
			depth = 0;
			return true;
		}

		size_t leftDepth = 0;
		size_t rightDepth = 0;

		if (_IsBalanceOP(root->_left,leftDepth)
			&& _IsBalanceOP(root->_right,rightDepth)
		{
				depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
				return (leftDepth - rightDepth) < 2;
		}
		else
		{
			return false;
		}
	}
protected:
	Node* _root;
};

void TestAVL()
{
	AVLTree<int, int> t;
	t.Insert(1, 0);
	t.Insert(2, 0);
	t.Insert(3, 0);
	t.Insert(4, 0);
	t.Insert(5, 0);
	t.Insert(6, 0);
	t.Insert(7, 0);
	t.Insert(8, 0);
	t.InOrder(); 
}
