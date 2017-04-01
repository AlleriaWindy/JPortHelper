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

	m_hComm = CreateFileA(PortNum,  /** 设备名,COM1,COM2等 */  
        GENERIC_READ | GENERIC_WRITE, /** 访问模式,可同时读写 */  
        0,                            /** 共享模式,0表示不共享 */  
        NULL,                         /** 安全性设置,一般使用NULL */  
        OPEN_EXISTING,                /** 该参数表示设备必须存在,否则创建失败 */  
        0,  
        0);
	/** 如果打开失败，释放资源并返回 */  
    if (m_hComm == INVALID_HANDLE_VALUE)  
    {  
        LeaveCriticalSection(&m_csCommunicationSync);  
        return false;  
    } 
	/** 退出临界区 */  
    LeaveCriticalSection(&m_csCommunicationSync);  
	
    return true;  

	return false;
}

bool MySerial::Init()
{
	/** 进入临界段 */  
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
        // 将ANSI字符串转换为UNICODE字符串    
        DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, NULL, 0);  
        wchar_t *pwText = new wchar_t[dwNum];  
        if (!MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, pwText, dwNum))  
        {  
            bIsSuccess = TRUE;  
        }  
		
        /** 获取当前串口配置参数,并且构造串口DCB参数 */  
        bIsSuccess = GetCommState(m_hComm, &dcb) && BuildCommDCB(szDCBparam, &dcb);  
        /** 开启RTS flow控制 */  
        dcb.fRtsControl = RTS_CONTROL_ENABLE;  
		
        /** 释放内存空间 */  
        delete[] pwText;  
    }  

if (bIsSuccess)  
{  
	/** 使用DCB参数配置串口状态 */  
	bIsSuccess = SetCommState(m_hComm, &dcb);  
}  

/**  清空串口缓冲区 */  
PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);  

/** 离开临界段 */  
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
	CString *  strSerialList = new CString[256];  // 临时定义 256 个字符串组，因为系统最多也就 256 个 
	LPCTSTR data_Set="HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
	dwName = sizeof(Name); 
	dwSizeofPortName = sizeof(szPortName);
	//long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey)); 
	long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey); //打开一个制定的注册表键,成功返回ERROR_SUCCESS即“0”值
	if(ret0 == ERROR_SUCCESS) 
	{
		do 
		{ 
			
			Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type, szPortName, &dwSizeofPortName);//读取键值 
			if((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA)) 
			{ 
				strSerialList[i] = CString(szPortName);       // 串口字符串保存 
				printf("serial:%s\n",strSerialList[i]);
				i++;// 串口计数 
			} 
			//每读取一次dwName和dwSizeofPortName都会被修改 
			//注意一定要重置,否则会出现很离奇的错误,本人就试过因没有重置,出现先插入串口号大的（如COM4）,再插入串口号小的（如COM3），此时虽能发现两个串口，但都是同一串口号（COM4）的问题，同时也读不了COM大于10以上的串口 
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
	
    /** 临界区保护 */  
    EnterCriticalSection(&m_csCommunicationSync);  
	
    /** 向缓冲区写入指定量的数据 */  
    bResult = WriteFile(m_hComm, pData, length, &BytesToSend, NULL);  
    if (!bResult)  
    {  
        DWORD dwError = GetLastError();  
        /** 清空串口缓冲区 */  
        PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_RXABORT);  
        LeaveCriticalSection(&m_csCommunicationSync);  
		
        return false;  
    }  
	
    /** 离开临界区 */  
    LeaveCriticalSection(&m_csCommunicationSync);  
	
    return true;  	
}
