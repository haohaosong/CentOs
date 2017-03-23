/*
* author:haohaosong
* date:2016/11/30
* note:�Թ���ʵ�֣���Ҫ�ļ� maze.txt
* �����Լ�ʵ�� һ�� maze.txt Ҳ����ֱ���ñ����ṩ��maze.txt
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<stack>
const int N = 10;

struct Pos
{
	size_t _row;//��
	size_t _col;//��
};

//��ӡ��ǰ�ĵ�ͼ
void PrintMaze(int *maze,size_t N)
{
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			//ͨ��ƫ������ǰ��Ԫ��
			cout << maze[i*N + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//�ж�һ�����Ƿ������
bool CheckIsAccess(int *maze, size_t N, Pos next)
{
	if (maze[next._row*N + next._col] == 0)
	{
		return true;
	}
	return false;
}

bool CheckIsAccess(int *maze, size_t N, Pos next, Pos cur)
{
	//Խ�磬�޷���
	if (next._row < 0 || next._row >= N || next._col < 0 || next._col >= N)
	{
		return false;
	}

	if (maze[next._row*N + next._col] == 0 )
	{
		return true;
	}
	return (maze[next._row*N + next._col] > (maze[cur._row*N + cur._col] + 1));
}

//��maze.txt�Ӷ��õ��õ�ͼ
void GetMaze(int *maze, size_t N)
{
	FILE *fp = fopen("1.txt","r");
	if (fp == NULL)
	{
		//�����ʧ�ܣ��׳��쳣
		throw invalid_argument("Read maze filed");
	}
	
	//��������ĳ�ʼ��
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N;)
		{	
			//�����0��1����ʼ��
			//������������ַ���˵����ͼ�����׳��쳣
			char ch = fgetc(fp);
			if (ch == '0' || ch == '1')
			{	
				maze[i*N + j] = ch - '0';
				++j;
			}
			else if (ch == EOF)
			{
				throw invalid_argument("Maze Error");
			}
		}
	}
}

//�õ��Թ���·��
bool GetMazePath(int *maze, size_t n, Pos entry, stack<Pos>&path)
{
	maze[entry._row*N + entry._col] = 2;
	Pos cur, next;
	cur = entry;
	path.push(entry);
	while (!path.empty())
	{
		cur = path.top();

		//�������߽磬���ҵ��˳���
		if (cur._row == N - 1)
		{
			return true;
		}

		next = cur;
		
		//������
		next._row += 1;
		if (CheckIsAccess((int*)maze, N, next) == true)
		{
			path.push(next);
			maze[next._row*N + next._col] = 2;
			continue;
		}
		next = cur;
	
		//������
		next._row -= 1;
		if (CheckIsAccess((int*)maze, N, next) == true)
		{
			path.push(next);
			maze[next._row*N + next._col] = 2;
			continue;
		}
		next = cur;

		//������
		next._col += 1;
		if (CheckIsAccess((int*)maze, N, next) == true)
		{
			path.push(next);
			maze[next._row*N + next._col] = 2;
			continue;
		}
		next = cur;

		//������
		next._col -= 1;
		if (CheckIsAccess((int*)maze, N, next) == true)
		{
			path.push(next);
			maze[next._row*N + next._col] = 2;
			continue;
		}
		next = cur;
	
		//����������޷��ߣ��򷵻���һ����
		//�����ǵ���ջ��Ԫ��
		path.pop();
	}
	return false;
}

//�ݹ�õ��Թ���·��
void GetMazePath_R(int *maze, size_t N, Pos entry, stack<Pos>&path)
{
	if (entry._row == N - 1)
	{
		return;
	}
	Pos cur, next;
	cur = entry;

	next = cur;

	next._row += 1;
	if (CheckIsAccess((int*)maze, N, next) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = 2;
		GetMazePath_R(maze, N, next, path);
	}
	next = cur;

	next._row -= 1;
	if (CheckIsAccess((int*)maze, N, next) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = 2;
		GetMazePath_R(maze, N, next, path);
	}
	next = cur;

	next._col += 1;
	if (CheckIsAccess((int*)maze, N, next) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = 2;
		GetMazePath_R(maze, N, next, path);
		next = cur;

		next._col -= 1;
		if (CheckIsAccess((int*)maze, N, next) == true)
		{
			path.push(next);
			maze[next._row*N + next._col] = 2;
			GetMazePath_R(maze, N, next, path);
		}
		next = cur;
	}
}

//�ݹ�ȥ����ѵ�·��
void GetMazePath_R(int *maze, size_t N, Pos entry, stack<Pos>&path, stack<Pos>&shortpath)
{
	if (entry._row == N - 1)
	{
		if (path.size() < shortpath.size() || shortpath.size() == 0)
		{
			shortpath = path;
		}
		path.pop();
		return;
	}
	Pos cur, next;
	cur = entry;
	next = cur;

	next._row += 1;
	if (CheckIsAccess((int*)maze, N, next, cur) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = maze[cur._row*N + cur._col] + 1;
		GetMazePath_R(maze, N, next, path, shortpath);
	}
	next = cur;

	next._row -= 1;
	if (CheckIsAccess((int*)maze, N, next, cur) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = maze[cur._row*N + cur._col] + 1;
		GetMazePath_R(maze, N, next, path, shortpath);
	}
	next = cur;

	next._col += 1;
	if (CheckIsAccess((int*)maze, N, next, cur) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = maze[cur._row*N + cur._col] + 1;
		GetMazePath_R(maze, N, next, path, shortpath);
	}
	
	next = cur;
	next._col -= 1;
	if (CheckIsAccess((int*)maze, N, next, cur) == true)
	{
		path.push(next);
		maze[next._row*N + next._col] = maze[cur._row*N + cur._col] + 1;
		GetMazePath_R(maze, N, next, path, shortpath);
	}
	path.pop();
}

//���е�ͼ������
void ReMaze(int* maze)
{
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			if (maze[i*N + j] != 1)
			{
				maze[i*N + j] = 0;
			}
		}
	}
}

/*
* note:��������и�С���⣬�����ֻ���ʱ���޷�����
*   ���� void GetMazePath_R(int *maze, size_t N, Pos entry, stack<Pos>&path, stack<Pos>&shortpath) ���Դ����������
*/

//����С·��
stack<Pos> MinPath()
{
	int maze[N][N] = { 0 };
	int curmaze[N][N] = { 0 }; 
	GetMaze((int*)maze, N);
	stack<Pos> path,MinPath,empty;
	
	while (GetMazePath((int*)maze, N, { 2, 0 }, path))
	{
		if (path.size() < MinPath.size()||MinPath.size() == 0)
		{
			MinPath = path;
		}
		
		//���õ�ͼ������һ����
		ReMaze((int*)maze);
		
		//���ϴεĳ��ڸ�Ϊ1
		maze[path.top()._row][path.top()._col] = 1;
		
		path = empty;
	}
	return MinPath;
}

void TestMaze()
{
	//�����쳣�������쳣�Ĵ���
	try
	{
		int maze[N][N] = { 0 };
		int curmaze[N][N] = { 0 };
		GetMaze((int*)maze, N);
		stack<Pos> path, shortpath;
		path.push({2,0});
		GetMazePath_R((int*)maze, N, { 2, 0 },path, shortpath);
		cout << shortpath.size() << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
}
