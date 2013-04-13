#pragma once


// CDialog_WareHouse 对话框

class CDialog_WareHouse : public CDialog
{
	DECLARE_DYNAMIC(CDialog_WareHouse)

public:
	CDialog_WareHouse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_WareHouse();

// 对话框数据
	enum { IDD = IDD_DLG_WAREHOUSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();
};
