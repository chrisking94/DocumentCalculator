#include "StdAfx.h"
#include "KeyMatcher.h"
#include "CharControl.h"
#include <string>
#include "Oper.h"

CKeyMatcher::~CKeyMatcher(void)
{
}

CKeyMatcher::CKeyMatcher(CVarList *pVL):m_pvl(pVL)
{

}

CKeyMatcher::KeyType CKeyMatcher::Parse(char *&s)
{
#define JUMP_WHITE_CHARS while(*s==' '||*s=='	') {s++;i++;}
	CCharControl cc;
	cc.SetFlag('0','9',1);
	cc.SetFlag('.',1);
	KeyType kt = _Undef;
	char *szName;
	int i=0;

	JUMP_WHITE_CHARS;
	char *pb=buffer;

	if(*s=='?')//����Ļ����
	{
		printf("\n�������������ֵ����");
		m_type = _Const;
		scanf("%s",pb);
		s++;
	}
	else if(cc.Table[*s]==1)//���� 
	{
		while(cc.Table[*s]==1)
		{
			*pb++=*s++;
		}
		m_type = _Const;
		*pb = 0;
	}
	else
	{
		//�����Ƿ�Ϊ�����
		szName = COper::Match(s);
		if(szName)//�ҵ������
		{
			m_type = _Opr;
		}
		else
		{
			szName = m_pvl->Match(s);
			if(!szName)
			{
				s-=i;//����
				return _Undef;//�Ƿ��ַ�
			}
			else m_type = _Var;
		}
		strcpy(buffer,szName);
	}

	return m_type;
}

void CKeyMatcher::ToStrStream(char *&s)
{
	strcpy(s,buffer);
	s+=strlen(buffer);
}

double CKeyMatcher::ToNum() const
{
	return atof(buffer);
}

char * CKeyMatcher::GetStr() const
{
	return (char*)buffer;
}
