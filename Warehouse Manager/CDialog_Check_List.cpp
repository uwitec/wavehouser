// CDialog_Check_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_List.h"
#include "CControl_Export.h"
#include "CControl_check.h"
#include "CControl_user.h"
#include "CControl_class.h"
#include "CDialog_Check.h"
//#include "afxdialogex.h"


// CDialog_Check_List �Ի���

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
	ON_COMMAND(ID_CLISTMENU_ADD, &CDialog_Check_List::OnClistmenuAdd)
	ON_COMMAND(ID_CLISTMENU_EDIT, &CDialog_Check_List::OnClistmenuEdit)
	ON_COMMAND(ID_CLISTMENU_DEL, &CDialog_Check_List::OnClistmenuDel)
END_MESSAGE_MAP()


// CDialog_Check_List ��Ϣ�������

BOOL CDialog_Check_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_isExport)
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
	InitList();
	InitComobox();

	m_checkModal_ctrl.AddString(_T("����"));
	m_checkModal_ctrl.AddString(_T("֧��"));
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
		m_class_ctrl.SetCurSel(0);
	}
}

void CDialog_Check_List::InitList()
{
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, GetWindowLong(m_list.m_hWnd, GWL_STYLE) |LVS_REPORT);
	DWORD dwStyles = m_list.GetExStyle();
	dwStyles &= ~LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.InsertColumn(0, _T( "���" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T( "��֧" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, _T( "��������" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T( "����" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T( "����Ա" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T( "�����ͺ�" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, _T( "����" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, _T( "���" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(8, _T( "����" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(9, _T( "��ϸ" ),LVCFMT_LEFT, 500);
}

void CDialog_Check_List::OnBnClickedSearchBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_searcher.m_checkModal = m_checkModal_ctrl.GetCurSel() == 0 ? _T("1"):_T("0");
	m_mName_ctrl.GetWindowText(m_searcher.m_name);
	m_searcher.m_class = m_dateChange.stringToCstring(m_allClass.at(m_class_ctrl.GetCurSel()).GetId());
	m_searcher.m_pName = m_dateChange.stringToCstring(m_allUser.at(m_user_ctrl.GetCurSel()).GetId());

	m_tBegin_ctrl.GetWindowText(m_searcher.m_tBegin);
	m_tEnd_ctrl.GetWindowText(m_searcher.m_tEnd);
	if(m_searcher.m_tBegin.IsEmpty() || m_searcher.m_tEnd.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ��ʱ��");
		return;
	}
	else
	{
	}
	CString tmp;
	m_keyWord_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_dateChange.CStringtostring(tmp));

	CControl_check tmpc;
	m_searchDates = tmpc.SearchList_Check(m_searcher);

	if (!m_searchDates.empty())
	{
		ListCtrlShow();
	}
}

void CDialog_Check_List::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CControl_Export::ExportCheck(m_searchDates);
}

void CDialog_Check_List::ListCtrlShow()
{

}

void CDialog_Check_List::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu menu; 
	POINT pt = {0}; 
	GetCursorPos(&pt);//�õ������λ�� 
	menu.LoadMenu(IDR_LIST_MENU);//�˵���ԴID 
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
	menu.GetSubMenu(0)->TrackPopupMenu(0,pt.x,pt.y,this);     //m_newListCtrl��CListCtrl����

	*pResult = 0;
}

void CDialog_Check_List::OnClistmenuAdd()
{
	// TODO: �ڴ���������������
	CDialog_Check dlg;
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenuEdit()
{
	// TODO: �ڴ���������������
	CDialog_Check dlg;
	
	dlg.SetDate(m_changeDate);
	dlg.DoModal();
}

void CDialog_Check_List::OnClistmenuDel()
{
	// TODO: �ڴ���������������
	CControl_check tmp;
	tmp.SetData(&m_changeDate);
	if(tmp.Delete())
	{
		CRuntimeMessageBox::RunMessageBox("ɾ���ɹ���");
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("ɾ��ʧ�ܣ�");
	}
}
