// CDialog_UserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_UserInfo.h"
#include "CControl_user.h"
// CDialog_UserInfo �Ի���

IMPLEMENT_DYNAMIC(CDialog_UserInfo, CDialog)

CDialog_UserInfo::CDialog_UserInfo(const bool &isSelf/* = true*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_UserInfo::IDD, pParent)
{
	m_isSelf = isSelf;
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

BOOL CDialog_UserInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_isSelf )
	{
		if(!m_date.GetId().empty())
		{
			m_name_ctrl.SetWindowText(m_date.m_name);
			m_cName_ctrl.SetWindowText(m_date.m_companyName);
			m_age_ctrl.SetWindowText(m_date.m_age);
			m_phone_ctrl.SetWindowText(m_date.m_tellPhone);
			m_email_ctrl.SetWindowText(m_date.m_email);
			m_detail_ctrl.SetWindowText(m_date.m_detail);
		}
	}
	else 
	{
		CControl_user tmp;
		if (tmp.Search())
		{
			m_name_ctrl.SetWindowText(CControl_bace::s_userInfo.m_name);
			m_cName_ctrl.SetWindowText(CControl_bace::s_userInfo.m_companyName);
			m_age_ctrl.SetWindowText(CControl_bace::s_userInfo.m_age);
			m_phone_ctrl.SetWindowText(CControl_bace::s_userInfo.m_tellPhone);
			m_email_ctrl.SetWindowText(CControl_bace::s_userInfo.m_email);
			m_detail_ctrl.SetWindowText(CControl_bace::s_userInfo.m_detail);
		}
	}
	return FALSE;
}


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

	CControl_user tmp;
	tmp.SetData(&m_date);
	if (tmp.Save(m_isSelf))
	{
		CRuntimeMessageBox::RunMessageBox("����ɹ���");

		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("����ʧ�ܣ�");
	}
}


void CDialog_UserInfo::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CDialog_UserInfo::SetDate( const CDate_User &date )
{
	m_date = date;
}
