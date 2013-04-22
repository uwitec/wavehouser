#pragma once

#include "CDate_Material.h"
#include "afxwin.h"
// CDialog_Material 对话框

class CDialog_Material : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Material)

public:
	CDialog_Material(const bool &isEdit = false,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Material();

// 对话框数据
	enum { IDD = IDD_DLG_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CDate_Material m_date;
	bool m_isEdit;
public:
	CEdit m_name_ctrl;
	CEdit m_modal_ctrl;
	CEdit m_manufacturer_ctrl;
	CEdit m_unit_ctrl;
	CEdit m_price_ctrl;
	CEdit m_detail_ctrl;
	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();
	virtual	BOOL OnInitDialog();

	void SetDate(const CDate_Material &date);
	CDate_Material GetDate();
};
