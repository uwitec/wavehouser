#pragma once
#include "afxwin.h"
#include "CStringTransform.h"
#include "CDate_check.h"
#include "CDate_Material.h"
#include "CDate_User.h"

// CDialog_Check 对话框

class CDialog_Check : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Check)

public:
	CDialog_Check(BOOL checkModal = TRUE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Check();

// 对话框数据
	enum { IDD = IDD_DLG_CHECK };
	
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_mName_ctrl;
	CEdit m_mNum_ctrl;
	CEdit m_total_ctrl;
	CEdit m_wName_ctrl;
	CComboBox m_cName_ctrl;
	CComboBox m_pName_ctrl;
	CEdit m_telPhone_ctrl;
	CEdit m_detail_ctrl;
	afx_msg void OnBnClickedAddMaterialBtn();
	afx_msg void OnBnClickedAddClassBtn();
	afx_msg void OnBnClickedAddPeopleBtn();
	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();

private:
	BOOL m_checkModal;
	CDate_check m_date;
	CDate_Material m_material;
	CDate_User m_user;
	CStringTransform m_dateChange;
};
