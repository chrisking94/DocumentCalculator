#include "StdAfx.h"
#include "WmfFile.h"
#include "Common.h"
#include <string>

CWmfFile::CWmfFile(char *szFilePath)
{
	_strcpy(m_szFilePath,szFilePath);
}


CWmfFile::~CWmfFile(void)
{
}

void CWmfFile::Parse()
{
	FILE *fp ;
	DWORD nWords = 0 ,nTotal;
	WmfRcrdNode *pRcrd;
	
	fp = fopen(m_szFilePath,"rb");
	ReadStruct("ittttttit",&m_Position,fp);//读取位置头
	if(!m_Position.IsLegal())//没有位置头
	{
		fseek(fp,0,SEEK_SET);
	}
	//读取文件头
	nWords += ReadStruct("tttitti",&m_Header,fp)>>1;
	//读取事件
	pRcrd = &m_RcrdHead;
	for(;;)
	{
		pRcrd->next = new WmfRcrdNode;
		pRcrd = pRcrd->next;
		ReadStruct("it",pRcrd,fp);
		_fread(pRcrd->pData,2,pRcrd->dwRcrdWordsCnt-3,fp);
		nWords += pRcrd->dwRcrdWordsCnt;
		if(pRcrd->wGDIFunction == 0 || nWords>=m_Header.dwFileLength)//结尾
		{
			pRcrd->next = 0;
			break;
		}
	}

	fclose(fp);
	m_szFilePath[strlen(m_szFilePath)-5] = '@';
	fp = fopen(m_szFilePath , "wb+");
	m_Header.WriteToFile(fp);
	m_RcrdHead.WriteToFile(fp);
	fclose(fp);
}
