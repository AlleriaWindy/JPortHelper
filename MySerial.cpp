// MySerial.cpp: implementation of the MySerial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testMFC.h"
#include "MySerial.h"
#include <afxtempl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MySerial::MySerial()
{
	m_hComm = INVALID_HANDLE_VALUE; 
	InitializeCriticalSection(&m_csCommunicationSync); 
}

MySerial::MySerial(CString name,int baud)
{
	this->PortNum = name;
	this->BaudRate = baud;
	m_hComm = INVALID_HANDLE_VALUE; 
	InitializeCriticalSection(&m_csCommunicationSync);
}

MySerial::~MySerial()
{
	DeleteCriticalSection(&m_csCommunicationSync);
}

bool MySerial::Open()
{

	m_hComm = CreateFileA(PortNum,  /** �豸��,COM1,COM2�� */  
        GENERIC_READ | GENERIC_WRITE, /** ����ģʽ,��ͬʱ��д */  
        0,                            /** ����ģʽ,0��ʾ������ */  
        NULL,                         /** ��ȫ������,һ��ʹ��NULL */  
        OPEN_EXISTING,                /** �ò�����ʾ�豸�������,���򴴽�ʧ�� */  
        0,  
        0);
	/** �����ʧ�ܣ��ͷ���Դ������ */  
    if (m_hComm == INVALID_HANDLE_VALUE)  
    {  
        LeaveCriticalSection(&m_csCommunicationSync);  
        return false;  
    } 
	/** �˳��ٽ��� */  
    LeaveCriticalSection(&m_csCommunicationSync);  
	
    return true;  

	return false;
}

bool MySerial::Init()
{
	/** �����ٽ�� */  
    EnterCriticalSection(&m_csCommunicationSync); 

	BOOL bIsSuccess = TRUE;

	COMMTIMEOUTS  CommTimeouts;  
    CommTimeouts.ReadIntervalTimeout = 0;  
    CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
    CommTimeouts.ReadTotalTimeoutConstant = 0;  
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;  
    CommTimeouts.WriteTotalTimeoutConstant = 0; 

	if (bIsSuccess)  
    {  
        bIsSuccess = SetCommTimeouts(m_hComm, &CommTimeouts);  
    }  

	char szDCBparam[]={"baud=9600 parity=N data=8 stop=1"};  
     
	DCB  dcb;  
    if (bIsSuccess)  
    {  
        // ��ANSI�ַ���ת��ΪUNICODE�ַ���    
        DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, NULL, 0);  
        wchar_t *pwText = new wchar_t[dwNum];  
        if (!MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, pwText, dwNum))  
        {  
            bIsSuccess = TRUE;  
        }  
		
        /** ��ȡ��ǰ�������ò���,���ҹ��촮��DCB���� */  
        bIsSuccess = GetCommState(m_hComm, &dcb) && BuildCommDCB(szDCBparam, &dcb);  
        /** ����RTS flow���� */  
        dcb.fRtsControl = RTS_CONTROL_ENABLE;  
		
        /** �ͷ��ڴ�ռ� */  
        delete[] pwText;  
    }  

if (bIsSuccess)  
{  
	/** ʹ��DCB�������ô���״̬ */  
	bIsSuccess = SetCommState(m_hComm, &dcb);  
}  

/**  ��մ��ڻ����� */  
PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);  

/** �뿪�ٽ�� */  
LeaveCriticalSection(&m_csCommunicationSync);  

    return bIsSuccess == TRUE;  
}

CString * MySerial::ListAllPorts(int &n)
{
	int i = 0; 
	CHAR Name[25]; 
	UCHAR szPortName[25]; 
	LONG Status; 
	DWORD dwIndex = 0; 
	DWORD dwName; 
	DWORD dwSizeofPortName; 
	DWORD Type;
	HKEY hKey; 
	CString *  strSerialList = new CString[256];  // ��ʱ���� 256 ���ַ����飬��Ϊϵͳ���Ҳ�� 256 �� 
	LPCTSTR data_Set="HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
	dwName = sizeof(Name); 
	dwSizeofPortName = sizeof(szPortName);
	//long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey)); 
	long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey); //��һ���ƶ���ע����,�ɹ�����ERROR_SUCCESS����0��ֵ
	if(ret0 == ERROR_SUCCESS) 
	{
		do 
		{ 
			
			Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type, szPortName, &dwSizeofPortName);//��ȡ��ֵ 
			if((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA)) 
			{ 
				strSerialList[i] = CString(szPortName);       // �����ַ������� 
				printf("serial:%s\n",strSerialList[i]);
				i++;// ���ڼ��� 
			} 
			//ÿ��ȡһ��dwName��dwSizeofPortName���ᱻ�޸� 
			//ע��һ��Ҫ����,�������ֺ�����Ĵ���,���˾��Թ���û������,�����Ȳ��봮�ںŴ�ģ���COM4��,�ٲ��봮�ں�С�ģ���COM3������ʱ���ܷ����������ڣ�������ͬһ���ںţ�COM4�������⣬ͬʱҲ������COM����10���ϵĴ��� 
			dwName = sizeof(Name); 
			dwSizeofPortName = sizeof(szPortName); 
		} while((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA)); 
		
		RegCloseKey(hKey); 
 }
	n = i;
	return strSerialList;
}

void MySerial::Close()
{
	if (m_hComm != INVALID_HANDLE_VALUE)  
    {  
        CloseHandle(m_hComm);  
        m_hComm = INVALID_HANDLE_VALUE;  
    }
}

bool MySerial::WriteData(UCHAR * pData,UINT length)
{
	BOOL   bResult = TRUE;  
    DWORD  BytesToSend = 0;  
    if (m_hComm == INVALID_HANDLE_VALUE)  
    {  
        return false;  
    }  
	
    /** �ٽ������� */  
    EnterCriticalSection(&m_csCommunicationSync);  
	
    /** �򻺳���д��ָ���������� */  
    bResult = WriteFile(m_hComm, pData, length, &BytesToSend, NULL);  
    if (!bResult)  
    {  
        DWORD dwError = GetLastError();  
        /** ��մ��ڻ����� */  
        PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_RXABORT);  
        LeaveCriticalSection(&m_csCommunicationSync);  
		
        return false;  
    }  
	
    /** �뿪�ٽ��� */  
    LeaveCriticalSection(&m_csCommunicationSync);  
	
    return true;  	
}
