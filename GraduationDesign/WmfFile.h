#pragma once
#include "Common.h"
//#include <kernelspecs.h>


class CWmfFile
{
public:
	CWmfFile(char *szFilePath);
	~CWmfFile(void);

	void Parse();
	HGDIOBJ SetFont(
		char *szFaceName
		,LONG lHeight 
		,LONG lWidth=0
		,LONG lWeight=FW_NORMAL//�Ƿ����(��ΧΪ0��1000��������س̶ȣ���׼��400�����أ�700��
		,BYTE bPitchAndFamily=FF_ROMAN|DEFAULT_PITCH//���
		,BYTE bItalic=0
		,BYTE bUnderline=0
		,LONG lEscapment=0 //��������뵱ǰ����ϵX��֮���������ת�ĽǶȣ���1/10��Ϊ��λ
		,LONG lOrientation= 0//ÿ���ַ��뵱ǰ����ϵX��֮��ĽǶȣ���1/10��Ϊ��λ
		,BYTE bStrikeOut=0//�Ƿ����л��ߣ���Ϊ0��ʾ���л��ߣ�
		,BYTE bCharSet=CHINESEBIG5_CHARSET//�ַ���
		,BYTE bOutPrecision=OUT_DEFAULT_PRECIS//�������
		,BYTE bClipPrecision=CLIP_DEFAULT_PRECIS//���þ���
		,BYTE bQuality=DEFAULT_QUALITY// Ʒ��
		);
	HGDIOBJ SetFont(const LOGFONTA &font);
	COLORREF SetTextColor(COLORREF color=0);
	BOOL TextOut(int x,int y,LPCSTR lpString);
	BOOL LineTo(int x,int y);
	BOOL MoveTo(int x,int y);//lpptΪout
private:
	char *m_szFilePath;
	HDC dc;
};

