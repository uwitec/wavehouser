#pragma once
#include "afxdtctl.h"

// CDialog_Piechart 对话框

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

class CDialog_Piechart : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Piechart)

public:
	CDialog_Piechart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Piechart();

// 对话框数据
	enum { IDD = IDD_DLG_CHECK_STATS };
	
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	
	void SetEPos();	
	void FormatStaticDatas(const vector<PieData > &dates);
	void SetEPos(const CRect &ellipseRect,const CRect &detailRect);
	void DoPaintDetail( CPaintDC &pDc );
	void DoPaintEllipse( CPaintDC &pDc );
private:
	void SortDates(const vector<PieData > &dates);

	bool GetNormalFont(CFont &fonts,int height=12,int weight=400)
	{
		LOGFONT lf;
		RtlZeroMemory(&lf, sizeof(LOGFONT));
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = height ;
		lf.lfWeight = weight;
		_tcscpy(lf.lfFaceName, TEXT("新宋体") );
		if(fonts.GetSafeHandle() != NULL)
		{
			fonts.DeleteObject();
		}
		return fonts.CreateFontIndirect(&lf);
	}
	CRect m_eRect;

	COLORREF m_AreaBkColor;
	COLORREF m_EllipseBkColor;
	COLORREF m_DetailBkColor;

	CRect m_RectArea;
	CRect m_ClientRect;
	CRect m_EllipseRect;
	CRect m_DetaiRect;
	CRect m_TotalRect;
	CFont m_TextFont, m_TextFont2;
	float m_R,m_EllipseR;
	CPoint m_OPoint;
	vector<PieData > m_PieDatas;
	int m_DataNum;
};
