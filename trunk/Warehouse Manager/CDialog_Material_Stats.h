#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "CDialog_Piechart.h"
#include "CDate_base.h"
#include "CDate_Material.h"
// CDialog_Material_Stats 对话框

class CDialog_Material_Stats : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Material_Stats)

public:
	CDialog_Material_Stats(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Material_Stats();

// 对话框数据
	enum { IDD = IDD_DLG_MATERIAL_STATS };

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK(){ return  ;};
	virtual void OnCancel(){ return  ;};
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_modal;
	CDateTimeCtrl m_tBegin_ctrl;
	CDateTimeCtrl m_tEnd_ctrl;
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedCheck2();

	CDialog_Piechart m_pieChart_ctrl;

private:
	CDate_search m_searcher;
	vector<CDate_Material> m_searchDates;
	void ShowEllipse();
	void FormatSearchDates(const int &modal = 0);
};
