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
	CVar(COper *pOpr):m_szName((char*)pOpr),m_assigned(0),m_val(0),m_type(_opr){}//操作符变量

	void SetVal(double v){m_assigned=1;m_val=v;};
	int CmpMe(char *szName) const;//用szName 和 m_szName比较
	double Val() const{return m_val;};
	char *GetName() const{return m_szName;}
	char IsAssigned() const{return m_assigned;};
	void ToStrStream(char *&s,int nDigitsAfterDot);//小数点后的位数
	VAR_TYPE TypeOf() const{return m_type;}
	void NameToStrStream(char *&szStream);

	CVar &operator=(const CVar &src);

	static void Initialize();//必须先调用该函数才能使用该类
	static CCharControl VarNameChar;
public:
	char	*m_szName;
private:
	double		m_val;
	char		m_assigned;
	VAR_TYPE	m_type;//类型
};

