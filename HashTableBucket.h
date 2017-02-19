#pragma once 

/*
* author:haohaosong
* date:2017/2/19
* note:��ϣͰ��ʵ�� 
*/

#include<iostream>
using namespace std;

#include<vector>

//�����ϣͰ��һ���ڵ�
template<typename K,typename V>
struct HashTableBucketNode
{
	K _key;
	V _value;

	HashTableBucketNode<K, V>* _next;

	HashTableBucketNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};

//ʹ��������Ķ�����Ϊ��ϣ������������Խ��͹�ϣ��ͻ 
const int _PrimeSize = 28;
static const unsigned long _PrimeList[_PrimeSize] =
{
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul,
	786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul,
	25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul,
	805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

//����º�������һ�����͵�keyֵ
template<typename K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//string���ػ��汾
template<>
struct __HashFunc<string>
{
	size_t operator()(const string& s)
	{
		string::const_iterator it = s.begin();
		size_t ret = 0;
		while (it != s.end())
		{
			ret += (*it + 131);
		}
		return ret;
	}
};

//�����ϣͰ
template<typename K, typename V, typename HashFunC = __HashFunc<K>>
class HashTableBucket
{
	typedef HashTableBucketNode<K, V> Node;
public:
	//���캯��
	HashTableBucket(size_t size)
		:_size(0)
	{
		size_t newsize = GetNextPrime(size);
		_v.resize(newsize);
	}

	//��ȡ��ϣֵ
	size_t HashFunc(const K& key)
	{
		HashFunC hf;
		size_t index = hf(key);
		return index % _v.size();
	}

	//���뺯��������һ���ṹ������
	pair<Node*,bool> Insert(const K& key,const V& value)
	{
		CheckCapacity();
		size_t index = HashFunc(key);

		//���û����
		if (!_v[index])
		{
			Node* newNode = new Node(key, value);
			_v[index] = newNode;
			++_size;
			return make_pair(newNode, true);
		}
		
		Node* prev = NULL;
		Node* cur = _v[index];
		while (cur)
		{
			//��ʾ�Ѿ�����
			if (cur->_key == key)
				return make_pair(cur, false);

			prev = cur;
			cur = cur->_next;
		}
		Node* newNode = new Node(key, value);
		prev->_next = newNode;
		++_size;
		return make_pair(newNode, true);
	}

	Node* find(const K& key)
	{
		//������Ͱ
		for (size_t index = 0; index < _size; ++index)
		{
			Node* cur = _v[index];

			//����ÿһ����_v[index]Ϊͷ������
			while (cur)
			{
				//�ҵ��ýڵ㣬����
				if (cur->_key == key)
					return cur;

				cur = cur->_next;
			}
		}

		//û�в�ѯ��
		return NULL;
	}

	bool Erase(const K& key)
	{
		//�ҳ�key���ڵ�����λ��
		size_t index = HashFunc(key);

		//�����Ը�_v[index]Ϊͷ������
		Node* cur = _v[index];//��Ҫɾ���Ľڵ�
		Node* prev = NULL;//ɾ���ڵ��ǰһ���ڵ�

		while (cur)
		{
			if (cur->_key == key)
			{
				if (prev == NULL)
					_v[index] = NULL;
				else
					prev->_next = cur->_next;

				delete cur;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}

		return false;
	}

protected:
	vector<Node*> _v;
	size_t _size;
protected:
	//����������ϣͰ������
	void Swap(HashTableBucket<K,V> & tmp)
	{
		std::swap(_v, tmp._v);
		std::swap(_size, tmp._size);
	}

	size_t GetNextPrime(size_t size)
	{
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			//�ҵ���һ������
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}

		return _PrimeList[_PrimeSize-1];
	}


	//����Ƿ���Ҫ����
	void CheckCapacity()
	{
		//��ʱϵ��Ϊ1���ﵽ1��ʱ������
		if (_size == _v.size())
		{
			HashTableBucket<K, V> tmp(_v.size());

			for (size_t index = 0; index < _size; ++index)
			{
				Node* cur = _v[index];
				while (cur)
				{
					tmp.Insert(cur->_key, cur->_value);
					cur = cur->_next;
				}
			}

			Swap(tmp);
		}
	}
};

void TestHashTableBucket()
{
	HashTableBucket<int, int> hb(4);
	hb.Insert(10, 0);
	hb.Insert(20, 0);
	hb.Insert(30, 0);
	hb.Insert(40, 0);
	hb.Insert(50, 0);
	hb.Insert(60, 0);
	hb.Insert(70, 0);

	hb.Erase(10);
}
