#pragma once

#include "stdafx.h"
#include "resource.h"
#include <atlmisc.h>
#include <atlctrls.h>
#include <iostream>
#include <vector>

#define M_PI     3.14159265358979323846
#define ER(x,y)  abs(fabs(x*x + y*y))  //直角第三边

using namespace std;

struct PiePoint{
	CPoint sPoint;
	CPoint ePoint;
};
struct PieData{
	CString PieName;    //名字
	COLORREF PieColor;  //颜色
	float PiePer;       //百分比
	float PicAngle;     //角度
	int PieNum;         //个数
	PiePoint pPoint;    //起始点
	CString PieOther;   //其他
};


class CEllipseStatic:public CWindowImpl<CEllipseStatic,CStatic>
{
public:
	CEllipseStatic(void);
	CEllipseStatic(vector<PieData > pieDatas);
	virtual ~CEllipseStatic(void);

	BOOL CreateEllipseStatic(HWND parenHwnd,CRect rectArea ,CRect ellipseRect ,CRect detailRect);
	BOOL CreateEllipseStatic(HWND parenHwnd,CRect rectArea ,CRect ellipseRect ,CRect detailRect,vector<PieData > pieDatas);
	BOOL CreateEllipseStatic(HWND parenHwnd,CRect rectArea ,CPoint ellipsePoint , int ellipseWidth,CPoint detailPoint,int detailWidth,vector<PieData > pieDatas);

	BOOL ShowEllipseStatic(const bool &isShow = TRUE);
	void SetAreaBkColor(COLORREF areaBkColor,COLORREF ellipseBkColor,COLORREF detailBkColor);

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);

	void FormatStaticDatas();
	DECLARE_WND_CLASS( _T("CEllipseStatic") )
	BEGIN_MSG_MAP(CEllipseStatic)
		MESSAGE_HANDLER( WM_PAINT,			OnPaint )
		MESSAGE_HANDLER( WM_DESTROY,		OnDestroy)
		MESSAGE_HANDLER( WM_NCHITTEST,		OnNcHitTest)
	END_MSG_MAP()

private:
	void DoPaintEllipse(CPaintDC &pDc);
	void DoPaintDetail(CPaintDC &pDc);
	void FormatStaticPercen();

	bool GetNormalFont(CFont &fonts,int height=12,int weight=400)
	{
		LOGFONT lf;
		RtlZeroMemory(&lf, sizeof(LOGFONT));
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = height ;
		lf.lfWeight = weight;
		_tcscpy(lf.lfFaceName, TEXT("新宋体") );
		if(fonts != NULL)
		{
			fonts.DeleteObject();
		}
		return fonts.CreateFontIndirect(&lf);
	}
	COLORREF m_AreaBkColor;
	COLORREF m_EllipseBkColor;
	COLORREF m_DetailBkColor;

	HWND m_ParentHwnd;
	CRect m_RectArea;
	CRect m_ClientRect;
	CRect m_EllipseRect;
	CRect m_DetaiRect;
	CFont m_TextFont, m_TextFont2;
	float m_R,m_EllipseR;
	CPoint m_OPoint;
	vector<PieData > m_PieDatas;
	int m_DataNum;
	//vector<PiePoint > m_PiePoints;
};
