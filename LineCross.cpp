// LineCross.cpp: implementation of the LineCross class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "LineCross.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPoint temp;
double delta, rmd, miu;//LineCross

LineCross::LineCross()
{
	
}

/*=========================
//	Cross
//
===========================*/
void LineCross::Cross(CDC* pDC)
{
	pDC->SelectObject(CPen (PS_SOLID,2,RGB(255,0,0)));
	
	if(LCSCOUNT==4)
	{
		delta=(LCSP[1].x-LCSP[0].x)*(LCSP[2].y-LCSP[3].y)-(LCSP[2].x-LCSP[3].x)*(LCSP[1].y-LCSP[0].y);
		
		if (delta!=0)
		{
			rmd=((LCSP[2].x-LCSP[0].x)*(LCSP[2].y-LCSP[3].y)-(LCSP[2].x-LCSP[3].x)*(LCSP[2].y-LCSP[0].y))/delta;
			
			if (rmd>=0&&rmd<=1)
			{
				miu=((LCSP[1].x-LCSP[0].x)*(LCSP[2].y-LCSP[0].y)-(LCSP[2].x-LCSP[0].x)*(LCSP[1].y-LCSP[0].y))/delta;
				
				if (miu>=0&&miu<=1)//
				{
					temp.x=long(LCSP[0].x+rmd*(LCSP[1].x-LCSP[0].x));
					temp.y=long(LCSP[0].y+rmd*(LCSP[1].y-LCSP[0].y));
					
					ShowPoints(pDC,temp);
					
				}
			}
		}
		
		LCSCOUNT=0;
	}
	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(700,70,_T("两点画线"));
	pDC->TextOut(700,100,_T("两线求交"));
}

/*=========================
//	ShowPoints
//
===========================*/
void LineCross::ShowPoints(CDC* pDC,CPoint point )
{
	TCHAR Buffer[8];
	
	pDC->SetTextColor(RGB(0,85,234));
	
	pDC->TextOut(point.x,point.y,_T("("));
	
	pDC->TextOut(point.x+10,point.y,Buffer,wsprintf (Buffer, TEXT ("%d"),point.x));
	
	pDC->TextOut(point.x+40,point.y,_T(","));
	
	pDC->TextOut(point.x+50,point.y,Buffer,wsprintf (Buffer, TEXT ("%d"),point.y));
	
	pDC->TextOut(point.x+80,point.y,_T(")"));
}

LineCross::~LineCross()
{
	
}
