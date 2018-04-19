#pragma once
#include "Oper.h"
#include "CharControl.h"
class CVar
{
public:
	typedef enum
	{
		_var,
		_const,
		_sysConst,
		_unit,
		_opr,
	}VAR_TYPE;
public:
	~CVar(void);
	CVar(char *m_szName ,VAR_TYPE t = _var);
	CVar(COper *pOpr):m_szName((char*)pOpr),m_assigned(0),m_val(0),m_type(_opr){}//����������

	void SetVal(double v){m_assigned=1;m_val=v;};
	int CmpMe(char *szName) const;//��szName �� m_szName�Ƚ�
	double Val() const{return m_val;};
	char *GetName() const{return m_szName;}
	char IsAssigned() const{return m_assigned;};
	void ToStrStream(char *&s,int nDigitsAfterDot);//С������λ��
	VAR_TYPE TypeOf() const{return m_type;}
	void NameToStrStream(char *&szStream);

	CVar &operator=(const CVar &src);

	static void Initialize();//�����ȵ��øú�������ʹ�ø���
	static CCharControl VarNameChar;
public:
	char	*m_szName;
private:
	double		m_val;
	char		m_assigned;
	VAR_TYPE	m_type;//����
};

