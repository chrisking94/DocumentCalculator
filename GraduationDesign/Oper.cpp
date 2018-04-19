#include "StdAfx.h"
#include "Oper.h"
#include <string>

COper::COper(void):m_nAsso(_Ignore),m_nMeshNum(_null)
{
	
}

COper::COper(char *szOpr,Associativity asso)
{
	if(szOpr)
	{
		Parse(szOpr,asso);
	}
}


COper::~COper(void)
{
}

int COper::Parse( char *&s ,Associativity asso)
{
	char opt[4]={0,0,0,0};
	char *szOpr;

	if(*s=='@')
		int kk=1;
	m_nOptID = MatchGetID(s,asso);
	if(m_nOptID>=0)
	{
		szOpr = opts[m_nOptID];
		strcpy(m_oper,szOpr+2);
		m_nMeshNum = (Mesh_Number)(szOpr[0]-0x30);
		m_nAsso = (Associativity)(szOpr[1]-0x30);
		int i=m_nOptID-1;
		while(opts[i][0]!='$') i--;
		m_nPriority = opts[i][1] - 'a';

		return 1;
	}
	return 0;
}

char COper::opts[][7]=
{
	//��ʽΪ "m a opt"
	//m:������Ŀ�� a:����� opt:�����string
	 "$a$","00#"//�����#�� 0������֮��ӽ����ģ������ID��Ҫ+1��$xΪ���ȼ����
	,"$b$","00(","00)"
	,"$c$","11cos","11sin","11tan","11cot"
	,"$d$","20^"//�η�
	,"$e$","11sqrt"//��ƽ��
	,"$f$","20/","22x","22*","20mod"//���ֳ˺�
	,"$g$","11-"//-Ϊ����
	,"$h$","20+","22-"//�Ӽ���
	,"$i$","11��","20~"//��ͣ�~Ϊȡ��Χ����
	,"$j$","20@>","20@<"//@Ϊȡ�ϴ�/С���ļ������
	,"$k$","20==","20��"
	,"$l$","20=","20>","20��","20<","20��"
	,""//�б����
};

#define PRIORITY_COUNT ('l'-'a'+1)

int COper::ISP() const
{
	//һЩ������������ȼ�
	switch(m_nOptID)
	{
	case _Sharp://	#
		return 0;
	case _LBracket://	(
		return 1;
	case _RBracket://	)
		return PRIORITY_COUNT*2+1;
	}
	
	return PRIORITY_COUNT*2 - m_nPriority*2+1;
}

int COper::ICP() const
{
	//һЩ������������ȼ�
	switch(m_nOptID)
	{
	case _Sharp://	#
		return 0;
	case _LBracket://	(
		return PRIORITY_COUNT*2+1;
	case _RBracket://	)
		return 1;
	}
	return PRIORITY_COUNT*2 - m_nPriority*2;
}

COper::OPT_ID COper::GetID() const
{
	return m_nOptID;
}

COper::Mesh_Number COper::GetMN() const
{
	return m_nMeshNum;
}

COper::Associativity COper::GetAsso() const
{
	return m_nAsso;
}

void COper::SetAsso( const Associativity as )
{
	m_nAsso = as;
}

char * COper::Match(char *&s)
{
	int i = MatchGetID(s);

	if(i>=0) return &(opts[i][2]);
	else return 0;
}

int COper::MatchGetID(char *&s ,Associativity asso)
{
	char *szName;
	int i,k=0;

	while(opts[k][0])
	{
		if(opts[k][0]!='$')
		{
			szName = &opts[k][2];
			i=0;
			while(szName[i]&&szName[i]==s[i]) i++;
			if(szName[i]==0 && (opts[k][1]-0x30==_Ignore||asso==_Ignore||opts[k][1]-0x30==asso))
			{
				s+=i;
				return k;
			}
		}
		k++;
	}

	return -1;//δ�ҵ�
}

int COper::operator==(const COper &opr) const
{
	if(strcmp(opr.m_oper,m_oper)==0) return 1;
	else return 0;
}

void  COper::ToStrStream(char *&szStream)
{
	strcpy(szStream,m_oper);
	szStream += strlen(m_oper);
}
