#include "stdafx.h"
#include "ToolKit.h"


CToolKit::CToolKit()
{

	

}


CToolKit::~CToolKit()
{

}

BOOL CToolKit::IsAdmin()
{
	bAdmin = CSysInfo::IsRunAsAdmin();
	return bAdmin;
}


int CToolKit::execExp(int order)
{	

	int ret = (this->*funcList[order])();
	return ret;
}

//�����EXP ���ж���
LPFUNC CToolKit::funcList[16] = {
	&CToolKit::exp_ms_11046,
};

