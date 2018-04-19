#include "StdAfx.h"
#include "Var.h"
#include <string.h>

CVar::CVar(char *szName ,VAR_TYPE t):m_szName(0),m_assigned(0),m_val(0),m_type(t)
{
	if(szName)
	{
		m_szName = new char[strlen(szName)+1];
		strcpy(m_szName,szName);
	}//无名变量
	else m_type = _const;//常量
}


CVar::~CVar(void)
{
}

int CVar::CmpMe(char *szName) const
{
	if(m_szName==0) return 1;
	return strcmp(szName,m_szName);
}

CVar & CVar::operator=(const CVar &src)
{
	SetVal(src.m_val);
	return *this;
}

void CVar::ToStrStream(char *&s,int nDigitsAfterDot)
{
	static char szFormat[]="%.2lf";
	szFormat[2] = nDigitsAfterDot + 0x30;
	sprintf( s, szFormat, m_val );//for doublt use %lf
	//格式化
	int i=strlen(s)-1;
	while(s[i]=='0'&&s[i]!='.') i--;
	if(s[i]=='.') s[i]=0;
	else s[++i]=0;
	
	s+=i;
}

void CVar::Initialize()
{
	VarNameChar.SetFlag('A','Z',1);
	VarNameChar.SetFlag('a','z',1);
	VarNameChar.SetFlag('0','9',1);
	VarNameChar.SetFlag("_'",1);
	VarNameChar.SetFlag("δ△ηαγθμρλ");
}


void CVar::NameToStrStream(char *&szStream)
{
	if(m_szName)
	{
		strcpy(szStream,m_szName);
		szStream += strlen(m_szName);
	}
	else ToStrStream(szStream,2);
}


CCharControl CVar::VarNameChar;
