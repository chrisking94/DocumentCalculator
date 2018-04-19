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
	//格式为 "m a opt"
	//m:操作数目数 a:结合性 opt:运算符string
	 "$a$","00#"//特殊的#号 0，这是之后加进来的，后面的ID都要+1，$x为优先级标号
	,"$b$","00(","00)"
	,"$c$","11cos","11sin","11tan","11cot"
	,"$d$","20^"//次方
	,"$e$","11sqrt"//开平方
	,"$f$","20/","22x","22*","20mod"//两种乘号
	,"$g$","11-"//-为负号
	,"$h$","20+","22-"//加减号
	,"$i$","11Σ","20~"//求和，~为取范围负号
	,"$j$","20@>","20@<"//@为取较大/小数的计算符号
	,"$k$","20==","20≠"
	,"$l$","20=","20>","20≥","20<","20≤"
	,""//列表结束
};

#define PRIORITY_COUNT ('l'-'a'+1)

int COper::ISP() const
{
	//一些运算的特殊优先级
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
	//一些运算的特殊优先级
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

	return -1;//未找到
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
