// GraphicsDoc.h : interface of the CGraphicsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSDOC_H__43E0169F_C0C3_46BC_8ABD_6D5A05636D29__INCLUDED_)
#define AFX_GRAPHICSDOC_H__43E0169F_C0C3_46BC_8ABD_6D5A05636D29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicsDoc : public CDocument
{
protected: // create from serialization only
	CGraphicsDoc();
	DECLARE_DYNCREATE(CGraphicsDoc)

// Attributes
public:
	CBitmap m_Bitmap;		//位图对象
	int		m_nWidth;		//存储位图宽的数据成员
	int		m_nHeight;		//存储位图高的数据成员
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSDOC_H__43E0169F_C0C3_46BC_8ABD_6D5A05636D29__INCLUDED_)
