#pragma once
#include "Var.h"
#include "MathExp.h"
#include "Common.h"

typedef class CExpNode
{
public:
	CExpNode(void);
	~CExpNode(void);

	void ToVarExpStrStream(char *&szStream , CExpNode* pParent);//返回左边指针
	void ToNumExpStrStream(char *&szStream , CExpNode* pParent);
	void ToMathExp(CMathExp *pFile, CExpNode* pParent,int x,int y,byte level);
	RECT GetRect();

	void Execute();
public:
	CVar *pVar;
	COper *pOpt;//运算符，如果是操作数则这个opt = 0
	CExpNode *lchild,*rchild;
}*ExpTree;

