#pragma once
class CCharControl
{
public:
	char Table[256];
public:
	CCharControl(void);
	~CCharControl(void);
	void SetFlag(char ch,char flag);
	void SetFlag(char from,char to,char flag);
	void SetFlag(char *s,char flag);
	void SetFlag(char *s);//���ַ�
	void RecoverFlag(char flag);//kuanzifu��Flag�ָ����ϴ�SetFlag֮ǰ��ֵ

	void FlagCharactor(const char flag);//Ϊ��ĸ����Flag
	void FlagNumber(const char flag);//Ϊ��������Flag
	void FlagVarName(const char flag);//Ϊ����������Flag,������ĸ�����֣��»���

	int WCharCheck(char *s);//����Ƿ����ù��� wchar�ı�־
private:
	short m_wChTable[100];//��֧��100��wchar
	char m_CompareTable[256];//���ڶԱ�Table���޸ģ�ÿ���޸�Tableǰ����Ҫ�޸ĵ������
};

