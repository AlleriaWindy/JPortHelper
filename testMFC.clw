; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestMFCDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "testMFC.h"

ClassCount=4
Class1=CTestMFCApp
Class2=CTestMFCDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_TESTMFC_DIALOG
Class3=IDD_DIALOG1
Class4=MyDialog1
Resource3=IDD_second

[CLS:CTestMFCApp]
Type=0
HeaderFile=testMFC.h
ImplementationFile=testMFC.cpp
Filter=N

[CLS:CTestMFCDlg]
Type=0
HeaderFile=testMFCDlg.h
ImplementationFile=testMFCDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1



[DLG:IDD_TESTMFC_DIALOG]
Type=1
Class=CTestMFCDlg
ControlCount=5
Control1=IDC_BUTTON1,button,1342242816
Control2=MyList1,listbox,1352728833
Control3=btn_play,button,1342242816
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_BUTTON2,button,1342242816

[CLS:IDD_DIALOG1]
Type=0
HeaderFile=IDD_DIALOG1.h
ImplementationFile=IDD_DIALOG1.cpp
BaseClass=CDialog
Filter=D
LastObject=IDD_DIALOG1

[DLG:IDD_second]
Type=1
Class=MyDialog1
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:MyDialog1]
Type=0
HeaderFile=MyDialog1.h
ImplementationFile=MyDialog1.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL

