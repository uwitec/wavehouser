// CDialog_WareHouse.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_WareHouse.h"
#include "CControl_warehouse.h"
//#include "afxdialogex.h"


// CDialog_WareHouse 对话框

IMPLEMENT_DYNAMIC(CDialog_WareHouse, CDialog)

CDialog_WareHouse::CDialog_WareHouse(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_WareHouse::IDD, pParent)
{

}

CDialog_WareHouse::~CDialog_WareHouse()
{
}

void CDialog_WareHouse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_wName_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_cName_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_aName_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_tellPhone_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_email_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_WareHouse, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_WareHouse::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_WareHouse::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_WareHouse 消息处理程序


void CDialog_WareHouse::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wName_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的仓库名字");
		return;
	}
	m_cName_ctrl.GetWindowText(m_date.m_cname);
	if(m_date.m_cname.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的公司名字");
		return;
	}
	m_aName_ctrl.GetWindowText(m_date.m_aname);
	if(m_date.m_aname.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的管理员名字");
		return;
	}
	m_tellPhone_ctrl.GetWindowText(m_date.m_tell);
	if(m_date.m_tell.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的联系电话");
		return;
	}
	m_email_ctrl.GetWindowText(m_date.m_email);
	if(m_date.m_email.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的邮箱地址");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);

	CControl_warehouse tmpc;
	tmpc.SetData(&m_date);

	if(tmpc.Save())
		CRuntimeMessageBox::RunMessageBox("保存成功！");
	else
		CRuntimeMessageBox::RunMessageBox("保存失败！");
}


void CDialog_WareHouse::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL CDialog_WareHouse::OnInitDialog()
{
	CDialog::OnInitDialog();

	CControl_warehouse tmp;
	if (tmp.Search())
	{
		m_wName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_name);
		m_cName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_cname);
		m_aName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_aname);
		m_tellPhone_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_tell);
		m_email_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_email);
		m_detail_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_detail);
	}
	return FALSE;
}
