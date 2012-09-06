// GraphicsView.cpp : implementation of the CGraphicsView class
//

#include "stdafx.h"
#include "Graphics.h"

#include "GraphicsDoc.h"
#include "GraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*========================
名称:	图形学实验
作者:	ELEVEN
日期:	2007年12月15日
==========================*/
#include "DrawLine.h"
#include "Circle.h"
#include "DrawFill.h"
#include "Ploygon.h"
#include "Planar.h"
#include "Square.h"
#include "LineCut.h"
#include "Hermite.h"
#include "Bezier.h"
#include "Coons.h"
#include "BCurve.h"
#include "LineCross.h"

static	int DrawMode;
const	int ModeMySelf  =0;
const	int ModeLine	=1;
const	int ModeCircle	=2;
const	int ModeFill	=3;
const	int ModeCouple	=4;
const	int ModeET		=5;
const	int ModePlanar  =6;
const	int ModeSquare	=7;
const	int ModeLineCutC=8;
const	int ModeLineCutL=9;
const	int ModeLagrange=10;
const	int ModeHermite	=11;
const	int ModeBizierL =12;
const	int ModeBizierLD=13;
const	int ModeBizierLS=14;
const	int ModeBizierM =15;
const	int ModeCoons   =16;
const	int ModeBcurveL	=17;
const	int ModeBcurveM	=18;
const	int ModeLineCross=19;

DrawLine	L;
CCircle		C;
DrawFill	F;
Ploygon		G;
Planar		P;
Square		S;
LineCut		LC;
Hermite		H;
Bezier		B;
CCoons		CO;
BCurve		BC;
LineCross   LCS;

//int Mcount;int xx=200;TCHAR MBUFFER[10];
/////////////////////////////////////////////////////////////////////////////
// CGraphicsView

/*=========================
//	消息映射
//
===========================*/
IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	ON_COMMAND(ID_ELEVEN,ShowMySelf)
	
	ON_COMMAND(ID_Line,DrawLineMain)

	ON_COMMAND(ID_Circle,DrawCircleMain)

	ON_COMMAND(ID_Fill,DrawFillMain)

	ON_COMMAND(ID_Couple,DrawCoupleMain)
	ON_COMMAND(ID_ET,DrawETMain)

	ON_COMMAND(ID_Planar,DrawPlanarMain)

	ON_COMMAND(ID_Square,DrawSquareMain)

	ON_COMMAND(ID_LineCutC,DrawLineCutCMain)
	ON_COMMAND(ID_LineCutL,DrawLineCutLMain)

	ON_COMMAND(ID_Lagrange,DrawLagrangeMain)
	ON_COMMAND(ID_Hermite,DrawHermiteMain)
	
	ON_COMMAND(ID_BezierL,DrawBezierLMain)
	ON_COMMAND(ID_BezierM,DrawBezierMMain)

	ON_COMMAND(ID_Coons,DrawCoonsMain)

	ON_COMMAND(ID_BcurveL,DrawBcurveLMain)

	ON_COMMAND(ID_BezierLDecas,DrawBezierLDecasMain)
	ON_COMMAND(ID_BezierLSplit,DrawBezierLSplitMain)
	
	ON_COMMAND(ID_BcurveM,DrawBcurveMMain)
	
	ON_COMMAND(ID_LineCross,DrawLineCrossMain)
	
	//{{AFX_MSG_MAP(CGraphicsView)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

void CGraphicsView::OnTimer(UINT_PTR nIDEvent)
{
	CDC* pDC=GetDC();
	//Mcount=0;
	
	switch (nIDEvent)
	{
	case 1:  // 计时器1

		//.... // 处理的代码

		//MX+=10;

		/*pDC->TextOut(xx,500,MBUFFER,wsprintf (MBUFFER, TEXT ("%s"),">"));
		
		xx+=20;Mcount++;

		if (Mcount<10)
		{
			InvalidateRect(NULL,FALSE);
		}
		else
		{
			xx=200;
			InvalidateRect(NULL,TRUE);
			KillTimer(1);
		}*/
		

		KillTimer(1);  // 删除此计时器，否则计时器中断完后会自动重新开始计时，到下一次中断时还会发生新的中断
		
		break;
			
	case 2:  // 计时器2

		//.... // 处理的代码
		
		break;

	default:
		
		MessageBox("default: KillTimer");

		KillTimer(nIDEvent);

		break;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CGraphicsView construction/destruction

CGraphicsView::CGraphicsView()
{
	// TODO: add construction code here

}

CGraphicsView::~CGraphicsView()
{
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}
/*=========================
//	MyInfomation
//
===========================*/
void CGraphicsView::MyInfomation(CDC* pDC)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	CBitmap m_Bmp;
	m_Bmp.LoadBitmap(IDB_JAY); 
	
	CDC MemDC;	//定义设备环境对象
	MemDC.CreateCompatibleDC(NULL);
	MemDC.SelectObject(pDoc->m_Bitmap);

	int MX=GetSystemMetrics(SM_CXSCREEN)/5;
	int MY=GetSystemMetrics(SM_CYSCREEN)/5;
	
	pDC->BitBlt(MX,MY,pDoc->m_nWidth,pDoc->m_nHeight,&MemDC,0,0,SRCCOPY);
	
	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(MX+350,MY+50,_T("ELEVEN  12.15"));
	
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(MX+350,MY+150,_T("计算机图形学实验演示"));

//	SetTimer(1, 100, NULL);
	
}
/*=========================
//	OnDraw
//
===========================*/
/////////////////////////////////////////////////////////////////////////////
// CGraphicsView drawing

void CGraphicsView::OnDraw(CDC* pDC)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	switch(DrawMode)
	{
	case ModeMySelf:
		
		MyInfomation(pDC);
		
		break;
		
	case ModeLine:
		
		L.OnDrawLine(pDC);
		
		break;
	case ModeCircle:
		
		C.OnDrawCircle(pDC);
		
		break;	
	case ModeFill:
		
		F.OnDrawFill(pDC);
		
		break;
		case ModeCouple:
		
		G.OnDrawCouple(pDC);

		break;

	case ModeET:

		G.OnDrawET(pDC);

		break;
	case ModePlanar:

		P.OnDrawPlanar(pDC);
		
		break;
	case ModeSquare:
		
		S.OnDrawSquare(pDC);
		
		break;
	case ModeLineCutC:
		
		LC.OnDrawLineCutC(pDC);
		
		break;
		
	case ModeLineCutL:
		
		LC.OnDrawLineCutL(pDC);
		
		break;

	case ModeLagrange:

		H.OnDrawLargange(pDC);

		break;

	case ModeHermite:

		H.OnDrawHermite(pDC);

		break;
	case ModeBizierL:

		B.OnDrawBezierL(pDC);

		break;
	case ModeBizierLD:
		
		B.OnDrawBezierLD(pDC);
		
		break;
	case ModeBizierLS:
		
		B.OnDrawBezierLS(pDC);
		
		break;
	case ModeBizierM:

		B.OnDrawBezierM(pDC);

		break;
	case ModeCoons:
		
		CO.OnDrawCoons(pDC);
		
		break;
	case ModeBcurveL:
		
		BC.OnDrawBcurveL(pDC);
		
		break;
		
	case ModeBcurveM:
		
		BC.OnDrawBcurveM(pDC);
		
		break;
		
	case ModeLineCross:
		
		LCS.Cross(pDC);
		
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView printing

BOOL CGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView diagnostics

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

/*=========================
//	Message handlers
//
===========================*/
/////////////////////////////////////////////////////////////////////////////
// CGraphicsView message handlers
void CGraphicsView::ShowMySelf()
{
	DrawMode=ModeMySelf;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawLineMain()
{
	DrawMode=ModeLine;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawCircleMain()
{
	DrawMode=ModeCircle;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawFillMain()
{
	DrawMode=ModeFill;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawCoupleMain()
{
	DrawMode=ModeCouple;

	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawETMain()
{
	DrawMode=ModeET;

	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawPlanarMain()
{
	DrawMode=ModePlanar;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawSquareMain()
{
	DrawMode=ModeSquare;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawLineCutCMain()
{
	DrawMode=ModeLineCutC;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawLineCutLMain()
{
	DrawMode=ModeLineCutL;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawLagrangeMain()
{
	DrawMode=ModeLagrange;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawHermiteMain()
{
	DrawMode=ModeHermite;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawBezierLMain()
{
	DrawMode=ModeBizierL;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawBezierLDecasMain()
{
	DrawMode=ModeBizierLD;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawBezierLSplitMain()
{
	DrawMode=ModeBizierLS;

	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawBezierMMain()
{
	DrawMode=ModeBizierM;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawCoonsMain()
{
	DrawMode=ModeCoons;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawBcurveLMain()
{
	DrawMode=ModeBcurveL;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawBcurveMMain()
{
	DrawMode=ModeBcurveM;
	
	InvalidateRect(NULL,TRUE);
}
void CGraphicsView::DrawLineCrossMain()
{
	DrawMode=ModeLineCross;
	
	InvalidateRect(NULL,TRUE);
}
/*=========================
//	键盘消息
//
===========================*/
void CGraphicsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC=GetDC();int i;//,j;

	switch (nChar) 
	{ 
	case VK_UP:

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].ReMove (0,-10);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{
		}*/
		
		break;
	case VK_DOWN:

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].ReMove (0,10);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{
		}*/
		
		break;
	case VK_LEFT:

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].ReMove(-10,0);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{
		}*/
		
		break;
	case VK_RIGHT:
		
		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].ReMove (10,0);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{
		}*/

		break;
	case 'L':

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].ReSize (2,2);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{
		}*/

		break;

	case 'S':
		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].ReSize (0.5,0.5);
			}
		}
		else if (DrawMode==ModeSquare)
		{
			//平移变换
			for(i=0;i<8;i++)
			{
				S.P[i].Move(0,20,0);
			}
		}

		break;
	case 'P':

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].Cycle (15);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{}*/
		
		break;
	case 'O':

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].Cycle (-15);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{}*/
		
		break;
	case 'I':

		if (DrawMode==ModePlanar)
		{
			P.first=true;
		}
		/*else if (DrawMode==ModeSquare)
		{}*/
		
		break;
	case 'Y':
		
		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].symmetry_y ();
			}
		}
		else if (DrawMode==ModeSquare)
		{
			for(i=0;i<8;i++)
			{
				S.P[i].Roat_y(S.D2R2(15));;
			}
		}
		
		break;
	case 'J':

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].cuoqie (4,1,0);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{}*/

		break;
	case 'K':

		if (DrawMode==ModePlanar)
		{
			for(i=0;i<4;i++)
			{
				P.PP[i].cuoqie (-4,-1,0);
			}
		}
		/*else if (DrawMode==ModeSquare)
		{}*/
		
		break;
	case 'M':  
		
		if (DrawMode==ModeSquare)
		{
			S.me=(S.me+1)%2;
		}
		/*else if ()
		{}*/
		
		break;

	case 'R':  

		if (DrawMode==ModeSquare)
		{
			S.ts=(S.ts+1)%2;
		}
		/*else if ()
		{}*/
		
		break;

	case 'Q':  

		if (DrawMode==ModeSquare)
		{
			//平移变换
			for(i=0;i<8;i++)
			{
				S.P[i].Move(0,0,-20);
			}
		}
		/*else if ()
		{}*/

		break;
		
	case 'E':  
	
		if (DrawMode==ModeSquare)
		{
			//平移变换
			for(i=0;i<8;i++)
			{
				S.P[i].Move(0,0,20);
			}
		}
		/*else if ()
		{}*/
		
		break;

	case 'W':  

		if (DrawMode==ModeSquare)
		{
			//平移变换
			for(i=0;i<8;i++)
			{
				S.P[i].Move(0,-20,0);
			}
		}
		/*else if ()
		{}*/
	
		break; 

	case 'A':  

		if (DrawMode==ModeSquare)
		{
			//平移变换
			for(i=0;i<8;i++)
			{
				S.P[i].Move(-20,0,0);
			}
		}
		/*else if ()
		{}*/

		break; 

	case 'D':

		if (DrawMode==ModeSquare)
		{
			//平移变换
			for(i=0;i<8;i++)
			{
				S.P[i].Move(20,0,0);
			}
		}
		/*else if ()
		{}*/

		break; 

	case 'F': 
		if (DrawMode==ModeSquare)
		{
			//比例变换大
			//resize
			for(i=0;i<8;i++)
			{
				S.P[i].Resize(S.Pos[3].Get_X(),S.Pos[ 3].Get_Y(),S.Pos[3].Get_Z(),2,2,2);
			}
		}
		/*else if ()
		{}*/
		
		break; 

	case 'G': 
		
		if (DrawMode==ModeSquare)
		{
			//比例变换小
			//resize
			for(i=0;i<8;i++)
			{
				S.P[i].Resize(S.P[3].Get_X(),S.P[ 3].Get_Y(),S.P[3].Get_Z(),0.5,0.5,0.5);
			}
		}
		/*else if ()
		{}*/
		
		break;

	case 'X': 

		if (DrawMode==ModeSquare)
		{
			//旋转变换
			for(i=0;i<8;i++)
			{
				S.P[i].Roat_x(S.D2R2(15));;
			}
		}
		/*else if ()
		{}*/
		
		break;

	case 'Z': //

		if (DrawMode==ModeSquare)
		{
			//旋转变换
			for(i=0;i<8;i++)
			{
				S.P[i].Roat_z(S.D2R2(15));;
			}
		}
		/*else if ()
		{}*/
		
		break;

	case 'T':

		if (DrawMode==ModeSquare)
		{
			S.ty=(S.ty+1)%2;
		}
		/*else if ()
		{}*/

		break;

	case 'V':

		if (DrawMode==ModeSquare)
		{
			S.first=true;
		}
		/*else if ()
		{}*/
		
		break;

	default: 

		break; 
	} 
	
	InvalidateRect(NULL,TRUE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
/*=========================
//	鼠标消息
//
===========================*/
void CGraphicsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDC *pDC=GetDC();
	CBrush Brush;Brush.CreateSolidBrush(RGB(255,0,0));

	CRect rect;

	switch(DrawMode)
	{
	case ModeLineCutC:

		LC.p1=point;

		break;

	case ModeLineCutL:
		
		LC.m_Oldpoint=point;//保存光标的当前位置
		LC.m_Newpoint=point;//存放画线的起始位置

		SetCapture(); //捕捉鼠标

		LC.m_pLMouseDown=true;//表示鼠标为按下的状态

		break;

	case ModeLagrange:
		
		pDC->SelectObject(&Brush);
		
		H.P[H.count]=point;
		
		H.count++;//how many points
		
		pDC->Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);

		break;

	case ModeHermite:
		
		if (H.countH<4)
		{
			pDC->SelectObject(&Brush);
			
			H.PH[H.countH]=point;
			H.countH++;//how many points
			
			if (H.countH==3) 
			{
				pDC->MoveTo(H.PH[0]);
				pDC->LineTo(H.PH[2]);
			}
			else
			{
				if (H.countH==4)
				{
					pDC->MoveTo(H.PH[1]);
					pDC->LineTo(H.PH[3]);
				}
			}
			
			pDC->Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);
		}

		break;

	case ModeBizierL:
		
		pDC->SelectObject(&Brush);
		
		B.p[B.count]=point;
		B.count++;//how many points


		pDC->Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);

		
		if (B.count>1)
		{
			pDC->MoveTo(B.p[B.count-2]);
			pDC->LineTo(B.p[B.count-1]);
		}

		break;
	case ModeBizierLD:
		
		pDC->SelectObject(&Brush);
		
		B.D[B.Dcount]=point;
		B.Dcount++;//how many points
		
		
		pDC->Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);
		
		
		if (B.Dcount>1)
		{
			pDC->MoveTo(B.D[B.Dcount-2]);
			pDC->LineTo(B.D[B.Dcount-1]);
		}
		
		break;
	case ModeBizierLS:
		
		pDC->SelectObject(&Brush);
		
		B.S[B.Scount]=point;
		B.Scount++;//how many points
		
		
		pDC->Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);
		
		
		if (B.Scount>1)
		{
			pDC->MoveTo(B.S[B.Scount-2]);
			pDC->LineTo(B.S[B.Scount-1]);
		}
		
		break;
		
	case ModeBcurveL:
		pDC->SelectObject(&Brush);
		
		BC.p[BC.count]=point;
		BC.count++;//how many points
		
		pDC->Ellipse(point.x-5,point.y-5,point.x+5,point.y+5);
		
		if (BC.count>1)
		{
			pDC->MoveTo(BC.p[BC.count-2]);
			pDC->LineTo(BC.p[BC.count-1]);
		}
		
		break;

	case ModeLineCross:
		
		LCS.ShowPoints(pDC,point);

		LCS.LCSP[LCS.LCSCOUNT]=point;

		LCS.LCSCOUNT++;

		if (LCS.LCSCOUNT==2)
		{
			//pDC->SelectObject(CPen(PS_SOLID,2,RGB(255,0,0)));
			
			pDC->MoveTo(LCS.LCSP[LCS.LCSCOUNT-1]);
			pDC->LineTo(LCS.LCSP[LCS.LCSCOUNT-2]);
		}

		if (LCS.LCSCOUNT==4)
		{

			//pDC->SelectObject(CPen(PS_SOLID,2,RGB(0,255,0)));
			
			pDC->MoveTo(LCS.LCSP[LCS.LCSCOUNT-1]);
			pDC->LineTo(LCS.LCSP[LCS.LCSCOUNT-2]);

			InvalidateRect(NULL,FALSE);
		}

		break;

	default:

		break;
	}

	ReleaseDC(pDC);
	
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDC *pDC=GetDC();

	switch(DrawMode)
	{
	case ModeLineCutC:
		
		LC.p2=point;
		
		pDC->SelectObject(&LC.pen2);
		
		pDC->MoveTo(LC.p1);pDC->LineTo(LC.p2);

		break;

	case ModeLineCutL:

		if(LC.m_pLMouseDown)
		{
			LC.m_pLMouseDown=false;//标志鼠标释放

			ReleaseCapture();//释放鼠标捕捉
			
			ClipCursor(NULL);//使光标可以随意移动

			LC.L_Barsky(pDC,LC.m_Newpoint.x,LC.m_Newpoint.y,LC.m_Oldpoint.x,LC.m_Oldpoint.y);
		}

		break;

	default:

		break;
	}

	
	ReleaseDC(pDC);

	CView::OnLButtonUp(nFlags, point);
}

void CGraphicsView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC=GetDC();
	double i,t;int j;
	long minx,maxx;
	CPoint R;CPoint temp;
	
	CPoint p[200];int npoints=200;

	switch(DrawMode)
	{
	case ModeLineCutC:
		
		pDC->SelectObject(&LC.pen1);
	
		LC.Cohen_Sutherland(pDC,LC.p1.x,LC.p1.y,LC.p2.x,LC.p2.y);

		break;

	case ModeLineCutL:
		
		Invalidate(TRUE);

		break;

	case ModeLagrange:
		
		minx=H.P[0].x,maxx=H.P[0].x;
		
		//xmin->xmax
		for (j=0;j<4;j++)
		{
			
			if (H.P[j].x<minx) 
			{
				minx=H.P[j].x;
			}
			
			if (H.P[j].x>maxx)
			{
				maxx=H.P[j].x;
			}
			
		}
		
		for (i=minx;i<maxx;i+=0.1)
		{
			R.x=long(i);
			R.y=long(H.P[0].y*H.g0(i)+H.P[1].y*H.g1(i)+H.P[2].y*H.g2(i)+H.P[3].y*H.g3(i));
			
			pDC->SetPixel(R,RGB(255,0,0));
		}
		H.count=0;
		
		break;

	case ModeHermite:

		H.DrawHermite(pDC,H.PH);

		H.countH=0;

		break;

	case ModeBizierL://p80  bezier曲线1
		
		B.count=0;
		
		//p 80
		for (t=0.000;t<1.000;t+=1/double(500))
		{
			temp.x+=long(B.p[0].x*(1-t)*(1-t)*(1-t)+B.p[1].x*3*t*(1-t)*(1-t)+B.p[2].x*3*t*t*(1-t)+B.p[3].x*t*t*t);
			temp.y+=long(B.p[0].y*(1-t)*(1-t)*(1-t)+B.p[1].y*3*t*(1-t)*(1-t)+B.p[2].y*3*t*t*(1-t)+B.p[3].y*t*t*t);
			
			pDC->SetPixel(temp,RGB(255,0,0));
			
			temp.x=0;temp.y=0;
		}
		
		//InvalidateRect(NULL,FALSE);

		break;

	case ModeBizierLD:
		
		
		B.bez_to_point(pDC,3,npoints,B.D,p);
		
		pDC->MoveTo(B.D[0]);
		
		for(j=0;j<npoints;j++)
			pDC->LineTo(p[j]);
		
		//MessageBox (TEXT ("未完成!"), TEXT ("提示"), 0) ;
		
		B.Dcount=0;

		InvalidateRect(NULL,FALSE);

		break;
	case ModeBizierLS:
		
		B.new_split_Bezier(pDC,B.S);
		
		//MessageBox (TEXT ("未完成!"), TEXT ("提示"), 0) ;
		
		B.Scount=0;
		
		InvalidateRect(NULL,FALSE);
		
		break;

	case ModeBcurveL:
		
		BC.count=0;

		pDC->SelectObject(CPen(PS_SOLID,2,RGB(0,0,255)));
		
		//B样条曲线
		for (t=0.000;t<1.000;t+=1/double(200))
		{
			BC.DrawL(pDC,t);
		}

		InvalidateRect(NULL,FALSE);

		break;
		
	default:break;

	}

	ReleaseDC(pDC);
	
	CView::OnRButtonDown(nFlags, point);
}

void CGraphicsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC=GetDC();

	switch(DrawMode)
	{
	case ModeLineCutL:
		
		if(LC.m_pLMouseDown)
		{
			CClientDC dc(this);
			dc.SetROP2(R2_NOT); //设置绘图模式，以屏幕颜色的相反色绘图  
			
			dc.MoveTo(LC.m_Newpoint);//以重绘的方式擦除前一个OnMouseMove绘制的直线
			dc.LineTo(LC.m_Oldpoint);
			dc.MoveTo(LC.m_Newpoint); //重新位置到当前位置画一条直线
			dc.LineTo(point);
			LC.m_Oldpoint=point; //存放当前鼠标位置
		}
		
		break;
		
	default:
		
		break;
	}
	
	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}
