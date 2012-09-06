// BCurve.cpp: implementation of the BCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "BCurve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//largger
const int bei=20;

//display offset
const int spacex=450;
const int spacey=250;

//largger
const int Bbei=450;

//display offset
const int Bbasicx=250;
const int Bbasicy=100;

//initial only once
static BOOL Bfirst=true;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BCurve::BCurve()
{
}

void BCurve::DrawL(CDC *pDC,double u)//b样条曲线
{
	static CPoint r;
	
	/*double Mu[1][4]={u*u*u,u*u,u,1};
	
	  double Matrix[4][4]={
	  
		{-1 , 3 ,-3 , 1},
		{ 3 ,-6 , 3 , 0},
		{-3 , 0 , 3 , 0},
		{ 1 , 4 , 1 , 0}
		
};*/
	
	//(u3 ,u2 ,u ,1)*M[][]
	double Result[1][4]={
		
		(  -u*u*u+3*u*u-3*u+1),
			( 3*u*u*u-6*u*u+4),
			(-3*u*u*u+3*u*u+3*u+1),
			(   u*u*u)
	};
	
	//MatMultiply(Mu,1,Matrix,Result);
	
	//(Result[0][0]*p[0].x+Result[0][1]*p[1].x+Result[0][2]*p[2].x+Result[0][3]*p[3].x)/6;
	
	r.x=long(Result[0][0]*p[0].x+Result[0][1]*p[1].x+Result[0][2]*p[2].x+Result[0][3]*p[3].x)/long(6);
	
	r.y=long(Result[0][0]*p[0].y+Result[0][1]*p[1].y+Result[0][2]*p[2].y+Result[0][3]*p[3].y)/long(6);
	
	pDC->SetPixel(r,RGB(0,0,255));
}
/*=========================
//	OnDrawBcurveL
//
===========================*/
void BCurve:: OnDrawBcurveL(CDC* pDC)
{

	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("B样条曲线"));
	
	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,100,_T("左键四点，右键画线"));
}
//MatMultiply
//ay 行 ax列 的a x ax列 bx行 的b-->c
void BMatMultiply(double a[][4], int ah, double b[4][4], double c[][4])
{
	for(int j=0;j<4;j++)
	{
		for(int k=0;k<4;k++)
		{
			c[j][k]=0;
		}
	}
	
	for(int i=0;i<ah;i++)//a hang
	{
		for(int j=0;j<4;j++)//b lie
		{
			for(int k=0;k<4;k++)//a lie
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}
//关于角点的信息的矩阵M
double BMx[4][4]={
	
	{ 0    , 0    ,-0.75 , 0.75 },
	{ 0.75 , 0.75 ,-0.75 ,-0.75 },
	{ 0.75 , 0.75 ,-0.75 , 0.75 },
	{ 0.75 , 0.75 , 0.75 ,-0.75 }
	
};
double BMy[4][4]={
	
	{ 0    , 0.75 , 0.75 , 0.75 },
	{ 0    , 0.75 , 0.75 , 0.75 },
	{ 0.75 , 0.75 ,-0.75 , 0.75 },
	{-0.75 ,-0.75 , 0.75 ,-0.75 }
	
};
double BMz[4][4]={
	
	{ 0    , 0    , 0.75 , 0.75 },
	{ 0    , 0    , 0.75 , 0.75 },
	{ 0    , 0    ,-0.75 , 0.75 },
	{ 0    , 0    , 0.75 ,-0.75 }
	
};
//		   -1		-1	T
//V  =36*(B  H) M (B  H)
// kl
void Bchange(double M[4][4])
{

	/*double B[4][4]={
		
		{-1	, 3	,-3	,1},
		{ 3	,-6	, 3	,0},
		{-3	, 0	, 3	,0},
		{ 1	, 4	, 1	,0}
	};*/

	double B1[4][4]={
		
		{ 0	, 1/double(9)	,-1/double(6)	,1/double(6)},
		{ 0	,-1/double(18)	, 0				,1/double(6)},
		{ 0	, 1/double(9)	, 1/double(6)	,1/double(6)},
		{ 1	, 11/double(18)	, 1/double(3)	,1/double(6)}
	};

	double B1T[4][4]={
		
		{ 0				, 0				,	0			,1},
		{ 1/double(9)	,-1/double(18)	,	1/double(9)	,11/double(18)},
		{-1/double(6)	, 0				,	1/double(6)	,1/double(3)},
		{ 1/double(6)	, 1/double(6)	,	1/double(6)	,1/double(6)}
	};

	double H[4][4]={
	
		{ 2 ,-2 , 1 , 1},
		{-3 , 3 ,-2 ,-1},
		{ 0 , 0 , 1 , 0},
		{ 1 , 0 , 0 , 0}
	};
	
	double HT[4][4]={
		
		{ 2 ,-3 , 0 , 1},
		{-2 , 3 , 0 , 0},
		{ 1 ,-2 , 1 , 0},
		{ 1 ,-1 , 0 , 0}
		
	};

	double Temp[4][4];
	double Temp1[4][4];

	//B1[][]*H[][]
	BMatMultiply(B1,4,H,Temp);

	//B1[][]*H[][]*M[][]
	BMatMultiply(Temp,4,M,Temp1);

	//B1[][]*H[][]*M[][]*HT[][]
	BMatMultiply(Temp1,4,HT,Temp);

	//B1[][]*H[][]*M[][]*HT[][]*B1T[][]
	BMatMultiply(Temp,4,B1T,Temp1);

	//B1[][]*H[][]*M[][]*HT[][]*B1T[][]*36
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			M[i][j]=Temp1[i][j]*36;
		}
	}
}
//B=B/6
//	 3   2			  T				  T
//[u ,u, u, 1]B Vkl B [ w3, w2, w, 1]
double B_curve(double u,double w,double Vx[4][4])
{
	double B[4][4]={//B/6
	
		{-1/double(6),  1/double(2),-1/double(2),1/double(6)},
		{ 1/double(2), -1  , 1/double(2),0  },
		{-1/double(2),  0  , 1/double(2),0  },
		{ 1/double(6),  2/double(3), 1/double(6),0  }
	};

	double temp[4][4];
	double temp1[4][4];

	//(u3,u2,u,1)*[B]
	for (int i=0;i<4;i++)//temp 列
	{
		temp[0][i]=u*u*u*B[0][i]+u*u*B[1][i]+u*B[2][i]+1*B[3][i];
	}

	//(u3,u2,u,1)*[B]*[Vx]
	for (i=0;i<4;i++) 
	{
		temp1[0][i]=temp[0][0]*Vx[0][i]+temp[0][1]*Vx[1][i]+temp[0][2]*Vx[2][i]+temp[0][3]*Vx[3][i];
	}

	double BT[4][4]={
	
		{-1/double(6),  1/double(2)	,-1/double(2)	,1/double(6)},
		{ 1/double(2), -1			, 0				,2/double(3)},
		{-1/double(2),  1/double(2)	, 1/double(2)	,1/double(6)},
		{ 1/double(6),  0			, 0				,0			}
	};

	//(u3,u2,u,1)*[B]*[Vx]*[BT]
	for (i=0;i<4;i++)//temp 列
	{

		temp[0][i]=temp1[0][0]*BT[0][i]+temp1[0][1]*BT[1][i]+temp1[0][2]*BT[2][i]+temp[0][3]*BT[3][i];

	}

	return w*w*w*temp[0][0]+w*w*temp[0][1]+w*temp[0][2]+temp[0][3];
}
/*=========================
//	OnDrawBcurveM
//
===========================*/
void BCurve::OnDrawBcurveM(CDC* pDC)
{
	if (Bfirst){Bchange(BMx);Bchange(BMy);Bchange(BMz);}Bfirst=false;
	
	CPen pen1;
	pen1.CreatePen( PS_SOLID,1,RGB(20,20,200) );
	
	pDC->SelectObject(&pen1);
	
	const double delta=1.0/double(50);
	
	for (double u=0.000;u<=1.000;u+=delta)
	{
		for (double w=0.000;w<=1.000;w+=delta)
		{
			pDC->MoveTo(int(B_curve(u,w,BMx)*Bbei+Bbasicx),int(B_curve(u,w,BMy)*Bbei+Bbasicy));
			
			if (u+delta<=1.000)
			{
				pDC->LineTo(int(B_curve(u+delta,w,BMx)*Bbei+Bbasicx),int(B_curve(u+delta,w,BMy)*Bbei+Bbasicy));
			}
			
			
			pDC->MoveTo(int(B_curve(u,w,BMx)*Bbei+Bbasicx),int(B_curve(u,w,BMy)*Bbei+Bbasicy));
			
			if (w+delta<=1.000)
			{
				pDC->LineTo(int(B_curve(u,w+delta,BMx)*Bbei+Bbasicx),int(B_curve(u,w+delta,BMy)*Bbei+Bbasicy));
			}
		}
	}

	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("B样条曲面"));
}
BCurve::~BCurve()
{

}
