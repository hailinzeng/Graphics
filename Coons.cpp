// Coons.cpp: implementation of the CCoons class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Coons.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//#include "Matrix.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoons::CCoons()
{

}
//MatMultiply
//ay 行 ax列 的a x ax列 bx行 的b-->c
void CCoons:: MatMultiply(double a[][4], int ah, double b[4][4], double c[][4])
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
double CMx[4][4]={

	{ 0    , 0    ,-0.75 , 0.75 },
	{ 0.75 , 0.75 ,-0.75 ,-0.75 },
	{ 0.75 , 0.75 ,-0.75 , 0.75 },
	{ 0.75 , 0.75 , 0.75 ,-0.75 }

};
double CMy[4][4]={

	{ 0    , 0.75 , 0.75 , 0.75 },
	{ 0    , 0.75 , 0.75 , 0.75 },
	{ 0.75 , 0.75 ,-0.75 , 0.75 },
	{-0.75 ,-0.75 , 0.75 ,-0.75 }
	
};
double CMz[4][4]={

	{ 0    , 0    , 0.75 , 0.75 },
	{ 0    , 0    , 0.75 , 0.75 },
	{ 0    , 0    ,-0.75 , 0.75 },
	{ 0    , 0    , 0.75 ,-0.75 }

};
//         3  2           T  3  2     T
//由M计算(u ,u ,u,1) H M H (w ,w ,w,1)
void CCoons:: uw(double M[][4],double Matrix[][4])
{

	double Temp[4][4];

	double Hermite[4][4]={

		{ 2 ,-2 , 1 , 1},
		{-3 , 3 ,-2 ,-1},
		{ 0 , 0 , 1 , 0},
		{ 1 , 0 , 0 , 0}

	};

	double HermiteT[4][4]={
		
		{ 2 ,-3 , 0 , 1},
		{-2 , 3 , 0 , 0},
		{ 1 ,-2 , 1 , 0},
		{ 1 ,-1 , 0 , 0}
		
	};

	MatMultiply(Hermite,4,M,Temp);

	MatMultiply(Temp,4,HermiteT,Matrix);

}

double CCoons:: x(double u,double w)
{
	double temp;

	double M[4];
	
	/*double R[4][4]={
		
        {3,-3,0,0},
        {-4.5,3.75,0.75,0},
        {0,0.75,-0.75,0.75},
        {0,0.75,-0.75,0}
		
    };*/
	double Matrix[4][4];
	
	uw(CMx,Matrix);

	for (int i=0;i<4;i++)
	{
		//M[i]=u*u*u*R[i][0]+u*u*R[i][1]+u*R[i][2]+R[i][3];
		M[i]=u*u*u*Matrix[i][0]+u*u*Matrix[i][1]+u*Matrix[i][2]+Matrix[i][3];
	}

	
	temp=w*w*w*M[0]+w*w*M[1]+w*M[2]+M[3];

	return temp;
}
double CCoons:: y(double u,double w)
{
	double temp;
	
	double M[4];

	/*double R[4][4]={
		
        {0,0,0,0},
        {0,-0.75,0.75,-0.75},
        {0,0.75,-0.75,0.75},
        {0,0,-0.75,0}
		
    };*/

	double Matrix[4][4];

	uw(CMy,Matrix);

	for (int i=0;i<4;i++)
	{
		//M[i]=u*u*u*R[i][0]+u*u*R[i][1]+u*R[i][2]+R[i][3];
		M[i]=u*u*u*Matrix[i][0]+u*u*Matrix[i][1]+u*Matrix[i][2]+Matrix[i][3];
	}
	
	
	temp=w*w*w*M[0]+w*w*M[1]+w*M[2]+M[3];
	
	return temp;
}
//useless
/*double z(double u,double w){}*/

/*=========================
//	OnDrawCoons
//
===========================*/
void CCoons::OnDrawCoons(CDC* pDC)
{
	double delta=1.0/(double)50;
	
	CPen pen1;
	
	pen1.CreatePen( PS_SOLID,1,RGB(25,100,200) );
	pDC->SelectObject(&pen1);
	
	for (double u=0.000;u<1.000;u+=delta)
	{
		for (double w=0.000;w<1.000;w+=delta)
		{
			//pDC->SetPixel(x(u,w)*450+250,y(u,w)*450+100,RGB(255,0,0));
			pDC->MoveTo(int(x(u,w)*450+250),int(y(u,w)*450+100));
			if(u+delta<=1.000)
			{
				pDC->LineTo(int(x(u+delta,w)*450+250),int(y(u+delta,w)*450+100));
			}
			
			pDC->MoveTo(int(x(u,w)*450+250),int(y(u,w)*450+100));
			if (w+delta<=1.000)
			{
				pDC->LineTo(int(x(u,w+delta)*450+250),int(y(u,w+delta)*450+100));
			}
		}
	}

	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(700,50,_T("Coons曲面"));
}
//
CCoons::~CCoons()
{

}
