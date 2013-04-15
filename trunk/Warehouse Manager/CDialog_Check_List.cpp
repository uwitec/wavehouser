// CDialog_Check_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_List.h"
#include "CControl_Export.h"
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
END_MESSAGE_MAP()


// CDialog_Check_List ��Ϣ�������

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
	m_mName_ctrl.GetWindowText(m_searcher.m_name);
	if(m_searcher.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ�������");
		return;
	}
	m_checkModal_ctrl.GetWindowText(m_searcher.m_modal);
	if(m_searcher.m_modal.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ������");
		return;
	}
	m_class_ctrl.GetWindowText(m_searcher.m_class);
	if(m_searcher.m_class.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ���");
		return;
	}
	m_user_ctrl.GetWindowText(m_searcher.m_pName);
	if(m_searcher.m_pName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ����Ա");
		return;
	}
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
}

void CDialog_Check_List::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CControl_Export::ExportCheck()
}
