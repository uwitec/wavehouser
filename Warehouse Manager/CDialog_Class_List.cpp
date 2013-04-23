// CDialog_Class_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Class_List.h"
#include "CDialog_CLass.h"
#include "CControl_class.h"
#include "CControl_Export.h"
// CDialog_Class_List �Ի���

IMPLEMENT_DYNAMIC(CDialog_Class_List, CDialog)

CDialog_Class_List::CDialog_Class_List(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Class_List::IDD, pParent)
{

}

CDialog_Class_List::~CDialog_Class_List()
{
}

void CDialog_Class_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_cName_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_pName_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_coName_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_tellPhone);
	DDX_Control(pDX, IDC_EDIT5, m_keyWord_ctrl);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDialog_Class_List, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDialog_Class_List::OnNMRclickList1)
	ON_COMMAND(ID_CLISTMENU_ADD, &CDialog_Class_List::OnClistmenuAdd)
	ON_COMMAND(ID_CLISTMENU_EDIT, &CDialog_Class_List::OnClistmenuEdit)
	ON_COMMAND(ID_CLISTMENU_DEL, &CDialog_Class_List::OnClistmenuDel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Class_List::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_Class_List::OnBnClickedExport)
END_MESSAGE_MAP()


// CDialog_Class_List ��Ϣ�������

BOOL CDialog_Class_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	//if(!m_isExport)
	//	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

	InitList();
	return TRUE;
}

void CDialog_Class_List::InitList()
{
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, GetWindowLong(m_list.m_hWnd, GWL_STYLE) |LVS_REPORT);
	DWORD dwStyles = m_list.GetExStyle();
	dwStyles &= ~LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, _T( "���" ),LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T( "��������" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T( "������" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T( "��������" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T( "��ϵ��" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T( "��ϵ�绰" ),LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, _T( "������ϸ" ),LVCFMT_LEFT, 500);
}

void CDialog_Class_List::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	menu.GetSubMenu(0)->TrackPopupMenu(0,pt.x,pt.y,this);   

	*pResult = 0;
}

void CDialog_Class_List::OnClistmenuAdd()
{
	// TODO: �ڴ���������������
	CDialog_CLass dlg;
	dlg.DoModal();
}

void CDialog_Class_List::OnClistmenuEdit()
{
	// TODO: �ڴ���������������
	CDialog_CLass dlg;
	dlg.SetDate(m_changeDate);
	dlg.DoModal();
}

void CDialog_Class_List::OnClistmenuDel()
{
	// TODO: �ڴ���������������
	CControl_class tmp;
	tmp.SetData(&m_changeDate);
	tmp.Delete();
}

void CDialog_Class_List::OnBnClickedSearchBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cName_ctrl.GetWindowText(m_searcher.m_name);
	m_pName_ctrl.GetWindowText(m_searcher.m_cpName);
	m_coName_ctrl.GetWindowText(m_searcher.m_coName);
	m_tellPhone.GetWindowText(m_searcher.m_tellPhone);
	CString tmp;
	m_keyWord_ctrl.GetWindowText(tmp);
	m_searcher.SetKeyword(m_stringTranser.CStringtostring(tmp));

	CControl_class tmps;
	m_searchDates = tmps.SearchList_Class(m_searcher);

	ListCtrlShow();

	GetDlgItem(IDC_BUTTON4)->EnableWindow(!m_searchDates.empty());
}

void CDialog_Class_List::ListCtrlShow()
{
	m_list.DeleteAllItems();
	for(int i = 0;i<m_searchDates.size();i++)
	{
		int newRow = m_list.InsertItem(i,_T("����"));
		CString tmp;
		tmp.Format(_T("%d"),i+1);
		m_list.SetItemText(newRow,0,tmp);
		m_list.SetItemText(newRow,1,m_searchDates[i].m_name);
		m_list.SetItemText(newRow,2,m_searchDates[i].m_pName);
		m_list.SetItemText(newRow,3,m_searchDates[i].m_num);
		m_list.SetItemText(newRow,4,m_searchDates[i].m_contact);
		m_list.SetItemText(newRow,5,m_searchDates[i].m_tellPhone);
		m_list.SetItemText(newRow,6,m_searchDates[i].m_detail);
	}
}
void CDialog_Class_List::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(CControl_Export::ExportClass(m_searchDates))
		CRuntimeMessageBox::RunMessageBox("�����ɹ���");
	else
		CRuntimeMessageBox::RunMessageBox("����ʧ�ܣ�");
}
