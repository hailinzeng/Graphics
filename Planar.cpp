// Planar.cpp: implementation of the Planar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Planar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <cmath> 

const int PlanarX=GetSystemMetrics(SM_CXSCREEN)/2;
const int PlanarY=GetSystemMetrics(SM_CYSCREEN)/2;

RECT rect1,rect2,rect3;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Planar::Planar()
{
	first=true;
}
/*=========================
//  默认构造函数
//
===========================*/
C2DPoint::C2DPoint()
{
    PMatrix[0]=0;
    PMatrix[1]=0;
}
/*=========================
//  构造函数
//
===========================*/
C2DPoint::C2DPoint(int x, int y)
{
    PMatrix[0]=double(x);
    PMatrix[1]=double(y);
}
/*=========================
//	设置坐标
//
===========================*/
void C2DPoint::SetPoint(int x, int y)
{
    PMatrix[0]=x;
    PMatrix[1]=y;
}
/*=========================
//	D2R
//
===========================*/
double C2DPoint::D2R(double deg)
{ 
	return deg / 180.0 * 3.14159265; 
} 
/*=========================
//	ReSize
//
===========================*/
void C2DPoint::ReSize(double Sx,double Sy)
{

	PMatrix[0]=PMatrix[0]*Sx;
	PMatrix[1]=PMatrix[1]*Sy;
	
}
/*=========================
//	ReMove
//
===========================*/
void C2DPoint::ReMove(long Tx,long Ty)
{
	PMatrix[0]+=Tx;
	PMatrix[1]+=Ty;

}
/*=========================
//	Cycle
//
===========================*/
void C2DPoint::Cycle(double a)
{
	a=D2R(a);

	double x=PMatrix[0];

	PMatrix[0]=PMatrix[0]*cos(a)-PMatrix[1]*sin(a);
	PMatrix[1]=x*sin(a)+PMatrix[1]*cos(a);
	
}
/*=========================
//	symmetry_y
//
===========================*/
void C2DPoint::symmetry_y()
{
	PMatrix[0]=-PMatrix[0];
}
/*=========================
//	cuoqie
//
===========================*/
void C2DPoint::cuoqie(int n,float b,float d)
{
	
	PMatrix[0]=PMatrix[0]+b*PMatrix[1];
	PMatrix[1]=d*PMatrix[0]+PMatrix[1];

}
/*=========================
//	DisRect
//
===========================*/
void Planar::DisPlay(CDC* pDC,C2DPoint* PS)
{
	for(int i=0;i<4;i++)
	{
		pDC->MoveTo(long(PS[i].PMatrix[0]+PlanarX),long(PS[i].PMatrix[1]+PlanarY));
		pDC->LineTo(long(PS[(i+1)%4].PMatrix[0]+PlanarX),long(PS[(i+1)%4].PMatrix[1]+PlanarY));
	}
}
/*=========================
//	OndrawPlanar
//
===========================*/
void Planar::OnDrawPlanar(CDC* pDC)
{
	//初始化
	if (first){
		PP[0].SetPoint(-100,100);
		PP[1].SetPoint(100,100);
		PP[2].SetPoint(100,-100);
		PP[3].SetPoint(-100,-100);
	}first=false;
	//END 初始化

	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(PlanarX-120,20,_T("二维图形的比例、平移、旋转、对称、错切"));
		
	pDC->SetTextColor(RGB(14,99,87));
	pDC->TextOut(2*PlanarX-160,500,_T("上"));
	pDC->TextOut(2*PlanarX-130,530,_T("左"));
	pDC->TextOut(2*PlanarX-190,530,_T("右"));
	pDC->TextOut(2*PlanarX-160,560,_T("下"));

	pDC->SetTextColor(RGB(180,100,180));
	pDC->TextOut(50,120,_T("Y:  Y轴对称"));
	
	pDC->SetTextColor(RGB(65,180,253));
	pDC->TextOut(50,200,_T("L:  放大   2倍"));
	pDC->TextOut(50,250,_T("S:  缩小   2倍"));
	
	pDC->SetTextColor(RGB(1,191,7));
	pDC->TextOut(50,350,_T("O:逆时针旋转"));
	pDC->TextOut(50,400,_T("P:顺时针旋转"));

	pDC->SetTextColor(RGB(185,103,233));
	pDC->TextOut(50,500,_T("J K:错切变换"));

	pDC->SetTextColor(RGB(0,85,234));
	pDC->TextOut(50,570,_T("I:  恢复到初始状态"));
	
	DisPlay(pDC,PP);
}
Planar::~Planar()
{

}
