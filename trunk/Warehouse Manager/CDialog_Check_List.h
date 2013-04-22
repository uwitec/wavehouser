#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "CDate_check.h"
#include "CDate_base.h"
#include "CStringTransform.h"
// CDialog_Check_List 对话框

class CDialog_Check_List : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Check_List)

public:
	CDialog_Check_List(const bool &isExpot = false,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Check_List();

// 对话框数据
	enum { IDD = IDD_DLG_CHECK_LIST };
	
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_checkModal_ctrl;
	CEdit m_mName_ctrl;
	CComboBox m_class_ctrl;
	CComboBox m_user_ctrl;
	CDateTimeCtrl m_tBegin_ctrl;
	CDateTimeCtrl m_tEnd_ctrl;
	CEdit m_keyWord_ctrl;
	CListCtrl m_list;
	afx_msg void OnBnClickedSearchBtn();

private:
	CDate_search m_searcher;
	CStringTransform m_dateChange;

	CDate_check m_changeDate;
	vector<CDate_check > m_searchDates;
	vector<CDate_User> m_allUser;
	vector<CDate_Class> m_allClass;
	bool m_isExport;
	void InitComobox(const int &initFlag = -1);
	void InitList();

	void ListCtrlShow();
public:
	afx_msg void OnBnClickedExport();
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClistmenuAdd();
	afx_msg void OnClistmenuEdit();
	afx_msg void OnClistmenuDel();
};
