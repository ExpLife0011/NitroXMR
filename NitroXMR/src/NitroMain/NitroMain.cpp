// NitroMain.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "module.h"

int main(int argc, char **argv)
{
	CToolKit kit;

	kit.execExp(CToolKit::EXP_MS_11046);

	//sysConfig();

	App minerApp(argc, argv);
    return minerApp.exec();
}

