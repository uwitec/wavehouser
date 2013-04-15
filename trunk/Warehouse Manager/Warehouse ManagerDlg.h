// Warehouse ManagerDlg.h : 头文件
//

#pragma once

#include "CDialog_Company.h"
#include "CDialog_Material.h"
#include "CDialog_UserInfo.h"
#include "CDialog_WareHouse.h"
#include "CDialog_Material_List.h"
#include "CDialog_Check.h"
#include "CDialog_Check_list.h"
#include "CDialog_Check_Stats.h"
#include "CDialog_User_List.h"
// CWarehouseManagerDlg 对话框
class CWarehouseManagerDlg : public CDialog
{
// 构造
public:
	CWarehouseManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WAREHOUSEMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCompanyBtn();
	afx_msg void OnUserInfoBtn();
	afx_msg void OnMaterialBtn();
	afx_msg void OnWareHouseBtn();
	afx_msg void OnAddMatrtial();
	afx_msg void OnEditMaterial();
	afx_msg void OnSearchMaterial();
	afx_msg void OnSearchMaterialState();
	afx_msg void OnExit();

private:
	CDialog_Material_List *m_MaterialList;
	CDialog_Material_List *m_MaterialList_out;
	CDialog_Check_Stats *m_MaterialStats;

	CDialog_Check_List *m_checkList;
	CDialog_Check_List *m_checkList_out;
	CDialog_Check_Stats *m_checkStats;
		
	CDialog_User_List *m_UserList;
public:
	afx_msg void OnAddBuyBtn();
	afx_msg void OnAddPayBtn();
	afx_msg void OnCheckSearchBtn();
	afx_msg void OnCheckStats();
	afx_msg void OnOutM();
	afx_msg void OnOutUser();
	afx_msg void OnOutCheck();
	afx_msg void OnSetSystem();
	afx_msg void OnHelp();
	afx_msg void OnAbout();
};
