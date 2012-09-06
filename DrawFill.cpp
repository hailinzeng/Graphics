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
	(x,y)�Ǹ���������λ��
	oldvalue������������ԭֵ
	newvalue��Ҫȡ��ԭֵ����ֵ��Ӧ������ԭֵ
	*/
	if(pDC->GetPixel(x,y)==oldvalue)
	{
		pDC->SetPixel(x,y,newvalue);//�ı�ԭֵΪ��ֵ
		Floodfill(pDC,x,y-1,oldvalue,newvalue);//���ĸ�������ɢ
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
	(x,y)�Ǹ��������ӵ�λ��
	boundaryvalue�Ǳ߽������ص�ֵ
	newvalue������������Ӧ���������ֵ
	*/
	if((pDC->GetPixel(x,y)!=boundaryvalue)/*û�е���߽�*/&&(pDC->GetPixel(x,y)!=newvalue)/*����û�б����ʹ�*/)
	{
		pDC->SetPixel(x,y,newvalue);//������ֵ
		Boundaryfill(pDC,x,y-1,boundaryvalue,newvalue);//���ĸ�������ɢ
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
{//��䵱ǰ��,Ȼ��ɨ�����ڵ���������,Ѱ���µ����ӵ�
	int x0,xl,xr,y0,xid;//,x,y;
	bool flag;
	int xnextspan;
	CStack  s;
	//CStack <CPoint> s;				//������ջ 
	CPoint p;						//����һ����
	s.Push(CPoint(x,y));			//����������ջ

	//��ջ�ǿ�ʱѭ��
	while(!s.StackEmpty())
	{
		p=s.Pop();									//ջ�����س�ջ
		pDC->SetPixel(p.x,p.y,newvalue);	//����(x,y)��� 
		x=p.x; y=p.y; 
		x0=x+1;										//������һ������
		while(pDC->GetPixel(x0,y)!=boundaryvalue)			//����ҷ�����
		{																	//����(x0,y)������ֵ�����ڱ߽�����ֵʱ,ѭ��
			pDC->SetPixel(x0,y,newvalue);						//����(x0,y)���
			x0++;															//������һ������,ѭ��--�������,ֱ�����߽��
		}
		xr=x0-1;															//���ҷ����� //xrΪ�ұ߽������һ�����xֵ,��¼��
		x0=x-1;															//x0���ԭ���ӵ�p��һ�����xֵ
		while(pDC->GetPixel(x0,y)!=boundaryvalue)			//���������
		{																	//����(x0,y)������ֵ�����ڱ߽�����ֵʱ,ѭ��
			pDC->SetPixel(x0,y,newvalue);						//����(x0,y)���
			x0--;															//������һ������,ѭ��--�������,ֱ�����߽��
		}
		xl=x0+1;															//��������� //xlΪ��߽����ұ�һ�����xֵ,��¼��
		//�����һ��ɨ���ߺ���һ��ɨ���ߣ������ڷǱ߽���δ�������أ���ѡȡ������������������������ջ
		y0=y;																//Ϊy0��ֵΪy,�����ӵ��yֵ���
		for(int i=1;i>=-1;i-=2)										//������ѭ��,֮�����������帳ֵ,��Ϊ�����б���Ҫ�õ�i��ֵ
		{
			x0=xr;														//���ұ߽����һ���xr��ֵ����x0
			y=y0+i;														//y��ֵ�ȼ�1,�ټ�1,��ʾ������һ��,���´�ѭ��ʱ����һ��
			while(x0>=xl)												//��x0>=xlʱѭ��
			{
				flag=false;
				while((pDC->GetPixel(x0,y)!=boundaryvalue)&&(pDC->GetPixel(x0,y)!=newvalue)&&(x0>xl)) //����(x0,y)û������Ҳ��Ǳ߽�   ��   x0>=xlʱ   ---ѭ��
				{
					if(!flag)												//���flagΪfalse 
					{
						flag=true;										//��flag��Ϊture 
						xid=x0;											//xid��ֵΪx0,xid��Ϊ��¼x0��
					}
					x0--;													//��(x0,y)   ÿ��ѭ������һ��
				}
				if(flag)													//��flagΪtureʱ
				{
					s.Push(CPoint(xid,y));							//����(xid,y)��ջ  
					flag=false;											//Ȼ���ڽ�flag��Ϊfalse 
				}
				xnextspan=x0;
				while((pDC->GetPixel(x0,y)==boundaryvalue)||(pDC->GetPixel(x0,y)==newvalue)&&(x0>=xl))//����(x0,y)�Ǳ߽�   ����   ����ʱ,(x0,y)   ������һ��
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

	pDC->TextOut(FillX+300,FillY+210,_T("�������"));
}
DrawFill::~DrawFill()
{

}
