/*
* author:haohaosong
* date:2017/1/1
* note:�������� 
*/ 

#pragma once

#include<iostream>
using namespace std;
#include"heap.h"

template<typename T>
struct HuffmanTreeNode
{
	typedef HuffmanTreeNode<T> Node;

	T _weight;    //Ȩ��

	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;//������������Ѱ�Ҹ��׽ڵ� 

	HuffmanTreeNode(const T& x)
		:_left(0)
		,_right(0)
		,_parent(0)
		, _weight(x)
	{}

	//����+
	Node operator + (const Node& t)
	{
		return new Node(_weight + t._weight);
	}
};

template<typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
	{}

	HuffmanTree(T* arr, size_t n, T& invalid)
	{
		//����º���������huffman���ڵ�ıȽ� 
		struct compare
		{
			bool operator()(Node* l,Node* r)
			{
				return l->_weight < r->_weight;
			}
		};

		//�������ʼ����һ����
		Heap<Node*,compare> hp; 
		for (size_t i = 0; i<n; ++i)
		{
			if (arr[i] != invalid)
			{
				hp.Push(new Node(arr[i]));
			}
		}

		//���й��������Ĺ������Ѷ�Ԫ������С�� 
		while (hp.Size()>1)
		{
			Node* left = hp.Top();
			hp.Pop();
			Node* right = hp.Top();
			hp.Pop();
			Node* parent = new Node(left->_weight + right->_weight);

			parent->_left = left;
			parent->_right = right;
			left->_parent = parent; 
			right->_parent = parent;

			hp.Push(parent);
		}
		_root = hp.Top();
	}

	~HuffmanTree()
	{
		Destory(_root);
		_root = NULL;
	}
protected:
	Node* _root;

	void Destory(Node* root)
	{
		if (root == NULL)
			return;

		Destory(root->_left);
		Destory(root->_right);

		delete root;
		root = NULL;
	}
	//������ 
	HuffmanTree(const HuffmanTree<T>& t);
	HuffmanTree& operator=(const HuffmanTree<T>& t);
};

void TestHuffman()
{
	int arr[5] = { 1, 2, 3, 4 };
	HuffmanTree<int> huff(arr,4,0);
}
