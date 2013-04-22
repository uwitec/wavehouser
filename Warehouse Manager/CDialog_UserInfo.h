#pragma once

#include "CDate_User.h"
#include "afxwin.h"

// CDialog_UserInfo �Ի���

class CDialog_UserInfo : public CDialog
{
	DECLARE_DYNAMIC(CDialog_UserInfo)

public:
	CDialog_UserInfo(const bool &isSelf = true,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_UserInfo();

// �Ի�������
	enum { IDD = IDD_DLG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CDate_User m_date;
	bool m_isSelf;
public:
	CEdit m_name_ctrl;
	CEdit m_cName_ctrl;
	CEdit m_age_ctrl;
	CEdit m_phone_ctrl;
	CEdit m_email_ctrl;
	CEdit m_detail_ctrl;
	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();
	virtual	BOOL OnInitDialog();

	void SetDate(const CDate_User &date);
	CDate_User GetDate()
	{
		return m_date;
	}
};
