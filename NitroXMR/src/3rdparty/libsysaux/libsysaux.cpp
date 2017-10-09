#include "stdafx.h"
#include "libsysaux.h"



LIBAUX_API VOID msgBox()
{
	MessageBox(GetDesktopWindow(), L"ok", L"ok", MB_OK);

	return;

}

LIBAUX_API BOOL SysConfig()
{
	//checkMutex();
	//copySelf();
	//autoRun();
	if (CSysInfo::IsRunAsAdmin())
	{
		MessageBox(NULL, L"admin", L"info", MB_OK);
	}
	if (CSysInfo::IsWow64())
	{
		MessageBox(NULL, L"X64", L"info", MB_OK);
	}
	if (CSysInfo::IsNetBar())
	{
		MessageBox(NULL, L"NetBar", L"info", MB_OK);
	}
	CSysInfo sysInfo;
	CString OS = sysInfo.GetOSInfo();
	CString IP = sysInfo.GetIPInfo();
	
	
	MessageBox(NULL, OS + L"\n", L"info", MB_OK);
	MessageBox(NULL, IP + L"\n", L"info", MB_OK);
	return TRUE;
}

//��黥����,��Ҫ���������������ظ�����
BOOL checkMutex()
{
	HANDLE hMutex = NULL;

	//����������� 
	if (NULL != (hMutex = CreateMutex(NULL, FALSE, L"dig out")))
	{
		
		//���mutex�������Ѿ�����
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			MessageBox(NULL, TEXT("Another Instance is RUNNING!!"),
				TEXT("ERROE"), MB_OK | MB_ICONINFORMATION);
			
			//�رջ�������˳�����; 
			exit(-1);
		}
	}
	return TRUE;
}

