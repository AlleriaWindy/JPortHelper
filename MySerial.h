// MySerial.h: interface for the MySerial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSERIAL_H__DB949795_5287_4367_B9E5_7ED0BCC4A6C4__INCLUDED_)
#define AFX_MYSERIAL_H__DB949795_5287_4367_B9E5_7ED0BCC4A6C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class MySerial  
{
public:
	MySerial();
	MySerial(CString name,int baud);
	virtual ~MySerial();
	/*My Members*/
	CString PortNum;
	int BaudRate;
	/*My Functions*/
	bool Open();
	void Close();
	bool Init();
	bool WriteData(UCHAR * pData,UINT length);
	static CString * ListAllPorts(int &n);
private:
	bool _openning;
	bool _poolling;
	CRITICAL_SECTION   m_csCommunicationSync;
	HANDLE m_hComm;
};

#endif // !defined(AFX_MYSERIAL_H__DB949795_5287_4367_B9E5_7ED0BCC4A6C4__INCLUDED_)



