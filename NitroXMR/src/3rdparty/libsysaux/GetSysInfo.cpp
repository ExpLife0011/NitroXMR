#include "stdafx.h"
#include "GetSysInfo.h"

CString CSysInfo::GetOSInfo()
{
	SYSTEM_INFO info;        //��SYSTEM_INFO�ṹ�ж�64λAMD������   
	GetSystemInfo(&info);    //����GetSystemInfo�������ṹ   
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	CString osname = "unknown OperatingSystem.";

	if (GetVersionEx((OSVERSIONINFO *)&os))
	{
		//������ݰ汾��Ϣ�жϲ���ϵͳ����   
		switch (os.dwMajorVersion)//�ж����汾��  
		{
		case 4:
			switch (os.dwMinorVersion)//�жϴΰ汾��   
			{
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					osname = "Microsoft Windows NT 4.0"; //1996��7�·���   
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					osname = "Microsoft Windows 95";
				break;
			case 10:
				osname = "Microsoft Windows 98";
				break;
			case 90:
				osname = "Microsoft Windows Me";
				break;
			}
			break;

		case 5:
			switch (os.dwMinorVersion)   //�ٱȽ�dwMinorVersion��ֵ  
			{
			case 0:
				osname = "Microsoft Windows 2000";//1999��12�·���  
				break;

			case 1:
				osname = "Microsoft Windows XP";//2001��8�·���  
				break;

			case 2:
				if (os.wProductType == VER_NT_WORKSTATION
					&& info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
				{
					osname = "Microsoft Windows XP Professional x64 Edition";
				}
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					osname = "Microsoft Windows Server 2003";//2003��3�·���   
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
					osname = "Microsoft Windows Server 2003 R2";
				break;
			}
			break;

		case 6:
			switch (os.dwMinorVersion)
			{
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					osname = "Microsoft Windows Vista";
				else
					osname = "Microsoft Windows Server 2008";//�������汾   
				break;
			case 1:
				if (os.wProductType == VER_NT_WORKSTATION)
					osname = "Microsoft Windows 7";
				else
					osname = "Microsoft Windows Server 2008 R2";
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION)
				{
					if (IsWindows10OrGreater())
					{
						osname = "Microsoft Windows 10";
					}//����ʹ���º�������Ƿ�Ϊ win10 
					else
					{
						osname = "Microsoft Windows 8";
					}
				}
				else
				{
					osname = "Microsoft Windows Server 2012";
				}
				break;
			case 3:
				if (os.wProductType == VER_NT_WORKSTATION)
					osname = "Microsoft Windows 8.1";
				else
					osname = "Microsoft Windows Server 2012 R2";
				break;
			}
			break;

		case 10:
			switch (os.dwMinorVersion)
			{
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					osname = "Microsoft Windows 10";
				else
					osname = "Microsoft Windows Server 2016 Technical Preview";//�������汾   
				break;
			}
			break;
		}
	}//if(GetVersionEx((OSVERSIONINFO *)&os))  
	 //https://msdn.microsoft.com/en-us/library/ms724832.aspx  
	
	m_OSstring = osname;
	wprintf("[*] Current Windows Version : " + m_OSstring + "\n");
	return osname;
}

CString CSysInfo::GetIPInfo()
{
	m_IPstring.Empty();
	CString invalidIP("Invalid IP Address");

	//1.��ʼ��wsa  
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret == 0)
	{
		//2.��ȡ������  
		char hostname[256];
		ret = gethostname(hostname, sizeof(hostname));
		if (ret == SOCKET_ERROR)
		{
			printf("error with return %d\n", ret);
			return invalidIP;
		}
		printf("%s\n", hostname);
		//3.��ȡ����ip  
		HOSTENT* host = gethostbyname(hostname);
		if (host == NULL)
		{
			printf("error with return %d\n", ret);
			return invalidIP;
		}
		//4.ת��Ϊchar*����������  
		char ip[32] = {'\0'};
		TCHAR wip[32] ;
		strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));

		mbstowcs(wip, ip, strlen(ip)+1);

		m_IPstring.Append(wip);
		wprintf("[*] Current IP Address : " + m_IPstring + "\n");

		return m_IPstring;
	}
	wprintf("[*] Get IP Failed! : " + invalidIP + "\n");

	return invalidIP;
}

CString CSysInfo::GetCPUInfo()
{
	return CString();
}

CString CSysInfo::GetMACInfo()
{
	return "";
}

BOOL CSysInfo::IsNetBar()
{

	char* NetRoomKey[] =
	{
		"SOFTWARE\\Hintsoft\\PubwinClient",
		"SOFTWARE\\Hintsoft\\pubwin",
		"SOFTWARE\\Sicent\\wx2004Clt",
		"SOFTWARE\\MpSoft\\smenu",
		"SOFTWARE\\Microsoft\\jingzu",
		"SOFTWARE\\iCafe8",
		"SOFTWARE\\Goyoo\\i8desk",
		"SOFTWARE\\Hintsoft1\\XunShanPro",
		"SOFTWARE\\SyncExpertNetBar",
		"SOFTWARE\\EYOOCLIENTSTATUS",
		"SOFTWARE\\Richtech",
		"SOFTWARE\\\u676d\u5dde\u987a\u7f51\u4fe1\u606f\u6280\u672f\u6709\u9650\u516c\u53f8\\\u7f51\u7ef4\u5927\u5e08\u874c\u86aa\u5a31\u4e50\u5e73\u53f0",
		"SOFTWARE\\iCafe8",
		"SOFTWARE\\Sicent\\wx2004Clt",
		"SOFTWARE\\Sicent\\WxAdv",
		"SOFTWARE\\Grabsun\\Netsense",
	};

	HKEY subKey[sizeof(NetRoomKey)/sizeof(char*)];

	for (int i = 0; i < sizeof(NetRoomKey) / sizeof(char*); i++)
	{
		//�򿪲����������Ӽ� ,�������һ�������ɿ�
		//�޸�����ֵbug
		if (ERROR_SUCCESS == RegOpenKeyA(HKEY_LOCAL_MACHINE, NetRoomKey[i], &subKey[i]))
		{
			printf("[*] IS NetBar : YES\n");

			return TRUE;
			break;
		}
	}

	for (int i = 0; i < sizeof(NetRoomKey) / sizeof(char*); i++)
	{
		RegCloseKey(subKey[i]);
	}
	
	printf("[*] IS NetBar : NO\n");
	return FALSE;
}

BOOL CSysInfo::IsRunAsAdmin()
{
	BOOL bElevated = FALSE;
	HANDLE hToken = NULL;

	// �򿪵�ǰ�û�����
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		return FALSE;

	TOKEN_ELEVATION tokenEle;
	DWORD dwRetLen = 0;

	// ȡ���û�����������Ϣ
	if (GetTokenInformation(hToken, TokenElevation, &tokenEle, sizeof(tokenEle), &dwRetLen))
	{
		if (dwRetLen == sizeof(tokenEle))
		{
			bElevated = tokenEle.TokenIsElevated;
			//�Ƿ�ΪAdmin
		}
	}
	CloseHandle(hToken);
	
	return bElevated;
}

BOOL CSysInfo::IsWow64()
{
	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;

	//IsWow64Process is not available on all supported versions of Windows.    
	//Use GetModuleHandle to get a handle to the DLL that contains the function    
	//and GetProcAddress to get a pointer to the function if available.    

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			//handle error    
		}
	}
	return bIsWow64;
}





