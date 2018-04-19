#include "StdAfx.h"
#include "WmfFile.h"
#include "Common.h"
#include <string>
#include <Windows.h>

CWmfFile::CWmfFile(char *szFilePath)
{
	_strcpy(m_szFilePath,szFilePath);
	dc = CreateMetaFileA(m_szFilePath); 
}


CWmfFile::~CWmfFile(void)
{
	HMETAFILE hWMF;

	hWMF = CloseMetaFile(dc);            //关闭图元文件设备场景,返回向量图像句柄
	::DeleteMetaFile( hWMF);                 //删除设备场景
	::DeleteDC(dc);
}

void CWmfFile::Parse()
{
	
	SIZE DCsize;
	LOGFONTA font;
	
}

HGDIOBJ CWmfFile::SetFont(
	char *szFaceName
	,LONG lHeight 
	,LONG lWidth
	,LONG lWeight
	,BYTE bPitchAndFamily
	,BYTE bItalic
	,BYTE bUnderline
	,LONG lEscapment
	,LONG lOrientation
	,BYTE bStrikeOut
	,BYTE bCharSet
	,BYTE bOutPrecision
	,BYTE bClipPrecision
	,BYTE bQuality
	)
{
	HFONT hFont=::CreateFontA(lHeight,lWeight,lEscapment,lOrientation,lWeight,bItalic,bUnderline,bStrikeOut,bCharSet,bOutPrecision,bClipPrecision,bQuality,bPitchAndFamily,szFaceName);
	return ::SelectObject(dc,hFont);
}

HGDIOBJ CWmfFile::SetFont(const LOGFONTA &font)
{
	HFONT hFont = ::CreateFontIndirectA(&font);    //创建逻辑字体
	return ::SelectObject(dc,hFont);
}

COLORREF CWmfFile::SetTextColor(COLORREF color)
{
	return ::SetTextColor(dc,color);
}

BOOL CWmfFile::TextOut(int x,int y,LPCSTR lpString)
{
	return ::TextOutA(dc,x,y,lpString,strlen(lpString)+1);
}

BOOL CWmfFile::LineTo(int x,int y)
{
	return ::LineTo(dc,x,y);
}

BOOL CWmfFile::MoveTo(int x,int y)
{
	POINT point;
	return ::MoveToEx(dc,x,y,&point);
}
