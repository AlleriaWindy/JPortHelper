#if !defined(AFX_MYDIALOG1_H__433527A1_01A9_4E5E_A6D2_5F85929DFE70__INCLUDED_)
#define AFX_MYDIALOG1_H__433527A1_01A9_4E5E_A6D2_5F85929DFE70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyDialog1 dialog

class MyDialog1 : public CDialog
{
// Construction
public:
	MyDialog1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MyDialog1)
	enum { IDD = IDD_second };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyDialog1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyDialog1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOG1_H__433527A1_01A9_4E5E_A6D2_5F85929DFE70__INCLUDED_)
