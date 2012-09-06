// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__5C390A72_CBCC_4BAD_858D_C64228BB6930__INCLUDED_)
#define AFX_STACK_H__5C390A72_CBCC_4BAD_858D_C64228BB6930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
//#include "stdio.h"

const int MaxStackSize=2500;			//设定数组规模

//template <class T>					//类Stack为模版类
class CStack
{
private:
	CPoint StackList[MaxStackSize];

	//T StackList[MaxStackSize];		//存放堆栈元素的数组

	int top;							//栈顶所在数组元素的下标
	
public:
	CStack (void);						//构造函数，初始化top

	void Push (const CPoint & item);

	//void Push (const T& item);		//向栈顶压入一个元素

	CPoint Pop (void);

	//T Pop (void);						//从栈顶弹出一个元素

	void ClearStack (void);				//清空栈
	CPoint Peek (void )const;

	//T Peek (void) const;				//读取栈顶元素

	int StackEmpty (void) const;		//检测栈是否为空
	int StackFull (void) const;			//检测栈是否为满

	//~CStack(void);
};

#endif // !defined(AFX_STACK_H__5C390A72_CBCC_4BAD_858D_C64228BB6930__INCLUDED_)