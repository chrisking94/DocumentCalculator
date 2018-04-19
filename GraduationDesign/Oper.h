#pragma once

//�����������
class COper
{
public:
	typedef int OPT_ID;
#define  _Sharp 1
#define  _LBracket 3 
#define  _RBracket 4
	typedef enum
	{
		_null//��Ŀ
		,_single//��Ŀ
		,_double//˫Ŀ
		,_triple//��Ŀ
	}Mesh_Number;//������Ŀ��

	typedef enum
	{
		_Ignore,//����
		_Right2Left,
		_Left2Right,
	}Associativity;//�����
public:
	COper(void);
	~COper(void);
	COper(char *szOpr,Associativity asso=_Ignore);

	int Parse(char *&s,Associativity asso=_Ignore);
	int ISP() const;//In stack priority��ͬһ�������ISPһ�����ICP
	int ICP() const;//In coming priority
	OPT_ID GetID() const;
	Mesh_Number GetMN() const;//������Ŀ��
	Associativity GetAsso() const;//�����
	void SetAsso(const Associativity as);//���ý����
	char *GetName() const{return (char*)m_oper;}
	void ToStrStream(char *&szStream);//������ַ�������������'\0'char��ָ��

	int operator==(const COper &opr) const;
	int operator!=(const COper &opr) const{return !((*this)==opr);}

	static int MatchGetID(char *&s ,Associativity asso=_Ignore);//����������
	static char * Match(char *&s);
protected:
	OPT_ID m_nOptID;//ID����0��ʼ
	Mesh_Number m_nMeshNum;//������Ŀ��
	Associativity m_nAsso;
	char m_nPriority;//���ȼ���������õ����ȼ���С�ˣ�����������ȼ�Խ�󣬸���Խ��
	char m_oper[6];
public:
	static char opts[][7];//������б�
	static char prioritys[];//��ʾһ����Χ����һ��char��ʾ���ȼ�Ϊ1�������ID��Χ
	static bool optSigns[256];//�����������ǣ����char c; optSigns[c]==1�棬��cΪ�����
};

