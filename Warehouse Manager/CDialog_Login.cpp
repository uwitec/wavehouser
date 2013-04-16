// CDialog_Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Login.h"
#include "CControl_Login.h"
//#include "afxdialogex.h"


// CDialog_Login �Ի���

IMPLEMENT_DYNAMIC(CDialog_Login, CDialog)

CDialog_Login::CDialog_Login(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Login::IDD, pParent)
{

}

CDialog_Login::~CDialog_Login()
{
}

void CDialog_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_user_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_ps_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Login, CDialog)
	ON_BN_CLICKED(IDOK, &CDialog_Login::OnBnClickedLogin)
	ON_BN_CLICKED(IDCANCEL, &CDialog_Login::OnBnClickedLoginOut)
END_MESSAGE_MAP()


// CDialog_Login ��Ϣ�������


void CDialog_Login::OnBnClickedLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialog::OnOK();

	CDate_User tmpUser;
	CString tmpu;
	m_user_ctrl.GetWindowText(tmpu);
	if(tmpu.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("�������û���");
		return;
	}
	CString tmps;
	m_ps_ctrl.GetWindowText(tmps);
	if(tmps.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("����������");
		return;
	}
	
	//m_user.m_name = tmpu;
	//m_user.m_pass = tmps;
	CControl_Login tmp;
	//tmp.SetData(&m_user);

	if(tmp.Search(tmpu,tmps) == 1)
	{
		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("��¼ʧ��");
	}
}


void CDialog_Login::OnBnClickedLoginOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

BOOL CDialog_Login::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_user_ctrl.SetWindowText(_T("admin"));
	m_ps_ctrl.SetWindowText(_T("123456"));

	return TRUE;
}
