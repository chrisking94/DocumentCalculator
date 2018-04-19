// GraduationDesign.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GD.h"
#include "stdlib.h"
#include "WmfFile.h"
#include "atlconv.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//CGD obj("C:\\Users\\Administrator.PC--20130717MTX\\Desktop\\毕业设计\\立柱设计计算\\计算过程.txt");
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
			printf("#         自动计算器          #\n");
			printf("#          By King            #\n");
			printf("#        2017年4月21日        #\n");
			printf("# 2017年5月08日:修复运算符Bug #\n");
			printf("###############################\n");
			printf("#***    将文件拖放到这里   ***#\n");
			printf("#      按[Enter]键开始计算    #\n");
			printf("###############################\n");
			gets(buffer);
			if(buffer[0] == 'q') return 0;
			CGD obj(buffer);

			printf("按回车键继续，或者按q退出。\n");
		} while (getchar()!='q');
	}
	return 0;
}

