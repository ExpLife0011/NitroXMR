// NitroMain.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "App.h"
#include "libsysaux.h"

int main(int argc, char **argv)
{
	sysConfig();

	App minerApp(argc, argv);
    return minerApp.exec();
}

