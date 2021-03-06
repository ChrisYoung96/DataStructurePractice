// myqueue.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

/*
 * 队列节点结构体
 */
struct qnode{
	int data;
	struct qnode *next;
};

/*
 * 链表队列
 */
 struct linkqueue
{
	 //指向队头的指针
	qnode* front;
	 //指向队尾的指针
	qnode* rear;
};

 /*
  *	初始化队列，创建一个空队列，队头指针和队尾指针同时指向队头
  */
void initqueue(linkqueue &q)
{
	q.front = new qnode();
	q.rear = q.front;
	q.front->next = NULL;
	
}

/*
 * 销毁队列
 */
void destroyqueue(linkqueue &q)
{
	while(q.front)
	{
		q.rear = q.front->next;
		free(q.front);
		q.front = q.rear;
	}
	
}


/**
 * 清空队列
 */
void cleanqueue(linkqueue &q)
{
	q.rear = q.front;
	cout << "队列已经清空" << endl;
}

/**
 * 判断队列是否为空
 */
bool isempty(linkqueue q)
{
	return q.front == q.rear;
}

/*
 * 获取队列的长度
 */
int getlength(linkqueue q)
{
	int length = 0;
	qnode *temp = q.front->next;
	while(temp)
	{
		temp = temp->next;
		length++;
	}
	return length;
}

/*
 * 如果队列不为空，则将队头元素复制给参数head,否则输出错误信息
 */
void gethead(linkqueue q,int &head)
{
	if(isempty(q))
	{
		cout << "Error:The queue is empty" << endl;
	}else
	{
		head = q.front->next->data;
	}
}

/*
 * 进入队列
 */
void enqueue(linkqueue &q,int e)
{
	if(q.front==NULL)
	{
		cout << "Error:未创建队列" << endl;
	}else
	{
		qnode *temp = new qnode();
		temp->data = e;
		temp->next = NULL;
		q.rear->next = temp;
		q.rear = temp;
	}
}

/*
 * 离开队列
 */
void dequeue(linkqueue &q)
{
	if(q.front==NULL)
	{
		cout << "Error:未创建队列" << endl;
	}else if(q.front==q.rear)
	{
		cout << "Error:队列为空" << endl;
	}else
	{
		qnode *temp = q.front->next;
		q.front->next = temp->next;
		//注意：如果队列中只有一个元素，则删除该元素直接将尾部指针指回队头即可
		if(q.rear==temp)
		{
			q.rear = q.front;
		}
		free(temp);
	}
}

/*
 * 遍历队列元素并输出
 */
void queuetravle(linkqueue q)
{
	if(q.front==q.rear)
	{
		cout << "队列为空" << endl;
	}else
	{
		qnode *temp = q.front->next;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
		free(temp);
	}

}


int main()
{
	int n=1, data;
	linkqueue q;
	while(n!=0)
	{
		cout << "请选择队列的相关操作" << endl;
		cout << "1.创建队列  2.进队列  3.显示队列元素  4.获取队头元素  5.获取队列长度  6.销毁队列  7.出队列  8.清空队列  0.退出" << endl;
		cin >> n;
		switch (n){
		case 1:
			initqueue(q);
			break;
		case 2:
			int x,t;
			cout << "请输入元素个数" << endl;
			cin >> t;
			for(int i=0;i<t;i++)
			{
			cin >> x;
			enqueue(q, x);
			}
			break;
		case 3:
			queuetravle(q);
			break;
		case 4:
			int head;
			gethead(q, head);
			cout <<"队头元素为："<< head<<endl;
			break;
		case 5:
			cout << "队列长度为："<<getlength(q) << endl;
			break;
		case 6:
			destroyqueue(q);
			break;
		case 7:
			dequeue(q);
			break;
		case 8:
			cleanqueue(q);
		default:
			cout << "输入无效，请重新输入" << endl;

		}
	}
    return 0;
}

