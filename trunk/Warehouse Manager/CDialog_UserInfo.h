#pragma once


// CDialog_UserInfo �Ի���

class CDialog_UserInfo : public CDialog
{
	DECLARE_DYNAMIC(CDialog_UserInfo)

public:
	CDialog_UserInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_UserInfo();

// �Ի�������
	enum { IDD = IDD_DLG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
