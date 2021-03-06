// mycirclequeue.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

#define  MAXSIZE 10

struct circlequeue
{
	int *base;
	int front;
	int rear;
};

void initqueue(circlequeue &q)
{
	q.base = new int[MAXSIZE];
	q.front = q.rear = 0;
}

int getlength(circlequeue q)
{
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

void enqueue(circlequeue &q,int e)
{
	if((q.rear+1)%MAXSIZE==q.front)
	{
		cout << "队列已满" << endl;
	}else
	{
		q.base[q.rear] = e;
		q.rear = (q.rear + 1) % MAXSIZE;
	}

}

int dequeue(circlequeue &q)
{
	if(q.rear==q.front)
	{
		cout << "队列为空" << endl;
		return 0;
	}else
	{
		int temp = q.base[q.front];
		q.front = (q.front + 1) % MAXSIZE;
		return temp;
	}
}


void showelems(circlequeue q)
{
	int temp = q.front;
	while(temp!=(q.rear)%MAXSIZE)
	{
		cout << q.base[temp] << " ";
		temp = (temp + 1) % MAXSIZE;
	}
	cout << endl;
}




int main()
{
	int n=10;
	circlequeue q;
	cout << "请选择对循环队列的操作" << endl;
	cout << "1. 创建队列   2.元素进队列   3.元素出队列  4.获得队列元素个数   5.显示队列元素  0.退出 " << endl;
	
	while(n!=0)
	{
		cin >> n;
		switch (n)
		{
		case 1:
			initqueue(q);
			break;
		case 2:
			int a,b;
			cout << "请输入插入元素个数：" << endl;
			cin >> b;
			if(b>MAXSIZE)
			{
				cout << "Error:元素个数超出队列容量" << endl;
			}else
			{
				for(int i=0;i<b;i++)
				{
					cin >> a;
					enqueue(q, a);
				}
			}
			break;
		case 3:
			cout << "弹出元素为：" << dequeue(q) << endl;
			break;
		case 4:
			cout << "队列元素个数为：" << getlength(q) << endl;
			break;
		case 5:
			showelems(q);
			break;
		default: 
			;
		}
	}
	
    return 0;
}

