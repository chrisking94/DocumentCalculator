#include "StdAfx.h"
#include "Exp.h"
#include "CharControl.h"
#include "StrParallelCmp.h"
#include "KeyMatcher.h"
#include "VarList.h"
#include <math.h>
#include <string.h>
#include "Common.h"
#include "MathExp.h"

#define NOT_WHITE_CHARS (*s!=' '&&*s!='	'&&*s!='\r'&&*s!='\n')

CExp::CExp( CVarList *pvl ):m_expTree(NULL),m_pCVL (pvl) 
{

}


CExp::~CExp(void)
{
	DestroyTree(m_expTree);
}

BOOL CExp::Parse( char *&s )
{
	enum
	{
		_operand,
		_operator,
	}LastOPType = _operator;
	//格式化表达式字符串
	char buff[1024];
	int i = 0;
	buff[i++] = '#';
	char *szName=&buff[20];//第20个字符为 =，开始向两边解析

	*szName = 0;

	//读取需要赋值的变量名
	s--;//跳过=
	while(!NOT_WHITE_CHARS) s--;//跳过空白符
	//读取变量名
	//while(NOT_WHITE_CHARS)//表达式之前一定要白字符，支持中文变量名
	for(;;)
	{
		if(CVar::VarNameChar.WCharCheck(s-1))
			*--szName=*s--;
		else if(!CVar::VarNameChar.Table[*s])
			break;
		*--szName=*s--;
	}
	//创建该变量
	m_pCVL->GetVar(szName);


	//开始读取并格式化整个表达式
	i=0;
	CKeyMatcher km(m_pCVL);
	CKeyMatcher::KeyType kt=CKeyMatcher::_Const,lastKt=CKeyMatcher::_Undef;
	char *pb = buff;

	*pb++='#';
	s++;
	i=0;
	for(;;)
	{
		kt=km.Parse(s);
		if(kt==CKeyMatcher::_Undef) break;
		if((lastKt == CKeyMatcher::_Const||lastKt== CKeyMatcher::_Var) && kt== CKeyMatcher::_Opr)
		{
			if(km.GetStr()[0]=='(') *pb++='*';//恢复*    3(a*c+9)//这种类型
			else if (COper(km.GetStr()).GetMN()==1)
			{
				if(COper(km.GetStr())!="-") *pb++='*';//10tan(k)//这种类型，不包括10-k
			}
		}
		else if((lastKt == CKeyMatcher::_Const || lastKt == CKeyMatcher::_Var) && (kt== CKeyMatcher::_Var ))//乘法简写
		{
			*pb++='*';//恢复*
		}
		lastKt = kt;
		km.ToStrStream(pb);
	}
	*pb++ = '#';
	*pb++ = '\0';

	char bVarExpOut = 0;
	char bNumExpOut = 0;

	//转换标准表达式
	char *s_std = buff;

	//生成表达式树
#define MAX_OPS 100
	CVar *in[MAX_OPS];//中缀表达式
	CVar *post[MAX_OPS];//后缀表达式
	int len=0,inI=0,postI=0;//表达式长度
	CVar *stack[MAX_OPS];
	int top=-1;

	CVar *p;

	bool bBack = false;//指针是否回退
	COper *pOptIC,*pOptIS;//In coming ,In stack
	bool bOnceAgin = true;

	pOptIC = new COper;
	pOptIC->Parse(s_std);//#入栈
	stack[++top] = new CVar(pOptIC);//#入栈

	//pbo = szNumExp;
	while(*s_std)
	{
		km.Parse(s_std);
		//操作符属性特殊处理，判断结合性
		if(km.TypeOf() == CKeyMatcher::_Opr)//检测是否出现操作符
		{
			if(LastOPType == _operator)
			{
				//单目，右到左结合
				pOptIC = new COper(km.GetStr(),COper::_Right2Left);
			}
			else
			{
				pOptIC = new COper(km.GetStr(),COper::_Left2Right);
			}
			
			if(*pOptIC!="#")
			{
				//操作符输出到容器
				if(*pOptIC != "=") 
					bNumExpOut = 1;//有计算的表达式，输出结果
			}

			if(*pOptIC==")") LastOPType = _operand;//括号标记为操作数
			else LastOPType = _operator;//标记为操作符

			do//至少一次
			{
				pOptIS = (COper*)stack[top]->GetName();
				bOnceAgin = false;

				if(pOptIC->ICP()==pOptIS->ISP())//( # 之类
				{
					--top;//直接出栈
					len-=2;//后序字符串长度减2，因为不包括( #
					//删除(	#
					delete pOptIC;
					delete pOptIS;
					if((*pOptIC) == "#")//表达式结束
					{
						bOnceAgin = true;//①用于标记跳出外部大循环
						break;
					}
				}
				else if(pOptIC->ICP()<pOptIS->ISP())//将高优先级顶出
				{
					post[postI++] = stack[top--];
					bOnceAgin = true;//连续查看，是否还可以顶
				}
				else
				{
					p = new CVar(pOptIC);//用未赋值的变量存储运算符
					if(*pOptIC!="("
						&&*pOptIC!=")"
						&&*pOptIC!="#")	in[inI++] = p;
					stack[++top] = p;//相对优先级未知，入栈等待运算符
				}
			}while(bOnceAgin);

			if(bOnceAgin) break;//多用途变量，查看上面说明①
		}
		else//操作数
		{
			LastOPType = _operand;//标记为操作数

			switch(km.TypeOf())//分类处理
			{
			case  CKeyMatcher::_Const://数字，为数字创建无名变量
				p = new CVar((char*)NULL);
				p->SetVal(km.ToNum());
				break;
			case  CKeyMatcher::_Var://变量
				p = m_pCVL->GetVar(km.GetStr());//寻址
				if(!p->IsAssigned()) p->SetVal(0);//初始化为0
				else
				{
					bVarExpOut = 1;
				}
				break;
			}
			in[inI++] = p;
			post[postI++]=p;
		}
	}

	//通过前序序列和后序序列创建表达式树
	if(inI>0)//==0是空表达式
	{
		--inI; 
		--postI;
		m_expTree = InPostCreateTree(&in[0],&in[inI],&post[0],&post[postI]);
		
		//计算
		char *pbo = szVarExp;
		if(m_expTree)
		{
			//m_expTree->lchild->pVar->NameToStrStream(pbo);
			m_expTree->Execute();
			if(m_expTree->rchild->pVar->CmpMe("$") == 0)
			{
				bVarExpOut = 0;
				bNumExpOut = 0;
			}
			if(bVarExpOut)
			{
				m_expTree->pOpt->ToStrStream(pbo);
				m_expTree->rchild->ToVarExpStrStream(pbo ,m_expTree);
			}
			if(bNumExpOut)
			{
				m_expTree->pOpt->ToStrStream(pbo);
				m_expTree->rchild->ToNumExpStrStream(pbo ,m_expTree);
			}
			//输出结果
			m_expTree->pOpt->ToStrStream(pbo);
			m_expTree->pVar->ToStrStream(pbo,2);
		}
		while(!NOT_WHITE_CHARS)
		{
			*pbo++=*s++;//追加末尾白字符
		}
		*pbo = 0;

		return TRUE;
	}

	return FALSE;//空表达式
}


void CExp::ToMathExp()
{
	char sz[1024]="C:\\Users\\Administrator.PC--20130717MTX\\Desktop\\";
	char *p=sz+strlen(sz);
	m_expTree->lchild->pVar->NameToStrStream(p);
	strcpy(p,".wmf");
	CMathExp mexp(sz);
	m_expTree->ToMathExp(&mexp,0,0,0,2);
}

ExpTree CExp::InPostCreateTree( CVar **in1,CVar **in2,CVar **post1,CVar **post2 )
{
	if(post1>post2) return NULL;
	CVar **pin = in1;
	ExpTree pRet;
	while(pin<=in2)//查找中序序列中的节点
	{
		if(*pin == *post2)
		{
			break;
		}
		++pin;
	}
	//创建根节点
	pRet = new CExpNode;
	pRet->pVar = *pin;
	if(pRet->pVar->IsAssigned() == 0) pRet->pOpt = (COper *)pRet->pVar->GetName();//这种是特殊的运算符变量
	else pRet->pOpt = NULL;
	pRet->lchild = InPostCreateTree(in1,pin-1,post1,post1+(pin-in1)-1);
	pRet->rchild = InPostCreateTree(pin+1,in2,post1+(pin-in1),post2-1);

	return pRet;
}

void CExp::DestroyTree( ExpTree p )
{
	if(!p) return;
	DestroyTree(p->lchild);
	DestroyTree(p->rchild);
	delete p->pOpt;
	if(p->pVar->GetName() == 0)//删除无名变量
		delete p->pVar;
	delete p;
	p = NULL;
}
