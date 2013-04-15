// CDialog_Check_List.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_List.h"
#include "CControl_Export.h"
//#include "afxdialogex.h"


// CDialog_Check_List 对话框

IMPLEMENT_DYNAMIC(CDialog_Check_List, CDialog)

CDialog_Check_List::CDialog_Check_List(const bool &isExpot /*= false*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Check_List::IDD, pParent)
{
	m_isExport = isExpot;
}

CDialog_Check_List::~CDialog_Check_List()
{
}

void CDialog_Check_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_checkModal_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_mName_ctrl);
	DDX_Control(pDX, IDC_COMBO2, m_class_ctrl);
	DDX_Control(pDX, IDC_COMBO3, m_user_ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_tBegin_ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_tEnd_ctrl);
	DDX_Control(pDX, IDC_EDIT5, m_keyWord_ctrl);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDialog_Check_List, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Check_List::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialog_Check_List::OnBnClickedExport)
END_MESSAGE_MAP()


// CDialog_Check_List 消息处理程序

BOOL CDialog_Check_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_isExport)
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
	InitList();
	return TRUE;
}

void CDialog_Check_List::InitList()
{
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, GetWindowLong(m_list.m_hWnd, GWL_STYLE) |LVS_REPORT);
	DWORD dwStyles = m_list.GetExStyle();
	dwStyles &= ~LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.InsertColumn(0, _T( "序号" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T( "收支" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, _T( "材料名称" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T( "部门" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T( "操作员" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T( "材料型号" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, _T( "数量" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, _T( "金额" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(8, _T( "日期" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(9, _T( "详细" ),LVCFMT_LEFT, 500);
}

void CDialog_Check_List::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mName_ctrl.GetWindowText(m_searcher.m_name);
	if(m_searcher.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的材料名字");
		return;
	}
	m_checkModal_ctrl.GetWindowText(m_searcher.m_modal);
	if(m_searcher.m_modal.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的类型");
		return;
	}
	m_class_ctrl.GetWindowText(m_searcher.m_class);
	if(m_searcher.m_class.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的部门");
		return;
	}
	m_user_ctrl.GetWindowText(m_searcher.m_pName);
	if(m_searcher.m_pName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的人员");
		return;
	}
	m_tBegin_ctrl.GetWindowText(m_searcher.m_tBegin);
	m_tEnd_ctrl.GetWindowText(m_searcher.m_tEnd);
	if(m_searcher.m_tBegin.IsEmpty() || m_searcher.m_tEnd.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的时间");
		return;
	}
	else
	{
	}
	CString tmp;
	m_keyWord_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_dateChange.CStringtostring(tmp));
}

void CDialog_Check_List::OnBnClickedExport()
{
	// TODO: 在此添加控件通知处理程序代码
	//CControl_Export::ExportCheck()
}
