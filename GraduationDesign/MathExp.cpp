#include "StdAfx.h"
#include "MathExp.h"


CMathExp::CMathExp(void):CWmfFile("")
{
	m_lRect.x=m_lRect.y=m_lRect.w=m_lRect.h=0;
	m_size=20;
	CWmfFile::SetFont("Î¢ÈíÑÅºÚ",m_size,m_size);
}


CMathExp::CMathExp(char *szFile):CWmfFile(szFile)
{
	m_lRect.x=m_lRect.y=m_lRect.w=m_lRect.h=0;
	m_size=20;
	CWmfFile::SetFont("Î¢ÈíÑÅºÚ",m_size,m_size);
}

CMathExp::~CMathExp(void)
{
}

void CMathExp::SetSize(byte size)
{
	switch(size)
	{
	case 1:
		m_size = 10;
		break;
	case 2:
		m_size = 20;
		break;
	}
}

CMathExp::MRect CMathExp::DrawStr(char *sz)
{
	m_lRect.x+=m_lRect.w;
	CWmfFile::TextOut(m_lRect.x,m_lRect.y,sz);
	m_lRect.w=m_size*strlen(sz);

	return m_lRect;
}

CMathExp::MRect CMathExp::DrawVarName(char *szVar)
{
	return m_lRect;
}

CMathExp::MRect CMathExp::DrawOpr(char *szOpr)
{
	return m_lRect;
}

CMathExp::MRect CMathExp::DrawDivisor(int x,int length)
{
	return m_lRect;
}
