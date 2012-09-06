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
    //构造函数
    //参数：坐标
    C3DPoint(int x, int y, int z);
    C3DPoint();
	
	//透视
	void perspect(double x0,double y0,double z0);
	
	//投影
	void project(double l,double ct);
	
	//绕X轴旋转
	void Roat_x(double ct);
	
	//绕Y轴旋转
	void Roat_y(double ct);
	
	//绕Z轴旋转
	void Roat_z(double ct);
	
    //旋转
    //参数：int x1,y1,z1,x2,y2,z2 旋转直线, int ct 旋转角度
    void Roat(int x1, int y1, int z1, int x2, int y2, int z2, double ct);
	
    //比例变换
    //参数：int sx x轴比例系数, int sy y轴比例系数
    void Resize(int ox, int oy, int oz, double sx, double sy, double sz);
	
    //平移
    //参数：int dx x轴偏移量, int dy y轴偏移量
    void Move(int dx, int dy, int dz);
	
    //对称
    void Symmetry(int x, int y, int z);
	
    //返回x坐标
    int Get_X();
	
    //返回y坐标
    int Get_Y();
	
    //返回z坐标
    int Get_Z();
	
    //设置坐标
    void SetPoint(int x, int y, int z);
	
private:
    //三维点的矩阵
    double Matrix[1][4];
	
};
//矩阵相乘函数
void MatMultiply(double a[][4], int ah, double b[4][4], double c[][4]);
//重新赋值
void Reback();
//存储p[]
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
