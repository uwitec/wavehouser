// CDialog_Material_List.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material_List.h"
#include "CControl_Export.h"
#include "CControl_material.h"
#include "CDialog_Material.h"
//#include "afxdialogex.h"

// CDialog_Material_List 对话框

IMPLEMENT_DYNAMIC(CDialog_Material_List, CDialog)

CDialog_Material_List::CDialog_Material_List(const bool &isExpot /*= false*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Material_List::IDD, pParent)
{
	m_isExport = isExpot;
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
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_Material_List::OnBnClickedExport)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDialog_Material_List::OnNMRclickList1)
	ON_COMMAND(ID_CLISTMENU_ADD, &CDialog_Material_List::OnClistmenuAdd)
	ON_COMMAND(ID_CLISTMENU_EDIT, &CDialog_Material_List::OnClistmenuEdit)
	ON_COMMAND(ID_CLISTMENU_DEL, &CDialog_Material_List::OnClistmenuDel)
END_MESSAGE_MAP()


// CDialog_Material_List 消息处理程序

BOOL CDialog_Material_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_isExport)
		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
	InitList();
	return TRUE;
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

void CDialog_Material_List::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name_ctrl.GetWindowText(m_searcher.m_name);
	m_modal_ctrl.GetWindowText(m_searcher.m_modal);
	m_manufacturer_ctrl.GetWindowText(m_searcher.m_manufacturer);
	m_unit_ctrl.GetWindowText(m_searcher.m_unit);
	m_price_ctrl.GetWindowText(m_searcher.m_price);
	CString tmp;
	m_keyword_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_stringTranser.CStringtostring(tmp));

	CControl_material tmps;
	m_searchDates = tmps.SearchList_Material(m_searcher);

	ListCtrlShow();
	
	GetDlgItem(IDC_BUTTON4)->EnableWindow(!m_searchDates.empty());
}

void CDialog_Material_List::ListCtrlShow()
{
	m_list.DeleteAllItems();
	for(int i = 0;i<m_searchDates.size();i++)
	{
		int newRow = m_list.InsertItem(i,_T("新行"));
		CString tmp;
		tmp.Format(_T("%d"),i+1);
		m_list.SetItemText(newRow,0,tmp);
		m_list.SetItemText(newRow,1,m_searchDates[i].m_name);
		m_list.SetItemText(newRow,2,m_searchDates[i].m_manufacturer);
		m_list.SetItemText(newRow,3,m_searchDates[i].m_modal);
		m_list.SetItemText(newRow,4,m_searchDates[i].m_unit);
		m_list.SetItemText(newRow,5,m_searchDates[i].m_price);
		m_list.SetItemText(newRow,6,m_searchDates[i].m_detail);
	}
}


void CDialog_Material_List::OnBnClickedExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CControl_Export::ExportMaterial(m_searchDates);
}

void CDialog_Material_List::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu; 
	POINT pt = {0}; 
	GetCursorPos(&pt);//得到鼠标点击位置 
	menu.LoadMenu(IDR_LIST_MENU);//菜单资源ID 
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR; 
	if(pNMListView->iItem != -1) 
	{ 
		m_changeDate = m_searchDates.at(pNMListView->iItem);
	} 
	else
	{
		menu.EnableMenuItem(ID_CLISTMENU_EDIT,TRUE);
		menu.EnableMenuItem(ID_CLISTMENU_DEL,TRUE);
	}
	menu.GetSubMenu(0)->TrackPopupMenu(0,pt.x,pt.y,this);   

	*pResult = 0;
}

void CDialog_Material_List::OnClistmenuAdd()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Material dlg;
	dlg.DoModal();
}

void CDialog_Material_List::OnClistmenuEdit()
{
	// TODO: 在此添加命令处理程序代码
	if(m_changeDate.GetId().empty())
		return;
	CDialog_Material dlg;
	dlg.SetDate(m_changeDate);
	dlg.DoModal();
}

void CDialog_Material_List::OnClistmenuDel()
{
	// TODO: 在此添加命令处理程序代码
	CControl_material tmp;
	tmp.SetData(&m_changeDate);
	tmp.Delete();
}
