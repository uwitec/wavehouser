#pragma once


// CDialog_Material 对话框

class CDialog_Material : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Material)

public:
	CDialog_Material(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Material();

// 对话框数据
	enum { IDD = IDD_DLG_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
