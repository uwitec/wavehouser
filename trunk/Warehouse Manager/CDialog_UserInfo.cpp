// CDialog_UserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_UserInfo.h"
#include "CControl_user.h"
// CDialog_UserInfo 对话框

IMPLEMENT_DYNAMIC(CDialog_UserInfo, CDialog)

CDialog_UserInfo::CDialog_UserInfo(const bool &isSelf/* = true*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_UserInfo::IDD, pParent)
{
	m_isSelf = isSelf;
}

CDialog_UserInfo::~CDialog_UserInfo()
{
}

void CDialog_UserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_cName_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_age_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_phone_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_email_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_UserInfo, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_UserInfo::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_UserInfo::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_UserInfo 消息处理程序

BOOL CDialog_UserInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_isSelf )
	{
		if(!m_date.GetId().empty())
		{
			m_name_ctrl.SetWindowText(m_date.m_name);
			m_cName_ctrl.SetWindowText(m_date.m_companyName);
			m_age_ctrl.SetWindowText(m_date.m_age);
			m_phone_ctrl.SetWindowText(m_date.m_tellPhone);
			m_email_ctrl.SetWindowText(m_date.m_email);
			m_detail_ctrl.SetWindowText(m_date.m_detail);
		}
	}
	else 
	{
		CControl_user tmp;
		if (tmp.Search())
		{
			m_name_ctrl.SetWindowText(CControl_bace::s_userInfo.m_name);
			m_cName_ctrl.SetWindowText(CControl_bace::s_userInfo.m_companyName);
			m_age_ctrl.SetWindowText(CControl_bace::s_userInfo.m_age);
			m_phone_ctrl.SetWindowText(CControl_bace::s_userInfo.m_tellPhone);
			m_email_ctrl.SetWindowText(CControl_bace::s_userInfo.m_email);
			m_detail_ctrl.SetWindowText(CControl_bace::s_userInfo.m_detail);
		}
	}
	return FALSE;
}


void CDialog_UserInfo::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的名字");
		return;
	}
	m_cName_ctrl.GetWindowText(m_date.m_companyName);
	if(m_date.m_companyName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的公司名字");
		return;
	}
	m_age_ctrl.GetWindowText(m_date.m_age);
	if(m_date.m_age.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的年龄");
		return;
	}
	m_phone_ctrl.GetWindowText(m_date.m_tellPhone);
	if(m_date.m_tellPhone.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的电话");
		return;
	}
	m_email_ctrl.GetWindowText(m_date.m_email);
	if(m_date.m_email.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的EMail");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);

	CControl_user tmp;
	tmp.SetData(&m_date);
	if (tmp.Save(m_isSelf))
	{
		CRuntimeMessageBox::RunMessageBox("保存成功！");

		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("保存失败！");
	}
}


void CDialog_UserInfo::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDialog_UserInfo::SetDate( const CDate_User &date )
{
	m_date = date;
}
