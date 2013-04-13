// CDialog_Material.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material.h"


// CDialog_Material �Ի���

IMPLEMENT_DYNAMIC(CDialog_Material, CDialog)

CDialog_Material::CDialog_Material(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Material::IDD, pParent)
{

}

CDialog_Material::~CDialog_Material()
{
}

void CDialog_Material::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_modal_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_manufacturer_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_unit_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_price_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Material, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_Material::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_Material::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_Material ��Ϣ�������


void CDialog_Material::OnBnClickedBtbSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_name_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ�������");
		return;
	}
	m_modal_ctrl.GetWindowText(m_date.m_modal);
	if(m_date.m_modal.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ����ͺ�");
		return;
	}
	m_manufacturer_ctrl.GetWindowText(m_date.m_manufacturer);
	if(m_date.m_manufacturer.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ����������");
		return;
	}
	m_unit_ctrl.GetWindowText(m_date.m_unit);
	if(m_date.m_unit.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ�λ");
		return;
	}
	m_price_ctrl.GetWindowText(m_date.m_price);
	if(m_date.m_price.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ���");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);
}


void CDialog_Material::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
