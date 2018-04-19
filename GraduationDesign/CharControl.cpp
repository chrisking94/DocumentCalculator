#include "StdAfx.h"
#include "CharControl.h"
#include <string>


CCharControl::CCharControl(void)
{
	for(int i=0;i<256;i++) {Table[i]=0;m_CompareTable[i]=0;}
	m_wChTable[0] = 0;
}


CCharControl::~CCharControl(void)
{
}

void CCharControl::SetFlag( char ch,char flag )
{
	m_CompareTable[ch]=Table[ch];
	Table[ch]=flag;
}

void CCharControl::SetFlag( char from,char to,char flag )
{
	unsigned char m=from,n=to;

	for(int i=m;i<=n;i++)
	{
		m_CompareTable[i]=Table[i];
		Table[i]=flag;
	}
}

void CCharControl::RecoverFlag( char flag )
{
	for(int i=0;i<256;i++)
	{
		if(Table[i]==flag)
		{
			Table[i]=m_CompareTable[i];
		}
	}
}

#define strlenT(x) (strlen((char*)x)>>1)
void CCharControl::SetFlag( char *s,char flag )
{
	while(*s)
	{
		m_CompareTable[*s]=Table[*s];
		Table[*s++]=flag;
	}
}

void CCharControl::SetFlag(char *s)
{
	//wchar_存入表
	short wc;
	int i;

	while(*s)
	{
		//插入排序
		wc = *(short*)s;
		for(i=m_wChTable[0];i>0&&m_wChTable[i]>wc;i--) m_wChTable[i+1]=m_wChTable[i];
		m_wChTable[i+1] = wc;
		m_wChTable[0]++;
		s+=2;
	}
}

void CCharControl::FlagCharactor( const char flag )
{
	SetFlag('0','9',1);
}

void CCharControl::FlagNumber( const char flag )
{
	SetFlag('A','Z',1);
	SetFlag('a','z',1);
}

void CCharControl::FlagVarName( const char flag )
{
	FlagCharactor(flag);
	FlagNumber(flag);
	SetFlag('_',flag);
}

int CCharControl::WCharCheck(char *s)
{
	//wchar_存入表
	int high=m_wChTable[0],low=1,mid;
	short c=*(short*)s ,wc;
	
	while(low<=high)
	{
		mid = (low+high)/2;
		wc = m_wChTable[mid];
		
		if(wc>c)
		{
			high = mid -1;
		}
		else if(wc<c)
		{
			low=mid+1;
		}
		else if(wc==c)
		{
			return 1;
		}
	}

	return 0;
}
