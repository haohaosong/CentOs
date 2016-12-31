/*
* author:haohaosong
* date:2016/12/31
* note:��һ������ǰK������������ö�ʵ�� 
*/

#pragma once 
 
void TopK(int* a, size_t k, size_t n)
{
	//��ʼ��һ������
	int* heap = new int[k];

	//��ǰk��Ԫ�ط�������
	for (size_t i = 0; i < k; i++)
	{
		heap[i] = a[i];
	}

	//���µ�����ʹ֮��Ϊ��
	for (int i = (k - 2) / 2; i >= 0; --i)
	{
		AdjustDown(heap,k,i);
	}

	//����������ѵĶ���
	for (size_t i = k; i < n; ++i)
	{
		//����ȶѶ�С�����룬�������µ���
		if (a[i]>heap[0])
		{
			heap[0] = a[i];
			AdjustDown(heap, k, 0);
		}
	}

	for (size_t i = 0; i < k; i++)
	{
		cout << heap[i] << " ";
	}
	cout << endl;
}

void TestTopK()
{
	const int N = 10000;
	const int K = 5;
	int a[N];

	for (size_t i = 0; i < N; ++i)
	{
		a[i] = rand() % N;
	}

	a[1] = N + 1;
	a[100] = N + 2;
	a[200] = N + 3;
	a[666] = N + 4;
	a[111] = N + 19;

	TopK(a, K, N);
}
