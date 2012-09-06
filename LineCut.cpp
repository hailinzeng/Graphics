// LineCut.cpp: implementation of the LineCut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "LineCut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*===============*/
const int xl=300;
const int xr=450;
const int yt=150;
const int yb=300;

const int Lyt=300;//L
const int Lyb=150;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LineCut::LineCut()
{
	pen1.CreatePen( PS_SOLID,2,RGB(200,0,0) );
	pen2.CreatePen( PS_SOLID,1,RGB(0,20,200) );
}
/*=========================
//	makecode
//
===========================*/
int LineCut::makecode(double x,double y)
{
	int code=0;
	
	if(x>xr){code=2;}else{if(x<xl)code=1;}
	
	if(y<yt){code+=8;}else{if(y>yb)code+=4;}
	
	return code;
}

/*=========================
//	Cohen_Sutherland
//
===========================*/
void LineCut::Cohen_Sutherland(CDC* pDC,double x0,double y0,double x2,double y2)
{
	static int c,c1,c2;//,cc;
	
	double x,y;
	
	//flag=1;
	
	c1=makecode(x0,y0);
	c2=makecode(x2,y2);
	
	while((c1!=0)||(c2!=0))
	{
		//	cc=c1&c2;
		
		if(c1&c2==1)  return;//Í¬Ê±ÔÚÄ³Ò»²à
		
		c=c1;
		if(c==0)
			c=c2;
		if(c&1==1)
		{
			y=y0+(y2-y0)*(xl-x0)/(x2-x0);x=xl;
		}
		else
		{
			if(c&2)
			{
				y=y0+(y2-y0)*(xr-x0)/(x2-x0);x=xr;
			}
			else
			{
				if(c&4)
				{
					x=x0+(x2-x0)*(yb-y0)/(y2-y0);y=yb;
				}
				else 
				{
					if(c&8)
					{
						x=x0+(x2-x0)*(yt-y0)/(y2-y0);y=yt;
					}
				}
			}
		}
		
		if(c==c1)
		{
			x0=x;y0=y;c1=makecode(x,y);
		}
		else
		{
			x2=x;y2=y;c2=makecode(x,y);
		}
		
	}
	pDC->MoveTo(int(x0),int(y0));
	pDC->LineTo(int(x2),int(y2));
}

/*=========================
//	OnDrawLineCutC
//
===========================*/
void LineCut::OnDrawLineCutC(CDC* pDC)
{
	pDC->Rectangle (xl,yt,xr,yb);
	
	for(int i=xl-150;i<xr+150;i++)
	{
		if((i-xl+150)%20<5)
		{
			pDC->SetPixel(i,yt,RGB(200,200,200));
			pDC->SetPixel(i,yb,RGB(200,200,200));
		}
	}
	for(i=yt-150;i<yb+150;i++)
	{
		if((i-yt+150)%20<5)
		{
			pDC->SetPixel(xl,i,RGB(200,200,200));
			pDC->SetPixel(xr,i,RGB(200,200,200));
		}
	}
	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,200,_T("×ó¼ü»­Ïß"));
	pDC->TextOut(700,230,_T("ÓÒ¼ü²Ã¼ô"));

	pDC->SetTextColor(RGB(0,85,234));
	pDC->TextOut(650,500,_T("Cohen_Sutherland"));
}
/*========================================================*/

/*=========================
//	cansee
//
===========================*/
bool LineCut::cansee(double q,double d,double &t0,double &t1)
{
	double r;
	if(q<0)
	{
		r=d/q;
		if(r>t1)
		{
			//cansee=false;
			return 0;
		}
		else  if(r>t0) t0=r;
	}
	else  if(q>0)
	{
		r=d/q;
		if(r<t0)  
		{
			//cansee=false;
			return 0;
		}
		else if(r<t1)  t1=r;
	}
	else  if(d<0)  
	{
		//cansee=false;
		return 0;
	}
	//	cansee=true;
	//	else
	return 1;
}
/*=========================
//	L_Barsky
//
===========================*/
void LineCut::L_Barsky(CDC*pDC,double x0,double y0,double x2,double y2)
{
	double t0=0.0;
	double t1=1.0;

	double deltax=x2-x0;

	if(!cansee(-deltax,x0-xl,t0,t1))return;
	if(!cansee(deltax,xr-x0,t0,t1))return;

	double deltay=y2-y0;
	if(!cansee(-deltay,y0-Lyb,t0,t1))return;
	if(!cansee(deltay,Lyt-y0,t0,t1))return;

	//x2=x0+t1*deltax;
	//y2=y0+t1*deltay;
	//x0=x0+t0*deltax;
	//y0=y0+t0*deltay;

	pDC->SelectObject(&pen1);

	//pDC->MoveTo(int(x0),int(y0));
	//pDC->LineTo(int(x2),int(y2));

	pDC->MoveTo(int(x0+t0*deltax),int(y0+t0*deltay));
	pDC->LineTo(int(x0+t1*deltax),int(y0+t1*deltay));
}
/*=========================
//	OnDrawLineCutL
//
===========================*/
void LineCut::OnDrawLineCutL(CDC* pDC)
{
	pDC->Rectangle (xl,yt,xr,yb);

	for(int i=xl-150;i<xr+150;i++)
	{
		if((i-xl+150)%20<5)
		{
			pDC->SetPixel(i,yt,RGB(200,200,200));
			pDC->SetPixel(i,yb,RGB(200,200,200));
		}
	}
	for(i=yt-150;i<yb+150;i++)
	{
		if((i-yt+150)%20<5)
		{
			pDC->SetPixel(xl,i,RGB(200,200,200));
			pDC->SetPixel(xr,i,RGB(200,200,200));
		}
	}
	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,200,_T("×ó¼ü»­Ïß"));
	pDC->TextOut(700,230,_T("ÓÒ¼üÇåÆÁ"));
	
	pDC->SetTextColor(RGB(0,85,234));
	pDC->TextOut(650,500,_T("L_Barsky"));
	
}
LineCut::~LineCut()
{

}
