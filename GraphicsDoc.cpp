// GraphicsDoc.cpp : implementation of the CGraphicsDoc class
//

#include "stdafx.h"
#include "Graphics.h"

#include "GraphicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc

IMPLEMENT_DYNCREATE(CGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc construction/destruction

CGraphicsDoc::CGraphicsDoc()
{
	// TODO: add one-time construction code here
	BITMAP BM;
	m_Bitmap.LoadBitmap(IDB_JAY);
	m_Bitmap.GetBitmap(&BM);
	m_nWidth=BM.bmWidth;
	m_nHeight=BM.bmHeight;
}

CGraphicsDoc::~CGraphicsDoc()
{
}

BOOL CGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc serialization

void CGraphicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc diagnostics

#ifdef _DEBUG
void CGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc commands
