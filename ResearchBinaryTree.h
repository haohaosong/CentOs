/*
* author:haohaosong
* date:2017/1/8
* note:������������ʵ�֣���Ҫ�ж��Ƿ�ɾ��Ϊ���ڵ����� 
*/

#pragma once 
#include<assert.h> 
#include<iostream>
using namespace std;

template<typename K,typename V>
struct ResearchBinaryTreeNode
{
	ResearchBinaryTreeNode<K, V>* _left;
	ResearchBinaryTreeNode<K, V>* _right;

	K _key;
	V _value;

	ResearchBinaryTreeNode(const K& key,const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<typename K,typename V>
class ResearchBinaryTree
{
	typedef ResearchBinaryTreeNode<K,typename V> Node;
public:
	ResearchBinaryTree()
		:_root(NULL)
	{}

	~ResearchBinaryTree()
	{
		Destory(_root);
		_root = NULL; 
	}

	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key��value);
			return true;
		}

		Node* cur = _root;
		Node* parent = cur;

		//�ҵ���Ҫ����ڵ�ĸ��׽ڵ�
		while (cur)
		{
			parent = cur;

			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key>key)
				cur = cur->_left;
			else
				return false; 
		}

		//parentΪ��Ҫ����ڵ�ĸ��׽ڵ�
		if (parent->_key > key)
			parent->_left = new Node(key,value);
		else if (parent->_key<key)
			parent->_right = new Node(key,value);

		return true;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root; 
		
		//�����������������ص������в���
		while (cur)
		{
			if (key < cur->_key)
				cur = cur->_left;
			else if (key>cur->_key)
				cur = cur->_right;
			else
				return cur;
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		Node* delNode = NULL;

		//�ҳ�Ҫɾ���Ľڵ��Լ��丸�׽ڵ�
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key >cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}
	
		if (cur == NULL)
			return false;

		//���ɾ�����Ǹ��ڵ㣬��ôparent��ֵΪNULL 
		//cur��ʱ��Ҫɾ���Ľڵ�
		if (cur->_left == NULL)
		{
			delNode = cur;

			//cur�Ǹ��׽ڵ�����ӵĻ����Ͱ�cur���Һ��Ӹ������׽ڵ������
			//���򣬽�cur���Һ��Ӹ������׽ڵ���Һ���
			if (parent == NULL)
				_root = cur->_right;
			else if (parent->_left == cur)
				parent->_left = cur->_right;
			else
				parent->_right = cur->_right;
		}
		else if (cur->_right == NULL)
		{
			delNode = cur;

			//cur�Ǹ��׽ڵ�����ӵĻ����Ͱ�cur���Һ��Ӹ������׽ڵ������
			//���򣬽�cur���Һ��Ӹ������׽ڵ���Һ���
			if (parent == NULL)
				_root = cur->_left;

			else if(parent->_left == cur)	
				parent->_left = cur->_left;
			else
				parent->_right = cur->_left;
		}
		else
		{
			//����Ϊ�յ��������Ҫ�����滻�������
			Node* subLeft = NULL;//����������������ڵ�

			//ѭ���ҵ�������������ڵ�
			//����subLeft������Ϊ��
			subLeft = cur->_right;
			parent = cur;
			while (subLeft->_left)
			{
				parent = subLeft;
				subLeft = subLeft->_left;
			}

			cur->_key = subLeft->_key;

			if (parent->_left == subLeft)
				parent->_left = subLeft->_right;
			else
				parent->_right = subLeft->_right;

			delNode = subLeft;
		}

		delete delNode;
		delNode = NULL;

		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	
	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}

	bool RemoveR(const K&key)
	{
		return _RemoveR(_root, key);
	}
protected:
	bool _RemoveR(Node* root,const K& key)
	{
		if (root == NULL)
			return false;

		//�ݹ飬�ҵ�Ҫɾ���Ľڵ�
		if (root->_key < key)
			return _RemoveR(root->_right, key);
		else if (root->_key > key)
			return _RemoveR(root->_left, key);
		else
		{
			Node* delNode = root;

			//ɾ���ڵ����Ϊ��
			if (root->_left == NULL)
				root = root->_right; 
			else if (root->_right == NULL)
				root = root->_left;
			else//���Ҷ���Ϊ�յ����
			{
				Node* parent = root;
				Node* subLeft = root->_right;

				while (subLeft->_left)
				{
					parent = subLeft;
					subLeft = subLeft->_left;
				}

				delNode = subLeft;

				//��Ϊ����������������whileѭ��������û����ѭ��
				//Ҫɾ���Ľڵ���subLeft

				root->_key = subLeft->_key;

				if (parent->_left == subLeft)
					parent->_left = subLeft->_right;
				else
					parent->_right = subLeft->_right;

				delete delNode;
				return true;
			}
		}
	}

	bool _InsertR(Node*& root, const K& key, const V& value)
	{
		//�����½ڵ�
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		
		if (key < root->_key)
			return _InsertR(root->_left, key, value);
		else if (key > root->_key)
			return _InsertR(root->_right, key, value);
		else
			return false;
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;

		if (key < root->_key)
			return _FindR(root->_left, key);
		else if (key>root->_key)
			return _FindR(root->_right, key);
		else
			return root;
	}
	
	void Destory(Node* root)
	{
		if (root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
protected:
	Node* _root;
};
