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

	int push(const ETYPE& e);		//��Ԫ��ѹ��ջ
	int pop(ETYPE &e);				//��ջ��Ԫ�س�ջ
	int isEmpty() const				//�ж�ջ�Ƿ�Ϊ��
	{
		return top == -1;
	}

	int isFull() const			//�ж�ջ�Ƿ���
	{
		return top == size-1;
	}

	ETYPE operator [] (int index);

	int Size() const
	{
		return top + 1;
	}

	ETYPE* getData() const;		//�������
	

private:
	int size;		//Ԫ�ظ���
	int top;		//ջ��ָ��
	ETYPE *stackPtr;	//ָ��ջ��Ԫ�ص�ָ��
};

//���岿��
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
	//���ջ�Ѿ�������׷�ӿռ�
	if (isFull())
	{
		stackPtr = (ETYPE *)realloc(stackPtr,(size+10)*sizeof(ETYPE));
		stackPtr[++top] = e;
		size += 10;			//����Ҳ��10
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