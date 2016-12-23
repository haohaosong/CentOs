/*
* author:haohaosong
* date:2016/12/7
* note:Vector����˳���ʵ�ֵģ�������ʵ�ֵ�������ʱ�����ǿ��Բ���ԭ��ָ��
*     ���Ƿ������������Ҫ���¶��壬�ڶ��巴���������ģ���������Ҫ����++��--
*	  �Լ������õȲ�����
*/
#pragma once 

#include<assert.h>
#include<iostream>
using namespace std;

//���巴�������ģ��
template<typename T,typename Ref,typename  Ptr>
struct __VectorReverseIterator
{
	typedef __VectorReverseIterator<T, T&, T*> self;//������Ϊself

	T* _node;//���������Ҳֻ��һ��ԭ��ָ�룬ֻ��++��--�Ĳ�����ͬ����

	__VectorReverseIterator(T* node)//���캯��������һ��ԭ��ָ�룬��������ɷ��������
		:_node(node)
	{}

	//�������������Ҫ�Ĳ��֣�����++��--
	self& operator++()//ǰ��++
	{
		return _node--;
	}
	self operator++(int)//����++
	{
		self tmp(_node);
		_node--;
		return tmp;
	}
	self& operator--()//ǰ��++
	{
		return _node++;
	}
	self operator--(int)//����++
	{
		self tmp(_node);
		_node++;
		return tmp;
	}

	//����==��!=����Ҳ�Ƿǳ���Ҫ�ģ���Ȼ��ʹ�� it != v.rEnd();����ʾ != û�ж���
	bool operator==(const self & s)
	{
		return _node == s._node;
	}
	bool operator!=(const self & s)
	{
		return _node != s._node;
	}

	//�����ã�����ԭ��ָ���Ԫ��
	Ref operator*()
	{
		return (*_node);
	}
	Ref operator->()
	{
		return (*_node);
	}
};

//����Vector
template<typename T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
	typedef __VectorReverseIterator<T, T&, T*> ReverseIterator;//��������ΪReverseIterator
public:
	//���캯��
	Vector()
		:_start(0)
		, _finish(0)
		, _endOfStorage(0)
	{}
	Vector(const Vector<T>& v)
		:_start(new T[v.Size()])
	{
		_finish = _start + v.Size();
		_endOfStorage = _start + v.Size();
		if (TypeTraits<T>::IsPODType().Get())
		{
			memcpy(_start, v._start, sizeof(T)*v.Size());
		}
		else
		{
			for (size_t i = 0; i < v.Size(); ++i)
			{
				_start[i] = v._start[i];
			}
		}
	}

	//�Զ����swap���������ڲ���swapֻ�����ڽ�����������
	void swap(Vector<T> v)
	{
		std::swap(v._endOfStorage, _endOfStorage);
		std::swap(v._finish, _finish);
		std::swap(v._start, _start);
	}
	Vector<T>& operator=(Vector<T> v)
	{
		//���ﲻ��ֱ�ӵ��ÿ�����swap���ж���Ľ����������ѭ���ݹ���õ���ջ����ĺ��
		swap(v);
		return *this;
	}

	//���/ɾ��һ��Ԫ��
	void PushBack(const T& x)
	{
		CheckCapacity();
		*_finish = x;
		++_finish;
	}
	void PopBack()
	{
		assert(Size());
		--_finish;
	}

	//���һ��Ԫ�ص�λ��
	Iterator Begin()
	{
		return _start;
	}
	const Iterator Begin() const
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}
	const Iterator End() const
	{
		return _finish;
	}

	//����ֻ������� rBegin�ӿں� rEnd()�ӿ�
	ReverseIterator rBegin()
	{
		return _finish - 1;
	}
	ReverseIterator rEnd()
	{
		return _start - 1;
	}

	//ɾ���̶�λ�õ�һ��Ԫ��
	void Erase(Iterator pos)
	{
		Iterator cur = pos;
		while (cur != _finish)
		{
			*cur = *(cur + 1);
			++cur;
		}
		--_finish;
	}

	//��ָ��λ�ò���һ��Ԫ�أ�����Ϊx
	void Insert(Iterator pos, const T& x)
	{
		//���������ж�
		if (Capacity() == 0)
		{
			CheckCapacity();
			*_start = x;
		}
		else
		{
			size_t tmp = pos - _start;
			CheckCapacity();
			Iterator cur = _finish - 1;
			while (cur >= (_start + tmp))
			{
				*(cur + 1) = *cur;
				cur--;
			}
			*(_start + tmp) = x;
		}
		++_finish;
	}

	//�ı�Vecctor�Ĵ�С��ȱʡ�����Ǹ�����Ĭ��ֵ
	void Resize(size_t sz, T c = T())
	{
		if (sz <= Size())
		{
			_finish -= (Size() - sz);
		}
		size_t size = Size();
		size_t capacity = Capacity();
		if (sz > capacity)
		{
			size_t newcapacity = sz;
			Iterator tmp = new T[newcapacity];

			//����������͵��жϣ�����������ȡ
			if (TypeTraits<T>::IsPODType().Get())
			{
				//����ǳ����
				memcpy(tmp, _start, sizeof(T)*size);
			}
			else
			{
				//�������
				for (size_t i = 0; i < size; ++i)
				{
					tmp[i] = _start[i];
				}
			}

			//�ͷ�ԭ���Ŀռ䣬ָ���¿��ٵ���οռ�
			delete _start;
			_start = tmp;

			//_finish��_endOfStorage ��Ҫ��start���м��㣬��Ϊ�ڴ�λ���Ѿ��ı�
			_finish = _start + sz;
			_endOfStorage = _finish;

			//�������Ĵ�С��֮ǰ�����µĿռ丳ֵΪĬ��ֵc
			Iterator cur = _finish;
			while (cur != _finish)
			{
				*cur = c;
				cur++;
			}
		}
		else
		{
			//ֱ�Ӹ�ֵΪĬ��ֵc
			Iterator cur = _finish;
			_finish = _start + sz;
			while (cur != _finish)
			{
				*cur = c;
				cur++;
			}
		}
	}

	//����
	void Reserve(size_t newcapacity)
	{
		size_t size = Size();
		if (newcapacity <= Capacity())
			return;
		Iterator tmp = new T[newcapacity];

		//���ɽ���������ȡ
		if (TypeTraits<T>::IsPODType().Get())
		{
			memcpy(tmp, _start, sizeof(T)*size);
		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				tmp[i] = _start[i];
			}
		}
		delete[] _start;
		_start = tmp;
		_finish = _start + size;
		_endOfStorage = _start + newcapacity;
	}

	//����[],����������һ��ʹ��
	T& operator[](const size_t pos)
	{
		assert(pos< Size());
		return _start[pos];
	}
	const T& operator[](const size_t pos) const
	{
		assert(pos < Size());
		return _start[pos];
	}

	//Front��Back�ӿ�
	Iterator Front()
	{
		return _start;
	}
	ConstIterator Front()const
	{
		return _start;
	}
	Iterator Back()
	{
		return _finish;
	}
	ConstIterator Back()const
	{
		return _finish;
	}

	//���Vector��Size��Capacity
	size_t Size()
	{
		return _finish - _start;
	}
	size_t Size() const
	{
		return _finish - _start;
	}
	size_t Capacity()
	{
		return _endOfStorage - _start;
	}
	size_t Capacity() const
	{
		return _endOfStorage - _start;
	}
protected:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
	void CheckCapacity()
	{
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t newcapacity = Capacity() * 2 + 3;
			Iterator tmp = new T[newcapacity];
			if (TypeTraits<T>::IsPODType().Get())
			{
				memcpy(tmp, _start, sizeof(T)*size);
			}
			else
			{
				for (size_t i = 0; i < size; ++i)
				{
					tmp[i] = _start[i];
				}
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + newcapacity;
		}
	}
};

//������ȡ
struct __TrueType
{
	bool Get()
	{
		return true;
	}
};
struct __FalseType
{
	bool Get()
	{
		return false;
	}
};
//������ȡ 
template<typename T>
struct TypeTraits
{
	typedef __FalseType IsPODType;
};
template<>
struct TypeTraits<int>
{
	typedef __TrueType IsPODType;
};
template<>
struct TypeTraits<char>
{
	typedef __TrueType IsPODType;
};

//���Է��������
void FunTest()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);

	Vector<int>::ReverseIterator it = v.rBegin();//���巴������� it ,ָ�����һ��Ԫ��
	while (it != v.rEnd())//�ж�it �ǲ���ָ���һ��Ԫ�ص�ǰһ��
	{
		cout << *it << " ";//���д�ӡ
		it++;//Ԫ����ǰŲ
	}
	cout << endl;
}
