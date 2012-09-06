// GraphicsView.h : interface of the CGraphicsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSVIEW_H__DC8C1D44_1E45_4838_891B_5F61A4EA7777__INCLUDED_)
#define AFX_GRAPHICSVIEW_H__DC8C1D44_1E45_4838_891B_5F61A4EA7777__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicsView : public CView
{
protected: // create from serialization only
	CGraphicsView();
	DECLARE_DYNCREATE(CGraphicsView)

// Attributes
public:
	CGraphicsDoc* GetDocument();

	void OnTimer(UINT_PTR nIDEvent);

// Operations
public:
	void MyInfomation(CDC* pDC);

	afx_msg void ShowMySelf();

	afx_msg void DrawLineMain();

	afx_msg void DrawCircleMain();
	
	afx_msg void DrawFillMain();

	afx_msg void DrawCoupleMain();
	afx_msg void DrawETMain();

	afx_msg void DrawPlanarMain();

	afx_msg void DrawSquareMain();

	afx_msg void DrawLineCutCMain();
	afx_msg void DrawLineCutLMain();

	afx_msg void DrawLagrangeMain();
	afx_msg void DrawHermiteMain();

	afx_msg void DrawBezierLMain();
	afx_msg void DrawBezierLDecasMain();
	afx_msg void DrawBezierLSplitMain();
	
	afx_msg void DrawBezierMMain();

	afx_msg void DrawCoonsMain();

	afx_msg void DrawBcurveLMain();
	afx_msg void DrawBcurveMMain();

	afx_msg void DrawLineCrossMain();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphicsView.cpp
inline CGraphicsDoc* CGraphicsView::GetDocument()
   { return (CGraphicsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSVIEW_H__DC8C1D44_1E45_4838_891B_5F61A4EA7777__INCLUDED_)
