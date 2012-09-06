// Stack.cpp: implementation of the CStack class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "stack.h"

#include <iostream>
using namespace std;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//template <class T>
//CStack<T>::CStack(void):top(-1)
CStack::CStack(void):top(-1)
{}

//template <class T>
//void CStack <T>::Push(const T& item)
void CStack ::Push(const CPoint& item)
{
	if(top==MaxStackSize-1)
	{
		cerr<<"Stack overflow !"<<endl;
		exit(1);
	}
	top++;
	StackList[top]=item;
}

//template <class T>
//T CStack<T>::Pop (void)
CPoint CStack::Pop (void)
{
	CPoint temp;
	if(top==-1)
	{
		cerr<<"Attempt to pop an empty stack !"<<endl;
		exit(1);
	}
	temp=StackList[top];
	top--;
	return temp;
}

//template <class T>
//T CStack<T>::Peek(void ) const
CPoint CStack::Peek(void ) const
{
	if(top==-1)
	{
		cerr<<"Attempt to peek an empty stack !"<<endl;
		exit(1);
	}
	return StackList[top];
}

//template <class T>
//int CStack<T>::StackEmpty(void )const
int CStack::StackEmpty(void )const
{
	return top==-1;
}

//template <class T>
//int CStack<T>::StackFull(void )const
int CStack::StackFull(void )const
{
	return top==MaxStackSize-1;
}

//template <class T>
//void CStack<T>::ClearStack(void)
void CStack::ClearStack(void)
{
	top=-1;
}

//template <class T>
//CStack<T>::~CStack(void)
/*CStack::~CStack(void)
{
delete [] StackList;
}*/