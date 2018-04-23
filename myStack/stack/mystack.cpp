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
	//进栈首先判断栈是否“满”，若不满，则可以进栈；否则，报错
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
	//获取栈顶元素，首先判断栈是否为“空”，若不为空，则返回栈顶元素；若为空，则报错；
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
