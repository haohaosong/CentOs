#pragma once

#include<iostream>
using namespace std;

/*
* author:haohaosong
* date:2017/2/23
* note:B����ʵ�� 
*/

//B������ɾ��ĵ�ʱ�临�Ӷ� O(logM(N))

//����B���Ľڵ�
template<typename K,typename V,size_t M = 3>
struct BTreeNode
{
	pair<K,V> _kv[M];
	
	BTreeNode<K, V> *_subs[M+1];
	BTreeNode<K, V> *_parent;

	//��ʾ�洢�˶��ٸ�Keyֵ
	size_t _size;

	//�ڵ�Ĺ��캯��
	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (size_t i = 0; i <= M; ++i)
		{
			_subs[i] = NULL;
		}
	}
};

//B���Ķ���
template<typename K, typename V,size_t M = 3>
class BTree
{
	typedef BTreeNode<K, V> Node;
public:
	//���캯��
	BTree()
		:_root(NULL)
	{}

	//���Һ������䷵��ֵ�����ʵ����Insert�ĸ���
	pair<Node*,int> Find(const K& key)
	{
		//����ѯ����������parent��¼��Ҫ����Ľڵ�ĸ��ڵ�
		//ʵ����Insert�ĸ���
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			size_t index = 0;
			while (index < cur->_size)
			{
				if (key > cur->_kv[index].first)
				{
					index++;
				}
				else if (key == cur->_kv[index].first)
				{
					//��ѯ�������ز�ѯ�Ľڵ�
					return make_pair(cur, index);
				}
				else
				{
					break;
				}
			}
			parent = cur;
			cur = cur->_subs[index];
		}

		//û�в�ѯ��,������Ҫ����ڵ�ĸ��׽ڵ�
		//ʵ����Insert�����ĸ���
		return make_pair(parent, -1);
	}

	bool Insert(const pair<K, V>& kv)
	{
		//�����ڵ�Ϊ�յ�ʱ����Ҫ��_root���и�ֵ
		if (_root == NULL)
		{
			_root = new Node;
			_root->_size = 1;
			_root->_kv[0] = kv;
			return true;
		}

		//��Ϊ�գ����ҵ������λ��
		//���second��ֵ��Ϊ-1�����ʾ�Ѿ����ڣ�����Ҫ����
		pair<Node*, int> ret = Find(kv.first); 
		if (ret.second != -1)
			return false;

		//���в���
		Node* cur = ret.first;
		Node* temp = cur;
		pair<K, V> newKV = kv;
		Node* sub = NULL;

		while (1)
		{
			//��cur�ڵ����kv��sub
			_Insert(cur, newKV,sub);

			//���curû�������ʾ����ɹ�
			//������Ҫ���з���
			if (cur->_size < M)
				return true;

			//����һ���½ڵ�tmp
			Node* tmp = new Node;
			size_t mid = M >> 1;
			size_t i = mid+1;
			size_t j = 0;

			//���Ұ������Ԫ���Ƶ�tmp��
			while (i < cur->_size)
			{
				tmp->_kv[j] = cur->_kv[i];
				cur->_kv[i] = pair<K, V>();

				tmp->_subs[j] = cur->_subs[i];
				if (cur->_subs[i])
					cur->_subs[i]->_parent = tmp;

				//����
				i++;
				j++;
				tmp->_size++;
				cur->_size--;
			}

			//�������һ���Һ���
			tmp->_subs[j] = cur->_subs[i];
			cur->_subs[i] = NULL;
			if (cur->_subs[i])
				cur->_subs[i]->_parent = tmp;

			//���curû�и��׽ڵ㣬��Ҫ����
			//���cur�и��׽ڵ㣬��ô��Ҫ���м�Ԫ�ز��뵽���׽ڵ���
			if (cur->_parent)
			{
				//�������ϵ������б��Ƿ�parent����
				newKV = cur->_kv[mid];
				sub = tmp;
				cur->_size--;
				cur = cur->_parent;
			}
			else
			{
				//����һ���¸��ڵ㣬���м�Ԫ�ط���ýڵ���
				Node* newRoot = new Node;
				newRoot->_kv[0] = cur->_kv[mid];
				newRoot->_size = 1;

				//�����¸��ڵ����������cur��tmp
				//���޸����ǵĸ��׽ڵ�
				newRoot->_subs[0] = cur;
				cur->_parent = newRoot;
				newRoot->_subs[1] = tmp;
				tmp->_parent = newRoot;

				cur->_size--;

				//�����ڵ����¸�ֵ
				_root = newRoot;
				return true;
			}
		}
	}

	//�������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	void _Insert(Node* cur,const pair<K,V>& newKV,Node* sub)
	{
		//����Ҫ��int��������size_t����Ӱ��whileѭ�����ж�����
		int index = (cur->_size)-1;
		while (index >= 0)
		{
			//�ҵ����ʵĲ���λ�ã�����
			if (newKV.first > cur->_kv[index].first)
				break;

			//��keyֵ����ƶ������ҽ�����Ҳ�ƶ�
			cur->_kv[index + 1] = cur->_kv[index];
			cur->_subs[index + 2] = cur->_subs[index + 1];
			index--;
		}

		//�����µ�KV�Լ�����
		cur->_kv[index+1] = newKV;
		cur->_subs[index+2] = sub;

		//���Ӵ��ڣ����丸�׸�ֵ
		if (sub)
			sub->_parent = cur;

		cur->_size++;
	}

	//��������ݹ麯��
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		//����ÿһ��keyֵ��������
		size_t index = 0;
		while (index < root->_size)
		{
			_InOrder(root->_subs[index]);
			cout << root->_kv[index].first<<" ";
			index++;
		}

		//��ӡ���һ��keyֵ���Һ���
		_InOrder(root->_subs[root->_size]);
	}
protected:
	Node* _root;
};

void TestBtree()
{
	BTree<int, int> t;
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t.Insert(make_pair(a[i], i));
		t.InOrder();
	}

	t.InOrder();
}
