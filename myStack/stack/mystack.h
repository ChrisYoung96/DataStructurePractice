#pragma once
#define MAXSIZE 100
#include <iostream>
using namespace  std;
class mystack
{
private:
	int data[MAXSIZE];
	int *base, *top;
public:
	mystack();
	void initStack();
	bool isEmpty() const;
	void push(int n);
	void pop();
	int getTop();
	bool clearStack();




	~mystack();
};

