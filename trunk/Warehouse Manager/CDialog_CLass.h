#pragma once

#include "CDate_Class.h"
#include "afxwin.h"
// CDialog_CLass 对话框

class CDialog_CLass : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_CLass)

public:
	CDialog_CLass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_CLass();

// 对话框数据
	enum { IDD = IDD_DLG_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CDate_Class m_date;
public:
	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();

	CEdit m_name_ctrl;
	CEdit m_pName_ctrl;
	CEdit m_num_ctrl;
	CEdit m_telphone_ctrl;
	CEdit m_contact_ctrl;
	CEdit m_detail_ctrl;
};
