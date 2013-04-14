#pragma once

#include "CDialog_Piechart.h"

// CDialog_Check_Stats 对话框

class CDialog_Check_Stats : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Check_Stats)

public:
	CDialog_Check_Stats(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Check_Stats();

// 对话框数据
	enum { IDD = IDD_DLG_CHECK_STATS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CDateTimeCtrl m_tBegin_ctrl;
	CDateTimeCtrl m_tEnd_ctrl;
	afx_msg void OnBnClickedSearchBtn();
	CDialog_Piechart m_pieChart_ctrl;
};
