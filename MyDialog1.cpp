// MyDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "testMFC.h"
#include "MyDialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyDialog1 dialog


MyDialog1::MyDialog1(CWnd* pParent /*=NULL*/)
	: CDialog(MyDialog1::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyDialog1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyDialog1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyDialog1, CDialog)
	//{{AFX_MSG_MAP(MyDialog1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyDialog1 message handlers
