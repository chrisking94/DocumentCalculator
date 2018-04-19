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
		,LONG lWeight=FW_NORMAL//是否粗体(范围为0－1000，字体加重程度：标准＝400，加重＝700）
		,BYTE bPitchAndFamily=FF_ROMAN|DEFAULT_PITCH//间距
		,BYTE bItalic=0
		,BYTE bUnderline=0
		,LONG lEscapment=0 //输出方向与当前坐标系X轴之间的字体旋转的角度，以1/10度为单位
		,LONG lOrientation= 0//每个字符与当前坐标系X轴之间的角度，以1/10度为单位
		,BYTE bStrikeOut=0//是否有中划线（不为0表示带中划线）
		,BYTE bCharSet=CHINESEBIG5_CHARSET//字符集
		,BYTE bOutPrecision=OUT_DEFAULT_PRECIS//输出精度
		,BYTE bClipPrecision=CLIP_DEFAULT_PRECIS//剪裁精度
		,BYTE bQuality=DEFAULT_QUALITY// 品质
		);
	HGDIOBJ SetFont(const LOGFONTA &font);
	COLORREF SetTextColor(COLORREF color=0);
	BOOL TextOut(int x,int y,LPCSTR lpString);
	BOOL LineTo(int x,int y);
	BOOL MoveTo(int x,int y);//lppt为out
private:
	char *m_szFilePath;
	HDC dc;
};

