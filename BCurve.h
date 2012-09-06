// BCurve.h: interface for the BCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCURVE_H__FC104DAD_AD76_46A9_8D80_A8CFEEDB23DB__INCLUDED_)
#define AFX_BCURVE_H__FC104DAD_AD76_46A9_8D80_A8CFEEDB23DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BCurve  
{
public:

	int count;
	CPoint p[4];
	
	void	DrawL(CDC *pDC,double u);
	void	OnDrawBcurveL(CDC* pDC);
	
	void	OnDrawBcurveM(CDC* pDC);
	
	BCurve();
	virtual ~BCurve();
	
};

#endif // !defined(AFX_BCURVE_H__FC104DAD_AD76_46A9_8D80_A8CFEEDB23DB__INCLUDED_)
