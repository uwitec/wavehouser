#pragma once
#include "CDate_base.h"
#include "CDate_Material.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "CStringTransform.h"
// CDialog_Material_List �Ի���

class CDialog_Material_List : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Material_List)

public:
	CDialog_Material_List(const bool &isExpot = false,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Material_List();

// �Ի�������
	enum { IDD = IDD_DLG_MATERIAL_LIST };
	
	virtual BOOL OnInitDialog();
	virtual void OnOK(){ return  ;};
	virtual void OnCancel(){ return  ;};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CDate_search m_searcher;
	CStringTransform m_stringTranser;
	bool m_isExport;
	CDate_Material m_changeDate;
	vector<CDate_Material > m_searchDates;
public:
	CEdit m_name_ctrl;
	CEdit m_manufacturer_ctrl;
	CEdit m_modal_ctrl;
	CEdit m_price_ctrl;
	CEdit m_unit_ctrl;
	CEdit m_keyword_ctrl;
	CListCtrl m_list;
	afx_msg void OnBnClickedSearchBtn();
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void InitList();
	afx_msg void OnBnClickedExport();
	void ListCtrlShow();
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClistmenuAdd();
	afx_msg void OnClistmenuEdit();
	afx_msg void OnClistmenuDel();
};