#pragma once


// CDialog_WareHouse �Ի���

class CDialog_WareHouse : public CDialog
{
	DECLARE_DYNAMIC(CDialog_WareHouse)

public:
	CDialog_WareHouse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_WareHouse();

// �Ի�������
	enum { IDD = IDD_DLG_WAREHOUSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtbSave();
	afx_msg void OnBnClickedBtbQuit();
};
