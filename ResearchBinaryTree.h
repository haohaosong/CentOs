/*
* author:haohaosong
* date:2017/1/8
* note:������������ʵ�֣���Ҫ�ж��Ƿ�ɾ��Ϊ���ڵ����� 
*/

#pragma once 

#include<iostream>
using namespace std;

template<typename T>
struct ResearchBinaryTreeNode
{
	ResearchBinaryTreeNode<T>* _left;
	ResearchBinaryTreeNode<T>* _right;
	T _key;

	ResearchBinaryTreeNode(const T& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<typename K>
class ResearchBinaryTree
{
	typedef ResearchBinaryTreeNode<K> Node;
public:
	ResearchBinaryTree()
		:_root(NULL)
	{}

	~ResearchBinaryTree()
	{
		Destory(_root);
	}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
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
			parent->_left = new Node(key);
		else if (parent->_key<key)
			parent->_right = new Node(key);

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
protected:
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
