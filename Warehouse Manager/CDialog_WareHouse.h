#pragma once
#include "afxwin.h"
#include "CDate_Warehouse.h"

// CDialog_WareHouse 对话框

class CDialog_WareHouse : public CDialog
{
	DECLARE_DYNAMIC(CDialog_WareHouse)

public:
	CDialog_WareHouse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_WareHouse();

// 对话框数据
	enum { IDD = IDD_DLG_WAREHOUSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();
	CEdit m_wName_ctrl;
	CEdit m_cName_ctrl;
	CEdit m_aName_ctrl;
	CEdit m_tellPhone_ctrl;
	CEdit m_email_ctrl;
	CEdit m_detail_ctrl;

private:
	CDate_warehouse m_date;
};
