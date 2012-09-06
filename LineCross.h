// LineCross.h: interface for the LineCross class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINECROSS_H__28D4CFB0_D4D7_4EFE_ACBB_45FAF091396F__INCLUDED_)
#define AFX_LINECROSS_H__28D4CFB0_D4D7_4EFE_ACBB_45FAF091396F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LineCross  
{
public:
	int LCSCOUNT;

	CPoint LCSP[4];

	void Cross(CDC* pDC);

	void ShowPoints(CDC* pDC,CPoint point );
	
	LineCross();
	virtual ~LineCross();
	
};

#endif // !defined(AFX_LINECROSS_H__28D4CFB0_D4D7_4EFE_ACBB_45FAF091396F__INCLUDED_)
