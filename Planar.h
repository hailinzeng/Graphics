// Planar.h: interface for the Planar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANAR_H__43CDE50E_245C_43B7_913A_217F2FEBE437__INCLUDED_)
#define AFX_PLANAR_H__43CDE50E_245C_43B7_913A_217F2FEBE437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C2DPoint
{
public:

	//构造函数
    //参数：坐标
    C2DPoint(int x, int y);
    C2DPoint();

	//CPoint	pp[4];
	RECT	rect;//作为初始化;
	
	double  PMatrix[2];
	
	double	D2R(double deg);
	
	void	SetPoint(int x, int y);
	
	void 	ReSize(double Sx,double Sy);
	
	void	ReMove(long Tx,long Ty);
	
	void	Cycle(double a);
	
	void	symmetry_y();
	
	void	cuoqie(int n,float b,float d);
};


class Planar  
{
public:
	Planar();

	bool	first;
	
	C2DPoint  PP[4];

	void	DisPlay(CDC* pDC,C2DPoint *PS);

	void	OnDrawPlanar(CDC* pDC);
	
	virtual ~Planar();

};

#endif // !defined(AFX_PLANAR_H__43CDE50E_245C_43B7_913A_217F2FEBE437__INCLUDED_)
