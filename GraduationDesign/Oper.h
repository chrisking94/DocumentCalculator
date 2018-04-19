#pragma once

//运算符管理类
class COper
{
public:
	typedef int OPT_ID;
#define  _Sharp 1
#define  _LBracket 3 
#define  _RBracket 4
	typedef enum
	{
		_null//多目
		,_single//单目
		,_double//双目
		,_triple//三目
	}Mesh_Number;//操作数目数

	typedef enum
	{
		_Ignore,//忽略
		_Right2Left,
		_Left2Right,
	}Associativity;//结合性
public:
	COper(void);
	~COper(void);
	COper(char *szOpr,Associativity asso=_Ignore);

	int Parse(char *&s,Associativity asso=_Ignore);
	int ISP() const;//In stack priority，同一个运算符ISP一般高于ICP
	int ICP() const;//In coming priority
	OPT_ID GetID() const;
	Mesh_Number GetMN() const;//操作数目数
	Associativity GetAsso() const;//结合性
	void SetAsso(const Associativity as);//设置结合性
	char *GetName() const{return (char*)m_oper;}
	void ToStrStream(char *&szStream);//输出到字符串流，并返回'\0'char的指针

	int operator==(const COper &opr) const;
	int operator!=(const COper &opr) const{return !((*this)==opr);}

	static int MatchGetID(char *&s ,Associativity asso=_Ignore);//返回索引号
	static char * Match(char *&s);
protected:
	OPT_ID m_nOptID;//ID，从0开始
	Mesh_Number m_nMeshNum;//操作数目数
	Associativity m_nAsso;
	char m_nPriority;//优先级，这里采用的优先级是小端，即运算符优先级越大，该数越大
	char m_oper[6];
public:
	static char opts[][7];//运算符列表
	static char prioritys[];//表示一个范围，第一个char表示优先级为1的运算符ID范围
	static bool optSigns[256];//运算符特征标记，如果char c; optSigns[c]==1真，则c为运算符
};

