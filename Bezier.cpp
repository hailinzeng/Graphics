// Bezier.cpp: implementation of the Bezier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Bezier.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "math.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Bezier::Bezier()
{
	first=true;
	bei=450;
}

/*=========================
//	关于角点的信息的矩阵M
//
===========================*/
double Mx[4][4]={
	
	{ 0    , 0    ,-0.75 , 0.75 },
	{ 0.75 , 0.75 ,-0.75 ,-0.75 },
	{ 0.75 , 0.75 ,-0.75 , 0.75 },
	{ 0.75 , 0.75 , 0.75 ,-0.75 }
	
};
double My[4][4]={
	
	{ 0    , 0.75 , 0.75 , 0.75 },
	{ 0    , 0.75 , 0.75 , 0.75 },
	{ 0.75 , 0.75 ,-0.75 , 0.75 },
	{-0.75 ,-0.75 , 0.75 ,-0.75 }
	
};
double Mz[4][4]={
	
	{ 0    , 0    , 0.75 , 0.75 },
	{ 0    , 0    , 0.75 , 0.75 },
	{ 0    , 0    ,-0.75 , 0.75 },
	{ 0    , 0    , 0.75 ,-0.75 }
	
};

/*=========================
//	M->V
//
===========================*/
void change(double M[4][4])
{
	
	double temp[4][4]={
		M[0][0]							,M[0][0]+(1/double(3))*M[0][2]									,M[0][1]-(1/double(3))*M[0][3]									,M[0][1],
		M[0][0]+(1/double(3))*M[2][0]	,M[0][0]+(1/double(3))*(M[2][0]+M[0][2])+(1/double(9))*M[2][2]	,M[0][1]+(1/double(3))*(M[2][1]-M[0][3])-(1/double(9))*M[2][3]	,M[0][1]+(1/double(3))*M[2][1],
		M[1][0]-(1/double(3))*M[3][0]	,M[1][0]-(1/double(3))*(M[3][0]-M[1][2])-(1/double(9))*M[3][2]	,M[1][1]-(1/double(3))*(M[3][1]+M[1][3])+(1/double(9))*M[3][3]	,M[1][1]-(1/double(3))*M[3][1],
		M[1][0]							,M[1][0]+(1/double(3))*M[1][2]									,M[1][1]-(1/double(3))*M[1][3]									,M[1][1]
	};
	
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			M[i][j]=temp[i][j];
		}
	}
}

/*=========================
//
//[u3,u2,u,1]BVBt[w3,w2,w,1]t
===========================*/
double Bezier::DrawM(double u,double w,double v[4][4])//面
{
	double B[4][4]={
		
		{-1, 3,-3,1},
		{ 3,-6, 3,0},
		{-3, 3, 0,0},
		{ 1, 0, 0,0}
	};
	
	double temp[4][4];
	double temp1[4][4];
	
	//(u3,u2,u,1)*[B]
	for (int i=0;i<4;i++)//temp 列
	{
		temp[0][i]=u*u*u*B[0][i]+u*u*B[1][i]+u*B[2][i]+1*B[3][i];
	}
	
	//(u3,u2,u,1)*[B]*[v]
	for (i=0;i<4;i++) 
	{
		temp1[0][i]=temp[0][0]*v[0][i]+temp[0][1]*v[1][i]+temp[0][2]*v[2][i]+temp[0][3]*v[3][i];
	}
	
	//(u3,u2,u,1)*[B]*[v]*[B]
	for (i=0;i<4;i++)//temp 列
	{
		
		temp[0][i]=temp1[0][0]*B[0][i]+temp1[0][1]*B[1][i]+temp1[0][2]*B[2][i]+temp1[0][3]*B[3][i];
		
	}
	
	return w*w*w*temp[0][0]+w*w*temp[0][1]+w*temp[0][2]+temp[0][3];
}
/*=========================
//	OnDrawBezierM
//
===========================*/
void Bezier::OnDrawBezierM(CDC* pDC)
{
	if (first){change(Mx);change(My);change(Mz);}first=false;
	
	CPen pen1;
	pen1.CreatePen( PS_SOLID,1,RGB(20,20,200) );
	
	pDC->SelectObject(&pen1);
	
	double delta=1/double(50);
	
	for (double u=0.000;u<1.000;u+=delta)
	{
		for (double w=0.000;w<1.000;w+=delta)
		{
			pDC->MoveTo(int(DrawM(u,w,Mx)*bei+250),int(DrawM(u,w,My)*bei+100));
			if (u+delta<=1.000)
			{
				pDC->LineTo(int(DrawM(u+delta,w,Mx)*bei+250),int(DrawM(u+delta,w,My)*bei+100));
			}
			
			pDC->MoveTo(int(DrawM(u,w,Mx)*bei+250),int(DrawM(u,w,My)*bei+100));
			if (w+delta<=1.000)
			{
				pDC->LineTo(int(DrawM(u,w+delta,Mx)*bei+250),int(DrawM(u,w+delta,My)*bei+100));
			}
		}
	}

	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Bezier曲面"));

}
/*=========================
//	OnDrawBezierL
//
===========================*/

void Bezier::OnDrawBezierL(CDC* pDC)
{
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Bezier曲线"));

	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,100,_T("左键四点，右键画线"));
}
/*=======================================*/
void Bezier::bez_to_point(CDC*pDC,int degree,int npoints,CPoint coeff[],CPoint points[])//p82几何作图法
{
	POINT* P;
	double t,delt;
	delt=1.0/(double)npoints;
	
	t=0.0;
	for (int i=0;i<=npoints;i++)
	{
		//points[i]=decas(degree,coeff,t);
		P=decas(degree,coeff,t);

		points[i].x=P->x;
		points[i].y=P->y;
		t+=delt;
	}
}
CPoint* Bezier::decas(int degree,POINT coeff[],double t) 
//double Bezier::decas(int degree,double coeff[],double t)
{
	int r,i;
	//double *coeffa,coeffa0;
	CPoint codffa0;
	//coeffa=new double[degree+1];
	CPoint * coeffa=new CPoint[degree+1];
	for(i=0;i<=degree;i++)
	{
		coeffa[i].x=coeff[i].x;
		coeffa[i].y=coeff[i].y;
	}
	for(r=1;r<=degree;r++)
	{
		for(i=0;i<=degree-r;i++)
		{
			coeffa[i].x=long(coeffa[i].x+t*(coeffa[i+1].x-coeffa[i].x));
            coeffa[i].y=long(coeffa[i].y+t*(coeffa[i+1].y-coeffa[i].y));
		}
	}
	temp.x=coeffa[0].x;
	temp.y=coeffa[0].y;

	delete coeffa;

	return &temp;
}
/*=========================
//	OnDrawBezierLD
//
===========================*/

void Bezier::OnDrawBezierLD(CDC* pDC)
{
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Bezier曲线几何作图法"));

	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,100,_T("左键四点，右键画线"));

}
/*===========================================*/
double maxdistance(CPoint P[4])
{
	double k;
	if((P[3].x-P[0].x)!=0)
		k=(P[3].y-P[0].y)/(P[3].x-P[0].x);
	double d1,d2;
	d1=(P[1].y-P[0].y-k*(P[1].x-P[0].x))/sqrt(1+k*k);
	if(d1<0) d1=-d1;
    d2=(P[2].y-P[0].y-k*(P[2].x-P[0].x))/sqrt(1+k*k); 
    if(d2<0) d2=-d2;
	if(d1>d2)
		return d1;
	else 
		return d2;
	
}
void Bezier::new_split_Bezier(CDC*pDC,CPoint P[])
{
	CPoint R[4],Q[4];
	int i,j;
	const double epsilon=1.5;
	if (maxdistance(P)<epsilon)
	{
		pDC->MoveTo(P[0].x,P[0].y);
		pDC->LineTo(P[3].x,P[3].y);
	}
	else
	{
		for (i=0;i<=3;i++)
		{
			R[i]=P[i];
		}
		for (i=0;i<=2;i++)
		{
			Q[i]=R[0];
			for (j=0;j<=2-i;j++)
			{
				R[j].x=(R[j].x+R[j+1].x)/2;
				R[j].y=(R[j].y+R[j+1].y)/2;
			}
		}
		Q[3]=R[0];
		new_split_Bezier(pDC,Q);
		new_split_Bezier(pDC,R);
	}
}
/*=========================
//	OnDrawBezierLS
//
===========================*/

void Bezier::OnDrawBezierLS(CDC* pDC)
{
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Bezier曲线分裂法"));

	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,100,_T("左键四点，右键画线"));

}
Bezier::~Bezier()
{

}
