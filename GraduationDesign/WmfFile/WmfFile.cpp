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
	ReadStruct("ittttttit",&m_Position,fp);//��ȡλ��ͷ
	if(!m_Position.IsLegal())//û��λ��ͷ
	{
		fseek(fp,0,SEEK_SET);
	}
	//��ȡ�ļ�ͷ
	nWords += ReadStruct("tttitti",&m_Header,fp)>>1;
	//��ȡ�¼�
	pRcrd = &m_RcrdHead;
	for(;;)
	{
		pRcrd->next = new WmfRcrdNode;
		pRcrd = pRcrd->next;
		ReadStruct("it",pRcrd,fp);
		_fread(pRcrd->pData,2,pRcrd->dwRcrdWordsCnt-3,fp);
		nWords += pRcrd->dwRcrdWordsCnt;
		if(pRcrd->wGDIFunction == 0 || nWords>=m_Header.dwFileLength)//��β
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
