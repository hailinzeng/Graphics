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

const int MaxStackSize=2500;			//�趨�����ģ

//template <class T>					//��StackΪģ����
class CStack
{
private:
	CPoint StackList[MaxStackSize];

	//T StackList[MaxStackSize];		//��Ŷ�ջԪ�ص�����

	int top;							//ջ����������Ԫ�ص��±�
	
public:
	CStack (void);						//���캯������ʼ��top

	void Push (const CPoint & item);

	//void Push (const T& item);		//��ջ��ѹ��һ��Ԫ��

	CPoint Pop (void);

	//T Pop (void);						//��ջ������һ��Ԫ��

	void ClearStack (void);				//���ջ
	CPoint Peek (void )const;

	//T Peek (void) const;				//��ȡջ��Ԫ��

	int StackEmpty (void) const;		//���ջ�Ƿ�Ϊ��
	int StackFull (void) const;			//���ջ�Ƿ�Ϊ��

	//~CStack(void);
};

#endif // !defined(AFX_STACK_H__5C390A72_CBCC_4BAD_858D_C64228BB6930__INCLUDED_)