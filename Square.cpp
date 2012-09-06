// Square.cpp: implementation of the Square class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "Square.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Square::Square()
{
	first	=true;
}

TCHAR	szBuffer [10] ;

COLORREF color=RGB(51,102,255);
CPen newpenS(PS_SOLID,2,color);

/*=====================================*/
int Basicx=GetSystemMetrics(SM_CXSCREEN)/2; 
int Basicy=GetSystemMetrics(SM_CYSCREEN)/2;
/*=====================================*/

/*=========================
//	�Ƕ�ת��
//
===========================*/
double Square::D2R2(double deg)
{ 
	return deg / 180.0 * 3.14159265; 
} 

/*=========================
//  Ĭ�Ϲ��캯��
//
===========================*/
C3DPoint::C3DPoint()
{
    Matrix[0][0]=0;
    Matrix[0][1]=0;
    Matrix[0][2]=0;
    Matrix[0][3]=1;
}

/*=========================
//  ���캯��
//
===========================*/
C3DPoint::C3DPoint(int x, int y, int z)
{
        Matrix[0][0]=double(x);
        Matrix[0][1]=double(y);
        Matrix[0][2]=double(z);
        Matrix[0][3]=double(1);
}

/*=========================
//  ͸��
//
===========================*/
void C3DPoint::perspect(double x0,double y0,double z0)
{
	double d=-z0;
	
	double Temp1[1][4]={0,0,0,0};

	double M_b[4][4]={
		
		{1,0,0,0},
		{0,1,0,0},
		{x0/d,y0/d,0,1/d}, 
		{0,0,0,1}

	};

	MatMultiply (Matrix,1,M_b,Temp1);

	//Temp1->Matrix
    Matrix[0][0]=Temp1[0][0]/Temp1[0][3];
    Matrix[0][1]=Temp1[0][1]/Temp1[0][3];
    Matrix[0][2]=0;
	Matrix[0][3]=1;
}

/*=========================
//  ͶӰ�任
//  ������l,a
//
===========================*/
void C3DPoint::project(double l,double ct)
{
	double Temp1[1][4]={0,0,0,0};

	double M_b[4][4]={
		
		{1,0,0,0},
		{0,1,0,0},
		{l*cos(ct),l*sin(ct),0,0},
		{0,0,0,1}

	};

	MatMultiply (Matrix,1,M_b,Temp1);

	//Temp1->Matrix
    Matrix[0][0]=Temp1[0][0];
    Matrix[0][1]=Temp1[0][1];
    Matrix[0][2]=0;
	Matrix[0][3]=1;
}

/*=========================
//	��X����ת
//
===========================*/
void C3DPoint::Roat_x(double ct)
{
	double Temp1[1][4]={0,0,0,0};
	
	double M_b[4][4]={
		
		{1,0,0,0},
		{0,cos(ct),sin(ct),0},
		{0,-sin(ct),cos(ct),0},
		{0,0,0,1}
		
	};
	
	MatMultiply (Matrix,1,M_b,Temp1);
	
	//Temp1->Matrix
    Matrix[0][0]=Temp1[0][0];
    Matrix[0][1]=Temp1[0][1];
    Matrix[0][2]=Temp1[0][2];
	Matrix[0][3]=Temp1[0][3];
}

/*=========================
//	��Y����ת
//
===========================*/
void C3DPoint::Roat_y(double ct)
{
	double Temp1[1][4]={0,0,0,0};
	
	double M_b[4][4]={
		
		{cos(ct),0,-sin(ct),0},
		{0,1,0,0},
		{sin(ct),0,cos(ct),0},
		{0,0,0,1}
		
	};
	
	MatMultiply (Matrix,1,M_b,Temp1);
	
	//Temp1->Matrix
    Matrix[0][0]=Temp1[0][0];
    Matrix[0][1]=Temp1[0][1];
    Matrix[0][2]=Temp1[0][2];
	Matrix[0][3]=Temp1[0][3];
}

/*=========================
//	��Z����ת
//
===========================*/
void C3DPoint::Roat_z(double ct)
{
	double Temp1[1][4]={0,0,0,0};
	
	double M_b[4][4]={
		
		{cos(ct),sin(ct),0,0},
		{-sin(ct),cos(ct),0,0},
		{0,0,1,0},
		{0,0,0,1}
		
	};
	
	MatMultiply (Matrix,1,M_b,Temp1);
	
	//Temp1->Matrix
    Matrix[0][0]=Temp1[0][0];
    Matrix[0][1]=Temp1[0][1];
    Matrix[0][2]=Temp1[0][2];
	Matrix[0][3]=Temp1[0][3];
}

/*=========================
//��ת�任
//������int x1,y1,z1,x2,y2,z2 ��תֱ��, int ct ��ת�Ƕ�
===========================*/
void C3DPoint::Roat(int x1, int y1, int z1, int x2, int y2, int z2, double ct)
{

//��ֱ�߷�������
    double a=x2-x1;
    double b=y2-y1;
    double c=z2-z1;

    double tt=sqrt(double(a*a+b*b+c*c));

    double n1=a/tt;
    double n2=b/tt;
    double n3=c/tt;
//(n1,n2,n3)

	double v=sqrt(n2*n2+n3*n3);

	//cosa
    double c_na=n3/v;
    double c_a=c_na;

	//sina
    double s_na=n2/v;
    double s_a=-s_na;

	//cosb
    double c_nb=v;
    double c_b=c_nb;

	//sinb
    double s_nb=-n1;
    double s_b=s_nb;

	//Rx(a)
	double R_X[4][4]={
		
		{1,0,0,0},
		{0,n3/v,n2/v,0},
		{0,-n2/v,n3/v,0},
		{0,0,0,1}

	};

	//Ry(B)
    double R_Y[4][4]={

        {v,0,n1,0},
        {0,1,0,0},
        {-n1,0,v,0},
        {0,0,0,1}

    };

	//Rz(o)
    double R_Z[4][4]={
    
        {cos(ct),sin(ct),0,0},
        {-sin(ct),cos(ct),0,0},
        {0,0,1,0},
        {0,0,0,1}
    
    };

	//Ry(-B)
    double R_NY[4][4]={

        {v,0,-n1,0},
        {0,1,0,0},
        {n1,0,v,0},
        {0,0,0,1}

    };

	//Rx(-a)
    double R_NX[4][4]={

        {1,0,0,0},
        {0,n3/v,-n2/v,0},
        {0,n2/v,n3/v,0},
        {0,0,0,1}

    };


    double Temp1[1][4]={0,0,0,0};
    double Temp2[1][4]={0,0,0,0};

//ƽ�Ƶ�ԭ��
    Matrix[0][0]-=x1;
    Matrix[0][1]-=y1;
    Matrix[0][1]-=z1;
	
	MatMultiply (Matrix,1,R_X,Temp1);
	MatMultiply (Temp1,1,R_Y,Temp2);

	//backup Temp1
    Temp1[0][0]=0;
    Temp1[0][1]=0;
    Temp1[0][2]=0;
    Temp1[0][3]=0;

	MatMultiply (Temp2,1,R_Z,Temp1);

    Temp2[0][0]=0;
    Temp2[0][1]=0;
    Temp2[0][2]=0;
    Temp2[0][3]=0;

    MatMultiply (Temp1,1,R_NY,Temp2);

    Temp1[0][0]=0;
    Temp1[0][1]=0;
    Temp1[0][2]=0;
    Temp1[0][3]=0;

    MatMultiply (Temp2,1,R_NX,Temp1);

	//Temp1->Matrix
    Matrix[0][0]=Temp1[0][0];
    Matrix[0][1]=Temp1[0][1];
    Matrix[0][2]=Temp1[0][2];

//��ԭ��ƽ�ƻ�
    Matrix[0][0]+=x1;
    Matrix[0][1]+=y1;
    Matrix[0][2]+=z1;

}

/*=========================
//�����任
//������int sx x�����ϵ��, int sy y�����ϵ��
===========================*/
void C3DPoint::Resize(int ox, int oy, int oz, double sx, double sy, double sz)
{
    Matrix[0][0]-=ox;
    Matrix[0][1]-=oy;
    Matrix[0][2]-=oz;

    Matrix[0][0]*=sx;
    Matrix[0][1]*=sy;
    Matrix[0][2]*=sz;

    Matrix[0][0]+=ox;
    Matrix[0][1]+=oy;
    Matrix[0][2]+=oz;
}

/*=========================
//ƽ�Ʊ任
//������int dx x��ƫ����, int dy y��ƫ����
===========================*/
void C3DPoint::Move(int dx, int dy, int dz)
{
    Matrix[0][0]+=dx;
    Matrix[0][1]+=dy;
    Matrix[0][2]+=dz;
}


/*=========================
//	�Գ�
//
===========================*/
void C3DPoint::Symmetry(int x, int y, int z)
{
    Matrix[0][0]=2*x-Matrix[0][0];
    Matrix[0][1]=2*y-Matrix[0][1];
    Matrix[0][2]=2*y-Matrix[0][2];
}

/*=========================
//	����x����
//
===========================*/
int C3DPoint::Get_X()
{
    return int(Matrix[0][0]);
}

/*=========================
//	����y����
//
===========================*/
int C3DPoint::Get_Y()
{
    return int(Matrix[0][1]);
}

/*=========================
//	����z����
//
===========================*/
int C3DPoint::Get_Z()
{
    return int(Matrix[0][2]);
}

/*=========================
//	��������
//
===========================*/
void C3DPoint::SetPoint(int x, int y, int z)
{
    Matrix[0][0]=x;
    Matrix[0][1]=y;
    Matrix[0][2]=z;
}

/*=========================
//	��������
//
===========================*/
void Square::DrawSquare(CDC* pDC,C3DPoint *spt)
{
	ReStore();

	if (ts)//͸�ӿ���?
	{
		for(int i=0;i<8;i++)
		{
			P[i].perspect(0,0,400);
		}
	}
	
	if (ty)//ͶӰ����
	{
		for(int i=0;i<8;i++)
		{
			P[i].project(1,D2R2(45));
		}
	}

	for(int k=0;k<=3;k++)
	{
		pDC->MoveTo(Basicx+spt[k].Get_X(),Basicy+spt[k].Get_Y());
		pDC->LineTo(Basicx+spt[(k+1)%4].Get_X(),Basicy+spt[(k+1)%4].Get_Y());

		pDC->MoveTo(Basicx+spt[k].Get_X(),Basicy+spt[k].Get_Y());
		pDC->LineTo(Basicx+spt[k+4].Get_X(),Basicy+spt[k+4].Get_Y());

		pDC->MoveTo(Basicx+spt[k+4].Get_X(),Basicy+spt[k+4].Get_Y());
		pDC->LineTo(Basicx+spt[(k+1)%4+4].Get_X(),Basicy+spt[(k+1)%4+4].Get_Y());

		pDC->TextOut(Basicx+spt[k].Get_X(),Basicy+spt[k].Get_Y(),szBuffer,wsprintf (szBuffer, TEXT ("%d"),k));
		pDC->TextOut(Basicx+spt[k+4].Get_X(),Basicy+spt[k+4].Get_Y(),szBuffer,wsprintf (szBuffer, TEXT ("%d"),k+4));
	}

	Reback();
}

/*=========================
//	���¸�ֵ
//
===========================*/
void Square::Reback()
{
	for(int i=0;i<8;i++)
	{
		P[i]=Pos[i];
	}
}

/*=========================
//	�洢p[]
//
===========================*/
void Square::ReStore()
{
	for(int i=0;i<8;i++)
	{
		Pos[i]=P[i];
	}
}

/*=========================
//MatMultiply
//ay �� ax�� ��a x ax�� bx�� ��b-->c
===========================*/
void MatMultiply(double a[][4], int ah, double b[4][4], double c[][4])
{
	for(int i=0;i<ah;i++)//a hang
	{
		for(int j=0;j<4;j++)//b lie
		{
			for(int k=0;k<4;k++)//a lie
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}
/*=========================
//OnDrawSquare
//
===========================*/
void Square::OnDrawSquare(CDC* pDC)
{
	//��ʼ��
	if (first){Pos[0].SetPoint(-100,-100,-100);Pos[1].SetPoint(100,-100,-100);Pos[2].SetPoint(100,100,-100);Pos[3].SetPoint(-100,100,-100);Pos[4].SetPoint(-100,-100,100);Pos[5].SetPoint(100,-100,100);Pos[6].SetPoint(100,100,100);Pos[7].SetPoint(-100,100,100);P[0].SetPoint(-100,-100,-100);P[1].SetPoint(100,-100,-100);P[2].SetPoint(100,100,-100);P[3].SetPoint(-100,100,-100);P[4].SetPoint(-100,-100,100);P[5].SetPoint(100,-100,100);P[6].SetPoint(100,100,100);P[7].SetPoint(-100,100,100);}first=false;
	//END ��ʼ��
	
	pDC->SetTextColor(RGB(255,102,0));
	pDC->TextOut(Basicx-120,20,_T("������ı�����ƽ�ơ���ת��ͶӰ��ʾ"));
	
	pDC->SetTextColor(RGB(14,99,87));
	pDC->TextOut(50,50,_T("A:x-"));
	pDC->TextOut(50,100,_T("D:x+"));
	pDC->SetTextColor(RGB(104,9,87));
	pDC->TextOut(100,50,_T("W:Y-"));
	pDC->TextOut(100,100,_T("S:Y+"));
	pDC->SetTextColor(RGB(14,99,7));
	pDC->TextOut(150,50,_T("Q:Z-"));
	pDC->TextOut(150,100,_T("E:Z+"));
	
	pDC->SetTextColor(RGB(65,180,253));
	pDC->TextOut(50,200,_T("F:  �Ŵ�   2��"));
	pDC->TextOut(50,250,_T("G:  ��С   2��"));
	
	pDC->SetTextColor(RGB(1,191,7));
	pDC->TextOut(50,350,_T("R:͸��"));
	pDC->TextOut(50,400,_T("T:ͶӰ"));
	//////////////////////////////////
	pDC->SetTextColor(RGB(255,0,0));
	if (ts) 
	{
		pDC->TextOut(100,350,_T("�ѿ���"));
	}
	else
	{
		pDC->TextOut(100,350,_T("�ѹر�"));
	}
	if (ty) 
	{
		pDC->TextOut(100,400,_T("�ѿ���"));
	}
	else
	{
		pDC->TextOut(100,400,_T("�ѹر�"));
	}
	//////////////////////////////////
	
	pDC->SetTextColor(RGB(185,103,233));
	pDC->TextOut(50,500,_T("X  Y  Z     ������ת"));
	
	pDC->SetTextColor(RGB(0,85,234));
	pDC->TextOut(50,570,_T("V:  �ָ�����ʼ״̬"));
	
	pDC->SetTextColor(RGB(65,180,65));
	pDC->TextOut(2*Basicx-250,100,_T("ELEVEN  11.19"));
	
	pDC->SelectObject(&newpenS);
	pDC->SetTextColor(RGB(255,153,204));
	//Draw Square
	DrawSquare(pDC,P);
}

Square::~Square()
{

}
