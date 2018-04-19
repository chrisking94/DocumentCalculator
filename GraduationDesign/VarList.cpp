#include "StdAfx.h"
#include "VarList.h"
#include <string.h>
#include "CharControl.h"
#include <math.h>

CVarList::CVarList(void):m_count(0)
{
	m_lst[0]=0;
	//��ӳ���
	GetVar("��",CVar::_sysConst)->SetVal(3.14159265358979323846);
	GetVar("e",CVar::_sysConst)->SetVal(2.718281828459);
	GetVar("%",CVar::_sysConst)->SetVal(0.01);
	//��λ���۲�֧��̫�൥λ
	GetVar("kw",CVar::_unit)->SetVal(1000);
	GetVar("��",CVar::_unit)->SetVal(3.14159265358979323846/180);
	//GetVar("m",CVar::_unit)->SetVal(1);//ת��mm
	//GetVar("N",CVar::_unit)->SetVal(1);
	//GetVar("min",CVar::_unit)->SetVal(1);
	//����
	//GetVar("?",1)->SetVal(0);//������Ļ����
	//�������
	GetVar("$",CVar::_var)->SetVal(0);//��F=$�������F=val(F)
}  


CVarList::~CVarList(void)
{
}

CVar * CVarList::GetVar(char *szName , CVar::VAR_TYPE vType)
{
	CVar *p;
	int i=0;
	for(;m_lst[i]&&m_lst[i]->CmpMe(szName)<0;i++);
	p=m_lst[i];
	if(p)
	{
		if(p->CmpMe(szName)==0)
		{
			return p;
		}
		else
		{
			for(int j=m_count;j>i;j--) m_lst[j]=m_lst[j-1];//���Ʊ���
		}
	}//�����Ѿ�����β��
	//�������
	p=new CVar(szName,vType);
	m_lst[i] = p;
	m_lst[++m_count]=0;

	return p;
}

char * CVarList::Match(char *&s)
{
	char *szName;
	int i;

	for(int k=0;k<m_count;k++)//ƥ��ÿ������
	{
		szName = m_lst[k]->m_szName;
		for(i=0;szName[i]&&szName[i]==s[i];i++);
		if(szName[i]==0)
		{
			//��ȫƥ��
			s+=i;
			return szName;
		}
	}

	return 0;//δ�ҵ�
}

int CVarList::ExistsVar(char *szName)
{
	//���ֲ���
	int tmp=0;

	return FindVar(szName,tmp);
}

int CVarList::FindVar(char *szName,int &indexRet)
{
	//���ֲ���
	int low=0,high=m_count-1,k;

	while(low<=high)
	{
		indexRet = (low+high)/2;
		k = m_lst[indexRet]->CmpMe(szName);
		if(k>0)
		{
			high = indexRet-1;
		}
		else if(k<0)
		{
			low=indexRet+1;
		}
		else
		{
			return 1;
		}
	}

	indexRet = low;
	return 0;
}
