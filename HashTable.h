/*
* author:haohaosong
* date:2017/2/17
* note:��ϣ���ʵ�� 
*/

#pragma once 

#include<iostream>
using namespace std;

#include<assert.h>
#include<vector>

//����ڵ������״̬ 
enum Status
{
    EXIST,
    DELETE,
    EMPTY,
};

//�����ϣ�ڵ� 
template<typename K,typename V>
struct HashNode
{
    K _key;
    V _value;
    Status _status;

    HashNode(const K& key = K(), const V& value = V())
        :_key(key)
        , _value(value)
        , _status(EMPTY)
    {}
};

//����º���
template<typename K>
struct __HashFunc
{
    size_t operator()(const K& key)
    {
        return key;
    }
};

//�ػ�string�İ汾
template<>
struct __HashFunc<string>
{
    size_t operator()(const string& s)
    {
        size_t ret = 0;

        //���õ���������ÿ���ַ���Ȼ����ϸ��ַ���ASCII��
        string::const_iterator it = s.begin();
        while (it != s.end())
        {
            ret +=(131+*it);
            it++;
        }
        return ret;
    }
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

template<typename K, typename V, typename HashFunc = __HashFunc<K>>
class HashTable
{
    typedef HashNode<K, V> Node;
public:
    HashTable()
    {}

    HashTable(size_t size)
        :_size(0)
    {
        assert(size > 0);
        _v.resize(size);
    }

    //��Kֵת���ɹ�ϣֵ
    size_t __HashFunC(const K& key)
    {
        HashFunc hf;//����һ��HashFunc�ı���hf
        size_t hash = hf(key);//�ñ���hf����HashFunc�ķº��������ض�Ӧ������
        return hash % _v.size();//�����ϣֵ��������
    }

    pair<Node*, bool> Insert(const K& key,const V& value)
    {
        //����Ƿ���Ҫ����
        CheckCapacity();

        //��Kֵ����ȡ�࣬�жϲ����λ��
        size_t index = HashFunC(key);

        //������ڣ���ѭ���ż���Ѱ��
        while (_v[index]._status == EXIST)
        {
            index++;
            if (index == _v.size())
                index = 0;
        }

        _v[index]._key = key;
        _v[index]._value = value;
        _v[index]._status = EXIST;

        _size++;

        return make_pair<Node*,bool>(&_v[index] ,true);
    }

    Node* find(const K& key)
    {
        //��Kֵ����ȡ�࣬�жϲ����λ��
        size_t index = HashFunC(key);

        //������ڣ������Ѱ��
        while (_v[index]._status == EXIST)
        {
            //����ȣ��ж�״̬�Ƿ���ɾ��
            //��ɾ������û�ҵ������ؿ�
            //��ûɾ�����򷵻ظ�λ�õĵ�ַ
            if (_v[index]._key == key)
            {
                if (_v[index]._status == DELETE)
                    return NULL;

                return &_v[index];
            }

            index++;
            if (index == _size)
                index = 0;
        }

        return &_v[index];
    }

    void Remove(const K& key)
    {
        //ɾ������Ҫ��״̬�޸�
        Node* delNode = find(key);

        if (delNode)
            delNode->_status = DELETE;
    }
    
protected:
    vector<Node> _v;
    size_t _size;
protected:
    //����������ϣ��
    void Swap(HashTable<K, V> &h)
    {
        swap(_v, h._v);
        swap(_size, h._size);
        return;
    }

    void CheckCapacity()
    {
        //���_vΪ�գ������ݵ�7
        if (_v.empty())
        {
            _v.resize(_PrimeList[0]);
            return;
        }

        //�����������ϵ��������Ҫ����
        if (_size*10 / _v.size() >= 7)
        {
            /*size_t newSize = 2 * _v.size();*/

            //�ҵ�����һ�������� 
            size_t index = 0;
            while (_PrimeList[index] < _v.size())
            {
                index++;
            }
            size_t newSize = _PrimeList[index];

            //��һ����ʱ�������洢�����ɵĹ�ϣ��
            //������ɺ󣬽����_v����
            HashTable<K, V> tmp(newSize);
            for (size_t i = 0; i < _v.size(); ++i)
            {
                //������ڣ��򽫸�λ�õĹ�ϣֵ���뵽��ʱ�Ĺ�ϣ����
                if (_v[i]._status == EXIST)
                    tmp.Insert(_v[i]._key,_v[i]._value);
            }
            //����������ϣ��
            Swap(tmp);
        }
    }
};

void TestHashTable()
{
    HashTable<int, int> h1(10);
    h1.Insert(89, 0);
    h1.Insert(18, 0);
    h1.Insert(49, 0);
    h1.Insert(58, 0);

    h1.find(9);

    HashTable<string, string> dict;
    dict.Insert("left", "���");
    dict.Insert("sort", "����");
    dict.Insert("right", "�ұ�");
    dict.Insert("int", "����");
    dict.Insert("double", "˫����");
    dict.Insert("hello", "���");

    dict.Remove("left");
    dict.Remove("left");
    dict.Remove("left");
}
