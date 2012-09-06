// Ploygon.cpp: implementation of the Ploygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Ploygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*===============*/
TNode AET;

static TNode ET[MAX];
/*===============*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ploygon::Ploygon()
{

}
/*=========================
//	CoupleFill
//
===========================*/
void Ploygon::CoupleFill(CDC* pDC)
{

	CPen newpen(PS_SOLID,1,RGB(0,255,0));
	CPen *old=pDC->SelectObject(&newpen);

	int s=0;								//记录随着Scan往上,不再相交的edge
	int p[5];								//每根扫描线交点

	int pmin=spt[0].y,pmax=spt[0].y;		//记录边中ymax ymin

	//0-6	i<->i+1 (0 1) --- (5 6)
	for(int i=0;i<6;i++)					//建立边表 (每条边的信息) (0 5)
	{
		edge[i].dx=(float)(spt[i+1].x-spt[i].x)/(spt[i+1].y-spt[i].y);//斜率倒数

		if(spt[i].y<=spt[i+1].y)
		{
			edge[i].num=i;
			edge[i].ymin=spt[i].y;
			edge[i].ymax=spt[i+1].y;
			edge[i].xmin=(float)spt[i].x;
			edge[i].xmax=(float)spt[i+1].x;

			if(pmax<spt[i+1].y)pmax=spt[i+1].y;
			if(pmin>spt[i].y)pmin=spt[i].y;
		}
		else
		{
			edge[i].num=i;
			edge[i].ymin=spt[i+1].y;
			edge[i].ymax=spt[i].y;
			edge[i].xmax=(float)spt[i].x;
			edge[i].xmin=(float)spt[i+1].x;

			if(pmax<spt[i].y)pmax=spt[i].y;
			if(pmin>spt[i+i].y)pmin=spt[i+1].y;
		}
	}//END FOR

/*===================
//edge[0]--edge[5] 6边
//
====================*/
	
	//r=0 ->qmax=5,q+1=6
	for(int r=1;r<6;r++)						//排序edge
	{
		for(int q=0;q<6-r;q++)
		{
			if(edge[q].ymin<edge[q+1].ymin)		//ymin最小的将被送到最后
			{
				newedge[0]=edge[q];
				edge[q]=edge[q+1];
				edge[q+1]=newedge[0];
			}
		}
	}//for r

/*==================================
//	edge[0]--edge[5] ymin递减序 越后的越靠上
(2,3)
|
|
|
|
|
\
(2 ,9)
	\
	  \
		\
		(7,11)
//ymin 在最上方,ymax在最下方

//为了表示点，所以开始选择越上y越小
====================================*/

	for(int scan=pmax-1;scan>=pmin+1;scan--)		//pmax->pmin行扫描
	{
		int b=0;

		for(int j=s;j<6;j++)						//s记录随着Scan往上,不再相交的edge
		{
			if((scan>edge[j].ymin)&&(scan<=edge[j].ymax))//判断扫描线与线段相交
			{
				if(scan==edge[j].ymax)
				{
					if(spt[edge[j].num+1].y<edge[j].ymax)
					{
						b++;
						p[b]=(int)edge[j].xmax;
					}
					if(spt[edge[j].num-1].y<edge[j].ymax)
					{
						b++;		
						p[b]=(int)edge[j].xmax;
					}			
				}			
				 //if((scan>edge[j].ymin)&&(scan<edge[j].ymax))
				else
				{
					b++;
					p[b]=(int)(edge[j].xmax+edge[j].dx*(scan-edge[j].ymax));
				}
			}//end if

			if(scan<=edge[j].ymin)//当扫描线scan低于edge时,s=j
				s=j;
			
		}//for(j=k;j<6;j++)

		if(b>1)
		{
			for(int u=1;u<b;u+=2)
			{
				pDC->MoveTo(p[u],scan);
				pDC->LineTo(p[u+1],scan);
			}
			Sleep(1);
		}
	}
	pDC->SelectObject(old);	
}
/*=========================
//	OnDrawCouple
//
===========================*/
void Ploygon:: OnDrawCouple(CDC* pDC)
{
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
	pDC->TextOut(320,350,_T("多边形扫描转换算法"));
	
	/*================
	//	绘制多边形区域
	//
	=================*/
	spt[0]=CPoint(2*pbei,3*pbei);
	pDC->TextOut(spt[0].x-10,spt[0].y-5,_T("0"));
	
	spt[1]=CPoint(2*pbei,9*pbei);
	pDC->TextOut(spt[1].x-10,spt[1].y,_T("1"));
	
	spt[2]=CPoint(7*pbei,11*pbei);
	pDC->TextOut(spt[2].x,spt[2].y,_T("2"));
	
	spt[3]=CPoint(13*pbei,7*pbei);
	pDC->TextOut(spt[3].x+5,spt[3].y,_T("3"));
	
	spt[4]=CPoint(13*pbei,1*pbei);
	pDC->TextOut(spt[4].x+5,spt[4].y,_T("4"));
	
	spt[5]=CPoint(7*pbei,5*pbei);
	pDC->TextOut(spt[5].x,spt[5].y-20,_T("5"));
	
	spt[6]=CPoint(2*pbei,3*pbei);
	//pDC->TextOut(spt[6].x,spt[6].y,_T("6"));
	
	//spt[7]=CPoint(100,100);
	
	pDC->Polyline(spt,7);
	
	pDC->SelectObject(old);

	/*===============
	//	CoupleFill
	//
	=================*/

	CoupleFill(pDC);
}
/*==========================================*/
/*bool IsLocalMinMax(POINT* PolyNode, int i)
{

	if (PolyNode[i].y>PolyNode[(i+1)%N].y&&PolyNode[i].y>PolyNode[(i-1)%N].y)
	{
		return true;
	}
	else
	{
		if (PolyNode[i].y<PolyNode[(i+1)%N].y&&PolyNode[i].y<PolyNode[(i-1)%N].y)
		{
			return true;
		}
	}

	return false;
}*/

/*=========================
//	ConstructET
//
===========================*/
//ConstructET
void Ploygon::ConstructET(POINT *PolyNode,TNode *ET)
{
	int i,count=0;
	float delta;//斜率
	static bool flag=false;
	TNode *pET,*qAET,*qAET0;

	//int backi;//IsLocalMaxMin

	//初始化为空
	for(i=0;i<MAX;i++)
	{
		ET[i].y_max = 0;
		ET[i].next = NULL;
	}

	for(i=0;i<N;i++)//each line
	{
		pET = (LinkList)malloc(sizeof(TNode));

		delta = (float)(PolyNode[(i+1)%N].x-PolyNode[i].x)/(float)(PolyNode[(i+1)%N].y-PolyNode[i].y);
		
		//local=i+1;//IsLocalMaxMin
		if(PolyNode[i].y<=PolyNode[(i+1)%N].y)
		{
			pET->next=NULL;
			pET->x_min =(float) PolyNode[i].x ;
			pET->y_max = PolyNode[(i+1)%N].y;
			pET->dx = delta;

			/*if (IsLocalMinMax(PolyNode,i+1))
			{
				i=(i+1)%N;
			}*/
		//	{
				//ET[PolyNode[local].y].y_max++;
			//}
			//else
			//{
				ET[PolyNode[i].y].y_max++;
			//}
			
			if(ET[PolyNode[i].y].next==NULL)
			{//直接
				pET->next = ET[PolyNode[i].y].next;//add to ET table
				ET[PolyNode[i].y].next = pET;
			}
			else
			{
				qAET=ET[PolyNode[i].y].next;
	
				if(qAET->y_max>pET->y_max)
				{//the first wil be suit
					ET[PolyNode[i].y].next=pET;
					pET->next=qAET;
					//break;
				}
				else
				{
					flag=false;
					while(pET->y_max>qAET->y_max)
					{
						if(qAET->next==NULL)
						{//the end
							qAET->next=pET;
							//break;
							flag=true;//slove the break problem
							break;
						}
						else
						{
							qAET0=qAET;
							qAET=qAET->next;
						}
					}
					if(!flag)
					{
						qAET0->next=pET;
						pET->next=qAET;
					}//if(!flag)
				}//else
			}//else 直接

			/*if (IsLocalMinMax(PolyNode,i))
			{
				i=(i-1)%N;
			}*/

		}
		else
		{
		
			flag=false;
			pET->next=NULL;
			pET->x_min = (float)PolyNode[(i+1)%N].x;
			pET->y_max = PolyNode[i].y;
			pET->dx = delta; 

		/*	if (IsLocalMinMax(PolyNode,i))
			{
				i=(i+1)%N;
			}*/

			ET[PolyNode[(i+1)%N].y].y_max++;


			if(ET[PolyNode[(i+1)%N].y].next==NULL)
			{//direct add in 
				pET->next = ET[PolyNode[(i+1)%N].y].next;
				ET[PolyNode[(i+1)%N].y].next = pET;
			}
			else
			{
				qAET=ET[PolyNode[(i+1)%N].y].next;
				
				if(qAET->y_max>pET->y_max)
				{//the first will be ok
					ET[PolyNode[(i+1)%N].y].next=pET;
					pET->next=qAET;
					//break;
				}
				else
				{
					flag=false;
					while(pET->y_max>qAET->y_max)
					{
						if(qAET->next==NULL)
						{
							qAET->next=pET;
							//break;
							flag=true;
							break;
						}
						else
						{
							qAET0=qAET;
							qAET=qAET->next;
						}
					}//while
				//}
					if(!flag){qAET0->next=pET;pET->next=qAET;}
				}
			}

			/*if (IsLocalMinMax(PolyNode,i))
			{
				i=(i-1)%N;
			}*/
		}
	}//for
}

/*=========================
//	InitialAET
//
===========================*/
//Initial AET
void Ploygon::InitialAET(TNode AET)
{
	AET.y_max = 0;
	AET.next = NULL;
}

/*=========================
//	InsetNode
//
===========================*/
//InsetNode into AET
TNode  Ploygon::InsetNode(TNode *pInset,TNode AET,int i)
{
	bool flag=false;
	static TNode *pAET,*qAET,*qAET0;

	pAET = AET.next;

	if(pAET==NULL)
	{
		//pInset->next = AET[i].next;
		AET.y_max=ET[i].y_max;
		AET.next = pInset;
	}////////////////////////////////
	else
	{
		qAET=AET.next;

		while(pInset!=NULL)
		{
			if(AET.next->x_min>pInset->x_min)
			{//the first wil be suit
				qAET=AET.next;

				AET.next=pInset;

				if(pInset->next!=NULL)
					pInset=pInset->next;
				else
				{
					AET.next->next=qAET;
					break;
				}

				AET.next->next=qAET;
			//break;
			}////////////////////////////////////

			else
			{//y_max>=，往后

				if(AET.next->x_min==pInset->x_min)
				{//x is ok
					qAET=AET.next;

					if(AET.next->y_max>=pInset->y_max)
					{
						qAET=AET.next;

						AET.next=pInset;

						if(pInset->next!=NULL)
							pInset=pInset->next;
						else
						{
							AET.next->next=qAET;
							break;
						}

						AET.next->next=qAET;
					}/////////////////y
					else
					{
						flag=false;
						qAET=AET.next;
						while(pInset->x_min==qAET->x_min&&pInset->y_max>qAET->y_max)//?
						{
							if(qAET->next==NULL)
							{
								qAET->next=pInset;
								flag=true;
								break;
							}
							else
							{
								qAET0=qAET;
								qAET=qAET->next;
							}
						}
						if(!flag)
						{
							qAET0->next=pInset;
							pInset->next=qAET;
						}
						else
							break;
						
						if(pInset->next)
							break;
						else
							pInset=pInset->next;
					//break*/
					}
				}/////////////////////////////////
				else
				{
					flag=false;
					while(pInset->x_min>qAET->x_min)
					{
						if(qAET->next==NULL)
						{//the end
							qAET->next=pInset;
							flag=true;//slove the break problem
							break;
						}
						else
						{
							qAET0=qAET;
							qAET=qAET->next;
						}
					}
					if(!flag)
					{
						qAET0->next=pInset;
						pInset->next=qAET;
					}
					else
						break;

					if(pInset->next)
						break;
					else
						pInset=pInset->next;
				}
			}
		}
	}
	return AET;
}

/*=========================
//	Fill
//
===========================*/
//Fill the line with AET
void Ploygon::Fill(CDC* pDC,TNode AET,COLORREF color,int i)
{
	TNode *pdraw1,*pdraw2;
	
	pdraw1 = AET.next;
	pdraw2 = AET.next->next;

	while(pdraw1&&pdraw2)
	{
		pDC->MoveTo(int(pdraw1->x_min),i);pDC->LineTo(int(pdraw2->x_min),i);

		Sleep(1);

		//pDC->MoveTo(int(pdraw1->x_min)*bei,i*bei);pDC->LineTo(int(pdraw2->x_min)*bei,i*bei);
		
		if(pdraw2->next==NULL)
			break;
		else
		{
			pdraw1=pdraw2->next;
			if(pdraw1->next==NULL)
				break;
			else
				pdraw2=pdraw1->next;
		}
	}
}

/*=========================
//	DealNode
//
===========================*/
//Form the next AET
TNode Ploygon::DealNode(TNode AET,int i)
{
	TNode *pdel,*pAET;
	pAET = AET.next;
	//pInset=AET;

	if(pAET->y_max<i+1)
	{
		pdel=pAET;
		AET.next=pAET->next;
		free(pdel);
	}
	else
	{
		pdel=AET.next;

		while(pAET)
		{

			if(pAET->y_max >= i+1)//scanline
			{
				pAET->x_min+=pAET->dx;
				pdel=pAET;
				pAET = pAET->next;
			}
			else//delete
			{
				if(pdel->next==NULL)
					break;
				else
				{
					pdel->next=pdel->next->next;
					pAET=pdel->next;
				}
			}
		}
	}
	return AET;
}

/*=========================
//	DealAET
//
===========================*/
//DealAET
void  Ploygon::DealAET(CDC* pDC,TNode *ET,TNode AET,COLORREF color)
{
	int count=0;
	TNode * pET,*pInset;

	for(int i=0;i<MAX;i++)//ET
	{
		if(ET[i].next!=NULL)// ADD TO AET TABLE
		{
			count++;

			pET = ET[i].next;
			ET[i].next = NULL;

			pInset = pET;

			AET=InsetNode(pInset,AET,i);//line i
			ET[i].y_max=0;
		}

		if(AET.next==NULL)
			continue;
		else//!=NULL
		{
			//Fill as the AET
			Fill(pDC,AET,color,i);
			AET=DealNode(AET,i);//initial next AET
		}
		if(count>N)
			break;

	}//END FOR
}

/*=========================
//	PolyFill
//
===========================*/
//this is the fuction to fill the polygon
void Ploygon::PolyFill(CDC* pDC,POINT *PolyNode,COLORREF color)
{
	ConstructET(PolyNode,ET);

	InitialAET(AET);

	DealAET(pDC,ET,AET,color);
}

/*=========================
//	OnDrawET
//
===========================*/
void Ploygon::OnDrawET(CDC* pDC)
{
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
	pDC->TextOut(320,350,_T("活跃边表算法"));
	
	POINT points[N]={{2,3},{2,9},{7,11},{13,7},{13,1},{7,5}};
	
	POINT spt[N+1];
	int i;
	
	for(i=0;i<N+1;i++){spt[i].x=points[i%N].x*pbei;spt[i].y=points[i%N].y*pbei;}
	
	POINT points1[N];
	for(i=0;i<N;i++)
	{
		points1[i].x=spt[i].x;
		points1[i].y=spt[i].y;
	}
	
    //draw the polygon
	pDC->TextOut(spt[0].x-10,spt[0].y-5,_T("0"));
	pDC->TextOut(spt[1].x-10,spt[1].y,_T("1"));
	pDC->TextOut(spt[2].x,spt[2].y,_T("2"));
	pDC->TextOut(spt[3].x+5,spt[3].y,_T("3"));
	pDC->TextOut(spt[4].x+5,spt[4].y,_T("4"));
	pDC->TextOut(spt[5].x,spt[5].y-20,_T("5"));
	
	pDC->Polyline(spt,N+1);
	
	COLORREF color=RGB(255,118,163);
	
	CPen newpen1(PS_SOLID,2,color);
	pDC->SelectObject(&newpen1);
	//CPen *old1=pDC->SelectObject(&newpen1);
	
	PolyFill(pDC,points1,color);
	
    //pDC->SelectObject(old);
}
Ploygon::~Ploygon()
{

}
