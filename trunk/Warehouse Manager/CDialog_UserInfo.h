#pragma once


// CDialog_UserInfo 对话框

class CDialog_UserInfo : public CDialog
{
	DECLARE_DYNAMIC(CDialog_UserInfo)

public:
	CDialog_UserInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_UserInfo();

// 对话框数据
	enum { IDD = IDD_DLG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
