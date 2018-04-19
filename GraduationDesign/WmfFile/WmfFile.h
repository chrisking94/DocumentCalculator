#pragma once
#include "Common.h"

class CWmfFile
{
	typedef enum
	{
		_savedc               = 0x01E ,//  将设备场景状态保存到堆栈
		_Realizepalette       = 0x035 ,//  将逻辑调色板映像为系统调色板
		_SETPALENTRIES        = 0x037 ,//
		_AbortDoc             = 0x052 ,//  取消一份文档的打印
		_CreatePalette        = 0x0F7 ,//  建立逻辑色彩调色板
		_SetBkMode            = 0x102 ,//  指定填充方式
		_setmapmode           = 0x103 ,//  设置设备场景的映射模式
		_SetROP2              = 0x104 ,//  设置绘图模式
		_SetRelabs            = 0x105 ,//
		_SetPolyFillMode      = 0x106 ,//  设置多边形的填充模式
		_SetStretchBltMode    = 0x107 ,//  指定函数的伸缩模式
		_SetTextCharacterExtra= 0x108 ,//  指定要在描绘的文本间插入的额外间距
		_RestoreDC            = 0x127 ,//  从堆栈恢复一个原先保存的设备场景
		_INVERTREGION         = 0x12A ,//
		_PAINTREGION          = 0x12B ,//
		_SELECTCLIPREGION     = 0x12C ,//
		_SelectObject         = 0x12D ,//  选入图形对象到设备场景
		_SetTextAlign         = 0x12E ,//  设置文本对齐方式
		_Resizepalette        = 0x139 ,//  修改逻辑调色板大小
		_DIBCREATEPATTERNBRUSH= 0x142 ,//
		_DeleteObject         = 0x1F0 ,//  删除GDI对象
		_CreatePatternBrush   = 0x1F9 ,//  创建一个刷子
		_SetBkColor           = 0x201 ,//  设置背景颜色
		_SetTextColor         = 0x209 ,//  设置文本颜色
		_SetTextJustification = 0x20A ,//  指定一个文本行应占据的额外空间
		_SetWindowOrg         = 0x20B ,//  设置设备场景窗口起点
		_SetWindowExt         = 0x20C ,//  设置设备场景窗口范围
		_SetViewportOrg       = 0x20D ,//  设置设备场景视口起点
		_SetViewportExt       = 0x20E ,//  设置设备场景视口范围
		_OffsetWindowOrg      = 0x20F ,//  平移设备场景窗口起点
		_OffsetViewportOrg    = 0x211 ,//  平移设备场景视口区域
		_LineTo               = 0x213 ,//  用当前画笔画一条线
		_MoveTo               = 0x214 ,//  为设备场景指定一个新的当前画笔位置
		_OffsetClipRgn        = 0x220 ,//  按指定量平移设备场景剪裁区
		_SetMapperFlags       = 0x231 ,//  选择与目标设备的纵横比相符的光栅字体
		_SelectPalette        = 0x234 ,//  选定调色板
		_CreatePenIndirect    = 0x2FA ,//  根据指定的LOGPEN结构创建一个画笔
		_CreateFontIndirect   = 0x2FB ,//  用指定的属性创建一种逻辑字体
		_CreateBrushIndirect  = 0x2FC ,//  在LOGBRUSH结构的基础上创建一个刷子
		_Polygon              = 0x324 ,//  描绘一个多边形
		_Polyline             = 0x325 ,//  用当前画笔描绘一系列线段
		_ScaleWindowExt       = 0x410 ,//  缩放设备场景窗口范围
		_ScaleViewportExt     = 0x412 ,//  缩放设备场景视口范围
		_ExcludeClipRect      = 0x415 ,//  从设备场景剪裁区中去掉一个矩形区
		_IntersectClipRect    = 0x416 ,//  为指定设备定义一个新的剪裁区
		_Ellipse              = 0x418 ,//  描绘一个椭圆
		_FloodFill            = 0x419 ,//  用选定的刷子在设备场景中填充一个区域
		_Rectangle            = 0x41B ,//  用选定的画笔描绘矩形
		_SetPixel             = 0x41F ,//  在设备场景中画点（像素的RGB值）
		_AnimatePalette       = 0x436 ,//  替换逻辑调色板中的项目
		_TextOut              = 0x521 ,//  文本绘图
		_PolyPolygon          = 0x538 ,//  用选定画笔描绘多边形
		_ExtFloodFill         = 0x548 ,//  用选择的刷子填充一个区域
		_RoundRect            = 0x61C ,//  画一个圆角矩形
		_PatBlt               = 0x61D ,//  用一个图案填充指定的设备场景
		_Escape               = 0x626 ,//  设备控制
		_CREATEREGION         = 0x6FF ,//
		_Arc                  = 0x817 ,//  画一个圆弧
		_Pie                  = 0x81A ,//  画一个饼图
		_Chord                = 0x830 ,//  画一个弦
		_BitBlt               = 0x922 ,//  将位图从一个设备场景复制到另一个
		_DIBBITBLT            = 0x940 ,//
		_ExtTextOut           = 0xA32 ,//  文本描绘
		_StretchBlt           = 0xB23 ,//  将位图从一个设备场景缩放到另一个
		_DIBSTRETCHBLT        = 0xB41 ,//
		_SETDIBTODEV          = 0xD33 ,//
		_StretchDIB           = 0xF43 ,//  将位图部分数据复制到指定的设备场景
	}GDIFunction;

	typedef struct WmfRcrdNode 
	{
		DWORD	dwRcrdWordsCnt;//记录长度，单位：字
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
		WORD	wType;//数据＝1，表示这是一个磁盘图元文件
		WORD	wNine;//这个数据总是＝9
		WORD	wVersion;//版本号＝300，支持设备无关位图
		DWORD	dwFileLength;//文件总长度＝42个字（10进制的66），66×2＝132字节
		WORD	wObjectCount;//文件中有1个对象
		WORD	wMaxRecordLength;//最大记录的长度＝1C 个字
		DWORD	dwReserved;//保留的
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
		WORD	wGraphUnit;//每英寸逻辑单位数目
		DWORD	dwReserved1;//总是0
		WORD	wCheckSum;
		int IsLegal() const
		{
			return dwKey == 0xD7CDC69A;
		}
	}m_Position;
	WmfRcrdNode	m_RcrdHead;
	char *m_szFilePath;
};

