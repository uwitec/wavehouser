#pragma once


// CDialog_Material �Ի���

class CDialog_Material : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Material)

public:
	CDialog_Material(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Material();

// �Ի�������
	enum { IDD = IDD_DLG_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
