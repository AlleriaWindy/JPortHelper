// testMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testMFC.h"
#include "testMFCDlg.h"
#include "MyDialog1.h"
#include "MySerial.h"

#define MusicOffset 0


#define MUSIC_LEN_test 15
const UINT16 Music_Table_test [MUSIC_LEN_test] = { 
	0x4184 , 0x4284 , 0x4384 , 0x4484 , 0x4584 , 0x4684 , 0x4784 , 0x4084 , 0x4784 , 0x4684 ,
		0x4584 , 0x4484 , 0x4384 , 0x4284 , 0x4184 ,
};


#define MUSIC_LEN1 128
const UINT16 Music_Table1 [MUSIC_LEN1] = { 
 0x3384 , 0x4080 , 0x3384 , 0x3484 , 0x3584 , 0x4080 , 0x3584 , 0x3484 , 0x3384 , 0x3284 ,
 0x3184 , 0x4080 , 0x3184 , 0x3284 , 0x3384 , 0x4080 , 0x3385 , 0x3283 , 0x4080 , 0x3286 ,
 0x3384 , 0x4080 , 0x3384 , 0x3484 , 0x3584 , 0x4080 , 0x3584 , 0x3484 , 0x3384 , 0x3284 ,
 0x3184 , 0x4080 , 0x3184 , 0x3284 , 0x3384 , 0x4080 , 0x3285 , 0x3183 , 0x4080 , 0x3186 ,
 0x3284 , 0x4080 , 0x3284 , 0x3384 , 0x3184 , 0x4080 , 0x3284 , 0x3383 , 0x3483 , 0x3384 ,
 0x3184 , 0x3284 , 0x3383 , 0x3483 , 0x3384 , 0x3284 , 0x3184 , 0x3284 , 0x2584 , 0x3386 ,
 0x4080 , 0x3384 , 0x3484 , 0x3584 , 0x4080 , 0x3584 , 0x3484 , 0x3384 , 0x3284 , 0x3184 ,
 0x4080 , 0x3184 , 0x3284 , 0x3384 , 0x4080 , 0x3285 , 0x3183 , 0x4080 , 0x3186 , 0x3284 ,
 0x4080 , 0x3284 , 0x3384 , 0x3184 , 0x4080 , 0x3284 , 0x3383 , 0x3483 , 0x3384 , 0x3184 ,
 0x3284 , 0x3383 , 0x3483 , 0x3384 , 0x3284 , 0x3184 , 0x3284 , 0x2584 , 0x3386 , 0x4080 ,
 0x3384 , 0x3484 , 0x3584 , 0x4080 , 0x3584 , 0x3484 , 0x3384 , 0x3284 , 0x3184 , 0x4080 ,
 0x3184 , 0x3284 , 0x3384 , 0x4080 , 0x3385 , 0x3183 , 0x4080 , 0x3186 , 0x4083 , 0x4083 ,
 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 ,
};








#define MUSIC_LEN2 185
const UINT16 Music_Table2 [MUSIC_LEN2] = { 
 0x3285 , 0x3485 , 0x3684 , 0x3585 , 0x3385 , 0x3184 , 0x3285 , 0x3485 , 0x3684 , 0x4185 ,
 0x3585 , 0x3384 , 0x3285 , 0x3485 , 0x3684 , 0x3585 , 0x3385 , 0x3184 , 0x3287 , 0x4083 ,
 0x4083 , 0x4083 , 0x4083 , 0x3485 , 0x4083 , 0x3484 , 0x3383 , 0x3583 , 0x3484 , 0x3384 ,
 0x3183 , 0x3284 , 0x3083 , 0xB185 , 0x4083 , 0x3684 , 0xB583 , 0x3783 , 0x3684 , 0xB584 ,
 0x3383 , 0xB485 , 0x3485 , 0x4083 , 0x3484 , 0x3383 , 0x3583 , 0x3484 , 0x3384 , 0x3183 ,
 0x3284 , 0x3083 , 0xB185 , 0x4083 , 0x3684 , 0xB583 , 0x3783 , 0x3684 , 0xB584 , 0x3383 ,
 0xB485 , 0x4083 , 0x3483 , 0x2683 , 0x3483 , 0xB183 , 0x3383 , 0xB183 , 0x3582 , 0x3682 ,
 0x3484 , 0x3584 , 0x3683 , 0x3583 , 0x3483 , 0x3384 , 0x4080 , 0x3483 , 0x2683 , 0x3483 ,
 0x3383 , 0x3483 , 0x3383 , 0x3183 , 0x2784 , 0xB184 , 0x3284 , 0x3384 , 0x4080 , 0x3483 ,
 0x2683 , 0x3483 , 0xB183 , 0x3383 , 0xB183 , 0x3582 , 0x3682 , 0x3484 , 0x3584 , 0x3683 ,
 0x3583 , 0x3483 , 0x3384 , 0x4080 , 0x3483 , 0x2683 , 0x3483 , 0x3383 , 0x3483 , 0x3383 ,
 0x3183 , 0x2784 , 0xB184 , 0x3284 , 0x3384 , 0xB486 , 0x4083 , 0x4083 , 0x4083 , 0x3285 ,
 0x3485 , 0x3684 , 0x3585 , 0x3385 , 0x3184 , 0x3285 , 0x3485 , 0x3684 , 0x4185 , 0x3585 ,
 0x3384 , 0x3285 , 0x3485 , 0x3684 , 0x3585 , 0x3385 , 0x3184 , 0x3286 , 0x4083 , 0x3283 ,
 0x3383 , 0x3484 , 0x3384 , 0x3484 , 0x3584 , 0x4080 , 0x3285 , 0x3485 , 0x3684 , 0x3585 ,
 0x3385 , 0x3184 , 0x3285 , 0x3485 , 0x3684 , 0x4185 , 0x3585 , 0x3384 , 0x3285 , 0x3485 ,
 0x3684 , 0x3585 , 0x3385 , 0x3184 , 0x3286 , 0x3084 , 0x3285 , 0x3485 , 0x3684 , 0x3585 ,
 0x3385 , 0x3184 , 0x3288 , 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 ,
 0x4083 , 0x4083 , 0x4083 , 0x4083 , 0x4083 ,
};

/*
2-4-65-3-12-4-6[1]-5-32-4-65-3-12---||||
4- | 43/5/431/2 0/
#1- | 6 #5/7/ 6 #5 3/ #4-
4- | 43/5/431/2 0/
#1- | 6 #5/7/ 6 #5 3/ #4-|
4/(6)/4/ #1/3/#1/5//6//  456/5/4/3*
4/(6)/4/ 3/4/3/1/(7)#123*
4/(6)/4/ #1/3/#1/5//6// 456/5/4/3*
4/(6)/4/ 3/4/3/1/(7)#123#4--|||

  2-4-65-3-12-4-6[1]-5-32-4-65-3-12--| 2/3/4345*
  2-4-65-3-12-4-6[1]-5-32-4-65-3-12--0 2-4-65-3-12----
  
	||||||||||||
==========
  */

#define MUSIC_LEN 49
const UINT16 Music_Table [MUSIC_LEN] = { 
	0xB384 , 0x3584 , 0xB586 , 0xB384 , 0xB584 , 0xB784 , 0xB684 , 0xB584 , 0x3584 , 0xB285 ,
		0xB685 , 0xB785 , 0xB586 , 0x3484 , 0x3584 , 0xB584 , 0xB184 , 0xB184 , 0x3584 , 0xB584 ,
		0xB684 , 0xB584 , 0x3584 , 0xB284 , 0xC185 , 0xB785 , 0xB684 , 0x3584 , 0xB586 , 0xB186 ,
		0xB384 , 0xB584 , 0xB784 , 0xB684 , 0xB584 , 0x3586 , 0xB285 , 0xB685 , 0x3585 , 0xB585 ,
		0xB584 , 0xB684 , 0xB785 , 0xB685 , 0xB585 , 0x3585 , 0x3485 , 0xB285 , 0x3485 ,
};




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMFCDlg dialog

CTestMFCDlg::CTestMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestMFCDlg)
	m_edit1_val = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestMFCDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit1_val);
	DDV_MinMaxUInt(pDX, m_edit1_val, 0, 20000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CTestMFCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_LBN_SELCHANGE(MyList1, OnSelchangeList1)
	ON_BN_CLICKED(btn_play, Onplay)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMFCDlg message handlers

BOOL CTestMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	player = NULL;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CTestMFCDlg::OnButton1() 
{
	
	
	
}

void CTestMFCDlg::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	
}

void CTestMFCDlg::Onplay() 
{
	// TODO: Add your control notification handler code here
	if(player)
	{
		delete player;
		player = 0;
	}
	this->player = new MyMusicPlay(0.55F,Music_Table1 + MusicOffset,MUSIC_LEN1 - MusicOffset,2300);
	this->player->OpenSoundCard();

	
	
	
}

void CTestMFCDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//delete player;
	
	CDialog::OnClose();
}

void CTestMFCDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(1);

	
}

void CTestMFCDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if(player)
	{
		delete player;
		player = 0;
	}
	
}
