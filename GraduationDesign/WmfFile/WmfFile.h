#pragma once
#include "Common.h"

class CWmfFile
{
	typedef enum
	{
		_savedc               = 0x01E ,//  ���豸����״̬���浽��ջ
		_Realizepalette       = 0x035 ,//  ���߼���ɫ��ӳ��Ϊϵͳ��ɫ��
		_SETPALENTRIES        = 0x037 ,//
		_AbortDoc             = 0x052 ,//  ȡ��һ���ĵ��Ĵ�ӡ
		_CreatePalette        = 0x0F7 ,//  �����߼�ɫ�ʵ�ɫ��
		_SetBkMode            = 0x102 ,//  ָ����䷽ʽ
		_setmapmode           = 0x103 ,//  �����豸������ӳ��ģʽ
		_SetROP2              = 0x104 ,//  ���û�ͼģʽ
		_SetRelabs            = 0x105 ,//
		_SetPolyFillMode      = 0x106 ,//  ���ö���ε����ģʽ
		_SetStretchBltMode    = 0x107 ,//  ָ������������ģʽ
		_SetTextCharacterExtra= 0x108 ,//  ָ��Ҫ�������ı������Ķ�����
		_RestoreDC            = 0x127 ,//  �Ӷ�ջ�ָ�һ��ԭ�ȱ�����豸����
		_INVERTREGION         = 0x12A ,//
		_PAINTREGION          = 0x12B ,//
		_SELECTCLIPREGION     = 0x12C ,//
		_SelectObject         = 0x12D ,//  ѡ��ͼ�ζ����豸����
		_SetTextAlign         = 0x12E ,//  �����ı����뷽ʽ
		_Resizepalette        = 0x139 ,//  �޸��߼���ɫ���С
		_DIBCREATEPATTERNBRUSH= 0x142 ,//
		_DeleteObject         = 0x1F0 ,//  ɾ��GDI����
		_CreatePatternBrush   = 0x1F9 ,//  ����һ��ˢ��
		_SetBkColor           = 0x201 ,//  ���ñ�����ɫ
		_SetTextColor         = 0x209 ,//  �����ı���ɫ
		_SetTextJustification = 0x20A ,//  ָ��һ���ı���Ӧռ�ݵĶ���ռ�
		_SetWindowOrg         = 0x20B ,//  �����豸�����������
		_SetWindowExt         = 0x20C ,//  �����豸�������ڷ�Χ
		_SetViewportOrg       = 0x20D ,//  �����豸�����ӿ����
		_SetViewportExt       = 0x20E ,//  �����豸�����ӿڷ�Χ
		_OffsetWindowOrg      = 0x20F ,//  ƽ���豸�����������
		_OffsetViewportOrg    = 0x211 ,//  ƽ���豸�����ӿ�����
		_LineTo               = 0x213 ,//  �õ�ǰ���ʻ�һ����
		_MoveTo               = 0x214 ,//  Ϊ�豸����ָ��һ���µĵ�ǰ����λ��
		_OffsetClipRgn        = 0x220 ,//  ��ָ����ƽ���豸����������
		_SetMapperFlags       = 0x231 ,//  ѡ����Ŀ���豸���ݺ������Ĺ�դ����
		_SelectPalette        = 0x234 ,//  ѡ����ɫ��
		_CreatePenIndirect    = 0x2FA ,//  ����ָ����LOGPEN�ṹ����һ������
		_CreateFontIndirect   = 0x2FB ,//  ��ָ�������Դ���һ���߼�����
		_CreateBrushIndirect  = 0x2FC ,//  ��LOGBRUSH�ṹ�Ļ����ϴ���һ��ˢ��
		_Polygon              = 0x324 ,//  ���һ�������
		_Polyline             = 0x325 ,//  �õ�ǰ�������һϵ���߶�
		_ScaleWindowExt       = 0x410 ,//  �����豸�������ڷ�Χ
		_ScaleViewportExt     = 0x412 ,//  �����豸�����ӿڷ�Χ
		_ExcludeClipRect      = 0x415 ,//  ���豸������������ȥ��һ��������
		_IntersectClipRect    = 0x416 ,//  Ϊָ���豸����һ���µļ�����
		_Ellipse              = 0x418 ,//  ���һ����Բ
		_FloodFill            = 0x419 ,//  ��ѡ����ˢ�����豸���������һ������
		_Rectangle            = 0x41B ,//  ��ѡ���Ļ���������
		_SetPixel             = 0x41F ,//  ���豸�����л��㣨���ص�RGBֵ��
		_AnimatePalette       = 0x436 ,//  �滻�߼���ɫ���е���Ŀ
		_TextOut              = 0x521 ,//  �ı���ͼ
		_PolyPolygon          = 0x538 ,//  ��ѡ�������������
		_ExtFloodFill         = 0x548 ,//  ��ѡ���ˢ�����һ������
		_RoundRect            = 0x61C ,//  ��һ��Բ�Ǿ���
		_PatBlt               = 0x61D ,//  ��һ��ͼ�����ָ�����豸����
		_Escape               = 0x626 ,//  �豸����
		_CREATEREGION         = 0x6FF ,//
		_Arc                  = 0x817 ,//  ��һ��Բ��
		_Pie                  = 0x81A ,//  ��һ����ͼ
		_Chord                = 0x830 ,//  ��һ����
		_BitBlt               = 0x922 ,//  ��λͼ��һ���豸�������Ƶ���һ��
		_DIBBITBLT            = 0x940 ,//
		_ExtTextOut           = 0xA32 ,//  �ı����
		_StretchBlt           = 0xB23 ,//  ��λͼ��һ���豸�������ŵ���һ��
		_DIBSTRETCHBLT        = 0xB41 ,//
		_SETDIBTODEV          = 0xD33 ,//
		_StretchDIB           = 0xF43 ,//  ��λͼ�������ݸ��Ƶ�ָ�����豸����
	}GDIFunction;

	typedef struct WmfRcrdNode 
	{
		DWORD	dwRcrdWordsCnt;//��¼���ȣ���λ����
		WORD	wGDIFunction;
		BYTE	*pData;

		WmfRcrdNode	*next;

		WmfRcrdNode():dwRcrdWordsCnt(0){}
		GDIFunction GetFunction() const{return (GDIFunction)wGDIFunction;}
		DWORD GetLength() const
		{
			if(next) return dwRcrdWordsCnt + next->GetLength();
			else return dwRcrdWordsCnt;
		}
		void WriteToFile(FILE *fp) const
		{
			if(dwRcrdWordsCnt != 0)
			{
				WriteStruct("it",(void*)this,fp);
				_fwrite(pData,fp);
			}
			if(next) next->WriteToFile(fp);
		}
	}WmfRcrdNode;
public:
	CWmfFile(char *szFilePath);
	~CWmfFile(void);

	void Parse();
	void AppendRecord(WmfRcrdNode *pRcrd);
private:
	struct  WmfHeader
	{
		WORD	wType;//���ݣ�1����ʾ����һ������ͼԪ�ļ�
		WORD	wNine;//����������ǣ�9
		WORD	wVersion;//�汾�ţ�300��֧���豸�޹�λͼ
		DWORD	dwFileLength;//�ļ��ܳ��ȣ�42���֣�10���Ƶ�66����66��2��132�ֽ�
		WORD	wObjectCount;//�ļ�����1������
		WORD	wMaxRecordLength;//����¼�ĳ��ȣ�1C ����
		DWORD	dwReserved;//������
		WmfHeader():wType(1),wNine(9),wVersion(300),wObjectCount(1),wMaxRecordLength(0){}
		void WriteToFile(FILE *fp) const
		{
			WriteStruct("tttitti",(void*)this,fp);
		}
	}m_Header;
	struct	PositionHeader
	{
		DWORD	dwKey;
		WORD	wReserved;
		WORD	wLeft;
		WORD	wTop;
		WORD	wRight;
		WORD	wBottom;
		WORD	wGraphUnit;//ÿӢ���߼���λ��Ŀ
		DWORD	dwReserved1;//����0
		WORD	wCheckSum;
		int IsLegal() const
		{
			return dwKey == 0xD7CDC69A;
		}
	}m_Position;
	WmfRcrdNode	m_RcrdHead;
	char *m_szFilePath;
};

