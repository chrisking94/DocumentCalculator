#pragma once
#include "Var.h"

class CVarList
{
public:
	CVarList(void);
	~CVarList(void);

	CVar *GetVar(char *szName ,CVar::VAR_TYPE vType = CVar::_var);//查找，若不存在，则提示用户输入，并创建Var
	int ExistsVar(char *szName);
	int FindVar(char *szName,int &indexRet);//查找变量，若不存在则从indexRet返回应当插入的位置，并返回0
	char *Match(char *&s);//在该字符串s中查找变量名，找到则返回变量名，并将s移动到变量名后面一个字符。否则返回0，不移动s
	//double GetVarVal(char *szName);
	//void AddVar(char *szName,double val);
private:
	CVar *m_lst[500];
	unsigned int m_count;//变量数
};
