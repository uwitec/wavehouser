// Warehouse ManagerDlg.h : ͷ�ļ�
//

#pragma once

#include "CDialog_Company.h"

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
};
