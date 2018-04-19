#pragma once
#include "wmffile.h"

class CMathExp :
	public CWmfFile
{
public:
	typedef struct
	{
		int x,y;
		int w,h;
	}MRect;
public:
	CMathExp(void);
	CMathExp(char *szFile);
	~CMathExp(void);

	void SetSize(byte size);
	MRect DrawStr(char *sz);
	MRect DrawVarName(char *szVar);
	MRect DrawOpr(char *szOpr);
	MRect DrawDivisor(int x,int length);
private:
	MRect m_lRect;
	int m_size;
};

