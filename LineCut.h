// LineCut.h: interface for the LineCut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINECUT_H__9E683A9B_16AD_4E6E_BA8A_CDED4ED812B7__INCLUDED_)
#define AFX_LINECUT_H__9E683A9B_16AD_4E6E_BA8A_CDED4ED812B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LineCut  
{
public:
	CPen pen1;
	CPen pen2;

	CPoint p1;
	CPoint p2;
	
	CPoint m_Oldpoint;
	CPoint m_Newpoint;
	bool m_pLMouseDown;
	
	int makecode(double x,double y);
	void Cohen_Sutherland(CDC* pDC,double x0,double y0,double x2,double y2);
	
	void OnDrawLineCutC(CDC* pDC);
	
	void L_Barsky(CDC*pDC,double ,double ,double ,double );
	bool cansee(double q,double d,double &t0,double &t1);
	
	void OnDrawLineCutL(CDC* pDC);
	
	LineCut();
	virtual ~LineCut();
	
};

#endif // !defined(AFX_LINECUT_H__9E683A9B_16AD_4E6E_BA8A_CDED4ED812B7__INCLUDED_)
