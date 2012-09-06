// Hermite.cpp: implementation of the Hermite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Hermite.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Hermite::Hermite()
{

}
/*=========================
//	g0 g1 g2 g3
//
===========================*/
double Hermite::g0(double t)
{
	return double((t-P[1].x)*(t-P[2].x)*(t-P[3].x))/double((P[0].x-P[1].x)*(P[0].x-P[2].x)*(P[0].x-P[3].x));
}
double Hermite::g1(double t)
{
	return double((t-P[0].x)*(t-P[2].x)*(t-P[3].x))/double((P[1].x-P[0].x)*(P[1].x-P[2].x)*(P[1].x-P[3].x));
}
double Hermite::g2(double t)
{
	return double((t-P[0].x)*(t-P[1].x)*(t-P[3].x))/double((P[2].x-P[0].x)*(P[2].x-P[1].x)*(P[2].x-P[3].x));
}
double Hermite::g3(double t)
{
	return double((t-P[0].x)*(t-P[1].x)*(t-P[2].x))/double((P[3].x-P[0].x)*(P[3].x-P[1].x)*(P[3].x-P[2].x));
}

/*=========================
//	MATULTIPLY
//
===========================*/
void Hermite:: MatMultiply(long a[4][4], long b[4][2], long c[4][2])
{
	for(int i=0;i<4;i++)//A R 4 
	{
		for(int j=0;j<2;j++)//B L 2
		{
			for(int k=0;k<4;k++)// A L 4
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}

/*=========================
//  HERMITE
//
===========================*/
void Hermite:: DrawHermite(CDC* pDC,CPoint* p)
//void Hermite(CDC* pDC)
{
	static CPoint D;
	
	long T[4][2]=
	{
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	};
	
	long R[4][4]={
		
        { 2,-2, 1, 1},
        {-3, 3,-2,-1},
        { 0, 0, 1, 0},
        { 1, 0, 0, 0}
		
    };
	
	long S[4][2]={
		
		{p[0].x			,p[0].y			},
		{p[1].x			,p[1].y			},
		{p[2].x-p[0].x	,p[2].y-p[0].y	},
		{p[3].x-p[1].x	,p[3].y-p[1].y	}
	};
	
	//[4][4]*P[][]
	MatMultiply(R,S,T);
	/*	long T[4][2]=
	{
	{-4,-2},
	{60,20},
	{1,1},
	{1,1}
};*/
	
	static double i;
	
	for (int j=1;j<=500;j++)
	{
		i=j*(1/double(500));
		
		D.x=long(T[0][0]*i*i*i+T[1][0]*i*i+T[2][0]*i+T[3][0]);
		D.y=long(T[0][1]*i*i*i+T[1][1]*i*i+T[2][1]*i+T[3][1]);
		
		pDC->SetPixel(D,RGB(255,0,0));
	}
	//	ReleaseDC(pDC);
}

/*=========================
//  OnDrawHermite
//
===========================*/
void Hermite ::OnDrawHermite(CDC* pDC)
{
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Hermite曲线"));

	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,100,_T("左键四点，右键画线"));
}

/*=========================
//	OnDrawLargange
//
===========================*/
void Hermite ::OnDrawLargange(CDC* pDC)
{
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Lagrange曲线"));

	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,100,_T("左键四点，右键画线"));
}
Hermite::~Hermite()
{

}
