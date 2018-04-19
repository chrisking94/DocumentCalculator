#pragma once
#include "VarList.h"

class CKeyMatcher
{
public:
	typedef enum
	{
		_Undef,
		_Var,//变量名
		_Const,//常量
		_Opr//运算符
	}KeyType;
public:
	CKeyMatcher(CVarList *pVL);
	~CKeyMatcher(void);

	KeyType Parse(char *&s);
	void ToStrStream(char *&s);//把buffer中的字符串复制到s中，并移动s
	KeyType TypeOf() const{return m_type;}
	double ToNum() const;
	char *GetStr() const;
private:
	char buffer[128];
	KeyType m_type;
	CVarList *m_pvl;
};

