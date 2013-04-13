#pragma once
#include "CDate_base.h"
#include "CDate_Material.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "CStringTransform.h"
// CDialog_Material_List 对话框

class CDialog_Material_List : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Material_List)

public:
	CDialog_Material_List(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Material_List();

// 对话框数据
	enum { IDD = IDD_DLG_MATERIAL_LIST };
	
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CDate_search m_searcher;
	CStringTransform m_stringTranser;
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
};
