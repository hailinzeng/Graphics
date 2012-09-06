// Ploygon.h: interface for the Ploygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLOYGON_H__4189E8E2_5DB7_42FB_8D9F_8490895F01E3__INCLUDED_)
#define AFX_PLOYGON_H__4189E8E2_5DB7_42FB_8D9F_8490895F01E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*=========================*/

typedef struct//建立边表结构
{
	int		num ,ymin,ymax;
	float	xmin,xmax,dx;
}  Edge;

/*=========================*/
#define N    6

#define MAX  400

const int pbei=30;
/*================*/
typedef struct TNode
{
	int		y_max;
	float	x_min;
	float	dx;
	TNode	*next;
}TNode,*LinkList;
/*=========================*/
class Ploygon  
{
public:
	void	CoupleFill(CDC* pDC) ;
	
	//交点对填充
	void	OnDrawCouple(CDC* pDC);
	
	void	ConstructET(POINT *PolyNode,TNode *ET);
	void	InitialAET(TNode AET);
	TNode	InsetNode(TNode *pInset,TNode AET,int i);
	void	Fill(CDC* pDC,TNode AET,COLORREF color,int i);
	TNode	DealNode(TNode AET,int i);
	void	DealAET(CDC* pDC,TNode *ET,TNode AET,COLORREF color);

	void	PolyFill(CDC* pDC,POINT *PolyNode,COLORREF color);

	//活跃边表算法
	void	OnDrawET(CDC* pDC);
	
	CPoint  s_point,spt[7];
	Edge	edge[7],edge1[7],newedge[1];
	
	Ploygon();
	virtual ~Ploygon();
	
};

#endif // !defined(AFX_PLOYGON_H__4189E8E2_5DB7_42FB_8D9F_8490895F01E3__INCLUDED_)
