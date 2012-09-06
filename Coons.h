// Coons.h: interface for the CCoons class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COONS_H__055D8F1A_7274_4912_80BB_75B6E1D7B452__INCLUDED_)
#define AFX_COONS_H__055D8F1A_7274_4912_80BB_75B6E1D7B452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCoons  
{
public:
	
	void MatMultiply(double a[][4], int ah, double b[4][4], double c[][4]);

	void uw(double M[][4],double Matrix[][4]);

	double x(double u,double w);
	double y(double u,double w);

	void OnDrawCoons(CDC* pDC);

	CCoons();
	virtual ~CCoons();

};

#endif // !defined(AFX_COONS_H__055D8F1A_7274_4912_80BB_75B6E1D7B452__INCLUDED_)
