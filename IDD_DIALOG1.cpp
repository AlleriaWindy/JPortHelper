// IDD_DIALOG1.cpp : implementation file
//

#include "stdafx.h"
#include "testMFC.h"
#include "IDD_DIALOG1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IDD_DIALOG1 dialog


IDD_DIALOG1::IDD_DIALOG1(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1::IDD, pParent)
{
	//{{AFX_DATA_INIT(IDD_DIALOG1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void IDD_DIALOG1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IDD_DIALOG1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IDD_DIALOG1, CDialog)
	//{{AFX_MSG_MAP(IDD_DIALOG1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IDD_DIALOG1 message handlers
