#pragma once

#include "CDialog_Piechart.h"

// CDialog_Check_Stats �Ի���

class CDialog_Check_Stats : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Check_Stats)

public:
	CDialog_Check_Stats(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Check_Stats();

// �Ի�������
	enum { IDD = IDD_DLG_CHECK_STATS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CDateTimeCtrl m_tBegin_ctrl;
	CDateTimeCtrl m_tEnd_ctrl;
	afx_msg void OnBnClickedSearchBtn();
	CDialog_Piechart m_pieChart_ctrl;
};
