// Bezier.h: interface for the Bezier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIER_H__213138B7_9177_4635_9DC9_B5F3CA5DA493__INCLUDED_)
#define AFX_BEZIER_H__213138B7_9177_4635_9DC9_B5F3CA5DA493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Bezier  
{
public:

	int bei;
	int first;
	int count;
	CPoint p[4];
	
	int count1;
	CPoint p1[4];
	//CPoint cpoints[4];
	//double dpoints[];

	void OnDrawBezierL(CDC* pDC);
	
	double DrawM(double u,double w,double v[4][4]);
	void OnDrawBezierM(CDC* pDC);
	
	/*===========================================*/
	CPoint temp,D[4];int Dcount;

	void bez_to_point(CDC*pDC,int degree,int npoints,CPoint coeff[],CPoint points[]);
	//double decas(int degree,double coeff[],double t);
	CPoint* decas(int degree,POINT coeff[],double t);

	void OnDrawBezierLD(CDC* pDC);
	
	/*===========================================*/
	CPoint S[4];int Scount;
	void new_split_Bezier(CDC* pDC,CPoint P[]);

	void OnDrawBezierLS(CDC* pDC);
	
	Bezier();
	virtual ~Bezier();
	
};

#endif // !defined(AFX_BEZIER_H__213138B7_9177_4635_9DC9_B5F3CA5DA493__INCLUDED_)
