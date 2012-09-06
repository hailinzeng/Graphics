// Hermite.h: interface for the Hermite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HERMITE_H__BEFD62F8_240F_4185_B679_8CD52AEDA63B__INCLUDED_)
#define AFX_HERMITE_H__BEFD62F8_240F_4185_B679_8CD52AEDA63B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Hermite  
{
public:
	
	int count,countH;
	CPoint P[4];
	
	CPoint PH[4];

	double g0(double t);
	double g1(double t);
	double g2(double t);
	double g3(double t);
	
	void MatMultiply(long a[4][4], long b[4][2], long c[4][2]);
	void DrawHermite(CDC* pDC,CPoint* p);
	
	void OnDrawLargange(CDC* pDC);
	void OnDrawHermite(CDC* pDC);
	
	Hermite();
	virtual ~Hermite();
	
};

#endif // !defined(AFX_HERMITE_H__BEFD62F8_240F_4185_B679_8CD52AEDA63B__INCLUDED_)
