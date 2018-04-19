#include "StdAfx.h"
#include "ExpNode.h"
#include <math.h>

CExpNode::CExpNode(void):lchild(0),rchild(0),pVar(0),pOpt(0)
{
}


CExpNode::~CExpNode(void)
{
}

void CExpNode::ToVarExpStrStream(char *&szStream , CExpNode* pParent)
{
	char bracket = 0;

	if(pParent)
	{
		if(pParent->lchild == this)//左树
		{
			if(pOpt)
			{
				if(pParent->pOpt->ICP() > pOpt->ISP())
				{
					bracket = ')';
					*szStream++ = '(';
				}
			}
		}
		else//右树
		{
			if(pOpt)
			{
				if(pParent->pOpt->ISP() > pOpt->ICP())
				{
					bracket = ')';
					*szStream++ = '(';
				}
			}
		}
	}

	if(lchild)
	{
		lchild->ToVarExpStrStream(szStream , this);
	}
	if(pOpt)
	{
		CVar::VAR_TYPE t = rchild->pVar->TypeOf();
		if(!(*pOpt == "*" && (t == CVar::_unit || t==CVar::_var || t==CVar::_sysConst ||(rchild->pOpt&&rchild->pOpt->GetMN()==1))))
			pOpt->ToStrStream(szStream);
	}
	else
	{
		pVar->NameToStrStream(szStream);
	}
	if(rchild)
	{
		rchild->ToVarExpStrStream(szStream ,this);
	}

	if(bracket)
	{
		*szStream++=bracket;
		*szStream = '\0';
	}
}

void CExpNode::ToNumExpStrStream(char *&szStream , CExpNode* pParent)
{
	char bracket = 0;

	if(pParent)
	{
		if(pParent->lchild == this)//左树
		{
			if(pOpt)
			{
				if(pParent->pOpt->ICP() > pOpt->ISP())
				{
					bracket = ')';
					*szStream++ = '(';
				}
			}
		}
		else//右树
		{
			if(pOpt)
			{
				if(pParent->pOpt->ISP() > pOpt->ICP())
				{
					bracket = ')';
					*szStream++ = '(';
				}
			}
		}
	}

	if(lchild)
	{
		lchild->ToNumExpStrStream(szStream , this);
	}
	if(pOpt)
	{
		if(!(*pOpt == "*" && rchild && rchild->pVar->TypeOf() == CVar::_unit))
			pOpt->ToStrStream(szStream);
	}
	else
	{
		pVar->ToStrStream(szStream,2);
	}
	if(rchild)
	{
		if(rchild->pVar->TypeOf() == CVar::_unit)
			rchild->ToVarExpStrStream(szStream ,this);
		else
			rchild->ToNumExpStrStream(szStream ,this);
	}

	if(bracket)
	{
		*szStream++=bracket;
		*szStream = '\0';
	}
}

void CExpNode::ToMathExp(CMathExp *pFile, CExpNode* pParent,int x,int y,byte level)
{
	char bracket = 0;

	if(pParent)
	{
		if(pParent->lchild == this)//左树
		{
			if(pOpt)
			{
				if(pParent->pOpt->ICP() > pOpt->ISP())
				{
					bracket = ')';
					pFile->DrawStr("(");
				}
			}
		}
		else//右树
		{
			if(pOpt)
			{
				if(pParent->pOpt->ISP() > pOpt->ICP())
				{
					bracket = ')';
					pFile->DrawStr("(");
				}
			}
		}
	}

	if(lchild)
	{
		lchild->ToMathExp(pFile,this,0,0,2);
	}
	if(pOpt)
	{
		CVar::VAR_TYPE t = rchild->pVar->TypeOf();
		if(!(*pOpt == "*" && (t == CVar::_unit || t==CVar::_var || t==CVar::_sysConst ||(rchild->pOpt&&rchild->pOpt->GetMN()==1))))
			pFile->DrawStr(pOpt->GetName());
	}
	else
	{
		char buffer[256],*pbb=buffer;
		pVar->NameToStrStream(pbb);
		pFile->DrawStr(buffer);
	}
	if(rchild)
	{
		rchild->ToMathExp(pFile,this,0,0,2);
	}

	if(bracket)
	{
		pFile->DrawStr(")");
	}
}

void CExpNode::Execute()
{
	if(pOpt!=NULL)//运算符
	{
		CVar *pLOperand,*pROperand;

		if(lchild)
		{
			lchild->Execute();
			pLOperand = lchild->pVar;
		}
		if(rchild)
		{
			rchild->Execute();
			pROperand = rchild->pVar;
		}

		if((*pOpt)=="=")
		{
			if(pROperand->CmpMe("$")==0)//输出变量本身的值
				*pVar = *pROperand = *pLOperand;
			else
				*pVar = *pLOperand = *pROperand;
		}
		else if((*pOpt)=="+")
		{
			pVar->SetVal(pLOperand->Val() + pROperand->Val());
		}
		else if((*pOpt)=="-")
		{
			if(pOpt->GetMN() == COper::_single)//负号
			{
				pVar->SetVal(0 - pROperand->Val());
			}
			else pVar->SetVal(pLOperand->Val() - pROperand->Val());
		}
		else if((*pOpt)=="*")
		{
			pVar->SetVal(pLOperand->Val() * pROperand->Val());
		}
		else if((*pOpt)=="/")
		{
			pVar->SetVal(pLOperand->Val() / pROperand->Val());
		}
		else if((*pOpt)=="^")
		{
			pVar->SetVal(pow(pLOperand->Val() , pROperand->Val()));
		}
		else if((*pOpt)=="cos")
		{
			pVar->SetVal(cos(pROperand->Val()));
		}
		else if((*pOpt)=="sin")
		{
			pVar->SetVal(sin(pROperand->Val()));
		}
		else if((*pOpt)=="tan")
		{
			pVar->SetVal(tan(pROperand->Val()));
		}
		else if((*pOpt)=="cot")
		{
			pVar->SetVal(1/tan(pROperand->Val()));
		}
		else if((*pOpt)=="Σ")
		{

		}
		else if((*pOpt)=="sqrt")
		{
			pVar->SetVal(sqrt(pROperand->Val()));
		}
		else if((*pOpt)=="@>")
		{
			pVar->SetVal(pLOperand->Val()>pROperand->Val()?pLOperand->Val():pROperand->Val());
		}
		else if((*pOpt)=="@<")
		{
			pVar->SetVal(pLOperand->Val()<pROperand->Val()?pLOperand->Val():pROperand->Val());
		}
		else if((*pOpt)=="~")
		{
			double d;
			do 
			{
				printf("\n请输入一个数，在[%.2lf~%.2lf]之间：",pLOperand->Val(),pROperand->Val());
				scanf("%lf",&d);
			} while (d<pLOperand->Val()||d>pROperand->Val());
			pVar->SetVal(d);
		}
		else if((*pOpt)==">")
		{
			if(pLOperand->Val()>pROperand->Val()) pVar->SetVal(1);
			else
			{
				pVar->SetVal(0);
				static char szbuffer[256] ,*s=szbuffer;
				ToVarExpStrStream(s,0);
				printf("\n\n ------警告：比较表达式 %s %lf>%lf 不成立！\n\n",szbuffer,pLOperand->Val(),pROperand->Val());
				system("pause");
			}
		}
		else if((*pOpt)=="<")
		{
			if(pLOperand->Val()<pROperand->Val()) pVar->SetVal(1);
			else
			{
				pVar->SetVal(0);
				printf("\n 警告：比较表达式 %lf<%lf 不成立！\n",pLOperand->Val(),pROperand->Val());
				system("pause");
			}
		}
		else if((*pOpt)=="≥")
		{
			if(pLOperand->Val() >= pROperand->Val()) pVar->SetVal(1);
			else
			{
				pVar->SetVal(0);
				printf("\n 警告：比较表达式 %lf≥%lf 不成立！\n",pLOperand->Val(),pROperand->Val());
				system("pause");
			}
		}
		else if((*pOpt)=="≤")
		{
			if(pLOperand->Val() <= pROperand->Val()) pVar->SetVal(1);
			else
			{
				pVar->SetVal(0);
				printf("\n 警告：比较表达式 %lf≤%lf 不成立！\n",pLOperand->Val(),pROperand->Val());
				system("pause");
			}
		}
	}
}
