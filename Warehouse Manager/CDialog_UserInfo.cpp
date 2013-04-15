// CDialog_UserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_UserInfo.h"

// CDialog_UserInfo �Ի���

IMPLEMENT_DYNAMIC(CDialog_UserInfo, CDialog)

CDialog_UserInfo::CDialog_UserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_UserInfo::IDD, pParent)
{

}

CDialog_UserInfo::~CDialog_UserInfo()
{
}

void CDialog_UserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_cName_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_age_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_phone_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_email_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_UserInfo, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_UserInfo::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_UserInfo::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_UserInfo ��Ϣ�������


void CDialog_UserInfo::OnBnClickedBtbSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_name_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ������");
		return;
	}
	m_cName_ctrl.GetWindowText(m_date.m_companyName);
	if(m_date.m_companyName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĺ�˾����");
		return;
	}
	m_age_ctrl.GetWindowText(m_date.m_age);
	if(m_date.m_age.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ������");
		return;
	}
	m_phone_ctrl.GetWindowText(m_date.m_tellPhone);
	if(m_date.m_tellPhone.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ绰");
		return;
	}
	m_email_ctrl.GetWindowText(m_date.m_email);
	if(m_date.m_email.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ��EMail");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);
}


void CDialog_UserInfo::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
