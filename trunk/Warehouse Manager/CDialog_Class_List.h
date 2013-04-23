#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "CDate_Class.h"

// CDialog_Class_List 对话框

class CDialog_Class_List : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Class_List)

public:
	CDialog_Class_List(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Class_List();

// 对话框数据
	enum { IDD = IDD_DLG_CLASS_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cName_ctrl;
	CEdit m_pName_ctrl;
	CEdit m_coName_ctrl;
	CEdit m_tellPhone;
	CEdit m_keyWord_ctrl;
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClistmenuAdd();
	afx_msg void OnClistmenuEdit();
	afx_msg void OnClistmenuDel();
private:
	CDate_search m_searcher;
	CStringTransform m_stringTranser;

	CDate_Class m_changeDate;
	vector<CDate_Class > m_searchDates;

	void InitList();
	void ListCtrlShow();
public:
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedExport();

};
