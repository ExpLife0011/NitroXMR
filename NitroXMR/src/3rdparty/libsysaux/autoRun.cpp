#include "stdafx.h"
#include "autoRun.h"

// executePath


LIBAUX_API BOOL autoRun()
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
	}

	return TRUE;
}