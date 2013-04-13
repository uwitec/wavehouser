// CDialog_Check_List.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_List.h"
#include "afxdialogex.h"


// CDialog_Check_List �Ի���

IMPLEMENT_DYNAMIC(CDialog_Check_List, CDialog)

CDialog_Check_List::CDialog_Check_List(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Check_List::IDD, pParent)
{

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
END_MESSAGE_MAP()


// CDialog_Check_List ��Ϣ�������

BOOL CDialog_Check_List::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
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
