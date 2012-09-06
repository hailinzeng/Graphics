// Square.h: interface for the Square class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQUARE_H__1F659CA3_291C_431D_9F5D_B7C4891B1375__INCLUDED_)
#define AFX_SQUARE_H__1F659CA3_291C_431D_9F5D_B7C4891B1375__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include<math.h>

//C3DPoint
class C3DPoint{
	
public:
    //���캯��
    //����������
    C3DPoint(int x, int y, int z);
    C3DPoint();
	
	//͸��
	void perspect(double x0,double y0,double z0);
	
	//ͶӰ
	void project(double l,double ct);
	
	//��X����ת
	void Roat_x(double ct);
	
	//��Y����ת
	void Roat_y(double ct);
	
	//��Z����ת
	void Roat_z(double ct);
	
    //��ת
    //������int x1,y1,z1,x2,y2,z2 ��תֱ��, int ct ��ת�Ƕ�
    void Roat(int x1, int y1, int z1, int x2, int y2, int z2, double ct);
	
    //�����任
    //������int sx x�����ϵ��, int sy y�����ϵ��
    void Resize(int ox, int oy, int oz, double sx, double sy, double sz);
	
    //ƽ��
    //������int dx x��ƫ����, int dy y��ƫ����
    void Move(int dx, int dy, int dz);
	
    //�Գ�
    void Symmetry(int x, int y, int z);
	
    //����x����
    int Get_X();
	
    //����y����
    int Get_Y();
	
    //����z����
    int Get_Z();
	
    //��������
    void SetPoint(int x, int y, int z);
	
private:
    //��ά��ľ���
    double Matrix[1][4];
	
};
//������˺���
void MatMultiply(double a[][4], int ah, double b[4][4], double c[][4]);
//���¸�ֵ
void Reback();
//�洢p[]
void ReStore();

class Square  
{
public:
	
	int ty,ts,me,first;
	C3DPoint P[8],Pos[8];
	
	double D2R2(double deg);
	void DrawSquare(CDC* pDC,C3DPoint *spt);
	
	void Reback();
	void ReStore();
	
	void OnDrawSquare(CDC* pDC);
	
	Square();
	virtual ~Square();
	
};

#endif // !defined(AFX_SQUARE_H__1F659CA3_291C_431D_9F5D_B7C4891B1375__INCLUDED_)
