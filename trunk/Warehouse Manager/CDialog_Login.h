#pragma once
#include "afxwin.h"

#include "CDate_User.h"

// CDialog_Login �Ի���

class CDialog_Login : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Login)

public:
	CDialog_Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Login();

// �Ի�������
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_user_ctrl;
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedLoginOut();

	virtual BOOL OnInitDialog();
private:
	CDate_User m_user;

public:
	CEdit m_ps_ctrl;
};
