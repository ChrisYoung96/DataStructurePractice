#include "stdafx.h"
#include "mystack.h"


mystack::mystack()
{
	initStack();
}

void mystack::initStack()
{
	top = data;
	base = top;
}

void mystack::push(int n)
{
	//��ջ�����ж�ջ�Ƿ�������������������Խ�ջ�����򣬱���
	if(top-base==MAXSIZE)
	{
		cout << "Push failed,the stack is full" << endl;
		return;
	}
	*top = n;
	top++;
}

int mystack::getTop()
{
	//��ȡջ��Ԫ�أ������ж�ջ�Ƿ�Ϊ���ա�������Ϊ�գ��򷵻�ջ��Ԫ�أ���Ϊ�գ��򱨴�
	if(base==top)
	{
		cout << "Erro:The stack is empty!" << endl;
		return -1;
	}
	top = base + MAXSIZE - 1;
	return *top;
}

bool mystack::clearStack()
{
	top = base;
	return true;
	
}

bool mystack::isEmpty() const
{
	return base == top;
}

void mystack::pop()
{
	if(base==top)
	{
		cout << "Error:The stack is empty!" << endl;
	}else
	{
		top--;
	}
}




mystack::~mystack()
{
}
