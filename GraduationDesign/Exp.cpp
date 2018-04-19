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
	//��ʽ�����ʽ�ַ���
	char buff[1024];
	int i = 0;
	buff[i++] = '#';
	char *szName=&buff[20];//��20���ַ�Ϊ =����ʼ�����߽���

	*szName = 0;

	//��ȡ��Ҫ��ֵ�ı�����
	s--;//����=
	while(!NOT_WHITE_CHARS) s--;//�����հ׷�
	//��ȡ������
	//while(NOT_WHITE_CHARS)//���ʽ֮ǰһ��Ҫ���ַ���֧�����ı�����
	for(;;)
	{
		if(CVar::VarNameChar.WCharCheck(s-1))
			*--szName=*s--;
		else if(!CVar::VarNameChar.Table[*s])
			break;
		*--szName=*s--;
	}
	//�����ñ���
	m_pCVL->GetVar(szName);


	//��ʼ��ȡ����ʽ���������ʽ
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
			if(km.GetStr()[0]=='(') *pb++='*';//�ָ�*    3(a*c+9)//��������
			else if (COper(km.GetStr()).GetMN()==1)
			{
				if(COper(km.GetStr())!="-") *pb++='*';//10tan(k)//�������ͣ�������10-k
			}
		}
		else if((lastKt == CKeyMatcher::_Const || lastKt == CKeyMatcher::_Var) && (kt== CKeyMatcher::_Var ))//�˷���д
		{
			*pb++='*';//�ָ�*
		}
		lastKt = kt;
		km.ToStrStream(pb);
	}
	*pb++ = '#';
	*pb++ = '\0';

	char bVarExpOut = 0;
	char bNumExpOut = 0;

	//ת����׼���ʽ
	char *s_std = buff;

	//���ɱ��ʽ��
#define MAX_OPS 100
	CVar *in[MAX_OPS];//��׺���ʽ
	CVar *post[MAX_OPS];//��׺���ʽ
	int len=0,inI=0,postI=0;//���ʽ����
	CVar *stack[MAX_OPS];
	int top=-1;

	CVar *p;

	bool bBack = false;//ָ���Ƿ����
	COper *pOptIC,*pOptIS;//In coming ,In stack
	bool bOnceAgin = true;

	pOptIC = new COper;
	pOptIC->Parse(s_std);//#��ջ
	stack[++top] = new CVar(pOptIC);//#��ջ

	//pbo = szNumExp;
	while(*s_std)
	{
		km.Parse(s_std);
		//�������������⴦���жϽ����
		if(km.TypeOf() == CKeyMatcher::_Opr)//����Ƿ���ֲ�����
		{
			if(LastOPType == _operator)
			{
				//��Ŀ���ҵ�����
				pOptIC = new COper(km.GetStr(),COper::_Right2Left);
			}
			else
			{
				pOptIC = new COper(km.GetStr(),COper::_Left2Right);
			}
			
			if(*pOptIC!="#")
			{
				//���������������
				if(*pOptIC != "=") 
					bNumExpOut = 1;//�м���ı��ʽ��������
			}

			if(*pOptIC==")") LastOPType = _operand;//���ű��Ϊ������
			else LastOPType = _operator;//���Ϊ������

			do//����һ��
			{
				pOptIS = (COper*)stack[top]->GetName();
				bOnceAgin = false;

				if(pOptIC->ICP()==pOptIS->ISP())//( # ֮��
				{
					--top;//ֱ�ӳ�ջ
					len-=2;//�����ַ������ȼ�2����Ϊ������( #
					//ɾ��(	#
					delete pOptIC;
					delete pOptIS;
					if((*pOptIC) == "#")//���ʽ����
					{
						bOnceAgin = true;//�����ڱ�������ⲿ��ѭ��
						break;
					}
				}
				else if(pOptIC->ICP()<pOptIS->ISP())//�������ȼ�����
				{
					post[postI++] = stack[top--];
					bOnceAgin = true;//�����鿴���Ƿ񻹿��Զ�
				}
				else
				{
					p = new CVar(pOptIC);//��δ��ֵ�ı����洢�����
					if(*pOptIC!="("
						&&*pOptIC!=")"
						&&*pOptIC!="#")	in[inI++] = p;
					stack[++top] = p;//������ȼ�δ֪����ջ�ȴ������
				}
			}while(bOnceAgin);

			if(bOnceAgin) break;//����;�������鿴����˵����
		}
		else//������
		{
			LastOPType = _operand;//���Ϊ������

			switch(km.TypeOf())//���ദ��
			{
			case  CKeyMatcher::_Const://���֣�Ϊ���ִ�����������
				p = new CVar((char*)NULL);
				p->SetVal(km.ToNum());
				break;
			case  CKeyMatcher::_Var://����
				p = m_pCVL->GetVar(km.GetStr());//Ѱַ
				if(!p->IsAssigned()) p->SetVal(0);//��ʼ��Ϊ0
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

	//ͨ��ǰ�����кͺ������д������ʽ��
	if(inI>0)//==0�ǿձ��ʽ
	{
		--inI; 
		--postI;
		m_expTree = InPostCreateTree(&in[0],&in[inI],&post[0],&post[postI]);
		
		//����
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
			//������
			m_expTree->pOpt->ToStrStream(pbo);
			m_expTree->pVar->ToStrStream(pbo,2);
		}
		while(!NOT_WHITE_CHARS)
		{
			*pbo++=*s++;//׷��ĩβ���ַ�
		}
		*pbo = 0;

		return TRUE;
	}

	return FALSE;//�ձ��ʽ
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
	while(pin<=in2)//�������������еĽڵ�
	{
		if(*pin == *post2)
		{
			break;
		}
		++pin;
	}
	//�������ڵ�
	pRet = new CExpNode;
	pRet->pVar = *pin;
	if(pRet->pVar->IsAssigned() == 0) pRet->pOpt = (COper *)pRet->pVar->GetName();//��������������������
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
	if(p->pVar->GetName() == 0)//ɾ����������
		delete p->pVar;
	delete p;
	p = NULL;
}
