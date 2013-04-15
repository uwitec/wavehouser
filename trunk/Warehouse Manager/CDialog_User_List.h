#pragma once
#include "afxwin.h"
#include "CDate_base.h"
#include "CStringTransform.h"
#include "afxcmn.h"

// CDialog_User_List �Ի���

class CDialog_User_List : public CDialog
{
	DECLARE_DYNAMIC(CDialog_User_List)

public:
	CDialog_User_List(const bool &isExpot = false,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_User_List();

// �Ի�������
	enum { IDD = IDD_DLG_USER_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
private:
	CDate_search m_searcher;
	CStringTransform m_dateChange;
	bool m_isExport;
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedExport();
};
