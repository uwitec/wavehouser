#pragma once
#include "afxwin.h"
#include "CDate_base.h"
#include "CStringTransform.h"
#include "afxcmn.h"
#include "CDate_User.h"
// CDialog_User_List 对话框

class CDialog_User_List : public CDialog
{
	DECLARE_DYNAMIC(CDialog_User_List)

public:
	CDialog_User_List(const bool &isExpot = false,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_User_List();

// 对话框数据
	enum { IDD = IDD_DLG_USER_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_name_ctrl;
	CEdit m_phone_ctrl;
	CEdit m_aBegin_ctrl;
	CEdit m_aEnd_ctrl;
	CEdit m_email_ctrl;
	CEdit m_keyWord_ctrl;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSearchBtn();
	void InitList();
	void ListCtrlShow();
private:
	CDate_search m_searcher;
	CStringTransform m_dateChange;
	bool m_isExport;
	CDate_User m_changeDate;
	vector<CDate_User > m_searchDates;
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedExport();
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClistmenuAdd();
	afx_msg void OnClistmenuEdit();
	afx_msg void OnClistmenuDel();
};
