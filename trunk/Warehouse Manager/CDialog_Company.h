#pragma once

#include "CDate_Company.h"
#include "afxwin.h"
// CDialog_Company �Ի���

class CDialog_Company : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Company)

public:
	CDialog_Company(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Company();

// �Ի�������
	enum { IDD = IDD_DLG_COMPANY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CDate_Company m_company;
public:
	afx_msg void OnBnClickedBtbSave();
	CEdit m_edit_companyName;
	CEdit m_edit_wareName;
	CEdit m_edit_address;
	CEdit m_edit_tellPhone;
	CEdit m_edit_tellMan;
	CEdit m_edit_detail;
	afx_msg void OnBnClickedBtbQuit();
};
