// Circle.cpp: implementation of the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Circle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircle::CCircle()
{

}
/*=========================
//	MidpointCircle
//
===========================*/
void CCircle::MidpointCircle(CDC *pDC,int R)
{
	int x,y;
	double d;
	x=0;y=R;d=1.25-R;
	//pDC->SetPixel(x,y,RGB(0,0,200));
	pDC->SetPixel(CircleX+x,CircleY+100+y,RGB(200,0,0));
	pDC->SetPixel(CircleX+y,CircleY+100+x,RGB(200,0,0));
	
	pDC->SetPixel(CircleX-x,CircleY+100+y,RGB(200,0,0));
	pDC->SetPixel(CircleX+y,CircleY+100-x,RGB(200,0,0));
	
	pDC->SetPixel(CircleX-x,CircleY+100-y,RGB(200,0,0));
	pDC->SetPixel(CircleX-y,CircleY+100-x,RGB(200,0,0));
	
	pDC->SetPixel(CircleX+x,CircleY+100-y,RGB(200,0,0));
	pDC->SetPixel(CircleX-y,CircleY+100+x,RGB(200,0,0));
	while(x<y)
	{
		if(d<0)
		{
			d+=2*x+3;
			x++;
		}
		else
		{
			d+=2*(x-y)+5;
			x++;
			y--;
		}
		//pDC->SetPixel(x,y,RGB(200,0,0));
		pDC->SetPixel(CircleX+x,CircleY+100+y,RGB(200,0,0));
		pDC->SetPixel(CircleX+y,CircleY+100+x,RGB(200,0,0));
		
		pDC->SetPixel(CircleX-x,CircleY+100+y,RGB(200,0,0));
		pDC->SetPixel(CircleX+y,CircleY+100-x,RGB(200,0,0));
		
		pDC->SetPixel(CircleX-x,CircleY+100-y,RGB(200,0,0));
		pDC->SetPixel(CircleX-y,CircleY+100-x,RGB(200,0,0));
		
		pDC->SetPixel(CircleX+x,CircleY+100-y,RGB(200,0,0));
		pDC->SetPixel(CircleX-y,CircleY+100+x,RGB(200,0,0));
	}
}
/*=========================
//	MidpointCircle1
//
===========================*/
void CCircle::MidpointCircle1(CDC *pDC,int R)
{
	int x,y,d;
	x=0;y=R;d=1-R;
	pDC->SetPixel(CircleX+60+x,CircleY+100+y,RGB(0,0,200));
	pDC->SetPixel(CircleX+60+y,CircleY+100+x,RGB(0,0,200));
	
	pDC->SetPixel(CircleX+60-x,CircleY+100+y,RGB(0,0,200));
	pDC->SetPixel(CircleX+60+y,CircleY+100-x,RGB(0,0,200));
	
	pDC->SetPixel(CircleX+60-x,CircleY+100-y,RGB(0,0,200));
	pDC->SetPixel(CircleX+60-y,CircleY+100-x,RGB(0,0,200));
	
	pDC->SetPixel(CircleX+60+x,CircleY+100-y,RGB(0,0,200));
	pDC->SetPixel(CircleY+100-y,CircleY+100+x,RGB(0,0,200));
	while(x<y)
	{
		if(d<0)
		{
			d+=2*x+3;
			x++;
		}
		else
		{
			d+=2*(x-y)+5;
			x++;
			y--;
		}
		pDC->SetPixel(CircleX+60+x,CircleY+100+y,RGB(0,0,200));
		pDC->SetPixel(CircleX+60+y,CircleY+100+x,RGB(0,0,200));
		
		pDC->SetPixel(CircleX+60-x,CircleY+100+y,RGB(0,0,200));
		pDC->SetPixel(CircleX+60+y,CircleY+100-x,RGB(0,0,200));
		
		pDC->SetPixel(CircleX+60-x,CircleY+100-y,RGB(0,0,200));
		pDC->SetPixel(CircleX+60-y,CircleY+100-x,RGB(0,0,200));
		
		pDC->SetPixel(CircleX+60+x,CircleY+100-y,RGB(0,0,200));
		pDC->SetPixel(CircleX+60-y,CircleY+100+x,RGB(0,0,200));
	}
}
/*=========================
//	MidpointCircle2
//
===========================*/
void CCircle::MidpointCircle2(CDC *pDC,int R)
{
	int x,y,deltax,deltay,d;
	x=0;y=R;d=1-R;
	deltax=3;
	deltay=5-R-R;
	
	pDC->SetPixel(CircleX+120+x,CircleY+100+y,RGB(0,0,0));
	pDC->SetPixel(CircleX+120+y,CircleY+100+x,RGB(0,0,0));
	
	pDC->SetPixel(CircleX+120-x,CircleY+100+y,RGB(0,0,0));
	pDC->SetPixel(CircleX+120+y,CircleY+100-x,RGB(0,0,0));
	
	pDC->SetPixel(CircleX+120-x,CircleY+100-y,RGB(0,0,0));
	pDC->SetPixel(CircleX+120-y,CircleY+100-x,RGB(0,0,0));
	
	pDC->SetPixel(CircleX+120+x,CircleY+100-y,RGB(0,0,0));
	pDC->SetPixel(CircleX+120-y,CircleY+100+x,RGB(0,0,0));
	
	while(x<y)
	{
		if(d<0)
		{
			d+=deltax;
			deltax+=2;
			x++;
		}
		else
		{
			d+=(deltax+deltay);
			deltax+=2;
			deltay+=2;
			x++;
			y--;
		}
		pDC->SetPixel(CircleX+120+x,CircleY+100+y,RGB(0,0,0));
		pDC->SetPixel(CircleX+120+y,CircleY+100+x,RGB(0,0,0));
		
		pDC->SetPixel(CircleX+120-x,CircleY+100+y,RGB(0,0,0));
		pDC->SetPixel(CircleX+120+y,CircleY+100-x,RGB(0,0,0));
		
		pDC->SetPixel(CircleX+120-x,CircleY+100-y,RGB(0,0,0));
		pDC->SetPixel(CircleX+120-y,CircleY+100-x,RGB(0,0,0));
		
		pDC->SetPixel(CircleX+120+x,CircleY+100-y,RGB(0,0,0));
		pDC->SetPixel(CircleX+120-y,CircleY+100+x,RGB(0,0,0));
	}
}
/*=========================
//	BresenhamCircle
//
===========================*/
void CCircle::BresenhamCircle(CDC*pDC,int R)
{
	int x,y,p;
	x=0;
	y=R;
	p=3-2*R;
	for(;x<=y;x++)
	{
		pDC->SetPixel(CircleX+x+180,CircleY+100+y,RGB(0,200,0));
		pDC->SetPixel(CircleX+y+180,CircleY+100+x,RGB(0,200,0));

		pDC->SetPixel(CircleX+x+180,CircleY+100-y,RGB(0,200,0));
		pDC->SetPixel(CircleX-y+180,CircleY+100+x,RGB(0,200,0));

		pDC->SetPixel(CircleX-x+180,CircleY+100-y,RGB(0,200,0));
		pDC->SetPixel(CircleX-y+180,CircleY+100-x,RGB(0,200,0));

		pDC->SetPixel(CircleX-x+180,CircleY+100+y,RGB(0,200,0));
		pDC->SetPixel(CircleX+y+180,CircleY+100-x,RGB(0,200,0));
		if(p>=0)
		{
			p+=4*(x-y)+10;//
			y--;
		}
		else
		{
			p+=4*x+6;
		}
	}//for
}
/*=========================
//	OnDraw
//
===========================*/
void CCircle::OnDrawCircle(CDC*pDC)
{
	MidpointCircle(pDC,100);
	MidpointCircle1(pDC,100);
	MidpointCircle2(pDC,100);
	BresenhamCircle(pDC,100);
	
	/*===============
	//	Mark
	//
	================*/
	CPen pen1,pen2,pen3,pen4;//CPen*OldPen;
	
	pen1.CreatePen( PS_SOLID,2,RGB(200,0,0) );
	pDC->SelectObject(&pen1);
	pDC->MoveTo(CircleX+300,CircleY+20);
	pDC->LineTo(CircleX+400,CircleY+20);
	pDC->TextOut(CircleX+450,CircleY+10,_T("MidpointCircle"));
	
	pen2.CreatePen( PS_SOLID,2,RGB(0,0,200) );
	pDC->SelectObject(&pen2);
	pDC->MoveTo(CircleX+300,CircleY+80);
	pDC->LineTo(CircleX+400,CircleY+80);
	pDC->TextOut(CircleX+450,CircleY+70,_T("MidpointCircle1"));
	
	pen4.CreatePen( PS_SOLID,2,RGB(0,0,0) );
	pDC->SelectObject(&pen4);
	pDC->MoveTo(CircleX+300,CircleY+140);
	pDC->LineTo(CircleX+400,CircleY+140);
	pDC->TextOut(CircleX+450,CircleY+130,_T("MidpointCircle2"));
	
	pen3.CreatePen( PS_SOLID,2,RGB(0,200,0) );
	pDC->SelectObject(&pen3);
	pDC->MoveTo(CircleX+300,CircleY+200);
	pDC->LineTo(CircleX+400,CircleY+200);
	pDC->TextOut(CircleX+450,CircleY+190,_T("BresenhamCircle"));
	
	pDC->TextOut(CircleX+300,CircleY+210,_T("Ô²µÄÉ¨Ãè×ª»»»­·¨"));
}
CCircle::~CCircle()
{

}
