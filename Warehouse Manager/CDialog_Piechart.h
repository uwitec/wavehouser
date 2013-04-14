#pragma once
#include "afxdtctl.h"

// CDialog_Piechart 对话框

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
	void SetEPos(const CRect &pos);	
private:
	CRect m_eRect;
};
