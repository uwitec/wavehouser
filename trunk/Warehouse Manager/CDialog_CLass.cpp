// CDialog_CLass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_CLass.h"
#include "CControl_class.h"
//#include "afxdialogex.h"


// CDialog_CLass �Ի���

IMPLEMENT_DYNAMIC(CDialog_CLass, CDialog)

CDialog_CLass::CDialog_CLass(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_CLass::IDD, pParent)
{

}

CDialog_CLass::~CDialog_CLass()
{
}

void CDialog_CLass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_pName_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_num_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_telphone_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_contact_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_CLass, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_CLass::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_CLass::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_CLass ��Ϣ�������


void CDialog_CLass::OnBnClickedBtbSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_name_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ�������");
		return;
	}
	m_pName_ctrl.GetWindowText(m_date.m_pName);
	if(m_date.m_pName.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĸ�����");
		return;
	}
	m_num_ctrl.GetWindowText(m_date.m_num);
	if(m_date.m_num.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ�������");
		return;
	}
	m_telphone_ctrl.GetWindowText(m_date.m_tellPhone);
	if(m_date.m_tellPhone.IsEmpty() || m_date.m_tellPhone.SpanIncluding(_T("1234567890")) != m_date.m_tellPhone)
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ绰");
		return;
	}
	m_contact_ctrl.GetWindowText(m_date.m_contact);
	if(m_date.m_contact.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ����ϵ��");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);
	CControl_class tmp;
	tmp.SetData(&m_date);
	if (tmp.Save())
	{
		CRuntimeMessageBox::RunMessageBox("����ɹ���");

		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("����ʧ�ܣ�");
	}
}


void CDialog_CLass::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

BOOL CDialog_CLass::OnInitDialog()
{
	CDialog::OnInitDialog();

	return FALSE;
}
