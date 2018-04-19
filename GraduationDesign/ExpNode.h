#pragma once
#include "Var.h"
#include "MathExp.h"
#include "Common.h"

typedef class CExpNode
{
public:
	CExpNode(void);
	~CExpNode(void);

	void ToVarExpStrStream(char *&szStream , CExpNode* pParent);//�������ָ��
	void ToNumExpStrStream(char *&szStream , CExpNode* pParent);
	void ToMathExp(CMathExp *pFile, CExpNode* pParent,int x,int y,byte level);
	RECT GetRect();

	void Execute();
public:
	CVar *pVar;
	COper *pOpt;//�����������ǲ����������opt = 0
	CExpNode *lchild,*rchild;
}*ExpTree;

