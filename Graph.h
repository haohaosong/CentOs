#pragma once 

/*
* author:haohaosong
* date:2017/3/14
* note:ͼ��ʵ���Լ���ȹ�����ȱ���
*/

#include<iostream>
using namespace std;

#include<vector>
#include<assert.h>
#include<queue>
#include<string>
#include<set>
//ͼ������ʵ�ַ�ʽ:�ڽӱ��ڽӾ���
//����1:�ڽӾ���

template<typename V,typename W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertexs, size_t n, const W& invalid = W(), bool IsDirected = false)
		:_vertexs(vertexs, vertexs + n)
		, _isDirected(IsDirected)
	{
		_matrix = new W*[n];
		for (size_t i = 0; i < n; ++i)
		{
			_matrix[i] = new W[n];
			for (size_t j = 0; j < n; ++j)
			{
				_matrix[i][j] = invalid;
			}
		}
	}

	~GraphMatrix()
	{}

	int GetIndex(const V& v)
	{
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (_vertexs[i] == v)
				return i;
		}
		assert(false);
		return -1;
	}

	void AddEdge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetIndex(v1);
		size_t des = GetIndex(v2);
		_matrix[src][des] = w;

		if (_isDirected == false)
			_matrix[des][src] = w;
	}
protected:
	vector<V> _vertexs;//����ļ���
	W** _matrix;//�ڽӾ���ߵļ���
	bool _isDirected;//�Ƿ�������ͼ
};

void TestGraphMatrix()
{
	string city[] = { "����", "�Ϻ�", "����", "����", "����" };
	GraphMatrix<string, double> gpm(city, sizeof(city) / sizeof(city[0]));
	gpm.AddEdge("����", "�Ϻ�", 300.3);
	gpm.AddEdge("����", "����", 850.5);
	gpm.AddEdge("����", "����", 299);
	gpm.AddEdge("����", "����", 475);
}

//����2:�ڽӱ�
template<typename W>
struct LinkNode
{
	W _weight;
	LinkNode<W> *_next;
	size_t _src;
	size_t _des;

	LinkNode(size_t src,size_t des,const W& weight)
		:_weight(weight)
		, _next(NULL)
		, _src(src)
		, _des(des)
	{}
};

template<typename V,typename W>
class GraphLink
{
	typedef LinkNode<W> Node;
public:
	GraphLink(V* vertexs, size_t n, bool IsDirected = false)
	{
		_vertexs.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			_vertexs[i] = vertexs[i];
		}
		_linkTables.resize(n, NULL);
	}

	~GraphLink()
	{}

	int GetIndex(const V& v)
	{
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (v == _vertexs[i])
				return i;
		}
		assert(false); 
		return -1;
	}

	V& GetV(const size_t index)
	{
		assert(index < _vertexs.size());
		return _vertexs[index];
	}

	void _AddEgde(const size_t& src, const size_t& des, const W&w)
	{
		//����ͷ��
		Node* newNode = new Node(src,des, w);
		newNode->_next = _linkTables[src];
		_linkTables[src] = newNode;
	}

	void AddEdge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetIndex(v1);
		size_t des = GetIndex(v2);
		_AddEgde(src, des, w);

		if (_isDirected == false)
			_AddEgde(des, src, w);
	}

	void GFS(const V& src)//������ȱ���
	{
		//���ö��������й�����ȱ���
		//����set�������ж�һ�������Ƿ񱻷��ʹ�
		queue<size_t> q;
		q.push(GetIndex(src));
		set<size_t> s;
		s.insert(GetIndex(src));
		while (!q.empty())
		{
			size_t tmp = q.front();
			cout << GetV(tmp) << " ";
			q.pop();
			Node* cur = _linkTables[tmp];

			//����һ���ڵ���ڽӱ�
			//��û�з��ʹ��Ľڵ������к�set��
			while (cur)
			{
				//����insert�ķ���ֵ���ж��Ƿ񶥵��Ѿ������ʹ�
				//���û�б����ʹ��������ɹ��������������
				pair<set<size_t>::iterator, bool> ret = s.insert(cur->_des);
				if (ret.second == true)
					q.push(*ret.first);

				cur = cur->_next;
			}
		}
		cout << endl;
	}
	void DFS(const V& src)//������ȱ���
	{
		size_t isrc = GetIndex(src);
		set<size_t> s;
		s.insert(isrc);
		_DFS(isrc, s);
		cout << endl;
	}
protected:
	void _DFS(const size_t src, set<size_t> &s)
	{
		Node* cur = _linkTables[src];
		cout << GetV(src) << " ";
		while (cur)
		{
			//ͨ���ж�pair�ķ���ֵ�ж�һ�������Ƿ���ʹ�
			//��û���ʹ�����ݹ����
			pair<set<size_t>::iterator, bool> ret = s.insert(cur->_des);
			if (ret.second == true)
				_DFS(cur->_des, s);

			cur = cur->_next;
		}
	}
protected:
	vector<V> _vertexs;//����ļ��ϣ������洢�����ֵ
	vector<Node*> _linkTables;//�ߵļ���
	bool _isDirected;//�Ƿ�������ͼ
};

void TestGraphLink()
{
	string city[] = { "����", "�Ϻ�", "����", "����", "����" };
	GraphLink<string, double> gpm(city, sizeof(city) / sizeof(city[0]));
	gpm.AddEdge("����", "�Ϻ�", 300.3);
	gpm.AddEdge("����", "����", 850.5);
	gpm.AddEdge("����", "����", 299);
	gpm.AddEdge("����", "����", 475);
	gpm.AddEdge("�Ϻ�", "����", 475);

	gpm.GFS("����");
	gpm.DFS("����");
}