// CDialog_Check_List.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_List.h"
#include "CControl_Export.h"
#include "CControl_check.h"
#include "CControl_user.h"
#include "CControl_class.h"
#include "CDialog_Check.h"
#include "CDialog_CLass.h"
#include "CDialog_UserInfo.h"
#include "CDialog_Material.h"
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
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDialog_Check_List::OnNMRclickList1)
	ON_COMMAND(ID_CLISTMENU2_ADDIN, &CDialog_Check_List::OnClistmenu2Addin)
	ON_COMMAND(ID_CLISTMENU2_ADDOUT, &CDialog_Check_List::OnClistmenu2Addout)
	ON_COMMAND(ID_CLISTMENU2_SCLASS, &CDialog_Check_List::OnClistmenu2Sclass)
	ON_COMMAND(ID_CLISTMENU2_SUSER, &CDialog_Check_List::OnClistmenu2Suser)
	ON_COMMAND(ID_CLISTMENU2_SMATERIAL, &CDialog_Check_List::OnClistmenu2Smaterial)
	ON_COMMAND(ID_CLISTMENU2_EDIT, &CDialog_Check_List::OnClistmenu2Edit)
	ON_COMMAND(ID_CLISTMENU2_DEL, &CDialog_Check_List::OnClistmenu2Del)
	ON_BN_CLICKED(IDC_CHECK1, &CDialog_Check_List::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CDialog_Check_List 消息处理程序

BOOL CDialog_Check_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_isExport)
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
	InitList();
	InitComobox();

	m_checkModal_ctrl.AddString(_T("全部"));
	m_checkModal_ctrl.AddString(_T("入库"));
	m_checkModal_ctrl.AddString(_T("出库"));
	m_checkModal_ctrl.SetCurSel(0);


	return TRUE;
}

void CDialog_Check_List::InitComobox(const int &initFlag )
{
	CDate_search condition;
	if(initFlag == -1 || initFlag == 1)
	{
		CControl_user tmpu;
		m_allUser = tmpu.SearchList_UserInfo(condition);
		
		m_user_ctrl.Clear();
		for (int i = 0;i< m_allUser.size() ;i++)
		{
			m_user_ctrl.AddString(m_allUser[i].m_name);
		}
		m_user_ctrl.InsertString(0,_T("不限"));
		m_user_ctrl.SetCurSel(0);
	}
	if (initFlag == -1 || initFlag == 2)
	{
		CControl_class tmpc;
		m_allClass = tmpc.SearchList_Class(condition);
		m_class_ctrl.Clear();
		for (int i = 0;i< m_allClass.size() ;i++)
		{
			m_class_ctrl.AddString(m_allClass[i].m_name);
		}
		m_class_ctrl.InsertString(0,_T("不限"));
		m_class_ctrl.SetCurSel(0);
	}
}

void CDialog_Check_List::InitList()
{
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, GetWindowLong(m_list.m_hWnd, GWL_STYLE) |LVS_REPORT);
	DWORD dwStyles = m_list.GetExStyle();
	dwStyles &= ~LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.InsertColumn(0, _T( "序号" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T( "类型" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, _T( "材料名称" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T( "部门" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T( "操作员" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T( "材料型号" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, _T( "联系电话" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, _T( "数量" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(8, _T( "金额" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(9, _T( "日期" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(10, _T( "详细" ),LVCFMT_LEFT, 500);
}

void CDialog_Check_List::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_searcher.m_checkModal = m_checkModal_ctrl.GetCurSel() == 0 ? _T("-1"):m_checkModal_ctrl.GetCurSel() == 1 ?_T("1"):_T("0");
	m_mName_ctrl.GetWindowText(m_searcher.m_name);
	m_searcher.m_class = m_class_ctrl.GetCurSel() == 0 ? _T("") : m_dateChange.stringToCstring(m_allClass.at(m_class_ctrl.GetCurSel() - 1).GetId());
	m_searcher.m_pName = m_user_ctrl.GetCurSel() == 0 ? _T("") : m_dateChange.stringToCstring(m_allUser.at(m_user_ctrl.GetCurSel() - 1).GetId());


	if(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK1 ))
	{
		m_tBegin_ctrl.GetWindowText(m_searcher.m_tBegin);
		m_tEnd_ctrl.GetWindowText(m_searcher.m_tEnd);
		if(m_searcher.m_tBegin.IsEmpty() || m_searcher.m_tEnd.IsEmpty())
		{
			CRuntimeMessageBox::RunMessageBox("请输入正确的时间");
			return;
		}
	}
	else
	{
		m_searcher.m_aBegin.Empty();
		m_searcher.m_tEnd.Empty();
	}
	CString tmp;
	m_keyWord_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_dateChange.CStringtostring(tmp));

	CControl_check tmpc;
	m_searchDates = tmpc.SearchList_Check(m_searcher);

	ListCtrlShow();

	GetDlgItem(IDC_BUTTON5)->EnableWindow(!m_searchDates.empty());
}

void CDialog_Check_List::OnBnClickedExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CControl_Export::ExportCheck(m_searchDates);
}

void CDialog_Check_List::ListCtrlShow()
{
	m_list.DeleteAllItems();
	for(int i = 0;i<m_searchDates.size();i++)
	{
		int newRow = m_list.InsertItem(i,_T("新行"));
		CString tmp;
		tmp.Format(_T("%d"),i+1);
		m_list.SetItemText(newRow,0,tmp);
		if(m_searchDates[i].m_checkModal == 1)
			m_list.SetItemText(newRow,1,_T("入库"));
		else
			m_list.SetItemText(newRow,1,_T("出库"));
		m_list.SetItemText(newRow,2,m_searchDates[i].m_material.m_name);
		m_list.SetItemText(newRow,3,m_searchDates[i].m_class.m_name);
		m_list.SetItemText(newRow,4,m_searchDates[i].m_userInfo.m_name);
		m_list.SetItemText(newRow,5,m_searchDates[i].m_material.m_modal);
		m_list.SetItemText(newRow,6,m_searchDates[i].m_tellPhone);
		tmp.Format(_T("%d"),m_searchDates[i].m_num);
		m_list.SetItemText(newRow,7,tmp);
		tmp.Format(_T("%.2lf"),m_searchDates[i].m_total);
		m_list.SetItemText(newRow,8,tmp);
		m_list.SetItemText(newRow,9,m_searchDates[i].m_time);
		m_list.SetItemText(newRow,10,m_searchDates[i].m_detail);
	}
}

void CDialog_Check_List::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu; 
	POINT pt = {0}; 
	GetCursorPos(&pt);//得到鼠标点击位置 
	menu.LoadMenu(IDR_LIST_MENU2);//菜单资源ID 
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR; 
	if(pNMListView->iItem != -1) 
	{ 
		m_changeDate = m_searchDates.at(pNMListView->iItem);
	} 
	else
	{
		menu.EnableMenuItem(ID_CLISTMENU2_SCLASS,TRUE);
		menu.EnableMenuItem(ID_CLISTMENU2_SUSER,TRUE);
		menu.EnableMenuItem(ID_CLISTMENU2_SMATERIAL,TRUE);
		menu.EnableMenuItem(ID_CLISTMENU2_EDIT,TRUE);
		menu.EnableMenuItem(ID_CLISTMENU2_DEL,TRUE);
	}
	menu.GetSubMenu(0)->TrackPopupMenu(0,pt.x,pt.y,this);     //m_newListCtrl是CListCtrl对象

	*pResult = 0;
}

void CDialog_Check_List::OnClistmenu2Addin()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Check dlg;
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenu2Addout()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Check dlg(FALSE);
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenu2Edit()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Check dlg;

	dlg.SetDate(m_changeDate);
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenu2Del()
{
	// TODO: 在此添加命令处理程序代码
	CControl_check tmp;
	tmp.SetData(&m_changeDate);
	if(tmp.Delete())
	{
		CRuntimeMessageBox::RunMessageBox("删除成功！");
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("删除失败！");
	}
}

void CDialog_Check_List::OnClistmenu2Sclass()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_CLass dlg;
	dlg.SetDate(m_changeDate.m_class);
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenu2Suser()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_UserInfo dlg(false);
	dlg.SetDate(m_changeDate.m_userInfo);
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenu2Smaterial()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Material dlg;
	dlg.SetDate(m_changeDate.m_material);
	dlg.DoModal();
}

void CDialog_Check_List::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	//if(GetDlgItem(IDC_CHECK1)->check)
	m_tBegin_ctrl.EnableWindow(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK1 ));
	m_tEnd_ctrl.EnableWindow(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK1 ));
}
