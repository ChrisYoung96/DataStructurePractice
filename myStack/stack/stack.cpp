// stack.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	mystack stack;
	for(int i=0;i<10;i++)
	{
		stack.push(i);
	}

	for(int i=0;i<10;i++)
	{
		cout << stack.getTop()<<" ";
		stack.pop();
	}

    return 0;
}

