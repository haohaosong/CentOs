#pragma once

/*
* author:haohaosong 
* date:2017/2/13 
* note:红黑树的实现 
*/

#include<iostream>
using namespace std;

//定义枚举Color,标示 红黑树的颜色 
enum Color
{
	RED,
	BLACK,
};

//定义一个红黑树的节点 
template<typename K,typename V>
struct RBTreeNode
{
	K _key;
	V _value;

	Color _col;

	//这里实现的是三叉链 
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	//构造函数 
	RBTreeNode(const K& key,const V& value)
		: _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _col(RED)
	{}
};

//定义一颗红黑树 
template<typename K,typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	//插入函数 
	pair<Node*,bool> Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return make_pair(_root,true);
		}

		Node* cur = _root;
		Node* parent = NULL;
		
		//找到插入节点的位置 
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, false);
			}
		}

		//将节点插入 
		cur = new Node(key, value);
		Node* newNode = cur;
		if (key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
	
		//循环判断是否需要调整 
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.叔叔存在且为红，变色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else //叔叔不存在/叔叔存在且为黑
				{
					//2.进行单旋
					if (cur == parent->_left)
					{
						RotateR(grandfather);

						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else //3.进行双旋
					{
						RotateL(parent);
						RotateR(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//1.叔叔存在且为红，变色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else //叔叔不存在/叔叔存在且为黑
				{
					//2.进行单旋
					if (cur == parent->_right)
					{
						RotateL(grandfather);

						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else //3.进行双旋
					{
						RotateR(parent);
						RotateL(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}

		_root->_col = BLACK;
		return make_pair(newNode, true);
	}

	bool IsBalance()
	{
		//1.空树，属于红黑树
		if (_root == NULL)
			return true; 

		//2.根节点不为黑
		if (_root->_col != BLACK)
			return false;

		//3.统计出一条路径上黑色节点的数量
		size_t k = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				k++;

			cur = cur->_left;
		}

		return CheckColor(_root) && CheckBlackNum(_root, k, 0);
	}

	//中序遍历 
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	//重载[]，来插入元素 
	V& operator[](const K& key)
	{	
		return Insert(key, V()).first->_value;
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

	bool CheckColor(Node* root)
	{
		//1.空树，满足
		if (root == NULL)
			return true;

		//2.判断父亲，是否是连续的红色
		if (root->_col == RED && root->_parent->_col == RED)
			return false;

		return CheckColor(root->_left) && CheckColor(root->_right);
	}

	bool CheckBlackNum(Node* root, const size_t &k, size_t num)
	{
		//1.空树，满足
		if (root == NULL)
			return true;

		if (root->_col == BLACK)
			++num;

		//2.叶子节点，判断黑色节点数量
		if (root->_left == NULL && root->_right == NULL && num != k)
			return false;

		return CheckBlackNum(root->_left, k, num) 
			&& CheckBlackNum(root->_right, k, num);
	}

	//右旋 
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
	}

	//左旋 
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
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		else
		{
			_root = subR;
			subR->_parent = NULL;
		}
	}
protected:
	Node* _root;
};

void TestRBTree()
{
	int s[12] = { 2, 6, 1, 0, 3, 8, 11, 15, 10, 9, 4, 7 };
	RBTree<int, int> rb;

	for (size_t i = 0; i < sizeof(s) / sizeof(s[0]); ++i)
	{
		rb.Insert(s[i], 0);
		cout << s[i] << " IsBalance:" << rb.IsBalance() << endl;
	}

	cout <<"IsBalance:" << rb.IsBalance() << endl;
	rb.InOrder();
}
