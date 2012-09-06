// Graphics.h : main header file for the GRAPHICS application
//

#if !defined(AFX_GRAPHICS_H__6EED0594_0AA1_4919_8DF7_72DF08A5AB0C__INCLUDED_)
#define AFX_GRAPHICS_H__6EED0594_0AA1_4919_8DF7_72DF08A5AB0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphicsApp:
// See Graphics.cpp for the implementation of this class
//

class CGraphicsApp : public CWinApp
{
public:
	CGraphicsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphicsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICS_H__6EED0594_0AA1_4919_8DF7_72DF08A5AB0C__INCLUDED_)
