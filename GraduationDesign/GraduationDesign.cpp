// GraduationDesign.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GD.h"
#include "stdlib.h"
#include "WmfFile.h"
#include "atlconv.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//CGD obj("C:\\Users\\Administrator.PC--20130717MTX\\Desktop\\��ҵ���\\������Ƽ���\\�������.txt");
	//CWmfFile wmf("C:\\Users\\Administrator.PC--20130717MTX\\Desktop\\123.wmf");
	//wmf.Parse();
	
	//obj.go();
	CVar::Initialize();
	CGD obj("C:\\Users\\Administrator.PC--20130717MTX\\Desktop\\choosed.txt");
	//return 0;
	//if(argc == 1)
	{
		char buffer[1024];
		USES_CONVERSION;
		if(argc==2) strcpy(buffer,T2A(argv[1]));
		do 
		{
			printf("###############################\n");
			printf("#         �Զ�������          #\n");
			printf("#          By King            #\n");
			printf("#        2017��4��21��        #\n");
			printf("# 2017��5��08��:�޸������Bug #\n");
			printf("###############################\n");
			printf("#***    ���ļ��Ϸŵ�����   ***#\n");
			printf("#      ��[Enter]����ʼ����    #\n");
			printf("###############################\n");
			gets(buffer);
			if(buffer[0] == 'q') return 0;
			CGD obj(buffer);

			printf("���س������������߰�q�˳���\n");
		} while (getchar()!='q');
	}
	return 0;
}

