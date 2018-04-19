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
	void SetFlag(char *s);//宽字符
	void RecoverFlag(char flag);//kuanzifu将Flag恢复到上次SetFlag之前的值

	void FlagCharactor(const char flag);//为字母设置Flag
	void FlagNumber(const char flag);//为数字设置Flag
	void FlagVarName(const char flag);//为变量名设置Flag,包括字母，数字，下划线

	int WCharCheck(char *s);//检查是否设置过该 wchar的标志
private:
	short m_wChTable[100];//仅支持100个wchar
	char m_CompareTable[256];//用于对比Table的修改，每次修改Table前，将要修改的项存入
};

