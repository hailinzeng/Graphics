// DrawLine.h: interface for the DrawLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWLINE_H__42ECE737_5E22_44EE_93D0_72B6F08DC3EB__INCLUDED_)
#define AFX_DRAWLINE_H__42ECE737_5E22_44EE_93D0_72B6F08DC3EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*======================================================*/
#include "math.h"

const int LineX=GetSystemMetrics(SM_CXSCREEN)/2-200;
const int LineY=GetSystemMetrics(SM_CYSCREEN)/2-200;
/*======================================================*/
class DrawLine  
{
public:
	DrawLine();

	//DDAֱ��ɨ��ת���㷨
	void DDALine(CDC* pDC,int x1,int y1,int x2,int y2);
	
	//�е㻭�߷�
	void MidpointLine(CDC* pDC,int x0,int y0,int x1,int y1);
	
	//Bresenham�����㷨
	void BresenhamLine(CDC* pDC,int x1,int y1,int x2,int y2);
	
	//����
	void OnDrawLine(CDC* pDC);
	
	virtual ~DrawLine();

};

#endif // !defined(AFX_DRAWLINE_H__42ECE737_5E22_44EE_93D0_72B6F08DC3EB__INCLUDED_)
