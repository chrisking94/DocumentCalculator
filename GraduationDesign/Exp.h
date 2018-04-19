#pragma once
#include "Var.h"
#include "Oper.h"
#include "VarList.h"
#include "ExpNode.h"
#include "Common.h"

class CExp
{
public:
	~CExp(void);
	CExp(CVarList *pvl);

	BOOL Parse(char *&s);//解析都是从等号处开始的
	CVar *Execute();
	void ToMathExp();

	ExpTree InPostCreateTree(CVar **in1,CVar **in2,CVar **post1,CVar **post2);//通过中序序列后序序列创建树
	void DestroyTree(ExpTree p);//删除树
	
public:
#define EXP_BUF_SIZ 256
	char szVarExp[EXP_BUF_SIZ];//字母表达式
protected:
	ExpTree m_expTree;
private:
	CVarList *m_pCVL;
};

