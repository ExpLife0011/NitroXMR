#pragma once
#include "stdafx.h"

//ע��
BOOL InjectDll(PCWSTR szDllFullPath, DWORD dwRemoteProcessID);

// ����������Pid
DWORD GetProcID(TCHAR szProcName[]);

// ������ǰ����Ȩ��
int EnableDebugPriv(TCHAR szName[]);
