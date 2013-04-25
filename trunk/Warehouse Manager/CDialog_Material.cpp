// CDialog_Material.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material.h"
#include "CControl_material.h"
#include "CDialog_Material_List.h"
// CDialog_Material 对话框

IMPLEMENT_DYNAMIC(CDialog_Material, CDialog)

CDialog_Material::CDialog_Material(const bool &isEdit/* = false*/,CWnd* pParent /*=NULL*/)
: CDialog(CDialog_Material::IDD, pParent)
{
	m_isEdit = isEdit;
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

BOOL CDialog_Material::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_date.GetId().empty())
	{
		if(m_date.m_unit.IsEmpty())
		{
			CControl_material tmp;
			m_date = tmp.Search_byId(m_date.GetId());
		}
		m_name_ctrl.SetWindowText(m_date.m_name);
		m_modal_ctrl.SetWindowText(m_date.m_modal);
		m_manufacturer_ctrl.SetWindowText(m_date.m_manufacturer);
		m_unit_ctrl.SetWindowText(m_date.m_unit);
		m_price_ctrl.SetWindowText(m_date.m_price);
		m_detail_ctrl.SetWindowText(m_date.m_detail);
	}
	return FALSE;
}

void CDialog_Material::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_date.GetDel())
		if(::MessageBox(::GetActiveWindow(),_T("此信息已经被删除了，是否重新保存恢复？"),_T("提示"),MB_YESNO) == IDNO)
			return ;
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

	CControl_material tmp;
	tmp.SetData(&m_date);
	if (tmp.Save())
	{
		CRuntimeMessageBox::RunMessageBox("保存成功！");

		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("保存失败！");
	}
}


void CDialog_Material::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDialog_Material::SetDate( const CDate_Material &date )
{
	m_date = date;
}

CDate_Material CDialog_Material::GetDate()
{
	return m_date;
}
