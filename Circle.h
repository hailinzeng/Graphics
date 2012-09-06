// Circle.h: interface for the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__4FD4AC86_2DF5_4614_9351_28238B67A966__INCLUDED_)
#define AFX_CIRCLE_H__4FD4AC86_2DF5_4614_9351_28238B67A966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*========================================================*/
const int CircleX=GetSystemMetrics(SM_CXSCREEN)/2-200;
const int CircleY=GetSystemMetrics(SM_CYSCREEN)/2-200;
/*========================================================*/
class CCircle  
{
public:
	CCircle();
	
	//中点画圆法
	void MidpointCircle(CDC *pDC,int R);
	
	void MidpointCircle1(CDC *pDC,int R);
	
	void MidpointCircle2(CDC *pDC,int R);
	
	//BresenhamCircle 画圆法
	void BresenhamCircle(CDC*pDC,int R);
	
	//画圆
	void OnDrawCircle(CDC* pDC);
	
	virtual ~CCircle();

};

#endif // !defined(AFX_CIRCLE_H__4FD4AC86_2DF5_4614_9351_28238B67A966__INCLUDED_)
