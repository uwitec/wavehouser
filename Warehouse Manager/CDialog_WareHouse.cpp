// CDialog_WareHouse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_WareHouse.h"
#include "CControl_warehouse.h"
//#include "afxdialogex.h"


// CDialog_WareHouse �Ի���

IMPLEMENT_DYNAMIC(CDialog_WareHouse, CDialog)

CDialog_WareHouse::CDialog_WareHouse(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_WareHouse::IDD, pParent)
{

}

CDialog_WareHouse::~CDialog_WareHouse()
{
}

void CDialog_WareHouse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_wName_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_cName_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_aName_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_tellPhone_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_email_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_WareHouse, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_WareHouse::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_WareHouse::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_WareHouse ��Ϣ�������


void CDialog_WareHouse::OnBnClickedBtbSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_wName_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳֿ�����");
		return;
	}
	m_cName_ctrl.GetWindowText(m_date.m_cname);
	if(m_date.m_cname.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĺ�˾����");
		return;
	}
	m_aName_ctrl.GetWindowText(m_date.m_aname);
	if(m_date.m_aname.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĺ���Ա����");
		return;
	}
	m_tellPhone_ctrl.GetWindowText(m_date.m_tell);
	if(m_date.m_tell.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ����ϵ�绰");
		return;
	}
	m_email_ctrl.GetWindowText(m_date.m_email);
	if(m_date.m_email.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�������ַ");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);

	CControl_warehouse tmpc;
	tmpc.SetData(&m_date);

	if(tmpc.Save())
		CRuntimeMessageBox::RunMessageBox("����ɹ���");
	else
		CRuntimeMessageBox::RunMessageBox("����ʧ�ܣ�");
}


void CDialog_WareHouse::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

BOOL CDialog_WareHouse::OnInitDialog()
{
	CDialog::OnInitDialog();

	CControl_warehouse tmp;
	if (tmp.Search())
	{
		m_wName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_name);
		m_cName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_cname);
		m_aName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_aname);
		m_tellPhone_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_tell);
		m_email_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_email);
		m_detail_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_detail);
	}
	return FALSE;
}
