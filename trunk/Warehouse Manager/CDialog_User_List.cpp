// CDialog_User_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_User_List.h"
#include "CControl_Export.h"
#include "CControl_user.h"
#include "CDialog_UserInfo.h"
// CDialog_User_List �Ի���

IMPLEMENT_DYNAMIC(CDialog_User_List, CDialog)

CDialog_User_List::CDialog_User_List( const bool &isExpot /*= false*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_User_List::IDD, pParent)
{
	m_isExport = isExpot;
}

CDialog_User_List::~CDialog_User_List()
{
}

void CDialog_User_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_phone_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_aBegin_ctrl);
	DDX_Control(pDX, IDC_EDIT9, m_aEnd_ctrl);
	DDX_Control(pDX, IDC_EDIT10, m_email_ctrl);
	DDX_Control(pDX, IDC_EDIT5, m_keyWord_ctrl);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDialog_User_List, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_User_List::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_User_List::OnBnClickedExport)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDialog_User_List::OnNMRclickList1)
	ON_COMMAND(ID_CLISTMENU_ADD, &CDialog_User_List::OnClistmenuAdd)
	ON_COMMAND(ID_CLISTMENU_EDIT, &CDialog_User_List::OnClistmenuEdit)
	ON_COMMAND(ID_CLISTMENU_DEL, &CDialog_User_List::OnClistmenuDel)
END_MESSAGE_MAP()


// CDialog_User_List ��Ϣ�������

BOOL CDialog_User_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_isExport)
		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

	InitList();
	return TRUE;
}

void CDialog_User_List::InitList()
{
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, GetWindowLong(m_list.m_hWnd, GWL_STYLE) |LVS_REPORT);
	DWORD dwStyles = m_list.GetExStyle();
	dwStyles &= ~LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, _T( "���" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T( "����" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, _T( "��˾" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T( "����" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T( "�绰" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T( "Email" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, _T( "��ϸ" ),LVCFMT_LEFT, 500);
}

void CDialog_User_List::OnBnClickedSearchBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_name_ctrl.GetWindowText(m_searcher.m_name);
	m_phone_ctrl.GetWindowText(m_searcher.m_phone);
	m_email_ctrl.GetWindowText(m_searcher.m_email);
	m_aBegin_ctrl.GetWindowText(m_searcher.m_aBegin);
	m_aEnd_ctrl.GetWindowText(m_searcher.m_aEnd);
	if(m_searcher.m_aBegin.IsEmpty())
	{
		m_searcher.m_aBegin = _T("0");
	}
	if(m_searcher.m_aEnd.IsEmpty())
	{
		m_searcher.m_aEnd = _T("0");
	}
	CString tmp;
	m_keyWord_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_dateChange.CStringtostring(tmp));

	CControl_user tmpc;
	m_searchDates = tmpc.SearchList_UserInfo(m_searcher);

	ListCtrlShow();

	GetDlgItem(IDC_BUTTON4)->EnableWindow(!m_searchDates.empty());
}

void CDialog_User_List::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	vector<CDate_User> dates;
// 	for(int i=0;i<2;i++)
// 	{
// 		CDate_User tmp;
// 		tmp.m_name = _T("���մ�");
// 		tmp.m_companyName = _T("���մ�");
// 		tmp.m_age = _T("11");
// 		tmp.m_tellPhone = _T("12321312312312");
// 		tmp.m_email = _T("sdadA2@163.com");
// 		tmp.m_detail = _T("dsad�������Ĵ��մ��ɨ��ɨ");
// 		dates.push_back(tmp);
// 	}
	CControl_Export::ExportUser(m_searchDates);
}

void CDialog_User_List::ListCtrlShow()
{
	m_list.DeleteAllItems();
	for(int i = 0;i<m_searchDates.size();i++)
	{
		int newRow = m_list.InsertItem(i,_T("����"));
		CString tmp;
		tmp.Format(_T("%d"),i+1);
		m_list.SetItemText(newRow,0,tmp);
		m_list.SetItemText(newRow,1,m_searchDates[i].m_name);
		m_list.SetItemText(newRow,2,m_searchDates[i].m_companyName);
		m_list.SetItemText(newRow,3,m_searchDates[i].m_age);
		m_list.SetItemText(newRow,4,m_searchDates[i].m_tellPhone);
		m_list.SetItemText(newRow,5,m_searchDates[i].m_email);
		m_list.SetItemText(newRow,6,m_searchDates[i].m_detail);
	}
}

void CDialog_User_List::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu menu; 
	POINT pt = {0}; 
	GetCursorPos(&pt);//�õ������λ�� 
	menu.LoadMenu(IDR_LIST_MENU);//�˵���ԴID 
	menu.GetSubMenu(0)->TrackPopupMenu(0,pt.x,pt.y,this);     //m_newListCtrl��CListCtrl����

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

	*pResult = 0;
}

void CDialog_User_List::OnClistmenuAdd()
{
	// TODO: �ڴ���������������
	CDialog_UserInfo dlg(false);
	dlg.DoModal();
}

void CDialog_User_List::OnClistmenuEdit()
{
	// TODO: �ڴ���������������
	if (m_changeDate.GetId().empty())
		return ;
	CDialog_UserInfo dlg(false);

	dlg.SetDate(m_changeDate);
	dlg.DoModal();
}

void CDialog_User_List::OnClistmenuDel()
{
	// TODO: �ڴ���������������
	CControl_user tmp;
	tmp.SetData(&m_changeDate);
	tmp.Delete();
}
