#include "StdAfx.h"
#include "GD.h"
#include <math.h>
#include "Exp.h"
#include <string.h>

CGD::CGD(char *szFile)
{
	fp=fopen(szFile,"r");
	char buffer[2048]={0},*pBufStart = buffer+1 ,*s = pBufStart;;
	char inBuf[256];
	strcpy(pBufStart,szFile);
	s+=strlen(pBufStart)-1;
	while(*s!='.'&&*s!='\\') s--;//回退
	if(*s=='\\')
	{
		s=pBufStart+strlen(pBufStart);
	}
	strcpy(s,"_计算结果.txt");
	FILE *fo = fopen(pBufStart,"w");

	while(!feof(fp))
	{
		//读取一行，一行不能太长（不超过 buffer size）
		s=pBufStart;
		do 
		{
			*s=fgetc(fp);
		} while (*s++!='\n'&&!feof(fp));
		*s='\0';
		s=pBufStart;
		
		while (*s)
		{
			if(*s == '=')
			{
				CExp exp(&m_vl);
				exp.Parse(s);
				fputs(exp.szVarExp,fo);
				printf("%s",exp.szVarExp);
				//exp.ToMathExp();
			}
			else if(*s == '%')
			{
				switch(*(s+1))
				{
				case '?'://请求输入 
					scanf("%s",inBuf);
					fputs(inBuf,fo);
					printf("%s",inBuf);
					s+=2;
					break;
				}
			}
			else 
			{
				printf("%c",*s);
				fputc(*s++,fo);
			}
		}
	}
	fputc(EOF,fo);
	fclose(fp);
	fclose(fo);
}


CGD::~CGD(void)
{
}