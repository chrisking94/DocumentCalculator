#pragma once
#include "VarList.h"

class CGD
{
public:
	CGD(char *szFile);
	~CGD(void);
private:
	FILE *fp;
	
	CVarList m_vl;
};

