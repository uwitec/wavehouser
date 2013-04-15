// CDialog_User_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_User_List.h"
#include "CControl_Export.h"


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
	if(m_searcher.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ����Ա����");
		return;
	}
	m_phone_ctrl.GetWindowText(m_searcher.m_phone);
	if(m_searcher.m_phone.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ绰");
		return;
	}
	m_email_ctrl.GetWindowText(m_searcher.m_email);
	if(m_searcher.m_email.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ���ʼ�");
		return;
	}
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
}

void CDialog_User_List::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vector<CDate_User> dates;
	for(int i=0;i<2;i++)
	{
		CDate_User tmp;
		tmp.m_name = _T("���մ�");
		tmp.m_companyName = _T("���մ�");
		tmp.m_age = _T("11");
		tmp.m_tellPhone = _T("12321312312312");
		tmp.m_email = _T("sdadA2@163.com");
		tmp.m_detail = _T("dsad�������Ĵ��մ��ɨ��ɨ");
		dates.push_back(tmp);
	}
	CControl_Export::ExportUser(dates);
}
