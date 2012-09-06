// DrawFill.cpp: implementation of the DrawFill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "DrawFill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DrawFill::DrawFill()
{

}
/*=========================
//	Floodfill
//
===========================*/
void DrawFill::Floodfill(CDC* pDC,int x,int y,COLORREF oldvalue,COLORREF newvalue)
{
	/*
	(x,y)是给出的种子位置
	oldvalue是区域内像素原值
	newvalue是要取代原值的新值，应不等于原值
	*/
	if(pDC->GetPixel(x,y)==oldvalue)
	{
		pDC->SetPixel(x,y,newvalue);//改变原值为新值
		Floodfill(pDC,x,y-1,oldvalue,newvalue);//向四个方向扩散
		Floodfill(pDC,x,y+1,oldvalue,newvalue);
		Floodfill(pDC,x-1,y,oldvalue,newvalue);
		Floodfill(pDC,x+1,y,oldvalue,newvalue);
	}
}
/*=========================
//	Boundaryfill
//
===========================*/
void DrawFill::Boundaryfill(CDC* pDC,int x,int y,COLORREF boundaryvalue, COLORREF newvalue)
{
	/*
	(x,y)是给出的种子的位置
	boundaryvalue是边界上像素的值
	newvalue是区域内像素应被送入的新值
	*/
	if((pDC->GetPixel(x,y)!=boundaryvalue)/*没有到达边界*/&&(pDC->GetPixel(x,y)!=newvalue)/*并且没有被访问过*/)
	{
		pDC->SetPixel(x,y,newvalue);//赋予新值
		Boundaryfill(pDC,x,y-1,boundaryvalue,newvalue);//向四个方向扩散
		Boundaryfill(pDC,x,y+1,boundaryvalue,newvalue);
		Boundaryfill(pDC,x-1,y,boundaryvalue,newvalue);
		Boundaryfill(pDC,x+1,y,boundaryvalue,newvalue);
	}
}
/*=========================
//	 ScanlineSeedfill
//	  
===========================*/

void DrawFill::ScanlineSeedfill(CDC* pDC,int x,int y,COLORREF boundaryvalue,COLORREF newvalue)
{//填充当前行,然后扫描相邻的上下两行,寻找新的种子点
	int x0,xl,xr,y0,xid;//,x,y;
	bool flag;
	int xnextspan;
	CStack  s;
	//CStack <CPoint> s;				//操作数栈 
	CPoint p;						//定义一个点
	s.Push(CPoint(x,y));			//种子像素入栈

	//当栈非空时循环
	while(!s.StackEmpty())
	{
		p=s.Pop();									//栈顶像素出栈
		pDC->SetPixel(p.x,p.y,newvalue);	//将点(x,y)填充 
		x=p.x; y=p.y; 
		x0=x+1;										//向右移一个像素
		while(pDC->GetPixel(x0,y)!=boundaryvalue)			//填充右方像素
		{																	//当点(x0,y)的像素值不等于边界像素值时,循环
			pDC->SetPixel(x0,y,newvalue);						//将点(x0,y)填充
			x0++;															//向右移一个像素,循环--继续填充,直至到边界点
		}
		xr=x0-1;															//最右方像素 //xr为右边界点的左边一个点的x值,记录用
		x0=x-1;															//x0变成原种子点p左一个点的x值
		while(pDC->GetPixel(x0,y)!=boundaryvalue)			//填充左方像素
		{																	//当点(x0,y)的像素值不等于边界像素值时,循环
			pDC->SetPixel(x0,y,newvalue);						//将点(x0,y)填充
			x0--;															//向左移一个像素,循环--继续填充,直至到边界点
		}
		xl=x0+1;															//最左边像素 //xl为左边界点的右边一个点的x值,记录用
		//检查上一条扫描线和下一条扫描线，若存在非边界且未填充的像素，则选取代表各连续区间的种子像素入栈
		y0=y;																//为y0赋值为y,与种子点的y值相等
		for(int i=1;i>=-1;i-=2)										//做两次循环,之所以这样定义赋值,因为下面有变量要用到i的值
		{
			x0=xr;														//将右边界左边一点的xr的值传给x0
			y=y0+i;														//y的值先加1,再减1,表示点下移一行,在下次循环时上移一行
			while(x0>=xl)												//当x0>=xl时循环
			{
				flag=false;
				while((pDC->GetPixel(x0,y)!=boundaryvalue)&&(pDC->GetPixel(x0,y)!=newvalue)&&(x0>xl)) //当点(x0,y)没被填充且不是边界   且   x0>=xl时   ---循环
				{
					if(!flag)												//如果flag为false 
					{
						flag=true;										//将flag改为ture 
						xid=x0;											//xid赋值为x0,xid作为记录x0用
					}
					x0--;													//点(x0,y)   每次循环左移一点
				}
				if(flag)													//当flag为ture时
				{
					s.Push(CPoint(xid,y));							//将点(xid,y)入栈  
					flag=false;											//然后在将flag置为false 
				}
				xnextspan=x0;
				while((pDC->GetPixel(x0,y)==boundaryvalue)||(pDC->GetPixel(x0,y)==newvalue)&&(x0>=xl))//当点(x0,y)是边界   或者   填充过时,(x0,y)   向左移一点
					x0--;
				if(xnextspan==x0)x0--;
			}//end   of   while(x0>=xl) 
		}//end   of   for(int   i=1;i>=-1;i-=2)
	}//end   of   while(!s.empty()) 
}
void DrawFill::OnDrawFill(CDC* pDC)
{
	/*===============
	//	Fill
	//
	================*/
	pDC->Rectangle(FillX-50,FillY+100,FillX,FillY+150);
	Floodfill(pDC,FillX-30,FillY+120,RGB(255,255,255),RGB(200,0,0));

	pDC->Ellipse(FillX+50,FillY+100,FillX+100,FillY+150);
	Boundaryfill(pDC,FillX+70,FillY+120,RGB(0,0,0),RGB(200,200,200));

	pDC->Ellipse(FillX+150,FillY+100,FillX+250,FillY+150);
	ScanlineSeedfill(pDC,FillX+162,FillY+120,RGB(0,0,0),RGB(20,200,200));

	/*===============
	//	Mark
	================*/

	CPen pen1,pen2,pen3;//CPen*OldPen;

	pen1.CreatePen( PS_SOLID,2,RGB(200,0,0) );
	pDC->SelectObject(&pen1);
	pDC->MoveTo(FillX+300,FillY+20);
	pDC->LineTo(FillX+400,FillY+20);
	pDC->TextOut(FillX+450,FillY+10,_T("Floodfill"));

	pen2.CreatePen( PS_SOLID,2,RGB(200,200,200) );
	pDC->SelectObject(&pen2);
	pDC->MoveTo(FillX+300,FillY+80);
	pDC->LineTo(FillX+400,FillY+80);
	pDC->TextOut(FillX+450,FillY+70,_T("Boundaryfill"));

	pen3.CreatePen( PS_SOLID,2,RGB(20,200,200) );
	pDC->SelectObject(&pen3);
	pDC->MoveTo(FillX+300,FillY+140);
	pDC->LineTo(FillX+400,FillY+140);
	pDC->TextOut(FillX+450,FillY+130,_T("ScanlineSeedfill"));

	pDC->TextOut(FillX+300,FillY+210,_T("区域填充"));
}
DrawFill::~DrawFill()
{

}
