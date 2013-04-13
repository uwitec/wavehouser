// Warehouse ManagerDlg.h : ͷ�ļ�
//

#pragma once

#include "CDialog_Company.h"
#include "CDialog_Material.h"
#include "CDialog_UserInfo.h"
#include "CDialog_WareHouse.h"
#include "CDialog_Material_List.h"
#include "CDialog_Check.h"
#include "CDialog_Check_list.h"
// CWarehouseManagerDlg �Ի���
class CWarehouseManagerDlg : public CDialog
{
// ����
public:
	CWarehouseManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WAREHOUSEMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CDialog_Check_List *m_checkLisk;
public:
	afx_msg void OnAddBuyBtn();
	afx_msg void OnAddPayBtn();
};
