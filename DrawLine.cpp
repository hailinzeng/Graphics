// DrawLine.cpp: implementation of the DrawLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "DrawLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DrawLine::DrawLine()
{

}
/*=========================
//	DDALine
//
===========================*/

void DrawLine::DDALine(CDC* pDC,int x1,int y1,int x2,int y2)
{
	x1=LineX+20*x1;
	y1=LineY+20*y1;
	x2=LineX+20*x2;
	y2=LineY+20*y2;
	
	double dx,dy,e,x,y;
	dx=x2-x1;
	dy=y2-y1;
	e=(fabs(dx)>fabs(dy))?fabs(dx):fabs(dy);
	dx/=e;
	dy/=e;
	x=x1;
	y=y1;
	for(int i=1;i<=e;i++)
	{
		pDC->SetPixel((int)(x+0.5),(int)(y+0.5),RGB(220,0,0));
		x+=dx;
		y+=dy;
	}
}

/*=========================
//	MidpointLine
//
===========================*/

void DrawLine::MidpointLine(CDC* pDC,int x0,int y0,int x1,int y1)
{
	x0=LineX+20*x0;
	y0=LineY+20*y0;
	x1=LineX+20*x1;
	y1=LineY+20*y1;
	
	int a,b,delta1,delta2,d,x,y;
	a=y0-y1;
	b=x1-x0;
	d=2*a+b;
	delta1=2*a;
	delta2=2*(a+b);
	x=x0;
	y=y0;
	pDC->SetPixel(x,y,RGB(0,0,200));
	while(x<x1)
	{
		if(d<0)
		{
			x++;
			y++;
			d+=delta2;
		}
		else
		{
			x++;
			d+=delta1;
		}
		pDC->SetPixel(x,y,RGB(0,0,200));
	}/*end while*/
}/*end MidpointLine*/

 /*=========================
 //	BresenhamLine
 //
===========================*/
void DrawLine::BresenhamLine(CDC* pDC,int x1,int y1,int x2,int y2)
{
	x1=LineX+20*x1;
	y1=LineY+20*y1;
	x2=LineX+20*x2;
	y2=LineY+20*y2;
	
	int x,y,dx,dy,p;
	x=x1;
	y=y1;
	dx=x2-x1;
	dy=y2-y1;
	p=2*dy-dx;
	for(;x<=x2;x++)
	{
		pDC->SetPixel(x,y,RGB(0,200,0));
		if(p>=0)
		{
			y++;
			p+=2*(dy-dx);
		}
		else
		{
			p+=2*dy;
		}
	}
}
/*=========================
//	OnDraw
//
===========================*/
void DrawLine::OnDrawLine(CDC*pDC)
{
	//坐标
	TCHAR  szBuffer [2];
	/*===================================
	(LineX,LineY)
	+－－－－－－－－>x(LineX+200,LineY)
	|
	|
	|
	|
	|
	V
	y
	(LineX,LineY+200)
	===================================*/
	for(int i=0;i<10;i+=1)
	{
		//行
		pDC->MoveTo(LineX,LineY+i*20);
		pDC->LineTo(LineX+200,LineY+i*20);
		
		//y坐标
		pDC->TextOut(LineX-20,LineY+i*20,szBuffer,wsprintf (szBuffer, TEXT ("%d"),i));
		//pDC->TextOut(space-20,space+i*20,c[i]);
		
		//列
		pDC->MoveTo(LineX+i*20,LineY);
		pDC->LineTo(LineX+i*20,LineY+200);
		
		//x坐标
		pDC->TextOut(LineX+i*20,LineY-20,szBuffer,wsprintf (szBuffer, TEXT ("%d"),i));
	}
	
	//改装成0~9坐标
	DDALine(pDC,0,0,9,8);
	
	MidpointLine(pDC,0,0,7,4);
	
	BresenhamLine(pDC,0,0,8,6);
	
	//MidpointLine(pDC,0,0,9,8);
	//The Problem is that y is ....,while in fact adding
	
	/*===============
	//	Mark
	================*/
	
	CPen pen1,pen2,pen3;
	
	pen1.CreatePen( PS_SOLID,2,RGB(220,0,0) );
	pDC->SelectObject(&pen1);
	pDC->MoveTo(LineX+300,LineY+20);
	pDC->LineTo(LineX+400,LineY+20);
	pDC->TextOut(LineX+450,LineY+10,_T("DDALine"));
	
	pen2.CreatePen( PS_SOLID,2,RGB(0,0,200));
	pDC->SelectObject(&pen2);
	pDC->MoveTo(LineX+300,LineY+80);
	pDC->LineTo(LineX+400,LineY+80);
	pDC->TextOut(LineX+450,LineY+70,_T("MidpointLine"));
	
	pen3.CreatePen( PS_SOLID,2,RGB(0,200,0) );
	pDC->SelectObject(&pen3);
	pDC->MoveTo(LineX+300,LineY+140);
	pDC->LineTo(LineX+400,LineY+140);
	pDC->TextOut(LineX+450,LineY+130,_T("BresenhamLine"));
	
	pDC->TextOut(LineX+300,LineY+210,_T("直线扫描转换画法"));
}
DrawLine::~DrawLine()
{

}
