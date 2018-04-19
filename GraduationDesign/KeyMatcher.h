#pragma once
#include "VarList.h"

class CKeyMatcher
{
public:
	typedef enum
	{
		_Undef,
		_Var,//������
		_Const,//����
		_Opr//�����
	}KeyType;
public:
	CKeyMatcher(CVarList *pVL);
	~CKeyMatcher(void);

	KeyType Parse(char *&s);
	void ToStrStream(char *&s);//��buffer�е��ַ������Ƶ�s�У����ƶ�s
	KeyType TypeOf() const{return m_type;}
	double ToNum() const;
	char *GetStr() const;
private:
	char buffer[128];
	KeyType m_type;
	CVarList *m_pvl;
};

