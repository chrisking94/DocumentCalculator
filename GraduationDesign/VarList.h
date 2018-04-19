#pragma once
#include "Var.h"

class CVarList
{
public:
	CVarList(void);
	~CVarList(void);

	CVar *GetVar(char *szName ,CVar::VAR_TYPE vType = CVar::_var);//���ң��������ڣ�����ʾ�û����룬������Var
	int ExistsVar(char *szName);
	int FindVar(char *szName,int &indexRet);//���ұ����������������indexRet����Ӧ�������λ�ã�������0
	char *Match(char *&s);//�ڸ��ַ���s�в��ұ��������ҵ��򷵻ر�����������s�ƶ�������������һ���ַ������򷵻�0�����ƶ�s
	//double GetVarVal(char *szName);
	//void AddVar(char *szName,double val);
private:
	CVar *m_lst[500];
	unsigned int m_count;//������
};
