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

	BOOL Parse(char *&s);//�������ǴӵȺŴ���ʼ��
	CVar *Execute();
	void ToMathExp();

	ExpTree InPostCreateTree(CVar **in1,CVar **in2,CVar **post1,CVar **post2);//ͨ���������к������д�����
	void DestroyTree(ExpTree p);//ɾ����
	
public:
#define EXP_BUF_SIZ 256
	char szVarExp[EXP_BUF_SIZ];//��ĸ���ʽ
protected:
	ExpTree m_expTree;
private:
	CVarList *m_pCVL;
};

