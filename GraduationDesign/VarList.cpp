#include "StdAfx.h"
#include "VarList.h"
#include <string.h>
#include "CharControl.h"
#include <math.h>

CVarList::CVarList(void):m_count(0)
{
	m_lst[0]=0;
	//添加常量
	GetVar("π",CVar::_sysConst)->SetVal(3.14159265358979323846);
	GetVar("e",CVar::_sysConst)->SetVal(2.718281828459);
	GetVar("%",CVar::_sysConst)->SetVal(0.01);
	//单位，咱不支持太多单位
	GetVar("kw",CVar::_unit)->SetVal(1000);
	GetVar("°",CVar::_unit)->SetVal(3.14159265358979323846/180);
	//GetVar("m",CVar::_unit)->SetVal(1);//转成mm
	//GetVar("N",CVar::_unit)->SetVal(1);
	//GetVar("min",CVar::_unit)->SetVal(1);
	//输入
	//GetVar("?",1)->SetVal(0);//请求屏幕输入
	//特殊变量
	GetVar("$",CVar::_var)->SetVal(0);//若F=$，则输出F=val(F)
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
			for(int j=m_count;j>i;j--) m_lst[j]=m_lst[j-1];//后移变量
		}
	}//否则已经到表尾部
	//插入变量
	p=new CVar(szName,vType);
	m_lst[i] = p;
	m_lst[++m_count]=0;

	return p;
}

char * CVarList::Match(char *&s)
{
	char *szName;
	int i;

	for(int k=0;k<m_count;k++)//匹配每个变量
	{
		szName = m_lst[k]->m_szName;
		for(i=0;szName[i]&&szName[i]==s[i];i++);
		if(szName[i]==0)
		{
			//完全匹配
			s+=i;
			return szName;
		}
	}

	return 0;//未找到
}

int CVarList::ExistsVar(char *szName)
{
	//二分查找
	int tmp=0;

	return FindVar(szName,tmp);
}

int CVarList::FindVar(char *szName,int &indexRet)
{
	//二分查找
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
