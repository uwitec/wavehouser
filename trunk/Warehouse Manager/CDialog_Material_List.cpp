// CDialog_Material_List.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material_List.h"
#include "afxdialogex.h"

// CDialog_Material_List 对话框

IMPLEMENT_DYNAMIC(CDialog_Material_List, CDialogEx)

CDialog_Material_List::CDialog_Material_List(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Material_List::IDD, pParent)
{

}

CDialog_Material_List::~CDialog_Material_List()
{
}

void CDialog_Material_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_manufacturer_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_modal_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_price_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_unit_ctrl);
	DDX_Control(pDX, IDC_EDIT5, m_keyword_ctrl);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDialog_Material_List, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Material_List::OnBnClickedSearchBtn)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDialog_Material_List 消息处理程序

BOOL CDialog_Material_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitList();
	return TRUE;
}

void CDialog_Material_List::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name_ctrl.GetWindowText(m_searcher.m_name);
	if(m_searcher.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的材料名字");
		return;
	}
	m_modal_ctrl.GetWindowText(m_searcher.m_modal);
	if(m_searcher.m_modal.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的材料型号");
		return;
	}
	m_manufacturer_ctrl.GetWindowText(m_searcher.m_manufacturer);
	if(m_searcher.m_manufacturer.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的生产厂家");
		return;
	}
	m_unit_ctrl.GetWindowText(m_searcher.m_unit);
	if(m_searcher.m_unit.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的单位");
		return;
	}
	m_price_ctrl.GetWindowText(m_searcher.m_price);
	if(m_searcher.m_price.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的单价");
		return;
	}
	CString tmp;
	m_keyword_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_stringTranser.CStringtostring(tmp));
}


void CDialog_Material_List::InitList()
{
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, GetWindowLong(m_list.m_hWnd, GWL_STYLE) |LVS_REPORT);
	DWORD dwStyles = m_list.GetExStyle();
	dwStyles &= ~LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, _T( "序号" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T( "材料名称" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T( "生产厂家" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T( "材料型号" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T( "采购单位" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T( "采购价格" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, _T( "材料详细" ),LVCFMT_LEFT, 500);
}
