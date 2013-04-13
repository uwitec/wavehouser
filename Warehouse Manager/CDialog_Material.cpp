// CDialog_Material.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material.h"


// CDialog_Material 对话框

IMPLEMENT_DYNAMIC(CDialog_Material, CDialog)

CDialog_Material::CDialog_Material(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Material::IDD, pParent)
{

}

CDialog_Material::~CDialog_Material()
{
}

void CDialog_Material::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_modal_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_manufacturer_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_unit_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_price_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Material, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_Material::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_Material::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_Material 消息处理程序


void CDialog_Material::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的材料名字");
		return;
	}
	m_modal_ctrl.GetWindowText(m_date.m_modal);
	if(m_date.m_modal.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的材料型号");
		return;
	}
	m_manufacturer_ctrl.GetWindowText(m_date.m_manufacturer);
	if(m_date.m_manufacturer.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的生产厂家");
		return;
	}
	m_unit_ctrl.GetWindowText(m_date.m_unit);
	if(m_date.m_unit.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的单位");
		return;
	}
	m_price_ctrl.GetWindowText(m_date.m_price);
	if(m_date.m_price.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的单价");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);
}


void CDialog_Material::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
