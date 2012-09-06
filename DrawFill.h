// DrawFill.h: interface for the DrawFill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWFILL_H__F649D1DC_38AF_450A_BAD0_3F2BE990E430__INCLUDED_)
#define AFX_DRAWFILL_H__F649D1DC_38AF_450A_BAD0_3F2BE990E430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*===================================================*/
#include "Stack.h"

const int FillX=GetSystemMetrics(SM_CXSCREEN)/2-200;
const int FillY=GetSystemMetrics(SM_CYSCREEN)/2-200;
/*===================================================*/

class DrawFill  
{
public:
	DrawFill();

	void Floodfill(CDC* pDC,int x,int y,COLORREF oldvalue,COLORREF newvalue);
	
	void Boundaryfill(CDC* pDC,int x,int y,COLORREF boundaryvalue, COLORREF newvalue);
	
	void ScanlineSeedfill(CDC* pDC,int x,int y,COLORREF boundaryvalue,COLORREF newvalue);
	
	//Моід
	void OnDrawFill(CDC* pDC);
	
	virtual ~DrawFill();

};

#endif // !defined(AFX_DRAWFILL_H__F649D1DC_38AF_450A_BAD0_3F2BE990E430__INCLUDED_)
