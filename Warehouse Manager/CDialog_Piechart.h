#pragma once
#include "afxdtctl.h"

// CDialog_Piechart �Ի���

struct PiePoint{
	CPoint sPoint;
	CPoint ePoint;
};
struct PieData{
	CString PieName;    //����
	COLORREF PieColor;  //��ɫ
	float PiePer;       //�ٷֱ�
	float PicAngle;     //�Ƕ�
	int PieNum;         //����
	PiePoint pPoint;    //��ʼ��
	CString PieOther;   //����
};

class CDialog_Piechart : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Piechart)

public:
	CDialog_Piechart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Piechart();

// �Ի�������
	enum { IDD = IDD_DLG_CHECK_STATS };
	
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
		_tcscpy(lf.lfFaceName, TEXT("������") );
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
