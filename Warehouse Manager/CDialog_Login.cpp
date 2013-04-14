// CDialog_Login.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Login.h"
#include "afxdialogex.h"


// CDialog_Login 对话框

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
	DDX_Control(pDX, IDC_EDIT2, m_pass_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Login, CDialog)
	ON_BN_CLICKED(IDOK, &CDialog_Login::OnBnClickedLogin)
	ON_BN_CLICKED(IDCANCEL, &CDialog_Login::OnBnClickedLoginOut)
END_MESSAGE_MAP()


// CDialog_Login 消息处理程序


void CDialog_Login::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
}


void CDialog_Login::OnBnClickedLoginOut()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
