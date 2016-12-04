#pragma once
#include <stdlib.h>
 #include<iostream>
using namespace std;

template<class ETYPE>
class Stack
{
public:
	Stack(void);
	~Stack(void);

	int push(const ETYPE& e);		//将元素压入栈
	int pop(ETYPE &e);				//将栈顶元素出栈
	int isEmpty() const				//判断栈是否为空
	{
		return top == -1;
	}

	int isFull() const			//判断栈是否满
	{
		return top == size-1;
	}

	ETYPE operator [] (int index);

	int Size() const
	{
		return top + 1;
	}

	ETYPE* getData() const;		//获得数据
	

private:
	int size;		//元素个数
	int top;		//栈顶指针
	ETYPE *stackPtr;	//指向栈顶元素的指针
};

//定义部分
template<class ETYPE>
Stack<ETYPE>::Stack(void)
{
	size = 100;
	top = -1;
	stackPtr = new ETYPE[size]; 
}

template<class ETYPE>
Stack<ETYPE>::~Stack(void)
{
	delete [] stackPtr;
}

template<class ETYPE>
int Stack<ETYPE>::push(const ETYPE &e)
{
	//如果栈已经满，则追加空间
	if (isFull())
	{
		stackPtr = (ETYPE *)realloc(stackPtr,(size+10)*sizeof(ETYPE));
		stackPtr[++top] = e;
		size += 10;			//容量也加10
		return 1;
	}
	else
	{
		stackPtr[++top] = e;
		return 1;
	}
	return 0;
}

template<class ETYPE>
int Stack<ETYPE>::pop(ETYPE &e)
{
	if (!isEmpty())
	{
		e = stackPtr[top--];
		return 1;
	}
	return 0;
}

template <class ETYPE>
ETYPE Stack<ETYPE>::operator[](int index)
{
	return stackPtr[index];
}

template <class ETYPE>
ETYPE* Stack<ETYPE>::getData() const
{
	return stackPtr;
}