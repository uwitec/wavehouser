// CDialog_Check.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check.h"
//#include "afxdialogex.h"
#include "CDialog_Material.h"
#include "CDialog_UserInfo.h"
#include "CDialog_Class.h"

// CDialog_Check 对话框

IMPLEMENT_DYNAMIC(CDialog_Check, CDialog)

CDialog_Check::CDialog_Check(BOOL checkModal /*= TRUE*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Check::IDD, pParent)
{
	m_checkModal =  checkModal;
}

CDialog_Check::~CDialog_Check()
{
}

void CDialog_Check::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_mName_ctrl);
	DDX_Control(pDX, IDC_EDIT5, m_mNum_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_total_ctrl);
	DDX_Control(pDX, IDC_EDIT8, m_wName_ctrl);
	DDX_Control(pDX, IDC_COMBO2, m_cName_ctrl);
	DDX_Control(pDX, IDC_COMBO3, m_pName_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_telPhone_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Check, CDialog)
	//ON_WM_INITDIALOG()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Check::OnBnClickedAddMaterialBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_Check::OnBnClickedAddClassBtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog_Check::OnBnClickedAddPeopleBtn)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_Check::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_Check::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_Check 消息处理程序

BOOL CDialog_Check::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_checkModal)
	{
		SetWindowText(_T("购进"));
	}
	else
	{
		SetWindowText(_T("支出"));
	}

	return TRUE;
}

void CDialog_Check::OnBnClickedAddMaterialBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_Material dlg;
	dlg.DoModal();
}


void CDialog_Check::OnBnClickedAddClassBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_CLass dlg;
	dlg.DoModal();
}


void CDialog_Check::OnBnClickedAddPeopleBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_UserInfo dlg;
	dlg.DoModal();
}


void CDialog_Check::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mName_ctrl.GetWindowText(m_date.m_mName);
	if(m_date.m_mName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请选择正确的材料");
	}
	CString tmp;
	m_mNum_ctrl.GetWindowText(tmp);
	if(tmp.IsEmpty() || tmp.SpanIncluding(_T("1234567890")) != tmp)
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的数目！");
	}
	else
	{
		m_date.m_num = atoi((const char *)tmp.GetBuffer(tmp.GetLength()));
		double price = atof(m_dateChange.CStringtostring(m_material.m_price).c_str());
		tmp.Format(_T("%ld"),m_date.m_num * price);
		m_total_ctrl.SetWindowText(tmp);
		m_date.m_total = price;
	}
	m_wName_ctrl.GetWindowText(m_date.m_operateWare);
	if(m_date.m_operateWare.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的仓库");
	}
	m_cName_ctrl.GetWindowText(m_date.m_operateClass);
	if(m_date.m_operateClass.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的部门名称");
	}
	m_pName_ctrl.GetWindowText(m_date.m_operatePeople);
	if(m_date.m_operatePeople.IsEmpty())
	{
		if(m_checkModal)
			CRuntimeMessageBox::RunMessageBox("请输入正确的购进人员");
		else
			CRuntimeMessageBox::RunMessageBox("请输入正确的支出人员");
	}
	m_telPhone_ctrl.GetWindowText(m_date.m_tellPhone);
	if(m_date.m_tellPhone.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的电话号码");
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);
}


void CDialog_Check::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
