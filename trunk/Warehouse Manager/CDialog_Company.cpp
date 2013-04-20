// CDialog_Company.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Company.h"
#include "CControl_company.h"

// CDialog_Company 对话框

IMPLEMENT_DYNAMIC(CDialog_Company, CDialog)

CDialog_Company::CDialog_Company(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Company::IDD, pParent)
{

}

CDialog_Company::~CDialog_Company()
{
}

void CDialog_Company::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_companyName);
	DDX_Control(pDX, IDC_EDIT2, m_edit_wareName);
	DDX_Control(pDX, IDC_EDIT3, m_edit_address);
	DDX_Control(pDX, IDC_EDIT6, m_edit_tellPhone);
	DDX_Control(pDX, IDC_EDIT4, m_edit_tellMan);
	DDX_Control(pDX, IDC_EDIT7, m_edit_detail);
}


BEGIN_MESSAGE_MAP(CDialog_Company, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_Company::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_Company::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_Company 消息处理程序

BOOL CDialog_Company::OnInitDialog()
{
	CDialog::OnInitDialog();

	CControl_company tmp;
	if (tmp.Search())
	{
		m_edit_companyName.SetWindowText(CControl_bace::s_company.m_companyName);
		m_edit_address.SetWindowText(CControl_bace::s_company.m_address);
		m_edit_tellPhone.SetWindowText(CControl_bace::s_company.m_tellPhone);
		m_edit_tellMan.SetWindowText(CControl_bace::s_company.m_tellMan);
		m_edit_detail.SetWindowText(CControl_bace::s_company.m_detail);
	}
	m_edit_wareName.SetWindowText(CControl_bace::s_company.m_wareName);
	return FALSE;
}

void CDialog_Company::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_companyName.GetWindowText(m_company.m_companyName);
	if(m_company.m_companyName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的公司名字");
		return;
	}
	m_edit_wareName.GetWindowText(m_company.m_wareName);
	if(m_company.m_wareName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的仓库名字");
		return;
	}
	m_edit_address.GetWindowText(m_company.m_address);
	if(m_company.m_address.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的公司地址");
		return;
	}
	m_edit_tellPhone.GetWindowText(m_company.m_tellPhone);
	if(m_company.m_tellPhone.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的公司电话");
		return;
	}
	m_edit_tellMan.GetWindowText(m_company.m_tellMan);
	if(m_company.m_tellMan.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的联系人");
		return;
	}
	m_edit_detail.GetWindowText(m_company.m_detail);

	CControl_company tmpc;
	tmpc.SetData(&m_company);

	if(tmpc.Save())
		CRuntimeMessageBox::RunMessageBox("保存成功！");
	else
		CRuntimeMessageBox::RunMessageBox("保存失败！");
}

void CDialog_Company::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
